#include "dw4/reflected.h"
#include "dw4/igSmartPointer.h"
#include "dw4/igTDataList.h"
#define SELECT_ALLOCATOR(var, arg) { int base_ = igObject_GetAllocator(arg); if (g_useOwnerAllocator != 0) var = base_; else var = Memory_GetAllocatorBySelector(g_defaultAllocatorSelector[0]); }
#define RELEASE(q) { igObject *o_ = (igObject *)(q); if (o_) { o_->_refCount = o_->_refCount - 1; if ((o_->_refCount & 0x7fffff) == 0) igObject_Destroy(o_); } }
#define RETAIN(q) { igObject *o_ = (igObject *)(q); if (o_) o_->_refCount = o_->_refCount + 1; }

/* The messages a beModelCtrl answers, in the order of its message enum (beModelCtrl_GetMessageEnum). */
enum beModelCtrlMessage {
    MSG_GENERATE,
    MSG_GENERATE_NDSP,
    MSG_REMOVE,
    MSG_GETINFONAME,
    MSG_GETINFONAME_RUN,
    MSG_SETMATRIX,
    MSG_CHKBULLET,
    MSG_SETLABEL,
    MSG_SETEFFECT,
    MSG_SETSOUND,
    MSG_GETMATRIX,
    MSG_GETMATRIX_ALL,
    MSG_GETMATRIX_ACTIVE,
    MSG_GETTRCDATA,
    MSG_GETHP,
    MSG_SETHP,
    MSG_GETRECNO,
    MSG_ACTION1,
    MSG_ONCTRL,
    MSG_OFCTRL,
    MSG_ONFREEZE,
    MSG_OFFREEZE,
    MSG_SETLODHIGH,
    MSG_RESETLODHIGH,
    MSG_MOVETRANS,
    MSG_SETCONVEYOR,
    MSG_SETQUICKSAND,
    MSG_SETSLIPPEDFLOOR,
    MSG_ISRUN,
    MSG_ISSEQNAME,
    MSG_ONHITBULLETBOX,
    MSG_OFHITBULLETBOX,
    MSG_GETSEQNAMELIST,
};
/* Local views of the retail vtables: a dN entry holds the place of a slot this file does not call, and
 * vfunc_NN dispatches slot NN of the class named in each comment. */
/* beModelCtrl and its subclasses */
class beModelCtrlSlots {
public:
    virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19();
    virtual int vfunc_20();
    virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29();
    virtual int vfunc_30();
    virtual void d31(); virtual void d32();
    virtual int vfunc_33(beBaseInfoRam *ram, const char *message);
    virtual void d34();
    virtual int vfunc_35(const char *kind);
    virtual void vfunc_36(beBaseInfoRam *ram);
    virtual void vfunc_37(beBaseInfoRam *ram);
    virtual void vfunc_38(beBaseInfoRam *ram);
    virtual void vfunc_39(beBaseInfoRam *ram);
    virtual void vfunc_40(beBaseInfoRam *ram);
    virtual void vfunc_41(beBaseInfoRam *ram);
    virtual void vfunc_42(beBaseInfoRam *ram);
    virtual void vfunc_43(beBaseInfoRam *ram);
    virtual void vfunc_44(beBaseInfoRam *ram);
    virtual void vfunc_45(beBaseInfoRam *ram);
    virtual void vfunc_46(beBaseInfoRam *ram);
    virtual unsigned char vfunc_47(beBaseInfoRam *ram, const char *message);
};
/* any igObject: slot 20 returns its meta object */
class igObjectSlots {
public:
    virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19();
    virtual int vfunc_20();
};
/* beSystem's random generator: slot 22 draws the next number */
class RandomSlots {
public:
    virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21();
    virtual int vfunc_22();
};
/* beModelCtrlInfoRideOn2/3/4: slot 21 moves the ride-on model */
class beModelCtrlInfoRideOnSlots {
public:
    virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20();
    virtual void vfunc_21(void *matrix);
};
/* beModelCtrlNode2 (an igTransform): slot 35 sets the node matrix */
class beModelCtrlNode2Slots {
public:
    virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual void d32(); virtual void d33(); virtual void d34();
    virtual void vfunc_35(void *matrix);
};
/* igLod: slot 20 meta object; slot 29 follows an edit of its range list */
class igLodSlots {
public:
    virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19();
    virtual int vfunc_20();
    virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28();
    virtual void vfunc_29();
};
extern "C" int igTraversal_RegisterFunction(int, int, void (*)(void));
extern "C" int beMeterCtrlNode_ResolveMetaObject(...);
extern "C" void beMeterCtrlNode_RegisterTraversalFunction(void);
extern "C" void beModelCtrl_DrawDebugHitBox(void);
extern "C" int thunk_igAABox_Transform(...);
extern "C" int Memory_GetAllocatorBySelector(...);
extern "C" int igObject_GetAllocator(...);
extern "C" int ObjectList_AppendRetained(...);
extern "C" int igInsightCore_FindManager(...);
extern "C" int Gap__Core__igObject__vfunc_30(void);
extern "C" void Gap__Core__igObject__vfunc_39(void);
extern "C" void Gap__Core__igObject__vfunc_46(void);
extern "C" void Gap__Core__igObject__vfunc_45(void);
extern "C" void Gap__Core__igObject__vfunc_44(void);
extern "C" void Gap__Core__igObject__vfunc_43(void);
extern "C" void Gap__Core__igObject__vfunc_41(void);
extern "C" void Gap__Core__igObject__vfunc_40(void);
extern "C" void Gap__Core__igObject__vfunc_42(void);
extern "C" int Gap__Core__igObject__vfunc_47(void);
extern "C" int Gap__Core__igObject__vfunc_25(...);
extern "C" int Gap__Bec__beModelCtrl__vfunc_25(beModelCtrl *self, beModelCtrlInfo *info);
extern "C" int beMessenger_RegisterReceiverFromInfo(...);
extern "C" void * igProperty_FindByName(...);
extern "C" void Gap__Bec__beNDMWMdlMapCursor__vfunc_37(void);
extern "C" int StringPool_Allocate(...);
extern "C" int StringPool_Construct(...);
extern "C" int StringChunk_ReleaseHeader(...);
extern "C" int beBaseInfoRam_IsTimerExpired(void *, void *);
extern "C" int beTargetObj_SetTarget(void *, void *);
extern "C" int beTargetObj_SelectTarget(void *, void *, void *);
extern "C" float beTargetObj_GetTargetDistanceSq(...);
extern "C" float beTargetObj_GetTargetBearing(int, int, int, float);
extern "C" int beBaseInfoRam_StartTimer(...);
extern "C" int __fixsfdi(float);
extern "C" int strcmp(...);
extern "C" int beMessenger_SendNamed(...);
extern "C" int Matrix44_Copy(...);
extern "C" void igObject_Destroy(void *);
extern "C" void Matrix44_SetTranslation(float *matrix, void *vec3);
extern "C" int Gap__Bec__beModelCtrlInfoRideOn2__vfunc_20(void);
extern "C" float sqrtf(float);
extern "C" int Matrix44_GetTranslation(int, float *);
extern "C" void *beModelCtrlInfoRideOn_Create(...);
extern "C" int beMessenger_GetBool(...);
extern "C" int beMessenger_GetBoolCount(...);
extern "C" int beMessenger_GetInt(...);
extern "C" int beMessenger_GetStringCount(...);
extern "C" float beBaseInfoRam_GetTimerFrameDelta(...);
extern "C" int Matrix44_TranslateLocal(...);
extern "C" int beBaseInfoRam_HasTimer(...);
extern "C" void *beModelCtrlMoveObject_Create(...);
extern "C" float atan2f(float, float);
extern "C" int Vec3f_TransformDirection(...);
extern "C" void * StringPool_Intern(...);
extern "C" int beMessenger_GetObjectCount(...);
extern "C" void beModelCtrlInfoWork_SetSeqLabel(beModelCtrl *self, beBaseInfoRam *ram, beModelCtrlInfoWork *work, const char *seqName, const char *labelName);
extern "C" int sprintf(...);
extern "C" int beLua__RunNamedChunk(...);
extern "C" int beBaseInfoRam_RemoveTimer(...);

extern "C" int beModelCtrlSubCom_StopType(int, int, int);
extern "C" void beModelCtrl_UpdateMuteki(beModelCtrl *self, beBaseInfoRam *ram, beModelCtrlInfoWork *work);
extern "C" int FUN_00190ed0(int, float, float, float);
extern "C" int igMatrix44f_SetIdentity(...);
extern "C" int FUN_001904f0(...);
extern "C" int FUN_001906d0(...);
extern "C" int FUN_00191f30(...);
extern "C" void beModelCtrl_UpdateKeyCtrl(beModelCtrl *self, beBaseInfo *info, beBaseInfoRam *ram, beModelCtrlInfoWork *work);
extern "C" int beModelCtrlSubCom_Update(...);
extern "C" int beMessenger_AppendString(...);
extern "C" int beMessenger_DispatchSelected(...);
extern "C" int beMessenger_GetMatrix(...);
extern "C" int beMessenger_GetMatrixCount(...);
extern "C" int beMessenger_SelectReceivers(...);
extern "C" int igAABox_Transform(...);
extern "C" bool FUN_0018b050(void *, int);
extern "C" void FUN_00191670(void *, void *, float);
extern "C" int beModelCtrl_GetMessageEnum(void);
extern "C" void beModelCtrlSubCom_AddSound(int, const char *, float);
extern "C" void beMessenger_AppendBool(int, unsigned char);
extern "C" void beMessenger_AppendInt(int, int);
extern "C" void beMessenger_AppendMatrix(int, void *);
extern "C" void beMessenger_AppendObject(int, void *);
extern "C" float beMessenger_GetFloat(int, int);
extern "C" int beMessenger_GetIntCount(int);
extern "C" const char * beMessenger_GetString(...);
extern "C" int beMessenger_GetVec3Count(int);
extern "C" void beMessenger_PopArgContext(int);
extern "C" void beMessenger_PushArgContext(int);
extern "C" unsigned beMessenger_ResolveEnumValue(int, int, const char *);
extern "C" int Gap__Bec__beModelCtrlInfoRideOn4__vfunc_20(void);
extern "C" int Gap__Bec__beModelCtrlInfoRideOn3__vfunc_20(void);
extern "C" int Gap__Bec__beModelCtrl__vfunc_20(void);
extern "C" int beMeterCtrlNode_Traverse(void *node, igCommonTraversal *traversal, void *data);
extern "C" int beMeterCtrlNode_TraversalFunction(igCommonTraversal *traversal, void *node);
extern "C" int DAT_00562640[4];

/* three floats as the retail code copies them: a plain aggregate, without igVec3f's constructors */
struct Vec3 { float x, y, z; };
extern "C" igAABox * igAABox_CreateInstance(...);
extern "C" void FUN_0018b990(igAABox *, float *);
extern "C" int g_propertyNameField[4];
extern "C" char HIT[];
extern "C" int g_defaultAllocatorSelector[4];
extern "C" unsigned char g_useOwnerAllocator;
extern "C" igAABoxList *beModelCtrlInfoHitBody_GetAABoxList(beModelCtrlInfoHitBody *body, beBaseInfoRam *ram, int matrix, long long time);
extern "C" int g_beTargetObj_metaObject[4];
extern "C" int g_beLua_metaObject[4];
extern "C" void beModelCtrl_ResolveManagers(beModelCtrl *self);
extern "C" int g_beModelCtrlInfo_metaObject[4];
extern "C" char MODELCTRL_7[];
extern "C" char HITPLAYERBULLET_2[];
extern "C" char HITPLAYERTALK_2[];
extern "C" char HITENEMYBULLET_2[];
extern "C" void Gap__Core__igObject__vfunc_29(beModelCtrl *self, beBaseInfoRam *ram);
extern "C" int g_beNDMWMdlMapCursor_metaObject[4];
extern "C" igObject * beBaseInfoDataList_Create(...);
extern "C" int emptyString[4];
extern "C" char ONE_3[];
extern "C" char AITIMER[];
extern "C" char NEAR[];
extern "C" char WPOS[];
extern "C" char PLAYER_3[];
extern "C" char SQ_WALK[];
extern "C" int g_stringPool[4];

/* Owning stack reference to a pooled string token (count at p[-1], chunk header at p[-2]). */
class StringRef {
public:
    char *p;
    StringRef(char *s) : p(s) {}
    StringRef() {}
    ~StringRef() { if (p) { int *h = (int *)p - 2; int r = ((int *)p)[-1] - 1; ((int *)p)[-1] = r; if (r == 0) StringChunk_ReleaseHeader(*h, h); } }
};
struct DataListInstall { static inline void go(beBaseInfoRam *ram, const igSmartPointer<igObject> &fresh) {
    igObject *o = fresh.p;
    igObject *old;
    if (o != 0) {
        o->_refCount = o->_refCount + 1;
    }
    old = (igObject *)ram->_dataList;
    if (old != 0) {
        old->_refCount = old->_refCount - 1;
        if ((old->_refCount & 0x7FFFFF) == 0) {
            igObject_Destroy(old);
        }
    }
    ram->_dataList = (int)o;
}
static inline void make(beBaseInfoRam *ram, int v) { igSmartPointer<igObject> fresh(beBaseInfoDataList_Create(v)); go(ram, fresh); }
};
extern "C" void beModelCtrl_UpdateMapAI(beModelCtrl *self, void *info, beBaseInfoRam *ram, beModelCtrlInfoWork *work, beModelCtrlInfoDataAIM *aim);
extern "C" char onWalk[];
extern "C" char toWalk[];
extern "C" char toWait[];
extern "C" char isLive[];
extern "C" char onFall[];
extern "C" char noFall[];
extern "C" int beModelCtrl_RunCtrl(beModelCtrl *self, beModelCtrlInfoWork *work, beModelCtrlCTRL *command);

extern "C" void beModelCtrl_UpdateHomingAI(beModelCtrl *self, beBaseInfo *info, beBaseInfoRam *ram, beModelCtrlInfoWork *work, beModelCtrlInfoDataAIH *homing);
extern "C" char AIM[];
extern "C" char AIH[];
extern "C" void Gap__Core__igObject__vfunc_38(beModelCtrl *self, beBaseInfoRam *ram);
extern "C" char ACTION_2[];
extern "C" int beModelCtrl_RunAction(beModelCtrl *self, beModelCtrlInfo *info, beBaseInfoRam *ram, beModelCtrlACTION *command);
extern "C" igObject * beMessenger_GetObject(...);
extern "C" char GETMATRIX_2[];
extern "C" void beModelCtrlInfoRideOn_SetModel(beModelCtrlInfoRideOn *self, int modelName, int ramNo, int messenger);
extern "C" int beModelCtrlInfoRideOn_IsModel(beModelCtrlInfoRideOn *self, int modelName, int ramNo);
extern "C" int g_beModelCtrlInfoRideOn2_metaObject[4];
extern "C" void Gap__Bec__beModelCtrlInfoRideOn2__vfunc_21(beModelCtrlInfoRideOn2 *self);
extern "C" float g_vec3Zero[4];
extern "C" void Gap__Bec__beModelCtrlInfoRideOn3__vfunc_21(beModelCtrlInfoRideOn3 *self, void *m);
extern "C" char HITWALL[];
extern "C" char HITWALLFULL[];
extern "C" char HITLANDDELIVER[];
extern "C" char WHit[];
extern "C" char HITFLOORCHECK[];
extern "C" char emptyString_2[];
extern "C" char HITFLOORADJUST[];
extern "C" char SQ_SLEP[];
extern "C" char SQ_FALL[];
extern "C" char FHit[];
struct Slot { beModelCtrlInfoRideOn4 *p; void set(beModelCtrlInfoRideOn4 *n) { beModelCtrlInfoRideOn4 *o = p; if (o) { --o->_refCount; if (((unsigned long long)(long long)o->_refCount & 0x7fffffULL) == 0) igObject_Destroy(o); } p = n; } };
/* Scope holder for the freshly built ride-on record. The constructor takes the allocation result,
 * so the protected range starts after the allocation call. */
struct RideOnRef { beModelCtrlInfoRideOn4 *p; RideOnRef(beModelCtrlInfoRideOn4 *x) { p = x; } ~RideOnRef() { beModelCtrlInfoRideOn4 *o = p; if (o) { --o->_refCount; if (((unsigned long long)(long long)o->_refCount & 0x7fffffULL) == 0) igObject_Destroy(o); } } };
extern "C" void beModelCtrl_CheckWallAndFloor(beModelCtrl *self, beBaseInfo *info, beBaseInfoRam *ram, beModelCtrlInfoWork *work);
extern "C" unsigned char beModelCtrl_QueryMove(beModelCtrl *self, beBaseInfoRam *ram, beModelCtrlInfoWork *work, unsigned int query);
extern "C" void beModelCtrlMoveObject_Start(beModelCtrlMoveObject *self, int mode, float value, float frames, float endTime);
extern "C" void beModelCtrlMoveObject_Stop(beModelCtrlMoveObject *self);
extern "C" float beModelCtrlMoveObject_Step(beModelCtrlMoveObject *self, float frames);

extern "C" char KEIKATIMER[];
extern "C" void beModelCtrl_ApplyMoves(beModelCtrl *self, beBaseInfo *info, beBaseInfoRam *ram, beModelCtrlInfoWork *work);
extern "C" int g_vec3ZAxis[4];
extern "C" char Stop[];
extern "C" char Move[];
extern "C" char Push[];
extern "C" char Back[];
extern "C" char Jump[];
extern "C" char Fall[];
extern "C" char JOINT[];
extern "C" char GETTRCDATA[];
extern "C" int g_beModelCtrlMOVEEX_metaObject[4];
extern "C" int g_beModelCtrlMOVE_metaObject[4];

struct MoveRef {
    igObject *p;
    MoveRef() { p = 0; }
    ~MoveRef() { igObject *o = p; if (o != 0) { o->_refCount = o->_refCount - 1; if ((o->_refCount & 0x7fffff) == 0) igObject_Destroy(o); } }
};

/* matching construct: the data-list holder (slot 152) must sit below the move-object holder (slot 156), so it is
 * a local of a static inline member (allocated after the caller's); al/p/old stay the caller's locals. */
