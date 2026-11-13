#include "dw4/reflected.h"
#include "dw4/igTDataList.h"
#include "dw4/igSmartPointer.h"

typedef void (*TraversalFunction)(void);
typedef int (*PopProc)(int attr, int data);

extern "C" {
long long __fixsfdi(float);
int igMatrix44f_SetIdentity(...);
int FUN_001904f0(...);
int igObjectPool_Grow(...);
int igAttrStackManager_MarkStackChanged(...);
int FUN_001b12f0(...);
int FUN_001b13d0(...);
int igTraversal_TraverseChildren(...);
int FUN_001356b0(...);
int igTimeAttr_CreateInstance(...);
int igTraversal_RegisterFunction(int, int, TraversalFunction);
int beModelCtrlNode2_ResolveMetaObject(...);
int beModelCtrl_DrawDebugHitBox(...);
int beModelCtrl_CallLua(...);
int Memory_GetAllocatorBySelector(...);
int igObject_GetAllocator(...);
int thunk_FUN_0018ac80(...);
igAABox *FUN_0018a660(int);
igObject *beBaseInfoDataList_Create(int);
beModelCtrlInfoRamData *igProperty_FindByName(...);
beModelCtrlSCSound *beModelCtrlSCSound_Create(...);
beModelCtrlSCHitBox *beModelCtrlSCHitBox_Create(int);
beModelCtrlSCEffect *beModelCtrlSCEffect_Create(int);
int beMessenger_AppendInt(...);
int beMessenger_AppendMatrix(...);
int beMessenger_AppendObject(...);
int beMessenger_AppendString(...);
int beMessenger_DispatchSelected(...);
int beMessenger_GetBoolCount(...);
int beMessenger_SelectGroup(...);
int beMessenger_SetRunCheck(...);
int beMessenger_AppendBool(int, unsigned char);
int beMessenger_AppendVec3(int, float *);
int beMessenger_GetObjectCount(int);
beBaseInfoRam *beMessenger_GetObject(int, int);
int beMessenger_SelectReceivers(int, int *, int, int);
int beMessenger_SendNamed(int, int *, int, int, int *);
int beMessenger_GetInt(int, int);
long long beMessenger_GetLong(int, int);
int beMessenger_AppendLong(int, long long);
int List_RemoveWordAt(...);
int StringPool_Allocate(...);
int ObjectList_AppendRetained(...);
int StringChunk_ReleaseHeader(...);
int StringPool_Construct(...);
void *StringPool_Intern(...);

extern igMetaObject *g_igModelViewMatrixAttr_metaObject[4];
extern int g_beModelCtrlSCSound_metaObject[4];
extern int g_beModelCtrlSCEffect_metaObject[4];
extern int g_beModelCtrlSCHitBox_metaObject[4];
extern int DAT_00562640[4];
extern int g_propertyNameField[4];
extern int g_defaultAllocatorSelector[4];
extern int g_stringPool[4];
extern unsigned char GPR_00554c14;
extern int emptyString[4];
extern int ONE[4];
extern int HITPLAYERBULLET[4];
extern int HITPLAYERTALK[4];
extern int HITENEMYBULLET[4];
extern int CHKBULLET[4];
extern int BHit[4];
extern int MODELCTRL_4[4];
extern int FIND_SPACE[4];
extern int GENERATE_3[4];
extern int SQ_ERAS[4];
extern int SOUND_2[4];
extern int PLAY[4];
extern int DOWN[4];
extern int VOLUMECTL[4];
/* Debug draw colour per bullet mode (RGBA), filled on first use. */
extern float g_hitBoxDebugColors[12];
extern char g_hitBoxDebugColorsReady;

int beModelCtrlNode2_TraversalFunction(igCommonTraversal *trav, beModelCtrlNode2 *node);
long long beModelCtrlNode2_LocalTime(beModelCtrlNode2 *node, long long now);
int beModelCtrlNode2_Traverse(beModelCtrlNode2 *node, igCommonTraversal *trav);
void beModelCtrlNode2_RegisterTraversalFunction(void);
int Gap__Bec__beModelCtrlSCHitBox__vfunc_21(beModelCtrlSCHitBox *self, beBaseInfoRam *ram);
int Gap__Bec__beModelCtrlSCHitBox__vfunc_22(beModelCtrlSCHitBox *self, beBaseInfoRam *ram, int frames);
int Gap__Bec__beModelCtrlSCEffect__vfunc_21(beModelCtrlSCEffect *self, beBaseInfoRam *ram);
void Gap__Bec__beModelCtrlSCEffect__vfunc_23(beModelCtrlSCEffect *self, beBaseInfoRam *ram);
int Gap__Bec__beModelCtrlSCSound__vfunc_21(beModelCtrlSCSound *self, beBaseInfoRam *ram);
void Gap__Bec__beModelCtrlSCSound__vfunc_23(beModelCtrlSCSound *self, beBaseInfoRam *ram);
unsigned char beModelCtrlSubComBase_Update(beModelCtrlSubComBase *self, beBaseInfoRam *ram);
void beModelCtrlSubCom_Update(beModelCtrlSubCom *self, beBaseInfoRam *ram);
void beModelCtrlSubCom_StopAll(beModelCtrlSubCom *self, beBaseInfoRam *ram);
void beModelCtrlSubCom_StopType(beModelCtrlSubCom *self, beBaseInfoRam *ram, int metaObject);
void beModelCtrlSubCom_AddEffect(beModelCtrlSubCom *self, int modelName, int seqName, float *offset, float *rotation, char isSeqDead, char isPositionLock, float startFrame);
void beModelCtrlSubCom_AddHitBox(beModelCtrlSubCom *self, beModelCtrlHITBOX *hitBox);
void beModelCtrlSubCom_AddSound(beModelCtrlSubCom *self, int sndName, float startFrame);
int Gap__Bec__beModelCtrlSCSound__vfunc_20(void);
int Gap__Bec__beModelCtrlSCEffect__vfunc_20(void);
int Gap__Bec__beModelCtrlSCHitBox__vfunc_20(void);
}

