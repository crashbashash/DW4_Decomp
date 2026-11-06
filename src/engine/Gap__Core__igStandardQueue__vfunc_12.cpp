/* Queue teardown: while the queue still owns its data buffer (vfunc_25 returns `_data != 0`),
 * vfunc_24 frees it (it releases `_data` and zeroes it); then the thunk to FUN_00305000 runs the
 * shared release loop over the `_serviceThreads` list (FUN_00305000 is matched in src/unmatched).
 * DW4VC_96_0 / DW4VC_100_0 are stand-in classes: their single real virtual sits at vtable byte
 * offset 96 (slot 24) and 100 (slot 25) respectively. */
extern "C" {
int thunk_FUN_00305000(...);
void Gap__Core__igStandardQueue__vfunc_12(void **self);
}
class DW4VC_96_0 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual int vX(); };
class DW4VC_100_0 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual int vX(); };
void Gap__Core__igStandardQueue__vfunc_12(void **self) {
    if (((DW4VC_100_0 *)(self))->vX() != 0) {
        ((DW4VC_96_0 *)(self))->vX();
    }
    thunk_FUN_00305000(self);
}
