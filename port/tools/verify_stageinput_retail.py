#!/usr/bin/env python3
"""STAGECTL PADINPUT and neutral-pad selection against retail instructions."""
import ctypes as C
import subprocess
import tempfile
from pathlib import Path
from verify_statusctrl_retail import Retail as Base,ROOT,BASE
OWNER,RAM,MSG,PAD,LIST=range(BASE+0x320000,BASE+0x320500,0x100)
class Value(C.Structure):_fields_=[('type',C.c_int),('number',C.c_double),('string',C.c_char_p),('length',C.c_size_t)]
class State(C.Structure):_fields_=[('disabled',C.c_uint8)]
def string(x):return Value(2,0,x,len(x))
class Retail(Base):
    def call(self,e,a):
        if e==0x3bbd40:return 0
        if e==0x38d4a0:return 1
        if e==0x38f820:return self.count
        if e==0x38f8f0:return self.token(self.argument)
        if e==0x236f80:return PAD
        if e==0x38f1d0:return 0
        if e==0x38f150:self.results.append(a[1]&255);return 0
        return super().call(e,a)
def main():
    elf=ROOT.parent.parent/'local/extracted/SLUS_208.36'
    if not elf.exists():print('stage input: private ELF unavailable, skipped');return
    w=Retail(elf.read_bytes());total=0
    with tempfile.TemporaryDirectory() as td:
        so=Path(td)/'input.so';subprocess.run(['cc','-shared','-fPIC','-std=c99','-I'+str(ROOT/'include'),str(ROOT/'src/stageinput.c'),'-o',str(so)],check=True)
        lib=C.CDLL(str(so));lib.dw4_stageinput_service.argtypes=[C.POINTER(State),C.c_char_p,C.POINTER(Value),C.c_size_t,C.POINTER(Value),C.c_char_p,C.c_size_t];lib.dw4_stageinput_slot.argtypes=[C.POINTER(State),C.c_int32]
        for previous in (0,1,128,255):
            for argument in ('ENABLE','DISABLE','STATUS','unknown'):
                for count in (0,1):
                    w.w(PAD+29,1,previous);w.argument=argument;w.count=count;w.results=[];w.invoke(0x3cd810,OWNER,RAM,MSG)
                    state=State(previous);args=(Value*5)(string(b'STAGECTL'),Value(),Value(1,-1,None,0),string(b'PADINPUT'),string(argument.encode()));result=Value();error=C.create_string_buffer(256)
                    assert not lib.dw4_stageinput_service(C.byref(state),b'sd',args,4+count,C.byref(result),error,256)
                    results=[] if result.type==0 else [int(result.number)]
                    assert (state.disabled,results)==(w.read(PAD+29,1),w.results),(previous,argument,count,state.disabled,results,w.results);total+=1
            w.w(PAD+29,1,previous);w.w(PAD+20,4,LIST);slots=[BASE+0x321000+i*0x100 for i in range(5)];w.list(LIST,slots)
            for player in range(6):
                address=w.invoke(0x39b810,PAD,player)&0xffffffff
                assert slots[lib.dw4_stageinput_slot(C.byref(State(previous)),player)]==address;total+=1
    print(f'stage input: {total} disable-byte/result/neutral-slot cases match original3cd810/39b810; enum/context/argument leaves controlled')
if __name__=='__main__':main()
