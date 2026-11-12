#include "dw4/reflected.h"

extern "C" int igObject_Destroy(...);
extern "C" void * beBaseInfoDataList_Create(...);
extern "C" int *FUN_0040c180(int *arg0, int *arg1);
extern "C" int Gap__Bec__beNDMWSaveIntf__vfunc_30(void);
extern "C" int Gap__Bec__beNDMWSaveIntf__vfunc_20(void);
extern "C" void *FUN_003bc940(...);
extern "C" int FUN_003bcc20(...);
extern "C" void *FUN_003c2e60(...);
extern "C" void *FUN_003c3560(...);
extern "C" void *FUN_003c3900(...);
extern "C" void *FUN_003c3e40(...);
extern "C" void *FUN_003c6b00(...);
extern "C" void *beNDMWLoadIntf2ComMdlCtrl_Create(...);
extern "C" void *beNDMWLoadIntf2TextOrder_Create(...);
extern "C" int FUN_003d9de0(...);
extern "C" int Memory_GetAllocatorBySelector(...);
extern "C" int ObjectList_AppendRetained(...);
extern "C" int beMessenger_AppendInt(...);
extern "C" int beMessenger_DispatchSelected(...);
extern "C" int beMessenger_GetInt(...);
extern "C" int beMessenger_GetIntCount(...);
extern "C" void *beMessenger_GetObject(...);
extern "C" unsigned int beMessenger_ResolveEnumValue(...);
extern "C" int beMessenger_SelectGroup(...);
extern "C" int beMessenger_SendNamed(...);
extern "C" int beMessenger_SetInt(...);
extern "C" int igObject_GetAllocator(...);
extern "C" void *igProperty_FindByName(...);
/* reference-counted engine object header: refcount word at +4 */

typedef struct RefCountedHeader { char pad4[4]; int f4; } RefCountedHeader;
extern "C" RefCountedHeader * FUN_00236f80(...);
extern "C" int DAT_00588518[4];
extern "C" void Gap__Bec__beNDMWSaveIntf__vfunc_32(beNDMWSaveIntf *arg0);
extern "C" int g_beNDMWSaveIntfInfo_metaObject[4];
extern "C" int g_beNDMWSaveIntf_metaObject[4];
extern "C" int beMessenger_RegisterReceiver(int, beBaseInfoRam *, int *, int, int);
extern "C" int beMessenger_RegisterReceiverFromInfo(int, beBaseInfoRam *, int *);
extern "C" int DAT_00519908[4];
extern "C" int DAT_00519918[4];
extern "C" void Gap__Bec__beNDMWSaveIntf__vfunc_29(beNDMWSaveIntf *arg0, beBaseInfoRam *arg1);
/* reference-counted engine object header: refcount word at +4 */
struct RC { int vt; int rc; };
/* Message record: only the enum value name at +20 is read. */
struct MsgArg { char pad20[20]; int f20; };
/* matching construct: element of the list reached through the COMMONINTF object (+40 -> +16 array of flag holders); no reflected class established */
struct PropZ { char pad13[13]; unsigned char f13; };
struct PropY { char pad16[16]; struct PropZ **f16; };
struct PropX { char pad40[40]; struct PropY *f40; };
extern "C" int DAT_004cf640[4];
extern "C" int DAT_004cf644[4];
extern "C" int DAT_004cf648[4];
extern "C" int DAT_00519670[4];
extern "C" int DAT_00519678[4];
extern "C" int DAT_00519688[4];
extern "C" int DAT_00519698[4];
extern "C" int DAT_005196a8[4];
extern "C" int DAT_005196e0[4];
extern "C" int DAT_00519928[4];
extern "C" int DAT_00519938[4];
extern "C" int DAT_00519948[4];
extern "C" int DAT_00519958[4];
extern "C" int DAT_00585be0[4];
extern "C" int DAT_00587110[4];
extern "C" int DAT_00587d08[4];
extern "C" int DAT_00589208[4];
extern "C" unsigned char GPR_00554c14;
/* Owning stack reference to a request or window object; one instantiation per object class (0 the
 * data list, 1 the control data, 2 text order, 3 model control, 4 message window, 5 slot selector,
 * 6 state control, 7 state data, 8 data selector), so each gets its own out-of-line destructor. */
