#include "dw4/reflected.h"
/* reference-counted engine object header: refcount word at +4 */
struct RC { int vt; int rc; };
/* message record: only the enum value name at +20 is read; its class is not established */
struct MsgArg { char pad20[20]; int f20; };
/* matching construct: element of the list reached through the COMMONINTF object (+40 -> +16 array of flag holders); no reflected class established */
struct PropZ { char pad13[13]; unsigned char f13; };
struct PropY { char pad16[16]; struct PropZ **f16; };
struct PropX { char pad40[40]; struct PropY *f40; };
extern "C" {
int FUN_00236f80(...);
void *beBaseInfoDataList_Create(...);
void *FUN_003bc940(...);
int FUN_003bcc20(...);
void *FUN_003c2e60(...);
void *FUN_003c3560(...);
void *FUN_003c3900(...);
void *FUN_003c3e40(...);
void *FUN_003c6b00(...);
void *beNDMWLoadIntf2ComMdlCtrl_Create(...);
void *beNDMWLoadIntf2TextOrder_Create(...);
int FUN_003d9de0(...);
int Memory_GetAllocatorBySelector(...);
int ObjectList_AppendRetained(...);
int beMessenger_AppendInt(...);
int beMessenger_DispatchSelected(...);
int beMessenger_GetInt(...);
int beMessenger_GetIntCount(...);
void *beMessenger_GetObject(...);
unsigned int beMessenger_ResolveEnumValue(...);
int beMessenger_SelectGroup(...);
int beMessenger_SendNamed(...);
int beMessenger_SetInt(...);
int igObject_Destroy(...);
int igObject_GetAllocator(...);
void *igProperty_FindByName(...);
extern int DAT_004cf640[4];
extern int DAT_004cf644[4];
extern int DAT_004cf648[4];
extern int DAT_00519670[4];
extern int DAT_00519678[4];
extern int DAT_00519688[4];
extern int DAT_00519698[4];
extern int DAT_005196a8[4];
extern int DAT_005196e0[4];
extern int DAT_00519928[4];
extern int DAT_00519938[4];
extern int DAT_00519948[4];
extern int DAT_00519958[4];
extern int DAT_00585be0[4];
extern int DAT_00587110[4];
extern int DAT_00587d08[4];
extern int DAT_00588518[4];
extern int DAT_00589208[4];
extern unsigned char GPR_00554c14;
int Gap__Bec__beNDMWSaveIntf__vfunc_34(beNDMWSaveIntf *arg0, beBaseInfoRam *arg1, MsgArg *arg2);
}
/* Owning stack reference to a request or window object; one instantiation per object class (0 the data list, 1 the control data,
 * 2 text order, 3 model control, 4 message window, 5 slot selector, 6 state control, 7 state data, 8 data selector), so the out-of-line
 * destructor copies the exception table names stay distinct (config/SLUS-20836/unit-objects.json emitted/duplicates __dt__5RP<k>Fv). */
template <int kind> struct RP {
    RC *p;
    RP(RC *q) : p(q) {}
    ~RP() { RC *q = p; if (q != 0) { q->rc = q->rc - 1; if ((q->rc & 0x7fffff) == 0) igObject_Destroy(q); } }
};
/* matching construct: inlined get-or-create of arg1's list; its own stack smart-pointer slot per expansion */
/* matching construct: the holder destructor nested in this inline function is only inlined (as retail has it) with the inline depth raised */
#pragma inline_depth(8)
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
            arg0->_system_ = FUN_00236f80(arg0->_insight, DAT_00587d08[0]);
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
                o4->_lua = FUN_00236f80(arg0->_insight, DAT_00589208[0]);
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
                ((beNDMWLoadIntf2MesWin *)bc.p)->_padManager = FUN_00236f80(arg0->_insight, DAT_00588518[0]);
                ObjectList_AppendRetained(arg1->_dataList, bc.p);
                En::Run(arg1);
                ((beNDMWLoadIntf2MesWin *)bc.p)->_textOrder = (int)igProperty_FindByName(arg1->_dataList, DAT_00585be0[0], &DAT_00519948[0]);
            }
            {
                int base = igObject_GetAllocator(arg0); int a; if (GPR_00554c14 != 0) { a = base; } else { a = Memory_GetAllocatorBySelector(DAT_00587110[0]); }
                RP<5> b8((RC *)FUN_003c2e60(a));
                ((beNDMWLoadIntf2SelSlot *)b8.p)->_ramNo = arg1->_ramNo;
                ((beNDMWLoadIntf2SelSlot *)b8.p)->_messenger = arg0->_messenger;
                ((beNDMWLoadIntf2SelSlot *)b8.p)->_padManager = FUN_00236f80(arg0->_insight, DAT_00588518[0]);
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
                ((beNDMWLoadIntf2DataSelIntf *)a8.p)->_padManager = FUN_00236f80(arg0->_insight, DAT_00588518[0]);
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
