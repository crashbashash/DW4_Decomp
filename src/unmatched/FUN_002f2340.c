struct R2340 { long long p0, f8, f16, f24, f32, f40, f48, f56, f64, f72, f80, f88, f96; };
void FUN_002f2340(struct R2340 *arg0, int arg1, int arg2, int arg3) {
    long long a;
    long long b;

    if (arg3 != 0) {
        a = arg1;
        arg0->f8 = arg0->f8 + a;
        arg0->f24 = arg0->f24 + a;
        if (arg0->f32 < arg0->f24) {
            arg0->f32 = arg0->f24;
        }
        b = arg2;
        arg0->f40 = arg0->f40 + b;
        arg0->f56 = arg0->f56 + b;
        if (arg0->f64 < arg0->f56) {
            arg0->f64 = arg0->f56;
        }
        arg0->f72 = arg0->f72 + 1;
        arg0->f88 = arg0->f88 + 1;
        if (arg0->f96 < arg0->f88) {
            arg0->f96 = arg0->f88;
        }
    } else {
        a = arg1;
        b = arg2;
        arg0->f16 = arg0->f16 + a;
        arg0->f24 = arg0->f24 - a;
        arg0->f48 = arg0->f48 + b;
        arg0->f56 = arg0->f56 - b;
        arg0->f80 = arg0->f80 + 1;
        arg0->f88 = arg0->f88 - 1;
    }
}