struct Locals {
    static inline void CreateDataList(beBaseInfoRam *arg1, int &al, igObject *&p, igObject *&old) {
        SELECT_ALLOCATOR(al, arg1);
        {
            igSmartPointer<igObject> sp98((igObject *)((void *)beBaseInfoDataList_Create(al)));
            p = sp98.p;
            if (p != 0) p->_refCount = p->_refCount + 1;
            old = (igObject *)arg1->_dataList;
            if (old != 0) {
                old->_refCount = old->_refCount - 1;
                if ((old->_refCount & 0x7FFFFF) == 0) igObject_Destroy(old);
            }
            arg1->_dataList = (int)p;
        }
    }
};
extern "C" unsigned char beModelCtrl_RunMove(beModelCtrl *self, beBaseInfoRam *ram, beModelCtrlInfoWork *work, igObject *command);
extern "C" float D_004c8fa0[4];
extern "C" int beModelCtrl_RunPdMove(beModelCtrl *self, beBaseInfoRam *ram, beModelCtrlInfoWork *work, beModelCtrlPDMOVE *command);
extern "C" int beModelCtrl_RunLabelCtrl(beModelCtrl *self, beBaseInfoRam *ram, beModelCtrlInfoWork *work, beModelCtrlLABELCTRL *command);

extern "C" char s_s_lua[];
extern "C" beBaseInfoRam *g_mdlEntity[4];
extern "C" int g_mdlRamNo[4];
extern "C" int g_mdlMatrix[4];
extern "C" int g_mdlMaxHp[4];
extern "C" int g_mdlHp[4];
extern "C" int g_mdlRecNo[4];
extern "C" int g_mdlInfoName[4];
extern "C" int g_mdlBulletKind[4];
extern "C" int g_mdlBulletBoxNo[4];
extern "C" int g_hitterInfoName[4];
extern "C" int g_bltShootRamNo[4];
extern "C" int g_hitterRecNo[4];
extern "C" char g_mdlDmgTurn[16];
extern "C" int g_mdlCallName[4];
extern "C" void beModelCtrl_CallLua(beModelCtrl *self, beBaseInfoRam *ram, const char *function, const char *callName, const char *infoName, int bulletKind, int bulletBoxNo, const char *hitterName, int hitterRamNo, int hitterRecNo);
extern "C" char BHit_2[];
extern "C" int beModelCtrl_RunLuaCall(beModelCtrl *self, beBaseInfo *info, beBaseInfoRam *ram, beModelCtrlInfoWork *work, beModelCtrlLUACALL *command);
extern "C" char aim[];
extern "C" char WPos[];
extern "C" Vec3 *g_mdlWorldPosTarget[4];
extern "C" int beModelCtrl_RunAiMap(beModelCtrl *self, beModelCtrlInfo *info, beBaseInfoRam *ram, beModelCtrlInfoWork *work, beModelCtrlAIMAP *command);
extern "C" unsigned char beModelCtrl_RunMsgBox(beModelCtrl *self, beModelCtrlInfo *info, beModelCtrlInfoWork *work, beModelCtrlMSGBOX *command);
extern "C" int beModelCtrl_RunJump(beModelCtrl *self, beBaseInfoRam *ram, beModelCtrlJUMP *command);
extern "C" int beModelCtrl_StartWaitCheck(beModelCtrl *self, beModelCtrlInfoWork *work, beModelCtrlWCHECK *command);
extern "C" char TurnY[];
extern "C" char Landing[];
extern "C" char Action[];
extern "C" char ISCOMEND[];
extern "C" char Moving[];
extern "C" char Rotation[];
extern "C" void beModelCtrl_UpdateWaitCheck(beModelCtrl *self, beModelCtrlInfo *info, beBaseInfoRam *ram, beModelCtrlInfoWork *work);
extern "C" int beModelCtrlSubCom_AddHitBox(int, beModelCtrlHITBOX *);
extern "C" char AllClear[];
extern "C" char Set[];
extern "C" int g_beModelCtrlSCHitBox_metaObject[4];
extern "C" int beModelCtrl_RunHitBox(beModelCtrl *self, beBaseInfoRam *ram, beModelCtrlInfoWork *work, beModelCtrlHITBOX *command);
extern "C" char OFFWALL[];
extern "C" char ONWALL[];
extern "C" char OFFFLOOR[];
extern "C" char ONFLOOR[];
struct MutekiNameOf { static int *Get(beModelCtrlMUTEKI *m) { if (m->_name != 0) { return (int *)m->_name; } return &emptyString[0]; } };
extern "C" int beModelCtrl_RunMuteki(beModelCtrl *self, beBaseInfoRam *ram, beModelCtrlInfoWork *work, beModelCtrlMUTEKI *command);
extern "C" int g_beModelCtrlCTRL_metaObject[4];
extern "C" int g_beModelCtrlACTION_metaObject[4];
extern "C" int g_beModelCtrlMOVERL_metaObject[4];
extern "C" int g_beModelCtrlPDMOVE_metaObject[4];
extern "C" int g_beModelCtrlWCHECK_metaObject[4];
extern "C" int g_beModelCtrlHITBOX_metaObject[4];
extern "C" int g_beModelCtrlMUTEKI_metaObject[4];
extern "C" int g_beModelCtrlLABELCTRL_metaObject[4];
extern "C" int g_beModelCtrlLUACALL_metaObject[4];
extern "C" int g_beModelCtrlAIMAP_metaObject[4];
extern "C" int g_beModelCtrlMSGBOX_metaObject[4];
extern "C" int g_beModelCtrlLABEL_metaObject[4];
extern "C" int g_beModelCtrlJUMP_metaObject[4];
extern "C" void beModelCtrl_RunCommands(beModelCtrl *self, beModelCtrlInfo *info, beBaseInfoRam *ram, beModelCtrlInfoWork *work);

extern "C" void beModelCtrl_UpdateDirection(beModelCtrl *self, beBaseInfo *info, beBaseInfoRam *ram, beModelCtrlInfoWork *work, int force);
extern "C" char SQ_NONE[];
extern "C" char SQ_ERAS_2[];
extern "C" char REMOVE_2[];
extern "C" char GETBONEMATRIX[];
extern "C" void * DAT_00561288[4];
extern "C" void Gap__Core__igObject__vfunc_31(beModelCtrl *self, beBaseInfoRam *ram);
extern "C" int FUN_001cafc0(int list, StringRef *key, int);
extern "C" StringRef StringList_CopyRetained(int list, int index);
extern "C" int beModelCtrlInfoWork_FindSeqLabel(beModelCtrl *self, beModelCtrlInfoWork *work);
struct Rel { static inline void go(igAABox *object) {
    if (object) {
        --object->_refCount;
        if (((unsigned long long)(long long)(int)object->_refCount & 0x7fffffULL) == 0)
            igObject_Destroy(object);
    }
} };
extern "C" void beModelCtrl_UpdateBound(beModelCtrl *self, beModelCtrlNode2 *node, igAABox *box);
extern "C" beModelCtrlNode2 *beModelCtrlNode2_Create(int);
extern "C" beModelCtrlInfoRideOn4 *beModelCtrlInfoRideOn4_Create(int);
extern "C" beModelCtrlInfoRideOn3 *beModelCtrlInfoRideOn3_Create(int);
extern "C" beModelCtrlInfoRideOn2 *beModelCtrlInfoRideOn2_Create(int);
extern "C" beModelCtrlInfoAI *beModelCtrlInfoAI_Create(int);
extern "C" beModelCtrlInfoHitBody *beModelCtrlInfoHitBody_Create(int);
extern "C" void beModelCtrlSubCom_StopAll(int, beBaseInfoRam *);
extern "C" void beModelCtrlSubCom_AddEffect(int, const char *, const char *, Vec3 *, Vec3 *, int, float, int);
extern "C" void beBaseInfoRam_SetAllTimerScales(beBaseInfoRam *, float);
extern "C" void beBaseInfoRam_RemoveAllTimers(beBaseInfoRam *);
extern "C" void Matrix44_FromTranslation(void *, Vec3 *);
extern "C" void beMessenger_GetVec3(Vec3 *, int, int);
extern "C" float DAT_004c8fb8[4];
extern "C" float DAT_004e0ef0[4];
extern "C" float g_vec3XAxis[4];
extern "C" float g_vec3YAxis[4];
extern "C" char SQ_WAIT_2[];
extern "C" char NDSP_2[];
extern "C" char SEQ[];
extern "C" char TRC[];
extern "C" char ONFREEZE[];
extern "C" char OFFREEZE[];
extern "C" char GETRECNO[];
extern "C" char hit[];
extern "C" char Hit[];
extern "C" char SQ_ERAS2[];
extern "C" int g_igLod_metaObject[4];

/* Owning stack references to the objects this handler creates before binding them: kind 0 the AI
 * info, 1 the hit-body info, 2..4 the ride-on infos of commands 25..27 and 5 their model node. */
template <int kind> struct ObjRef {
    igObject *p;
    ObjRef(igObject *q) : p(q) {}
    ~ObjRef() { igObject *x = p; if (x) { --x->_refCount; if ((x->_refCount & 0x7fffff) == 0) igObject_Destroy(x); } }
};

/* Creates the ram's data list on first use.
 * matching construct: the handler's ride-on local doubles as the list's holder; a local of its own moves registers */
struct DataList {
    static inline void Ensure(beBaseInfoRam *ram, beModelCtrlInfoRideOn *&held) {
        if (ram->_dataList == 0) {
            int a = igObject_GetAllocator(ram);
            a = g_useOwnerAllocator ? a : Memory_GetAllocatorBySelector(g_defaultAllocatorSelector[0]);
            igSmartPointer<igObject> r((igObject *)((beBaseInfoDataList *)beBaseInfoDataList_Create(a)));
            held = (beModelCtrlInfoRideOn *)r.p;
            RETAIN(held)
            RELEASE(ram->_dataList)
            ram->_dataList = (int)held;
        }
    }
};
extern "C" int Gap__Bec__beModelCtrl__vfunc_33(beModelCtrl *self, beBaseInfoRam *ram, const char *message);
extern "C" int g_beModelCtrlInfoRideOn4_metaObject[4];
extern "C" int g_beModelCtrlInfoRideOn3_metaObject[4];
extern "C" int g_beModelCtrl_metaObject[4];

int beMeterCtrlNode_TraversalFunction(igCommonTraversal *traversal, void *node)
{
    return beMeterCtrlNode_Traverse(node, traversal, node);
}

void beMeterCtrlNode_RegisterTraversalFunction(void) {
    igTraversal_RegisterFunction(DAT_00562640[0], beMeterCtrlNode_ResolveMetaObject(), (void (*)())beMeterCtrlNode_TraversalFunction);
}

void beModelCtrl_DrawDebugHitBox(void)
{
}

igAABoxList *beModelCtrlInfoHitBody_GetAABoxList(beModelCtrlInfoHitBody *body, beBaseInfoRam *ram, int matrix, long long time) {
    if (body->_isFirst != 0) {
        beModelCtrlInfoDataHit *hit = ((beModelCtrlInfoDataHit *)igProperty_FindByName(((beBaseInfo *)ram->_parentInfo)->_dataList, g_propertyNameField[0], HIT));
        igAABoxList *boxes = (igAABoxList *)hit->_hitBulletAABoxList;
        body->_orgAABoxList = (int)boxes;
        body->_count = boxes->_count;
        int n = body->_count;
        int i;
        for (i = 0; i < n; i++) {
            igAABox *box = ((igAABox **)((igAABoxList *)body->_orgAABoxList)->_data)[i];
            float center[3];
            float below[3];
            float above[3];
            int j;
            FUN_0018b990(box, (float *)center);
            j = 0;
            {
                float *pCenter = center, *pBelow = below, *pAbove = above; igAABox *pBox = box;
                for (; j < 3; j++) {
                    float d = *(float *)&pCenter[0] - pBox->_min[0];
                    *pBelow = d < 0.0f ? -d : d;
                    d = pBox->_max[0] - *pCenter;
                    *pAbove = d < 0.0f ? -d : d;
                    pBox = (igAABox *)((char *)pBox + 4); pCenter++; pBelow++; pAbove++;
                }
            }
            {
                int k;
                igDataList *list = (igDataList *)body->_AABoxMinList;
                k = list->_count;
                if (k < list->_capacity) list->_count = k + 1; else List_Resize(list, k + 1, 12);
                Vec3 *extent = &((Vec3 *)list->_data)[k];
                extent->x = below[0]; extent->y = below[1]; extent->z = below[2];
            }
            {
                int k;
                igDataList *list = (igDataList *)body->_AABoxMaxList;
                k = list->_count;
                if (k < list->_capacity) list->_count = k + 1; else List_Resize(list, k + 1, 12);
                Vec3 *extent = &((Vec3 *)list->_data)[k];
                extent->x = above[0]; extent->y = above[1]; extent->z = above[2];
            }
            {
                int alloc = igObject_GetAllocator(body);
                int a;
                if (g_useOwnerAllocator != 0) a = alloc; else a = Memory_GetAllocatorBySelector(g_defaultAllocatorSelector[0]);
                igSmartPointer<igAABox> created(igAABox_CreateInstance(a));
                { igAABox *boxPtr = created.p; igAABoxList *boxList = (igAABoxList *)body->_AABoxList; ObjectList_AppendRetained(boxList, boxPtr); }
            }
        }
        body->_isFirst = 0;
    }
    if (time != body->_calcTime) {
        int n;
        int i;
        body->_calcTime = time;
        n = body->_count;
        for (i = 0; i < n; i++) {
            igAABox *src = ((igAABox **)((igAABoxList *)body->_orgAABoxList)->_data)[i];
            igAABox *dst = ((igAABox **)((igAABoxList *)body->_AABoxList)->_data)[i];
            float center[3];
            float below[3];
            float above[3];
            int k;
            for (k = 0; k < 3; k++) { float *a = &dst->_min[k]; float *box = &dst->_max[k]; *a = src->_min[k]; *box = src->_max[k]; }
            thunk_igAABox_Transform(dst, matrix);
            center[0] = (dst->_min[0]) * 0.5f + (dst->_max[0]) * 0.5f;
            center[1] = (dst->_min[1]) * 0.5f + (dst->_max[1]) * 0.5f;
            center[2] = (dst->_min[2]) * 0.5f + (dst->_max[2]) * 0.5f;
            *(Vec3 *)below = ((Vec3 *)((igDataList *)body->_AABoxMinList)->_data)[i];
            *(Vec3 *)above = ((Vec3 *)((igDataList *)body->_AABoxMaxList)->_data)[i];
            for (k = 0; k < 3; k++) { float *a = &dst->_min[k]; float *box = &dst->_max[k]; *a = center[k] - below[k]; *box = center[k] + above[k]; }
        }
    }
    return (igAABoxList *)body->_AABoxList;
}

void beModelCtrl_ResolveManagers(beModelCtrl *self) {
    if (self->_luaManager == 0) {
        self->_luaManager = igInsightCore_FindManager(self->_insight, g_beLua_metaObject[0]);
    }
    if (self->_targetObj == 0) {
        self->_targetObj = igInsightCore_FindManager(self->_insight, g_beTargetObj_metaObject[0]);
    }
}

/* Slot 30 default: first word of the beModelCtrlInfo MetaObject record. */
int Gap__Core__igObject__vfunc_30(void)
{
    return g_beModelCtrlInfo_metaObject[0];
}

int Gap__Bec__beModelCtrl__vfunc_25(beModelCtrl *self, beModelCtrlInfo *info) {
    int infoMeta;

    infoMeta = ((beModelCtrlSlots *)self)->vfunc_30();
    if ((infoMeta == ((igObjectSlots *)info)->vfunc_20()) && ((((beModelCtrlSlots *)self)->vfunc_35((const char *)info->_kindString) & 0xFF) == 1)) {
        Gap__Core__igObject__vfunc_25(self, info);
        return 1;
    }
    return 0;
}

void Gap__Core__igObject__vfunc_29(beModelCtrl *self, beBaseInfoRam *ram) {
    beBaseInfo *info;
    beModelCtrlInfoDataHit *hit;

    info = (beBaseInfo *)ram->_parentInfo;
    beMessenger_RegisterReceiverFromInfo(self->_messenger, ram, MODELCTRL_7);
    hit = (beModelCtrlInfoDataHit *)igProperty_FindByName(info->_dataList, g_propertyNameField[0], HIT);
    if (hit != 0) {
        if (hit->_isHitPlayerBullet != 0) {
            beMessenger_RegisterReceiverFromInfo(self->_messenger, ram, HITPLAYERBULLET_2);
        }
        if (hit->_isHitPlayerTalk != 0) {
            beMessenger_RegisterReceiverFromInfo(self->_messenger, ram, HITPLAYERTALK_2);
        }
        if (hit->_isHitEnemyBullet != 0) {
            beMessenger_RegisterReceiverFromInfo(self->_messenger, ram, HITENEMYBULLET_2);
        }
    }
    ((beModelCtrlSlots *)self)->vfunc_37(ram);
}

void Gap__Bec__beNDMWMdlMapCursor__vfunc_37(void)
{
}

