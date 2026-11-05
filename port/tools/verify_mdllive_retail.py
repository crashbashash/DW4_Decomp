#!/usr/bin/env python3
"""373dd0 MDLisLive byte reduction; SD collection/lookup are controlled leaves."""
import argparse,ctypes as C,subprocess,tempfile
from pathlib import Path
from verify_scriptservices_retail import World,ROOT,MSG
class Value(C.Structure):
    _fields_=[('type',C.c_int),('number',C.c_double),('string',C.c_char_p),('length',C.c_size_t)]
class Live(World):
    def call(self,entry,args):
        if entry==0x38e5f0:return 0
        if entry==0x38f0f0:return len(self.rows)
        if entry==0x38f220:return self.rows[args[1]]&255
        return super().call(entry,args)
def main():
    p=argparse.ArgumentParser();p.add_argument('--elf',type=Path,default=ROOT.parent/'../local/extracted/SLUS_208.36');a=p.parse_args()
    world=Live(a.elf.read_bytes());world.w(0x58a1c0,4,MSG)
    with tempfile.TemporaryDirectory(prefix='dw4-mdllive-') as td:
        so=Path(td)/'sd.so'
        subprocess.run(['cc','-shared','-fPIC','-std=c99','-I'+str(ROOT/'include'),str(ROOT/'src/scriptservices.c'),'-lm','-o',str(so)],check=True)
        lib=C.CDLL(str(so));lib.dw4_scriptservices_open.restype=C.c_void_p
        lib.dw4_scriptservices_close.argtypes=[C.c_void_p]
        lib.dw4_scriptservices_category.argtypes=[C.c_void_p,C.c_char_p]
        callback=C.CFUNCTYPE(C.c_int,C.c_void_p,C.c_char_p,C.POINTER(Value),C.c_size_t,C.POINTER(Value),C.c_void_p,C.c_size_t)
        @callback
        def query(user,method,args,count,result,error,cap):
            result[0]=Value(1,world.rows[user-1],None,0);return 0
        lib.dw4_scriptservices_register.argtypes=[C.c_void_p,C.c_uint64,C.c_char_p,C.c_char_p,C.c_int32,C.c_int,callback,C.c_void_p]
        lib.dw4_scriptservices_register.restype=C.c_uint64
        lib.dw4_scriptservices_any.argtypes=[C.c_void_p,C.POINTER(Value),C.c_size_t,C.POINTER(Value),C.c_char_p,C.c_size_t]
        scenarios=([],[0],[1],[0,1],[1,0],[0,0,255],[0,256],[256,-256],[0,-1])
        for rows in scenarios:
            world.rows=rows;wanted=world.invoke(0x373dd0,0,-1)
            sd=lib.dw4_scriptservices_open();assert sd
            try:
                assert lib.dw4_scriptservices_category(sd,b'MODELCTRL')==0
                for i,v in enumerate(rows):assert lib.dw4_scriptservices_register(sd,1,b'MODELCTRL',None,i,1,query,i+1)
                args=(Value*4)(Value(2,0,b'MODELCTRL',9),Value(),Value(1,-1,None,0),Value(2,0,b'ISRUN',5));out=Value();error=C.create_string_buffer(128)
                assert lib.dw4_scriptservices_any(sd,args,4,C.byref(out),error,128)==0,error.value
                assert out.type==1 and out.number==wanted,(rows,out.number,wanted)
            finally:lib.dw4_scriptservices_close(sd)
        print(f'MDLisLive retail: {len(scenarios)} exact empty/first/later/byte-wrapped result cases; SD lookup/collection controlled')
if __name__=='__main__':main()
