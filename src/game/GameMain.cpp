#include "dw4/reflected.h"
#include "dw4/igTDataList.h"
#include "dw4/igSmartPointer.h"
#include "dw4/igWindowDispatchView.h"
#include "dw4/igCommonTraversalDispatchView.h"
#include "dw4/ViewerSetup.h"
#include "dw4/ViewerOptions.h"
#include "dw4/igMemoryPoolView.h"

#pragma push
#pragma readonly_strings on
#define RELEASE_SHIFTED(v) { igObject *t_ = (igObject *)(v); if (t_ != 0) { t_->_refCount = t_->_refCount - 1; if (((unsigned long long) ((long long) (int) t_->_refCount << 0x29) >> 0x29) == 0) { igObject_Destroy(t_); } } }


extern "C" int igViewportAttr_EnsureRegistered(...);
extern "C" int igVertexBlendStateAttr_EnsureRegistered(...);
extern "C" int igTextureUnloadAttr_EnsureRegistered(...);
extern "C" int igTextureStateAttr_EnsureRegistered(...);
extern "C" int igTextureMatrixStateAttr_EnsureRegistered(...);
extern "C" int igTextureMatrixAttr_EnsureRegistered(...);
extern "C" int igTextureFunctionAttr_EnsureRegistered(...);
extern "C" int igTextureCoordSourceAttr_EnsureRegistered(...);
extern "C" int igTextureBindAttr_EnsureRegistered(...);
extern "C" int igTextureAttr_EnsureRegistered(...);
extern "C" int igImageMipMapList_EnsureRegistered(...);
extern "C" int igShadeModelAttr_EnsureRegistered(...);
extern "C" int igSetRenderDestinationAttr_EnsureRegistered(...);
extern "C" int igRenderDestinationAttr_EnsureRegistered(...);
extern "C" int igProjectionMatrixAttr_EnsureRegistered(...);
extern "C" int igParticleAttr_EnsureRegistered(...);
extern "C" int igNormalizeNormalsStateAttr_EnsureRegistered(...);
extern "C" int igModelViewMatrixAttr_EnsureRegistered(...);
extern "C" int igMaterialAttr_EnsureRegistered(...);
extern "C" int igLightingStateAttr_EnsureRegistered(...);
extern "C" int igLightStateAttrList_EnsureRegistered(...);
extern "C" int igLightStateAttr_EnsureRegistered(...);
extern "C" int igLightList_EnsureRegistered(...);
extern "C" int igLightAttr_EnsureRegistered(...);
extern "C" int igGeometrySetAttr_EnsureRegistered(...);
extern "C" int igGeometryAttr1_5_EnsureRegistered(...);
extern "C" int igFogStateAttr_EnsureRegistered(...);
extern "C" int igFogAttr_EnsureRegistered(...);
extern "C" int igDepthWriteStateAttr_EnsureRegistered(...);
extern "C" int igDepthStateAttr_EnsureRegistered(...);
extern "C" int igCullFaceAttr_EnsureRegistered(...);
extern "C" int igCopyRenderDestinationAttr_EnsureRegistered(...);
extern "C" int igColorMaskAttr_EnsureRegistered(...);
extern "C" int igColorAttr_EnsureRegistered(...);
extern "C" int igClearAttr_EnsureRegistered(...);
extern "C" int igBlendStateAttr_EnsureRegistered(...);
extern "C" int igBlendFunctionAttr_EnsureRegistered(...);
extern "C" int igTextureList_EnsureRegistered(...);
extern "C" int igAttrPool_EnsureRegistered(...);
extern "C" int igAttrListList_EnsureRegistered(...);
extern "C" int igNonRefCountedAttrList_EnsureRegistered(...);
extern "C" int igAttrList_EnsureRegistered(...);
extern "C" int igAlphaStateAttr_EnsureRegistered(...);
extern "C" int igAlphaFunctionAttr_EnsureRegistered(...);
extern "C" int igVertexArray1_1_EnsureRegistered(...);
extern "C" int igPrimLengthArray1_1_EnsureRegistered(...);
extern "C" int igParticleFormat_EnsureRegistered(...);
extern "C" int igIndexArray_EnsureRegistered(...);
extern "C" int igImage_EnsureRegistered(...);
extern "C" int igTrackedElementMetaField_EnsureRegistered(...);
extern "C" int igExternalImageEntry_EnsureRegistered(...);
extern "C" int igClut_EnsureRegistered(...);
extern "C" int igVec4ucMetaField_EnsureRegistered(...);
extern "C" int igVec4fMetaField_EnsureRegistered(...);
extern "C" int igVec4fArrayMetaField_EnsureRegistered(...);
extern "C" int igVec3fMetaField_EnsureRegistered(...);
extern "C" int igVec2fMetaField_EnsureRegistered(...);
extern "C" int igMatrix44fMetaField_EnsureRegistered(...);
extern "C" int igGetCenterFunctionList_EnsureRegistered(...);
extern "C" int igIsEmptyFunctionList_EnsureRegistered(...);
extern "C" int igEmptyFunctionList_EnsureRegistered(...);
extern "C" int igTransformFunctionList_EnsureRegistered(...);
extern "C" int igContainsVecFunctionList_EnsureRegistered(...);
extern "C" int igExtendByVecFunctionList_EnsureRegistered(...);
extern "C" int igContainsRayFunctionList_EnsureRegistered(...);
extern "C" int igExtendByRayFunctionList_EnsureRegistered(...);
extern "C" int igRayIntersectionFunctionList_EnsureRegistered(...);
extern "C" int igContainsFunctionList_EnsureRegistered(...);
extern "C" int igExtendByFunctionList_EnsureRegistered(...);
extern "C" int igIntersectionFunctionList_EnsureRegistered(...);
extern "C" int igQuaternionfList_EnsureRegistered(...);
extern "C" int igVec3fList_EnsureRegistered(...);
extern "C" int igAABox_EnsureRegistered(...);
extern "C" int igTransformSequence1_5_EnsureRegistered(...);
extern "C" int igTransformRecorder_EnsureRegistered(...);
extern "C" int igTransformList_EnsureRegistered(...);
extern "C" int igTransform_EnsureRegistered(...);
extern "C" int igSwitch_EnsureRegistered(...);
extern "C" int igSkinList_EnsureRegistered(...);
extern "C" int igSkin_EnsureRegistered(...);
extern "C" int igSkeletonList_EnsureRegistered(...);
extern "C" int igSkeleton_EnsureRegistered(...);
extern "C" int igSkeletonBoneInfoList_EnsureRegistered(...);
extern "C" int igSkeletonBoneInfo_EnsureRegistered(...);
extern "C" int igShaderInfo_EnsureRegistered(...);
extern "C" int igShaderFactoryList_EnsureRegistered(...);
extern "C" int igTraversalFunctionList_EnsureRegistered(...);
extern "C" int igSceneInfo_EnsureRegistered(...);
extern "C" int igProjectiveShadowShader_EnsureRegistered(...);
extern "C" int igNonRefCountedNodeList_EnsureRegistered(...);
extern "C" int igNodeList_EnsureRegistered(...);
extern "C" int igModelViewMatrixBoneSelectListSg_EnsureRegistered(...);
extern "C" int igModelViewMatrixBoneSelect_EnsureRegistered(...);
extern "C" int igLod_EnsureRegistered(...);
extern "C" int igLightStateSet_EnsureRegistered(...);
extern "C" int igLightSet_EnsureRegistered(...);
extern "C" int igIniShaderFactory_EnsureRegistered(...);
extern "C" int igGroup_EnsureRegistered(...);
extern "C" int igGraphPathList_EnsureRegistered(...);
extern "C" int igGraphPath_EnsureRegistered(...);
extern "C" int igGeometryList_EnsureRegistered(...);
extern "C" int igGeometry_EnsureRegistered(...);
extern "C" int igEnbayaTransformSource_EnsureRegistered(...);
extern "C" int igEnbayaContextPool_RunStaticInit(...);
extern "C" int igEnbayaAnimationState_EnsureRegistered(...);
extern "C" int igEnbayaAnimationSource_EnsureRegistered(...);
extern "C" int igCompressedAnimationSequenceQS_EnsureRegistered(...);
extern "C" int igCommonTraversal_EnsureRegistered(...);
extern "C" int igCamera_EnsureRegistered(...);
extern "C" int igBlendMatrixSelect_EnsureRegistered(...);
extern "C" int igBitMask_EnsureRegistered(...);
extern "C" int igBillboard_EnsureRegistered(...);
extern "C" int igAttrSet_EnsureRegistered(...);
extern "C" int igAppearanceList_EnsureRegistered(...);
extern "C" int igAppearance_EnsureRegistered(...);
extern "C" int igAnimationStatePool_RunStaticInit(...);
extern "C" int igAnimationStateList_EnsureRegistered(...);
extern "C" int igAnimationModifierList_EnsureRegistered(...);
extern "C" int igAnimationDatabase_EnsureRegistered(...);
extern "C" int igAnimationCombinerBoneInfoPool_RunStaticInit(...);
extern "C" int igAnimationCombinerBoneInfoListList_EnsureRegistered(...);
extern "C" int igAnimationCombinerBoneInfoList_EnsureRegistered(...);
extern "C" int igAnimationCombinerList_EnsureRegistered(...);
extern "C" int igAnimationCombiner_EnsureRegistered(...);
extern "C" int igAnimationBindingList_EnsureRegistered(...);
extern "C" int igAnimationBinding_EnsureRegistered(...);
extern "C" int igAnimationList_EnsureRegistered(...);
extern "C" int igAnimation_EnsureRegistered(...);
extern "C" int igAnimationTransitionDefinitionList_EnsureRegistered(...);
extern "C" int igAnimationTrackList_EnsureRegistered(...);
extern "C" int igAnimationTrack_EnsureRegistered(...);
extern "C" int igActorList_EnsureRegistered(...);
extern "C" int igActor_EnsureRegistered(...);
extern "C" int igVirtualCFuncMetaField_EnsureRegistered(...);
extern "C" int igUnsignedShortArrayMetaField_EnsureRegistered(...);
extern "C" int igUnsignedLongArrayMetaField_EnsureRegistered(...);
extern "C" int igUnsignedIntArrayMetaField_EnsureRegistered(...);
extern "C" int igUnsignedCharArrayMetaField_EnsureRegistered(...);
extern "C" int igStringArrayMetaField_EnsureRegistered(...);
extern "C" int igShortArrayMetaField_EnsureRegistered(...);
extern "C" int igRawRefArrayMetaField_EnsureRegistered(...);
extern "C" int igObjectStringMap_EnsureRegistered(...);
extern "C" int igObjectRefArrayMetaField_EnsureRegistered(...);
extern "C" int igNamedObjectInfo_EnsureRegistered(...);
extern "C" int igNamedObjectList_EnsureRegistered(...);
extern "C" int igMemoryRefArrayMetaField_EnsureRegistered(...);
extern "C" int igMemoryFileEntryList_EnsureRegistered(...);
extern "C" int igLongArrayMetaField_EnsureRegistered(...);
extern "C" int igFloatArrayMetaField_EnsureRegistered(...);
extern "C" int igEnumArrayMetaField_EnsureRegistered(...);
extern "C" int igDoubleMetaField_EnsureRegistered(...);
extern "C" int igDoubleArrayMetaField_EnsureRegistered(...);
extern "C" int igDependencyMetaField_EnsureRegistered(...);
extern "C" int igPointerListList_EnsureRegistered(...);
extern "C" int igFloatListList_EnsureRegistered(...);
extern "C" int igFloatList_EnsureRegistered(...);
extern "C" int igUnsignedShortList_EnsureRegistered(...);
extern "C" int igLongList_EnsureRegistered(...);
extern "C" int igBoolList_EnsureRegistered(...);
extern "C" int igBoolArrayMetaField_EnsureRegistered(...);
extern "C" int igMemoryDescriptorMetaField_EnsureRegistered(...);
extern "C" void GameMain_RegisterEngineClasses(void);
extern "C" int __dl__FPv(...);
extern "C" int igVisualContext_SetImageMemoryPool(int);
extern "C" int igObjectSystem_Acquire(int);
extern "C" int igObjectSystem_Release(...);
extern "C" int StringChunk_ReleaseHeader(...);
extern "C" int main(int argc, int *argv);
extern "C" const char *GameMain_GetIniText(void);
extern "C" int igObjectSystem_SetIniText(const char *);
extern "C" void GameMain_ApplyIniText(void);
extern "C" int sceOpen(char *, int);
extern "C" int sceClose(int);
extern "C" int sceRead(int, void *, int);
extern "C" int sceWrite(int, const char *, int);
extern "C" char *Memory_SystemAllocate(int);
extern "C" void GameMain_AtstreamThread(void);
extern "C" void **igThread_Create(...);
extern "C" void GameMain_StartAtstreamThread(void);
extern "C" int igObject_MallocAligned(...);
extern "C" int igObject_FreeMemory(...);
extern "C" bool GameMain_SetAtfilePrefix(const char *path);
extern "C" void GameMain_InitAtstream(void);
extern "C" int StringPool_Allocate(...);
extern "C" int ViewerSetup_ResetView(...);
extern "C" int StringPool_Construct(...);
extern "C" int StringPool_Intern(...);
extern "C" void GameMain_LoadScene(struct Blk *app);
extern "C" void *igInsightCore_FindManager(...);
extern "C" int CollisionLibrary_RegisterClasses(...);
extern "C" int AdxMovieLibrary_RegisterClasses(...);
extern "C" int BecLibrary_RegisterClasses(...);
extern "C" int LuaAPI_RegisterClasses(...);
extern "C" int NdmwLibrary_RegisterClasses(...);
extern "C" int ViewerSetup_Open(...);
extern "C" int ViewerSetup_Close(...);
extern "C" int ViewerSetup_RunFrame(...);
extern "C" int ViewerSetup_Update(...);
extern "C" int fptodp(float);
extern "C" int igReport_Info(...);
extern "C" int igModel_NotifyViews(...);
extern "C" int SceneSearchLibrary_RegisterClasses(...);
extern "C" int strcpy(...);
extern "C" int strlen(...);
extern "C" int igStringObj_HasFileExtensionText(...);
extern "C" int List_RemoveWordAt(...);
extern "C" igSmartPointer<igStringRefList> igFolder_ListEntries(void);
extern "C" int igObject_IsKindOf(...);
extern "C" int ViewerSetup_ClearInfos(...);
/* matching construct: out-of-line ctor/dtor classes reproduce the retail unwind table (retail 0x2595e0 table 0x542b5c: App dtor 0x234b90, Blk dtor 0x25a330, scope guard dtor 0x2599b0) */
/* The viewer's parsed command line: the option block, then the repeat counts and the model names. */
struct App { char options[232]; igIntList *intList; igStringRefList *stringList; App(); ~App(); };
extern "C" SharedViewerOptions *__nw__FUi(...);
extern "C" int ViewerOptions_ParseCommandLine(App *, int, int *);
extern "C" SharedViewerOptions *ViewerOptions_Construct(...);
extern "C" igMemoryPoolView *Memory_GetAllocatorBySelector(int);
extern "C" igAnimationCombinerBoneInfoPool * igAnimationCombinerBoneInfoPool_Create(...);
extern "C" igAnimationStatePool * igAnimationStatePool_Create(...);
extern "C" igEnbayaContextPool * igEnbayaContextPool_Create(...);
extern igSmartPointer<igAnimationCombinerBoneInfoPool> g_igAnimationCombinerBoneInfoPool_instance;
extern "C" SharedViewerOptions *g_sharedViewerOptions[4];
extern "C" int g_bootstrapPoolPreSize[4];
extern "C" int g_systemPoolPreSize[4];
extern "C" int g_metaDataPoolPreSize[4];
extern "C" int g_stringPoolPreSize[4];
extern "C" int kIGMemoryPoolHandleUser0[4];
extern "C" int g_igPsx2_useCdrom[4];
extern "C" const char *g_igPsx2_iopImagePath[4];
extern "C" unsigned char g_reportEchoToStdout;
extern "C" unsigned char g_igPsx2_resetIopServices;
extern "C" unsigned char g_useOwnerAllocator;
struct Guard { ~Guard() { igObjectSystem_Release(); } };
/* The allocator a new pool comes from: the owner's, or the user-0 pool when the owner allocator is off. */
static inline int PoolAllocator(int owner) {
    if (g_useOwnerAllocator) return owner;
    else return ((int)Memory_GetAllocatorBySelector(kIGMemoryPoolHandleUser0[0]));
}
/* Releases the object a slot holds, through the 64-bit masked count test; the slot is left as it was. */
static inline void ReleaseObject(igObject **slot) {
    igObject *o = slot[0];
    if (o != 0) {
        o->_refCount = o->_refCount - 1;
        if (((unsigned long long)(long long)o->_refCount & 0x7fffffULL) == 0) igObject_Destroy(o);
    }
}
/* Takes a use of the shared viewer options, creating them on first use. */
static inline void AcquireSharedOptions() {
    if (g_sharedViewerOptions[0] == 0) {
        SharedViewerOptions *created = __nw__FUi(0xF0);
        if (created != 0) {
            created = ViewerOptions_Construct(created);
        }
        g_sharedViewerOptions[0] = created;
    }
    g_sharedViewerOptions[0]->useCount = g_sharedViewerOptions[0]->useCount + 1;
}

