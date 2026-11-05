#!/usr/bin/env python3
"""Compare complete character-menu cursor geometry at an explicitly sampled pose.

Export test_mainmenu_cursor ROMS DIRECTORY STATE SECONDS [WIDTH HEIGHT --gpu].
This requires one-to-one triangle, texture, XY/UV/Q and color agreement. It
validates geometry at that diagnostic pose, not live clock/transition parity.
"""
import argparse
import csv
import hashlib
import json
from pathlib import Path
import sys

import numpy as np
from PIL import Image
from verify_mainmenu_summary import triangles, match_triangles

sys.path.insert(0,str(Path(__file__).resolve().parents[2] / 'scripts'))
import gsdump


def main():
    p=argparse.ArgumentParser(description=__doc__)
    p.add_argument('--dump',required=True)
    p.add_argument('--native-dir',required=True,type=Path)
    p.add_argument('--state',required=True,choices=('create','call','yes','no',
        'name-empty','name-aa','name-moved','name-backspace','name-controls','name-mode','name-key'))
    p.add_argument('--retail-vsync',type=int,default=1)
    p.add_argument('--json',type=Path)
    a=p.parse_args()
    naming=a.state.startswith('name-')
    controls=a.state in ('name-controls','name-mode','name-key')
    center=None if naming else {'create':(27,92),'call':(27,114),'yes':(29,159),'no':(29,176)}[a.state]
    def in_cursor(vertices):
        v=np.array(vertices)
        if controls:
            left,right=(0,70) if a.state=='name-mode' else (70,320) if a.state=='name-key' else (0,320)
            return len(v) and (v[:,0]>left).all() and (v[:,0]<right).all() and \
                (v[:,1]>45).all() and (v[:,1]<140).all() and \
                (abs(v[:,3]-.46875)<.002).all() and (v[:,2]>=.15).all() and (v[:,2]<=.35).all()
        if naming:
            return len(v) and (v[:,0]>75).all() and (v[:,0]<235).all() and \
                (v[:,1]>0).all() and (v[:,1]<50).all() and \
                (abs(v[:,2]-.96875)<.002).all() and (abs(v[:,3]-.03125)<.002).all()
        return len(v) and (v[:,0]>5).all() and (v[:,0]<55).all() and \
            (v[:,1]>center[1]-25).all() and (v[:,1]<center[1]+25).all()
    dump=gsdump.read_dump(a.dump);st=gsdump.read_state(dump);o=st['CTXT0.XYOFFSET']
    ox,oy=(o&65535)/16,(o>>32&65535)/16
    key=None;retail=[]
    for draw in gsdump.draws(dump):
        if draw['vsync']!=a.retail_vsync or (not naming and len(draw['verts']) not in (21,23)) or \
            not draw['state']['PRIM_EFF']&16:
            continue
        v=[]
        for vertex in draw['verts']:
            s,t,q=vertex['ST'];assert q
            v.append([vertex['XYZ'][0]/16-ox,vertex['XYZ'][1]/16-oy,s/q,t/q,q,*vertex['RGBA']])
        if not in_cursor(v):
            continue
        tex=draw['state'].get(6,st['CTXT0.TEX0'])
        fields=gsdump.tex0_fields(tex)
        if naming and (fields['TW'],fields['TH'])!=(32,32):continue
        assert fields['PSM']==19
        rgba,w,h,_=gsdump.texture_rgba(dump,tex)
        current=(hashlib.sha256(rgba).hexdigest(),(w,h))
        if key is None:key=current
        assert key==current,'inconsistent cursor atlases'
        retail.extend(np.array(t) for t in triangles(draw['state']['PRIM_EFF'],v))
    expected=46 if a.state in ('name-mode','name-key') else 92 if controls else 34 if naming else 40
    assert len(retail)==expected,'missing complete retail cursor geometry'
    rows=list(csv.DictReader((a.native_dir/'draws.tsv').open(),delimiter='\t'))
    textures={}
    for t in {r['texture'] for r in rows if r['texture']!='-1'}:
        image=Image.open(a.native_dir/f'tex-{t}.png').convert('RGBA')
        textures[t]=(hashlib.sha256(image.tobytes()).hexdigest(),image.size)
    native=[]
    for i in range(0,len(rows),3):
        block=rows[i:i+3];assert len(block)==3
        assert len({r['triangle'] for r in block})==1
        assert len({r['texture'] for r in block})==1
        if textures.get(block[0]['texture'])!=key:
            continue
        v=np.array([[float(r[k]) for k in ('x','y','u','v','q','r','g','b','a')] for r in block])
        if in_cursor(v):native.append(v)
    assert all((t[:,4]==1).all() for t in native+retail), 'unexpected cursor reciprocal Q'
    error=match_triangles(native,retail)
    report={'scope':('complete mode/key outlines' if controls else 'complete name-field brackets' if naming else 'complete diamond/ring')+
        ' at explicitly sampled pose; live timing unverified',
        'state':a.state,'retail_vsync':a.retail_vsync,'center':center,
        'triangles':len(native),'vertices':3*len(native),'one_to_one_triangles':True,
        'texture_rgba_byte_exact':True,'colors_and_q_exact':True,
        'position_tolerance_px':.126,'max_position_error_px':error,'uv_tolerance':.002}
    print(json.dumps(report,indent=2))
    if a.json:a.json.write_text(json.dumps(report,indent=2)+'\n')


if __name__=='__main__':main()
