/* beCri: the CRI sound controller. It owns the BGM and ambience stream handles and the pool of effect
 * handles (beCriHandle: a beCriAudio voice, a beCriVolume fade and the play id of the cue it plays),
 * plays, stops, fades and pauses them for beSound, transfers the sound banks (beCriSfpData) to the
 * sound IOP module, and installs the ADX file system. The file opens with the traversal callbacks of the
 * copy nodes beCopyModelCtrl2 and beCopyTransform. See docs/engine/sound-format.md. */
#include "dw4/reflected.h"
#include "dw4/igTDataList.h"
#include "dw4/igSmartPointer.h"

extern "C" {
/* scene graph */
int igAttrStackManager_MarkStackChanged(igAttrStackManager *manager, igAttrStack *stack, int index);
int igTraversal_TraverseChildren(igCommonTraversal *traversal, void *node);
int igTraversal_RegisterFunction(int table, igMetaObject *meta, void (*function)());
int igObjectPool_Grow(igObjectPool *pool, void *create);
int FUN_001356b0(...);
int igTimeAttr_CreateInstance(...);
int igMatrix44f_SetIdentity(void *matrix);
int FUN_001904f0(void *result, void *left, void *right);
int igMatrix44f_Copy(void *to, void *from);
igMetaObject *FUN_003680b0(void);
igMetaObject *FUN_00367e50(void);
extern int DAT_00562640[4];
extern igMetaObject *g_igModelViewMatrixAttr_metaObject[4];

/* object system */
void *Memory_GetAllocatorBySelector(int selector);
void *igObject_GetAllocator(void *object);
int igObject_IsKindOf(int object, int meta);
int igNamedObject_SetName(...);
int ObjectList_AppendRetained(...);
int ObjectList_RemoveFirstRetained(...);
int List_Reserve(...);
int List_RemoveWordAt(igObjectList *list, int index);
int Memory_FreeBuffer(...);
int igMetaObject_FindFieldByName(int meta, const char *name);
int igMemoryRefMetaField_SetAlignmentType(int field, const char *name);
int igResource_AddAlignment(int context, const char *name, int alignment);
void igInsightCore_AddToScheduler(int insight, beCri *component);
int igInsightCore_RemoveFromScheduler(...);
int igInsightCore_FindManager(int insight, int meta);
int igRegistry_GetSectionIndex(int registry, const char *section, int create);
int igRegistry_GetValueStringObj(int registry, int section, const char *key, igSmartPointer<igStringObj> *value, const char *fallback, int flags);
igStringObj *igStringObj_Create(void *allocator);
void igStringObj_Set(...);
int igStringObj_StripDirectory(igNamedObject *);
int igStringObj_ToLower(igNamedObject *);
int strcmp(...);
int strlen(...);
extern int kIGMemoryPoolHandleUser1[4];
extern int kIGMemoryPoolHandleUser0[4];
extern unsigned char g_useOwnerAllocator;
extern int g_globalContext[4];
extern int g_igMemoryRefMetaField_metaObject[4];
extern char *g_stringObjEmptyText[4];
extern char emptyString[];

/* the ADX library */
void igAdx_SetModulePath(const char *path);
void igAdx_SetHostRootPath(int);
void igAdx_Initialize(int);
int igAdx_ExecServer(...);
int igAdx_SetPartitionCount(int count);
int igAdx_SetInsideFiles(int files);
int igAdx_LoadPartition(int partition, const char *path, int mode, int fileCount);
void igAdx_AddPartitionName(int partition, const char *name);
int igAdxAudio_GetStatus(int adxt);
extern int g_adxMediaMode[4];
extern int g_adxPartitionCount[4];
extern unsigned char g_adxUseFileInfoCache;
extern int g_igAdxFile_metaObject[4];
extern igMetaObject *g_igFile_metaObject[4];

/* the sound IOP module */
int FUN_00280f60(void *sizes);
int FUN_00281078(int port, int buffer);
int FUN_002813c8(int port);
int FUN_00281cf8(...);
void FUN_002829f0(int command, int value);
int FUN_002825e0(int channel, unsigned int command, int value);

/* the voices */
beCriHandle *beCriHandle_Create(void *allocator);
int beCriAudio_Setup(int audio, int channels);
int beCriAudio_Release(int audio);
int beCriAudio_PlayFile(...);
int beCriAudio_PlayMemory(beCriAudio *, void *, int);
int beCriAudio_PlaySfp(beCriAudio *, int, int);
int beCriAudio_Stop(beCriAudio *);
int beCriAudio_SetVolume(...);
int beCriAudio_GetStatus(...);
int beCriAudio_Pause(...);
int beCriAudio_IsPaused(...);
int beCriAudio_Suspend(...);
int beCriAudio_Resume(...);
void beCriVolume_StartFade(beCriVolume *, int, float, float, float);
int beCriVolume_StepAdxLevel(...);
int beCriVolume_StepSndfLevel(...);

extern int g_beCri_metaObject[4];
extern int g_beSystem_metaObject[4];
extern int g_beCriFxInfo_metaObject[4];
extern int g_beCriSfpData_metaObject[4];
extern int g_beCriAcxData_metaObject[4];

extern char BECRUNTIME[];
extern char AdxModulePath[];
extern char g_adxModulePathDefault[];
extern char text_9_31s281[];
extern char text_9_18[];
extern char C_cri_ps2_iop_modules[];
extern char C_usr_local_cri_mwlib_iop_drv[];
extern char NONE[];
extern char ALL[];
extern char sndfBuffer[];
extern char _dataBuffer[];
extern int g_savedIgFileAbstractProxy[4];
extern int g_sfpTransferState[4];
}

/* The two tables handed to the sound IOP module: per port, a bank's table size and its PCM size. */
struct SfpPortSizes {
    int tblSize[32];
    int pcmSize[32];
};
extern "C" SfpPortSizes g_sfpPortSizes;

