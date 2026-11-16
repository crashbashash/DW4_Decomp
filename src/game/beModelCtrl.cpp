#include "dw4/reflected.h"
#include "dw4/igSmartPointer.h"
#include "dw4/igTDataList.h"
#include "dw4/igVec3f.h"
#include "dw4/igTraversalView.h"
#include "dw4/beModelCtrlDispatchView.h"
#include "dw4/igRandomNumberDispatchView.h"
#include "dw4/igTransformDispatchView.h"
#include "dw4/igLodDispatchView.h"
#include "dw4/beTime.h"
#include "dw4/listSet.h"
#include "dw4/beMeterCtrlNode.h"
#include "dw4/beModelCtrl.h"
#include "dw4/beModelCtrlInfoWork.h"
#define SELECT_ALLOCATOR(var, arg) { int base_ = igObject_GetAllocator(arg); if (g_useOwnerAllocator != 0) var = base_; else var = Memory_GetAllocatorBySelector(kIGMemoryPoolHandleUser1[0]); }
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
/* beModelCtrlInfoRideOn2/3/4: slot 21 moves the ride-on model with a matrix.
 * ABI view only: never instantiated. */
class beModelCtrlInfoRideOnDispatchView : public igObjectDispatchView {
public:
    virtual void Move(float *matrix);                                       /* slot 21 */
};
/* The matrix of a transform node held as a plain reference field. */
static inline float *NodeMatrix(int node) { return ((igTransform *)node)->_m; }
extern "C" void igTraversal_RegisterFunction(struct igTraversalFunctionList *table, struct igMetaObject *meta, void *function);
extern "C" int thunk_igAABox_Transform(...);
extern "C" int Memory_GetAllocatorBySelector(...);
extern "C" int igObject_GetAllocator(...);
extern "C" int ObjectList_AppendRetained(...);
extern "C" int igInsightCore_FindManager(...);
extern "C" int beModelCtrl_GetInfoMeta(void);
extern "C" void beModelCtrl_OnWaitCheck(void);
extern "C" void beModelCtrl_OnUpdateRam(void);
extern "C" void beModelCtrl_OnAction1(void);
extern "C" void beModelCtrl_OnSequenceChange(void);
extern "C" void beModelCtrl_OnErase(void);
extern "C" void beModelCtrl_OnFreeze(void);
extern "C" void beModelCtrl_OnControlOff(void);
extern "C" void beModelCtrl_OnRemove(void);
extern "C" int beModelCtrl_OnPreMessage(void);
extern "C" int beBaseInfoManager_AddInfo(...);
extern "C" int beModelCtrl_AddInfo(beModelCtrl *self, beModelCtrlInfo *info);
extern "C" int beMessenger_RegisterReceiverFromInfo(...);
extern "C" void * igProperty_FindByName(...);
extern "C" void beModelCtrl_RegisterReceiver(void);
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
extern "C" int igMatrix44f_Copy(...);
extern "C" void igObject_Destroy(void *);
extern "C" void igMatrix44f_SetTranslation(float *matrix, void *vec3);
extern "C" int beModelCtrlInfoRideOn2_GetMeta(void);
extern "C" float sqrtf(float);
extern "C" int igMatrix44f_GetTranslation(int, float *);
extern "C" void *beModelCtrlInfoRideOn_Create(...);
extern "C" unsigned char beMessenger_GetBool(struct beMessenger *self, int index);
extern "C" int beMessenger_GetBoolCount(...);
extern "C" int beMessenger_GetInt(...);
extern "C" int beMessenger_GetStringCount(...);
extern "C" float beBaseInfoRam_GetTimerFrameDelta(...);
extern "C" int igMatrix44f_TranslateLocal(...);
extern "C" int beBaseInfoRam_HasTimer(...);
extern "C" void *beModelCtrlMoveObject_Create(...);
extern "C" float atan2f(float, float);
extern "C" int Vec3f_TransformDirection(...);
extern "C" void * StringPool_Intern(...);
extern "C" int beMessenger_GetObjectCount(...);
extern "C" int sprintf(...);
extern "C" int beLua__RunNamedChunk(...);
extern "C" int beBaseInfoRam_RemoveTimer(...);

extern "C" int beModelCtrlSubCom_StopType(int, int, igMetaObject *);
extern "C" void beModelCtrl_UpdateMuteki(beModelCtrl *self, beBaseInfoRam *ram, beModelCtrlInfoWork *work);
extern "C" int igMatrix44f_MakeEulerRotation(int, float, float, float);
extern "C" int igMatrix44f_SetIdentity(...);
extern "C" int igMatrix44f_Multiply(...);
extern "C" int igMatrix44f_PreMultiply(...);
extern "C" int igMatrix44f_Invert(...);
extern "C" void beModelCtrl_UpdateKeyCtrl(beModelCtrl *self, beBaseInfo *info, beBaseInfoRam *ram, beModelCtrlInfoWork *work);
extern "C" int beModelCtrlSubCom_Update(...);
extern "C" int beMessenger_AppendString(...);
extern "C" int beMessenger_DispatchSelected(...);
extern "C" int beMessenger_GetMatrix(...);
extern "C" int beMessenger_GetMatrixCount(...);
extern "C" int beMessenger_SelectReceivers(...);
extern "C" int igAABox_Transform(...);
extern "C" bool igAABox_IntersectBox(void *, int);
extern "C" void igMatrix44f_PreRotateAxisAngle(void *, void *, float);
extern "C" int igMatrix44f_SetEulerRotation(void *, float, float, float);
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
extern "C" unsigned beMessenger_ResolveEnumValue(int, igMetaEnum *, const char *);
extern "C" int beModelCtrlInfoRideOn4_GetMeta(void);
extern "C" int beModelCtrlInfoRideOn3_GetMeta(void);
extern "C" igMetaObject *beModelCtrl_GetMeta(void);
extern "C" int beMeterCtrlNode_Traverse(void *node, igCommonTraversal *traversal, void *data);
extern "C" int beMeterCtrlNode_TraversalFunction(igCommonTraversal *traversal, void *node);
extern "C" int g_igCommonTraversal_travProcs[4];
/* A component of a vector by index, read through the vector's address.
 * matching construct: only this inline read gives the generate handler retail's float registers (the degree
 * factor in $f2, x in $f3); .x/.y/.z, igVec3f::operator[] and the same cast written in place exchange the two.
 * operator[] written this way matches here too, but beWaterPlain_UpdateRam needs its (&x)[i] form. */
static inline float Component(const igVec3f &v, int i) { return ((const float *)&v)[i]; }

extern "C" igAABox * igAABox_CreateInstance(...);
extern "C" void igAABox_GetCenter(igAABox *, float *);
extern "C" int g_propertyNameField[4];
extern "C" char HIT[];
extern "C" int kIGMemoryPoolHandleUser1[4];
extern "C" unsigned char g_useOwnerAllocator;
extern "C" igAABoxList *beModelCtrlInfoHitBody_GetAABoxList(beModelCtrlInfoHitBody *body, beBaseInfoRam *ram, int matrix, long long time);
extern "C" int g_beTargetObj_metaObject[4];
extern "C" int g_beLua_metaObject[4];
extern "C" void beModelCtrl_Prepare(beModelCtrl *self);
extern "C" int g_beModelCtrlInfo_metaObject[4];
extern "C" char MODELCTRL_7[];
extern "C" char HITPLAYERBULLET_2[];
extern "C" char HITPLAYERTALK_2[];
extern "C" char HITENEMYBULLET_2[];
extern "C" void beModelCtrl_OnAddRam(beModelCtrl *self, beBaseInfoRam *ram);
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

