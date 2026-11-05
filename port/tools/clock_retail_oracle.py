"""Run retail clock instructions over the port's clock arena and model callback."""
import ctypes as C
from verify_systemclock import Retail, Api, READ, WRITE, CALL
BASE=0x1600000
INVOKE=C.CFUNCTYPE(C.c_uint64,C.c_int,C.c_uint32,C.POINTER(Api),C.c_uint64,C.c_uint64)
class Oracle(Retail):
    def __init__(self,image,api):
        super().__init__(image);self.api=api
    def read(self,a,n):
        if hasattr(self,'api') and BASE<=a<BASE+0x800:return self.api.read(self.api.user,a,n)
        return super().read(a,n)
    def write(self,a,n,v):
        if hasattr(self,'api') and BASE<=a<BASE+0x800:
            self.api.write(self.api.user,a,n,v);return
        super().write(a,n,v)
    def call_hook(self,entry):
        self.r[2]=self.api.call(self.api.user,entry,(C.c_uint64*8)(*self.r[4:12]))
def install(image,lib,traces,errors,hits):
    fn=lib.dw4_clock_call
    fn.argtypes=[C.POINTER(Api),C.c_uint32,C.c_uint64,C.c_uint64];fn.restype=C.c_uint64
    def invoke(i,entry,api,a,b):
        try:
            hits.add((i,entry));original=api.contents
            def write(u,addr,n,v):
                traces[i].append(('clock-store',addr,n,v));original.write(original.user,addr,n,v)
            def call(u,addr,args):
                traces[i].append(('clock-call',addr,args[0]))
                return original.call(original.user,addr,args)
            proxy=Api(None,READ(lambda u,a,n:original.read(original.user,a,n)),WRITE(write),CALL(call))
            if i==1:Oracle(image,proxy).invoke(entry,a,b)
            else:fn(C.byref(proxy),entry,a,b)
            return 0 # Only void lifecycle/update entries are invoked by the adapter.
        except Exception as e:errors.append(e);return 0
    callback=INVOKE(invoke)
    lib.bridge_clock_oracle.argtypes=[INVOKE];lib.bridge_clock_oracle(callback)
    return callback
