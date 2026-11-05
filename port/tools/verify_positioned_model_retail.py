#!/usr/bin/env python3
"""Compare 3f5c90's positioned model branch with native registered commands."""
from native_shared import build_shared
import ctypes as C
import itertools
import struct
import subprocess
import tempfile
from pathlib import Path
from verify_statusctrl_retail import Retail as BaseRetail, NODE, BASE, ROOT
from verify_scriptservices_retail import Value, CALL

class Retail(BaseRetail):
    def call(self,e,a):
        a=[v&0xffffffff for v in a]
        if e==0x38e5f0:
            self.events.append(('query' if self.string(a[4])=='ISRUN' else 'direct',self.string(a[2]),C.c_int32(a[3]).value,self.string(a[4])));return 0
        if e==0x38f220:return self.active
        if e==0x38d860:self.name=self.string(a[2]);self.slot=C.c_int32(a[3]).value;return 0
        if e==0x38f830:self.sequence=self.string(a[1]);return 0
        if e==0x38f4b0:self.position=tuple(struct.unpack('<f',self.read(a[1]+i*4,4).to_bytes(4,'little'))[0] for i in range(3));return 0
        if e==0x38e060:self.events.append(('generate',self.name,self.slot,self.sequence,self.position));return 0
        return super().call(e,a)

def main():
    elf=ROOT.parent.parent/'local/extracted/SLUS_208.36'
    if not elf.exists():print('positioned model: private ELF unavailable, skipped');return
    w=Retail(elf.read_bytes());total=0
    with tempfile.TemporaryDirectory() as td:
        td=Path(td);bridge=td/'bridge.c';bridge.write_text('''#include "dw4/statusui.h"
static dw4_script_binding sink;
void set_sink(dw4_script_binding cb){sink=cb;}
int dw4_scriptservices_call(void *sd,const char *method,const dw4_script_value *a,size_t n,dw4_script_value *r,char *e,size_t cap)
{(void)sd;return sink(NULL,method,a,n,r,e,cap);}
int positioned(const char *name,int slot,const char *seq,float x,float y,float z,char *e,size_t cap)
{dw4_statusview_context c={0};c.sd=(dw4_scriptservices *)(uintptr_t)1;return dw4_statusui_positioned(&c,name,slot,seq,x,y,z,e,cap);}
''')
        so=td/'positioned.so';build_shared(['cc','-shared','-fPIC','-std=c99','-I'+str(ROOT/'include'),str(ROOT/'src/statusui.c'),str(bridge),'-o',str(so)],check=True)
        names=[line.split()[-1] for line in subprocess.check_output(['nm','-D','-u',str(so)],text=True).splitlines() if line.split()[-1].startswith('dw4_')]
        stub=td/'stubs.c';stub.write_text('#include <stdlib.h>\n'+''.join('void '+name+'(void){abort();}\n' for name in names))
        stubso=td/'stubs.so';subprocess.run(['cc','-shared','-fPIC',str(stub),'-o',str(stubso)],check=True)
        stubs=C.CDLL(str(stubso),mode=C.RTLD_GLOBAL);lib=C.CDLL(str(so));lib.set_sink.argtypes=[CALL]
        lib.positioned.argtypes=[C.c_char_p,C.c_int,C.c_char_p,C.c_float,C.c_float,C.c_float,C.c_char_p,C.c_size_t]
        for active,slot,position in itertools.product((0,1,256),(0,3),((-121,109,0),(12,13,14))):
            w.active=active;w.events=[]
            for i,v in enumerate(position):w.w(BASE+0x280000+i*4,4,int.from_bytes(struct.pack('<f',v),'little'))
            w.invoke(0x3f5c90,NODE,w.token('i_stcursor04'),slot,w.token('SQ_OPEN01'),0,BASE+0x280000)
            events=[]
            @CALL
            def sink(u,method,a,n,r,error,cap):
                name=a[1].string.decode();key=a[3].string.decode();owner=int(a[2].number)
                if method==b'querySD':events.append(('query',name,owner,key));r[0]=Value(1,active,None,0)
                elif key=='GENERATE':
                    seq,vector=a[4].string.decode().split('/V<');xyz=tuple(float(x) for x in vector[:-1].split(','));events.append(('generate',name,owner,seq,xyz))
                else:events.append(('direct',name,owner,key))
                return 0
            lib.set_sink(sink);error=C.create_string_buffer(256)
            assert not lib.positioned(b'i_stcursor04',slot,b'SQ_OPEN01',*position,error,len(error))
            assert events==w.events,(active,slot,position,events,w.events)
            total+=1
    print(f'positioned model: {total} active/inactive/256-result command traces match original 3f5c90; receiver/position leaves controlled, NULL close key adds no tracking')
if __name__=='__main__':main()