void beModelCtrl_UpdateMapAI(beModelCtrl *self, void *info, beBaseInfoRam *ram, beModelCtrlInfoWork *work, beModelCtrlInfoDataAIM *aim) {
    float pos[3];
    beModelCtrlInfoRamData *ramData;
    beModelCtrlAIData *zone;
    beModelCtrlInfoAI *ai;
    beModelCtrlAIMap *map;
    beModelCtrlAIDataList *zoneList;
    beModelCtrlAIData **zones;
    int pool;
    int i;
    int count;
    int roll;
    char *text;
    char *zoneName;
    char *token;
    char *old;
    float value;
    if (ram->_dataList == 0) {
        pool = igObject_GetAllocator(ram);
        pool = (g_useOwnerAllocator != 0) ? pool : Memory_GetAllocatorBySelector(g_defaultAllocatorSelector[0]);
        DataListInstall::make(ram, pool);
    }
    ramData = ((beModelCtrlInfoRamData *)igProperty_FindByName((igObject *)ram->_dataList, g_propertyNameField[0], ONE_3));
    ai = (beModelCtrlInfoAI *)work->_aI;
    StringRef seqName(0);
    if (beBaseInfoRam_IsTimerExpired(ram, AITIMER) != 0) {
        map = ((beModelCtrlAIMap **)((beModelCtrlAIMapList *)aim->_aIMapList)->_data)[ai->_mapNo];
        if ((char *)map->_targetType == 0) {
            if (g_stringPool[0] == 0) {
                pool = StringPool_Allocate(16);
                if (pool != 0) {
                    pool = StringPool_Construct(pool);
                }
                g_stringPool[0] = pool;
            }
            token = (char *)StringPool_Intern(g_stringPool[0], NEAR);
            old = (char *)map->_targetType;
            if (old != 0) {
                int *header = (int *)old - 2;
                int refs = ((int *)old)[-1] - 1;
                ((int *)old)[-1] = refs;
                if (refs == 0) {
                    StringChunk_ReleaseHeader(*header, header);
                }
            }
            map->_targetType = (int)token;
        }
        if (strcmp((char *)map->_targetType, WPOS) == 0) {
            beModelCtrlInfoAI *ai2 = (beModelCtrlInfoAI *)work->_aI;
            pos[0] = ai2->_worldPos[0];
            pos[1] = ai2->_worldPos[1];
            pos[2] = ai2->_worldPos[2];
            if ((beTargetObj_SetTarget((char *)ramData->_node + 32, pos) & 0xff) == 0) {
                return;
            }
        } else {
            if ((beTargetObj_SelectTarget((char *)ramData->_node + 32, PLAYER_3, (char *)map->_targetType) & 0xff) == 0) {
                return;
            }
        }
        value = beTargetObj_GetTargetDistanceSq();
        work->_directionLimiter[1] = map->_rotLimiter;
        if (!(map->_x1Square <= value)) {
            zoneList = (beModelCtrlAIDataList *)map->_zoneA;
        } else if (!(map->_x2Square <= value)) {
            zoneList = (beModelCtrlAIDataList *)map->_zoneB;
        } else if (!(map->_x3Square <= value)) {
            zoneList = (beModelCtrlAIDataList *)map->_zoneC;
        } else {
            zoneList = (beModelCtrlAIDataList *)map->_zoneD;
        }
        roll = ((RandomSlots *)((beSystem *)self->_system)->_random)->vfunc_22() & 0xf;
        count = zoneList->_count;
        i = 0;
        if (i < count) {
            zones = (beModelCtrlAIData **)zoneList->_data;
            do {
                zone = *zones;
                if (roll < zone->_limit) break;
                zones = zones + 1;
            } while (++i < count);
        }
        work->_targetDirection[1] = beTargetObj_GetTargetBearing(count, i, roll, zone->_dirRadian);
        zoneName = (char *)zone->_name;
        if (zoneName != 0) {
            text = zoneName;
        } else {
            text = (char *)&emptyString[0];
        }
        if (g_stringPool[0] == 0) {
            pool = StringPool_Allocate(16);
            if (pool != 0) {
                pool = StringPool_Construct(pool);
            }
            g_stringPool[0] = pool;
        }
        token = (char *)StringPool_Intern(g_stringPool[0], text);
        old = seqName.p;
        if (old != 0) {
            int *header = (int *)old - 2;
            int refs = ((int *)old)[-1] - 1;
            ((int *)old)[-1] = refs;
            if (refs == 0) {
                StringChunk_ReleaseHeader(*header, header);
            }
        }
        seqName.p = token;
        value = zone->_time; value = value; beBaseInfoRam_StartTimer(ram, AITIMER, __fixsfdi((1e9f * value) / 60.0f));
    } else {
        text = (char *)ai->_seqName;
        if (g_stringPool[0] == 0) {
            pool = StringPool_Allocate(16);
            if (pool != 0) {
                pool = StringPool_Construct(pool);
            }
            g_stringPool[0] = pool;
        }
        token = (char *)StringPool_Intern(g_stringPool[0], text);
        old = seqName.p;
        if (old != 0) {
            int *header = (int *)old - 2;
            int refs = ((int *)old)[-1] - 1;
            ((int *)old)[-1] = refs;
            if (refs == 0) {
                StringChunk_ReleaseHeader(*header, header);
            }
        }
        seqName.p = token;
    }
    work->_keyInput = strcmp(seqName.p, SQ_WALK) == 0;
    text = seqName.p;
    if (g_stringPool[0] == 0) {
        pool = StringPool_Allocate(16);
        if (pool != 0) {
            pool = StringPool_Construct(pool);
        }
        g_stringPool[0] = pool;
    }
    token = (char *)StringPool_Intern(g_stringPool[0], text);
    old = (char *)work->_keyEventName;
    if (old != 0) {
        int *header = (int *)old - 2;
        int refs = ((int *)old)[-1] - 1;
        ((int *)old)[-1] = refs;
        if (refs == 0) {
            StringChunk_ReleaseHeader(*header, header);
        }
    }
    work->_keyEventName = (int)token;
    text = seqName.p;
    if (g_stringPool[0] == 0) {
        pool = StringPool_Allocate(16);
        if (pool != 0) {
            pool = StringPool_Construct(pool);
        }
        g_stringPool[0] = pool;
    }
    token = (char *)StringPool_Intern(g_stringPool[0], text);
    old = (char *)ai->_seqName;
    if (old != 0) {
        int *header = (int *)old - 2;
        int refs = ((int *)old)[-1] - 1;
        ((int *)old)[-1] = refs;
        if (refs == 0) {
            StringChunk_ReleaseHeader(*header, header);
        }
    }
    ai->_seqName = (int)token;
}

int beModelCtrl_RunCtrl(beModelCtrl *self, beModelCtrlInfoWork *work, beModelCtrlCTRL *command) {
    char *name;
    if (command->_name != 0) name = (char *)command->_name;
    else name = (char *)emptyString;
    if (strcmp(name, onWalk) == 0) {
        work->_ctrlSt0 = 1;
        work->_ctrlSt1 = 0;
    } else if (strcmp(name, toWalk) == 0) {
        work->_ctrlSt0 = 2;
        work->_ctrlSt1 = 0;
    } else if (strcmp(name, toWait) == 0) {
        work->_ctrlSt0 = 3;
        work->_ctrlSt1 = 0;
    } else if (strcmp(name, isLive) == 0) {
        work->_ctrlSt0 = 4;
        work->_ctrlSt1 = 0;
    } else if (strcmp(name, onFall) == 0) {
        work->_isFallCheck = 1;
    } else if (strcmp(name, noFall) == 0) {
        work->_isFallCheck = 0;
    }
    return 1;
}

/* Owning stack reference to the freshly created data list; released on scope exit (reference count
 * in the low 23 bits of _refCount). */

void Gap__Core__igObject__vfunc_38(beModelCtrl *self, beBaseInfoRam *ram) {
    beBaseInfo *info;
    int work;
    beBaseInfoData *property;
    int allocator;
    igObject *list;
    igObject *old;
    info = (beBaseInfo *)ram->_parentInfo;
    if (ram->_dataList == 0) {
        allocator = igObject_GetAllocator(ram);
        allocator = (g_useOwnerAllocator != 0) ? allocator : Memory_GetAllocatorBySelector(g_defaultAllocatorSelector[0]);
        igSmartPointer<igObject> ref(beBaseInfoDataList_Create(allocator));
        list = ref.p;
        if (list != 0) {
            list->_refCount = list->_refCount + 1;
        }
        old = (igObject *)ram->_dataList;
        if (old != 0) {
            old->_refCount = old->_refCount - 1;
            if ((old->_refCount & 0x7FFFFF) == 0) {
                igObject_Destroy(old);
            }
        }
        ram->_dataList = (int)list;
    }
    work = ((beModelCtrlInfoRamData *)igProperty_FindByName(ram->_dataList, g_propertyNameField[0], ONE_3))->_work;
    property = (beBaseInfoData *)igProperty_FindByName(info->_dataList, g_propertyNameField[0], AIM);
    if (property != 0) {
        if (((igObjectList *)((beModelCtrlInfoDataAIM *)property)->_aIMapList)->_count != 0) {
            beModelCtrl_UpdateMapAI(self, info, ram, (beModelCtrlInfoWork *)work, (beModelCtrlInfoDataAIM *)property);
        }
    } else {
        property = (beBaseInfoData *)igProperty_FindByName(info->_dataList, g_propertyNameField[0], AIH);
        if (property != 0) {
            beModelCtrl_UpdateHomingAI(self, info, ram, (beModelCtrlInfoWork *)work, (beModelCtrlInfoDataAIH *)property);
        }
    }
}

struct KeyEventName { static inline void rel(char *p) {
    if (p != 0) {
        int *h = (int *)(p - 8);
        int r = *(int *)(p - 4) - 1;
        *(int *)(p - 4) = r;
        if (r == 0) StringChunk_ReleaseHeader(*h, h);
    }
} };
void beModelCtrl_UpdateKeyCtrl(beModelCtrl *self, beBaseInfo *info, beBaseInfoRam *ram, beModelCtrlInfoWork *work)
{
    if (work->_isOnCtrl != 0) ((beModelCtrlSlots *)self)->vfunc_38(ram);
    if (strcmp((void *)work->_keyEventName, SQ_NONE) == 0) {
        switch (work->_ctrlSt0) {
        case 1: {
            int mode = work->_ctrlSt1;
            int move = ((int *)((beModelCtrlMoveObjectList *)work->_moveObjectList)->_data)[2];
            switch (mode) {
            case 0:
                if (work->_keyInput != 0) {
                    beModelCtrlMoveObject_Start((beModelCtrlMoveObject *)move, 0, ((float *)((igFloatList *)work->_pdMoveDataList)->_data)[2], ((float *)((igFloatList *)work->_pdMoveDataList)->_data)[3], 0.0f);
                    work->_ctrlSt1 = 1;
                } else {
                    beModelCtrlMoveObject_Start((beModelCtrlMoveObject *)move, 2, ((float *)((igFloatList *)work->_pdMoveDataList)->_data)[0], ((float *)((igFloatList *)work->_pdMoveDataList)->_data)[1], 0.0f);
                    work->_ctrlSt1 = 2;
                }
                break;
            case 1:
                if (work->_keyInput == 0) {
                    beModelCtrlMoveObject_Start((beModelCtrlMoveObject *)move, 2, ((float *)((igFloatList *)work->_pdMoveDataList)->_data)[0], ((float *)((igFloatList *)work->_pdMoveDataList)->_data)[1], 0.0f);
                    work->_ctrlSt1 = 2;
                }
                break;
            case 2:
                if (work->_keyInput == 1) {
                    beModelCtrlMoveObject_Start((beModelCtrlMoveObject *)move, 0, ((float *)((igFloatList *)work->_pdMoveDataList)->_data)[2], ((float *)((igFloatList *)work->_pdMoveDataList)->_data)[3], 0.0f);
                    work->_ctrlSt1 = 1;
                }
                break;
            }
            break;
        }
        case 2:
            if (work->_keyInput == 1) {
                char *token;
                if (g_stringPool[0] == 0) {
                    int pool = StringPool_Allocate(16);
                    if (pool != 0) pool = StringPool_Construct(pool);
                    g_stringPool[0] = pool;
                }
                token = (char *)StringPool_Intern(g_stringPool[0], SQ_WALK);
                KeyEventName::rel((char *)work->_keyEventName);
                work->_keyEventName = (int)token;
            }
            break;
        case 3:
            if (work->_keyInput == 0) {
                char *token;
                if (g_stringPool[0] == 0) {
                    int pool = StringPool_Allocate(16);
                    if (pool != 0) pool = StringPool_Construct(pool);
                    g_stringPool[0] = pool;
                }
                token = (char *)StringPool_Intern(g_stringPool[0], SQ_WAIT_2);
                KeyEventName::rel((char *)work->_keyEventName);
                work->_keyEventName = (int)token;
            }
            break;
        }
    }
    if (strcmp((void *)work->_keyEventName, SQ_NONE) != 0 && strcmp((void *)work->_keyEventName, (void *)work->_seqCodeName) != 0) {
        ((beModelCtrlSlots *)self)->vfunc_33(ram, (const char *)work->_keyEventName);
    }
}

int beModelCtrl_RunAction(beModelCtrl *self, beModelCtrlInfo *info, beBaseInfoRam *ram, beModelCtrlACTION *command) {
    int modelName;
    int action;
    int ramNo;

    action = command->_name ? command->_name : (int)&emptyString[0];
    ramNo = ram->_ramNo;
    modelName = info->_name ? info->_name : (int)&emptyString[0];
    beMessenger_SendNamed(self->_messenger, ACTION_2, modelName, ramNo, action);
    return 1;
}

void beModelCtrlInfoRideOn_SetModel(beModelCtrlInfoRideOn *self, int modelName, int ramNo, int messenger) {
    int matrix[16];
    igObject *node;
    int token, value;
    int *header;
    int old;
    igObject *oldNode;
    beMessenger_SendNamed(messenger, MODELCTRL_7, modelName, ramNo, GETMATRIX_2);
    node = beMessenger_GetObject(messenger, 0);
    Matrix44_Copy(matrix, (char *)node + 32);
    if (g_stringPool[0] == 0) {
        value = StringPool_Allocate(16);
        if (value != 0) {
            value = StringPool_Construct(value);
        }
        g_stringPool[0] = value;
    }
    token = ((int)StringPool_Intern(g_stringPool[0], modelName));
    old = self->_modelName;
    if (old != 0) {
        header = (int *)(old - 8);
        value = *(int *)(old - 4) - 1;
        *(int *)(old - 4) = value;
        if (value == 0) {
            StringChunk_ReleaseHeader(*header, header);
        }
    }
    self->_modelName = token;
    self->_modelRamNo = ramNo;
    if (node != 0) {
        node->_refCount = node->_refCount + 1;
    }
    oldNode = (igObject *)self->_modelNode;
    if (oldNode != 0) {
        oldNode->_refCount = oldNode->_refCount - 1;
        if (((unsigned long long)(long long)oldNode->_refCount & 0x7fffffULL) == 0)
            igObject_Destroy((void *)oldNode);
    }
    self->_modelNode = (int)node;
    Matrix44_Copy(&self->_oldMatrix, matrix);
}

int beModelCtrlInfoRideOn_IsModel(beModelCtrlInfoRideOn *self, int modelName, int ramNo) {
    if (strcmp(self->_modelName, modelName) != 0) return 0;
    if (ramNo == self->_modelRamNo) return 1;
    return 0;
}

/* Resets the ride-on pose: clears the translation of `_oldMatrix` to (0,0,0) and writes `_vector`
 * into the translation of the model node's matrix (+0x20 of a node, the igTransform `_m` offset).
 * Matrix44_SetTranslation copies vec3 into matrix words 12..14. */
void Gap__Bec__beModelCtrlInfoRideOn2__vfunc_21(beModelCtrlInfoRideOn2 *self) {
    Matrix44_SetTranslation(self->_oldMatrix, &g_vec3Zero[0]);
    Matrix44_SetTranslation((float *)(self->_modelNode + 0x20), self->_vector);
}

void Gap__Bec__beModelCtrlInfoRideOn3__vfunc_21(beModelCtrlInfoRideOn3 *self, void *m) {
    Vec3 t;
    Vec3 d;
    float e, x, g, k, b, z, len, inv, y, c, a;
    Matrix44_SetTranslation((float *)((char *)self->_oldMatrix), g_vec3Zero);
    Matrix44_GetTranslation((int)m, (float *)&t);
    d.x = ((Vec3 *)self->_worldPosition)->x;
    d.y = ((Vec3 *)self->_worldPosition)->y;
    d.z = ((Vec3 *)self->_worldPosition)->z;
    d.x = d.x - t.x;
    d.y = d.y - t.y;
    d.z = d.z - t.z;
    y = ((Vec3 *)&d)->y; x = d.x; z = ((Vec3 *)&d)->z;
    len = sqrtf(x * x + y * y + z * z);
    inv = 1.0f / len;
    d.x = d.x * inv;
    d.y = d.y * inv;
    d.z = d.z * inv;
    k = self->_minSpeed;
    a = self->_maxSpeed;
    b = self->_minKyori;
    c = self->_maxKyori;
    e = a - k;
    g = c - b;
    if (len < 0.0f) {
        len = -len;
    }
    if (!(len < c)) {
        k = k;
    } else {
        k = a;
        if (len <= b) {
            k = k;
        } else {
            k = a - ((len - b) / (g / e));
        }
    }
    d.x = d.x * k;
    d.y = d.y * k;
    d.z = d.z * k;
    Matrix44_SetTranslation((float *)((char *)self->_modelNode + 32), &d);
}

