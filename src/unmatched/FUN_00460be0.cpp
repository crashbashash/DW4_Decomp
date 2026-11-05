class V { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual int vX(); };
struct P { char pad[32]; int f32; };
extern "C" {
int igObject_IsKindOf(...);
int igMetaObject_FindFieldByName(...);
int igProperty_FindByPointer(...);
extern int DAT_0051fab8[4];
extern int DAT_0055f468[4];
extern int DAT_00585b20[4];
void FUN_00460be0(V *arg0, P *arg1);
}
void FUN_00460be0(V *arg0, P *arg1) {
    int var_s0;

    var_s0 = igMetaObject_FindFieldByName(DAT_0055f468[0], &DAT_0051fab8[0]);
    if ((var_s0 != 0) && (igObject_IsKindOf(var_s0, DAT_00585b20[0]) != 0)) {
        asm { nop }
    } else {
        var_s0 = 0;
        asm { nop }
    }
    igProperty_FindByPointer(arg1->f32, var_s0, arg0->vX());
}