/* The classes whose virtual functions this file calls, seen through the slots it calls. */
/* igModelViewMatrixAttr: slot 30 stores the matrix. */
class ModelViewMatrixAttrView {
public:
    virtual void s0(); virtual void s1(); virtual void s2(); virtual void s3(); virtual void s4();
    virtual void s5(); virtual void s6(); virtual void s7(); virtual void s8(); virtual void s9();
    virtual void s10(); virtual void s11(); virtual void s12(); virtual void s13(); virtual void s14();
    virtual void s15(); virtual void s16(); virtual void s17(); virtual void s18(); virtual void s19();
    virtual void s20(); virtual void s21(); virtual void s22(); virtual void s23(); virtual void s24();
    virtual void s25(); virtual void s26(); virtual void s27(); virtual void s28(); virtual void s29();
    virtual void setMatrix(void *matrix);
};
/* igCommonTraversal: slot 30 takes the time a subtree runs at, slot 31 drops it again. */
class CommonTraversalView {
public:
    virtual void s0(); virtual void s1(); virtual void s2(); virtual void s3(); virtual void s4();
    virtual void s5(); virtual void s6(); virtual void s7(); virtual void s8(); virtual void s9();
    virtual void s10(); virtual void s11(); virtual void s12(); virtual void s13(); virtual void s14();
    virtual void s15(); virtual void s16(); virtual void s17(); virtual void s18(); virtual void s19();
    virtual void s20(); virtual void s21(); virtual void s22(); virtual void s23(); virtual void s24();
    virtual void s25(); virtual void s26(); virtual void s27(); virtual void s28(); virtual void s29();
    virtual void pushTime(long long time);
    virtual void popTime();
};
/* igObject: slot 20 returns the object's meta object. */
class MetaObjectView {
public:
    virtual void s0(); virtual void s1(); virtual void s2(); virtual void s3(); virtual void s4();
    virtual void s5(); virtual void s6(); virtual void s7(); virtual void s8(); virtual void s9();
    virtual void s10(); virtual void s11(); virtual void s12(); virtual void s13(); virtual void s14();
    virtual void s15(); virtual void s16(); virtual void s17(); virtual void s18(); virtual void s19();
    virtual int getMetaObject();
};

typedef void (*AttrPopProc)(void *attr, int data);
struct Matrix { float m[16]; };
/* The registry the object system reads its ini settings into. */
struct ObjectSystemView { char pad[56]; int registry; };
extern "C" ObjectSystemView *g_objectSystem[4];

extern "C" {
int beCopyModelCtrl2_TraverseCallback(igCommonTraversal *traversal, beCopyModelCtrl2 *node);
int beCopyModelCtrl2_Traverse(beCopyModelCtrl2 *node, igCommonTraversal *traversal);
void beCopyModelCtrl2_RegisterTraversal(void);
int beCopyTransform_TraverseCallback(igCommonTraversal *traversal, beCopyTransform *node);
int beCopyTransform_Traverse(beCopyTransform *node, igCommonTraversal *traversal);
void beCopyTransform_RegisterTraversal(void);
void Gap__Bec__beCri__vfunc_21(beCri *self);
int beCri_AdxFileProxy(void);
void Gap__Bec__beCri__vfunc_22(beCri *self);
void Gap__Bec__beCri__vfunc_23(beCri *self);
void Gap__Bec__beCri__vfunc_24(beCri *self);
int Gap__Bec__beCri__vfunc_25(beCri *self, MetaObjectView *info);
void Gap__Bec__beCri__vfunc_26(beCri *self);
void Gap__Bec__beCri__vfunc_27(beCri *self);
int beCri_AcquireVoice(beCri *self, unsigned char kind, short priority);
long long beCri_PlayStream(beCri *self, igObjectList *names, beSoundData *cue);
long long beCri_PlayEffect(beCri *self, igObjectList *names, beSoundData *cue);
void beCri_StopHandle(beCri *self, beCriHandle *handle);
void beCri_StopByID(beCri *self, long long playID);
void beCri_StopGroup(beCri *self, int group);
void beCri_UnpauseByName(beCri *self, const char *name);
void beCri_FadeByName(beCri *self, char *name, float from, float to, float frames);
void beCri_FadeByID(beCri *self, long long playID, float from, float to, float frames);
void beCri_SetupPartitions(beCri *self, int count, int insideFiles);
void beCri_LoadPartition(beCri *self, int partition, const char *path, int fileCount);
void beCri_ReleasePartitions(beCri *self);
void beCri_CreateEffectVoices(beCri *self);
void beCri_ReleaseEffectVoices(beCri *self);
void beCri_SetFreezeAudible(beCri *self, int audible);
int beCri_TransferSfp(beCri *self, beCriSfpData *bank);
bool beCri_StartSfpTransfers(beCri *self);
int beCri_FreeSfpData(beCri *self, int includeFirst);
bool beCri_IsTransferDone(beCri *self);
void beCri_SetFx(beCri *self, char *name);
unsigned char beCri_IsReady(beCri *self, const char *name);
void beCri_SetSndfVolume(beCri *self, int volume);
void beCriSfpData_SetupBufferAlignment(void);
int Gap__Bec__beCri__vfunc_20(void);
}

/* A name field read as text: a null name reads as "". */
static inline char *NameOf(char *text) { return text != 0 ? text : emptyString; }
static inline char *NameOf(int name) { return NameOf((char *)name); }
static inline igObjectList *Handles(beCri *self) { return (igObjectList *)self->_hdSEs; }
static inline beCriHandle *HandleAt(igObjectList *list, int i) { return ((beCriHandle **)list->_data)[i]; }
static inline beCriHandle *Bgm(beCri *self) { return (beCriHandle *)self->_hdBGM; }
static inline beCriHandle *Env(beCri *self) { return (beCriHandle *)self->_hdENV; }
static inline igObjectList *Banks(beCri *self) { return (igObjectList *)self->_lsBinObjs; }
static inline beCriSfpData *BankAt(igObjectList *list, int i) { return ((beCriSfpData **)list->_data)[i]; }

/* The allocator the controller's handles come from: its own, or the NDMW allocator. */
static inline void *HandleAllocator(beCri *self) {
    void *allocator = igObject_GetAllocator(self);
    return g_useOwnerAllocator ? allocator : Memory_GetAllocatorBySelector(kIGMemoryPoolHandleUser0[0]);
}

/* The next free object of a traversal's pool, which `create` grows when it is used up. */
static inline void *TakePooled(igObjectPool *pool, void *create) {
    if (pool->_freeIndex >= pool->_count) {
        igObjectPool_Grow(pool, create);
    }
    int slot = pool->_freeIndex;
    pool->_freeIndex = slot + 1;
    return ((void **)pool->_data)[slot];
}

/* Pops the top attribute of the attribute stack at `index`, through the stack's pop procedure. */
static inline void PopAttr(igAttrStackManager *attrs, int index) {
    igAttrStack *top = ((igAttrStack **)((igObjectList *)attrs->_attrStacks)->_data)[index];
    int last = top->_count - 1;
    AttrPopProc pop = (AttrPopProc)top->_popProc;
    void *popped = ((void **)top->_data)[last];
    if (pop != 0) {
        pop(popped, attrs->_popProcData);
    }
    top->_count = top->_count - 1;
    igAttrStackManager_MarkStackChanged(attrs, top, index);
}

/* Releases every object of a retained list and leaves it empty. */
static inline void ReleaseAll(igObjectList *list) {
    int count = list->_count;
    int i;
    for (i = 0; i < count; i++) {
        igObject *object = ((igObject **)list->_data)[i];
        igRelease(object);
    }
    int remaining = list->_count;
    int j;
    for (j = 0; j < remaining; j++) {
        ((igObject **)list->_data)[j] = 0;
    }
    list->_count = 0;
}