/* Releases a reference to an interned string. */
static inline void ReleaseStringRef(int string) {
    if (string != 0) {
        int *header = (int *)(string - 8);
        int count = ((int *)string)[-1] - 1;
        ((int *)string)[-1] = count;
        if (count == 0) {
            StringChunk_ReleaseHeader(*header, header);
        }
    }
}

/* Drops a use of the shared viewer options and frees them with the last one. */
static inline void ReleaseSharedOptions() {
    if (g_sharedViewerOptions[0] != 0) {
        int remaining = g_sharedViewerOptions[0]->useCount - 1;
        g_sharedViewerOptions[0]->useCount = remaining;
        if (remaining <= 0) {
            SharedViewerOptions *options = g_sharedViewerOptions[0];
            if (options != 0) {
                if (&options->internedString) {
                    ReleaseStringRef(options->internedString);
                }
                if (options != 0) {
                    ReleaseStringRef((int)options->extraCommandLine);
                }
                __dl__FPv(options);
            }
            g_sharedViewerOptions[0] = 0;
        }
    }
}

extern "C" { char *g_atstreamText; }
extern "C" { char g_atstreamTextReady; }
/* igResult: the status a call returns by value. */
class igResult {
public:
    int v;
    igResult() {}
    igResult(int x) : v(x) {}
    igResult(const igResult &o) : v(o.v) {}
    bool operator==(const igResult &o) const { return v == o.v; }
};
extern "C" const igResult g_resultSuccess;
extern "C" const igResult g_resultFailure;
/* igPsx2Thread (reflected layout in dw4/reflected.h) with the virtuals this file calls: slot 23 sleeps for a
 * number of nanoseconds, 28 starts the thread, 30 tells whether it is running, 31 sets its function, 37 its
 * stack size, 40 gives the stack alignment and 48 sets its priority. */
