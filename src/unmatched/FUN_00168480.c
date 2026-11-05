long long FUN_00168420(void *);
struct D { char pad24[24]; int f24; int f28; int f32; };
void FUN_00168480(struct D *arg0, char *arg1) {
    int i; int a; int v;
    v = arg0->f24 - 1;
    arg0->f24 = v;
    if (v <= 0) {
        arg0->f24 = (signed char)FUN_00168420(arg0);
        a = arg0->f24;
        if (a & 0x80) {
            arg0->f24 = (a & 0x7F) + 1;
            arg0->f28 = 1;
            for (i = 0; i < arg0->f32; i++) { arg1[i] = FUN_00168420(arg0); }
        } else {
            arg0->f24 = a + 1;
            arg0->f28 = 0;
        }
    }
    if (arg0->f28 == 0) {
        for (i = 0; i < arg0->f32; i++) { arg1[i] = FUN_00168420(arg0); }
    }
}