#define CLOCK_TICK_SHIFT 18

/* Virtual slot 30: the matrix attribute takes its matrix. */
class MatrixAttrVT { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void setMatrix(float *m); };
/* Virtual slots 24, 30 and 31: the traversal reads its time, sets a node time and ends it. */
class TraversalVT { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual long long getTime(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void setTime(long long t); virtual void endTime(); };
/* The sub-command slots: 20 meta object, 21 start, 22 update, 23 stop. */
class SubCommandVT { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual int metaObject(); virtual unsigned char start(beBaseInfoRam *ram, int frames); virtual unsigned char update(beBaseInfoRam *ram, int frames); virtual void stop(beBaseInfoRam *ram); };
typedef igTDataList<igAttr *> AttrList;

/* matching construct: expression temporary -- the freshly created data list is held by a temporary passed to an
   inline helper, so its frame slot (168) sorts below the box reference (172); a named local took 172 instead. */
struct RamDataList { static inline void assign(beBaseInfoRam *ram, const igSmartPointer<igObject> &created) {
        igObject *list = created.p;
        if (list != 0) {
            list->_refCount++;
        }
        igRelease((igObject *)ram->_dataList);
        ram->_dataList = (int)list;
}
static inline void create(beBaseInfoRam *ram, int allocator) { igSmartPointer<igObject> list(beBaseInfoDataList_Create(allocator)); assign(ram, list); }
};

int beModelCtrlNode2_TraversalFunction(igCommonTraversal *trav, beModelCtrlNode2 *node)
{
    return beModelCtrlNode2_Traverse(node, trav);
}

/* The node's clock: the traversal time scaled by _timeScale, in units of 2^18 ns, plus _timeBias. */
long long beModelCtrlNode2_LocalTime(beModelCtrlNode2 *node, long long now) {
    unsigned int ticks = (unsigned int)(now >> CLOCK_TICK_SHIFT);
    float scaled = (float)ticks;
    long long time;
    scaled = scaled * node->_timeScale;
    time = __fixsfdi(scaled) << CLOCK_TICK_SHIFT;
    return time + node->_timeBias;
}

static inline igAttrList *overrides(const beModelCtrlNode2 *node) { return (igAttrList *)node->_overrideAttrList; }

/* Pushes the node's matrix (times the current model-view top) and its local time, then the
 * override attributes, traverses the children and pops everything in reverse. */
int beModelCtrlNode2_Traverse(beModelCtrlNode2 *node, igCommonTraversal *trav) {
    long long time;
    short *matAttrIndex;
    short *matUnitID;
    igAttrStackManager *mgr;
    igAttrStack *stack;
    igModelViewMatrixAttr *matAttr;
    igTimeAttr *timeAttr;
    int metaId;
    int matSlot;
    int timeSlot;
    int i;
    int j;
    int l;
    int jo;
    int lo;
    short *timeAttrIndex;
    short *timeUnitID;
    int result;
    igAttrStack *mvStack;
    int last;
    int *entries;
    float m[16];
    float identity[16];

    mgr = (igAttrStackManager *)trav->_attrStack;
    metaId = g_igModelViewMatrixAttr_metaObject[0]->_id;
    mvStack = ((igAttrStack **)((igAttrStackList *)mgr->_attrStacks)->_data)[((int *)mgr->_attrStackIndexTable)[metaId]];
    time = beModelCtrlNode2_LocalTime(node, ((TraversalVT *)trav)->getTime());
    node->_time = time;
    igMatrix44f_SetIdentity(m);
    if (mvStack->_count != 0) {
        last = mvStack->_count - 1;
        entries = (int *)mvStack->_data;
        FUN_001904f0(m, node->_m, ((igModelViewMatrixAttr *)entries[last])->_m);
    } else {
        igMatrix44f_SetIdentity(identity);
        FUN_001904f0(m, node->_m, identity);
    }
    {
        igObjectPool *pool = (igObjectPool *)trav->_matrixPool;
        if (pool->_freeIndex >= pool->_count) igObjectPool_Grow(pool, FUN_001356b0);
        i = pool->_freeIndex;
        pool->_freeIndex = i + 1;
        matAttr = ((igModelViewMatrixAttr **)pool->_data)[i];
    }
    ((MatrixAttrVT *)matAttr)->setMatrix(m);
    {
        igObjectPool *pool = (igObjectPool *)trav->_timePool;
        if (pool->_freeIndex >= pool->_count) igObjectPool_Grow(pool, igTimeAttr_CreateInstance);
        i = pool->_freeIndex;
        pool->_freeIndex = i + 1;
        timeAttr = ((igTimeAttr **)pool->_data)[i];
    }
    timeAttr->_time = time;
    ((TraversalVT *)trav)->setTime(time);

    matUnitID = &matAttr->_cachedUnitID;
    matAttrIndex = &matAttr->_cachedAttrIndex;
    matSlot = matAttr->_cachedUnitID + ((int *)mgr->_attrStackIndexTable)[matAttr->_cachedAttrIndex];
    stack = ((igAttrStack **)((igAttrStackList *)mgr->_attrStacks)->_data)[matSlot];
    ((AttrList *)stack)->append((igAttr *)matAttr);
    igAttrStackManager_MarkStackChanged(mgr, stack, matSlot);

    timeAttrIndex = &timeAttr->_cachedAttrIndex;
    timeUnitID = &timeAttr->_cachedUnitID;
    timeSlot = timeAttr->_cachedUnitID + ((int *)mgr->_attrStackIndexTable)[timeAttr->_cachedAttrIndex];
    stack = ((igAttrStack **)((igAttrStackList *)mgr->_attrStacks)->_data)[timeSlot];
    ((AttrList *)stack)->append((igAttr *)timeAttr);
    igAttrStackManager_MarkStackChanged(mgr, stack, timeSlot);

    j = 0;
    if (j < overrides(node)->_count) {
        jo = 0;
        do {
            FUN_001b12f0(mgr, *(int *)(((igAttrList *)node->_overrideAttrList)->_data + jo));
            j++;
            jo += 4;
        } while (j < ((igAttrList *)node->_overrideAttrList)->_count);
    }
    result = igTraversal_TraverseChildren(trav, node);
    for (l = ((igAttrList *)node->_overrideAttrList)->_count - 1, lo = l * 4; l >= 0; l--) {
        FUN_001b13d0(mgr, *(int *)(((igAttrList *)node->_overrideAttrList)->_data + lo));
        lo -= 4;
    }
    {
        int slot = *timeUnitID + ((int *)mgr->_attrStackIndexTable)[*timeAttrIndex];
        igAttrStack *st = ((igAttrStack **)((igAttrStackList *)mgr->_attrStacks)->_data)[slot];
        int top = st->_count - 1;
        int *data = (int *)st->_data;
        int attr = data[top];
        PopProc popProc = (PopProc)st->_popProc;
        if (popProc != 0) popProc(attr, mgr->_popProcData);
        st->_count = st->_count - 1;
        igAttrStackManager_MarkStackChanged(mgr, st, slot);
    }
    {
        int slot = *matUnitID + ((int *)mgr->_attrStackIndexTable)[*matAttrIndex];
        igAttrStack *st = ((igAttrStack **)((igAttrStackList *)mgr->_attrStacks)->_data)[slot];
        int top = st->_count - 1;
        int *data = (int *)st->_data;
        int attr = data[top];
        PopProc popProc = (PopProc)st->_popProc;
        if (popProc != 0) popProc(attr, mgr->_popProcData);
        st->_count = st->_count - 1;
        igAttrStackManager_MarkStackChanged(mgr, st, slot);
    }
    ((TraversalVT *)trav)->endTime();
    if (result == 2) return 2;
    return 0;
}

void beModelCtrlNode2_RegisterTraversalFunction(void) {
    igTraversal_RegisterFunction(DAT_00562640[0], beModelCtrlNode2_ResolveMetaObject(), (TraversalFunction)beModelCtrlNode2_TraversalFunction);
}

/* Start: builds the hit box around the owner's node (offset, sized by _boxSize, moved into the node's
 * matrix), draws it in debug mode, and sends it to the bullet group of _bulletMode. When a receiver
 * reports a hit, the owner's BHit Lua function runs. */
int Gap__Bec__beModelCtrlSCHitBox__vfunc_21(beModelCtrlSCHitBox *self, beBaseInfoRam *ram) {
    float center[3];
    int i;
    float color[4];
    beModelCtrlInfoRamData *ramData;
    beModelCtrlInfoWork *work;
    beModelCtrl *ctrl;
    beBaseInfo *info = (beBaseInfo *)ram->_parentInfo;
    igAABox *box;
    if (ram->_dataList == 0) {
        int own = igObject_GetAllocator(ram);
        RamDataList::create(ram, GPR_00554c14 != 0 ? own : Memory_GetAllocatorBySelector(g_defaultAllocatorSelector[0]));
    }
    ramData = igProperty_FindByName(ram->_dataList, g_propertyNameField[0], ONE);
    work = (beModelCtrlInfoWork *)ramData->_work;
    ctrl = (beModelCtrl *)ram->_parentManager;
    int own = igObject_GetAllocator(self);
    int allocator;
    if (GPR_00554c14 != 0) {
        allocator = own;
    } else {
        allocator = Memory_GetAllocatorBySelector(g_defaultAllocatorSelector[0]);
    }
    igSmartPointer<igAABox> hitBox(FUN_0018a660(allocator));
    goto placeAtOffset;
toNodeSpace:
    thunk_FUN_0018ac80(hitBox.p, ((beModelCtrlNode2 *)ramData->_node)->_m);
    { box = hitBox.p;
    center[0] = box->_min[0] * 0.5f + box->_max[0] * 0.5f;
    center[1] = box->_min[1] * 0.5f + box->_max[1] * 0.5f;
    center[2] = box->_min[2] * 0.5f + box->_max[2] * 0.5f; }
    goto sizeAroundCenter;
send:
    if (ctrl->_isDebugHitBox != 0 && work != 0) {
        int debugNode = work->_debugHitBoxNode;
        if (debugNode != 0) {
            if (g_hitBoxDebugColorsReady == 0) {
                g_hitBoxDebugColors[0] = 0;
                g_hitBoxDebugColors[1] = 0;
                g_hitBoxDebugColors[2] = 1.0f;
                g_hitBoxDebugColors[3] = 0.5f;
                g_hitBoxDebugColors[4] = 1.0f;
                g_hitBoxDebugColors[5] = 1.0f;
                g_hitBoxDebugColors[8] = 1.0f;
                g_hitBoxDebugColors[6] = 0;
                g_hitBoxDebugColors[7] = 0.5f;
                g_hitBoxDebugColors[11] = 0.5f;
                g_hitBoxDebugColors[9] = 0;
                g_hitBoxDebugColors[10] = 0;
                g_hitBoxDebugColorsReady = 1;
            }
            {
                float *rgba = &g_hitBoxDebugColors[self->_bulletMode * 4];
                color[0] = rgba[0]; color[1] = rgba[1]; color[2] = rgba[2]; color[3] = rgba[3];
            }
            beModelCtrl_DrawDebugHitBox(ctrl, debugNode, hitBox.p, color);
        }
    }
    switch (self->_bulletMode) {
    case 0:
        beMessenger_SelectGroup(ctrl->_messenger, HITPLAYERBULLET);
        break;
    case 1:
        beMessenger_SelectGroup(ctrl->_messenger, HITPLAYERTALK);
        break;
    default:
        beMessenger_SelectGroup(ctrl->_messenger, HITENEMYBULLET);
        break;
    }
    beMessenger_AppendInt(ctrl->_messenger, self->_kind);
    beMessenger_AppendObject(ctrl->_messenger, hitBox.p);
    beMessenger_AppendMatrix(ctrl->_messenger, ((beModelCtrlNode2 *)ramData->_node)->_m);
    {
        int parentName = work->_hitParentName;
        if (parentName == 0) {
            int name = info->_name != 0 ? info->_name : (int)emptyString;
            beMessenger_AppendString(ctrl->_messenger, name);
            beMessenger_AppendInt(ctrl->_messenger, ram->_ramNo);
        } else {
            beMessenger_AppendString(ctrl->_messenger, parentName);
            beMessenger_AppendInt(ctrl->_messenger, work->_hitParentRamNo);
        }
    }
    beMessenger_SetRunCheck(ctrl->_messenger, 1);
    beMessenger_DispatchSelected(ctrl->_messenger, CHKBULLET);
    if (beMessenger_GetBoolCount(ctrl->_messenger) != 0) {
        int luaBHit = ((beModelCtrlInfoWork *)ramData->_work)->_luaBHit;
        if (luaBHit != 0) {
            int name = info->_name != 0 ? info->_name : (int)emptyString;
            beModelCtrl_CallLua(ctrl, ram, luaBHit, BHit, name, 0, 0, 0, 0, 0);
        }
    }
    return 1;
sizeAroundCenter:
    for (i = 0; i < 3; i++) {
        float size = self->_boxSize[i];
        box = hitBox.p;
        box->_min[i] = center[i] - size / 2.0f;
        box = hitBox.p;
        box->_max[i] = size / 2.0f + center[i];
    }
    goto send;
placeAtOffset:
    { igAABox *b = hitBox.p; b->_min[0] = b->_max[0] = self->_offset[0]; }
    { float v = self->_offset[1]; igAABox *b = hitBox.p; b->_max[1] = v; b->_min[1] = v; }
    { igAABox *b = hitBox.p; b->_min[2] = b->_max[2] = self->_offset[2]; }
    goto toNodeSpace;
}

/* Update: the hit box is sent again every frame until _endFrame. */
int Gap__Bec__beModelCtrlSCHitBox__vfunc_22(beModelCtrlSCHitBox *self, beBaseInfoRam *ram, int frames) {
    if (!(self->_runFrame < self->_endFrame)) {
        return 0;
    }
    ((SubCommandVT *)self)->start(ram, frames);
    return 1;
}

/* Start: finds a free gene model (_geneRamNo) for _modelName and has it generate _seqName at the
 * owner, or at the hit parent named by the owner's work, with the offset, rotation and position
 * lock. A sequence that dies by itself ends the sub-command at once. */
int Gap__Bec__beModelCtrlSCEffect__vfunc_21(beModelCtrlSCEffect *self, beBaseInfoRam *ram) {
    beBaseInfo *info;
    beBaseInfoManager *manager;
    int *name;
    int *ownerName;
    beModelCtrlInfoWork *work;
    float offset[3];
    float rotation[3];
    manager = (beBaseInfoManager *)ram->_parentManager;
    info = (beBaseInfo *)ram->_parentInfo;
    beMessenger_SendNamed(manager->_messenger, &MODELCTRL_4[0], self->_modelName, -1, &FIND_SPACE[0]);
    if (beMessenger_GetObjectCount(manager->_messenger) != 0) {
        self->_geneRamNo = beMessenger_GetObject(manager->_messenger, 0)->_ramNo;
        beMessenger_SelectReceivers(manager->_messenger, &MODELCTRL_4[0], self->_modelName, self->_geneRamNo);
        beMessenger_AppendInt(manager->_messenger, ram->_ramNo);
        name = (int *)info->_name;
        if (name != 0) ownerName = name; else ownerName = &emptyString[0];
        beMessenger_AppendString(manager->_messenger, ownerName);
        beMessenger_AppendString(manager->_messenger, self->_seqName);
        if (ram->_dataList == 0) {
            int own = igObject_GetAllocator(ram);
            RamDataList::create(ram, GPR_00554c14 != 0 ? own : Memory_GetAllocatorBySelector(g_defaultAllocatorSelector[0]));
        }
        work = (beModelCtrlInfoWork *)igProperty_FindByName(ram->_dataList, g_propertyNameField[0], &ONE[0])->_work;
        if (work->_hitParentName == 0) {
            name = (int *)info->_name;
            if (name != 0) ownerName = name; else ownerName = &emptyString[0];
            beMessenger_AppendString(manager->_messenger, ownerName);
            beMessenger_AppendInt(manager->_messenger, ram->_ramNo);
        } else {
            beMessenger_AppendString(manager->_messenger, work->_hitParentName);
            beMessenger_AppendInt(manager->_messenger, work->_hitParentRamNo);
        }
        offset[0] = self->_offset[0];
        offset[1] = self->_offset[1];
        offset[2] = self->_offset[2];
        beMessenger_AppendVec3(manager->_messenger, offset);
        rotation[0] = self->_rotation[0];
        rotation[1] = self->_rotation[1];
        rotation[2] = self->_rotation[2];
        beMessenger_AppendVec3(manager->_messenger, rotation);
        beMessenger_AppendBool(manager->_messenger, self->_isPositionLock);
        beMessenger_DispatchSelected(manager->_messenger, &GENERATE_3[0]);
    } else {
        return 0;
    }
    return self->_isSeqDead != 0;
}

/* Stop: erases the sequence on the gene model once it has started. */
void Gap__Bec__beModelCtrlSCEffect__vfunc_23(beModelCtrlSCEffect *self, beBaseInfoRam *ram) {
    int geneRamNo;

    if (self->_isOneSet != 0) {
        geneRamNo = self->_geneRamNo;
        if (geneRamNo != -1) {
            beMessenger_SendNamed(((beBaseInfoManager *)ram->_parentManager)->_messenger, &MODELCTRL_4[0], self->_modelName, geneRamNo, &SQ_ERAS[0]);
        }
    }
}

/* Start: plays _sndName; the sub-command lives on while the sound handle is valid. */
int Gap__Bec__beModelCtrlSCSound__vfunc_21(beModelCtrlSCSound *self, beBaseInfoRam *ram) {
    beBaseInfoManager *manager = (beBaseInfoManager *)ram->_parentManager;
    long long handle;
    beMessenger_SelectGroup(manager->_messenger, &SOUND_2[0]);
    beMessenger_AppendString(manager->_messenger, self->_sndName);
    beMessenger_DispatchSelected(manager->_messenger, &PLAY[0]);
    handle = beMessenger_GetLong(manager->_messenger, 0);
    if (handle == -1) {
        return 0;
    }
    if (handle == 0) {
        return 0;
    }
    if (beMessenger_GetInt(manager->_messenger, 0) != 4) {
        return 0;
    }
    self->_sndHandle = handle;
    return 1;
}

/* Stop: fades the playing sound down. */
void Gap__Bec__beModelCtrlSCSound__vfunc_23(beModelCtrlSCSound *self, beBaseInfoRam *ram) {
    beBaseInfoManager *manager = (beBaseInfoManager *)ram->_parentManager;
    if (self->_sndHandle != 0) {
        beMessenger_SelectGroup(manager->_messenger, &SOUND_2[0]);
        beMessenger_AppendString(manager->_messenger, &DOWN[0]);
        beMessenger_AppendLong(manager->_messenger, self->_sndHandle);
        beMessenger_DispatchSelected(manager->_messenger, &VOLUMECTL[0]);
    }
}

/* Advances the run frame; starts the sub-command once it reaches _startFrame and updates it after.
 * Returns 0 when the sub-command has finished. */
unsigned char beModelCtrlSubComBase_Update(beModelCtrlSubComBase *self, beBaseInfoRam *ram) {
    float runFrame;
    unsigned char alive;

    runFrame = self->_runFrame + ((beSystem *)((beBaseInfoManager *)ram->_parentManager)->_system)->_frameTimeF;
    self->_runFrame = runFrame;
    alive = 1;
    if (self->_isOneSet == 0) {
        if (!(runFrame < self->_startFrame)) {
            self->_isOneSet = 1;
            alive = ((SubCommandVT *)self)->start(ram, 1);
        }
    } else {
        alive = ((SubCommandVT *)self)->update(ram, 1);
    }
    return alive;
}

/* Updates every sub-command and drops the finished ones. */
void beModelCtrlSubCom_Update(beModelCtrlSubCom *self, beBaseInfoRam *ram) {
    int count;
    int i;
    igObjectList *list;

    count = ((igObjectList *)self->_comList)->_count;
    i = 0;
    if (count > 0) {
        do {
            if (!(beModelCtrlSubComBase_Update(((beModelCtrlSubComBase **)((igObjectList *)self->_comList)->_data)[i], ram) & 0xFF)) {
                list = (igObjectList *)(self->_comList);
                igRelease(((igObject **)list->_data)[i]);
                List_RemoveWordAt(list, i);
                i -= 1;
                count -= 1;
                ((int *)list->_data)[list->_count] = 0;
            }
            i += 1;
        } while (i < count);
    }
}

/* Stops every sub-command (an effect only when its sequence dies by itself) and empties the list. */
void beModelCtrlSubCom_StopAll(beModelCtrlSubCom *self, beBaseInfoRam *ram) {
    igObjectList *list;
    int i;
    int count;
    int cleared;
    SubCommandVT *command;
    int j;
    int k;
    int n;
    int effectMeta;

    n = ((igObjectList *)self->_comList)->_count;
    i = 0;
    if (0 < n) {
        do {
            effectMeta = g_beModelCtrlSCEffect_metaObject[0];
            command = ((SubCommandVT **)((igObjectList *)self->_comList)->_data)[i];
            if (effectMeta != command->metaObject() || ((beModelCtrlSCEffect *)command)->_isSeqDead != 0) {
                command->stop(ram);
            }
            i += 1;
        } while (i < n);
    }
    list = (igObjectList *)self->_comList;
    count = list->_count;
    j = 0;
    if (0 < count) {
        do {
            igRelease(((igObject **)list->_data)[j]);
            j += 1;
        } while (j < count);
    }
    cleared = list->_count;
    for (k = 0; k < cleared; k++) {
        ((int *)list->_data)[k] = 0;
    }
    list->_count = 0;
}

/* Stops and drops every sub-command of one class. */
void beModelCtrlSubCom_StopType(beModelCtrlSubCom *self, beBaseInfoRam *ram, int metaObject) {
    int count; int i; SubCommandVT *command; igObjectList *list;
    count = ((igObjectList *)self->_comList)->_count;
    i = 0;
    if (count > 0) {
        do {
            command = ((SubCommandVT **)((igObjectList *)self->_comList)->_data)[i];
            if (metaObject == command->metaObject()) {
                command->stop(ram);
                list = (igObjectList *)self->_comList;
                igRelease(((igObject **)list->_data)[i]);
                List_RemoveWordAt(list, i);
                i--;
                count--;
                ((int *)list->_data)[list->_count] = 0;
            }
            i++;
        } while (i < count);
    }
}

/* Interns `text` in the string pool (made on first use) and stores it in `field`, releasing the
 * string the field held. */
static inline void setInternedString(int *field, int text) {
    int pool;
    int *interned;
    int *old;
    int *header;
    int refs;
    if (g_stringPool[0] == 0) {
        pool = StringPool_Allocate(0x10);
        if (pool != 0) {
            pool = StringPool_Construct(pool);
        }
        g_stringPool[0] = pool;
    }
    interned = (int *)StringPool_Intern(g_stringPool[0], text);
    old = (int *)*field;
    if (old != 0) {
        header = old - 2;
        refs = old[-1] - 1;
        old[-1] = refs;
        if (refs == 0) {
            StringChunk_ReleaseHeader(*header, header);
        }
    }
    *field = (int)interned;
}

/* Appends an effect sub-command with interned model and sequence names. */
void beModelCtrlSubCom_AddEffect(beModelCtrlSubCom *self, int modelName, int seqName, float *offset, float *rotation, char isSeqDead, char isPositionLock, float startFrame) {
    int own;
    beModelCtrlSCEffect *record;
    own = igObject_GetAllocator(self);
    igSmartPointer<beModelCtrlSCEffect> effect(beModelCtrlSCEffect_Create(GPR_00554c14 != 0 ? own : Memory_GetAllocatorBySelector(g_defaultAllocatorSelector[0])));
    record = effect.p;
    setInternedString(&record->_modelName, modelName);
    effect.p->_geneRamNo = -1;
    record = effect.p;
    setInternedString(&record->_seqName, seqName);
    effect.p->_startFrame = startFrame;
    record = effect.p;
    record->_offset[0] = offset[0];
    record->_offset[1] = offset[1];
    record->_offset[2] = offset[2];
    record = effect.p;
    record->_rotation[0] = rotation[0];
    record->_rotation[1] = rotation[1];
    record->_rotation[2] = rotation[2];
    effect.p->_isSeqDead = isSeqDead;
    effect.p->_isPositionLock = isPositionLock;
    ObjectList_AppendRetained(self->_comList, effect.p);
}

/* Appends a hit-box sub-command built from a HITBOX command; a length of -1 never ends. The bullet
 * mode (0 HITPLAYERBULLET, 1 HITPLAYERTALK, 2 HITENEMYBULLET) comes from the kind's ten-thousands
 * digit: 6 is mode 1, 7 and 8 are mode 2, and below 10000 a kind from 1000 on is mode 2. */
void beModelCtrlSubCom_AddHitBox(beModelCtrlSubCom *self, beModelCtrlHITBOX *hitBox) {
    int allocator;
    float endFrame;
    float length;
    beModelCtrlSCHitBox *box;
    int kind;

    allocator = igObject_GetAllocator(self);
    allocator = (GPR_00554c14 != 0) ? allocator : Memory_GetAllocatorBySelector(g_defaultAllocatorSelector[0]);
    igSmartPointer<beModelCtrlSCHitBox> command(beModelCtrlSCHitBox_Create(allocator));
    command.p->_startFrame = hitBox->_start;
    length = hitBox->_length;
    if (length == -1.0f) {
        endFrame = 100000000.0f;
    } else {
        endFrame = hitBox->_start + length;
    }
    box = command.p;
    box->_endFrame = endFrame;
    box = command.p;
    box->_offset[0] = hitBox->_offset[0];
    box->_offset[1] = hitBox->_offset[1];
    box->_offset[2] = hitBox->_offset[2];
    box = command.p;
    box->_boxSize[0] = hitBox->_boxSize[0];
    box->_boxSize[1] = hitBox->_boxSize[1];
    box->_boxSize[2] = hitBox->_boxSize[2];
    kind = hitBox->_kind;
    switch (kind / 10000) {
    case 0:
        if (kind < 1000) {
            command.p->_bulletMode = 0;
        } else {
            command.p->_bulletMode = 2;
        }
        break;
    case 6:
        command.p->_bulletMode = 1;
        break;
    case 7:
    case 8:
        command.p->_bulletMode = 2;
        break;
    case 1:
    case 2:
    case 3:
    case 4:
    case 5:
    case 9:
    default:
        command.p->_bulletMode = 0;
        break;
    }
    command.p->_kind = hitBox->_kind;
    ObjectList_AppendRetained(self->_comList, command.p);
}

/* Appends a sound sub-command with an interned sound name. */
void beModelCtrlSubCom_AddSound(beModelCtrlSubCom *self, int sndName, float startFrame) {
    int *header;
    int refs;
    int allocator;
    int name;
    int pool;
    int *old;
    beModelCtrlSCSound *sound;

    name = sndName;
    allocator = igObject_GetAllocator(self);
    allocator = (GPR_00554c14 != 0) ? allocator : Memory_GetAllocatorBySelector(g_defaultAllocatorSelector[0]);
    igSmartPointer<beModelCtrlSCSound> command(beModelCtrlSCSound_Create(allocator));
    sound = command.p;
    if (g_stringPool[0] == 0) {
        pool = StringPool_Allocate(0x10);
        if (pool != 0) {
            pool = StringPool_Construct(pool);
        }
        g_stringPool[0] = pool;
    }
    name = (int)StringPool_Intern(g_stringPool[0], name);
    old = (int *)sound->_sndName;
    if (old != 0) {
        header = old - 2;
        refs = old[-1] - 1;
        old[-1] = refs;
        if (refs == 0) {
            StringChunk_ReleaseHeader(*header, header);
        }
    }
    sound->_sndName = name;
    command.p->_startFrame = startFrame;
    ObjectList_AppendRetained(self->_comList, command.p);
}

int Gap__Bec__beModelCtrlSCSound__vfunc_20(void)
{
    return g_beModelCtrlSCSound_metaObject[0];
}

int Gap__Bec__beModelCtrlSCEffect__vfunc_20(void)
{
    return g_beModelCtrlSCEffect_metaObject[0];
}

int Gap__Bec__beModelCtrlSCHitBox__vfunc_20(void)
{
    return g_beModelCtrlSCHitBox_metaObject[0];
}