/* Gives an emptied list its first block again. */
static inline void ReserveIfEmpty(igObjectList *list) {
    bool hasEntries = list->_count > 0;
    if (hasEntries == false) {
        List_Reserve(list, 0, 4);
    }
}

int beCopyModelCtrl2_TraverseCallback(igCommonTraversal *traversal, beCopyModelCtrl2 *node) {
    return beCopyModelCtrl2_Traverse(node, traversal);
}

/* Takes the source node's matrix and clock, pushes the composed model-view matrix and the clock as
 * attributes for the children, and pops both after them. */
int beCopyModelCtrl2_Traverse(beCopyModelCtrl2 *node, igCommonTraversal *traversal)
{
    igAttrStackManager *attrs;
    int timeIndex;
    Matrix modelView;
    Matrix identity;
    long long time;
    igObjectPool *matrixPool;
    igObjectPool *timePool;
    ModelViewMatrixAttrView *matrixAttr;
    igTimeAttr *timeAttr;
    igAttrStack *stack;
    int matrixIndex;
    int result;
    int attrId;
    short *matrixAttrIndex;
    short *matrixUnitID;
    short *timeAttrIndex;
    short *timeUnitID;
    int depth;

    attrs = (igAttrStackManager *)traversal->_attrStack;
    attrId = g_igModelViewMatrixAttr_metaObject[0]->_id;
    stack = ((igAttrStack **)((igObjectList *)attrs->_attrStacks)->_data)[((int *)attrs->_attrStackIndexTable)[attrId]];
    igMatrix44f_Copy(node->_m, ((beModelCtrlNode2 *)node->_srcNode)->_m);
    time = ((beModelCtrlNode2 *)node->_srcNode)->_time;
    igMatrix44f_SetIdentity(&modelView);
    if (stack->_count != 0) {
        depth = stack->_count - 1;
        FUN_001904f0(&modelView, node->_m, (char *)((void **)stack->_data)[depth] + 12);
    } else {
        igMatrix44f_SetIdentity(&identity);
        FUN_001904f0(&modelView, node->_m, &identity);
    }
    matrixPool = (igObjectPool *)traversal->_matrixPool;
    matrixAttr = (ModelViewMatrixAttrView *)TakePooled(matrixPool, (void *)&FUN_001356b0);
    matrixAttr->setMatrix(&modelView);
    timePool = (igObjectPool *)traversal->_timePool;
    timeAttr = (igTimeAttr *)TakePooled(timePool, (void *)&igTimeAttr_CreateInstance);
    timeAttr->_time = time;
    ((CommonTraversalView *)traversal)->pushTime(time);
    matrixAttrIndex = &((igAttr *)matrixAttr)->_cachedAttrIndex;
    matrixUnitID = &((igAttr *)matrixAttr)->_cachedUnitID;
    matrixIndex = *matrixUnitID + ((int *)attrs->_attrStackIndexTable)[*matrixAttrIndex];
    stack = ((igAttrStack **)((igObjectList *)attrs->_attrStacks)->_data)[matrixIndex];
    ((igTDataList<ModelViewMatrixAttrView *> *)stack)->append(matrixAttr);
    igAttrStackManager_MarkStackChanged(attrs, stack, matrixIndex);
    timeAttrIndex = &timeAttr->_cachedAttrIndex;
    timeUnitID = &timeAttr->_cachedUnitID;
    timeIndex = *timeUnitID + ((int *)attrs->_attrStackIndexTable)[*timeAttrIndex];
    stack = ((igAttrStack **)((igObjectList *)attrs->_attrStacks)->_data)[timeIndex];
    ((igTDataList<igTimeAttr *> *)stack)->append(timeAttr);
    igAttrStackManager_MarkStackChanged(attrs, stack, timeIndex);
    result = igTraversal_TraverseChildren(traversal, node);
    PopAttr(attrs, *timeUnitID + ((int *)attrs->_attrStackIndexTable)[*timeAttrIndex]);
    PopAttr(attrs, *matrixUnitID + ((int *)attrs->_attrStackIndexTable)[*matrixAttrIndex]);
    ((CommonTraversalView *)traversal)->popTime();
    if (result == 2) {
        return 2;
    }
    return 0;
}

void beCopyModelCtrl2_RegisterTraversal(void) {
    igTraversal_RegisterFunction(DAT_00562640[0], FUN_003680b0(), (void (*)())beCopyModelCtrl2_TraverseCallback);
}

int beCopyTransform_TraverseCallback(igCommonTraversal *traversal, beCopyTransform *node)
{
    return beCopyTransform_Traverse(node, traversal);
}

/* Takes the source transform's matrix and pushes the composed model-view matrix for the children. */
int beCopyTransform_Traverse(beCopyTransform *node, igCommonTraversal *traversal)
{
    igAttrStackManager *attrs;
    Matrix modelView;
    Matrix identity;
    igObjectPool *matrixPool;
    ModelViewMatrixAttrView *matrixAttr;
    igAttrStack *stack;
    int index;
    int result;
    int attrId;
    short *attrIndex;
    short *unitID;
    igAttrStack *matrices;
    int depth;

    attrs = (igAttrStackManager *)traversal->_attrStack;
    attrId = g_igModelViewMatrixAttr_metaObject[0]->_id;
    matrices = ((igAttrStack **)((igObjectList *)attrs->_attrStacks)->_data)[((int *)attrs->_attrStackIndexTable)[attrId]];
    igMatrix44f_Copy(node->_m, ((igTransform *)node->_srcTransform)->_m);
    igMatrix44f_SetIdentity(&modelView);
    if (matrices->_count != 0) {
        depth = matrices->_count - 1;
        FUN_001904f0(&modelView, node->_m, (char *)((void **)matrices->_data)[depth] + 12);
    } else {
        igMatrix44f_SetIdentity(&identity);
        FUN_001904f0(&modelView, node->_m, &identity);
    }
    matrixPool = (igObjectPool *)traversal->_matrixPool;
    matrixAttr = (ModelViewMatrixAttrView *)TakePooled(matrixPool, (void *)&FUN_001356b0);
    matrixAttr->setMatrix(&modelView);
    attrIndex = &((igAttr *)matrixAttr)->_cachedAttrIndex;
    unitID = &((igAttr *)matrixAttr)->_cachedUnitID;
    stack = (igAttrStack *)attrs->_attrStacks;
    index = *attrIndex;
    index = *unitID + ((int *)attrs->_attrStackIndexTable)[index];
    stack = ((igAttrStack **)stack->_data)[index];
    ((igTDataList<ModelViewMatrixAttrView *> *)stack)->append(matrixAttr);
    igAttrStackManager_MarkStackChanged(attrs, stack, index);
    result = igTraversal_TraverseChildren(traversal, node);
    PopAttr(attrs, *unitID + ((int *)attrs->_attrStackIndexTable)[*attrIndex]);
    if (result == 2) {
        return 2;
    }
    return 0;
}