class igPsx2ThreadView : public igVirtualObject {
public:
    virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22();
    virtual igResult Sleep(int nanoseconds);
    virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27();
    virtual igResult Start();
    virtual void d29();
    virtual int IsRunning();
    virtual igResult SetFunction(void (*function)(void));
    virtual void d32(); virtual void d33(); virtual void d34(); virtual void d35(); virtual void d36();
    virtual igResult SetStackSize(unsigned int stackSize);
    virtual void d38(); virtual void d39();
    virtual int GetStackAlignment();
    virtual void d41(); virtual void d42(); virtual void d43(); virtual void d44(); virtual void d45(); virtual void d46(); virtual void d47();
    virtual igResult SetPriority(int priority);
    int _name;
    int _type;
    int _scope;
    int _state;
    int _priority;
    int _arg;
    int _stack;
    unsigned int _stackSize;
    int _function;
    unsigned char _isMaster;
    unsigned char _userStack;
};
extern "C" igResult igPsx2Thread_SetStackSize(igPsx2ThreadView *self, unsigned int stackSize);
extern "C" igResult igPsx2_SetAtfilePrefix(const char *path);
extern "C" { bool g_atfilePrefixSet; }
extern "C" igPsx2ThreadManager *g_threadManager[4];
extern "C" { unsigned char g_atstreamFullReload = 1; }
extern "C" { unsigned char g_startupFlagB = 1; }
extern "C" igSmartPointer<igPsx2Window> Viewer_CreateDisplay(int);
extern "C" igFolder *igFolder_Create(int);
extern "C" igViewerLoadingFileMessage *igViewerLoadingFileMessage_Create(int);
/* The viewer application: the viewer setup (its window sits at +24), the repeat counts and model names of the
 * command line, the quit flag, the model files found on the disc and the loading message. */
