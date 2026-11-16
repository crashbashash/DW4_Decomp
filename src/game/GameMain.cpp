#include "dw4/reflected.h"
#include "dw4/igTDataList.h"
#include "dw4/igSmartPointer.h"
#include "dw4/ViewerSetup.h"

#pragma push
#pragma readonly_strings on
#define REL(x) if ((x) != 0) { int *hd_ = (int *)(x) - 2; int c_ = ((int *)(x))[-1] - 1; ((int *)(x))[-1] = c_; if (c_ == 0) StringChunk_ReleaseHeader(*hd_, hd_); }
#define REL_25afe0(v) { igObject *t_ = (igObject *)(v); if (t_ != 0) { t_->_refCount = t_->_refCount - 1; if (((unsigned long long) ((long long) (int) t_->_refCount << 0x29) >> 0x29) == 0) { igObject_Destroy(t_); } } }

class Pool;
struct NamedLists;
struct Holder;
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
extern "C" int FUN_0019d360(...);
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
extern "C" void FUN_002590c0(void);
extern "C" int __dl__FPv(...);
extern "C" int FUN_00165d20(int);
extern "C" int igObjectSystem_Acquire(int);
extern "C" int igObjectSystem_Release(...);
extern "C" int StringChunk_ReleaseHeader(...);
extern "C" int main(int arg0, int *arg1);
extern "C" const char *FUN_00259a10(void);
extern "C" int igObjectSystem_SetIniText(const char *);
extern "C" void FUN_00259a20(void);
extern "C" int sceOpen(char *, int);
extern "C" int sceClose(int);
extern "C" int sceRead(int, void *, int);
extern "C" int sceWrite(int, const char *, int);
extern "C" char *Memory_SystemAllocate(int);
extern "C" void FUN_00259a60(void);
extern "C" void **igThread_Create(...);
extern "C" void FUN_00259b60(void);
extern "C" int igObject_MallocAligned(...);
extern "C" int igObject_FreeMemory(...);
extern "C" bool FUN_00259cd0(const char *path);
extern "C" void FUN_00259d10(void);
extern "C" int StringPool_Allocate(...);
extern "C" int FUN_00463c70(...);
extern "C" int StringPool_Construct(...);
extern "C" int StringPool_Intern(...);
extern "C" void FUN_00259f80(int *arg0);
extern "C" void *igInsightCore_FindManager(...);
extern "C" int FUN_00239390(...);
extern "C" int FUN_00238d40(...);
extern "C" int FUN_003343a0(...);
extern "C" int FUN_0033bf50(...);
extern "C" int LuaAPI_RegisterClasses(...);
extern "C" int FUN_003b04e0(...);
extern "C" int FUN_00463b30(...);
extern "C" int FUN_00463b70(...);
extern "C" int FUN_00463bb0(...);
extern "C" int FUN_00463bc0(...);
extern "C" float __floatdisf(int);
extern "C" int fptodp(float);
extern "C" int igReport_Info(...);
extern "C" int igModel_NotifyViews(...);
extern "C" int thunk_FUN_00238ed0(...);
extern "C" int strcpy(...);
extern "C" int strlen(...);
extern "C" int igStringObj_HasFileExtensionText(...);
extern "C" int List_RemoveWordAt(...);
extern "C" void igFolder_ListEntries(void **arg0);
extern "C" int igObject_IsKindOf(...);
extern "C" int FUN_00463c80(...);
typedef igObject Obj;
/* matching construct: out-of-line ctor/dtor classes reproduce the retail unwind table (retail 0x2595e0 table 0x542b5c: App dtor 0x234b90, Blk dtor 0x25a330, scope guard dtor 0x2599b0) */
struct App { char p[232]; int f232; int f236; App(); ~App(); };
struct G { int f0; char p[212]; unsigned char f216; char p2[15]; int f232; int f236; };
extern "C" G * __nw__FUi(...);
extern "C" int FUN_00234d70(App *, int, int *);
extern "C" G * ViewerOptions_Construct(...);
extern "C" Pool *Memory_GetAllocatorBySelector(int);
extern "C" igAnimationCombinerBoneInfoPool * igAnimationCombinerBoneInfoPool_Create(...);
extern "C" igAnimationStatePool * igAnimationStatePool_Create(...);
extern "C" igEnbayaContextPool * igEnbayaContextPool_Create(...);
extern igSmartPointer<igAnimationCombinerBoneInfoPool> g_igAnimationCombinerBoneInfoPool_instance;
extern "C" G *g_sharedViewerOptions[4];
extern "C" int DAT_00586fd8[4];
extern "C" int DAT_00586fe0[4];
extern "C" int DAT_00586fe8[4];
extern "C" int DAT_00586ff0[4];
extern "C" int kIGMemoryPoolHandleUser0[4];
extern "C" int DAT_00587338[4];
extern "C" const char *DAT_00587340[4];
extern "C" char GPR_0055499c;
extern "C" char GPR_005549b8;
extern "C" unsigned char g_useOwnerAllocator;
struct Guard { ~Guard() { igObjectSystem_Release(); } };
struct U {
    static inline int alloc(int fallback) {
        if (g_useOwnerAllocator) return fallback;
        else return ((int)Memory_GetAllocatorBySelector(kIGMemoryPoolHandleUser0[0]));
    }
    static inline void relg(Obj **g) {
        Obj *o = g[0];
        if (o != 0) {
            o->_refCount = o->_refCount - 1;
            if (((unsigned long long)(long long)o->_refCount & 0x7fffffULL) == 0) igObject_Destroy(o);
        }
    }
    static inline void relstr(int *slot) {
        if (slot != 0) {
            int v = *slot;
            if (v != 0) {
                int *hd = (int *)(v - 8);
                int c = ((int *)v)[-1] - 1;
                ((int *)v)[-1] = c;
                if (c == 0) StringChunk_ReleaseHeader(*hd, hd);
            }
        }
    }
};
extern "C" { char *g_atstreamText; }
extern "C" { char g_atstreamTextReady; }
struct DW4SR4 { int w0; };
class DW4VCSR_120_0 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual DW4SR4 vX(); };
class DW4VCSR_132_1 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual DW4SR4 vX(void (*)(void)); };
class DW4VCSR_156_1 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual void d32(); virtual void d33(); virtual void d34(); virtual void d35(); virtual void d36(); virtual DW4SR4 vX(int); };
class DW4VCSR_200_1 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual void d32(); virtual void d33(); virtual void d34(); virtual void d35(); virtual void d36(); virtual void d37(); virtual void d38(); virtual void d39(); virtual void d40(); virtual void d41(); virtual void d42(); virtual void d43(); virtual void d44(); virtual void d45(); virtual void d46(); virtual void d47(); virtual DW4SR4 vX(int); };
struct R { int v; R() {} R(int x) { v = x; } R(const R &o) : v(o.v) {} };
class C { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual int v30(); virtual void d31(); virtual void d32(); virtual void d33(); virtual void d34(); virtual void d35(); virtual void d36(); virtual void d37(); virtual void d38(); virtual void d39(); virtual int v40(); char p4[28]; int f32; int f36; char p40[5]; unsigned char f45; };
extern "C" int g_resultSuccess[4];
extern "C" int g_resultFailure[4];
extern "C" R igPsx2Thread_SetStackSize(C *arg1, int arg2);
class igResult {
public:
    int v;
    igResult(const igResult &o) : v(o.v) {}
    bool operator==(const igResult &o) const { return v == o.v; }
};
extern "C" igResult igPsx2_SetAtfilePrefix(const char *path);
extern "C" { bool g_atfilePrefixSet; }
extern "C" void * g_threadManager[4];
extern "C" { unsigned char g_atstreamFullReload = 1; }
extern "C" { unsigned char g_startupFlagB = 1; }
struct R_259d40 { int a; };
class VC { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual R_259d40 vX(int); };
extern "C" void FUN_00259d40(NamedLists *arg0, int arg1);
typedef struct CountedHeader { int w0; int refs; } CountedHeader;
typedef igTDataList<int> NameList;
typedef struct NamedLists { char pad[36]; NameList *_names; void *_name; } NamedLists;
extern "C" CountedHeader *igStringRefList_Create(int);
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
extern "C" int FUN_001ca620(void *, StringRef *);
extern "C" void FUN_00259dc0(NamedLists *arg0, int arg1, int arg2);
struct R_259f90 { int w0; int rc; };
struct A { char pad[36]; struct R_259f90 *f36; struct R_259f90 *f40; };
extern "C" void FUN_00259f90(struct A *arg0, struct R_259f90 *arg1, struct R_259f90 *arg2);
extern "C" void FUN_0025a550(NamedLists *arg0, int);
struct Fr;
extern "C" { struct A0 *g_activeApp; }
extern "C" int g_beSystem_metaObject[16];
struct Fr {
    void *f0;
    char f4;
    unsigned char f5;
    char p0[86];
    unsigned char f92;
    char p1;
    unsigned char f94;
    char p2[53];
    int f148;
    int f152;
    int f156;
    int f160;
    char p3[4];
    unsigned char f168;
    char p4[11];
    unsigned char f180;
    char p5[32];
    unsigned char f213;
    char p6[18];
    int f232;
    void *f236;
};
struct Rd {
    char p0[16];
    unsigned char f16;
    char p1[43];
    void *f60;
    unsigned char f64;
};
struct X { char p0[52]; int f52; char p1[8]; long long f64; };
class D { public: virtual void e0(); virtual void e1(); virtual void e2(); virtual void e3(); virtual void e4(); virtual void e5(); virtual void e6(); virtual void e7(); virtual void e8(); virtual void e9(); virtual void e10(); virtual void e11(); virtual void e12(); virtual void e13(); virtual void e14(); virtual void e15(); virtual void e16(); virtual void e17(); virtual void e18(); virtual void e19(); virtual void e20(); virtual void e21(); virtual void e22(); virtual void e23(); virtual void e24(); virtual void e25(); virtual void e26(); virtual void e27(); virtual void e28(); virtual void e29(); virtual void e30(); virtual void e31(); virtual void e32(); virtual void e33(); virtual void e34(); virtual void e35(); virtual void e36(); virtual void e37(); virtual void e38(); virtual void e39(); virtual void e40(); virtual void e41(); virtual void e42(); virtual void e43(); virtual void e44(); virtual void e45(); virtual void e46(); virtual void e47(); virtual void e48(); virtual void e49(); virtual void e50(); virtual void e51(); virtual void e52(); virtual void e53(); virtual void e54(); virtual void e55(); virtual void e56(); virtual void e57(); virtual void e58(); virtual void e59(); virtual void e60(); virtual void e61(); virtual void e62(); virtual void e63(); virtual void e64(); virtual void e65(); virtual void e66(); virtual void e67(); virtual void e68(); virtual void e69(); virtual void e70(); virtual void e71(); virtual void e72(); virtual void e73(); virtual void e74(); virtual void e75(); virtual void e76(); virtual void e77(); virtual void e78(); virtual void e79(); virtual void e80(); virtual void e81(); virtual void e82(); virtual void e83(); virtual void e84(); virtual void e85(); virtual void e86(); virtual void e87(); virtual void e88(); virtual void e89(); virtual void e90(); virtual void e91(); virtual void e92(); virtual void e93(); virtual void e94(); virtual void e95(); virtual void e96(); virtual void e97(); virtual void e98(); virtual void e99(); virtual void e100(); virtual void e101(); virtual void e102(); virtual void e103(); virtual void e104(); virtual void e105(); virtual void e106(); virtual void e107(); virtual void e108(); virtual void e109(); virtual void e110(); virtual void e111(); virtual void e112(); virtual void e113(); virtual void e114(); virtual void e115(); virtual void e116(); virtual void e117(); virtual void e118(); virtual void e119(); virtual void e120(); virtual void e121(); virtual void e122(); virtual void e123(); virtual void e124(); virtual void e125(); virtual void e126(); virtual void e127(); virtual void e128(); virtual void e129(); virtual void e130(); virtual void e131(); virtual void e132(); virtual void e133(); virtual void e134(); virtual void e135(); virtual void e136(); virtual void e137(); virtual void e138(); virtual void e139(); virtual void e140(); virtual void e141(); virtual void e142(); virtual void e143(); virtual void e144(); virtual void e145(); virtual void e146(); virtual void e147(); virtual void e148(); virtual void e149(); virtual void e150(); virtual void e151(); virtual void e152(); virtual void e153(); virtual void e154(); virtual void e155(); virtual void e156(); virtual void e157(); virtual void e158(); virtual void e159(); virtual void e160(); virtual void e161(); virtual void e162(); virtual void e163(); virtual void e164(); virtual void e165(); virtual void e166(); virtual void e167(); virtual void e168(); virtual void e169(); virtual void e170(); virtual void e171(); virtual void e172(); virtual void e173(); virtual void e174();  virtual void vB(int *); };
class C_25a580 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual void d32(); virtual void d33(); virtual void d34(); virtual void d35();  virtual D *vA(); };
struct A0 { X *f0; char p0[20]; C_25a580 *f24; char p1[16]; unsigned char f44; };
extern "C" void FUN_0025a580(A0 *arg0);
struct Frame {
    void *f0;
    char pad[228];
    int f232;
    void *f236;
};
struct Ev { int a; int b; int c; int d; };
struct Tm {
    virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23();
    virtual int vA(); virtual void d25(); virtual void vB(); virtual void d27(); virtual void d28(); virtual void vC();
    int rc;
};
struct App_25a8c0 { int f0; igViewerSceneInfoManager *f4; char pad[16]; int f24; };
extern "C" Tm *igTimer_Create(...);
extern "C" int DAT_0058cab8[4];
extern "C" int DAT_0058cac0[4];
extern "C" int DAT_0058cac8[4];
extern "C" int DAT_0058cad0[4];
extern "C" { unsigned char g_frameRateReportIgnored; }
struct TimerType {};
struct Ref {
    Tm *p;
    Ref(Tm *object) : p(object) {}
    ~Ref() {
        Tm *object = p;
        if (object) {
            --object->rc;
            if (((unsigned long long)(long long)object->rc & 0x7fffffULL) == 0)
                igObject_Destroy(object);
        }
    }
};
extern "C" void FUN_0025a8c0(App_25a8c0 *arg0);
struct R_25ac60 { int w0; int refs; int f8; int w12; int *f16; };
extern "C" igSmartPointer<igPsx2Window> Viewer_CreateDisplay(int);
extern "C" igFolder *igFolder_Create(int);
extern "C" igViewerLoadingFileMessage *FUN_0045a680(int);
struct Blk {
    ViewerSetup viewer;
    igSmartPointer<igObject> f28;
    igSmartPointer<igObject> f32;
    igSmartPointer<igIntList> f36;
    igSmartPointer<igStringRefList> f40;
    bool f44;
    igSmartPointer<igStringRefList> f48;
    igSmartPointer<igFolder> folder;
    igSmartPointer<igViewerLoadingFileMessage> loadingMessage;
    Blk();
    ~Blk();
};
class V { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual igSmartPointer<igStringRefList> v24(); };
/* matching construct: the returned reference is a temporary of the call, so it takes a low frame slot and is released right after the store */
struct Assign {
    static inline void Take(R_25ac60 *&dst, const igSmartPointer<igStringRefList> &src) {
        R_25ac60 *rs = (R_25ac60 *)src.p;
        R_25ac60 *o;
        if (rs != 0) rs->refs = rs->refs + 1;
        o = dst;
        if (o != 0) {
            o->refs = o->refs - 1;
            if (((unsigned long long)(long long)o->refs & 0x7fffffULL) == 0) igObject_Destroy(o);
        }
        dst = rs;
    }
};
struct S { char p0[48]; R_25ac60 *f48; V *f52; };
extern "C" StringRef StringList_CopyRetained(void *, int);
extern "C" void FUN_0025ac60(S *arg0);
class Pool {
public:
    virtual void d0();
    virtual void d1();
    virtual void d2();
    virtual void d3();
    virtual void d4();
    virtual void d5();
    virtual void d6();
    virtual void d7();
    virtual void d8();
    virtual void d9();
    virtual void d10();
    virtual void d11();
    virtual void d12();
    virtual void d13();
    virtual void d14();
    virtual void d15();
    virtual void d16();
    virtual void d17();
    virtual void d18();
    virtual void d19();
    virtual void d20();
    virtual void d21();
    virtual void d22();
    virtual void d23();
    virtual void d24();
    virtual void v108(int);
};
class Ctl {
public:
    virtual void d0();
    virtual void d1();
    virtual void d2();
    virtual void d3();
    virtual void d4();
    virtual void d5();
    virtual void d6();
    virtual void d7();
    virtual void d8();
    virtual void d9();
    virtual void d10();
    virtual void d11();
    virtual void d12();
    virtual void d13();
    virtual void d14();
    virtual void d15();
    virtual void d16();
    virtual void d17();
    virtual void d18();
    virtual void d19();
    virtual void d20();
    virtual void d21();
    virtual void d22();
    virtual void d23();
    virtual void d24();
    virtual void d25();
    virtual void d26();
    virtual void d27();
    virtual void d28();
    virtual void v124();
};
class Sub {
public:
    virtual void d0();
    virtual void d1();
    virtual void d2();
    virtual void d3();
    virtual void d4();
    virtual void d5();
    virtual void d6();
    virtual void d7();
    virtual void d8();
    virtual void d9();
    virtual void d10();
    virtual void d11();
    virtual void d12();
    virtual void d13();
    virtual void d14();
    virtual void d15();
    virtual void d16();
    virtual void d17();
    virtual void d18();
    virtual void d19();
    virtual void d20();
    virtual void d21();
    virtual void d22();
    virtual void d23();
    virtual void d24();
    virtual void d25();
    virtual void d26();
    virtual void d27();
    virtual void d28();
    virtual void d29();
    virtual void d30();
    virtual void d31();
    virtual void d32();
    virtual void v140();
};
struct Holder { igInsightCore *p; };
extern "C" Pool * Memory_GetCurrentAllocator(...);
extern igSmartPointer<igAnimationStatePool> g_igAnimationStatePool_instance;
extern igSmartPointer<igEnbayaContextPool> g_igEnbayaContextPool_instance;
extern "C" int kIGMemoryPoolHandleUser1[4];
extern "C" int g_igViewerSceneInfoManager_metaObject[4];
struct H { static void *castit(void *s) {
    if (s != 0 && igObject_IsKindOf(s, g_igViewerSceneInfoManager_metaObject[0]) != 0) return s; else return 0; } };
