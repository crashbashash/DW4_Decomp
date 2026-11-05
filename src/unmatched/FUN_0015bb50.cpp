extern "C" float FUN_00123658(float, float);
struct B { char pad[44]; int f44; };
struct A { char p0[8]; B *b; char p1[8]; float f20; float f24; float f28; char p2[48]; unsigned f80; };
struct V { float x; float y; };
extern "C" bool FUN_0015bb50(A *arg0, V *arg1, float *arg2) {
    bool ok = true;
    if (arg0->b->f44 > 1) {
        *arg2 = arg1->y + arg1->x * arg0->f28;
    } else {
        *arg2 = arg1->y;
    }
    unsigned fl = arg0->f80;
    if (fl & 2) {
        float t = *arg2;
        if (t < arg0->f20 || !(t <= arg0->f24)) ok = false;
    }
    if (fl & 1) {
        if (ok) *arg2 = FUN_00123658(*arg2, 1.0f);
    }
    return ok;
}
