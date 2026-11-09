extern "C" {
void *FUN_002eb010(int);
void *StringPool_Construct(void *);
const char *StringPool_Intern(void *, const char *);
void StringChunk_ReleaseHeader(int, int *);
void *FUN_003b51b0(void *);
void *Memory_GetAllocatorBySelector(int);
void *igObject_GetAllocator();
int beNDMWWindow_BindContext(void *, void *, int, int, int);
int ObjectList_AppendRetained(int, void *);
int beNDMWWindow_RunMessageScript(void *, int *, int);
int igObject_Destroy(void *);
extern int DAT_00519b50[4];
extern int DAT_00519b90[4];
extern int DAT_00519d98[4];
extern void *DAT_00586f20[4];
extern int DAT_00587110[4];
extern unsigned char GPR_00554c14;
}
struct Item { char p[24]; int f24; };
struct List { char p[8]; int n; int pad; Item **data; };
struct Sh { char p[8]; int f8; char p2[8]; int f20; char p3[28]; int f52; char p4[28]; int f84; char p5[4]; int f92; char p6[4]; List *f100; };
struct Win { int w0; int refs; char p[52]; int f60; int f64; char p2[16]; int f84; int f88; int f92; int f96; int f100; };
/* Owning stack reference to a pooled string token (reference count at p[-1], chunk header at
 * p[-2]); releases the token on scope exit. */
class StringRef {
public:
    const char *p;
    StringRef(const char *s) : p(s) {}
    ~StringRef() { if (p) { int *h = (int *)p - 2; int r = ((int *)p)[-1] - 1; ((int *)p)[-1] = r; if (r == 0) StringChunk_ReleaseHeader(*h, h); } }
};
/* Owning stack reference to the sub-window created here; released on scope exit (reference count
 * in the low 23 bits of refs). */
template <class T> class igSmartPointer {
public:
    T *p;
    igSmartPointer(T *w) : p(w) {}
    ~igSmartPointer() { T *w = p; if (w != 0) { --w->refs; if ((w->refs & 0x7fffff) == 0) igObject_Destroy(w); } }
};
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
extern "C" int StringList_AppendRetained(int, StringRef *);
extern "C" void Gap__Bec__beNDMWStatusPowerSocket__vfunc_33(Sh *arg0) {
    int alloc;
    int a2;
    alloc = (int)igObject_GetAllocator();
    if (GPR_00554c14 != 0) {
        alloc = (int)alloc;
    } else {
        alloc = (int)Memory_GetAllocatorBySelector(DAT_00587110[0]);
    }
    igSmartPointer<Win> win((Win *)FUN_003b51b0((void *)alloc));
    beNDMWWindow_BindContext(win.p, arg0, arg0->f8, arg0->f20, 0);
    { Win *t = win.p; ObjectList_AppendRetained(arg0->f52, t); }
    INTERN_APPEND(win.p->f60, DAT_00519b50)
    INTERN_APPEND(win.p->f64, DAT_00519d98)
    beNDMWWindow_RunMessageScript(win.p, DAT_00519b90, 0x8A);
    a2 = 1;
    if (arg0->f100->n > 0) {
        Item *it = arg0->f100->data[arg0->f84];
        if (it != 0) a2 = it->f24;
    }
    win.p->f84 = a2;
    { Win *t = win.p;
    t->f88 = 0xC2A60000;
    t->f92 = 0x425C0000;
    t->f96 = 0; }
    win.p->f100 = arg0->f92;
}