void beCopyTransform_RegisterTraversal(void) {
    igTraversal_RegisterFunction(DAT_00562640[0], FUN_00367e50(), (void (*)())beCopyTransform_TraverseCallback);
}

/* Attach: registers with the insight, reads the IOP module path from the BECRUNTIME ini section (else
 * the CRI default for the library version), starts the ADX library on DVD media, and routes igFile
 * through igAdxFile. */
void Gap__Bec__beCri__vfunc_21(beCri *self) {
    int section;
    int registry;
    igInsightCore_AddToScheduler(self->_insight, self);
    registry = g_objectSystem[0]->registry;
    if (registry == 0) return;
    section = igRegistry_GetSectionIndex(registry, BECRUNTIME, 0);
    if (section == -1) return;
    void *allocator = igObject_GetAllocator(self);
    allocator = g_useOwnerAllocator ? allocator : Memory_GetAllocatorBySelector(kIGMemoryPoolHandleUser1[0]);
    igSmartPointer<igStringObj> path(igStringObj_Create(allocator));
    if (igRegistry_GetValueStringObj(registry, section, AdxModulePath, &path, g_adxModulePathDefault, 0) == 0) {
        if (strcmp(text_9_31s281, text_9_18) == 0)
            igStringObj_Set((igStringObj *)path, C_cri_ps2_iop_modules);
        else
            igStringObj_Set((igStringObj *)path, C_usr_local_cri_mwlib_iop_drv);
    }
    char *text = (char *)path->_buffer;
    igAdx_SetModulePath(text == 0 ? g_stringObjEmptyText[0] : text);
    g_adxUseFileInfoCache = 1;
    igAdx_SetHostRootPath(0);
    g_adxMediaMode[0] = 2;
    igAdx_Initialize(1);
    igMetaObject *file = g_igFile_metaObject[0];
    g_savedIgFileAbstractProxy[0] = file->_abstractProxy;
    file->_abstractProxy = (int)beCri_AdxFileProxy;
}

/* igFile's abstract proxy while the controller is attached: files open as igAdxFile. */
int beCri_AdxFileProxy(void) {
    return g_igAdxFile_metaObject[0];
}

/* Detach: restores igFile's proxy and leaves the insight. */
void Gap__Bec__beCri__vfunc_22(beCri *self) {
    g_igFile_metaObject[0]->_abstractProxy = g_savedIgFileAbstractProxy[0];
    igInsightCore_RemoveFromScheduler(self->_insight, self);
}

/* Start: finds the beSystem, creates the BGM and ambience stream handles (two-channel ADX) and the
 * effect handles, and clears the sound-bank port tables. */
void Gap__Bec__beCri__vfunc_23(beCri *self) {
    void *allocator;
    void *ambienceAllocator;
    beCriHandle *old;
    int i;

    self->_system = igInsightCore_FindManager(self->_insight, g_beSystem_metaObject[0]);
    allocator = HandleAllocator(self);
    old = Bgm(self);
    igRelease(old);
    self->_hdBGM = (int)beCriHandle_Create(allocator);
    beCriAudio_Setup(Bgm(self)->_audio, 2);
    igNamedObject_SetName(self->_hdBGM, 0);
    ambienceAllocator = HandleAllocator(self);
    old = Env(self);
    igRelease(old);
    self->_hdENV = (int)beCriHandle_Create(ambienceAllocator);
    beCriAudio_Setup(Env(self)->_audio, 2);
    igNamedObject_SetName(self->_hdENV, 0);
    beCri_CreateEffectVoices(self);
    self->_pauseOnetime = 0;
    for (i = 0; i < 32; i++) {
        g_sfpPortSizes.tblSize[i] = 0;
        g_sfpPortSizes.pcmSize[i] = 0;
        g_sfpTransferState[i] = 0;
    }
}

/* Stop: stops every handle and releases the voices. */
void Gap__Bec__beCri__vfunc_24(beCri *self) {
    beCri_StopGroup(self, 5);
    beCriAudio_Release(Bgm(self)->_audio);
    beCriAudio_Release(Env(self)->_audio);
    beCri_ReleaseEffectVoices(self);
}

/* Takes a beCriFxInfo into the effect list. */
int Gap__Bec__beCri__vfunc_25(beCri *self, MetaObjectView *info) {
    int meta;

    meta = g_beCriFxInfo_metaObject[0];
    if (meta == info->getMetaObject()) {
        ObjectList_AppendRetained(self->_infoList, info);
        return 1;
    }
    return 0;
}

/* Reset: turns the effect off, empties the effect list and frees the sound banks. */
void Gap__Bec__beCri__vfunc_26(beCri *self) {
    beCri_SetFx(self, NONE);
    ReleaseAll((igObjectList *)self->_infoList);
    ReserveIfEmpty((igObjectList *)self->_infoList);
    beCri_FreeSfpData(self, 0);
}

/* Update, once a frame: while beSystem reports a disc error every playing handle is suspended, and
 * resumed once it clears; otherwise each playing handle's fade steps, and a handle whose voice has
 * stopped, or whose fade to silence has passed audibility, is stopped. The BGM and ambience handles
 * join the effect list for the walk. */
