extern "C" {
struct RefCountedHeader { int word0; int references; };
void igObject_Destroy(RefCountedHeader *);
int List_Resize(...);
int Memory_GetAllocatorBySelector(...);
int ObjectList_AppendRetained(...);
int beNDMWWindow_BindContext(...);
int beNDMWWindow_RunMessageScript(...);
int igObject_GetAllocator(...);
void *FUN_002eb010(int);
void *StringPool_Construct(void *);
const char *StringPool_Intern(void *, const char *);
void StringChunk_ReleaseHeader(int, int *);
extern int DAT_004cf6f0[4];
extern int DAT_00519b50[4];
extern int DAT_00519b90[4];
extern int DAT_00519d98[4];
extern void *DAT_00586f20[4];
extern int DAT_00587110[4];
extern unsigned char GPR_00554c14;
}
struct ElementBufferList { char p[8]; int n; int cap; int *data; };
/* window object: close-text lists at +60/+64 are beNDMWWindow fields; the rest (list at +104, flag bytes at +108/+110/+111) belongs to an unreflected subclass */
struct WindowObject { int word0; int references; char p8[52]; int f60; int f64; char p9[32]; ElementBufferList *list; int f104; char f108; char pad109; char f110; char f111; };
/* Owning stack reference to a pooled string token (reference count at p[-1], chunk header at p[-2]):
 * releases the token on scope exit.  The out-of-line copy the exception table names is the retail
 * body StringRef_Destruct_00130720 (config/SLUS-20836/unit-objects.json, duplicate __dt__9StringRefFv). */
class StringRef {
public:
    const char *p;
    StringRef(const char *s) : p(s) {}
    ~StringRef() { if (p) { int *h = (int *)p - 2; int r = ((int *)p)[-1] - 1; ((int *)p)[-1] = r; if (r == 0) StringChunk_ReleaseHeader(*h, h); } }
};
/* Owning stack reference to the sub-window created here: released on scope exit (reference count in
 * the low 23 bits of references).  The out-of-line copy the exception table names is the retail body
 * 0x00414420 (config/SLUS-20836/unit-objects.json, duplicate __dt__9WindowRefFv). */
class WindowRef {
public:
    WindowObject *p;
    WindowRef(WindowObject *w) : p(w) {}
    ~WindowRef() { WindowObject *w = p; if (w != 0) { --w->references; if ((w->references & 0x7fffff) == 0) igObject_Destroy((RefCountedHeader *)w); } }
};
extern "C" int StringList_AppendRetained(int, const StringRef &);
#include "dw4/reflected.h"
extern "C" WindowObject *FUN_003baf10(...);
/* intern `text` (the pool singleton is created on first use) and append the token to `field` */
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
    StringList_AppendRetained(field, StringRef(tok)); }
extern "C" void Gap__Bec__beNDMWStatusSubSlot__vfunc_29(beNDMWStatusSubSlot *arg0);
void Gap__Bec__beNDMWStatusSubSlot__vfunc_29(beNDMWStatusSubSlot *arg0) {
    int alloc;
    int a;
    int s1;
    ElementBufferList *s0;
    alloc = igObject_GetAllocator(arg0);
    if (GPR_00554c14 != 0) {
        a = alloc;
    } else {
        a = Memory_GetAllocatorBySelector(DAT_00587110[0]);
    }
    WindowRef win(FUN_003baf10(a));
    beNDMWWindow_BindContext(win.p, arg0, arg0->_insight, arg0->_playerNo, 0);
    ObjectList_AppendRetained(arg0->_subWindow, win.p);
    INTERN_APPEND(((beNDMWWindow *)win.p)->_textCloseTypeList, DAT_00519b50)
    INTERN_APPEND(((beNDMWWindow *)win.p)->_textCloseNameList, DAT_00519d98)
    beNDMWWindow_RunMessageScript(win.p, DAT_00519b90, 139);
    s0 = win.p->list;
    s1 = s0->n;
    if (s1 < s0->cap) {
        s0->n = ((volatile ElementBufferList *)s0)->n + 1;
    } else {
        List_Resize(s0, s1 + 1, 4);
    }
    s0->data[s1] = DAT_004cf6f0[0];
    win.p->f108 = 1;
    win.p->f110 = 1;
    win.p->f111 = 0;
}
