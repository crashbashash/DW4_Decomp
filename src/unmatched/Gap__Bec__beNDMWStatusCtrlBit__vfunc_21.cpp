#include "dw4/reflected.h"
struct ChildWindow;
extern "C" {
int FUN_002eb010(int);
int FUN_003b4f50(int);
int FUN_003b9560(int);
int List_Resize(igIntList *, int, int);
int Memory_GetAllocatorBySelector(int);
int ObjectList_AppendRetained(int, void *);
int StringChunk_ReleaseHeader(int, int *);
int StringPool_Construct(int);
int StringPool_Intern(int, int *);
int beMessenger_AppendInt(int, int);
int beMessenger_DispatchSelected(int, int *);
int beMessenger_GetObject(int, int);
int beMessenger_SelectGroup(int, int *);
int beMessenger_SendGroup(int, int *, int *);
int beNDMWWindow_BindContext(struct ChildWindow *, beNDMWStatusCtrlBit *, int, int, int);
int beNDMWWindow_ClearQueuedText(beNDMWStatusCtrlBit *);
int beNDMWWindow_PlayQueuedModelClose(beNDMWStatusCtrlBit *);
int beNDMWWindow_PollCloseComplete(beNDMWStatusCtrlBit *);
int beNDMWWindow_RequestChildrenClose(beNDMWStatusCtrlBit *);
int beNDMWWindow_RunMessageScript(beNDMWStatusCtrlBit *, int *, int);
void igObject_Destroy(struct ChildWindow *);
int igObject_GetAllocator(beNDMWStatusCtrlBit *);
int igProperty_GetRecord(int, int *);
void *igProperty_GetRecordByte(int, int *);
extern int *DAT_004cf670[4];
extern int DAT_00519b50[4];
extern int DAT_00519b90[4];
extern int DAT_00519ba0[4];
extern int DAT_00519ba8[4];
extern int DAT_0051a0f8[4];
extern int DAT_0051a1a0[4];
extern int DAT_0051a270[4];
extern int DAT_00586f20[4];
extern int DAT_00587110[4];
extern unsigned char GPR_00554c14;
}
typedef struct PropertyRecord { char p[12]; unsigned char f12; } PropertyRecord;
typedef struct ChildWindow { int w0; int refs; char p8[52]; int f60; int f64; char p68[24]; int f92; } ChildWindow;
/* Owning stack reference to a pooled string token (reference count at p[-1], chunk header at
 * p[-2]); releases the token on scope exit. */
static inline int count(const igIntList *list) { return list->_count; }
class StringRef {
public:
    int *p;
    StringRef(int *s) : p(s) {}
    ~StringRef() { if (p) { int *h = (int *)p - 2; int r = ((int *)p)[-1] - 1; ((int *)p)[-1] = r; if (r == 0) StringChunk_ReleaseHeader(*h, h); } }
};
extern "C" int StringList_AppendRetained(int, const StringRef &);
/* Owning stack reference to the first sub-window while it is set up, released on scope exit
 * (reference count in the low 23 bits of refs). */
class WindowRef {
public:
    ChildWindow *p;
    WindowRef(ChildWindow *w) : p(w) {}
    ~WindowRef() { ChildWindow *w = p; if (w != 0) { --w->refs; if ((w->refs & 0x7fffff) == 0) igObject_Destroy(w); } }
};
/* Owning stack reference to the player-select sub-window (receives the player-number list) while
 * it is set up. */
class SelectWindowRef {
public:
    ChildWindow *p;
    SelectWindowRef(ChildWindow *w) : p(w) {}
    ~SelectWindowRef() { ChildWindow *w = p; if (w != 0) { --w->refs; if ((w->refs & 0x7fffff) == 0) igObject_Destroy(w); } }
};
struct Str { static inline int *intern(int *s) {
    int *tok;
    if (s == 0) {
        tok = 0;
    } else {
        if (DAT_00586f20[0] == 0) {
            int pool = FUN_002eb010(0x10);
            if (pool != 0) pool = StringPool_Construct(pool);
            DAT_00586f20[0] = pool;
        }
        tok = (int *)StringPool_Intern(DAT_00586f20[0], s);
    }
    return tok;
} };
/* intern text and append it to the string list, which takes its own share; the interning share is a
 * temporary released at the end of the statement */