extern "C" void FUN_0025afe0(Holder *arg0);

void FUN_002590c0(void) {
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
    FUN_0019d360();
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

int main(int arg0, int *arg1) {
    int a;
    G *s0;
    FUN_00259a20();
    FUN_00259cd0((const char *)(*arg1));
    DAT_00587338[0] = 2;
    GPR_0055499c = 0;
    DAT_00587340[0] = "cdrom0:\\MODULES\\IOPRP280.IMG;1";
    GPR_005549b8 = 1;
    g_startupFlagB = 0;
    DAT_00586fd8[0] = 0x40000;
    DAT_00586fe0[0] = 0x4000;
    DAT_00586fe8[0] = 0xA0000;
    DAT_00586ff0[0] = 0x69000;
    igObjectSystem_Acquire(0xC80);
    Guard guard;
    FUN_00259d10();
    FUN_002590c0();
    App sp70;
    FUN_00234d70(&sp70, arg0, arg1);
    a = U::alloc(((int)Memory_GetCurrentAllocator()));
    FUN_00165d20(a);
    U::relg((Obj **)&g_igEnbayaContextPool_instance.p);
    g_igEnbayaContextPool_instance.p = 0;
    a = U::alloc(((int)Memory_GetCurrentAllocator()));
    U::relg((Obj **)&g_igEnbayaContextPool_instance.p);
    g_igEnbayaContextPool_instance.p = igEnbayaContextPool_Create(a);
    a = U::alloc(((int)Memory_GetCurrentAllocator()));
    U::relg((Obj **)&g_igAnimationCombinerBoneInfoPool_instance.p);
    g_igAnimationCombinerBoneInfoPool_instance.p = igAnimationCombinerBoneInfoPool_Create(a);
    g_igAnimationCombinerBoneInfoPool_instance->_resetMode = 0;
    a = U::alloc(((int)Memory_GetCurrentAllocator()));
    U::relg((Obj **)&g_igAnimationStatePool_instance.p);
    g_igAnimationStatePool_instance.p = igAnimationStatePool_Create(a);
    Blk sp30;
    FUN_00259f90((struct A *)&sp30, (struct R_259f90 *)sp70.f236, (struct R_259f90 *)sp70.f232);
    if (g_sharedViewerOptions[0] == 0) {
        G *v = __nw__FUi(240);
        if (v != 0) v = ViewerOptions_Construct(v);
        g_sharedViewerOptions[0] = v;
    }
    g_sharedViewerOptions[0]->f232 = g_sharedViewerOptions[0]->f232 + 1;
    if (g_sharedViewerOptions[0]->f216 != 0) FUN_0025a8c0((App_25a8c0 *)&sp30);
    else FUN_0025a580((A0 *)&sp30);
    if (g_sharedViewerOptions[0] != 0) {
        int t = g_sharedViewerOptions[0]->f232 - 1;
        g_sharedViewerOptions[0]->f232 = t;
        if (t <= 0) {
            s0 = g_sharedViewerOptions[0];
            if (s0 != 0) {
                U::relstr(&s0->f236);
                U::relstr((int *)s0);
                __dl__FPv(s0);
            }
            g_sharedViewerOptions[0] = 0;
        }
    }
    return 0;
}

const char *FUN_00259a10(void) {
    return "[CORE]\nintrinsicModulePath = MODULES\nsonyModulePath = MODULES\nuserFileIO = false\nscratchPoolSize = 0x4000\nmoveVTablesToScratchPad = 1\n[DISPLAY]\nsupportMultitap = PORT0\n[BECRUNTIME]\nAdxModulePath = /MODULES\n[MEMORYPOOLS]\nDefault     = POOL_DEFAULT\nDriverData  = POOL_DRIVERDATA\nRenderList  = POOL_RENDERLIST\nDMA         = POOL_DMA\nHandles     = POOL_HANDLES\n\nTemporary   = POOL_TEMPORARY\nLevel       = POOL_LEVEL\nAttribute   = POOL_ATTRIBUTE\nTexture     = POOL_TEXTURE\nImage       = POOL_IMAGE\nUser0       = POOL_USER0\nUser1       = POOL_USER1\n\nList        = POOL_LIST\nVertex      = POOL_VERTEX\nApplication = POOL_APPLICATION\nWorld       = POOL_WORLD\nActor       = POOL_ACTOR\nFrame       = POOL_FRAME\nPhysics     = POOL_PHYSICS\nAI          = POOL_AI\nClut        = POOL_CLUT\nAudio       = POOL_AUDIO\nVideo       = POOL_VIDEO\nImageObject = POOL_IMAGEOBJECT\nNode        = POOL_NODE\n\n[POOL_DEFAULT]\nSize = 5951424\n[POOL_DRIVERDATA]\nSize = 32768\n[POOL_RENDERLIST]\nSize = 4718592\n[POOL_DMA]\nSize = 1585152\n[POOL_HANDLES]\nSize = 262144\n[POOL_TEMPORARY]\nAliasedTo = Default\n[POOL_LEVEL]\nAliasedTo = Default\n[POOL_ATTRIBUTE]\nAliasedTo = Default\n[POOL_TEXTURE]\nAliasedTo = User1\n[POOL_IMAGE]\nAliasedTo = User1\n[POOL_USER0]\nAliasedTo = Default\n[POOL_USER1]\nSize = 10485760\n[POOL_LIST]\nAliasedTo = Default\n[POOL_VERTEX]\nAliasedTo = Default\n[POOL_APPLICATION]\nAliasedTo = Default\n[POOL_WORLD]\nAliasedTo = Default\n[POOL_ACTOR]\nAliasedTo = Default\n[POOL_FRAME]\nAliasedTo = Default\n[POOL_PHYSICS]\nAliasedTo = Default\n[POOL_AI]\nAliasedTo = Default\n[POOL_CLUT]\nAliasedTo = Default\n[POOL_AUDIO]\nAliasedTo = Default\n[POOL_VIDEO]\nAliasedTo = Default\n[POOL_IMAGEOBJECT]\nAliasedTo = Default\n[POOL_NODE]\nAliasedTo = Default\n";
}

void FUN_00259a20(void) {
    const char *temp_v0;

    temp_v0 = FUN_00259a10();
    if (temp_v0 != 0) {
        igObjectSystem_SetIniText(temp_v0);
    }
}

void FUN_00259a60(void) {
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

void FUN_00259b60(void) {
    DW4SR4 sp2C;
    DW4SR4 sp28;
    DW4SR4 sp24;
    DW4SR4 sp20;
    void **temp_v0;

    temp_v0 = (void **)(igThread_Create(0));
    sp2C = ((DW4VCSR_156_1 *)(temp_v0))->vX((int)(0x2000));
    sp28 = ((DW4VCSR_132_1 *)(temp_v0))->vX(&FUN_00259a60);
    sp24 = ((DW4VCSR_200_1 *)(temp_v0))->vX((int)(0xFF));
    sp20 = ((DW4VCSR_120_0 *)(temp_v0))->vX();
}

R igPsx2Thread_SetStackSize(C *arg1, int arg2) {
    if (arg1->v30() == 0) {
        if (arg2 & 0xF) {
            return R(g_resultFailure[0]);
        }
        arg1->f36 = arg2;
        if (arg1->f45 == 0) {
            int a1 = arg1->f32;
            if (a1 != 0) {
                igObject_FreeMemory(arg1, a1);
            }
        }
        arg1->f45 = 0;
        arg1->f32 = igObject_MallocAligned(arg1, arg1->f36, arg1->v40() & 0xFFFF);
        return R(g_resultSuccess[0]);
    }
    return R(g_resultFailure[0]);
}

bool FUN_00259cd0(const char *path) {
    return g_atfilePrefixSet = igPsx2_SetAtfilePrefix(path) == (*(igResult *)g_resultSuccess);
}

void FUN_00259d10(void) {
    if ((*(unsigned char *)&g_atfilePrefixSet) != 0) {
        FUN_00259b60();
    }
}

void FUN_00259d40(NamedLists *arg0, int arg1) {
    int sp2C;
    VC *temp_a1;

    if ((*(unsigned char *)&g_atfilePrefixSet) != 0) {
        if (arg1 != 0) {
            temp_a1 = (VC *)(**(int **)((char *)(*(int *)((char *)(g_threadManager[0]) + 8)) + 16));
            temp_a1->vX(0xF4240);
        }
        if ((*(unsigned char *)&g_atstreamTextReady) != 0) {
            FUN_00259dc0(arg0, (int)g_atstreamText, g_atstreamFullReload);
            g_atstreamFullReload = 0;
            (*(unsigned char *)&g_atstreamTextReady) = 0;
        }
    }
}

static inline void releaseRef(CountedHeader *t) {
    if (t != 0) {
        t->refs = t->refs - 1;
        if (((unsigned long long)(long long)t->refs & 0x7fffffULL) == 0) {
            igObject_Destroy(t);
        }
    }
}

static inline void resetName(NamedLists *o, AdoptReference) { releaseRef((CountedHeader *)o->_name); o->_name = igStringRefList_Create(0); }

static inline void resetList(NamedLists *o, AdoptReference) { releaseRef((CountedHeader *)o->_names); o->_names = igIntList_Create(0); }

void FUN_00259dc0(NamedLists *arg0, int arg1, int arg2) {
    int var_v0;
    int obj;
    int n;
    NameList *l;
    int *hd;
    int cnt;
    int dv;
    resetName(arg0, AdoptReference());
    if (arg1 == 0) {
        var_v0 = 0;
    } else {
        if (g_stringPool[0] == 0) {
            obj = StringPool_Allocate(0x10);
            if (obj != 0) {
                obj = StringPool_Construct(obj);
            }
            g_stringPool[0] = obj;
        }
        var_v0 = StringPool_Intern(g_stringPool[0], arg1);
    }
    {
        StringRef name(var_v0);
        FUN_001ca620(arg0->_name, &name);
    }
    resetList(arg0, AdoptReference());
    l = arg0->_names;
    n = l->_count;
    if (n < l->_capacity) {
        l->_count = l->count() + 1;
    } else {
        List_Resize(l, n + 1, 4);
    }
    dv = g_defaultNameValue;
    l->_data[n] = dv;
    FUN_0025a550(arg0, dv);
    if (arg2 != 0) {
        FUN_00463c70(arg0);
    }
}

void FUN_00259f80(int *arg0) {
    /* matching construct: hand search — the branch folds away, leaving the load and its delay slot */
    if (arg0[10]) return;
}

void FUN_00259f90(struct A *arg0, struct R_259f90 *arg1, struct R_259f90 *arg2) {
    struct R_259f90 *t;
    struct R_259f90 *u;
    if (arg1 != 0) {
        arg1->rc = arg1->rc + 1;
    }
    t = arg0->f40;
    if (t != 0) {
        t->rc = t->rc - 1;
        if ((t->rc & 0x7FFFFF) == 0) {
            igObject_Destroy(t);
        }
    }
    arg0->f40 = arg1;
    if (arg2 != 0) {
        arg2->rc = arg2->rc + 1;
    }
    u = arg0->f36;
    if (u != 0) {
        u->rc = u->rc - 1;
        if ((u->rc & 0x7FFFFF) == 0) {
            igObject_Destroy(u);
        }
    }
    arg0->f36 = arg2;
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
    : viewer(Viewer_CreateDisplay(0)), f28(0, kRetainReference), f32(0, kRetainReference), f36(0, kRetainReference),
      f40(0, kRetainReference), f44(false), f48(0, kRetainReference), folder(igFolder_Create(0), AdoptReference()),
      loadingMessage(FUN_0045a680(0), AdoptReference()) {
    setFolderName(folder, "cdrom0:");
    FUN_0025ac60((S *)this);
}

Blk::~Blk() {
}

void FUN_0025a550(NamedLists *arg0, int) {
    FUN_0025afe0((Holder *)arg0);
    FUN_00259f80((int *)arg0);
}

void FUN_0025a580(A0 *arg0) {
    Rd *s0;
    void *s2;
    int sp40[4];
    if (arg0->f24 != 0) {
        g_activeApp = arg0;
        if (((struct Fr * *)g_sharedViewerOptions)[0] == 0) {
            void **v = ((void **)__nw__FUi(0xF0));
            if (v != 0) {
                v = ((void **)ViewerOptions_Construct(v));
            }
            ((struct Fr * *)g_sharedViewerOptions)[0] = (Fr *)v;
        }
        ((struct Fr * *)g_sharedViewerOptions)[0]->f232 = ((struct Fr * *)g_sharedViewerOptions)[0]->f232 + 1;
        {
            Fr *g = ((struct Fr * *)g_sharedViewerOptions)[0];
            g->f180 = 0;
            g->f213 = 0;
            g->f5 = 0;
            g->f148 = 0x3DCCCCCD;
            g->f152 = 0x3DCCCCCD;
            g->f156 = 0x3DCCCCCD;
            g->f160 = 0x3F800000;
            g->f92 = 0;
            g->f94 = 1;
            g->f168 = 1;
        }
        if (((struct Fr * *)g_sharedViewerOptions)[0] != 0) {
            int rc = ((struct Fr * *)g_sharedViewerOptions)[0]->f232 - 1;
            ((struct Fr * *)g_sharedViewerOptions)[0]->f232 = rc;
            if (rc <= 0) {
                Fr *f = ((struct Fr * *)g_sharedViewerOptions)[0];
                if (f != 0) {
                    if (&f->f236) {
                        void *p = f->f236;
                        if (p != 0) {
                            int *h = (int *)((char *)p - 8);
                            int r = *(int *)((char *)p - 4) - 1;
                            *(int *)((char *)p - 4) = r;
                            if (r == 0) {
                                StringChunk_ReleaseHeader(*h, h);
                            }
                        }
                    }
                    if (f != 0) {
                        void *p = f->f0;
                        if (p != 0) {
                            int *h = (int *)((char *)p - 8);
                            int r = *(int *)((char *)p - 4) - 1;
                            *(int *)((char *)p - 4) = r;
                            if (r == 0) {
                                StringChunk_ReleaseHeader(*h, h);
                            }
                        }
                    }
                    __dl__FPv(f);
                }
                ((struct Fr * *)g_sharedViewerOptions)[0] = 0;
            }
        }
        FUN_00239390();
        FUN_00238d40();
        FUN_003343a0();
        FUN_0033bf50();
        LuaAPI_RegisterClasses();
        FUN_003b04e0();
        FUN_00463b30(arg0);
        FUN_00259f80((int *)arg0);
        FUN_00463c70(arg0);
        s0 = (Rd *)igInsightCore_FindManager(arg0->f0, g_beSystem_metaObject[0]);
        if (g_stringPool[0] == 0) {
            int v = StringPool_Allocate(0x10);
            if (v != 0) {
                v = StringPool_Construct(v);
            }
            g_stringPool[0] = v;
        }
        {
            void *old;
            s2 = ((void *)StringPool_Intern(g_stringPool[0], "ndmw.igb"));
            old = s0->f60;
            if (old != 0) {
                int *h = (int *)((char *)old - 8);
                int r = *(int *)((char *)old - 4) - 1;
                *(int *)((char *)old - 4) = r;
                if (r == 0) {
                    StringChunk_ReleaseHeader(*h, h);
                }
            }
            s0->f60 = s2;
        }
        {
            D *dd = arg0->f24->vA();
            sp40[0] = 0;
            sp40[3] = 0x3F800000;
            sp40[1] = 0;
            sp40[2] = 0;
            dd->vB(sp40);
        }
        while (arg0->f44 == 0 && s0->f16 == 0) {
            while (arg0->f44 == 0 && s0->f64 != 0) {
                X *x = arg0->f0;
                int a1 = ((x->f64 >= 0xFE502B)) & 0xFF;
                if (x->f52 % 15 != 0) {
                    a1 = 0;
                }
                FUN_00259d40((NamedLists *)arg0, a1);
                if (FUN_00463bc0(arg0) == 0) break;
                FUN_00463bb0(arg0);
            }
            if (s0->f60 == 0) break;
            FUN_0025afe0((Holder *)arg0);
            s0->f64 = 1;
        }
        FUN_0025afe0((Holder *)arg0);
        FUN_00463b70(arg0);
        g_activeApp = 0;
    }
}

static inline Tm *createTimer(TimerType) { return igTimer_Create(0); }

void FUN_0025a8c0(App_25a8c0 *arg0) {
    Ev e0;
    Ev e1;
    Ev e2;
    Ev e3;
    int s2;
    float temp_f12;
    void *p;
    int rc;
    int i;
    int s1;
    int *h;
    igViewerParameters *obj;
    int r;
    Frame *f;
    int s4;
    if (arg0->f24 != 0) {
        FUN_00239390();
        thunk_FUN_00238ed0();
        FUN_00463b30(arg0);
        FUN_00259f80((int *)arg0);
        FUN_00463c70(arg0);
        obj = (igViewerParameters *)arg0->f4->_parameters;
        obj->_showGui = 0;
        e0.a = 2; e0.b = 0; e0.c = DAT_0058cab8[0];
        igModel_NotifyViews(obj, &e0);
        obj->_showBoundingBox = 0;
        e1.a = 2; e1.b = 0; e1.c = DAT_0058cac0[0];
        igModel_NotifyViews(obj, &e1);
        obj->_showNormals = 0;
        e2.a = 2; e2.b = 0; e2.c = DAT_0058cac8[0];
        igModel_NotifyViews(obj, &e2);
        if (((Frame * *)g_sharedViewerOptions)[0] == 0) {
            Frame *v = ((Frame *)__nw__FUi(240));
            if (v != 0) v = ((Frame *)ViewerOptions_Construct(v));
            ((Frame * *)g_sharedViewerOptions)[0] = v;
        }
        ((Frame * *)g_sharedViewerOptions)[0]->f232 = ((Frame * *)g_sharedViewerOptions)[0]->f232 + 1;
        s2 = *(int *)((char *)((Frame * *)g_sharedViewerOptions)[0] + 220);
        if (s2 < 0) s2 = 0;
        s1 = *(int *)((char *)((Frame * *)g_sharedViewerOptions)[0] + 224);
        if (s1 < 0) s1 = 0;
        if (((Frame * *)g_sharedViewerOptions)[0] != 0) {
            if (--((Frame * *)g_sharedViewerOptions)[0]->f232 <= 0) {
                f = ((Frame * *)g_sharedViewerOptions)[0];
                if (f != 0) {
                    if (&f->f236) {
                        p = f->f236;
                        if (p != 0) {
                            h = (int *)((char *)(p) - 8);
                            rc = *(int *)((char *)(p) - 4) - 1;
                            *(int *)((char *)(p) - 4) = rc;
                            if (rc == 0) StringChunk_ReleaseHeader(*h, h);
                        }
                    }
                    if (f != 0) {
                        p = f->f0;
                        if (p != 0) {
                            h = (int *)((char *)(p) - 8);
                            rc = *(int *)((char *)(p) - 4) - 1;
                            *(int *)((char *)(p) - 4) = rc;
                            if (rc == 0) StringChunk_ReleaseHeader(*h, h);
                        }
                    }
                    __dl__FPv(f);
                }
                ((Frame * *)g_sharedViewerOptions)[0] = 0;
            }
        }
        FUN_00463bc0(arg0);
        s4 = 0;
        if (0 < s2) {
            do {
                FUN_00463bb0(arg0);
                s4++;
            } while (s4 < s2);
        }
        FUN_00463bc0(arg0);
        Ref sp(createTimer(TimerType()));
        sp.p->vC();
        i = 0;
        if (0 < s1 - 1) {
            do {
                FUN_00463bb0(arg0);
                i++;
            } while (i < s1 - 1);
        }
        obj->_flushFrames = 1;
        e3.a = 2; e3.b = 0; e3.c = DAT_0058cad0[0];
        igModel_NotifyViews(obj, &e3);
        FUN_00463bb0(arg0);
        sp.p->vB();
        temp_f12 = (1e9f * (float)s1) / __floatdisf(sp.p->vA());
        if (g_frameRateReportIgnored == 0) {
            r = igReport_Info("average frame rate over %d frames : %f fps", s1, fptodp(temp_f12));
            if (r != 1 && r == 2) g_frameRateReportIgnored = 1;
        }
        FUN_00463b70(arg0);
    }
}

void FUN_0025ac60(S *arg0) {
    char buf[256];
    R_25ac60 *l2;
    int s2;
    int s3;
    int *np;
    R_25ac60 *la;
    R_25ac60 *lb;
    R_25ac60 *l3;
    int cnt;
    int *slot;
    int s1;
    R_25ac60 *o;

    Assign::Take(arg0->f48, arg0->f52->v24());
    la = arg0->f48;
    if (la != 0) {
        s3 = la->f8 - 1;
        s1 = s3 * 4;
        if (s3 >= 0) {
            do {
                {
                StringRef s348 = StringList_CopyRetained(arg0->f48, s3);
                strcpy(buf, s348.p);
                buf[strlen(buf) - 2] = 0;
                if (g_stringPool[0] == 0) {
                    int v = StringPool_Allocate(0x10);
                    if (v != 0) v = StringPool_Construct(v);
                    g_stringPool[0] = v;
                }
                np = (int *)StringPool_Intern(g_stringPool[0], buf);
                StringRef::Release(s348.p);
                s348.p = np;
                lb = arg0->f48;
                cnt = lb->f8;
                if (cnt != 0 && s3 >= 0 && s3 < cnt) {
                    slot = (int *)((char *)lb->f16 + s1);
                    if (s348.p != 0) s348.p[-1] = s348.p[-1] + 1;
                    StringRef::Release((int *)*slot);
                    *slot = (int)s348.p;
                }
                }
                s3 -= 1;
                s1 -= 4;
            } while (s3 >= 0);
        }
        l2 = arg0->f48;
        if (l2 != 0) {
            s2 = l2->f8 - 1;
            if (s2 >= 0) {
                do {
                    {
                    StringRef s344 = StringList_CopyRetained(arg0->f48, s2);
                    if (igStringObj_HasFileExtensionText(s344.p, "igb") == 0) {
                        l3 = arg0->f48;
                        StringRef::Release(StringList_CopyRetained(l3, s2).p);
                        List_RemoveWordAt(l3, s2);
                        l3->f16[l3->f8] = 0;
                    }
                    }
                    s2 -= 1;
                } while (s2 >= 0);
            }
        }
    }
}

void igFolder_ListEntries(void **arg0) {
    void *temp_a0;

    *arg0 = 0;
    temp_a0 = (void *)(*arg0);
    if (temp_a0 != 0) {
        *(int *)((char *)(temp_a0) + 4) = (int)((int) (*(int *)((char *)(temp_a0) + 4) + 1));
    }
}

void FUN_0025afe0(Holder *arg0) {
    Pool *var_a0;
    Pool *var_v0;
    void *var_s0;
    FUN_00463c80();
    var_s0 = H::castit(igInsightCore_FindManager(arg0->p, g_igViewerSceneInfoManager_metaObject[0]));
    ((Ctl *)((igViewerRenderer *)((igViewerSceneInfoManager *)var_s0)->_viewerRenderer)->_sceneTraversal)->v124();
    ((Sub *)arg0->p->_visualContext)->v140();
    REL_25afe0(g_igEnbayaContextPool_instance.p);
    g_igEnbayaContextPool_instance.p = 0;
    { Pool *a_ = Memory_GetCurrentAllocator(); var_v0 = g_useOwnerAllocator != 0 ? a_ : Memory_GetAllocatorBySelector(kIGMemoryPoolHandleUser0[0]); }
    REL_25afe0(g_igEnbayaContextPool_instance.p);
    g_igEnbayaContextPool_instance.p = igEnbayaContextPool_Create(var_v0);
    { Pool *a_ = Memory_GetCurrentAllocator(); var_v0 = g_useOwnerAllocator != 0 ? a_ : Memory_GetAllocatorBySelector(kIGMemoryPoolHandleUser0[0]); }
    REL_25afe0(g_igAnimationCombinerBoneInfoPool_instance.p);
    g_igAnimationCombinerBoneInfoPool_instance.p = igAnimationCombinerBoneInfoPool_Create(var_v0);
    g_igAnimationCombinerBoneInfoPool_instance->_resetMode = 0;
    { Pool *a_ = Memory_GetCurrentAllocator(); var_v0 = g_useOwnerAllocator != 0 ? a_ : Memory_GetAllocatorBySelector(kIGMemoryPoolHandleUser0[0]); }
    REL_25afe0(g_igAnimationStatePool_instance.p);
    g_igAnimationStatePool_instance.p = igAnimationStatePool_Create(var_v0);
    { Pool *a_ = Memory_GetCurrentAllocator(); var_a0 = g_useOwnerAllocator != 0 ? a_ : Memory_GetAllocatorBySelector(kIGMemoryPoolHandleUser1[0]); }
    if (var_a0 != 0) {
        var_a0->v108(0);
    }
}
#pragma pop