extern "C" void beModelCtrl_UpdateHomingAI(beModelCtrl *self, beModelCtrlInfo *info, beBaseInfoRam *ram, beModelCtrlInfoWork *work, beModelCtrlInfoDataAIH *homing);
extern "C" char AIM[];
extern "C" char AIH[];
extern "C" char KIND_EBULLET_2[];
extern "C" char ENEMY_4[];
extern "C" igVec3f *beTargetObj_GetOrigin(void);
extern "C" igVec3f *beTargetObj_GetTargetPosition(void);
extern "C" void beModelCtrl_UpdateControl(beModelCtrl *self, beBaseInfoRam *ram);
extern "C" char ACTION_2[];
extern "C" int beModelCtrl_RunAction(beModelCtrl *self, beModelCtrlInfo *info, beBaseInfoRam *ram, beModelCtrlACTION *command);
extern "C" igObject * beMessenger_GetObject(...);
extern "C" char GETMATRIX_2[];
extern "C" void beModelCtrlInfoRideOn_SetModel(beModelCtrlInfoRideOn *self, int modelName, int ramNo, int messenger);
extern "C" int beModelCtrlInfoRideOn_IsModel(beModelCtrlInfoRideOn *self, int modelName, int ramNo);
extern "C" int g_beModelCtrlInfoRideOn2_metaObject[4];
extern "C" void beModelCtrlInfoRideOn2_Move(beModelCtrlInfoRideOn2 *self);
extern "C" float g_vec3Zero[4];
extern "C" void beModelCtrlInfoRideOn3_Move(beModelCtrlInfoRideOn3 *self, void *m);
extern "C" void beModelCtrlInfoRideOn4_Move(beModelCtrlInfoRideOn4 *self, void *m);
extern "C" void Vec3_Lerp(void *out, float t, void *from, void *to);
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
extern "C" igMetaObject *g_beModelCtrlMOVEEX_metaObject;
extern "C" igMetaObject *g_beModelCtrlMOVE_metaObject;

struct MoveRef {
    igObject *p;
    MoveRef() { p = 0; }
    ~MoveRef() { igObject *o = p; if (o != 0) { o->_refCount = o->_refCount - 1; if ((o->_refCount & 0x7fffff) == 0) igObject_Destroy(o); } }
};

/* matching construct: the data-list holder (slot 152) must sit below the move-object holder (slot 156), so it is
 * a local of a static inline member (allocated after the caller's); al/p/old stay the caller's locals. Assigned
 * through igSmartPointer::operator= instead, beModelCtrl_RunMove's registers differ. */
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
extern "C" char BHit_2[];
extern "C" int beModelCtrl_RunLuaCall(beModelCtrl *self, beBaseInfo *info, beBaseInfoRam *ram, beModelCtrlInfoWork *work, beModelCtrlLUACALL *command);
extern "C" char aim[];
extern "C" char WPos[];
extern "C" igVec3f *g_mdlWorldPosTarget[4];
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
extern "C" igMetaObject *g_beModelCtrlSCHitBox_metaObject[4];
extern "C" int beModelCtrl_RunHitBox(beModelCtrl *self, beBaseInfoRam *ram, beModelCtrlInfoWork *work, beModelCtrlHITBOX *command);
extern "C" char OFFWALL[];
extern "C" char ONWALL[];
extern "C" char OFFFLOOR[];
extern "C" char ONFLOOR[];
struct MutekiNameOf { static int *Get(beModelCtrlMUTEKI *m) { if (m->_name != 0) { return (int *)m->_name; } return &emptyString[0]; } };
extern "C" int beModelCtrl_RunMuteki(beModelCtrl *self, beBaseInfoRam *ram, beModelCtrlInfoWork *work, beModelCtrlMUTEKI *command);
extern "C" igMetaObject *g_beModelCtrlCTRL_metaObject;
extern "C" igMetaObject *g_beModelCtrlACTION_metaObject;
extern "C" igMetaObject *g_beModelCtrlMOVERL_metaObject;
extern "C" igMetaObject *g_beModelCtrlPDMOVE_metaObject;
extern "C" igMetaObject *g_beModelCtrlWCHECK_metaObject;
extern "C" igMetaObject *g_beModelCtrlHITBOX_metaObject;
extern "C" igMetaObject *g_beModelCtrlMUTEKI_metaObject;
extern "C" igMetaObject *g_beModelCtrlLABELCTRL_metaObject;
extern "C" igMetaObject *g_beModelCtrlLUACALL_metaObject;
extern "C" igMetaObject *g_beModelCtrlAIMAP_metaObject;
extern "C" igMetaObject *g_beModelCtrlMSGBOX_metaObject;
extern "C" igMetaObject *g_beModelCtrlLABEL_metaObject;
extern "C" igMetaObject *g_beModelCtrlJUMP_metaObject;

extern "C" void beModelCtrl_UpdateDirection(beModelCtrl *self, beBaseInfo *info, beBaseInfoRam *ram, beModelCtrlInfoWork *work, int force);
extern "C" char SQ_NONE[];
extern "C" char SQ_ERAS_2[];
extern "C" char REMOVE_2[];
extern "C" char GETBONEMATRIX[];
extern "C" void * g_igTransformRecorder_mMetaField[4];
extern "C" void beModelCtrl_UpdateRam(beModelCtrl *self, beBaseInfoRam *ram);
extern "C" int igStringRefList_IndexOf(int list, StringRef *key, int);
extern "C" StringRef StringList_CopyRetained(int list, int index);
extern "C" int beModelCtrlInfoWork_FindSeqLabel(beModelCtrl *self, beModelCtrlInfoWork *work);
extern "C" void beModelCtrl_UpdateBound(beModelCtrl *self, beModelCtrlNode2 *node, igAABox *box);
extern "C" beModelCtrlNode2 *beModelCtrlNode2_Create(int);
extern "C" beModelCtrlInfoRideOn4 *beModelCtrlInfoRideOn4_Create(int);
extern "C" beModelCtrlInfoRideOn3 *beModelCtrlInfoRideOn3_Create(int);
extern "C" beModelCtrlInfoRideOn2 *beModelCtrlInfoRideOn2_Create(int);
extern "C" beModelCtrlInfoAI *beModelCtrlInfoAI_Create(int);
extern "C" beModelCtrlInfoHitBody *beModelCtrlInfoHitBody_Create(int);
extern "C" void beModelCtrlSubCom_StopAll(int, beBaseInfoRam *);
extern "C" void beModelCtrlSubCom_AddEffect(beModelCtrlSubCom *self, const char *modelName, const char *seqName, float startFrame, const igVec3f &offset, igVec3f rotation, unsigned char isSeqDead, unsigned char isPositionLock);
/* The work's sub-command list (effects, sounds, hit boxes started by commands). */
static inline beModelCtrlSubCom *SubCommands(beModelCtrlInfoWork *work) { return (beModelCtrlSubCom *)work->_subCommand; }
extern "C" void beBaseInfoRam_SetAllTimerScales(beBaseInfoRam *, float);
extern "C" void beBaseInfoRam_RemoveAllTimers(beBaseInfoRam *);
extern "C" void igMatrix44f_FromTranslation(void *, igVec3f *);
extern "C" igVec3f beMessenger_GetVec3(int messenger, int index);
extern "C" float g_matrix44Identity[4];
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
extern "C" igMetaObject *g_igLod_metaObject;

/* Owning stack references to the objects this handler creates before binding them: kind 0 the AI
 * info, 1 the hit-body info, 2..4 the ride-on infos of commands 25..27 and 5 their model node. */
template <int kind> struct ObjRef {
    igObject *p;
    ObjRef(igObject *q) : p(q) {}
    ~ObjRef() { igObject *x = p; if (x) { --x->_refCount; if ((x->_refCount & 0x7fffff) == 0) igObject_Destroy(x); } }
};

/* Creates the ram's data list on first use.
 * matching construct: the handler's ride-on local doubles as the list's holder; a local of its own, or an
 * assignment through igSmartPointer::operator=, moves registers */
struct DataList {
    static inline void Ensure(beBaseInfoRam *ram, beModelCtrlInfoRideOn *&held) {
        if (ram->_dataList == 0) {
            int a = igObject_GetAllocator(ram);
            a = g_useOwnerAllocator ? a : Memory_GetAllocatorBySelector(kIGMemoryPoolHandleUser1[0]);
            igSmartPointer<igObject> r((igObject *)((beBaseInfoDataList *)beBaseInfoDataList_Create(a)));
            held = (beModelCtrlInfoRideOn *)r.p;
            RETAIN(held)
            RELEASE(ram->_dataList)
            ram->_dataList = (int)held;
        }
    }
};
extern "C" int beModelCtrl_OnMessageText(beModelCtrl *self, beBaseInfoRam *ram, const char *message);
extern "C" int g_beModelCtrlInfoRideOn4_metaObject[4];
extern "C" int g_beModelCtrlInfoRideOn3_metaObject[4];

extern "C" int igTraversal_TraverseChildren(igCommonTraversal *traversal, void *node);
extern "C" int igTraversal_TraverseNode(igCommonTraversal *traversal, void *node);
extern "C" igMetaObject *g_igModelViewMatrixAttr_metaObject[4];

