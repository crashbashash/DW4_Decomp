#!/usr/bin/env python3
"""Compare the complete exported created-summary glyph and label triangle sets.

This validates the summary foreground against one retail GS vsync interval.
It does not assert full-frame/background, message-window or animation parity.
Export with test_mainmenu ROMS EXISTING_PRIVATE_DIRECTORY [--gpu WIDTH HEIGHT].
"""
import argparse
import csv
import hashlib
import itertools
import json
from pathlib import Path
import sys

import numpy as np
from PIL import Image

sys.path.insert(0, str(Path(__file__).resolve().parents[2] / 'scripts'))
import gsdump


def triangles(primitive, vertices):
    kind = primitive & 7
    if kind == 3:
        return [vertices[i:i+3] for i in range(0, len(vertices)-2, 3)]
    if kind == 4:
        return [vertices[i:i+3] for i in range(len(vertices)-2)]
    if kind == 5:
        return [[vertices[0], vertices[i], vertices[i+1]] for i in range(1, len(vertices)-1)]
    raise AssertionError(f'unsupported summary primitive {kind}')


def match_triangles(native, retail):
    assert len(native) == len(retail), f"triangle count {len(native)} != {len(retail)}"
    edges = []
    for n in native:
        candidates = []
        for i,r in enumerate(retail):
            for permutation in itertools.permutations(range(3)):
                v = r[list(permutation)]
                delta = np.abs(n-v)
                if (delta[:,:2] <= .126).all() and (delta[:,2:4] < .002).all() and \
                   (delta[:,4] <= 1e-8+abs(v[:,4])*.00002).all() and (delta[:,5:] == 0).all():
                    candidates.append((i,float(delta[:,:2].max())))
                    break
        edges.append(candidates)
    assignment = {}
    def claim(i, visited):
        for r,error in edges[i]:
            if r in visited:
                continue
            visited.add(r)
            if r not in assignment or claim(assignment[r][0],visited):
                assignment[r] = (i,error)
                return True
        return False
    assert all(claim(i,set()) for i in range(len(native))), 'unmatched complete triangles'
    return max(error for _,error in assignment.values())


def main():
    p = argparse.ArgumentParser(description=__doc__)
    p.add_argument('--dump', required=True)
    p.add_argument('--native-dir', required=True, type=Path)
    p.add_argument('--frame', type=int, default=0)
    p.add_argument('--retail-vsync', type=int, default=1)
    p.add_argument('--json', type=Path)
    a = p.parse_args()
    rows = list(csv.DictReader((a.native_dir / f'root-{a.frame}.tsv').open(), delimiter='\t'))
    groups = {}
    for part, index in sorted({(r['part'], r['texture']) for r in rows}):
        image = Image.open(a.native_dir / f'root-{a.frame}-{part}-{index}.png').convert('RGBA')
        key = (hashlib.sha256(image.tobytes()).hexdigest(), image.size)
        selected = [r for r in rows if (r['part'], r['texture']) == (part, index)]
        values = np.array([[float(r[k]) for k in ('x','y','u','v','q','r','g','b','a')] for r in selected])
        assert len(values) and len(values) % 3 == 0
        assert part in ('summary', 'labels'), 'unexpected export scope'
        groups[part] = {'key': key, 'native': list(values.reshape(-1,3,9)), 'retail': []}
    assert set(groups) == {'summary', 'labels'}, 'missing summary/labels group'
    dump = gsdump.read_dump(a.dump)
    state = gsdump.read_state(dump)
    offset = state['CTXT0.XYOFFSET']
    ox, oy = (offset & 65535)/16, ((offset >> 32) & 65535)/16
    textures = {}
    for draw in gsdump.draws(dump):
        if draw['vsync'] != a.retail_vsync or not draw['state']['PRIM_EFF'] & 16:
            continue
        tex = draw['state'].get(6, state['CTXT0.TEX0'])
        if tex not in textures:
            fields = gsdump.tex0_fields(tex)
            if fields['PSM'] != 19:
                textures[tex] = None
            else:
                rgba,w,h,_ = gsdump.texture_rgba(dump,tex)
                textures[tex] = (hashlib.sha256(rgba).hexdigest(), (w,h))
        for part, group in groups.items():
            if textures[tex] != group['key']:
                continue
            vertices = []
            for v in draw['verts']:
                s,t,q = v['ST']
                assert q
                vertices.append([v['XYZ'][0]/16-ox, v['XYZ'][1]/16-oy, s/q, t/q, q, *v['RGBA']])
            if not vertices:
                continue
            if part == 'summary' and not all(0 <= v[1] < 90 for v in vertices):
                continue
            group['retail'].extend(np.array(t) for t in triangles(draw['state']['PRIM_EFF'],vertices))
    report = {'scope': 'complete created-summary glyph/label triangle sets; other foreground/background unverified',
              'position_tolerance_px': .126, 'uv_tolerance': .002,
              'retail_vsync': a.retail_vsync, 'groups': {}}
    for part, group in groups.items():
        native, retail = group['native'], group['retail']
        assert len(native) == len(retail), f'{part}: triangle count {len(native)} != {len(retail)}'
        # Require a one-to-one assignment of complete triangles, so repeated
        # corners or duplicate submissions cannot hide missing retail geometry.
        error = match_triangles(native,retail)
        report['groups'][part] = {'triangles': len(native), 'vertices': len(native)*3,
            'texture_rgba_byte_exact': True, 'one_to_one_triangles': True,
            'max_position_error_px': error}
    print(json.dumps(report,indent=2))
    if a.json:
        a.json.write_text(json.dumps(report,indent=2)+'\n')


if __name__ == '__main__':
    main()