void Gap__Bec__beCri__vfunc_27(beCri *self) {
    int removed0, removed1, removed2, removed3, removed4, removed5;
    int i;
    int j;
    int k;
    int level;
    beCriHandle *handle;
    beCriAudio *audio;
    beCriHandle *t;
    beCriVolume *volume;
    igAdx_ExecServer(1);
    if (self->_execDvdErr > 0) {
        if (((beSystem *)self->_system)->_execDvdErr == 0) {
            ObjectList_AppendRetained(Handles(self), self->_hdBGM);
            ObjectList_AppendRetained(Handles(self), self->_hdENV);
            for (i = 0; i < Handles(self)->_count; i++) {
                t = HandleAt(Handles(self), i);
                if (t->_playID != 0) beCriAudio_Resume((beCriAudio *)t->_audio);
            }
            ObjectList_RemoveFirstRetained(&removed0, Handles(self), self->_hdBGM, 0);
            ObjectList_RemoveFirstRetained(&removed1, Handles(self), self->_hdENV, 0);
            self->_execDvdErr = 0;
        }
    } else {
        if (((beSystem *)self->_system)->_execDvdErr > 0) {
            ObjectList_AppendRetained(Handles(self), self->_hdBGM);
            ObjectList_AppendRetained(Handles(self), self->_hdENV);
            for (j = 0; j < Handles(self)->_count; j++) {
                t = HandleAt(Handles(self), j);
                if (t->_playID != 0) beCriAudio_Suspend((beCriAudio *)t->_audio);
            }
            ObjectList_RemoveFirstRetained(&removed2, Handles(self), self->_hdBGM, 0);
            ObjectList_RemoveFirstRetained(&removed3, Handles(self), self->_hdENV, 0);
            self->_execDvdErr = 1;
            return;
        }
        ObjectList_AppendRetained(Handles(self), self->_hdBGM);
        ObjectList_AppendRetained(Handles(self), self->_hdENV);
        for (k = 0; k < Handles(self)->_count; k++) {
            handle = ((beCriHandle **)Handles(self)->_data)[k];
            if (handle->_playID == 0) continue;
            audio = (beCriAudio *)handle->_audio;
            volume = (beCriVolume *)handle->_volume;
            switch (beCriAudio_GetStatus(audio)) {
            case 1:
                if (beCriAudio_IsPaused(audio) == 0) {
                    switch (volume->_isExec) {
                    case 3: /* a fade runs */
                        if (audio->_audioType == 3) {
                            level = beCriVolume_StepSndfLevel(volume, self->_baseVolume);
                        } else {
                            level = beCriVolume_StepAdxLevel(volume, self->_baseVolume);
                        }
                        beCriAudio_SetVolume(audio, level);
                        if (volume->_end == 0.0f) {
                            if (audio->_audioType == 3) {
                                if (level < 13) beCri_StopHandle(self, handle);
                            } else if (level < -209) {
                                beCri_StopHandle(self, handle);
                            }
                        }
                        break;
                    }
                }
                break;
            case -1:
            case 0:
                beCri_StopHandle(self, handle);
                break;
            }
        }
        ObjectList_RemoveFirstRetained(&removed4, Handles(self), self->_hdBGM, 0);
        ObjectList_RemoveFirstRetained(&removed5, Handles(self), self->_hdENV, 0);
    }
}

/* The effect handle a play of `kind` (1 an ADX voice, 0 a sound-bank voice) and `priority` takes: the
 * first idle capable handle, else the oldest capable handle whose priority is not above the request's,
 * which is stopped. -1 when there is none. */
int beCri_AcquireVoice(beCri *self, unsigned char kind, short priority) {
    beCriHandle *handle; /* matching construct: declaration-order search — the handle and its audio declared before the lists */
    beCriAudio *audio;
    beCriHandleList *handles;
    beCriHandleList *list;
    beCriHandle *candidate;
    beCriAudio *candidateAudio;
    long long bestID;
    short bestPriority;
    int best;
    int i;
    handles = (beCriHandleList *)self->_hdSEs;
    for (i = 0, list = handles; i < list->_count; i++) {
        handle = ((beCriHandle **)list->_data)[i];
        audio = (beCriAudio *)handle->_audio;
        if (!(kind == 1 && audio->_adxt == 0) && !(kind == 0 && audio->_sndf == 0)) {
            if (handle->_playID == 0) return i;
        }
        /* matching construct: hand search — the list re-read from self each iteration keeps the element address unreduced */
        list = (beCriHandleList *)self->_hdSEs;
    }
    bestID = self->_request;
    bestPriority = 0x7fff;
    for (i = 0, list = handles; i < list->_count; i++) {
        candidate = ((beCriHandle **)list->_data)[i];
        candidateAudio = (beCriAudio *)candidate->_audio;
        if (!(kind == 1 && candidateAudio->_adxt == 0) && !(kind == 0 && candidateAudio->_sndf == 0)) {
            if (candidate->_priority <= priority && candidate->_playID < bestID && candidate->_priority <= bestPriority) {
                bestID = candidate->_playID;
                bestPriority = candidate->_priority;
                best = i;
            }
        }
        list = (beCriHandleList *)self->_hdSEs; /* matching construct: hand search — re-read as in the first scan */
    }
    if (best != -1) beCri_StopHandle(self, ((beCriHandle **)handles->_data)[best]);
    return best;
}

/* Plays a music (type 1) or ambience (type 2) cue on its stream handle. While the handle's voice still
 * plays, a 10-frame fade-out is armed instead and 0 returned, so beSound retries. Returns the play id,
 * 0 when nothing started. */
long long beCri_PlayStream(beCri *self, igObjectList *names, beSoundData *cue) {
    beCriHandle *handle;
    beCriAudio *audio;
    beCriVolume *volume;
    char *name;
    long long playID;
    if (cue->_memoryIdx != -1) return 0;
    handle = 0; audio = 0; volume = 0;
    switch (cue->_type) {
    case 4:
    case 3:
        return 0;
    case 1:
        handle = Bgm(self);
        audio = (beCriAudio *)handle->_audio;
        volume = (beCriVolume *)handle->_volume;
        break;
    case 2:
        handle = Env(self);
        audio = (beCriAudio *)handle->_audio;
        volume = (beCriVolume *)handle->_volume;
        break;
    }
    if (beCriAudio_GetStatus(audio) == 1) {
        if (volume->_isExec == 0) beCriVolume_StartFade(volume, self->_baseVolume, 1.0f, 0.0f, 10.0f);
        return 0;
    }
    volume->_max = cue->_volume;
    name = NameOf(((igNamedObject **)names->_data)[cue->_fnameIdx]->_name);
    beCriAudio_Pause(audio, 1);
    beCriAudio_SetVolume(audio, volume->_max + self->_baseVolume);
    if (beCriAudio_PlayFile(audio, name) & 0xff) {
        if (self->_pauseOnetime != 0) self->_pauseOnetime = 0; else beCriAudio_Pause(audio, 0);
        playID = self->_request + 1;
        self->_request = playID;
        handle->_playID = playID;
        handle->_type = cue->_type;
        name = NameOf(cue->_name);
        igNamedObject_SetName(handle, name);
        return playID;
    }
    return 0;
}

/* Plays an effect cue on an effect handle: memory index -1 streams the named ADX file; otherwise the cue's
 * bank is found by name and plays from memory (ADX banks, data type 0) or through the sound IOP module
 * (sound banks, data type 1, once transferred). Returns the play id, 0 when nothing started, -1 without
 * effect handles. */
