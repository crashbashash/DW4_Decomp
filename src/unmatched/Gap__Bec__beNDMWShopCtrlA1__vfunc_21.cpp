#include "dw4/reflected.h"
extern "C" {
igObject *FUN_003b4250(void *);
igObject *FUN_003b4950(void *);
igObject *FUN_003b4b10(void *);
igObject *FUN_003b7a40(void *);
int FUN_0042df70(void *);
int FUN_0042e330(void *);
int FUN_0042e9e0(void *);
void *Memory_GetAllocatorBySelector(int);
int ObjectList_AppendRetained(int, void *);
int beMessenger_AppendInt(int, int);
int beMessenger_AppendString(int, void *);
int beMessenger_AppendVec3(int, void *);
int beMessenger_DispatchSelected(int, void *);
int beMessenger_GetBool(int, int);
int beMessenger_GetObject(int, int);
int beMessenger_SelectGroup(int, void *);
int beMessenger_SelectReceivers(int, void *, void *, int);
int beMessenger_SendNamed(int, void *, void *, int, void *);
int beNDMWWindow_BindContext(void *, void *, int, int, int);
int beNDMWWindow_ClearQueuedText(void *);
int beNDMWWindow_PlayQueuedModelClose(void *);
int beNDMWWindow_PollCloseComplete(void *);
int beNDMWWindow_RequestChildrenClose(void *);
int beNDMWWindow_RunMessageScript(void *, void *, int);
void igObject_Destroy(void *);
void *igObject_GetAllocator(void *);
struct Item { int p[3]; int f12; int p16; int f20; };
/* matching construct: the const list pointer keeps the retail per-iteration reload of the list size (no loop-invariant hoist). */
struct Rec { int p[3]; igObjectList *f12; };
Rec *igProperty_GetRecordFolder(int, void *);
extern void *DAT_004cf8a8[4];
extern float DAT_004e1058[4];
extern float DAT_004e105c[4];
extern float DAT_004e1060[4];
extern int DAT_0051b1c8[4];
extern int DAT_0051b1d0[4];
extern int DAT_0051b308[4];
extern int DAT_0051b318[4];
extern int DAT_0051b338[4];
extern int DAT_0051b398[4];
extern int DAT_0051b3c0[4];
extern int DAT_0051b3e8[4];
extern int DAT_0051b550[4];
extern int DAT_0051b558[4];
extern int DAT_0051b620[4];
extern int DAT_0051b6b0[4];
extern int DAT_0051b6b8[4];
extern int DAT_0051b6c0[4];
extern int DAT_0051b7e0[4];
extern int DAT_0051b868[4];
extern int DAT_0051b878[4];
extern int DAT_0051b888[4];
extern int DAT_0051b890[4];
extern int DAT_0051b8a0[4];
extern int DAT_0051b8a8[4];
extern int DAT_0051b8b8[4];
extern int DAT_0051b8c8[4];
extern int DAT_0051b8d8[4];
extern int DAT_0051b8e8[4];
extern int DAT_0051b8f0[4];
extern int DAT_0051b8f8[4];
extern int DAT_00587110[4];
extern unsigned char GPR_00554c14;
void Gap__Bec__beNDMWShopCtrlA1__vfunc_21(beNDMWShopCtrlA1 *arg0);
}
/* Owning stack reference to a sub-window of one of the four window classes opened here (kind 0..3
 * in textual order); constructed from the factory result and released on scope exit (reference
 * count in the low 23 bits of _refCount). */
