#include "dw4/support/reflected.h"
#include "dw4/core/igTDataList.h"
#include "dw4/core/igSmartPointer.h"
#include "dw4/windowinput/igWindowDispatchView.h"
#include "dw4/scenegraph/igCommonTraversalDispatchView.h"
#include "dw4/viewer/ViewerSetup.h"
#include "dw4/viewer/ViewerOptions.h"
#include "dw4/core/igMemoryPoolView.h"
#include "dw4/support/ClassRegistration.h"
#include "dw4/core/igMemoryPoolContext.h"
#include "dw4/core/igObjectSystem.h"
#include "dw4/core/igObject.h"
#include "dw4/core/igResult.h"
#include "dw4/core/igReport.h"
#include "dw4/core/igPsx2File.h"
#include "dw4/core/igThread.h"
#include "dw4/core/igTimer.h"
#include "dw4/core/igFolder.h"
#include "dw4/core/igDataLists.h"
#include "dw4/core/igStringObj.h"
#include "dw4/core/StringPool.h"
#include "dw4/core/igStringRef.h"
#include "dw4/scenegraph/AnimationPools.h"
#include "dw4/gfx/igVisualContext.h"
#include "dw4/insight/igInsightCore.h"
#include "dw4/gui/igModel.h"
#include "dw4/viewer/igViewerLoadingFileMessage.h"
#include "dw4/viewer/igViewerParameters.h"
#include "dw4/viewer/igViewerSceneInfoManager.h"
#include "dw4/game/beSystem.h"
#include "dw4/support/softfloat.h"
#include "dw4/sony/sifdev.h"
#include <string.h>
#include "dw4/support/list-services.h"

#pragma push
#pragma readonly_strings on
#define RELEASE_SHIFTED(v) { igObject *t_ = (igObject *)(v); if (t_ != 0) { t_->_refCount = t_->_refCount - 1; if (((unsigned long long) ((long long) (int) t_->_refCount << 0x29) >> 0x29) == 0) { igObject_Destroy(t_); } } }
/* matching construct: out-of-line ctor/dtor classes reproduce the retail unwind table (retail 0x2595e0 table 0x542b5c: App dtor 0x234b90, Blk dtor 0x25a330, scope guard dtor 0x2599b0) */
struct App { char options[232]; igIntList *intList; igStringRefList *stringList; App(); ~App(); };
struct Guard { ~Guard() { igObjectSystem_Release(); } };
/* The allocator a new pool comes from: the owner's, or the user-0 pool when the owner allocator is off. */
static inline int PoolAllocator(int owner) {
    if (g_useOwnerAllocator) return owner;
    else return ((int)Memory_GetAllocatorBySelector(kIGMemoryPoolHandleUser0));
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
    if (g_sharedViewerOptions == 0) {
        SharedViewerOptions *created = (SharedViewerOptions *)operator new(sizeof(SharedViewerOptions));
        if (created != 0) {
            created = igViewerDefaults_Construct(created);
        }
        g_sharedViewerOptions = created;
    }
    g_sharedViewerOptions->useCount = g_sharedViewerOptions->useCount + 1;
}

/* Releases a reference to an interned string. */
static inline void ReleaseStringRef(int string) {
    if (string != 0) {
        int *header = (int *)(string - 8);
        int count = ((int *)string)[-1] - 1;
        ((int *)string)[-1] = count;
        if (count == 0) {
            StringChunk_ReleaseHeader((StringChunk *)*header, (StringTokenHeader *)header);
        }
    }
}

/* Drops a use of the shared viewer options and frees them with the last one. */
static inline void ReleaseSharedOptions() {
    if (g_sharedViewerOptions != 0) {
        int remaining = g_sharedViewerOptions->useCount - 1;
        g_sharedViewerOptions->useCount = remaining;
        if (remaining <= 0) {
            SharedViewerOptions *options = g_sharedViewerOptions;
            if (options != 0) {
                if (&options->internedString) {
                    ReleaseStringRef(options->internedString);
                }
                if (options != 0) {
                    ReleaseStringRef((int)options->extraCommandLine);
                }
                operator delete(options);
            }
            g_sharedViewerOptions = 0;
        }
    }
}

