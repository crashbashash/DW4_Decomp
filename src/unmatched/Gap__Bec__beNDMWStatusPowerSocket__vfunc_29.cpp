#include "dw4/reflected.h"
extern "C" {
/* igObject header: the reference count at +4 is not a reflected field */
void igObject_Destroy(igObject *);
int List_Resize(...);
int Memory_GetAllocatorBySelector(...);
int ObjectList_AppendRetained(...);
int beNDMWWindow_BindContext(...);
int beNDMWWindow_RunMessageScript(...);
int igObject_GetAllocator(...);
int FUN_002eb010(int);
int StringPool_Construct(int);
int *StringPool_Intern(int, const char *);
void StringChunk_ReleaseHeader(int, int *);
extern int DAT_004cf6d0[4];
extern int DAT_00519b50[4];
extern int DAT_00519b90[4];
extern int DAT_00519d98[4];
extern int DAT_00586f20[4];
extern int DAT_00587110[4];
extern unsigned char GPR_00554c14;
}
/* Owning stack reference to a pooled string token (reference count at p[-1], chunk header at
 * p[-2]); releases the token on scope exit. */
static inline int count(const igIntList *list) { return list->_count; }
class StringRef {
public:
    int *p;
    StringRef(int *s) : p(s) {}
    ~StringRef() { if (p) { int *h = (int *)p - 2; int r = ((int *)p)[-1] - 1; ((int *)p)[-1] = r; if (r == 0) StringChunk_ReleaseHeader(*h, h); } }
};
/* The list takes its own reference to the token it is handed. */
extern "C" int StringList_AppendRetained(int, const StringRef &);
/* Owning stack reference to the new item-page window; released on scope exit (reference count in
 * the low 23 bits of _refCount). */
class WindowRef {
public:
    beNDMWStatusCtrlD0 *p;
    WindowRef(beNDMWStatusCtrlD0 *w) : p(w) {}
    ~WindowRef() { beNDMWStatusCtrlD0 *w = p; if (w != 0) { --w->_refCount; if ((w->_refCount & 0x7fffff) == 0) igObject_Destroy((igObject *)w); } }
};
struct Str { static inline int *intern(const char *s) {
    int *token;
    if (s == 0) {
        token = 0;
    } else {
        if (DAT_00586f20[0] == 0) {
            int pool = FUN_002eb010(0x10);
            if (pool != 0) pool = StringPool_Construct(pool);
            DAT_00586f20[0] = pool;
        }
        token = StringPool_Intern(DAT_00586f20[0], s);
    }
    return token;
} };
extern "C" beNDMWStatusCtrlD0 *FUN_003baf10(...);
extern "C" void Gap__Bec__beNDMWStatusPowerSocket__vfunc_29(beNDMWStatusPowerSocket *arg0);
void Gap__Bec__beNDMWStatusPowerSocket__vfunc_29(beNDMWStatusPowerSocket *arg0) {
    int alloc;
    int a;
    int s1;
    igIntList *s0;
    alloc = igObject_GetAllocator(arg0);
    if (GPR_00554c14 != 0) {
        a = alloc;
    } else {
        a = Memory_GetAllocatorBySelector(DAT_00587110[0]);
    }
    WindowRef win(FUN_003baf10(a));
    beNDMWWindow_BindContext(win.p, arg0, arg0->_insight, arg0->_playerNo, 0);
    ObjectList_AppendRetained(arg0->_subWindow, win.p);
    { int *tok = Str::intern((const char *)&DAT_00519b50[0]); StringList_AppendRetained(win.p->_textCloseTypeList, StringRef(tok)); }
    { int *tok = Str::intern((const char *)&DAT_00519d98[0]); StringList_AppendRetained(win.p->_textCloseNameList, StringRef(tok)); }
    beNDMWWindow_RunMessageScript(win.p, DAT_00519b90, 0x8B);
    s0 = (igIntList *)win.p->_kindList;
    s1 = s0->_count;
    if (s1 < s0->_capacity) {
        s0->_count = count(s0) + 1;
    } else {
        List_Resize(s0, s1 + 1, 4);
    }
    ((int *)s0->_data)[s1] = DAT_004cf6d0[0];
    win.p->_isEquipDisable = 1;
    win.p->_isUnknownDisable = 1;
    win.p->_isAutoClose = 0;
}