void beModelCtrl_CheckWallAndFloor(beModelCtrl *self, beBaseInfo *info, beBaseInfoRam *ram, beModelCtrlInfoWork *work) {
    unsigned char landed;
    bool rideOnChanged;
    int floorHit;
    int hasFloorModel;
    int floorRamNo;
    int floorModel;
    rideOnChanged = false;
    if (work->_isWallCheck) {
        const char *kind;
        int name, ramNo;
        if (work->_rideOnData == 0) kind = HITWALL; else kind = HITWALLFULL;
        name = info->_name;
        ramNo = ram->_ramNo;
        name = name ? name : (int)emptyString;
        beMessenger_SendNamed(self->_messenger, HITLANDDELIVER, name, ramNo, kind);
        if (work->_luaWHit != 0 && beMessenger_GetBool(self->_messenger, 1) != 0) {
            int name = info->_name;
            name = name ? name : (int)emptyString;
            beModelCtrl_CallLua(self, ram, (const char *)work->_luaWHit, WHit, (const char *)name, 0, 0, (const char *)0, 0, 0);
        }
    }
    if (work->_isFloorCheck) {
        if (((int)beModelCtrl_QueryMove(self, ram, work, 3))) return;
        {
            int name = info->_name;
            int ramNo = ram->_ramNo;
            name = name ? name : (int)emptyString;
            beMessenger_SendNamed(self->_messenger, HITLANDDELIVER, name, ramNo, HITFLOORCHECK);
        }
        if (beMessenger_GetBoolCount(self->_messenger) == 0) return;
        floorModel = 0;
        hasFloorModel = beMessenger_GetStringCount(self->_messenger);
        if (hasFloorModel != 0) {
            floorModel = ((int)beMessenger_GetString(self->_messenger, 0));
            if (strcmp(floorModel, emptyString_2) != 0) {
                floorRamNo = beMessenger_GetInt(self->_messenger, 0);
            } else {
                hasFloorModel = 0;
            }
        }
        landed = beMessenger_GetBool(self->_messenger, 0);
        floorHit = beMessenger_GetBool(self->_messenger, 1) & 0xFF;
        rideOnChanged = false;
        if (work->_isFallCheck) {
            if (((int)beModelCtrl_QueryMove(self, ram, work, 4))) {
                if (floorHit != 0) {
                    int name = info->_name;
                    int ramNo = ram->_ramNo;
                    name = name ? name : (int)emptyString;
                    beMessenger_SendNamed(self->_messenger, HITLANDDELIVER, name, ramNo, HITFLOORADJUST);
                    beModelCtrl_QueryMove(self, ram, work, 5);
                    rideOnChanged = true;
                }
            } else if (landed) {
                int name = info->_name;
                int ramNo = ram->_ramNo;
                name = name ? name : (int)emptyString;
                beMessenger_SendNamed(self->_messenger, HITLANDDELIVER, name, ramNo, HITFLOORADJUST);
                beModelCtrl_QueryMove(self, ram, work, 5);
                return;
            } else {
                if (strcmp(work->_seqCodeName, SQ_SLEP) == 0) return;
                ((beModelCtrlSlots *)self)->vfunc_33(ram, SQ_FALL);
                return;
            }
        }
        if (work->_luaFHit != 0 && floorHit != 0) {
            int name = info->_name;
            name = name ? name : (int)emptyString;
            beModelCtrl_CallLua(self, ram, (const char *)work->_luaFHit, FHit, (const char *)name, 0, 0, (const char *)0, 0, 0);
        }
        if (rideOnChanged) {
            beModelCtrlInfoRideOn4 *rideOn = (beModelCtrlInfoRideOn4 *)work->_rideOnData;
            if (rideOn == 0 || rideOn->_modelRamNo < 100) {
                if (hasFloorModel == 0) {
                    if (rideOn != 0) {
                        ((Slot *)&work->_rideOnData)->set(0);
                    }
                } else if (rideOn == 0) {
                    int base = igObject_GetAllocator(self);
                    int allocator;
                    beModelCtrlInfoRideOn4 *created;
                    if (g_useOwnerAllocator != 0) allocator = base; else allocator = Memory_GetAllocatorBySelector(g_defaultAllocatorSelector[0]);
                    RideOnRef holder((beModelCtrlInfoRideOn4 *)beModelCtrlInfoRideOn_Create(allocator));
                    beModelCtrlInfoRideOn_SetModel((beModelCtrlInfoRideOn *)holder.p, floorModel, floorRamNo, self->_messenger);
                    created = holder.p;
                    if (created != 0) created->_refCount++;
                    ((Slot *)&work->_rideOnData)->set(created);
                } else if (!(beModelCtrlInfoRideOn_IsModel((beModelCtrlInfoRideOn *)rideOn, floorModel, floorRamNo) & 0xFF)) {
                    beModelCtrlInfoRideOn_SetModel((beModelCtrlInfoRideOn *)((beModelCtrlInfoRideOn4 *)work->_rideOnData), floorModel, floorRamNo, self->_messenger);
                }
            }
        }
    }
}

/* Movement query on the work's beModelCtrlMoveObjectList (_moveObjectList, +200): the list is
 * enabled when _count != 0 and _data holds four beModelCtrlMoveObject handles (0 move, 1 rotation,
 * 2 turn-Y/landing, 3 fourth channel); selector 5 also clears entry 1 (_isRun and _speed). _data
 * is an array of arena handles, so entries are reached via casts. */
unsigned char beModelCtrl_QueryMove(beModelCtrl *self, beBaseInfoRam *ram, beModelCtrlInfoWork *work, unsigned int query) {
    beModelCtrlMoveObjectList *list;
    beModelCtrlMoveObject **moves;
    beModelCtrlMoveObject *move;
    list = (beModelCtrlMoveObjectList *)work->_moveObjectList;
    if (list->_count == 0) {
        return 0;
    }
    switch (query) {
    case 0:
        moves = (beModelCtrlMoveObject **)list->_data;
        if (moves[0]->_isRun != 0) {
            return 1;
        }
        if (moves[1]->_isRun != 0) {
            return 1;
        }
        move = moves[2];
        if (move->_isRun) {
            return move->_isRun;
        }
        return move->_isRun;
    case 1:
        return ((beModelCtrlMoveObject **)list->_data)[3]->_isRun;
    case 2:
        return ((beModelCtrlMoveObject **)list->_data)[1]->_isRun;
    case 3:
        move = ((beModelCtrlMoveObject **)list->_data)[1];
        if (move->_isRun != 0 && move->_mode == 4) {
            return 1;
        }
        return 0;
    case 4:
        move = ((beModelCtrlMoveObject **)list->_data)[1];
        if (move->_isRun != 0 && move->_mode == 1) {
            return 1;
        }
        return 0;
    case 5:
        move = ((beModelCtrlMoveObject **)list->_data)[1];
        move->_isRun = 0;
        move->_speed = 0;
    default:
        return 1;
    }
}

void beModelCtrlMoveObject_Start(beModelCtrlMoveObject *self, int mode, float value, float frames, float endTime) {
    self->_mode = mode;
    self->_value = value;
    self->_acc = value / ((frames * frames) / 2.0f);
    self->_endTime = endTime;
    self->_isSeqStop = 0;
    switch (mode) {
    case 4:
        self->_speed = value;
        break;
    case 5:
        self->_speed = -value;
        break;
    }
    self->_isRun = 1;
}

void beModelCtrlMoveObject_Stop(beModelCtrlMoveObject *self) {
    float zero = 0.0f;
    self->_endTime = zero;
    if (self->_mode == 0) { beModelCtrlMoveObject_Start(self, 2, self->_stopValue, self->_stopFrame, zero); } else if (self->_mode == 1) { beModelCtrlMoveObject_Start(self, 3, self->_stopValue, self->_stopFrame, zero); } else { self->_isRun = 0; self->_speed = zero; }
    self->_isSeqStop = 0;
}

float beModelCtrlMoveObject_Step(beModelCtrlMoveObject *self, float frames) {
    float speed, delta, limit;
    if (self->_isRun == 0) { return 0.0f; }
    speed = self->_endTime;
    if (speed != 0.0f) {
        speed = speed - frames;
        if (speed < 0.0f) {
            beModelCtrlMoveObject_Stop((beModelCtrlMoveObject *)self);
            if (self->_isRun == 0) { return 0.0f; }
        } else {
            self->_endTime = speed;
        }
    }
    if (!(frames <= 3.0f)) { frames = 3.0f; }
    speed = self->_speed;
    delta = frames * self->_acc;
    switch (self->_mode) {
    case 2:
    case 4:
        speed = speed - delta;
        if (speed < 0.0f) { self->_isRun = 0; speed = 0.0f; self->_speed = 0.0f; }
        break;
    case 3:
    case 5:
        speed = speed + delta;
        if (!(speed <= 0.0f)) { self->_isRun = 0; speed = 0.0f; self->_speed = 0.0f; }
        break;
    case 0:
        limit = self->_value;
        speed = speed + delta;
        if (!(speed <= limit)) { speed = limit; }
        break;
    case 1:
        speed = speed - delta;
        limit = -self->_value;
        if (speed < limit) { speed = limit; }
        break;
    }
    self->_speed = speed;
    return speed * frames;
}

static inline beModelCtrlMoveObject **MoveObjects(beModelCtrlInfoWork *work) {
    return (beModelCtrlMoveObject **)((beModelCtrlMoveObjectList *)work->_moveObjectList)->_data;
}

void beModelCtrl_ApplyMoves(beModelCtrl *self, beBaseInfo *info, beBaseInfoRam *ram, beModelCtrlInfoWork *work) {
    float step[3];
    int matrix[16];
    float frames;
    float turn;
    int allocator;
    beModelCtrlMoveObjectList *moves;
    beModelCtrlMoveObject **objects;
    beModelCtrlInfoRamData *ramData;
    igObject *created;
    igObject *old;
    void *box;

    moves = (beModelCtrlMoveObjectList *)work->_moveObjectList;
    work->_isHitCheck = 0;
    if (moves->_count != 0) {
        frames = beBaseInfoRam_GetTimerFrameDelta(ram, KEIKATIMER);
        if (((beModelCtrlMoveObject **)moves->_data)[3]->_isRun != 0) {
            turn = 0.017453292f * beModelCtrlMoveObject_Step(MoveObjects(work)[3], frames);
            work->_targetDirection[1] = work->_targetDirection[1] + turn;
            if (turn < 0.0f) {
                turn = -turn;
            }
            work->_directionLimiter[1] = 1.25f * turn;
        }
        beModelCtrl_UpdateDirection(self, info, ram, work, 0);
        objects = (beModelCtrlMoveObject **)moves->_data;
        if (objects[0]->_isRun != 0 || objects[1]->_isRun != 0 || objects[2]->_isRun != 0) {
            if (ram->_dataList == 0) {
                allocator = igObject_GetAllocator(ram);
                if (g_useOwnerAllocator != 0) {
                    /* matching construct: self-assignment keeps the retail select of the allocator */
                    allocator = (int)allocator;
                } else {
                    allocator = Memory_GetAllocatorBySelector(g_defaultAllocatorSelector[0]);
                }
                {
                    igSmartPointer<igObject> ref(beBaseInfoDataList_Create(allocator));
                    created = ref.p;
                    if (created != 0) {
                        created->_refCount = created->_refCount + 1;
                    }
                    old = (igObject *)ram->_dataList;
                    if (old != 0) {
                        old->_refCount = old->_refCount - 1;
                        if ((old->_refCount & 0x7FFFFF) == 0) {
                            igObject_Destroy(old);
                        }
                    }
                    ram->_dataList = (int)created;
                }
            }
            ramData = ((beModelCtrlInfoRamData *)igProperty_FindByName((igObject *)ram->_dataList, g_propertyNameField[0], ONE_3));
            Matrix44_Copy(matrix, (char *)ramData->_node + 0x20);
            step[0] = beModelCtrlMoveObject_Step(MoveObjects(work)[0], frames);
            step[1] = beModelCtrlMoveObject_Step(MoveObjects(work)[1], frames);
            step[2] = beModelCtrlMoveObject_Step(MoveObjects(work)[2], frames);
            Matrix44_TranslateLocal(matrix, step);
            ((beModelCtrlNode2Slots *)ramData->_node)->vfunc_35(matrix);
            work->_isHitCheck = 1;
            box = (void *)work->_baseAABox;
            if (box != 0) {
                beModelCtrl_UpdateBound(self, (beModelCtrlNode2 *)ramData->_node, (igAABox *)box);
            }
        }
    }
}

unsigned char beModelCtrl_RunMove(beModelCtrl *self, beBaseInfoRam *ram, beModelCtrlInfoWork *work, igObject *command)
{
    float forward[3];
    int meta;
    if (!(beBaseInfoRam_HasTimer(ram, KEIKATIMER) & 0xFF)) {
        beBaseInfoRam_StartTimer(ram, KEIKATIMER, 0);
    }
    if (work->_isPosLock != 0) {
        work->_isPosLock = 0;
        if (ram->_dataList == 0) {
            int allocator;
            igObject *pool, *old;
            Locals::CreateDataList(ram, allocator, pool, old);
        }
        Vec3f_TransformDirection(&forward[0], &g_vec3ZAxis[0], (char *)((beModelCtrlInfoRamData *)igProperty_FindByName((igObject *)ram->_dataList, g_propertyNameField[0], ONE_3))->_node + 32);
        {
            float angle = atan2f(forward[0], forward[2]);
            work->_direction[1] = angle;
            work->_targetDirection[1] = angle;
        }
    }
    if (((beModelCtrlMoveObjectList *)work->_moveObjectList)->_count == 0) {
        int allocator;
        igObject *old;
        MoveRef object;
        SELECT_ALLOCATOR(allocator, self);
        old = object.p;
        if (old != 0) { old->_refCount = old->_refCount - 1; if ((old->_refCount & 0x7FFFFF) == 0) igObject_Destroy(old); }
        object.p = (igObject *)beModelCtrlMoveObject_Create(allocator);
        { igObject *created = object.p; beModelCtrlMoveObjectList *list = *(beModelCtrlMoveObjectList **)&work->_moveObjectList; ObjectList_AppendRetained(list, created); }
        SELECT_ALLOCATOR(allocator, self);
        old = object.p;
        if (old != 0) { old->_refCount = old->_refCount - 1; if ((old->_refCount & 0x7FFFFF) == 0) igObject_Destroy(old); }
        object.p = (igObject *)beModelCtrlMoveObject_Create(allocator);
        { igObject *created = object.p; beModelCtrlMoveObjectList *list = *(beModelCtrlMoveObjectList **)&work->_moveObjectList; ObjectList_AppendRetained(list, created); }
        SELECT_ALLOCATOR(allocator, self);
        old = object.p;
        if (old != 0) { old->_refCount = old->_refCount - 1; if ((old->_refCount & 0x7FFFFF) == 0) igObject_Destroy(old); }
        object.p = (igObject *)beModelCtrlMoveObject_Create(allocator);
        { igObject *created = object.p; beModelCtrlMoveObjectList *list = *(beModelCtrlMoveObjectList **)&work->_moveObjectList; ObjectList_AppendRetained(list, created); }
        SELECT_ALLOCATOR(allocator, self);
        old = object.p;
        if (old != 0) { old->_refCount = old->_refCount - 1; if ((old->_refCount & 0x7FFFFF) == 0) igObject_Destroy(old); }
        object.p = (igObject *)beModelCtrlMoveObject_Create(allocator);
        { igObject *created = object.p; beModelCtrlMoveObjectList *list = *(beModelCtrlMoveObjectList **)&work->_moveObjectList; ObjectList_AppendRetained(list, created); }
    }
    meta = g_beModelCtrlMOVE_metaObject[0];
    if (meta == ((igObjectSlots *)command)->vfunc_20()) {
        char *name;
        float value, frame;
        beModelCtrlMOVE *m = (beModelCtrlMOVE *)command;
        name = m->_name ? (char *)m->_name : (char *)&emptyString[0];
        value = m->_value;
        frame = m->_frame;
        if (strcmp(name, Stop) == 0) {
            beModelCtrlMoveObject_Start(MoveObjects(work)[2], 2, value, frame, 0.0f);
        } else if (strcmp(name, Move) == 0) {
            beModelCtrlMoveObject_Start(MoveObjects(work)[2], 0, value, frame, 0.0f);
        } else if (strcmp(name, Push) == 0) {
            beModelCtrlMoveObject_Start(MoveObjects(work)[2], 4, value, frame, 0.0f);
        } else if (strcmp(name, Back) == 0) {
            beModelCtrlMoveObject_Start(MoveObjects(work)[2], 5, value, frame, 0.0f);
        } else if (strcmp(name, Jump) == 0) {
            beModelCtrlMoveObject_Start(MoveObjects(work)[1], 4, value, frame, 0.0f);
        } else if (strcmp(name, Fall) == 0) {
            beModelCtrlMoveObject_Start(MoveObjects(work)[1], 1, value, frame, 0.0f);
        }
    } else {
        meta = g_beModelCtrlMOVEEX_metaObject[0];
        if (meta == ((igObjectSlots *)command)->vfunc_20()) {
            char *name;
            int idx, mode, base;
            unsigned char isSeqStop;
            float value, frame, playTime, stopValue, stopFrame;
            beModelCtrlMoveObject *move;
            beModelCtrlMOVEEX *m = (beModelCtrlMOVEEX *)command;
            name = m->_name ? (char *)m->_name : (char *)&emptyString[0];
            value = m->_value;
            frame = m->_frame;
            playTime = m->_playTime;
            isSeqStop = m->_isSeqStop;
            stopValue = m->_stopValue;
            stopFrame = m->_stopFrame;
            base = (name[0] == 'T') ? 0 : 2;
            idx = name[1] - 'X' + base;
            switch (name[3]) {
            case 'A': mode = 0; break;
            case 'D': mode = 2; break;
            case 'T': mode = 4; break;
            }
            if (name[2] == 'M') mode += 1;
            move = MoveObjects(work)[idx];
            beModelCtrlMoveObject_Start(move, mode, value, frame, playTime);
            move->_isSeqStop = isSeqStop;
            move->_stopValue = stopValue;
            move->_stopFrame = stopFrame;
        } else {
            char *name;
            beModelCtrlMOVERL *m = (beModelCtrlMOVERL *)command;
            name = m->_name ? (char *)m->_name : (char *)&emptyString[0];
            if (strcmp(name, JOINT) == 0) {
                igObject *trc, *old;
                beMessenger_SendNamed(self->_messenger, MODELCTRL_7, (char *)m->_modelName, ram->_ramNo, GETTRCDATA);
                if (beMessenger_GetObjectCount(self->_messenger) == 1) {
                    work->_isPosLock = 1;
                    trc = (igObject *)beMessenger_GetObject(self->_messenger, 0);
                    if (trc != 0) trc->_refCount = trc->_refCount + 1;
                    old = (igObject *)work->_posLockTrc;
                    if (old != 0) {
                        old->_refCount = old->_refCount - 1;
                        if ((old->_refCount & 0x7FFFFF) == 0) igObject_Destroy(old);
                    }
                    work->_posLockTrc = (int)trc;
                }
            } else {
                char *modelName, *boneName;
                char *oldModelName, *oldBoneName;
                modelName = (char *)m->_modelName;
                if (g_stringPool[0] == 0) {
                    int pool = StringPool_Allocate(16);
                    if (pool != 0) pool = StringPool_Construct(pool);
                    g_stringPool[0] = pool;
                }
                modelName = (char *)StringPool_Intern(g_stringPool[0], modelName);
                oldModelName = (char *)work->_posLockModelName;
                if (oldModelName != 0) {
                    int *header = (int *)(oldModelName - 8);
                    int refs = *(int *)(oldModelName - 4) - 1;
                    *(int *)(oldModelName - 4) = refs;
                    if (refs == 0) StringChunk_ReleaseHeader(*header, header);
                }
                work->_posLockModelName = (int)modelName;
                boneName = (char *)m->_boneName;
                if (g_stringPool[0] == 0) {
                    int pool = StringPool_Allocate(16);
                    if (pool != 0) pool = StringPool_Construct(pool);
                    g_stringPool[0] = pool;
                }
                boneName = (char *)StringPool_Intern(g_stringPool[0], boneName);
                oldBoneName = (char *)work->_posLockBoneName;
                if (oldBoneName != 0) {
                    int *header = (int *)(oldBoneName - 8);
                    int refs = *(int *)(oldBoneName - 4) - 1;
                    *(int *)(oldBoneName - 4) = refs;
                    if (refs == 0) StringChunk_ReleaseHeader(*header, header);
                }
                work->_posLockBoneName = (int)boneName;
                work->_isPosLock = 1;
            }
        }
    }
    return 1;
}

