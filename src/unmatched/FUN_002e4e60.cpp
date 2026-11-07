extern "C" {
int igObject_GetSerializedSize(...);
int igObject_WritePersistentFields(int, int, int, int, unsigned char);
int thunk_FUN_002d7e90(...);
extern int DAT_004fb410[4];
}
class VC220 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual void d32(); virtual void d33(); virtual void d34(); virtual void d35(); virtual void d36(); virtual void d37(); virtual void d38(); virtual void d39(); virtual void d40(); virtual void d41(); virtual void d42(); virtual void d43(); virtual void d44(); virtual void d45(); virtual void d46(); virtual void d47(); virtual void d48(); virtual void d49(); virtual void d50(); virtual void d51(); virtual void d52(); virtual int vX(int, int); };
struct Lst { char pad8[8]; int n; };
struct Cx { char pad40[40]; Lst *f40; char pad44[68]; int f112; char pad116[8]; int f124; char pad128[40]; unsigned char f168; char pad169[3]; char pad172[4]; int f176; char pad180[12]; int f192; char pad196[84]; VC220 *f280; };
extern "C" void FUN_002e4e60(int *arg0, Cx *arg1) {
    int temp_v0;
    int var_s0;
    int var_s3;
    int var_s0_2;

    arg1->f124 = 0;
    arg1->f112 = arg1->f40->n;
    for (var_s0 = 0; var_s0 < arg1->f112; var_s0++) {
        temp_v0 = igObject_GetSerializedSize(thunk_FUN_002d7e90(arg1->f40, var_s0));
        arg1->f124 = arg1->f124 + temp_v0;
    }
    arg1->f176 = arg1->f280->vX(arg1->f124, 0x10);
    var_s3 = arg1->f176;
    for (var_s0_2 = 0; var_s0_2 < arg1->f112; var_s0_2++) {
        var_s3 += igObject_WritePersistentFields(thunk_FUN_002d7e90(arg1->f40, var_s0_2), var_s3, 0, arg1->f192, arg1->f168);
    }
    *arg0 = DAT_004fb410[0];
}