extern "C" { char *g_atstreamText; }
extern "C" { char g_atstreamTextReady; }
/* igPsx2Thread (reflected layout in dw4/support/reflected.h) with the virtuals this file calls: slot 23 sleeps for a
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
extern "C" { bool g_atfilePrefixSet; }
extern "C" { unsigned char g_atstreamFullReload = 1; }
extern "C" { unsigned char g_startupFlagB = 1; }
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
typedef igTDataList<int> NameList;
extern "C" { int g_defaultNameValue = 1; }
extern "C" { Blk *g_activeApp; }
/* igFolder's virtual functions: slot 24 lists the folder's entries (igFolder_ListEntries).
 * ABI view only: never instantiated. */
class igFolderDispatchView : public igObjectDispatchView {
public:
    virtual void d21(); virtual void d22(); virtual void d23();
    virtual igSmartPointer<igStringRefList> ListEntries();                  /* slot 24 */
};
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
extern "C" { unsigned char g_frameRateReportIgnored; }
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
/* The manager when it is a viewer scene-info manager, else null. */
static inline igViewerSceneInfoManager *AsSceneInfoManager(igObject *manager) {
    if (manager != 0 && ((Gap::Core::igObject *)manager)->isOfType(g_igViewerSceneInfoManager_metaObject) != 0) return (igViewerSceneInfoManager *)manager; else return 0;
}
/* Defined below their first use. */
extern "C" {
void GameMain_ApplyIniText(void);
bool GameMain_SetAtfilePrefix(const char *path);
void GameMain_InitAtstream(void);
void GameMain_SetViewerFileLists(Blk *app, igStringRefList *modelNames, igIntList *repeatCounts);
void GameMain_RunGame(Blk *app);
void GameMain_RunBenchmark(Blk *app);
void GameMain_ReplaceSceneFile(Blk *app, int text, int fullReload);
void GameMain_ReloadScene(Blk *app, int);
void GameMain_ListIgbFiles(Blk *app);
void GameMain_ClearScene(Blk *app);
}

