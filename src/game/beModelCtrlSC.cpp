#include "dw4/reflected.h"
#include "dw4/igTDataList.h"
#include "dw4/igSmartPointer.h"
#include "dw4/igTraversalView.h"
#include "dw4/igObjectDispatchView.h"
#include "dw4/beModelCtrlNode2.h"
#include "dw4/beModelCtrlSubCom.h"
#include "dw4/StringPool.h"
#include "dw4/beBaseInfoDataList.h"
#include "dw4/beMessenger.h"
#include "dw4/beModelCtrl.h"
#include "dw4/beModelCtrlSCEffect.h"
#include "dw4/beModelCtrlSCHitBox.h"
#include "dw4/beModelCtrlSCSound.h"
#include "dw4/igDataLists.h"
#include "dw4/igMatrix44f.h"
#include "dw4/igMemoryPoolContext.h"
#include "dw4/igNamedObject.h"
#include "dw4/igObject.h"
#include "dw4/igTraversal.h"
#include "dw4/softfloat.h"
#include "dw4/igAABox.h"
/* kept local: no include/dw4 home; SceneGraph reads igCommonTraversal::_travProcs through its own load-bearing view. */
extern "C" int g_igCommonTraversal_travProcs[4];
#pragma push
#pragma readonly_strings on

typedef void (*TraversalFunction)(void);

#include "dw4/emptyString.h"
extern "C" {


/* Debug draw colour per bullet mode (RGBA), filled on first use. */
float g_hitBoxDebugColors[12];
char g_hitBoxDebugColorsReady;

int beModelCtrlNode2_TraversalFunction(igCommonTraversal *trav, beModelCtrlNode2 *node);
int beModelCtrlNode2_Traverse(beModelCtrlNode2 *node, igCommonTraversal *trav);
int beModelCtrlSCHitBox_Start(beModelCtrlSCHitBox *self, beBaseInfoRam *ram);
int beModelCtrlSCHitBox_Update(beModelCtrlSCHitBox *self, beBaseInfoRam *ram, int frames);
int beModelCtrlSCEffect_Start(beModelCtrlSCEffect *self, beBaseInfoRam *ram);
void beModelCtrlSCEffect_Stop(beModelCtrlSCEffect *self, beBaseInfoRam *ram);
int beModelCtrlSCSound_Start(beModelCtrlSCSound *self, beBaseInfoRam *ram);
void beModelCtrlSCSound_Stop(beModelCtrlSCSound *self, beBaseInfoRam *ram);
unsigned char beModelCtrlSubComBase_Advance(beModelCtrlSubComBase *self, beBaseInfoRam *ram);
igMetaObject *beModelCtrlSCSound_GetMeta(void);
igMetaObject *beModelCtrlSCEffect_GetMeta(void);
igMetaObject *beModelCtrlSCHitBox_GetMeta(void);
}

#define CLOCK_TICK_SHIFT 18

/* The sub-commands' virtual functions past igObject's: slot 21 starts the command, slot 22 updates it
 * each frame (beModelCtrlSCHitBox_Update) and slot 23 stops it (beModelCtrlSC<Kind>_Stop).
 * ABI view only: never instantiated. */
class beModelCtrlSubComDispatchView : public igObjectDispatchView {
public:
    virtual unsigned char Start(beBaseInfoRam *ram, int frames);            /* slot 21 */
    virtual unsigned char Update(beBaseInfoRam *ram, int frames);
    virtual void Stop(beBaseInfoRam *ram);
};
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
    metaId = g_igModelViewMatrixAttr_metaObject->_id;
    mvStack = ((igAttrStack **)((igAttrStackList *)mgr->_attrStacks)->_data)[((int *)mgr->_attrStackIndexTable)[metaId]];
    time = beModelCtrlNode2_LocalTime(node, ((igCommonTraversalDispatchView *)trav)->getTime());
    node->_time = time;
    igMatrix44f_SetIdentity(m);
    if (mvStack->_count != 0) {
        last = mvStack->_count - 1;
        entries = (int *)mvStack->_data;
        igMatrix44f_Multiply(m, node->_m, ((igModelViewMatrixAttr *)entries[last])->_m);
    } else {
        igMatrix44f_SetIdentity(identity);
        igMatrix44f_Multiply(m, node->_m, identity);
    }
    matAttr = (igModelViewMatrixAttr *)TakePooled((igObjectPool *)trav->_matrixPool, (igObject *(*)(int))igModelViewMatrixAttr_CreateInstance);
    ((igModelViewMatrixAttrDispatchView *)matAttr)->setMatrix(m);
    timeAttr = (igTimeAttr *)TakePooled((igObjectPool *)trav->_timePool, (igObject *(*)(int))igTimeAttr_CreateInstance);
    timeAttr->_time = time;
    ((igCommonTraversalDispatchView *)trav)->pushTime(time);

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
            igAttrStackManager_PushOverrideAttr(mgr, (igAttr *)*(int *)(((igAttrList *)node->_overrideAttrList)->_data + jo));
            j++;
            jo += 4;
        } while (j < ((igAttrList *)node->_overrideAttrList)->_count);
    }
    result = igTraversal_TraverseChildren((igTraversal *)trav, (igNode *)node);
    for (l = ((igAttrList *)node->_overrideAttrList)->_count - 1, lo = l * 4; l >= 0; l--) {
        igAttrStackManager_PopOverrideAttr(mgr, (igAttr *)*(int *)(((igAttrList *)node->_overrideAttrList)->_data + lo));
        lo -= 4;
    }
    PopAttr(mgr, *timeUnitID + ((int *)mgr->_attrStackIndexTable)[*timeAttrIndex]);
    PopAttr(mgr, *matUnitID + ((int *)mgr->_attrStackIndexTable)[*matAttrIndex]);
    ((igCommonTraversalDispatchView *)trav)->popTime();
    if (result == 2) return 2;
    return 0;
}

