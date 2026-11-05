/* 0x002bf2e0 — igMemoryRefMetaField_Create. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
extern "C" {
int igMemoryRefMetaField_EnsureRegistered(...);
void **igObject_AllocateRawStorage(...);
void **igMemoryRefMetaField_Construct(...);
void **igMetaObject_CreateInstance(...);
extern int DAT_00585d80[4];
extern unsigned char * DAT_00586dc8[4];
void **igMemoryRefMetaField_Create(int arg0);
}
class DW4VC_36_1 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual int vX(int); };
class DW4VC_44_0 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual int vX(); };
void **igMemoryRefMetaField_Create(int arg0) {
    void **var_s0;

    if (*DAT_00586dc8[0] != 0) {
        igMemoryRefMetaField_EnsureRegistered();
        var_s0 = (void **)(igMetaObject_CreateInstance(DAT_00585d80[0], arg0));
    } else {
        var_s0 = (void **)(igObject_AllocateRawStorage(0x50, 0, arg0));
        if (var_s0 != 0) {
            var_s0 = (void **)(igMemoryRefMetaField_Construct(var_s0, 1));
        }
        ((DW4VC_44_0 *)(var_s0))->vX();
        ((DW4VC_36_1 *)(var_s0))->vX((int)(0));
    }
    return var_s0;
}