struct Blk {
    ViewerSetup viewer;
    igSmartPointer<igObject> reservedA;
    igSmartPointer<igObject> reservedB;
    igSmartPointer<igIntList> repeatCounts;
    igSmartPointer<igStringRefList> modelNames;
    bool isFinished;
    igSmartPointer<igStringRefList> fileNames;
    igSmartPointer<igFolder> folder;
    igSmartPointer<igViewerLoadingFileMessage> loadingMessage;
    Blk();
    ~Blk();
};
extern "C" void GameMain_PollAtstream(Blk *app, int idle);
typedef igTDataList<int> NameList;
extern "C" igStringRefList *igStringRefList_Create(int);
extern "C" NameList *igIntList_Create(int);
extern "C" { int g_defaultNameValue = 1; }
extern "C" int g_stringPool[4];
struct StringRef {
    int *p;
    StringRef() {}
    StringRef(int s) : p((int *)s) {}
    static inline void Release(int *x) {
        if (x != 0) { int *hd = x - 2; int c = x[-1] - 1; x[-1] = c; if (c == 0) StringChunk_ReleaseHeader(*hd, hd); }
    }
    ~StringRef() { Release(p); }
};
extern "C" int StringList_AppendRetained(void *, StringRef *);
extern "C" void GameMain_ReplaceSceneFile(Blk *app, int text, int fullReload);
extern "C" void GameMain_SetViewerFileLists(Blk *app, igStringRefList *modelNames, igIntList *repeatCounts);
extern "C" void GameMain_ReloadScene(Blk *app, int);
extern "C" { Blk *g_activeApp; }
extern "C" int g_beSystem_metaObject[16];
/* igFolder's virtual functions: slot 24 lists the folder's entries (igFolder_ListEntries).
 * ABI view only: never instantiated. */
class igFolderDispatchView : public igObjectDispatchView {
public:
    virtual void d21(); virtual void d22(); virtual void d23();
    virtual igSmartPointer<igStringRefList> ListEntries();                  /* slot 24 */
};
extern "C" void GameMain_RunGame(Blk *app);
/* A model change record handed to igModel_NotifyViews: type 2 reports that the field named by `field` changed. */
struct ModelChange { int type; int flags; int field; int reserved; };
/* igTimer's virtual functions as the game calls them on igPsx2LongTimer (igPsx2LongTimer_<Name>):
 * slot 24 reads the elapsed nanoseconds, slot 26 stops the clock and slot 29 restarts it.
 * ABI view only: never instantiated. */
class igTimerDispatchView : public igObjectDispatchView {
public:
    virtual void d21(); virtual void d22(); virtual void d23();
    virtual long long GetElapsedTime();                                     /* slot 24 */
    virtual void d25();
    virtual void Stop();                                                    /* slot 26 */
    virtual void d27(); virtual void d28();
    virtual void Restart();                                                 /* slot 29 */
};
extern "C" igTimerDispatchView *igTimer_Create(...);
extern "C" int g_igViewerParameters_showGuiMetaField[4];
extern "C" int g_igViewerParameters_showBoundingBoxMetaField[4];
extern "C" int g_igViewerParameters_showNormalsMetaField[4];
extern "C" int g_igViewerParameters_flushFramesMetaField[4];
extern "C" { unsigned char g_frameRateReportIgnored; }
extern "C" void GameMain_RunBenchmark(Blk *app);
/* matching construct: the returned reference is a temporary of the call, so it takes a low frame slot and is released right after the store */
struct Assign {
    static inline void Take(igStringRefList *&dst, const igSmartPointer<igStringRefList> &src) {
        igStringRefList *list = src.p;
        igStringRefList *old;
        if (list != 0) list->_refCount = list->_refCount + 1;
        old = dst;
        if (old != 0) {
            old->_refCount = old->_refCount - 1;
            if (((unsigned long long)(long long)old->_refCount & 0x7fffffULL) == 0) igObject_Destroy(old);
        }
        dst = list;
    }
};
extern "C" StringRef StringList_CopyRetained(void *, int);
extern "C" void GameMain_ListIgbFiles(Blk *app);
extern "C" igMemoryPoolView * Memory_GetCurrentAllocator(...);
extern igSmartPointer<igAnimationStatePool> g_igAnimationStatePool_instance;
extern igSmartPointer<igEnbayaContextPool> g_igEnbayaContextPool_instance;
extern "C" int kIGMemoryPoolHandleUser1[4];
extern "C" int g_igViewerSceneInfoManager_metaObject[4];
/* The manager when it is a viewer scene-info manager, else null. */
static inline igViewerSceneInfoManager *AsSceneInfoManager(void *manager) {
    if (manager != 0 && igObject_IsKindOf(manager, g_igViewerSceneInfoManager_metaObject[0]) != 0) return (igViewerSceneInfoManager *)manager; else return 0;
}
extern "C" void GameMain_ClearScene(Blk *app);

