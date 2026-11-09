#include "dw4/reflected.h"
extern "C" {
typedef struct S_ref { char pad4[4]; int f4; } S_ref;
typedef struct S_obj { char pad4[4]; int f4; char pad8[0x68]; igIntList *f112; } S_obj;
typedef struct S_rec { char pad12[12]; unsigned char f12; } S_rec;
void *FUN_00236f80(...);
int igObject_IsKindOf(...);
void *FUN_003b2c00(...);
void *FUN_003b31b0(...);
void *FUN_003b36f0(...);
void *FUN_003b3ac0(...);
void *FUN_003b4b10(...);
void *FUN_003b7c00(...);
int FUN_00425fb0(...);
int FUN_00426530(...);
int List_Resize(...);
int Memory_GetAllocatorBySelector(...);
int ObjectList_AppendRetained(...);
int beMessenger_AppendInt(...);
int beMessenger_AppendString(...);
int beMessenger_DispatchSelected(...);
int beMessenger_GetBool(...);
int beMessenger_GetObject(...);
int beMessenger_SelectGroup(...);
int beMessenger_SelectReceivers(...);
int beNDMWWindow_BindContext(...);
int beNDMWWindow_ClearQueuedText(...);
int beNDMWWindow_PlayQueuedModelClose(...);
int beNDMWWindow_PollCloseComplete(...);
int beNDMWWindow_PresentModelAtOrigin(...);
int beNDMWWindow_RequestChildrenClose(...);
int igObject_Destroy(...);
int igObject_GetAllocator(...);
S_rec *igProperty_GetRecordByte(...);
extern int DAT_0051b308[4];
extern int DAT_0051b318[4];
extern int DAT_0051b338[4];
extern int DAT_0051b348[4];
extern int DAT_0051b398[4];
extern int DAT_0051b3e8[4];
extern int DAT_0051b620[4];
extern int DAT_0051b848[4];
extern int DAT_0051b858[4];
extern int DAT_0051b868[4];
extern int DAT_0051b870[4];
extern int DAT_00587110[4];
extern int DAT_00587d08[4];
extern int DAT_0058ab68[4];
extern unsigned char GPR_00554c14;
}
/* matching construct: stack smart pointer; each distinct N is a distinct destructor symbol, as retail has one per window class */
template <int N> struct Ref {
    S_ref *p;
    Ref(S_ref *q) : p(q) {}
    ~Ref() {
        S_ref *object = p;
        if (object) {
            --object->f4;
            if (((unsigned long long)(long long)object->f4 & 0x7fffffULL) == 0)
                igObject_Destroy(object);
        }
    }
};