long long beCri_PlayEffect(beCri *self, igObjectList *names, beSoundData *cue) {
    beCriSfpData *memoryBank;
    beCriAudio *memoryAudio;
    unsigned char ok;
    beCriAudio *fileAudio;
    beCriHandle *handle;
    beCriVolume *fileVolume;
    int found;
    long long playID;
    int i;
    beCriVolume *memoryVolume;
    beCriAudio *sfpAudio;
    int index;
    char *name;
    char *wanted;
    beCriSfpData *bank;
    if (Handles(self)->_count <= 0) return -1;
    switch (cue->_type) {
    case 1: return 0;
    case 2: return 0;
    default: break;
    }
    ok = 0;
    handle = 0;
    if (cue->_memoryIdx == -1) {
        index = beCri_AcquireVoice(self, 1, cue->_priority);
        if (index < 0 || index >= Handles(self)->_count) return 0;
        handle = HandleAt(Handles(self), index);
        fileAudio = (beCriAudio *)handle->_audio;
        fileVolume = (beCriVolume *)handle->_volume;
        fileVolume->_max = cue->_volume;
        name = NameOf(((igNamedObject **)names->_data)[cue->_fnameIdx]->_name);
        fileAudio->_audioType = 1;
        beCriAudio_Pause(fileAudio, 1);
        beCriAudio_SetVolume(fileAudio, fileVolume->_max + self->_baseVolume);
        ok = beCriAudio_PlayFile(fileAudio, name);
        if (ok) {
            if (self->_pauseOnetime) self->_pauseOnetime = 0; else beCriAudio_Pause(fileAudio, 0);
        }
    } else {
        if (Banks(self)->_count <= 0) return 0;
        name = NameOf(((igNamedObject **)names->_data)[cue->_fnameIdx]->_name);
        igSmartPointer<igStringObj> bankName((igStringObj *)((beSystem *)self->_system)->_globalStrObj, kRetainReference);
        igStringObj_Set(bankName.p, name);
        igStringObj_StripDirectory((igNamedObject *)bankName.p);
        igStringObj_ToLower((igNamedObject *)bankName.p);
        found = -1;
        for (i = 0; i < Banks(self)->_count; i++) {
            bank = BankAt(Banks(self), i);
            name = NameOf(bank->_name);
            wanted = (char *)bankName.p->_buffer;
            wanted = (wanted == 0) ? g_stringObjEmptyText[0] : wanted;
            if (strcmp(wanted, name) == 0) { found = i; break; }
        }
        if (found == -1) {
            return 0;
        }
        switch (self->_dataType) {
        case 0:
            memoryBank = ((beCriSfpData **)Banks(self)->_data)[found];
            if (memoryBank->_dataBuffer != 0) {
                index = beCri_AcquireVoice(self, 1, cue->_priority);
                if (index < 0 || index >= Handles(self)->_count) {
                    return 0;
                }
                handle = HandleAt(Handles(self), index);
                memoryAudio = (beCriAudio *)handle->_audio;
                memoryVolume = (beCriVolume *)handle->_volume;
                memoryVolume->_max = cue->_volume;
                memoryAudio->_audioType = 2;
                beCriAudio_Pause(memoryAudio, 1);
                beCriAudio_SetVolume(memoryAudio, memoryVolume->_max + self->_baseVolume);
                ok = beCriAudio_PlayMemory(memoryAudio, (void *)memoryBank->_dataBuffer, cue->_memoryIdx);
                if (self->_pauseOnetime) self->_pauseOnetime = 0;
                beCriAudio_Pause(memoryAudio, 0);
            } else {
                return 0;
            }
            break;
        case 1:
            if (((beCriSfpData **)Banks(self)->_data)[found]->_isTransfer != 0) {
                index = beCri_AcquireVoice(self, 0, cue->_priority);
                if (index < 0 || index >= Handles(self)->_count) {
                    return 0;
                }
                handle = HandleAt(Handles(self), index);
                sfpAudio = (beCriAudio *)handle->_audio;
                ((beCriVolume *)handle->_volume)->_max = cue->_volume;
                ok = beCriAudio_PlaySfp(sfpAudio, index, cue->_memoryIdx);
                if (ok) beCriAudio_SetVolume(sfpAudio, 127);
                if (self->_pauseOnetime) self->_pauseOnetime = 0;
            } else {
                return 0;
            }
            break;
        default:
            break;
        }
    }
    if (ok) {
        playID = self->_request + 1;
        self->_request = playID;
        handle->_playID = playID;
        handle->_type = cue->_type;
        name = NameOf(cue->_name);
        igNamedObject_SetName(handle, name);
        handle->_priority = cue->_priority;
        return playID;
    }
    return 0;
}

/* Stops a handle's voice, silences it and clears the handle. */
void beCri_StopHandle(beCri *self, beCriHandle *handle) {
    beCriAudio *audio;
    beCriVolume *volume;

    audio = (beCriAudio *)handle->_audio;
    volume = (beCriVolume *)handle->_volume;
    handle->_playID = 0;
    handle->_type = 0;
    volume->_isExec = 0;
    volume->_max = 0;
    volume->_current = 0;
    volume->_sta = 0;
    volume->_end = 0;
    if (audio->_audioType == 3) {
        beCriAudio_SetVolume(audio, 0);
    } else {
        beCriAudio_SetVolume(audio, -999);
    }
    beCriAudio_Stop(audio);
    igNamedObject_SetName(handle, 0);
}

/* Stops the handle playing `playID`. */
void beCri_StopByID(beCri *self, long long playID) {
    int i;
    beCriHandle *handle;

    handle = Bgm(self);
    if (playID == handle->_playID) {
        beCri_StopHandle(self, handle);
        return;
    }
    handle = Env(self);
    if (playID == handle->_playID) {
        beCri_StopHandle(self, handle);
        return;
    }
    for (i = 0; i < Handles(self)->_count; i++) {
        handle = HandleAt(Handles(self), i);
        if (playID == handle->_playID) {
            beCri_StopHandle(self, handle);
        }
    }
}

/* Stops a group of handles: 1 the BGM, 2 the ambience, 3 and 4 the effects, 5 (and any other) all. */
void beCri_StopGroup(beCri *self, int group) {
    int i;
    int j;

    switch (group) {
    case 1:
        beCri_StopHandle(self, Bgm(self));
        break;
    case 2:
        beCri_StopHandle(self, Env(self));
        break;
    case 3:
    case 4:
        for (i = 0; i < Handles(self)->_count; i++) {
            beCri_StopHandle(self, HandleAt(Handles(self), i));
        }
        break;
    case 5:
    default:
        beCri_StopHandle(self, Bgm(self));
        beCri_StopHandle(self, Env(self));
        for (j = 0; j < Handles(self)->_count; j++) {
            beCri_StopHandle(self, HandleAt(Handles(self), j));
        }
        break;
    }
}

/* Unpauses the BGM or ambience handle named `name`, else every effect handle of that name. */
void beCri_UnpauseByName(beCri *self, const char *name) {
    int i;
    beCriHandle *handle;

    if (strcmp(NameOf(Bgm(self)->_name), name) == 0) {
        beCriAudio_Pause(Bgm(self)->_audio, 0);
    } else {
        if (strcmp(NameOf(Env(self)->_name), name) == 0) {
            beCriAudio_Pause(Env(self)->_audio, 0);
        } else {
            for (i = 0; i < Handles(self)->_count; i++) {
                handle = HandleAt(Handles(self), i);
                if (NameOf(handle->_name) != 0 && strlen(NameOf(handle->_name)) != 0
                    && strcmp(NameOf(handle->_name), name) == 0) {
                    beCriAudio_Pause(handle->_audio, 0);
                }
            }
        }
    }
}

