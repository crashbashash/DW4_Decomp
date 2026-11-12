#include "dw4/reflected.h"

extern "C" int igObject_Destroy(void *);
extern "C" void * beBaseInfoDataList_Create(...);
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
struct DW4Sret4 { int v; DW4Sret4(const DW4Sret4 &o):v(o.v) {} };
extern "C" int DataList_GetData_003e9090(...);
extern "C" void *DataList_GetWordAt_003e9240(...);
extern "C" int FUN_002294f0(...);
extern "C" void *FUN_003c6360(...);
extern "C" void *beNDMWDegiData_Create(...);
extern "C" int FUN_003d9e10(...);
extern "C" int FUN_003d9e70(...);
extern "C" int FUN_003d9e90(...);
extern "C" int FUN_003da7c0(...);
extern "C" int FUN_003dafb0(...);
extern "C" int beNDMWLoadIntf2DataSelIntf__ClearStatesFrom(...);
extern "C" int FUN_003db060(...);
extern "C" int beNDMWLoadIntf2DataSelIntf__UpdateSelection(...);
extern "C" int FUN_003dbf90(...);
extern "C" int FUN_003dc2e0(...);
extern "C" int FUN_003dc590(...);
extern "C" int FUN_003dcab0(...);
extern "C" int FUN_003dcc60(...);
extern "C" int FUN_003dd160(...);
extern "C" int FUN_003dd440(...);
extern "C" int FUN_003dd6d0(...);
extern "C" int FUN_003e0b80(...);
extern "C" int beNDMWLoadIntf2SelSlot__Init(...);
extern "C" int beNDMWLoadIntf2SelSlot__Open(...);
extern "C" int beNDMWLoadIntf2SelSlot__UpdateSelection(...);
extern "C" int beNDMWLoadIntf2SelSlot__PublishCursor(...);
extern "C" int beNDMWLoadIntf2SelSlot__Close(...);
extern "C" int beNDMWLoadIntf2SelSlot__RefreshSlotMarks(...);
extern "C" int beNDMWLoadIntf2ComMdlCtrl__IsOpenQueueEmpty(...);
extern "C" int beNDMWLoadIntf2ComMdlCtrl__Close(...);
extern "C" int beNDMWLoadIntf2ComMdlCtrl__IsCloseQueueEmpty(...);
extern "C" int beNDMWLoadIntf2ComMdlCtrl__Poll(...);
extern "C" int beNDMWLoadSavePlWork__SetIsCtrl(...);
extern "C" int beNDMWLoadSavePlWork__GetIsRdy(...);
extern "C" int beNDMWLoadSavePlWork__GetIsEntry(...);
extern "C" int FUN_003e9220(...);
extern "C" void *FUN_003e9280(...);
extern "C" int FUN_003e92a0(...);
extern "C" DW4Sret4 FUN_003e9360(...);
extern "C" int FUN_003e93b0(...);
extern "C" int beNDMWLoadIntf2MesWin__Update(...);
extern "C" int beNDMWLoadIntf2MesWin__RequestOpen(...);
extern "C" int beNDMWLoadIntf2MesWin__RequestClose(...);
extern "C" int FUN_003ecad0(...);
extern "C" int FUN_003ecae0(...);
extern "C" int FUN_003ecb00(...);
extern "C" int FUN_003ecb20(...);
extern "C" int beNDMWLoadIntf2MesWin__GetIsCtrl(...);
extern "C" int FUN_003ecb80(...);
extern "C" int beNDMWLoadIntf2MesWin__RequestMesErase(...);
extern "C" int FUN_003ecba0(...);
extern "C" int beNDMWLoadIntf2MesWin__EndSystemMessage(...);
extern "C" int FUN_003ecdc0(...);
extern "C" int FUN_003ed050(...);
extern "C" int FUN_003ed2e0(...);
extern "C" int beNDMWLoadCtrl2CommonIntf__StepReadMedia(...);
extern "C" int FUN_003edc20(...);
extern "C" int beNDMWLoadCtrl2CommonIntf__StepFormatMemoryCard(...);
extern "C" int FUN_003ee250(...);
extern "C" int beNDMWLoadCtrl2CommonIntf__RemoveAccessPlayer(...);
extern "C" int beNDMWDegiData__LoadFromProperties(...);
extern "C" int List_Resize(...);
extern "C" int Memory_SelectAllocator_003e9370(...);
extern "C" void *ObjectList_GetAt_003e9260(...);
extern "C" int ObjectRef_Destruct_0033e9c0(...);
extern "C" int ObjectRef_Release_003e9110(...);
extern "C" int beMessenger_AppendString(...);
extern "C" void *bePadManager_GetPadForPlayer(...);
extern "C" void *igProperty_GetRecordByte(...);
extern "C" int * DAT_004cec70[4];
extern "C" int DAT_00519690[4];
extern "C" int DAT_005196b8[4];
extern "C" int DAT_005196c8[4];
extern "C" int DAT_005196d8[4];
extern "C" int DAT_005196e8[4];
extern "C" int DAT_005196f8[4];
extern "C" int DAT_00519700[4];
extern "C" int DAT_00519710[4];
extern "C" int DAT_00519720[4];
extern "C" int DAT_00519730[4];
extern "C" int DAT_00519740[4];
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
struct DW4ListRec { int w0; int w1; int count; int cap; int getCount() const { return count; } };
struct DW4SelAlloc { static int Get(const int *sel, int fb) { if (GPR_00554c14) return fb; else return Memory_GetAllocatorBySelector(*sel); } };
struct DW4Vec16 { int a, b, c, d; DW4Vec16(const DW4Vec16 &o); };
extern "C" int beNDMWLoadIntf2ComMdlCtrl__StartAt(void *, int, void *, void *, DW4Vec16 &, int);
class RecoveryCopiedRef { public: void *value; RecoveryCopiedRef(const DW4Sret4 &source) : value(beBaseInfoDataList_Create(source.v)) {} ~RecoveryCopiedRef(); };
extern "C" int *ObjectRef_Assign_003e92b0(void *, const RecoveryCopiedRef &);
struct DW4Fresh { static int *Assign(void *obj, int alloc) { RecoveryCopiedRef c(FUN_003e9360(Memory_SelectAllocator_003e9370(&DAT_00587110[0], alloc))); return ObjectRef_Assign_003e92b0(obj, c); } };
static inline void EnterState(beNDMWSaveIntfCtrlData *c, int state) { c->_st0 = state; c->_st3 = 0; c->_st2 = 0; c->_st1 = 0; }
static inline void NextStep(beNDMWSaveIntfCtrlData *c) { c->_st1 = c->_st1 + 1; c->_st3 = 0; c->_st2 = 0; }
static inline void SetStep(beNDMWSaveIntfCtrlData *c, int step) { c->_st1 = step; c->_st3 = 0; c->_st2 = 0; }
static inline void NextSubstep(beNDMWSaveIntfCtrlData *c) { c->_st2 = c->_st2 + 1; c->_st3 = 0; }
static inline void SetSubstep(beNDMWSaveIntfCtrlData *c, int substep) { c->_st2 = substep; c->_st3 = 0; }
static inline void NextTick(beNDMWSaveIntfCtrlData *c) { c->_st3 = c->_st3 + 1; }
static inline void EnterSlotState(beNDMWLoadIntf2SelSlot *c, int state) { c->_st0 = state; c->_st3 = 0; c->_st2 = 0; c->_st1 = 0; }
static inline void EnterStage(beNDMWLoadSavePlWork *w, int stage) { w->_sysStat0 = stage; w->_sysStat3 = 0; w->_sysStat2 = 0; w->_sysStat1 = 0; }
static inline void NextStageStep(beNDMWLoadSavePlWork *w) { w->_sysStat1 = w->_sysStat1 + 1; w->_sysStat3 = 0; w->_sysStat2 = 0; }
static inline void SetStageStep(beNDMWLoadSavePlWork *w, int step) { w->_sysStat1 = step; w->_sysStat3 = 0; w->_sysStat2 = 0; }
static inline void NextStageSubstep(beNDMWLoadSavePlWork *w) { w->_sysStat2 = w->_sysStat2 + 1; w->_sysStat3 = 0; }
static inline void SetStageSubstep(beNDMWLoadSavePlWork *w, int substep) { w->_sysStat2 = substep; w->_sysStat3 = 0; }
static inline void NextStageTick(beNDMWLoadSavePlWork *w) { w->_sysStat3 = w->_sysStat3 + 1; }
static inline int TextId(const beBaseInfoRam *host, int token) { return (host->_ramNo << 0x10) | token; }
extern "C" void Gap__Bec__beNDMWSaveIntf__vfunc_31(beNDMWSaveIntf *arg0, beBaseInfoRam *arg1);
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

