#define INTERN_APPEND(field, text) { \
    const char *tok; \
    if ((text) == 0) { \
        tok = 0; \
    } else { \
        if (g_stringPool[0] == 0) { \
            void *pool = FUN_002eb010(0x10); \
            if (pool != 0) pool = StringPool_Construct(pool); \
            g_stringPool[0] = pool; \
        } \
        tok = StringPool_Intern(g_stringPool[0], (const char *)(text)); \
    } \
    StringRef held(tok); \
    StringList_AppendRetained(field, &held); }

extern "C" int beNDMWWindow_PresentModelAtOrigin(...);
extern "C" void Gap__Bec__beNDMWShopTitle00__vfunc_22(int *arg0);
extern "C" void *FUN_002eb010(int);
extern "C" void *StringPool_Construct(void *);
extern "C" const char *StringPool_Intern(void *, const char *);
extern "C" void StringChunk_ReleaseHeader(int, int *);
extern "C" int beNDMWWindow_RunMessageScript(void *, int *, int);
extern "C" void Gap__Bec__beNDMWShopTitle03__vfunc_22(int p0, char * p1, int p2, char * p3, char * p4);
extern "C" int Gap__Bec__beNDMWShopTitle03__vfunc_20(void);
extern "C" int Gap__Bec__beNDMWShopTitle01__vfunc_20(void);
extern "C" int Gap__Bec__beNDMWShopTitle00__vfunc_20(void);
extern "C" int DAT_0051cb28[4];
extern "C" int DAT_0051cb38[4];
extern "C" int DAT_0051cb40[4];
extern "C" int DAT_0051cb50[4];
extern "C" int DAT_0051cb60[4];
extern "C" int DAT_0051cb70[4];
extern "C" int DAT_0051cb80[4];
extern "C" int DAT_0051cb88[4];
extern "C" void *g_stringPool[4];
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
extern "C" void Gap__Bec__beNDMWShopTitle01__vfunc_22(Sh *arg0);
extern "C" char DAT_0051cbd0[];
extern "C" int g_beNDMWShopTitle03_metaObject[4];
extern "C" int g_beNDMWShopTitle01_metaObject[4];
extern "C" int g_beNDMWShopTitle00_metaObject[4];

void Gap__Bec__beNDMWShopTitle00__vfunc_22(int *arg0) {
    beNDMWWindow_PresentModelAtOrigin(arg0, &DAT_0051cb28[0], 0, &DAT_0051cb38[0], &DAT_0051cb40[0]);
    beNDMWWindow_PresentModelAtOrigin(arg0, &DAT_0051cb50[0], 0, &DAT_0051cb38[0], &DAT_0051cb40[0]);
}

void Gap__Bec__beNDMWShopTitle01__vfunc_22(Sh *arg0) {
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

void Gap__Bec__beNDMWShopTitle03__vfunc_22(int p0, char * p1, int p2, char * p3, char * p4)
{
    beNDMWWindow_PresentModelAtOrigin(p0, DAT_0051cbd0, 0, ((char *)DAT_0051cb38), ((char *)DAT_0051cb40));
}

int Gap__Bec__beNDMWShopTitle03__vfunc_20(void)
{
    return g_beNDMWShopTitle03_metaObject[0];
}

int Gap__Bec__beNDMWShopTitle01__vfunc_20(void)
{
    return g_beNDMWShopTitle01_metaObject[0];
}

int Gap__Bec__beNDMWShopTitle00__vfunc_20(void)
{
    return g_beNDMWShopTitle00_metaObject[0];
}