/* Arms a fade on the BGM or ambience handle named `name`, else on every effect handle of that name. */
void beCri_FadeByName(beCri *self, char *name, float from, float to, float frames) {
    int i;
    beCriHandle *handle;
    if (NameOf(Bgm(self)->_name) != 0 && strcmp(NameOf(Bgm(self)->_name), name) == 0) {
        beCriVolume_StartFade((beCriVolume *)Bgm(self)->_volume, self->_baseVolume, from, to, frames);
    } else if (NameOf(Env(self)->_name) != 0 && strcmp(NameOf(Env(self)->_name), name) == 0) {
        beCriVolume_StartFade((beCriVolume *)Env(self)->_volume, self->_baseVolume, from, to, frames);
    } else {
        for (i = 0; i < Handles(self)->_count; i++) {
            handle = HandleAt(Handles(self), i);
            if (NameOf(handle->_name) != 0 && strlen(NameOf(handle->_name)) != 0
                && strcmp(name, NameOf(handle->_name)) == 0) {
                beCriVolume_StartFade((beCriVolume *)handle->_volume, self->_baseVolume, from, to, frames);
            }
        }
    }
}

/* Arms a fade on the handle playing `playID`. */
void beCri_FadeByID(beCri *self, long long playID, float from, float to, float frames) {
    beCriHandle *handle;
    int i;
    handle = Bgm(self);
    if (playID == handle->_playID) {
        beCriVolume_StartFade((beCriVolume *)handle->_volume, self->_baseVolume, from, to, frames);
        return;
    }
    handle = Env(self);
    if (playID == handle->_playID) {
        beCriVolume_StartFade((beCriVolume *)handle->_volume, self->_baseVolume, from, to, frames);
        return;
    }
    for (i = 0; i < Handles(self)->_count; i++) {
        handle = HandleAt(Handles(self), i);
        if (playID == handle->_playID) {
            beCriVolume_StartFade((beCriVolume *)handle->_volume, self->_baseVolume, from, to, frames);
        }
    }
}

/* beNDMWAfsSetup's partitions: their count and the inside-file list, then each partition's archive. */
void beCri_SetupPartitions(beCri *self, int count, int insideFiles) {
    igAdx_SetPartitionCount(count);
    igAdx_SetInsideFiles(insideFiles);
}

void beCri_LoadPartition(beCri *self, int partition, const char *path, int fileCount) {
    if ((partition < 0) || (partition >= g_adxPartitionCount[0])) {
        return;
    }
    igAdx_LoadPartition(partition, path, 0, fileCount);
}

void beCri_ReleasePartitions(beCri *self)
{
    igAdx_AddPartitionName(-1, 0);
}

/* Appends an effect handle whose voice has `channels` (-1: a sound-bank voice). */
static inline void AppendVoice(beCri *self, int channels) {
    igSmartPointer<beCriHandle> handle(beCriHandle_Create(HandleAllocator(self)));
    beCriAudio_Setup(handle->_audio, channels);
    igNamedObject_SetName((beCriHandle *)handle, 0);
    ObjectList_AppendRetained(self->_hdSEs, (beCriHandle *)handle);
}

/* The effect handles: 4 single-channel ADX voices, then 48 sound-bank voices. */
void beCri_CreateEffectVoices(beCri *self) {
    int i;
    if (Handles(self)->_count > 0) beCri_ReleaseEffectVoices(self);
    for (i = 0; i < 4; i++) {
        AppendVoice(self, 1);
    }
    for (i = 0; i < 48; i++) {
        AppendVoice(self, -1);
    }
}

/* Stops the effect handles, releases their voices and empties the list. */
void beCri_ReleaseEffectVoices(beCri *self) {
    igObjectList *list;
    beCriHandle *first;
    beCri_StopGroup(self, 3);
    while (Handles(self)->_count > 0) {
        beCriAudio_Release(HandleAt(Handles(self), 0)->_audio);
        list = Handles(self);
        first = HandleAt(list, 0);
        igRelease(first);
        List_RemoveWordAt(list, 0);
        ((int *)list->_data)[list->_count] = 0; /* the slot the removal vacated */
    }
}

/* ONFREEZE and OFFREEZE: playing type 4 effect voices go silent (0) or back to full level (1). */
void beCri_SetFreezeAudible(beCri *self, int audible) {
    int i;
    for (i = 0; i < Handles(self)->_count; i++) {
        beCriHandle *handle = HandleAt(Handles(self), i);
        if (handle->_playID != 0 && handle->_type == 4) {
            beCriAudio *audio = (beCriAudio *)handle->_audio;
            if (beCriAudio_GetStatus(audio) == 1) {
                if (audible != 0) {
                    beCriAudio_SetVolume(audio, audio->_audioType == 3 ? 127 : 0);
                } else {
                    beCriAudio_SetVolume(audio, audio->_audioType == 3 ? 0 : -999);
                }
            }
        }
    }
}

/* Starts the transfer of a sound bank to its port: frees what the port held, records the bank's
 * sizes and sends the data. 0 when the module refuses. */
int beCri_TransferSfp(beCri *self, beCriSfpData *bank) {
    int port;
    if (bank->_isTransfer != 0) {
        return 1;
    }
    port = bank->_portNo;
    if (g_sfpPortSizes.tblSize[port] != 0 || g_sfpPortSizes.pcmSize[port] != 0) {
        FUN_002813c8(port);
    }
    g_sfpPortSizes.tblSize[port] = bank->_tblSize;
    g_sfpPortSizes.pcmSize[port] = bank->_pcmSize;
    if (FUN_00280f60(&g_sfpPortSizes) < 0) {
        return 0;
    }
    if (FUN_00281078(port, bank->_dataBuffer) < 0) {
        return 0;
    }
    g_sfpTransferState[port] = 1;
    return 1;
}

/* MAKEBINLIST: gives each sound bank not yet transferred its port and starts the first transfer; the
 * rest wait (state 1) for beCri_IsTransferDone to chain them, a transferred bank is state 2. */
bool beCri_StartSfpTransfers(beCri *self) {
    bool ok = true;
    igObjectList *banks = Banks(self);
    if (self->_dataType == 1) {
        bool first = true;
        int i;
        for (i = 0; i < banks->_count; i++) {
            beCriSfpData *bank = BankAt(banks, i);
            if (bank->_isTransfer == 0) {
                bank->_portNo = i;
                if (first) {
                    if (beCri_TransferSfp(self, bank) == 0) ok = false;
                    first = false;
                } else {
                    g_sfpTransferState[i] = 1;
                }
            } else {
                g_sfpTransferState[i] = 2;
            }
        }
    }
    return ok;
}

/* FREESFPDATA: frees the ports of the transferred sound banks, the first bank's only when
 * `includeFirst`, and empties the bank list. */
