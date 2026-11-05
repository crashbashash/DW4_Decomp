typedef struct S1 { char pad4[4]; int f4; } S1;
typedef struct O { char pad8[8]; S1 *a; S1 *b; } O;
extern "C" {
int igObject_Destroy(S1 *);
int FUN_003323d0(S1 *);
void FUN_003a6b50(O *arg0);
}
void FUN_003a6b50(O *arg0) {
    S1 *t0;
    S1 *t1;
    S1 *t2;
    t0 = arg0->b;
    if (t0 != 0) {
        t0->f4 = (int)((int) (t0->f4 - 1));
        if (((unsigned long long) ((long long) t0->f4 << 0x29) >> 0x29) == 0) {
            igObject_Destroy(t0);
        }
    }
    arg0->b = 0;
    t1 = arg0->a;
    if (t1 != 0) {
        FUN_003323d0(t1);
    }
    t2 = arg0->a;
    if (t2 != 0) {
        t2->f4 = (int)((int) (t2->f4 - 1));
        if (((unsigned long long) ((long long) t2->f4 << 0x29) >> 0x29) == 0) {
            igObject_Destroy(t2);
        }
    }
    arg0->a = 0;
}