int beModelCtrl_RunPdMove(beModelCtrl *self, beBaseInfoRam *ram, beModelCtrlInfoWork *work, beModelCtrlPDMOVE *command) {
    char *name;
    int idx, i, k, isMove;
    igTDataList<float> *list;
    const igTDataList<float> *view;
    igTDataList<float> *valueList;
    int valueCount;
    igTDataList<float> *frameList;
    int frameCount;
    int frameIdx;
    float value, frame;
    name = command->_name ? (char *)command->_name : (char *)emptyString;
    isMove = strcmp(name, Move);
    list = (igTDataList<float> *)work->_pdMoveDataList;
    idx = isMove == 0 ? 2 : 0;
    if (list->_count == 0) {
        for (i = 0; i < 4; i++) {
            list = (igTDataList<float> *)work->_pdMoveDataList;
            view = list;
            k = view->_count;
            if (k < list->_capacity) {
                list->_count = list->_count + 1;
            } else {
                List_Resize(list, k + 1, 4);
            }
            list->_data[k] = D_004c8fa0[0];
        }
    }
    valueList = (igTDataList<float> *)work->_pdMoveDataList;
    valueCount = valueList->_count;
    value = command->_value;
    if (valueCount != 0 && idx >= 0 && idx < valueCount) {
        valueList->_data[idx] = value;
    }
    frameList = (igTDataList<float> *)work->_pdMoveDataList;
    frameCount = frameList->_count;
    frame = command->_frame;
    if (frameCount != 0) {
        frameIdx = idx + 1;
        if (frameIdx >= 0 && frameIdx < frameCount) {
            frameList->_data[idx + 1] = frame;
        }
    }
    return 1;
}

extern "C" void *igStringRefList_Create(int);
extern "C" void *igIntList_Create(int);
extern "C" int FUN_001ca620(igStringRefList *, StringRef *);
extern "C" int DAT_004c8fa8[4];
extern "C" int DAT_004c8fb0[4];
static inline int intListCount(const igIntList *list) { return list->_count; }
/* Holder of the label lists created on first use; the table names its own out-of-line destructor copy. */
struct LabelListRef { igObject *p; LabelListRef() { p = 0; } ~LabelListRef() { igObject *o = p; if (o != 0) { o->_refCount = o->_refCount - 1; if ((o->_refCount & 0x7fffff) == 0) igObject_Destroy(o); } } };

void beModelCtrlInfoWork_SetSeqLabel(beModelCtrl *self, beBaseInfoRam *ram, beModelCtrlInfoWork *work, const char *seqName, const char *labelName) {
    igStringRefList *seqList, *labelList;
    igIntList *offsetList;
    int base, allocator, token, idx, word, count, k;
    igObject *released, *created;
    int *header, *slot;
    int tokenWord, oldWord;

    seqList = (igStringRefList *)work->_labelSeqList;
    labelList = (igStringRefList *)work->_labelNameList;
    offsetList = (igIntList *)work->_labelOffsetList;
    if (seqList == 0) {
        LabelListRef listRef;
        igSmartPointer<igIntList> intListRef;
        base = igObject_GetAllocator(self);
        if (g_useOwnerAllocator != 0) {
            allocator = base;
        } else {
            allocator = Memory_GetAllocatorBySelector(g_defaultAllocatorSelector[0]);
        }
        released = listRef.p;
        if (released != 0) {
            released->_refCount = released->_refCount - 1;
            if ((released->_refCount & 0x7fffff) == 0) igObject_Destroy(released);
        }
        listRef.p = (igObject *)igStringRefList_Create(allocator);
        created = listRef.p;
        if (created != 0) created->_refCount = created->_refCount + 1;
        released = (igObject *)work->_labelSeqList;
        if (released != 0) {
            released->_refCount = released->_refCount - 1;
            if ((released->_refCount & 0x7fffff) == 0) igObject_Destroy(released);
        }
        work->_labelSeqList = (int)created;
        seqList = (igStringRefList *)listRef.p;

        base = igObject_GetAllocator(self);
        if (g_useOwnerAllocator != 0) {
            allocator = base;
        } else {
            allocator = Memory_GetAllocatorBySelector(g_defaultAllocatorSelector[0]);
        }
        released = listRef.p;
        if (released != 0) {
            released->_refCount = released->_refCount - 1;
            if ((released->_refCount & 0x7fffff) == 0) igObject_Destroy(released);
        }
        listRef.p = (igObject *)igStringRefList_Create(allocator);
        created = listRef.p;
        if (created != 0) created->_refCount = created->_refCount + 1;
        released = (igObject *)work->_labelNameList;
        if (released != 0) {
            released->_refCount = released->_refCount - 1;
            if ((released->_refCount & 0x7fffff) == 0) igObject_Destroy(released);
        }
        work->_labelNameList = (int)created;
        labelList = (igStringRefList *)listRef.p;

        base = igObject_GetAllocator(self);
        if (g_useOwnerAllocator != 0) {
            allocator = base;
        } else {
            allocator = Memory_GetAllocatorBySelector(g_defaultAllocatorSelector[0]);
        }
        released = intListRef.p;
        if (released != 0) {
            released->_refCount = released->_refCount - 1;
            if ((released->_refCount & 0x7fffff) == 0) igObject_Destroy(released);
        }
        intListRef.p = (igIntList *)igIntList_Create(allocator);
        created = intListRef.p;
        if (created != 0) created->_refCount = created->_refCount + 1;
        released = (igObject *)work->_labelOffsetList;
        if (released != 0) {
            released->_refCount = released->_refCount - 1;
            if ((released->_refCount & 0x7fffff) == 0) igObject_Destroy(released);
        }
        work->_labelOffsetList = (int)created;
        offsetList = (igIntList *)intListRef.p;
    }
    if (seqName == 0) {
        token = 0;
    } else {
        if (g_stringPool[0] == 0) {
            word = StringPool_Allocate(16);
            if (word != 0) word = StringPool_Construct(word);
            g_stringPool[0] = word;
        }
        token = (int)StringPool_Intern(g_stringPool[0], seqName);
    }
    {
        StringRef key((char *)token);
        idx = FUN_001cafc0((int)seqList, &key, 0);
    }
    if (idx != -1) {
        if (seqName == 0) {
            token = 0;
        } else {
            if (g_stringPool[0] == 0) {
                word = StringPool_Allocate(16);
                if (word != 0) word = StringPool_Construct(word);
                g_stringPool[0] = word;
            }
            token = (int)StringPool_Intern(g_stringPool[0], seqName);
        }
        {
        StringRef seqToken((char *)token);
        count = seqList->_count;
        if (count != 0 && idx >= 0 && idx < count) {
            slot = &((int *)seqList->_data)[idx];
            tokenWord = (int)seqToken.p;
            if (tokenWord != 0) *(int *)(tokenWord - 4) = *(int *)(tokenWord - 4) + 1;
            oldWord = *slot;
            if (oldWord != 0) {
                header = (int *)(oldWord - 8);
                word = *(int *)(oldWord - 4) - 1;
                *(int *)(oldWord - 4) = word;
                if (word == 0) StringChunk_ReleaseHeader(*header, header);
            }
            *slot = (int)seqToken.p;
        }
        }
        if (labelName == 0) {
            token = 0;
        } else {
            if (g_stringPool[0] == 0) {
                word = StringPool_Allocate(16);
                if (word != 0) word = StringPool_Construct(word);
                g_stringPool[0] = word;
            }
            token = (int)StringPool_Intern(g_stringPool[0], labelName);
        }
        {
        StringRef labelToken((char *)token);
        count = labelList->_count;
        if (count != 0 && idx >= 0 && idx < count) {
            slot = &((int *)labelList->_data)[idx];
            tokenWord = (int)labelToken.p;
            if (tokenWord != 0) *(int *)(tokenWord - 4) = *(int *)(tokenWord - 4) + 1;
            oldWord = *slot;
            if (oldWord != 0) {
                header = (int *)(oldWord - 8);
                word = *(int *)(oldWord - 4) - 1;
                *(int *)(oldWord - 4) = word;
                if (word == 0) StringChunk_ReleaseHeader(*header, header);
            }
            *slot = (int)labelToken.p;
        }
        }
        count = offsetList->_count;
        if (count != 0 && idx >= 0 && idx < count) {
            ((int *)offsetList->_data)[idx] = DAT_004c8fa8[0];
        }
    } else {
        if (seqName == 0) {
            token = 0;
        } else {
            if (g_stringPool[0] == 0) {
                word = StringPool_Allocate(16);
                if (word != 0) word = StringPool_Construct(word);
                g_stringPool[0] = word;
            }
            token = (int)StringPool_Intern(g_stringPool[0], seqName);
        }
        {
            StringRef newSeq((char *)token);
            FUN_001ca620(seqList, &newSeq);
        }
        if (labelName == 0) {
            token = 0;
        } else {
            if (g_stringPool[0] == 0) {
                word = StringPool_Allocate(16);
                if (word != 0) word = StringPool_Construct(word);
                g_stringPool[0] = word;
            }
            token = (int)StringPool_Intern(g_stringPool[0], labelName);
        }
        {
            StringRef newLabel((char *)token);
            FUN_001ca620(labelList, &newLabel);
        }
        k = intListCount(offsetList);
        if (k < offsetList->_capacity) {
            offsetList->_count = offsetList->_count + 1;
        } else {
            List_Resize(offsetList, k + 1, 4);
        }
        ((int *)offsetList->_data)[k] = DAT_004c8fb0[0];
    }
}

int beModelCtrl_RunLabelCtrl(beModelCtrl *self, beBaseInfoRam *ram, beModelCtrlInfoWork *work, beModelCtrlLABELCTRL *command) {
    int *labelName = (int *)command->_name;
    labelName = labelName != 0 ? labelName : &emptyString[0];
    beModelCtrlInfoWork_SetSeqLabel(self, ram, work, (const char *)command->_seqName, (const char *)labelName);
    return 1;
}

/* Owning stack reference to the freshly created property list; released on scope exit once the ram
 * holds its own reference (reference count in the low 23 bits of _refCount). */

void beModelCtrl_CallLua(beModelCtrl *self, beBaseInfoRam *ram, const char *function, const char *callName, const char *infoName, int bulletKind, int bulletBoxNo, const char *hitterName, int hitterRamNo, int hitterRecNo) {
    int chunk[11];
    int base;
    int allocator;
    igObject *p;
    igObject *old;
    beModelCtrlInfoRamData *ramData;
    beModelCtrlInfoWork *work;
    int hpBefore;
    beDataObjInt *hp;

    if (ram->_dataList == 0) {
        base = igObject_GetAllocator(ram);
        if (g_useOwnerAllocator != 0) {
            allocator = base;
        } else {
            allocator = Memory_GetAllocatorBySelector(g_defaultAllocatorSelector[0]);
        }
        igSmartPointer<igObject> created(beBaseInfoDataList_Create(allocator));
        p = created.p;
        if (p != 0) {
            p->_refCount = p->_refCount + 1;
        }
        old = (igObject *)ram->_dataList;
        if (old != 0) {
            old->_refCount = old->_refCount - 1;
            if ((old->_refCount & 0x7fffff) == 0) {
                igObject_Destroy(old);
            }
        }
        ram->_dataList = (int)p;
    }
    ramData = ((beModelCtrlInfoRamData *)igProperty_FindByName((igObject *)ram->_dataList, g_propertyNameField[0], ONE_3));
    work = (beModelCtrlInfoWork *)ramData->_work;
    g_mdlEntity[0] = ram;
    g_mdlRamNo[0] = ram->_ramNo;
    g_mdlMatrix[0] = ramData->_node + 0x20;
    g_mdlMaxHp[0] = ((beDataObjInt *)work->_mHp)->_data;
    g_mdlHp[0] = ((beDataObjInt *)work->_hp)->_data;
    g_mdlRecNo[0] = work->_recNo;
    g_mdlInfoName[0] = (int)infoName;
    g_mdlBulletKind[0] = bulletKind;
    g_mdlBulletBoxNo[0] = bulletBoxNo;
    g_hitterInfoName[0] = (int)hitterName;
    g_bltShootRamNo[0] = hitterRamNo;
    g_hitterRecNo[0] = hitterRecNo;
    g_mdlDmgTurn[0] = 1;
    g_mdlCallName[0] = (int)callName;
    hpBefore = ((beDataObjInt *)work->_hp)->_data;
    sprintf(chunk, s_s_lua, function, infoName);
    beLua__RunNamedChunk(self->_luaManager, chunk, 0);
    hp = (beDataObjInt *)work->_hp;
    if (hpBefore == hp->_data) {
        hp->_data = g_mdlHp[0];
    }
}

#define SET_LUA_FUNCTION(fld) { \
    int *p; \
    token = (int *)command->_name; \
    if (token != 0) { token = (int *)token; } else { token = &emptyString[0]; } \
    if (g_stringPool[0] == 0) { \
        int pool = StringPool_Allocate(0x10); \
        if (pool != 0) pool = StringPool_Construct(pool); \
        g_stringPool[0] = pool; \
    } \
    token = (int *)StringPool_Intern(g_stringPool[0], token); \
    p = (int *)work->fld; \
    if (p != 0) { \
        int *hd = p - 2; \
        int c = p[-1] - 1; \
        p[-1] = c; \
        if (c == 0) StringChunk_ReleaseHeader(*hd, hd); \
    } \
    work->fld = (int)token; }
int beModelCtrl_RunLuaCall(beModelCtrl *self, beBaseInfo *info, beBaseInfoRam *ram, beModelCtrlInfoWork *work, beModelCtrlLUACALL *command) {
    unsigned char call;
    int *function;
    int *infoName;
    int mode;
    int *token;
    call = 0;
    mode = command->_modeName;
    if (mode == 0) {
        call = 1;
    } else if (strcmp(mode, BHit_2) == 0) {
        SET_LUA_FUNCTION(_luaBHit)
    } else if (strcmp(command->_modeName, WHit) == 0) {
        SET_LUA_FUNCTION(_luaWHit)
    } else if (strcmp(command->_modeName, FHit) == 0) {
        SET_LUA_FUNCTION(_luaFHit)
    } else {
        call = 1;
    }
    if (call) {
        infoName = (int *)info->_name;
        if (infoName != 0) { infoName = (int *)infoName; } else { infoName = &emptyString[0]; }
        mode = command->_modeName;
        function = (int *)command->_name;
        if (function != 0) { function = (int *)function; } else { function = &emptyString[0]; }
        beModelCtrl_CallLua(self, ram, (const char *)function, (const char *)mode, (const char *)infoName, 0, 0, (const char *)0, 0, 0);
    }
    return 1;
}

#undef SET_LUA_FUNCTION

int beModelCtrl_RunAiMap(beModelCtrl *self, beModelCtrlInfo *info, beBaseInfoRam *ram, beModelCtrlInfoWork *work, beModelCtrlAIMAP *command) {
    Vec3 target;
    int i;
    int count;
    int idx;
    beModelCtrlAIMapList *maps;
    int *name;
    int *infoName;
    beModelCtrlInfoAI *ai;
    beModelCtrlAIMap *map;
    maps = (beModelCtrlAIMapList *)((beModelCtrlInfoDataAIM *)igProperty_FindByName(info->_dataList, g_propertyNameField[0], AIM))->_aIMapList;
    name = (int *)command->_name;
    name = name != 0 ? name : &emptyString[0];
    map = (beModelCtrlAIMap *)igProperty_FindByName(maps, g_propertyNameField[0], name);
    beModelCtrlAIMap *key = map;
    count = maps->_count;
    for (i = 0; i < count; i++) { if (*(beModelCtrlAIMap **)&key == ((beModelCtrlAIMap **)maps->_data)[i]) { idx = i; goto found; } }
    idx = -1;
found:
    ai = (beModelCtrlInfoAI *)work->_aI;
    if (ai != 0) {
        ai->_mapNo = idx;
        if (map->_targetType != 0 && strcmp(map->_targetType, WPOS) == 0) {
            g_mdlWorldPosTarget[0] = &target;
            infoName = (int *)info->_name;
            infoName = infoName != 0 ? infoName : &emptyString[0];
            beModelCtrl_CallLua(self, ram, (const char *)aim, (const char *)WPos, (const char *)infoName, 0, 0, (const char *)0, 0, 0);
            { beModelCtrlInfoAI *ai2 = (beModelCtrlInfoAI *)work->_aI; ai2->_worldPos[0] = target.x; ai2->_worldPos[1] = target.y; ai2->_worldPos[2] = target.z; }
            g_mdlWorldPosTarget[0] = 0;
        }
    }
    beBaseInfoRam_RemoveTimer(ram, AITIMER);
    return 1;
}

unsigned char beModelCtrl_RunMsgBox(beModelCtrl *self, beModelCtrlInfo *info, beModelCtrlInfoWork *work, beModelCtrlMSGBOX *command)
{
    return 1;
}

int beModelCtrl_RunJump(beModelCtrl *self, beBaseInfoRam *ram, beModelCtrlJUMP *command) {
    int *sequence;

    sequence = (int *)(command->_name);
    sequence = sequence ? sequence : (int *)&emptyString[0];
    ((beModelCtrlSlots *)self)->vfunc_33(ram, (const char *)sequence);
    return 1;
}