void GameMain_RegisterEngineClasses(void) {
    igExternalImageEntry_EnsureRegistered();
    igVirtualCFuncMetaField_EnsureRegistered();
    igUnsignedShortArrayMetaField_EnsureRegistered();
    igUnsignedLongArrayMetaField_EnsureRegistered();
    igUnsignedIntArrayMetaField_EnsureRegistered();
    igUnsignedCharArrayMetaField_EnsureRegistered();
    igStringArrayMetaField_EnsureRegistered();
    igShortArrayMetaField_EnsureRegistered();
    igRawRefArrayMetaField_EnsureRegistered();
    igObjectStringMap_EnsureRegistered();
    igNamedObjectList_EnsureRegistered();
    igObjectRefArrayMetaField_EnsureRegistered();
    igNamedObjectInfo_EnsureRegistered();
    igMemoryRefArrayMetaField_EnsureRegistered();
    igMemoryFileEntryList_EnsureRegistered();
    igLongArrayMetaField_EnsureRegistered();
    igFloatArrayMetaField_EnsureRegistered();
    igEnumArrayMetaField_EnsureRegistered();
    igDoubleMetaField_EnsureRegistered();
    igDoubleArrayMetaField_EnsureRegistered();
    igDependencyMetaField_EnsureRegistered();
    igPointerListList_EnsureRegistered();
    igBoolArrayMetaField_EnsureRegistered();
    igMemoryDescriptorMetaField_EnsureRegistered();
    igRayIntersectionFunctionList_EnsureRegistered();
    igExtendByRayFunctionList_EnsureRegistered();
    igContainsRayFunctionList_EnsureRegistered();
    igExtendByVecFunctionList_EnsureRegistered();
    igContainsVecFunctionList_EnsureRegistered();
    igEmptyFunctionList_EnsureRegistered();
    igIsEmptyFunctionList_EnsureRegistered();
    igTransformFunctionList_EnsureRegistered();
    igGetCenterFunctionList_EnsureRegistered();
    igIntersectionFunctionList_EnsureRegistered();
    igExtendByFunctionList_EnsureRegistered();
    igContainsFunctionList_EnsureRegistered();
    igVec3fMetaField_EnsureRegistered();
    igVec2fMetaField_EnsureRegistered();
    igVec4fMetaField_EnsureRegistered();
    igVec4ucMetaField_EnsureRegistered();
    igMatrix44fMetaField_EnsureRegistered();
    igTrackedElementMetaField_EnsureRegistered();
    igImage_EnsureRegistered();
    igViewportAttr_EnsureRegistered();
    igTextureAttr_EnsureRegistered();
    igImageMipMapList_EnsureRegistered();
    igTextureStateAttr_EnsureRegistered();
    igTextureMatrixStateAttr_EnsureRegistered();
    igTextureFunctionAttr_EnsureRegistered();
    igTextureBindAttr_EnsureRegistered();
    igLightingStateAttr_EnsureRegistered();
    igDepthWriteStateAttr_EnsureRegistered();
    igCullFaceAttr_EnsureRegistered();
    igBlendStateAttr_EnsureRegistered();
    igBlendFunctionAttr_EnsureRegistered();
    igAttrPool_EnsureRegistered();
    igAttrListList_EnsureRegistered();
    igAttrList_EnsureRegistered();
    igAlphaStateAttr_EnsureRegistered();
    igVec4fArrayMetaField_EnsureRegistered();
    igTraversalFunctionList_EnsureRegistered();
    igShaderInfo_EnsureRegistered();
    igShaderFactoryList_EnsureRegistered();
    igAnimation_EnsureRegistered();
    igAnimationBindingList_EnsureRegistered();
    igAnimationTrackList_EnsureRegistered();
    igAnimationTransitionDefinitionList_EnsureRegistered();
    igAnimationCombinerBoneInfoPool_RunStaticInit();
    igAnimationStatePool_RunStaticInit();
    igIniShaderFactory_EnsureRegistered();
    igEnbayaContextPool_RunStaticInit();
    igClut_EnsureRegistered();
    igAABox_EnsureRegistered();
    igVertexArray1_1_EnsureRegistered();
    igTextureList_EnsureRegistered();
    igShadeModelAttr_EnsureRegistered();
    igMaterialAttr_EnsureRegistered();
    igGeometrySetAttr_EnsureRegistered();
    igGeometryAttr1_5_EnsureRegistered();
    igColorAttr_EnsureRegistered();
    igNonRefCountedNodeList_EnsureRegistered();
    igNodeList_EnsureRegistered();
    igSwitch_EnsureRegistered();
    igBitMask_EnsureRegistered();
    igAttrSet_EnsureRegistered();
    igGeometry_EnsureRegistered();
    igSceneInfo_EnsureRegistered();
    igGraphPathList_EnsureRegistered();
    igTransform_EnsureRegistered();
    igPrimLengthArray1_1_EnsureRegistered();
    igIndexArray_EnsureRegistered();
    igBoolList_EnsureRegistered();
    igFloatList_EnsureRegistered();
    igVertexBlendStateAttr_EnsureRegistered();
    igSkin_EnsureRegistered();
    igSkinList_EnsureRegistered();
    igSkeletonBoneInfo_EnsureRegistered();
    igSkeletonBoneInfoList_EnsureRegistered();
    igSkeleton_EnsureRegistered();
    igSkeletonList_EnsureRegistered();
    igModelViewMatrixBoneSelectListSg_EnsureRegistered();
    igAnimationBinding_EnsureRegistered();
    igAnimationTrack_EnsureRegistered();
    igActor_EnsureRegistered();
    igAppearance_EnsureRegistered();
    igAnimationDatabase_EnsureRegistered();
    igAnimationList_EnsureRegistered();
    igAppearanceList_EnsureRegistered();
    igAnimationCombinerList_EnsureRegistered();
    igAnimationCombiner_EnsureRegistered();
    igAnimationCombinerBoneInfoListList_EnsureRegistered();
    igAnimationCombinerBoneInfoList_EnsureRegistered();
    igAnimationStateList_EnsureRegistered();
    igAnimationModifierList_EnsureRegistered();
    igEnbayaTransformSource_EnsureRegistered();
    igEnbayaAnimationSource_EnsureRegistered();
    igEnbayaAnimationState_EnsureRegistered();
    igBlendMatrixSelect_EnsureRegistered();
    igActorList_EnsureRegistered();
    igProjectionMatrixAttr_EnsureRegistered();
    igModelViewMatrixAttr_EnsureRegistered();
    igFogStateAttr_EnsureRegistered();
    igDepthStateAttr_EnsureRegistered();
    igLongList_EnsureRegistered();
    igVec3fList_EnsureRegistered();
    igGroup_EnsureRegistered();
    igTransformSequence1_5_EnsureRegistered();
    igQuaternionfList_EnsureRegistered();
    igAlphaFunctionAttr_EnsureRegistered();
    igBillboard_EnsureRegistered();
    igNormalizeNormalsStateAttr_EnsureRegistered();
    igColorMaskAttr_EnsureRegistered();
    igParticleFormat_EnsureRegistered();
    igParticleAttr_EnsureRegistered();
    igTextureUnloadAttr_EnsureRegistered();
    igTextureMatrixAttr_EnsureRegistered();
    igTextureCoordSourceAttr_EnsureRegistered();
    igSetRenderDestinationAttr_EnsureRegistered();
    igRenderDestinationAttr_EnsureRegistered();
    igLightStateAttr_EnsureRegistered();
    igLightAttr_EnsureRegistered();
    igLightStateAttrList_EnsureRegistered();
    igLightList_EnsureRegistered();
    igFogAttr_EnsureRegistered();
    igNonRefCountedAttrList_EnsureRegistered();
    igCopyRenderDestinationAttr_EnsureRegistered();
    igClearAttr_EnsureRegistered();
    igProjectiveShadowShader_EnsureRegistered();
    igLightStateSet_EnsureRegistered();
    igLightSet_EnsureRegistered();
    igTransformList_EnsureRegistered();
    igGraphPath_EnsureRegistered();
    igGeometryList_EnsureRegistered();
    igCamera_EnsureRegistered();
    igUnsignedShortList_EnsureRegistered();
    igCompressedAnimationSequenceQS_EnsureRegistered();
    igModelViewMatrixBoneSelect_EnsureRegistered();
    igFloatListList_EnsureRegistered();
    igTransformRecorder_EnsureRegistered();
    igLod_EnsureRegistered();
    igCommonTraversal_EnsureRegistered();
}

