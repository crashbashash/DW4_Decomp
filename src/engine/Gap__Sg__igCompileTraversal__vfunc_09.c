typedef struct Q { char pad4[4]; int f4; } Q;
typedef struct C { char pad[28]; Q *f28; } C;
int Gap__Sg__igCommonTraversal__vfunc_09();
int igObject_Destroy();
extern Q * DAT_00562648[4];

void Gap__Sg__igCompileTraversal__vfunc_09(C *arg0, int arg1) {
    Q *t;
    Q *s;

    Gap__Sg__igCommonTraversal__vfunc_09();
    if (arg1 == 0) {
        s = DAT_00562648[0];
        if (s != 0) {
            s->f4 += 1;
        }
        t = arg0->f28;
        if (t != 0) {
            t->f4 -= 1;
            if ((t->f4 & 0x7fffff) == 0) {
                igObject_Destroy(t);
            }
        }
        arg0->f28 = s;
    }
}
