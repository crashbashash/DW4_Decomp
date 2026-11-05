extern int DAT_004c2150[4];
struct P { int a; int b; };
struct T { char p0[8]; int count; char pc[4]; struct P *items; };
struct O { char p0[12]; int f12; struct T *t; int f20; };

void Gap__Core__igMemoryDictionary__vfunc_27(struct O *arg0) {
    struct T *t; int half; int j; struct P *pp; int n; int i;
    t = arg0->t;
    half = *(int *)((char *)t + 8) / 2;
    pp = t->items;
    n = t->count;
    for (i = 0; i < n; i++) {
        ((int *)pp)[i] = DAT_004c2150[0];
    }
    arg0->f12 = 0;
    arg0->f20 = 0;
    for (j = 0; j < half; j++) {
        pp->b = -1;
        pp++;
    }
}
