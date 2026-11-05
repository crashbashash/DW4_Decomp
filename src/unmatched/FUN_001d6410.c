typedef struct Rc { int w0; int refs; int cnt; int p; int data; } Rc;
typedef struct Ls { char p0[8]; unsigned cnt; char p1[4]; int *data; } Ls;
typedef struct Ob { char p0[28]; Ls *f28; } Ob;
Rc *FUN_0019f630();
int FUN_001c5740();
int FUN_001c5870();
int FUN_001c58c0();
int igObject_IsKindOf();
int ObjectList_AppendRetained();
int igObject_Destroy();
int igObject_GetAllocator();
extern int DAT_005619f8[16];
extern int DAT_00561ea0[16];
void FUN_001d6410(Ob *arg0, Ob *arg1, int arg2) {
    Rc *volatile sp7C;
    unsigned s1;
    unsigned s0;
    int s5;
    Ls *t0;
    Rc *t;
    if (arg1 != 0) {
        if (igObject_IsKindOf(arg1, DAT_005619f8[0]) != 0) {
            t0 = arg1->f28;
            s1 = 0;
            if (t0 != 0) {
                s1 = t0->cnt;
            }
            for (s0 = 0; s0 < s1; s0++) {
                s5 = arg1->f28->data[s0];
                FUN_001c5870(arg2, s0);
                FUN_001d6410(arg0, (Ob *)s5, arg2);
                FUN_001c58c0(arg2);
            }
        }
        if (igObject_IsKindOf(arg1, DAT_00561ea0[0]) != 0) {
            sp7C = FUN_0019f630(igObject_GetAllocator(arg0));
            FUN_001c5740(sp7C, arg2);
            ObjectList_AppendRetained(arg0->f28, sp7C);
            t = sp7C;
            if (t != 0) {
                t->refs = t->refs - 1;
                if (((unsigned long long)(long long)t->refs & 0x7fffffULL) == 0) {
                    igObject_Destroy(t);
                }
            }
        }
    }
}