extern "C" void Gap__Bec__beNDMWShopCtrlA0__vfunc_21(beNDMWShopCtrlA0 *arg0) {
    S_ref *t;
    int x;
    int i;

    switch (arg0->_st0) {
    case 0:
        switch (arg0->_st1) {
        case 0:
            beNDMWWindow_PresentModelAtOrigin(arg0, &DAT_0051b848[0], 0, &DAT_0051b858[0], &DAT_0051b620[0]);
            beNDMWWindow_PresentModelAtOrigin(arg0, &DAT_0051b348[0], 0, &DAT_0051b868[0], &DAT_0051b620[0]);
            arg0->_st1 = arg0->_st1 + 1;
            arg0->_st3 = 0;
            arg0->_st2 = 0;
            return;
        case 1:
            beMessenger_SelectReceivers(arg0->_messenger, &DAT_0051b308[0], &DAT_0051b848[0], 0);
            beMessenger_AppendString(arg0->_messenger, &DAT_0051b858[0]);
            beMessenger_DispatchSelected(arg0->_messenger, &DAT_0051b338[0]);
            if ((beMessenger_GetBool(arg0->_messenger, 0) & 0xFF) != 1) {
                x = igObject_GetAllocator(arg0);
                { Ref<1> r1((S_ref *)FUN_003b2c00(GPR_00554c14 != 0 ? x : Memory_GetAllocatorBySelector(DAT_00587110[0])));
                beNDMWWindow_BindContext(r1.p, arg0, arg0->_insight, arg0->_playerNo, 0);
                ObjectList_AppendRetained(arg0->_subWindow, r1.p);
                }  
                x = igObject_GetAllocator(arg0);
                { Ref<2> r2((S_ref *)FUN_003b36f0(GPR_00554c14 != 0 ? x : Memory_GetAllocatorBySelector(DAT_00587110[0])));
                beNDMWWindow_BindContext(r2.p, arg0, arg0->_insight, arg0->_playerNo, 0);
                ObjectList_AppendRetained(arg0->_subWindow, r2.p);
                {
                    S_ref *n = (S_ref *)r2.p;
                    if (n != 0) { n->f4 = (int)((int)(n->f4 + 1)); }
                    t = (S_ref *)(arg0->_account);
                    if (t != 0) {
                        t->f4 = (int)((int)(t->f4 - 1));
                        if (((unsigned long long)((long long)t->f4 << 0x29) >> 0x29) == 0) {
                            igObject_Destroy(t);
                        }
                    }
                    arg0->_account = (int)n;
                }
                FUN_00426530(arg0->_account, 0);
                }  
                x = igObject_GetAllocator(arg0);
                { Ref<3> r3((S_ref *)FUN_003b31b0(GPR_00554c14 != 0 ? x : Memory_GetAllocatorBySelector(DAT_00587110[0])));
                beNDMWWindow_BindContext(r3.p, arg0, arg0->_insight, arg0->_playerNo, arg0->_entCode);
                ObjectList_AppendRetained(arg0->_subWindow, r3.p);
                }  
                i = 0;
                do {
                    beMessenger_SelectGroup(arg0->_messenger, &DAT_0051b398[0]);
                    beMessenger_AppendInt(arg0->_messenger, i);
                    beMessenger_DispatchSelected(arg0->_messenger, &DAT_0051b3e8[0]);
                    if (igProperty_GetRecordByte(beMessenger_GetObject(arg0->_messenger, 0), &DAT_0051b870[0])->f12 != 0) {
                        int c;
                        igIntList *l;
                        l = (igIntList *)arg0->_playerNoList;
                        c = l->_count;
                        if (c < l->_capacity) {
                            l->_count = *(const int *)&l->_count + 1;
                        } else {
                            List_Resize(l, c + 1, 4);
                        }
                        ((int *)l->_data)[c] = i;
                    }
                    i += 1;
                } while (i < 4);
                x = igObject_GetAllocator(arg0);
                { Ref<4> r4((S_ref *)FUN_003b3ac0(GPR_00554c14 != 0 ? x : Memory_GetAllocatorBySelector(DAT_00587110[0])));
                beNDMWWindow_BindContext(r4.p, arg0, arg0->_insight, arg0->_playerNo, 1);
                ObjectList_AppendRetained(arg0->_subWindow, r4.p);
                }  
                arg0->_st0 = arg0->_st0 + 1;
                arg0->_st3 = 0;
                arg0->_st2 = 0;
                arg0->_st1 = 0;
                return;
            }
            break;
        }
        break;
    case 1:
        switch (arg0->_st1) {
        case 0:
            beMessenger_SelectReceivers(arg0->_messenger, &DAT_0051b308[0], &DAT_0051b318[0], 0);
            beMessenger_AppendString(arg0->_messenger, &DAT_0051b868[0]);
            beMessenger_DispatchSelected(arg0->_messenger, &DAT_0051b338[0]);
            if (((beMessenger_GetBool(arg0->_messenger, 0) & 0xFF) != 1) && (arg0->_entCode == 0xA)) {
                arg0->_st1 = 1;
                arg0->_st3 = 0;
                arg0->_st2 = 0;
                return;
            }
            break;
        case 1:
            switch (arg0->_st2) {
            case 0:
                x = igObject_GetAllocator(arg0);
                { Ref<5> r5((S_ref *)FUN_003b4b10(GPR_00554c14 != 0 ? x : Memory_GetAllocatorBySelector(DAT_00587110[0])));
                beNDMWWindow_BindContext(r5.p, arg0, arg0->_insight, arg0->_playerNo, 0x7D3);
                ObjectList_AppendRetained(arg0->_subWindow, r5.p);
                FUN_00426530(arg0->_account, 0);
                }  
                arg0->_nowProcKazu = ((igObjectList *)arg0->_subWindow)->_count;
                arg0->_st2 = arg0->_st2 + 1;
                arg0->_st3 = 0;

            case 1:
                if (((igObjectList *)arg0->_subWindow)->_count != arg0->_nowProcKazu) {
                    switch (arg0->_retCode) {
                    case 0:
                        arg0->_st1 = 2;
                        arg0->_st3 = 0;
                        arg0->_st2 = 0;
                        return;
                    default:
                    case 1:
                        arg0->_st0 = arg0->_st0 + 1;
                        arg0->_st3 = 0;
                        arg0->_st2 = 0;
                        arg0->_st1 = 0;
                        ((beSystem *)FUN_00236f80(arg0->_insight, DAT_00587d08[0]))->_isSResetEnable = 0;
                        return;
                    }
                }
                break;
            }
            break;
        case 2:
            switch (arg0->_st2) {
            case 0:
                x = igObject_GetAllocator(arg0);
                { Ref<5> r6((S_ref *)FUN_003b4b10(GPR_00554c14 != 0 ? x : Memory_GetAllocatorBySelector(DAT_00587110[0])));
                beNDMWWindow_BindContext(r6.p, arg0, arg0->_insight, arg0->_playerNo, -1);
                ObjectList_AppendRetained(arg0->_subWindow, r6.p);
                i = 0;
                {
                    int j;
                    int c;
                    igIntList *l;
                    int *src;
                    for (j = 0; j < ((igIntList *)arg0->_playerNoList)->_count; j++) {
                        src = (int *)((igIntList *)arg0->_playerNoList)->_data + j;
                        l = ((S_obj *)r6.p)->f112;
                        c = l->_count;
                        if (c < l->_capacity) {
                            l->_count = *(const int *)&l->_count + 1;
                        } else {
                            List_Resize(l, c + 1, 4);
                        }
                        ((int *)l->_data)[c] = *src;
                    }
                }
                }  
                FUN_00426530(arg0->_account, 1);
                arg0->_nowProcKazu = ((igObjectList *)arg0->_subWindow)->_count;
                arg0->_st2 = arg0->_st2 + 1;
                arg0->_st3 = 0;

            case 1:
                {
                    if (((igObjectList *)arg0->_subWindow)->_count != arg0->_nowProcKazu) {
                        switch (arg0->_retCode) {
                        case 0:
                        case 1:
                        case 2:
                        case 3:
                            {
                                int *found = 0;
                                int *obj;
                                int idx;
                                for (idx = 0; idx < ((igObjectList *)arg0->_subWindow)->_count; idx++) {
                                    obj = (int *)((int *)((igObjectList *)(*(int *)&arg0->_subWindow))->_data)[idx];
                                    if ((obj != 0) && (igObject_IsKindOf(obj, DAT_0058ab68[0]) != 0)) {
                                        found = obj;
                                    } else {
                                        found = 0;
                                    }
                                    if (found != 0) break;
                                }
                                if (found != 0) {
                                    found[5] = ((int *)((igIntList *)arg0->_playerNoList)->_data)[arg0->_retCode];
                                    FUN_00425fb0(found);
                                    arg0->_playerNo = ((int *)((igIntList *)arg0->_playerNoList)->_data)[arg0->_retCode];
                                }
                            }
                            x = igObject_GetAllocator(arg0);
                            { Ref<7> r7((S_ref *)FUN_003b7c00(GPR_00554c14 != 0 ? x : Memory_GetAllocatorBySelector(DAT_00587110[0])));
                            beNDMWWindow_BindContext(r7.p, arg0, arg0->_insight, ((int *)((igIntList *)arg0->_playerNoList)->_data)[arg0->_retCode], 0);
                            ObjectList_AppendRetained(arg0->_subWindow, r7.p);
                            }  
                            arg0->_nowProcKazu = ((igObjectList *)arg0->_subWindow)->_count;
                            arg0->_st1 = 3;
                            arg0->_st3 = 0;
                            arg0->_st2 = 0;
                            return;
                        default:
                            arg0->_st1 = 1;
                            arg0->_st3 = 0;
                            arg0->_st2 = 0;
                            return;
                        }
                    }
                }
                break;
            }
            break;
        case 3:
            if (((igObjectList *)arg0->_subWindow)->_count != arg0->_nowProcKazu) {
                arg0->_st1 = 2;
                arg0->_st3 = 0;
                arg0->_st2 = 0;
                return;
            }
            break;
        }
        break;
    case 2:
        beNDMWWindow_PlayQueuedModelClose();
        beNDMWWindow_ClearQueuedText(arg0);
        beNDMWWindow_RequestChildrenClose(arg0);
        arg0->_st0 = arg0->_st0 + 1;
        arg0->_st3 = 0;
        arg0->_st2 = 0;
        arg0->_st1 = 0;
        t = (S_ref *)(arg0->_account);
        if (t != 0) {
            t->f4 = (int)((int)(t->f4 - 1));
            if (((unsigned long long)((long long)t->f4 << 0x29) >> 0x29) == 0) {
                igObject_Destroy(t);
            }
        }
        arg0->_account = 0;
        return;
    case 3:
        if (beNDMWWindow_PollCloseComplete() != 0) {
            arg0->_isRun = 0;
        }
        break;
    }
}
