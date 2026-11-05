/* 0x002b5fe0 — FUN_002b5fe0. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
extern "C" {
int FUN_002b61d0(...);
void **igObject_AllocateRawStorage(...);
void **FUN_0030edd0(...);
void **igMetaObject_CreateInstance(...);
extern int DAT_005856e8[4];
extern unsigned char * DAT_00586dc8[4];
void **FUN_002b5fe0(int arg0);
}
class DW4VC_36_1 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual int vX(int); };
class DW4VC_44_0 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual int vX(); };
void **FUN_002b5fe0(int arg0) {
    void **var_s0;

    if (*DAT_00586dc8[0] != 0) {
        FUN_002b61d0();
        var_s0 = (void **)(igMetaObject_CreateInstance(DAT_005856e8[0], arg0));
    } else {
        var_s0 = (void **)(igObject_AllocateRawStorage(0x34, 0, arg0));
        if (var_s0 != 0) {
            var_s0 = (void **)(FUN_0030edd0(var_s0, 1));
        }
        ((DW4VC_44_0 *)(var_s0))->vX();
        ((DW4VC_36_1 *)(var_s0))->vX((int)(0));
    }
    return var_s0;
}