void beModelCtrlNode2_RegisterTraversalFunction(void) {
    igTraversal_RegisterFunction((igTraversalFunctionList *)g_igCommonTraversal_travProcs[0], beModelCtrlNode2_ResolveMetaObject(), (void *)beModelCtrlNode2_TraversalFunction);
}

/* Start: builds the hit box around the owner's node (offset, sized by _boxSize, moved into the node's
 * matrix), draws it in debug mode, and sends it to the bullet group of _bulletMode. When a receiver
 * reports a hit, the owner's BHit Lua function runs. */
int beModelCtrlSCHitBox_Start(beModelCtrlSCHitBox *self, beBaseInfoRam *ram) {
    float center[3];
    int i;
    float color[4];
    beModelCtrlInfoRamData *ramData;
    beModelCtrlInfoWork *work;
    beModelCtrl *ctrl;
    beBaseInfo *info = (beBaseInfo *)ram->_parentInfo;
    igAABox *box;
    if (ram->_dataList == 0) {
        int own = (int)igObject_GetAllocator(ram);
        RamDataList::create(ram, g_useOwnerAllocator != 0 ? own : (int)Memory_GetAllocatorBySelector(kIGMemoryPoolHandleUser1));
    }
    ramData = (beModelCtrlInfoRamData *)igProperty_FindByName((igObjectList *)ram->_dataList, g_propertyNameField, "ONE");
    work = (beModelCtrlInfoWork *)ramData->_work;
    ctrl = (beModelCtrl *)ram->_parentManager;
    int own = (int)igObject_GetAllocator(self);
    int allocator;
    if (g_useOwnerAllocator != 0) {
        allocator = own;
    } else {
        allocator = (int)Memory_GetAllocatorBySelector(kIGMemoryPoolHandleUser1);
    }
    igSmartPointer<igAABox> hitBox(igAABox_CreateInstance(allocator));
    goto placeAtOffset;
toNodeSpace:
    thunk_igAABox_Transform(hitBox.p, ((beModelCtrlNode2 *)ramData->_node)->_m);
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
            beModelCtrl_DrawDebugHitBox(ctrl, (igNode *)debugNode, hitBox.p, color);
        }
    }
    switch (self->_bulletMode) {
    case 0:
        beMessenger_SelectGroup((beMessenger *)ctrl->_messenger, "HITPLAYERBULLET");
        break;
    case 1:
        beMessenger_SelectGroup((beMessenger *)ctrl->_messenger, "HITPLAYERTALK");
        break;
    default:
        beMessenger_SelectGroup((beMessenger *)ctrl->_messenger, "HITENEMYBULLET");
        break;
    }
    beMessenger_AppendInt((beMessenger *)ctrl->_messenger, self->_kind);
    beMessenger_AppendObject((beMessenger *)ctrl->_messenger, hitBox.p);
    beMessenger_AppendMatrix((beMessenger *)ctrl->_messenger, ((beModelCtrlNode2 *)ramData->_node)->_m);
    {
        int parentName = work->_hitParentName;
        if (parentName == 0) {
            int name = info->_name != 0 ? info->_name : (int)emptyString;
            beMessenger_AppendString((beMessenger *)ctrl->_messenger, (const char *)name);
            beMessenger_AppendInt((beMessenger *)ctrl->_messenger, ram->_ramNo);
        } else {
            beMessenger_AppendString((beMessenger *)ctrl->_messenger, (const char *)parentName);
            beMessenger_AppendInt((beMessenger *)ctrl->_messenger, work->_hitParentRamNo);
        }
    }
    beMessenger_SetRunCheck((beMessenger *)ctrl->_messenger, 1);
    beMessenger_DispatchSelected((beMessenger *)ctrl->_messenger, "CHKBULLET");
    if (beMessenger_GetBoolCount((beMessenger *)ctrl->_messenger) != 0) {
        int luaBHit = ((beModelCtrlInfoWork *)ramData->_work)->_luaBHit;
        if (luaBHit != 0) {
            int name = info->_name != 0 ? info->_name : (int)emptyString;
            beModelCtrl_CallLua(ctrl, ram, (const char *)luaBHit, "BHit", (const char *)name, 0, 0, 0, 0, 0);
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
int beModelCtrlSCHitBox_Update(beModelCtrlSCHitBox *self, beBaseInfoRam *ram, int frames) {
    if (!(self->_runFrame < self->_endFrame)) {
        return 0;
    }
    ((beModelCtrlSubComDispatchView *)self)->Start(ram, frames);
    return 1;
}

/* Start: finds a free gene model (_geneRamNo) for _modelName and has it generate _seqName at the
 * owner, or at the hit parent named by the owner's work, with the offset, rotation and position
 * lock. A sequence that dies by itself ends the sub-command at once. */
int beModelCtrlSCEffect_Start(beModelCtrlSCEffect *self, beBaseInfoRam *ram) {
    beBaseInfo *info;
    beBaseInfoManager *manager;
    int *name;
    int *ownerName;
    beModelCtrlInfoWork *work;
    float offset[3];
    float rotation[3];
    manager = (beBaseInfoManager *)ram->_parentManager;
    info = (beBaseInfo *)ram->_parentInfo;
    beMessenger_SendNamed((beMessenger *)manager->_messenger, "MODELCTRL", (const char *)self->_modelName, -1, "FIND_SPACE");
    if (beMessenger_GetObjectCount((beMessenger *)manager->_messenger) != 0) {
        self->_geneRamNo = ((beBaseInfoRam *)beMessenger_GetObject((beMessenger *)manager->_messenger, 0))->_ramNo;
        beMessenger_SelectReceivers((beMessenger *)manager->_messenger, "MODELCTRL", (const char *)self->_modelName, self->_geneRamNo);
        beMessenger_AppendInt((beMessenger *)manager->_messenger, ram->_ramNo);
        name = (int *)info->_name;
        if (name != 0) ownerName = name; else ownerName = (int *)emptyString;
        beMessenger_AppendString((beMessenger *)manager->_messenger, (const char *)ownerName);
        beMessenger_AppendString((beMessenger *)manager->_messenger, (const char *)self->_seqName);
        if (ram->_dataList == 0) {
            int own = (int)igObject_GetAllocator(ram);
            RamDataList::create(ram, g_useOwnerAllocator != 0 ? own : (int)Memory_GetAllocatorBySelector(kIGMemoryPoolHandleUser1));
        }
        work = (beModelCtrlInfoWork *)((beModelCtrlInfoRamData *)igProperty_FindByName((igObjectList *)ram->_dataList, g_propertyNameField, "ONE"))->_work;
        if (work->_hitParentName == 0) {
            name = (int *)info->_name;
            if (name != 0) ownerName = name; else ownerName = (int *)emptyString;
            beMessenger_AppendString((beMessenger *)manager->_messenger, (const char *)ownerName);
            beMessenger_AppendInt((beMessenger *)manager->_messenger, ram->_ramNo);
        } else {
            beMessenger_AppendString((beMessenger *)manager->_messenger, (const char *)work->_hitParentName);
            beMessenger_AppendInt((beMessenger *)manager->_messenger, work->_hitParentRamNo);
        }
        offset[0] = self->_offset[0];
        offset[1] = self->_offset[1];
        offset[2] = self->_offset[2];
        beMessenger_AppendVec3((beMessenger *)manager->_messenger, offset);
        rotation[0] = self->_rotation[0];
        rotation[1] = self->_rotation[1];
        rotation[2] = self->_rotation[2];
        beMessenger_AppendVec3((beMessenger *)manager->_messenger, rotation);
        beMessenger_AppendBool((beMessenger *)manager->_messenger, self->_isPositionLock);
        beMessenger_DispatchSelected((beMessenger *)manager->_messenger, "GENERATE");
    } else {
        return 0;
    }
    return self->_isSeqDead != 0;
}

/* Stop: erases the sequence on the gene model once it has started. */
void beModelCtrlSCEffect_Stop(beModelCtrlSCEffect *self, beBaseInfoRam *ram) {
    int geneRamNo;

    if (self->_isOneSet != 0) {
        geneRamNo = self->_geneRamNo;
        if (geneRamNo != -1) {
            beMessenger_SendNamed((beMessenger *)((beBaseInfoManager *)ram->_parentManager)->_messenger, "MODELCTRL", (const char *)self->_modelName, geneRamNo, "SQ_ERAS");
        }
    }
}

/* Start: plays _sndName; the sub-command lives on while the sound handle is valid. */
int beModelCtrlSCSound_Start(beModelCtrlSCSound *self, beBaseInfoRam *ram) {
    beBaseInfoManager *manager = (beBaseInfoManager *)ram->_parentManager;
    long long handle;
    beMessenger_SelectGroup((beMessenger *)manager->_messenger, "SOUND");
    beMessenger_AppendString((beMessenger *)manager->_messenger, (const char *)self->_sndName);
    beMessenger_DispatchSelected((beMessenger *)manager->_messenger, "PLAY");
    handle = beMessenger_GetLong((beMessenger *)manager->_messenger, 0);
    if (handle == -1) {
        return 0;
    }
    if (handle == 0) {
        return 0;
    }
    if (beMessenger_GetInt((beMessenger *)manager->_messenger, 0) != 4) {
        return 0;
    }
    self->_sndHandle = handle;
    return 1;
}

/* Stop: fades the playing sound down. */
void beModelCtrlSCSound_Stop(beModelCtrlSCSound *self, beBaseInfoRam *ram) {
    beBaseInfoManager *manager = (beBaseInfoManager *)ram->_parentManager;
    if (self->_sndHandle != 0) {
        beMessenger_SelectGroup((beMessenger *)manager->_messenger, "SOUND");
        beMessenger_AppendString((beMessenger *)manager->_messenger, "DOWN");
        beMessenger_AppendLong((beMessenger *)manager->_messenger, self->_sndHandle);
        beMessenger_DispatchSelected((beMessenger *)manager->_messenger, "VOLUMECTL");
    }
}

/* Advances the run frame; starts the sub-command once it reaches _startFrame and updates it after.
 * Returns 0 when the sub-command has finished. */
unsigned char beModelCtrlSubComBase_Advance(beModelCtrlSubComBase *self, beBaseInfoRam *ram) {
    float runFrame;
    unsigned char alive;

    runFrame = self->_runFrame + ((beSystem *)((beBaseInfoManager *)ram->_parentManager)->_system)->_frameTimeF;
    self->_runFrame = runFrame;
    alive = 1;
    if (self->_isOneSet == 0) {
        if (!(runFrame < self->_startFrame)) {
            self->_isOneSet = 1;
            alive = ((beModelCtrlSubComDispatchView *)self)->Start(ram, 1);
        }
    } else {
        alive = ((beModelCtrlSubComDispatchView *)self)->Update(ram, 1);
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
            if (beModelCtrlSubComBase_Advance(((beModelCtrlSubComBase **)((igObjectList *)self->_comList)->_data)[i], ram) == 0) {
                list = (igObjectList *)(self->_comList);
                igRelease(((igObject **)list->_data)[i]);
                List_RemoveWordAt((igDataList *)list, i);
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
    beModelCtrlSubComDispatchView *command;
    int j;
    int k;
    int n;
    igMetaObject *effectMeta;

    n = ((igObjectList *)self->_comList)->_count;
    i = 0;
    if (0 < n) {
        do {
            effectMeta = g_beModelCtrlSCEffect_metaObject;
            command = ((beModelCtrlSubComDispatchView **)((igObjectList *)self->_comList)->_data)[i];
            if (effectMeta != command->GetMeta() || ((beModelCtrlSCEffect *)command)->_isSeqDead != 0) {
                command->Stop(ram);
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
void beModelCtrlSubCom_StopType(beModelCtrlSubCom *self, beBaseInfoRam *ram, igMetaObject *metaObject) {
    int count; int i; beModelCtrlSubComDispatchView *command; igObjectList *list;
    count = ((igObjectList *)self->_comList)->_count;
    i = 0;
    if (count > 0) {
        do {
            command = ((beModelCtrlSubComDispatchView **)((igObjectList *)self->_comList)->_data)[i];
            if (metaObject == command->GetMeta()) {
                command->Stop(ram);
                list = (igObjectList *)self->_comList;
                igRelease(((igObject **)list->_data)[i]);
                List_RemoveWordAt((igDataList *)list, i);
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
    if (g_stringPool == 0) {
        pool = (int)StringPool_Allocate(0x10);
        if (pool != 0) {
            pool = (int)StringPool_Construct((StringPool *)pool);
        }
        g_stringPool = (StringPool *)pool;
    }
    interned = (int *)StringPool_Intern(g_stringPool, (const char *)text);
    old = (int *)*field;
    if (old != 0) {
        header = old - 2;
        refs = old[-1] - 1;
        old[-1] = refs;
        if (refs == 0) {
            StringChunk_ReleaseHeader((StringChunk *)*header, (StringTokenHeader *)header);
        }
    }
    *field = (int)interned;
}

/* Appends an effect sub-command with interned model and sequence names. */
void beModelCtrlSubCom_AddEffect(beModelCtrlSubCom *self, const char *modelName, const char *seqName, float startFrame, const igVec3f &offset, igVec3f rotation, unsigned char isSeqDead, unsigned char isPositionLock) {
    int own;
    beModelCtrlSCEffect *record;
    own = (int)igObject_GetAllocator(self);
    igSmartPointer<beModelCtrlSCEffect> effect(beModelCtrlSCEffect_Create(g_useOwnerAllocator != 0 ? own : (int)Memory_GetAllocatorBySelector(kIGMemoryPoolHandleUser1)));
    record = effect.p;
    setInternedString(&record->_modelName, (int)modelName);
    effect.p->_geneRamNo = -1;
    record = effect.p;
    setInternedString(&record->_seqName, (int)seqName);
    effect.p->_startFrame = startFrame;
    record = effect.p;
    record->_offset[0] = offset.x;
    record->_offset[1] = offset.y;
    record->_offset[2] = offset.z;
    record = effect.p;
    record->_rotation[0] = rotation.x;
    record->_rotation[1] = rotation.y;
    record->_rotation[2] = rotation.z;
    effect.p->_isSeqDead = isSeqDead;
    effect.p->_isPositionLock = isPositionLock;
    ObjectList_AppendRetained((igObjectList *)self->_comList, (igObject *)effect.p);
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

    allocator = (int)igObject_GetAllocator(self);
    allocator = (g_useOwnerAllocator != 0) ? allocator : (int)Memory_GetAllocatorBySelector(kIGMemoryPoolHandleUser1);
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
    ObjectList_AppendRetained((igObjectList *)self->_comList, (igObject *)command.p);
}

/* Appends a sound sub-command with an interned sound name. */
void beModelCtrlSubCom_AddSound(beModelCtrlSubCom *self, const char *sndName, float startFrame) {
    int *header;
    int refs;
    int allocator;
    const char *name;
    int pool;
    int *old;
    beModelCtrlSCSound *sound;

    name = sndName;
    allocator = (int)igObject_GetAllocator(self);
    allocator = (g_useOwnerAllocator != 0) ? allocator : (int)Memory_GetAllocatorBySelector(kIGMemoryPoolHandleUser1);
    igSmartPointer<beModelCtrlSCSound> command(beModelCtrlSCSound_Create(allocator));
    sound = command.p;
    if (g_stringPool == 0) {
        pool = (int)StringPool_Allocate(0x10);
        if (pool != 0) {
            pool = (int)StringPool_Construct((StringPool *)pool);
        }
        g_stringPool = (StringPool *)pool;
    }
    name = (const char *)StringPool_Intern(g_stringPool, name);
    old = (int *)sound->_sndName;
    if (old != 0) {
        header = old - 2;
        refs = old[-1] - 1;
        old[-1] = refs;
        if (refs == 0) {
            StringChunk_ReleaseHeader((StringChunk *)*header, (StringTokenHeader *)header);
        }
    }
    sound->_sndName = (int)name;
    command.p->_startFrame = startFrame;
    ObjectList_AppendRetained((igObjectList *)self->_comList, (igObject *)command.p);
}

igMetaObject *beModelCtrlSCSound_GetMeta(void)
{
    return g_beModelCtrlSCSound_metaObject;
}

igMetaObject *beModelCtrlSCEffect_GetMeta(void)
{
    return g_beModelCtrlSCEffect_metaObject;
}

igMetaObject *beModelCtrlSCHitBox_GetMeta(void)
{
    return g_beModelCtrlSCHitBox_metaObject;
}

#pragma pop
