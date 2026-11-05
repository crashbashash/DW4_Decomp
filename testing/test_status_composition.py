#!/usr/bin/env python3
"""Composition oracle rejects vertex-only coverage and invalid occlusion."""
import sys
import copy
from pathlib import Path
import numpy as np
sys.path.insert(0,str(Path(__file__).resolve().parents[1]/'port/tools'))
from verify_status_composition import match_triangle,compare_ordered,backdrop,uniform_backdrop,covered_sample,opaque_pixels,depth_retirement

def vertex(x,y):return [x,y,x/10,y/10,1,127,127,127,128,1000,1,1,1,1,0]
a,b,c,d=[vertex(x,y) for x,y in ((0,0),(10,0),(10,10),(0,10))]
ret=np.array([a,b,c]);native=np.array([[a,b,c]])
assert match_triangle(native,ret)
assert match_triangle(native,ret[[2,0,1]])
key=('texture',16,16);other=np.array([a,b,d])
ordered=[(key,ret),(key,other)]
assert compare_ordered(ordered,ordered)[0]
assert not compare_ordered(ordered,ordered[::-1])[0]
assert not compare_ordered(ordered,ordered+[ordered[0]])[0]
assert not compare_ordered(ordered,[ordered[0],ordered[0]])[0]
# Each vertex exists in the native set, but this triangle does not.
assert not match_triangle(np.array([[a,b,d],[a,c,d]]),ret)
assert covered_sample(ret)
sliver=np.array([vertex(.0625,170.8125),vertex(-27.5,258.5625),vertex(-144.5,170.8125)])
assert covered_sample(sliver)
sliver[0,0]=0
assert not covered_sample(sliver)
sliver[0,0]=2
assert covered_sample(sliver)
for column,delta in ((4,.0001),(5,1),(9,2),(10,1),(11,1),(12,1),(13,1),(14,1)):
    bad=ret.copy();bad[0,column]+=delta
    assert not match_triangle(native,bad)
state={'CTXT0.XYOFFSET':0,'CTXT0.TEST':5<<16,'CTXT0.ZBUF':0,'CTXT0.TEX1':0,
       'CTXT0.ALPHA':0x44,'CTXT0.TEX0':1<<34,'CTXT0.FRAME':0,'CTXT0.SCISSOR':(639<<16)|(447<<48)}
draw={'state':{'PRIM_EFF':4|16|64},'verts':[]}
for x,y in ((-32,-16),(672,-16),(-32,464),(672,464)):
    draw['verts'].append({'XYZ':(x*16,y*16,1000*16),'Z':1000,'ST':(.25,.25,1),'RGBA':(127,127,127,128),'ADC':False})
rgba=bytes([0,0,0,128]*16)
assert backdrop(draw,rgba,4,4,state,999)
assert not backdrop(draw,rgba,4,4,state,1001)
assert not backdrop(draw,bytes([0,0,0,0])+rgba[4:],4,4,state,999)
assert uniform_backdrop(draw,state)
assert not backdrop(draw,bytes([0,0,0,91]*16),4,4,state,999)
assert depth_retirement(draw,bytes([0,0,0,91]*16),4,4,state,999)
state['CTXT0.FRAME']=0xffffffff<<32
assert not backdrop(draw,rgba,4,4,state,999)
assert depth_retirement(draw,rgba,4,4,state,999)
state['CTXT0.FRAME']=0;state['CTXT0.TEST']=3<<16;state['CTXT0.ZBUF']=1<<32
state['CTXT0.TEX1']=(1<<5)|(1<<6);draw['state']['PRIM_EFF']|=8
assert opaque_pixels(draw,rgba,4,4,state).all()
halves=[]
for indices in ((0,1,2),(1,2,3)):
    triangle=copy.deepcopy(draw);triangle['state']['PRIM_EFF']=(triangle['state']['PRIM_EFF']&~7)|3
    triangle['verts']=[triangle['verts'][i] for i in indices]
    halves.append(opaque_pixels(triangle,rgba,4,4,state))
assert not halves[0].all() and not halves[1].all() and (halves[0]|halves[1]).all()
assert not opaque_pixels(draw,bytes([0,0,0,127]*16),4,4,state).any()
state['CTXT0.FRAME']=0xff<<32
assert not opaque_pixels(draw,rgba,4,4,state).any()
state['CTXT0.FRAME']=0;state['CTXT0.TEST']|=1<<14
assert not opaque_pixels(draw,rgba,4,4,state).any()
state['CTXT0.TEST']=3<<16
draw['verts'][0]['ST']=(.25,.25,-1)
assert not opaque_pixels(draw,rgba,4,4,state).all()
draw['verts'][0]['ST']=(.25,.25,1)
draw['verts'][2]['ADC']=True
assert not backdrop(draw,rgba,4,4,state,999)
assert not opaque_pixels(draw,rgba,4,4,state).all()
print('STATUS composition oracle: triangle membership, pipeline fields, opacity union, framebuffer masks, depth retirement and ADC guards pass')
