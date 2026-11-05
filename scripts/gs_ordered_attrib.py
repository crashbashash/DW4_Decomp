#!/usr/bin/env python3
"""Attribute each ordered state part of a GS dump frame to pack meshes (UV-multiset coverage).

Uses the ordered collector from gs_ordered_probe.py, so a part is a run of vertices between GIF
PRE boundaries / register-state changes, with its ALPHA and PRMODE.  A part made of a pack mesh
contains that mesh's per-vertex UV multiset; the top covering meshes are listed per part.
Animated (UV-scrolled) meshes will under-cover: an unmatched residue means the stream's UVs differ
from the pack's.  Meshes share an atlas, so a low-coverage runner-up is coincidental overlap.

Usage: python3 gs_ordered_attrib.py <dump.gs.zst> <FRAME-section index> [obj_dir]
"""
import collections, os, sys
from pathlib import Path

HERE = Path(__file__).resolve().parent
sys.path.insert(0, str(HERE))
import gs_ordered_probe as G

TOL = 1.5 / 4096.0


def mesh_hist(obj_dir):
    out = {}
    for fn in os.listdir(obj_dir):
        if fn.startswith('model_') and fn.endswith('.obj'):
            c = collections.Counter()
            for line in open(os.path.join(obj_dir, fn)):
                if line.startswith('vt'):
                    t = line[2:].split()
                    c[(round(float(t[0]), 5), round(float(t[1]), 5))] += 1
            out[fn[len('model_'):-len('.obj')]] = c
    return out


def main():
    path, section = sys.argv[1], int(sys.argv[2])
    obj_dir = sys.argv[3] if len(sys.argv) > 3 else str(HERE.parent / '../local/tools/gs/obj620')
    mesh = mesh_hist(obj_dir)
    keys = list({k for c in mesh.values() for k in c})

    def snap(u, v):
        best, bd = None, TOL * TOL
        for p in keys:
            d = (p[0] - u) ** 2 + (p[1] - v) ** 2
            if d < bd:
                best, bd = p, d
        return best

    _, frames = G.collect(path)
    for ri, run in enumerate(frames[section]['runs']):
        verts, begin, part = run['verts'], 0, 0
        for end in range(1, len(verts) + 1):
            if end != len(verts) and verts[end][8] == verts[begin][8]:
                continue
            sub = verts[begin:end]
            uv = collections.Counter()
            for v in sub:
                if v[6]:
                    s = snap(round(v[4] / v[6], 5), round(v[5] / v[6], 5))
                    if s:
                        uv[s] += 1
            scored = sorted(((sum(min(c, m[q]) for q, c in uv.items() if q in m), n, sum(m.values()))
                             for n, m in mesh.items()), reverse=True)
            st = sub[0][8]
            print('run%d part%d verts=%d ALPHA=%#x PRMODE=%#x' % (ri, part, len(sub), st[0x42], st[0x1b]))
            for n, name, tot in scored[:6]:
                if n:
                    print('    %-22s cover %4d / %4d (mesh nv %d)' % (name, n, len(sub), tot))
            begin, part = end, part + 1


if __name__ == '__main__':
    main()
