extern "C" { int FUN_002d91c0(...); int FUN_003087a0(...); int igObject_Destroy(...); }
struct S1 { char pad4[4]; int f4; char pad8[24]; S1 *f32; };
struct W { char p[12]; S1 *f12; };
extern "C" void FUN_00309750(W *arg0, int arg1);
void FUN_00309750(W *arg0, int arg1) {
    S1 *sp3C;
    int temp_v0;
    bool var_s1;
    S1 *temp_a0;
    S1 *t;

    FUN_003087a0(&sp3C, arg0, arg1);
    t = sp3C;
    if (t == 0) {
        if (t != 0) {
            t->f4 = (int)((int) (t->f4 - 1));
            if (((unsigned long long) ((long long) t->f4 << 0x29) >> 0x29) == 0) {
                igObject_Destroy(t);
            }
        }
    } else {
        var_s1 = 0;
        if (t == arg0->f12) {
            var_s1 = 1;
        }
        if (t->f32 == 0) {
            t->f32 = (S1 *)arg0;
        }
        temp_v0 = FUN_002d91c0(sp3C);
        if (var_s1 && (temp_v0 <= 0)) {
            temp_a0 = arg0->f12;
            if (temp_a0 != 0) {
                temp_a0->f4 = (int)((int) (temp_a0->f4 - 1));
                if (((unsigned long long) ((long long) temp_a0->f4 << 0x29) >> 0x29) == 0) {
                    igObject_Destroy(temp_a0);
                }
            }
            arg0->f12 = 0;
        }
        t = sp3C;
        if (t != 0) {
            t->f4 = (int)((int) (t->f4 - 1));
            if (((unsigned long long) ((long long) t->f4 << 0x29) >> 0x29) == 0) {
                igObject_Destroy(t);
            }
        }
    }
}

