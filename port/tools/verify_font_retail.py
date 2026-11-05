#!/usr/bin/env python3
"""Font glyphs/line layout versus 4534f0/4535d0/383bf0/383ed0.

Metric lookup and vertex storage are controlled leaves. Glyph generation,
multiline rebasing and alignment run original instructions. No retail data is
embedded: fixtures use synthetic metrics and the user's private retail ELF.
"""
import argparse
import ctypes as C
import itertools
from pathlib import Path
import struct
import subprocess
import tempfile
from verify_scriptservices_retail import World, ROOT, BASE

OWNER,FONT,FACES,METRICS,VBO,CODES,DATA,ENDS,LENGTHS = [BASE+0x1b0000+i*0x100 for i in range(9)]
VERTICES=BASE+0x1c0000
VTABLE=BASE+0x1d0000
SET_POINT,SET_UV,HAS_GLYPH=0x70000010,0x70000020,0x70000030
OBJECT=BASE+0x1f0000
class Glyph(C.Structure):
    _fields_=[(k,C.c_float) for k in ('advance','bx','by','w','h','u0','v0','u1','v1')]
class Vertex(C.Structure):
    _fields_=[(k,C.c_float) for k in ('x','y','z','u','v')]
def bits(v):return struct.unpack('<I',struct.pack('<f',v))[0]
class Retail(World):
    def __init__(self,image):
        super().__init__(image)
        self.descend={0x4534f0,0x4535d0,0x383bf0,0x383ed0,0x381d70}
        self.w(FONT,4,VTABLE);self.w(VTABLE+100,4,HAS_GLYPH)
        self.w(VBO,4,VTABLE);self.w(VTABLE+116,4,SET_POINT);self.w(VTABLE+200,4,SET_UV)
        self.w(VBO+16,4,VERTICES);self.w(VBO+20,4,20)
        self.w(FONT+28,4,METRICS);self.list(METRICS,[0,0])
        self.list(FACES,[FONT]);self.w(OWNER+36,4,FACES);self.w(OWNER+40,4,0)
        self.list(ENDS,[]);self.list(LENGTHS,[])
        self.w(OWNER+48,4,ENDS);self.w(OWNER+52,4,LENGTHS)
    def call(self,e,a):
        a=[x&0xffffffff for x in a]
        if e==0x361df0:return 0
        if e==0x38d4a0:return 8
        if e in (0x38f660,0x38f240):return 1
        if e==0x38f800:return OBJECT
        if e==0x38f320:return self.replacement
        if e==0x2ed4e0:return self.object_bytes
        if e==HAS_GLYPH:return int(a[1] in self.metric_codes)
        if e==0x453830:return self.metric_codes.index(a[1]) if a[1] in self.metric_codes else -1
        if e==SET_POINT:
            for i in range(3):self.w(VERTICES+a[1]*20+i*4,4,self.read(a[2]+i*4,4))
            return 0
        if e==SET_UV:
            for i in range(2):self.w(VERTICES+a[2]*20+12+i*4,4,self.read(a[3]+i*4,4))
            return 0
        return super().call(e,a)
    def build(self,glyphs,metric_codes,codes,width,align,height,baseline):
        self.metric_codes=metric_codes
        self.w(FONT+12,4,bits(height));self.w(FONT+16,4,bits(baseline))
        self.w(METRICS+16,4,BASE+0x1e0000)
        for i,g in enumerate(glyphs):
            self.w(BASE+0x1e0000+i*40,2,metric_codes[i])
            for j,(key,_) in enumerate(Glyph._fields_):self.w(BASE+0x1e0000+i*40+4+4*j,4,bits(getattr(g,key)))
        for i,c in enumerate([*codes,0]):self.w(CODES+i*2,2,c)
        for i in range((len(codes)+1)*6*20):self.w(VERTICES+i,1,0)
        self.w(VBO+12,4,(len(codes)+1)*6)
        self.invoke(0x4534f0,FONT,VBO,CODES)
        self.invoke(0x383bf0,OWNER,CODES,DATA,VBO)
        self.w(DATA+28,4,bits(width));self.w(DATA+36,4,align)
        if align:self.invoke(0x383ed0,OWNER,CODES,DATA,VBO)
        n=self.read(VBO+12,4)
        return [[self.read(VERTICES+i*20+j*4,4) for j in range(5)] for i in range(n)]
    def replace_unknown(self,codes,replacement):
        self.replacement=replacement;self.object_bytes=(len(codes)+1)*2;self.w(DATA+24,4,1);self.w(OBJECT+12,4,CODES)
        for i,c in enumerate([*codes,0]):self.w(CODES+2*i,2,c)
        self.invoke(0x381d70,OWNER,DATA,0)
        return [self.read(CODES+2*i,2) for i in range(len(codes))]
