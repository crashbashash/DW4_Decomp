int Gap__Core__igObject__vfunc_16(void *);
int FUN_002eb010(int);
int StringChunk_ReleaseHeader(int, int *);
int StringPool_Construct(int);
int StringPool_Intern(int, char *);
extern int DAT_00586f20[4];
typedef struct S { char p[20]; int f20,f24,f28,f32,f36,f40,f44,f48,f52,f56,f60,f64,f68,f72,f76,f80; } S;
#define SETSTR(off) { \
    int v_; int s_; int old_; int *hd_; \
    if (DAT_00586f20[0] == 0) { \
        v_ = FUN_002eb010(0x10); \
        if (v_ != 0) v_ = StringPool_Construct(v_); \
        DAT_00586f20[0] = v_; \
    } \
    s_ = StringPool_Intern(DAT_00586f20[0], 0); \
    old_ = arg0->f##off; \
    if (old_ != 0) { \
        hd_ = (int *)(old_ - 8); \
        v_ = *(int *)(old_ - 4) - 1; \
        *(int *)(old_ - 4) = v_; \
        if (v_ == 0) StringChunk_ReleaseHeader(*hd_, hd_); \
    } \
    arg0->f##off = s_; }
void Gap__Core__igMemoryPoolInfo__vfunc_18(S *arg0) {
    Gap__Core__igObject__vfunc_16(arg0);
    SETSTR(20)
    SETSTR(24)
    arg0->f28 = 0;
    arg0->f32 = 0;
    arg0->f36 = 0;
    SETSTR(40)
    SETSTR(44)
    SETSTR(48)
    SETSTR(52)
    SETSTR(56)
    SETSTR(60)
    SETSTR(64)
    SETSTR(68)
    SETSTR(72)
    SETSTR(76)
    arg0->f80 = 0;
}
