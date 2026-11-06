/* The constant string address is still tested (if-else layout with the null arm first), and the
 * price switch has an uninitialised default. */
extern "C" {
void *FUN_002eb010(int);
void *StringPool_Construct(void *);
const char *StringPool_Intern(void *, const char *);
void StringChunk_ReleaseHeader(int, int *);
int beNDMWWindow_PresentModelAtOrigin(void *, int *, int, int *, int *);
int beNDMWWindow_RunMessageScript(void *, int *, int);
extern int DAT_0051cb38[4];
extern int DAT_0051cb40[4];
extern int DAT_0051cb60[4];
extern int DAT_0051cb70[4];
extern int DAT_0051cb80[4];
extern int DAT_0051cb88[4];
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
struct Sh { char p[44]; unsigned f44; char q[12]; int f60; int f64; };
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
extern "C" void Gap__Bec__beNDMWShopTitle01__vfunc_22(Sh *arg0) {
    int s;
    beNDMWWindow_PresentModelAtOrigin(arg0, DAT_0051cb60, 0, DAT_0051cb38, DAT_0051cb40);
    switch (arg0->f44) {
    case 1: s = 1100; break;
    case 2: s = 1200; break;
    case 3: s = 1300; break;
    case 4: s = 1400; break;
    case 5: s = 1500; break;
    case 6: s = 1600; break;
    case 7: s = 1700; break;
    case 8: s = 1800; break;
    case 9: s = 1900; break;
    case 10: s = 2000; break;
    }
    INTERN_APPEND(arg0->f60, DAT_0051cb70)
    INTERN_APPEND(arg0->f64, DAT_0051cb80)
    beNDMWWindow_RunMessageScript(arg0, DAT_0051cb88, s);
}
