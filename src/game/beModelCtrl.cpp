#include "dw4/support/reflected.h"
#include "dw4/core/igSmartPointer.h"
#include "dw4/core/igTDataList.h"
#include "dw4/maths/igVec3f.h"
#include "dw4/scenegraph/igTraversalView.h"
#include "dw4/game/beModelCtrlDispatchView.h"
#include "dw4/datapump/igRandomNumberDispatchView.h"
#include "dw4/scenegraph/igTransformDispatchView.h"
#include "dw4/scenegraph/igLodDispatchView.h"
#include "dw4/game/beTime.h"
#include "dw4/game/ndmw/listSet.h"
#include "dw4/game/beMeterCtrlNode.h"
#include "dw4/game/beModelCtrl.h"
#include "dw4/game/beModelCtrlInfoWork.h"
#include "dw4/core/StringPool.h"
#include "dw4/core/igStringRef.h"
#include "dw4/game/be.h"
#include "dw4/game/beBaseInfoDataList.h"
#include "dw4/game/beBaseInfoManager.h"
#include "dw4/game/beBaseInfoRam.h"
#include "dw4/game/beLua.h"
#include "dw4/game/beMessenger.h"
#include "dw4/game/beModelCtrlACTION.h"
#include "dw4/game/beModelCtrlAIMAP.h"
#include "dw4/game/beModelCtrlCTRL.h"
#include "dw4/game/beModelCtrlHITBOX.h"
#include "dw4/game/beModelCtrlInfo.h"
#include "dw4/game/beModelCtrlInfoAI.h"
#include "dw4/game/beModelCtrlInfoHitBody.h"
#include "dw4/game/beModelCtrlInfoRideOn.h"
#include "dw4/game/beModelCtrlInfoRideOn2.h"
#include "dw4/game/beModelCtrlInfoRideOn3.h"
#include "dw4/game/beModelCtrlInfoRideOn4.h"
#include "dw4/game/beModelCtrlJUMP.h"
#include "dw4/game/beModelCtrlLABEL.h"
#include "dw4/game/beModelCtrlLABELCTRL.h"
#include "dw4/game/beModelCtrlLUACALL.h"
#include "dw4/game/beModelCtrlMOVE.h"
#include "dw4/game/beModelCtrlMOVEEX.h"
#include "dw4/game/beModelCtrlMOVERL.h"
#include "dw4/game/beModelCtrlMSGBOX.h"
#include "dw4/game/beModelCtrlMUTEKI.h"
#include "dw4/game/beModelCtrlMoveObject.h"
#include "dw4/game/beModelCtrlNode2.h"
#include "dw4/game/beModelCtrlPDMOVE.h"
#include "dw4/game/beModelCtrlSCHitBox.h"
#include "dw4/game/beModelCtrlSubCom.h"
#include "dw4/game/beModelCtrlWCHECK.h"
#include "dw4/game/ndmw/beNDMWMdlMapCursor.h"
#include "dw4/game/beTargetObj.h"
#include "dw4/core/igDataLists.h"
#include "dw4/insight/igInsightCore.h"
#include "dw4/scenegraph/igLod.h"
#include "dw4/maths/igMathConstants.h"
#include "dw4/maths/igMatrix44f.h"
#include "dw4/core/igResult.h"
#include "dw4/core/igMemoryPoolContext.h"
#include "dw4/core/igNamedObject.h"
#include "dw4/core/igObject.h"
#include "dw4/scenegraph/igTransformRecorder.h"
#include "dw4/scenegraph/igTraversal.h"
#include "dw4/scenegraph/igCommonTraversal.h"
#include "dw4/support/softfloat.h"
#include <math.h>
#include <stdio.h>
#include <string.h>
#include "dw4/support/emptyString.h"
#include "dw4/support/list-services.h"
#include "dw4/maths/igAABox.h"
#define SELECT_ALLOCATOR(var, arg) { int base_ = (int)((Gap::Core::igObject *)(arg))->getMemoryPool(); if (g_useOwnerAllocator != 0) var = base_; else var = (int)Memory_GetAllocatorBySelector(kIGMemoryPoolHandleUser1); }
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
extern "C" igMetaObject *beModelCtrl_GetInfoMeta(void);
extern "C" void beModelCtrl_OnWaitCheck(void);
extern "C" void beModelCtrl_OnUpdateRam(void);
extern "C" void beModelCtrl_OnAction1(void);
extern "C" void beModelCtrl_OnSequenceChange(void);
extern "C" void beModelCtrl_OnErase(void);
extern "C" void beModelCtrl_OnFreeze(void);
extern "C" void beModelCtrl_OnControlOff(void);
extern "C" void beModelCtrl_OnRemove(void);
extern "C" int beModelCtrl_OnPreMessage(void);
extern "C" int beModelCtrl_AddInfo(beModelCtrl *self, beModelCtrlInfo *info);
extern "C" void beModelCtrl_RegisterReceiver(void);
extern "C" igMetaObject *beModelCtrlInfoRideOn2_GetMeta(void);

extern "C" void beModelCtrl_UpdateMuteki(beModelCtrl *self, beBaseInfoRam *ram, beModelCtrlInfoWork *work);
extern "C" void beModelCtrl_UpdateKeyCtrl(beModelCtrl *self, beBaseInfo *info, beBaseInfoRam *ram, beModelCtrlInfoWork *work);
extern "C" igMetaObject *beModelCtrlInfoRideOn4_GetMeta(void);
extern "C" igMetaObject *beModelCtrlInfoRideOn3_GetMeta(void);
extern "C" igMetaObject *beModelCtrl_GetMeta(void);
extern "C" int beMeterCtrlNode_Traverse(void *node, igCommonTraversal *traversal, void *data);
extern "C" int beMeterCtrlNode_TraversalFunction(igCommonTraversal *traversal, void *node);
/* A component of a vector by index, read through the vector's address.
 * matching construct: only this inline read gives the generate handler retail's float registers (the degree
 * factor in $f2, x in $f3); .x/.y/.z, igVec3f::operator[] and the same cast written in place exchange the two.
 * operator[] written this way matches here too, but beWaterPlain_UpdateRam needs its (&x)[i] form. */
static inline float Component(const igVec3f &v, int i) { return ((const float *)&v)[i]; }

extern "C" char HIT[];
extern "C" igAABoxList *beModelCtrlInfoHitBody_GetAABoxList(beModelCtrlInfoHitBody *body, beBaseInfoRam *ram, int matrix, long long time);
extern "C" void beModelCtrl_Prepare(beModelCtrl *self);
extern "C" char MODELCTRL_7[];
extern "C" char HITPLAYERBULLET_2[];
extern "C" char HITPLAYERTALK_2[];
extern "C" char HITENEMYBULLET_2[];
extern "C" void beModelCtrl_OnAddRam(beModelCtrl *self, beBaseInfoRam *ram);
extern "C" char ONE_3[];
extern "C" char AITIMER[];
extern "C" char NEAR[];
extern "C" char WPOS[];
extern "C" char PLAYER_3[];
extern "C" char SQ_WALK[];