int beModelCtrl_StartWaitCheck(beModelCtrl *self, beModelCtrlInfoWork *work, beModelCtrlWCHECK *command) {
    int *name;
    int *header;
    int refs;
    int pool;
    void *token;
    char *old;
    name = (int *)command->_name;
    name = name != 0 ? name : (int *)(&emptyString[0]);
    if (g_stringPool[0] == 0) {
        pool = StringPool_Allocate(0x10);
        if (pool != 0) {
            pool = StringPool_Construct(pool);
        }
        g_stringPool[0] = pool;
    }
    token = (void *)(StringPool_Intern(g_stringPool[0], name));
    old = (char *)work->_wCheckName;
    if (old != 0) {
        header = (int *)(old - 8);
        refs = *(int *)(old - 4) - 1;
        *(int *)(old - 4) = refs;
        if (refs == 0) {
            StringChunk_ReleaseHeader(*header, header);
        }
    }
    work->_wCheckName = (int)token;
    return 0;
}

#define END_WAIT() do { \
    int v; int token; int old; int *hd; \
    if (g_stringPool[0] == 0) { v = StringPool_Allocate(16); if (v != 0) v = StringPool_Construct(v); g_stringPool[0] = v; } \
    token = ((int)StringPool_Intern(g_stringPool[0], 0)); \
    old = work->_wCheckName; \
    if (old != 0) { hd = (int *)(old - 8); v = *(int *)(old - 4) - 1; *(int *)(old - 4) = v; if (v == 0) StringChunk_ReleaseHeader(*hd, hd); } \
    work->_wCheckName = token; \
    beModelCtrl_RunCommands(self, info, ram, work); \
} while (0)
void beModelCtrl_UpdateWaitCheck(beModelCtrl *self, beModelCtrlInfo *info, beBaseInfoRam *ram, beModelCtrlInfoWork *work) {
    if (strcmp(work->_wCheckName, TurnY) == 0 || strcmp(work->_wCheckName, Landing) == 0) {
        if (!(beModelCtrl_QueryMove(self, ram, work, 2) & 0xFF)) {
            END_WAIT();
        }
    } else if (strcmp(work->_wCheckName, Action) == 0) {
        int name = info->_name;
        int ramNo = ram->_ramNo;
        name = name ? name : (int)emptyString;
        beMessenger_SendNamed(self->_messenger, ACTION_2, name, ramNo, ISCOMEND);
        if (beMessenger_GetBool(self->_messenger, 0) != 0) {
            END_WAIT();
        }
    } else if (strcmp(work->_wCheckName, Moving) == 0) {
        if (!(beModelCtrl_QueryMove(self, ram, work, 0) & 0xFF)) {
            END_WAIT();
        }
    } else if (strcmp(work->_wCheckName, Rotation) == 0) {
        if (!(beModelCtrl_QueryMove(self, ram, work, 1) & 0xFF)) {
            END_WAIT();
        }
    } else {
        ((beModelCtrlSlots *)self)->vfunc_39(ram);
    }
}

#undef END_WAIT

/* Slot 39 default: empty. */
void Gap__Core__igObject__vfunc_39(void)
{
}

int beModelCtrl_RunHitBox(beModelCtrl *self, beBaseInfoRam *ram, beModelCtrlInfoWork *work, beModelCtrlHITBOX *command) {
    char *mode;
    char *mode2;
    char *name;

    name = (char *)command->_name;
    if (name != 0) {
        mode = name;
    } else {
        mode = ((char *)emptyString);
    }
    if (strcmp(mode, AllClear) == 0) {
        beModelCtrlSubCom_StopType(work->_subCommand, (int)ram, g_beModelCtrlSCHitBox_metaObject[0]);
    } else {
        name = (char *)command->_name;
        if (name != 0) {
            mode2 = name;
        } else {
            mode2 = ((char *)emptyString);
        }
        if (strcmp(mode2, Set) == 0) {
            beModelCtrlSubCom_AddHitBox(work->_subCommand, command);
        }
    }
    return 1;
}

int beModelCtrl_RunMuteki(beModelCtrl *self, beBaseInfoRam *ram, beModelCtrlInfoWork *work, beModelCtrlMUTEKI *command) {
    if (!(beBaseInfoRam_HasTimer(ram, KEIKATIMER) & 0xFF)) { beBaseInfoRam_StartTimer(ram, KEIKATIMER, 0); }
    if (strcmp(MutekiNameOf::Get(command), OFFWALL) == 0) { work->_isWallCheck = 0; }
    else if (strcmp(MutekiNameOf::Get(command), ONWALL) == 0) { work->_isWallCheck = 1; }
    else if (strcmp(MutekiNameOf::Get(command), OFFFLOOR) == 0) { work->_isFloorCheck = 0; }
    else if (strcmp(MutekiNameOf::Get(command), ONFLOOR) == 0) { work->_isFloorCheck = 1; }
    else { work->_mutekiCount = command->_frame; }
    return 1;
}

void beModelCtrl_UpdateMuteki(beModelCtrl *self, beBaseInfoRam *ram, beModelCtrlInfoWork *work) {
    float count = work->_mutekiCount;
    if (!(count <= 0.0f)) {
        float left = count - beBaseInfoRam_GetTimerFrameDelta(ram, KEIKATIMER);
        if (left < 0.0f) left = 0.0f;
        work->_mutekiCount = left;
    }
}

void beModelCtrl_RunCommands(beModelCtrl *self, beModelCtrlInfo *info, beBaseInfoRam *ram, beModelCtrlInfoWork *work) {
    int jumped;
    const beModelCtrlData *commands;
    int index;
    unsigned char next;
    igObjectSlots *command;
    jumped = 0;
    commands = (beModelCtrlData *)work->_comData;
    index = work->_comIndex;
    if (index != ((igObjectList *)commands->_comList)->_count) {
        do {
            next = 1;
            command = ((igObjectSlots **)((igObjectList *)commands->_comList)->_data)[index];
            if (g_beModelCtrlCTRL_metaObject[0] == command->vfunc_20()) {
                next = ((unsigned char)beModelCtrl_RunCtrl(self, work, (beModelCtrlCTRL *)command));
                index += 1;
            } else if (g_beModelCtrlACTION_metaObject[0] == command->vfunc_20()) {
                next = ((unsigned char)beModelCtrl_RunAction(self, info, ram, (beModelCtrlACTION *)command));
                index += 1;
            } else if (g_beModelCtrlMOVE_metaObject[0] == command->vfunc_20()) {
                next = beModelCtrl_RunMove(self, ram, work, (igObject *)command);
                index += 1;
            } else if (g_beModelCtrlMOVEEX_metaObject[0] == command->vfunc_20()) {
                next = beModelCtrl_RunMove(self, ram, work, (igObject *)command);
                index += 1;
            } else if (g_beModelCtrlMOVERL_metaObject[0] == command->vfunc_20()) {
                next = beModelCtrl_RunMove(self, ram, work, (igObject *)command);
                index += 1;
            } else if (g_beModelCtrlPDMOVE_metaObject[0] == command->vfunc_20()) {
                next = ((unsigned char)beModelCtrl_RunPdMove(self, ram, work, (beModelCtrlPDMOVE *)command));
                index += 1;
            } else if (g_beModelCtrlWCHECK_metaObject[0] == command->vfunc_20()) {
                next = ((unsigned char)beModelCtrl_StartWaitCheck(self, work, (beModelCtrlWCHECK *)command));
                index += 1;
            } else if (g_beModelCtrlHITBOX_metaObject[0] == command->vfunc_20()) {
                next = ((unsigned char)beModelCtrl_RunHitBox(self, ram, work, (beModelCtrlHITBOX *)command));
                index += 1;
            } else if (g_beModelCtrlMUTEKI_metaObject[0] == command->vfunc_20()) {
                next = ((unsigned char)beModelCtrl_RunMuteki(self, ram, work, (beModelCtrlMUTEKI *)command));
                index += 1;
            } else if (g_beModelCtrlLABELCTRL_metaObject[0] == command->vfunc_20()) {
                next = ((unsigned char)beModelCtrl_RunLabelCtrl(self, ram, work, (beModelCtrlLABELCTRL *)command));
                index += 1;
            } else if (g_beModelCtrlLUACALL_metaObject[0] == command->vfunc_20()) {
                next = ((unsigned char)beModelCtrl_RunLuaCall(self, (beBaseInfo *)info, ram, work, (beModelCtrlLUACALL *)command));
                index += 1;
            } else if (g_beModelCtrlAIMAP_metaObject[0] == command->vfunc_20()) {
                next = ((unsigned char)beModelCtrl_RunAiMap(self, info, ram, work, (beModelCtrlAIMAP *)command));
                index += 1;
            } else if (g_beModelCtrlMSGBOX_metaObject[0] == command->vfunc_20()) {
                next = beModelCtrl_RunMsgBox(self, info, work, (beModelCtrlMSGBOX *)command);
                index += 1;
            } else if (g_beModelCtrlLABEL_metaObject[0] == command->vfunc_20()) {
                if (work->_comLabelCount != 0) {
                    next = 0;
                } else {
                    work->_comLabelCount = 1;
                    index += 1;
                }
            } else if (g_beModelCtrlJUMP_metaObject[0] == command->vfunc_20()) {
                jumped = ((unsigned char)beModelCtrl_RunJump(self, ram, (beModelCtrlJUMP *)command)) & 0xFF;
            }
        } while (jumped == 0 && (next & 0xFF) && index != ((igObjectList *)commands->_comList)->_count);
    }
    if (!(jumped & 0xFF)) {
        work->_comIndex = index;
    }
}

/* Owning stack reference to the freshly created data list, released on scope exit (reference count
 * in the low 23 bits of _refCount). */

void beModelCtrl_UpdateDirection(beModelCtrl *self, beBaseInfo *info, beBaseInfoRam *ram, beModelCtrlInfoWork *work, int force) {
    Vec3 rotation;
    float translation[4];
    int axis;
    float *target;
    float *current;
    float *limit;
    int offset;
    float *next;
    float *direction;
    int matrix;
    float step;
    float from;
    float to;
    float up;
    float down;
    float wrapped;
    target = (float *)&work->_targetDirection[0];
    ((float*)&rotation)[0] = work->_targetDirection[0];
    ((float*)&rotation)[1] = work->_targetDirection[1];
    ((float*)&rotation)[2] = work->_targetDirection[2];
    if (!(force & 0xff)) {
        axis = 0;
        goto pre;
    body:
        if (*current != *target) {
            limit = (float *)((char *)&work->_directionLimiter[0] + offset);
            if (*limit == 0.0f) {
                *next = *(float *)((char *)&work->_direction[0] + offset);
            } else {
                step = *limit * beBaseInfoRam_GetTimerFrameDelta(ram, KEIKATIMER);
                from = *(float *)((char *)&work->_direction[0] + offset);
                to = *(float *)((char *)&work->_targetDirection[0] + offset);
                while (from < 0.0f) from += 6.2831855f;
                while (from >= 6.2831855f) from -= 6.2831855f;
                while (to < 0.0f) to += 6.2831855f;
                while (to >= 6.2831855f) to -= 6.2831855f;
                if (from <= to) {
                    up = to - from;
                    down = from - (to - 6.2831855f);
                } else {
                    down = from - to;
                    wrapped = to; wrapped += 6.2831855f; up = wrapped - from;
                }
                if (up < down) {
                    if (up > step) to = from + step;
                    else to = to;
                } else if (down > step) {
                    to = from - step;
                } else to = to;
                *next = to;
            }
        }
        target++; current++; offset += 4; next++; axis++;
    test:
        if (axis < 3) goto body;
    }
    if (force == 0) {
        bool diff;
        direction = (float *)&work->_direction[0];
        diff = rotation.x != direction[0] || rotation.y != direction[1] || rotation.z != direction[2];
        if (!diff) goto done;
    }
    if (((igObject *)ram->_dataList) == 0) {
        int base = igObject_GetAllocator(ram);
        int allocator;
        if (g_useOwnerAllocator != 0) allocator = base; else allocator = Memory_GetAllocatorBySelector(g_defaultAllocatorSelector[0]);
        igSmartPointer<igObject> created(((igObject *)beBaseInfoDataList_Create(allocator)));
        igObject *list = (igObject *)created.p;
        if (list != 0) list->_refCount = list->_refCount + 1;
        igObject *old = ((igObject *)ram->_dataList);
        if (old != 0) {
            old->_refCount = old->_refCount - 1;
            if ((old->_refCount & 0x7fffff) == 0) igObject_Destroy(old);
        }
        ram->_dataList = (int)list;
    }
    matrix = ((beModelCtrlInfoRamData *)igProperty_FindByName(((igObject *)ram->_dataList), g_propertyNameField[0], ONE_3))->_node + 32;
    Matrix44_GetTranslation(matrix, translation);
    FUN_00190ed0(matrix, rotation.x, ((float*)&rotation)[1], ((float*)&rotation)[2]);
    Matrix44_SetTranslation((float *)matrix, (void *)translation);
    work->_direction[0] = rotation.x;
    work->_direction[1] = rotation.y;
    work->_direction[2] = rotation.z;
done:
    return;
pre:
    current = (float *)&work->_direction[0];
    offset = 0;
    next = &rotation.x;
    goto test;
}

/* Owning stack reference to the freshly created data list; released on scope exit (reference count
 * in the low 23 bits of _refCount). */

void Gap__Core__igObject__vfunc_31(beModelCtrl *self, beBaseInfoRam *ram) {
    int inverted;
    float oldPos[3];
    float newPos[3];
    float delta[3];
    float pos[3];
    int lockMatrix[16];
    int boneMatrix[16];
    int modelMatrix[16];
    int oldRotation[16];
    int offset[16];
    int local[16];
    int world[16];
    beBaseInfo *info = (beBaseInfo *)ram->_parentInfo;
    if (ram->_dataList == 0) {
        int allocator = igObject_GetAllocator(ram);
        int chosen;
        igObject *created;
        igObject *old;
        if (g_useOwnerAllocator != 0) { chosen = allocator; } else { chosen = Memory_GetAllocatorBySelector(g_defaultAllocatorSelector[0]); }
        igSmartPointer<igObject> ref(beBaseInfoDataList_Create(chosen));
        created = ref.p;
        if (created != 0) created->_refCount = created->_refCount + 1;
        old = (igObject *)ram->_dataList;
        if (old != 0) {
            old->_refCount = old->_refCount - 1;
            if ((old->_refCount & 0x7FFFFF) == 0) igObject_Destroy(old);
        }
        ram->_dataList = (int)created;
    }
    beModelCtrlInfoRamData *ramData = (beModelCtrlInfoRamData *)igProperty_FindByName(ram->_dataList, g_propertyNameField[0], ONE_3);
    beModelCtrlInfoWork *work = (beModelCtrlInfoWork *)ramData->_work;
    if (ram->_isRun != 0 && work->_isOnFreeze == 0) {
        int token;
        int posNode;
        beModelCtrlInfoRideOn4 *rideOn;
        if (strcmp(work->_seqCodeName, SQ_ERAS_2) == 0) {
            ((beModelCtrlSlots *)self)->vfunc_33(ram, REMOVE_2);
            return;
        }
        work->_keyInput = 0;
        if (g_stringPool[0] == 0) {
            int pool = StringPool_Allocate(16);
            if (pool != 0) pool = StringPool_Construct(pool);
            g_stringPool[0] = pool;
        }
        token = ((int)StringPool_Intern(g_stringPool[0], SQ_NONE));
        if (work->_keyEventName != 0) {
            int *header = (int *)(work->_keyEventName - 8);
            int refs = *(int *)(work->_keyEventName - 4) - 1;
            *(int *)(work->_keyEventName - 4) = refs;
            if (refs == 0) StringChunk_ReleaseHeader(*header, header);
        }
        work->_keyEventName = token;
        if (work->_ctrlSt0 != 0) {
            beModelCtrl_UpdateKeyCtrl(self, info, ram, work);
        } else if (work->_aI != 0) {
            beBaseInfoRam_RemoveTimer(ram, AITIMER);
        }
        ((beModelCtrlSlots *)self)->vfunc_46(ram);
        if (work->_isPosLock == 0) {
            beModelCtrl_ApplyMoves(self, info, ram, work);
        } else {
            if (work->_posLockNode != 0) {
                Matrix44_Copy(lockMatrix, work->_posLockNode + 32);
                Matrix44_TranslateLocal(lockMatrix, &work->_posLockOffset[0]);
                ((beModelCtrlNode2Slots *)ramData->_node)->vfunc_35(lockMatrix);
            } else if (work->_posLockTrc != 0) {
                ((beModelCtrlNode2Slots *)ramData->_node)->vfunc_35((int *)(*(int *)(work->_posLockTrc + 16) + *(int *)((char *)DAT_00561288[0] + 8)));
            } else if (work->_posLockModelName != 0) {
                beMessenger_SelectReceivers(self->_messenger, ACTION_2, work->_posLockModelName, ram->_ramNo);
                beMessenger_AppendString(self->_messenger, work->_posLockBoneName);
                beMessenger_DispatchSelected(self->_messenger, GETBONEMATRIX);
                if (beMessenger_GetMatrixCount(self->_messenger) == 1) {
                    beMessenger_GetMatrix(boneMatrix, self->_messenger, 0);
                    beMessenger_SendNamed(self->_messenger, MODELCTRL_7, work->_posLockModelName, ram->_ramNo, GETMATRIX_2);
                    if (beMessenger_GetMatrixCount(self->_messenger) == 1) {
                        beMessenger_GetMatrix(modelMatrix, self->_messenger, 0);
                        FUN_001906d0(modelMatrix, boneMatrix);
                        ((beModelCtrlNode2Slots *)ramData->_node)->vfunc_35(modelMatrix);
                    }
                }
            }
            if (work->_baseAABox != 0) beModelCtrl_UpdateBound(self, (beModelCtrlNode2 *)ramData->_node, (igAABox *)work->_baseAABox);
        }
        rideOn = (beModelCtrlInfoRideOn4 *)work->_rideOnData;
        if (rideOn != 0) {
            ((beModelCtrlInfoRideOnSlots *)rideOn)->vfunc_21((void *)(ramData->_node + 32));
            Matrix44_GetTranslation((int)rideOn->_oldMatrix, (float *)oldPos);
            Matrix44_GetTranslation(ramData->_node + 32, newPos);
            delta[0] = newPos[0] - oldPos[0];
            delta[1] = newPos[1] - oldPos[1];
            delta[2] = newPos[2] - oldPos[2];
            Matrix44_Copy(oldRotation, rideOn->_oldMatrix);
            Matrix44_Copy(offset, ramData->_node + 32);
            Matrix44_SetTranslation((float *)oldRotation, (void *)&g_vec3Zero[0]);
            FUN_00191f30(&inverted, oldRotation, oldRotation);
            Matrix44_SetTranslation((float *)offset, (void *)delta);
            igMatrix44f_SetIdentity(local);
            FUN_001904f0(local, offset, oldRotation);
            igMatrix44f_SetIdentity(world);
            FUN_001904f0(world, local, rideOn->_modelNode + 32);
            ((beModelCtrlNode2Slots *)ramData->_node)->vfunc_35(world);
            Matrix44_Copy(rideOn->_oldMatrix, rideOn->_modelNode + 32);
            work->_isHitCheck = 1;
        }
        if (work->_wCheckName != 0) beModelCtrl_UpdateWaitCheck(self, (beModelCtrlInfo *)info, ram, work);
        beModelCtrl_UpdateMuteki(self, ram, work);
        beModelCtrlSubCom_Update(work->_subCommand, ram);
        if (work->_isHitCheck != 0) beModelCtrl_CheckWallAndFloor(self, info, ram, work);
        rideOn = (beModelCtrlInfoRideOn4 *)work->_rideOnData;
        if (rideOn != 0 && rideOn->_modelRamNo == 0x68) {
            Matrix44_GetTranslation(ramData->_node + 32, pos);
            ((float *)&rideOn->_oldPlayerPos[0])[0] = pos[0];
            ((float *)&rideOn->_oldPlayerPos[0])[1] = pos[1];
            ((float *)&rideOn->_oldPlayerPos[0])[2] = pos[2];
        }
    }
}

