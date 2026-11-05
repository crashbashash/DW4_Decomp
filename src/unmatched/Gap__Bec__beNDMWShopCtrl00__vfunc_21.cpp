#include "dw4/reflected.h"
extern "C" {
typedef struct S_ref { char pad4[4]; int f4; } S_ref;
void *FUN_003b31b0(...);
void *FUN_003b3370(...);
void *FUN_003b36f0(...);
void *FUN_003b3900(...);
void *FUN_003b3ac0(...);
void *FUN_003b6310(...);
void *FUN_003b6650(...);
void *FUN_003b81d0(...);
void *FUN_003b8400(...);
void *FUN_003b8630(...);
void *FUN_003b8b60(...);
int Memory_GetAllocatorBySelector(...);
int ObjectList_AppendRetained(...);
int beMessenger_AppendString(...);
int beMessenger_DispatchSelected(...);
int beMessenger_GetBool(...);
int beMessenger_SelectReceivers(...);
int beMessenger_SendNamed(...);
int beNDMWWindow_BindContext(...);
int beNDMWWindow_ClearQueuedText(...);
int beNDMWWindow_PlayQueuedModelClose(...);
int beNDMWWindow_PollCloseComplete(...);
int beNDMWWindow_RequestChildrenClose(...);
int igObject_Destroy(...);
int igObject_GetAllocator(...);
extern int DAT_0051b308[4];
extern int DAT_0051b318[4];
extern int DAT_0051b328[4];
extern int DAT_0051b338[4];
extern int DAT_0051b348[4];
extern int DAT_0051b358[4];
extern int DAT_00587110[4];
extern unsigned char GPR_00554c14;
}
/* One releasing holder class per retail destructor copy (each block-local holder below has its own copy):
 * RefA 0x00427020, RefB 0x0040ed60, RefC 0x0040ece0, RefD 0x003b7fe0, RefE 0x00426fa0, RefF 0x003b90a0. */
struct RefA {
    S_ref *p;
    RefA(S_ref *q) : p(q) {}
    ~RefA() {
        S_ref *object = p;
        if (object) {
            --object->f4;
            if (((unsigned long long)(long long)object->f4 & 0x7fffffULL) == 0)
                igObject_Destroy(object);
        }
    }
};
struct RefB {
    S_ref *p;
    RefB(S_ref *q) : p(q) {}
    ~RefB() {
        S_ref *object = p;
        if (object) {
            --object->f4;
            if (((unsigned long long)(long long)object->f4 & 0x7fffffULL) == 0)
                igObject_Destroy(object);
        }
    }
};
struct RefC {
    S_ref *p;
    RefC(S_ref *q) : p(q) {}
    ~RefC() {
        S_ref *object = p;
        if (object) {
            --object->f4;
            if (((unsigned long long)(long long)object->f4 & 0x7fffffULL) == 0)
                igObject_Destroy(object);
        }
    }
};
struct RefD {
    S_ref *p;
    RefD(S_ref *q) : p(q) {}
    ~RefD() {
        S_ref *object = p;
        if (object) {
            --object->f4;
            if (((unsigned long long)(long long)object->f4 & 0x7fffffULL) == 0)
                igObject_Destroy(object);
        }
    }
};
struct RefE {
    S_ref *p;
    RefE(S_ref *q) : p(q) {}
    ~RefE() {
        S_ref *object = p;
        if (object) {
            --object->f4;
            if (((unsigned long long)(long long)object->f4 & 0x7fffffULL) == 0)
                igObject_Destroy(object);
        }
    }
};
struct RefF {
    S_ref *p;
    RefF(S_ref *q) : p(q) {}
    ~RefF() {
        S_ref *object = p;
        if (object) {
            --object->f4;
            if (((unsigned long long)(long long)object->f4 & 0x7fffffULL) == 0)
                igObject_Destroy(object);
        }
    }
};