/* Pops the attribute pushed for a subtree and the traversal time, and passes the subtree's result on. */
static inline int PopSubtree(igCommonTraversal *traversal, igAttrStackManager *attrs, int index, const int result) {
    PopAttr(attrs, index);
    ((igCommonTraversalDispatchView *)traversal)->popTime();
    return result;
}

int beMeterCtrlNode_TraversalFunction(igCommonTraversal *traversal, void *node)
{
    return beMeterCtrlNode_Traverse(node, traversal, node);
}

/* Meter nodes run their children once per entry of the time list, each time with the matrix
 * translated by the node's number offset; a plain node pushes the first time only. */
int beMeterCtrlNode_Traverse(void *node, igCommonTraversal *traversal, void *data)
{
    beMeterCtrlNode *meter = (beMeterCtrlNode *)node;
    igTimeAttr *clock;
    int depth;
    igObjectList *times;
    short *timeAttrIndex;
    short *matrixAttrIndex;
    float modelView[16];
    igTDataList<igAttr *> *stack;
    igAttrStack *matrices;
    long long time;
    igVec3f translation;
    int slot;
    int result;
    igAttrStackManager *attrs;
    igModelViewMatrixAttrDispatchView *matrixAttr;
    int attrId;
    void *firstChild;
    int index;
    igObjectPool *timePool;
    igTimeAttr *timeAttr;
    igAttr *pushed;
    int count;
    int i;
    short *timeUnitID;
    short *matrixUnitID;

    attrs = (igAttrStackManager *)traversal->_attrStack;
    attrId = g_igModelViewMatrixAttr_metaObject[0]->_id;
    matrices = ((igAttrStack **)((igObjectList *)attrs->_attrStacks)->_data)[((int *)attrs->_attrStackIndexTable)[attrId]];
    result = 0;
    if (meter->_isMeter) {
        times = (igObjectList *)meter->_timeList;
        if (times->_count != 0) {
            time = ((long long *)times->_data)[0];
            timePool = (igObjectPool *)traversal->_timePool;
            if (timePool->_freeIndex >= timePool->_count) {
                igObjectPool_Grow(timePool, (void *)&igTimeAttr_CreateInstance);
            }
            slot = timePool->_freeIndex;
            timePool->_freeIndex = slot + 1;
            timeAttr = ((igTimeAttr **)timePool->_data)[slot];
            timeAttr->_time = time;
            ((igCommonTraversalDispatchView *)traversal)->pushTime(time);
            timeAttrIndex = &timeAttr->_cachedAttrIndex;
            timeUnitID = &timeAttr->_cachedUnitID;
            index = *timeUnitID + ((int *)attrs->_attrStackIndexTable)[*timeAttrIndex];
            stack = ((igTDataList<igAttr *> **)((igObjectList *)attrs->_attrStacks)->_data)[index];
            pushed = (igAttr *)timeAttr;
            stack->append(pushed);
            igAttrStackManager_MarkStackChanged(attrs, (igAttrStack *)stack, index);
            result = PopSubtree(traversal, attrs, *timeUnitID + ((int *)attrs->_attrStackIndexTable)[*timeAttrIndex], igTraversal_TraverseChildren(traversal, node));
        }
    } else {
        firstChild = ((void **)((igObjectList *)((beMeterCtrlNode *)data)->_childList)->_data)[0];
        igMatrix44f_SetIdentity(modelView);
        matrixAttr = (igModelViewMatrixAttrDispatchView *)TakePooled((igObjectPool *)traversal->_matrixPool, (void *)&igModelViewMatrixAttr_CreateInstance);
        depth = matrices->_count - 1;
        igMatrix44f_Copy(modelView, (char *)((void **)matrices->_data)[depth] + 12);
        igMatrix44f_GetTranslation((int)modelView, (float *)&translation);
        clock = (igTimeAttr *)TakePooled((igObjectPool *)traversal->_timePool, (void *)&igTimeAttr_CreateInstance);
        count = ((igObjectList *)meter->_timeList)->_count;
        for (i = 0; i < count; i++) {
            time = ((long long *)((igObjectList *)meter->_timeList)->_data)[i];
            if (i != 0) {
                /* matching construct: IR dump — read through the float view, x stays an assignment where the front end
                 * makes y and z compound `+=` updates; as `translation.x` the x load moves behind the offset's */
                translation.x = ((float *)&translation)[0] + meter->_numberOffset[0];
                translation.y = translation.y + meter->_numberOffset[1];
                translation.z = translation.z + meter->_numberOffset[2];
            }
            igMatrix44f_SetTranslation(modelView, &translation);
            matrixAttr->setMatrix(modelView);
            clock->_time = time;
            ((igCommonTraversalDispatchView *)traversal)->pushTime(time);
            matrixAttrIndex = &((igAttr *)matrixAttr)->_cachedAttrIndex;
            matrixUnitID = &((igAttr *)matrixAttr)->_cachedUnitID;
            index = *matrixUnitID + ((int *)attrs->_attrStackIndexTable)[*matrixAttrIndex];
            stack = ((igTDataList<igAttr *> **)((igObjectList *)attrs->_attrStacks)->_data)[index];
            pushed = (igAttr *)matrixAttr;
            stack->append(pushed);
            igAttrStackManager_MarkStackChanged(attrs, (igAttrStack *)stack, index);
            /* the digit's own traversal result is dropped, so a prune or abort below a digit never stops the walk */
            igTraversal_TraverseNode(traversal, firstChild);
            result = PopSubtree(traversal, attrs, *matrixUnitID + ((int *)attrs->_attrStackIndexTable)[*matrixAttrIndex], result);
            if (result == 1) {
                result = 0;
                break;
            }
            if (result == 2) break;
        }
    }
    if (result == 2) {
        return 2;
    }
    return 0;
}

void beMeterCtrlNode_RegisterTraversalFunction(void) {
    igTraversal_RegisterFunction((igTraversalFunctionList *)g_igCommonTraversal_travProcs[0], (igMetaObject *)beMeterCtrlNode_ResolveMetaObject(), (void *)beMeterCtrlNode_TraversalFunction);
}

void beModelCtrl_DrawDebugHitBox(beModelCtrl *self, igNode *node, igAABox *box, float *color)
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
            igAABox_GetCenter(box, (float *)center);
            j = 0;
            {
                float *pCenter = center, *pBelow = below, *pAbove = above; igAABox *pBox = box;
                for (; j < 3; j++) {
                    float d = *(float *)&pCenter[0] - pBox->_min[0];
                    *pBelow = d < 0.0f ? -d : d;
                    d = pBox->_max[0] - *pCenter;
                    *pAbove = d < 0.0f ? -d : d;
                    pBox = (igAABox *)((float *)pBox + 1); pCenter++; pBelow++; pAbove++;
                }
            }
            {
                int k;
                igDataList *list = (igDataList *)body->_AABoxMinList;
                k = list->_count;
                if (k < list->_capacity) list->_count = k + 1; else List_Resize(list, k + 1, 12);
                igVec3f *extent = &((igVec3f *)list->_data)[k];
                extent->x = below[0]; extent->y = below[1]; extent->z = below[2];
            }
            {
                int k;
                igDataList *list = (igDataList *)body->_AABoxMaxList;
                k = list->_count;
                if (k < list->_capacity) list->_count = k + 1; else List_Resize(list, k + 1, 12);
                igVec3f *extent = &((igVec3f *)list->_data)[k];
                extent->x = above[0]; extent->y = above[1]; extent->z = above[2];
            }
            {
                int alloc = igObject_GetAllocator(body);
                int a;
                if (g_useOwnerAllocator != 0) a = alloc; else a = Memory_GetAllocatorBySelector(kIGMemoryPoolHandleUser1[0]);
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
            *(igVec3f *)below = ((igVec3f *)((igDataList *)body->_AABoxMinList)->_data)[i];
            *(igVec3f *)above = ((igVec3f *)((igDataList *)body->_AABoxMaxList)->_data)[i];
            for (k = 0; k < 3; k++) { float *a = &dst->_min[k]; float *box = &dst->_max[k]; *a = center[k] - below[k]; *box = center[k] + above[k]; }
        }
    }
    return (igAABoxList *)body->_AABoxList;
}

void beModelCtrl_Prepare(beModelCtrl *self) {
    if (self->_luaManager == 0) {
        self->_luaManager = igInsightCore_FindManager(self->_insight, g_beLua_metaObject[0]);
    }
    if (self->_targetObj == 0) {
        self->_targetObj = igInsightCore_FindManager(self->_insight, g_beTargetObj_metaObject[0]);
    }
}