#define INTERN_APPEND(field, text) { int *tok = Str::intern((int *)(text)); StringList_AppendRetained(field, StringRef(tok)); }
extern "C" void Gap__Bec__beNDMWStatusCtrlBit__vfunc_21(beNDMWStatusCtrlBit *arg0);
void Gap__Bec__beNDMWStatusCtrlBit__vfunc_21(beNDMWStatusCtrlBit *arg0) {
    int s2;
    int al;
    int i;
    int s1;
    igIntList *l4;
    switch (arg0->_st0) {
    case 0:
        beMessenger_SendGroup(arg0->_messenger, DAT_00519ba0, DAT_0051a0f8);
        igProperty_GetRecord(beMessenger_GetObject(arg0->_messenger, 0), DAT_0051a270);
        i = 0;
        do {
            beMessenger_SelectGroup(arg0->_messenger, DAT_00519ba0);
            beMessenger_AppendInt(arg0->_messenger, i);
            beMessenger_DispatchSelected(arg0->_messenger, DAT_00519ba8);
            if (((PropertyRecord *)igProperty_GetRecordByte(beMessenger_GetObject(arg0->_messenger, 0), DAT_0051a1a0))->f12 != 0 && i != arg0->_playerNo) {
                l4 = (igIntList *)arg0->_playerNoList;
                s1 = l4->_count;
                if (s1 < l4->_capacity) {
                    l4->_count = count(l4) + 1;
                } else {
                    List_Resize(l4, s1 + 1, 4);
                }
                ((int *)l4->_data)[s1] = i;
            }
            i += 1;
        } while (i < 4);
        arg0->_st0 = arg0->_st0 + 1;
        arg0->_st3 = 0;
        arg0->_st2 = 0;
        arg0->_st1 = 0;
        if (((igIntList *)arg0->_playerNoList)->_count == 0) {
            arg0->_st1 = 0;
            arg0->_st3 = 0;
            arg0->_st2 = 0;
        } else {
            arg0->_st1 = 1;
            arg0->_st3 = 0;
            arg0->_st2 = 0;
        }
    case 1:
        switch (arg0->_st1) {
        case 0:
            switch (arg0->_st2) {
            case 0:
                al = igObject_GetAllocator(arg0);
                al = (GPR_00554c14 != 0) ? al : Memory_GetAllocatorBySelector(DAT_00587110[0]);
                {
                    WindowRef win((ChildWindow *)FUN_003b4f50(al));
                    beNDMWWindow_BindContext(win.p, arg0, arg0->_insight, arg0->_playerNo, 0);
                    ObjectList_AppendRetained((unsigned)arg0->_subWindow, win.p);
                    INTERN_APPEND(((beNDMWWindow *)win.p)->_textCloseTypeList, &DAT_00519b50[0])
                    s2 = (int)DAT_004cf670[0];
                    INTERN_APPEND(((beNDMWWindow *)win.p)->_textCloseNameList, s2)
                    beNDMWWindow_RunMessageScript(arg0, DAT_00519b90, 0x58);
                }
                arg0->_nowProcKazu = ((beNDMWWindowList *)(arg0->_subWindow))->_count;
                arg0->_st2 = arg0->_st2 + 1;
                arg0->_st3 = 0;
                return;
            case 1:
                if (((beNDMWWindowList *)(arg0->_subWindow))->_count != arg0->_nowProcKazu) {
                    arg0->_st0 = arg0->_st0 + 1;
                    arg0->_st3 = 0;
                    arg0->_st2 = 0;
                    arg0->_st1 = 0;
                }
                break;
            }
            break;
        case 1:
            switch (arg0->_st2) {
            case 0:
                al = igObject_GetAllocator(arg0);
                al = (GPR_00554c14 != 0) ? al : Memory_GetAllocatorBySelector(DAT_00587110[0]);
                {
                    SelectWindowRef win((ChildWindow *)FUN_003b9560(al));
                    beNDMWWindow_BindContext(win.p, arg0, arg0->_insight, arg0->_playerNo, 0);
                    ObjectList_AppendRetained((unsigned)arg0->_subWindow, win.p);
                    {
                        igIntList *lst = (igIntList *)arg0->_playerNoList;
                        ChildWindow *w = win.p;
                        ChildWindow *old;
                        if (lst != 0) lst->_refCount = lst->_refCount + 1;
                        old = (ChildWindow *)w->f92;
                        if (old != 0) {
                            old->refs = old->refs - 1;
                            if (((unsigned long long)((long long)old->refs << 0x29) >> 0x29) == 0) igObject_Destroy(old);
                        }
                        w->f92 = (int)lst;
                    }
                }
                arg0->_nowProcKazu = ((beNDMWWindowList *)(arg0->_subWindow))->_count;
                arg0->_st2 = arg0->_st2 + 1;
                arg0->_st3 = 0;
            case 1:
                if (((beNDMWWindowList *)(arg0->_subWindow))->_count != arg0->_nowProcKazu) {
                    arg0->_st0 = arg0->_st0 + 1;
                    arg0->_st3 = 0;
                    arg0->_st2 = 0;
                    arg0->_st1 = 0;
                    return;
                }
                break;
            }
            break;
        }
        break;
    case 2:
        beNDMWWindow_PlayQueuedModelClose(arg0);
        beNDMWWindow_ClearQueuedText(arg0);
        beNDMWWindow_RequestChildrenClose(arg0);
        arg0->_st0 = arg0->_st0 + 1;
        arg0->_st3 = 0;
        arg0->_st2 = 0;
        arg0->_st1 = 0;
        return;
    case 3:
        if (beNDMWWindow_PollCloseComplete(arg0) != 0) {
            arg0->_isRun = 0;
        }
        break;
    }
}
