/* Opens the item page (beNDMWStatusCtrlD0) under the status main slot: binds it, registers its
 * close text type/name, runs its message script, adds the one kind to its kind list and sets the
 * equip/unknown-disable flags with auto-close off. The new window is owned by a stack reference
 * until the end of the function; the two interned names are temporaries. */
#include "dw4/igSmartPointer.h"
static inline int countOf(const igDataList *l) { return l->_count; }
extern "C" {
int FUN_002eb010(int);
beNDMWStatusCtrlD0 *FUN_003baf10(int);
int List_Resize(void *, int, int);
int Memory_GetAllocatorBySelector(int);
int ObjectList_AppendRetained(int, void *);
int StringChunk_ReleaseHeader(int, int *);
int StringPool_Construct(int);
int *StringPool_Intern(int, int *);
int beNDMWWindow_BindContext(void *, void *, int, int, int);
int beNDMWWindow_RunMessageScript(void *, int *, int);
int igObject_GetAllocator(void *);
extern int DAT_004cf6e0[4];
extern int DAT_00519b50[4];
extern int DAT_00519b90[4];
extern int DAT_00519d98[4];
extern int DAT_00586f20[4];
extern int DAT_00587110[4];
extern unsigned char GPR_00554c14;
}
/* Owning stack reference to the item page window created here, released on scope exit (reference
 * count in the low 23 bits of _refCount). */

/* Owning stack reference to a pooled string token (reference count at p[-1], chunk header at
 * p[-2]); releases the token on scope exit. */
class StringRef {
public:
    int *p;
    StringRef(int *s) : p(s) {}
    ~StringRef() { if (p) { int *h = (int *)p - 2; int r = ((int *)p)[-1] - 1; ((int *)p)[-1] = r; if (r == 0) StringChunk_ReleaseHeader(*h, h); } }
};
extern "C" int StringList_AppendRetained(int, const StringRef &);
struct Str { static inline int *intern(int *s) {
    int *ref;
    if (s == 0) {
        ref = 0;
    } else {
        if (DAT_00586f20[0] == 0) {
            int pool = FUN_002eb010(16);
            if (pool != 0) pool = StringPool_Construct(pool);
            DAT_00586f20[0] = pool;
        }
        ref = StringPool_Intern(DAT_00586f20[0], s);
    }
    return ref;
} };
extern "C" void Gap__Bec__beNDMWStatusMainSlot__vfunc_29(beNDMWStatusMainSlot *arg0);
void Gap__Bec__beNDMWStatusMainSlot__vfunc_29(beNDMWStatusMainSlot *arg0) {
    int al;
    int c;
    igDataList *l;

    al = igObject_GetAllocator(arg0);
    al = (GPR_00554c14 != 0) ? al : Memory_GetAllocatorBySelector(DAT_00587110[0]);
    igSmartPointer<beNDMWStatusCtrlD0> win(FUN_003baf10(al));
    beNDMWWindow_BindContext(win.p, arg0, arg0->_insight, arg0->_playerNo, 0);
    ObjectList_AppendRetained(arg0->_subWindow, win.p);
    { int *tok = Str::intern(&DAT_00519b50[0]); StringList_AppendRetained(win.p->_textCloseTypeList, StringRef(tok)); }
    { int *tok = Str::intern(&DAT_00519d98[0]); StringList_AppendRetained(win.p->_textCloseNameList, StringRef(tok)); }
    beNDMWWindow_RunMessageScript(win.p, &DAT_00519b90[0], 139);
    l = (igDataList *)win.p->_kindList;
    c = l->_count;
    if (c < l->_capacity) {
        l->_count = countOf(l) + 1;
    } else {
        List_Resize(l, c + 1, 4);
    }
    ((int *)l->_data)[c] = DAT_004cf6e0[0];
    win.p->_isEquipDisable = 1;
    win.p->_isUnknownDisable = 1;
    win.p->_isAutoClose = 0;
}