void Gap__Bec__beNDMWSaveIntf__vfunc_31(beNDMWSaveIntf *arg0, beBaseInfoRam *arg1) {
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
    void *temp_s0_2;
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
    void *temp_v0_3;
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
    if (arg1->_dataList != 0) {
        tref = FUN_003e93b0(&arg1->_dataList);
        if (tref == 0) {
            DW4Fresh::Assign(&arg1->_dataList, igObject_GetAllocator(arg1));
        }
        temp_s3 = (beNDMWSaveIntfCtrlData *)(FUN_003e9280(FUN_003e92a0(&arg1->_dataList), DAT_00585be0[0], &DAT_00519670[0]));
        tref = FUN_003e93b0(&arg1->_dataList);
        if (tref == 0) {
            DW4Fresh::Assign(&arg1->_dataList, igObject_GetAllocator(arg1));
        }
        temp_s7 = (void *)(FUN_003e9280(FUN_003e92a0(&arg1->_dataList), DAT_00585be0[0], &DAT_00519678[0]));
        tref = FUN_003e93b0(&arg1->_dataList);
        if (tref == 0) {
            DW4Fresh::Assign(&arg1->_dataList, igObject_GetAllocator(arg1));
        }
        temp_s2 = (void *)(FUN_003e9280(FUN_003e92a0(&arg1->_dataList), DAT_00585be0[0], &DAT_00519688[0]));
        tref = FUN_003e93b0(&arg1->_dataList);
        if (tref == 0) {
            DW4Fresh::Assign(&arg1->_dataList, igObject_GetAllocator(arg1));
        }
        temp_s1 = (beNDMWLoadIntf2SelSlot *)(FUN_003e9280(FUN_003e92a0(&arg1->_dataList), DAT_00585be0[0], &DAT_00519690[0]));
        tref = FUN_003e93b0(&arg1->_dataList);
        if (tref == 0) {
            DW4Fresh::Assign(&arg1->_dataList, igObject_GetAllocator(arg1));
        }
        temp_s0 = (beNDMWLoadCtrl2CommonIntf *)(FUN_003e9280(FUN_003e92a0(&arg1->_dataList), DAT_00585be0[0], &DAT_00519698[0]));
        tref = FUN_003e93b0(&arg1->_dataList);
        if (tref == 0) {
            DW4Fresh::Assign(&arg1->_dataList, igObject_GetAllocator(arg1));
        }
        temp_s8 = (beNDMWLoadIntf2DegiStateCtrl *)(FUN_003e9280(FUN_003e92a0(&arg1->_dataList), DAT_00585be0[0], &DAT_005196a8[0]));
        tref = FUN_003e93b0(&arg1->_dataList);
        if (tref == 0) {
            DW4Fresh::Assign(&arg1->_dataList, igObject_GetAllocator(arg1));
        }
        temp_s5 = (beNDMWLoadIntf2DataSelIntf *)(FUN_003e9280(FUN_003e92a0(&arg1->_dataList), DAT_00585be0[0], &DAT_005196b8[0]));
        beNDMWLoadIntf2ComMdlCtrl__Poll(temp_s7);
        beNDMWLoadIntf2MesWin__Update(temp_s2);
        spB0 = 0;
        if (((beNDMWLoadSavePlWork *)(ObjectList_GetAt_003e9260(temp_s0->_flagWork, arg1->_ramNo)))->_isCtrl == 1) {
            spB0 = ((bePadData *)(bePadManager_GetPadForPlayer(arg0->_padManager, arg1->_ramNo)))->_trigger;
        }
        temp_v1 = ((beNDMWLoadSavePlWork *)(ObjectList_GetAt_003e9260(temp_s0->_flagWork, arg1->_ramNo)))->_sysStat0;
        switch (temp_v1) {
        case 1:
            spA0 = 0;
            temp_a0 = ((beNDMWLoadSavePlWork *)(ObjectList_GetAt_003e9260(temp_s0->_flagWork, arg1->_ramNo)))->_sysStat1;
            switch (temp_a0) {
            case 0:
                FUN_003ecba0(temp_s2, TextId(arg1, 0x51C));
                temp_v0 = (beNDMWLoadSavePlWork *)(DataList_GetWordAt_003e9240(temp_s0->_flagWork, arg1->_ramNo));
                SetStageStep(temp_v0, 1);
                break;
            case 1:
                temp_v0_2 = (beNDMWLoadSavePlWork *)(ObjectList_GetAt_003e9260(temp_s0->_flagWork, arg1->_ramNo));
                temp_v1_2 = temp_v0_2->_sysCount0 - 1;
                temp_v0_2->_sysCount0 = temp_v1_2;
                if (temp_v1_2 <= 0) {
                    { beNDMWLoadSavePlWork *r_ = (beNDMWLoadSavePlWork *)ObjectList_GetAt_003e9260(temp_s0->_flagWork, arg1->_ramNo); r_->_sysCount0 = 0; }
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
                            beNDMWLoadIntf2ComMdlCtrl__StartAt(temp_s7, arg1->_ramNo, &DAT_005196c8[0], &DAT_005196d8[0], spD0, 1);
                            NextStep(temp_s3);
                            return;
                                            case 1:
                        if ((beNDMWLoadIntf2ComMdlCtrl__IsOpenQueueEmpty(temp_s7) & 0xFF) == 1) {
                            NextStep(temp_s3);
                            return;
                        }
                                            break;
                    case 2:
                        beMessenger_SelectGroup(arg0->_messenger, &DAT_005196e0[0]);
                        beMessenger_AppendInt(arg0->_messenger, arg1->_ramNo);
                        beMessenger_DispatchSelected(arg0->_messenger, &DAT_005196e8[0]);
                        temp_v0_3 = beMessenger_GetObject(arg0->_messenger, 0);
                        if (*(unsigned char *)((char *)(igProperty_GetRecordByte(temp_v0_3, &DAT_005196f8[0])) + 12) == 1) {
                            beMessenger_SelectGroup(arg0->_messenger, &DAT_005196e0[0]);
                            beMessenger_AppendInt(arg0->_messenger, arg1->_ramNo);
                            beMessenger_DispatchSelected(arg0->_messenger, &DAT_00519700[0]);
                            beNDMWDegiData__LoadFromProperties(ObjectList_GetAt_003e9260(temp_s0->_gameUseData, arg1->_ramNo), temp_v0_3);
                            EnterState(temp_s3, 1);
                            { beNDMWLoadSavePlWork *r_ = (beNDMWLoadSavePlWork *)ObjectList_GetAt_003e9260(temp_s0->_flagWork, arg1->_ramNo); r_->_isRdy = 0; }
                            { beNDMWLoadSavePlWork *r_ = (beNDMWLoadSavePlWork *)ObjectList_GetAt_003e9260(temp_s0->_flagWork, arg1->_ramNo); r_->_isEntry = 1; }
                            return;
                        }
                        temp_a1 = arg1->_ramNo;
                        if (temp_a1 == 0) {
                            beMessenger_SelectGroup(arg0->_messenger, &DAT_005196e0[0]);
                            beMessenger_AppendInt(arg0->_messenger, arg1->_ramNo);
                            beMessenger_AppendString(arg0->_messenger, DAT_004cec70[0]);
                            beMessenger_AppendString(arg0->_messenger, &DAT_00519710[0]);
                            beMessenger_DispatchSelected(arg0->_messenger, &DAT_00519720[0]);
                            beMessenger_SelectGroup(arg0->_messenger, &DAT_005196e0[0]);
                            beMessenger_AppendInt(arg0->_messenger, arg1->_ramNo);
                            beMessenger_DispatchSelected(arg0->_messenger, &DAT_005196e8[0]);
                            temp_s0_2 = beMessenger_GetObject(arg0->_messenger, 0);
                            beNDMWDegiData__LoadFromProperties(ObjectList_GetAt_003e9260(temp_s0->_gameUseData, arg1->_ramNo), temp_s0_2);
                            return;
                        }
                        { beNDMWLoadSavePlWork *r_ = (beNDMWLoadSavePlWork *)ObjectList_GetAt_003e9260(temp_s0->_flagWork, temp_a1); r_->_isEntry = 0; }
                        EnterState(temp_s3, 9);
                        return;
                                            break;
                    }
                    break;
                case 1:
                    temp_a0_2 = temp_s3->_st1;
                    switch (temp_a0_2) {
                    case 0:
                        DW4Vec16 spC0(*(DW4Vec16 *)&((beNDMWSaveIntfComMdlCtrl *)temp_s7)->_pos);
                        beNDMWLoadIntf2ComMdlCtrl__StartAt(temp_s7, arg1->_ramNo, &DAT_00519730[0], &DAT_005196d8[0], spC0, 1);
                        beNDMWLoadIntf2MesWin__RequestOpen(temp_s2);
                        NextStep(temp_s3);
                        return;
                    case 1:
                        if ((beNDMWLoadIntf2ComMdlCtrl__IsOpenQueueEmpty(temp_s7) & 0xFF) == 1) {
                            beNDMWLoadIntf2MesWin__RequestMesErase(temp_s2);
                            EnterState(temp_s3, 2);
                            return;
                        }
                        break;
                    }
                    break;
                case 2:
                    temp_a0_3 = temp_s3->_st1;
                    switch (temp_a0_3) {
                    default:
                            FUN_003ecae0(temp_s2, TextId(arg1, 0x502), 0);
                            NextStep(temp_s3);
                            return;
                                            case 1:
                        if (!(beNDMWLoadIntf2MesWin__GetIsCtrl(temp_s2) & 0xFF)) {
                            temp_v0_4 = FUN_003ecb80(temp_s2);
                            switch (temp_v0_4) {
                            case 0:
                                EnterState(temp_s3, 4);
                                return;
                            case 1:
                                NextStep(temp_s3);
                                return;
                            }
                        }
                                            break;
                    case 2:
                        temp_a0_4 = temp_s3->_st2;
                        switch (temp_a0_4) {
                        case 0:
                            temp_s0_3 = arg1->_ramNo;
                            temp_a0_23 = ObjectList_GetAt_003e9260(temp_s8->_statDataList, 0);
                            FUN_003d9e10(temp_a0_23, 1, temp_s0_3);
                            NextSubstep(temp_s3);
                            return;
                        case 1:
                            if ((FUN_003da7c0(ObjectList_GetAt_003e9260(temp_s8->_statDataList, 0)) & 0xFF) == 1) {
                                if (arg1->_ramNo == 0) {
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
                                        EnterState(temp_s3, 8);
                                        return;
                                    }
                                    EnterState(temp_s3, 7);
                                    return;
                                }
                                EnterState(temp_s3, 7);
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
                            beNDMWLoadCtrl2CommonIntf__RemoveAccessPlayer(temp_s0, arg1->_ramNo, 2);
                            beNDMWLoadIntf2SelSlot__Init(temp_s1);
                            EnterSlotState(temp_s1, 0);
                            NextSubstep(temp_s3);
                            return;
                        case 1:
                            if ((beNDMWLoadIntf2SelSlot__Open(temp_s1, -1, 2) & 0xFF) == 1) {
                                temp_v1_7 = temp_s0->_kindHard;
                                var_a1 = -1;
                                switch (temp_v1_7) {
                                case 0:
                                    var_a1 = TextId(arg1, 0x1024);
                                    break;
                                case 1:
                                    var_a1 = TextId(arg1, 0x2024);
                                    break;
                                case 2:
                                    var_a1 = TextId(arg1, 0x3024);
                                    break;
                                }
                                FUN_003ecad0(temp_s2, var_a1);
                                EnterSlotState(temp_s1, 1);
                                NextStep(temp_s3);
                                return;
                            }
                            break;
                        }
                        break;
                    case 1:
                        temp_v1_8 = temp_s3->_st2;
                        switch (temp_v1_8) {
                        case 0:
                            if ((beNDMWLoadIntf2SelSlot__UpdateSelection(temp_s1, ((beNDMWLoadSavePlWork *)(ObjectList_GetAt_003e9260(temp_s0->_flagWork, arg1->_ramNo)))->_isCtrl, 1) & 0xFF) == 1) {
                                if (temp_s1->_isReOpenReq == 1) {
                                    NextStep(temp_s3);
                                    return;
                                }
                                if (temp_s1->_isCansel == 1) {
                                    NextStep(temp_s3);
                                    return;
                                }
                                NextSubstep(temp_s3);
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
                                    var_a1_2 = TextId(arg1, 0x1004);
                                    break;
                                case 1:
                                    var_a1_2 = TextId(arg1, 0x2004);
                                    break;
                                case 2:
                                    var_a1_2 = TextId(arg1, 0x3004);
                                    break;
                                }
                                FUN_003ecad0(temp_s2, var_a1_2);
                                FUN_003ee250(temp_s0, arg1->_ramNo, 4);
                                NextTick(temp_s3);
                                return;
                            case 1:
                                temp_a0_5 = ((beNDMWLoadSavePlWork *)(ObjectList_GetAt_003e9260(temp_s0->_flagWork, arg1->_ramNo)))->_utilReturn;
                                switch (temp_a0_5) {
                                case 0:
                                    NextStep(temp_s3);
                                    return;
                                case 1:
                                case 2:
                                    temp_v1_10 = temp_s0->_kindHard;
                                    var_a1_3 = -1;
                                    switch (temp_v1_10) {
                                    case 0:
                                        var_a1_3 = TextId(arg1, 0x1024);
                                        break;
                                    case 1:
                                        var_a1_3 = TextId(arg1, 0x2024);
                                        break;
                                    case 2:
                                        var_a1_3 = TextId(arg1, 0x3024);
                                        break;
                                    }
                                    FUN_003ecad0(temp_s2, var_a1_3);
                                    beNDMWLoadIntf2SelSlot__PublishCursor(temp_s1);
                                    SetStep(temp_s3, 1);
                                    return;
                                case 4:
                                    temp_v1_11 = temp_s0->_kindHard;
                                    var_a1_4 = -1;
                                    switch (temp_v1_11) {
                                    case 0:
                                        var_a1_4 = TextId(arg1, 0x1024);
                                        break;
                                    case 1:
                                        var_a1_4 = TextId(arg1, 0x2024);
                                        break;
                                    case 2:
                                        var_a1_4 = TextId(arg1, 0x3024);
                                        break;
                                    }
                                    FUN_003ecad0(temp_s2, var_a1_4);
                                    beNDMWLoadIntf2SelSlot__PublishCursor(temp_s1);
                                    SetStep(temp_s3, 1);
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
                            EnterSlotState(temp_s1, 2);
                            NextSubstep(temp_s3);
                            return;
                        case 1:
                            if ((beNDMWLoadIntf2SelSlot__Close(temp_s1) & 0xFF) == 1) {
                                if (temp_s1->_isReOpenReq == 1) {
                                    EnterState(temp_s3, 4);
                                    return;
                                }
                                if (temp_s1->_isCansel == 1) {
                                    EnterState(temp_s3, 2);
                                    return;
                                }
                                EnterState(temp_s3, 5);
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
                        FUN_003dafb0(temp_s5, arg1->_ramNo, 1);
                        NextStep(temp_s3);
                        return;
                    case 1:
                        temp_v1_13 = temp_s3->_st2;
                        switch (temp_v1_13) {
                        case 0:
                            beNDMWLoadIntf2DataSelIntf__ClearStatesFrom(temp_s5, 0, 1);
                            NextSubstep(temp_s3);
                            return;
                        case 1:
                            if ((FUN_003db060(temp_s5, 0, 1) & 0xFF) == 1) {
                                EnterState(temp_s3, 6);
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
                        if (((beNDMWLoadSavePlWork *)(ObjectList_GetAt_003e9260(temp_s0->_flagWork, arg1->_ramNo)))->_isCutConnect == 1) {
                            SetStep(temp_s3, 0x64);
                            return;
                        }
                        temp_a0_8 = temp_s3->_st2;
                        switch (temp_a0_8) {
                        case 0:
                            beNDMWLoadIntf2DataSelIntf__ClearStatesFrom(temp_s5, 0);
                            NextSubstep(temp_s3);
                            return;
                        case 1:
                            if ((beNDMWLoadIntf2DataSelIntf__UpdateSelection(temp_s5, 0) & 0xFF) == 1) {
                                if (temp_s5->_isCancel != 0) {
                                    NextSubstep(temp_s3);
                                    return;
                                }
                                NextStep(temp_s3);
                                return;
                            }
                            break;
                        case 2:
                            beNDMWLoadIntf2DataSelIntf__ClearStatesFrom(temp_s5, 0);
                            NextSubstep(temp_s3);
                            return;
                        case 3:
                            if ((FUN_003dbf90(temp_s5, 0) & 0xFF) == 1) {
                                EnterState(temp_s3, 4);
                                return;
                            }
                            break;
                        }
                        break;
                    case 0x1:
                        temp_a0_9 = temp_s3->_st2;
                        switch (temp_a0_9) {
                        case 0x0:
                            FUN_003ee250(temp_s0, arg1->_ramNo, 3);
                            NextSubstep(temp_s3);
                            return;
                        case 0x1:
                            temp_a0_10 = ((beNDMWLoadSavePlWork *)(ObjectList_GetAt_003e9260(temp_s0->_flagWork, arg1->_ramNo)))->_utilReturn;
                            switch (temp_a0_10) {
                            case 0:
                                temp_s3->_isOneSave = 1;
                                NextStep(temp_s3);
                                return;
                            case 1:
                                SetSubstep(temp_s3, 0x32);
                                return;
                            case 3:
                                temp_s1->_isSelect = 0;
                                SetStep(temp_s3, 0);
                                return;
                            case 2:
                                SetSubstep(temp_s3, 0x32);
                                return;
                            }
                            break;
                        case 0x32:
                            EnterSlotState(temp_s1, 2);
                            NextSubstep(temp_s3);
                            return;
                        case 0x33:
                            if ((beNDMWLoadIntf2SelSlot__Close(temp_s1, 1, 2) & 0xFF) == 1) {
                                SetStep(temp_s3, 0x64);
                                return;
                            }
                            break;
                        }
                        break;
                    case 0x2:
                        if (((beNDMWLoadSavePlWork *)(ObjectList_GetAt_003e9260(temp_s0->_flagWork, arg1->_ramNo)))->_isCutConnect == 1) {
                            SetStep(temp_s3, 0x64);
                            return;
                        }
                        temp_v1_14 = temp_s3->_st2;
                        switch (temp_v1_14) {
                        default:
                        case 0:
                            FUN_003ecb00(temp_s2, TextId(arg1, 0x50B));
                            NextSubstep(temp_s3);
                            return;
                        case 1:
                            if (!(beNDMWLoadIntf2MesWin__GetIsCtrl(temp_s2, 1) & 0xFF)) {
                                NextSubstep(temp_s3);
                                return;
                            }
                            break;
                        case 2:
                            FUN_003ecae0(temp_s2, TextId(arg1, 0x50D), 0);
                            NextSubstep(temp_s3);
                            return;
                        case 3:
                            if (!(beNDMWLoadIntf2MesWin__GetIsCtrl(temp_s2, 1) & 0xFF)) {
                                temp_v0_6 = FUN_003ecb80(temp_s2);
                                switch (temp_v0_6) {
                                case 0:
                                    SetSubstep(temp_s3, 5);
                                    return;
                                case 1:
                                    SetSubstep(temp_s3, 4);
                                    return;
                                }
                            }
                            break;
                        case 4:
                            temp_v1_15 = temp_s3->_st3;
                            switch (temp_v1_15) {
                            case 0:
                                beNDMWLoadIntf2DataSelIntf__ClearStatesFrom(temp_s5, 0);
                                NextTick(temp_s3);
                                return;
                            case 1:
                                if ((FUN_003dd160(temp_s5, 0) & 0xFF) == 1) {
                                    EnterState(temp_s3, 6);
                                    return;
                                }
                                break;
                            }
                            break;
                        case 5:
                            temp_v1_16 = temp_s3->_st3;
                            switch (temp_v1_16) {
                            case 0:
                                beNDMWLoadCtrl2CommonIntf__RemoveAccessPlayer(temp_s0, arg1->_ramNo);
                                beNDMWLoadIntf2DataSelIntf__ClearStatesFrom(temp_s5, 0);
                                NextTick(temp_s3);
                                return;
                            case 1:
                                if ((FUN_003dd440(temp_s5, 0) & 0xFF) == 1) {
                                    if (arg1->_ramNo == 0) {
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
                                            EnterState(temp_s3, 8);
                                            return;
                                        }
                                        EnterState(temp_s3, 7);
                                        return;
                                    }
                                    EnterState(temp_s3, 7);
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
                            NextSubstep(temp_s3);
                            return;
                        case 1:
                            if ((FUN_003dbf90(temp_s5, 0) & 0xFF) == 1) {
                                EnterState(temp_s3, 4);
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
                            FUN_003ecb00(temp_s2, TextId(arg1, 0x50E));
                            NextSubstep(temp_s3);
                            return;
                        case 1:
                            if (!(beNDMWLoadIntf2MesWin__GetIsCtrl(temp_s2) & 0xFF)) {
                                NextSubstep(temp_s3);
                                return;
                            }
                            break;
                        case 2:
                            FUN_003ecae0(temp_s2, TextId(arg1, 0x510), 0);
                            NextSubstep(temp_s3);
                            return;
                        case 3:
                            if (!(beNDMWLoadIntf2MesWin__GetIsCtrl(temp_s2) & 0xFF)) {
                                temp_v0_7 = FUN_003ecb80(temp_s2);
                                switch (temp_v0_7) {
                                case 0:
                                    EnterState(temp_s3, 8);
                                    return;
                                case 1:
                                    NextStep(temp_s3);
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
                                SetSubstep(temp_s3, 4);
                                return;
                            }
                            FUN_003ecb00(temp_s2, TextId(arg1, 0x527), 1);
                            NextSubstep(temp_s3);
                            return;
                        case 1:
                            if (!(beNDMWLoadIntf2MesWin__GetIsCtrl(temp_s2) & 0xFF)) {
                                NextSubstep(temp_s3);
                                return;
                            }
                            break;
                        case 2:
                            FUN_003ecae0(temp_s2, TextId(arg1, 0x529), 1);
                            NextSubstep(temp_s3);
                            return;
                        case 3:
                            if (!(beNDMWLoadIntf2MesWin__GetIsCtrl(temp_s2) & 0xFF)) {
                                temp_v0_8 = FUN_003ecb80(temp_s2);
                                switch (temp_v0_8) {
                                case 0:
                                    SetSubstep(temp_s3, 4);
                                    return;
                                case 1:
                                    SetSubstep(temp_s3, 5);
                                    return;
                                }
                            }
                            break;
                        case 4:
                            temp_v1_18 = temp_s3->_st3;
                            switch (temp_v1_18) {
                            case 0:
                                FUN_003d9e70(ObjectList_GetAt_003e9260(temp_s8->_statDataList, 0), 1);
                                beNDMWLoadIntf2ComMdlCtrl__Close(temp_s7, arg1->_ramNo, &DAT_00519730[0], &DAT_00519740[0], 1);
                                beNDMWLoadIntf2MesWin__RequestClose(temp_s2);
                                NextTick(temp_s3);
                                return;
                            case 1:
                                if (((FUN_003da7c0(ObjectList_GetAt_003e9260(temp_s8->_statDataList, 0)) & 0xFF) == 1) && ((beNDMWLoadIntf2ComMdlCtrl__IsCloseQueueEmpty(temp_s7) & 0xFF) == 1)) {
                                    EnterState(temp_s3, 9);
                                    { beNDMWLoadSavePlWork *r_ = (beNDMWLoadSavePlWork *)ObjectList_GetAt_003e9260(temp_s0->_flagWork, arg1->_ramNo); r_->_isEntry = 0; }
                                    { beNDMWLoadSavePlWork *r_ = (beNDMWLoadSavePlWork *)ObjectList_GetAt_003e9260(temp_s0->_flagWork, arg1->_ramNo); r_->_isRdy = 0; }
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
                                NextTick(temp_s3);
                                return;
                            case 1:
                                if ((FUN_003da7c0(ObjectList_GetAt_003e9260(temp_s8->_statDataList, 0)) & 0xFF) == 1) {
                                    EnterState(temp_s3, 2);
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
                        { beNDMWLoadSavePlWork *r_ = (beNDMWLoadSavePlWork *)ObjectList_GetAt_003e9260(temp_s0->_flagWork, arg1->_ramNo); r_->_isRdy = 1; }
                        temp_v0_9 = arg1->_ramNo;
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
                                FUN_003ecad0(temp_s2, TextId(arg1, 0x51D));
                                SetStep(temp_s3, 3);
                                return;
                            }
                            FUN_003ecad0(temp_s2, TextId(arg1, 0x530));
                            NextStep(temp_s3);
                            return;
                        }
                        FUN_003ecad0(temp_s2, (temp_v0_9 << 0x10) | 0x530);
                        NextStep(temp_s3);
                        return;
                    case 1:
                        temp_v1_20 = temp_s3->_st3;
                        switch (temp_v1_20) {
                        case 0:
                            if (arg1->_ramNo == 0) {
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
                                    SetStep(temp_s3, 3);
                                    return;
                                }
                                if (spB0 & 0x2000) {
                                    { beNDMWLoadSavePlWork *r_ = (beNDMWLoadSavePlWork *)ObjectList_GetAt_003e9260(temp_s0->_flagWork, arg1->_ramNo); r_->_isRdy = 0; }
                                    NextStep(temp_s3);
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
                                    FUN_003ecad0(temp_s2, TextId(arg1, 0x51F));
                                    NextTick(temp_s3);
                                    return;
                                }
                                if (spB0 & 0x2000) {
                                    { beNDMWLoadSavePlWork *r_ = (beNDMWLoadSavePlWork *)ObjectList_GetAt_003e9260(temp_s0->_flagWork, arg1->_ramNo); r_->_isRdy = 0; }
                                    NextStep(temp_s3);
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
                                FUN_003ecad0(temp_s2, TextId(arg1, 0x530));
                                temp_s3->_st3 = 0;
                                return;
                            }
                            if (spB0 & 0x2000) {
                                { beNDMWLoadSavePlWork *r_ = (beNDMWLoadSavePlWork *)ObjectList_GetAt_003e9260(temp_s0->_flagWork, arg1->_ramNo); r_->_isRdy = 0; }
                                NextStep(temp_s3);
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
                            NextSubstep(temp_s3);
                            return;
                        case 1:
                            if ((FUN_003da7c0(ObjectList_GetAt_003e9260(temp_s8->_statDataList, 0)) & 0xFF) == 1) {
                                EnterState(temp_s3, 2);
                                return;
                            }
                            break;
                        }
                        break;
                    case 3:
                        temp_a0_14 = temp_s3->_st2;
                        switch (temp_a0_14) {
                        case 0:
                            FUN_003ecad0(temp_s2, TextId(arg1, 0x51D));
                            NextSubstep(temp_s3);
                            return;
                        case 1:
                            if (spB0 & 0x2000) {
                                { beNDMWLoadSavePlWork *r_ = (beNDMWLoadSavePlWork *)ObjectList_GetAt_003e9260(temp_s0->_flagWork, arg1->_ramNo); r_->_isRdy = 0; }
                                SetStep(temp_s3, 2);
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
                                    NextSubstep(temp_s3);
                                    return;
                                }
                            } else {
                                FUN_003ecad0(temp_s2, TextId(arg1, 0x530));
                                SetStep(temp_s3, 1);
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
                        temp_v1_21 = arg1->_ramNo;
                        if (temp_v1_21 == 0) {
                            FUN_003ecad0(temp_s2, (temp_v1_21 << 0x10) | 0x51F);
                            var_s1_9 = 0;
                            temp_s0->_intfStat = 3;
                            temp_s0_5 = (void *)(temp_s0->_flagWork);
                            for (var_s1_9 = 0; var_s1_9 < FUN_002294f0(temp_s0_5); var_s1_9++) {
                                    beNDMWLoadSavePlWork__SetIsCtrl(DataList_GetWordAt_003e9240(temp_s0_5, var_s1_9), 0);
                            }
                        }
                        NextStep(temp_s3);
                        return;
                    case 1:
                        break;
                    }
                    break;
                }
            }
            break;
        case 2:
            temp_a0_16 = ((beNDMWLoadSavePlWork *)(ObjectList_GetAt_003e9260(temp_s0->_flagWork, arg1->_ramNo)))->_sysStat1;
            switch (temp_a0_16) {
            case 0:
                switch (temp_s3->_st0) {
                case 9:
                default:
                    temp_v0_10 = (beNDMWLoadSavePlWork *)(DataList_GetWordAt_003e9240(temp_s0->_flagWork, arg1->_ramNo));
                    SetStageStep(temp_v0_10, 1);
                    break;
                case 8:
                    beNDMWLoadIntf2ComMdlCtrl__Close(temp_s7, arg1->_ramNo, &DAT_00519730[0], &DAT_00519740[0], 1);
                    beNDMWLoadIntf2MesWin__RequestClose(temp_s2);
                    FUN_003d9e90(ObjectList_GetAt_003e9260(temp_s8->_statDataList, 0));
                    temp_v0_11 = (beNDMWLoadSavePlWork *)(DataList_GetWordAt_003e9240(temp_s0->_flagWork, arg1->_ramNo));
                    SetStageStep(temp_v0_11, 2);
                    break;
                }
                beNDMWLoadIntf2ComMdlCtrl__Close(temp_s7, arg1->_ramNo, &DAT_005196c8[0], &DAT_00519740[0], 1);
                return;
            case 1:
                if ((beNDMWLoadIntf2ComMdlCtrl__IsCloseQueueEmpty(temp_s7) & 0xFF) == 1) {
                    { beNDMWLoadSavePlWork *r_ = (beNDMWLoadSavePlWork *)ObjectList_GetAt_003e9260(temp_s0->_flagWork, arg1->_ramNo); r_->_isClose = 1; }
                    temp_v0_12 = (beNDMWLoadSavePlWork *)(DataList_GetWordAt_003e9240(temp_s0->_flagWork, arg1->_ramNo));
                    SetStageStep(temp_v0_12, 3);
                    return;
                }
                break;
            case 2:
                if (((FUN_003da7c0(ObjectList_GetAt_003e9260(temp_s8->_statDataList, 0)) & 0xFF) == 1) && ((beNDMWLoadIntf2ComMdlCtrl__IsCloseQueueEmpty(temp_s7) & 0xFF) == 1)) {
                    { beNDMWLoadSavePlWork *r_ = (beNDMWLoadSavePlWork *)ObjectList_GetAt_003e9260(temp_s0->_flagWork, arg1->_ramNo); r_->_isClose = 1; }
                    temp_v0_13 = (beNDMWLoadSavePlWork *)(DataList_GetWordAt_003e9240(temp_s0->_flagWork, arg1->_ramNo));
                    SetStageStep(temp_v0_13, 3);
                    return;
                }
                break;
            case 3:
                break;
            }
            break;
        case 3:
            temp_v0_14 = (beNDMWLoadSavePlWork *)(ObjectList_GetAt_003e9260(temp_s0->_flagWork, arg1->_ramNo));
            temp_a2 = temp_v0_14->_sysStat1;
            switch (temp_a2) {
            case 0x0:
                temp_v1_22 = temp_v0_14->_sysStat2;
                switch (temp_v1_22) {
                case 0:
                    beNDMWLoadIntf2DataSelIntf__ClearStatesFrom(temp_s5, 0);
                    NextStageSubstep(temp_v0_14);
                    return;
                case 1:
                    if ((FUN_003dc2e0(temp_s5, 0) & 0xFF) == 1) {
                        NextStageStep(temp_v0_14);
                        return;
                    }
                    break;
                }
                break;
            case 0x1:
                temp_v1_23 = temp_v0_14->_sysStat2;
                switch (temp_v1_23) {
                default:
                    if (((beNDMWLoadSavePlWork *)(ObjectList_GetAt_003e9260(temp_s0->_flagWork, arg1->_ramNo)))->_isCutConnect == 1) {
                        SetStageStep(temp_v0_14, 0x64);
                        return;
                    }
                    temp_a0_17 = temp_v0_14->_sysStat3;
                    switch (temp_a0_17) {
                    case 0:
                        if (((beNDMWDegiData *)(ObjectList_GetAt_003e9260(((beNDMWLoadSlotPlayer *)(temp_v0_14->_haveSaveData))->_saveDataList, temp_s5->_svDataSelPoint)))->_isUse == 0) {
                            FUN_003ecb00(temp_s2, TextId(arg1, 0x508));
                        } else {
                            FUN_003ecb00(temp_s2, TextId(arg1, 0x505));
                        }
                        NextStageTick(temp_v0_14);
                        return;
                    case 1:
                        if (!(beNDMWLoadIntf2MesWin__GetIsCtrl(temp_s2, 1) & 0xFF)) {
                            NextStageTick(temp_v0_14);
                            return;
                        }
                        break;
                    case 2:
                        if (((beNDMWDegiData *)(ObjectList_GetAt_003e9260(((beNDMWLoadSlotPlayer *)(temp_v0_14->_haveSaveData))->_saveDataList, temp_s5->_svDataSelPoint)))->_isUse == 1) {
                            FUN_003ecae0(temp_s2, TextId(arg1, 0x50A), 0);
                        } else {
                            FUN_003ecae0(temp_s2, TextId(arg1, 0x507), 0);
                        }
                        NextStageTick(temp_v0_14);
                        return;
                    case 3:
                        if (!(beNDMWLoadIntf2MesWin__GetIsCtrl(temp_s2, 1) & 0xFF)) {
                            NextStageSubstep(temp_v0_14);
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
                        NextStageTick(temp_v0_14);
                        return;
                    case 1:
                        if (FUN_003ecb80(temp_s2, 2) == 0) {
                            if ((FUN_003dcab0(temp_s5, 0) & 0xFF) == 1) {
                                NextStageSubstep(temp_v0_14);
                                return;
                            }
                        } else if ((FUN_003dc590(temp_s5, 0) & 0xFF) == 1) {
                            NextStageSubstep(temp_v0_14);
                            return;
                        }
                        break;
                    }
                    break;
                case 2:
                    temp_v0_15 = FUN_003ecb80(temp_s2, 2);
                    switch (temp_v0_15) {
                    case 0:
                        NextStageStep(temp_v0_14);
                        temp_v1_25 = temp_s0->_kindHard;
                        var_a1_5 = -1;
                        switch (temp_v1_25) {
                        case 0:
                            var_a1_5 = TextId(arg1, 0x100B);
                            break;
                        case 1:
                            var_a1_5 = TextId(arg1, 0x200B);
                            break;
                        case 2:
                            var_a1_5 = TextId(arg1, 0x300B);
                            break;
                        }
                        FUN_003ecad0(temp_s2, var_a1_5);
                        return;
                    case 1:
                        NextStageSubstep(temp_v0_14);
                        return;
                    }
                    break;
                case 3:
                    temp_v1_26 = temp_v0_14->_sysStat3;
                    switch (temp_v1_26) {
                    case 0:
                        beNDMWLoadIntf2DataSelIntf__ClearStatesFrom(temp_s5, 0);
                        NextStageTick(temp_v0_14);
                        return;
                    case 1:
                        if ((FUN_003dd160(temp_s5, 0) & 0xFF) == 1) {
                            EnterStage(temp_v0_14, 7);
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
                        EnterSlotState(temp_s1, 0);
                        NextStageTick(temp_v0_14);
                        return;
                    case 1:
                        if (((beNDMWMcSlot *)(ObjectList_GetAt_003e9260(((beNDMWMcUtilCtrl *)(temp_s0->_mcUtilCtrl))->_slot, temp_s1->_mcSelPoint)))->_isConnect != 1) {
                            NextStageTick(temp_v0_14);
                            return;
                        }
                        if ((beNDMWLoadIntf2SelSlot__Open(temp_s1, -1) & 0xFF) == 1) {
                            NextStageSubstep(temp_v0_14);
                            return;
                        }
                        break;
                    case 2:
                        if ((beNDMWLoadIntf2SelSlot__Open(temp_s1, -1) & 0xFF) == 1) {
                            ((beNDMWMcUtilCtrl *)(temp_s0->_mcUtilCtrl))->_result = 0xC;
                            ((beSystem *)arg0->_system_)->_isResetEnable = 1;
                            EnterStage(temp_v0_14, 6);
                            return;
                        }
                        break;
                    }
                    break;
                case 1:
                    temp_v0_16 = FUN_003ed050(temp_s0, arg1->_ramNo, temp_s2, temp_s1->_mcSelPoint, 3);
                    switch (temp_v0_16) {
                    case 0:
                        break;
                    case 1:
                        NextStageSubstep(temp_v0_14);
                        return;
                    case 2:
                        switch (((beNDMWMcUtilCtrl *)(temp_s0->_mcUtilCtrl))->_result) {
                        case 0xC:
                        ((beSystem *)arg0->_system_)->_isResetEnable = 1;
                        EnterStage(temp_v0_14, 6);
                        return;
                        default:
                            ((beSystem *)arg0->_system_)->_isResetEnable = 1;
                            EnterStage(temp_v0_14, 6);
                            return;
                        }
                    }
                    break;
                case 2:
                    temp_v0_17 = FUN_003edc20(temp_s0, arg1->_ramNo, temp_s2, temp_s1->_mcSelPoint, temp_s5->_svDataSelPoint, 3);
                    switch (temp_v0_17) {
                    case 0:
                        break;
                    case 1:
                        NextStageStep(temp_v0_14);
                        return;
                    case 2:
                        switch (((beNDMWMcUtilCtrl *)(temp_s0->_mcUtilCtrl))->_result) {
                        case 0xC:
                        ((beSystem *)arg0->_system_)->_isResetEnable = 1;
                        EnterStage(temp_v0_14, 6);
                        return;
                        default:
                            ((beSystem *)arg0->_system_)->_isResetEnable = 1;
                            EnterStage(temp_v0_14, 6);
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
                    EnterSlotState(temp_s1, 2);
                    NextStageSubstep(temp_v0_14);
                    return;
                case 1:
                    if ((beNDMWLoadIntf2SelSlot__Close(temp_s1) & 0xFF) == 1) {
                        NextStageSubstep(temp_v0_14);
                        return;
                    }
                    break;
                case 2:
                    beNDMWLoadIntf2DataSelIntf__ClearStatesFrom(temp_s5, 0);
                    NextStageSubstep(temp_v0_14);
                    return;
                case 3:
                    if ((FUN_003dcc60(temp_s5, 0) & 0xFF) == 1) {
                        NextStageSubstep(temp_v0_14);
                        return;
                    }
                    break;
                case 4:
                    beNDMWLoadIntf2DataSelIntf__ClearStatesFrom(temp_s5, 0);
                    NextStageSubstep(temp_v0_14);
                    return;
                case 5:
                    if ((FUN_003dd6d0(temp_s5, 0) & 0xFF) == 1) {
                        if (temp_v0_14->_sysStat3 == 0) {
                            EnterStage(temp_v0_14, 7);
                            temp_v0_14->_utilReturn = 0;
                            return;
                        }
                        NextStageStep(temp_v0_14);
                        return;
                    }
                    break;
                }
                break;
            case 0x4:
                temp_a0_18 = temp_v0_14->_sysStat3;
                switch (temp_a0_18) {
                case 0:
                    FUN_003ecb00(temp_s2, TextId(arg1, 0x50B));
                    NextStageTick(temp_v0_14);
                    return;
                case 1:
                    if (!(beNDMWLoadIntf2MesWin__GetIsCtrl(temp_s2) & 0xFF)) {
                        SetStageStep(temp_v0_14, 0x64);
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
                    NextStageSubstep(temp_v0_14);
                    beNDMWLoadIntf2DataSelIntf__ClearStatesFrom(temp_s5, 0);
                    return;
                case 1:
                    if ((FUN_003dbf90(temp_s5, 0) & 0xFF) == 1) {
                        EnterStage(temp_v0_14, 7);
                        temp_v0_14->_utilReturn = 2;
                        return;
                    }
                    break;
                }
                break;
            }
            break;
        case 4:
            temp_v0_18 = (beNDMWLoadSavePlWork *)(ObjectList_GetAt_003e9260(temp_s0->_flagWork, arg1->_ramNo));
            temp_v1_30 = temp_v0_18->_sysStat1;
            switch (temp_v1_30) {
            case 0:
                temp_v0_19 = FUN_003ed050(temp_s0, arg1->_ramNo, temp_s2, temp_s1->_mcSelPoint, 3);
                switch (temp_v0_19) {
                case 0:
                    break;
                case 1:
                    SetStageStep(temp_v0_18, 5);
                    return;
                case 2:
                    temp_a0_20 = ((beNDMWMcUtilCtrl *)(temp_s0->_mcUtilCtrl))->_result;
                    switch (temp_a0_20) {
                    case 2:
                        SetStageStep(temp_v0_18, 5);
                        return;
                    case 4:
                    case 3:
                        SetStageStep(temp_v0_18, 1);
                        return;
                    case 7:
                        SetStageStep(temp_v0_18, 3);
                        return;
                    case 12:
                        EnterStage(temp_v0_18, 6);
                        return;
                    default:
                        EnterStage(temp_v0_18, 6);
                        return;
                    }
                    break;
                }
                break;
            case 1:
                if (((beNDMWMcSlot *)(ObjectList_GetAt_003e9260(((beNDMWMcUtilCtrl *)(temp_s0->_mcUtilCtrl))->_slot, temp_s1->_mcSelPoint)))->_isConnect != 1) {
                    FUN_003ecb20(temp_s2);
                    EnterStage(temp_v0_18, 7);
                    temp_v0_18->_utilReturn = 2;
                    return;
                }
                temp_v1_31 = temp_s0->_kindHard;
                var_a3 = -1;
                var_a4 = -1;
                switch (temp_v1_31) {
                case 0:
                    temp_v0_20 = arg1->_ramNo << 0x10;
                    var_a3 = temp_v0_20 | 0x1000;
                    var_a4 = temp_v0_20 | 0x1002;
                    break;
                case 1:
                    temp_v0_21 = arg1->_ramNo << 0x10;
                    var_a3 = temp_v0_21 | 0x2000;
                    var_a4 = temp_v0_21 | 0x2002;
                    break;
                case 2:
                    temp_v0_22 = arg1->_ramNo << 0x10;
                    var_a3 = temp_v0_22 | 0x3000;
                    var_a4 = temp_v0_22 | 0x3002;
                    break;
                }
                temp_v0_23 = FUN_003ecdc0(temp_s0, arg1->_ramNo, temp_s2, var_a3, var_a4, 0, 3);
                switch (temp_v0_23) {
                case 0:
                    break;
                case 1:
                    SetStageStep(temp_v0_18, 2);
                    return;
                case 2:
                    EnterStage(temp_v0_18, 7);
                    temp_v0_18->_utilReturn = 1;
                    return;
                }
                break;
            case 2:
                temp_a0_21 = temp_v0_18->_sysStat2;
                switch (temp_a0_21) {
                case 0:
                    ((beSystem *)arg0->_system_)->_isResetEnable = 0;
                    NextStageSubstep(temp_v0_18);
                    return;
                case 1:
                    temp_v0_24 = FUN_003ed2e0(temp_s0, arg1->_ramNo, temp_s2, temp_s1->_mcSelPoint, 3);
                    switch (temp_v0_24) {
                    case 0:
                        break;
                    case 1:
                        SetStageStep(temp_v0_18, 5);
                        break;
                    case 2:
                        temp_v1_32 = ((beNDMWMcUtilCtrl *)(temp_s0->_mcUtilCtrl))->_result;
                        switch (temp_v1_32 - 3) {
                        case 4:
                            SetStageStep(temp_v0_18, 3);
                            break;
                        case 6:
                        case 7:
                            EnterStage(temp_v0_18, 6);
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
                            EnterStage(temp_v0_18, 6);
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
                    EnterStage(temp_v0_18, 7);
                    temp_v0_18->_utilReturn = 2;
                    return;
                }
                temp_v1_33 = temp_s0->_kindHard;
                var_a3_2 = -1;
                var_a4_2 = -1;
                switch (temp_v1_33) {
                case 0:
                    temp_v0_25 = arg1->_ramNo << 0x10;
                    var_a3_2 = temp_v0_25 | 0x1005;
                    var_a4_2 = temp_v0_25 | 0x1007;
                    break;
                case 1:
                    temp_v0_26 = arg1->_ramNo << 0x10;
                    var_a3_2 = temp_v0_26 | 0x2005;
                    var_a4_2 = temp_v0_26 | 0x2007;
                    break;
                case 2:
                    temp_v0_27 = arg1->_ramNo << 0x10;
                    var_a3_2 = temp_v0_27 | 0x3005;
                    var_a4_2 = temp_v0_27 | 0x3007;
                    break;
                }
                temp_v0_28 = FUN_003ecdc0(temp_s0, arg1->_ramNo, temp_s2, var_a3_2, var_a4_2, 1, 3);
                switch (temp_v0_28) {
                case 0:
                    break;
                case 1:
                    SetStageStep(temp_v0_18, 4);
                    return;
                case 2:
                    EnterStage(temp_v0_18, 7);
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
                        var_a1_6 = TextId(arg1, 0x1008);
                        break;
                    case 1:
                        var_a1_6 = TextId(arg1, 0x2008);
                        break;
                    case 2:
                        var_a1_6 = TextId(arg1, 0x3008);
                        break;
                    }
                    FUN_003ecad0(temp_s2, var_a1_6);
                    ((beSystem *)arg0->_system_)->_isResetEnable = 0;
                    NextStageSubstep(temp_v0_18);
                    return;
                case 1:
                    temp_v0_29 = beNDMWLoadCtrl2CommonIntf__StepFormatMemoryCard(temp_s0, arg1->_ramNo, temp_s2, temp_s1->_mcSelPoint, 3);
                    switch (temp_v0_29) {
                    case 0:
                        break;
                    case 1:
                        SetStageStep(temp_v0_18, 1);
                        break;
                    case 2:
                        temp_v1_36 = ((beNDMWMcUtilCtrl *)(temp_s0->_mcUtilCtrl))->_result;
                        switch (temp_v1_36 - 3) {
                        case 9:
                            EnterStage(temp_v0_18, 6);
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
                            EnterStage(temp_v0_18, 6);
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
                        NextStageStep(temp_v0_18);
                        return;
                    }
                } else {
                    temp_s0_6 = (DW4ListRec *)(((beNDMWLoadSlotPlayer *)(var_s2_4))->_accessPlList);
                    temp_s1_2 = arg1->_ramNo;
                    temp_s4 = temp_s0_6->count;
                    if (temp_s4 < temp_s0_6->cap) {
                        temp_s0_6->count = (temp_s0_6->getCount() + 1);
                    } else {
                        List_Resize(temp_s0_6, temp_s4 + 1, 4);
                    }
                    ((int *)DataList_GetData_003e9090(temp_s0_6))[temp_s4] = temp_s1_2;
                    temp_v0_18->_haveSaveData = (int)(var_s2_4);
                    EnterStage(temp_v0_18, 7);
                    temp_v0_18->_utilReturn = 0;
                    return;
                }
                break;
            case 6:
                temp_v0_30 = beNDMWLoadCtrl2CommonIntf__StepReadMedia(temp_s0, arg1->_ramNo, temp_s2, temp_s1->_mcSelPoint, 3);
                switch (temp_v0_30) {
                case 0:
                    break;
                case 1:
                    EnterStage(temp_v0_18, 7);
                    temp_v0_18->_utilReturn = 0;
                    return;
                case 2:
                    temp_v1_37 = ((beNDMWMcUtilCtrl *)(temp_s0->_mcUtilCtrl))->_result;
                    switch (temp_v1_37 - 3) {
                    case 4:
                        SetStageStep(temp_v0_18, 3);
                        return;
                    case 6:
                    case 7:
                        EnterStage(temp_v0_18, 6);
                        temp_v0_18->_utilReturn = 1;
                        return;
                    case 5:
                        NextStageStep(temp_v0_18);
                        return;
                    case 0:
                    case 1:
                    case 2:
                    case 3:
                    case 8:
                    case 9:
                    default:
                        EnterStage(temp_v0_18, 6);
                        temp_v0_18->_utilReturn = 1;
                        return;
                    }
                    break;
                }
                break;
            case 7:
                if (((beNDMWMcSlot *)(ObjectList_GetAt_003e9260(((beNDMWMcUtilCtrl *)(temp_s0->_mcUtilCtrl))->_slot, temp_s1->_mcSelPoint)))->_isConnect != 1) {
                    FUN_003ecb20(temp_s2);
                    EnterStage(temp_v0_18, 7);
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
                        var_a1_7 = TextId(arg1, 0x102B);
                        break;
                    case 1:
                        var_a1_7 = TextId(arg1, 0x202B);
                        break;
                    case 2:
                        var_a1_7 = TextId(arg1, 0x302B);
                        break;
                    }
                    FUN_003ecb00(temp_s2, var_a1_7);
                    NextStageSubstep(temp_v0_18);
                    return;
                case 1:
                    if (!(beNDMWLoadIntf2MesWin__GetIsCtrl(temp_s2) & 0xFF)) {
                        NextStageSubstep(temp_v0_18);
                        return;
                    }
                    break;
                case 2:
                    temp_v1_40 = temp_s0->_kindHard;
                    var_a1_8 = -1;
                    switch (temp_v1_40) {
                    case 0:
                        var_a1_8 = TextId(arg1, 0x102C);
                        break;
                    case 1:
                        var_a1_8 = TextId(arg1, 0x202C);
                        break;
                    case 2:
                        var_a1_8 = TextId(arg1, 0x302C);
                        break;
                    }
                    FUN_003ecb00(temp_s2, var_a1_8);
                    NextStageSubstep(temp_v0_18);
                    return;
                case 3:
                    if (!(beNDMWLoadIntf2MesWin__GetIsCtrl(temp_s2) & 0xFF)) {
                        NextStageSubstep(temp_v0_18);
                        return;
                    }
                    break;
                case 4:
                    temp_v1_41 = temp_s0->_kindHard;
                    var_a1_9 = -1;
                    switch (temp_v1_41) {
                    case 0:
                        var_a1_9 = TextId(arg1, 0x102D);
                        break;
                    case 1:
                        var_a1_9 = TextId(arg1, 0x202D);
                        break;
                    case 2:
                        var_a1_9 = TextId(arg1, 0x302D);
                        break;
                    }
                    FUN_003ecae0(temp_s2, var_a1_9, 0);
                    NextStageSubstep(temp_v0_18);
                    return;
                case 5:
                    if (!(beNDMWLoadIntf2MesWin__GetIsCtrl(temp_s2) & 0xFF)) {
                        temp_v0_31 = FUN_003ecb80(temp_s2);
                        switch (temp_v0_31) {
                        case 0:
                            NextStageSubstep(temp_v0_18);
                            return;
                        case 1:
                            temp_v0_18->_utilReturn = 1;
                            EnterStage(temp_v0_18, 7);
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
                    temp_s2_2 = arg1->_ramNo;
                    temp_s1_3 = (DW4ListRec *)(((beNDMWLoadSlotPlayer *)(sp11C.value))->_accessPlList);
                    temp_s4_2 = temp_s1_3->count;
                    if (temp_s4_2 < temp_s1_3->cap) {
                        temp_s1_3->count = (temp_s1_3->getCount() + 1);
                    } else {
                        List_Resize(temp_s1_3, temp_s4_2 + 1, 4);
                    }
                    ((int *)DataList_GetData_003e9090(temp_s1_3))[temp_s4_2] = temp_s2_2;
                    ObjectList_AppendRetained((temp_s0->_slotSaveData), sp11C.value);
                    temp_v0_18->_haveSaveData = (int)(sp11C.value);
                    }
                    temp_v0_18->_utilReturn = 0;
                    EnterStage(temp_v0_18, 7);
                    return;
                }
                break;
            }
            break;
        case 6:
            temp_s5_2 = (beNDMWLoadSavePlWork *)(ObjectList_GetAt_003e9260(temp_s0->_flagWork, arg1->_ramNo));
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
                        var_a1_10 = TextId(arg1, 0x100E);
                        break;
                    case 1:
                        var_a1_10 = TextId(arg1, 0x200E);
                        break;
                    case 2:
                        var_a1_10 = TextId(arg1, 0x300E);
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
                            var_a1_11 = TextId(arg1, 0x1012);
                            break;
                        case 1:
                            var_a1_11 = TextId(arg1, 0x2012);
                            break;
                        case 2:
                            var_a1_11 = TextId(arg1, 0x3012);
                            break;
                        }
                        FUN_003ecb00(temp_s2, var_a1_11);
                        break;
                    case 6:
                        temp_v1_44 = temp_s0->_kindHard;
                        var_a1_12 = -1;
                        switch (temp_v1_44) {
                        case 0:
                            var_a1_12 = TextId(arg1, 0x1014);
                            break;
                        case 1:
                            var_a1_12 = TextId(arg1, 0x2014);
                            break;
                        case 2:
                            var_a1_12 = TextId(arg1, 0x3014);
                            break;
                        }
                        FUN_003ecb00(temp_s2, var_a1_12);
                        break;
                    case 7:
                        temp_v1_45 = temp_s0->_kindHard;
                        var_a1_13 = -1;
                        switch (temp_v1_45) {
                        case 0:
                            var_a1_13 = TextId(arg1, 0x1015);
                            break;
                        case 1:
                            var_a1_13 = TextId(arg1, 0x2015);
                            break;
                        case 2:
                            var_a1_13 = TextId(arg1, 0x3015);
                            break;
                        }
                        FUN_003ecb00(temp_s2, var_a1_13);
                        break;
                    case 2:
                        temp_v1_46 = temp_s0->_kindHard;
                        var_a1_14 = -1;
                        switch (temp_v1_46) {
                        case 0:
                            var_a1_14 = TextId(arg1, 0x1010);
                            break;
                        case 1:
                            var_a1_14 = TextId(arg1, 0x2010);
                            break;
                        case 2:
                            var_a1_14 = TextId(arg1, 0x3010);
                            break;
                        }
                        FUN_003ecb00(temp_s2, var_a1_14);
                        break;
                    case 3:
                        temp_v1_47 = temp_s0->_kindHard;
                        var_a1_15 = -1;
                        switch (temp_v1_47) {
                        case 0:
                            var_a1_15 = TextId(arg1, 0x1011);
                            break;
                        case 1:
                            var_a1_15 = TextId(arg1, 0x2011);
                            break;
                        case 2:
                            var_a1_15 = TextId(arg1, 0x3011);
                            break;
                        }
                        FUN_003ecb00(temp_s2, var_a1_15);
                        break;
                    case 5:
                        temp_v1_48 = temp_s0->_kindHard;
                        var_a1_16 = -1;
                        switch (temp_v1_48) {
                        case 0:
                            var_a1_16 = TextId(arg1, 0x1013);
                            break;
                        case 1:
                            var_a1_16 = TextId(arg1, 0x2013);
                            break;
                        case 2:
                            var_a1_16 = TextId(arg1, 0x3013);
                            break;
                        }
                        FUN_003ecb00(temp_s2, var_a1_16);
                        break;
                    case 9:
                        temp_v1_49 = temp_s0->_kindHard;
                        var_a1_17 = -1;
                        switch (temp_v1_49) {
                        case 0:
                            var_a1_17 = TextId(arg1, 0x1016);
                            break;
                        case 1:
                            var_a1_17 = TextId(arg1, 0x2016);
                            break;
                        case 2:
                            var_a1_17 = TextId(arg1, 0x3016);
                            break;
                        }
                        FUN_003ecb00(temp_s2, var_a1_17);
                        break;
                    case 1:
                        temp_v1_50 = temp_s0->_kindHard;
                        var_a1_18 = -1;
                        switch (temp_v1_50) {
                        case 0:
                            var_a1_18 = TextId(arg1, 0x100F);
                            break;
                        case 1:
                            var_a1_18 = TextId(arg1, 0x200F);
                            break;
                        case 2:
                            var_a1_18 = TextId(arg1, 0x300F);
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
                            var_a1_19 = TextId(arg1, 0x100E);
                            break;
                        case 1:
                            var_a1_19 = TextId(arg1, 0x200E);
                            break;
                        case 2:
                            var_a1_19 = TextId(arg1, 0x300E);
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
                        var_a1_20 = TextId(arg1, 0x1016);
                        break;
                    case 1:
                        var_a1_20 = TextId(arg1, 0x2016);
                        break;
                    case 2:
                        var_a1_20 = TextId(arg1, 0x3016);
                        break;
                    }
                    FUN_003ecb00(temp_s2, var_a1_20);
                }
                NextStageSubstep(temp_s5_2);
                return;
            case 1:
                if (!(beNDMWLoadIntf2MesWin__GetIsCtrl(temp_s2) & 0xFF)) {
                    temp_s5_2->_utilReturn = 1;
                    EnterStage(temp_s5_2, 7);
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
                EnterStage(temp_v0_32, 8);
            } while (var_s1_10 < 4);
            return;
        case 8:
            beNDMWLoadIntf2MesWin__EndSystemMessage(temp_s2);
            temp_v0_33 = (beNDMWLoadSavePlWork *)(DataList_GetWordAt_003e9240(temp_s0->_flagWork, arg1->_ramNo));
            EnterStage(temp_v0_33, 0);
            { beNDMWLoadSavePlWork *r_ = (beNDMWLoadSavePlWork *)ObjectList_GetAt_003e9260(temp_s0->_flagWork, arg1->_ramNo); r_->_isCtrl = 1; }
            break;
        }
    }
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