int main(int argc, int *argv) {
    int allocator;
    SharedViewerOptions *options;
    GameMain_ApplyIniText();
    GameMain_SetAtfilePrefix((const char *)(*argv));
    g_igPsx2_useCdrom[0] = 2;
    g_reportEchoToStdout = 0;
    g_igPsx2_iopImagePath[0] = "cdrom0:\\MODULES\\IOPRP280.IMG;1";
    g_igPsx2_resetIopServices = 1;
    g_startupFlagB = 0;
    g_bootstrapPoolPreSize[0] = 0x40000;
    g_systemPoolPreSize[0] = 0x4000;
    g_metaDataPoolPreSize[0] = 0xA0000;
    g_stringPoolPreSize[0] = 0x69000;
    igObjectSystem_Acquire(0xC80);
    Guard guard;
    GameMain_InitAtstream();
    GameMain_RegisterEngineClasses();
    App args;
    ViewerOptions_ParseCommandLine(&args, argc, argv);
    allocator = PoolAllocator(((int)Memory_GetCurrentAllocator()));
    igVisualContext_SetImageMemoryPool(allocator);
    ReleaseObject((igObject **)&g_igEnbayaContextPool_instance.p);
    g_igEnbayaContextPool_instance.p = 0;
    allocator = PoolAllocator(((int)Memory_GetCurrentAllocator()));
    ReleaseObject((igObject **)&g_igEnbayaContextPool_instance.p);
    g_igEnbayaContextPool_instance.p = igEnbayaContextPool_Create(allocator);
    allocator = PoolAllocator(((int)Memory_GetCurrentAllocator()));
    ReleaseObject((igObject **)&g_igAnimationCombinerBoneInfoPool_instance.p);
    g_igAnimationCombinerBoneInfoPool_instance.p = igAnimationCombinerBoneInfoPool_Create(allocator);
    g_igAnimationCombinerBoneInfoPool_instance->_resetMode = 0;
    allocator = PoolAllocator(((int)Memory_GetCurrentAllocator()));
    ReleaseObject((igObject **)&g_igAnimationStatePool_instance.p);
    g_igAnimationStatePool_instance.p = igAnimationStatePool_Create(allocator);
    Blk app;
    GameMain_SetViewerFileLists(&app, args.stringList, args.intList);
    AcquireSharedOptions();
    if (g_sharedViewerOptions[0]->benchmark != 0) GameMain_RunBenchmark(&app);
    else GameMain_RunGame(&app);
    ReleaseSharedOptions();
    return 0;
}

const char *GameMain_GetIniText(void) {
    return "[CORE]\nintrinsicModulePath = MODULES\nsonyModulePath = MODULES\nuserFileIO = false\nscratchPoolSize = 0x4000\nmoveVTablesToScratchPad = 1\n[DISPLAY]\nsupportMultitap = PORT0\n[BECRUNTIME]\nAdxModulePath = /MODULES\n[MEMORYPOOLS]\nDefault     = POOL_DEFAULT\nDriverData  = POOL_DRIVERDATA\nRenderList  = POOL_RENDERLIST\nDMA         = POOL_DMA\nHandles     = POOL_HANDLES\n\nTemporary   = POOL_TEMPORARY\nLevel       = POOL_LEVEL\nAttribute   = POOL_ATTRIBUTE\nTexture     = POOL_TEXTURE\nImage       = POOL_IMAGE\nUser0       = POOL_USER0\nUser1       = POOL_USER1\n\nList        = POOL_LIST\nVertex      = POOL_VERTEX\nApplication = POOL_APPLICATION\nWorld       = POOL_WORLD\nActor       = POOL_ACTOR\nFrame       = POOL_FRAME\nPhysics     = POOL_PHYSICS\nAI          = POOL_AI\nClut        = POOL_CLUT\nAudio       = POOL_AUDIO\nVideo       = POOL_VIDEO\nImageObject = POOL_IMAGEOBJECT\nNode        = POOL_NODE\n\n[POOL_DEFAULT]\nSize = 5951424\n[POOL_DRIVERDATA]\nSize = 32768\n[POOL_RENDERLIST]\nSize = 4718592\n[POOL_DMA]\nSize = 1585152\n[POOL_HANDLES]\nSize = 262144\n[POOL_TEMPORARY]\nAliasedTo = Default\n[POOL_LEVEL]\nAliasedTo = Default\n[POOL_ATTRIBUTE]\nAliasedTo = Default\n[POOL_TEXTURE]\nAliasedTo = User1\n[POOL_IMAGE]\nAliasedTo = User1\n[POOL_USER0]\nAliasedTo = Default\n[POOL_USER1]\nSize = 10485760\n[POOL_LIST]\nAliasedTo = Default\n[POOL_VERTEX]\nAliasedTo = Default\n[POOL_APPLICATION]\nAliasedTo = Default\n[POOL_WORLD]\nAliasedTo = Default\n[POOL_ACTOR]\nAliasedTo = Default\n[POOL_FRAME]\nAliasedTo = Default\n[POOL_PHYSICS]\nAliasedTo = Default\n[POOL_AI]\nAliasedTo = Default\n[POOL_CLUT]\nAliasedTo = Default\n[POOL_AUDIO]\nAliasedTo = Default\n[POOL_VIDEO]\nAliasedTo = Default\n[POOL_IMAGEOBJECT]\nAliasedTo = Default\n[POOL_NODE]\nAliasedTo = Default\n";
}

void GameMain_ApplyIniText(void) {
    const char *iniText;

    iniText = GameMain_GetIniText();
    if (iniText != 0) {
        igObjectSystem_SetIniText(iniText);
    }
}

void GameMain_AtstreamThread(void) {
    struct { int len; int type; } hdr;
    char *buf;
    int h;

    buf = Memory_SystemAllocate(0x200);
    while (1) {
        h = sceOpen("atstream:!-5150", 3);
        if (sceRead(h, &hdr, 8) < 0) {
            sceClose(h);
            continue;
        }
        if (hdr.type == 0) {
            sceClose(h);
            continue;
        }
        if (hdr.len > 0) {
            sceRead(h, buf, hdr.len);
        }
        if (hdr.type == 1) {
            g_atstreamText = buf;
            buf[hdr.len] = 0;
            g_atstreamTextReady = 1;
        }
        hdr.len = 0;
        hdr.type = 0;
        sceWrite(h, "a", 2);
        sceClose(h);
    }
}

void GameMain_StartAtstreamThread(void) {
    igPsx2ThreadView *thread = (igPsx2ThreadView *)igThread_Create(0);
    thread->SetStackSize(0x2000);
    thread->SetFunction(&GameMain_AtstreamThread);
    thread->SetPriority(0xFF);
    thread->Start();
}

igResult igPsx2Thread_SetStackSize(igPsx2ThreadView *self, unsigned int stackSize) {
    if (self->IsRunning() == 0) {
        if (stackSize & 0xF) {
            return g_resultFailure;
        }
        self->_stackSize = stackSize;
        if (self->_userStack == 0) {
            int stack = self->_stack;
            if (stack != 0) {
                igObject_FreeMemory(self, stack);
            }
        }
        self->_userStack = 0;
        self->_stack = igObject_MallocAligned(self, self->_stackSize, self->GetStackAlignment() & 0xFFFF);
        return g_resultSuccess;
    }
    return g_resultFailure;
}

bool GameMain_SetAtfilePrefix(const char *path) {
    return g_atfilePrefixSet = igPsx2_SetAtfilePrefix(path) == g_resultSuccess;
}

void GameMain_InitAtstream(void) {
    if (g_atfilePrefixSet != 0) {
        GameMain_StartAtstreamThread();
    }
}

void GameMain_PollAtstream(Blk *app, int idle) {
    if (g_atfilePrefixSet != 0) {
        if (idle != 0) {
            igObjectList *threads = (igObjectList *)g_threadManager[0]->_threadList;
            ((igPsx2ThreadView *)((void **)threads->_data)[0])->Sleep(1000000);
        }
        if ((*(unsigned char *)&g_atstreamTextReady) != 0) {
            GameMain_ReplaceSceneFile(app, (int)g_atstreamText, g_atstreamFullReload);
            g_atstreamFullReload = 0;
            (*(unsigned char *)&g_atstreamTextReady) = 0;
        }
    }
}