template <int kind> struct RP {
    RC *p;
    RP(RC *q) : p(q) {}
    ~RP() { RC *q = p; if (q != 0) { q->rc = q->rc - 1; if ((q->rc & 0x7fffff) == 0) igObject_Destroy(q); } }
};
/* matching construct: inlined get-or-create of arg1's list; its own stack smart-pointer slot per expansion */
/* matching construct: the holder destructor nested in this inline function is only inlined (as retail has it) with the inline depth raised */
struct En { static inline void Run(beBaseInfoRam *o) {
    if (o->_dataList == 0) {
        int base = igObject_GetAllocator(o); int a; if (GPR_00554c14 != 0) { a = base; } else { a = Memory_GetAllocatorBySelector(DAT_00587110[0]); }
        RP<0> r((RC *)beBaseInfoDataList_Create(a)); RC *n; RC *old;
        n = r.p; if (n != 0) n->rc = n->rc + 1;
        old = (RC *)o->_dataList;
        if (old != 0) { old->rc = old->rc - 1; if (((unsigned long long)((long long)old->rc << 0x29) >> 0x29) == 0) igObject_Destroy(old); }
        o->_dataList = (int)n;
    }
} };
extern "C" int Gap__Bec__beNDMWSaveIntf__vfunc_34(beNDMWSaveIntf *arg0, beBaseInfoRam *arg1, MsgArg *arg2);

void Gap__Bec__beNDMWSaveIntf__vfunc_32(beNDMWSaveIntf *arg0) {
    RefCountedHeader *temp_a0;
    RefCountedHeader *temp_v0;

    if (arg0->_padManager == 0) {
        temp_v0 = FUN_00236f80(arg0->_insight, DAT_00588518[0]);
        if (temp_v0 != 0) {
            temp_v0->f4 = (int)((int) (temp_v0->f4 + 1));
        }
        temp_a0 = (RefCountedHeader *)arg0->_padManager;
        if (temp_a0 != 0) {
            temp_a0->f4 = (int)((int) (temp_a0->f4 - 1));
            if (((unsigned long long) ((long long) temp_a0->f4 << 0x29) >> 0x29) == 0) {
                igObject_Destroy(temp_a0);
            }
        }
        arg0->_padManager = (int)temp_v0;
    }
}

int *FUN_0040c180(int *arg0, int *arg1) {
    *arg0 = ((int)beBaseInfoDataList_Create(*arg1));
    return arg0;
}

int Gap__Bec__beNDMWSaveIntf__vfunc_30(void)
{
    return g_beNDMWSaveIntfInfo_metaObject[0];
}

void Gap__Bec__beNDMWSaveIntf__vfunc_29(beNDMWSaveIntf *arg0, beBaseInfoRam *arg1) {
    beMessenger_RegisterReceiverFromInfo(arg0->_messenger, arg1, &DAT_00519908[0]);
    beMessenger_RegisterReceiver(arg0->_messenger, arg1, &DAT_00519918[0], 0, arg1->_ramNo);
}