/* Slot 46 default: empty. */
void Gap__Core__igObject__vfunc_46(void)
{
}

int beModelCtrlInfoWork_FindSeqLabel(beModelCtrl *self, beModelCtrlInfoWork *work) {
    int index = 0;
    if (work->_labelSeqList != 0) {
        int seqName = work->_seqCodeName;
        int token;
        int slot;
        if (seqName == 0) {
            token = 0;
        } else {
            if (g_stringPool[0] == 0) {
                int pool = StringPool_Allocate(16);
                if (pool != 0) pool = StringPool_Construct(pool);
                g_stringPool[0] = pool;
            }
            token = ((int)StringPool_Intern(g_stringPool[0], seqName));
        }
        {
            StringRef key((char *)token);
            slot = FUN_001cafc0(work->_labelSeqList, &key, 0);
        }
        if (slot != -1) {
            index = ((int *)((igIntList *)work->_labelOffsetList)->_data)[slot];
            if (index == -1) {
                int labelName;
                beModelCtrlData *commands;
                int count, i;
                /* the copied token is a temporary: only the pointer outlives it (the list keeps its share) */
                labelName = (int)StringList_CopyRetained(work->_labelNameList, slot).p;
                commands = (beModelCtrlData *)work->_comData;
                count = ((igObjectList *)commands->_comList)->_count;
                for (i = 0; i < count; i++) {
                    beModelCtrlLABEL *label = (beModelCtrlLABEL *)((int *)((igObjectList *)commands->_comList)->_data)[i];
                    if (g_beModelCtrlLABEL_metaObject[0] == ((igObjectSlots *)label)->vfunc_20()) {
                        if (strcmp(label->_name != 0 ? (int *)label->_name : &emptyString[0], labelName) == 0) {
                            igIntList *offsets = (igIntList *)work->_labelOffsetList;
                            index = i;
                            if (offsets->_count != 0 && slot >= 0 && slot < offsets->_count) {
                                ((int *)offsets->_data)[slot] = i;
                            }
                            break;
                        }
                    }
                }
            }
        }
    }
    return index;
}

/* Owning stack reference to the freshly created bound box; released on scope exit once the node
 * holds its own reference (reference count in the low 23 bits of _refCount). */

void beModelCtrl_UpdateBound(beModelCtrl *self, beModelCtrlNode2 *node, igAABox *box) {
    igAABox *bound;
    bound = (igAABox *)node->_bound;
    if (bound == 0) {
        int base = igObject_GetAllocator(self);
        int allocator;
        if (g_useOwnerAllocator != 0) {
            allocator = base;
        } else {
            allocator = Memory_GetAllocatorBySelector(g_defaultAllocatorSelector[0]);
        }
        igSmartPointer<igAABox> created(igAABox_CreateInstance(allocator));
        bound = created.p;
        if (bound != 0) {
            bound->_refCount++;
        }
        Rel::go((igAABox *)node->_bound);
        node->_bound = (int)bound;
        /* matching construct: the box is re-read from the reference before it leaves scope, so the release
         * below works on that register copy (retail 0x003969ec) */
        bound = created.p;
    }
    bound->_min[0] = box->_min[0];
    bound->_min[1] = box->_min[1];
    bound->_min[2] = box->_min[2];
    bound->_max[0] = box->_max[0];
    bound->_max[1] = box->_max[1];
    bound->_max[2] = box->_max[2];
    igAABox_Transform(bound, node->_m);
}