static inline void releaseRef(igObject *object) {
    if (object != 0) {
        object->_refCount = object->_refCount - 1;
        if (((unsigned long long)(long long)object->_refCount & 0x7fffffULL) == 0) {
            igObject_Destroy(object);
        }
    }
}

static inline void resetNames(Blk *app, AdoptReference) { releaseRef(app->modelNames.p); app->modelNames.p = igStringRefList_Create(0); }

static inline void resetCounts(Blk *app, AdoptReference) { releaseRef(app->repeatCounts.p); app->repeatCounts.p = (igIntList *)igIntList_Create(0); }

void GameMain_ReplaceSceneFile(Blk *app, int text, int fullReload) {
    int interned;
    int pool;
    int index;
    NameList *counts;
    int defaultCount;
    resetNames(app, AdoptReference());
    if (text == 0) {
        interned = 0;
    } else {
        if (g_stringPool[0] == 0) {
            pool = StringPool_Allocate(0x10);
            if (pool != 0) {
                pool = StringPool_Construct(pool);
            }
            g_stringPool[0] = pool;
        }
        interned = StringPool_Intern(g_stringPool[0], text);
    }
    {
        StringRef name(interned);
        StringList_AppendRetained(app->modelNames.p, &name);
    }
    resetCounts(app, AdoptReference());
    counts = (NameList *)app->repeatCounts.p;
    index = counts->_count;
    if (index < counts->_capacity) {
        counts->_count = counts->count() + 1;
    } else {
        List_Resize(counts, index + 1, 4);
    }
    defaultCount = g_defaultNameValue;
    counts->_data[index] = defaultCount;
    GameMain_ReloadScene(app, defaultCount);
    if (fullReload != 0) {
        ViewerSetup_ResetView(app);
    }
}

void GameMain_LoadScene(Blk *app) {
    /* matching construct: hand search — the branch folds away, leaving the load and its delay slot */
    if (app->modelNames.p) return;
}

void GameMain_SetViewerFileLists(Blk *app, igStringRefList *modelNames, igIntList *repeatCounts) {
    app->modelNames = modelNames;
    app->repeatCounts = repeatCounts;
}

static inline int *internString(const char *s) {
    if (g_stringPool[0] == 0) {
        int pool = StringPool_Allocate(16);
        if (pool != 0) pool = StringPool_Construct(pool);
        g_stringPool[0] = pool;
    }
    return (int *)StringPool_Intern(g_stringPool[0], s);
}

static inline void setFolderName(igFolder *folder, const char *name) {
    int *s = internString(name);
    StringRef::Release((int *)folder->_folderName);
    folder->_folderName = (int)s;
}

Blk::Blk()
    : viewer(Viewer_CreateDisplay(0)), reservedA(0, kRetainReference), reservedB(0, kRetainReference), repeatCounts(0, kRetainReference),
      modelNames(0, kRetainReference), isFinished(false), fileNames(0, kRetainReference), folder(igFolder_Create(0), AdoptReference()),
      loadingMessage(igViewerLoadingFileMessage_Create(0), AdoptReference()) {
    setFolderName(folder, "cdrom0:");
    GameMain_ListIgbFiles(this);
}

Blk::~Blk() {
}

void GameMain_ReloadScene(Blk *app, int) {
    GameMain_ClearScene(app);
    GameMain_LoadScene(app);
}

void GameMain_RunGame(Blk *app) {
    beSystem *system;
    int nextStage;
    float clearColor[4];
    if (app->viewer.window.p != 0) {
        g_activeApp = app;
        AcquireSharedOptions();
        {
            SharedViewerOptions *options = g_sharedViewerOptions[0];
            options->optimizeTextures = 0;
            options->showLogo = 0;
            options->showNormals = 0;
            options->clearColor[0] = 0.1f;
            options->clearColor[1] = 0.1f;
            options->clearColor[2] = 0.1f;
            options->clearColor[3] = 1.0f;
            options->autoSceneLights = 0;
            options->useSceneLights = 1;
            options->alphaTest = 1;
        }
        ReleaseSharedOptions();
        CollisionLibrary_RegisterClasses();
        SceneSearchLibrary_RegisterClasses();
        AdxMovieLibrary_RegisterClasses();
        BecLibrary_RegisterClasses();
        LuaAPI_RegisterClasses();
        NdmwLibrary_RegisterClasses();
        ViewerSetup_Open(app);
        GameMain_LoadScene(app);
        ViewerSetup_ResetView(app);
        system = (beSystem *)igInsightCore_FindManager(app->viewer.core.p, g_beSystem_metaObject[0]);
        if (g_stringPool[0] == 0) {
            int pool = StringPool_Allocate(0x10);
            if (pool != 0) {
                pool = StringPool_Construct(pool);
            }
            g_stringPool[0] = pool;
        }
        {
            nextStage = ((int)StringPool_Intern(g_stringPool[0], "ndmw.igb"));
            ReleaseStringRef(system->_nextStage);
            system->_nextStage = nextStage;
        }
        {
            igVisualContextDispatchView *context = ((igWindowDispatchView *)app->viewer.window.p)->getVisualContext();
            clearColor[0] = 0.0f;
            clearColor[3] = 1.0f;
            clearColor[1] = 0.0f;
            clearColor[2] = 0.0f;
            context->setClearColor(clearColor);
        }
        while (app->isFinished == 0 && system->_isShutDown == 0) {
            while (app->isFinished == 0 && system->_isStageLoop != 0) {
                igInsightCore *core = (igInsightCore *)app->viewer.core.p;
                int idle = ((core->_frameTime >= 0xFE502B)) & 0xFF;
                if (core->_frames % 15 != 0) {
                    idle = 0;
                }
                GameMain_PollAtstream(app, idle);
                if (ViewerSetup_Update(app) == 0) break;
                ViewerSetup_RunFrame(app);
            }
            if (system->_nextStage == 0) break;
            GameMain_ClearScene(app);
            system->_isStageLoop = 1;
        }
        GameMain_ClearScene(app);
        ViewerSetup_Close(app);
        g_activeApp = 0;
    }
}