extern "C" void GameMain_RegisterEngineClasses(void) {
    igExternalImageEntry_EnsureRegistered();
    Gap::Core::igVirtualCFuncMetaField::arkRegister();
    Gap::Core::igUnsignedShortArrayMetaField::arkRegister();
    Gap::Core::igUnsignedLongArrayMetaField::arkRegister();
    Gap::Core::igUnsignedIntArrayMetaField::arkRegister();
    Gap::Core::igUnsignedCharArrayMetaField::arkRegister();
    Gap::Core::igStringArrayMetaField::arkRegister();
    Gap::Core::igShortArrayMetaField::arkRegister();
    Gap::Core::igRawRefArrayMetaField::arkRegister();
    igObjectStringMap_EnsureRegistered();
    igNamedObjectList_EnsureRegistered();
    Gap::Core::igObjectRefArrayMetaField::arkRegister();
    igNamedObjectInfo_EnsureRegistered();
    Gap::Core::igMemoryRefArrayMetaField::arkRegister();
    igMemoryFileEntryList_EnsureRegistered();
    Gap::Core::igLongArrayMetaField::arkRegister();
    Gap::Core::igFloatArrayMetaField::arkRegister();
    Gap::Core::igEnumArrayMetaField::arkRegister();
    Gap::Core::igDoubleMetaField::arkRegister();
    Gap::Core::igDoubleArrayMetaField::arkRegister();
    igDependencyMetaField_EnsureRegistered();
    igPointerListList_EnsureRegistered();
    Gap::Core::igBoolArrayMetaField::arkRegister();
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
    Gap::Math::igVec3fMetaField::arkRegister();
    Gap::Math::igVec2fMetaField::arkRegister();
    Gap::Math::igVec4fMetaField::arkRegister();
    Gap::Math::igVec4ucMetaField::arkRegister();
    Gap::Math::igMatrix44fMetaField::arkRegister();
    igTrackedElementMetaField_EnsureRegistered();
    igImage_EnsureRegistered();
    igViewportAttr_EnsureRegistered();
    igTextureAttr_EnsureRegistered();
    igImageMipMapList_EnsureRegistered();
    igTextureStateAttr_EnsureRegistered();
    igTextureMatrixStateAttr_EnsureRegistered();
    igTextureFunctionAttr_EnsureRegistered();
    igTextureBindAttr_EnsureRegistered();
    Gap::Attrs::igLightingStateAttr::arkRegister();
    Gap::Attrs::igDepthWriteStateAttr::arkRegister();
    igCullFaceAttr_EnsureRegistered();
    Gap::Attrs::igBlendStateAttr::arkRegister();
    igBlendFunctionAttr_EnsureRegistered();
    igAttrPool_EnsureRegistered();
    igAttrListList_EnsureRegistered();
    igAttrList_EnsureRegistered();
    Gap::Attrs::igAlphaStateAttr::arkRegister();
    Gap::Math::igVec4fArrayMetaField::arkRegister();
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
    Gap::Attrs::igVertexBlendStateAttr::arkRegister();
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
    Gap::Attrs::igFogStateAttr::arkRegister();
    Gap::Attrs::igDepthStateAttr::arkRegister();
    igLongList_EnsureRegistered();
    igVec3fList_EnsureRegistered();
    igGroup_EnsureRegistered();
    igTransformSequence1_5_EnsureRegistered();
    igQuaternionfList_EnsureRegistered();
    igAlphaFunctionAttr_EnsureRegistered();
    igBillboard_EnsureRegistered();
    Gap::Attrs::igNormalizeNormalsStateAttr::arkRegister();
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

extern "C" int main(int argc, char **argv) {
    int allocator;
    SharedViewerOptions *options;
    GameMain_ApplyIniText();
    GameMain_SetAtfilePrefix(argv[0]);
    g_igPsx2_useCdrom = 2;
    g_reportEchoToStdout = 0;
    g_igPsx2_iopImagePath = "cdrom0:\\MODULES\\IOPRP280.IMG;1";
    g_igPsx2_resetIopServices = 1;
    g_startupFlagB = 0;
    g_bootstrapPoolPreSize = 0x40000;
    g_systemPoolPreSize = 0x4000;
    g_metaDataPoolPreSize = 0xA0000;
    g_stringPoolPreSize = 0x69000;
    igObjectSystem_Acquire(0xC80);
    Guard guard;
    GameMain_InitAtstream();
    GameMain_RegisterEngineClasses();
    App args;
    igCommandLine_ParseArgs(&args, argc, argv);
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
    if (g_sharedViewerOptions->benchmark != 0) GameMain_RunBenchmark(&app);
    else GameMain_RunGame(&app);
    ReleaseSharedOptions();
    return 0;
}

extern "C" const char *GameMain_GetIniText(void) {
    return "[CORE]\nintrinsicModulePath = MODULES\nsonyModulePath = MODULES\nuserFileIO = false\nscratchPoolSize = 0x4000\nmoveVTablesToScratchPad = 1\n[DISPLAY]\nsupportMultitap = PORT0\n[BECRUNTIME]\nAdxModulePath = /MODULES\n[MEMORYPOOLS]\nDefault     = POOL_DEFAULT\nDriverData  = POOL_DRIVERDATA\nRenderList  = POOL_RENDERLIST\nDMA         = POOL_DMA\nHandles     = POOL_HANDLES\n\nTemporary   = POOL_TEMPORARY\nLevel       = POOL_LEVEL\nAttribute   = POOL_ATTRIBUTE\nTexture     = POOL_TEXTURE\nImage       = POOL_IMAGE\nUser0       = POOL_USER0\nUser1       = POOL_USER1\n\nList        = POOL_LIST\nVertex      = POOL_VERTEX\nApplication = POOL_APPLICATION\nWorld       = POOL_WORLD\nActor       = POOL_ACTOR\nFrame       = POOL_FRAME\nPhysics     = POOL_PHYSICS\nAI          = POOL_AI\nClut        = POOL_CLUT\nAudio       = POOL_AUDIO\nVideo       = POOL_VIDEO\nImageObject = POOL_IMAGEOBJECT\nNode        = POOL_NODE\n\n[POOL_DEFAULT]\nSize = 5951424\n[POOL_DRIVERDATA]\nSize = 32768\n[POOL_RENDERLIST]\nSize = 4718592\n[POOL_DMA]\nSize = 1585152\n[POOL_HANDLES]\nSize = 262144\n[POOL_TEMPORARY]\nAliasedTo = Default\n[POOL_LEVEL]\nAliasedTo = Default\n[POOL_ATTRIBUTE]\nAliasedTo = Default\n[POOL_TEXTURE]\nAliasedTo = User1\n[POOL_IMAGE]\nAliasedTo = User1\n[POOL_USER0]\nAliasedTo = Default\n[POOL_USER1]\nSize = 10485760\n[POOL_LIST]\nAliasedTo = Default\n[POOL_VERTEX]\nAliasedTo = Default\n[POOL_APPLICATION]\nAliasedTo = Default\n[POOL_WORLD]\nAliasedTo = Default\n[POOL_ACTOR]\nAliasedTo = Default\n[POOL_FRAME]\nAliasedTo = Default\n[POOL_PHYSICS]\nAliasedTo = Default\n[POOL_AI]\nAliasedTo = Default\n[POOL_CLUT]\nAliasedTo = Default\n[POOL_AUDIO]\nAliasedTo = Default\n[POOL_VIDEO]\nAliasedTo = Default\n[POOL_IMAGEOBJECT]\nAliasedTo = Default\n[POOL_NODE]\nAliasedTo = Default\n";
}

void GameMain_ApplyIniText(void) {
    const char *iniText;

    iniText = GameMain_GetIniText();
    if (iniText != 0) {
        igObjectSystem_SetIniText(iniText);
    }
}

extern "C" void GameMain_AtstreamThread(void) {
    struct { int len; int type; } hdr;
    char *buf;
    int h;

    buf = (char *)Memory_SystemAllocate(0x200);
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

extern "C" void GameMain_StartAtstreamThread(void) {
    igPsx2ThreadView *thread = (igPsx2ThreadView *)igThread_Create(0);
    thread->SetStackSize(0x2000);
    thread->SetFunction(&GameMain_AtstreamThread);
    thread->SetPriority(0xFF);
    thread->Start();
}

extern "C" igResult igPsx2Thread_SetStackSize(igPsx2ThreadView *self, unsigned int stackSize) {
    if (self->IsRunning() == 0) {
        if (stackSize & 0xF) {
            return g_resultFailure;
        }
        self->_stackSize = stackSize;
        if (self->_userStack == 0) {
            int stack = self->_stack;
            if (stack != 0) {
                ((Gap::Core::igObject *)self)->free((void *)stack);
            }
        }
        self->_userStack = 0;
        self->_stack = (int)((Gap::Core::igObject *)self)->mallocAligned(self->_stackSize, self->GetStackAlignment());
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

extern "C" void GameMain_PollAtstream(Blk *app, int idle) {
    if (g_atfilePrefixSet != 0) {
        if (idle != 0) {
            igObjectList *threads = (igObjectList *)g_threadManager->_threadList;
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

static inline void resetCounts(Blk *app, AdoptReference) { releaseRef(app->repeatCounts.p); app->repeatCounts.p = igIntList_Create(0); }

void GameMain_ReplaceSceneFile(Blk *app, int text, int fullReload) {
    int index;
    NameList *counts;
    int defaultCount;
    resetNames(app, AdoptReference());
    {
        igStringRef name((char *)text);
        StringList_AppendRetained(app->modelNames.p, &name.p);
    }
    resetCounts(app, AdoptReference());
    counts = (NameList *)app->repeatCounts.p;
    index = counts->_count;
    if (index < counts->_capacity) {
        counts->_count = counts->count() + 1;
    } else {
        ((Gap::Core::igDataList *)counts)->resizeAndSetCount(index + 1, 4);
    }
    defaultCount = g_defaultNameValue;
    counts->_data[index] = defaultCount;
    GameMain_ReloadScene(app, defaultCount);
    if (fullReload != 0) {
        ViewerSetup_ResetView(&app->viewer);
    }
}

extern "C" void GameMain_LoadScene(Blk *app) {
    /* matching construct: hand search — the branch folds away, leaving the load and its delay slot */
    if (app->modelNames.p) return;
}

void GameMain_SetViewerFileLists(Blk *app, igStringRefList *modelNames, igIntList *repeatCounts) {
    app->modelNames = modelNames;
    app->repeatCounts = repeatCounts;
}

static inline int *internString(const char *s) {
    if (g_stringPool == 0) {
        StringPool *pool = (StringPool *)StringPool_Allocate(16);
        if (pool != 0) pool = StringPool_Construct(pool);
        g_stringPool = pool;
    }
    return (int *)StringPool_Intern((StringPool *)g_stringPool, s);
}

static inline void setFolderName(igFolder *folder, const char *name) {
    int *s = internString(name);
    releaseString((const char *)folder->_folderName);
    folder->_folderName = (int)s;
}

Blk::Blk()
    : viewer(igInsightCore_CreateWindow(0)), reservedA(0, kRetainReference), reservedB(0, kRetainReference), repeatCounts(0, kRetainReference),
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
            SharedViewerOptions *options = g_sharedViewerOptions;
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
        ViewerSetup_Open(&app->viewer);
        GameMain_LoadScene(app);
        ViewerSetup_ResetView(&app->viewer);
        system = (beSystem *)igInsightCore_FindManager((igInsightCore *)app->viewer.core.p, g_beSystem_metaObject);
        if (g_stringPool == 0) {
            StringPool *pool = (StringPool *)StringPool_Allocate(0x10);
            if (pool != 0) {
                pool = StringPool_Construct(pool);
            }
            g_stringPool = pool;
        }
        {
            nextStage = (int)StringPool_Intern(g_stringPool, "ndmw.igb");
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
                if (ViewerSetup_Update(&app->viewer) == 0) break;
                ViewerSetup_RunFrame(&app->viewer);
            }
            if (system->_nextStage == 0) break;
            GameMain_ClearScene(app);
            system->_isStageLoop = 1;
        }
        GameMain_ClearScene(app);
        ViewerSetup_Close(&app->viewer);
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
        ViewerSetup_Open(&app->viewer);
        GameMain_LoadScene(app);
        ViewerSetup_ResetView(&app->viewer);
        parameters = (igViewerParameters *)((igViewerSceneInfoManager *)app->viewer.sceneInfo.p)->_parameters;
        parameters->_showGui = 0;
        showGui.type = 2; showGui.source = 0; showGui.field = g_igViewerParameters_showGuiMetaField;
        igModel_NotifyViews((igModel *)parameters, &showGui);
        parameters->_showBoundingBox = 0;
        showBoundingBox.type = 2; showBoundingBox.source = 0; showBoundingBox.field = g_igViewerParameters_showBoundingBoxMetaField;
        igModel_NotifyViews((igModel *)parameters, &showBoundingBox);
        parameters->_showNormals = 0;
        showNormals.type = 2; showNormals.source = 0; showNormals.field = g_igViewerParameters_showNormalsMetaField;
        igModel_NotifyViews((igModel *)parameters, &showNormals);
        AcquireSharedOptions();
        skipFrames = g_sharedViewerOptions->benchmarkSkipFrames;
        if (skipFrames < 0) skipFrames = 0;
        frames = g_sharedViewerOptions->benchmarkFrames;
        if (frames < 0) frames = 0;
        ReleaseSharedOptions();
        ViewerSetup_Update(&app->viewer);
        step = 0;
        if (0 < skipFrames) {
            do {
                ViewerSetup_RunFrame(&app->viewer);
                step++;
            } while (step < skipFrames);
        }
        ViewerSetup_Update(&app->viewer);
        igSmartPointer<igTimerDispatchView> timer((igTimerDispatchView *)igTimer_Create(0), AdoptReference());
        timer->Restart();
        i = 0;
        if (0 < frames - 1) {
            do {
                ViewerSetup_RunFrame(&app->viewer);
                i++;
            } while (i < frames - 1);
        }
        parameters->_flushFrames = 1;
        flushFrames.type = 2; flushFrames.source = 0; flushFrames.field = g_igViewerParameters_flushFramesMetaField;
        igModel_NotifyViews((igModel *)parameters, &flushFrames);
        ViewerSetup_RunFrame(&app->viewer);
        timer->Stop();
        framesPerSecond = (1e9f * (float)frames) / (float)timer->GetElapsedTime();
        if (g_frameRateReportIgnored == 0) {
            result = igReport_Info("average frame rate over %d frames : %f fps", frames, fptodp(framesPerSecond));
            if (result != 1 && result == 2) g_frameRateReportIgnored = 1;
        }
        ViewerSetup_Close(&app->viewer);
    }
}

void GameMain_ListIgbFiles(Blk *app) {
    char buf[256];
    igStringRefList *secondPass;
    int removeIndex;
    int index;
    igStringRefList *firstPass;
    igStringRefList *renameList;
    igStringRefList *removeList;
    int count;

    Assign::Take(app->fileNames.p, ((igFolderDispatchView *)app->folder.p)->ListEntries());
    firstPass = app->fileNames.p;
    if (firstPass != 0) {
        index = firstPass->_count - 1;
        if (index >= 0) {
            do {
                {
                igStringRef name = StringList_CopyRetained(app->fileNames.p, index);
                strcpy(buf, name.p);
                buf[strlen(buf) - 2] = 0;
                name = buf;
                renameList = app->fileNames.p;
                count = renameList->_count;
                if (count != 0 && index >= 0 && index < count) {
                    ((igStringRef *)renameList->_data)[index] = name;
                }
                }
                index -= 1;
            } while (index >= 0);
        }
        secondPass = app->fileNames.p;
        if (secondPass != 0) {
            removeIndex = secondPass->_count - 1;
            if (removeIndex >= 0) {
                do {
                    {
                    igStringRef name = StringList_CopyRetained(app->fileNames.p, removeIndex);
                    if (igStringObj_HasFileExtensionText(name.p, "igb") == 0) {
                        removeList = app->fileNames.p;
                        releaseString(StringList_CopyRetained(removeList, removeIndex).p);
                        List_RemoveWordAt((igDataList *)removeList, removeIndex);
                        ((int *)removeList->_data)[removeList->_count] = 0;
                    }
                    }
                    removeIndex -= 1;
                } while (removeIndex >= 0);
            }
        }
    }
}

extern "C" igSmartPointer<igStringRefList> igFolder_ListEntries(void) {
    return igSmartPointer<igStringRefList>(0, kRetainReference);
}

void GameMain_ClearScene(Blk *app) {
    igMemoryPoolView *userPool;
    igMemoryPoolView *allocator;
    igViewerSceneInfoManager *sceneInfo;
    ViewerSetup_ClearInfos(&app->viewer);
    sceneInfo = AsSceneInfoManager(igInsightCore_FindManager((igInsightCore *)app->viewer.core.p, g_igViewerSceneInfoManager_metaObject));
    ((igCommonTraversalDispatchView *)((igViewerRenderer *)sceneInfo->_viewerRenderer)->_sceneTraversal)->reset();
    ((igVisualContextDispatchView *)((igInsightCore *)app->viewer.core.p)->_visualContext)->releaseVertexArrays();
    RELEASE_SHIFTED(g_igEnbayaContextPool_instance.p);
    g_igEnbayaContextPool_instance.p = 0;
    { igMemoryPoolView *current = (igMemoryPoolView *)Memory_GetCurrentAllocator(); allocator = g_useOwnerAllocator != 0 ? current : (igMemoryPoolView *)Memory_GetAllocatorBySelector(kIGMemoryPoolHandleUser0); }
    RELEASE_SHIFTED(g_igEnbayaContextPool_instance.p);
    g_igEnbayaContextPool_instance.p = igEnbayaContextPool_Create((int)allocator);
    { igMemoryPoolView *current = (igMemoryPoolView *)Memory_GetCurrentAllocator(); allocator = g_useOwnerAllocator != 0 ? current : (igMemoryPoolView *)Memory_GetAllocatorBySelector(kIGMemoryPoolHandleUser0); }
    RELEASE_SHIFTED(g_igAnimationCombinerBoneInfoPool_instance.p);
    g_igAnimationCombinerBoneInfoPool_instance.p = igAnimationCombinerBoneInfoPool_Create((int)allocator);
    g_igAnimationCombinerBoneInfoPool_instance->_resetMode = 0;
    { igMemoryPoolView *current = (igMemoryPoolView *)Memory_GetCurrentAllocator(); allocator = g_useOwnerAllocator != 0 ? current : (igMemoryPoolView *)Memory_GetAllocatorBySelector(kIGMemoryPoolHandleUser0); }
    RELEASE_SHIFTED(g_igAnimationStatePool_instance.p);
    g_igAnimationStatePool_instance.p = igAnimationStatePool_Create((int)allocator);
    { igMemoryPoolView *current = (igMemoryPoolView *)Memory_GetCurrentAllocator(); userPool = g_useOwnerAllocator != 0 ? current : (igMemoryPoolView *)Memory_GetAllocatorBySelector(kIGMemoryPoolHandleUser1); }
    if (userPool != 0) {
        userPool->Trim(0);
    }
}
#pragma pop