int Gap__Bec__beNDMWSaveIntf__vfunc_34(beNDMWSaveIntf *arg0, beBaseInfoRam *arg1, MsgArg *arg2) {
    unsigned int v = beMessenger_ResolveEnumValue(arg0->_messenger, FUN_003bcc20(), arg2->f20);
    if (v == 0) {
        if (arg1->_dataList == 0) {
            int base = igObject_GetAllocator(arg0); int a; if (GPR_00554c14 != 0) { a = base; } else { a = Memory_GetAllocatorBySelector(DAT_00587110[0]); }
            RP<0> cc((RC *)beBaseInfoDataList_Create(a)); RC *n; RC *old;
            n = cc.p; if (n != 0) n->rc = n->rc + 1;
            old = (RC *)arg1->_dataList;
            if (old != 0) { old->rc = old->rc - 1; if (((unsigned long long)((long long)old->rc << 0x29) >> 0x29) == 0) igObject_Destroy(old); }
            arg1->_dataList = (int)n;
            arg0->_system_ = ((int)FUN_00236f80(arg0->_insight, DAT_00587d08[0]));
            {
                int base = igObject_GetAllocator(arg0); int a; if (GPR_00554c14 != 0) { a = base; } else { a = Memory_GetAllocatorBySelector(DAT_00587110[0]); }
                RP<1> c8((RC *)FUN_003bc940(a));
                ObjectList_AppendRetained(arg1->_dataList, c8.p);
                ((beNDMWSaveIntfCtrlData *)c8.p)->_isRun = 1;
                if (arg1->_ramNo == 0) {
                    ((beNDMWSaveIntfCtrlData *)c8.p)->_isRdy = 0;
                    ((beNDMWSaveIntfCtrlData *)c8.p)->_isEntry = 1;
                    ((beNDMWSaveIntfCtrlData *)c8.p)->_isCtrl = 1;
                } else {
                    ((beNDMWSaveIntfCtrlData *)c8.p)->_isRdy = 0;
                    ((beNDMWSaveIntfCtrlData *)c8.p)->_isEntry = 0;
                    ((beNDMWSaveIntfCtrlData *)c8.p)->_isCtrl = 1;
                }
            }
            beMessenger_SendNamed(arg0->_messenger, &DAT_00519928[0], 0, 0, &DAT_00519938[0]);
            ObjectList_AppendRetained(arg1->_dataList, beMessenger_GetObject(arg0->_messenger, 0));
            {
                int base = igObject_GetAllocator(arg0); int a; if (GPR_00554c14 != 0) { a = base; } else { a = Memory_GetAllocatorBySelector(DAT_00587110[0]); }
                RP<2> c4((RC *)beNDMWLoadIntf2TextOrder_Create(a));
                ((beNDMWLoadIntf2TextOrder *)c4.p)->_messenger = arg0->_messenger;
                beNDMWLoadIntf2TextOrder *o4 = (beNDMWLoadIntf2TextOrder *)c4.p;
                o4->_lua = ((int)FUN_00236f80(arg0->_insight, DAT_00589208[0]));
                ObjectList_AppendRetained(arg1->_dataList, c4.p);
            }
            {
                int base = igObject_GetAllocator(arg0); int a; if (GPR_00554c14 != 0) { a = base; } else { a = Memory_GetAllocatorBySelector(DAT_00587110[0]); }
                RP<3> c0((RC *)beNDMWLoadIntf2ComMdlCtrl_Create(a));
                ObjectList_AppendRetained(arg1->_dataList, c0.p);
                ((beNDMWLoadIntf2ComMdlCtrl *)c0.p)->_messenger = arg0->_messenger;
                int i3 = arg1->_ramNo * 12;
                beNDMWLoadIntf2ComMdlCtrl *o0 = (beNDMWLoadIntf2ComMdlCtrl *)c0.p;
                float fx, fy, fz;
                fz = *(float *)((char *)DAT_004cf648 + i3);
                fy = *(float *)((char *)DAT_004cf644 + i3);
                fx = *(float *)((char *)DAT_004cf640 + i3);
                ((float *)&o0->_pos)[0] = fx;
                ((float *)&o0->_pos)[1] = fy;
                ((float *)&o0->_pos)[2] = fz;
            }
            {
                int base = igObject_GetAllocator(arg0); int a; if (GPR_00554c14 != 0) { a = base; } else { a = Memory_GetAllocatorBySelector(DAT_00587110[0]); }
                RP<4> bc((RC *)FUN_003c6b00(a));
                ((beNDMWLoadIntf2MesWin *)bc.p)->_ramNo = arg1->_ramNo;
                ((beNDMWLoadIntf2MesWin *)bc.p)->_messenger = arg0->_messenger;
                ((beNDMWLoadIntf2MesWin *)bc.p)->_padManager = ((int)FUN_00236f80(arg0->_insight, DAT_00588518[0]));
                ObjectList_AppendRetained(arg1->_dataList, bc.p);
                En::Run(arg1);
                ((beNDMWLoadIntf2MesWin *)bc.p)->_textOrder = (int)igProperty_FindByName(arg1->_dataList, DAT_00585be0[0], &DAT_00519948[0]);
            }
            {
                int base = igObject_GetAllocator(arg0); int a; if (GPR_00554c14 != 0) { a = base; } else { a = Memory_GetAllocatorBySelector(DAT_00587110[0]); }
                RP<5> b8((RC *)FUN_003c2e60(a));
                ((beNDMWLoadIntf2SelSlot *)b8.p)->_ramNo = arg1->_ramNo;
                ((beNDMWLoadIntf2SelSlot *)b8.p)->_messenger = arg0->_messenger;
                ((beNDMWLoadIntf2SelSlot *)b8.p)->_padManager = ((int)FUN_00236f80(arg0->_insight, DAT_00588518[0]));
                En::Run(arg1);
                ((beNDMWLoadIntf2SelSlot *)b8.p)->_comMdlCtrl = (int)igProperty_FindByName(arg1->_dataList, DAT_00585be0[0], &DAT_00519678[0]);
                En::Run(arg1);
                ((beNDMWLoadIntf2SelSlot *)b8.p)->_textOrder = (int)igProperty_FindByName(arg1->_dataList, DAT_00585be0[0], &DAT_00519948[0]);
                En::Run(arg1);
                ((beNDMWLoadIntf2SelSlot *)b8.p)->_commonIntf = (int)igProperty_FindByName(arg1->_dataList, DAT_00585be0[0], &DAT_00519698[0]);
                ObjectList_AppendRetained(arg1->_dataList, b8.p);
            }
            {
                int base = igObject_GetAllocator(arg0); int a; if (GPR_00554c14 != 0) { a = base; } else { a = Memory_GetAllocatorBySelector(DAT_00587110[0]); }
                RP<6> b4((RC *)FUN_003c3900(a));
                {
                    int base2 = igObject_GetAllocator(arg0); int a2; if (GPR_00554c14 != 0) { a2 = base2; } else { a2 = Memory_GetAllocatorBySelector(DAT_00587110[0]); }
                    RP<7> b0((RC *)FUN_003c3e40(a2));
                    En::Run(arg1);
                    void *s0 = igProperty_FindByName(arg1->_dataList, DAT_00585be0[0], &DAT_00519698[0]);
                    En::Run(arg1);
                    void *s4 = igProperty_FindByName(arg1->_dataList, DAT_00585be0[0], &DAT_00519948[0]);
                    En::Run(arg1);
                    FUN_003d9de0(b0.p, arg1->_ramNo, s0, s4, igProperty_FindByName(arg1->_dataList, DAT_00585be0[0], &DAT_00519678[0]), arg0->_messenger, 0);
                    ObjectList_AppendRetained(((beNDMWLoadIntf2DegiStateCtrl *)b4.p)->_statDataList, b0.p);
                }
                {
                    int base2 = igObject_GetAllocator(arg0); int a2; if (GPR_00554c14 != 0) { a2 = base2; } else { a2 = Memory_GetAllocatorBySelector(DAT_00587110[0]); }
                    RP<7> ac((RC *)FUN_003c3e40(a2));
                    En::Run(arg1);
                    void *s0 = igProperty_FindByName(arg1->_dataList, DAT_00585be0[0], &DAT_00519698[0]);
                    En::Run(arg1);
                    void *s4 = igProperty_FindByName(arg1->_dataList, DAT_00585be0[0], &DAT_00519948[0]);
                    En::Run(arg1);
                    FUN_003d9de0(ac.p, arg1->_ramNo, s0, s4, igProperty_FindByName(arg1->_dataList, DAT_00585be0[0], &DAT_00519678[0]), arg0->_messenger, 1);
                    ObjectList_AppendRetained(((beNDMWLoadIntf2DegiStateCtrl *)b4.p)->_statDataList, ac.p);
                }
                ObjectList_AppendRetained(arg1->_dataList, b4.p);
            }
            {
                int base = igObject_GetAllocator(arg0); int a; if (GPR_00554c14 != 0) { a = base; } else { a = Memory_GetAllocatorBySelector(DAT_00587110[0]); }
                RP<8> a8((RC *)FUN_003c3560(a));
                ((beNDMWLoadIntf2DataSelIntf *)a8.p)->_padManager = ((int)FUN_00236f80(arg0->_insight, DAT_00588518[0]));
                En::Run(arg1);
                ((beNDMWLoadIntf2DataSelIntf *)a8.p)->_comMdlCtrl = (int)igProperty_FindByName(arg1->_dataList, DAT_00585be0[0], &DAT_00519678[0]);
                En::Run(arg1);
                ((beNDMWLoadIntf2DataSelIntf *)a8.p)->_textOrder = (int)igProperty_FindByName(arg1->_dataList, DAT_00585be0[0], &DAT_00519948[0]);
                En::Run(arg1);
                ((beNDMWLoadIntf2DataSelIntf *)a8.p)->_commonIntf = (int)igProperty_FindByName(arg1->_dataList, DAT_00585be0[0], &DAT_00519698[0]);
                En::Run(arg1);
                ((beNDMWLoadIntf2DataSelIntf *)a8.p)->_mesWin = (int)igProperty_FindByName(arg1->_dataList, DAT_00585be0[0], &DAT_00519688[0]);
                En::Run(arg1);
                ((beNDMWLoadIntf2DataSelIntf *)a8.p)->_statDisp = (int)igProperty_FindByName(arg1->_dataList, DAT_00585be0[0], &DAT_005196a8[0]);
                ObjectList_AppendRetained(arg1->_dataList, a8.p);
            }
        }
        return 1;
    }
    if (arg1->_dataList == 0) {
        return 1;
    }
    En::Run(arg1);
    beNDMWSaveIntfCtrlData *p = (beNDMWSaveIntfCtrlData *)igProperty_FindByName(arg1->_dataList, DAT_00585be0[0], &DAT_00519670[0]);
    switch (v) {
    case 1:
        ObjectList_AppendRetained(arg1->_dataList, beMessenger_GetObject(arg0->_messenger, 0));
        return 1;
    case 2:
        if (beMessenger_GetIntCount(arg0->_messenger) == 0) {
            beMessenger_AppendInt(arg0->_messenger, 0);
        }
        if (p->_isEntry == 1) {
            beMessenger_SetInt(arg0->_messenger, 0, beMessenger_GetInt(arg0->_messenger, 0) + 1);
        }
        return 1;
    case 3:
        if (beMessenger_GetIntCount(arg0->_messenger) == 0) {
            beMessenger_AppendInt(arg0->_messenger, 0);
        }
        if (p->_isRdy == 1) {
            beMessenger_SetInt(arg0->_messenger, 0, beMessenger_GetInt(arg0->_messenger, 0) + 1);
        }
        return 1;
    case 4:
        p->_isCtrl = 1;
        return 1;
    case 5:
        p->_isCtrl = 0;
        return 1;
    case 6:
        En::Run(arg1);
        {
            PropX *q = (PropX *)igProperty_FindByName(arg1->_dataList, DAT_00585be0[0], &DAT_00519698[0]);
            if (q->f40->f16[arg1->_ramNo]->f13 != 1) {
                beMessenger_SelectGroup(arg0->_messenger, &DAT_005196e0[0]);
                beMessenger_AppendInt(arg0->_messenger, arg1->_ramNo);
                beMessenger_DispatchSelected(arg0->_messenger, &DAT_00519958[0]);
            }
        }
        return 1;
    default:
        return 0;
    }
}

int Gap__Bec__beNDMWSaveIntf__vfunc_20(void)
{
    return g_beNDMWSaveIntf_metaObject[0];
}