struct DataListInstall { static inline void go(beBaseInfoRam *ram, const igSmartPointer<igObject> &fresh) {
    igObject *o = fresh.p;
    igObject *old;
    igObject::ref(o);
    old = (igObject *)ram->_dataList;
    igObject::release(old);
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
extern "C" unsigned char beModelCtrl_RunCtrl(beModelCtrl *self, beModelCtrlInfoWork *work, beModelCtrlCTRL *command);

extern "C" void beModelCtrl_UpdateHomingAI(beModelCtrl *self, beModelCtrlInfo *info, beBaseInfoRam *ram, beModelCtrlInfoWork *work, beModelCtrlInfoDataAIH *homing);
extern "C" char AIM[];
extern "C" char AIH[];
extern "C" char KIND_EBULLET_2[];
extern "C" char ENEMY_4[];
extern "C" void beModelCtrl_UpdateControl(beModelCtrl *self, beBaseInfoRam *ram);
extern "C" char ACTION_2[];
extern "C" unsigned char beModelCtrl_RunAction(beModelCtrl *self, beModelCtrlInfo *info, beBaseInfoRam *ram, beModelCtrlACTION *command);
extern "C" char GETMATRIX_2[];
extern "C" void beModelCtrlInfoRideOn_SetModel(beModelCtrlInfoRideOn *self, int modelName, int ramNo, int messenger);
extern "C" unsigned char beModelCtrlInfoRideOn_IsModel(beModelCtrlInfoRideOn *self, int modelName, int ramNo);
extern "C" void beModelCtrlInfoRideOn2_Move(beModelCtrlInfoRideOn2 *self);
extern "C" void beModelCtrlInfoRideOn3_Move(beModelCtrlInfoRideOn3 *self, void *m);
extern "C" void beModelCtrlInfoRideOn4_Move(beModelCtrlInfoRideOn4 *self, void *m);
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
struct Slot { beModelCtrlInfoRideOn4 *p; void set(beModelCtrlInfoRideOn4 *n) { beModelCtrlInfoRideOn4 *o = p; igObject::release(o); p = n; } };
/* Scope holder for the freshly built ride-on record. The constructor takes the allocation result,
 * so the protected range starts after the allocation call. */
struct RideOnRef { beModelCtrlInfoRideOn4 *p; RideOnRef(beModelCtrlInfoRideOn4 *x) { p = x; } ~RideOnRef() { beModelCtrlInfoRideOn4 *o = p; igObject::release(o); } };
extern "C" void beModelCtrl_CheckWallAndFloor(beModelCtrl *self, beBaseInfo *info, beBaseInfoRam *ram, beModelCtrlInfoWork *work);
extern "C" unsigned char beModelCtrl_QueryMove(beModelCtrl *self, beBaseInfoRam *ram, beModelCtrlInfoWork *work, unsigned int query);
extern "C" void beModelCtrlMoveObject_Start(beModelCtrlMoveObject *self, int mode, float value, float frames, float endTime);
extern "C" void beModelCtrlMoveObject_Stop(beModelCtrlMoveObject *self);
extern "C" float beModelCtrlMoveObject_Step(beModelCtrlMoveObject *self, float frames);

extern "C" char KEIKATIMER[];
extern "C" void beModelCtrl_ApplyMoves(beModelCtrl *self, beBaseInfo *info, beBaseInfoRam *ram, beModelCtrlInfoWork *work);
extern "C" char Stop[];
extern "C" char Move[];
extern "C" char Push[];
extern "C" char Back[];
extern "C" char Jump[];
extern "C" char Fall[];
extern "C" char JOINT[];
extern "C" char GETTRCDATA[];

struct MoveRef {
    igObject *p;
    MoveRef() { p = 0; }
    ~MoveRef() { igObject *o = p; igObject::release(o); }
};

/* matching construct: the data-list holder (slot 152) must sit below the move-object holder (slot 156), so it is
 * a local of a static inline member (allocated after the caller's); al/p/old stay the caller's locals. Assigned
 * through igSmartPointer::operator= instead, beModelCtrl_RunMove's registers differ. */
struct Locals {
    static inline void CreateDataList(beBaseInfoRam *ram, int &al, igObject *&p, igObject *&old) {
        SELECT_ALLOCATOR(al, ram);
        {
            igSmartPointer<igObject> sp98((igObject *)((void *)beBaseInfoDataList_Create(al)));
            p = sp98.p;
            if (p != 0) p->_refCount = p->_refCount + 1;
            old = (igObject *)ram->_dataList;
            igObject::release(old);
            ram->_dataList = (int)p;
        }
    }
};
extern "C" unsigned char beModelCtrl_RunMove(beModelCtrl *self, beBaseInfoRam *ram, beModelCtrlInfoWork *work, igObject *command);
extern "C" unsigned char beModelCtrl_RunPdMove(beModelCtrl *self, beBaseInfoRam *ram, beModelCtrlInfoWork *work, beModelCtrlPDMOVE *command);
extern "C" unsigned char beModelCtrl_RunLabelCtrl(beModelCtrl *self, beBaseInfoRam *ram, beModelCtrlInfoWork *work, beModelCtrlLABELCTRL *command);

extern "C" char s_s_lua[];
extern "C" char BHit_2[];
extern "C" unsigned char beModelCtrl_RunLuaCall(beModelCtrl *self, beBaseInfo *info, beBaseInfoRam *ram, beModelCtrlInfoWork *work, beModelCtrlLUACALL *command);
extern "C" char aim[];
extern "C" char WPos[];
extern "C" unsigned char beModelCtrl_RunAiMap(beModelCtrl *self, beModelCtrlInfo *info, beBaseInfoRam *ram, beModelCtrlInfoWork *work, beModelCtrlAIMAP *command);
extern "C" unsigned char beModelCtrl_RunMsgBox(beModelCtrl *self, beModelCtrlInfo *info, beModelCtrlInfoWork *work, beModelCtrlMSGBOX *command);
extern "C" unsigned char beModelCtrl_RunJump(beModelCtrl *self, beBaseInfoRam *ram, beModelCtrlJUMP *command);
extern "C" unsigned char beModelCtrl_StartWaitCheck(beModelCtrl *self, beModelCtrlInfoWork *work, beModelCtrlWCHECK *command);
extern "C" char TurnY[];
extern "C" char Landing[];
extern "C" char Action[];
extern "C" char ISCOMEND[];
extern "C" char Moving[];
extern "C" char Rotation[];
extern "C" void beModelCtrl_UpdateWaitCheck(beModelCtrl *self, beModelCtrlInfo *info, beBaseInfoRam *ram, beModelCtrlInfoWork *work);
extern "C" char AllClear[];
extern "C" char Set[];
extern "C" unsigned char beModelCtrl_RunHitBox(beModelCtrl *self, beBaseInfoRam *ram, beModelCtrlInfoWork *work, beModelCtrlHITBOX *command);
extern "C" char OFFWALL[];
extern "C" char ONWALL[];
extern "C" char OFFFLOOR[];
extern "C" char ONFLOOR[];
struct MutekiNameOf { static int *Get(beModelCtrlMUTEKI *m) { if (m->_name != 0) { return (int *)m->_name; } return (int *)emptyString; } };
extern "C" unsigned char beModelCtrl_RunMuteki(beModelCtrl *self, beBaseInfoRam *ram, beModelCtrlInfoWork *work, beModelCtrlMUTEKI *command);

extern "C" void beModelCtrl_UpdateDirection(beModelCtrl *self, beBaseInfo *info, beBaseInfoRam *ram, beModelCtrlInfoWork *work, int force);
extern "C" char SQ_NONE[];
extern "C" char SQ_ERAS_2[];
extern "C" char REMOVE_2[];
extern "C" char GETBONEMATRIX[];
extern "C" void beModelCtrl_UpdateRam(beModelCtrl *self, beBaseInfoRam *ram);
extern "C" int beModelCtrlInfoWork_FindSeqLabel(beModelCtrl *self, beModelCtrlInfoWork *work);
extern "C" void beModelCtrl_UpdateBound(beModelCtrl *self, beModelCtrlNode2 *node, igAABox *box);
/* The work's sub-command list (effects, sounds, hit boxes started by commands). */
static inline beModelCtrlSubCom *SubCommands(beModelCtrlInfoWork *work) { return (beModelCtrlSubCom *)work->_subCommand; }
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

/* Owning stack references to the objects this handler creates before binding them: kind 0 the AI
 * info, 1 the hit-body info, 2..4 the ride-on infos of commands 25..27 and 5 their model node. */
template <int kind> struct ObjRef {
    igObject *p;
    ObjRef(igObject *q) : p(q) {}
    ~ObjRef() { igObject *x = p; igObject::release(x); }
};

/* Creates the ram's data list on first use.
 * matching construct: the handler's ride-on local doubles as the list's holder; a local of its own, or an
 * assignment through igSmartPointer::operator=, moves registers */
struct DataList {
    static inline void Ensure(beBaseInfoRam *ram, beModelCtrlInfoRideOn *&held) {
        if (ram->_dataList == 0) {
            int a = (int)((Gap::Core::igObject *)ram)->getMemoryPool();
            a = g_useOwnerAllocator ? a : (int)Memory_GetAllocatorBySelector(kIGMemoryPoolHandleUser1);
            igSmartPointer<igObject> r((igObject *)(beBaseInfoDataList_Create(a)));
            held = (beModelCtrlInfoRideOn *)r.p;
            RETAIN(held)
            RELEASE(ram->_dataList)
            ram->_dataList = (int)held;
        }
    }
};
extern "C" int beModelCtrl_OnMessageText(beModelCtrl *self, beBaseInfoRam *ram, const char *message);


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
    Gap::Attrs::igModelViewMatrixAttr *matrixAttr;
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
    attrId = Gap::Attrs::igModelViewMatrixAttr::getClassMeta()->_id;
    matrices = ((igAttrStack **)((igObjectList *)attrs->_attrStacks)->_data)[((int *)attrs->_attrStackIndexTable)[attrId]];
    result = 0;
    if (meter->_isMeter) {
        times = (igObjectList *)meter->_timeList;
        if (times->_count != 0) {
            time = ((long long *)times->_data)[0];
            timePool = (igObjectPool *)traversal->_timePool;
            if (timePool->_freeIndex >= timePool->_count) {
                igObjectPool_Grow(timePool, (igObject *(*)(int))Gap::Attrs::igTimeAttr::_instantiateFromPool);
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
            result = igTraversal_TraverseChildren((igTraversal *)traversal, (igNode *)node);
            ((Gap::Sg::igAttrStackManager *)attrs)->fastPopAttr(*timeUnitID + ((int *)attrs->_attrStackIndexTable)[*timeAttrIndex]);
            ((igCommonTraversalDispatchView *)traversal)->popTime();
        }
    } else {
        firstChild = ((void **)((igObjectList *)((beMeterCtrlNode *)data)->_childList)->_data)[0];
        igMatrix44f_SetIdentity(modelView);
        matrixAttr = (Gap::Attrs::igModelViewMatrixAttr *)TakePooled((igObjectPool *)traversal->_matrixPool, (igObject *(*)(int))Gap::Attrs::igModelViewMatrixAttr::_instantiateFromPool);
        depth = matrices->_count - 1;
        igMatrix44f_Copy(modelView, (const float *)((char *)((void **)matrices->_data)[depth] + 12));
        igMatrix44f_GetTranslation((const float *)modelView, (float *)&translation);
        clock = (igTimeAttr *)TakePooled((igObjectPool *)traversal->_timePool, (igObject *(*)(int))Gap::Attrs::igTimeAttr::_instantiateFromPool);
        count = ((igObjectList *)meter->_timeList)->_count;
        for (i = 0; i < count; i++) {
            time = ((long long *)((igObjectList *)meter->_timeList)->_data)[i];
            if (i != 0) {
                /* matching construct: the offset through a named const reference; `translation +=` the
                 * field itself moves the x load of translation behind the offset's */
                const igVec3f &offset = meter->_numberOffset;
                translation += offset;
            }
            igMatrix44f_SetTranslation(modelView, translation.vec);
            matrixAttr->setMatrix((const igMatrix44f &)modelView);
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
            ((Gap::Sg::igTraversal *)traversal)->dispatch((Gap::Core::igObject *)firstChild);
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
    igMetaObject *meta = (igMetaObject *)beMeterCtrlNode_ResolveMetaObject();
    Gap::Sg::igTraversal::_setFunction(Gap::Sg::igCommonTraversal::_getTraversalFunctions(), meta, (igTraversalFunction *)beMeterCtrlNode_TraversalFunction);
}

void beModelCtrl_DrawDebugHitBox(beModelCtrl *self, igNode *node, igAABox *box, float *color)
{
}

igAABoxList *beModelCtrlInfoHitBody_GetAABoxList(beModelCtrlInfoHitBody *body, beBaseInfoRam *ram, int matrix, long long time) {
    if (body->_isFirst != 0) {
        beModelCtrlInfoDataHit *hit = ((beModelCtrlInfoDataHit *)((Gap::Core::igObjectList *)(((beBaseInfo *)ram->_parentInfo)->_dataList))->search((Gap::Core::igStringMetaField *)Gap::Core::igNamedObject::k_name, HIT));
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
                if (k < list->_capacity) list->_count = k + 1; else ((Gap::Core::igDataList *)list)->resizeAndSetCount(k + 1, 12);
                igVec3f *extent = &((igVec3f *)list->_data)[k];
                extent->vec[0] = below[0]; extent->vec[1] = below[1]; extent->vec[2] = below[2];
            }
            {
                int k;
                igDataList *list = (igDataList *)body->_AABoxMaxList;
                k = list->_count;
                if (k < list->_capacity) list->_count = k + 1; else ((Gap::Core::igDataList *)list)->resizeAndSetCount(k + 1, 12);
                igVec3f *extent = &((igVec3f *)list->_data)[k];
                extent->vec[0] = above[0]; extent->vec[1] = above[1]; extent->vec[2] = above[2];
            }
            {
                int alloc = (int)((Gap::Core::igObject *)body)->getMemoryPool();
                int a;
                if (g_useOwnerAllocator != 0) a = alloc; else a = (int)Memory_GetAllocatorBySelector(kIGMemoryPoolHandleUser1);
                igSmartPointer<igAABox> created(igAABox_CreateInstance(a));
                { igAABox *boxPtr = created.p; igAABoxList *boxList = (igAABoxList *)body->_AABoxList; ((Gap::Core::igObjectList *)boxList)->append((Gap::Core::igObject *)boxPtr); }
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
            igVec3f center;
            igVec3f below;
            igVec3f above;
            int k;
            for (k = 0; k < 3; k++) { dst->_min[k] = src->_min[k]; dst->_max[k] = src->_max[k]; }
            thunk_igAABox_Transform(dst, (const float *)matrix);
            center.combine(0.5f, dst->_min, 0.5f, dst->_max);
            below = ((igVec3f *)((igDataList *)body->_AABoxMinList)->_data)[i];
            above = ((igVec3f *)((igDataList *)body->_AABoxMaxList)->_data)[i];
            for (k = 0; k < 3; k++) { dst->_min[k] = center[k] - below[k]; dst->_max[k] = center[k] + above[k]; }
        }
    }
    return (igAABoxList *)body->_AABoxList;
}

void beModelCtrl_Prepare(beModelCtrl *self) {
    if (self->_luaManager == 0) {
        self->_luaManager = (int)igInsightCore_FindManager((igInsightCore *)self->_insight, g_beLua_metaObject);
    }
    if (self->_targetObj == 0) {
        self->_targetObj = (int)igInsightCore_FindManager((igInsightCore *)self->_insight, g_beTargetObj_metaObject);
    }
}

/* Slot 30 default: first word of the beModelCtrlInfo MetaObject record. */
igMetaObject *beModelCtrl_GetInfoMeta(void)
{
    return g_beModelCtrlInfo_metaObject;
}

int beModelCtrl_AddInfo(beModelCtrl *self, beModelCtrlInfo *info) {
    igMetaObject *infoMeta;

    infoMeta = ((beModelCtrlDispatchView *)self)->GetInfoMeta();
    if ((infoMeta == ((igObjectDispatchView *)info)->GetMeta()) && (((beModelCtrlDispatchView *)self)->IsKind((const char *)info->_kindString) == 1)) {
        beBaseInfoManager_AddInfo((beBaseInfoManager *)self, (beBaseInfo *)info);
        return 1;
    }
    return 0;
}

void beModelCtrl_OnAddRam(beModelCtrl *self, beBaseInfoRam *ram) {
    beBaseInfo *info;
    beModelCtrlInfoDataHit *hit;

    info = (beBaseInfo *)ram->_parentInfo;
    beMessenger_RegisterReceiverFromInfo((beMessenger *)self->_messenger, ram, MODELCTRL_7);
    hit = (beModelCtrlInfoDataHit *)((Gap::Core::igObjectList *)info->_dataList)->search((Gap::Core::igStringMetaField *)Gap::Core::igNamedObject::k_name, HIT);
    if (hit != 0) {
        if (hit->_isHitPlayerBullet != 0) {
            beMessenger_RegisterReceiverFromInfo((beMessenger *)self->_messenger, ram, HITPLAYERBULLET_2);
        }
        if (hit->_isHitPlayerTalk != 0) {
            beMessenger_RegisterReceiverFromInfo((beMessenger *)self->_messenger, ram, HITPLAYERTALK_2);
        }
        if (hit->_isHitEnemyBullet != 0) {
            beMessenger_RegisterReceiverFromInfo((beMessenger *)self->_messenger, ram, HITENEMYBULLET_2);
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
    int pool;
    int roll;
    int i;
    int count;
    beModelCtrlAIData **zones;
    char *text;
    char *zoneName;
    char *token;
    char *old;
    float value;
    if (ram->_dataList == 0) {
        pool = (int)((Gap::Core::igObject *)ram)->getMemoryPool();
        pool = (g_useOwnerAllocator != 0) ? pool : (int)Memory_GetAllocatorBySelector(kIGMemoryPoolHandleUser1);
        DataListInstall::make(ram, pool);
    }
    ramData = ((beModelCtrlInfoRamData *)((Gap::Core::igObjectList *)ram->_dataList)->search((Gap::Core::igStringMetaField *)Gap::Core::igNamedObject::k_name, ONE_3));
    ai = (beModelCtrlInfoAI *)work->_aI;
    igStringRef seqName;
    if (beBaseInfoRam_IsTimerExpired(ram, AITIMER)) {
        map = ((beModelCtrlAIMap **)((beModelCtrlAIMapList *)aim->_aIMapList)->_data)[ai->_mapNo];
        if ((char *)map->_targetType == 0) {
            if (g_stringPool == 0) {
                pool = (int)StringPool_Allocate(16);
                if (pool != 0) {
                    pool = (int)StringPool_Construct((StringPool *)pool);
                }
                g_stringPool = (StringPool *)pool;
            }
            token = StringPool_Intern(g_stringPool, NEAR);
            old = (char *)map->_targetType;
            if (old != 0) {
                int *header = (int *)old - 2;
                int refs = ((int *)old)[-1] - 1;
                ((int *)old)[-1] = refs;
                if (refs == 0) {
                    StringChunk_ReleaseHeader((StringChunk *)*header, (StringTokenHeader *)header);
                }
            }
            map->_targetType = (int)token;
        }
        if (strcmp((char *)map->_targetType, WPOS) == 0) {
            beModelCtrlInfoAI *ai2 = (beModelCtrlInfoAI *)work->_aI;
            pos[0] = ai2->_worldPos[0];
            pos[1] = ai2->_worldPos[1];
            pos[2] = ai2->_worldPos[2];
            if (beTargetObj_SetTarget(NodeMatrix(ramData->_node), pos) == 0) {
                return;
            }
        } else {
            if (beTargetObj_SelectTarget(NodeMatrix(ramData->_node), PLAYER_3, (char *)map->_targetType) == 0) {
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
        work->_targetDirection[1] = beTargetObj_GetTargetBearing(zone->_dirRadian);
        zoneName = (char *)zone->_name;
        if (zoneName != 0) {
            text = zoneName;
        } else {
            text = (char *)emptyString;
        }
        seqName = text;
        beBaseInfoRam_StartTimer(ram, AITIMER, FramesToTime(zone->_time));
    } else {
        text = (char *)ai->_seqName;
        seqName = text;
    }
    work->_keyInput = strcmp(seqName.p, SQ_WALK) == 0;
    text = seqName.p;
    if (g_stringPool == 0) {
        pool = (int)StringPool_Allocate(16);
        if (pool != 0) {
            pool = (int)StringPool_Construct((StringPool *)pool);
        }
        g_stringPool = (StringPool *)pool;
    }
    token = StringPool_Intern(g_stringPool, text);
    old = (char *)work->_keyEventName;
    if (old != 0) {
        int *header = (int *)old - 2;
        int refs = ((int *)old)[-1] - 1;
        ((int *)old)[-1] = refs;
        if (refs == 0) {
            StringChunk_ReleaseHeader((StringChunk *)*header, (StringTokenHeader *)header);
        }
    }
    work->_keyEventName = (int)token;
    text = seqName.p;
    if (g_stringPool == 0) {
        pool = (int)StringPool_Allocate(16);
        if (pool != 0) {
            pool = (int)StringPool_Construct((StringPool *)pool);
        }
        g_stringPool = (StringPool *)pool;
    }
    token = StringPool_Intern(g_stringPool, text);
    old = (char *)ai->_seqName;
    if (old != 0) {
        int *header = (int *)old - 2;
        int refs = ((int *)old)[-1] - 1;
        ((int *)old)[-1] = refs;
        if (refs == 0) {
            StringChunk_ReleaseHeader((StringChunk *)*header, (StringTokenHeader *)header);
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
        allocator = (int)((Gap::Core::igObject *)ram)->getMemoryPool();
        allocator = (g_useOwnerAllocator != 0) ? allocator : (int)Memory_GetAllocatorBySelector(kIGMemoryPoolHandleUser1);
        DataListInstall::make(ram, allocator);
    }
    ramData = ((beModelCtrlInfoRamData *)((Gap::Core::igObjectList *)ram->_dataList)->search((Gap::Core::igStringMetaField *)Gap::Core::igNamedObject::k_name, ONE_3));
    ai = (beModelCtrlInfoAI *)work->_aI;
    turnX = 1;
    turnY = 0;
    switch (ai->_hStatus) {
    case 0:
        beBaseInfoRam_StartTimer(ram, AITIMER, FramesToTime(homing->_firstFrame));
        ai->_hStatus = 1;
    case 1:
        if (beBaseInfoRam_IsTimerExpired(ram, AITIMER) != 0) {
            turnY = 1;
            ai->_hStatus = 2;
        }
        break;
    case 2:
        beBaseInfoRam_StartTimer(ram, AITIMER, FramesToTime(homing->_secondFrame));
        ai->_hStatus = 3;
    case 3:
        if (beBaseInfoRam_IsTimerExpired(ram, AITIMER) != 0) {
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
            if (beTargetObj_SelectTarget(NodeMatrix(ramData->_node), PLAYER_3, NEAR) == 0) {
                return;
            }
        } else {
            if (beTargetObj_SelectTarget(NodeMatrix(ramData->_node), ENEMY_4, NEAR) == 0) {
                return;
            }
        }
        distanceSq = beTargetObj_GetTargetDistanceSq();
        if (distanceSq <= homing->_areaSquare) {
            origin = beTargetObj_GetOrigin();
            originX = origin->vec[0];
            originY = origin->vec[1];
            originZ = origin->vec[2];
            target = beTargetObj_GetTargetPosition();
            targetX = target->vec[0];
            targetY = target->vec[1];
            targetZ = target->vec[2];
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

unsigned char beModelCtrl_RunCtrl(beModelCtrl *self, beModelCtrlInfoWork *work, beModelCtrlCTRL *command) {
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
        allocator = (int)((Gap::Core::igObject *)ram)->getMemoryPool();
        allocator = (g_useOwnerAllocator != 0) ? allocator : (int)Memory_GetAllocatorBySelector(kIGMemoryPoolHandleUser1);
        igSmartPointer<igObject> ref(beBaseInfoDataList_Create(allocator));
        list = ref.p;
        igObject::ref(list);
        old = (igObject *)ram->_dataList;
        igObject::release(old);
        ram->_dataList = (int)list;
    }
    work = ((beModelCtrlInfoRamData *)((Gap::Core::igObjectList *)ram->_dataList)->search((Gap::Core::igStringMetaField *)Gap::Core::igNamedObject::k_name, ONE_3))->_work;
    property = (beBaseInfoData *)((Gap::Core::igObjectList *)info->_dataList)->search((Gap::Core::igStringMetaField *)Gap::Core::igNamedObject::k_name, AIM);
    if (property != 0) {
        if (((igObjectList *)((beModelCtrlInfoDataAIM *)property)->_aIMapList)->_count != 0) {
            beModelCtrl_UpdateMapAI(self, info, ram, (beModelCtrlInfoWork *)work, (beModelCtrlInfoDataAIM *)property);
        }
    } else {
        property = (beBaseInfoData *)((Gap::Core::igObjectList *)info->_dataList)->search((Gap::Core::igStringMetaField *)Gap::Core::igNamedObject::k_name, AIH);
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
        if (r == 0) StringChunk_ReleaseHeader((StringChunk *)*h, (StringTokenHeader *)h);
    }
} };
void beModelCtrl_UpdateKeyCtrl(beModelCtrl *self, beBaseInfo *info, beBaseInfoRam *ram, beModelCtrlInfoWork *work)
{
    if (work->_isOnCtrl != 0) ((beModelCtrlDispatchView *)self)->UpdateControl(ram);
    if (strcmp((const char *)work->_keyEventName, SQ_NONE) == 0) {
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
                if (g_stringPool == 0) {
                    StringPool *pool = (StringPool *)StringPool_Allocate(16);
                    if (pool != 0) pool = StringPool_Construct(pool);
                    g_stringPool = pool;
                }
                token = StringPool_Intern(g_stringPool, SQ_WALK);
                KeyEventName::rel((char *)work->_keyEventName);
                work->_keyEventName = (int)token;
            }
            break;
        case 3:
            if (work->_keyInput == 0) {
                char *token;
                if (g_stringPool == 0) {
                    StringPool *pool = (StringPool *)StringPool_Allocate(16);
                    if (pool != 0) pool = StringPool_Construct(pool);
                    g_stringPool = pool;
                }
                token = StringPool_Intern(g_stringPool, SQ_WAIT_2);
                KeyEventName::rel((char *)work->_keyEventName);
                work->_keyEventName = (int)token;
            }
            break;
        }
    }
    if (strcmp((const char *)work->_keyEventName, (const char *)SQ_NONE) != 0 && strcmp((const char *)work->_keyEventName, (const char *)work->_seqCodeName) != 0) {
        ((beModelCtrlDispatchView *)self)->OnMessageText(ram, (const char *)work->_keyEventName);
    }
}

unsigned char beModelCtrl_RunAction(beModelCtrl *self, beModelCtrlInfo *info, beBaseInfoRam *ram, beModelCtrlACTION *command) {
    int modelName;
    int action;
    int ramNo;

    action = command->_name ? command->_name : (int)emptyString;
    ramNo = ram->_ramNo;
    modelName = info->_name ? info->_name : (int)emptyString;
    beMessenger_SendNamed((beMessenger *)self->_messenger, ACTION_2, (const char *)modelName, ramNo, (const char *)action);
    return 1;
}

void beModelCtrlInfoRideOn_SetModel(beModelCtrlInfoRideOn *self, int modelName, int ramNo, int messenger) {
    int matrix[16];
    igObject *node;
    int token, value;
    int *header;
    int old;
    igObject *oldNode;
    beMessenger_SendNamed((beMessenger *)messenger, MODELCTRL_7, (const char *)modelName, ramNo, GETMATRIX_2);
    node = beMessenger_GetObject((beMessenger *)messenger, 0);
    igMatrix44f_Copy((float *)matrix, (const float *)NodeMatrix((int)node));
    if (g_stringPool == 0) {
        value = (int)StringPool_Allocate(16);
        if (value != 0) {
            value = (int)StringPool_Construct((StringPool *)value);
        }
        g_stringPool = (StringPool *)value;
    }
    token = ((int)StringPool_Intern(g_stringPool, (const char *)modelName));
    old = self->_modelName;
    if (old != 0) {
        header = (int *)(old - 8);
        value = *(int *)(old - 4) - 1;
        *(int *)(old - 4) = value;
        if (value == 0) {
            StringChunk_ReleaseHeader((StringChunk *)*header, (StringTokenHeader *)header);
        }
    }
    self->_modelName = token;
    self->_modelRamNo = ramNo;
    igObject::ref(node);
    oldNode = (igObject *)self->_modelNode;
    igObject::release(oldNode);
    self->_modelNode = (int)node;
    igMatrix44f_Copy((float *)&self->_oldMatrix, (const float *)matrix);
}

unsigned char beModelCtrlInfoRideOn_IsModel(beModelCtrlInfoRideOn *self, int modelName, int ramNo) {
    if (strcmp((const char *)self->_modelName, (const char *)modelName) != 0) return 0;
    if (ramNo == self->_modelRamNo) return 1;
    return 0;
}

/* Resets the ride-on pose: clears the translation of `_oldMatrix` to (0,0,0) and writes `_vector`
 * into the translation of the model node's matrix (+0x20 of a node, the igTransform `_m` offset).
 * igMatrix44f_SetTranslation copies vec3 into matrix words 12..14. */
void beModelCtrlInfoRideOn2_Move(beModelCtrlInfoRideOn2 *self) {
    igMatrix44f_SetTranslation(self->_oldMatrix, g_vec3Zero.vec);
    igMatrix44f_SetTranslation(NodeMatrix(self->_modelNode), self->_vector.vec);
}

void beModelCtrlInfoRideOn3_Move(beModelCtrlInfoRideOn3 *self, void *m) {
    igVec3f t;
    igVec3f d;
    float e, x, g, k, b, z, len, inv, y, c, a;
    igMatrix44f_SetTranslation((float *)((char *)self->_oldMatrix), g_vec3Zero.vec);
    igMatrix44f_GetTranslation((const float *)m, (float *)&t);
    d[0] = self->_worldPosition.vec[0];
    d[1] = self->_worldPosition.vec[1];
    d[2] = self->_worldPosition.vec[2];
    d[0] = d[0] - t[0];
    d[1] = d[1] - t[1];
    d[2] = d[2] - t[2];
    y = ((igVec3f *)&d)->vec[1]; x = d[0]; z = ((igVec3f *)&d)->vec[2];
    len = sqrtf(x * x + y * y + z * z);
    inv = 1.0f / len;
    d[0] = d[0] * inv;
    d[1] = d[1] * inv;
    d[2] = d[2] * inv;
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
    d[0] = d[0] * k;
    d[1] = d[1] * k;
    d[2] = d[2] * k;
    igMatrix44f_SetTranslation(NodeMatrix(self->_modelNode), (const float *)&d);
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
    igMatrix44f_SetTranslation(self->_oldMatrix, g_vec3Zero.vec);
    igMatrix44f_GetTranslation((const float *)m, player.vec);
    height = player[1];
    player[1] = 0;
    last.set(self->_oldPlayerPos);
    last[1] = 0;
    delta.subtract(player, last);
    switch (self->_isFirst) {
    case 0:
        igMatrix44f_SetTranslation(NodeMatrix(self->_modelNode), g_vec3Zero.vec);
        self->_isFirst = 1;
        break;
    case 1: {
        float lengthSq;
        delta[1] = 0;
        lengthSq = delta.length2();
        if (!(lengthSq < 0.6f * 0.6f)) {
            delta.scale(1.0f / sqrtf(lengthSq));
            delta.scale(0.6f);
        }
        self->_vector = delta;
        igMatrix44f_SetTranslation(NodeMatrix(self->_modelNode), g_vec3Zero.vec);
        self->_isFirst = 2;
        break;
    }
    default: {
        int i;
        igVec3f zero;
        Vec3_Lerp(step.vec, self->_scalar, self->_vector.vec, delta.vec);
        zero = g_vec3Zero;
        for (i = 0; i < 3; i++) {
            if (i == 1) {
                step[i] = 0;
            }
            if (!(step[i] <= self->_limitter)) break;
            if (step[i] < -self->_limitter) break;
            if (i == 2) {
                step = zero;
            }
        }
        self->_vector = step;
        igMatrix44f_SetTranslation(NodeMatrix(self->_modelNode), step.vec);
        step += last;
        last[1] = height;
        igMatrix44f_SetTranslation((float *)m, last.vec);
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
        beMessenger_SendNamed((beMessenger *)self->_messenger, HITLANDDELIVER, (const char *)name, ramNo, kind);
        if (work->_luaWHit != 0 && beMessenger_GetBool((beMessenger *)self->_messenger, 1)) {
            int name = info->_name;
            name = name ? name : (int)emptyString;
            beModelCtrl_CallLua(self, ram, (const char *)work->_luaWHit, WHit, (const char *)name, 0, 0, (const char *)0, 0, 0);
        }
    }
    if (work->_isFloorCheck) {
        if (beModelCtrl_QueryMove(self, ram, work, 3)) return;
        {
            int name = info->_name;
            int ramNo = ram->_ramNo;
            name = name ? name : (int)emptyString;
            beMessenger_SendNamed((beMessenger *)self->_messenger, HITLANDDELIVER, (const char *)name, ramNo, HITFLOORCHECK);
        }
        if (beMessenger_GetBoolCount((beMessenger *)self->_messenger) == 0) return;
        floorModel = 0;
        hasFloorModel = beMessenger_GetStringCount((beMessenger *)self->_messenger);
        if (hasFloorModel != 0) {
            floorModel = ((int)beMessenger_GetString((beMessenger *)self->_messenger, 0));
            if (strcmp((const char *)floorModel, emptyString_2) != 0) {
                floorRamNo = beMessenger_GetInt((beMessenger *)self->_messenger, 0);
            } else {
                hasFloorModel = 0;
            }
        }
        landed = beMessenger_GetBool((beMessenger *)self->_messenger, 0);
        floorHit = beMessenger_GetBool((beMessenger *)self->_messenger, 1);
        rideOnChanged = false;
        if (work->_isFallCheck) {
            if (beModelCtrl_QueryMove(self, ram, work, 4)) {
                if (floorHit != 0) {
                    int name = info->_name;
                    int ramNo = ram->_ramNo;
                    name = name ? name : (int)emptyString;
                    beMessenger_SendNamed((beMessenger *)self->_messenger, HITLANDDELIVER, (const char *)name, ramNo, HITFLOORADJUST);
                    beModelCtrl_QueryMove(self, ram, work, 5);
                    rideOnChanged = true;
                }
            } else if (landed) {
                int name = info->_name;
                int ramNo = ram->_ramNo;
                name = name ? name : (int)emptyString;
                beMessenger_SendNamed((beMessenger *)self->_messenger, HITLANDDELIVER, (const char *)name, ramNo, HITFLOORADJUST);
                beModelCtrl_QueryMove(self, ram, work, 5);
                return;
            } else {
                if (strcmp((const char *)work->_seqCodeName, SQ_SLEP) == 0) return;
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
                    int base = (int)((Gap::Core::igObject *)self)->getMemoryPool();
                    int allocator;
                    beModelCtrlInfoRideOn4 *created;
                    if (g_useOwnerAllocator != 0) allocator = base; else allocator = (int)Memory_GetAllocatorBySelector(kIGMemoryPoolHandleUser1);
                    RideOnRef holder((beModelCtrlInfoRideOn4 *)beModelCtrlInfoRideOn_Create(allocator));
                    beModelCtrlInfoRideOn_SetModel((beModelCtrlInfoRideOn *)holder.p, floorModel, floorRamNo, self->_messenger);
                    created = holder.p;
                    if (created != 0) created->_refCount++;
                    ((Slot *)&work->_rideOnData)->set(created);
                } else if (beModelCtrlInfoRideOn_IsModel((beModelCtrlInfoRideOn *)rideOn, floorModel, floorRamNo) == 0) {
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
    igVec3f step;
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
                allocator = (int)((Gap::Core::igObject *)ram)->getMemoryPool();
                allocator = g_useOwnerAllocator ? allocator : (int)Memory_GetAllocatorBySelector(kIGMemoryPoolHandleUser1);
                {
                    igSmartPointer<igObject> ref(beBaseInfoDataList_Create(allocator));
                    created = ref.p;
                    igObject::ref(created);
                    old = (igObject *)ram->_dataList;
                    igObject::release(old);
                    ram->_dataList = (int)created;
                }
            }
            ramData = ((beModelCtrlInfoRamData *)((Gap::Core::igObjectList *)ram->_dataList)->search((Gap::Core::igStringMetaField *)Gap::Core::igNamedObject::k_name, ONE_3));
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
    if (beBaseInfoRam_HasTimer(ram, KEIKATIMER) == 0) {
        beBaseInfoRam_StartTimer(ram, KEIKATIMER, 0);
    }
    if (work->_isPosLock != 0) {
        work->_isPosLock = 0;
        if (ram->_dataList == 0) {
            int allocator;
            igObject *pool, *old;
            Locals::CreateDataList(ram, allocator, pool, old);
        }
        Vec3f_TransformDirection(&forward[0], g_vec3ZAxis.vec, NodeMatrix(((beModelCtrlInfoRamData *)((Gap::Core::igObjectList *)ram->_dataList)->search((Gap::Core::igStringMetaField *)Gap::Core::igNamedObject::k_name, ONE_3))->_node));
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
        igObject::release(old);
        object.p = (igObject *)Gap::Bec::beModelCtrlMoveObject::_instantiateFromPool((igMemoryPoolView *)allocator);
        { igObject *created = object.p; beModelCtrlMoveObjectList *list = *(beModelCtrlMoveObjectList **)&work->_moveObjectList; ((Gap::Core::igObjectList *)list)->append((Gap::Core::igObject *)created); }
        SELECT_ALLOCATOR(allocator, self);
        old = object.p;
        igObject::release(old);
        object.p = (igObject *)Gap::Bec::beModelCtrlMoveObject::_instantiateFromPool((igMemoryPoolView *)allocator);
        { igObject *created = object.p; beModelCtrlMoveObjectList *list = *(beModelCtrlMoveObjectList **)&work->_moveObjectList; ((Gap::Core::igObjectList *)list)->append((Gap::Core::igObject *)created); }
        SELECT_ALLOCATOR(allocator, self);
        old = object.p;
        igObject::release(old);
        object.p = (igObject *)Gap::Bec::beModelCtrlMoveObject::_instantiateFromPool((igMemoryPoolView *)allocator);
        { igObject *created = object.p; beModelCtrlMoveObjectList *list = *(beModelCtrlMoveObjectList **)&work->_moveObjectList; ((Gap::Core::igObjectList *)list)->append((Gap::Core::igObject *)created); }
        SELECT_ALLOCATOR(allocator, self);
        old = object.p;
        igObject::release(old);
        object.p = (igObject *)Gap::Bec::beModelCtrlMoveObject::_instantiateFromPool((igMemoryPoolView *)allocator);
        { igObject *created = object.p; beModelCtrlMoveObjectList *list = *(beModelCtrlMoveObjectList **)&work->_moveObjectList; ((Gap::Core::igObjectList *)list)->append((Gap::Core::igObject *)created); }
    }
    meta = Gap::Bec::beModelCtrlMOVE::getClassMeta();
    if (meta == ((igObjectDispatchView *)command)->GetMeta()) {
        char *name;
        float value, frame;
        beModelCtrlMOVE *m = (beModelCtrlMOVE *)command;
        name = m->_name ? (char *)m->_name : (char *)emptyString;
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
        meta = Gap::Bec::beModelCtrlMOVEEX::getClassMeta();
        if (meta == ((igObjectDispatchView *)command)->GetMeta()) {
            char *name;
            int idx, mode, base;
            unsigned char isSeqStop;
            float value, frame, playTime, stopValue, stopFrame;
            beModelCtrlMoveObject *move;
            beModelCtrlMOVEEX *m = (beModelCtrlMOVEEX *)command;
            name = m->_name ? (char *)m->_name : (char *)emptyString;
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
            name = m->_name ? (char *)m->_name : (char *)emptyString;
            if (strcmp(name, JOINT) == 0) {
                igObject *trc, *old;
                beMessenger_SendNamed((beMessenger *)self->_messenger, MODELCTRL_7, (char *)m->_modelName, ram->_ramNo, GETTRCDATA);
                if (beMessenger_GetObjectCount((beMessenger *)self->_messenger) == 1) {
                    work->_isPosLock = 1;
                    trc = beMessenger_GetObject((beMessenger *)self->_messenger, 0);
                    if (trc != 0) trc->_refCount = trc->_refCount + 1;
                    old = (igObject *)work->_posLockTrc;
                    igObject::release(old);
                    work->_posLockTrc = (int)trc;
                }
            } else {
                char *modelName, *boneName;
                char *oldModelName, *oldBoneName;
                modelName = (char *)m->_modelName;
                if (g_stringPool == 0) {
                    StringPool *pool = (StringPool *)StringPool_Allocate(16);
                    if (pool != 0) pool = StringPool_Construct(pool);
                    g_stringPool = pool;
                }
                modelName = StringPool_Intern(g_stringPool, modelName);
                oldModelName = (char *)work->_posLockModelName;
                if (oldModelName != 0) {
                    int *header = (int *)(oldModelName - 8);
                    int refs = *(int *)(oldModelName - 4) - 1;
                    *(int *)(oldModelName - 4) = refs;
                    if (refs == 0) StringChunk_ReleaseHeader((StringChunk *)*header, (StringTokenHeader *)header);
                }
                work->_posLockModelName = (int)modelName;
                boneName = (char *)m->_boneName;
                if (g_stringPool == 0) {
                    StringPool *pool = (StringPool *)StringPool_Allocate(16);
                    if (pool != 0) pool = StringPool_Construct(pool);
                    g_stringPool = pool;
                }
                boneName = StringPool_Intern(g_stringPool, boneName);
                oldBoneName = (char *)work->_posLockBoneName;
                if (oldBoneName != 0) {
                    int *header = (int *)(oldBoneName - 8);
                    int refs = *(int *)(oldBoneName - 4) - 1;
                    *(int *)(oldBoneName - 4) = refs;
                    if (refs == 0) StringChunk_ReleaseHeader((StringChunk *)*header, (StringTokenHeader *)header);
                }
                work->_posLockBoneName = (int)boneName;
                work->_isPosLock = 1;
            }
        }
    }
    return 1;
}

unsigned char beModelCtrl_RunPdMove(beModelCtrl *self, beBaseInfoRam *ram, beModelCtrlInfoWork *work, beModelCtrlPDMOVE *command) {
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
                ((Gap::Core::igDataList *)list)->resizeAndSetCount(k + 1, 4);
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

static inline int intListCount(const igIntList *list) { return list->_count; }
/* Holder of the label lists created on first use; the table names its own out-of-line destructor copy. */
struct LabelListRef { igObject *p; LabelListRef() { p = 0; } ~LabelListRef() { igObject *o = p; igObject::release(o); } };

void beModelCtrlInfoWork_SetSeqLabel(beModelCtrl *self, beBaseInfoRam *ram, beModelCtrlInfoWork *work, const char *seqName, const char *labelName) {
    igStringRefList *seqList, *labelList;
    igIntList *offsetList;
    int base, allocator, idx, count, k;
    igObject *released, *created;

    seqList = (igStringRefList *)work->_labelSeqList;
    labelList = (igStringRefList *)work->_labelNameList;
    offsetList = (igIntList *)work->_labelOffsetList;
    if (seqList == 0) {
        LabelListRef listRef;
        igSmartPointer<igIntList> intListRef;
        base = (int)((Gap::Core::igObject *)self)->getMemoryPool();
        if (g_useOwnerAllocator != 0) {
            allocator = base;
        } else {
            allocator = (int)Memory_GetAllocatorBySelector(kIGMemoryPoolHandleUser1);
        }
        released = listRef.p;
        igObject::release(released);
        listRef.p = (igObject *)igStringRefList_Create(allocator);
        created = listRef.p;
        if (created != 0) created->_refCount = created->_refCount + 1;
        released = (igObject *)work->_labelSeqList;
        igObject::release(released);
        work->_labelSeqList = (int)created;
        seqList = (igStringRefList *)listRef.p;

        base = (int)((Gap::Core::igObject *)self)->getMemoryPool();
        if (g_useOwnerAllocator != 0) {
            allocator = base;
        } else {
            allocator = (int)Memory_GetAllocatorBySelector(kIGMemoryPoolHandleUser1);
        }
        released = listRef.p;
        igObject::release(released);
        listRef.p = (igObject *)igStringRefList_Create(allocator);
        created = listRef.p;
        if (created != 0) created->_refCount = created->_refCount + 1;
        released = (igObject *)work->_labelNameList;
        igObject::release(released);
        work->_labelNameList = (int)created;
        labelList = (igStringRefList *)listRef.p;

        base = (int)((Gap::Core::igObject *)self)->getMemoryPool();
        if (g_useOwnerAllocator != 0) {
            allocator = base;
        } else {
            allocator = (int)Memory_GetAllocatorBySelector(kIGMemoryPoolHandleUser1);
        }
        released = intListRef.p;
        igObject::release(released);
        intListRef.p = igIntList_Create(allocator);
        created = intListRef.p;
        if (created != 0) created->_refCount = created->_refCount + 1;
        released = (igObject *)work->_labelOffsetList;
        igObject::release(released);
        work->_labelOffsetList = (int)created;
        offsetList = (igIntList *)intListRef.p;
    }
    {
        igStringRef key((char *)seqName);
        idx = igStringRefList_IndexOf(seqList, &key.p, 0);
    }
    if (idx != -1) {
        {
        igStringRef seqToken((char *)seqName);
        count = seqList->_count;
        if (count != 0 && idx >= 0 && idx < count) {
            ((igStringRef *)seqList->_data)[idx] = seqToken;
        }
        }
        {
        igStringRef labelToken((char *)labelName);
        count = labelList->_count;
        if (count != 0 && idx >= 0 && idx < count) {
            ((igStringRef *)labelList->_data)[idx] = labelToken;
        }
        }
        count = offsetList->_count;
        if (count != 0 && idx >= 0 && idx < count) {
            ListStoreAt((int *)offsetList->_data, idx, -1);
        }
    } else {
        {
            igStringRef newSeq((char *)seqName);
            StringList_AppendRetained(seqList, &newSeq.p);
        }
        {
            igStringRef newLabel((char *)labelName);
            StringList_AppendRetained(labelList, &newLabel.p);
        }
        k = intListCount(offsetList);
        if (k < offsetList->_capacity) {
            offsetList->_count = offsetList->_count + 1;
        } else {
            ((Gap::Core::igDataList *)offsetList)->resizeAndSetCount(k + 1, 4);
        }
        ListStoreAt((int *)offsetList->_data, k, -1);
    }
}

unsigned char beModelCtrl_RunLabelCtrl(beModelCtrl *self, beBaseInfoRam *ram, beModelCtrlInfoWork *work, beModelCtrlLABELCTRL *command) {
    int *labelName = (int *)command->_name;
    labelName = labelName != 0 ? labelName : (int *)emptyString;
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
        base = (int)((Gap::Core::igObject *)ram)->getMemoryPool();
        if (g_useOwnerAllocator != 0) {
            allocator = base;
        } else {
            allocator = (int)Memory_GetAllocatorBySelector(kIGMemoryPoolHandleUser1);
        }
        igSmartPointer<igObject> created(beBaseInfoDataList_Create(allocator));
        p = created.p;
        igObject::ref(p);
        old = (igObject *)ram->_dataList;
        igObject::release(old);
        ram->_dataList = (int)p;
    }
    ramData = ((beModelCtrlInfoRamData *)((Gap::Core::igObjectList *)ram->_dataList)->search((Gap::Core::igStringMetaField *)Gap::Core::igNamedObject::k_name, ONE_3));
    work = (beModelCtrlInfoWork *)ramData->_work;
    g_mdlEntity = ram;
    g_mdlRamNo = ram->_ramNo;
    g_mdlMatrix = (float *)NodeMatrix(ramData->_node);
    g_mdlMaxHp = ((beDataObjInt *)work->_mHp)->_data;
    g_mdlHp = ((beDataObjInt *)work->_hp)->_data;
    g_mdlRecNo = work->_recNo;
    g_mdlInfoName = (const char *)infoName;
    g_mdlBulletKind = bulletKind;
    g_mdlBulletBoxNo = bulletBoxNo;
    g_hitterInfoName = (const char *)hitterName;
    g_bltShootRamNo = hitterRamNo;
    g_hitterRecNo = hitterRecNo;
    g_mdlDmgTurn[0] = 1;
    g_mdlCallName = (const char *)callName;
    hpBefore = ((beDataObjInt *)work->_hp)->_data;
    sprintf((char *)chunk, s_s_lua, function, infoName);
    beLua__RunNamedChunk((beLua *)self->_luaManager, (const char *)chunk, 0);
    hp = (beDataObjInt *)work->_hp;
    if (hpBefore == hp->_data) {
        hp->_data = g_mdlHp;
    }
}

#define SET_LUA_FUNCTION(fld) { \
    int *p; \
    token = (int *)command->_name; \
    if (token != 0) { token = (int *)token; } else { token = (int *)emptyString; } \
    if (g_stringPool == 0) { \
        StringPool *pool = (StringPool *)StringPool_Allocate(0x10); \
        if (pool != 0) pool = StringPool_Construct(pool); \
        g_stringPool = pool; \
    } \
    token = (int *)StringPool_Intern((StringPool *)g_stringPool, (const char *)token); \
    p = (int *)work->fld; \
    if (p != 0) { \
        int *hd = p - 2; \
        int c = p[-1] - 1; \
        p[-1] = c; \
        if (c == 0) StringChunk_ReleaseHeader((StringChunk *)*hd, (StringTokenHeader *)hd); \
    } \
    work->fld = (int)token; }
unsigned char beModelCtrl_RunLuaCall(beModelCtrl *self, beBaseInfo *info, beBaseInfoRam *ram, beModelCtrlInfoWork *work, beModelCtrlLUACALL *command) {
    unsigned char call;
    int *function;
    int *infoName;
    int mode;
    int *token;
    call = 0;
    mode = command->_modeName;
    if (mode == 0) {
        call = 1;
    } else if (strcmp((const char *)mode, BHit_2) == 0) {
        SET_LUA_FUNCTION(_luaBHit)
    } else if (strcmp((const char *)command->_modeName, WHit) == 0) {
        SET_LUA_FUNCTION(_luaWHit)
    } else if (strcmp((const char *)command->_modeName, FHit) == 0) {
        SET_LUA_FUNCTION(_luaFHit)
    } else {
        call = 1;
    }
    if (call) {
        infoName = (int *)info->_name;
        if (infoName != 0) { infoName = (int *)infoName; } else { infoName = (int *)emptyString; }
        mode = command->_modeName;
        function = (int *)command->_name;
        if (function != 0) { function = (int *)function; } else { function = (int *)emptyString; }
        beModelCtrl_CallLua(self, ram, (const char *)function, (const char *)mode, (const char *)infoName, 0, 0, (const char *)0, 0, 0);
    }
    return 1;
}

#undef SET_LUA_FUNCTION

unsigned char beModelCtrl_RunAiMap(beModelCtrl *self, beModelCtrlInfo *info, beBaseInfoRam *ram, beModelCtrlInfoWork *work, beModelCtrlAIMAP *command) {
    igVec3f target;
    int i;
    int count;
    int idx;
    beModelCtrlAIMapList *maps;
    int *name;
    int *infoName;
    beModelCtrlInfoAI *ai;
    beModelCtrlAIMap *map;
    maps = (beModelCtrlAIMapList *)((beModelCtrlInfoDataAIM *)((Gap::Core::igObjectList *)info->_dataList)->search((Gap::Core::igStringMetaField *)Gap::Core::igNamedObject::k_name, AIM))->_aIMapList;
    name = (int *)command->_name;
    name = name != 0 ? name : (int *)emptyString;
    map = (beModelCtrlAIMap *)((Gap::Core::igObjectList *)maps)->search((Gap::Core::igStringMetaField *)Gap::Core::igNamedObject::k_name, (const char *)name);
    beModelCtrlAIMap *key = map;
    count = maps->_count;
    for (i = 0; i < count; i++) { if (*(beModelCtrlAIMap **)&key == ((beModelCtrlAIMap **)maps->_data)[i]) { idx = i; goto found; } }
    idx = -1;
found:
    ai = (beModelCtrlInfoAI *)work->_aI;
    if (ai != 0) {
        ai->_mapNo = idx;
        if (map->_targetType != 0 && strcmp((const char *)map->_targetType, WPOS) == 0) {
            g_mdlWorldPosTarget = (float *)&target;
            infoName = (int *)info->_name;
            infoName = infoName != 0 ? infoName : (int *)emptyString;
            beModelCtrl_CallLua(self, ram, (const char *)aim, (const char *)WPos, (const char *)infoName, 0, 0, (const char *)0, 0, 0);
            { beModelCtrlInfoAI *ai2 = (beModelCtrlInfoAI *)work->_aI; ai2->_worldPos[0] = target[0]; ai2->_worldPos[1] = target[1]; ai2->_worldPos[2] = target[2]; }
            g_mdlWorldPosTarget = 0;
        }
    }
    beBaseInfoRam_RemoveTimer(ram, AITIMER);
    return 1;
}

unsigned char beModelCtrl_RunMsgBox(beModelCtrl *self, beModelCtrlInfo *info, beModelCtrlInfoWork *work, beModelCtrlMSGBOX *command)
{
    return 1;
}

unsigned char beModelCtrl_RunJump(beModelCtrl *self, beBaseInfoRam *ram, beModelCtrlJUMP *command) {
    int *sequence;

    sequence = (int *)(command->_name);
    sequence = sequence ? sequence : (int *)emptyString;
    ((beModelCtrlDispatchView *)self)->OnMessageText(ram, (const char *)sequence);
    return 1;
}

unsigned char beModelCtrl_StartWaitCheck(beModelCtrl *self, beModelCtrlInfoWork *work, beModelCtrlWCHECK *command) {
    int *name;
    int *header;
    int refs;
    int pool;
    void *token;
    char *old;
    name = (int *)command->_name;
    name = name != 0 ? name : (int *)(emptyString);
    if (g_stringPool == 0) {
        pool = (int)StringPool_Allocate(0x10);
        if (pool != 0) {
            pool = (int)StringPool_Construct((StringPool *)pool);
        }
        g_stringPool = (StringPool *)pool;
    }
    token = (void *)StringPool_Intern(g_stringPool, (const char *)name);
    old = (char *)work->_wCheckName;
    if (old != 0) {
        header = (int *)(old - 8);
        refs = *(int *)(old - 4) - 1;
        *(int *)(old - 4) = refs;
        if (refs == 0) {
            StringChunk_ReleaseHeader((StringChunk *)*header, (StringTokenHeader *)header);
        }
    }
    work->_wCheckName = (int)token;
    return 0;
}

#define END_WAIT() do { \
    int v; int token; int old; int *hd; \
    if (g_stringPool == 0) { v = (int)StringPool_Allocate(16); if (v != 0) v = (int)StringPool_Construct((StringPool *)v); g_stringPool = (StringPool *)v; } \
    token = ((int)StringPool_Intern((StringPool *)g_stringPool, 0)); \
    old = work->_wCheckName; \
    if (old != 0) { hd = (int *)(old - 8); v = *(int *)(old - 4) - 1; *(int *)(old - 4) = v; if (v == 0) StringChunk_ReleaseHeader((StringChunk *)*hd, (StringTokenHeader *)hd); } \
    work->_wCheckName = token; \
    beModelCtrl_RunCommands(self, info, ram, work); \
} while (0)
void beModelCtrl_UpdateWaitCheck(beModelCtrl *self, beModelCtrlInfo *info, beBaseInfoRam *ram, beModelCtrlInfoWork *work) {
    if (strcmp((const char *)work->_wCheckName, TurnY) == 0 || strcmp((const char *)work->_wCheckName, Landing) == 0) {
        if (beModelCtrl_QueryMove(self, ram, work, 2) == 0) {
            END_WAIT();
        }
    } else if (strcmp((const char *)work->_wCheckName, Action) == 0) {
        int name = info->_name;
        int ramNo = ram->_ramNo;
        name = name ? name : (int)emptyString;
        beMessenger_SendNamed((beMessenger *)self->_messenger, ACTION_2, (const char *)name, ramNo, ISCOMEND);
        if (beMessenger_GetBool((beMessenger *)self->_messenger, 0)) {
            END_WAIT();
        }
    } else if (strcmp((const char *)work->_wCheckName, Moving) == 0) {
        if (beModelCtrl_QueryMove(self, ram, work, 0) == 0) {
            END_WAIT();
        }
    } else if (strcmp((const char *)work->_wCheckName, Rotation) == 0) {
        if (beModelCtrl_QueryMove(self, ram, work, 1) == 0) {
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

unsigned char beModelCtrl_RunHitBox(beModelCtrl *self, beBaseInfoRam *ram, beModelCtrlInfoWork *work, beModelCtrlHITBOX *command) {
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
        beModelCtrlSubCom_StopType((beModelCtrlSubCom *)work->_subCommand, (beBaseInfoRam *)ram, g_beModelCtrlSCHitBox_metaObject);
    } else {
        name = (char *)command->_name;
        if (name != 0) {
            mode2 = name;
        } else {
            mode2 = ((char *)emptyString);
        }
        if (strcmp(mode2, Set) == 0) {
            beModelCtrlSubCom_AddHitBox((beModelCtrlSubCom *)work->_subCommand, command);
        }
    }
    return 1;
}

unsigned char beModelCtrl_RunMuteki(beModelCtrl *self, beBaseInfoRam *ram, beModelCtrlInfoWork *work, beModelCtrlMUTEKI *command) {
    if (beBaseInfoRam_HasTimer(ram, KEIKATIMER) == 0) { beBaseInfoRam_StartTimer(ram, KEIKATIMER, 0); }
    if (strcmp((const char *)(MutekiNameOf::Get(command)), OFFWALL) == 0) { work->_isWallCheck = 0; }
    else if (strcmp((const char *)(MutekiNameOf::Get(command)), ONWALL) == 0) { work->_isWallCheck = 1; }
    else if (strcmp((const char *)(MutekiNameOf::Get(command)), OFFFLOOR) == 0) { work->_isFloorCheck = 0; }
    else if (strcmp((const char *)(MutekiNameOf::Get(command)), ONFLOOR) == 0) { work->_isFloorCheck = 1; }
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
            if (Gap::Bec::beModelCtrlCTRL::getClassMeta() == command->GetMeta()) {
                next = beModelCtrl_RunCtrl(self, work, (beModelCtrlCTRL *)command);
                index += 1;
            } else if (Gap::Bec::beModelCtrlACTION::getClassMeta() == command->GetMeta()) {
                next = beModelCtrl_RunAction(self, info, ram, (beModelCtrlACTION *)command);
                index += 1;
            } else if (Gap::Bec::beModelCtrlMOVE::getClassMeta() == command->GetMeta()) {
                next = beModelCtrl_RunMove(self, ram, work, (igObject *)command);
                index += 1;
            } else if (Gap::Bec::beModelCtrlMOVEEX::getClassMeta() == command->GetMeta()) {
                next = beModelCtrl_RunMove(self, ram, work, (igObject *)command);
                index += 1;
            } else if (Gap::Bec::beModelCtrlMOVERL::getClassMeta() == command->GetMeta()) {
                next = beModelCtrl_RunMove(self, ram, work, (igObject *)command);
                index += 1;
            } else if (Gap::Bec::beModelCtrlPDMOVE::getClassMeta() == command->GetMeta()) {
                next = beModelCtrl_RunPdMove(self, ram, work, (beModelCtrlPDMOVE *)command);
                index += 1;
            } else if (Gap::Bec::beModelCtrlWCHECK::getClassMeta() == command->GetMeta()) {
                next = beModelCtrl_StartWaitCheck(self, work, (beModelCtrlWCHECK *)command);
                index += 1;
            } else if (Gap::Bec::beModelCtrlHITBOX::getClassMeta() == command->GetMeta()) {
                next = beModelCtrl_RunHitBox(self, ram, work, (beModelCtrlHITBOX *)command);
                index += 1;
            } else if (Gap::Bec::beModelCtrlMUTEKI::getClassMeta() == command->GetMeta()) {
                next = beModelCtrl_RunMuteki(self, ram, work, (beModelCtrlMUTEKI *)command);
                index += 1;
            } else if (Gap::Bec::beModelCtrlLABELCTRL::getClassMeta() == command->GetMeta()) {
                next = beModelCtrl_RunLabelCtrl(self, ram, work, (beModelCtrlLABELCTRL *)command);
                index += 1;
            } else if (Gap::Bec::beModelCtrlLUACALL::getClassMeta() == command->GetMeta()) {
                next = beModelCtrl_RunLuaCall(self, (beBaseInfo *)info, ram, work, (beModelCtrlLUACALL *)command);
                index += 1;
            } else if (g_beModelCtrlAIMAP_metaObject == command->GetMeta()) {
                next = beModelCtrl_RunAiMap(self, info, ram, work, (beModelCtrlAIMAP *)command);
                index += 1;
            } else if (Gap::Bec::beModelCtrlMSGBOX::getClassMeta() == command->GetMeta()) {
                next = beModelCtrl_RunMsgBox(self, info, work, (beModelCtrlMSGBOX *)command);
                index += 1;
            } else if (Gap::Bec::beModelCtrlLABEL::getClassMeta() == command->GetMeta()) {
                if (work->_comLabelCount != 0) {
                    next = 0;
                } else {
                    work->_comLabelCount = 1;
                    index += 1;
                }
            } else if (Gap::Bec::beModelCtrlJUMP::getClassMeta() == command->GetMeta()) {
                jumped = beModelCtrl_RunJump(self, ram, (beModelCtrlJUMP *)command);
            }
        } while (jumped == 0 && next != 0 && index != ((igObjectList *)commands->_comList)->_count);
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
        diff = rotation != *(const igVec3f *)direction;
        if (!diff) goto done;
    }
    if (((igObject *)ram->_dataList) == 0) {
        int base = (int)((Gap::Core::igObject *)ram)->getMemoryPool();
        int allocator;
        if (g_useOwnerAllocator != 0) allocator = base; else allocator = (int)Memory_GetAllocatorBySelector(kIGMemoryPoolHandleUser1);
        igSmartPointer<igObject> created(((igObject *)beBaseInfoDataList_Create(allocator)));
        igObject *list = (igObject *)created.p;
        if (list != 0) list->_refCount = list->_refCount + 1;
        igObject *old = ((igObject *)ram->_dataList);
        igObject::release(old);
        ram->_dataList = (int)list;
    }
    matrix = (int)NodeMatrix(((beModelCtrlInfoRamData *)((Gap::Core::igObjectList *)((igObject *)ram->_dataList))->search((Gap::Core::igStringMetaField *)Gap::Core::igNamedObject::k_name, ONE_3))->_node);
    igMatrix44f_GetTranslation((const float *)matrix, translation);
    igMatrix44f_MakeEulerRotation((void *)matrix, rotation[0], ((float*)&rotation)[1], ((float*)&rotation)[2]);
    igMatrix44f_SetTranslation((float *)matrix, (const float *)translation);
    work->_direction[0] = rotation[0];
    work->_direction[1] = rotation[1];
    work->_direction[2] = rotation[2];
done:
    return;
pre:
    current = (float *)&work->_direction[0];
    offset = 0;
    next = rotation.vec;
    goto test;
}

/* Owning stack reference to the freshly created data list; released on scope exit (reference count
 * in the low 23 bits of _refCount). */

void beModelCtrl_UpdateRam(beModelCtrl *self, beBaseInfoRam *ram) {
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
        int allocator = (int)((Gap::Core::igObject *)ram)->getMemoryPool();
        int chosen;
        if (g_useOwnerAllocator != 0) { chosen = allocator; } else { chosen = (int)Memory_GetAllocatorBySelector(kIGMemoryPoolHandleUser1); }
        DataListInstall::make(ram, chosen);
    }
    beModelCtrlInfoRamData *ramData = (beModelCtrlInfoRamData *)((Gap::Core::igObjectList *)ram->_dataList)->search((Gap::Core::igStringMetaField *)Gap::Core::igNamedObject::k_name, ONE_3);
    beModelCtrlInfoWork *work = (beModelCtrlInfoWork *)ramData->_work;
    if (ram->_isRun != 0 && work->_isOnFreeze == 0) {
        int token;
        int posNode;
        beModelCtrlInfoRideOn4 *rideOn;
        if (strcmp((const char *)work->_seqCodeName, SQ_ERAS_2) == 0) {
            ((beModelCtrlDispatchView *)self)->OnMessageText(ram, REMOVE_2);
            return;
        }
        work->_keyInput = 0;
        if (g_stringPool == 0) {
            StringPool *pool = (StringPool *)StringPool_Allocate(16);
            if (pool != 0) pool = StringPool_Construct(pool);
            g_stringPool = pool;
        }
        token = ((int)StringPool_Intern(g_stringPool, SQ_NONE));
        if (work->_keyEventName != 0) {
            int *header = (int *)(work->_keyEventName - 8);
            int refs = *(int *)(work->_keyEventName - 4) - 1;
            *(int *)(work->_keyEventName - 4) = refs;
            if (refs == 0) StringChunk_ReleaseHeader((StringChunk *)*header, (StringTokenHeader *)header);
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
                igMatrix44f_TranslateLocal(lockMatrix, work->_posLockOffset);
                ((igTransformDispatchView *)ramData->_node)->SetMatrix(lockMatrix);
            } else if (work->_posLockTrc != 0) {
                ((igTransformDispatchView *)ramData->_node)->SetMatrix((float *)(*(int *)(work->_posLockTrc + 16) + g_igTransformRecorder_mMetaField->_offset));
            } else if (work->_posLockModelName != 0) {
                beMessenger_SelectReceivers((beMessenger *)self->_messenger, ACTION_2, (const char *)work->_posLockModelName, ram->_ramNo);
                beMessenger_AppendString((beMessenger *)self->_messenger, (const char *)work->_posLockBoneName);
                beMessenger_DispatchSelected((beMessenger *)self->_messenger, GETBONEMATRIX);
                if (beMessenger_GetMatrixCount((beMessenger *)self->_messenger) == 1) {
                    beMessenger_GetMatrix(boneMatrix, (beMessenger *)self->_messenger, 0);
                    beMessenger_SendNamed((beMessenger *)self->_messenger, MODELCTRL_7, (const char *)work->_posLockModelName, ram->_ramNo, GETMATRIX_2);
                    if (beMessenger_GetMatrixCount((beMessenger *)self->_messenger) == 1) {
                        beMessenger_GetMatrix(modelMatrix, (beMessenger *)self->_messenger, 0);
                        igMatrix44f_PreMultiply(modelMatrix, (const float *)boneMatrix);
                        ((igTransformDispatchView *)ramData->_node)->SetMatrix(modelMatrix);
                    }
                }
            }
            if (work->_baseAABox != 0) beModelCtrl_UpdateBound(self, (beModelCtrlNode2 *)ramData->_node, (igAABox *)work->_baseAABox);
        }
        rideOn = (beModelCtrlInfoRideOn4 *)work->_rideOnData;
        if (rideOn != 0) {
            ((beModelCtrlInfoRideOnDispatchView *)rideOn)->Move(NodeMatrix(ramData->_node));
            igMatrix44f_GetTranslation((const float *)rideOn->_oldMatrix, (float *)oldPos);
            igMatrix44f_GetTranslation((const float *)NodeMatrix(ramData->_node), newPos);
            delta[0] = newPos[0] - oldPos[0];
            delta[1] = newPos[1] - oldPos[1];
            delta[2] = newPos[2] - oldPos[2];
            igMatrix44f_Copy((float *)oldRotation, rideOn->_oldMatrix);
            igMatrix44f_Copy((float *)offset, (const float *)NodeMatrix(ramData->_node));
            igMatrix44f_SetTranslation((float *)oldRotation, g_vec3Zero.vec);
            igMatrix44f_Invert((float *)oldRotation, (const float *)oldRotation);
            igMatrix44f_SetTranslation((float *)offset, (const float *)delta);
            igMatrix44f_SetIdentity((float *)local);
            igMatrix44f_Multiply((float *)local, (const float *)offset, (const float *)oldRotation);
            igMatrix44f_SetIdentity(world);
            igMatrix44f_Multiply(world, (const float *)local, (const float *)NodeMatrix(rideOn->_modelNode));
            ((igTransformDispatchView *)ramData->_node)->SetMatrix(world);
            igMatrix44f_Copy(rideOn->_oldMatrix, NodeMatrix(rideOn->_modelNode));
            work->_isHitCheck = 1;
        }
        if (work->_wCheckName != 0) beModelCtrl_UpdateWaitCheck(self, (beModelCtrlInfo *)info, ram, work);
        beModelCtrl_UpdateMuteki(self, ram, work);
        beModelCtrlSubCom_Update((beModelCtrlSubCom *)work->_subCommand, ram);
        if (work->_isHitCheck != 0) beModelCtrl_CheckWallAndFloor(self, info, ram, work);
        rideOn = (beModelCtrlInfoRideOn4 *)work->_rideOnData;
        if (rideOn != 0 && rideOn->_modelRamNo == 0x68) {
            igMatrix44f_GetTranslation((const float *)NodeMatrix(ramData->_node), pos);
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
        int slot;
        {
            igStringRef key((char *)work->_seqCodeName);
            slot = igStringRefList_IndexOf((igStringRefList *)work->_labelSeqList, &key.p, 0);
        }
        if (slot != -1) {
            index = ((int *)((igIntList *)work->_labelOffsetList)->_data)[slot];
            if (index == -1) {
                int labelName;
                beModelCtrlData *commands;
                int count, i;
                /* the copied token is a temporary: only the pointer outlives it (the list keeps its share) */
                labelName = (int)StringList_CopyRetained((igStringRefList *)work->_labelNameList, slot).p;
                commands = (beModelCtrlData *)work->_comData;
                count = ((igObjectList *)commands->_comList)->_count;
                for (i = 0; i < count; i++) {
                    beModelCtrlLABEL *label = (beModelCtrlLABEL *)((int *)((igObjectList *)commands->_comList)->_data)[i];
                    if (Gap::Bec::beModelCtrlLABEL::getClassMeta() == ((igObjectDispatchView *)label)->GetMeta()) {
                        if (strcmp(label->_name != 0 ? (const char *)label->_name : emptyString, (const char *)labelName) == 0) {
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
        allocator = (int)((Gap::Core::igObject *)ram)->getMemoryPool();
        allocator = g_useOwnerAllocator ? allocator : (int)Memory_GetAllocatorBySelector(kIGMemoryPoolHandleUser1);
        {
            igSmartPointer<igObject> ref(beBaseInfoDataList_Create(allocator));
            created = ref.p;
            igObject::ref(created);
            old = (igObject *)ram->_dataList;
            igObject::release(old);
            ram->_dataList = (int)created;
        }
    }
    ramData = (beModelCtrlInfoRamData *)((Gap::Core::igObjectList *)ram->_dataList)->search((Gap::Core::igStringMetaField *)Gap::Core::igNamedObject::k_name, ONE_3);
    work = (beModelCtrlInfoWork *)ramData->_work;
    if (beMessenger_GetStringCount((beMessenger *)self->_messenger) == 0) return;
    if (beMessenger_GetStringCount((beMessenger *)self->_messenger) == 1) return;
    parentName = (char *)beMessenger_GetString((beMessenger *)self->_messenger, 0);
    parentRamNo = beMessenger_GetInt((beMessenger *)self->_messenger, 0);
    igVec3f offset = beMessenger_GetVec3((beMessenger *)self->_messenger, 0);
    igVec3f rotation = beMessenger_GetVec3Count((beMessenger *)self->_messenger) == 2
        ? beMessenger_GetVec3((beMessenger *)self->_messenger, 1) : g_vec3Zero;
    posLock = beMessenger_GetBool((beMessenger *)self->_messenger, 0);
    hitParentName = (char *)beMessenger_GetString((beMessenger *)self->_messenger, 2);
    {
        char *token;
        char *oldName;
        if (g_stringPool == 0) {
            StringPool *pool = (StringPool *)StringPool_Allocate(16);
            if (pool != 0) pool = StringPool_Construct(pool);
            g_stringPool = pool;
        }
        token = StringPool_Intern(g_stringPool, hitParentName);
        oldName = (char *)work->_hitParentName;
        if (oldName != 0) {
            int *header = (int *)(oldName - 8);
            int refs = *(int *)(oldName - 4) - 1;
            *(int *)(oldName - 4) = refs;
            if (refs == 0) StringChunk_ReleaseHeader((StringChunk *)*header, (StringTokenHeader *)header);
        }
        work->_hitParentName = (int)token;
    }
    work->_hitParentRamNo = beMessenger_GetInt((beMessenger *)self->_messenger, 1);
    beMessenger_SendNamed((beMessenger *)self->_messenger, MODELCTRL_7, parentName, parentRamNo, GETMATRIX_2);
    if (posLock) {
        igObject *node = beMessenger_GetObject((beMessenger *)self->_messenger, 0);
        igObject *oldNode;
        igObject::ref(node);
        oldNode = (igObject *)work->_posLockNode;
        igObject::release(oldNode);
        work->_posLockNode = (int)node;
        work->_posLockOffset[0] = offset[0];
        work->_posLockOffset[1] = offset[1];
        work->_posLockOffset[2] = offset[2];
        work->_isPosLock = 1;
    }
    igMatrix44f_SetIdentity(matrix);
    beMessenger_GetMatrix(parentMatrix, (beMessenger *)self->_messenger, 0);
    igMatrix44f_Copy(matrix, parentMatrix);
    igMatrix44f_TranslateLocal(matrix, offset);
    if (rotation[0] != 0.0f) igMatrix44f_PreRotateAxisAngle(matrix, g_vec3XAxis.vec, rotation[0]);
    if (rotation[1] != 0.0f) igMatrix44f_PreRotateAxisAngle(matrix, g_vec3YAxis.vec, rotation[1]);
    if (rotation[2] != 0.0f) igMatrix44f_PreRotateAxisAngle(matrix, (float *)&g_vec3ZAxis, rotation[2]);
    ((igTransformDispatchView *)ramData->_node)->SetMatrix(matrix);
    work->_aIHOffsetY = offset[1];
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
        allocator = (int)((Gap::Core::igObject *)ram)->getMemoryPool();
        allocator = g_useOwnerAllocator ? allocator : (int)Memory_GetAllocatorBySelector(kIGMemoryPoolHandleUser1);
        {
            igSmartPointer<igObject> ref(beBaseInfoDataList_Create(allocator));
            created = ref.p;
            igObject::ref(created);
            old = (igObject *)ram->_dataList;
            igObject::release(old);
            ram->_dataList = (int)created;
        }
    }
    ramData = (beModelCtrlInfoRamData *)((Gap::Core::igObjectList *)ram->_dataList)->search((Gap::Core::igStringMetaField *)Gap::Core::igNamedObject::k_name, ONE_3);
    if (beMessenger_GetVec3Count((beMessenger *)self->_messenger) != 0) {
        igMatrix44f_Copy(matrix, NodeMatrix(ramData->_node));
        igMatrix44f_SetTranslation(matrix, beMessenger_GetVec3((beMessenger *)self->_messenger, 0).vec);
        if (beMessenger_GetVec3Count((beMessenger *)self->_messenger) == 2) {
            igVec3f rotation = beMessenger_GetVec3((beMessenger *)self->_messenger, 1);
            igMatrix44f_SetEulerRotation(matrix, 0.017453292f * Component(rotation, 0), 0.017453292f * Component(rotation, 1), 0.017453292f * Component(rotation, 2));
        }
        ((igTransformDispatchView *)ramData->_node)->SetMatrix(matrix);
        return;
    }
    if (beMessenger_GetMatrixCount((beMessenger *)self->_messenger) != 0) {
        beMessenger_GetMatrix(given, (beMessenger *)self->_messenger, 0);
        ((igTransformDispatchView *)ramData->_node)->SetMatrix(given);
    }
}

/* Owning stack reference to the freshly created bound box; released on scope exit once the node
 * holds its own reference (reference count in the low 23 bits of _refCount). */

void beModelCtrl_UpdateBound(beModelCtrl *self, beModelCtrlNode2 *node, igAABox *box) {
    igAABox *bound;
    bound = (igAABox *)node->_bound;
    if (bound == 0) {
        int base = (int)((Gap::Core::igObject *)self)->getMemoryPool();
        int allocator;
        if (g_useOwnerAllocator != 0) {
            allocator = base;
        } else {
            allocator = (int)Memory_GetAllocatorBySelector(kIGMemoryPoolHandleUser1);
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

#define ALLOCATOR(a, o) int a = (int)((Gap::Core::igObject *)(o))->getMemoryPool(); a = g_useOwnerAllocator ? a : (int)Memory_GetAllocatorBySelector(kIGMemoryPoolHandleUser1);
#define POOL() if (g_stringPool == 0) { StringPool *pl_ = (StringPool *)StringPool_Allocate(0x10); if (pl_ != 0) pl_ = StringPool_Construct(pl_); g_stringPool = pl_; }
#define RELEASE_STRING(old) if (old) { int *h_ = (int *)old - 2; int c_ = ((int *)old)[-1] - 1; ((int *)old)[-1] = c_; if (c_ == 0) StringChunk_ReleaseHeader((StringChunk *)*h_, (StringTokenHeader *)h_); }
#define SET_WORK_STRING(fld, txt) { POOL() const char *tk_ = ((const char *)StringPool_Intern(g_stringPool, (const char *)txt)); const char *old_ = (const char *)work->fld; RELEASE_STRING(old_) work->fld = (int)tk_; }
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
    beModelCtrlInfoRamData *ramData = (beModelCtrlInfoRamData *)((beBaseInfoData *)((Gap::Core::igObjectList *)ram->_dataList)->search((Gap::Core::igStringMetaField *)Gap::Core::igNamedObject::k_name, ONE_3));
    beModelCtrlInfoWork *work = (beModelCtrlInfoWork *)ramData->_work;
    if (((beModelCtrlDispatchView *)self)->OnPreMessage(ram, message) == 1) return 1;
    unsigned sel = beMessenger_ResolveEnumValue((beMessenger *)MESSENGER, beModelCtrl_GetMessageEnum(), message);
    switch (sel) {
    case MSG_GENERATE: {
        igStringRef sequence;
        ram->_isRun = 1;
        ram->_st0 = 0; ram->_st3 = 0; ram->_st2 = 0; ram->_st1 = 0;
        if (beMessenger_GetStringCount((beMessenger *)MESSENGER) == 1) {
            sequence = (char *)beMessenger_GetString((beMessenger *)MESSENGER, 0);
        } else if (beMessenger_GetStringCount((beMessenger *)MESSENGER) >= 2) {
            sequence = (char *)beMessenger_GetString((beMessenger *)MESSENGER, 1);
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
        Vec3f_TransformDirection((float *)&startForward, g_vec3ZAxis.vec, MODEL_NODE->_m);
        float ang = atan2f(startForward[0], startForward[2]);
        started->_direction[1] = ang;
        started->_targetDirection[1] = ang;
        if (((beBaseInfoData *)((Gap::Core::igObjectList *)info->_dataList)->search((Gap::Core::igStringMetaField *)Gap::Core::igNamedObject::k_name, AIM)) != 0 ||
            ((beBaseInfoData *)((Gap::Core::igObjectList *)info->_dataList)->search((Gap::Core::igStringMetaField *)Gap::Core::igNamedObject::k_name, AIH)) != 0) {
            ALLOCATOR(a, self)
            ObjRef<0> r((igObject *)Gap::Bec::beModelCtrlInfoAI::_instantiateFromPool((igMemoryPoolView *)a));
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
            beMessenger_PushArgContext((beMessenger *)MESSENGER);
            int id = ram->_ramNo;
            INFO_NAME(n)
            beMessenger_SendNamed((beMessenger *)MESSENGER, ((char *)ACTION_2), n, id, NDSP_2);
            if (work != 0) beModelCtrlSubCom_StopAll((beModelCtrlSubCom *)work->_subCommand, ram);
            RELEASE(ramData->_work)
            ramData->_work = 0;
            beModelCtrlNode2 *modelNode = MODEL_NODE;
            RELEASE(modelNode->_bound)
            modelNode->_bound = 0;
            beBaseInfoRam_RemoveAllTimers(ram);
            ram->_isRun = 0;
            beMessenger_PopArgContext((beMessenger *)MESSENGER);
        }
        return 1;
    case MSG_ISRUN: {
        unsigned char f = ram->_isRun;
        beMessenger_AppendBool((beMessenger *)MESSENGER, f);
        return 1;
    }
    case MSG_ISSEQNAME:
        if (ram->_isRun == 0) {
            beMessenger_AppendBool((beMessenger *)MESSENGER, 0);
        } else if (work == 0) {
            beMessenger_AppendBool((beMessenger *)MESSENGER, 0);
        } else if (strcmp((const char *)work->_seqCodeName, beMessenger_GetString((beMessenger *)MESSENGER, 0)) == 0) {
            beMessenger_AppendBool((beMessenger *)MESSENGER, 1);
        } else {
            beMessenger_AppendBool((beMessenger *)MESSENGER, 0);
        }
        return 1;
    case MSG_SETEFFECT:
        if (ram->_isRun != 0 && work != 0) {
            beModelCtrlSubCom_AddEffect(SubCommands(work), beMessenger_GetString((beMessenger *)MESSENGER, 0), beMessenger_GetString((beMessenger *)MESSENGER, 1),
                beMessenger_GetFloat((beMessenger *)MESSENGER, 0), beMessenger_GetVec3((beMessenger *)MESSENGER, 0),
                beMessenger_GetVec3Count((beMessenger *)MESSENGER) == 2 ? beMessenger_GetVec3((beMessenger *)MESSENGER, 1) : g_vec3Zero,
                beMessenger_GetBool((beMessenger *)MESSENGER, 0), beMessenger_GetBool((beMessenger *)MESSENGER, 1));
        }
        return 1;
    case MSG_SETSOUND:
        if (ram->_isRun != 0 && work != 0) {
            int sub = work->_subCommand;
            const char *s0 = beMessenger_GetString((beMessenger *)MESSENGER, 0);
            beModelCtrlSubCom_AddSound((beModelCtrlSubCom *)sub, s0, beMessenger_GetFloat((beMessenger *)MESSENGER, 0));
        }
        return 1;
    case MSG_GETSEQNAMELIST: {
        beModelCtrlInfoDataSeq *seq = (beModelCtrlInfoDataSeq *)((beBaseInfoData *)((Gap::Core::igObjectList *)info->_dataList)->search((Gap::Core::igStringMetaField *)Gap::Core::igNamedObject::k_name, SEQ));
        igObjectList *l = (igObjectList *)seq->_dataList;
        int n = l->_count;
        beMessenger_AppendString((beMessenger *)MESSENGER, ((char *)SQ_ERAS_2));
        int i;
        for (i = 0; i < n; i++) {
            beModelCtrlData *entry = (beModelCtrlData *)((void **)l->_data)[i];
            const char *b;
            const char *a_ = (const char *)entry->_name;
            if (a_ != 0) b = a_; else b = ((char *)emptyString);
            beMessenger_AppendString((beMessenger *)MESSENGER, b);
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
        beMessenger_AppendString((beMessenger *)MESSENGER, n);
        return 1;
    }
    case MSG_GETINFONAME_RUN:
        if (ram->_isRun != 0) {
            INFO_NAME(n)
            beMessenger_AppendString((beMessenger *)MESSENGER, n);
        }
        return 1;
    case MSG_SETMATRIX:
        if (ram->_isRun != 0 && work != 0 && beMessenger_GetMatrixCount((beMessenger *)MESSENGER) != 0) {
            beMessenger_GetMatrix(setMatrix, (beMessenger *)MESSENGER, 0);
            ((igTransformDispatchView *)ramData->_node)->SetMatrix(setMatrix);
            if (work != 0) {
                Vec3f_TransformDirection((float *)&setForward, g_vec3ZAxis.vec, setMatrix);
                float ang = atan2f(setForward[0], setForward[2]);
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
        beMessenger_AppendInt((beMessenger *)MESSENGER, ram->_ramNo);
        beMessenger_AppendMatrix((beMessenger *)MESSENGER, MODEL_NODE->_m);
        beMessenger_AppendObject((beMessenger *)MESSENGER, (igObject *)MODEL_NODE);
        return 1;
    case MSG_GETMATRIX_ACTIVE:
        if (ram->_isRun != 0 && work != 0 && work->_mutekiCount == 0.0f)
            beMessenger_AppendMatrix((beMessenger *)MESSENGER, MODEL_NODE->_m);
        return 1;
    case MSG_GETTRCDATA:
        if (ram->_isRun != 0) {
            ENSURE_DATA_LIST(ram)
            beBaseInfoData *t = ((beBaseInfoData *)((Gap::Core::igObjectList *)ram->_dataList)->search((Gap::Core::igStringMetaField *)Gap::Core::igNamedObject::k_name, TRC));
            if (t != 0) beMessenger_AppendObject((beMessenger *)MESSENGER, (igObject *)t);
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
            beMessenger_SendNamed((beMessenger *)MESSENGER, ((char *)ACTION_2), n, id, ONFREEZE);
            work->_isOnFreeze = 1;
            ((beModelCtrlDispatchView *)self)->OnFreeze(ram);
        }
        return 1;
    case MSG_OFFREEZE:
        if (ram->_isRun != 0 && work != 0) {
            beBaseInfoRam_SetAllTimerScales(ram, 1.0f);
            int id = ram->_ramNo;
            INFO_NAME(n)
            beMessenger_SendNamed((beMessenger *)MESSENGER, ((char *)ACTION_2), n, id, OFFREEZE);
            work->_isOnFreeze = 0;
        }
        return 1;
    case MSG_SETLODHIGH:
        if (ram->_isRun != 0 && work != 0 && work->_svLODHighRange == -1.0f) {
            igMetaObject *t = Gap::Sg::igLod::getClassMeta();
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
            igVec3f movePosition = beMessenger_GetVec3((beMessenger *)MESSENGER, 0);
            igVec3f moveRotation = beMessenger_GetVec3((beMessenger *)MESSENGER, 1);
            igMatrix44f_SetIdentity(moveMatrix);
            igMatrix44f_FromTranslation(moveMatrix, movePosition);
            if (moveRotation[0] != 0.0f) igMatrix44f_PreRotateAxisAngle(moveMatrix, g_vec3XAxis.vec, 0.017453292f * moveRotation[0]);
            if (moveRotation[1] != 0.0f) igMatrix44f_PreRotateAxisAngle(moveMatrix, g_vec3YAxis.vec, 0.017453292f * moveRotation[1]);
            { float rz = moveRotation[2]; if (rz != 0.0f) igMatrix44f_PreRotateAxisAngle(moveMatrix, (float *)&g_vec3ZAxis, 0.017453292f * rz); }
            ((igTransformDispatchView *)ramData->_node)->SetMatrix(moveMatrix);
            work->_targetDirection[1] = 0.017453292f * moveRotation[1];
            beModelCtrl_UpdateDirection(self, info, ram, work, 1);
            igObject *a2 = (igObject *)work->_baseAABox;
            if (a2 != 0) beModelCtrl_UpdateBound(self, MODEL_NODE, (igAABox *)a2);
        }
        return 1;
    case MSG_SETLABEL:
        if (ram->_isRun != 0 && work != 0) {
            const char *s1 = beMessenger_GetString((beMessenger *)MESSENGER, 0);
            beModelCtrlInfoWork_SetSeqLabel(self, ram, work, s1, beMessenger_GetString((beMessenger *)MESSENGER, 1));
        }
        return 1;
    case MSG_GETHP:
        if (ram->_isRun == 0) {
            beMessenger_AppendInt((beMessenger *)MESSENGER, 0);
        } else if (work == 0) {
            beMessenger_AppendInt((beMessenger *)MESSENGER, 0);
        } else {
            beMessenger_AppendInt((beMessenger *)MESSENGER, ((beDataObjInt *)work->_hp)->_data);
            beMessenger_AppendObject((beMessenger *)MESSENGER, (igObject *)work->_hp);
            beMessenger_AppendObject((beMessenger *)MESSENGER, (igObject *)work->_mHp);
        }
        return 1;
    case MSG_SETHP:
        if (ram->_isRun != 0 && work != 0) {
            int v = beMessenger_GetInt((beMessenger *)MESSENGER, 0);
            ((beDataObjInt *)work->_hp)->_data = v;
            beDataObjInt *mHp = (beDataObjInt *)work->_mHp;
            if (mHp->_data < v) mHp->_data = v;
        }
        return 1;
    case MSG_GETRECNO:
        if (ram->_isRun != 0 && work != 0) beMessenger_AppendInt((beMessenger *)MESSENGER, work->_recNo);
        return 1;
    case MSG_CHKBULLET:
        if (work->_mutekiCount != 0.0f) {
            unsigned char ok = 0;
            INFO_NAME(n)
            if (*n == 0x70 && *beMessenger_GetString((beMessenger *)MESSENGER, 0) == 0x70 && work->_hp != 0) ok = 1;
            if (!(ok & 0xFF)) return 1;
        }
        if (work->_isOnCtrl == 0 || strcmp((const char *)work->_seqCodeName, ((char *)SQ_ERAS_2)) == 0) return 1;
        {
            igObject *hitbody = (igObject *)work->_hitBody;
            if (hitbody == 0) {
                ALLOCATOR(a, self)
                ObjRef<1> r((igObject *)Gap::Bec::beModelCtrlInfoHitBody::_instantiateFromPool((igMemoryPoolView *)a));
                igObject *s = r.p;
                RETAIN(s)
                RELEASE(work->_hitBody)
                work->_hitBody = (int)s;
                hitbody = r.p;
            }
            bullet = ((int)beMessenger_GetObject((beMessenger *)MESSENGER, 0));
            boxes = ((igObjectList *)beModelCtrlInfoHitBody_GetAABoxList((beModelCtrlInfoHitBody *)hitbody, ram, (int)MODEL_NODE->_m, ((igInsightCore *)self->_insight)->_worldTime));
            unsigned char found = 0;
            int idx = 0;
            int cnt = boxes->_count;
            for (idx = 0; idx < cnt; idx++) {
                if (!igAABox_IntersectBox((const igAABox *)(((void **)boxes->_data)[idx]), (const igAABox *)bullet)) continue;
                {
                    hitBox = idx;
                    found = 1;
                    break;
                }
            }
            if (found) {
                int bulletKind = beMessenger_GetInt((beMessenger *)MESSENGER, 0);
                beMessenger_GetMatrix(bulletMatrix, (beMessenger *)MESSENGER, 0);
                const char *hitterName = beMessenger_GetString((beMessenger *)MESSENGER, 0);
                int hitterRamNo = beMessenger_GetInt((beMessenger *)MESSENGER, 1);
                int hitterRecNo = -1;
                igVec3f bulletPos, modelPos;
                igMatrix44f_GetTranslation((const float *)bulletMatrix, (float *)&bulletPos);
                igMatrix44f_GetTranslation((const float *)MODEL_NODE->_m, (float *)&modelPos);
                beMessenger_PushArgContext((beMessenger *)MESSENGER);
                if (*hitterName != 0x70) {
                    beMessenger_SendNamed((beMessenger *)MESSENGER, ((char *)MODELCTRL_7), hitterName, hitterRamNo, GETRECNO);
                    if (beMessenger_GetIntCount((beMessenger *)MESSENGER) == 1)
                        hitterRecNo = beMessenger_GetInt((beMessenger *)MESSENGER, 0);
                    else
                        hitterRecNo = -9;
                }
                if (hitterRecNo != -9) {
                    INFO_NAME(n)
                    beModelCtrl_CallLua(self, ram, hit, Hit, n, bulletKind, hitBox, hitterName, hitterRamNo, hitterRecNo);
                    if (((unsigned char *)g_mdlDmgTurn)[0] != 0) {
                        work->_targetDirection[1] = atan2f(bulletPos[0] - modelPos[0], bulletPos[2] - modelPos[2]);
                        beModelCtrl_UpdateDirection(self, info, ram, work, 1);
                    }
                }
                beMessenger_PopArgContext((beMessenger *)MESSENGER);
                if (beMessenger_GetBoolCount((beMessenger *)MESSENGER) == 0) beMessenger_AppendBool((beMessenger *)MESSENGER, 1);
            }
        }
        return 1;
    case MSG_GENERATE_NDSP:
    default:
        if (ram->_isRun != 0) {
            if (strcmp(message, ((char *)SQ_ERAS_2)) == 0) {
                ((beModelCtrlDispatchView *)self)->OnErase(ram);
                POOL()
                const char *tk = ((const char *)StringPool_Intern(g_stringPool, ((char *)SQ_ERAS_2)));
                const char *old = (const char *)work->_seqCodeName;
                RELEASE_STRING(old)
                work->_seqCodeName = (int)tk;
            } else if (strcmp(message, SQ_ERAS2) == 0) {
                beMessenger_PushArgContext((beMessenger *)MESSENGER);
                int id = ram->_ramNo;
                INFO_NAME(n)
                beMessenger_SendNamed((beMessenger *)MESSENGER, ((char *)ACTION_2), n, id, NDSP_2);
                if (work != 0) beModelCtrlSubCom_StopAll((beModelCtrlSubCom *)work->_subCommand, ram);
                beModelCtrlNode2 *modelNode = MODEL_NODE;
                RELEASE(modelNode->_bound)
                modelNode->_bound = 0;
                beBaseInfoRam_RemoveAllTimers(ram);
                beMessenger_PopArgContext((beMessenger *)MESSENGER);
            } else {
                const char *tk;
                beModelCtrlInfoDataSeq *fb = (beModelCtrlInfoDataSeq *)((beBaseInfoData *)((Gap::Core::igObjectList *)info->_dataList)->search((Gap::Core::igStringMetaField *)Gap::Core::igNamedObject::k_name, SEQ));
                beModelCtrlData *t = (beModelCtrlData *)((beBaseInfoData *)((Gap::Core::igObjectList *)fb->_dataList)->search((Gap::Core::igStringMetaField *)Gap::Core::igNamedObject::k_name, (const char *)message));
                POOL()
                tk = ((const char *)StringPool_Intern(g_stringPool, message));
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
                beModelCtrlSubCom_StopAll((beModelCtrlSubCom *)work->_subCommand, ram);
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
            if (beMessenger_GetInt((beMessenger *)MESSENGER, 0) != 0) {
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
                    ((beModelCtrlInfoRideOn2 *)r.p)->_vector = beMessenger_GetVec3((beMessenger *)MESSENGER, 0);
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
            if (beMessenger_GetInt((beMessenger *)MESSENGER, 0) != 0) {
                if (work->_rideOnData == 0) {
                    ALLOCATOR(a, self)
                    ObjRef<3> r((igObject *)beModelCtrlInfoRideOn3_Create(a));
                    igVec3f quicksandPos;
                    igMatrix44f_GetTranslation((const float *)MODEL_NODE->_m, (float *)&quicksandPos);
                    igMatrix44f_Copy(quicksandMatrix, g_matrix44Identity.m);
                    igMatrix44f_SetTranslation((float *)quicksandMatrix, (const float *)&quicksandPos);
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
                    ((beModelCtrlInfoRideOn3 *)r.p)->_worldPosition = beMessenger_GetVec3((beMessenger *)MESSENGER, 0);
                    ((beModelCtrlInfoRideOn3 *)r.p)->_minKyori = beMessenger_GetFloat((beMessenger *)MESSENGER, 0);
                    ((beModelCtrlInfoRideOn3 *)r.p)->_maxKyori = beMessenger_GetFloat((beMessenger *)MESSENGER, 1);
                    ((beModelCtrlInfoRideOn3 *)r.p)->_minSpeed = beMessenger_GetFloat((beMessenger *)MESSENGER, 2);
                    ((beModelCtrlInfoRideOn3 *)r.p)->_maxSpeed = beMessenger_GetFloat((beMessenger *)MESSENGER, 3);
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
            if (beMessenger_GetInt((beMessenger *)MESSENGER, 0) != 0) {
                if (work->_rideOnData == 0) {
                    ALLOCATOR(a, self)
                    ObjRef<4> r((igObject *)beModelCtrlInfoRideOn4_Create(a));
                    igVec3f floorPos;
                    igMatrix44f_GetTranslation((const float *)MODEL_NODE->_m, (float *)&floorPos);
                    igMatrix44f_Copy(floorMatrix, g_matrix44Identity.m);
                    igMatrix44f_SetTranslation((float *)floorMatrix, (const float *)&floorPos);
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
                    { beModelCtrlInfoRideOn4 *f4 = (beModelCtrlInfoRideOn4 *)r.p; f4->_oldPlayerPos[0] = floorPos[0]; f4->_oldPlayerPos[1] = floorPos[1]; f4->_oldPlayerPos[2] = floorPos[2]; }
                    { beModelCtrlInfoRideOn4 *f4 = (beModelCtrlInfoRideOn4 *)r.p; f4->_vector[0] = g_vec3Zero[0]; f4->_vector[1] = g_vec3Zero[1]; f4->_vector[2] = g_vec3Zero[2]; }
                    ((beModelCtrlInfoRideOn4 *)r.p)->_scalar = beMessenger_GetFloat((beMessenger *)MESSENGER, 0);
                    ((beModelCtrlInfoRideOn4 *)r.p)->_limitter = beMessenger_GetFloat((beMessenger *)MESSENGER, 1);
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

igMetaObject *beModelCtrlInfoRideOn4_GetMeta(void)
{
    return g_beModelCtrlInfoRideOn4_metaObject;
}

igMetaObject *beModelCtrlInfoRideOn3_GetMeta(void)
{
    return g_beModelCtrlInfoRideOn3_metaObject;
}

igMetaObject *beModelCtrlInfoRideOn2_GetMeta(void)
{
    return g_beModelCtrlInfoRideOn2_metaObject;
}

igMetaObject *beModelCtrl_GetMeta(void)
{
    return g_beModelCtrl_metaObject;
}
