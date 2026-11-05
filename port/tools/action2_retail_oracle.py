"""Test adapter: original Action2 instructions over the native logo arena.
Clock values and non-timing leaves are supplied; EE arithmetic remains modeled.
"""
import ctypes as C
from verify_action2time import Retail, LEAF, py_node_time
from verify_loadintf2 import PEEK, POKE, CALL, sx, MASK

class Api(C.Structure):
    _fields_=[(n,C.c_void_p) for n in ('user','peek','poke','call','call64')]
INVOKE=C.CFUNCTYPE(None,C.c_int,C.c_int,C.POINTER(Api),C.POINTER(C.c_int32))
BASE=0x1500000
GLOBALS={0x585be0,0x589fe8,0x589fc8,0x589fb0,0x589fa0,0x589f98,0x554c14}

class Oracle(Retail):
    def __init__(self,image,api):
        super().__init__(image);self.api=api
    def read(self,a,n):
        if hasattr(self,'api') and (BASE<=a<BASE+0x2000 or a in GLOBALS):
            if n==8:return self.read(a,4)|(self.read(a+4,4)<<32)
            return PEEK(self.api.peek)(self.api.user,a,n)&((1<<(n*8))-1)
        return super().read(a,n)
    def write(self,a,n,v):
        if hasattr(self,'api') and BASE<=a<BASE+0x2000:
            if n==8:
                self.write(a,4,v);self.write(a+4,4,v>>32);return
            POKE(self.api.poke)(self.api.user,a,n,sx(v,32));return
        super().write(a,n,v)
    def call_hook(self,addr):
        self.r[2]=CALL(self.api.call)(self.api.user,addr,(C.c_int32*8)(*[sx(v,32) for v in self.r[4:12]]))&MASK

def install(image,lib,traces,errors,hits):
    def invoke(i,addr,api,args):
        try:
            hits.add((i,addr))
            original=api.contents
            read=PEEK(original.peek);write=POKE(original.poke);call=CALL(original.call)
            def store(u,a,n,v):
                traces[i].append(('a2write',a,n,v));write(original.user,a,n,v)
            def leaf(u,a,v):
                try:
                    spec='p' if a==BASE+0x1300 else LEAF[a]
                    traces[i].append(('a2call',a,*v[:len(spec)]))
                    return call(original.user,a,v)
                except Exception as e:
                    errors.append(e);return 0
            peek=PEEK(lambda u,a,n:read(original.user,a,n));poke=POKE(store);callback=CALL(leaf)
            proxy=Api(None,*[C.cast(f,C.c_void_p) for f in (peek,poke,callback)],original.call64)
            if i==1:
                cpu=Oracle(image,proxy);cpu.invoke(addr,args[:3]);
                hits.update((i,pc) for pc in cpu.covered if pc in (0x376340,0x3764c0,0x376de0,0x376f40,0x3a7a20,0x3a7e90,0x3a7fd0,0x398e80,0x230110))
                return
            name={0x377700:'a2_start_components',0x3778d0:'a2_update',0x377990:'a2_msg_iscomend'}[addr]
            n=3 if addr==0x377990 else 2
            fn=getattr(lib,name);fn.argtypes=[C.POINTER(Api)]+[C.c_int32]*n;fn.restype=C.c_int32 if n==3 else None
            fn(C.byref(proxy),*args[:n])
        except Exception as e:
            errors.append(e)
    callback=INVOKE(invoke)
    lib.bridge_action2_oracle.argtypes=[INVOKE];lib.bridge_action2_oracle(callback)
    lib.bridge_clock.argtypes=[C.c_int,C.c_int64]
    return callback