template <int kind> class WindowRef {
public:
    igObject *p;
    WindowRef(igObject *w) : p(w) {}
    ~WindowRef() { igObject *w = p; if (w != 0) { --w->_refCount; if ((w->_refCount & 0x7fffff) == 0) igObject_Destroy(w); } }
};
void Gap__Bec__beNDMWShopCtrlA1__vfunc_21(beNDMWShopCtrlA1 *arg0) {
    void *alloc;
    float sp40[3];
    float sp30[3];
    const igObjectList *a;
    int s0;
    int i;
    Item *it;
    switch (arg0->_st0) {
    case 0:
        /* matching construct: const read reloads the state word after the dispatch. */
        arg0->_st0 = ((const beNDMWShopCtrlA1 *)arg0)->_st0 + 1;
        arg0->_st3 = 0;
        arg0->_st2 = 0;
        arg0->_st1 = 0;
        arg0->_st1 = 4;
        arg0->_st3 = 0;
        arg0->_st2 = 0;
        return;
    case 1:
        switch (arg0->_st1) {
        case 4:
            switch (arg0->_st2) {
            case 0:
                beMessenger_SelectReceivers(arg0->_messenger, DAT_0051b308, DAT_0051b878, arg0->_playerNo);
                beMessenger_AppendString(arg0->_messenger, DAT_0051b868);
                beMessenger_DispatchSelected(arg0->_messenger, DAT_0051b338);
                if ((beMessenger_GetBool(arg0->_messenger, 0) & 0xFF) == 1) {
                    return;
                }
                alloc = igObject_GetAllocator(arg0);
                alloc = GPR_00554c14 ? alloc : Memory_GetAllocatorBySelector(DAT_00587110[0]);
                {
                WindowRef<0> win(FUN_003b4b10(alloc));
                beNDMWWindow_BindContext(win.p, arg0, arg0->_insight, arg0->_playerNo, 0x7D5);
                ObjectList_AppendRetained(arg0->_subWindow, win.p);
                }
                arg0->_nowProcKazu = ((igDataList *)arg0->_subWindow)->_count;
                arg0->_st2 = arg0->_st2 + 1;
                arg0->_st3 = 0;
            case 1:
                if (((igDataList *)arg0->_subWindow)->_count != arg0->_nowProcKazu) {
                    switch (arg0->_retCode) {
                    case 0:
                        arg0->_st1 = 5;
                        arg0->_st3 = 0;
                        arg0->_st2 = 0;
                        return;
                    case 1:
                        arg0->_st1 = 6;
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
            }
            break;
        case 5:
            switch (arg0->_st2) {
            case 0:
                beMessenger_SelectGroup(arg0->_messenger, DAT_0051b398);
                beMessenger_AppendInt(arg0->_messenger, arg0->_playerNo);
                beMessenger_DispatchSelected(arg0->_messenger, DAT_0051b3e8);
                a = igProperty_GetRecordFolder(beMessenger_GetObject(arg0->_messenger, 0), DAT_0051b6c0)->f12;
                s0 = 0;
                i = 0;
                while (i < a->_count) {
                    it = ((Item **)((igObjectList *)a)->_data)[i];
                    if (it != 0 && it->f12 == 10) {
                        s0 = it->f20;
                        break;
                    }
                    i++;
                }
                if (s0 > 0) {
                    alloc = igObject_GetAllocator(arg0);
                    alloc = GPR_00554c14 ? alloc : Memory_GetAllocatorBySelector(DAT_00587110[0]);
                    WindowRef<1> win(FUN_003b7a40(alloc));
                    beNDMWWindow_BindContext(win.p, arg0, arg0->_insight, arg0->_playerNo, s0);
                    ObjectList_AppendRetained(arg0->_subWindow, win.p);
                } else {
                    alloc = igObject_GetAllocator(arg0);
                    alloc = GPR_00554c14 ? alloc : Memory_GetAllocatorBySelector(DAT_00587110[0]);
                    WindowRef<2> win(FUN_003b4950(alloc));
                    beNDMWWindow_BindContext(win.p, arg0, arg0->_insight, arg0->_playerNo, 0x7D7);
                    ObjectList_AppendRetained(arg0->_subWindow, win.p);
                    beMessenger_SelectGroup(arg0->_messenger, DAT_0051b888);
                    beMessenger_AppendString(arg0->_messenger, DAT_0051b890);
                    beMessenger_DispatchSelected(arg0->_messenger, DAT_0051b8a0);
                }
                arg0->_nowProcKazu = ((igDataList *)arg0->_subWindow)->_count;
                arg0->_st2 = arg0->_st2 + 1;
                arg0->_st3 = 0;
            case 1:
                if (((igDataList *)arg0->_subWindow)->_count != arg0->_nowProcKazu) {
                    switch (arg0->_retCode) {
                    case 6:
                        arg0->_st1 = 6;
                        arg0->_st3 = 0;
                        arg0->_st2 = 0;
                        return;
                    case 4:
                        arg0->_st1 = 4;
                        arg0->_st3 = 0;
                        arg0->_st2 = 0;
                        return;
                    default:
                    case 0:
                        arg0->_st1 = 4;
                        arg0->_st3 = 0;
                        arg0->_st2 = 0;
                        return;
                    }
                }
                break;
            }
            break;
        case 6:
            switch (arg0->_st2) {
            case 0:
                beMessenger_SendNamed(arg0->_messenger, DAT_0051b308, DAT_0051b8a8, 0, DAT_0051b620);
                beMessenger_SendNamed(arg0->_messenger, DAT_0051b308, DAT_0051b318, 0, DAT_0051b620);
                beMessenger_SelectGroup(arg0->_messenger, DAT_0051b3c0);
                beMessenger_AppendString(arg0->_messenger, DAT_0051b8b8);
                beMessenger_AppendString(arg0->_messenger, DAT_004cf8a8[0]);
                beMessenger_AppendString(arg0->_messenger, DAT_0051b550);
                beMessenger_DispatchSelected(arg0->_messenger, DAT_0051b558);
                alloc = igObject_GetAllocator(arg0);
                alloc = GPR_00554c14 ? alloc : Memory_GetAllocatorBySelector(DAT_00587110[0]);
                {
                WindowRef<3> win(FUN_003b4250(alloc));
                beNDMWWindow_BindContext(win.p, arg0, arg0->_insight, arg0->_playerNo, 0);
                ObjectList_AppendRetained(arg0->_subWindow, win.p);
                }
                FUN_0042df70(arg0);
                arg0->_nowProcKazu = ((igDataList *)arg0->_subWindow)->_count;
                arg0->_st2 = arg0->_st2 + 1;
                arg0->_st3 = 0;
                return;
            case 1:
                beMessenger_SelectReceivers(arg0->_messenger, DAT_0051b308, DAT_0051b8c8, 0);
                beMessenger_AppendString(arg0->_messenger, DAT_0051b868);
                beMessenger_DispatchSelected(arg0->_messenger, DAT_0051b338);
                if ((beMessenger_GetBool(arg0->_messenger, 0) & 0xFF) == 1) {
                    return;
                }
                beMessenger_SelectGroup(arg0->_messenger, DAT_0051b3c0);
                beMessenger_AppendString(arg0->_messenger, DAT_0051b8d8);
                beMessenger_AppendString(arg0->_messenger, DAT_0051b1c8);
                beMessenger_AppendString(arg0->_messenger, DAT_0051b8e8);
                beMessenger_DispatchSelected(arg0->_messenger, DAT_0051b6b0);
                beMessenger_SelectGroup(arg0->_messenger, DAT_0051b3c0);
                beMessenger_AppendString(arg0->_messenger, DAT_0051b8d8);
                beMessenger_AppendString(arg0->_messenger, DAT_0051b1d0);
                beMessenger_AppendString(arg0->_messenger, DAT_0051b8f0);
                beMessenger_DispatchSelected(arg0->_messenger, DAT_0051b6b0);
                arg0->_st2 = arg0->_st2 + 1;
                arg0->_st3 = 0;
            case 2:
                if (((igDataList *)arg0->_subWindow)->_count == arg0->_nowProcKazu) {
                    if (arg0->_retCode != -1 && arg0->_st3 != arg0->_retCode) {
                        FUN_0042e330(arg0);
                        arg0->_st3 = arg0->_retCode;
                        return;
                    }
                } else {
                    FUN_0042e9e0(arg0);
                    beNDMWWindow_RunMessageScript(arg0, DAT_0051b8f8, 0);
                    beMessenger_SelectGroup(arg0->_messenger, DAT_0051b3c0);
                    beMessenger_AppendString(arg0->_messenger, DAT_0051b8b8);
                    beMessenger_AppendString(arg0->_messenger, DAT_004cf8a8[0]);
                    beMessenger_AppendString(arg0->_messenger, DAT_0051b6b8);
                    beMessenger_DispatchSelected(arg0->_messenger, DAT_0051b558);
                    beMessenger_SelectReceivers(arg0->_messenger, DAT_0051b308, DAT_0051b8a8, 0);
                    beMessenger_AppendString(arg0->_messenger, DAT_0051b868);
                    sp40[0] = DAT_004e1058[0];
                    sp40[1] = DAT_004e105c[0];
                    sp40[2] = DAT_004e1060[0];
                    beMessenger_AppendVec3(arg0->_messenger, sp40);
                    beMessenger_DispatchSelected(arg0->_messenger, DAT_0051b7e0);
                    beMessenger_SelectReceivers(arg0->_messenger, DAT_0051b308, DAT_0051b318, 0);
                    beMessenger_AppendString(arg0->_messenger, DAT_0051b868);
                    sp30[0] = DAT_004e1058[0];
                    sp30[1] = DAT_004e105c[0];
                    sp30[2] = DAT_004e1060[0];
                    beMessenger_AppendVec3(arg0->_messenger, sp30);
                    beMessenger_DispatchSelected(arg0->_messenger, DAT_0051b7e0);
                    arg0->_st1 = 4;
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
