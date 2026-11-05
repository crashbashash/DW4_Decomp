typedef struct R { char pad[4]; int f4; } R;
R *FUN_002d7c50();
int igObject_Destroy();

int FUN_002d8460(void) {
    R *volatile sp1C;
    R *t;
    R *a;

    sp1C = FUN_002d7c50();
    t = sp1C;
    if (t != 0) {
        t->f4 = t->f4 + 1;
    }
    a = sp1C;
    if (a != 0) {
        if (a != 0) {
            a->f4 = a->f4 - 1;
            if (((unsigned long long) ((long long) a->f4 << 0x29) >> 0x29) == 0) {
                igObject_Destroy(a);
            }
        }
        return 1;
    }
    if (a != 0) {
        a->f4 = a->f4 - 1;
        if (((unsigned long long) ((long long) a->f4 << 0x29) >> 0x29) == 0) {
            igObject_Destroy(a);
        }
    }
    return 0;
}
