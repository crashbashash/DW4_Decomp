extern "C" {
void *FUN_002eb010(int);
void *StringPool_Construct(void *);
const char *StringPool_Intern(void *, const char *);
void StringChunk_ReleaseHeader(int, int *);
int beNDMWWindow_PresentModelAtOrigin(void *, int *, int, int *, int *);
int beNDMWWindow_RunMessageScript(void *, int *, int);
extern int DAT_0051a978[4];
extern int DAT_0051a988[4];
extern int DAT_0051a998[4];
extern int DAT_0051a9a8[4];
extern int DAT_0051a9b8[4];
extern int DAT_0051a9c0[4];
extern int DAT_0051a9c8[4];
extern int DAT_0051a9d0[4];
extern int DAT_0051a9e0[4];
extern void *DAT_00586f20[4];
}
/* Owning stack reference to a pooled string token (reference count at p[-1], chunk header at
 * p[-2]); releases the token on scope exit. */
class StringRef {
public:
    const char *p;
    StringRef(const char *s) : p(s) {}
    ~StringRef() { if (p) { int *h = (int *)p - 2; int r = ((int *)p)[-1] - 1; ((int *)p)[-1] = r; if (r == 0) StringChunk_ReleaseHeader(*h, h); } }
};
extern "C" int StringList_AppendRetained(int, StringRef *);
struct Sh { char p[60]; int f60; int f64; char q[12]; const char *f80; int f84; int f88; int f92; int f96; int pad100; char f104; };
#define INTERN_APPEND(field, text) { \
    const char *tok; \
    if ((text) == 0) { \
        tok = 0; \
    } else { \
        if (DAT_00586f20[0] == 0) { \
            void *pool = FUN_002eb010(0x10); \
            if (pool != 0) pool = StringPool_Construct(pool); \
            DAT_00586f20[0] = pool; \
        } \
        tok = StringPool_Intern(DAT_00586f20[0], (const char *)(text)); \
    } \
    StringRef held(tok); \
    StringList_AppendRetained(field, &held); }
extern "C" void Gap__Bec__beNDMWStatusSelect00__vfunc_22(Sh *arg0) {
    const char *t;
    const char *old;
    beNDMWWindow_PresentModelAtOrigin(arg0, DAT_0051a978, 0, DAT_0051a988, DAT_0051a998);
    INTERN_APPEND(arg0->f60, DAT_0051a9a8)
    INTERN_APPEND(arg0->f64, DAT_0051a9b8)
    INTERN_APPEND(arg0->f60, DAT_0051a9a8)
    INTERN_APPEND(arg0->f64, DAT_0051a9c0)
    INTERN_APPEND(arg0->f60, DAT_0051a9a8)
    INTERN_APPEND(arg0->f64, DAT_0051a9c8)
    beNDMWWindow_RunMessageScript(arg0, DAT_0051a9d0, 0xF);
    if (DAT_00586f20[0] == 0) {
        void *pool = FUN_002eb010(0x10);
        if (pool != 0) pool = StringPool_Construct(pool);
        DAT_00586f20[0] = pool;
    }
    t = StringPool_Intern(DAT_00586f20[0], (const char *)DAT_0051a9e0);
    old = arg0->f80;
    if (old != 0) {
        int *hd = (int *)old - 2;
        int cnt = ((int *)old)[-1] - 1;
        ((int *)old)[-1] = cnt;
        if (cnt == 0) StringChunk_ReleaseHeader(*hd, hd);
    }
    arg0->f80 = t;
    arg0->f84 = 3;
    arg0->f88 = 0xC2A60000;
    arg0->f92 = 0x43510000;
    arg0->f96 = 0;
    arg0->f104 = 0;
}
