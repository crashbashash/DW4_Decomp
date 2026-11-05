/* Gap__Bec__beNDMWShopDevice__vfunc_21 (0x0043cc20): update state machine of the shop device page.
 * State 1 opens one sub-window per step (_st1 0: the device select list FUN_003b4d90 with the entry
 * code of the shop kind, 1: FUN_003b6bc0 with the entry code, 2: FUN_003b7360) and waits for it to
 * close, routing the select result to the next step; state 2 closes everything; state 3 waits for the
 * close and clears _isRun.  Each new window is owned by a stack reference until it has been bound and
 * listed. */
#include "dw4/reflected.h"
extern "C" {
igObject *FUN_003b4d90(void *);
igObject *FUN_003b6bc0(void *);
igObject *FUN_003b7360(void *);
void *Memory_GetAllocatorBySelector(int);
int ObjectList_AppendRetained(void *, void *);
int beNDMWWindow_BindContext(void *, void *, int, int, int);
int beNDMWWindow_ClearQueuedText(void *);
int beNDMWWindow_PlayQueuedModelClose(void *);
int beNDMWWindow_PollCloseComplete(void *);
int beNDMWWindow_RequestChildrenClose(void *);
void igObject_Destroy(void *);
void *igObject_GetAllocator(void *);
extern int DAT_00587110[4];
extern unsigned char GPR_00554c14;
}
/* Owning stack reference to a sub-window of one of the three window classes opened here (kind 0..2
 * follows the _st1 step): constructed from the factory result and released on scope exit (reference
 * count in the low 23 bits of _refCount).  The out-of-line copies the exception table names are the
 * retail bodies 0x00428710, 0x0042c790 and 0x0042b800 (config/SLUS-20836/unit-objects.json, duplicates
 * __dt__12WindowRef<0>Fv, __dt__12WindowRef<1>Fv, __dt__12WindowRef<2>Fv). */
template <int kind> class WindowRef {
public:
    igObject *p;
    WindowRef(igObject *w) : p(w) {}
    ~WindowRef() { igObject *w = p; if (w != 0) { --w->_refCount; if ((w->_refCount & 0x7fffff) == 0) igObject_Destroy(w); } }
};
#define LST(d) ((igObjectList *)(d)->_subWindow)
typedef beNDMWShopDevice S;
extern "C" void Gap__Bec__beNDMWShopDevice__vfunc_21(S *arg0) {
    void *alloc;
    switch (arg0->_st0) {
    case 0:
        arg0->_st0 = ((volatile S *)arg0)->_st0 + 1;
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
                alloc = igObject_GetAllocator(arg0);
                alloc = GPR_00554c14 ? alloc : Memory_GetAllocatorBySelector(DAT_00587110[0]);
                {
                WindowRef<0> win(FUN_003b4d90(alloc));
                beNDMWWindow_BindContext(win.p, arg0, arg0->_insight, arg0->_playerNo, 0);
                ObjectList_AppendRetained(LST(arg0), win.p);
                switch (arg0->_entCode) {
                case 6: ((beNDMWShopSelect01 *)win.p)->_entCode = 0x672; break;
                case 7: ((beNDMWShopSelect01 *)win.p)->_entCode = 0x6D6; break;
                case 8: ((beNDMWShopSelect01 *)win.p)->_entCode = 0x73A; break;
                }
                }
                arg0->_nowProcKazu = LST(arg0)->_count;
                arg0->_st2 = arg0->_st2 + 1;
                arg0->_st3 = 0;
            case 1:
                if (LST(arg0)->_count != arg0->_nowProcKazu) {
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
                    default:
                    case 2:
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
        case 1:
            switch (arg0->_st2) {
            case 0:
                alloc = igObject_GetAllocator(arg0);
                alloc = GPR_00554c14 ? alloc : Memory_GetAllocatorBySelector(DAT_00587110[0]);
                {
                WindowRef<1> win(FUN_003b6bc0(alloc));
                beNDMWWindow_BindContext(win.p, arg0, arg0->_insight, arg0->_playerNo, arg0->_entCode);
                ObjectList_AppendRetained(LST(arg0), win.p);
                }
                arg0->_nowProcKazu = LST(arg0)->_count;
                arg0->_st2 = arg0->_st2 + 1;
                arg0->_st3 = 0;
            case 1:
                if (LST(arg0)->_count != arg0->_nowProcKazu) {
                    arg0->_st1 = 0;
                    arg0->_st3 = 0;
                    arg0->_st2 = 0;
                    return;
                }
                break;
            }
            break;
        case 2:
            switch (arg0->_st2) {
            case 0:
                alloc = igObject_GetAllocator(arg0);
                alloc = GPR_00554c14 ? alloc : Memory_GetAllocatorBySelector(DAT_00587110[0]);
                {
                WindowRef<2> win(FUN_003b7360(alloc));
                beNDMWWindow_BindContext(win.p, arg0, arg0->_insight, arg0->_playerNo, 0);
                ObjectList_AppendRetained(LST(arg0), win.p);
                }
                arg0->_nowProcKazu = LST(arg0)->_count;
                arg0->_st2 = arg0->_st2 + 1;
                arg0->_st3 = 0;
            case 1:
                if (LST(arg0)->_count != arg0->_nowProcKazu) {
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
