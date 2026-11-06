extern "C" {
int igRawRefMetaField_EnsureRegistered(...);
void **igObject_AllocateRawStorage(...);
void **FUN_00305400(...);
void **igMetaObject_CreateInstance(...);
extern int DAT_00585a80[4];
extern unsigned char * DAT_00586dc8[4];
void **FUN_002bba00(int arg0);
}
class DW4VC_36_1 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual int vX(int); };
class DW4VC_44_0 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual int vX(); };
void **FUN_002bba00(int arg0) {
    void **var_s0;

    if (*DAT_00586dc8[0] != 0) {
        igRawRefMetaField_EnsureRegistered();
        var_s0 = (void **)(igMetaObject_CreateInstance(DAT_00585a80[0], arg0));
    } else {
        var_s0 = (void **)(igObject_AllocateRawStorage(0x38, 0, arg0));
        if (var_s0 != 0) {
            var_s0 = (void **)(FUN_00305400(var_s0, 1));
        }
        ((DW4VC_44_0 *)(var_s0))->vX();
        ((DW4VC_36_1 *)(var_s0))->vX((int)(0));
    }
    return var_s0;
}
