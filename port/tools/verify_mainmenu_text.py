#!/usr/bin/env python3
"""Compare complete visible menu message/legend glyph triangle sets against retail.

Uses actual test_mainmenu_cursor exports. Slots includes Create/Call text;
message covers the lower window/legend; upper covers name/species/keyboard.
Models and backgrounds remain outside this comparison.
"""
import argparse
import csv
import hashlib
import json
from pathlib import Path
import sys

import numpy as np
from PIL import Image
from verify_mainmenu_summary import triangles,match_triangles
sys.path.insert(0,str(Path(__file__).resolve().parents[2]/'scripts'))
import gsdump


def main():
    p=argparse.ArgumentParser(description=__doc__)
    p.add_argument('--dump',required=True)
    p.add_argument('--native-dir',required=True,type=Path)
    p.add_argument('--region',choices=('slots','message','upper'),default='message')
    p.add_argument('--retail-vsync',type=int,default=1)
    p.add_argument('--json',type=Path)
    a=p.parse_args();bottom=75 if a.region=='slots' else 0 if a.region=='upper' else 140;top=140 if a.region=='upper' else 224
    def visible(v):
        v=np.array(v)
        return (v[:,0]>=0).all() and (v[:,0]<320).all() and (v[:,1]>=bottom).all() and (v[:,1]<top).all()
    rows=list(csv.DictReader((a.native_dir/'draws.tsv').open(),delimiter='\t'))
    keys={}
    for t in {r['texture'] for r in rows if r['texture']!='-1'}:
        image=Image.open(a.native_dir/f'tex-{t}.png').convert('RGBA')
        if image.size==(512,512):keys[t]=hashlib.sha256(image.tobytes()).hexdigest()
    native=[];used=set()
    for i in range(0,len(rows),3):
        block=rows[i:i+3];assert len(block)==3 and len({r['triangle'] for r in block})==1
        key=keys.get(block[0]['texture'])
        if key is None:continue
        v=np.array([[float(r[k]) for k in ('x','y','u','v','q','r','g','b','a')] for r in block])
        if visible(v):native.append(v);used.add(key)
    assert native and len(used)==1,'missing or unexpected native glyph atlas'
    dump=gsdump.read_dump(a.dump);state=gsdump.read_state(dump);o=state['CTXT0.XYOFFSET'];ox=(o&65535)/16;oy=(o>>32&65535)/16
    retail=[];textures={}
    for draw in gsdump.draws(dump):
        if draw['vsync']!=a.retail_vsync or not draw['state']['PRIM_EFF']&16:continue
        tex=draw['state'].get(6,state['CTXT0.TEX0'])
        if tex not in textures:
            f=gsdump.tex0_fields(tex);textures[tex]=None
            if f['PSM']==19 and (f['TW'],f['TH'])==(512,512):
                rgba,_,_,_=gsdump.texture_rgba(dump,tex);textures[tex]=hashlib.sha256(rgba).hexdigest()
        if textures[tex] not in used:continue
        v=[]
        for vertex in draw['verts']:
            s,t,q=vertex['ST'];assert q
            v.append([vertex['XYZ'][0]/16-ox,vertex['XYZ'][1]/16-oy,s/q,t/q,q,*vertex['RGBA']])
        for tri in triangles(draw['state']['PRIM_EFF'],v):
            if visible(tri):retail.append(np.array(tri))
    error=match_triangles(native,retail)
    assert all((t[:,4]==1).all() for t in native+retail)
    report={'scope':'complete visible glyph triangles in selected region; models/background excluded',
        'region':a.region,'retail_vsync':a.retail_vsync,'triangles':len(native),'vertices':3*len(native),
        'one_to_one_triangles':True,'texture_rgba_byte_exact':True,'colors_and_q_exact':True,
        'position_tolerance_px':.126,'max_position_error_px':error,'uv_tolerance':.002}
    print(json.dumps(report,indent=2))
    if a.json:a.json.write_text(json.dumps(report,indent=2)+'\n')


if __name__=='__main__':main()