int beCri_FreeSfpData(beCri *self, int includeFirst) {
    int i;
    int lowest;
    beCriSfpData *bank;
    int offset;
    int acx;
    int sfp;
    lowest = -(includeFirst & 0xFF);
    i = Banks(self)->_count - 1;
    if (lowest < i) {
        offset = i * 4;
        do {
            acx = g_beCriAcxData_metaObject[0];
            bank = *(beCriSfpData **)((char *)Banks(self)->_data + offset);
            if (acx != ((MetaObjectView *)bank)->getMetaObject()) {
                sfp = g_beCriSfpData_metaObject[0];
                if (sfp == ((MetaObjectView *)bank)->getMetaObject() && bank->_isTransfer != 0) {
                    int port = bank->_portNo;
                    if (g_sfpPortSizes.tblSize[port] != 0 || g_sfpPortSizes.pcmSize[port] != 0) {
                        FUN_002813c8(port);
                        g_sfpPortSizes.tblSize[port] = 0;
                        g_sfpPortSizes.pcmSize[port] = 0;
                        g_sfpTransferState[port] = 0;
                    }
                }
            }
            i -= 1;
            offset -= 4;
        } while (lowest < i);
    }
    ReleaseAll(Banks(self));
    ReserveIfEmpty(Banks(self));
    return 1;
}

/* ISDONETRANS: polls the ports whose transfer runs; a finished bank frees its data and starts the
 * next bank's transfer. false while any transfer runs or failed. */
bool beCri_IsTransferDone(beCri *self) {
    int status;
    beCriSfpData *next;
    bool ok;
    int i;
    int *state;
    int offset;
    beCriSfpData *bank;

    ok = true;
    i = 0;
    if (0 < Banks(self)->_count) {
        offset = 0;
        state = &g_sfpTransferState[0];
        do {
            if (*state != 0 && *state != 2) {
                *state = FUN_00281cf8(i);
                status = *state;
                switch (status) {
                case 1:
                    return false;
                case 2:
                    bank = *(beCriSfpData **)((char *)Banks(self)->_data + offset);
                    Memory_FreeBuffer(bank->_dataBuffer);
                    bank->_dataBuffer = 0;
                    bank->_isTransfer = 1;
                    if (i < Banks(self)->_count - 1) {
                        next = *(beCriSfpData **)((char *)Banks(self)->_data + offset + 4);
                        if (next->_isTransfer == 0) {
                            beCri_TransferSfp(self, next);
                        }
                    }
                    break;
                case 3:
                    ok = false;
                    break;
                default:
                    ok = false;
                    break;
                }
            }
            i += 1;
            state += 1;
            offset += 4;
        } while (i < Banks(self)->_count);
    }
    return ok;
}

/* FXCTL: when `name` (NONE when null) names the first beCriFxInfo, its reverb level goes to the sound
 * IOP module, else the full level 127. */
void beCri_SetFx(beCri *self, char *name) {
    igObjectList *infos = (igObjectList *)self->_infoList;
    beCriFxInfo *info;
    if (infos->_count > 0) {
        info = ((beCriFxInfo **)infos->_data)[0];
        if (name == 0) {
            name = NONE;
        }
        if (strcmp(name, NameOf(info->_name)) == 0) {
            FUN_002829f0(0xA4000000, info->_reverb);
            return;
        }
        FUN_002829f0(0xA4000000, 0x7F);
        return;
    }
    FUN_002829f0(0xA4000000, 0x7F);
}

/* ISREADY: 1 unless the handle named `name` plays an ADX voice not yet in state 3 (playing); ALL tests
 * every playing ADX file voice. */
unsigned char beCri_IsReady(beCri *self, const char *name) {
    unsigned char allReady;
    int i;
    unsigned char ready;
    int j;
    beCriHandle *handle;
    beCriHandle *each;
    int removed0;
    int removed1;

    if (strcmp(name, ALL) == 0) {
        allReady = 1;
        ObjectList_AppendRetained(self->_hdSEs, self->_hdBGM);
        ObjectList_AppendRetained(self->_hdSEs, self->_hdENV);
        for (i = 0; i < Handles(self)->_count; i++) {
            each = HandleAt(Handles(self), i);
            if (each->_playID != 0 && ((beCriAudio *)each->_audio)->_audioType == 1 && igAdxAudio_GetStatus(((beCriAudio *)each->_audio)->_adxt) != 3) {
                allReady = 0;
                break;
            }
        }
        ObjectList_RemoveFirstRetained(&removed0, self->_hdSEs, self->_hdBGM, 0);
        ObjectList_RemoveFirstRetained(&removed1, self->_hdSEs, self->_hdENV, 0);
        return allReady;
    }
    ready = 1;
    if (NameOf(Bgm(self)->_name) != 0 && strcmp(NameOf(Bgm(self)->_name), name) == 0) {
        if (igAdxAudio_GetStatus(((beCriAudio *)Bgm(self)->_audio)->_adxt) != 3) ready = 0;
    } else if (NameOf(Env(self)->_name) != 0 && strcmp(NameOf(Env(self)->_name), name) == 0) {
        if (igAdxAudio_GetStatus(((beCriAudio *)Env(self)->_audio)->_adxt) != 3) ready = 0;
    } else {
        for (j = 0; j < Handles(self)->_count; j++) {
            handle = HandleAt(Handles(self), j);
            if (NameOf(handle->_name) != 0 && strlen(NameOf(handle->_name)) != 0
                && strcmp(name, NameOf(handle->_name)) == 0 && handle->_playID != 0
                && igAdxAudio_GetStatus(((beCriAudio *)handle->_audio)->_adxt) != 3) {
                ready = 0;
                break;
            }
        }
    }
    return ready;
}

/* SNDFVOLUME: the sound-bank master level, set once (1..127, else 127). */
void beCri_SetSndfVolume(beCri *self, int volume) {
    if (self->_sndfVolume == 0) {
        if (volume <= 0 || volume > 127) volume = 127;
        self->_sndfVolume = volume;
        FUN_002825e0(0, 0xA0010000, volume);
    }
}

static inline int AsMemoryRefField(int field) {
    if (field != 0 && igObject_IsKindOf(field, g_igMemoryRefMetaField_metaObject[0]) != 0) {
        return field;
    }
    return 0;
}

/* beCriSfpData's registration callback: a sound bank's _dataBuffer is allocated with the 32-byte
 * "sndfBuffer" alignment. */
void beCriSfpData_SetupBufferAlignment(void) {
    int field;

    igResource_AddAlignment(g_globalContext[0], sndfBuffer, 0x20);
    field = igMetaObject_FindFieldByName(g_beCriSfpData_metaObject[0], _dataBuffer);
    field = AsMemoryRefField(field);
    igMemoryRefMetaField_SetAlignmentType(field, sndfBuffer);
}

int Gap__Bec__beCri__vfunc_20(void)
{
    return g_beCri_metaObject[0];
}
