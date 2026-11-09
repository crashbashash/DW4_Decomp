#include "dw4/reflected.h"
#pragma inline_depth(1)
extern "C" {
struct DW4Sret4 { int v; DW4Sret4(const DW4Sret4 &o):v(o.v) {} };
int DataList_GetData_003e9090(...);
void *DataList_GetWordAt_003e9240(...);
int FUN_002294f0(...);
void *FUN_003c6360(...);
void *beNDMWDegiData_Create(...);
int FUN_003d9e10(...);
int FUN_003d9e70(...);
int FUN_003d9e90(...);
int FUN_003da7c0(...);
int FUN_003dafb0(...);
int beNDMWLoadIntf2DataSelIntf__ClearStatesFrom(...);
int FUN_003db060(...);
int beNDMWLoadIntf2DataSelIntf__UpdateSelection(...);
int FUN_003dbf90(...);
int FUN_003dc2e0(...);
int FUN_003dc590(...);
int FUN_003dcab0(...);
int FUN_003dcc60(...);
int FUN_003dd160(...);
int FUN_003dd440(...);
int FUN_003dd6d0(...);
int FUN_003e0b80(...);
int beNDMWLoadIntf2SelSlot__Init(...);
int beNDMWLoadIntf2SelSlot__Open(...);
int beNDMWLoadIntf2SelSlot__UpdateSelection(...);
int beNDMWLoadIntf2SelSlot__PublishCursor(...);
int beNDMWLoadIntf2SelSlot__Close(...);
int beNDMWLoadIntf2SelSlot__RefreshSlotMarks(...);
int beNDMWLoadIntf2ComMdlCtrl__IsOpenQueueEmpty(...);
int beNDMWLoadIntf2ComMdlCtrl__Close(...);
int beNDMWLoadIntf2ComMdlCtrl__IsCloseQueueEmpty(...);
int beNDMWLoadIntf2ComMdlCtrl__Poll(...);
int beNDMWLoadSavePlWork__SetIsCtrl(...);
int beNDMWLoadSavePlWork__GetIsRdy(...);
int beNDMWLoadSavePlWork__GetIsEntry(...);
int FUN_003e9220(...);
void *FUN_003e9280(...);
int FUN_003e92a0(...);
DW4Sret4 FUN_003e9360(...);
int FUN_003e93b0(...);
int beNDMWLoadIntf2MesWin__Update(...);
int beNDMWLoadIntf2MesWin__RequestOpen(...);
int beNDMWLoadIntf2MesWin__RequestClose(...);
int FUN_003ecad0(...);
int FUN_003ecae0(...);
int FUN_003ecb00(...);
int FUN_003ecb20(...);
int beNDMWLoadIntf2MesWin__GetIsCtrl(...);
int FUN_003ecb80(...);
int beNDMWLoadIntf2MesWin__RequestMesErase(...);
int FUN_003ecba0(...);
int beNDMWLoadIntf2MesWin__EndSystemMessage(...);
int FUN_003ecdc0(...);
int FUN_003ed050(...);
int FUN_003ed2e0(...);
int beNDMWLoadCtrl2CommonIntf__StepReadMedia(...);
int FUN_003edc20(...);
int beNDMWLoadCtrl2CommonIntf__StepFormatMemoryCard(...);
int FUN_003ee250(...);
int beNDMWLoadCtrl2CommonIntf__RemoveAccessPlayer(...);
int beNDMWDegiData__LoadFromProperties(...);
int FUN_0040c180(...);
int List_Resize(...);
int Memory_GetAllocatorBySelector(...);
int Memory_SelectAllocator_003e9370(...);
int ObjectList_AppendRetained(...);
void *ObjectList_GetAt_003e9260(...);
int ObjectRef_Destruct_0033e9c0(...);
int ObjectRef_Release_003e9110(...);
int beMessenger_AppendInt(...);
int beMessenger_AppendString(...);
int beMessenger_DispatchSelected(...);
int beMessenger_GetObject(...);
int beMessenger_SelectGroup(...);
void *bePadManager_GetPadForPlayer(...);
int igObject_GetAllocator(...);
void *igProperty_GetRecordByte(...);
extern int * DAT_004cec70[4];
extern int DAT_00519670[4];
extern int DAT_00519678[4];
extern int DAT_00519688[4];
extern int DAT_00519690[4];
extern int DAT_00519698[4];
extern int DAT_005196a8[4];
extern int DAT_005196b8[4];
extern int DAT_005196c8[4];
extern int DAT_005196d8[4];
extern int DAT_005196e0[4];
extern int DAT_005196e8[4];
extern int DAT_005196f8[4];
extern int DAT_00519700[4];
extern int DAT_00519710[4];
extern int DAT_00519720[4];
extern int DAT_00519730[4];
extern int DAT_00519740[4];
extern int DAT_00585be0[4];
extern int DAT_00587110[4];
extern unsigned char GPR_00554c14;
extern "C" int igObject_Destroy(void *);
struct RecoveryTarget { int word0; int references;
 static void release(RecoveryTarget *object) {
  if(object) {
   --object->references;
   if(((unsigned long long)(long long)object->references & 0x7fffffULL)==0)
    igObject_Destroy(object);
  }
 }
};
template<int I> class RecoveryRef { public:
 void *value;
 RecoveryRef(void *p):value(p) {}
 ~RecoveryRef() { RecoveryTarget::release((RecoveryTarget *)value); }
};
struct DW4ListRec { int w0; int w1; int count; int cap; };
struct DW4SelAlloc { static int Get(const int *sel, int fb) { if (GPR_00554c14) return fb; else return Memory_GetAllocatorBySelector(*sel); } };
struct DW4Vec16 { int a, b, c, d; DW4Vec16(const DW4Vec16 &o); };
int beNDMWLoadIntf2ComMdlCtrl__StartAt(void *, int, void *, void *, DW4Vec16 &, int);
class RecoveryCopiedRef { public: void *value; RecoveryCopiedRef(const DW4Sret4 &source); ~RecoveryCopiedRef(); };
int *ObjectRef_Assign_003e92b0(void *, const RecoveryCopiedRef &);
struct DW4Fresh { static int *Assign(void *obj, int alloc) { RecoveryCopiedRef c(FUN_003e9360(Memory_SelectAllocator_003e9370(&DAT_00587110[0], alloc))); return ObjectRef_Assign_003e92b0(obj, c); } };
struct SaveHost { char pad0[8]; int player; char pad12[28]; int ref; };
void Gap__Bec__beNDMWSaveIntf__vfunc_31(beNDMWSaveIntf *arg0, SaveHost *arg1) {
    beNDMWSaveIntfCtrlData *temp_s3;
    void *temp_s7;
    void *temp_s2;
    beNDMWLoadIntf2SelSlot *temp_s1;
    beNDMWLoadCtrl2CommonIntf *temp_s0;
    beNDMWLoadIntf2DegiStateCtrl *temp_s8;
    beNDMWLoadIntf2DataSelIntf *temp_s5;
    void *temp_s6;
    int var_s5;
    int var_s1_3;
    int var_s0;
    int var_s5_2;
    int var_s2_3;
    int var_s1_4;
    int var_s5_3;
    int var_s6;
    int var_s1_5;
    int var_s5_4;
    int var_s6_2;
    int var_s1_6;
    int var_s5_5;
    int var_s6_3;
    int var_s1_7;
    int var_s1_8;
    int var_s1_9;
    void *sp11C;
    void *sp118;
    int spB0;
    unsigned char spA0;
    int temp_a0;
    int temp_a0_10;
    int temp_a0_15;
    int temp_a0_16;
    int temp_a0_17;
    int temp_a0_18;
    int temp_a0_20;
    int temp_a0_22;
    int temp_a0_2;
    int temp_a0_3;
    int temp_a0_5;
    int temp_a0_7;
    int temp_a1;
    int temp_a1_2;
    int temp_a2;
    int temp_s0_2;
    int temp_s0_3;
    int temp_s4;
    int temp_s1_2;
    int temp_s4_2;
    int temp_s2_2;
    int temp_v0_15;
    int temp_v0_16;
    int temp_v0_17;
    int temp_v0_19;
    int temp_v0_20;
    int temp_v0_21;
    int temp_v0_22;
    int temp_v0_23;
    int temp_v0_24;
    int temp_v0_25;
    int temp_v0_26;
    int temp_v0_27;
    int temp_v0_28;
    int temp_v0_29;
    int temp_v0_30;
    int temp_v0_31;
    int temp_v0_3;
    int temp_v0_4;
    int temp_v0_5;
    int temp_v0_6;
    int temp_v0_7;
    int temp_v0_8;
    int temp_v0_9;
    int temp_v1_10;
    int temp_v1_11;
    int temp_v1_12;
    int temp_v1_15;
    int temp_v1_16;
    int temp_v1_18;
    int temp_v1_19;
    int temp_v1_20;
    int temp_v1_21;
    int temp_v1_24;
    int temp_v1_25;
    int temp_v1_26;
    int temp_v1_28;
    int temp_v1_2;
    int temp_v1_31;
    unsigned int temp_v1_32;
    int temp_v1_33;
    int temp_v1_35;
    unsigned int temp_v1_36;
    int temp_v1_37;
    int temp_v1_39;
    int temp_v1_40;
    int temp_v1_41;
    int temp_v1_42;
    int temp_v1_43;
    int temp_v1_44;
    int temp_v1_45;
    int temp_v1_46;
    int temp_v1_47;
    int temp_v1_48;
    int temp_v1_49;
    int temp_v1_4;
    int temp_v1_50;
    int temp_v1_51;
    int temp_v1_52;
    int temp_v1_5;
    int temp_v1_7;
    int temp_v1_9;
    int var_a1;
    int var_a1_10;
    int var_a1_11;
    int var_a1_12;
    int var_a1_13;
    int var_a1_14;
    int var_a1_15;
    int var_a1_16;
    int var_a1_17;
    int var_a1_18;
    int var_a1_19;
    int var_a1_20;
    int var_a1_2;
    int var_a1_3;
    int var_a1_4;
    int var_a1_5;
    int var_a1_6;
    int var_a1_7;
    int var_a1_8;
    int var_a1_9;
    int var_a3;
    int var_a3_2;
    int var_a4;
    int var_a4_2;
    int var_s1;
    int var_s1_10;
    int var_s1_2;
    unsigned char var_s2;
    unsigned char var_s2_2;
    int var_s2_5;
    int var_s2_6;
    int var_s5_6;
    int var_v0;
    int var_v0_2;
    unsigned int temp_a0_11;
    unsigned int temp_a0_12;
    unsigned int temp_a0_13;
    unsigned int temp_a0_14;
    unsigned int temp_a0_19;
    unsigned int temp_a0_21;
    unsigned int temp_a0_4;
    unsigned int temp_a0_6;
    unsigned int temp_a0_8;
    unsigned int temp_a0_9;
    unsigned int temp_v1;
    unsigned int temp_v1_13;
    unsigned int temp_v1_14;
    unsigned int temp_v1_17;
    unsigned int temp_v1_22;
    unsigned int temp_v1_23;
    unsigned int temp_v1_27;
    unsigned int temp_v1_29;
    unsigned int temp_v1_30;
    unsigned int temp_v1_34;
    unsigned int temp_v1_38;
    unsigned int temp_v1_3;
    unsigned int temp_v1_6;
    unsigned int temp_v1_8;
    void *temp_a0_23;
    void *temp_s0_4;
    void *temp_s0_5;
    DW4ListRec *temp_s0_6;
    DW4ListRec *temp_s1_3;
    beNDMWLoadSavePlWork *temp_s5_2;
    int temp_s3_2;
    void *temp_s6_2;
    void *temp_s7_2;
    void *temp_s7_3;
    void *temp_s7_4;
    beNDMWLoadSavePlWork *temp_v0;
    beNDMWLoadSavePlWork *temp_v0_10;
    beNDMWLoadSavePlWork *temp_v0_11;
    beNDMWLoadSavePlWork *temp_v0_12;
    beNDMWLoadSavePlWork *temp_v0_13;
    beNDMWLoadSavePlWork *temp_v0_14;
    beNDMWLoadSavePlWork *temp_v0_18;
    beNDMWLoadSavePlWork *temp_v0_2;
    beNDMWLoadSavePlWork *temp_v0_32;
    beNDMWLoadSavePlWork *temp_v0_33;
    void *var_s2_4;

    int tref;
    if (arg1->ref != 0) {
        tref = FUN_003e93b0(&arg1->ref);
        if (tref == 0) {
            DW4Fresh::Assign(&arg1->ref, igObject_GetAllocator(arg1));
        }
        temp_s3 = (beNDMWSaveIntfCtrlData *)(FUN_003e9280(FUN_003e92a0(&arg1->ref), DAT_00585be0[0], &DAT_00519670[0]));
        tref = FUN_003e93b0(&arg1->ref);
        if (tref == 0) {
            DW4Fresh::Assign(&arg1->ref, igObject_GetAllocator(arg1));
        }
        temp_s7 = (void *)(FUN_003e9280(FUN_003e92a0(&arg1->ref), DAT_00585be0[0], &DAT_00519678[0]));
        tref = FUN_003e93b0(&arg1->ref);
        if (tref == 0) {
            DW4Fresh::Assign(&arg1->ref, igObject_GetAllocator(arg1));
        }
        temp_s2 = (void *)(FUN_003e9280(FUN_003e92a0(&arg1->ref), DAT_00585be0[0], &DAT_00519688[0]));
        tref = FUN_003e93b0(&arg1->ref);
        if (tref == 0) {
            DW4Fresh::Assign(&arg1->ref, igObject_GetAllocator(arg1));
        }
        temp_s1 = (beNDMWLoadIntf2SelSlot *)(FUN_003e9280(FUN_003e92a0(&arg1->ref), DAT_00585be0[0], &DAT_00519690[0]));
        tref = FUN_003e93b0(&arg1->ref);
        if (tref == 0) {
            DW4Fresh::Assign(&arg1->ref, igObject_GetAllocator(arg1));
        }
        temp_s0 = (beNDMWLoadCtrl2CommonIntf *)(FUN_003e9280(FUN_003e92a0(&arg1->ref), DAT_00585be0[0], &DAT_00519698[0]));
        tref = FUN_003e93b0(&arg1->ref);
        if (tref == 0) {
            DW4Fresh::Assign(&arg1->ref, igObject_GetAllocator(arg1));
        }
        temp_s8 = (beNDMWLoadIntf2DegiStateCtrl *)(FUN_003e9280(FUN_003e92a0(&arg1->ref), DAT_00585be0[0], &DAT_005196a8[0]));
        tref = FUN_003e93b0(&arg1->ref);
        if (tref == 0) {
            DW4Fresh::Assign(&arg1->ref, igObject_GetAllocator(arg1));
        }
        temp_s5 = (beNDMWLoadIntf2DataSelIntf *)(FUN_003e9280(FUN_003e92a0(&arg1->ref), DAT_00585be0[0], &DAT_005196b8[0]));
        beNDMWLoadIntf2ComMdlCtrl__Poll(temp_s7);
        beNDMWLoadIntf2MesWin__Update(temp_s2);
        spB0 = 0;
        if (((beNDMWLoadSavePlWork *)(ObjectList_GetAt_003e9260(temp_s0->_flagWork, arg1->player)))->_isCtrl == 1) {
            spB0 = ((bePadData *)(bePadManager_GetPadForPlayer(arg0->_padManager, arg1->player)))->_trigger;
        }
        temp_v1 = ((beNDMWLoadSavePlWork *)(ObjectList_GetAt_003e9260(temp_s0->_flagWork, arg1->player)))->_sysStat0;
        switch (temp_v1) {
        case 1:
            spA0 = 0;
            temp_a0 = ((beNDMWLoadSavePlWork *)(ObjectList_GetAt_003e9260(temp_s0->_flagWork, arg1->player)))->_sysStat1;
            switch (temp_a0) {
            case 0:
                FUN_003ecba0(temp_s2, (arg1->player << 0x10) | 0x51C);
                temp_v0 = (beNDMWLoadSavePlWork *)(DataList_GetWordAt_003e9240(temp_s0->_flagWork, arg1->player));
                temp_v0->_sysStat1 = 1;
                temp_v0->_sysStat3 = 0;
                temp_v0->_sysStat2 = 0;
                break;
            case 1:
                temp_v0_2 = (beNDMWLoadSavePlWork *)(ObjectList_GetAt_003e9260(temp_s0->_flagWork, arg1->player));
                temp_v1_2 = temp_v0_2->_sysCount0 - 1;
                temp_v0_2->_sysCount0 = temp_v1_2;
                if (temp_v1_2 <= 0) {
                    { beNDMWLoadSavePlWork *r_ = (beNDMWLoadSavePlWork *)ObjectList_GetAt_003e9260(temp_s0->_flagWork, arg1->player); r_->_sysCount0 = 0; }
                    spA0 = 1;
                }
                break;
            }
            if (spA0 != 1) {
            case 0:
                temp_v1_3 = temp_s3->_st0;
                switch (temp_v1_3) {
                case 0:
                    temp_v1_4 = temp_s3->_st1;
                    switch (temp_v1_4) {
                    default:
                            DW4Vec16 spD0(*(DW4Vec16 *)&((beNDMWSaveIntfComMdlCtrl *)temp_s7)->_pos);
                            beNDMWLoadIntf2ComMdlCtrl__StartAt(temp_s7, arg1->player, &DAT_005196c8[0], &DAT_005196d8[0], spD0, 1);
                            temp_s3->_st1 = (temp_s3->_st1 + 1);
                            temp_s3->_st3 = 0;
                            temp_s3->_st2 = 0;
                            return;
                                            case 1:
                        if ((beNDMWLoadIntf2ComMdlCtrl__IsOpenQueueEmpty(temp_s7) & 0xFF) == 1) {
                            temp_s3->_st1 = (temp_s3->_st1 + 1);
                            temp_s3->_st3 = 0;
                            temp_s3->_st2 = 0;
                            return;
                        }
                                            break;
                    case 2:
                        beMessenger_SelectGroup(arg0->_messenger, &DAT_005196e0[0]);
                        beMessenger_AppendInt(arg0->_messenger, arg1->player);
                        beMessenger_DispatchSelected(arg0->_messenger, &DAT_005196e8[0]);
                        temp_v0_3 = beMessenger_GetObject(arg0->_messenger, 0);
                        if (*(unsigned char *)((char *)(igProperty_GetRecordByte(temp_v0_3, &DAT_005196f8[0])) + 12) == 1) {
                            beMessenger_SelectGroup(arg0->_messenger, &DAT_005196e0[0]);
                            beMessenger_AppendInt(arg0->_messenger, arg1->player);
                            beMessenger_DispatchSelected(arg0->_messenger, &DAT_00519700[0]);
                            beNDMWDegiData__LoadFromProperties(ObjectList_GetAt_003e9260(temp_s0->_gameUseData, arg1->player), temp_v0_3);
                            temp_s3->_st0 = 1;
                            temp_s3->_st3 = 0;
                            temp_s3->_st2 = 0;
                            temp_s3->_st1 = 0;
                            { beNDMWLoadSavePlWork *r_ = (beNDMWLoadSavePlWork *)ObjectList_GetAt_003e9260(temp_s0->_flagWork, arg1->player); r_->_isRdy = 0; }
                            { beNDMWLoadSavePlWork *r_ = (beNDMWLoadSavePlWork *)ObjectList_GetAt_003e9260(temp_s0->_flagWork, arg1->player); r_->_isEntry = 1; }
                            return;
                        }
                        temp_a1 = arg1->player;
                        if (temp_a1 == 0) {
                            beMessenger_SelectGroup(arg0->_messenger, &DAT_005196e0[0]);
                            beMessenger_AppendInt(arg0->_messenger, arg1->player);
                            beMessenger_AppendString(arg0->_messenger, DAT_004cec70[0]);
                            beMessenger_AppendString(arg0->_messenger, &DAT_00519710[0]);
                            beMessenger_DispatchSelected(arg0->_messenger, &DAT_00519720[0]);
                            beMessenger_SelectGroup(arg0->_messenger, &DAT_005196e0[0]);
                            beMessenger_AppendInt(arg0->_messenger, arg1->player);
                            beMessenger_DispatchSelected(arg0->_messenger, &DAT_005196e8[0]);
                            temp_s0_2 = beMessenger_GetObject(arg0->_messenger, 0);
                            beNDMWDegiData__LoadFromProperties(ObjectList_GetAt_003e9260(temp_s0->_gameUseData, arg1->player), temp_s0_2);
                            return;
                        }
                        { beNDMWLoadSavePlWork *r_ = (beNDMWLoadSavePlWork *)ObjectList_GetAt_003e9260(temp_s0->_flagWork, temp_a1); r_->_isEntry = 0; }
                        temp_s3->_st0 = 9;
                        temp_s3->_st3 = 0;
                        temp_s3->_st2 = 0;
                        temp_s3->_st1 = 0;
                        return;
                                            break;
                    }
                    break;
                case 1:
                    temp_a0_2 = temp_s3->_st1;
                    switch (temp_a0_2) {
                    case 0:
                        DW4Vec16 spC0(*(DW4Vec16 *)&((beNDMWSaveIntfComMdlCtrl *)temp_s7)->_pos);
                        beNDMWLoadIntf2ComMdlCtrl__StartAt(temp_s7, arg1->player, &DAT_00519730[0], &DAT_005196d8[0], spC0, 1);
                        beNDMWLoadIntf2MesWin__RequestOpen(temp_s2);
                        temp_s3->_st1 = (temp_s3->_st1 + 1);
                        temp_s3->_st3 = 0;
                        temp_s3->_st2 = 0;
                        return;
                    case 1:
                        if ((beNDMWLoadIntf2ComMdlCtrl__IsOpenQueueEmpty(temp_s7) & 0xFF) == 1) {
                            beNDMWLoadIntf2MesWin__RequestMesErase(temp_s2);
                            temp_s3->_st0 = 2;
                            temp_s3->_st3 = 0;
                            temp_s3->_st2 = 0;
                            temp_s3->_st1 = 0;
                            return;
                        }
                        break;
                    }
                    break;
                case 2:
                    temp_a0_3 = temp_s3->_st1;
                    switch (temp_a0_3) {
                    default:
                            FUN_003ecae0(temp_s2, (arg1->player << 0x10) | 0x502, 0);
                            temp_s3->_st1 = (temp_s3->_st1 + 1);
                            temp_s3->_st3 = 0;
                            temp_s3->_st2 = 0;
                            return;
                                            case 1:
                        if (!(beNDMWLoadIntf2MesWin__GetIsCtrl(temp_s2) & 0xFF)) {
                            temp_v0_4 = FUN_003ecb80(temp_s2);
                            switch (temp_v0_4) {
                            case 0:
                                temp_s3->_st0 = 4;
                                temp_s3->_st3 = 0;
                                temp_s3->_st2 = 0;
                                temp_s3->_st1 = 0;
                                return;
                            case 1:
                                temp_s3->_st1 = (temp_s3->_st1 + 1);
                                temp_s3->_st3 = 0;
                                temp_s3->_st2 = 0;
                                return;
                            }
                        }
                                            break;
                    case 2:
                        temp_a0_4 = temp_s3->_st2;
                        switch (temp_a0_4) {
                        case 0:
                            temp_s0_3 = arg1->player;
                            temp_a0_23 = ObjectList_GetAt_003e9260(temp_s8->_statDataList, 0);
                            FUN_003d9e10(temp_a0_23, 1, temp_s0_3);
                            temp_s3->_st2 = (temp_s3->_st2 + 1);
                            temp_s3->_st3 = 0;
                            return;
                        case 1:
                            if ((FUN_003da7c0(ObjectList_GetAt_003e9260(temp_s8->_statDataList, 0)) & 0xFF) == 1) {
                                if (arg1->player == 0) {
                                    var_s1 = 1;
                                    var_s2 = 0;
                                    do {
                                        if (((beNDMWLoadSavePlWork *)(ObjectList_GetAt_003e9260(temp_s0->_flagWork, var_s1)))->_isEntry == 1) {
                                            var_s2 = 1;
                                            break;
                                        }
                                        var_s1 += 1;
                                    } while (var_s1 < 4);
                                    if ((var_s2 & 0xFF) == 1) {
                                        temp_s3->_st0 = 8;
                                        temp_s3->_st3 = 0;
                                        temp_s3->_st2 = 0;
                                        temp_s3->_st1 = 0;
                                        return;
                                    }
                                    temp_s3->_st0 = 7;
                                    temp_s3->_st3 = 0;
                                    temp_s3->_st2 = 0;
                                    temp_s3->_st1 = 0;
                                    return;
                                }
                                temp_s3->_st0 = 7;
                                temp_s3->_st3 = 0;
                                temp_s3->_st2 = 0;
                                temp_s3->_st1 = 0;
                                return;
                            }
                            break;
                        }
                                            break;
                    }
                    break;
                case 4:
                    temp_v1_5 = temp_s3->_st1;
                    switch (temp_v1_5) {
                    case 0:
                        temp_v1_6 = temp_s3->_st2;
                        switch (temp_v1_6) {
                        case 0:
                            beNDMWLoadCtrl2CommonIntf__RemoveAccessPlayer(temp_s0, arg1->player, 2);
                            beNDMWLoadIntf2SelSlot__Init(temp_s1);
                            temp_s1->_st0 = 0;
                            temp_s1->_st3 = 0;
                            temp_s1->_st2 = 0;
                            temp_s1->_st1 = 0;
                            temp_s3->_st2 = (temp_s3->_st2 + 1);
                            temp_s3->_st3 = 0;
                            return;
                        case 1:
                            if ((beNDMWLoadIntf2SelSlot__Open(temp_s1, -1, 2) & 0xFF) == 1) {
                                temp_v1_7 = temp_s0->_kindHard;
                                var_a1 = -1;
                                switch (temp_v1_7) {
                                case 0:
                                    var_a1 = (arg1->player << 0x10) | 0x1024;
                                    break;
                                case 1:
                                    var_a1 = (arg1->player << 0x10) | 0x2024;
                                    break;
                                case 2:
                                    var_a1 = (arg1->player << 0x10) | 0x3024;
                                    break;
                                }
                                FUN_003ecad0(temp_s2, var_a1);
                                temp_s1->_st0 = 1;
                                temp_s1->_st3 = 0;
                                temp_s1->_st2 = 0;
                                temp_s1->_st1 = 0;
                                temp_s3->_st1 = (temp_s3->_st1 + 1);
                                temp_s3->_st3 = 0;
                                temp_s3->_st2 = 0;
                                return;
                            }
                            break;
                        }
                        break;
                    case 1:
                        temp_v1_8 = temp_s3->_st2;
                        switch (temp_v1_8) {
                        case 0:
                            if ((beNDMWLoadIntf2SelSlot__UpdateSelection(temp_s1, ((beNDMWLoadSavePlWork *)(ObjectList_GetAt_003e9260(temp_s0->_flagWork, arg1->player)))->_isCtrl, 1) & 0xFF) == 1) {
                                if (temp_s1->_isReOpenReq == 1) {
                                    temp_s3->_st1 = (temp_s3->_st1 + 1);
                                    temp_s3->_st3 = 0;
                                    temp_s3->_st2 = 0;
                                    return;
                                }
                                if (temp_s1->_isCansel == 1) {
                                    temp_s3->_st1 = (temp_s3->_st1 + 1);
                                    temp_s3->_st3 = 0;
                                    temp_s3->_st2 = 0;
                                    return;
                                }
                                temp_s3->_st2 = (temp_s3->_st2 + 1);
                                temp_s3->_st3 = 0;
                                return;
                            }
                            break;
                        case 1:
                            temp_v1_9 = temp_s3->_st3;
                            switch (temp_v1_9) {
                            case 0:
                                temp_v0_5 = temp_s0->_kindHard;
                                var_a1_2 = -1;
                                switch (temp_v0_5) {
                                case 0:
                                    var_a1_2 = (arg1->player << 0x10) | 0x1004;
                                    break;
                                case 1:
                                    var_a1_2 = (arg1->player << 0x10) | 0x2004;
                                    break;
                                case 2:
                                    var_a1_2 = (arg1->player << 0x10) | 0x3004;
                                    break;
                                }
                                FUN_003ecad0(temp_s2, var_a1_2);
                                FUN_003ee250(temp_s0, arg1->player, 4);
                                temp_s3->_st3 = (temp_s3->_st3 + 1);
                                return;
                            case 1:
                                temp_a0_5 = ((beNDMWLoadSavePlWork *)(ObjectList_GetAt_003e9260(temp_s0->_flagWork, arg1->player)))->_utilReturn;
                                switch (temp_a0_5) {
                                case 0:
                                    temp_s3->_st1 = (temp_s3->_st1 + 1);
                                    temp_s3->_st3 = 0;
                                    temp_s3->_st2 = 0;
                                    return;
                                case 1:
                                case 2:
                                    temp_v1_10 = temp_s0->_kindHard;
                                    var_a1_3 = -1;
                                    switch (temp_v1_10) {
                                    case 0:
                                        var_a1_3 = (arg1->player << 0x10) | 0x1024;
                                        break;
                                    case 1:
                                        var_a1_3 = (arg1->player << 0x10) | 0x2024;
                                        break;
                                    case 2:
                                        var_a1_3 = (arg1->player << 0x10) | 0x3024;
                                        break;
                                    }
                                    FUN_003ecad0(temp_s2, var_a1_3);
                                    beNDMWLoadIntf2SelSlot__PublishCursor(temp_s1);
                                    temp_s3->_st1 = 1;
                                    temp_s3->_st3 = 0;
                                    temp_s3->_st2 = 0;
                                    return;
                                case 4:
                                    temp_v1_11 = temp_s0->_kindHard;
                                    var_a1_4 = -1;
                                    switch (temp_v1_11) {
                                    case 0:
                                        var_a1_4 = (arg1->player << 0x10) | 0x1024;
                                        break;
                                    case 1:
                                        var_a1_4 = (arg1->player << 0x10) | 0x2024;
                                        break;
                                    case 2:
                                        var_a1_4 = (arg1->player << 0x10) | 0x3024;
                                        break;
                                    }
                                    FUN_003ecad0(temp_s2, var_a1_4);
                                    beNDMWLoadIntf2SelSlot__PublishCursor(temp_s1);
                                    temp_s3->_st1 = 1;
                                    temp_s3->_st3 = 0;
                                    temp_s3->_st2 = 0;
                                    return;
                                }
                                break;
                            }
                            break;
                        }
                        break;
                    case 2:
                        temp_a0_6 = temp_s3->_st2;
                        switch (temp_a0_6) {
                        case 0:
                            temp_s1->_st0 = 2;
                            temp_s1->_st3 = 0;
                            temp_s1->_st2 = 0;
                            temp_s1->_st1 = 0;
                            temp_s3->_st2 = (temp_s3->_st2 + 1);
                            temp_s3->_st3 = 0;
                            return;
                        case 1:
                            if ((beNDMWLoadIntf2SelSlot__Close(temp_s1) & 0xFF) == 1) {
                                if (temp_s1->_isReOpenReq == 1) {
                                    temp_s3->_st0 = 4;
                                    temp_s3->_st3 = 0;
                                    temp_s3->_st2 = 0;
                                    temp_s3->_st1 = 0;
                                    return;
                                }
                                if (temp_s1->_isCansel == 1) {
                                    temp_s3->_st0 = 2;
                                    temp_s3->_st3 = 0;
                                    temp_s3->_st2 = 0;
                                    temp_s3->_st1 = 0;
                                    return;
                                }
                                temp_s3->_st0 = 5;
                                temp_s3->_st3 = 0;
                                temp_s3->_st2 = 0;
                                temp_s3->_st1 = 0;
                                return;
                            }
                            break;
                        }
                        break;
                    }
                    break;
                case 5:
                    temp_v1_12 = temp_s3->_st1;
                    switch (temp_v1_12) {
                    case 0:
                        FUN_003dafb0(temp_s5, arg1->player, 1);
                        temp_s3->_st1 = (temp_s3->_st1 + 1);
                        temp_s3->_st3 = 0;
                        temp_s3->_st2 = 0;
                        return;
                    case 1:
                        temp_v1_13 = temp_s3->_st2;
                        switch (temp_v1_13) {
                        case 0:
                            beNDMWLoadIntf2DataSelIntf__ClearStatesFrom(temp_s5, 0, 1);
                            temp_s3->_st2 = (temp_s3->_st2 + 1);
                            temp_s3->_st3 = 0;
                            return;
                        case 1:
                            if ((FUN_003db060(temp_s5, 0, 1) & 0xFF) == 1) {
                                temp_s3->_st0 = 6;
                                temp_s3->_st3 = 0;
                                temp_s3->_st2 = 0;
                                temp_s3->_st1 = 0;
                                return;
                            }
                            break;
                        }
                        break;
                    }
                    break;
                case 6:
                    temp_a0_7 = temp_s3->_st1;
                    switch (temp_a0_7) {
                    case 0x0:
                        if (((beNDMWLoadSavePlWork *)(ObjectList_GetAt_003e9260(temp_s0->_flagWork, arg1->player)))->_isCutConnect == 1) {
                            temp_s3->_st1 = 0x64;
                            temp_s3->_st3 = 0;
                            temp_s3->_st2 = 0;
                            return;
                        }
                        temp_a0_8 = temp_s3->_st2;
                        switch (temp_a0_8) {
                        case 0:
                            beNDMWLoadIntf2DataSelIntf__ClearStatesFrom(temp_s5, 0);
                            temp_s3->_st2 = (temp_s3->_st2 + 1);
                            temp_s3->_st3 = 0;
                            return;
                        case 1:
                            if ((beNDMWLoadIntf2DataSelIntf__UpdateSelection(temp_s5, 0) & 0xFF) == 1) {
                                if (temp_s5->_isCancel != 0) {
                                    temp_s3->_st2 = (temp_s3->_st2 + 1);
                                    temp_s3->_st3 = 0;
                                    return;
                                }
                                temp_s3->_st1 = (temp_s3->_st1 + 1);
                                temp_s3->_st3 = 0;
                                temp_s3->_st2 = 0;
                                return;
                            }
                            break;
                        case 2:
                            beNDMWLoadIntf2DataSelIntf__ClearStatesFrom(temp_s5, 0);
                            temp_s3->_st2 = (temp_s3->_st2 + 1);
                            temp_s3->_st3 = 0;
                            return;
                        case 3:
                            if ((FUN_003dbf90(temp_s5, 0) & 0xFF) == 1) {
                                temp_s3->_st0 = 4;
                                temp_s3->_st3 = 0;
                                temp_s3->_st2 = 0;
                                temp_s3->_st1 = 0;
                                return;
                            }
                            break;
                        }
                        break;
                    case 0x1:
                        temp_a0_9 = temp_s3->_st2;
                        switch (temp_a0_9) {
                        case 0x0:
                            FUN_003ee250(temp_s0, arg1->player, 3);
                            temp_s3->_st2 = (temp_s3->_st2 + 1);
                            temp_s3->_st3 = 0;
                            return;
                        case 0x1:
                            temp_a0_10 = ((beNDMWLoadSavePlWork *)(ObjectList_GetAt_003e9260(temp_s0->_flagWork, arg1->player)))->_utilReturn;
                            switch (temp_a0_10) {
                            case 0:
                                temp_s3->_isOneSave = 1;
                                temp_s3->_st1 = (temp_s3->_st1 + 1);
                                temp_s3->_st3 = 0;
                                temp_s3->_st2 = 0;
                                return;
                            case 1:
                                temp_s3->_st2 = 0x32;
                                temp_s3->_st3 = 0;
                                return;
                            case 3:
                                temp_s1->_isSelect = 0;
                                temp_s3->_st1 = 0;
                                temp_s3->_st3 = 0;
                                temp_s3->_st2 = 0;
                                return;
                            case 2:
                                temp_s3->_st2 = 0x32;
                                temp_s3->_st3 = 0;
                                return;
                            }
                            break;
                        case 0x32:
                            temp_s1->_st0 = 2;
                            temp_s1->_st3 = 0;
                            temp_s1->_st2 = 0;
                            temp_s1->_st1 = 0;
                            temp_s3->_st2 = (temp_s3->_st2 + 1);
                            temp_s3->_st3 = 0;
                            return;
                        case 0x33:
                            if ((beNDMWLoadIntf2SelSlot__Close(temp_s1, 1, 2) & 0xFF) == 1) {
                                temp_s3->_st1 = 0x64;
                                temp_s3->_st3 = 0;
                                temp_s3->_st2 = 0;
                                return;
                            }
                            break;
                        }
                        break;
                    case 0x2:
                        if (((beNDMWLoadSavePlWork *)(ObjectList_GetAt_003e9260(temp_s0->_flagWork, arg1->player)))->_isCutConnect == 1) {
                            temp_s3->_st1 = 0x64;
                            temp_s3->_st3 = 0;
                            temp_s3->_st2 = 0;
                            return;
                        }
                        temp_v1_14 = temp_s3->_st2;
                        switch (temp_v1_14) {
                        default:
                        case 0:
                            FUN_003ecb00(temp_s2, (arg1->player << 0x10) | 0x50B);
                            temp_s3->_st2 = (temp_s3->_st2 + 1);
                            temp_s3->_st3 = 0;
                            return;
                        case 1:
                            if (!(beNDMWLoadIntf2MesWin__GetIsCtrl(temp_s2, 1) & 0xFF)) {
                                temp_s3->_st2 = (temp_s3->_st2 + 1);
                                temp_s3->_st3 = 0;
                                return;
                            }
                            break;
                        case 2:
                            FUN_003ecae0(temp_s2, (arg1->player << 0x10) | 0x50D, 0);
                            temp_s3->_st2 = (temp_s3->_st2 + 1);
                            temp_s3->_st3 = 0;
                            return;
                        case 3:
                            if (!(beNDMWLoadIntf2MesWin__GetIsCtrl(temp_s2, 1) & 0xFF)) {
                                temp_v0_6 = FUN_003ecb80(temp_s2);
                                switch (temp_v0_6) {
                                case 0:
                                    temp_s3->_st2 = 5;
                                    temp_s3->_st3 = 0;
                                    return;
                                case 1:
                                    temp_s3->_st2 = 4;
                                    temp_s3->_st3 = 0;
                                    return;
                                }
                            }
                            break;
                        case 4:
                            temp_v1_15 = temp_s3->_st3;
                            switch (temp_v1_15) {
                            case 0:
                                beNDMWLoadIntf2DataSelIntf__ClearStatesFrom(temp_s5, 0);
                                temp_s3->_st3 = (temp_s3->_st3 + 1);
                                return;
                            case 1:
                                if ((FUN_003dd160(temp_s5, 0) & 0xFF) == 1) {
                                    temp_s3->_st0 = 6;
                                    temp_s3->_st3 = 0;
                                    temp_s3->_st2 = 0;
                                    temp_s3->_st1 = 0;
                                    return;
                                }
                                break;
                            }
                            break;
                        case 5:
                            temp_v1_16 = temp_s3->_st3;
                            switch (temp_v1_16) {
                            case 0:
                                beNDMWLoadCtrl2CommonIntf__RemoveAccessPlayer(temp_s0, arg1->player);
                                beNDMWLoadIntf2DataSelIntf__ClearStatesFrom(temp_s5, 0);
                                temp_s3->_st3 = (temp_s3->_st3 + 1);
                                return;
                            case 1:
                                if ((FUN_003dd440(temp_s5, 0) & 0xFF) == 1) {
                                    if (arg1->player == 0) {
                                        var_s1_2 = 1;
                                        var_s2_2 = 0;
                                        do {
                                            if (((beNDMWLoadSavePlWork *)(ObjectList_GetAt_003e9260(temp_s0->_flagWork, var_s1_2)))->_isEntry == 1) {
                                                var_s2_2 = 1;
                                                break;
                                            }
                                            var_s1_2 += 1;
                                        } while (var_s1_2 < 4);
                                        if ((var_s2_2 & 0xFF) == 1) {
                                            temp_s3->_st0 = 8;
                                            temp_s3->_st3 = 0;
                                            temp_s3->_st2 = 0;
                                            temp_s3->_st1 = 0;
                                            return;
                                        }
                                        temp_s3->_st0 = 7;
                                        temp_s3->_st3 = 0;
                                        temp_s3->_st2 = 0;
                                        temp_s3->_st1 = 0;
                                        return;
                                    }
                                    temp_s3->_st0 = 7;
                                    temp_s3->_st3 = 0;
                                    temp_s3->_st2 = 0;
                                    temp_s3->_st1 = 0;
                                    return;
                                }
                                break;
                            }
                            break;
                        }
                        break;
                    case 0x64:
                        temp_a0_11 = temp_s3->_st2;
                        switch (temp_a0_11) {
                        case 0:
                            FUN_003ecb20(temp_s2);
                            beNDMWLoadIntf2DataSelIntf__ClearStatesFrom(temp_s5, 0);
                            temp_s3->_st2 = (temp_s3->_st2 + 1);
                            temp_s3->_st3 = 0;
                            return;
                        case 1:
                            if ((FUN_003dbf90(temp_s5, 0) & 0xFF) == 1) {
                                temp_s3->_st0 = 4;
                                temp_s3->_st3 = 0;
                                temp_s3->_st2 = 0;
                                temp_s3->_st1 = 0;
                                return;
                            }
                            break;
                        }
                        break;
                    }
                    break;
                case 7:
                    switch (temp_s3->_st1) {
                    case 0:
                    default:
                        temp_a0_12 = temp_s3->_st2;
                        switch (temp_a0_12) {
                        case 0:
                            FUN_003ecb00(temp_s2, (arg1->player << 0x10) | 0x50E);
                            temp_s3->_st2 = (temp_s3->_st2 + 1);
                            temp_s3->_st3 = 0;
                            return;
                        case 1:
                            if (!(beNDMWLoadIntf2MesWin__GetIsCtrl(temp_s2) & 0xFF)) {
                                temp_s3->_st2 = (temp_s3->_st2 + 1);
                                temp_s3->_st3 = 0;
                                return;
                            }
                            break;
                        case 2:
                            FUN_003ecae0(temp_s2, (arg1->player << 0x10) | 0x510, 0);
                            temp_s3->_st2 = (temp_s3->_st2 + 1);
                            temp_s3->_st3 = 0;
                            return;
                        case 3:
                            if (!(beNDMWLoadIntf2MesWin__GetIsCtrl(temp_s2) & 0xFF)) {
                                temp_v0_7 = FUN_003ecb80(temp_s2);
                                switch (temp_v0_7) {
                                case 0:
                                    temp_s3->_st0 = 8;
                                    temp_s3->_st3 = 0;
                                    temp_s3->_st2 = 0;
                                    temp_s3->_st1 = 0;
                                    return;
                                case 1:
                                    temp_s3->_st1 = (temp_s3->_st1 + 1);
                                    temp_s3->_st3 = 0;
                                    temp_s3->_st2 = 0;
                                    return;
                                }
                            }
                            break;
                        }
                    break;
                    case 1:
                        temp_v1_17 = temp_s3->_st2;
                        switch (temp_v1_17) {
                        case 0:
                            if (temp_s3->_isOneSave == 1) {
                                temp_s3->_st2 = 4;
                                temp_s3->_st3 = 0;
                                return;
                            }
                            FUN_003ecb00(temp_s2, (arg1->player << 0x10) | 0x527, 1);
                            temp_s3->_st2 = (temp_s3->_st2 + 1);
                            temp_s3->_st3 = 0;
                            return;
                        case 1:
                            if (!(beNDMWLoadIntf2MesWin__GetIsCtrl(temp_s2) & 0xFF)) {
                                temp_s3->_st2 = (temp_s3->_st2 + 1);
                                temp_s3->_st3 = 0;
                                return;
                            }
                            break;
                        case 2:
                            FUN_003ecae0(temp_s2, (arg1->player << 0x10) | 0x529, 1);
                            temp_s3->_st2 = (temp_s3->_st2 + 1);
                            temp_s3->_st3 = 0;
                            return;
                        case 3:
                            if (!(beNDMWLoadIntf2MesWin__GetIsCtrl(temp_s2) & 0xFF)) {
                                temp_v0_8 = FUN_003ecb80(temp_s2);
                                switch (temp_v0_8) {
                                case 0:
                                    temp_s3->_st2 = 4;
                                    temp_s3->_st3 = 0;
                                    return;
                                case 1:
                                    temp_s3->_st2 = 5;
                                    temp_s3->_st3 = 0;
                                    return;
                                }
                            }
                            break;
                        case 4:
                            temp_v1_18 = temp_s3->_st3;
                            switch (temp_v1_18) {
                            case 0:
                                FUN_003d9e70(ObjectList_GetAt_003e9260(temp_s8->_statDataList, 0), 1);
                                beNDMWLoadIntf2ComMdlCtrl__Close(temp_s7, arg1->player, &DAT_00519730[0], &DAT_00519740[0], 1);
                                beNDMWLoadIntf2MesWin__RequestClose(temp_s2);
                                temp_s3->_st3 = (temp_s3->_st3 + 1);
                                return;
                            case 1:
                                if (((FUN_003da7c0(ObjectList_GetAt_003e9260(temp_s8->_statDataList, 0)) & 0xFF) == 1) && ((beNDMWLoadIntf2ComMdlCtrl__IsCloseQueueEmpty(temp_s7) & 0xFF) == 1)) {
                                    temp_s3->_st0 = 9;
                                    temp_s3->_st3 = 0;
                                    temp_s3->_st2 = 0;
                                    temp_s3->_st1 = 0;
                                    { beNDMWLoadSavePlWork *r_ = (beNDMWLoadSavePlWork *)ObjectList_GetAt_003e9260(temp_s0->_flagWork, arg1->player); r_->_isEntry = 0; }
                                    { beNDMWLoadSavePlWork *r_ = (beNDMWLoadSavePlWork *)ObjectList_GetAt_003e9260(temp_s0->_flagWork, arg1->player); r_->_isRdy = 0; }
                                    return;
                                }
                                break;
                            }
                            break;
                        case 5:
                            temp_v1_19 = temp_s3->_st3;
                            switch (temp_v1_19) {
                            case 0:
                                FUN_003d9e70(ObjectList_GetAt_003e9260(temp_s8->_statDataList, 0), 0);
                                temp_s3->_st3 = (temp_s3->_st3 + 1);
                                return;
                            case 1:
                                if ((FUN_003da7c0(ObjectList_GetAt_003e9260(temp_s8->_statDataList, 0)) & 0xFF) == 1) {
                                    temp_s3->_st0 = 2;
                                    temp_s3->_st3 = 0;
                                    temp_s3->_st2 = 0;
                                    temp_s3->_st1 = 0;
                                    return;
                                }
                                break;
                            }
                            break;
                        }
                    break;
                    }
                    break;
                case 8:
                    temp_a1_2 = temp_s3->_st1;
                    switch (temp_a1_2) {
                    case 0:
                        { beNDMWLoadSavePlWork *r_ = (beNDMWLoadSavePlWork *)ObjectList_GetAt_003e9260(temp_s0->_flagWork, arg1->player); r_->_isRdy = 1; }
                        temp_v0_9 = arg1->player;
                        if (temp_v0_9 == 0) {
                            temp_s6 = (void *)(temp_s0->_flagWork);
                            var_s5 = 0;
                            var_s1_3 = 0;
                            for (var_s0 = 0; var_s0 < FUN_002294f0(temp_s6); var_s0++) {
                                    if ((beNDMWLoadSavePlWork__GetIsEntry(DataList_GetWordAt_003e9240(temp_s6, var_s0)) & 0xFF) == 1) {
                                        var_s5 += 1;
                                    }
                                    if ((beNDMWLoadSavePlWork__GetIsRdy(DataList_GetWordAt_003e9240(temp_s6, var_s0)) & 0xFF) == 1) {
                                        var_s1_3 += 1;
                                    }
                            }
                            if ((var_s5 == var_s1_3) == 1) {
                                FUN_003ecad0(temp_s2, (arg1->player << 0x10) | 0x51D);
                                temp_s3->_st1 = 3;
                                temp_s3->_st3 = 0;
                                temp_s3->_st2 = 0;
                                return;
                            }
                            FUN_003ecad0(temp_s2, (arg1->player << 0x10) | 0x530);
                            temp_s3->_st1 = (temp_s3->_st1 + 1);
                            temp_s3->_st3 = 0;
                            temp_s3->_st2 = 0;
                            return;
                        }
                        FUN_003ecad0(temp_s2, (temp_v0_9 << 0x10) | 0x530);
                        temp_s3->_st1 = (temp_s3->_st1 + 1);
                        temp_s3->_st3 = 0;
                        temp_s3->_st2 = 0;
                        return;
                    case 1:
                        temp_v1_20 = temp_s3->_st3;
                        switch (temp_v1_20) {
                        case 0:
                            if (arg1->player == 0) {
                                temp_s6_2 = (void *)(temp_s0->_flagWork);
                                var_s5_2 = 0;
                                var_s2_3 = 0;
                                for (var_s1_4 = 0; var_s1_4 < FUN_002294f0(temp_s6_2); var_s1_4++) {
                                        if ((beNDMWLoadSavePlWork__GetIsEntry(DataList_GetWordAt_003e9240(temp_s6_2, var_s1_4)) & 0xFF) == 1) {
                                            var_s5_2 += 1;
                                        }
                                        if ((beNDMWLoadSavePlWork__GetIsRdy(DataList_GetWordAt_003e9240(temp_s6_2, var_s1_4)) & 0xFF) == 1) {
                                            var_s2_3 += 1;
                                        }
                                }
                                if ((var_s5_2 == var_s2_3) == 1) {
                                    temp_s3->_st1 = 3;
                                    temp_s3->_st3 = 0;
                                    temp_s3->_st2 = 0;
                                    return;
                                }
                                if (spB0 & 0x2000) {
                                    { beNDMWLoadSavePlWork *r_ = (beNDMWLoadSavePlWork *)ObjectList_GetAt_003e9260(temp_s0->_flagWork, arg1->player); r_->_isRdy = 0; }
                                    temp_s3->_st1 = (temp_s3->_st1 + 1);
                                    temp_s3->_st3 = 0;
                                    temp_s3->_st2 = 0;
                                    return;
                                }
                            } else {
                                temp_s7_2 = (void *)(temp_s0->_flagWork);
                                var_s5_3 = 0;
                                var_s6 = 0;
                                for (var_s1_5 = 0; var_s1_5 < FUN_002294f0(temp_s7_2); var_s1_5++) {
                                        if ((beNDMWLoadSavePlWork__GetIsEntry(DataList_GetWordAt_003e9240(temp_s7_2, var_s1_5)) & 0xFF) == 1) {
                                            var_s5_3 += 1;
                                        }
                                        if ((beNDMWLoadSavePlWork__GetIsRdy(DataList_GetWordAt_003e9240(temp_s7_2, var_s1_5)) & 0xFF) == 1) {
                                            var_s6 += 1;
                                        }
                                }
                                if ((var_s5_3 == var_s6) == 1) {
                                    FUN_003ecad0(temp_s2, (arg1->player << 0x10) | 0x51F);
                                    temp_s3->_st3 = (temp_s3->_st3 + 1);
                                    return;
                                }
                                if (spB0 & 0x2000) {
                                    { beNDMWLoadSavePlWork *r_ = (beNDMWLoadSavePlWork *)ObjectList_GetAt_003e9260(temp_s0->_flagWork, arg1->player); r_->_isRdy = 0; }
                                    temp_s3->_st1 = (temp_s3->_st1 + 1);
                                    temp_s3->_st3 = 0;
                                    temp_s3->_st2 = 0;
                                    return;
                                }
                            }
                            break;
                        case 1:
                            temp_s7_3 = (void *)(temp_s0->_flagWork);
                            var_s5_4 = 0;
                            var_s6_2 = 0;
                            for (var_s1_6 = 0; var_s1_6 < FUN_002294f0(temp_s7_3); var_s1_6++) {
                                    if ((beNDMWLoadSavePlWork__GetIsEntry(DataList_GetWordAt_003e9240(temp_s7_3, var_s1_6)) & 0xFF) == 1) {
                                        var_s5_4 += 1;
                                    }
                                    if ((beNDMWLoadSavePlWork__GetIsRdy(DataList_GetWordAt_003e9240(temp_s7_3, var_s1_6)) & 0xFF) == 1) {
                                        var_s6_2 += 1;
                                    }
                            }
                            if ((var_s5_4 == var_s6_2) == 0) {
                                FUN_003ecad0(temp_s2, (arg1->player << 0x10) | 0x530);
                                temp_s3->_st3 = 0;
                                return;
                            }
                            if (spB0 & 0x2000) {
                                { beNDMWLoadSavePlWork *r_ = (beNDMWLoadSavePlWork *)ObjectList_GetAt_003e9260(temp_s0->_flagWork, arg1->player); r_->_isRdy = 0; }
                                temp_s3->_st1 = (temp_s3->_st1 + 1);
                                temp_s3->_st3 = 0;
                                temp_s3->_st2 = 0;
                                return;
                            }
                            break;
                        }
                        break;
                    case 2:
                        temp_a0_13 = temp_s3->_st2;
                        switch (temp_a0_13) {
                        case 0:
                            FUN_003d9e70(ObjectList_GetAt_003e9260(temp_s8->_statDataList, 0), 2);
                            temp_s3->_st2 = (temp_s3->_st2 + 1);
                            temp_s3->_st3 = 0;
                            return;
                        case 1:
                            if ((FUN_003da7c0(ObjectList_GetAt_003e9260(temp_s8->_statDataList, 0)) & 0xFF) == 1) {
                                temp_s3->_st0 = 2;
                                temp_s3->_st3 = 0;
                                temp_s3->_st2 = 0;
                                temp_s3->_st1 = 0;
                                return;
                            }
                            break;
                        }
                        break;
                    case 3:
                        temp_a0_14 = temp_s3->_st2;
                        switch (temp_a0_14) {
                        case 0:
                            FUN_003ecad0(temp_s2, (arg1->player << 0x10) | 0x51D);
                            temp_s3->_st2 = (temp_s3->_st2 + 1);
                            temp_s3->_st3 = 0;
                            return;
                        case 1:
                            if (spB0 & 0x2000) {
                                { beNDMWLoadSavePlWork *r_ = (beNDMWLoadSavePlWork *)ObjectList_GetAt_003e9260(temp_s0->_flagWork, arg1->player); r_->_isRdy = 0; }
                                temp_s3->_st1 = 2;
                                temp_s3->_st3 = 0;
                                temp_s3->_st2 = 0;
                                return;
                            }
                            temp_s7_4 = (void *)(temp_s0->_flagWork);
                            var_s5_5 = 0;
                            var_s6_3 = 0;
                            for (var_s1_7 = 0; var_s1_7 < FUN_002294f0(temp_s7_4); var_s1_7++) {
                                    if ((beNDMWLoadSavePlWork__GetIsEntry(DataList_GetWordAt_003e9240(temp_s7_4, var_s1_7)) & 0xFF) == 1) {
                                        var_s5_5 += 1;
                                    }
                                    if ((beNDMWLoadSavePlWork__GetIsRdy(DataList_GetWordAt_003e9240(temp_s7_4, var_s1_7)) & 0xFF) == 1) {
                                        var_s6_3 += 1;
                                    }
                            }
                            if ((var_s5_5 == var_s6_3) == 1) {
                                if (spB0 & 8) {
                                    var_s1_8 = 0;
                                    temp_s0->_intfStat = 3;
                                    temp_s0_4 = (void *)(temp_s0->_flagWork);
                                    for (var_s1_8 = 0; var_s1_8 < FUN_002294f0(temp_s0_4); var_s1_8++) {
                                            beNDMWLoadSavePlWork__SetIsCtrl(DataList_GetWordAt_003e9240(temp_s0_4, var_s1_8), 0);
                                    }
                                    temp_s3->_st2 = (temp_s3->_st2 + 1);
                                    temp_s3->_st3 = 0;
                                    return;
                                }
                            } else {
                                FUN_003ecad0(temp_s2, (arg1->player << 0x10) | 0x530);
                                temp_s3->_st1 = 1;
                                temp_s3->_st3 = 0;
                                temp_s3->_st2 = 0;
                                return;
                            }
                            break;
                        }
                        break;
                    }
                    break;
                case 9:
                    temp_a0_15 = temp_s3->_st1;
                    switch (temp_a0_15) {
                    case 0:
                        temp_v1_21 = arg1->player;
                        if (temp_v1_21 == 0) {
                            FUN_003ecad0(temp_s2, (temp_v1_21 << 0x10) | 0x51F);
                            var_s1_9 = 0;
                            temp_s0->_intfStat = 3;
                            temp_s0_5 = (void *)(temp_s0->_flagWork);
                            for (var_s1_9 = 0; var_s1_9 < FUN_002294f0(temp_s0_5); var_s1_9++) {
                                    beNDMWLoadSavePlWork__SetIsCtrl(DataList_GetWordAt_003e9240(temp_s0_5, var_s1_9), 0);
                            }
                        }
                        temp_s3->_st1 = (temp_s3->_st1 + 1);
                        temp_s3->_st3 = 0;
                        temp_s3->_st2 = 0;
                        return;
                    case 1:
                        break;
                    }
                    break;
                }
            }
            break;
        case 2:
            temp_a0_16 = ((beNDMWLoadSavePlWork *)(ObjectList_GetAt_003e9260(temp_s0->_flagWork, arg1->player)))->_sysStat1;
            switch (temp_a0_16) {
            case 0:
                switch (temp_s3->_st0) {
                case 9:
                default:
                    temp_v0_10 = (beNDMWLoadSavePlWork *)(DataList_GetWordAt_003e9240(temp_s0->_flagWork, arg1->player));
                    temp_v0_10->_sysStat1 = 1;
                    temp_v0_10->_sysStat3 = 0;
                    temp_v0_10->_sysStat2 = 0;
                    break;
                case 8:
                    beNDMWLoadIntf2ComMdlCtrl__Close(temp_s7, arg1->player, &DAT_00519730[0], &DAT_00519740[0], 1);
                    beNDMWLoadIntf2MesWin__RequestClose(temp_s2);
                    FUN_003d9e90(ObjectList_GetAt_003e9260(temp_s8->_statDataList, 0));
                    temp_v0_11 = (beNDMWLoadSavePlWork *)(DataList_GetWordAt_003e9240(temp_s0->_flagWork, arg1->player));
                    temp_v0_11->_sysStat1 = 2;
                    temp_v0_11->_sysStat3 = 0;
                    temp_v0_11->_sysStat2 = 0;
                    break;
                }
                beNDMWLoadIntf2ComMdlCtrl__Close(temp_s7, arg1->player, &DAT_005196c8[0], &DAT_00519740[0], 1);
                return;
            case 1:
                if ((beNDMWLoadIntf2ComMdlCtrl__IsCloseQueueEmpty(temp_s7) & 0xFF) == 1) {
                    { beNDMWLoadSavePlWork *r_ = (beNDMWLoadSavePlWork *)ObjectList_GetAt_003e9260(temp_s0->_flagWork, arg1->player); r_->_isClose = 1; }
                    temp_v0_12 = (beNDMWLoadSavePlWork *)(DataList_GetWordAt_003e9240(temp_s0->_flagWork, arg1->player));
                    temp_v0_12->_sysStat1 = 3;
                    temp_v0_12->_sysStat3 = 0;
                    temp_v0_12->_sysStat2 = 0;
                    return;
                }
                break;
            case 2:
                if (((FUN_003da7c0(ObjectList_GetAt_003e9260(temp_s8->_statDataList, 0)) & 0xFF) == 1) && ((beNDMWLoadIntf2ComMdlCtrl__IsCloseQueueEmpty(temp_s7) & 0xFF) == 1)) {
                    { beNDMWLoadSavePlWork *r_ = (beNDMWLoadSavePlWork *)ObjectList_GetAt_003e9260(temp_s0->_flagWork, arg1->player); r_->_isClose = 1; }
                    temp_v0_13 = (beNDMWLoadSavePlWork *)(DataList_GetWordAt_003e9240(temp_s0->_flagWork, arg1->player));
                    temp_v0_13->_sysStat1 = 3;
                    temp_v0_13->_sysStat3 = 0;
                    temp_v0_13->_sysStat2 = 0;
                    return;
                }
                break;
            case 3:
                break;
            }
            break;
        case 3:
            temp_v0_14 = (beNDMWLoadSavePlWork *)(ObjectList_GetAt_003e9260(temp_s0->_flagWork, arg1->player));
            temp_a2 = temp_v0_14->_sysStat1;
            switch (temp_a2) {
            case 0x0:
                temp_v1_22 = temp_v0_14->_sysStat2;
                switch (temp_v1_22) {
                case 0:
                    beNDMWLoadIntf2DataSelIntf__ClearStatesFrom(temp_s5, 0);
                    temp_v0_14->_sysStat2 = (temp_v0_14->_sysStat2 + 1);
                    temp_v0_14->_sysStat3 = 0;
                    return;
                case 1:
                    if ((FUN_003dc2e0(temp_s5, 0) & 0xFF) == 1) {
                        temp_v0_14->_sysStat1 = (temp_v0_14->_sysStat1 + 1);
                        temp_v0_14->_sysStat3 = 0;
                        temp_v0_14->_sysStat2 = 0;
                        return;
                    }
                    break;
                }
                break;
            case 0x1:
                temp_v1_23 = temp_v0_14->_sysStat2;
                switch (temp_v1_23) {
                default:
                    if (((beNDMWLoadSavePlWork *)(ObjectList_GetAt_003e9260(temp_s0->_flagWork, arg1->player)))->_isCutConnect == 1) {
                        temp_v0_14->_sysStat1 = 0x64;
                        temp_v0_14->_sysStat3 = 0;
                        temp_v0_14->_sysStat2 = 0;
                        return;
                    }
                    temp_a0_17 = temp_v0_14->_sysStat3;
                    switch (temp_a0_17) {
                    case 0:
                        if (((beNDMWDegiData *)(ObjectList_GetAt_003e9260(((beNDMWLoadSlotPlayer *)(temp_v0_14->_haveSaveData))->_saveDataList, temp_s5->_svDataSelPoint)))->_isUse == 0) {
                            FUN_003ecb00(temp_s2, (arg1->player << 0x10) | 0x508);
                        } else {
                            FUN_003ecb00(temp_s2, (arg1->player << 0x10) | 0x505);
                        }
                        temp_v0_14->_sysStat3 = (temp_v0_14->_sysStat3 + 1);
                        return;
                    case 1:
                        if (!(beNDMWLoadIntf2MesWin__GetIsCtrl(temp_s2, 1) & 0xFF)) {
                            temp_v0_14->_sysStat3 = (temp_v0_14->_sysStat3 + 1);
                            return;
                        }
                        break;
                    case 2:
                        if (((beNDMWDegiData *)(ObjectList_GetAt_003e9260(((beNDMWLoadSlotPlayer *)(temp_v0_14->_haveSaveData))->_saveDataList, temp_s5->_svDataSelPoint)))->_isUse == 1) {
                            FUN_003ecae0(temp_s2, (arg1->player << 0x10) | 0x50A, 0);
                        } else {
                            FUN_003ecae0(temp_s2, (arg1->player << 0x10) | 0x507, 0);
                        }
                        temp_v0_14->_sysStat3 = (temp_v0_14->_sysStat3 + 1);
                        return;
                    case 3:
                        if (!(beNDMWLoadIntf2MesWin__GetIsCtrl(temp_s2, 1) & 0xFF)) {
                            temp_v0_14->_sysStat2 = (temp_v0_14->_sysStat2 + 1);
                            temp_v0_14->_sysStat3 = 0;
                            return;
                        }
                        break;
                    }
                    break;
                case 1:
                    temp_v1_24 = temp_v0_14->_sysStat3;
                    switch (temp_v1_24) {
                    case 0:
                        beNDMWLoadIntf2DataSelIntf__ClearStatesFrom(temp_s5, 0);
                        temp_v0_14->_sysStat3 = (temp_v0_14->_sysStat3 + 1);
                        return;
                    case 1:
                        if (FUN_003ecb80(temp_s2, 2) == 0) {
                            if ((FUN_003dcab0(temp_s5, 0) & 0xFF) == 1) {
                                temp_v0_14->_sysStat2 = (temp_v0_14->_sysStat2 + 1);
                                temp_v0_14->_sysStat3 = 0;
                                return;
                            }
                        } else if ((FUN_003dc590(temp_s5, 0) & 0xFF) == 1) {
                            temp_v0_14->_sysStat2 = (temp_v0_14->_sysStat2 + 1);
                            temp_v0_14->_sysStat3 = 0;
                            return;
                        }
                        break;
                    }
                    break;
                case 2:
                    temp_v0_15 = FUN_003ecb80(temp_s2, 2);
                    switch (temp_v0_15) {
                    case 0:
                        temp_v0_14->_sysStat1 = (temp_v0_14->_sysStat1 + 1);
                        temp_v0_14->_sysStat3 = 0;
                        temp_v0_14->_sysStat2 = 0;
                        temp_v1_25 = temp_s0->_kindHard;
                        var_a1_5 = -1;
                        switch (temp_v1_25) {
                        case 0:
                            var_a1_5 = (arg1->player << 0x10) | 0x100B;
                            break;
                        case 1:
                            var_a1_5 = (arg1->player << 0x10) | 0x200B;
                            break;
                        case 2:
                            var_a1_5 = (arg1->player << 0x10) | 0x300B;
                            break;
                        }
                        FUN_003ecad0(temp_s2, var_a1_5);
                        return;
                    case 1:
                        temp_v0_14->_sysStat2 = (temp_v0_14->_sysStat2 + 1);
                        temp_v0_14->_sysStat3 = 0;
                        return;
                    }
                    break;
                case 3:
                    temp_v1_26 = temp_v0_14->_sysStat3;
                    switch (temp_v1_26) {
                    case 0:
                        beNDMWLoadIntf2DataSelIntf__ClearStatesFrom(temp_s5, 0);
                        temp_v0_14->_sysStat3 = (temp_v0_14->_sysStat3 + 1);
                        return;
                    case 1:
                        if ((FUN_003dd160(temp_s5, 0) & 0xFF) == 1) {
                            temp_v0_14->_sysStat0 = 7;
                            temp_v0_14->_sysStat3 = 0;
                            temp_v0_14->_sysStat2 = 0;
                            temp_v0_14->_sysStat1 = 0;
                            temp_v0_14->_utilReturn = 3;
                            return;
                        }
                        break;
                    }
                    break;
                }
                break;
            case 0x2:
                temp_v1_27 = temp_v0_14->_sysStat2;
                switch (temp_v1_27) {
                case 0:
                    temp_v1_28 = temp_v0_14->_sysStat3;
                    switch (temp_v1_28) {
                    case 0:
                        ((beSystem *)arg0->_system_)->_isResetEnable = 0;
                        FUN_003e0b80(temp_s1, 2);
                        temp_s1->_st0 = 0;
                        temp_s1->_st3 = 0;
                        temp_s1->_st2 = 0;
                        temp_s1->_st1 = 0;
                        temp_v0_14->_sysStat3 = (temp_v0_14->_sysStat3 + 1);
                        return;
                    case 1:
                        if (((beNDMWMcSlot *)(ObjectList_GetAt_003e9260(((beNDMWMcUtilCtrl *)(temp_s0->_mcUtilCtrl))->_slot, temp_s1->_mcSelPoint)))->_isConnect != 1) {
                            temp_v0_14->_sysStat3 = (temp_v0_14->_sysStat3 + 1);
                            return;
                        }
                        if ((beNDMWLoadIntf2SelSlot__Open(temp_s1, -1) & 0xFF) == 1) {
                            temp_v0_14->_sysStat2 = (temp_v0_14->_sysStat2 + 1);
                            temp_v0_14->_sysStat3 = 0;
                            return;
                        }
                        break;
                    case 2:
                        if ((beNDMWLoadIntf2SelSlot__Open(temp_s1, -1) & 0xFF) == 1) {
                            ((beNDMWMcUtilCtrl *)(temp_s0->_mcUtilCtrl))->_result = 0xC;
                            ((beSystem *)arg0->_system_)->_isResetEnable = 1;
                            temp_v0_14->_sysStat0 = 6;
                            temp_v0_14->_sysStat3 = 0;
                            temp_v0_14->_sysStat2 = 0;
                            temp_v0_14->_sysStat1 = 0;
                            return;
                        }
                        break;
                    }
                    break;
                case 1:
                    temp_v0_16 = FUN_003ed050(temp_s0, arg1->player, temp_s2, temp_s1->_mcSelPoint, 3);
                    switch (temp_v0_16) {
                    case 0:
                        break;
                    case 1:
                        temp_v0_14->_sysStat2 = (temp_v0_14->_sysStat2 + 1);
                        temp_v0_14->_sysStat3 = 0;
                        return;
                    case 2:
                        switch (((beNDMWMcUtilCtrl *)(temp_s0->_mcUtilCtrl))->_result) {
                        case 0xC:
                        ((beSystem *)arg0->_system_)->_isResetEnable = 1;
                        temp_v0_14->_sysStat0 = 6;
                        temp_v0_14->_sysStat3 = 0;
                        temp_v0_14->_sysStat2 = 0;
                        temp_v0_14->_sysStat1 = 0;
                        return;
                        default:
                            ((beSystem *)arg0->_system_)->_isResetEnable = 1;
                            temp_v0_14->_sysStat0 = 6;
                            temp_v0_14->_sysStat3 = 0;
                            temp_v0_14->_sysStat2 = 0;
                            temp_v0_14->_sysStat1 = 0;
                            return;
                        }
                    }
                    break;
                case 2:
                    temp_v0_17 = FUN_003edc20(temp_s0, arg1->player, temp_s2, temp_s1->_mcSelPoint, temp_s5->_svDataSelPoint, 3);
                    switch (temp_v0_17) {
                    case 0:
                        break;
                    case 1:
                        temp_v0_14->_sysStat1 = (temp_v0_14->_sysStat1 + 1);
                        temp_v0_14->_sysStat3 = 0;
                        temp_v0_14->_sysStat2 = 0;
                        return;
                    case 2:
                        switch (((beNDMWMcUtilCtrl *)(temp_s0->_mcUtilCtrl))->_result) {
                        case 0xC:
                        ((beSystem *)arg0->_system_)->_isResetEnable = 1;
                        temp_v0_14->_sysStat0 = 6;
                        temp_v0_14->_sysStat3 = 0;
                        temp_v0_14->_sysStat2 = 0;
                        temp_v0_14->_sysStat1 = 0;
                        return;
                        default:
                            ((beSystem *)arg0->_system_)->_isResetEnable = 1;
                            temp_v0_14->_sysStat0 = 6;
                            temp_v0_14->_sysStat3 = 0;
                            temp_v0_14->_sysStat2 = 0;
                            temp_v0_14->_sysStat1 = 0;
                            return;
                        }
                    }
                    break;
                }
                break;
            case 0x3:
                if ((temp_v0_14->_sysStat3 == 0) && (((beNDMWMcSlot *)(ObjectList_GetAt_003e9260(((beNDMWMcUtilCtrl *)(temp_s0->_mcUtilCtrl))->_slot, temp_s1->_mcSelPoint)))->_isConnect != 1)) {
                    temp_v0_14->_sysStat3 = 1;
                }
                temp_v1_29 = temp_v0_14->_sysStat2;
                switch (temp_v1_29) {
                case 0:
                    ((beSystem *)arg0->_system_)->_isResetEnable = 1;
                    temp_s1->_st0 = 2;
                    temp_s1->_st3 = 0;
                    temp_s1->_st2 = 0;
                    temp_s1->_st1 = 0;
                    temp_v0_14->_sysStat2 = (temp_v0_14->_sysStat2 + 1);
                    temp_v0_14->_sysStat3 = 0;
                    return;
                case 1:
                    if ((beNDMWLoadIntf2SelSlot__Close(temp_s1) & 0xFF) == 1) {
                        temp_v0_14->_sysStat2 = (temp_v0_14->_sysStat2 + 1);
                        temp_v0_14->_sysStat3 = 0;
                        return;
                    }
                    break;
                case 2:
                    beNDMWLoadIntf2DataSelIntf__ClearStatesFrom(temp_s5, 0);
                    temp_v0_14->_sysStat2 = (temp_v0_14->_sysStat2 + 1);
                    temp_v0_14->_sysStat3 = 0;
                    return;
                case 3:
                    if ((FUN_003dcc60(temp_s5, 0) & 0xFF) == 1) {
                        temp_v0_14->_sysStat2 = (temp_v0_14->_sysStat2 + 1);
                        temp_v0_14->_sysStat3 = 0;
                        return;
                    }
                    break;
                case 4:
                    beNDMWLoadIntf2DataSelIntf__ClearStatesFrom(temp_s5, 0);
                    temp_v0_14->_sysStat2 = (temp_v0_14->_sysStat2 + 1);
                    temp_v0_14->_sysStat3 = 0;
                    return;
                case 5:
                    if ((FUN_003dd6d0(temp_s5, 0) & 0xFF) == 1) {
                        if (temp_v0_14->_sysStat3 == 0) {
                            temp_v0_14->_sysStat0 = 7;
                            temp_v0_14->_sysStat3 = 0;
                            temp_v0_14->_sysStat2 = 0;
                            temp_v0_14->_sysStat1 = 0;
                            temp_v0_14->_utilReturn = 0;
                            return;
                        }
                        temp_v0_14->_sysStat1 = (temp_v0_14->_sysStat1 + 1);
                        temp_v0_14->_sysStat3 = 0;
                        temp_v0_14->_sysStat2 = 0;
                        return;
                    }
                    break;
                }
                break;
            case 0x4:
                temp_a0_18 = temp_v0_14->_sysStat3;
                switch (temp_a0_18) {
                case 0:
                    FUN_003ecb00(temp_s2, (arg1->player << 0x10) | 0x50B);
                    temp_v0_14->_sysStat3 = (temp_v0_14->_sysStat3 + 1);
                    return;
                case 1:
                    if (!(beNDMWLoadIntf2MesWin__GetIsCtrl(temp_s2) & 0xFF)) {
                        temp_v0_14->_sysStat1 = 0x64;
                        temp_v0_14->_sysStat3 = 0;
                        temp_v0_14->_sysStat2 = 0;
                        return;
                    }
                    break;
                }
                break;
            case 0x64:
                temp_a0_19 = temp_v0_14->_sysStat2;
                switch (temp_a0_19) {
                case 0:
                    FUN_003ecb20(temp_s2);
                    temp_v0_14->_sysStat2 = (temp_v0_14->_sysStat2 + 1);
                    temp_v0_14->_sysStat3 = 0;
                    beNDMWLoadIntf2DataSelIntf__ClearStatesFrom(temp_s5, 0);
                    return;
                case 1:
                    if ((FUN_003dbf90(temp_s5, 0) & 0xFF) == 1) {
                        temp_v0_14->_sysStat0 = 7;
                        temp_v0_14->_sysStat3 = 0;
                        temp_v0_14->_sysStat2 = 0;
                        temp_v0_14->_sysStat1 = 0;
                        temp_v0_14->_utilReturn = 2;
                        return;
                    }
                    break;
                }
                break;
            }
            break;
        case 4:
            temp_v0_18 = (beNDMWLoadSavePlWork *)(ObjectList_GetAt_003e9260(temp_s0->_flagWork, arg1->player));
            temp_v1_30 = temp_v0_18->_sysStat1;
            switch (temp_v1_30) {
            case 0:
                temp_v0_19 = FUN_003ed050(temp_s0, arg1->player, temp_s2, temp_s1->_mcSelPoint, 3);
                switch (temp_v0_19) {
                case 0:
                    break;
                case 1:
                    temp_v0_18->_sysStat1 = 5;
                    temp_v0_18->_sysStat3 = 0;
                    temp_v0_18->_sysStat2 = 0;
                    return;
                case 2:
                    temp_a0_20 = ((beNDMWMcUtilCtrl *)(temp_s0->_mcUtilCtrl))->_result;
                    switch (temp_a0_20) {
                    case 2:
                        temp_v0_18->_sysStat1 = 5;
                        temp_v0_18->_sysStat3 = 0;
                        temp_v0_18->_sysStat2 = 0;
                        return;
                    case 4:
                    case 3:
                        temp_v0_18->_sysStat1 = 1;
                        temp_v0_18->_sysStat3 = 0;
                        temp_v0_18->_sysStat2 = 0;
                        return;
                    case 7:
                        temp_v0_18->_sysStat1 = 3;
                        temp_v0_18->_sysStat3 = 0;
                        temp_v0_18->_sysStat2 = 0;
                        return;
                    case 12:
                        temp_v0_18->_sysStat0 = 6;
                        temp_v0_18->_sysStat3 = 0;
                        temp_v0_18->_sysStat2 = 0;
                        temp_v0_18->_sysStat1 = 0;
                        return;
                    default:
                        temp_v0_18->_sysStat0 = 6;
                        temp_v0_18->_sysStat3 = 0;
                        temp_v0_18->_sysStat2 = 0;
                        temp_v0_18->_sysStat1 = 0;
                        return;
                    }
                    break;
                }
                break;
            case 1:
                if (((beNDMWMcSlot *)(ObjectList_GetAt_003e9260(((beNDMWMcUtilCtrl *)(temp_s0->_mcUtilCtrl))->_slot, temp_s1->_mcSelPoint)))->_isConnect != 1) {
                    FUN_003ecb20(temp_s2);
                    temp_v0_18->_sysStat0 = 7;
                    temp_v0_18->_sysStat3 = 0;
                    temp_v0_18->_sysStat2 = 0;
                    temp_v0_18->_sysStat1 = 0;
                    temp_v0_18->_utilReturn = 2;
                    return;
                }
                temp_v1_31 = temp_s0->_kindHard;
                var_a3 = -1;
                var_a4 = -1;
                switch (temp_v1_31) {
                case 0:
                    temp_v0_20 = arg1->player << 0x10;
                    var_a3 = temp_v0_20 | 0x1000;
                    var_a4 = temp_v0_20 | 0x1002;
                    break;
                case 1:
                    temp_v0_21 = arg1->player << 0x10;
                    var_a3 = temp_v0_21 | 0x2000;
                    var_a4 = temp_v0_21 | 0x2002;
                    break;
                case 2:
                    temp_v0_22 = arg1->player << 0x10;
                    var_a3 = temp_v0_22 | 0x3000;
                    var_a4 = temp_v0_22 | 0x3002;
                    break;
                }
                temp_v0_23 = FUN_003ecdc0(temp_s0, arg1->player, temp_s2, var_a3, var_a4, 0, 3);
                switch (temp_v0_23) {
                case 0:
                    break;
                case 1:
                    temp_v0_18->_sysStat1 = 2;
                    temp_v0_18->_sysStat3 = 0;
                    temp_v0_18->_sysStat2 = 0;
                    return;
                case 2:
                    temp_v0_18->_sysStat0 = 7;
                    temp_v0_18->_sysStat3 = 0;
                    temp_v0_18->_sysStat2 = 0;
                    temp_v0_18->_sysStat1 = 0;
                    temp_v0_18->_utilReturn = 1;
                    return;
                }
                break;
            case 2:
                temp_a0_21 = temp_v0_18->_sysStat2;
                switch (temp_a0_21) {
                case 0:
                    ((beSystem *)arg0->_system_)->_isResetEnable = 0;
                    temp_v0_18->_sysStat2 = (temp_v0_18->_sysStat2 + 1);
                    temp_v0_18->_sysStat3 = 0;
                    return;
                case 1:
                    temp_v0_24 = FUN_003ed2e0(temp_s0, arg1->player, temp_s2, temp_s1->_mcSelPoint, 3);
                    switch (temp_v0_24) {
                    case 0:
                        break;
                    case 1:
                        temp_v0_18->_sysStat1 = 5;
                        temp_v0_18->_sysStat3 = 0;
                        temp_v0_18->_sysStat2 = 0;
                        break;
                    case 2:
                        temp_v1_32 = ((beNDMWMcUtilCtrl *)(temp_s0->_mcUtilCtrl))->_result;
                        switch (temp_v1_32 - 3) {
                        case 4:
                            temp_v0_18->_sysStat1 = 3;
                            temp_v0_18->_sysStat3 = 0;
                            temp_v0_18->_sysStat2 = 0;
                            break;
                        case 6:
                        case 7:
                            temp_v0_18->_sysStat0 = 6;
                            temp_v0_18->_sysStat3 = 0;
                            temp_v0_18->_sysStat2 = 0;
                            temp_v0_18->_sysStat1 = 0;
                            temp_v0_18->_utilReturn = 1;
                            break;
                        case 0:
                        case 1:
                        case 2:
                        case 3:
                        case 5:
                        case 8:
                        case 9:
                        default:
                            temp_v0_18->_sysStat0 = 6;
                            temp_v0_18->_sysStat3 = 0;
                            temp_v0_18->_sysStat2 = 0;
                            temp_v0_18->_sysStat1 = 0;
                            temp_v0_18->_utilReturn = 1;
                            break;
                        }
                        break;
                    }
                    if (temp_v0_24 != 0) {
                        ((beSystem *)arg0->_system_)->_isResetEnable = 1;
                        return;
                    }
                    break;
                }
                break;
            case 3:
                if (((beNDMWMcSlot *)(ObjectList_GetAt_003e9260(((beNDMWMcUtilCtrl *)(temp_s0->_mcUtilCtrl))->_slot, temp_s1->_mcSelPoint)))->_isConnect != 1) {
                    FUN_003ecb20(temp_s2);
                    temp_v0_18->_sysStat0 = 7;
                    temp_v0_18->_sysStat3 = 0;
                    temp_v0_18->_sysStat2 = 0;
                    temp_v0_18->_sysStat1 = 0;
                    temp_v0_18->_utilReturn = 2;
                    return;
                }
                temp_v1_33 = temp_s0->_kindHard;
                var_a3_2 = -1;
                var_a4_2 = -1;
                switch (temp_v1_33) {
                case 0:
                    temp_v0_25 = arg1->player << 0x10;
                    var_a3_2 = temp_v0_25 | 0x1005;
                    var_a4_2 = temp_v0_25 | 0x1007;
                    break;
                case 1:
                    temp_v0_26 = arg1->player << 0x10;
                    var_a3_2 = temp_v0_26 | 0x2005;
                    var_a4_2 = temp_v0_26 | 0x2007;
                    break;
                case 2:
                    temp_v0_27 = arg1->player << 0x10;
                    var_a3_2 = temp_v0_27 | 0x3005;
                    var_a4_2 = temp_v0_27 | 0x3007;
                    break;
                }
                temp_v0_28 = FUN_003ecdc0(temp_s0, arg1->player, temp_s2, var_a3_2, var_a4_2, 1, 3);
                switch (temp_v0_28) {
                case 0:
                    break;
                case 1:
                    temp_v0_18->_sysStat1 = 4;
                    temp_v0_18->_sysStat3 = 0;
                    temp_v0_18->_sysStat2 = 0;
                    return;
                case 2:
                    temp_v0_18->_sysStat0 = 7;
                    temp_v0_18->_sysStat3 = 0;
                    temp_v0_18->_sysStat2 = 0;
                    temp_v0_18->_sysStat1 = 0;
                    temp_v0_18->_utilReturn = 1;
                    return;
                }
                break;
            case 4:
                temp_v1_34 = temp_v0_18->_sysStat2;
                switch (temp_v1_34) {
                case 0:
                    temp_v1_35 = temp_s0->_kindHard;
                    var_a1_6 = -1;
                    switch (temp_v1_35) {
                    case 0:
                        var_a1_6 = (arg1->player << 0x10) | 0x1008;
                        break;
                    case 1:
                        var_a1_6 = (arg1->player << 0x10) | 0x2008;
                        break;
                    case 2:
                        var_a1_6 = (arg1->player << 0x10) | 0x3008;
                        break;
                    }
                    FUN_003ecad0(temp_s2, var_a1_6);
                    ((beSystem *)arg0->_system_)->_isResetEnable = 0;
                    temp_v0_18->_sysStat2 = (temp_v0_18->_sysStat2 + 1);
                    temp_v0_18->_sysStat3 = 0;
                    return;
                case 1:
                    temp_v0_29 = beNDMWLoadCtrl2CommonIntf__StepFormatMemoryCard(temp_s0, arg1->player, temp_s2, temp_s1->_mcSelPoint, 3);
                    switch (temp_v0_29) {
                    case 0:
                        break;
                    case 1:
                        temp_v0_18->_sysStat1 = 1;
                        temp_v0_18->_sysStat3 = 0;
                        temp_v0_18->_sysStat2 = 0;
                        break;
                    case 2:
                        temp_v1_36 = ((beNDMWMcUtilCtrl *)(temp_s0->_mcUtilCtrl))->_result;
                        switch (temp_v1_36 - 3) {
                        case 9:
                            temp_v0_18->_sysStat0 = 6;
                            temp_v0_18->_sysStat3 = 0;
                            temp_v0_18->_sysStat2 = 0;
                            temp_v0_18->_sysStat1 = 0;
                            temp_v0_18->_utilReturn = 2;
                            break;
                        case 0:
                        case 1:
                        case 2:
                        case 3:
                        case 4:
                        case 5:
                        case 6:
                        case 7:
                        case 8:
                        default:
                            temp_v0_18->_utilReturn = 2;
                            temp_v0_18->_sysStat0 = 6;
                            temp_v0_18->_sysStat3 = 0;
                            temp_v0_18->_sysStat2 = 0;
                            temp_v0_18->_sysStat1 = 0;
                            break;
                        }
                        break;
                    }
                    if (temp_v0_29 != 0) {
                        ((beSystem *)arg0->_system_)->_isResetEnable = 1;
                        return;
                    }
                    break;
                }
                break;
            case 5:
                var_s2_4 = (void *)(0);
                for (var_s5_6 = 0; var_s5_6 < ((beNDMWLoadSlotPlayerList *)(*(int *)&temp_s0->_slotSaveData))->_count; var_s5_6++) {
                    beNDMWLoadSlotPlayer *elem_ = (beNDMWLoadSlotPlayer *)ObjectList_GetAt_003e9260((temp_s0->_slotSaveData), var_s5_6);
                    if (elem_->_connectNO == temp_s1->_mcSelPoint) {
                        var_s2_4 = (void *)(ObjectList_GetAt_003e9260((temp_s0->_slotSaveData), var_s5_6));
                        break;
                    }
                }
                if (var_s2_4 == 0) {
                    if (((beNDMWMcUtilCtrl *)(temp_s0->_mcUtilCtrl))->_isUseUtil != 0) {
                        temp_v0_18->_sysStat1 = (temp_v0_18->_sysStat1 + 1);
                        temp_v0_18->_sysStat3 = 0;
                        temp_v0_18->_sysStat2 = 0;
                        return;
                    }
                } else {
                    temp_s0_6 = (DW4ListRec *)(((beNDMWLoadSlotPlayer *)(var_s2_4))->_accessPlList);
                    temp_s1_2 = arg1->player;
                    temp_s4 = (*(int const *)&temp_s0_6->count);
                    if (temp_s4 < temp_s0_6->cap) {
                        temp_s0_6->count = (temp_s0_6->count + 1);
                    } else {
                        List_Resize(temp_s0_6, temp_s4 + 1, 4);
                    }
                    ((int *)DataList_GetData_003e9090(temp_s0_6))[temp_s4] = temp_s1_2;
                    temp_v0_18->_haveSaveData = (int)(var_s2_4);
                    temp_v0_18->_sysStat0 = 7;
                    temp_v0_18->_sysStat3 = 0;
                    temp_v0_18->_sysStat2 = 0;
                    temp_v0_18->_sysStat1 = 0;
                    temp_v0_18->_utilReturn = 0;
                    return;
                }
                break;
            case 6:
                temp_v0_30 = beNDMWLoadCtrl2CommonIntf__StepReadMedia(temp_s0, arg1->player, temp_s2, temp_s1->_mcSelPoint, 3);
                switch (temp_v0_30) {
                case 0:
                    break;
                case 1:
                    temp_v0_18->_sysStat0 = 7;
                    temp_v0_18->_sysStat3 = 0;
                    temp_v0_18->_sysStat2 = 0;
                    temp_v0_18->_sysStat1 = 0;
                    temp_v0_18->_utilReturn = 0;
                    return;
                case 2:
                    temp_v1_37 = ((beNDMWMcUtilCtrl *)(temp_s0->_mcUtilCtrl))->_result;
                    switch (temp_v1_37 - 3) {
                    case 4:
                        temp_v0_18->_sysStat1 = 3;
                        temp_v0_18->_sysStat3 = 0;
                        temp_v0_18->_sysStat2 = 0;
                        return;
                    case 6:
                    case 7:
                        temp_v0_18->_sysStat0 = 6;
                        temp_v0_18->_sysStat3 = 0;
                        temp_v0_18->_sysStat2 = 0;
                        temp_v0_18->_sysStat1 = 0;
                        temp_v0_18->_utilReturn = 1;
                        return;
                    case 5:
                        temp_v0_18->_sysStat1 = (temp_v0_18->_sysStat1 + 1);
                        temp_v0_18->_sysStat3 = 0;
                        temp_v0_18->_sysStat2 = 0;
                        return;
                    case 0:
                    case 1:
                    case 2:
                    case 3:
                    case 8:
                    case 9:
                    default:
                        temp_v0_18->_sysStat0 = 6;
                        temp_v0_18->_sysStat3 = 0;
                        temp_v0_18->_sysStat2 = 0;
                        temp_v0_18->_sysStat1 = 0;
                        temp_v0_18->_utilReturn = 1;
                        return;
                    }
                    break;
                }
                break;
            case 7:
                if (((beNDMWMcSlot *)(ObjectList_GetAt_003e9260(((beNDMWMcUtilCtrl *)(temp_s0->_mcUtilCtrl))->_slot, temp_s1->_mcSelPoint)))->_isConnect != 1) {
                    FUN_003ecb20(temp_s2);
                    temp_v0_18->_sysStat0 = 7;
                    temp_v0_18->_sysStat3 = 0;
                    temp_v0_18->_sysStat2 = 0;
                    temp_v0_18->_sysStat1 = 0;
                    temp_v0_18->_utilReturn = 2;
                    return;
                }
                temp_v1_38 = temp_v0_18->_sysStat2;
                switch (temp_v1_38) {
                case 0:
                    temp_v1_39 = temp_s0->_kindHard;
                    var_a1_7 = -1;
                    switch (temp_v1_39) {
                    case 0:
                        var_a1_7 = (arg1->player << 0x10) | 0x102B;
                        break;
                    case 1:
                        var_a1_7 = (arg1->player << 0x10) | 0x202B;
                        break;
                    case 2:
                        var_a1_7 = (arg1->player << 0x10) | 0x302B;
                        break;
                    }
                    FUN_003ecb00(temp_s2, var_a1_7);
                    temp_v0_18->_sysStat2 = (temp_v0_18->_sysStat2 + 1);
                    temp_v0_18->_sysStat3 = 0;
                    return;
                case 1:
                    if (!(beNDMWLoadIntf2MesWin__GetIsCtrl(temp_s2) & 0xFF)) {
                        temp_v0_18->_sysStat2 = (temp_v0_18->_sysStat2 + 1);
                        temp_v0_18->_sysStat3 = 0;
                        return;
                    }
                    break;
                case 2:
                    temp_v1_40 = temp_s0->_kindHard;
                    var_a1_8 = -1;
                    switch (temp_v1_40) {
                    case 0:
                        var_a1_8 = (arg1->player << 0x10) | 0x102C;
                        break;
                    case 1:
                        var_a1_8 = (arg1->player << 0x10) | 0x202C;
                        break;
                    case 2:
                        var_a1_8 = (arg1->player << 0x10) | 0x302C;
                        break;
                    }
                    FUN_003ecb00(temp_s2, var_a1_8);
                    temp_v0_18->_sysStat2 = (temp_v0_18->_sysStat2 + 1);
                    temp_v0_18->_sysStat3 = 0;
                    return;
                case 3:
                    if (!(beNDMWLoadIntf2MesWin__GetIsCtrl(temp_s2) & 0xFF)) {
                        temp_v0_18->_sysStat2 = (temp_v0_18->_sysStat2 + 1);
                        temp_v0_18->_sysStat3 = 0;
                        return;
                    }
                    break;
                case 4:
                    temp_v1_41 = temp_s0->_kindHard;
                    var_a1_9 = -1;
                    switch (temp_v1_41) {
                    case 0:
                        var_a1_9 = (arg1->player << 0x10) | 0x102D;
                        break;
                    case 1:
                        var_a1_9 = (arg1->player << 0x10) | 0x202D;
                        break;
                    case 2:
                        var_a1_9 = (arg1->player << 0x10) | 0x302D;
                        break;
                    }
                    FUN_003ecae0(temp_s2, var_a1_9, 0);
                    temp_v0_18->_sysStat2 = (temp_v0_18->_sysStat2 + 1);
                    temp_v0_18->_sysStat3 = 0;
                    return;
                case 5:
                    if (!(beNDMWLoadIntf2MesWin__GetIsCtrl(temp_s2) & 0xFF)) {
                        temp_v0_31 = FUN_003ecb80(temp_s2);
                        switch (temp_v0_31) {
                        case 0:
                            temp_v0_18->_sysStat2 = (temp_v0_18->_sysStat2 + 1);
                            temp_v0_18->_sysStat3 = 0;
                            return;
                        case 1:
                            temp_v0_18->_utilReturn = 1;
                            temp_v0_18->_sysStat0 = 7;
                            temp_v0_18->_sysStat3 = 0;
                            temp_v0_18->_sysStat2 = 0;
                            temp_v0_18->_sysStat1 = 0;
                            return;
                        }
                    }
                    break;
                case 6:
                    {
                    var_v0 = DW4SelAlloc::Get(&DAT_00587110[0], igObject_GetAllocator(arg0));
                    RecoveryRef<1> sp11C((void *)(FUN_003c6360(var_v0)));
                    var_s2_5 = 0;
                    do {
                        var_v0_2 = DW4SelAlloc::Get(&DAT_00587110[0], igObject_GetAllocator(arg0));
                        {
                        RecoveryRef<0> sp118((void *)(beNDMWDegiData_Create(var_v0_2)));
                        ObjectList_AppendRetained(((beNDMWLoadSlotPlayer *)(sp11C.value))->_saveDataList, sp118.value);
                        }
                        var_s2_5 += 1;
                    } while (var_s2_5 < 4);
                    var_s2_6 = 0;
                    do {
                        ((beNDMWDegiData *)(ObjectList_GetAt_003e9260(((beNDMWLoadSlotPlayer *)(sp11C.value))->_saveDataList, var_s2_6)))->_isUse = 0;
                        var_s2_6 += 1;
                    } while (var_s2_6 < 4);
                    ((beNDMWLoadSlotPlayer *)(sp11C.value))->_connectNO = (int)((int) temp_s1->_mcSelPoint);
                    temp_s2_2 = arg1->player;
                    temp_s1_3 = (DW4ListRec *)(((beNDMWLoadSlotPlayer *)(sp11C.value))->_accessPlList);
                    temp_s4_2 = (*(int const *)&temp_s1_3->count);
                    if (temp_s4_2 < temp_s1_3->cap) {
                        temp_s1_3->count = (temp_s1_3->count + 1);
                    } else {
                        List_Resize(temp_s1_3, temp_s4_2 + 1, 4);
                    }
                    ((int *)DataList_GetData_003e9090(temp_s1_3))[temp_s4_2] = temp_s2_2;
                    ObjectList_AppendRetained((temp_s0->_slotSaveData), sp11C.value);
                    temp_v0_18->_haveSaveData = (int)(sp11C.value);
                    }
                    temp_v0_18->_utilReturn = 0;
                    temp_v0_18->_sysStat0 = 7;
                    temp_v0_18->_sysStat3 = 0;
                    temp_v0_18->_sysStat2 = 0;
                    temp_v0_18->_sysStat1 = 0;
                    return;
                }
                break;
            }
            break;
        case 6:
            temp_s5_2 = (beNDMWLoadSavePlWork *)(ObjectList_GetAt_003e9260(temp_s0->_flagWork, arg1->player));
            if (temp_s0->_kindHard == 2) {
                beNDMWLoadIntf2SelSlot__UpdateSelection(temp_s1, 0, 0);
            }
            switch (temp_s5_2->_sysStat1) {
            case 0:
            temp_a0_22 = temp_s5_2->_sysStat2;
            switch (temp_a0_22) {
            case 0:
                temp_a0_23 = (void *)(temp_s0->_mcUtilCtrl);
                if (((beNDMWMcUtilCtrl *)(temp_a0_23))->_isFormatRun == 1) {
                    if (((beNDMWMcUtilCtrl *)(temp_a0_23))->_result == 0xC) {
                        beNDMWLoadIntf2SelSlot__RefreshSlotMarks(temp_s1, temp_s1->_mcSelPoint);
                    } else {
                        beNDMWLoadIntf2SelSlot__RefreshSlotMarks(temp_s1, -1);
                    }
                    temp_v1_42 = temp_s0->_kindHard;
                    var_a1_10 = -1;
                    switch (temp_v1_42) {
                    case 0:
                        var_a1_10 = (arg1->player << 0x10) | 0x100E;
                        break;
                    case 1:
                        var_a1_10 = (arg1->player << 0x10) | 0x200E;
                        break;
                    case 2:
                        var_a1_10 = (arg1->player << 0x10) | 0x300E;
                        break;
                    }
                    FUN_003ecb00(temp_s2, var_a1_10);
                } else if (((beNDMWMcSlot *)(ObjectList_GetAt_003e9260(((beNDMWMcUtilCtrl *)(temp_a0_23))->_slot, temp_s1->_mcSelPoint)))->_isConnect == 1) {
                    temp_s3_2 = ((beNDMWMcUtilCtrl *)(temp_s0->_mcUtilCtrl))->_result;
                    if (temp_s0->_kindHard != 2) {
                        if (temp_s3_2 == 0xC) {
                            beNDMWLoadIntf2SelSlot__RefreshSlotMarks(temp_s1, temp_s1->_mcSelPoint);
                        } else {
                            beNDMWLoadIntf2SelSlot__RefreshSlotMarks(temp_s1, -1);
                        }
                    }
                    switch (temp_s3_2 - 3) {
                    case 4:
                        temp_v1_43 = temp_s0->_kindHard;
                        var_a1_11 = -1;
                        switch (temp_v1_43) {
                        case 0:
                            var_a1_11 = (arg1->player << 0x10) | 0x1012;
                            break;
                        case 1:
                            var_a1_11 = (arg1->player << 0x10) | 0x2012;
                            break;
                        case 2:
                            var_a1_11 = (arg1->player << 0x10) | 0x3012;
                            break;
                        }
                        FUN_003ecb00(temp_s2, var_a1_11);
                        break;
                    case 6:
                        temp_v1_44 = temp_s0->_kindHard;
                        var_a1_12 = -1;
                        switch (temp_v1_44) {
                        case 0:
                            var_a1_12 = (arg1->player << 0x10) | 0x1014;
                            break;
                        case 1:
                            var_a1_12 = (arg1->player << 0x10) | 0x2014;
                            break;
                        case 2:
                            var_a1_12 = (arg1->player << 0x10) | 0x3014;
                            break;
                        }
                        FUN_003ecb00(temp_s2, var_a1_12);
                        break;
                    case 7:
                        temp_v1_45 = temp_s0->_kindHard;
                        var_a1_13 = -1;
                        switch (temp_v1_45) {
                        case 0:
                            var_a1_13 = (arg1->player << 0x10) | 0x1015;
                            break;
                        case 1:
                            var_a1_13 = (arg1->player << 0x10) | 0x2015;
                            break;
                        case 2:
                            var_a1_13 = (arg1->player << 0x10) | 0x3015;
                            break;
                        }
                        FUN_003ecb00(temp_s2, var_a1_13);
                        break;
                    case 2:
                        temp_v1_46 = temp_s0->_kindHard;
                        var_a1_14 = -1;
                        switch (temp_v1_46) {
                        case 0:
                            var_a1_14 = (arg1->player << 0x10) | 0x1010;
                            break;
                        case 1:
                            var_a1_14 = (arg1->player << 0x10) | 0x2010;
                            break;
                        case 2:
                            var_a1_14 = (arg1->player << 0x10) | 0x3010;
                            break;
                        }
                        FUN_003ecb00(temp_s2, var_a1_14);
                        break;
                    case 3:
                        temp_v1_47 = temp_s0->_kindHard;
                        var_a1_15 = -1;
                        switch (temp_v1_47) {
                        case 0:
                            var_a1_15 = (arg1->player << 0x10) | 0x1011;
                            break;
                        case 1:
                            var_a1_15 = (arg1->player << 0x10) | 0x2011;
                            break;
                        case 2:
                            var_a1_15 = (arg1->player << 0x10) | 0x3011;
                            break;
                        }
                        FUN_003ecb00(temp_s2, var_a1_15);
                        break;
                    case 5:
                        temp_v1_48 = temp_s0->_kindHard;
                        var_a1_16 = -1;
                        switch (temp_v1_48) {
                        case 0:
                            var_a1_16 = (arg1->player << 0x10) | 0x1013;
                            break;
                        case 1:
                            var_a1_16 = (arg1->player << 0x10) | 0x2013;
                            break;
                        case 2:
                            var_a1_16 = (arg1->player << 0x10) | 0x3013;
                            break;
                        }
                        FUN_003ecb00(temp_s2, var_a1_16);
                        break;
                    case 9:
                        temp_v1_49 = temp_s0->_kindHard;
                        var_a1_17 = -1;
                        switch (temp_v1_49) {
                        case 0:
                            var_a1_17 = (arg1->player << 0x10) | 0x1016;
                            break;
                        case 1:
                            var_a1_17 = (arg1->player << 0x10) | 0x2016;
                            break;
                        case 2:
                            var_a1_17 = (arg1->player << 0x10) | 0x3016;
                            break;
                        }
                        FUN_003ecb00(temp_s2, var_a1_17);
                        break;
                    case 1:
                        temp_v1_50 = temp_s0->_kindHard;
                        var_a1_18 = -1;
                        switch (temp_v1_50) {
                        case 0:
                            var_a1_18 = (arg1->player << 0x10) | 0x100F;
                            break;
                        case 1:
                            var_a1_18 = (arg1->player << 0x10) | 0x200F;
                            break;
                        case 2:
                            var_a1_18 = (arg1->player << 0x10) | 0x300F;
                            break;
                        }
                        FUN_003ecb00(temp_s2, var_a1_18);
                        break;
                    case 0:
                    case 8:
                    default:
                        temp_v1_51 = temp_s0->_kindHard;
                        var_a1_19 = -1;
                        switch (temp_v1_51) {
                        case 0:
                            var_a1_19 = (arg1->player << 0x10) | 0x100E;
                            break;
                        case 1:
                            var_a1_19 = (arg1->player << 0x10) | 0x200E;
                            break;
                        case 2:
                            var_a1_19 = (arg1->player << 0x10) | 0x300E;
                            break;
                        }
                        FUN_003ecb00(temp_s2, var_a1_19);
                        break;
                    }
                } else {
                    if (temp_s0->_kindHard != 2) {
                        beNDMWLoadIntf2SelSlot__RefreshSlotMarks(temp_s1, temp_s1->_mcSelPoint);
                    }
                    temp_v1_52 = temp_s0->_kindHard;
                    var_a1_20 = -1;
                    switch (temp_v1_52) {
                    case 0:
                        var_a1_20 = (arg1->player << 0x10) | 0x1016;
                        break;
                    case 1:
                        var_a1_20 = (arg1->player << 0x10) | 0x2016;
                        break;
                    case 2:
                        var_a1_20 = (arg1->player << 0x10) | 0x3016;
                        break;
                    }
                    FUN_003ecb00(temp_s2, var_a1_20);
                }
                temp_s5_2->_sysStat2 = (temp_s5_2->_sysStat2 + 1);
                temp_s5_2->_sysStat3 = 0;
                return;
            case 1:
                if (!(beNDMWLoadIntf2MesWin__GetIsCtrl(temp_s2) & 0xFF)) {
                    temp_s5_2->_utilReturn = 1;
                    temp_s5_2->_sysStat0 = 7;
                    temp_s5_2->_sysStat3 = 0;
                    temp_s5_2->_sysStat2 = 0;
                    temp_s5_2->_sysStat1 = 0;
                    return;
                }
                break;
            }
            break;
            }
            break;
        case 7:
            var_s1_10 = 0;
            do {
                temp_v0_32 = (beNDMWLoadSavePlWork *)(DataList_GetWordAt_003e9240(temp_s0->_flagWork, var_s1_10));
                var_s1_10 += 1;
                temp_v0_32->_sysStat0 = 8;
                temp_v0_32->_sysStat3 = 0;
                temp_v0_32->_sysStat2 = 0;
                temp_v0_32->_sysStat1 = 0;
            } while (var_s1_10 < 4);
            return;
        case 8:
            beNDMWLoadIntf2MesWin__EndSystemMessage(temp_s2);
            temp_v0_33 = (beNDMWLoadSavePlWork *)(DataList_GetWordAt_003e9240(temp_s0->_flagWork, arg1->player));
            temp_v0_33->_sysStat0 = 0;
            temp_v0_33->_sysStat3 = 0;
            temp_v0_33->_sysStat2 = 0;
            temp_v0_33->_sysStat1 = 0;
            { beNDMWLoadSavePlWork *r_ = (beNDMWLoadSavePlWork *)ObjectList_GetAt_003e9260(temp_s0->_flagWork, arg1->player); r_->_isCtrl = 1; }
            break;
        }
    }
}

}