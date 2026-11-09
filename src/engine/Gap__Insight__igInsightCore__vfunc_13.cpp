extern "C" int FUN_002d6f50(...);
extern "C" int FUN_002d7090(...);
extern "C" int FUN_002d78e0(...);
extern "C" int FUN_002eb010(...);
extern "C" int FUN_00454290(...);
extern "C" int Gap__Core__igObject__vfunc_11(...);
extern "C" int StringChunk_ReleaseHeader(...);
extern "C" int StringPool_Construct(...);
extern "C" int *StringPool_Intern(...);
extern "C" int DAT_004e9840[4];
extern "C" int DAT_004e9850[4];
extern "C" int DAT_004e9860[4];
extern "C" int DAT_00586f20[4];
struct A { char pad[28]; int f28; int f32; int f36; char pad40[4]; int f44; char pad48[24]; int f72; };
struct StringRef {
    int *p;
    StringRef(int *text) {
        int *interned;
        if (text == 0) {
            interned = 0;
        } else {
            if (DAT_00586f20[0] == 0) {
                int pool = FUN_002eb010(16);
                if (pool != 0) pool = StringPool_Construct(pool);
                DAT_00586f20[0] = pool;
            }
            interned = StringPool_Intern(DAT_00586f20[0], text);
        }
        p = interned;
    }
    ~StringRef() {
        int *s = p;
        if (s != 0) {
            int *hd = s - 2;
            int cnt = s[-1] - 1;
            s[-1] = cnt;
            if (cnt == 0) StringChunk_ReleaseHeader(*hd, hd);
        }
    }
};
extern "C" void Gap__Insight__igInsightCore__vfunc_13(struct A *arg0) {
    Gap__Core__igObject__vfunc_11();
    StringRef first(&DAT_004e9840[0]);
    StringRef second(&DAT_004e9850[0]);
    StringRef third(&DAT_004e9860[0]);
    FUN_002d78e0(arg0->f28, first.p);
    FUN_002d78e0(arg0->f28, second.p);
    FUN_002d78e0(arg0->f28, third.p);
    FUN_002d7090(arg0->f28, first.p, second.p);
    FUN_002d7090(arg0->f28, second.p, third.p);
    FUN_002d7090(arg0->f28, arg0->f44, first.p);
    FUN_002d6f50(arg0->f28, arg0->f44, 0);
    arg0->f72 = 0x40000;
    *(struct A **)(arg0->f36 + 8) = arg0;
    FUN_00454290(arg0->f32, arg0->f36);
}
