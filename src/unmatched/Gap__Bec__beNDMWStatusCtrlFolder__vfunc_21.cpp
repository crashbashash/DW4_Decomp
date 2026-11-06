/* Each sub-window holder is a scope object whose destructor releases the reference (the protected
 * range splits around the inlined release call, which a hand-spelled release cannot reproduce);
 * the constructor takes the allocation result so the range starts after that call. */
#include "dw4/reflected.h"
extern "C" {
void *FUN_003b3530(void *);
void *FUN_003b5530(void *);
void *FUN_003baf10(void *);
void *FUN_003b8f50(void *);
void *FUN_003b9db0(void *);
void *FUN_003b9a50(void *);
void *FUN_003b97d0(void *);
int FUN_003f5410(void *, void *, int, void *, void *);
int igObject_IsKindOf(void *, int);
int FUN_002eb010(int);
int StringPool_Construct(int);
void *StringPool_Intern(int, int);
int StringChunk_ReleaseHeader(int, int *);
void *Memory_GetAllocatorBySelector(int);
void *igObject_GetAllocator(void *);
int ObjectList_AppendRetained(int, void *);
int beNDMWWindow_BindContext(void *, void *, int, int, int);
int beNDMWWindow_ClearQueuedText(void *);
int beNDMWWindow_PlayQueuedModelClose(void *);
int beNDMWWindow_PollCloseComplete(void *);
int beNDMWWindow_RequestChildrenClose(void *);
int beNDMWWindow_RunMessageScript(void *, void *, int);
int beMessenger_AppendString(int, void *);
int beMessenger_DispatchSelected(int, void *);
int beMessenger_SelectGroup(int, void *);
void igObject_Destroy(void *);
extern int DAT_004cf670[4];
extern int DAT_00519b00[4];
extern int DAT_00519b08[4];
extern int DAT_00519b50[4];
extern int DAT_00519b60[4];
extern int DAT_00519b68[4];
extern int DAT_00519b90[4];
extern int DAT_00519c28[4];
extern int DAT_00519d98[4];
extern int DAT_00586f20[4];
extern int DAT_00587110[4];
extern int DAT_0058af98[4];
extern unsigned char GPR_00554c14;
void Gap__Bec__beNDMWStatusCtrlFolder__vfunc_21(beNDMWStatusCtrlFolder *arg0);
}
/* Scope holder for a freshly built sub-window: its destructor releases the reference. One class
 * per kind (0..4), so each gets its own out-of-line destructor. */