#define ALLOCATOR(a, o) int a = igObject_GetAllocator(o); a = g_useOwnerAllocator ? a : Memory_GetAllocatorBySelector(g_defaultAllocatorSelector[0]);
#define POOL() if (((void * *)g_stringPool)[0] == 0) { void *pl_ = ((void *)StringPool_Allocate(0x10)); if (pl_ != 0) pl_ = ((void *)StringPool_Construct(pl_)); ((void * *)g_stringPool)[0] = pl_; }
#define RELEASE_STRING(old) if (old) { int *h_ = (int *)old - 2; int c_ = ((int *)old)[-1] - 1; ((int *)old)[-1] = c_; if (c_ == 0) StringChunk_ReleaseHeader(*h_, h_); }
#define SET_WORK_STRING(fld, txt) { POOL() const char *tk_ = ((const char *)StringPool_Intern(((void * *)g_stringPool)[0], txt)); const char *old_ = (const char *)work->fld; RELEASE_STRING(old_) work->fld = (int)tk_; }
#define INFO_NAME(b) const char *b; { const char *a_ = (const char *)info->_name; if (a_ != 0) b = a_; else b = ((char *)emptyString); }
#define MESSENGER (self->_messenger)
#define MODEL_NODE ((beModelCtrlNode2 *)ramData->_node)
#define FIRST_LOD(n) (((igLod **)((igObjectList *)(n)->_childList)->_data)[0])
#define ENSURE_DATA_LIST(ram_) DataList::Ensure(ram_, held);
int Gap__Bec__beModelCtrl__vfunc_33(beModelCtrl *self, beBaseInfoRam *ram, const char *message) {
    beBaseInfo *info = (beBaseInfo *)ram->_parentInfo;
    Vec3 startForward, setForward, movePosition, moveRotation, bulletPos, modelPos, quicksandPos, floorPos, effectOffset, effectRotation, effectRotationIn, conveyorVector, quicksandCenter;
    float setMatrix[16], moveMatrix[16], bulletMatrix[16], quicksandMatrix[16], floorMatrix[16];
    int bullet;
    igObjectList *boxes;
    int hitBox;
    igObject *node2;
    beModelCtrlInfoRideOn *held;
    ENSURE_DATA_LIST(ram)
    beModelCtrlInfoRamData *ramData = (beModelCtrlInfoRamData *)((beBaseInfoData *)igProperty_FindByName(ram->_dataList, g_propertyNameField[0], ((char *)ONE_3)));
    beModelCtrlInfoWork *work = (beModelCtrlInfoWork *)ramData->_work;
    if (((beModelCtrlSlots *)self)->vfunc_47(ram, message) == 1) return 1;
    unsigned sel = beMessenger_ResolveEnumValue(MESSENGER, beModelCtrl_GetMessageEnum(), message);
    switch (sel) {
    case MSG_GENERATE: {
        StringRef sequence;
        sequence.p = 0;
        ram->_isRun = 1;
        ram->_st0 = 0; ram->_st3 = 0; ram->_st2 = 0; ram->_st1 = 0;
        if (beMessenger_GetStringCount(MESSENGER) == 1) {
            const char *t = beMessenger_GetString(MESSENGER, 0);
            POOL()
            const char *tk = ((const char *)StringPool_Intern(((void * *)g_stringPool)[0], t));
            const char *o = sequence.p;
            RELEASE_STRING(o)
            sequence.p = (char *)tk;
        } else if (beMessenger_GetStringCount(MESSENGER) >= 2) {
            const char *t = beMessenger_GetString(MESSENGER, 1);
            POOL()
            const char *tk = ((const char *)StringPool_Intern(((void * *)g_stringPool)[0], t));
            const char *o = sequence.p;
            RELEASE_STRING(o)
            sequence.p = (char *)tk;
        }
        ((beModelCtrlSlots *)self)->vfunc_36(ram);
        beModelCtrlInfoWork *started = (beModelCtrlInfoWork *)ramData->_work;
        beDataObjInt *mHp = (beDataObjInt *)started->_mHp;
        if (mHp->_data == 0) {
            mHp->_data = 0x64;
            ((beDataObjInt *)started->_hp)->_data = 0x64;
        }
        igObject *bound = (igObject *)FIRST_LOD(MODEL_NODE)->_bound;
        RETAIN(bound)
        RELEASE(started->_baseAABox)
        started->_baseAABox = (int)bound;
        beModelCtrlNode2 *modelNode = MODEL_NODE;
        RELEASE(modelNode->_bound)
        modelNode->_bound = 0;
        Vec3f_TransformDirection(&startForward, ((float *)g_vec3ZAxis), MODEL_NODE->_m);
        float ang = atan2f(startForward.x, startForward.z);
        started->_direction[1] = ang;
        started->_targetDirection[1] = ang;
        if (((beBaseInfoData *)igProperty_FindByName(info->_dataList, g_propertyNameField[0], ((char *)AIM))) != 0 ||
            ((beBaseInfoData *)igProperty_FindByName(info->_dataList, g_propertyNameField[0], ((char *)AIH))) != 0) {
            ALLOCATOR(a, self)
            ObjRef<0> r((igObject *)beModelCtrlInfoAI_Create(a));
            igObject *s = r.p;
            RETAIN(s)
            RELEASE(started->_aI)
            started->_aI = (int)s;
        }
        if (sequence.p == 0)
            ((beModelCtrlSlots *)self)->vfunc_33(ram, SQ_WAIT_2);
        else
            ((beModelCtrlSlots *)self)->vfunc_33(ram, sequence.p);
        igObject *baseBox = (igObject *)started->_baseAABox;
        if (baseBox != 0) beModelCtrl_UpdateBound(self, MODEL_NODE, (igAABox *)baseBox);
        return 1;
    }
    case MSG_REMOVE:
        if (ram->_isRun != 0) {
            ((beModelCtrlSlots *)self)->vfunc_42(ram);
            beMessenger_PushArgContext(MESSENGER);
            int id = ram->_ramNo;
            INFO_NAME(n)
            beMessenger_SendNamed(MESSENGER, ((char *)ACTION_2), n, id, NDSP_2);
            if (work != 0) beModelCtrlSubCom_StopAll(work->_subCommand, ram);
            RELEASE(ramData->_work)
            ramData->_work = 0;
            beModelCtrlNode2 *modelNode = MODEL_NODE;
            RELEASE(modelNode->_bound)
            modelNode->_bound = 0;
            beBaseInfoRam_RemoveAllTimers(ram);
            ram->_isRun = 0;
            beMessenger_PopArgContext(MESSENGER);
        }
        return 1;
    case MSG_ISRUN: {
        unsigned char f = ram->_isRun;
        beMessenger_AppendBool(MESSENGER, f);
        return 1;
    }
    case MSG_ISSEQNAME:
        if (ram->_isRun == 0) {
            beMessenger_AppendBool(MESSENGER, 0);
        } else if (work == 0) {
            beMessenger_AppendBool(MESSENGER, 0);
        } else if (strcmp((const char *)work->_seqCodeName, beMessenger_GetString(MESSENGER, 0)) == 0) {
            beMessenger_AppendBool(MESSENGER, 1);
        } else {
            beMessenger_AppendBool(MESSENGER, 0);
        }
        return 1;
    case MSG_SETEFFECT:
        if (ram->_isRun != 0 && work != 0) {
            float *p;
            if (beMessenger_GetVec3Count(MESSENGER) == 2) {
                beMessenger_GetVec3(&effectRotationIn, MESSENGER, 1);
                p = &effectRotationIn.x;
            } else {
                p = g_vec3Zero;
            }
            effectRotation.x = p[0]; effectRotation.y = p[1]; effectRotation.z = p[2];
            int sub = work->_subCommand;
            const char *s2 = beMessenger_GetString(MESSENGER, 0);
            const char *s1 = beMessenger_GetString(MESSENGER, 1);
            float f20 = beMessenger_GetFloat(MESSENGER, 0);
            beMessenger_GetVec3(&effectOffset, MESSENGER, 0);
            int b0 = beMessenger_GetBool(MESSENGER, 0);
            beModelCtrlSubCom_AddEffect(sub, s2, s1, &effectOffset, &effectRotation, b0, f20, beMessenger_GetBool(MESSENGER, 1));
        }
        return 1;
    case MSG_SETSOUND:
        if (ram->_isRun != 0 && work != 0) {
            int sub = work->_subCommand;
            const char *s0 = beMessenger_GetString(MESSENGER, 0);
            beModelCtrlSubCom_AddSound(sub, s0, beMessenger_GetFloat(MESSENGER, 0));
        }
        return 1;
    case MSG_GETSEQNAMELIST: {
        beModelCtrlInfoDataSeq *seq = (beModelCtrlInfoDataSeq *)((beBaseInfoData *)igProperty_FindByName(info->_dataList, g_propertyNameField[0], SEQ));
        igObjectList *l = (igObjectList *)seq->_dataList;
        int n = l->_count;
        beMessenger_AppendString(MESSENGER, ((char *)SQ_ERAS_2));
        int i;
        for (i = 0; i < n; i++) {
            beModelCtrlData *entry = (beModelCtrlData *)((void **)l->_data)[i];
            const char *b;
            const char *a_ = (const char *)entry->_name;
            if (a_ != 0) b = a_; else b = ((char *)emptyString);
            beMessenger_AppendString(MESSENGER, b);
        }
        return 1;
    }
    case MSG_ONHITBULLETBOX:
        self->_isDebugHitBox = 1;
        return 1;
    case MSG_OFHITBULLETBOX:
        self->_isDebugHitBox = 0;
        return 1;
    case MSG_GETINFONAME: {
        INFO_NAME(n)
        beMessenger_AppendString(MESSENGER, n);
        return 1;
    }
    case MSG_GETINFONAME_RUN:
        if (ram->_isRun != 0) {
            INFO_NAME(n)
            beMessenger_AppendString(MESSENGER, n);
        }
        return 1;
    case MSG_SETMATRIX:
        if (ram->_isRun != 0 && work != 0 && beMessenger_GetMatrixCount(MESSENGER) != 0) {
            beMessenger_GetMatrix(setMatrix, MESSENGER, 0);
            ((beModelCtrlNode2Slots *)ramData->_node)->vfunc_35(setMatrix);
            if (work != 0) {
                Vec3f_TransformDirection(&setForward, ((float *)g_vec3ZAxis), setMatrix);
                float ang = atan2f(setForward.x, setForward.z);
                work->_direction[1] = ang;
                work->_targetDirection[1] = ang;
            }
            igObject *a2 = (igObject *)work->_baseAABox;
            if (a2 != 0) beModelCtrl_UpdateBound(self, MODEL_NODE, (igAABox *)a2);
        }
        return 1;
    case MSG_GETMATRIX:
        if (ram->_isRun == 0) return 1;
    case MSG_GETMATRIX_ALL:
        beMessenger_AppendInt(MESSENGER, ram->_ramNo);
        beMessenger_AppendMatrix(MESSENGER, MODEL_NODE->_m);
        beMessenger_AppendObject(MESSENGER, MODEL_NODE);
        return 1;
    case MSG_GETMATRIX_ACTIVE:
        if (ram->_isRun != 0 && work != 0 && work->_mutekiCount == 0.0f)
            beMessenger_AppendMatrix(MESSENGER, MODEL_NODE->_m);
        return 1;
    case MSG_GETTRCDATA:
        if (ram->_isRun != 0) {
            ENSURE_DATA_LIST(ram)
            beBaseInfoData *t = ((beBaseInfoData *)igProperty_FindByName(ram->_dataList, g_propertyNameField[0], TRC));
            if (t != 0) beMessenger_AppendObject(MESSENGER, t);
        }
        return 1;
    case MSG_ONCTRL:
        if (ram->_isRun != 0 && work != 0) work->_isOnCtrl = 1;
        return 1;
    case MSG_OFCTRL:
        if (ram->_isRun != 0 && work != 0) {
            work->_isOnCtrl = 0;
            ((beModelCtrlSlots *)self)->vfunc_40(ram);
        }
        return 1;
    case MSG_ONFREEZE:
        if (ram->_isRun != 0 && work != 0) {
            beBaseInfoRam_SetAllTimerScales(ram, 0.0f);
            int id = ram->_ramNo;
            INFO_NAME(n)
            beMessenger_SendNamed(MESSENGER, ((char *)ACTION_2), n, id, ONFREEZE);
            work->_isOnFreeze = 1;
            ((beModelCtrlSlots *)self)->vfunc_41(ram);
        }
        return 1;
    case MSG_OFFREEZE:
        if (ram->_isRun != 0 && work != 0) {
            beBaseInfoRam_SetAllTimerScales(ram, 1.0f);
            int id = ram->_ramNo;
            INFO_NAME(n)
            beMessenger_SendNamed(MESSENGER, ((char *)ACTION_2), n, id, OFFREEZE);
            work->_isOnFreeze = 0;
        }
        return 1;
    case MSG_SETLODHIGH:
        if (ram->_isRun != 0 && work != 0 && work->_svLODHighRange == -1.0f) {
            int t = g_igLod_metaObject[0];
            igLod *o = FIRST_LOD(MODEL_NODE);
            if (t == ((igLodSlots *)o)->vfunc_20()) {
                igNodeList *children = (igNodeList *)o->_childList;
                int cnt = 0;
                if (children != 0) cnt = children->_count;
                if (cnt == 3) {
                    igFloatList *ranges = (igFloatList *)o->_rangeList;
                    work->_svLODHighRange = ((float *)ranges->_data)[2];
                    int n = ranges->_count;
                    if (n != 0 && n > 2) ((float *)ranges->_data)[2] = DAT_004c8fb8[0];
                    ((igLodSlots *)o)->vfunc_29();
                }
            }
        }
        return 1;
    case MSG_RESETLODHIGH:
        if (ram->_isRun != 0 && work != 0) {
            float f = work->_svLODHighRange;
            if (f != -1.0f) {
                igLod *o = FIRST_LOD(MODEL_NODE);
                igFloatList *ranges = (igFloatList *)o->_rangeList;
                int n = ranges->_count;
                if (n != 0 && n > 2) ((float *)ranges->_data)[2] = f;
                work->_svLODHighRange = -1.0f;
                ((igLodSlots *)o)->vfunc_29();
            }
        }
        return 1;
    case MSG_MOVETRANS:
        if (ram->_isRun != 0 && work != 0) {
            beMessenger_GetVec3(&movePosition, MESSENGER, 0);
            beMessenger_GetVec3(&moveRotation, MESSENGER, 1);
            igMatrix44f_SetIdentity(moveMatrix);
            Matrix44_FromTranslation(moveMatrix, &movePosition);
            if (moveRotation.x != 0.0f) FUN_00191670(moveMatrix, g_vec3XAxis, 0.017453292f * moveRotation.x);
            if (moveRotation.y != 0.0f) FUN_00191670(moveMatrix, g_vec3YAxis, 0.017453292f * moveRotation.y);
            { float rz = moveRotation.z; if (rz != 0.0f) FUN_00191670(moveMatrix, ((float *)g_vec3ZAxis), 0.017453292f * rz); }
            ((beModelCtrlNode2Slots *)ramData->_node)->vfunc_35(moveMatrix);
            work->_targetDirection[1] = 0.017453292f * moveRotation.y;
            beModelCtrl_UpdateDirection(self, info, ram, work, 1);
            igObject *a2 = (igObject *)work->_baseAABox;
            if (a2 != 0) beModelCtrl_UpdateBound(self, MODEL_NODE, (igAABox *)a2);
        }
        return 1;
    case MSG_SETLABEL:
        if (ram->_isRun != 0 && work != 0) {
            const char *s1 = beMessenger_GetString(MESSENGER, 0);
            beModelCtrlInfoWork_SetSeqLabel(self, ram, work, s1, beMessenger_GetString(MESSENGER, 1));
        }
        return 1;
    case MSG_GETHP:
        if (ram->_isRun == 0) {
            beMessenger_AppendInt(MESSENGER, 0);
        } else if (work == 0) {
            beMessenger_AppendInt(MESSENGER, 0);
        } else {
            beMessenger_AppendInt(MESSENGER, ((beDataObjInt *)work->_hp)->_data);
            beMessenger_AppendObject(MESSENGER, (void *)work->_hp);
            beMessenger_AppendObject(MESSENGER, (void *)work->_mHp);
        }
        return 1;
    case MSG_SETHP:
        if (ram->_isRun != 0 && work != 0) {
            int v = beMessenger_GetInt(MESSENGER, 0);
            ((beDataObjInt *)work->_hp)->_data = v;
            beDataObjInt *mHp = (beDataObjInt *)work->_mHp;
            if (mHp->_data < v) mHp->_data = v;
        }
        return 1;
    case MSG_GETRECNO:
        if (ram->_isRun != 0 && work != 0) beMessenger_AppendInt(MESSENGER, work->_recNo);
        return 1;
    case MSG_CHKBULLET:
        if (work->_mutekiCount != 0.0f) {
            unsigned char ok = 0;
            INFO_NAME(n)
            if (*n == 0x70 && *beMessenger_GetString(MESSENGER, 0) == 0x70 && work->_hp != 0) ok = 1;
            if (!(ok & 0xFF)) return 1;
        }
        if (work->_isOnCtrl == 0 || strcmp((const char *)work->_seqCodeName, ((char *)SQ_ERAS_2)) == 0) return 1;
        {
            igObject *hitbody = (igObject *)work->_hitBody;
            if (hitbody == 0) {
                ALLOCATOR(a, self)
                ObjRef<1> r((igObject *)beModelCtrlInfoHitBody_Create(a));
                igObject *s = r.p;
                RETAIN(s)
                RELEASE(work->_hitBody)
                work->_hitBody = (int)s;
                hitbody = r.p;
            }
            bullet = ((int)beMessenger_GetObject(MESSENGER, 0));
            boxes = ((igObjectList *)beModelCtrlInfoHitBody_GetAABoxList((beModelCtrlInfoHitBody *)hitbody, ram, (int)MODEL_NODE->_m, ((igInsightCore *)self->_insight)->_worldTime));
            unsigned char found = 0;
            int idx = 0;
            int cnt = boxes->_count;
            for (idx = 0; idx < cnt; idx++) {
                if (!FUN_0018b050(((void **)boxes->_data)[idx], bullet)) continue;
                {
                    hitBox = idx;
                    found = 1;
                    break;
                }
            }
            if (found) {
                int bulletKind = beMessenger_GetInt(MESSENGER, 0);
                beMessenger_GetMatrix(bulletMatrix, MESSENGER, 0);
                const char *hitterName = beMessenger_GetString(MESSENGER, 0);
                int hitterRamNo = beMessenger_GetInt(MESSENGER, 1);
                int hitterRecNo = -1;
                Matrix44_GetTranslation((int)bulletMatrix, (float *)&bulletPos);
                Matrix44_GetTranslation((int)MODEL_NODE->_m, (float *)&modelPos);
                beMessenger_PushArgContext(MESSENGER);
                if (*hitterName != 0x70) {
                    beMessenger_SendNamed(MESSENGER, ((char *)MODELCTRL_7), hitterName, hitterRamNo, GETRECNO);
                    if (beMessenger_GetIntCount(MESSENGER) == 1)
                        hitterRecNo = beMessenger_GetInt(MESSENGER, 0);
                    else
                        hitterRecNo = -9;
                }
                if (hitterRecNo != -9) {
                    INFO_NAME(n)
                    beModelCtrl_CallLua(self, ram, hit, Hit, n, bulletKind, hitBox, hitterName, hitterRamNo, hitterRecNo);
                    if (((unsigned char *)g_mdlDmgTurn)[0] != 0) {
                        work->_targetDirection[1] = atan2f(bulletPos.x - modelPos.x, bulletPos.z - modelPos.z);
                        beModelCtrl_UpdateDirection(self, info, ram, work, 1);
                    }
                }
                beMessenger_PopArgContext(MESSENGER);
                if (beMessenger_GetBoolCount(MESSENGER) == 0) beMessenger_AppendBool(MESSENGER, 1);
            }
        }
        return 1;
    case MSG_GENERATE_NDSP:
    default:
        if (ram->_isRun != 0) {
            if (strcmp(message, ((char *)SQ_ERAS_2)) == 0) {
                ((beModelCtrlSlots *)self)->vfunc_43(ram);
                POOL()
                const char *tk = ((const char *)StringPool_Intern(((void * *)g_stringPool)[0], ((char *)SQ_ERAS_2)));
                const char *old = (const char *)work->_seqCodeName;
                RELEASE_STRING(old)
                work->_seqCodeName = (int)tk;
            } else if (strcmp(message, SQ_ERAS2) == 0) {
                beMessenger_PushArgContext(MESSENGER);
                int id = ram->_ramNo;
                INFO_NAME(n)
                beMessenger_SendNamed(MESSENGER, ((char *)ACTION_2), n, id, NDSP_2);
                if (work != 0) beModelCtrlSubCom_StopAll(work->_subCommand, ram);
                beModelCtrlNode2 *modelNode = MODEL_NODE;
                RELEASE(modelNode->_bound)
                modelNode->_bound = 0;
                beBaseInfoRam_RemoveAllTimers(ram);
                beMessenger_PopArgContext(MESSENGER);
            } else {
                const char *tk;
                beModelCtrlInfoDataSeq *fb = (beModelCtrlInfoDataSeq *)((beBaseInfoData *)igProperty_FindByName(info->_dataList, g_propertyNameField[0], SEQ));
                beModelCtrlData *t = (beModelCtrlData *)((beBaseInfoData *)igProperty_FindByName(fb->_dataList, g_propertyNameField[0], message));
                POOL()
                tk = ((const char *)StringPool_Intern(((void * *)g_stringPool)[0], message));
                const char *old = (const char *)work->_seqCodeName;
                RELEASE_STRING(old)
                work->_seqCodeName = (int)tk;
                RETAIN(t)
                RELEASE(work->_comData)
                work->_comData = (int)t;
                work->_comIndex = beModelCtrlInfoWork_FindSeqLabel(self, work);
                work->_comLabelCount = 0;
                work->_ctrlSt0 = 0;
                work->_ctrlSt1 = 0;
                work->_ctrlSt1 = 0;
                ((igDataList *)work->_pdMoveDataList)->_count = 0;
                SET_WORK_STRING(_wCheckName, 0)
                beModelCtrlSubCom_StopAll(work->_subCommand, ram);
                SET_WORK_STRING(_luaBHit, 0)
                SET_WORK_STRING(_luaWHit, 0)
                SET_WORK_STRING(_luaFHit, 0)
                work->_isWallCheck = 1; work->_isFloorCheck = 1; work->_isFallCheck = 1;
                if (work->_mutekiCount < 0.0f) work->_mutekiCount = 0.0f;
                int n = ((beModelCtrlMoveObjectList *)work->_moveObjectList)->_count;
                int i;
                for (i = 0; i < n; i++) {
                    beModelCtrlMoveObject *c = MoveObjects(work)[i];
                    if (i != 3) {
                        if (c->_isSeqStop != 0) beModelCtrlMoveObject_Stop((beModelCtrlMoveObject *)c);
                    } else {
                        c->_isRun = 0;
                        c->_speed = 0;
                    }
                }
                beModelCtrl_RunCommands(self, (beModelCtrlInfo *)info, ram, work);
                ((beModelCtrlSlots *)self)->vfunc_44(ram);
            }
        }
        return 1;
    case MSG_ACTION1:
        ((beModelCtrlSlots *)self)->vfunc_45(ram);
        return 1;
    case MSG_SETCONVEYOR:
        if (work != 0) {
            if (beMessenger_GetInt(MESSENGER, 0) != 0) {
                if (work->_rideOnData == 0) {
                    ALLOCATOR(a, self)
                    ObjRef<2> r((igObject *)beModelCtrlInfoRideOn2_Create(a));
                                        float *mt = (float *)MODEL_NODE->_m;
                    {
                        ALLOCATOR(b, self)
                        ObjRef<5> r2((igObject *)beModelCtrlNode2_Create(b));
                        ((beModelCtrlNode2Slots *)r2.p)->vfunc_35(mt);
                        node2 = r2.p;
                        held = (beModelCtrlInfoRideOn *)r.p;
                        RETAIN(node2)
                        RELEASE(held->_modelNode)
                        held->_modelNode = (int)node2;
                    }
                    Matrix44_Copy(((beModelCtrlInfoRideOn2 *)r.p)->_oldMatrix, mt);
                    beMessenger_GetVec3(&conveyorVector, MESSENGER, 0);
                    { beModelCtrlInfoRideOn2 *f2 = (beModelCtrlInfoRideOn2 *)r.p; f2->_vector[0] = conveyorVector.x; f2->_vector[1] = conveyorVector.y; f2->_vector[2] = conveyorVector.z; }
                    {
                        igObject *s = r.p;
                        RETAIN(s)
                        RELEASE(work->_rideOnData)
                        work->_rideOnData = (int)s;
                    }
                }
            } else {
                RELEASE(work->_rideOnData)
                work->_rideOnData = 0;
            }
        }
        return 1;
    case MSG_SETQUICKSAND:
        if (work != 0) {
            if (beMessenger_GetInt(MESSENGER, 0) != 0) {
                if (work->_rideOnData == 0) {
                    ALLOCATOR(a, self)
                    ObjRef<3> r((igObject *)beModelCtrlInfoRideOn3_Create(a));
                                        Matrix44_GetTranslation((int)MODEL_NODE->_m, (float *)&quicksandPos);
                    Matrix44_Copy(quicksandMatrix, DAT_004e0ef0);
                    Matrix44_SetTranslation((float *)quicksandMatrix, (void *)&quicksandPos);
                    {
                        ALLOCATOR(b, self)
                        ObjRef<5> r2((igObject *)beModelCtrlNode2_Create(b));
                        ((beModelCtrlNode2Slots *)r2.p)->vfunc_35(quicksandMatrix);
                        node2 = r2.p;
                        held = (beModelCtrlInfoRideOn *)r.p;
                        RETAIN(node2)
                        RELEASE(held->_modelNode)
                        held->_modelNode = (int)node2;
                    }
                    Matrix44_Copy(((beModelCtrlInfoRideOn3 *)r.p)->_oldMatrix, quicksandMatrix);
                    beMessenger_GetVec3(&quicksandCenter, MESSENGER, 0);
                    { beModelCtrlInfoRideOn3 *f3 = (beModelCtrlInfoRideOn3 *)r.p; f3->_worldPosition[0] = quicksandCenter.x; f3->_worldPosition[1] = quicksandCenter.y; f3->_worldPosition[2] = quicksandCenter.z; }
                    ((beModelCtrlInfoRideOn3 *)r.p)->_minKyori = beMessenger_GetFloat(MESSENGER, 0);
                    ((beModelCtrlInfoRideOn3 *)r.p)->_maxKyori = beMessenger_GetFloat(MESSENGER, 1);
                    ((beModelCtrlInfoRideOn3 *)r.p)->_minSpeed = beMessenger_GetFloat(MESSENGER, 2);
                    ((beModelCtrlInfoRideOn3 *)r.p)->_maxSpeed = beMessenger_GetFloat(MESSENGER, 3);
                    {
                        igObject *s = r.p;
                        RETAIN(s)
                        RELEASE(work->_rideOnData)
                        work->_rideOnData = (int)s;
                    }
                }
            } else {
                RELEASE(work->_rideOnData)
                work->_rideOnData = 0;
            }
        }
        return 1;
    case MSG_SETSLIPPEDFLOOR:
        if (work != 0) {
            if (beMessenger_GetInt(MESSENGER, 0) != 0) {
                if (work->_rideOnData == 0) {
                    ALLOCATOR(a, self)
                    ObjRef<4> r((igObject *)beModelCtrlInfoRideOn4_Create(a));
                                        Matrix44_GetTranslation((int)MODEL_NODE->_m, (float *)&floorPos);
                    Matrix44_Copy(floorMatrix, DAT_004e0ef0);
                    Matrix44_SetTranslation((float *)floorMatrix, (void *)&floorPos);
                    {
                        ALLOCATOR(b, self)
                        ObjRef<5> r2((igObject *)beModelCtrlNode2_Create(b));
                        ((beModelCtrlNode2Slots *)r2.p)->vfunc_35(floorMatrix);
                        node2 = r2.p;
                        held = (beModelCtrlInfoRideOn *)r.p;
                        RETAIN(node2)
                        RELEASE(held->_modelNode)
                        held->_modelNode = (int)node2;
                    }
                    Matrix44_Copy(((beModelCtrlInfoRideOn4 *)r.p)->_oldMatrix, floorMatrix);
                    ((int *)&floorPos)[1] = 0;
                    { beModelCtrlInfoRideOn4 *f4 = (beModelCtrlInfoRideOn4 *)r.p; f4->_oldPlayerPos[0] = floorPos.x; f4->_oldPlayerPos[1] = floorPos.y; f4->_oldPlayerPos[2] = floorPos.z; }
                    { beModelCtrlInfoRideOn4 *f4 = (beModelCtrlInfoRideOn4 *)r.p; f4->_vector[0] = g_vec3Zero[0]; f4->_vector[1] = g_vec3Zero[1]; f4->_vector[2] = g_vec3Zero[2]; }
                    ((beModelCtrlInfoRideOn4 *)r.p)->_scalar = beMessenger_GetFloat(MESSENGER, 0);
                    ((beModelCtrlInfoRideOn4 *)r.p)->_limitter = beMessenger_GetFloat(MESSENGER, 1);
                    {
                        igObject *s = r.p;
                        RETAIN(s)
                        RELEASE(work->_rideOnData)
                        work->_rideOnData = (int)s;
                    }
                }
            } else {
                RELEASE(work->_rideOnData)
                work->_rideOnData = 0;
            }
        }
        return 1;
    }
}

#undef ENSURE_DATA_LIST
#undef FIRST_LOD
#undef MODEL_NODE
#undef MESSENGER
#undef INFO_NAME
#undef SET_WORK_STRING
#undef RELEASE_STRING
#undef POOL
#undef ALLOCATOR

/* Slot 45 default: empty. */
void Gap__Core__igObject__vfunc_45(void)
{
}

/* Slot 44 default: empty. */
void Gap__Core__igObject__vfunc_44(void)
{
}

/* Slot 43 default: empty. */
void Gap__Core__igObject__vfunc_43(void)
{
}

/* Slot 41 default: empty. */
void Gap__Core__igObject__vfunc_41(void)
{
}

/* Slot 40 default: empty. */
void Gap__Core__igObject__vfunc_40(void)
{
}

/* Slot 42 default: empty. */
void Gap__Core__igObject__vfunc_42(void)
{
}

/* Slot 47 default: always 0. */
int Gap__Core__igObject__vfunc_47(void) {
    return 0;
}

int Gap__Bec__beModelCtrlInfoRideOn4__vfunc_20(void)
{
    return g_beModelCtrlInfoRideOn4_metaObject[0];
}

int Gap__Bec__beModelCtrlInfoRideOn3__vfunc_20(void)
{
    return g_beModelCtrlInfoRideOn3_metaObject[0];
}

int Gap__Bec__beModelCtrlInfoRideOn2__vfunc_20(void)
{
    return g_beModelCtrlInfoRideOn2_metaObject[0];
}

int Gap__Bec__beModelCtrl__vfunc_20(void)
{
    return g_beModelCtrl_metaObject[0];
}
