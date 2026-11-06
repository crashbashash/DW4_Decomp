extern int FUN_002d6f50();
extern int FUN_002d7090();
extern int FUN_002d78e0();
extern int FUN_002eb010();
extern int FUN_00454290();
extern int Gap__Core__igObject__vfunc_11();
extern int StringChunk_ReleaseHeader();
extern int StringPool_Construct();
extern int *StringPool_Intern();
extern int DAT_004e9840[4];
extern int DAT_004e9850[4];
extern int DAT_004e9860[4];
extern int DAT_00586f20[4];
struct A { char pad[28]; int f28; int f32; int f36; char pad40[4]; int f44; char pad48[24]; int f72; };
void Gap__Core__igInsightCore__vfunc_13(struct A *arg0) {
    int * volatile sp2C;
    int * volatile sp28;
    int * volatile sp24;
    int pool;
    int *r;
    int *t;
    int *a1;
    int k;

    Gap__Core__igObject__vfunc_11();
    if (&DAT_004e9840[0] == 0) {
        r = 0;
    } else {
        if (DAT_00586f20[0] == 0) {
            pool = FUN_002eb010(16);
            if (pool != 0) pool = StringPool_Construct(pool);
            DAT_00586f20[0] = pool;
        }
        r = StringPool_Intern(DAT_00586f20[0], &DAT_004e9840[0]);
    }
    sp2C = r;
    if (&DAT_004e9850[0] == 0) {
        r = 0;
    } else {
        if (DAT_00586f20[0] == 0) {
            pool = FUN_002eb010(16);
            if (pool != 0) pool = StringPool_Construct(pool);
            DAT_00586f20[0] = pool;
        }
        r = StringPool_Intern(DAT_00586f20[0], &DAT_004e9850[0]);
    }
    sp28 = r;
    if (&DAT_004e9860[0] == 0) {
        r = 0;
    } else {
        if (DAT_00586f20[0] == 0) {
            pool = FUN_002eb010(16);
            if (pool != 0) pool = StringPool_Construct(pool);
            DAT_00586f20[0] = pool;
        }
        r = StringPool_Intern(DAT_00586f20[0], &DAT_004e9860[0]);
    }
    sp24 = r;
    FUN_002d78e0((int)(long)arg0->f28, sp2C);
    FUN_002d78e0((int)(long)arg0->f28, sp28);
    FUN_002d78e0((int)(long)arg0->f28, sp24);
    FUN_002d7090((int)(long)arg0->f28, sp2C, sp28);
    FUN_002d7090((int)(long)arg0->f28, sp28, sp24);
    FUN_002d7090((int)(long)arg0->f28, (int)(long)arg0->f44, sp2C);
    FUN_002d6f50(arg0->f28, arg0->f44, 0);
    arg0->f72 = 0x40000;
    *(struct A **)(arg0->f36 + 8) = arg0;
    FUN_00454290(arg0->f32, arg0->f36);
    t = sp24;
    if (t != 0) {
        a1 = t - 2;
        k = t[-1] - 1;
        t[-1] = k;
        if (k == 0) StringChunk_ReleaseHeader(*a1, a1);
    }
    t = sp28;
    if (t != 0) {
        a1 = t - 2;
        k = t[-1] - 1;
        t[-1] = k;
        if (k == 0) StringChunk_ReleaseHeader(*a1, a1);
    }
    t = sp2C;
    if (t != 0) {
        a1 = t - 2;
        k = t[-1] - 1;
        t[-1] = k;
        if (k == 0) StringChunk_ReleaseHeader(*a1, a1);
    }
}