void GameMain_RunBenchmark(Blk *app) {
    ModelChange showGui;
    ModelChange showBoundingBox;
    ModelChange showNormals;
    ModelChange flushFrames;
    int skipFrames;
    float framesPerSecond;
    int result;
    int i;
    int frames;
    igViewerParameters *parameters;
    int step;
    if (app->viewer.window.p != 0) {
        CollisionLibrary_RegisterClasses();
        SceneSearchLibrary_RegisterClasses();
        ViewerSetup_Open(app);
        GameMain_LoadScene(app);
        ViewerSetup_ResetView(app);
        parameters = (igViewerParameters *)((igViewerSceneInfoManager *)app->viewer.sceneInfo.p)->_parameters;
        parameters->_showGui = 0;
        showGui.type = 2; showGui.flags = 0; showGui.field = g_igViewerParameters_showGuiMetaField[0];
        igModel_NotifyViews(parameters, &showGui);
        parameters->_showBoundingBox = 0;
        showBoundingBox.type = 2; showBoundingBox.flags = 0; showBoundingBox.field = g_igViewerParameters_showBoundingBoxMetaField[0];
        igModel_NotifyViews(parameters, &showBoundingBox);
        parameters->_showNormals = 0;
        showNormals.type = 2; showNormals.flags = 0; showNormals.field = g_igViewerParameters_showNormalsMetaField[0];
        igModel_NotifyViews(parameters, &showNormals);
        AcquireSharedOptions();
        skipFrames = g_sharedViewerOptions[0]->benchmarkSkipFrames;
        if (skipFrames < 0) skipFrames = 0;
        frames = g_sharedViewerOptions[0]->benchmarkFrames;
        if (frames < 0) frames = 0;
        ReleaseSharedOptions();
        ViewerSetup_Update(app);
        step = 0;
        if (0 < skipFrames) {
            do {
                ViewerSetup_RunFrame(app);
                step++;
            } while (step < skipFrames);
        }
        ViewerSetup_Update(app);
        igSmartPointer<igTimerDispatchView> timer(igTimer_Create(0), AdoptReference());
        timer->Restart();
        i = 0;
        if (0 < frames - 1) {
            do {
                ViewerSetup_RunFrame(app);
                i++;
            } while (i < frames - 1);
        }
        parameters->_flushFrames = 1;
        flushFrames.type = 2; flushFrames.flags = 0; flushFrames.field = g_igViewerParameters_flushFramesMetaField[0];
        igModel_NotifyViews(parameters, &flushFrames);
        ViewerSetup_RunFrame(app);
        timer->Stop();
        framesPerSecond = (1e9f * (float)frames) / (float)timer->GetElapsedTime();
        if (g_frameRateReportIgnored == 0) {
            result = igReport_Info("average frame rate over %d frames : %f fps", frames, fptodp(framesPerSecond));
            if (result != 1 && result == 2) g_frameRateReportIgnored = 1;
        }
        ViewerSetup_Close(app);
    }
}

void GameMain_ListIgbFiles(Blk *app) {
    char buf[256];
    igStringRefList *secondPass;
    int removeIndex;
    int index;
    int *interned;
    igStringRefList *firstPass;
    igStringRefList *renameList;
    igStringRefList *removeList;
    int count;
    int *slot;
    int slotOffset;

    Assign::Take(app->fileNames.p, ((igFolderDispatchView *)app->folder.p)->ListEntries());
    firstPass = app->fileNames.p;
    if (firstPass != 0) {
        index = firstPass->_count - 1;
        slotOffset = index * 4;
        if (index >= 0) {
            do {
                {
                StringRef name = StringList_CopyRetained(app->fileNames.p, index);
                strcpy(buf, name.p);
                buf[strlen(buf) - 2] = 0;
                if (g_stringPool[0] == 0) {
                    int pool = StringPool_Allocate(0x10);
                    if (pool != 0) pool = StringPool_Construct(pool);
                    g_stringPool[0] = pool;
                }
                interned = (int *)StringPool_Intern(g_stringPool[0], buf);
                StringRef::Release(name.p);
                name.p = interned;
                renameList = app->fileNames.p;
                count = renameList->_count;
                if (count != 0 && index >= 0 && index < count) {
                    slot = (int *)(renameList->_data + slotOffset);
                    if (name.p != 0) name.p[-1] = name.p[-1] + 1;
                    StringRef::Release((int *)*slot);
                    *slot = (int)name.p;
                }
                }
                index -= 1;
                slotOffset -= 4;
            } while (index >= 0);
        }
        secondPass = app->fileNames.p;
        if (secondPass != 0) {
            removeIndex = secondPass->_count - 1;
            if (removeIndex >= 0) {
                do {
                    {
                    StringRef name = StringList_CopyRetained(app->fileNames.p, removeIndex);
                    if (igStringObj_HasFileExtensionText(name.p, "igb") == 0) {
                        removeList = app->fileNames.p;
                        StringRef::Release(StringList_CopyRetained(removeList, removeIndex).p);
                        List_RemoveWordAt(removeList, removeIndex);
                        ((int *)removeList->_data)[removeList->_count] = 0;
                    }
                    }
                    removeIndex -= 1;
                } while (removeIndex >= 0);
            }
        }
    }
}

igSmartPointer<igStringRefList> igFolder_ListEntries(void) {
    return igSmartPointer<igStringRefList>(0, kRetainReference);
}

void GameMain_ClearScene(Blk *app) {
    igMemoryPoolView *userPool;
    igMemoryPoolView *allocator;
    igViewerSceneInfoManager *sceneInfo;
    ViewerSetup_ClearInfos();
    sceneInfo = AsSceneInfoManager(igInsightCore_FindManager(app->viewer.core.p, g_igViewerSceneInfoManager_metaObject[0]));
    ((igCommonTraversalDispatchView *)((igViewerRenderer *)sceneInfo->_viewerRenderer)->_sceneTraversal)->reset();
    ((igVisualContextDispatchView *)((igInsightCore *)app->viewer.core.p)->_visualContext)->releaseVertexArrays();
    RELEASE_SHIFTED(g_igEnbayaContextPool_instance.p);
    g_igEnbayaContextPool_instance.p = 0;
    { igMemoryPoolView *current = Memory_GetCurrentAllocator(); allocator = g_useOwnerAllocator != 0 ? current : Memory_GetAllocatorBySelector(kIGMemoryPoolHandleUser0[0]); }
    RELEASE_SHIFTED(g_igEnbayaContextPool_instance.p);
    g_igEnbayaContextPool_instance.p = igEnbayaContextPool_Create(allocator);
    { igMemoryPoolView *current = Memory_GetCurrentAllocator(); allocator = g_useOwnerAllocator != 0 ? current : Memory_GetAllocatorBySelector(kIGMemoryPoolHandleUser0[0]); }
    RELEASE_SHIFTED(g_igAnimationCombinerBoneInfoPool_instance.p);
    g_igAnimationCombinerBoneInfoPool_instance.p = igAnimationCombinerBoneInfoPool_Create(allocator);
    g_igAnimationCombinerBoneInfoPool_instance->_resetMode = 0;
    { igMemoryPoolView *current = Memory_GetCurrentAllocator(); allocator = g_useOwnerAllocator != 0 ? current : Memory_GetAllocatorBySelector(kIGMemoryPoolHandleUser0[0]); }
    RELEASE_SHIFTED(g_igAnimationStatePool_instance.p);
    g_igAnimationStatePool_instance.p = igAnimationStatePool_Create(allocator);
    { igMemoryPoolView *current = Memory_GetCurrentAllocator(); userPool = g_useOwnerAllocator != 0 ? current : Memory_GetAllocatorBySelector(kIGMemoryPoolHandleUser1[0]); }
    if (userPool != 0) {
        userPool->Trim(0);
    }
}
#pragma pop