template <int kind> struct RP {
    igObject *p;
    RP(igObject *x) { p = x; }
    ~RP() { igObject *o = p; if (o != 0) { o->_refCount = o->_refCount - 1; if ((o->_refCount & 0x7fffff) == 0) igObject_Destroy(o); } }
    operator igObject *() { return p; }
};
#define REL(o) { igObject *rr = (o); if (rr != 0) { rr->_refCount = (int)rr->_refCount - 1; if (((unsigned long long)((long long)(int)rr->_refCount << 0x29) >> 0x29) == 0) { igObject_Destroy(rr); } } }
#define ALLOC(al) al = igObject_GetAllocator(arg0); al = GPR_00554c14 ? al : Memory_GetAllocatorBySelector(DAT_00587110[0]);
/* matching construct: inline type-checked cast; its early return gives the retail empty-arm branch. */
struct FolderHelpers {
static beNDMWStatusCtrlD0 *CastTo(beNDMWStatusCtrlD0 *p) { if (p != 0) { if (igObject_IsKindOf(p, DAT_0058af98[0]) != 0) { return p; } } return 0; }
static beNDMWStatusCtrlD0 *FindSub(beNDMWStatusCtrlFolder *w) { beNDMWStatusCtrlD0 *f = 0; int fi = 0; if (0 < (*(igDataList *volatile *)&w->_subWindow)->_count) { L:  f = CastTo(((beNDMWStatusCtrlD0 **)(*(igDataList *volatile *)&w->_subWindow)->_data)[fi]); if (f == 0) { fi++; if (fi < (*(igDataList *volatile *)&w->_subWindow)->_count) goto L; } } return f; }
};
#define MSG() { beMessenger_SelectGroup(arg0->_messenger, DAT_00519c28); beMessenger_AppendString(arg0->_messenger, DAT_00519b50); beMessenger_AppendString(arg0->_messenger, DAT_00519d98); beMessenger_AppendString(arg0->_messenger, DAT_00519b00); beMessenger_DispatchSelected(arg0->_messenger, DAT_00519b08); }
#define CLEAR(lst) { igDataList *l = (igDataList *)(lst); int n = l->_count; int i; int *slot; int *nw; int o; int *old; if (0 < n) { i = 0; o = 0; do { slot = (int *)(l->_data + o); if (DAT_00586f20[0] == 0) { int v = FUN_002eb010(0x10); if (v != 0) { v = StringPool_Construct(v); } DAT_00586f20[0] = v; } nw = (int *)StringPool_Intern(DAT_00586f20[0], 0); old = (int *)*slot; if (old != 0) { int *hd = old - 2; int c = old[-1] - 1; old[-1] = c; if (c == 0) { StringChunk_ReleaseHeader(*hd, hd); } } i++; *slot = (int)nw; o += 4; } while (i < n); } l->_count = 0; }
void Gap__Bec__beNDMWStatusCtrlFolder__vfunc_21(beNDMWStatusCtrlFolder *arg0) {
    void *alloc;
    beNDMWStatusCtrlD0 *found;
    switch (arg0->_st0) {
    case 0:
        ALLOC(alloc)
        {
        RP<0> sp9C((igObject *)FUN_003b3530(alloc));
        beNDMWWindow_BindContext(sp9C, arg0, arg0->_insight, arg0->_playerNo, 0x3C);
        ObjectList_AppendRetained(arg0->_subWindow, sp9C);
        }
        arg0->_folderMenu = 0;
        arg0->_st0 = ((volatile beNDMWStatusCtrlFolder *)arg0)->_st0 + 1;
        arg0->_st3 = 0;
        arg0->_st2 = 0;
        arg0->_st1 = 0;
        arg0->_st1 = 0;
        arg0->_st3 = 0;
        arg0->_st2 = 0;
    case 1:
        switch (arg0->_st1) {
        case 0:
            switch (arg0->_st2) {
            case 0:
                ALLOC(alloc)
                {
                RP<1> sp98((igObject *)FUN_003b5530(alloc));
                beNDMWWindow_BindContext(sp98, arg0, arg0->_insight, arg0->_playerNo, 0x3D);
                ObjectList_AppendRetained(arg0->_subWindow, sp98);
                ((beNDMWStatusSelect01 *)sp98.p)->_startPoint = arg0->_folderMenu;
                FUN_003f5410(sp98, DAT_00519b50, DAT_004cf670[0], DAT_00519b60, DAT_00519b68);
                }
                arg0->_nowProcKazu = ((igDataList *)arg0->_subWindow)->_count;
                arg0->_st2 = arg0->_st2 + 1;
                arg0->_st3 = 0;
            case 1:
                if (arg0->_retCode != -1) {
                    beNDMWWindow_RunMessageScript(arg0, DAT_00519b90, arg0->_retCode + 0x51);
                }
                arg0->_st2 = arg0->_st2 + 1;
                arg0->_st3 = 0;
                arg0->_st3 = arg0->_retCode;
            case 2:
                if (((igDataList *)arg0->_subWindow)->_count == arg0->_nowProcKazu) {
                    if (arg0->_retCode == -1) { return; }
                    if (arg0->_st3 == arg0->_retCode) { return; }
                    arg0->_st2 = 1;
                    arg0->_st3 = 0;
                    return;
                }
                if (arg0->_retCode != -1) {
                    arg0->_folderMenu = arg0->_retCode;
                }
                switch (arg0->_retCode) {
                case 0:
                    arg0->_st1 = 1;
                    arg0->_st3 = 0;
                    arg0->_st2 = 0;
                    return;
                case 1:
                    arg0->_st1 = 2;
                    arg0->_st3 = 0;
                    arg0->_st2 = 0;
                    return;
                case 2:
                    arg0->_st1 = 3;
                    arg0->_st3 = 0;
                    arg0->_st2 = 0;
                    return;
                case 3:
                    arg0->_st1 = 4;
                    arg0->_st3 = 0;
                    arg0->_st2 = 0;
                    return;
                default:
                    arg0->_st0 = arg0->_st0 + 1;
                    arg0->_st3 = 0;
                    arg0->_st2 = 0;
                    arg0->_st1 = 0;
                    return;
                }
            }
            break;
        case 1:
            switch (arg0->_st2) {
            case 0:
                ALLOC(alloc)
                {
                RP<2> sp94((igObject *)FUN_003baf10(alloc));
                beNDMWWindow_BindContext(sp94, arg0, arg0->_insight, arg0->_playerNo, 0);
                ObjectList_AppendRetained(arg0->_subWindow, sp94);
                ((beNDMWStatusCtrlD0 *)sp94.p)->_isAutoClose = 0;
                }
                arg0->_nowProcKazu = ((igDataList *)arg0->_subWindow)->_count;
                arg0->_st2 = arg0->_st2 + 1;
                arg0->_st3 = 0;
            case 1:
                if (arg0->_st3 == 0) {
                    beNDMWWindow_RunMessageScript(arg0, DAT_00519b90, 0x2B);
                    arg0->_st3 = 1;
                }
                found = FolderHelpers::FindSub(arg0);
                if (found != 0) {
                    if (arg0->_retCode == -1) {
                        MSG()
                        ((beNDMWWindow *)found)->_st0 = 2;
                        ((beNDMWWindow *)found)->_st3 = 0;
                        ((beNDMWWindow *)found)->_st2 = 0;
                        ((beNDMWWindow *)found)->_st1 = 0;
                        arg0->_st2 = 3;
                        arg0->_st3 = 0;
                        return;
                    }
                    if (((beNDMWWindow *)found)->_st0 == 1 && ((beNDMWWindow *)found)->_st1 == 2) {
                        MSG()
                        ALLOC(alloc)
                        {
                        RP<3> sp90((igObject *)FUN_003b8f50(alloc));
                        beNDMWWindow_BindContext(sp90, arg0, arg0->_insight, arg0->_playerNo, arg0->_retCode);
                        ObjectList_AppendRetained(arg0->_subWindow, sp90);
                        ((beNDMWStatusSubMenu *)sp90.p)->_selectDevice = arg0->_retCode;
                        {
                            beNDMWStatusSubMenu *o = (beNDMWStatusSubMenu *)sp90.p;
                            igObject *old;
                            if (found != 0) { found->_refCount = (int)found->_refCount + 1; }
                            old = (igObject *)o->_deviceFolderList;
                            REL(old)
                            o->_deviceFolderList = (int)found;
                        }
                        }
                        arg0->_nowProcKazu = ((igDataList *)arg0->_subWindow)->_count;
                        arg0->_st2 = arg0->_st2 + 1;
                        arg0->_st3 = 0;
                        return;
                    }
                }
                break;
            case 2:
                if (((igDataList *)arg0->_subWindow)->_count != arg0->_nowProcKazu) {
                    arg0->_nowProcKazu = ((igDataList *)arg0->_subWindow)->_count;
                    arg0->_retCode = 0;
                    beNDMWWindow_PlayQueuedModelClose(arg0);
                    CLEAR(arg0->_modelCloseInfoNameList)
                    ((igDataList *)arg0->_modelCloseRamNoList)->_count = 0;
                    CLEAR(arg0->_modelCloseSeqNameList)
                    beNDMWWindow_ClearQueuedText(arg0);
                    found = FolderHelpers::FindSub(arg0);
                    if (found != 0) {
                        ((beNDMWWindow *)found)->_st2 = 1;
                        ((beNDMWWindow *)found)->_st3 = 0;
                        arg0->_st2 = 1;
                        arg0->_st3 = 0;
                        return;
                    }
                    arg0->_st2 = 4;
                    arg0->_st3 = 0;
                    return;
                }
                break;
            case 3:
                found = FolderHelpers::FindSub(arg0);
                if (found == 0) {
                    arg0->_retCode = arg0->_folderMenu;
                    arg0->_st1 = 0;
                    arg0->_st3 = 0;
                    arg0->_st2 = 0;
                    return;
                }
                break;
            case 4:
                if (((igDataList *)arg0->_subWindow)->_count != arg0->_nowProcKazu) {
                    arg0->_st2 = 0;
                    arg0->_st3 = 0;
                    return;
                }
                break;
            }
            break;
        case 2:
        case 3:
        case 4:
            switch (arg0->_st2) {
            case 0:
                {
                RP<4> sp8C(0);
                switch (arg0->_st1) {
                case 2:
                    ALLOC(alloc)
                    { igObject *t = sp8C.p; REL(t) }
                    sp8C.p = (igObject *)FUN_003b9db0(alloc);
                    break;
                case 3:
                    ALLOC(alloc)
                    { igObject *t = sp8C.p; REL(t) }
                    sp8C.p = (igObject *)FUN_003b9a50(alloc);
                    break;
                case 4:
                    ALLOC(alloc)
                    { igObject *t = sp8C.p; REL(t) }
                    sp8C.p = (igObject *)FUN_003b97d0(alloc);
                    break;
                }
                beNDMWWindow_BindContext(sp8C, arg0, arg0->_insight, arg0->_playerNo, 0);
                ObjectList_AppendRetained(arg0->_subWindow, sp8C);
                }
                arg0->_nowProcKazu = ((igDataList *)arg0->_subWindow)->_count;
                arg0->_st2 = arg0->_st2 + 1;
                arg0->_st3 = 0;
            case 1:
                if (((igDataList *)arg0->_subWindow)->_count != arg0->_nowProcKazu) {
                    arg0->_retCode = arg0->_folderMenu;
                    arg0->_st1 = 0;
                    arg0->_st3 = 0;
                    arg0->_st2 = 0;
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
