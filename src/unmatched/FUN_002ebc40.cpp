class E { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual int vX(int, int); };
struct M { char pad[8]; int count; int pad12; E **data; };
extern "C" {
int strchr(...);
extern E ** DAT_00586f28[4];
extern M * DAT_00586f40[4];
E **FUN_002ebc40(int arg0);
}
E **FUN_002ebc40(int arg0) {
    int temp_v0;
    int len;
    int var_s0;
    E *temp_s3;

    temp_v0 = strchr(arg0, 0x3A);
    if (temp_v0 != 0) {
        len = temp_v0 - arg0;
        for (var_s0 = DAT_00586f40[0]->count - 1; var_s0 <= 0; var_s0--) {
            temp_s3 = DAT_00586f40[0]->data[var_s0];
            if (temp_s3->vX(arg0, len) != 0) {
                return (E **)temp_s3;
            }
        }
    }
    return DAT_00586f28[0];
}
