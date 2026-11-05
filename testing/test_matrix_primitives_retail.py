#!/usr/bin/env python3
"""Complete matrix-copy/translation run vs original EE instructions, no leaves."""
import argparse,ctypes as C,subprocess,sys,tempfile
from pathlib import Path
ROOT=Path(__file__).resolve().parents[1]
sys.path.insert(0,str(ROOT/'port/tools'))
from verify_scriptservices_retail import World
BASE=0x1800000
READ=C.CFUNCTYPE(C.c_uint32,C.c_void_p,C.c_uint32)
WRITE=C.CFUNCTYPE(None,C.c_void_p,C.c_uint32,C.c_uint32)
class Api(C.Structure):
    _fields_=[('user',C.c_void_p),('read',READ),('write',WRITE)]
ENTRIES={0x1908f0:'copy',0x1909b0:'from_translation',0x190a10:'set_translation',
         0x190a30:'get_translation',0x190a50:'translate_local'}
class Matrix(World):
    def __init__(self,image):super().__init__(image);self.descend=set(ENTRIES)
    def call(self,e,args):raise AssertionError(f'unexpected matrix callee {e:#x}')
def main():
    parser=argparse.ArgumentParser(description=__doc__);parser.add_argument('--elf',type=Path,default=ROOT/'orig/SLUS-20836/SLUS_208.36');args=parser.parse_args()
    image=args.elf.read_bytes();retail=Matrix(image);native=Matrix(image);cases=0;hits=set()
    read=READ(lambda _,p:native.read(p,4));write=WRITE(lambda _,p,v:native.write(p,4,v));api=Api(None,read,write)
    with tempfile.TemporaryDirectory(prefix='dw4-matrix-') as td:
        so=Path(td)/'matrix.so'
        subprocess.run(['cc','-shared','-fPIC','-std=c99','-Wall','-Wextra','-Werror',str(ROOT/'recovered/engine/matrix-primitives.c'),str(ROOT/'recovered/frontend/eefloat.c'),'-o',str(so)],check=True)
        lib=C.CDLL(str(so))
        functions={entry:getattr(lib,'dw4_matrix_'+role) for entry,role in ENTRIES.items()}
        for fn in functions.values():fn.argtypes=[C.POINTER(Api),C.c_uint32,C.c_uint32];fn.restype=None
        def compare(entry,destination,source,pattern):
            nonlocal cases
            retail.mem={}
            for i in range(256):retail.w(BASE+i*4,4,pattern[i%len(pattern)]^(i*0x10203))
            native.mem=retail.mem.copy()
            retail.invoke(entry,destination,source)
            functions[entry](C.byref(api),destination,source)
            assert native.mem==retail.mem,(hex(entry),destination,source,[(hex(p),retail.mem.get(p),native.mem.get(p)) for p in retail.mem.keys()|native.mem.keys() if retail.mem.get(p)!=native.mem.get(p)][:12])
            hits.add(entry);cases+=1
        raw=(0xffffffff,0x80000000,1,0x3f800000,0x7f800000,0xdeadbeef,0x12345678)
        for align in (0,4,8,12):
            for displacement in range(-96,100,4):
                compare(0x1908f0,BASE+256+align+displacement,BASE+256+align,raw)
        for entry in (0x1909b0,0x190a10,0x190a30):
            for align in (0,4,8,12):
                for displacement in range(-16,84,4):
                    compare(entry,BASE+256+align,BASE+256+align+displacement,raw)
        for pattern in ((0,0x3f800000,0xbf800000),(1,0x80000000,0x7f800000),
                        (0x7fffffff,0xff800000,0x3f000000),(0x3eaaaaab,0x4f123456,0xc7123456)):
            for align in (0,4,8,12):
                for displacement in range(-16,84,4):
                    compare(0x190a50,BASE+256+align,BASE+256+align+displacement,pattern)
        assert hits==set(ENTRIES)
    print(f'matrix primitives retail: {cases} exact RAM cases, all five bodies, alignment/overlap and float-model boundaries; no callee leaves')
if __name__=='__main__':main()
