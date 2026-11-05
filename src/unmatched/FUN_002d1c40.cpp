extern "C" {
int *FUN_00125d50(...);
int FUN_002eb010(...);
void *StringPool_Construct(...);
char *StringPool_Intern(...);
int StringChunk_ReleaseHeader(...);
extern int DAT_004f9460[4];
extern int DAT_004f9468[4];
extern int DAT_004f9470[4];
extern void *DAT_00586f20[4];
}
struct SRel { static inline void go(char *s) {
    if (s) {
        int *a1 = (int *)(s - 8);
        int v = *(int *)(s - 4) - 1;
        *(int *)(s - 4) = v;
        if (v == 0) {
            StringChunk_ReleaseHeader(*a1, a1);
        }
    }
} };
struct Pool { static inline void *get() {
    if (DAT_00586f20[0] == 0) {
        void *p = (void *)FUN_002eb010(16);
        if (p != 0) {
            p = StringPool_Construct(p);
        }
        DAT_00586f20[0] = p;
    }
    return DAT_00586f20[0];
} };
struct Obj { char p[920]; char *m920; char *m924; };
extern "C" void FUN_002d1c40(Obj *arg0);
void FUN_002d1c40(Obj *arg0) {
    char * volatile sp3C;
    char *s1;
    char *t;
    sp3C = 0;
    s1 = (char *)FUN_00125d50(DAT_004f9460);
    s1 = StringPool_Intern(Pool::get(), s1);
    SRel::go(t = sp3C);
    sp3C = s1;
    t = sp3C;
    if (t) {
        *(int *)(t - 4) = *(int *)(t - 4) + 1;
    }
    SRel::go(arg0->m920);
    arg0->m920 = sp3C;
    s1 = StringPool_Intern(Pool::get(), DAT_004f9468);
    SRel::go(arg0->m924);
    arg0->m924 = s1;
    s1 = StringPool_Intern(Pool::get(), DAT_004f9470);
    SRel::go(arg0->m924);
    arg0->m924 = s1;
    SRel::go(t = sp3C);
}