extern "C" void Gap__Bec__beNDMWShopCtrl00__vfunc_21(beNDMWShopCtrl00 *arg0) {
    S_ref *t;
    int x;

    switch (arg0->_st0) {
    case 0:
        x = igObject_GetAllocator(arg0);
        { RefA r1((S_ref *)FUN_003b3370(GPR_00554c14 != 0 ? x : Memory_GetAllocatorBySelector(DAT_00587110[0])));
        beNDMWWindow_BindContext(r1.p, arg0, arg0->_insight, arg0->_playerNo, 0);
        ObjectList_AppendRetained(arg0->_subWindow, r1.p);
        }
        x = igObject_GetAllocator(arg0);
        { RefB r2((S_ref *)FUN_003b3ac0(GPR_00554c14 != 0 ? x : Memory_GetAllocatorBySelector(DAT_00587110[0])));
        beNDMWWindow_BindContext(r2.p, arg0, arg0->_insight, arg0->_playerNo, 0);
        ObjectList_AppendRetained(arg0->_subWindow, r2.p);
        }
        x = igObject_GetAllocator(arg0);
        { RefC r3((S_ref *)FUN_003b3900(GPR_00554c14 != 0 ? x : Memory_GetAllocatorBySelector(DAT_00587110[0])));
        beNDMWWindow_BindContext(r3.p, arg0, arg0->_insight, arg0->_playerNo, 0);
        ObjectList_AppendRetained(arg0->_subWindow, r3.p);
        }
        x = igObject_GetAllocator(arg0);
        { RefD r4((S_ref *)FUN_003b36f0(GPR_00554c14 != 0 ? x : Memory_GetAllocatorBySelector(DAT_00587110[0])));
        beNDMWWindow_BindContext(r4.p, arg0, arg0->_insight, arg0->_playerNo, 0);
        ObjectList_AppendRetained(arg0->_subWindow, r4.p);
        }
        x = igObject_GetAllocator(arg0);
        { RefE r5((S_ref *)FUN_003b31b0(GPR_00554c14 != 0 ? x : Memory_GetAllocatorBySelector(DAT_00587110[0])));
        beNDMWWindow_BindContext(r5.p, arg0, arg0->_insight, arg0->_playerNo, arg0->_entCode);
        ObjectList_AppendRetained(arg0->_subWindow, r5.p);
        }
        arg0->_st0 = arg0->_st0 + 1;
        arg0->_st3 = 0;
        arg0->_st2 = 0;
        arg0->_st1 = 0;
        return;
    case 1:
        switch (arg0->_st1) {
        case 0:
            beMessenger_SelectReceivers(arg0->_messenger, &DAT_0051b308[0], &DAT_0051b318[0], 0);
            beMessenger_AppendString(arg0->_messenger, &DAT_0051b328[0]);
            beMessenger_DispatchSelected(arg0->_messenger, &DAT_0051b338[0]);
            if ((beMessenger_GetBool(arg0->_messenger, 0) & 0xFF) == 1) {
                return;
            } else {
                {
                RefF r6(0);
                switch (arg0->_entCode) {
                case 1:
                x = igObject_GetAllocator(arg0);
                x = GPR_00554c14 != 0 ? x : Memory_GetAllocatorBySelector(DAT_00587110[0]);
                t = r6.p;
                if (t != 0) {
                    t->f4 = (int)((int)(t->f4 - 1));
                    if (((unsigned long long)((long long)t->f4 << 0x29) >> 0x29) == 0) {
                        igObject_Destroy(t);
                    }
                }
                r6.p = (S_ref *)FUN_003b8b60(x);
                    break;
                case 3:
                x = igObject_GetAllocator(arg0);
                x = GPR_00554c14 != 0 ? x : Memory_GetAllocatorBySelector(DAT_00587110[0]);
                t = r6.p;
                if (t != 0) {
                    t->f4 = (int)((int)(t->f4 - 1));
                    if (((unsigned long long)((long long)t->f4 << 0x29) >> 0x29) == 0) {
                        igObject_Destroy(t);
                    }
                }
                r6.p = (S_ref *)FUN_003b8630(x);
                    break;
                case 4:
                x = igObject_GetAllocator(arg0);
                x = GPR_00554c14 != 0 ? x : Memory_GetAllocatorBySelector(DAT_00587110[0]);
                t = r6.p;
                if (t != 0) {
                    t->f4 = (int)((int)(t->f4 - 1));
                    if (((unsigned long long)((long long)t->f4 << 0x29) >> 0x29) == 0) {
                        igObject_Destroy(t);
                    }
                }
                r6.p = (S_ref *)FUN_003b8400(x);
                    break;
                case 5:
                x = igObject_GetAllocator(arg0);
                x = GPR_00554c14 != 0 ? x : Memory_GetAllocatorBySelector(DAT_00587110[0]);
                t = r6.p;
                if (t != 0) {
                    t->f4 = (int)((int)(t->f4 - 1));
                    if (((unsigned long long)((long long)t->f4 << 0x29) >> 0x29) == 0) {
                        igObject_Destroy(t);
                    }
                }
                r6.p = (S_ref *)FUN_003b81d0(x);
                    break;
                case 6:
                case 7:
                case 8:
                x = igObject_GetAllocator(arg0);
                x = GPR_00554c14 != 0 ? x : Memory_GetAllocatorBySelector(DAT_00587110[0]);
                t = r6.p;
                if (t != 0) {
                    t->f4 = (int)((int)(t->f4 - 1));
                    if (((unsigned long long)((long long)t->f4 << 0x29) >> 0x29) == 0) {
                        igObject_Destroy(t);
                    }
                }
                r6.p = (S_ref *)FUN_003b6650(x);
                    break;
                case 9:
                x = igObject_GetAllocator(arg0);
                x = GPR_00554c14 != 0 ? x : Memory_GetAllocatorBySelector(DAT_00587110[0]);
                t = r6.p;
                if (t != 0) {
                    t->f4 = (int)((int)(t->f4 - 1));
                    if (((unsigned long long)((long long)t->f4 << 0x29) >> 0x29) == 0) {
                        igObject_Destroy(t);
                    }
                }
                r6.p = (S_ref *)FUN_003b6310(x);
                    break;
                default:
                x = igObject_GetAllocator(arg0);
                x = GPR_00554c14 != 0 ? x : Memory_GetAllocatorBySelector(DAT_00587110[0]);
                t = r6.p;
                if (t != 0) {
                    t->f4 = (int)((int)(t->f4 - 1));
                    if (((unsigned long long)((long long)t->f4 << 0x29) >> 0x29) == 0) {
                        igObject_Destroy(t);
                    }
                }
                r6.p = (S_ref *)FUN_003b8b60(x);
                    break;
                }
                beNDMWWindow_BindContext(r6.p, arg0, arg0->_insight, arg0->_playerNo, arg0->_entCode);
                ObjectList_AppendRetained(arg0->_subWindow, r6.p);
                }
                arg0->_nowProcKazu = ((igObjectList *)arg0->_subWindow)->_count;
                arg0->_st1 = arg0->_st1 + 1;
                arg0->_st3 = 0;
                arg0->_st2 = 0;
            }
        case 1:
            if (((igObjectList *)arg0->_subWindow)->_count != arg0->_nowProcKazu) {
                arg0->_st0 = arg0->_st0 + 1;
                arg0->_st3 = 0;
                arg0->_st2 = 0;
                arg0->_st1 = 0;
                return;
            }
            break;
        }
        break;
    case 2:
        beMessenger_SendNamed(arg0->_messenger, &DAT_0051b308[0], &DAT_0051b348[0], 0, &DAT_0051b358[0]);
        beNDMWWindow_PlayQueuedModelClose(arg0);
        beNDMWWindow_ClearQueuedText(arg0);
        beNDMWWindow_RequestChildrenClose(arg0);
        arg0->_st0 = arg0->_st0 + 1;
        arg0->_st3 = 0;
        arg0->_st2 = 0;
        arg0->_st1 = 0;
        return;
    case 3:
        if (beNDMWWindow_PollCloseComplete() != 0) {
            arg0->_isRun = 0;
        }
        break;
    }
}