/* Slot 30 default: first word of the beModelCtrlInfo MetaObject record. */
int beModelCtrl_GetInfoMeta(void)
{
    return g_beModelCtrlInfo_metaObject[0];
}

int beModelCtrl_AddInfo(beModelCtrl *self, beModelCtrlInfo *info) {
    igMetaObject *infoMeta;

    infoMeta = ((beModelCtrlDispatchView *)self)->GetInfoMeta();
    if ((infoMeta == ((igObjectDispatchView *)info)->GetMeta()) && ((((beModelCtrlDispatchView *)self)->IsKind((const char *)info->_kindString) & 0xFF) == 1)) {
        beBaseInfoManager_AddInfo(self, info);
        return 1;
    }
    return 0;
}

void beModelCtrl_OnAddRam(beModelCtrl *self, beBaseInfoRam *ram) {
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
    ((beModelCtrlDispatchView *)self)->RegisterReceiver(ram);
}

void beModelCtrl_RegisterReceiver(void)
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
        pool = (g_useOwnerAllocator != 0) ? pool : Memory_GetAllocatorBySelector(kIGMemoryPoolHandleUser1[0]);
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
            if ((beTargetObj_SetTarget(NodeMatrix(ramData->_node), pos) & 0xff) == 0) {
                return;
            }
        } else {
            if ((beTargetObj_SelectTarget(NodeMatrix(ramData->_node), PLAYER_3, (char *)map->_targetType) & 0xff) == 0) {
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
        roll = ((igRandomNumberDispatchView *)((beSystem *)self->_system)->_random)->genrand() & 0xf;
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
        beBaseInfoRam_StartTimer(ram, AITIMER, FramesToTime(zone->_time));
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

/* The length of `frames` 60 Hz frames in the insight clock's nanoseconds. */

/* Turns the model towards the target while its homing timers run: pitch from the height difference
 * and the distance, yaw from the horizontal offset. */
void beModelCtrl_UpdateHomingAI(beModelCtrl *self, beModelCtrlInfo *info, beBaseInfoRam *ram, beModelCtrlInfoWork *work, beModelCtrlInfoDataAIH *homing) {
    beModelCtrlInfoRamData *ramData;
    igVec3f *origin;
    int allocator;
    unsigned char turnX;
    igVec3f *target;
    unsigned char turnY;
    beModelCtrlInfoAI *ai;
    float distanceSq;
    float originX, originY, originZ;
    float targetX, targetY, targetZ;
    if (ram->_dataList == 0) {
        allocator = igObject_GetAllocator(ram);
        allocator = (g_useOwnerAllocator != 0) ? allocator : Memory_GetAllocatorBySelector(kIGMemoryPoolHandleUser1[0]);
        DataListInstall::make(ram, allocator);
    }
    ramData = ((beModelCtrlInfoRamData *)igProperty_FindByName((igObject *)ram->_dataList, g_propertyNameField[0], ONE_3));
    ai = (beModelCtrlInfoAI *)work->_aI;
    turnX = 1;
    turnY = 0;
    switch (ai->_hStatus) {
    case 0:
        beBaseInfoRam_StartTimer(ram, AITIMER, FramesToTime(homing->_firstFrame));
        ai->_hStatus = 1;
    case 1:
        if ((beBaseInfoRam_IsTimerExpired(ram, AITIMER) & 0xff) != 0) {
            turnY = 1;
            ai->_hStatus = 2;
        }
        break;
    case 2:
        beBaseInfoRam_StartTimer(ram, AITIMER, FramesToTime(homing->_secondFrame));
        ai->_hStatus = 3;
    case 3:
        if ((beBaseInfoRam_IsTimerExpired(ram, AITIMER) & 0xff) != 0) {
            turnY = 1;
            ai->_hStatus = 2;
        }
        break;
    case 4:
        turnX = 0;
        break;
    }
    if ((turnX && homing->_isXHoming) || (turnY && homing->_isYHoming)) {
        if (turnY) {
            ai->_hCount = ai->_hCount + 1;
            if (homing->_limitCount <= ai->_hCount) {
                ai->_hStatus = 4;
            }
        }
        if (strcmp((char *)info->_kindString, KIND_EBULLET_2) == 0) {
            if ((beTargetObj_SelectTarget(NodeMatrix(ramData->_node), PLAYER_3, NEAR) & 0xff) == 0) {
                return;
            }
        } else {
            if ((beTargetObj_SelectTarget(NodeMatrix(ramData->_node), ENEMY_4, NEAR) & 0xff) == 0) {
                return;
            }
        }
        distanceSq = beTargetObj_GetTargetDistanceSq();
        if (distanceSq <= homing->_areaSquare) {
            origin = beTargetObj_GetOrigin();
            originX = origin->x;
            originY = origin->y;
            originZ = origin->z;
            target = beTargetObj_GetTargetPosition();
            targetX = target->x;
            targetY = target->y;
            targetZ = target->z;
            if (turnX && homing->_isXHoming) {
                work->_directionLimiter[0] = homing->_limitRotX;
                work->_targetDirection[0] = -atan2f(targetY + work->_aIHOffsetY - originY, sqrtf(distanceSq));
            }
            if (turnY && homing->_isYHoming) {
                work->_directionLimiter[1] = homing->_limitRotY;
                work->_targetDirection[1] = atan2f(targetX - originX, targetZ - originZ);
            }
            beModelCtrl_UpdateDirection(self, (beBaseInfo *)info, ram, work, 0);
            work->_targetDirection[1] = work->_direction[1];
        }
    }
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

void beModelCtrl_UpdateControl(beModelCtrl *self, beBaseInfoRam *ram) {
    beBaseInfo *info;
    int work;
    beBaseInfoData *property;
    int allocator;
    igObject *list;
    igObject *old;
    info = (beBaseInfo *)ram->_parentInfo;
    if (ram->_dataList == 0) {
        allocator = igObject_GetAllocator(ram);
        allocator = (g_useOwnerAllocator != 0) ? allocator : Memory_GetAllocatorBySelector(kIGMemoryPoolHandleUser1[0]);
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
            beModelCtrl_UpdateHomingAI(self, (beModelCtrlInfo *)info, ram, (beModelCtrlInfoWork *)work, (beModelCtrlInfoDataAIH *)property);
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
    if (work->_isOnCtrl != 0) ((beModelCtrlDispatchView *)self)->UpdateControl(ram);
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
        ((beModelCtrlDispatchView *)self)->OnMessageText(ram, (const char *)work->_keyEventName);
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
    igMatrix44f_Copy(matrix, NodeMatrix((int)node));
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
    igMatrix44f_Copy(&self->_oldMatrix, matrix);
}

int beModelCtrlInfoRideOn_IsModel(beModelCtrlInfoRideOn *self, int modelName, int ramNo) {
    if (strcmp(self->_modelName, modelName) != 0) return 0;
    if (ramNo == self->_modelRamNo) return 1;
    return 0;
}

/* Resets the ride-on pose: clears the translation of `_oldMatrix` to (0,0,0) and writes `_vector`
 * into the translation of the model node's matrix (+0x20 of a node, the igTransform `_m` offset).
 * igMatrix44f_SetTranslation copies vec3 into matrix words 12..14. */
void beModelCtrlInfoRideOn2_Move(beModelCtrlInfoRideOn2 *self) {
    igMatrix44f_SetTranslation(self->_oldMatrix, &g_vec3Zero[0]);
    igMatrix44f_SetTranslation(NodeMatrix(self->_modelNode), self->_vector);
}

void beModelCtrlInfoRideOn3_Move(beModelCtrlInfoRideOn3 *self, void *m) {
    igVec3f t;
    igVec3f d;
    float e, x, g, k, b, z, len, inv, y, c, a;
    igMatrix44f_SetTranslation((float *)((char *)self->_oldMatrix), g_vec3Zero);
    igMatrix44f_GetTranslation((int)m, (float *)&t);
    d.x = ((igVec3f *)self->_worldPosition)->x;
    d.y = ((igVec3f *)self->_worldPosition)->y;
    d.z = ((igVec3f *)self->_worldPosition)->z;
    d.x = d.x - t.x;
    d.y = d.y - t.y;
    d.z = d.z - t.z;
    y = ((igVec3f *)&d)->y; x = d.x; z = ((igVec3f *)&d)->z;
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
    igMatrix44f_SetTranslation(NodeMatrix(self->_modelNode), &d);
}

/* Moves the ride-on with its rider. `m` is the rider's matrix and `delta` its horizontal offset from
 * `_oldPlayerPos`. The first call clears the model node's offset; the second stores `delta`, cut to at
 * most 0.6 long, as `_vector`; every later call lerps `_vector` towards `delta` by `_scalar`, snaps the
 * step to zero when its x and z both lie within `_limitter`, moves the model node by it and puts the
 * rider back over `_oldPlayerPos` at its own height. */
void beModelCtrlInfoRideOn4_Move(beModelCtrlInfoRideOn4 *self, void *m) {
    igVec3f player;
    igVec3f last;
    igVec3f delta;
    igVec3f step;
    float height;
    igMatrix44f_SetTranslation(self->_oldMatrix, g_vec3Zero);
    igMatrix44f_GetTranslation((int)m, (float *)&player);
    height = (&player.x)[1];
    (&player.x)[1] = 0;
    last.x = self->_oldPlayerPos[0];
    (&last.x)[1] = self->_oldPlayerPos[1];
    (&last.x)[2] = self->_oldPlayerPos[2];
    (&last.x)[1] = 0;
    delta.x = player.x - last.x;
    delta.y = player.y - last.y;
    delta.z = player.z - last.z;
    switch (self->_isFirst) {
    case 0:
        igMatrix44f_SetTranslation(NodeMatrix(self->_modelNode), g_vec3Zero);
        self->_isFirst = 1;
        break;
    case 1: {
        float lengthSq;
        delta.y = 0;
        /* matching construct: post-allocation peephole trace — y read by index, not as delta.y, keeps it a copy of the stored zero */
        lengthSq = delta.x * delta.x + delta[1] * delta[1] + delta.z * delta.z;
        if (!(lengthSq < 0.6f * 0.6f)) {
            float inverse = 1.0f / sqrtf(lengthSq);
            delta.x = delta.x * inverse;
            delta.y = delta.y * inverse;
            delta.z = delta.z * inverse;
            delta.x = delta.x * 0.6f;
            delta.y = delta.y * 0.6f;
            delta.z = delta.z * 0.6f;
        }
        self->_vector[0] = delta.x;
        self->_vector[1] = delta[1];
        self->_vector[2] = delta.z;
        igMatrix44f_SetTranslation(NodeMatrix(self->_modelNode), g_vec3Zero);
        self->_isFirst = 2;
        break;
    }
    default: {
        int i;
        igVec3f zero;
        Vec3_Lerp(&step, self->_scalar, self->_vector, &delta);
        zero.x = g_vec3Zero[0];
        zero.y = g_vec3Zero[1];
        zero.z = g_vec3Zero[2];
        for (i = 0; i < 3; i++) {
            if (i == 1) {
                (&step.x)[i] = 0;
            }
            if (!((&step.x)[i] <= self->_limitter)) break;
            if ((&step.x)[i] < -self->_limitter) break;
            if (i == 2) {
                step = zero;
            }
        }
        *(igVec3f *)self->_vector = step;
        igMatrix44f_SetTranslation(NodeMatrix(self->_modelNode), &step);
        step.x = step.x + last.x;
        step.y = step.y + last.y;
        step.z = step.z + last.z;
        last.y = height;
        igMatrix44f_SetTranslation((float *)m, &last);
        break;
    }
    }
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
        if (work->_luaWHit != 0 && beMessenger_GetBool((beMessenger *)self->_messenger, 1)) {
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
        landed = beMessenger_GetBool((beMessenger *)self->_messenger, 0);
        floorHit = beMessenger_GetBool((beMessenger *)self->_messenger, 1);
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
                ((beModelCtrlDispatchView *)self)->OnMessageText(ram, SQ_FALL);
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
                    if (g_useOwnerAllocator != 0) allocator = base; else allocator = Memory_GetAllocatorBySelector(kIGMemoryPoolHandleUser1[0]);
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
    float matrix[16];
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
                allocator = g_useOwnerAllocator ? allocator : Memory_GetAllocatorBySelector(kIGMemoryPoolHandleUser1[0]);
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
            igMatrix44f_Copy(matrix, NodeMatrix(ramData->_node));
            step[0] = beModelCtrlMoveObject_Step(MoveObjects(work)[0], frames);
            step[1] = beModelCtrlMoveObject_Step(MoveObjects(work)[1], frames);
            step[2] = beModelCtrlMoveObject_Step(MoveObjects(work)[2], frames);
            igMatrix44f_TranslateLocal(matrix, step);
            ((igTransformDispatchView *)ramData->_node)->SetMatrix(matrix);
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
    igMetaObject *meta;
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
        Vec3f_TransformDirection(&forward[0], &g_vec3ZAxis[0], NodeMatrix(((beModelCtrlInfoRamData *)igProperty_FindByName((igObject *)ram->_dataList, g_propertyNameField[0], ONE_3))->_node));
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
    meta = g_beModelCtrlMOVE_metaObject;
    if (meta == ((igObjectDispatchView *)command)->GetMeta()) {
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
        meta = g_beModelCtrlMOVEEX_metaObject;
        if (meta == ((igObjectDispatchView *)command)->GetMeta()) {
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
            ListStoreAt(list->_data, k, 0.0f);
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
extern "C" int StringList_AppendRetained(igStringRefList *, StringRef *);
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
            allocator = Memory_GetAllocatorBySelector(kIGMemoryPoolHandleUser1[0]);
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
            allocator = Memory_GetAllocatorBySelector(kIGMemoryPoolHandleUser1[0]);
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
            allocator = Memory_GetAllocatorBySelector(kIGMemoryPoolHandleUser1[0]);
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
        idx = igStringRefList_IndexOf((int)seqList, &key, 0);
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
            ListStoreAt((int *)offsetList->_data, idx, -1);
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
            StringList_AppendRetained(seqList, &newSeq);
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
            StringList_AppendRetained(labelList, &newLabel);
        }
        k = intListCount(offsetList);
        if (k < offsetList->_capacity) {
            offsetList->_count = offsetList->_count + 1;
        } else {
            List_Resize(offsetList, k + 1, 4);
        }
        ListStoreAt((int *)offsetList->_data, k, -1);
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
            allocator = Memory_GetAllocatorBySelector(kIGMemoryPoolHandleUser1[0]);
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
    g_mdlMatrix[0] = (int)NodeMatrix(ramData->_node);
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
    igVec3f target;
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
    ((beModelCtrlDispatchView *)self)->OnMessageText(ram, (const char *)sequence);
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
        if (beMessenger_GetBool((beMessenger *)self->_messenger, 0)) {
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
        ((beModelCtrlDispatchView *)self)->OnWaitCheck(ram);
    }
}

#undef END_WAIT

/* Slot 39 default: empty. */
void beModelCtrl_OnWaitCheck(void)
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
    igObjectDispatchView *command;
    jumped = 0;
    commands = (beModelCtrlData *)work->_comData;
    index = work->_comIndex;
    if (index != ((igObjectList *)commands->_comList)->_count) {
        do {
            next = 1;
            command = ((igObjectDispatchView **)((igObjectList *)commands->_comList)->_data)[index];
            if (g_beModelCtrlCTRL_metaObject == command->GetMeta()) {
                next = ((unsigned char)beModelCtrl_RunCtrl(self, work, (beModelCtrlCTRL *)command));
                index += 1;
            } else if (g_beModelCtrlACTION_metaObject == command->GetMeta()) {
                next = ((unsigned char)beModelCtrl_RunAction(self, info, ram, (beModelCtrlACTION *)command));
                index += 1;
            } else if (g_beModelCtrlMOVE_metaObject == command->GetMeta()) {
                next = beModelCtrl_RunMove(self, ram, work, (igObject *)command);
                index += 1;
            } else if (g_beModelCtrlMOVEEX_metaObject == command->GetMeta()) {
                next = beModelCtrl_RunMove(self, ram, work, (igObject *)command);
                index += 1;
            } else if (g_beModelCtrlMOVERL_metaObject == command->GetMeta()) {
                next = beModelCtrl_RunMove(self, ram, work, (igObject *)command);
                index += 1;
            } else if (g_beModelCtrlPDMOVE_metaObject == command->GetMeta()) {
                next = ((unsigned char)beModelCtrl_RunPdMove(self, ram, work, (beModelCtrlPDMOVE *)command));
                index += 1;
            } else if (g_beModelCtrlWCHECK_metaObject == command->GetMeta()) {
                next = ((unsigned char)beModelCtrl_StartWaitCheck(self, work, (beModelCtrlWCHECK *)command));
                index += 1;
            } else if (g_beModelCtrlHITBOX_metaObject == command->GetMeta()) {
                next = ((unsigned char)beModelCtrl_RunHitBox(self, ram, work, (beModelCtrlHITBOX *)command));
                index += 1;
            } else if (g_beModelCtrlMUTEKI_metaObject == command->GetMeta()) {
                next = ((unsigned char)beModelCtrl_RunMuteki(self, ram, work, (beModelCtrlMUTEKI *)command));
                index += 1;
            } else if (g_beModelCtrlLABELCTRL_metaObject == command->GetMeta()) {
                next = ((unsigned char)beModelCtrl_RunLabelCtrl(self, ram, work, (beModelCtrlLABELCTRL *)command));
                index += 1;
            } else if (g_beModelCtrlLUACALL_metaObject == command->GetMeta()) {
                next = ((unsigned char)beModelCtrl_RunLuaCall(self, (beBaseInfo *)info, ram, work, (beModelCtrlLUACALL *)command));
                index += 1;
            } else if (g_beModelCtrlAIMAP_metaObject == command->GetMeta()) {
                next = ((unsigned char)beModelCtrl_RunAiMap(self, info, ram, work, (beModelCtrlAIMAP *)command));
                index += 1;
            } else if (g_beModelCtrlMSGBOX_metaObject == command->GetMeta()) {
                next = beModelCtrl_RunMsgBox(self, info, work, (beModelCtrlMSGBOX *)command);
                index += 1;
            } else if (g_beModelCtrlLABEL_metaObject == command->GetMeta()) {
                if (work->_comLabelCount != 0) {
                    next = 0;
                } else {
                    work->_comLabelCount = 1;
                    index += 1;
                }
            } else if (g_beModelCtrlJUMP_metaObject == command->GetMeta()) {
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
    igVec3f rotation;
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
        if (g_useOwnerAllocator != 0) allocator = base; else allocator = Memory_GetAllocatorBySelector(kIGMemoryPoolHandleUser1[0]);
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
    matrix = (int)NodeMatrix(((beModelCtrlInfoRamData *)igProperty_FindByName(((igObject *)ram->_dataList), g_propertyNameField[0], ONE_3))->_node);
    igMatrix44f_GetTranslation(matrix, translation);
    igMatrix44f_MakeEulerRotation(matrix, rotation.x, ((float*)&rotation)[1], ((float*)&rotation)[2]);
    igMatrix44f_SetTranslation((float *)matrix, (void *)translation);
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

void beModelCtrl_UpdateRam(beModelCtrl *self, beBaseInfoRam *ram) {
    int inverted;
    float oldPos[3];
    float newPos[3];
    float delta[3];
    float pos[3];
    float lockMatrix[16];
    int boneMatrix[16];
    float modelMatrix[16];
    int oldRotation[16];
    int offset[16];
    int local[16];
    float world[16];
    beBaseInfo *info = (beBaseInfo *)ram->_parentInfo;
    if (ram->_dataList == 0) {
        int allocator = igObject_GetAllocator(ram);
        int chosen;
        igObject *created;
        igObject *old;
        if (g_useOwnerAllocator != 0) { chosen = allocator; } else { chosen = Memory_GetAllocatorBySelector(kIGMemoryPoolHandleUser1[0]); }
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
            ((beModelCtrlDispatchView *)self)->OnMessageText(ram, REMOVE_2);
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
        ((beModelCtrlDispatchView *)self)->OnUpdateRam(ram);
        if (work->_isPosLock == 0) {
            beModelCtrl_ApplyMoves(self, info, ram, work);
        } else {
            if (work->_posLockNode != 0) {
                igMatrix44f_Copy(lockMatrix, NodeMatrix(work->_posLockNode));
                igMatrix44f_TranslateLocal(lockMatrix, &work->_posLockOffset[0]);
                ((igTransformDispatchView *)ramData->_node)->SetMatrix(lockMatrix);
            } else if (work->_posLockTrc != 0) {
                ((igTransformDispatchView *)ramData->_node)->SetMatrix((float *)(*(int *)(work->_posLockTrc + 16) + *(int *)((char *)g_igTransformRecorder_mMetaField[0] + 8)));
            } else if (work->_posLockModelName != 0) {
                beMessenger_SelectReceivers(self->_messenger, ACTION_2, work->_posLockModelName, ram->_ramNo);
                beMessenger_AppendString(self->_messenger, work->_posLockBoneName);
                beMessenger_DispatchSelected(self->_messenger, GETBONEMATRIX);
                if (beMessenger_GetMatrixCount(self->_messenger) == 1) {
                    beMessenger_GetMatrix(boneMatrix, self->_messenger, 0);
                    beMessenger_SendNamed(self->_messenger, MODELCTRL_7, work->_posLockModelName, ram->_ramNo, GETMATRIX_2);
                    if (beMessenger_GetMatrixCount(self->_messenger) == 1) {
                        beMessenger_GetMatrix(modelMatrix, self->_messenger, 0);
                        igMatrix44f_PreMultiply(modelMatrix, boneMatrix);
                        ((igTransformDispatchView *)ramData->_node)->SetMatrix(modelMatrix);
                    }
                }
            }
            if (work->_baseAABox != 0) beModelCtrl_UpdateBound(self, (beModelCtrlNode2 *)ramData->_node, (igAABox *)work->_baseAABox);
        }
        rideOn = (beModelCtrlInfoRideOn4 *)work->_rideOnData;
        if (rideOn != 0) {
            ((beModelCtrlInfoRideOnDispatchView *)rideOn)->Move(NodeMatrix(ramData->_node));
            igMatrix44f_GetTranslation((int)rideOn->_oldMatrix, (float *)oldPos);
            igMatrix44f_GetTranslation((int)NodeMatrix(ramData->_node), newPos);
            delta[0] = newPos[0] - oldPos[0];
            delta[1] = newPos[1] - oldPos[1];
            delta[2] = newPos[2] - oldPos[2];
            igMatrix44f_Copy(oldRotation, rideOn->_oldMatrix);
            igMatrix44f_Copy(offset, NodeMatrix(ramData->_node));
            igMatrix44f_SetTranslation((float *)oldRotation, (void *)&g_vec3Zero[0]);
            igMatrix44f_Invert(&inverted, oldRotation, oldRotation);
            igMatrix44f_SetTranslation((float *)offset, (void *)delta);
            igMatrix44f_SetIdentity(local);
            igMatrix44f_Multiply(local, offset, oldRotation);
            igMatrix44f_SetIdentity(world);
            igMatrix44f_Multiply(world, local, NodeMatrix(rideOn->_modelNode));
            ((igTransformDispatchView *)ramData->_node)->SetMatrix(world);
            igMatrix44f_Copy(rideOn->_oldMatrix, NodeMatrix(rideOn->_modelNode));
            work->_isHitCheck = 1;
        }
        if (work->_wCheckName != 0) beModelCtrl_UpdateWaitCheck(self, (beModelCtrlInfo *)info, ram, work);
        beModelCtrl_UpdateMuteki(self, ram, work);
        beModelCtrlSubCom_Update(work->_subCommand, ram);
        if (work->_isHitCheck != 0) beModelCtrl_CheckWallAndFloor(self, info, ram, work);
        rideOn = (beModelCtrlInfoRideOn4 *)work->_rideOnData;
        if (rideOn != 0 && rideOn->_modelRamNo == 0x68) {
            igMatrix44f_GetTranslation((int)NodeMatrix(ramData->_node), pos);
            ((float *)&rideOn->_oldPlayerPos[0])[0] = pos[0];
            ((float *)&rideOn->_oldPlayerPos[0])[1] = pos[1];
            ((float *)&rideOn->_oldPlayerPos[0])[2] = pos[2];
        }
    }
}

/* Slot 46 default: empty. */
void beModelCtrl_OnUpdateRam(void)
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
            slot = igStringRefList_IndexOf(work->_labelSeqList, &key, 0);
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
                    if (g_beModelCtrlLABEL_metaObject == ((igObjectDispatchView *)label)->GetMeta()) {
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

/* Generate for models that start on another model (bullets, effects): the message names the parent
 * model and its ram number, an offset and an optional rotation in radians from the parent's matrix, whether
 * the model stays locked to the parent, and the parent the hits are credited to. */
void beModelCtrl__OnGenerateFromParent(beModelCtrl *self, beBaseInfoRam *ram) {
    float matrix[16];
    float parentMatrix[16];
    beModelCtrlInfoRamData *ramData;
    beModelCtrlInfoWork *work;
    int allocator;
    igObject *created;
    igObject *old;
    char *parentName;
    int parentRamNo;
    unsigned char posLock;
    char *hitParentName;
    if (ram->_dataList == 0) {
        allocator = igObject_GetAllocator(ram);
        allocator = g_useOwnerAllocator ? allocator : Memory_GetAllocatorBySelector(kIGMemoryPoolHandleUser1[0]);
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
    ramData = (beModelCtrlInfoRamData *)igProperty_FindByName((igObject *)ram->_dataList, g_propertyNameField[0], ONE_3);
    work = (beModelCtrlInfoWork *)ramData->_work;
    if (beMessenger_GetStringCount(self->_messenger) == 0) return;
    if (beMessenger_GetStringCount(self->_messenger) == 1) return;
    parentName = (char *)beMessenger_GetString(self->_messenger, 0);
    parentRamNo = beMessenger_GetInt(self->_messenger, 0);
    igVec3f offset = beMessenger_GetVec3(self->_messenger, 0);
    igVec3f rotation = beMessenger_GetVec3Count(self->_messenger) == 2 ? beMessenger_GetVec3(self->_messenger, 1) : *(igVec3f *)g_vec3Zero;
    posLock = beMessenger_GetBool((beMessenger *)self->_messenger, 0);
    hitParentName = (char *)beMessenger_GetString(self->_messenger, 2);
    {
        char *token;
        char *oldName;
        if (g_stringPool[0] == 0) {
            int pool = StringPool_Allocate(16);
            if (pool != 0) pool = StringPool_Construct(pool);
            g_stringPool[0] = pool;
        }
        token = (char *)StringPool_Intern(g_stringPool[0], hitParentName);
        oldName = (char *)work->_hitParentName;
        if (oldName != 0) {
            int *header = (int *)(oldName - 8);
            int refs = *(int *)(oldName - 4) - 1;
            *(int *)(oldName - 4) = refs;
            if (refs == 0) StringChunk_ReleaseHeader(*header, header);
        }
        work->_hitParentName = (int)token;
    }
    work->_hitParentRamNo = beMessenger_GetInt(self->_messenger, 1);
    beMessenger_SendNamed(self->_messenger, MODELCTRL_7, parentName, parentRamNo, GETMATRIX_2);
    if (posLock) {
        igObject *node = (igObject *)beMessenger_GetObject(self->_messenger, 0);
        igObject *oldNode;
        if (node != 0) {
            node->_refCount = node->_refCount + 1;
        }
        oldNode = (igObject *)work->_posLockNode;
        if (oldNode != 0) {
            oldNode->_refCount = oldNode->_refCount - 1;
            if ((oldNode->_refCount & 0x7FFFFF) == 0) {
                igObject_Destroy(oldNode);
            }
        }
        work->_posLockNode = (int)node;
        work->_posLockOffset[0] = offset.x;
        work->_posLockOffset[1] = offset.y;
        work->_posLockOffset[2] = offset.z;
        work->_isPosLock = 1;
    }
    igMatrix44f_SetIdentity(matrix);
    beMessenger_GetMatrix(parentMatrix, self->_messenger, 0);
    igMatrix44f_Copy(matrix, parentMatrix);
    igMatrix44f_TranslateLocal(matrix, &offset);
    if (rotation.x != 0.0f) igMatrix44f_PreRotateAxisAngle(matrix, g_vec3XAxis, rotation.x);
    if (rotation.y != 0.0f) igMatrix44f_PreRotateAxisAngle(matrix, g_vec3YAxis, rotation.y);
    if (rotation.z != 0.0f) igMatrix44f_PreRotateAxisAngle(matrix, (float *)g_vec3ZAxis, rotation.z);
    ((igTransformDispatchView *)ramData->_node)->SetMatrix(matrix);
    work->_aIHOffsetY = offset.y;
}

/* Install the optional placement carried by the generate message: a position (with an optional
 * Euler rotation in degrees) or a full matrix, applied to the model node's matrix. */
void beModelCtrl__OnGenerate(beModelCtrl *self, beBaseInfoRam *ram) {
    float matrix[16];
    float given[16];
    beModelCtrlInfoRamData *ramData;
    int allocator;
    igObject *created;
    igObject *old;
    if (ram->_dataList == 0) {
        allocator = igObject_GetAllocator(ram);
        allocator = g_useOwnerAllocator ? allocator : Memory_GetAllocatorBySelector(kIGMemoryPoolHandleUser1[0]);
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
    ramData = (beModelCtrlInfoRamData *)igProperty_FindByName((igObject *)ram->_dataList, g_propertyNameField[0], ONE_3);
    if (beMessenger_GetVec3Count(self->_messenger) != 0) {
        igMatrix44f_Copy(matrix, NodeMatrix(ramData->_node));
        igMatrix44f_SetTranslation(matrix, &beMessenger_GetVec3(self->_messenger, 0));
        if (beMessenger_GetVec3Count(self->_messenger) == 2) {
            igVec3f rotation = beMessenger_GetVec3(self->_messenger, 1);
            igMatrix44f_SetEulerRotation(matrix, 0.017453292f * Component(rotation, 0), 0.017453292f * Component(rotation, 1), 0.017453292f * Component(rotation, 2));
        }
        ((igTransformDispatchView *)ramData->_node)->SetMatrix(matrix);
        return;
    }
    if (beMessenger_GetMatrixCount(self->_messenger) != 0) {
        beMessenger_GetMatrix(given, self->_messenger, 0);
        ((igTransformDispatchView *)ramData->_node)->SetMatrix(given);
    }
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
            allocator = Memory_GetAllocatorBySelector(kIGMemoryPoolHandleUser1[0]);
        }
        igSmartPointer<igAABox> created(igAABox_CreateInstance(allocator));
        (igSmartPointer<igAABox> &)node->_bound = created;
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

#define ALLOCATOR(a, o) int a = igObject_GetAllocator(o); a = g_useOwnerAllocator ? a : Memory_GetAllocatorBySelector(kIGMemoryPoolHandleUser1[0]);
#define POOL() if (((void * *)g_stringPool)[0] == 0) { void *pl_ = ((void *)StringPool_Allocate(0x10)); if (pl_ != 0) pl_ = ((void *)StringPool_Construct(pl_)); ((void * *)g_stringPool)[0] = pl_; }
#define RELEASE_STRING(old) if (old) { int *h_ = (int *)old - 2; int c_ = ((int *)old)[-1] - 1; ((int *)old)[-1] = c_; if (c_ == 0) StringChunk_ReleaseHeader(*h_, h_); }
#define SET_WORK_STRING(fld, txt) { POOL() const char *tk_ = ((const char *)StringPool_Intern(((void * *)g_stringPool)[0], txt)); const char *old_ = (const char *)work->fld; RELEASE_STRING(old_) work->fld = (int)tk_; }
#define INFO_NAME(b) const char *b; { const char *a_ = (const char *)info->_name; if (a_ != 0) b = a_; else b = ((char *)emptyString); }
#define MESSENGER (self->_messenger)
#define MODEL_NODE ((beModelCtrlNode2 *)ramData->_node)
#define FIRST_LOD(n) (((igLod **)((igObjectList *)(n)->_childList)->_data)[0])
#define ENSURE_DATA_LIST(ram_) DataList::Ensure(ram_, held);
int beModelCtrl_OnMessageText(beModelCtrl *self, beBaseInfoRam *ram, const char *message) {
    beBaseInfo *info = (beBaseInfo *)ram->_parentInfo;
    igVec3f startForward, setForward;
    float setMatrix[16], moveMatrix[16], bulletMatrix[16], quicksandMatrix[16], floorMatrix[16];
    int bullet;
    igObjectList *boxes;
    int hitBox;
    igObject *node2;
    beModelCtrlInfoRideOn *held;
    ENSURE_DATA_LIST(ram)
    beModelCtrlInfoRamData *ramData = (beModelCtrlInfoRamData *)((beBaseInfoData *)igProperty_FindByName(ram->_dataList, g_propertyNameField[0], ((char *)ONE_3)));
    beModelCtrlInfoWork *work = (beModelCtrlInfoWork *)ramData->_work;
    if (((beModelCtrlDispatchView *)self)->OnPreMessage(ram, message) == 1) return 1;
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
        ((beModelCtrlDispatchView *)self)->OnGenerate(ram);
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
            ((beModelCtrlDispatchView *)self)->OnMessageText(ram, SQ_WAIT_2);
        else
            ((beModelCtrlDispatchView *)self)->OnMessageText(ram, sequence.p);
        igObject *baseBox = (igObject *)started->_baseAABox;
        if (baseBox != 0) beModelCtrl_UpdateBound(self, MODEL_NODE, (igAABox *)baseBox);
        return 1;
    }
    case MSG_REMOVE:
        if (ram->_isRun != 0) {
            ((beModelCtrlDispatchView *)self)->OnRemove(ram);
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
            beModelCtrlSubCom_AddEffect(SubCommands(work), beMessenger_GetString(MESSENGER, 0), beMessenger_GetString(MESSENGER, 1), beMessenger_GetFloat(MESSENGER, 0),
                beMessenger_GetVec3(MESSENGER, 0), beMessenger_GetVec3Count(MESSENGER) == 2 ? beMessenger_GetVec3(MESSENGER, 1) : *(igVec3f *)g_vec3Zero,
                beMessenger_GetBool((beMessenger *)MESSENGER, 0), beMessenger_GetBool((beMessenger *)MESSENGER, 1));
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
            ((igTransformDispatchView *)ramData->_node)->SetMatrix(setMatrix);
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
            ((beModelCtrlDispatchView *)self)->OnControlOff(ram);
        }
        return 1;
    case MSG_ONFREEZE:
        if (ram->_isRun != 0 && work != 0) {
            beBaseInfoRam_SetAllTimerScales(ram, 0.0f);
            int id = ram->_ramNo;
            INFO_NAME(n)
            beMessenger_SendNamed(MESSENGER, ((char *)ACTION_2), n, id, ONFREEZE);
            work->_isOnFreeze = 1;
            ((beModelCtrlDispatchView *)self)->OnFreeze(ram);
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
            igMetaObject *t = g_igLod_metaObject;
            igLod *o = FIRST_LOD(MODEL_NODE);
            if (t == ((igLodDispatchView *)o)->GetMeta()) {
                igNodeList *children = (igNodeList *)o->_childList;
                int cnt = 0;
                if (children != 0) cnt = children->_count;
                if (cnt == 3) {
                    igFloatList *ranges = (igFloatList *)o->_rangeList;
                    work->_svLODHighRange = ((float *)ranges->_data)[2];
                    int n = ranges->_count;
                    if (n != 0 && n > 2) ListStoreAt((float *)ranges->_data, 2, 100000000.0f);
                    ((igLodDispatchView *)o)->resetLastRange();
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
                ((igLodDispatchView *)o)->resetLastRange();
            }
        }
        return 1;
    case MSG_MOVETRANS:
        if (ram->_isRun != 0 && work != 0) {
            igVec3f movePosition = beMessenger_GetVec3(MESSENGER, 0);
            igVec3f moveRotation = beMessenger_GetVec3(MESSENGER, 1);
            igMatrix44f_SetIdentity(moveMatrix);
            igMatrix44f_FromTranslation(moveMatrix, &movePosition);
            if (moveRotation.x != 0.0f) igMatrix44f_PreRotateAxisAngle(moveMatrix, g_vec3XAxis, 0.017453292f * moveRotation.x);
            if (moveRotation.y != 0.0f) igMatrix44f_PreRotateAxisAngle(moveMatrix, g_vec3YAxis, 0.017453292f * moveRotation.y);
            { float rz = moveRotation.z; if (rz != 0.0f) igMatrix44f_PreRotateAxisAngle(moveMatrix, ((float *)g_vec3ZAxis), 0.017453292f * rz); }
            ((igTransformDispatchView *)ramData->_node)->SetMatrix(moveMatrix);
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
                if (!igAABox_IntersectBox(((void **)boxes->_data)[idx], bullet)) continue;
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
                igVec3f bulletPos, modelPos;
                igMatrix44f_GetTranslation((int)bulletMatrix, (float *)&bulletPos);
                igMatrix44f_GetTranslation((int)MODEL_NODE->_m, (float *)&modelPos);
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
                ((beModelCtrlDispatchView *)self)->OnErase(ram);
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
                ((beModelCtrlDispatchView *)self)->OnSequenceChange(ram);
            }
        }
        return 1;
    case MSG_ACTION1:
        ((beModelCtrlDispatchView *)self)->OnAction1(ram);
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
                        ((igTransformDispatchView *)r2.p)->SetMatrix(mt);
                        node2 = r2.p;
                        held = (beModelCtrlInfoRideOn *)r.p;
                        RETAIN(node2)
                        RELEASE(held->_modelNode)
                        held->_modelNode = (int)node2;
                    }
                    igMatrix44f_Copy(((beModelCtrlInfoRideOn2 *)r.p)->_oldMatrix, mt);
                    *(igVec3f *)((beModelCtrlInfoRideOn2 *)r.p)->_vector = beMessenger_GetVec3(MESSENGER, 0);
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
                    igVec3f quicksandPos;
                    igMatrix44f_GetTranslation((int)MODEL_NODE->_m, (float *)&quicksandPos);
                    igMatrix44f_Copy(quicksandMatrix, g_matrix44Identity);
                    igMatrix44f_SetTranslation((float *)quicksandMatrix, (void *)&quicksandPos);
                    {
                        ALLOCATOR(b, self)
                        ObjRef<5> r2((igObject *)beModelCtrlNode2_Create(b));
                        ((igTransformDispatchView *)r2.p)->SetMatrix(quicksandMatrix);
                        node2 = r2.p;
                        held = (beModelCtrlInfoRideOn *)r.p;
                        RETAIN(node2)
                        RELEASE(held->_modelNode)
                        held->_modelNode = (int)node2;
                    }
                    igMatrix44f_Copy(((beModelCtrlInfoRideOn3 *)r.p)->_oldMatrix, quicksandMatrix);
                    *(igVec3f *)((beModelCtrlInfoRideOn3 *)r.p)->_worldPosition = beMessenger_GetVec3(MESSENGER, 0);
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
                    igVec3f floorPos;
                    igMatrix44f_GetTranslation((int)MODEL_NODE->_m, (float *)&floorPos);
                    igMatrix44f_Copy(floorMatrix, g_matrix44Identity);
                    igMatrix44f_SetTranslation((float *)floorMatrix, (void *)&floorPos);
                    {
                        ALLOCATOR(b, self)
                        ObjRef<5> r2((igObject *)beModelCtrlNode2_Create(b));
                        ((igTransformDispatchView *)r2.p)->SetMatrix(floorMatrix);
                        node2 = r2.p;
                        held = (beModelCtrlInfoRideOn *)r.p;
                        RETAIN(node2)
                        RELEASE(held->_modelNode)
                        held->_modelNode = (int)node2;
                    }
                    igMatrix44f_Copy(((beModelCtrlInfoRideOn4 *)r.p)->_oldMatrix, floorMatrix);
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
void beModelCtrl_OnAction1(void)
{
}

/* Slot 44 default: empty. */
void beModelCtrl_OnSequenceChange(void)
{
}

/* Slot 43 default: empty. */
void beModelCtrl_OnErase(void)
{
}

/* Slot 41 default: empty. */
void beModelCtrl_OnFreeze(void)
{
}

/* Slot 40 default: empty. */
void beModelCtrl_OnControlOff(void)
{
}

/* Slot 42 default: empty. */
void beModelCtrl_OnRemove(void)
{
}

/* Slot 47 default: always 0. */
int beModelCtrl_OnPreMessage(void) {
    return 0;
}

int beModelCtrlInfoRideOn4_GetMeta(void)
{
    return g_beModelCtrlInfoRideOn4_metaObject[0];
}

int beModelCtrlInfoRideOn3_GetMeta(void)
{
    return g_beModelCtrlInfoRideOn3_metaObject[0];
}

int beModelCtrlInfoRideOn2_GetMeta(void)
{
    return g_beModelCtrlInfoRideOn2_metaObject[0];
}

igMetaObject *beModelCtrl_GetMeta(void)
{
    return g_beModelCtrl_metaObject;
}
