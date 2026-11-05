#!/usr/bin/env python3
"""Reverse STATUS primitive coverage in one retail dump interval.

The viewport-covering UI backdrop identifies the UI suffix. An opaque backdrop
or a verified union of later opaque background triangles may retire the prefix.
Every UI triangle intersecting the viewport
must match one actual native triangle, including depth/filter/blend/color-mask
state. Pixel-bearing UI triangles must also match one-to-one in submission order.
Live phase and pixels remain separate.
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
sys.path.insert(0,str(Path(__file__).resolve().parents[2]/'scripts'))
import gsdump

FIELDS=('x','y','u','v','q','r','g','b','a','z','depth','depth_write','filter','blend','color_mask')

def native_triangles(directory,frame):
    rows=list(csv.DictReader((directory/f'root-{frame}.tsv').open(),delimiter='\t'))
    assert rows and all(k in rows[0] for k in FIELDS),'regenerate full native pipeline exports'
    keys={};triangles={}
    for row in rows:
        part,index=row['part'],row['texture'];identity=(part,index)
        if identity not in keys:
            im=Image.open(directory/f'root-{frame}-{part}-{index}.png').convert('RGBA')
            keys[identity]=(hashlib.sha256(im.tobytes()).hexdigest(),im.width,im.height)
        key=(keys[identity],part,row['triangle'])
        triangles.setdefault(key,[]).append([float(row[k]) for k in FIELDS])
    grouped={};ordered=[]
    for (texture,_,_),vertices in triangles.items():
        assert len(vertices)==3
        grouped.setdefault(texture,[]).append(vertices)
        triangle=np.array(vertices,dtype=float)
        if covered_sample(triangle):ordered.append((texture,triangle))
    return {k:np.array(v,dtype=float) for k,v in grouped.items()},ordered

def material(draw,state):
    prim=gsdump.prim_fields(draw['state']['PRIM_EFF'])
    test=draw['state'].get(0x47,state['CTXT0.TEST'])
    zbuf=draw['state'].get(0x4e,state['CTXT0.ZBUF'])
    mode={1:2,2:1}.get((test>>17)&3,-1)
    tex1=gsdump.tex1_fields(draw['state'].get(0x14,state['CTXT0.TEX1']))
    filtering={(0,0):1,(1,1):2}.get((tex1['MMAG'],tex1['MMIN']),-1)
    alpha=draw['state'].get(0x42,state['CTXT0.ALPHA'])&255
    blend=0 if not prim['ABE'] else {0x44:1,0x48:2}.get(alpha,-1)
    frame=draw['state'].get(0x4c,state['CTXT0.FRAME'])>>32
    mask=sum(1<<k for k in range(4) if (frame>>(8*k))&255==255)
    if any((frame>>(8*k))&255 not in (0,255) for k in range(4)):mask=-1
    return mode,1-((zbuf>>32)&1),filtering,blend,mask

def vertices(draw,state):
    offset=state['CTXT0.XYOFFSET'];ox,oy=(offset&65535)/16,((offset>>32)&65535)/16
    policy=material(draw,state);out=[]
    for v in draw['verts']:
        if 'ST' not in v or not v['ST'][2]:return None
        s,t,q=v['ST']
        out.append([v['XYZ'][0]/16-ox,v['XYZ'][1]/16-oy,s/q,t/q,q,*v['RGBA'],v['Z'],*policy])
    return np.array(out,dtype=float)

def triangles(draw):
    v=draw['verts'];kind=draw['state']['PRIM_EFF']&7
    if kind==3:indices=[(i,i+1,i+2) for i in range(0,len(v)-2,3)]
    elif kind==4:indices=[(i-2,i-1,i) for i in range(2,len(v))]
    elif kind==5:indices=[(0,i-1,i) for i in range(2,len(v))]
    else:return None
    return [i for i in indices if not v[i[-1]]['ADC']]

def uniform_backdrop(draw,state):
    v=vertices(draw,state)
    if v is None or len(v)!=4 or draw['state']['PRIM_EFF']&7!=4:return False
    if len(triangles(draw))!=2:return False
    texture=gsdump.tex0_fields(draw['state'].get(6,state['CTXT0.TEX0']))
    if (texture['TCC'],texture['TFX'])!=(1,0):return False
    corners={(p[0],p[1]) for p in v}
    x0,y0=v[:,:2].min(0);x1,y1=v[:,:2].max(0)
    if corners!={(x0,y0),(x0,y1),(x1,y0),(x1,y1)} or not (x0<=0 and y0<=0 and x1>=640 and y1>=448):return False
    if not (v[:,2:5]==v[0,2:5]).all() or not (v[:,5:9]==v[0,5:9]).all():return False
    if v[0,8]!=128 or v[0,13] not in (0,1):return False
    if not (v[:,9]==v[0,9]).all():return False
    if v[0,10] not in (1,2):return False
    sc=draw['state'].get(0x40,state['CTXT0.SCISSOR'])
    if ((sc&2047),(sc>>16)&2047,(sc>>32)&2047,(sc>>48)&2047)!=(0,639,0,447):return False
    return True

def backdrop(draw,rgba,w,h,state,prefix_z):
    if not uniform_backdrop(draw,state):return False
    if draw['state'].get(0x4c,state['CTXT0.FRAME'])>>32:return False
    test=draw['state'].get(0x47,state['CTXT0.TEST'])
    if test&(1<<14) or not test&(1<<16) or not alpha_passes(test,128):return False
    v=vertices(draw,state)
    if v[0,9]<prefix_z:return False
    # Constant UV makes this a uniform sample. Require all bilinear neighbours
    # opaque, avoiding assumptions about alpha elsewhere in the atlas.
    im=np.frombuffer(rgba,dtype=np.uint8).reshape(h,w,4)
    x=int(np.floor(v[0,2]*w-.5));y=int(np.floor(v[0,3]*h-.5))
    return all(im[(y+dy)%h,(x+dx)%w,3]==128 for dx,dy in itertools.product((0,1),repeat=2))

def match_triangle(native,retail):
    for perm in itertools.permutations(range(3)):
        n=native[:,perm,:]
        good=(abs(n[:,:,:2]-retail[None,:,:2])<=.126).all((1,2))
        good&=(abs(n[:,:,2:4]-retail[None,:,2:4])<.002).all((1,2))
        good&=(abs(n[:,:,4]-retail[None,:,4])<=1e-8+.00002*abs(retail[None,:,4])).all(1)
        good&=(n[:,:,5:9]==retail[None,:,5:9]).all((1,2))
        good&=(abs(n[:,:,9]-retail[None,:,9])<=1).all(1)
        good&=(n[:,:,10:]==retail[None,:,10:]).all((1,2))
        if good.any():return True
    return False

def compare_ordered(native,retail):
    """One-to-one ordered matching rejects duplicates and balanced omissions."""
    failures=[]
    if len(native)!=len(retail):failures.append({'reason':'primitive count differs','native':len(native),'retail':len(retail)})
    for i,((nk,n),(rk,r)) in enumerate(zip(native,retail)):
        if nk!=rk or not match_triangle(n[None,:,:],r):
            if len(failures)<8:failures.append({'reason':'ordered primitive differs','index':i,'native_texture':nk[0],'retail_texture':rk[0]})
    return not failures,failures

def pixel_coverage(vertices,width=640,height=448):
    """Does GS-grid top-left coverage contain an actual viewport pixel?

    A bounding-box intersection alone admits subpixel slivers at the scissor
    edge. Use the same documented integer sample grid, not a wider tolerance.
    """
    xy=np.rint(vertices[:,:2]*16).astype(np.int64)
    area=np.linalg.det(np.array([xy[1]-xy[0],xy[2]-xy[0]]))
    if not area:return None
    lo=np.maximum(0,np.ceil(xy.min(0)/16).astype(int));hi=np.minimum([width-1,height-1],np.floor(xy.max(0)/16).astype(int))
    if (hi<lo).any():return None
    y,x=np.mgrid[lo[1]:hi[1]+1,lo[0]:hi[0]+1];valid=np.ones(x.shape,dtype=bool)
    for e in range(3):
        a,b=(e,(e+1)%3) if area>0 else ((e+1)%3,e)
        dx,dy=xy[b]-xy[a];edge=dx*(y*16-xy[a,1])-dy*(x*16-xy[a,0])
        inclusive=dy<0 or (dy==0 and dx>0)
        valid&=(edge>0)|((edge==0)&inclusive)
    return lo,hi,valid

def covered_sample(vertices):
    coverage=pixel_coverage(vertices)
    return coverage is not None and bool(coverage[2].any())

def alpha_passes(test,alpha):
    if not test&1:return True
    ref=(test>>4)&255
    return (False,True,alpha<ref,alpha<=ref,alpha==ref,alpha>=ref,
            alpha>ref,alpha!=ref)[(test>>1)&7]

def depth_retirement(draw,rgba,w,h,state,prefix_z):
    """A full-screen depth write removes prefix Z, even with FBMSK=ffffffff."""
    if not uniform_backdrop(draw,state):return False
    v=vertices(draw,state);test=draw['state'].get(0x47,state['CTXT0.TEST'])
    if test&(1<<14) or not test&(1<<16) or v[0,9]<prefix_z or v[0,11]!=1:return False
    im=np.frombuffer(rgba,np.uint8).reshape(h,w,4)
    x=int(np.floor(v[0,2]*w-.5));y=int(np.floor(v[0,3]*h-.5))
    alphas=[int(im[(y+dy)%h,(x+dx)%w,3]) for dx,dy in itertools.product((0,1),repeat=2)]
    return len(set(alphas))==1 and alpha_passes(test,alphas[0])

def opaque_pixels(draw,rgba,w,h,state,width=640,height=448):
    """Conservative opacity: every bilinear neighbour in each UV bound is 128.

    Positive Q keeps interpolated UV inside the triangle's vertex bounds. Bounds
    stay inside the texture, so wrap/clamp cannot change this proof. ALWAYS and
    no depth writes prevent prefix depth from controlling these background draws.
    """
    mask=np.zeros((height,width),dtype=bool)
    prim=gsdump.prim_fields(draw['state']['PRIM_EFF'])
    tex=gsdump.tex0_fields(draw['state'].get(6,state['CTXT0.TEX0']))
    test=draw['state'].get(0x47,state['CTXT0.TEST'])
    frame=draw['state'].get(0x4c,state['CTXT0.FRAME'])
    scissor=draw['state'].get(0x40,state['CTXT0.SCISSOR'])
    if (not prim['TME'] or not prim['IIP'] or prim['FST'] or prim['CTXT'] or prim['FGE']
        or (tex['TCC'],tex['TFX'])!=(1,0) or material(draw,state) not in ((2,0,2,0,0),(2,0,2,1,0))
        or frame>>32 or (frame>>24)&63 or test&(1<<14) or not test&(1<<16) or not alpha_passes(test,128)
        or ((scissor&2047),(scissor>>16)&2047,(scissor>>32)&2047,(scissor>>48)&2047)!=(0,width-1,0,height-1)):
        return mask
    data=vertices(draw,state);indices=triangles(draw)
    if data is None or indices is None:return mask
    im=np.frombuffer(rgba,np.uint8).reshape(h,w,4)
    for indices in indices:
        t=data[list(indices)]
        if not (t[:,8]==128).all() or not (t[:,4]>0).all():continue
        lo=np.floor(t[:,2:4].min(0)*[w,h]-.5).astype(int)
        hi=np.floor(t[:,2:4].max(0)*[w,h]-.5).astype(int)+1
        if (lo<0).any() or (hi>=[w,h]).any() or not (im[lo[1]:hi[1]+1,lo[0]:hi[0]+1,3]==128).all():continue
        coverage=pixel_coverage(t,width,height)
        if coverage is not None:
            a,b,pixels=coverage;mask[a[1]:b[1]+1,a[0]:b[0]+1]|=pixels
    return mask

def main():
    p=argparse.ArgumentParser(description=__doc__)
    p.add_argument('--dump',required=True);p.add_argument('--native-dir',type=Path,required=True)
    p.add_argument('--frame',type=int,default=0);p.add_argument('--retail-vsync',type=int,required=True)
    p.add_argument('--json',type=Path);p.add_argument('--report-only',action='store_true');a=p.parse_args()
    native,native_order=native_triangles(a.native_dir,a.frame);dump=gsdump.read_dump(a.dump);state=gsdump.read_state(dump)
    retail_order=[]
    textures={};prefix_z=0;started=False;prefix=0;matched=0;outside=0;degenerate=0;failures=[];certificate=None;underlay=None;retail_triangles={}
    opaque=np.zeros((448,640),dtype=bool);opaque_draws=[];retired_depth=False;backdrop_frame=None;depth_ordinal=None;depth_frame_mask=None
    for ordinal,draw in enumerate(d for d in gsdump.draws(dump) if d['vsync']==a.retail_vsync):
        prim=gsdump.prim_fields(draw['state']['PRIM_EFF']);texture=None;data=None
        if prim['TME']:
            tex0=draw['state'].get(6,state['CTXT0.TEX0'])
            if gsdump.tex0_fields(tex0)['PSM']==19:
                if tex0 not in textures:
                    rgba,w,h,_=gsdump.texture_rgba(dump,tex0);textures[tex0]=((hashlib.sha256(rgba).hexdigest(),w,h),rgba,w,h)
                texture,rgba,w,h=textures[tex0];data=vertices(draw,state)
        if not started:
            if texture in native and uniform_backdrop(draw,state):
                started=True
                backdrop_frame=draw['state'].get(0x4c,state['CTXT0.FRAME'])&0xffffffff
                retired_depth=depth_retirement(draw,rgba,w,h,state,prefix_z)
                depth_ordinal=ordinal
                depth_frame_mask=f"{draw['state'].get(0x4c,state['CTXT0.FRAME'])>>32:08x}"
                if backdrop(draw,rgba,w,h,state,prefix_z):
                    certificate={'ordinal':ordinal,'prefix_draws_occluded':prefix,'prefix_max_z':prefix_z,'backdrop_z':float(data[0,9]),'record_offset':draw['record_offset']}
                else:
                    underlay={'ordinal':ordinal,'prefix_draws':prefix,'reason':'translucent backdrop does not prove prefix occlusion','record_offset':draw['record_offset']}
            else:
                prefix+=1
                prefix_z=max([prefix_z,*[v['Z'] for v in draw['verts']]])
                continue
        if data is None or texture not in native:
            failures.append({'ordinal':ordinal,'reason':'unmapped or unsupported post-backdrop draw'});continue
        if retired_depth and (draw['state'].get(0x4c,state['CTXT0.FRAME'])&0xffffffff)==backdrop_frame:
            pixels=opaque_pixels(draw,rgba,w,h,state)
            if pixels.any():opaque|=pixels;opaque_draws.append(ordinal)
        indices=triangles(draw)
        if indices is None:failures.append({'ordinal':ordinal,'reason':'unsupported primitive'});continue
        for i in indices:
            t=data[list(i)];area=np.linalg.det(np.array([t[1,:2]-t[0,:2],t[2,:2]-t[0,:2]]))
            if abs(area)<1e-10:degenerate+=1;continue
            if t[:,0].max()<=0 or t[:,0].min()>=640 or t[:,1].max()<=0 or t[:,1].min()>=448:outside+=1;continue
            retail_triangles.setdefault(texture,[]).append(t)
            if covered_sample(t):retail_order.append((texture,t))
            if match_triangle(native[texture],t):matched+=1
            else:failures.append({'ordinal':ordinal,'reason':'intersecting triangle absent from native','vertices':t.tolist()})
    native_matched=0;native_extra=[];native_empty_coverage=0
    for texture,tris in native.items():
        target=np.array(retail_triangles.get(texture,[]),dtype=float).reshape(-1,3,len(FIELDS))
        for t in tris:
            area=np.linalg.det(np.array([t[1,:2]-t[0,:2],t[2,:2]-t[0,:2]]))
            if abs(area)<1e-10 or t[:,0].max()<=0 or t[:,0].min()>=640 or t[:,1].max()<=0 or t[:,1].min()>=448:continue
            if match_triangle(target,t):native_matched+=1
            elif not covered_sample(t):native_empty_coverage+=1
            else:native_extra.append({'texture':texture[0],'vertices':t.tolist()})
    if certificate is None and retired_depth and opaque.all():
        certificate={'method':'opaque background triangle union after independent depth retirement','prefix_draws_occluded':prefix,'prefix_max_z':prefix_z,'depth_retirement_ordinal':depth_ordinal,'depth_retirement_frame_mask':depth_frame_mask,'opaque_pixels':int(opaque.sum()),'viewport_pixels':opaque.size,'opaque_draw_ordinals':opaque_draws}
        underlay=None
    coverage=started and not failures and not native_extra and matched>0
    ordered,order_failures=compare_ordered(native_order,retail_order)
    result={'scope':'bidirectional UI coverage, ordered pixel-bearing primitives and prefix occlusion proof; live phase and pixel parity remain separate','retail_vsync':a.retail_vsync,'opaque_prefix_certificate':certificate,'unverified_underlay':underlay,'matched_triangles':matched,'native_matched_triangles':native_matched,'native_empty_pixel_coverage':native_empty_coverage,'offscreen_triangles':outside,'degenerate_triangles':degenerate,'failures':failures,'native_extra_triangles':native_extra,'ui_coverage_pass':coverage,'ordered_primitive_pass':ordered,'ordered_pixel_triangles':len(retail_order),'ordered_mismatches':order_failures,'pass':coverage and ordered and certificate is not None}
    output=json.dumps(result,indent=2)+'\n'
    if a.json:a.json.write_text(output)
    print(output,end='');return 0 if a.report_only or result['pass'] else 1

if __name__=='__main__':raise SystemExit(main())