def main():
    p=argparse.ArgumentParser(description=__doc__)
    p.add_argument('--elf',type=Path,default=ROOT.parent.parent / 'local/extracted/SLUS_208.36');args=p.parse_args()
    if not args.elf.is_file():print('SKIP font oracle: private retail ELF unavailable');return
    shim='''#include "dw4/fontlayout.h"
#include <stdlib.h>
const dw4_glyph *dw4_fefont_glyph(const dw4_fefont*f,uint32_t c){for(int i=0;i<f->nall;i++)if(f->allcode[i]==c)return f->all+i;return 0;}
int build(dw4_glyph*g,uint32_t*mc,int ng,uint32_t*c,size_t n,float w,int a,float h,float b,dw4_font_vertex*out){
 dw4_fefont f={.have=1,.all=g,.allcode=mc,.nall=ng,.height=h,.baseline=b};
 dw4_font_vertex*v;size_t count;if(dw4_fontlayout_build(&f,c,n,w,a,&v,&count))return -1;
 for(size_t i=0;i<count;i++)out[i]=v[i];free(v);return (int)count;}
int replace(dw4_glyph*g,uint32_t*mc,int ng,uint16_t*c,size_t n,uint16_t r){
 dw4_fefont f={.have=1,.all=g,.allcode=mc,.nall=ng};return dw4_fontlayout_replace_unknown(&f,c,n,r);}
'''
    with tempfile.TemporaryDirectory(prefix='dw4-font-oracle-') as tmp:
        src=Path(tmp)/'shim.c';src.write_text(shim);libpath=Path(tmp)/'font.so'
        subprocess.run(['cc','-O2','-std=c99','-fPIC','-shared','-I'+str(ROOT/'include'),'-I'+str(ROOT/'recovered/frontend'),str(src),str(ROOT/'src/fontlayout.c'),str(ROOT/'recovered/frontend/eefloat.c'),'-o',str(libpath)],check=True)
        lib=C.CDLL(str(libpath));lib.build.argtypes=[C.POINTER(Glyph),C.POINTER(C.c_uint32),C.c_int,C.POINTER(C.c_uint32),C.c_size_t,C.c_float,C.c_int,C.c_float,C.c_float,C.POINTER(Vertex)]
        lib.replace.argtypes=[C.POINTER(Glyph),C.POINTER(C.c_uint32),C.c_int,C.POINTER(C.c_uint16),C.c_size_t,C.c_uint16]
        w=Retail(args.elf.read_bytes());total=0
        sequences=[[],[65],[65,66],[65,10,66],[65,13,66],[10,65],[65,10],[65,10,10,66],[65,66,10,66,65],[65,10,66,10,65]]
        for height,baseline,align,width,bearing in itertools.product([.18,.28],[-.01,0],range(3),[.1,1,4.96],[-.03,0,.02]):
            glyphs=[Glyph(.15,bearing,-.02,.14,.27,.1,.2,.3,.4),Glyph(.12,bearing+.01,.01,.11,.18,.5,.6,.7,.8)]
            for codes in sequences:
                expected=w.build(glyphs,[65,66],codes,width,align,height,baseline)
                g=(Glyph*2)(*glyphs);mc=(C.c_uint32*2)(65,66);text=(C.c_uint32*len(codes))(*codes);out=(Vertex*((len(codes)+1)*6))()
                n=lib.build(g,mc,2,text,len(codes),width,align,height,baseline,out)
                got=[[bits(getattr(out[i],key)) for key,_ in Vertex._fields_] for i in range(n)]
                assert got==expected,(height,baseline,align,width,bearing,codes,got,expected)
                total+=1
        replaced=0
        for glyph_codes in ([65,66],[65,0x2261],[32,65,66,0x2261]):
            w.metric_codes=glyph_codes;g=(Glyph*len(glyph_codes))();mc=(C.c_uint32*len(glyph_codes))(*glyph_codes)
            for codes,replacement in itertools.product([[65,0xffff,66],[0x2261,10,13,65],[0,0xffff],[0xffff,0,65]], [0,32,63,0x2261]):
                expected=w.replace_unknown(codes,replacement);text=(C.c_uint16*len(codes))(*codes)
                assert lib.replace(g,mc,len(glyph_codes),text,len(codes),replacement)==0
                assert list(text)==expected,(codes,replacement,list(text),expected)
                replaced+=1
        print(f'Font REPLACEUNKNOWN: {replaced} typed-object states match retail, including terminators and unsupported replacement codes')
        print(f'Font retail: {total} glyph/CR/LF/empty-line/bearing/alignment geometry states match original instructions')
if __name__=='__main__':main()
