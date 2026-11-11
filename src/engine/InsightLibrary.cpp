#include "dw4/reflected.h"
#include "dw4/igSmartPointer.h"
#include "dw4/igobject_release.h"
#include "dw4/fun_00235370_refs.h"
#define ReleaseObject(obj) do { igObject *held = (obj); IG_OBJECT_RELEASE(held); } while (0)
#define OPTION_BOOL(name, help, value)  if (name) FUN_002342b0(name, help, value)
#define OPTION_INT(name, help, value)   if (name) FUN_002342e0(name, help, value)
#define OPTION_FLOAT(name, help, value) if (name) FUN_00234300(name, help, value)

extern "C" unsigned char g_InsightLibrary_registered;
extern "C" void InsightLibrary_MarkRegistered(void);
extern "C" int thunk_FUN_002ed460__002ff810(...);
extern "C" int DAT_0052d060[4];
struct S {
    void *f0;
    char pad[4];
    void *f8;
};
extern "C" void *FUN_00230f70(struct S *arg0, short arg1);
extern "C" int DAT_0058c208[4];
extern "C" int FUN_00231010(void);
extern "C" int DAT_0056dad8[4];
extern "C" int FUN_00231020(void);
extern "C" int StringChunk_ReleaseHeader(...);
extern "C" int DAT_0052cf80[4];
extern "C" int DAT_00524950[4];
extern "C" void *FUN_00231030(struct S *arg0, short arg1);
extern "C" int DAT_0056dc38[4];
extern "C" int FUN_002310d0(void);
extern "C" igMetaObject *g_igSerialScheduler_metaObject[4];
extern "C" igMetaObject *igSerialScheduler_GetMetaObject(void);
struct T { int word0; int references; };
extern "C" int DAT_0052c830[4];
extern "C" char *DAT_00586dc8[4];
struct Obj {
    int *vt; char p4[4]; T *m8; T *m12; 
    inline void rel8() {
        T **self = &m8;
        if (self) {
            T *object = *self;
            if (object) {
                --object->references;
                if (((unsigned long long)(long long)object->references & 0x7fffffULL) == 0)
                    igObject_Destroy(object);
            }
        }
    }
    inline void rel12() {
        T **self = &m12;
        if (self) {
            T *object = *self;
            if (object) {
                --object->references;
                if (((unsigned long long)(long long)object->references & 0x7fffffULL) == 0)
                    igObject_Destroy(object);
            }
        }
    }
};
extern "C" int igObject_InitHeader(...);
extern "C" int igSerialScheduler_GetVTable(void);
extern "C" int FUN_00100610(...);
extern "C" void **FUN_00231210(void **arg0, long long arg1);
extern "C" void FUN_00231290(void);
extern "C" char igInsightScheduler_GetPublishedMetaObject[];
extern "C" char g_igSerialScheduler_callbackList[];
extern "C" char igSerialScheduler_className[];
extern "C" int igMetaObject_RegisterClass(...);
extern "C" void igSerialScheduler_Register(void);
extern "C" void thunk_igSerialScheduler_GetMetaObject(void);
extern "C" int DAT_0056db48[4];
extern "C" int FUN_00231330(void);
extern "C" int igMetaObject_CreateFields(...);
extern "C" void *igMetaObject_GetFieldAt(...);
extern "C" int igMetaObject_GetFieldCount(...);
extern "C" int igMetaObject_NameFields(...);
extern "C" int DAT_00497f90[4];
extern "C" int DAT_00497f98[4];
extern "C" int DAT_00497fa0[4];
extern "C" int DAT_00497fa8[4];
extern "C" int DAT_0056dab0[4];
extern "C" void igSerialScheduler_InitFields(void);
extern "C" int igMetaObject_Create(...);
extern "C" int Memory_GetAllocatorBySelector(...);
extern "C" int DAT_0056dac8[4];
extern "C" int DAT_00587040[4];
extern "C" int FUN_00231400(void);
extern "C" igMetaObject *g_igMessenger_metaObject[4];
extern "C" igMetaObject *igMessenger_GetMetaObject(void);
struct Ref { int pad; union { int w; struct { unsigned cnt:23; unsigned f:9; } b; } u; };
struct W { int *vt; int f4; struct Ref *ref; int fc; };
extern "C" int DAT_0052cf20[4];
extern "C" int igMessenger_GetVTable(void);
extern "C" void FUN_00231530(void);
extern "C" char igObject_GetMetaObject_ParentAccessor[];
extern "C" char igObject_Register[];
extern "C" char g_igMessenger_callbackList[];
extern "C" char igMessenger_className[];
extern "C" void igMessenger_Register(void);
extern "C" void thunk_igMessenger_GetMetaObject(void);
extern "C" int DAT_00497fb8[4];
extern "C" int DAT_00497fc0[4];
extern "C" int DAT_00497fc8[4];
extern "C" int DAT_00497fd0[4];
extern "C" void igMessenger_InitFields(void);
extern "C" igMetaObject *g_igMessage_metaObject[4];
extern "C" igMetaObject *igMessage_GetMetaObject(void);
extern "C" int DAT_0052d000[4];
struct Obj_2316c0 { int *vt; int b; };
extern "C" int igMessage_GetVTable(void);
extern "C" void FUN_00231700(void);
extern "C" char igMessage_className[];
extern "C" void igMessage_Register(void);
extern "C" void thunk_igMessage_GetMetaObject(void);
extern "C" int DAT_0056dae0[4];
extern "C" int FUN_00231790(void);
extern "C" igMetaObject *g_igMessageReceiverList_metaObject[4];
extern "C" igMetaObject *igMessageReceiverList_GetMetaObject(void);
struct Obj_231830 { int *vt; char pad[28]; };
extern "C" int DAT_0052ceb0[4];
extern "C" int igMessageReceiverList_GetVTable(void);
extern "C" void FUN_00231870(void);
extern "C" char igObjectList_GetPublishedMetaObject[];
extern "C" char igObjectList_Register[];
extern "C" char g_igMessageReceiverList_callbackList[];
extern "C" char igMessageReceiverList_className[];
extern "C" void igMessageReceiverList_Register(void);
extern "C" void thunk_igMessageReceiverList_GetMetaObject(void);
extern "C" igMetaObject *g_igMessageReceiver_metaObject[4];
extern "C" igMetaObject *igMessageReceiver_GetMetaObject(void);
extern "C" void FUN_00231950(void);
extern "C" char igMessageReceiver_className[];
extern "C" void igMessageReceiver_Register(void);
extern "C" void thunk_igMessageReceiver_GetMetaObject(void);
extern "C" int DAT_0056daf0[4];
extern "C" int FUN_002319d0(void);
extern "C" igMetaObject *g_igMessageFilterList_metaObject[4];
extern "C" igMetaObject *igMessageFilterList_GetMetaObject(void);
struct Obj_231a70 { int *vt; char pad[28]; };
extern "C" int DAT_0052ce40[4];
extern "C" int igMessageFilterList_GetVTable(void);
extern "C" void FUN_00231ab0(void);
extern "C" char g_igMessageFilterList_callbackList[];
extern "C" char igMessageFilterList_className[];
extern "C" void igMessageFilterList_Register(void);
extern "C" void thunk_igMessageFilterList_GetMetaObject(void);
extern "C" int igMetaObject_CreateInstance(int, int);
extern "C" int FUN_00231b40(int arg0);
extern "C" igMetaObject *g_igMessageFilter_metaObject[4];
extern "C" igMetaObject *igMessageFilter_GetMetaObject(void);
typedef struct S_ref { char pad4[4]; int f4; } S_ref;
union U { int vt; int w[4]; void *p[4]; char b[16]; };
extern "C" int DAT_0052cde0[4];
extern "C" int igMessageFilter_GetVTable(void);
extern "C" void FUN_00231cb0(void);
extern "C" char g_igMessageFilter_callbackList[];
extern "C" char igMessageFilter_className[];
extern "C" void igMessageFilter_Register(void);
extern "C" void thunk_igMessageFilter_GetMetaObject(void);
extern "C" int FUN_002be610(...);
extern "C" int DAT_00497ff8[4];
extern "C" int DAT_00498000[4];
extern "C" int DAT_00498008[4];
extern "C" int DAT_00498010[4];
extern "C" int DAT_0056daf8[4];
extern "C" void igMessageFilter_InitFields(void);
extern "C" igMetaObject *g_igFilterMessageDispatcher_metaObject[4];
extern "C" igMetaObject *igFilterMessageDispatcher_GetMetaObject(void);
extern "C" int DAT_0052c8b0[4];
extern "C" int igFilterMessageDispatcher_GetVTable(void);
extern "C" void FUN_00231f40(void);
extern "C" char igMessageDispatcher_GetPublishedMetaObject[];
extern "C" char g_igFilterMessageDispatcher_callbackList[];
extern "C" char igFilterMessageDispatcher_className[];
extern "C" void igFilterMessageDispatcher_Register(void);
extern "C" void thunk_igFilterMessageDispatcher_GetMetaObject(void);
extern "C" int DAT_0056db28[4];
extern "C" int FUN_00231fe0(void);
extern "C" int DAT_00498020[4];
extern "C" int DAT_00498028[4];
extern "C" int DAT_00498030[4];
extern "C" int DAT_00498038[4];
extern "C" int DAT_0056db10[4];
extern "C" void igFilterMessageDispatcher_InitFields(void);
extern "C" int FUN_002320b0(void);
extern "C" igMetaObject *g_igMessageDispatcher_metaObject[4];
extern "C" igMetaObject *igMessageDispatcher_GetMetaObject(void);
extern "C" void FUN_00232150(void);
extern "C" char igMessageDispatcher_className[];
extern "C" int igMessageDispatcher_SetAbstractProxy_002321e0[4];
extern "C" void igMessageDispatcher_Register(void);
extern "C" void thunk_igMessageDispatcher_GetMetaObject(void);
extern "C" void FUN_002321e0(void);
extern "C" void FUN_00232200(int arg0);
extern "C" igMetaObject *g_igMessageDefaultReceiver_metaObject[4];
extern "C" igMetaObject *igMessageDefaultReceiver_GetMetaObject(void);
extern "C" int DAT_0052c930[4];
union U_232290 { int vt; char b[32]; };
extern "C" int igMessageDefaultReceiver_GetVTable(void);
extern "C" void FUN_00232320(void);
extern "C" char igMessageReceiver_GetPublishedMetaObject[];
extern "C" char g_igMessageDefaultReceiver_callbackList[];
extern "C" char igMessageDefaultReceiver_className[];
extern "C" void igMessageDefaultReceiver_Register(void);
extern "C" void thunk_igMessageDefaultReceiver_GetMetaObject(void);
extern "C" int DAT_0056dae8[4];
extern "C" int FUN_002323c0(void);
extern "C" int DAT_00498048[4];
extern "C" int DAT_00498050[4];
extern "C" int DAT_00498058[4];
extern "C" int DAT_00498060[4];
extern "C" int DAT_0056db30[4];
extern "C" int DAT_00587198[4];
extern "C" void igMessageDefaultReceiver_InitFields(void);
extern "C" int FUN_00232470(void);
extern "C" igMetaObject *g_igInsightScheduler_metaObject[4];
extern "C" igMetaObject *igInsightScheduler_GetMetaObject(void);
extern "C" void FUN_00232510(void);
extern "C" char igInsightScheduler_className[];
extern "C" int igInsightScheduler_SetAbstractProxy_002325a0[4];
extern "C" void igInsightScheduler_Register(void);
extern "C" void thunk_igInsightScheduler_GetMetaObject(void);
extern "C" void FUN_002325a0(void);
extern "C" int DAT_0056db50[4];
extern "C" int FUN_002325c0(void);
extern "C" igMetaObject *g_igInsightPluginList_metaObject[4];
extern "C" igMetaObject *igInsightPluginList_GetMetaObject(void);
struct Obj_232660 { int *vt; char pad[28]; };
extern "C" int DAT_0052cd70[4];
extern "C" int igInsightPluginList_GetVTable(void);
extern "C" void FUN_002326a0(void);
extern "C" char g_igInsightPluginList_callbackList[];
extern "C" char igInsightPluginList_className[];
extern "C" void igInsightPluginList_Register(void);
extern "C" void thunk_igInsightPluginList_GetMetaObject(void);
extern "C" igMetaObject *g_igInsightPlugin_metaObject[4];
extern "C" igMetaObject *igInsightPlugin_GetMetaObject(void);
extern "C" void FUN_00232780(void);
extern "C" char igInsightPlugin_className[];
extern "C" void igInsightPlugin_Register(void);
extern "C" void thunk_igInsightPlugin_GetMetaObject(void);
extern "C" void FUN_00232800(int arg0);
extern "C" int DAT_0056db60[4];
extern "C" int FUN_00232840(void);
extern "C" igMetaObject *g_igInsightCore_metaObject[4];
extern "C" igMetaObject *igInsightCore_GetMetaObject(void);
struct Obj_2328e0 { int *vt; int w1; int w2; int w3; int w4; int w5; int w6; int w7; int w8; int w9; int w10; int w11; int w12; int w13; int w14; int w15; int w16; int w17; int w18; int w19; int w20; int w21; int w22; int w23; int w24; int w25; int w26; int w27; };
extern "C" int FUN_00130140(...);
extern "C" int FUN_00143350(...);
extern "C" int FUN_00150a70(...);
extern "C" int FUN_001d35d0(...);
extern "C" int DAT_0052c990[4];
extern "C" int igInsightCore_GetVTable(void);
struct S_temp_a0 { char pad4[4]; int f4; };
struct O { S_temp_a0 *m; };
extern "C" O *FUN_00232a60(O *arg0, short arg1);
/* Deleting destructor; the deletion flag is a signed short. */
typedef struct ObjectRefTarget { int word0; int references; } ObjectRefTarget;
typedef struct ObjectRefWord { ObjectRefTarget *value; } ObjectRefWord;
extern "C" ObjectRefWord *FUN_00232ae0(ObjectRefWord *self,int delete_storage);
typedef struct S_temp_a0_232b60 { char pad4[4]; int f4; } S_temp_a0_232b60;
extern "C" void **FUN_00232b60(void **arg0, short arg1);
extern "C" ObjectRefWord *FUN_00232be0(ObjectRefWord *self,int delete_storage);
extern "C" void **FUN_00232c60(void **arg0, short arg1);
extern "C" ObjectRefWord *FUN_00232ce0(ObjectRefWord *self,int delete_storage);
struct R { int vt; unsigned int rc; };
extern "C" struct R **FUN_00232d60(struct R **arg0, short arg1);
extern "C" void FUN_00232de0(void);
extern "C" char g_igInsightCore_callbackList[];
extern "C" char igInsightCore_className[];
extern "C" void igInsightCore_Register(void);
extern "C" void thunk_igInsightCore_GetMetaObject(void);
extern "C" int FUN_00145d40(...);
extern "C" int FUN_0014a040(...);
extern "C" int FUN_002b7a10(...);
extern "C" int FUN_002c3440(...);
extern "C" int FUN_0044c250(...);
extern "C" int FUN_0044c4d0(...);
extern "C" int FUN_004513b0(...);
extern "C" int DAT_004980b0[4];
extern "C" int DAT_00498100[4];
extern "C" int DAT_00498150[4];
extern "C" int DAT_004981a0[4];
extern "C" void igInsightCore_InitFields(void);
extern "C" void thunk_FUN_00236140(void);
extern "C" int DAT_0056dc00[4];
extern "C" int FUN_00233080(void);
extern "C" igMetaObject *g_igWindowResizeEventReceiver_metaObject[4];
extern "C" igMetaObject *igWindowResizeEventReceiver_GetMetaObject(void);
extern "C" int DAT_0052c9f0[4];
struct Obj_233120 { int *vt; char pad[12]; };
extern "C" int igWindowResizeEventReceiver_GetVTable(void);
extern "C" void FUN_00233160(void);
extern "C" char igEventReceiver_GetPublishedMetaObject[];
extern "C" char igEventReceiver_Register[];
extern "C" char g_igWindowResizeEventReceiver_callbackList[];
extern "C" char igWindowResizeEventReceiver_className[];
extern "C" void igWindowResizeEventReceiver_Register(void);
extern "C" void thunk_igWindowResizeEventReceiver_GetMetaObject(void);
extern "C" int DAT_0058c570[4];
extern "C" int FUN_00233200(void);
extern "C" int DAT_004981f8[4];
extern "C" int DAT_00498200[4];
extern "C" int DAT_00498208[4];
extern "C" int DAT_00498210[4];
extern "C" void igWindowResizeEventReceiver_InitFields(void);
extern "C" int FUN_002332b0(int arg0);
extern "C" igMetaObject *g_igViewportResizedMessage_metaObject[4];
extern "C" igMetaObject *igViewportResizedMessage_GetMetaObject(void);
struct Obj_233340 { int *vt; char pad[28]; };
extern "C" int DAT_0052cc80[4];
extern "C" int igViewportResizedMessage_GetVTable(void);
extern "C" void FUN_00233380(void);
extern "C" char igMessage_GetPublishedMetaObject[];
extern "C" char igViewportResizedMessage_className[];
extern "C" void igViewportResizedMessage_Register(void);
extern "C" void thunk_igViewportResizedMessage_GetMetaObject(void);
extern "C" int DAT_00498218[4];
extern "C" int DAT_00498220[4];
extern "C" int DAT_00498228[4];
extern "C" int DAT_00498230[4];
extern "C" int DAT_0056dc10[4];
extern "C" void igViewportResizedMessage_InitFields(void);
extern "C" int DAT_0056dc28[4];
extern "C" int FUN_00233480(void);
extern "C" igMetaObject *g_igInfoManagerOrderedList_metaObject[4];
extern "C" igMetaObject *igInfoManagerOrderedList_GetMetaObject(void);
typedef struct { int *vt; int w[5]; } Obj_233520;
extern "C" int DAT_0052cb60[4];
extern "C" int igInfoManagerOrderedList_GetVTable(void);
extern "C" ObjectRefWord *FUN_00233590(ObjectRefWord *self,int delete_storage);
extern "C" int FUN_00135430(...);
extern "C" int FUN_0014aa70(...);
extern "C" int ObjectRef_Destruct_001c6460(...);
extern "C" int DAT_0052cbc0[4];
extern "C" int DAT_0052cc20[4];
extern "C" int **FUN_00233610(int **arg0, long long arg1);
extern "C" void FUN_002336b0(void);
extern "C" char igDependencyOrderedList_GetPublishedMetaObject[];
extern "C" char igDependencyOrderedList_Register[];
extern "C" char g_igInfoManagerOrderedList_callbackList[];
extern "C" char igInfoManagerOrderedList_className[];
extern "C" void igInfoManagerOrderedList_Register(void);
extern "C" void thunk_igInfoManagerOrderedList_GetMetaObject(void);
extern "C" int DAT_00586738[4];
extern "C" int FUN_00233740(void);
extern "C" int DAT_0056dc30[4];
extern "C" int FUN_00233750(void);
extern "C" igMetaObject *g_igInfoManagerList_metaObject[4];
extern "C" igMetaObject *igInfoManagerList_GetMetaObject(void);
struct Obj_2337f0 { int *vt; char pad[28]; };
extern "C" int DAT_0052caf0[4];
extern "C" int igInfoManagerList_GetVTable(void);
extern "C" void FUN_00233830(void);
extern "C" char g_igInfoManagerList_callbackList[];
extern "C" char igInfoManagerList_className[];
extern "C" void igInfoManagerList_Register(void);
extern "C" void thunk_igInfoManagerList_GetMetaObject(void);
extern "C" igMetaObject *g_igInfoManager_metaObject[4];
extern "C" igMetaObject *igInfoManager_GetMetaObject(void);
extern "C" void FUN_00233910(void);
extern "C" char igNamedObject_GetPublishedMetaObject[];
extern "C" char igNamedObject_Register[];
extern "C" char g_igInfoManager_callbackList[];
extern "C" char igInfoManager_className[];
extern "C" void igInfoManager_Register(void);
extern "C" void thunk_igInfoManager_GetMetaObject(void);
extern "C" int DAT_00498250[4];
extern "C" int DAT_00498258[4];
extern "C" int DAT_00498260[4];
extern "C" int DAT_00498268[4];
extern "C" void igInfoManager_InitFields(void);
extern "C" int DAT_0056dc48[4];
extern "C" int FUN_00233a40(void);
union U_233a90 { int vt; int w[3]; char b[12]; };
extern "C" void igMetaObject_RunStaticInit(...);
extern "C" igMetaObject *g_igFlushRenderer_metaObject[4];
extern "C" int DAT_0052ca80[4];
extern "C" char igRenderer_GetPublishedMetaObject[];
extern "C" char igRenderer_Register[];
extern "C" char igFlushRenderer_className[];
extern "C" igMetaObject *igFlushRenderer_GetMetaObject(void);
extern "C" int igFlushRenderer_GetVTable(void);
extern "C" void FUN_00233b80(void);
extern "C" void igFlushRenderer_Register(void);
extern "C" void thunk_igFlushRenderer_GetMetaObject(void);
typedef struct StringHeader {
    int owner;
    int refCount;
} StringHeader;
typedef struct IntList {
    int _unk00[2];
    int count;
    int capacity;
    int *data;
} IntList;
struct InternedStringList : public igObject { };
typedef struct ViewerOptions ViewerOptions;
struct ViewerOptions {
    char *modelName;                    /* +0x00 positional model argument (interned string) */
    unsigned char showBbox;  /* +0x04 --show-bbox */
    unsigned char showNormals;  /* +0x05 --show-normals */
    unsigned char _pad06[2];
    float normalsColor[4];  /* +0x08 --normals-color */
    float invalidStoredNormalsColor[4];  /* +0x18 --invalid-stored-normals-color */
    float scaledNormalsColor[4];  /* +0x28 --scaled-normals-color */
    float invalidNormalsPrecision;  /* +0x38 --invalid-normals-precision */
    unsigned char autoSelectCamera;  /* +0x3C --auto-select-camera */
    unsigned char _pad3D[3];
    float hfov;  /* +0x40 --hfov */
    unsigned char autoPlanes;  /* +0x44 --auto-planes */
    unsigned char _pad45[3];
    float nearPlane;  /* +0x48 --near-plane */
    float farPlane;  /* +0x4C --far-plane */
    float upVector[3];  /* +0x50 --up-vector */
    unsigned char autoSceneLights;  /* +0x5C --auto-scene-lights */
    unsigned char autoHeadLight;  /* +0x5D --auto-head-light */
    unsigned char useSceneLights;  /* +0x5E --use-scene-lights */
    unsigned char useHeadLight;  /* +0x5F --use-head-light */
    unsigned char useHeadLightSpecular;  /* +0x60 --use-head-light-specular */
    unsigned char _pad61[3];
    float headLightDiffuse[4];  /* +0x64 --head-light-diffuse */
    float headLightSpecular[4];  /* +0x74 --head-light-specular */
    float headLightAmbient[4];  /* +0x84 --head-light-ambient */
    float clearColor[4];  /* +0x94 --clear-color */
    unsigned char wireframeMode;  /* +0xA4 --wireframe-mode */
    unsigned char forceWireframe;  /* +0xA5 --force-wireframe */
    unsigned char backfaceCullingMode;  /* +0xA6 --backface-culling-mode */
    unsigned char forceBackfaceCulling;  /* +0xA7 --force-backface-culling */
    unsigned char alphaTest;  /* +0xA8 --alpha-test */
    unsigned char forceAlphaTest;  /* +0xA9 --force-alpha-test */
    unsigned char _padAA[2];
    float alphaTestReference;  /* +0xAC --alpha-test-reference */
    float maximumFrameRate;  /* +0xB0 --maximum-frame-rate */
    unsigned char optimizeTextures;  /* +0xB4 --optimize-textures */
    unsigned char halfBuffer;  /* +0xB5 --half-buffer */
    unsigned char palVideoMode;  /* +0xB6 --pal-video-mode */
    unsigned char _padB7[1];
    int width;  /* +0xB8 --width */
    int height;  /* +0xBC --height */
    int swapInterval;  /* +0xC0 --swap-interval */
    int colorBits;  /* +0xC4 --color-bits */
    int alphaBits;  /* +0xC8 --alpha-bits */
    int depthBits;  /* +0xCC --depth-bits */
    int stencilBits;  /* +0xD0 --stencil-bits */
    unsigned char reportVideoFormat;  /* +0xD4 --report-video-format */
    unsigned char showLogo;  /* +0xD5 --show-logo */
    unsigned char showUi;  /* +0xD6 --show-ui */
    unsigned char enableMayaControls;  /* +0xD7 --enable-maya-controls */
    unsigned char benchmark;  /* +0xD8 --benchmark */
    unsigned char _padD9[3];
    int benchmarkSkipFrames;  /* +0xDC --benchmark-skip-frames */
    int benchmarkFrames;  /* +0xE0 --benchmark-frames */
    unsigned char columnStatistics;  /* +0xE4 --column-statistics */
    unsigned char allocateVisualContextInScratchpad;  /* +0xE5 --allocate-visual-context-in-scratchpad */
    unsigned char _padE6[2];
    struct igObject *intList;  /* +0xE8 */
    struct igObject *stringList;  /* +0xEC */
    ViewerOptions *applied;   /* +0xF0 */
};
struct FlushSettings {
    int f0;
    unsigned char b4;
    unsigned char b5;
    char pad6[2];
    int f8;
    float f12;
    float f16;
    float f20;
    float f24;
    float f28;
    float f32;
    float f36;
    float f40;
    float f44;
    float f48;
    float f52;
    float f56;
    unsigned char b60;
    char pad61[3];
    float f64;
    unsigned char b68;
    char pad69[3];
    float f72;
    float f76;
    float f80[3];
    unsigned char b92;
    unsigned char b93;
    unsigned char b94;
    unsigned char b95;
    unsigned char b96;
    char pad97[3];
    float f100[8];
    float f132[4];
    float f148;
    float f152;
    float f156;
    float f160;
    unsigned char b164;
    unsigned char b165;
    unsigned char b166;
    unsigned char b167;
    unsigned char b168;
    unsigned char b169;
    char pad170[2];
    float f172;
    int f176;
    unsigned char b180;
    unsigned char b181;
    unsigned char b182;
    char pad183[1];
    int width;
    int height;
    int f192;
    int f196;
    int f200;
    int f204;
    int f208;
    unsigned char b212;
    unsigned char b213;
    unsigned char b214;
    unsigned char b215;
    unsigned char b216;
    char pad217[3];
    int f220;
    int f224;
    unsigned char b228;
    unsigned char b229;
    char pad230[2];
    void *f232;
    void *f236;
    struct FlushShared *shared;
};
struct FlushShared { char *f0; char pad4[228]; int refs; void *f236; };
struct App {
    void *f0;
    char pad[228];
    igObject *f232;
    igObject *f236;
};
extern "C" void FUN_00234ee0(struct FlushSettings *settings, const char *text);
extern "C" int printf(...);
extern "C" int strcmp(...);
extern "C" int atoi(...);
extern "C" long long atof(...);
extern "C" int exit(int status);
extern "C" int fptodp(float);
extern "C" float dptofp(long long);
extern "C" struct FlushShared *FUN_001007e0(int size);
extern "C" int FUN_001e6d30(...);
extern "C" int FUN_001e6d80(...);
extern "C" void *FUN_002caa70(int allocator);
extern "C" InternedStringList *FUN_002b90e0(int allocator);
extern "C" int FUN_002eb010(...);
extern "C" int StringPool_Construct(...);
extern "C" char *StringPool_Intern(...);
extern "C" int StringList_CopyRetained(...);
extern "C" int StringList_AppendRetained(...);
extern "C" int List_Resize(IntList *list, int newCount, int elementSize);
extern "C" unsigned char GPR_00554c14;
extern "C" int DAT_00586f20[4];
extern "C" int DAT_00587028[4];
extern "C" int DAT_00587060[4];
extern "C" struct FlushShared *DAT_0056dc50[4];
extern "C" int DAT_004e95d0[4];
extern "C" int DAT_004e95f8[4];
extern "C" int DAT_004e9600[4];
extern "C" int DAT_004e9610[4];
extern "C" int DAT_004e9630[4];
extern "C" int DAT_004e9650[4];
extern "C" int DAT_004e9680[4];
extern "C" int DAT_004e96b0[4];
extern "C" int DAT_004e96c0[4];
extern "C" int DAT_004e96e0[4];
extern "C" const float g_vec3Zero[3];
extern "C" const float g_vec4Zero[4];
extern "C" char usage_s_option1_option2_n_number_f[];
extern "C" char n_number_loads_n_instances_of_the_[];
extern "C" char possible_options_are[];
extern "C" char help_prints_this_message[];
extern "C" char nologo_removes_the_logo_display[];
extern "C" char show_bounding_box_on_selected_obje[];
extern "C" char show_normals_on_selected_object[];
extern "C" char sets_the_normals_color[];
extern "C" char sets_the_non_normalized_stored_nor[];
extern "C" char sets_the_scaled_normals_color[];
extern "C" char sets_the_precision_on_the_normals_[];
extern "C" char select_the_first_camera_if_any_in_[];
extern "C" char sets_the_horizontal_field_of_view[];
extern "C" char find_automatically_near_and_far_cl[];
extern "C" char sets_the_default_near_clipping_pla[];
extern "C" char sets_the_default_far_clipping_plan[];
extern "C" char sets_the_default_up_vector_0_0_0_m[];
extern "C" char sets_automatic_usage_of_scene_ligh[];
extern "C" char sets_automatic_usage_of_head_light[];
extern "C" char use_scene_lights_if_not_automatic[];
extern "C" char enable_head_light_if_not_automatic[];
extern "C" char use_specular_head_light[];
extern "C" char sets_the_diffuse_color_for_the_hea[];
extern "C" char sets_the_specular_color_for_the_he[];
extern "C" char sets_the_ambient_color_for_the_hea[];
extern "C" char sets_the_clear_color[];
extern "C" char sets_wireframe_mode[];
extern "C" char force_wireframe_on_all_geometries[];
extern "C" char sets_back_face_culling_mode[];
extern "C" char force_back_face_culling_on_all_geo[];
extern "C" char sets_alpha_test_state[];
extern "C" char force_alpha_test_on_all_geometries[];
extern "C" char sets_alpha_test_reference_value[];
extern "C" char sets_the_maximum_frame_rate_0_mean[];
extern "C" char share_textures_at_load_time[];
extern "C" char sets_psx2_half_buffer_mode[];
extern "C" char sets_pal_video_mode[];
extern "C" char viewer_window_width[];
extern "C" char viewer_window_height[];
extern "C" char sets_the_swap_interval_0_means_no_[];
extern "C" char sets_color_buffer_bits_1_means_def[];
extern "C" char sets_alpha_buffer_bits_1_means_def[];
extern "C" char sets_depth_buffer_bits_1_means_def[];
extern "C" char sets_stencil_buffer_bits_1_means_d[];
extern "C" char if_set_reports_requested_and_actua[];
extern "C" char shows_alchemy_logo[];
extern "C" char sets_initial_gui_visibility[];
extern "C" char enables_or_disable_maya_controls[];
extern "C" char enables_or_disable_the_benchmark_m[];
extern "C" char sets_the_number_of_frames_to_skip_[];
extern "C" char sets_the_number_of_frames_to_bench[];
extern "C" char output_statistics_to_console_in_co[];
extern "C" char allocate_visual_context_from_scrat[];
extern "C" const char help[16];
extern "C" const char n[8];
extern "C" const char dashdash[8];
extern "C" const char unrecognized[32];
extern "C" const char showBbox[16];
extern "C" const char showNormals[16];
extern "C" const char normalsColor[16];
extern "C" const char invalidStoredNormalsColor[16];
extern "C" const char scaledNormalsColor[16];
extern "C" const char invalidNormalsPrecision[16];
extern "C" const char autoSelectCamera[16];
extern "C" const char hfov[16];
extern "C" const char autoPlanes[16];
extern "C" const char nearPlane[16];
extern "C" const char farPlane[16];
extern "C" const char upVector[16];
extern "C" const char autoSceneLights[16];
extern "C" const char autoHeadLight[16];
extern "C" const char useSceneLights[16];
extern "C" const char useHeadLight[16];
extern "C" const char useHeadLightSpecular[16];
extern "C" const char headLightDiffuse[16];
extern "C" const char headLightSpecular[16];
extern "C" const char headLightAmbient[16];
extern "C" const char clearColor[16];
extern "C" const char wireframeMode[16];
extern "C" const char forceWireframe[16];
extern "C" const char backfaceCullingMode[16];
extern "C" const char forceBackfaceCulling[16];
extern "C" const char alphaTest[16];
extern "C" const char forceAlphaTest[16];
extern "C" const char alphaTestReference[16];
extern "C" const char maximumFrameRate[16];
extern "C" const char optimizeTextures[16];
extern "C" const char halfBuffer[16];
extern "C" const char palVideoMode[16];
extern "C" const char width[16];
extern "C" const char height[16];
extern "C" const char swapInterval[16];
extern "C" const char colorBits[16];
extern "C" const char alphaBits[16];
extern "C" const char depthBits[16];
extern "C" const char stencilBits[16];
extern "C" const char reportVideoFormat[16];
extern "C" const char showLogo[16];
extern "C" const char showUi[16];
extern "C" const char enableMayaControls[16];
extern "C" const char benchmark[16];
extern "C" const char benchmarkSkipFrames[16];
extern "C" const char benchmarkFrames[16];
extern "C" const char columnStatistics[16];
extern "C" const char allocateVisualContextInScratchpad[16];
/* The object smart-pointer destructor: the held pointer is copied once (its slot is a plain field,
 * so it is read once), then released with the shared sequence. */


struct StringRef {
    char *p;
    StringRef() : p(0) {}
    StringRef(const StringRef &other) : p(other.p) {
        if (p != 0) {
            ((int *)p)[-1]++;
        }
    }
    StringRef(int text) {
        char *interned;
        if (text == 0) {
            interned = 0;
        } else {
            if (DAT_00586f20[0] == 0) {
                int pool = FUN_002eb010(0x10);
                if (pool != 0) {
                    pool = StringPool_Construct(pool);
                }
                DAT_00586f20[0] = pool;
            }
            interned = StringPool_Intern(DAT_00586f20[0], text);
        }
        p = interned;
    }
    ~StringRef() {
        char *s = p;
        if (s != 0) {
            StringHeader *header = (StringHeader *)s - 1;
            int count = ((int *)s)[-1] - 1;
            ((int *)s)[-1] = count;
            if (count == 0) StringChunk_ReleaseHeader(header->owner, header);
        }
    }
};
extern "C" void FUN_00233c10(const char *programName);
extern "C" void FUN_002342b0(const char *arg0, const char *arg1, int arg2);
extern "C" void FUN_002342e0(const char *arg0, const char *arg1, int arg2);
extern "C" void FUN_00234300(const char *arg0, const char *arg1, float arg2);
extern "C" void FUN_00234350(const char *arg0, const char *arg1, float *arg2);
extern "C" void FUN_002343d0(const char *arg0, const char *arg1, float *arg2);
extern "C" int FUN_00234470(igStringRefList *arg0, int *arg1, const char *arg2);
extern "C" int FUN_00234510(igStringRefList *a0, int *a1, const char *a2, int *arg3);
extern "C" int FUN_00234560(igStringRefList *arg0, int *arg1, const char *arg2, long long *arg3);
extern "C" int FUN_002345b0(igStringRefList *arg0, int *arg1, const char *arg2, void **arg3);
extern "C" int FUN_002346c0(igStringRefList *arg0, int *arg1, const char *arg2, void **arg3);
extern "C" int FUN_00234770(igStringRefList *arg0, int *arg1, const char *arg2, unsigned char *arg3);
extern "C" int thunk_FUN_00234510(igStringRefList *args, int *index, const char *name, int *value);
extern "C" int FUN_00234810(igStringRefList *arg0, int *arg1, const char *arg2, float *arg3);
extern "C" int FUN_00234860(igStringRefList *arg0, int *arg1, const char *arg2, float *arg3);
extern "C" int FUN_002348b0(igStringRefList *arg0, int *arg1, const char *arg2, float *arg3);
extern "C" struct FlushSettings *FUN_00234900(struct FlushSettings *s);
extern "C" void *FUN_00234b90(struct App *arg0, short arg1);
extern "C" void FUN_00234ca0(void);
extern "C" void FUN_00234d70(int self, int count, int *names);
extern "C" void FUN_00235370(ViewerOptions *opts, igStringRefList *args);
class igVisualContextView {
public:
    virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7();
    virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15();
    virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23();
    virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31();
    virtual void d32(); virtual void d33(); virtual void d34(); virtual void d35(); virtual void d36(); virtual void d37(); virtual void d38(); virtual void d39();
    virtual void d40(); virtual void d41(); virtual void d42(); virtual void d43(); virtual void d44(); virtual void d45(); virtual void d46(); virtual void d47();
    virtual void d48(); virtual void d49(); virtual void d50(); virtual void d51(); virtual void d52(); virtual void d53(); virtual void d54(); virtual void d55();
    virtual void d56(); virtual void d57(); virtual void d58(); virtual void d59(); virtual void d60(); virtual void d61(); virtual void d62(); virtual void d63();
    virtual void d64(); virtual void d65(); virtual void d66(); virtual void d67(); virtual void d68(); virtual void d69(); virtual void d70(); virtual void d71();
    virtual void d72(); virtual void d73(); virtual void d74(); virtual void d75(); virtual void d76(); virtual void d77(); virtual void d78(); virtual void d79();
    virtual void d80(); virtual void d81(); virtual void d82(); virtual void d83(); virtual void d84(); virtual void d85(); virtual void d86(); virtual void d87();
    virtual void d88(); virtual void d89(); virtual void d90(); virtual void d91(); virtual void d92(); virtual void d93(); virtual void d94(); virtual void d95();
    virtual void d96(); virtual void d97(); virtual void d98(); virtual void d99(); virtual void d100(); virtual void d101(); virtual void d102(); virtual void d103();
    virtual void d104(); virtual void d105(); virtual void d106(); virtual void d107(); virtual void d108(); virtual void d109(); virtual void d110(); virtual void d111();
    virtual void d112(); virtual void d113(); virtual void d114(); virtual void d115(); virtual void d116(); virtual void d117(); virtual void d118(); virtual void d119();
    virtual void d120(); virtual void d121(); virtual void d122(); virtual void d123(); virtual void d124(); virtual void d125(); virtual void d126(); virtual void d127();
    virtual void d128(); virtual void d129(); virtual void d130(); virtual void d131(); virtual void d132(); virtual void d133(); virtual void d134(); virtual void d135();
    virtual void d136(); virtual void d137(); virtual void d138(); virtual void d139(); virtual void d140(); virtual void d141(); virtual void d142(); virtual void d143();
    virtual void d144(); virtual void d145(); virtual void d146(); virtual void d147(); virtual void d148(); virtual void d149(); virtual void d150(); virtual void d151();
    virtual void d152(); virtual void d153(); virtual void d154(); virtual void d155(); virtual void d156(); virtual void d157(); virtual void d158(); virtual void d159();
    virtual void d160(); virtual void d161(); virtual void d162(); virtual void d163(); virtual void d164(); virtual void d165(); virtual void d166(); virtual void d167();
    virtual void d168(); virtual void d169(); virtual void d170(); virtual void d171(); virtual void d172();
    virtual void vfunc_173();
    virtual void vfunc_174(unsigned int buffers);
};
class igFlushRendererView {
public:
    int _vtable;
    unsigned int _refCount;
    igVisualContextView *_visualContext;
};
extern "C" void Gap__Insight__igFlushRenderer__vfunc_26(igFlushRendererView *self);
struct NamedObject : public igObject { int name; };
extern "C" NamedObject *FUN_002c43b0(...);
extern "C" int FUN_002e3850(...);
extern "C" int FUN_00304720(...);
extern "C" int DAT_004e9740[4];
extern "C" int DAT_004e9748[4];
extern "C" int DAT_004e9750[4];
extern "C" int DAT_00587038[4];
struct G { char p[76]; int f76; };
extern "C" void FUN_00236140(void);
struct TextValue : public igObject { char *text; };
struct ShadowSettings { int enabled; int width; int height; int left; int top; int right; int bottom; float scale; };
struct ShadowConfig {
    char pad0[184];
    int width;
    int height;
    char pad192[4];
    int left;
    int top;
    int right;
    int bottom;
    unsigned char verbose;
};
extern "C" TextValue *FUN_002b9500(int allocator);
extern "C" void FUN_0030b3c0(TextValue *value, const char *text);
extern "C" void FUN_0030b720(TextValue *value, int number, const char *format);
extern "C" int DAT_00587048[4];
extern "C" char *DAT_004c22f0[4];
extern "C" char DAT_004e9760[];
extern "C" char DAT_004e9778[];
extern "C" char DAT_004e9780[];
extern "C" char DAT_004e9788[];
extern "C" char DAT_004e9798[];
extern "C" char DAT_004e97a8[];
extern "C" char DAT_004e97b8[];
extern "C" ShadowSettings FUN_00236260(ShadowConfig *config);
struct ResizeEvent : public igObject { float origin[2]; float size[2]; };
extern "C" int igObject_GetAllocator(...);
extern "C" float DAT_004e0fa0[4];
extern "C" float DAT_004e0fa4[4];
struct WindowInfo { char p[40]; int f40; };
struct Receiver { char p[8]; WindowInfo *f8; };
extern "C" int Gap__Insight__igWindowResizeEventReceiver__vfunc_32(Receiver *self, int width, int height);
extern "C" int FUN_00236b70(...);
extern "C" int FUN_002d6f50(...);
class DW4VC_92_0 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual int vX(); };
extern "C" void FUN_00236ab0(void *arg0, void *arg1);
extern "C" int FUN_002d7750(...);
class DW4VC_96_0 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual int vX(); };
extern "C" void FUN_00236b10(void *arg0, void *arg1);
struct S12 { char pad[12]; void *f12; };
class DW4VC_96_1 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual int vX(int); };
class DW4VC_104_0 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual int vX(); };
extern "C" void FUN_00236be0(S12 *arg0, int arg1);
struct S236;
class DW4VC_100_1 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual int vX(int); };
struct S236 { int a, b, c; void *p; };
extern "C" void FUN_00236c40(S236 *arg0, int arg1);
struct Instance : public igObject { };
extern "C" int igMetaObject_CountTree(int);
extern "C" int FUN_002fe300(int, int);
extern "C" igSmartPointer<Instance> FUN_002fd6e0(int, int);
extern "C" void FUN_00236ca0(int self);
extern "C" int ObjectList_AppendRetained(...);
class DW4VC_92_1 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual int vX(int); };
extern "C" void FUN_00236dd0(void *arg0, void **arg1);
extern "C" int ObjectList_RemoveFirstRetained(...);
extern "C" void FUN_00236e20(void *arg0, void **arg1);
typedef struct L { char pad8[8]; int cnt; char pad12[4]; int *arr; } L;
typedef struct A { char pad104[104]; L *f68; } A;
extern "C" void FUN_00236e80(A *arg0);
extern "C" int FUN_00457ca0(...);
extern "C" void FUN_00236ee0(void *arg0, int arg1);
extern "C" int DAT_004fb410[4];
typedef struct Obj_236f30 { char pad[28]; int f28; } Obj_236f30;
extern "C" void FUN_00236f30(Obj_236f30 *arg0, int arg1);
struct Obj_236f80 { virtual int a0(); virtual int a1(); virtual int a2(); virtual int a3(); virtual int a4(); virtual int a5(); virtual int a6(); virtual int a7(); virtual int a8(); virtual int a9(); virtual int a10(); virtual int a11(); virtual int a12(); virtual int a13(); virtual int a14(); virtual int a15(); virtual int a16(); virtual int a17(); virtual int a18(); virtual int a19(); virtual int v20(); };
struct List { int pad[2]; unsigned int count; int pad2; Obj_236f80 **arr; };
struct Mid { int pad[2]; List *list; };
struct Self { int pad[2]; Mid *mid; };
extern "C" Obj_236f80 *FUN_00236f80(Self *arg0, int arg1);
extern "C" int FUN_00237010(void);
extern "C" int FUN_00237020(int *p);
/* Dummy class with 25 virtual slots before vX, so that vX is the manager's
 * vtable slot 27 (matching construct: gives the retail `lw t9,108(t9)` call). */
class DW4VC { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual int vX(int); };
extern "C" void igInsightCore_AddInfo(igInsightCore *self, int info);
extern "C" int List_Reserve(...);
/* matching construct: dummy virtual slots so the vX() call dispatches through the retail vtable offset 112 */
class VC112 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual int vX(); };
extern "C" void FUN_002370c0(igInsightCore *arg0);
class V100 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void vX(); };
class V108 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void vY(); };
struct L_2371f0 { char pad8[8]; unsigned int cnt; char pad12[4]; V100 **arr; };
struct M { char pad8[8]; L_2371f0 *l; };
struct S_2371f0 { char pad8[8]; M *m; char pad12[36]; V108 *f48; char pad52[4]; long long f56; long long f64; };
extern "C" void FUN_002371f0(S_2371f0 *arg0);
class A_237280 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void vX(); };
class B { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void vX(); };
struct Q { int p0; int p1; int count; int p3; B **data; };
extern "C" void FUN_00237280(int *arg0);
extern "C" int FUN_002d7090(...);
extern "C" int FUN_002d78e0(...);
extern "C" int FUN_00454290(...);
extern "C" int Gap__Core__igObject__vfunc_11(...);
extern "C" int DAT_004e9840[4];
extern "C" int DAT_004e9850[4];
extern "C" int DAT_004e9860[4];
struct A_237300 { char pad[28]; int f28; int f32; int f36; char pad40[4]; int f44; char pad48[24]; int f72; };
struct StringRef_237300 {
    int *p;
    StringRef_237300(int *text) {
        int *interned;
        if (text == 0) {
            interned = 0;
        } else {
            if (DAT_00586f20[0] == 0) {
                int pool = FUN_002eb010(16);
                if (pool != 0) pool = StringPool_Construct(pool);
                DAT_00586f20[0] = pool;
            }
            interned = (int *)StringPool_Intern(DAT_00586f20[0], text);
        }
        p = interned;
    }
    ~StringRef_237300() {
        int *s = p;
        if (s != 0) {
            int *hd = s - 2;
            int cnt = s[-1] - 1;
            s[-1] = cnt;
            if (cnt == 0) StringChunk_ReleaseHeader(*hd, hd);
        }
    }
};
extern "C" void Gap__Insight__igInsightCore__vfunc_13(struct A_237300 *arg0);
extern "C" int FUN_002364e0(...);
extern "C" int FUN_004541f0(...);
struct OO;
struct R_237530;
class DW4VC_152 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual void d32(); virtual void d33(); virtual void d34(); virtual void d35(); virtual R_237530 *vX(); };
struct R_237530 { int w0; int rc; };
struct Lst { char pad[8]; int n; int w12; int *items; };
struct Wr { char pad[8]; Lst *f8; };
struct OO { char pad[20]; DW4VC_152 *f20; R_237530 *f24; Wr *f28; int f32; };
extern "C" void FUN_00237530(OO *arg0);
struct L_2376b0 { char pad[8]; int count; int pad2; int *items; };
struct M_2376b0 { char pad[8]; struct L_2376b0 *list; };
struct H { char pad[28]; struct M_2376b0 *m; };
extern "C" int FUN_0013c110(...);
extern "C" void FUN_002376b0(struct H *arg0);
extern "C" long long __muldi3(long long, int);
class A21 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void vX(); };
class A24 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual long long vX(); };
struct S_237730 { char pad12[12]; A21 *f12; char pad16[16]; A21 *f32; char pad36[12]; A24 *f48; char pad52[4]; long long f56; long long f64; int f72; char pad76[4]; long long f80; };
extern "C" void FUN_00237730(S_237730 *arg0);
class ProfiledObject { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual int v23(); virtual long long v24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual void d32(); virtual void d33(); virtual int v34(); virtual void d35(); virtual void d36(); virtual void d37(); virtual void d38(); virtual void d39(); virtual void d40(); virtual void d41(); virtual void d42(); virtual void d43(); virtual void d44(); virtual void d45(); virtual void d46(); virtual void d47(); virtual void d48(); virtual void d49(); virtual void d50(); virtual void d51(); virtual void d52(); virtual void d53(); virtual void d54(); virtual void d55(); virtual void d56(); virtual void d57(); virtual void d58(); virtual void d59(); virtual void d60(); virtual void d61(); virtual void d62(); virtual void d63(); virtual void d64(); virtual void d65(); virtual void d66(); virtual void d67(); virtual void d68(); virtual void d69(); virtual void d70(); virtual void d71(); virtual void d72(); virtual void d73(); virtual void d74(); virtual void d75(); virtual void d76(); virtual void d77(); virtual void d78(); virtual void d79(); virtual void d80(); virtual void d81(); virtual void d82(); virtual void d83(); virtual void d84(); virtual void d85(); virtual void d86(); virtual void d87(); virtual void d88(); virtual void d89(); virtual void d90(); virtual void d91(); virtual void d92(); virtual void d93(); virtual void d94(); virtual void d95(); virtual void d96(); virtual void d97(); virtual void d98(); virtual void d99(); virtual void d100(); virtual void d101(); virtual void d102(); virtual void d103(); virtual void d104(); virtual void d105(); virtual void d106(); virtual void d107(); virtual void d108(); virtual void d109(); virtual void d110(); virtual void d111(); virtual void d112(); virtual void d113(); virtual void d114(); virtual void d115(); virtual void d116(); virtual void d117(); virtual void d118(); virtual void d119(); virtual void d120(); virtual void d121(); virtual void d122(); virtual void d123(); virtual void d124(); virtual void d125(); virtual void d126(); virtual void d127(); virtual void d128(); virtual void d129(); virtual void d130(); virtual void d131(); virtual void d132(); virtual void d133(); virtual void d134(); virtual void d135(); virtual void d136(); virtual void d137(); virtual void d138(); virtual void d139(); virtual void d140(); virtual void d141(); virtual void d142(); virtual void d143(); virtual void d144(); virtual void d145(); virtual void d146(); virtual void d147(); virtual void d148(); virtual void d149(); virtual void d150(); virtual void d151(); virtual void d152(); virtual void d153(); virtual void d154(); virtual void d155(); virtual void d156(); virtual void d157(); virtual void d158(); virtual void d159(); virtual void d160(); virtual void d161(); virtual void d162(); virtual void d163(); virtual void d164(); virtual void d165(); virtual void d166(); virtual void d167(); virtual void d168(); virtual void d169(); virtual void d170(); virtual int v171(); virtual int v172(); };
struct ProfiledObjectList { char pad[8]; int cnt; char pad2[4]; ProfiledObject **arr; };
struct ProfiledObjectHolder { char pad[8]; ProfiledObjectList *l; };
struct ProfilerState { char p0[24]; ProfiledObject *a; ProfiledObjectHolder *m; char p1[16]; ProfiledObject *b; int cnt; char p2[32]; long long d1; long long d2; };
extern "C" void FUN_002377c0(ProfilerState *t);
struct T_237940 { void m(); };
typedef void (T_237940::*PM)();
struct S_237940 { char pad[8]; T_237940 *obj; PM pm; };
extern "C" void Gap__Insight__igMessageDefaultReceiver__vfunc_23(S_237940 *s);
typedef struct E { int pad[2]; int f8; } E;
typedef struct L_237990 { int pad[2]; int f8; int pad2; E **f16; } L_237990;
typedef struct A_237990 { int pad[2]; L_237990 *f8; } A_237990;
extern "C" E *FUN_00237990(const A_237990 *arg0, int arg1);
struct MessageFilter : igObject {
    igSmartPointer<igObject> _target;
};
struct FilterList : igObject {
    int _count;
    int _capacity;
    MessageFilter **_data;
};
struct FilterDispatcher : igObject {
    FilterList *_filters;
};
extern "C" igSmartPointer<MessageFilter> FUN_002379e0(FilterDispatcher *self, igObject *target);
class N;
struct L_237b50 { char pad[8]; int cnt; int cap; N **data; };
class N { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual int vX(int); char pad[8]; L_237b50 *f12; };
extern "C" void Gap__Insight__igFilterMessageDispatcher__vfunc_28(N *arg0, int arg1);
extern "C" void igObject_IsKindOf(int, int);
extern "C" void Gap__Insight__igMessageFilter__vfunc_23(int arg0, int arg1);
class FilterDispatcherSlots {
public:
    virtual void vfunc_2(); virtual void vfunc_3(); virtual void vfunc_4(); virtual void vfunc_5(); virtual void vfunc_6(); virtual void vfunc_7();
    virtual void vfunc_8(); virtual void vfunc_9(); virtual void vfunc_10(); virtual void vfunc_11(); virtual void vfunc_12(); virtual void vfunc_13();
    virtual void vfunc_14(); virtual void vfunc_15(); virtual void vfunc_16(); virtual void vfunc_17(); virtual void vfunc_18(); virtual void vfunc_19();
    virtual void vfunc_20(); virtual void vfunc_21(); virtual void vfunc_22(); virtual void vfunc_23();
    virtual void dispatch(int message, igObject *filter);
};
extern "C" void Gap__Insight__igFilterMessageDispatcher__vfunc_23(FilterDispatcherSlots *self, int message, igObject *target);
extern "C" int ObjectList_AppendUniqueRetained(...);
extern "C" void Gap__Insight__igFilterMessageDispatcher__vfunc_24(void *arg0, void *arg1, void *arg2);
class DW4VC_108_2 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual int vX(int, int); };
extern "C" void Gap__Insight__igFilterMessageDispatcher__vfunc_26(void **arg0, int arg1, int arg2);
struct L_237d80 { int p0; int p1; int n; int p3; int *arr; };
class V { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void vX(int, int);
  char pad[8]; L_237d80 *list; };
extern "C" void Gap__Insight__igFilterMessageDispatcher__vfunc_25(V *arg0, int arg1);
typedef struct S_arg0 { char pad0[8]; int f8; int f12; } S_arg0;
typedef struct S_arg2 { char pad0[12]; int f12; } S_arg2;
extern "C" void Gap__Insight__igFilterMessageDispatcher__vfunc_27(S_arg0 *arg0, void *arg1, S_arg2 *arg2);
class igFilterMessageDispatcherView {
public:
    virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7();
    virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15();
    virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20();
    virtual void vfunc_21();
    virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25();
    virtual void vfunc_26(void *message);
};
struct igMessageDispatcherOwnerView {
    char _pad0[8];
    igFilterMessageDispatcherView *f8;
};
extern "C" void FUN_00237e80(igMessageDispatcherOwnerView *self);
extern "C" void FUN_00237ea0(igMessageDispatcherOwnerView *self, void *message);
class SchedulerManager {
public:
    virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7();
    virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15();
    virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23();
    virtual void d24(); virtual void d25(); virtual void d26(); virtual void update();
};
struct ManagerArray {
    int _pad0[2];
    int _count;
    int _capacity;
    SchedulerManager **_data;
};
struct ManagerListView : igObject {
    ManagerArray *_list;
};
extern "C" void ObjectList_ResizeRetained(ManagerArray *list, int count);
extern "C" void Gap__Insight__igSerialScheduler__vfunc_23(igSerialScheduler *scheduler);
extern "C" void Gap__Insight__igSerialScheduler__vfunc_24(void *arg0, int arg1);
typedef struct Obj_238020 { char pad[8]; int f8; } Obj_238020;
extern "C" void Gap__Insight__igSerialScheduler__vfunc_25(Obj_238020 *arg0, int arg1);
extern "C" void Gap__Insight__igSerialScheduler__vfunc_27(int a0);
typedef struct S0 { char pad8[8]; int f8; } S0;
extern "C" int FUN_002d7760(...);
extern "C" void Gap__Insight__igSerialScheduler__vfunc_28(S0 *arg0, int arg1, int arg2);
extern "C" int FUN_002d7840(...);
extern "C" void Gap__Insight__igSerialScheduler__vfunc_29(int a0);
extern "C" float DAT_004e1058[4];
extern "C" float DAT_004e105c[4];
extern "C" float DAT_004e1060[4];
extern "C" float DAT_004e1170[4];
extern "C" float DAT_004e1174[4];
extern "C" float DAT_004e1178[4];
extern "C" float DAT_004e117c[4];
extern "C" void *FUN_00238110(void *arg0);
/* Saves the Alchemy viewer (INSIGHT) options into the property tree: the INSIGHT group is looked
 * up in the property set held by the global (+56), falling back to 'Viewer', and each option is
 * written under its string name. Every write is guarded by its name pointer (the original option
 * table can drop a name); the guards are kept because the compiler does not fold them. Callee
 * names come from their roles: StoreString (thunk_FUN_00306910), StoreByte (thunk_FUN_00306e50),
 * StoreFloat (thunk_FUN_003066b0), StoreInt (thunk_FUN_003065f0), StoreVec4 (FUN_001e71f0),
 * StoreVec3 (FUN_001e70a0). */
typedef struct Vec3 { float x, y, z; } Vec3;
typedef struct Vec4 { float x, y, z, w; } Vec4;
typedef struct ViewerOptions_2382e0 {
  char * extraCommandLine;
  unsigned char showBBox;
  unsigned char showNormals;
  char pad6[2];
  Vec4 normalsColor;
  Vec4 invalidStoredNormalsColor;
  Vec4 scaledNormalsColor;
  float invalidNormalsPrecision;
  unsigned char autoSelectCamera;
  char pad61[3];
  float horizontalFieldOfView;
  unsigned char autoPlanes;
  char pad69[3];
  float defaultNearPlane;
  float defaultFarPlane;
  Vec3 upVector;
  unsigned char autoSceneLights;
  unsigned char autoHeadLight;
  unsigned char useSceneLights;
  unsigned char useHeadLight;
  unsigned char useHeadLightSpecular;
  char pad97[3];
  Vec4 headLightDiffuse;
  Vec4 headLightSpecular;
  Vec4 headLightAmbient;
  Vec4 clearColor;
  unsigned char wireframeMode;
  unsigned char forceWireframe;
  unsigned char backFaceCullingMode;
  unsigned char forceBackFaceCulling;
  unsigned char alphaTest;
  unsigned char forceAlphaTest;
  char pad170[2];
  float alphaTestReference;
  float maxFrameRate;
  unsigned char optimizeTextures;
  unsigned char halfBuffer;
  unsigned char palVideoMode;
  char pad183[1];
  int width;
  int height;
  int swapInterval;
  int colorBits;
  int alphaBits;
  int depthBits;
  int stencilBits;
  unsigned char reportVideoFormat;
  unsigned char showLogo;
  unsigned char showUI;
  unsigned char enableMayaControls;
  unsigned char benchmark;
  char pad217[3];
  int benchmarkSkipFrames;
  int benchmarkFrames;
  unsigned char columnStatistics;
  unsigned char allocateVisualContextInScratchPad;
} ViewerOptions_2382e0;
typedef struct PropertySet { char pad[56]; int props; } PropertySet;
extern "C" char DAT_004e9870[];
extern "C" char DAT_004e9878[];
extern "C" char DAT_004e9880[];
extern "C" char DAT_004e9898[];
extern "C" char DAT_004e98a8[];
extern "C" char DAT_004e98b8[];
extern "C" char DAT_004e98d0[];
extern "C" char DAT_004e98f0[];
extern "C" char DAT_004e9910[];
extern "C" char DAT_004e9930[];
extern "C" char DAT_004e9950[];
extern "C" char DAT_004e9968[];
extern "C" char DAT_004e9980[];
extern "C" char DAT_004e99a0[];
extern "C" char DAT_004e99b0[];
extern "C" char DAT_004e99c0[];
extern "C" char DAT_004e99d0[];
extern "C" char DAT_004e99e0[];
extern "C" char DAT_004e99f0[];
extern "C" char DAT_004e9a00[];
extern "C" char DAT_004e9a20[];
extern "C" char DAT_004e9a40[];
extern "C" char DAT_004e9a60[];
extern "C" char DAT_004e9a78[];
extern "C" char DAT_004e9a88[];
extern "C" char DAT_004e9a98[];
extern "C" char DAT_004e9ab0[];
extern "C" char DAT_004e9ad0[];
extern "C" char DAT_004e9ae8[];
extern "C" char DAT_004e9af8[];
extern "C" char DAT_004e9b10[];
extern "C" char DAT_004e9b28[];
extern "C" char DAT_004e9b40[];
extern "C" char DAT_004e9b58[];
extern "C" char DAT_004e9b68[];
extern "C" char DAT_004e9b78[];
extern "C" char DAT_004e9b80[];
extern "C" char DAT_004e9b88[];
extern "C" char DAT_004e9b98[];
extern "C" char DAT_004e9ba8[];
extern "C" char DAT_004e9bb8[];
extern "C" char DAT_004e9bc8[];
extern "C" char DAT_004e9be0[];
extern "C" char DAT_004e9bf8[];
extern "C" char DAT_004e9c08[];
extern "C" char DAT_004e9c10[];
extern "C" char DAT_004e9c28[];
extern "C" char DAT_004e9c40[];
extern "C" char DAT_004e9c60[];
extern "C" char DAT_004e9c70[];
extern "C" char DAT_004e9c90[];
extern "C" int FUN_00306360(int, char *, int);
extern "C" int thunk_FUN_00306910(int, int, char *, char **, char *, int);
extern "C" int thunk_FUN_00306e50(int, int, char *, unsigned char *, int, int);
extern "C" int thunk_FUN_003066b0(int, int, char *, float *, int, float);
extern "C" int thunk_FUN_003065f0(int, int, char *, int *, int, int);
extern "C" int FUN_001e71f0(int, int, char *, Vec4 *, Vec4 *, int);
extern "C" int FUN_001e70a0(int, int, char *, Vec3 *, Vec3 *, int);
extern "C" void FUN_002382e0(ViewerOptions_2382e0 *opt, int, int, int, int, int, int, int);
extern "C" int Gap__Insight__igSerialScheduler__vfunc_22(void);
extern "C" int Gap__Insight__igFilterMessageDispatcher__vfunc_22(void);
extern "C" int Gap__Insight__igMessageDefaultReceiver__vfunc_22(void);
extern "C" int Gap__Insight__igInsightCore__vfunc_22(void);
extern "C" int Gap__Insight__igWindowResizeEventReceiver__vfunc_22(void);
extern "C" int Gap__Gui__igEventReceiver__vfunc_23(void);
extern "C" int Gap__Bec__beKeyboardReceiver__vfunc_22(void);
extern "C" int Gap__Bec__beKeyboardReceiver__vfunc_23(void);
extern "C" int Gap__Bec__beKeyboardReceiver__vfunc_24(void);
extern "C" int Gap__Bec__beKeyboardReceiver__vfunc_25(void);
extern "C" int Gap__Bec__beKeyboardReceiver__vfunc_26(void);
extern "C" int Gap__Bec__beKeyboardReceiver__vfunc_27(void);
extern "C" int Gap__Bec__beKeyboardReceiver__vfunc_28(void);
extern "C" int Gap__Bec__beKeyboardReceiver__vfunc_29(void);
extern "C" int Gap__Bec__beKeyboardReceiver__vfunc_31(void);
extern "C" int Gap__Bec__beKeyboardReceiver__vfunc_32(void);
extern "C" int Gap__Bec__beKeyboardReceiver__vfunc_30(void);
extern "C" int Gap__Insight__igFlushRenderer__vfunc_22(void);
extern "C" void Gap__Insight__igFlushRenderer__vfunc_25(void);
extern "C" void Gap__Insight__igFlushRenderer__vfunc_23(void);
extern "C" void Gap__Insight__igFlushRenderer__vfunc_24(void);
extern "C" int Gap__Insight__igInfoManagerList__vfunc_22(void);
extern "C" int Gap__Insight__igInfoManagerOrderedList__vfunc_22(void);
extern "C" int Gap__Core__igDependencyOrderedList__vfunc_22(void);
extern "C" int Gap__Insight__igViewportResizedMessage__vfunc_22(void);
extern "C" int Gap__Gui__igEventReceiver__vfunc_22(void);
extern "C" int Gap__Insight__igInsightPluginList__vfunc_22(void);
extern "C" int Gap__Insight__igMessageFilter__vfunc_22(void);
extern "C" int Gap__Insight__igMessageFilterList__vfunc_22(void);
extern "C" int Gap__Insight__igMessageReceiverList__vfunc_22(void);
extern "C" int Gap__Insight__igMessenger__vfunc_22(void);
extern "C" int Gap__Insight__igMessage__vfunc_22(void);
extern "C" int g_igRenderer_metaObject[4];
extern "C" int FUN_00238cf0(void);
extern "C" int DAT_0056db58[4];
extern "C" int Gap__Insight__igInsightPluginList__vfunc_24(void);
extern "C" int Gap__Insight__igMessageFilterList__vfunc_24(void);
extern "C" int Gap__Insight__igInfoManagerList__vfunc_24(void);
extern "C" int Gap__Insight__igMessageReceiverList__vfunc_24(void);

void InsightLibrary_MarkRegistered(void) {
    if (g_InsightLibrary_registered == 0) {
        g_InsightLibrary_registered = 1;
    }
}

void *FUN_00230f70(struct S *arg0, short arg1) {
    void *p;
    int rc;

    if (arg0 != 0) {
        arg0->f0 = &DAT_0052d060[0];
        if (&arg0->f8) {
            p = arg0->f8;
            if (p != 0) {
                rc = *(int *)((char *)(p) + 4) - 1;
                *(int *)((char *)(p) + 4) = rc;
                if (((unsigned long long) ((long long) *(int *)((char *)(p) + 4) << 0x29) >> 0x29) == 0) {
                    igObject_Destroy(p);
                }
            }
        }
        if (arg1 > 0) {
            thunk_FUN_002ed460__002ff810(arg0);
        }
    }
    return arg0;
}

int FUN_00231010(void) {
    return DAT_0058c208[0];
}

int FUN_00231020(void) {
    return DAT_0056dad8[0];
}

void *FUN_00231030(struct S *arg0, short arg1) {
    void *p;
    int *h;
    int rc;

    if (arg0 != 0) {
        arg0->f0 = &DAT_0052cf80[0];
        if (arg0 != 0) {
            arg0->f0 = &DAT_00524950[0];
            if (&arg0->f8) {
                p = arg0->f8;
                if (p != 0) {
                    h = (int *)((char *)(p) - 8);
                    rc = *(int *)((char *)(p) - 4) - 1;
                    *(int *)((char *)(p) - 4) = rc;
                    if (rc == 0) {
                        StringChunk_ReleaseHeader(*h, h);
                    }
                }
            }
        }
        if (arg1 > 0) {
            thunk_FUN_002ed460__002ff810(arg0);
        }
    }
    return arg0;
}

int FUN_002310d0(void) {
    return DAT_0056dc38[0];
}

igMetaObject *igSerialScheduler_GetMetaObject(void)
{
    igMetaObject *g = g_igSerialScheduler_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_00231290();
    return g_igSerialScheduler_metaObject[0];
}

int igSerialScheduler_GetVTable(void) {
    Obj obj;
    int r;

    igObject_InitHeader(&obj);
    obj.vt = &DAT_0052c830[0];
    obj.m8 = 0;
    obj.m12 = 0;
    r = *(int *)((char *)&obj + *(int *)((char *)(DAT_00586dc8[0]) + 916));
    obj.vt = &DAT_0052c830[0];
    obj.rel12();
    obj.rel8();
    return r;
}

void **FUN_00231210(void **arg0, long long arg1) {
    char *o;

    if (arg0 != 0) {
        o = (char *)*arg0;
        if (o != 0) {
            *(int *)(o + 4) = *(int *)(o + 4) - 1;
            if ((*(int *)(o + 4) & 0x7FFFFF) == 0) {
                igObject_Destroy(o);
            }
        }
        if ((short)arg1 > 0) {
            FUN_00100610(arg0);
        }
    }
    return arg0;
}

void FUN_00231290(void)
{
    igMetaObject_RunStaticInit(igSerialScheduler_Register);
}

void igSerialScheduler_Register(void) {
    InsightLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igSerialScheduler_metaObject,
        igInsightScheduler_Register,
        igInsightScheduler_GetPublishedMetaObject,
        thunk_igSerialScheduler_GetMetaObject,
        igSerialScheduler_className,
        0x10, /* instance size */
        igSerialScheduler_GetVTable,
        &igSerialScheduler_InitFields,
        0, /* extra callback item */
        g_igSerialScheduler_callbackList /* callback list */
    );
}

void thunk_igSerialScheduler_GetMetaObject(void) {
    igSerialScheduler_GetMetaObject();
}

int FUN_00231330(void) {
    return DAT_0056db48[0];
}

void igSerialScheduler_InitFields(void) {
    int temp_s2;
    void *temp_s1_2;
    void *temp_s1;
    void *temp_s0;

    temp_s0 = (void *)DAT_0056dab0[0];
    temp_s2 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &DAT_00497f90[0], 2);
    temp_s1 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2));
    ((igObjectRefMetaField *)temp_s1)->_metaObject = FUN_00233480();
    ((igRefMetaField *)temp_s1)->_construct = 1;
    temp_s1_2 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 1));
    ((igObjectRefMetaField *)temp_s1_2)->_metaObject = FUN_00233750();
    ((igRefMetaField *)temp_s1_2)->_construct = 1;
    igMetaObject_NameFields(temp_s0, &DAT_00497f98[0], &DAT_00497fa0[0], &DAT_00497fa8[0], temp_s2);
}

int FUN_00231400(void) {
    if (DAT_0056dac8[0] == 0) {
        DAT_0056dac8[0] = igMetaObject_Create(Memory_GetAllocatorBySelector(DAT_00587040[0]));
    }
    return DAT_0056dac8[0];
}

igMetaObject *igMessenger_GetMetaObject(void)
{
    igMetaObject *g = g_igMessenger_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_00231530();
    return g_igMessenger_metaObject[0];
}

int igMessenger_GetVTable(void) {
    struct W o;
    int r;
    struct Ref *p;
    igObject_InitHeader(&o);
    o.vt = DAT_0052cf20;
    o.ref = 0;
    r = *(int *)((char *)&o + *(int *)(DAT_00586dc8[0] + 916));
    o.vt = DAT_0052cf20;
    if (&o.ref != 0) {
        p = o.ref;
        if (p != 0) {
            p->u.w = p->u.w - 1;
            if (p->u.b.cnt == 0) igObject_Destroy(p);
        }
    }
    return r;
}

void FUN_00231530(void)
{
    igMetaObject_RunStaticInit(igMessenger_Register);
}

void igMessenger_Register(void) {
    InsightLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igMessenger_metaObject,
        igObject_Register,
        igObject_GetMetaObject_ParentAccessor,
        thunk_igMessenger_GetMetaObject,
        igMessenger_className,
        0xC, /* instance size */
        igMessenger_GetVTable,
        &igMessenger_InitFields,
        0, /* extra callback item */
        g_igMessenger_callbackList /* callback list */
    );
}

void thunk_igMessenger_GetMetaObject(void) {
    igMessenger_GetMetaObject();
}

void igMessenger_InitFields(void) {
    int temp_s2;
    void *temp_s1;
    void *temp_s0;

    temp_s0 = (void *)DAT_0056dac8[0];
    temp_s2 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &DAT_00497fb8[0], 1);
    temp_s1 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2));
    ((igObjectRefMetaField *)temp_s1)->_metaObject = FUN_002320b0();
    ((igRefMetaField *)temp_s1)->_construct = 1;
    igMetaObject_NameFields(temp_s0, &DAT_00497fc0[0], &DAT_00497fc8[0], &DAT_00497fd0[0], temp_s2);
}

igMetaObject *igMessage_GetMetaObject(void)
{
    igMetaObject *g = g_igMessage_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_00231700();
    return g_igMessage_metaObject[0];
}

int igMessage_GetVTable(void) {
    struct Obj_2316c0 o; igObject_InitHeader(&o);
    o.vt = &DAT_0052d000[0];
    return *(int *)((char *)&o + *(int *)((char *)(DAT_00586dc8[0]) + 916));
}

void FUN_00231700(void)
{
    igMetaObject_RunStaticInit(igMessage_Register);
}

void igMessage_Register(void) {
    InsightLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igMessage_metaObject,
        igObject_Register,
        igObject_GetMetaObject_ParentAccessor,
        thunk_igMessage_GetMetaObject,
        igMessage_className,
        8, /* instance size */
        igMessage_GetVTable,
        0,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void thunk_igMessage_GetMetaObject(void) {
    igMessage_GetMetaObject();
}

int FUN_00231790(void) {
    if (DAT_0056dae0[0] == 0) {
        DAT_0056dae0[0] = igMetaObject_Create(Memory_GetAllocatorBySelector(DAT_00587040[0]));
    }
    return DAT_0056dae0[0];
}

igMetaObject *igMessageReceiverList_GetMetaObject(void)
{
    igMetaObject *g = g_igMessageReceiverList_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_00231870();
    return g_igMessageReceiverList_metaObject[0];
}

int igMessageReceiverList_GetVTable(void) {
    struct Obj_231830 obj;

    igObject_InitHeader(&obj);
    obj.vt = &DAT_0052ceb0[0];
    return *(int *)((char *)&obj + *(int *)((char *)(DAT_00586dc8[0]) + 916));
}

void FUN_00231870(void)
{
    igMetaObject_RunStaticInit(igMessageReceiverList_Register);
}

void igMessageReceiverList_Register(void) {
    InsightLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igMessageReceiverList_metaObject,
        igObjectList_Register,
        igObjectList_GetPublishedMetaObject,
        thunk_igMessageReceiverList_GetMetaObject,
        igMessageReceiverList_className,
        0x14, /* instance size */
        igMessageReceiverList_GetVTable,
        0,
        0, /* extra callback item */
        g_igMessageReceiverList_callbackList /* callback list */
    );
}

void thunk_igMessageReceiverList_GetMetaObject(void) {
    igMessageReceiverList_GetMetaObject();
}

igMetaObject *igMessageReceiver_GetMetaObject(void)
{
    igMetaObject *g = g_igMessageReceiver_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_00231950();
    return g_igMessageReceiver_metaObject[0];
}

void FUN_00231950(void)
{
    igMetaObject_RunStaticInit(igMessageReceiver_Register);
}

void igMessageReceiver_Register(void) {
    InsightLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        1, /* abstract */
        g_igMessageReceiver_metaObject,
        igObject_Register,
        igObject_GetMetaObject_ParentAccessor,
        thunk_igMessageReceiver_GetMetaObject,
        igMessageReceiver_className,
        8, /* instance size */
        0,
        0,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void thunk_igMessageReceiver_GetMetaObject(void) {
    igMessageReceiver_GetMetaObject();
}

int FUN_002319d0(void) {
    if (DAT_0056daf0[0] == 0) {
        DAT_0056daf0[0] = igMetaObject_Create(Memory_GetAllocatorBySelector(DAT_00587040[0]));
    }
    return DAT_0056daf0[0];
}

igMetaObject *igMessageFilterList_GetMetaObject(void)
{
    igMetaObject *g = g_igMessageFilterList_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_00231ab0();
    return g_igMessageFilterList_metaObject[0];
}

int igMessageFilterList_GetVTable(void) {
    struct Obj_231a70 obj;

    igObject_InitHeader(&obj);
    obj.vt = &DAT_0052ce40[0];
    return *(int *)((char *)&obj + *(int *)((char *)(DAT_00586dc8[0]) + 916));
}

void FUN_00231ab0(void)
{
    igMetaObject_RunStaticInit(igMessageFilterList_Register);
}

void igMessageFilterList_Register(void) {
    InsightLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igMessageFilterList_metaObject,
        igObjectList_Register,
        igObjectList_GetPublishedMetaObject,
        thunk_igMessageFilterList_GetMetaObject,
        igMessageFilterList_className,
        0x14, /* instance size */
        igMessageFilterList_GetVTable,
        0,
        0, /* extra callback item */
        g_igMessageFilterList_callbackList /* callback list */
    );
}

void thunk_igMessageFilterList_GetMetaObject(void) {
    igMessageFilterList_GetMetaObject();
}

int FUN_00231b40(int arg0) {
    FUN_00231cb0();
    return igMetaObject_CreateInstance(*(int *)0x56DAF8, arg0);
}

igMetaObject *igMessageFilter_GetMetaObject(void)
{
    igMetaObject *g = g_igMessageFilter_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_00231cb0();
    return g_igMessageFilter_metaObject[0];
}

int igMessageFilter_GetVTable(void) {
    union U u;
    int temp_s1;
    S_ref *q2;
    S_ref *q3;

    void *temp_a0;
    void *temp_a0_2;

    igObject_InitHeader(u.b);
    q2 = (S_ref *)&u.p[2];
    q3 = (S_ref *)&u.p[3];
    u.w[0] = (int)(&DAT_0052cde0[0]);
    *(int *)q2 = 0;
    *(int *)q3 = 0;
    temp_s1 = *(int *)&u.b[*(int *)((char *)(DAT_00586dc8[0]) + 916)];
    u.w[0] = (int)(&DAT_0052cde0[0]);
    if (q3 != 0) {
        q3 = *(S_ref **)q3;
        if (q3 != 0) {
            q3->f4 = (int)((int) (q3->f4 - 1));
            if (((unsigned long long) ((long long) q3->f4 << 0x29) >> 0x29) == 0) {
                igObject_Destroy(q3);
            }
        }
    }
    if (q2 != 0) {
        q2 = *(S_ref **)q2;
        if (q2 != 0) {
            q2->f4 = (int)((int) (q2->f4 - 1));
            if (((unsigned long long) ((long long) q2->f4 << 0x29) >> 0x29) == 0) {
                igObject_Destroy(q2);
            }
        }
    }
    return temp_s1;
}

void FUN_00231cb0(void)
{
    igMetaObject_RunStaticInit(igMessageFilter_Register);
}

void igMessageFilter_Register(void) {
    InsightLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igMessageFilter_metaObject,
        igObject_Register,
        igObject_GetMetaObject_ParentAccessor,
        thunk_igMessageFilter_GetMetaObject,
        igMessageFilter_className,
        0x10, /* instance size */
        igMessageFilter_GetVTable,
        &igMessageFilter_InitFields,
        0, /* extra callback item */
        g_igMessageFilter_callbackList /* callback list */
    );
}

void thunk_igMessageFilter_GetMetaObject(void) {
    igMessageFilter_GetMetaObject();
}

void igMessageFilter_InitFields(void) {
    int temp_s2;
    void *temp_s1_2;
    void *temp_s1;
    void *temp_s0;

    temp_s0 = (void *)DAT_0056daf8[0];
    temp_s2 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &DAT_00497ff8[0], 2);
    temp_s1 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2));
    ((igObjectRefMetaField *)temp_s1)->_metaObject = FUN_002be610();
    ((igRefMetaField *)temp_s1)->_construct = 1;
    temp_s1_2 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 1));
    ((igObjectRefMetaField *)temp_s1_2)->_metaObject = FUN_00231790();
    ((igRefMetaField *)temp_s1_2)->_construct = 1;
    igMetaObject_NameFields(temp_s0, &DAT_00498000[0], &DAT_00498008[0], &DAT_00498010[0], temp_s2);
}

igMetaObject *igFilterMessageDispatcher_GetMetaObject(void)
{
    igMetaObject *g = g_igFilterMessageDispatcher_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_00231f40();
    return g_igFilterMessageDispatcher_metaObject[0];
}

int igFilterMessageDispatcher_GetVTable(void) {
    igFilterMessageDispatcher obj;
    igObject *o;
    int t;
    igObject_InitHeader(&obj);
    *(int **)&obj._vtable = &DAT_0052c8b0[0];
    obj._defaultFilters = 0;
    obj._filters = 0;
    t = *(int *)((char *)&obj + *(int *)((char *)(DAT_00586dc8[0]) + 916));
    *(int **)&obj._vtable = &DAT_0052c8b0[0];
    if (&obj._filters != 0) {
        o = (igObject *)obj._filters;
        if (o != 0) {
            o->_refCount = o->_refCount - 1;
            if ((o->_refCount & 0x7FFFFF) == 0) {
                igObject_Destroy(o);
            }
        }
    }
    if (&obj._defaultFilters != 0) {
        o = (igObject *)obj._defaultFilters;
        if (o != 0) {
            o->_refCount = o->_refCount - 1;
            if ((o->_refCount & 0x7FFFFF) == 0) {
                igObject_Destroy(o);
            }
        }
    }
    return t;
}

void FUN_00231f40(void)
{
    igMetaObject_RunStaticInit(igFilterMessageDispatcher_Register);
}

void igFilterMessageDispatcher_Register(void) {
    InsightLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igFilterMessageDispatcher_metaObject,
        igMessageDispatcher_Register,
        igMessageDispatcher_GetPublishedMetaObject,
        thunk_igFilterMessageDispatcher_GetMetaObject,
        igFilterMessageDispatcher_className,
        0x10, /* instance size */
        igFilterMessageDispatcher_GetVTable,
        &igFilterMessageDispatcher_InitFields,
        0, /* extra callback item */
        g_igFilterMessageDispatcher_callbackList /* callback list */
    );
}

void thunk_igFilterMessageDispatcher_GetMetaObject(void) {
    igFilterMessageDispatcher_GetMetaObject();
}

int FUN_00231fe0(void) {
    return DAT_0056db28[0];
}

void igFilterMessageDispatcher_InitFields(void) {
    int temp_s2;
    void *temp_s1_2;
    void *temp_s1;
    void *temp_s0;

    temp_s0 = (void *)DAT_0056db10[0];
    temp_s2 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &DAT_00498020[0], 2);
    temp_s1 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2));
    ((igObjectRefMetaField *)temp_s1)->_metaObject = FUN_002319d0();
    ((igRefMetaField *)temp_s1)->_construct = 1;
    temp_s1_2 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 1));
    ((igObjectRefMetaField *)temp_s1_2)->_metaObject = FUN_002319d0();
    ((igRefMetaField *)temp_s1_2)->_construct = 1;
    igMetaObject_NameFields(temp_s0, &DAT_00498028[0], &DAT_00498030[0], &DAT_00498038[0], temp_s2);
}

int FUN_002320b0(void) {
    if (DAT_0056db28[0] == 0) {
        DAT_0056db28[0] = igMetaObject_Create(Memory_GetAllocatorBySelector(DAT_00587040[0]));
    }
    return DAT_0056db28[0];
}

igMetaObject *igMessageDispatcher_GetMetaObject(void)
{
    igMetaObject *g = g_igMessageDispatcher_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_00232150();
    return g_igMessageDispatcher_metaObject[0];
}

void FUN_00232150(void)
{
    igMetaObject_RunStaticInit(igMessageDispatcher_Register);
}

void igMessageDispatcher_Register(void) {
    InsightLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        1, /* abstract */
        g_igMessageDispatcher_metaObject,
        igObject_Register,
        igObject_GetMetaObject_ParentAccessor,
        thunk_igMessageDispatcher_GetMetaObject,
        igMessageDispatcher_className,
        8, /* instance size */
        0,
        &igMessageDispatcher_SetAbstractProxy_002321e0[0], /* post-init hook */
        0, /* extra callback item */
        0 /* callback list */
    );
}

void thunk_igMessageDispatcher_GetMetaObject(void) {
    igMessageDispatcher_GetMetaObject();
}

void FUN_002321e0(void) {
    *(int *)((char *)(DAT_0056db28[0]) + 60) = (int)(&thunk_igFilterMessageDispatcher_GetMetaObject);
}

void FUN_00232200(int arg0) {
    FUN_00232320();
    igMetaObject_CreateInstance(*(int *)0x56DB30, arg0);
}

igMetaObject *igMessageDefaultReceiver_GetMetaObject(void)
{
    unsigned char ready;
    if (g_igMessageDefaultReceiver_metaObject[0] != 0) {
        ready = (g_igMessageDefaultReceiver_metaObject[0]->_validity & 4) != 0;
        if (ready != 0) goto done;
    }
    FUN_00232320();
done:
    return g_igMessageDefaultReceiver_metaObject[0];
}

int igMessageDefaultReceiver_GetVTable(void) {
    union U_232290 u;
    int temp_s0;
    char *ps;
    int *p;
    int v;
    igObject_InitHeader(u.b);
    u.vt = (int)&DAT_0052c930[0];
    ps = &u.b[8];
    *(int *)ps = 0;
    temp_s0 = *(int *)&u.b[*(int *)((char *)(DAT_00586dc8[0]) + 916)];
    u.vt = (int)&DAT_0052c930[0];
    if (ps != 0) {
        p = *(int **)ps;
        if (p != 0) {
            v = p[1] - 1;
            p[1] = v;
            if ((p[1] & 0x7fffff) == 0) {
                igObject_Destroy(p);
            }
        }
    }
    return temp_s0;
}

void FUN_00232320(void)
{
    igMetaObject_RunStaticInit(igMessageDefaultReceiver_Register);
}

void igMessageDefaultReceiver_Register(void) {
    InsightLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igMessageDefaultReceiver_metaObject,
        igMessageReceiver_Register,
        igMessageReceiver_GetPublishedMetaObject,
        thunk_igMessageDefaultReceiver_GetMetaObject,
        igMessageDefaultReceiver_className,
        0x18, /* instance size */
        igMessageDefaultReceiver_GetVTable,
        &igMessageDefaultReceiver_InitFields,
        0, /* extra callback item */
        g_igMessageDefaultReceiver_callbackList /* callback list */
    );
}

void thunk_igMessageDefaultReceiver_GetMetaObject(void) {
    igMessageDefaultReceiver_GetMetaObject();
}

int FUN_002323c0(void) {
    return DAT_0056dae8[0];
}

void igMessageDefaultReceiver_InitFields(void) {
    int temp_s0;
    int temp_s1;
    char *p;

    temp_s0 = DAT_0056db30[0];
    temp_s1 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &DAT_00498048[0], 2);
    p = (char *)igMetaObject_GetFieldAt(temp_s0, temp_s1);
    *(int *)(p + 56) = (int)DAT_00587198[0];
    p = (char *)igMetaObject_GetFieldAt(temp_s0, temp_s1 + 1);
    *(short *)(p + 20) = 0xC;
    igMetaObject_NameFields(temp_s0, &DAT_00498050[0], &DAT_00498058[0], &DAT_00498060[0], temp_s1);
}

int FUN_00232470(void) {
    if (DAT_0056db48[0] == 0) {
        DAT_0056db48[0] = igMetaObject_Create(Memory_GetAllocatorBySelector(DAT_00587040[0]));
    }
    return DAT_0056db48[0];
}

igMetaObject *igInsightScheduler_GetMetaObject(void)
{
    igMetaObject *g = g_igInsightScheduler_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_00232510();
    return g_igInsightScheduler_metaObject[0];
}

void FUN_00232510(void)
{
    igMetaObject_RunStaticInit(igInsightScheduler_Register);
}

void igInsightScheduler_Register(void) {
    InsightLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        1, /* abstract */
        g_igInsightScheduler_metaObject,
        igObject_Register,
        igObject_GetMetaObject_ParentAccessor,
        thunk_igInsightScheduler_GetMetaObject,
        igInsightScheduler_className,
        8, /* instance size */
        0,
        &igInsightScheduler_SetAbstractProxy_002325a0[0], /* post-init hook */
        0, /* extra callback item */
        0 /* callback list */
    );
}

void thunk_igInsightScheduler_GetMetaObject(void) {
    igInsightScheduler_GetMetaObject();
}

void FUN_002325a0(void) {
    *(int *)((char *)(DAT_0056db48[0]) + 60) = (int)(&thunk_igSerialScheduler_GetMetaObject);
}

int FUN_002325c0(void) {
    if (DAT_0056db50[0] == 0) {
        DAT_0056db50[0] = igMetaObject_Create(Memory_GetAllocatorBySelector(DAT_00587040[0]));
    }
    return DAT_0056db50[0];
}

igMetaObject *igInsightPluginList_GetMetaObject(void)
{
    igMetaObject *g = g_igInsightPluginList_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_002326a0();
    return g_igInsightPluginList_metaObject[0];
}

int igInsightPluginList_GetVTable(void) {
    struct Obj_232660 obj;

    igObject_InitHeader(&obj);
    obj.vt = &DAT_0052cd70[0];
    return *(int *)((char *)&obj + *(int *)((char *)(DAT_00586dc8[0]) + 916));
}

void FUN_002326a0(void)
{
    igMetaObject_RunStaticInit(igInsightPluginList_Register);
}

void igInsightPluginList_Register(void) {
    InsightLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igInsightPluginList_metaObject,
        igObjectList_Register,
        igObjectList_GetPublishedMetaObject,
        thunk_igInsightPluginList_GetMetaObject,
        igInsightPluginList_className,
        0x14, /* instance size */
        igInsightPluginList_GetVTable,
        0,
        0, /* extra callback item */
        g_igInsightPluginList_callbackList /* callback list */
    );
}

void thunk_igInsightPluginList_GetMetaObject(void) {
    igInsightPluginList_GetMetaObject();
}

igMetaObject *igInsightPlugin_GetMetaObject(void)
{
    igMetaObject *g = g_igInsightPlugin_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_00232780();
    return g_igInsightPlugin_metaObject[0];
}

void FUN_00232780(void)
{
    igMetaObject_RunStaticInit(igInsightPlugin_Register);
}

void igInsightPlugin_Register(void) {
    InsightLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        1, /* abstract */
        g_igInsightPlugin_metaObject,
        igObject_Register,
        igObject_GetMetaObject_ParentAccessor,
        thunk_igInsightPlugin_GetMetaObject,
        igInsightPlugin_className,
        8, /* instance size */
        0,
        0,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void thunk_igInsightPlugin_GetMetaObject(void) {
    igInsightPlugin_GetMetaObject();
}

void FUN_00232800(int arg0) {
    FUN_00232de0();
    igMetaObject_CreateInstance(*(int *)0x56DB60, arg0);
}

int FUN_00232840(void) {
    if (DAT_0056db60[0] == 0) {
        DAT_0056db60[0] = igMetaObject_Create(Memory_GetAllocatorBySelector(DAT_00587040[0]));
    }
    return DAT_0056db60[0];
}

igMetaObject *igInsightCore_GetMetaObject(void)
{
    igMetaObject *g = g_igInsightCore_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_00232de0();
    return g_igInsightCore_metaObject[0];
}

int igInsightCore_GetVTable(void) {
    struct Obj_2328e0 obj;
    int t;
    igObject_InitHeader(&obj);
    obj.vt = &DAT_0052c990[0];
    obj.w2 = 0;
    obj.w3 = 0;
    obj.w4 = 0;
    obj.w5 = 0;
    obj.w6 = 0;
    obj.w7 = 0;
    obj.w8 = 0;
    obj.w9 = 0;
    obj.w10 = 0;
    obj.w11 = 0;
    obj.w12 = 0;
    obj.w26 = 0;
    t = *(int *)((char *)&obj + *(int *)((char *)(DAT_00586dc8[0]) + 916));
    obj.vt = &DAT_0052c990[0];
    FUN_00232d60((struct R **)&obj.w26, -1);
    FUN_00150a70(&obj.w12, -1);
    FUN_00232ce0((ObjectRefWord *)&obj.w11, -1);
    FUN_00232c60((void **)&obj.w10, -1);
    FUN_00232be0((ObjectRefWord *)&obj.w9, -1);
    FUN_00232b60((void **)&obj.w8, -1);
    FUN_00232ae0((ObjectRefWord *)&obj.w7, -1);
    FUN_00130140(&obj.w6, -1);
    FUN_00143350(&obj.w5, -1);
    FUN_001d35d0(&obj.w4, -1);
    FUN_00232a60((O *)&obj.w3, -1);
    FUN_00231210((void **)&obj.w2, -1);
    return t;
}

O *FUN_00232a60(O *arg0, short arg1) {
    if (arg0) {
        S_temp_a0 *t = arg0->m;
        if (t) { t->f4 -= 1; if ((t->f4 & 0x7fffff) == 0) igObject_Destroy(t); }
        if (arg1 > 0) FUN_00100610(arg0);
    }
    return arg0;
}

ObjectRefWord *FUN_00232ae0(ObjectRefWord *self,int delete_storage) {
    if(self) {
        ObjectRefTarget *object=self->value;
        if(object) {
            --object->references;
            if(((unsigned long long)(long long)object->references & 0x7fffffULL)==0)
                igObject_Destroy(object);
        }
        if((short)delete_storage>0) FUN_00100610(self);
    }
    return self;
}

void **FUN_00232b60(void **arg0, short arg1) {
    S_temp_a0_232b60 *temp_a0;

    if (arg0 != 0) {
        temp_a0 = (S_temp_a0_232b60 *)(*arg0);
        if (temp_a0 != 0) {
            temp_a0->f4 = (int)((int) (temp_a0->f4 - 1));
            if ((temp_a0->f4 & 0x7FFFFF) == 0) {
                igObject_Destroy(temp_a0);
            }
        }
        if (arg1 > 0) {
            FUN_00100610(arg0);
        }
    }
    return arg0;
}

ObjectRefWord *FUN_00232be0(ObjectRefWord *self,int delete_storage) {
    if(self) {
        ObjectRefTarget *object=self->value;
        if(object) {
            --object->references;
            if(((unsigned long long)(long long)object->references & 0x7fffffULL)==0)
                igObject_Destroy(object);
        }
        if((short)delete_storage>0) FUN_00100610(self);
    }
    return self;
}

void **FUN_00232c60(void **arg0, short arg1) {
    int *r;
    if (arg0 != 0) {
        r = (int *)*arg0;
        if (r != 0) {
            r[1] = r[1] - 1;
            if ((r[1] & 0x7fffff) == 0) {
                igObject_Destroy(r);
            }
        }
        if (arg1 > 0) {
            FUN_00100610(arg0);
        }
    }
    return arg0;
}

ObjectRefWord *FUN_00232ce0(ObjectRefWord *self,int delete_storage) {
    if(self) {
        ObjectRefTarget *object=self->value;
        if(object) {
            --object->references;
            if(((unsigned long long)(long long)object->references & 0x7fffffULL)==0)
                igObject_Destroy(object);
        }
        if((short)delete_storage>0) FUN_00100610(self);
    }
    return self;
}

struct R **FUN_00232d60(struct R **arg0, short arg1) {
    struct R *temp_a0;

    if (arg0 != 0) {
        temp_a0 = *arg0;
        if (temp_a0 != 0) {
            temp_a0->rc = temp_a0->rc - 1;
            if ((temp_a0->rc & 0x7FFFFF) == 0) {
                igObject_Destroy(temp_a0);
            }
        }
        if (arg1 > 0) {
            FUN_00100610(arg0);
        }
    }
    return arg0;
}

void FUN_00232de0(void)
{
    igMetaObject_RunStaticInit(igInsightCore_Register);
}

void igInsightCore_Register(void) {
    InsightLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igInsightCore_metaObject,
        igObject_Register,
        igObject_GetMetaObject_ParentAccessor,
        thunk_igInsightCore_GetMetaObject,
        igInsightCore_className,
        0x70, /* instance size */
        igInsightCore_GetVTable,
        &igInsightCore_InitFields,
        thunk_FUN_00236140, /* extra callback item */
        g_igInsightCore_callbackList /* callback list */
    );
}

void thunk_igInsightCore_GetMetaObject(void) {
    igInsightCore_GetMetaObject();
}

void igInsightCore_InitFields(void) {
    int temp_s1;
    void *temp_s2;
    void *temp_s2_10;
    void *temp_s2_11;
    void *temp_s2_12;
    void *temp_s2_2;
    void *temp_s2_3;
    void *temp_s2_4;
    void *temp_s2_5;
    void *temp_s2_6;
    void *temp_s2_7;
    void *temp_s2_8;
    void *temp_s2_9;
    void *temp_s0;

    temp_s0 = (void *)DAT_0056db60[0];
    temp_s1 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &DAT_004980b0[0], 0x13);
    temp_s2 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s1));
    ((igObjectRefMetaField *)temp_s2)->_metaObject = FUN_00233480();
    ((igRefMetaField *)temp_s2)->_construct = 1;
    temp_s2_2 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s1 + 1));
    ((igObjectRefMetaField *)temp_s2_2)->_metaObject = FUN_00232470();
    ((igRefMetaField *)temp_s2_2)->_construct = 1;
    temp_s2_3 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s1 + 2));
    ((igObjectRefMetaField *)temp_s2_3)->_metaObject = FUN_002c3440();
    ((igRefMetaField *)temp_s2_3)->_construct = 1;
    temp_s2_4 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s1 + 3));
    ((igObjectRefMetaField *)temp_s2_4)->_metaObject = FUN_00145d40();
    temp_s2_5 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s1 + 4));
    ((igObjectRefMetaField *)temp_s2_5)->_metaObject = FUN_0014a040();
    temp_s2_6 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s1 + 5));
    ((igObjectRefMetaField *)temp_s2_6)->_metaObject = FUN_0044c4d0();
    ((igRefMetaField *)temp_s2_6)->_construct = 1;
    temp_s2_7 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s1 + 6));
    ((igObjectRefMetaField *)temp_s2_7)->_metaObject = FUN_004513b0();
    ((igRefMetaField *)temp_s2_7)->_construct = 1;
    temp_s2_8 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s1 + 7));
    ((igObjectRefMetaField *)temp_s2_8)->_metaObject = FUN_00233080();
    ((igRefMetaField *)temp_s2_8)->_construct = 1;
    temp_s2_9 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s1 + 8));
    ((igObjectRefMetaField *)temp_s2_9)->_metaObject = FUN_00231400();
    ((igRefMetaField *)temp_s2_9)->_construct = 1;
    temp_s2_10 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s1 + 9));
    ((igObjectRefMetaField *)temp_s2_10)->_metaObject = FUN_0044c250();
    ((igRefMetaField *)temp_s2_10)->_construct = 1;
    temp_s2_11 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s1 + 0xA));
    ((igObjectRefMetaField *)temp_s2_11)->_metaObject = FUN_002b7a10();
    ((igRefMetaField *)temp_s2_11)->_construct = 1;
    temp_s2_12 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s1 + 0x12));
    ((igObjectRefMetaField *)temp_s2_12)->_metaObject = FUN_002325c0();
    ((igRefMetaField *)temp_s2_12)->_construct = 1;
    igMetaObject_NameFields(temp_s0, &DAT_00498100[0], &DAT_00498150[0], &DAT_004981a0[0], temp_s1);
}

void thunk_FUN_00236140(void) {
    FUN_00236140();
}

int FUN_00233080(void) {
    if (DAT_0056dc00[0] == 0) {
        DAT_0056dc00[0] = igMetaObject_Create(Memory_GetAllocatorBySelector(DAT_00587040[0]));
    }
    return DAT_0056dc00[0];
}

igMetaObject *igWindowResizeEventReceiver_GetMetaObject(void)
{
    igMetaObject *g = g_igWindowResizeEventReceiver_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_00233160();
    return g_igWindowResizeEventReceiver_metaObject[0];
}

int igWindowResizeEventReceiver_GetVTable(void) {
    struct Obj_233120 o;
    igObject_InitHeader(&o);
    o.vt = &DAT_0052c9f0[0];
    return *(int *)((char *)&o + *(int *)((char *)(DAT_00586dc8[0]) + 916));
}

void FUN_00233160(void)
{
    igMetaObject_RunStaticInit(igWindowResizeEventReceiver_Register);
}

void igWindowResizeEventReceiver_Register(void) {
    InsightLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igWindowResizeEventReceiver_metaObject,
        igEventReceiver_Register,
        igEventReceiver_GetPublishedMetaObject,
        thunk_igWindowResizeEventReceiver_GetMetaObject,
        igWindowResizeEventReceiver_className,
        0xC, /* instance size */
        igWindowResizeEventReceiver_GetVTable,
        &igWindowResizeEventReceiver_InitFields,
        0, /* extra callback item */
        g_igWindowResizeEventReceiver_callbackList /* callback list */
    );
}

void thunk_igWindowResizeEventReceiver_GetMetaObject(void) {
    igWindowResizeEventReceiver_GetMetaObject();
}

int FUN_00233200(void) {
    return DAT_0058c570[0];
}

void igWindowResizeEventReceiver_InitFields(void) {
    int temp_s2;
    void *temp_s1;
    void *temp_s0;

    temp_s0 = (void *)DAT_0056dc00[0];
    temp_s2 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &DAT_004981f8[0], 1);
    temp_s1 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2));
    ((igObjectRefMetaField *)temp_s1)->_metaObject = FUN_00232840();
    ((igObjectRefMetaField *)temp_s1)->_refCounted = 0;
    igMetaObject_NameFields(temp_s0, &DAT_00498200[0], &DAT_00498208[0], &DAT_00498210[0], temp_s2);
}

int FUN_002332b0(int arg0) {
    FUN_00233380();
    return igMetaObject_CreateInstance(*(int *)0x56DC10, arg0);
}

igMetaObject *igViewportResizedMessage_GetMetaObject(void)
{
    igMetaObject *g = g_igViewportResizedMessage_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_00233380();
    return g_igViewportResizedMessage_metaObject[0];
}

int igViewportResizedMessage_GetVTable(void) {
    struct Obj_233340 obj;

    igObject_InitHeader(&obj);
    obj.vt = &DAT_0052cc80[0];
    return *(int *)((char *)&obj + *(int *)((char *)(DAT_00586dc8[0]) + 916));
}

void FUN_00233380(void)
{
    igMetaObject_RunStaticInit(igViewportResizedMessage_Register);
}

void igViewportResizedMessage_Register(void) {
    InsightLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igViewportResizedMessage_metaObject,
        igMessage_Register,
        igMessage_GetPublishedMetaObject,
        thunk_igViewportResizedMessage_GetMetaObject,
        igViewportResizedMessage_className,
        0x18, /* instance size */
        igViewportResizedMessage_GetVTable,
        &igViewportResizedMessage_InitFields,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void thunk_igViewportResizedMessage_GetMetaObject(void) {
    igViewportResizedMessage_GetMetaObject();
}

void igViewportResizedMessage_InitFields(void) {
    int temp_s1;
    void *temp_s0;

    temp_s0 = (void *)DAT_0056dc10[0];
    temp_s1 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &DAT_00498218[0], 2);
    igMetaObject_NameFields(temp_s0, &DAT_00498220[0], &DAT_00498228[0], &DAT_00498230[0], temp_s1);
}

int FUN_00233480(void) {
    if (DAT_0056dc28[0] == 0) {
        DAT_0056dc28[0] = igMetaObject_Create(Memory_GetAllocatorBySelector(DAT_00587040[0]));
    }
    return DAT_0056dc28[0];
}

igMetaObject *igInfoManagerOrderedList_GetMetaObject(void)
{
    igMetaObject *g = g_igInfoManagerOrderedList_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_002336b0();
    return g_igInfoManagerOrderedList_metaObject[0];
}

int igInfoManagerOrderedList_GetVTable(void) {
    Obj_233520 o;
    int r;

    igObject_InitHeader(&o);
    o.w[1] = 0;
    o.w[2] = 0;
    o.w[3] = 0;
    o.w[4] = 0;
    o.vt = &DAT_0052cb60[0];
    r = *(int *)((char *)&o + *(int *)((char *)(DAT_00586dc8[0]) + 916));
    o.vt = &DAT_0052cb60[0];
    FUN_00233610((int **)&o, 0);
    return r;
}

ObjectRefWord *FUN_00233590(ObjectRefWord *self,int delete_storage) {
    if(self) {
        ObjectRefTarget *object=self->value;
        if(object) {
            --object->references;
            if(((unsigned long long)(long long)object->references & 0x7fffffULL)==0)
                igObject_Destroy(object);
        }
        if((short)delete_storage>0) FUN_00100610(self);
    }
    return self;
}

int **FUN_00233610(int **arg0, long long arg1) {
    if (arg0 != 0) {
        *arg0 = &DAT_0052cbc0[0];
        if (arg0 != 0) {
            *arg0 = &DAT_0052cc20[0];
            ObjectRef_Destruct_001c6460((int **)((char *)arg0 + 0x14), -1);
            FUN_00135430((int **)((char *)arg0 + 0x10), -1);
            FUN_00233590((ObjectRefWord *)((char *)arg0 + 0xC), -1);
            FUN_0014aa70((int **)((char *)arg0 + 8), -1);
        }
        if (((long long) (arg1 << 0x30) >> 0x30) > 0) {
            thunk_FUN_002ed460__002ff810(arg0);
        }
    }
    return arg0;
}

void FUN_002336b0(void)
{
    igMetaObject_RunStaticInit(igInfoManagerOrderedList_Register);
}

void igInfoManagerOrderedList_Register(void) {
    InsightLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igInfoManagerOrderedList_metaObject,
        igDependencyOrderedList_Register,
        igDependencyOrderedList_GetPublishedMetaObject,
        thunk_igInfoManagerOrderedList_GetMetaObject,
        igInfoManagerOrderedList_className,
        0x1C, /* instance size */
        igInfoManagerOrderedList_GetVTable,
        0,
        0, /* extra callback item */
        g_igInfoManagerOrderedList_callbackList /* callback list */
    );
}

void thunk_igInfoManagerOrderedList_GetMetaObject(void) {
    igInfoManagerOrderedList_GetMetaObject();
}

int FUN_00233740(void) {
    return DAT_00586738[0];
}

int FUN_00233750(void) {
    if (DAT_0056dc30[0] == 0) {
        DAT_0056dc30[0] = igMetaObject_Create(Memory_GetAllocatorBySelector(DAT_00587040[0]));
    }
    return DAT_0056dc30[0];
}

igMetaObject *igInfoManagerList_GetMetaObject(void)
{
    igMetaObject *g = g_igInfoManagerList_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_00233830();
    return g_igInfoManagerList_metaObject[0];
}

int igInfoManagerList_GetVTable(void) {
    struct Obj_2337f0 obj;

    igObject_InitHeader(&obj);
    obj.vt = &DAT_0052caf0[0];
    return *(int *)((char *)&obj + *(int *)((char *)(DAT_00586dc8[0]) + 916));
}

void FUN_00233830(void)
{
    igMetaObject_RunStaticInit(igInfoManagerList_Register);
}

void igInfoManagerList_Register(void) {
    InsightLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igInfoManagerList_metaObject,
        igObjectList_Register,
        igObjectList_GetPublishedMetaObject,
        thunk_igInfoManagerList_GetMetaObject,
        igInfoManagerList_className,
        0x14, /* instance size */
        igInfoManagerList_GetVTable,
        0,
        0, /* extra callback item */
        g_igInfoManagerList_callbackList /* callback list */
    );
}

void thunk_igInfoManagerList_GetMetaObject(void) {
    igInfoManagerList_GetMetaObject();
}

igMetaObject *igInfoManager_GetMetaObject(void)
{
    igMetaObject *g = g_igInfoManager_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_00233910();
    return g_igInfoManager_metaObject[0];
}

void FUN_00233910(void)
{
    igMetaObject_RunStaticInit(igInfoManager_Register);
}

void igInfoManager_Register(void) {
    InsightLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        1, /* abstract */
        g_igInfoManager_metaObject,
        igNamedObject_Register,
        igNamedObject_GetPublishedMetaObject,
        thunk_igInfoManager_GetMetaObject,
        igInfoManager_className,
        0x10, /* instance size */
        0,
        &igInfoManager_InitFields,
        0, /* extra callback item */
        g_igInfoManager_callbackList /* callback list */
    );
}

void thunk_igInfoManager_GetMetaObject(void) {
    igInfoManager_GetMetaObject();
}

void igInfoManager_InitFields(void) {
    int temp_s2;
    void *temp_s1;
    void *temp_s0;

    temp_s0 = (void *)DAT_0056dc38[0];
    temp_s2 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &DAT_00498250[0], 1);
    temp_s1 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2));
    ((igObjectRefMetaField *)temp_s1)->_metaObject = FUN_00232840();
    ((igObjectRefMetaField *)temp_s1)->_refCounted = 0;
    igMetaObject_NameFields(temp_s0, &DAT_00498258[0], &DAT_00498260[0], &DAT_00498268[0], temp_s2);
}

int FUN_00233a40(void) {
    if (DAT_0056dc48[0] == 0) {
        DAT_0056dc48[0] = igMetaObject_Create(Memory_GetAllocatorBySelector(DAT_00587040[0]));
    }
    return DAT_0056dc48[0];
}

/* Registers the class first when the slot is empty or its igMetaObject._validity (+36) lacks the
 * ready bit (mask 4), then returns the published MetaObject. */
igMetaObject *igFlushRenderer_GetMetaObject(void)
{
    unsigned char ready;
    if (g_igFlushRenderer_metaObject[0] != 0) {
        ready = (g_igFlushRenderer_metaObject[0]->_validity & 4) != 0;
        if (ready != 0) goto done;
    }
    FUN_00233b80();
done:
    return g_igFlushRenderer_metaObject[0];
}

int igFlushRenderer_GetVTable(void) {
    union U_233a90 u;
    int temp_s0;
    S_ref *q1;


    igObject_InitHeader(u.b);
    u.w[0] = (int)(&DAT_0052d060[0]);
    q1 = (S_ref *)&u.b[8];
    *(int *)q1 = 0;
    u.w[0] = (int)(&DAT_0052ca80[0]);
    temp_s0 = *(int *)&u.b[*(int *)((char *)(DAT_00586dc8[0]) + 916)];
    u.w[0] = (int)(&DAT_0052d060[0]);
    if (q1 != 0) {
        q1 = *(S_ref **)q1;
        if (q1 != 0) {
            q1->f4 = (int)((int) (q1->f4 - 1));
            if (((unsigned long long) ((long long) q1->f4 << 0x29) >> 0x29) == 0) {
                igObject_Destroy(q1);
            }
        }
    }
    return temp_s0;
}

void FUN_00233b80(void)
{
    igMetaObject_RunStaticInit(igFlushRenderer_Register);
}

void igFlushRenderer_Register(void) {
    InsightLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igFlushRenderer_metaObject,
        igRenderer_Register,
        igRenderer_GetPublishedMetaObject,
        thunk_igFlushRenderer_GetMetaObject,
        igFlushRenderer_className,
        0xC, /* instance size */
        igFlushRenderer_GetVTable,
        0,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void thunk_igFlushRenderer_GetMetaObject(void) {
    igFlushRenderer_GetMetaObject();
}

static inline int countOf(const IntList *list) { return list->count; }

/* The Alchemy viewer's usage / option help printer: prints the banner and then one help entry per
 * command-line option (name, description and default value) through five typed helpers (bool, int,
 * float, vec3, vec4) that format the entry with printf. Each entry is guarded by `if (name)`: the
 * literal's address is tested against zero, so the guard comes from the option macro, not from the
 * data. Argument: the program name for the USAGE line. */




void FUN_00233c10(const char *programName)
{
    /* matching construct: variant search — declaration order of the local arrays; b52 gives the first-declared array the highest stack slot */
    float defaultUpVector[3];
    float defaultNormalsColor[4];
    float defaultInvalidNormalsColor[4];
    float defaultScaledNormalsColor[4];
    float defaultHeadLightDiffuse[4];
    float defaultHeadLightSpecular[4];
    float defaultHeadLightAmbient[4];
    float defaultClearColor[4];
    printf(usage_s_option1_option2_n_number_f, programName);
    printf(n_number_loads_n_instances_of_the_);
    printf(possible_options_are);
    printf(help_prints_this_message);
    printf(nologo_removes_the_logo_display);
    OPTION_BOOL(showBbox, show_bounding_box_on_selected_obje, 1);
    OPTION_BOOL(showNormals, show_normals_on_selected_object, 0.0f);
    if (normalsColor) {
        defaultNormalsColor[0] = 0.0f;
        defaultNormalsColor[1] = 1.0f;
        defaultNormalsColor[2] = 0.0f;
        defaultNormalsColor[3] = 1.0f;
        FUN_002343d0(normalsColor, sets_the_normals_color, defaultNormalsColor);
    }
    if (invalidStoredNormalsColor) {
        defaultInvalidNormalsColor[0] = 1.0f;
        defaultInvalidNormalsColor[1] = 0.5f;
        defaultInvalidNormalsColor[2] = 0.0f;
        defaultInvalidNormalsColor[3] = 1.0f;
        FUN_002343d0(invalidStoredNormalsColor, sets_the_non_normalized_stored_nor, defaultInvalidNormalsColor);
    }
    if (scaledNormalsColor) {
        defaultScaledNormalsColor[0] = 1.0f;
        defaultScaledNormalsColor[1] = 0.0f;
        defaultScaledNormalsColor[2] = 0.0f;
        defaultScaledNormalsColor[3] = 1.0f;
        FUN_002343d0(scaledNormalsColor, sets_the_scaled_normals_color, defaultScaledNormalsColor);
    }
    OPTION_FLOAT(invalidNormalsPrecision, sets_the_precision_on_the_normals_, 0.00100000005f);
    OPTION_BOOL(autoSelectCamera, select_the_first_camera_if_any_in_, 1);
    OPTION_FLOAT(hfov, sets_the_horizontal_field_of_view, 45.0f);
    OPTION_BOOL(autoPlanes, find_automatically_near_and_far_cl, 1);
    OPTION_FLOAT(nearPlane, sets_the_default_near_clipping_pla, 0.100000001f);
    OPTION_FLOAT(farPlane, sets_the_default_far_clipping_plan, 1000.0f);
    if (upVector) {
        defaultUpVector[0] = g_vec3Zero[0];
        defaultUpVector[1] = g_vec3Zero[1];
        defaultUpVector[2] = g_vec3Zero[2];
        FUN_00234350(upVector, sets_the_default_up_vector_0_0_0_m, defaultUpVector);
    }
    OPTION_BOOL(autoSceneLights, sets_automatic_usage_of_scene_ligh, 1);
    OPTION_BOOL(autoHeadLight, sets_automatic_usage_of_head_light, 0.0f);
    OPTION_BOOL(useSceneLights, use_scene_lights_if_not_automatic, 0.0f);
    OPTION_BOOL(useHeadLight, enable_head_light_if_not_automatic, 0.0f);
    OPTION_BOOL(useHeadLightSpecular, use_specular_head_light, 0.0f);
    if (headLightDiffuse) {
        defaultHeadLightDiffuse[0] = 1.0f;
        defaultHeadLightDiffuse[1] = 1.0f;
        defaultHeadLightDiffuse[2] = 1.0f;
        defaultHeadLightDiffuse[3] = 1.0f;
        FUN_002343d0(headLightDiffuse, sets_the_diffuse_color_for_the_hea, defaultHeadLightDiffuse);
    }
    if (headLightSpecular) {
        defaultHeadLightSpecular[0] = 1.0f;
        defaultHeadLightSpecular[1] = 1.0f;
        defaultHeadLightSpecular[2] = 1.0f;
        defaultHeadLightSpecular[3] = 1.0f;
        FUN_002343d0(headLightSpecular, sets_the_specular_color_for_the_he, defaultHeadLightSpecular);
    }
    if (headLightAmbient) {
        defaultHeadLightAmbient[0] = g_vec4Zero[0];
        defaultHeadLightAmbient[1] = g_vec4Zero[1];
        defaultHeadLightAmbient[2] = g_vec4Zero[2];
        defaultHeadLightAmbient[3] = g_vec4Zero[3];
        FUN_002343d0(headLightAmbient, sets_the_ambient_color_for_the_hea, defaultHeadLightAmbient);
    }
    if (clearColor) {
        defaultClearColor[0] = 0.200000003f;
        defaultClearColor[1] = 0.200000003f;
        defaultClearColor[2] = 0.200000003f;
        defaultClearColor[3] = 1.0f;
        FUN_002343d0(clearColor, sets_the_clear_color, defaultClearColor);
    }
    OPTION_BOOL(wireframeMode, sets_wireframe_mode, 0.0f);
    OPTION_BOOL(forceWireframe, force_wireframe_on_all_geometries, 0.0f);
    OPTION_BOOL(backfaceCullingMode, sets_back_face_culling_mode, 0.0f);
    OPTION_BOOL(forceBackfaceCulling, force_back_face_culling_on_all_geo, 0.0f);
    OPTION_BOOL(alphaTest, sets_alpha_test_state, 0.0f);
    OPTION_BOOL(forceAlphaTest, force_alpha_test_on_all_geometries, 0.0f);
    OPTION_FLOAT(alphaTestReference, sets_alpha_test_reference_value, 0.100000001f);
    OPTION_FLOAT(maximumFrameRate, sets_the_maximum_frame_rate_0_mean, 0.0f);
    OPTION_BOOL(optimizeTextures, share_textures_at_load_time, 1);
    OPTION_BOOL(halfBuffer, sets_psx2_half_buffer_mode, 0.0f);
    OPTION_BOOL(palVideoMode, sets_pal_video_mode, 0.0f);
    OPTION_INT(width, viewer_window_width, 640);
    OPTION_INT(height, viewer_window_height, 448);
    OPTION_INT(swapInterval, sets_the_swap_interval_0_means_no_, 0.0f);
    OPTION_INT(colorBits, sets_color_buffer_bits_1_means_def, -1);
    OPTION_INT(alphaBits, sets_alpha_buffer_bits_1_means_def, -1);
    OPTION_INT(depthBits, sets_depth_buffer_bits_1_means_def, -1);
    OPTION_INT(stencilBits, sets_stencil_buffer_bits_1_means_d, -1);
    OPTION_BOOL(reportVideoFormat, if_set_reports_requested_and_actua, 1);
    OPTION_BOOL(showLogo, shows_alchemy_logo, 1);
    OPTION_BOOL(showUi, sets_initial_gui_visibility, 1);
    OPTION_BOOL(enableMayaControls, enables_or_disable_maya_controls, 0.0f);
    OPTION_BOOL(benchmark, enables_or_disable_the_benchmark_m, 0.0f);
    OPTION_INT(benchmarkSkipFrames, sets_the_number_of_frames_to_skip_, 5);
    OPTION_INT(benchmarkFrames, sets_the_number_of_frames_to_bench, 30);
    OPTION_BOOL(columnStatistics, output_statistics_to_console_in_co, 0.0f);
    OPTION_BOOL(allocateVisualContextInScratchpad, allocate_visual_context_from_scrat, 0.0f);
}

void FUN_002342b0(const char *arg0, const char *arg1, int arg2) {
    int *var_a3;

    if (arg2 != 0) {
        var_a3 = &DAT_004e95f8[0];
    } else {
        var_a3 = &DAT_004e9600[0];
    }
    printf(&DAT_004e95d0[0], arg0, arg1, var_a3);
}

void FUN_002342e0(const char *arg0, const char *arg1, int arg2) {
    printf(&DAT_004e9610[0], arg0, arg1, arg2);
}

void FUN_00234300(const char *arg0, const char *arg1, float arg2) {
    printf(&DAT_004e9630[0], arg0, arg1, fptodp(arg2));
}

void FUN_00234350(const char *arg0, const char *arg1, float *arg2) {
    /* matching construct: variant search — declaration order of the locals; b52 gives the last-declared local s0 */
    int temp_s1;
    int temp_s0;

    temp_s1 = fptodp(arg2[0]);
    temp_s0 = fptodp(arg2[1]);
    printf(&DAT_004e9650[0], arg0, arg1, temp_s1, temp_s0, fptodp(arg2[2]));
}

void FUN_002343d0(const char *arg0, const char *arg1, float *arg2) {
    /* matching construct: variant search — declaration order of the locals; b52 gives the last-declared local s0 */
    int temp_s2;
    int temp_s1;
    int temp_s0;
    temp_s2 = fptodp(*(float *)((char *)(arg2) + 0));
    temp_s1 = fptodp(*(float *)((char *)(arg2) + 4));
    temp_s0 = fptodp(*(float *)((char *)(arg2) + 12));
    printf(&DAT_004e9680[0], arg0, arg1, temp_s2, temp_s1, temp_s0, fptodp(*(float *)((char *)(arg2) + 8)));
}

int FUN_00234470(igStringRefList *arg0, int *arg1, const char *arg2) {
    void *sp3C;
    int *temp_a1;
    int temp_s1;
    int temp_v0;

    if (arg2 != 0) {
        StringList_CopyRetained(&sp3C, arg0, *arg1);
        temp_s1 = strcmp(sp3C, arg2) == 0;
        if (sp3C != 0) {
            temp_a1 = (int *)((char *)sp3C - 8);
            temp_v0 = *(int *)((char *)(sp3C) - 4) - 1;
            *(int *)((char *)(sp3C) - 4) = temp_v0;
            if (temp_v0 == 0) {
                StringChunk_ReleaseHeader(*temp_a1, temp_a1);
            }
        }
        if (temp_s1 != 0) {
            *arg1 += 1;
            return 1;
        }
    }
    return 0;
}

int FUN_00234510(igStringRefList *a0, int *a1, const char *a2, int *arg3) {
    void *sp2C;

    if (FUN_002345b0(a0, a1, a2, &sp2C) != 0) {
        *arg3 = atoi(sp2C);
        return 1;
    }
    return 0;
}

int FUN_00234560(igStringRefList *arg0, int *arg1, const char *arg2, long long *arg3) {
    void *sp2C;

    if (FUN_002345b0(arg0, arg1, arg2, &sp2C) != 0) {
        *arg3 = atof(sp2C);
        return 1;
    }
    return 0;
}

int FUN_002345b0(igStringRefList *arg0, int *arg1, const char *arg2, void **arg3) {
    void *sp5C;
    void *sp58;
    int eq;
    int v1;
    if (arg2 != 0) {
        StringList_CopyRetained(&sp5C, arg0, *arg1);
        eq = strcmp(sp5C, arg2) == 0;
        if (sp5C != 0) {
            int *a1 = (int *)((char *)sp5C - 8);
            int v0 = *(int *)((char *)sp5C - 4) - 1;
            *(int *)((char *)sp5C - 4) = v0;
            if (v0 == 0) {
                StringChunk_ReleaseHeader(*a1, a1);
            }
        }
        if (eq != 0) {
            v1 = *arg1 + 1;
            if (v1 < arg0->_count) {
                *arg1 = v1;
                StringList_CopyRetained(&sp58, arg0, *arg1);
                *arg3 = sp58;
                if (sp58 != 0) {
                    int *a1 = (int *)((char *)sp58 - 8);
                    int v0 = *(int *)((char *)sp58 - 4) - 1;
                    *(int *)((char *)sp58 - 4) = v0;
                    if (v0 == 0) {
                        StringChunk_ReleaseHeader(*a1, a1);
                    }
                }
                v1 = *arg1;
                *arg1 = v1 + 1;
                return 1;
            }
        }
    }
    return 0;
}

int FUN_002346c0(igStringRefList *arg0, int *arg1, const char *arg2, void **arg3) {
    void *sp3C;
    int str;
    int *temp_a1;
    int temp_v0;
    int var_v0;
    void *temp_s1;
    void *temp_v1;

    sp3C = 0;
    if (FUN_002345b0(arg0, arg1, arg2, &sp3C) != 0) {
        str = (int)sp3C;
        if (DAT_00586f20[0] == 0) {
            var_v0 = FUN_002eb010(0x10);
            if (var_v0 != 0) {
                var_v0 = StringPool_Construct(var_v0);
            }
            DAT_00586f20[0] = var_v0;
        }
        temp_s1 = (void *)(StringPool_Intern(DAT_00586f20[0], str));
        temp_v1 = (void *)(*arg3);
        if (temp_v1 != 0) {
            temp_a1 = (int *)((char *)temp_v1 - 8);
            temp_v0 = *(int *)((char *)(temp_v1) - 4) - 1;
            *(int *)((char *)(temp_v1) - 4) = temp_v0;
            if (temp_v0 == 0) {
                StringChunk_ReleaseHeader(*temp_a1, temp_a1);
            }
        }
        *arg3 = temp_s1;
        return 1;
    }
    return 0;
}

int FUN_00234770(igStringRefList *arg0, int *arg1, const char *arg2, unsigned char *arg3) {
    void *sp2C;
    if (FUN_002345b0(arg0, arg1, arg2, &sp2C) == 0) {
        return 0;
    }
    *arg3 = 0;
    if (strcmp(sp2C, &DAT_004e96b0[0]) == 0) {
        *arg3 = 1;
    } else if (strcmp(sp2C, &DAT_004e95f8[0]) == 0) {
        *arg3 = 1;
    }
    return 1;
}

int thunk_FUN_00234510(igStringRefList *args, int *index, const char *name, int *value)
{
    return FUN_00234510(args, index, name, value);
}

int FUN_00234810(igStringRefList *arg0, int *arg1, const char *arg2, float *arg3) {
    long long sp28;

    if (FUN_00234560(arg0, arg1, arg2, &sp28) != 0) {
        *arg3 = dptofp(sp28);
        return 1;
    }
    return 0;
}

int FUN_00234860(igStringRefList *arg0, int *arg1, const char *arg2, float *arg3) {
    void *sp2C;

    if (FUN_002345b0(arg0, arg1, arg2, &sp2C) != 0) {
        return FUN_001e6d30(sp2C, arg3, &DAT_004e96c0[0]);
    }
    return 0;
}

int FUN_002348b0(igStringRefList *arg0, int *arg1, const char *arg2, float *arg3) {
    void *sp2C;
    if (FUN_002345b0(arg0, arg1, arg2, &sp2C) != 0) {
        return FUN_001e6d80(sp2C, arg3, &DAT_004e96e0[0]);
    }
    return 0;
}

static inline int renderAllocator(void) {
    if (GPR_00554c14) {
        return Memory_GetAllocatorBySelector(DAT_00587028[0]);
    }
    return Memory_GetAllocatorBySelector(DAT_00587060[0]);
}

struct FlushSettings *FUN_00234900(struct FlushSettings *s) {
    s->f0 = 0;
    s->b4 = 1;
    s->b5 = 0;
    s->f8 = 0;
    s->f12 = 1.0f;
    s->f16 = 0.0f;
    s->f20 = 1.0f;
    s->f24 = 1.0f;
    s->f28 = 0.5f;
    s->f32 = 0.0f;
    s->f36 = 1.0f;
    s->f40 = 1.0f;
    s->f44 = 0.0f;
    s->f48 = 0.0f;
    s->f52 = 1.0f;
    s->f56 = 0.001f;
    s->b60 = 1;
    s->f64 = 45.0f;
    s->b68 = 1;
    s->f72 = 0.1f;
    s->f76 = 1000.0f;
    s->f80[0] = g_vec3Zero[0];
    s->f80[1] = g_vec3Zero[1];
    s->f80[2] = g_vec3Zero[2];
    s->b92 = 1;
    s->b93 = 0;
    s->b94 = 0;
    s->b95 = 0;
    s->b96 = 0;
    s->f100[0] = 1.0f;
    s->f100[1] = 1.0f;
    s->f100[2] = 1.0f;
    s->f100[3] = 1.0f;
    s->f100[4] = 1.0f;
    s->f100[5] = 1.0f;
    s->f100[6] = 1.0f;
    s->f100[7] = 1.0f;
    s->f132[0] = g_vec4Zero[0];
    s->f132[1] = g_vec4Zero[1];
    s->f132[2] = g_vec4Zero[2];
    s->f132[3] = g_vec4Zero[3];
    s->f148 = 0.2f;
    s->f152 = 0.2f;
    s->f156 = 0.2f;
    s->f160 = 1.0f;
    s->b164 = 0;
    s->b165 = 0;
    s->b166 = 0;
    s->b167 = 0;
    s->b168 = 0;
    s->b169 = 0;
    s->f172 = 0.1f;
    s->f176 = 0;
    s->b180 = 1;
    s->b181 = 0;
    s->b182 = 0;
    s->width = 640;
    s->height = 448;
    s->f192 = 0;
    s->f196 = -1;
    s->f200 = -1;
    s->f204 = -1;
    s->f208 = -1;
    s->b212 = 1;
    s->b213 = 1;
    s->b214 = 1;
    s->b215 = 0;
    s->b216 = 0;
    s->f220 = 5;
    s->f224 = 30;
    s->b228 = 0;
    s->b229 = 0;
    s->f232 = FUN_002caa70(renderAllocator());
    s->f236 = FUN_002b90e0(renderAllocator());
    if (DAT_0056dc50[0] == 0) {
        struct FlushShared *shared = FUN_001007e0(240);
        if (shared) {
            shared = (struct FlushShared *)FUN_00238110(shared);
        }
        DAT_0056dc50[0] = shared;
    }
    DAT_0056dc50[0]->refs++;
    s->shared = DAT_0056dc50[0];
    FUN_00234ee0(s, s->shared->f0);
    return s;
}

void *FUN_00234b90(struct App *arg0, short arg1) {
    igObject *p;
    void *q;
    int *h;
    int rc;

    if (arg0 != 0) {
        FUN_00234ca0();
        if (&arg0->f236) {
            p = arg0->f236;
            if (p != 0) {
                rc = p->_refCount - 1;
                p->_refCount = rc;
                if (((unsigned long long) ((long long) (int) p->_refCount << 0x29) >> 0x29) == 0) {
                    igObject_Destroy(p);
                }
            }
        }
        if (&arg0->f232) {
            p = arg0->f232;
            if (p != 0) {
                rc = p->_refCount - 1;
                p->_refCount = rc;
                if (((unsigned long long) ((long long) (int) p->_refCount << 0x29) >> 0x29) == 0) {
                    igObject_Destroy(p);
                }
            }
        }
        if (arg0 != 0) {
            q = arg0->f0;
            if (q != 0) {
                h = (int *)((char *)(q) - 8);
                rc = *(int *)((char *)(q) - 4) - 1;
                *(int *)((char *)(q) - 4) = rc;
                if (rc == 0) {
                    StringChunk_ReleaseHeader(*h, h);
                }
            }
        }
        if (arg1 > 0) {
            FUN_00100610(arg0);
        }
    }
    return arg0;
}

void FUN_00234ca0(void) {
    struct FlushShared *f;
    void *p;
    int *h;
    int rc;

    if (DAT_0056dc50[0] != 0) {
        if (--DAT_0056dc50[0]->refs <= 0) {
            f = DAT_0056dc50[0];
            if (f != 0) {
                if (&f->f236) {
                    p = f->f236;
                    if (p != 0) {
                        h = (int *)((char *)(p) - 8);
                        rc = *(int *)((char *)(p) - 4) - 1;
                        *(int *)((char *)(p) - 4) = rc;
                        if (rc == 0) {
                            StringChunk_ReleaseHeader(*h, h);
                        }
                    }
                }
                if (f != 0) {
                    p = f->f0;
                    if (p != 0) {
                        h = (int *)((char *)(p) - 8);
                        rc = *(int *)((char *)(p) - 4) - 1;
                        *(int *)((char *)(p) - 4) = rc;
                        if (rc == 0) {
                            StringChunk_ReleaseHeader(*h, h);
                        }
                    }
                }
                FUN_00100610(f);
            }
            DAT_0056dc50[0] = 0;
        }
    }
}

void FUN_00234d70(int self, int count, int *names) {
    int allocator;
    int i;
    if (GPR_00554c14 != 0) {
        allocator = Memory_GetAllocatorBySelector(DAT_00587028[0]);
    } else {
        allocator = Memory_GetAllocatorBySelector(DAT_00587060[0]);
    }
    igSmartPointer<InternedStringList> list(FUN_002b90e0(allocator));
    for (i = 0; i < count; i++) {
        int text = names[i];
        StringRef name(text);
        StringList_AppendRetained(list.get(), &name);
    }
    FUN_00235370((ViewerOptions *)self, (igStringRefList *)list.get());
}

/* Command-line parser of an Alchemy model-viewer style application. Each recognised '--option
 * value' is parsed into `opts` and echoed into the block `opts->applied` points at. '--help'
 * prints the usage text and exits, '--' or '-n' ends the option scan, any other '-x' token is
 * reported as unrecognised. The second loop collects the remaining tokens as model files, each
 * with its '-n N' repeat count. */
void FUN_00235370(ViewerOptions *opts, igStringRefList *args)
{
    StringRef modelFile;
    int repeat;
    int index;
    /* Each smart-pointer temporary of the original has its own stack slot. */
    char *helpRef;
    char *optionRef;
    char *printRef;
    char *helpRef2;
    char *currentRef;
    int argc;
    ViewerOptions *applied;
    int slot;
    IntList *repeats;

    repeat = 1;
    argc = args->_count;
    index = 1;

    while (index < argc) {
        if (FUN_00234470(args, &index, help)) {
            StringList_CopyRetained(&helpRef, args, 0);
            FUN_00233c10(helpRef);
            ReleaseString(helpRef);
            ReleaseObject(opts->intList);
            opts->intList = 0;
            ReleaseObject(opts->stringList);
            opts->stringList = 0;
            exit(0);
        } else if (FUN_002346c0(args, &index, 0, (void **)&opts->modelName)) {
            char *name;
            name = opts->modelName;
            applied = opts->applied;
            if (name != 0) {
                ((int *)name)[-1]++;
            }
            ReleaseString(applied->modelName);
            applied->modelName = opts->modelName;
        } else if (FUN_00234770(args, &index, showBbox, &opts->showBbox)) {
            opts->applied->showBbox = opts->showBbox;
        } else if (FUN_00234770(args, &index, showNormals, &opts->showNormals)) {
            opts->applied->showNormals = opts->showNormals;
        } else if (FUN_002348b0(args, &index, normalsColor, &opts->normalsColor[0])) {
            applied = opts->applied;
            applied->normalsColor[0] = opts->normalsColor[0];
            applied->normalsColor[1] = opts->normalsColor[1];
            applied->normalsColor[2] = opts->normalsColor[2];
            applied->normalsColor[3] = opts->normalsColor[3];
        } else if (FUN_002348b0(args, &index, invalidStoredNormalsColor, &opts->invalidStoredNormalsColor[0])) {
            applied = opts->applied;
            applied->invalidStoredNormalsColor[0] = opts->invalidStoredNormalsColor[0];
            applied->invalidStoredNormalsColor[1] = opts->invalidStoredNormalsColor[1];
            applied->invalidStoredNormalsColor[2] = opts->invalidStoredNormalsColor[2];
            applied->invalidStoredNormalsColor[3] = opts->invalidStoredNormalsColor[3];
        } else if (FUN_002348b0(args, &index, scaledNormalsColor, &opts->scaledNormalsColor[0])) {
            applied = opts->applied;
            applied->scaledNormalsColor[0] = opts->scaledNormalsColor[0];
            applied->scaledNormalsColor[1] = opts->scaledNormalsColor[1];
            applied->scaledNormalsColor[2] = opts->scaledNormalsColor[2];
            applied->scaledNormalsColor[3] = opts->scaledNormalsColor[3];
        } else if (FUN_00234810(args, &index, invalidNormalsPrecision, &opts->invalidNormalsPrecision)) {
            opts->applied->invalidNormalsPrecision = opts->invalidNormalsPrecision;
        } else if (FUN_00234770(args, &index, autoSelectCamera, &opts->autoSelectCamera)) {
            opts->applied->autoSelectCamera = opts->autoSelectCamera;
        } else if (FUN_00234810(args, &index, hfov, &opts->hfov)) {
            opts->applied->hfov = opts->hfov;
        } else if (FUN_00234770(args, &index, autoPlanes, &opts->autoPlanes)) {
            opts->applied->autoPlanes = opts->autoPlanes;
        } else if (FUN_00234810(args, &index, nearPlane, &opts->nearPlane)) {
            opts->applied->nearPlane = opts->nearPlane;
        } else if (FUN_00234810(args, &index, farPlane, &opts->farPlane)) {
            opts->applied->farPlane = opts->farPlane;
        } else if (FUN_00234860(args, &index, upVector, &opts->upVector[0])) {
            applied = opts->applied;
            applied->upVector[0] = opts->upVector[0];
            applied->upVector[1] = opts->upVector[1];
            applied->upVector[2] = opts->upVector[2];
        } else if (FUN_00234770(args, &index, autoSceneLights, &opts->autoSceneLights)) {
            opts->applied->autoSceneLights = opts->autoSceneLights;
        } else if (FUN_00234770(args, &index, autoHeadLight, &opts->autoHeadLight)) {
            opts->applied->autoHeadLight = opts->autoHeadLight;
        } else if (FUN_00234770(args, &index, useSceneLights, &opts->useSceneLights)) {
            opts->applied->useSceneLights = opts->useSceneLights;
        } else if (FUN_00234770(args, &index, useHeadLight, &opts->useHeadLight)) {
            opts->applied->useHeadLight = opts->useHeadLight;
        } else if (FUN_00234770(args, &index, useHeadLightSpecular, &opts->useHeadLightSpecular)) {
            opts->applied->useHeadLightSpecular = opts->useHeadLightSpecular;
        } else if (FUN_002348b0(args, &index, headLightDiffuse, &opts->headLightDiffuse[0])) {
            applied = opts->applied;
            applied->headLightDiffuse[0] = opts->headLightDiffuse[0];
            applied->headLightDiffuse[1] = opts->headLightDiffuse[1];
            applied->headLightDiffuse[2] = opts->headLightDiffuse[2];
            applied->headLightDiffuse[3] = opts->headLightDiffuse[3];
        } else if (FUN_002348b0(args, &index, headLightSpecular, &opts->headLightSpecular[0])) {
            applied = opts->applied;
            applied->headLightSpecular[0] = opts->headLightSpecular[0];
            applied->headLightSpecular[1] = opts->headLightSpecular[1];
            applied->headLightSpecular[2] = opts->headLightSpecular[2];
            applied->headLightSpecular[3] = opts->headLightSpecular[3];
        } else if (FUN_002348b0(args, &index, headLightAmbient, &opts->headLightAmbient[0])) {
            applied = opts->applied;
            applied->headLightAmbient[0] = opts->headLightAmbient[0];
            applied->headLightAmbient[1] = opts->headLightAmbient[1];
            applied->headLightAmbient[2] = opts->headLightAmbient[2];
            applied->headLightAmbient[3] = opts->headLightAmbient[3];
        } else if (FUN_002348b0(args, &index, clearColor, &opts->clearColor[0])) {
            applied = opts->applied;
            applied->clearColor[0] = opts->clearColor[0];
            applied->clearColor[1] = opts->clearColor[1];
            applied->clearColor[2] = opts->clearColor[2];
            applied->clearColor[3] = opts->clearColor[3];
        } else if (FUN_00234770(args, &index, wireframeMode, &opts->wireframeMode)) {
            opts->applied->wireframeMode = opts->wireframeMode;
        } else if (FUN_00234770(args, &index, forceWireframe, &opts->forceWireframe)) {
            opts->applied->forceWireframe = opts->forceWireframe;
        } else if (FUN_00234770(args, &index, backfaceCullingMode, &opts->backfaceCullingMode)) {
            opts->applied->backfaceCullingMode = opts->backfaceCullingMode;
        } else if (FUN_00234770(args, &index, forceBackfaceCulling, &opts->forceBackfaceCulling)) {
            opts->applied->forceBackfaceCulling = opts->forceBackfaceCulling;
        } else if (FUN_00234770(args, &index, alphaTest, &opts->alphaTest)) {
            opts->applied->alphaTest = opts->alphaTest;
        } else if (FUN_00234770(args, &index, forceAlphaTest, &opts->forceAlphaTest)) {
            opts->applied->forceAlphaTest = opts->forceAlphaTest;
        } else if (FUN_00234810(args, &index, alphaTestReference, &opts->alphaTestReference)) {
            opts->applied->alphaTestReference = opts->alphaTestReference;
        } else if (FUN_00234810(args, &index, maximumFrameRate, &opts->maximumFrameRate)) {
            opts->applied->maximumFrameRate = opts->maximumFrameRate;
        } else if (FUN_00234770(args, &index, optimizeTextures, &opts->optimizeTextures)) {
            opts->applied->optimizeTextures = opts->optimizeTextures;
        } else if (FUN_00234770(args, &index, halfBuffer, &opts->halfBuffer)) {
            opts->applied->halfBuffer = opts->halfBuffer;
        } else if (FUN_00234770(args, &index, palVideoMode, &opts->palVideoMode)) {
            opts->applied->palVideoMode = opts->palVideoMode;
        } else if (thunk_FUN_00234510(args, &index, width, &opts->width)) {
            opts->applied->width = opts->width;
        } else if (thunk_FUN_00234510(args, &index, height, &opts->height)) {
            opts->applied->height = opts->height;
        } else if (thunk_FUN_00234510(args, &index, swapInterval, &opts->swapInterval)) {
            opts->applied->swapInterval = opts->swapInterval;
        } else if (thunk_FUN_00234510(args, &index, colorBits, &opts->colorBits)) {
            opts->applied->colorBits = opts->colorBits;
        } else if (thunk_FUN_00234510(args, &index, alphaBits, &opts->alphaBits)) {
            opts->applied->alphaBits = opts->alphaBits;
        } else if (thunk_FUN_00234510(args, &index, depthBits, &opts->depthBits)) {
            opts->applied->depthBits = opts->depthBits;
        } else if (thunk_FUN_00234510(args, &index, stencilBits, &opts->stencilBits)) {
            opts->applied->stencilBits = opts->stencilBits;
        } else if (FUN_00234770(args, &index, reportVideoFormat, &opts->reportVideoFormat)) {
            opts->applied->reportVideoFormat = opts->reportVideoFormat;
        } else if (FUN_00234770(args, &index, showLogo, &opts->showLogo)) {
            opts->applied->showLogo = opts->showLogo;
        } else if (FUN_00234770(args, &index, showUi, &opts->showUi)) {
            opts->applied->showUi = opts->showUi;
        } else if (FUN_00234770(args, &index, enableMayaControls, &opts->enableMayaControls)) {
            opts->applied->enableMayaControls = opts->enableMayaControls;
        } else if (FUN_00234770(args, &index, benchmark, &opts->benchmark)) {
            opts->applied->benchmark = opts->benchmark;
        } else if (thunk_FUN_00234510(args, &index, benchmarkSkipFrames, &opts->benchmarkSkipFrames)) {
            opts->applied->benchmarkSkipFrames = opts->benchmarkSkipFrames;
        } else if (thunk_FUN_00234510(args, &index, benchmarkFrames, &opts->benchmarkFrames)) {
            opts->applied->benchmarkFrames = opts->benchmarkFrames;
        } else if (FUN_00234770(args, &index, columnStatistics, &opts->columnStatistics)) {
            opts->applied->columnStatistics = opts->columnStatistics;
        } else if (FUN_00234770(args, &index, allocateVisualContextInScratchpad, &opts->allocateVisualContextInScratchpad)) {
            opts->applied->allocateVisualContextInScratchpad = opts->allocateVisualContextInScratchpad;
        } else if (FUN_00234470(args, &index, n)) {
            index = index - 1;
            break;
        } else if (FUN_00234470(args, &index, dashdash)) {
            break;
        } else {
            int isOption;
            StringList_CopyRetained(&optionRef, args, index);
            isOption = optionRef[0] == '-';
            ReleaseString(optionRef);
            if (!isOption) {
                break;
            }
            StringList_CopyRetained(&printRef, args, index);
            printf(unrecognized, printRef);
            ReleaseString(printRef);
            StringList_CopyRetained(&helpRef2, args, 0);
            FUN_00233c10(helpRef2);
            ReleaseString(helpRef2);
            ReleaseObject(opts->intList);
            opts->intList = 0;
            ReleaseObject(opts->stringList);
            opts->stringList = 0;
            exit(0);
        }
    }

    while (index < argc) {
        if (!FUN_00234510(args, &index, n, &repeat)) {
            StringList_CopyRetained(&currentRef, args, index);
            if (currentRef != 0) {
                ((int *)currentRef)[-1]++;
            }
            ReleaseString(modelFile.p);
            modelFile.p = currentRef;
            ReleaseString(currentRef);
            {
                StringRef argument(modelFile);
                StringList_AppendRetained((igStringRefList *)opts->stringList, &argument.p);
            }
            repeats = (IntList *)opts->intList;
            slot = repeats->count;
            if (slot < repeats->capacity) {
                repeats->count = countOf(repeats) + 1;
            } else {
                List_Resize(repeats, slot + 1, 4);
            }
            repeats->data[slot] = repeat;
            repeat = 1;
            index = index + 1;
        }
    }
}

void Gap__Insight__igFlushRenderer__vfunc_26(igFlushRendererView *self)
{
    self->_visualContext->vfunc_173();
}

static inline int internedPool(void) {
    if (DAT_00586f20[0] == 0) {
        int v = FUN_002eb010(0x10);
        if (v != 0) { v = StringPool_Construct(v); }
        DAT_00586f20[0] = v;
    }
    return DAT_00586f20[0];
}

void FUN_00236140(void) {
    igSmartPointer<NamedObject> r(FUN_002c43b0(Memory_GetAllocatorBySelector(DAT_00587038[0])));
    NamedObject *s0 = r.get();
    int *s1 = (int *)StringPool_Intern(internedPool(), &DAT_004e9740[0]);
    int *old = (int *)s0->name;
    if (old != 0) {
        int *hdr = old - 2;
        int c = old[-1] - 1;
        old[-1] = c;
        if (c == 0) {
            StringChunk_ReleaseHeader(*hdr, hdr);
        }
    }
    s0->name = (int)s1;
    FUN_002e3850(r.get(), &DAT_004e9748[0]);
    FUN_00304720(((G *)DAT_00586dc8[0])->f76, &DAT_004e9750[0], r->name, 1);
}

static inline void describe(const igSmartPointer<TextValue> &text, int value) {
    if (value < 0) {
        FUN_0030b3c0(text.p, DAT_004e9778);
    } else {
        FUN_0030b720(text.p, value, DAT_004e9780);
    }
}

static inline const char *textOf(const TextValue *value) {
    const char *s = value->text;
    s = (s == 0) ? DAT_004c22f0[0] : s;
    return s;
}

ShadowSettings FUN_00236260(ShadowConfig *config) {
    igSmartPointer<TextValue> text(FUN_002b9500(Memory_GetAllocatorBySelector(DAT_00587048[0])));
    ShadowSettings settings;
    settings.enabled = 1;
    settings.width = config->width;
    settings.height = config->height;
    if (config->verbose) {
        printf(DAT_004e9760);
    }
    describe(text, config->left);
    if (config->verbose) {
        printf(DAT_004e9788, textOf(text.p));
    }
    describe(text, config->top);
    if (config->verbose) {
        printf(DAT_004e9798, textOf(text.p));
    }
    describe(text, config->right);
    if (config->verbose) {
        printf(DAT_004e97a8, textOf(text.p));
    }
    describe(text, config->bottom);
    if (config->verbose) {
        printf(DAT_004e97b8, textOf(text.p));
    }
    settings.left = config->left;
    settings.top = config->top;
    settings.right = config->right;
    settings.bottom = config->bottom;
    settings.scale = 1.0f;
    return settings;
}

int Gap__Insight__igWindowResizeEventReceiver__vfunc_32(Receiver *self, int width, int height) {
    igSmartPointer<ResizeEvent> event((ResizeEvent *)FUN_002332b0(igObject_GetAllocator()));
    {
        ResizeEvent *e = event.get();
        e->origin[0] = DAT_004e0fa0[0];
        e->origin[1] = DAT_004e0fa4[0];
    }
    {
        ResizeEvent *e = event.get();
        e->size[0] = (float)width;
        e->size[1] = (float)height;
    }
    FUN_00237ea0((igMessageDispatcherOwnerView *)self->f8->f40, event.get());
    return 0;
}

void FUN_00236ab0(void *arg0, void *arg1) {
    if (FUN_00236b70() == 0) {
        FUN_002d6f50(*(int *)((char *)(arg0) + 8), arg1, 0);
        *(int *)((char *)(arg1) + 12) = (int)(arg0);
        ((DW4VC_92_0 *)(((char *)(arg1) + 0)))->vX();
    }
}

void FUN_00236b10(void *arg0, void *arg1) {
    int sp3C;

    if (FUN_00236b70() != 0) {
        ((DW4VC_96_0 *)(((char *)(arg1) + 0)))->vX();
        *(int *)((char *)(arg1) + 12) = 0;
        FUN_002d7750(&sp3C, *(int *)((char *)(arg0) + 8), arg1);
    }
}

void FUN_00236be0(S12 *arg0, int arg1) {
    if (((DW4VC_104_0 *)(arg0->f12))->vX() == 0) {
        ((DW4VC_96_1 *)(arg0->f12))->vX(arg1);
    }
}

void FUN_00236c40(S236 *arg0, int arg1) {
    if (((DW4VC_104_0 *)arg0->p)->vX() != 0) {
        ((DW4VC_100_1 *)arg0->p)->vX((int)(arg1));
    }
}

void FUN_00236ca0(int self) {
    int meta;
    int count;
    int i;
    count = igMetaObject_CountTree(meta = (int)igInsightPlugin_GetMetaObject());
    for (i = 0; i < count; i++) {
        int type = FUN_002fe300(meta, i);
        igSmartPointer<Instance> plugin(FUN_002fd6e0(type, igObject_GetAllocator(self)).get(), kRetainReference);
        if (plugin.get()) {
            FUN_00236dd0((void *)self, (void **)plugin.get());
        }
    }
}

void FUN_00236dd0(void *arg0, void **arg1) {
    ObjectList_AppendRetained(*(int *)((char *)(arg0) + 104));
    ((DW4VC_92_1 *)(arg1))->vX((int)(arg0));
}

void FUN_00236e20(void *arg0, void **arg1) {
    int sp3C;

    ((DW4VC_96_1 *)(arg1))->vX((int)(arg0));
    ObjectList_RemoveFirstRetained(&sp3C, *(int *)((char *)(arg0) + 104), arg1, 0);
}

void FUN_00236e80(A *arg0) {
    int i;

    for (i = arg0->f68->cnt - 1; i >= 0; i--) {
        FUN_00236e20(arg0, (void **)arg0->f68->arr[i]);
    }
}

void FUN_00236ee0(void *arg0, int arg1) {
    FUN_00457ca0(arg1, *(int *)((char *)arg0 + 24));
    FUN_002d6f50(*(int *)((char *)arg0 + 28), arg1, 0);
}

void FUN_00236f30(Obj_236f30 *arg0, int arg1) {
    int sp2C;
    FUN_002d7750(&sp2C, arg0->f28, arg1);
    if (sp2C == DAT_004fb410[0]) {
        FUN_00457ca0(arg1, 0);
    }
}

Obj_236f80 *FUN_00236f80(Self *arg0, int arg1) {
    unsigned int i;
    for (i = 0; i < arg0->mid->list->count; i++) {
        Obj_236f80 *o = arg0->mid->list->arr[i];
        int r = o->v20(); if (r == arg1) return o;
    }
    return 0;
}

int FUN_00237010(void) {
    return (int)g_igInfoManager_metaObject[0];
}

int FUN_00237020(int *p)
{
    return FUN_002d7090(*(int *)((char *)p + 28));
}

void igInsightCore_AddInfo(igInsightCore *self, int info) {
    unsigned int index;
    igObjectList *managers;

    for (index = 0; managers = (igObjectList *)((igSerialScheduler *)self->_managerList)->_managerList, index < (unsigned int)managers->_count; index++) {
        int byteOffset = index * 4;
        DW4VC *manager = (DW4VC *)*(int *)(managers->_data + byteOffset);
        if (manager->vX(info) != 0) {
            break;
        }
    }
    ObjectList_AppendRetained(self->_infoList, info);
}

void FUN_002370c0(igInsightCore *arg0) {
    igObjectList *l;
    int n2;
    int j;
    int n;
    igObjectList *a;
    igObject *p;
    unsigned int k;
    int i;

    for (k = 0; k < (unsigned int)((igObjectList *)((igInfoManagerOrderedList *)arg0->_managerList)->_objectList)->_count; k++) {
        a = (igObjectList *)((igInfoManagerOrderedList *)arg0->_managerList)->_objectList;
        (*(VC112 ***)&a->_data)[k]->vX();
    }
    l = (igObjectList *)arg0->_infoList;
    n = l->_count;
    for (i = 0; i < n; i++) {
        p = (*(igObject ***)&l->_data)[i];
        if (p != 0) {
            *(int *)&p->_refCount = *(int *)&p->_refCount - 1;
            if (((unsigned long long)((long long)*(int *)&p->_refCount << 0x29) >> 0x29) == 0) {
                igObject_Destroy(p);
            }
        }
    }
    n2 = l->_count;
    for (j = 0; j < n2; j++) {
        (*(igObject ***)&l->_data)[j] = 0;
    }
    l->_count = 0;
    if (!(0 < ((igObjectList *)arg0->_infoList)->_count)) {
        List_Reserve(arg0->_infoList, 0, 4);
    }
}

void FUN_002371f0(S_2371f0 *arg0) {
    unsigned int i;

    arg0->f64 = 0;
    arg0->f56 = 0;
    for (i = 0; i < arg0->m->l->cnt; i++) {
        arg0->m->l->arr[i]->vX();
    }
    arg0->f48->vY();
}

void FUN_00237280(int *arg0) {
    unsigned int i;
    struct Q *q;

    ((A_237280 *)arg0[12])->vX();
    for (i = 0; i < (unsigned int)(q = *(struct Q **)(arg0[2] + 8))->count; i++) {
        q->data[i]->vX();
    }
}

void Gap__Insight__igInsightCore__vfunc_13(struct A_237300 *arg0) {
    Gap__Core__igObject__vfunc_11();
    StringRef_237300 first(&DAT_004e9840[0]);
    StringRef_237300 second(&DAT_004e9850[0]);
    StringRef_237300 third(&DAT_004e9860[0]);
    FUN_002d78e0(arg0->f28, first.p);
    FUN_002d78e0(arg0->f28, second.p);
    FUN_002d78e0(arg0->f28, third.p);
    FUN_002d7090(arg0->f28, first.p, second.p);
    FUN_002d7090(arg0->f28, second.p, third.p);
    FUN_002d7090(arg0->f28, arg0->f44, first.p);
    FUN_002d6f50(arg0->f28, arg0->f44, 0);
    arg0->f72 = 0x40000;
    *(struct A_237300 **)(arg0->f36 + 8) = arg0;
    FUN_00454290(arg0->f32, arg0->f36);
}

void FUN_00237530(OO *arg0) {
    R_237530 *sp4C;
    int temp_s1;
    int var_s0;
    R_237530 *t;
    R_237530 *s0;

    if (arg0->f20 == 0) {
        FUN_002364e0(&sp4C, 0);
        s0 = sp4C;
        if (s0 != 0) {
            s0->rc = s0->rc + 1;
        }
        t = (R_237530 *)arg0->f20;
        if (t != 0) {
            t->rc = t->rc - 1;
            if ((t->rc & 0x7FFFFF) == 0) {
                igObject_Destroy(t);
            }
        }
        arg0->f20 = (DW4VC_152 *)s0;
        if (sp4C != 0) {
            sp4C->rc = sp4C->rc - 1;
            if ((sp4C->rc & 0x7FFFFF) == 0) {
                igObject_Destroy(sp4C);
            }
        }
    }
    s0 = arg0->f20->vX();
    if (s0 != 0) {
        s0->rc = s0->rc + 1;
    }
    t = arg0->f24;
    if (t != 0) {
        t->rc = t->rc - 1;
        if ((t->rc & 0x7FFFFF) == 0) {
            igObject_Destroy(t);
        }
    }
    arg0->f24 = s0;
    FUN_004541f0(arg0->f32, arg0->f20);
    temp_s1 = arg0->f28->f8->n;
    var_s0 = 0;
    while (var_s0 < temp_s1) {
        FUN_00457ca0(arg0->f28->f8->items[var_s0], arg0->f24);
        var_s0 += 1;
    }
}

void FUN_002376b0(struct H *arg0) {
    int n;
    int i;

    n = arg0->m->list->count;
    for (i = 0; i < n; i++) {
        FUN_00457ca0(arg0->m->list->items[i], 0);
    }
    FUN_0013c110();
}

void FUN_00237730(S_237730 *arg0) {
    long long t = arg0->f48->vX();
    arg0->f64 = t - arg0->f56;
    arg0->f56 = t;
    arg0->f80 = arg0->f80 + (__muldi3(arg0->f64, arg0->f72) >> 18);
    arg0->f32->vX();
    arg0->f12->vX();
}

void FUN_002377c0(ProfilerState *t) {
    int n;
    int i;
    long long s2;
    long long s1;
    int j;
    long long s0;
    if (t->a->v34() == 0) {
        t->cnt = t->cnt + 1;
        n = t->m->l->cnt;
        s2 = t->b->v24();
        for (i = 0; i < n; i++) t->m->l->arr[i]->v23();
        if (t->a->v171() != 0) {
            s1 = t->b->v24();
            for (j = 0; j < n; j++) t->m->l->arr[j]->v24();
            s0 = t->b->v24();
            t->a->v172();
            t->d1 = s1 - s2;
            t->d2 = s0 - s1;
        }
    }
}

void Gap__Insight__igMessageDefaultReceiver__vfunc_23(S_237940 *s) {
    if (s->obj) { PM pm = s->pm; (s->obj->*pm)(); }
}

E *FUN_00237990(const A_237990 *arg0, int arg1) {
    int i;
    int n;
    E *e;

    n = arg0->f8->f8;
    for (i = 0; i < n; i++) {
        e = arg0->f8->f16[i];
        if (arg1 == e->f8) {
            return e;
        }
    }
    return 0;
}

igSmartPointer<MessageFilter> FUN_002379e0(FilterDispatcher *self, igObject *target)
{
    igSmartPointer<MessageFilter> filter((MessageFilter *)FUN_00237990((const A_237990 *)self, (int)target), kRetainReference);
    if (filter == 0) {
        void *allocator = (void *)igObject_GetAllocator(self);
        filter.release();
        filter.p = (MessageFilter *)FUN_00231b40((int)allocator);
        filter->_target = target;
        ObjectList_AppendRetained(self->_filters, filter.get());
    }
    return filter;
}

void Gap__Insight__igFilterMessageDispatcher__vfunc_28(N *arg0, int arg1) {
    int n;
    int i;
    N *t;
    int m;
    int j;
    n = arg0->f12->cnt;
    for (i = 0; i < n; i++) {
        t = arg0->f12->data[i];
        if (t->vX(arg1) != 0) {
            m = t->f12->cnt;
            for (j = 0; j < m; j++) {
                t->f12->data[j]->vX(arg1);
            }
        }
    }
}

void Gap__Insight__igMessageFilter__vfunc_23(int arg0, int arg1) {
    igObject_IsKindOf(arg1, *(int *)((char *)(arg0) + 8));
}

void Gap__Insight__igFilterMessageDispatcher__vfunc_23(FilterDispatcherSlots *self, int message, igObject *target)
{
    igSmartPointer<MessageFilter> filter = FUN_002379e0((FilterDispatcher *)self, target);

    self->dispatch(message, filter.get());
}

void Gap__Insight__igFilterMessageDispatcher__vfunc_24(void *arg0, void *arg1, void *arg2) {
    ObjectList_AppendUniqueRetained(*(int *)((char *)(arg2) + 12));
    ObjectList_AppendUniqueRetained(*(int *)((char *)(arg0) + 12), arg2);
}

void Gap__Insight__igFilterMessageDispatcher__vfunc_26(void **arg0, int arg1, int arg2) {
    int temp_v0;

    temp_v0 = (int)FUN_00237990((const A_237990 *)arg0, arg2);
    if (temp_v0 != 0) {
        ((DW4VC_108_2 *)(arg0))->vX((int)(arg1), (int)(temp_v0));
    }
}

void Gap__Insight__igFilterMessageDispatcher__vfunc_25(V *arg0, int arg1) {
    int i;
    for (i = arg0->list->n - 1; i >= 0; i--) {
        arg0->vX(arg1, arg0->list->arr[i]);
    }
}

void Gap__Insight__igFilterMessageDispatcher__vfunc_27(S_arg0 *arg0, void *arg1, S_arg2 *arg2) {
    int sp3C;
    int sp38;
    int sp34;

    ObjectList_RemoveFirstRetained(&sp3C, arg2->f12, arg1, 0);
    if (*(int *)((char *)(arg2->f12) + 8) == 0) {
        ObjectList_RemoveFirstRetained(&sp38, arg0->f12, arg2, 0);
        ObjectList_RemoveFirstRetained(&sp34, arg0->f8, arg2, 0);
    }
}

void FUN_00237e80(igMessageDispatcherOwnerView *self)
{
    self->f8->vfunc_21();
}

void FUN_00237ea0(igMessageDispatcherOwnerView *self, void *message)
{
    self->f8->vfunc_26(message);
}

static inline void setRetained(SchedulerManager *manager, ManagerArray *list, int index) {
    igObject *previous;

    if (manager != 0) {
        ((igObject *)manager)->_refCount = ((igObject *)manager)->_refCount + 1;
    }
    previous = (igObject *)list->_data[index];
    if (previous != 0) {
        previous->_refCount = previous->_refCount - 1;
        if ((previous->_refCount & 0x7fffff) == 0) {
            igObject_Destroy(previous);
        }
    }
    if (list->_count != 0 && index >= 0 && index < list->_count) {
        list->_data[index] = manager;
    }
}

/* matching construct: 4 variants, the inline parameter order */
void Gap__Insight__igSerialScheduler__vfunc_23(igSerialScheduler *scheduler) {
    unsigned int count = ((ManagerListView *)scheduler->_managerList)->_list->_count;
    int i;

    ObjectList_ResizeRetained((ManagerArray *)scheduler->_cachedManagerList, count);
    for (i = 0; i < count; i++) {
        setRetained(((ManagerListView *)scheduler->_managerList)->_list->_data[i], (ManagerArray *)scheduler->_cachedManagerList, i);
    }
    for (i = 0; i < count; i++) {
        ((ManagerArray *)scheduler->_cachedManagerList)->_data[i]->update();
    }
    ObjectList_ResizeRetained((ManagerArray *)scheduler->_cachedManagerList, 0);
}

void Gap__Insight__igSerialScheduler__vfunc_24(void *arg0, int arg1) {
    FUN_002d6f50(*(int *)((char *)(arg0) + 8), arg1, 1);
}

void Gap__Insight__igSerialScheduler__vfunc_25(Obj_238020 *arg0, int arg1) {
    int sp1C;
    FUN_002d7750(&sp1C, arg0->f8, arg1);
}

void Gap__Insight__igSerialScheduler__vfunc_27(int a0) {
    FUN_002d7090(*(int *)((char *)a0 + 8));
}

void Gap__Insight__igSerialScheduler__vfunc_28(S0 *arg0, int arg1, int arg2) {
    int sp1C;

    FUN_002d7760(&sp1C, arg0->f8, arg1, arg2);
}

void Gap__Insight__igSerialScheduler__vfunc_29(int a0) {
    FUN_002d7840(*(int *)((char *)a0 + 8));
}

void *FUN_00238110(void *arg0) {
    *(int *)((char *)(arg0) + 0) = 0;
    *(char *)((char *)(arg0) + 4) = 1;
    *(char *)((char *)(arg0) + 5) = 0;
    *(int *)((char *)(arg0) + 8) = 0;
    *(int *)((char *)(arg0) + 12) = 0x3F800000;
    *(int *)((char *)(arg0) + 16) = 0;
    *(int *)((char *)(arg0) + 20) = 0x3F800000;
    *(int *)((char *)(arg0) + 24) = 0x3F800000;
    *(int *)((char *)(arg0) + 28) = 0x3F000000;
    *(int *)((char *)(arg0) + 32) = 0;
    *(int *)((char *)(arg0) + 36) = 0x3F800000;
    *(int *)((char *)(arg0) + 40) = 0x3F800000;
    *(int *)((char *)(arg0) + 44) = 0;
    *(int *)((char *)(arg0) + 48) = 0;
    *(int *)((char *)(arg0) + 52) = 0x3F800000;
    *(float *)((char *)(arg0) + 56) = (float) 0.00100000005f;
    *(char *)((char *)(arg0) + 60) = 1;
    *(int *)((char *)(arg0) + 64) = 0x42340000;
    *(char *)((char *)(arg0) + 68) = 1;
    *(float *)((char *)(arg0) + 72) = (float) 0.100000001f;
    *(int *)((char *)(arg0) + 76) = 0x447A0000;
    *(float *)((char *)(arg0) + 80) = (float) DAT_004e1058[0];
    *(float *)((char *)(arg0) + 84) = (float) DAT_004e105c[0];
    *(float *)((char *)(arg0) + 88) = (float) DAT_004e1060[0];
    *(char *)((char *)(arg0) + 92) = 1;
    *(char *)((char *)(arg0) + 93) = 0;
    *(char *)((char *)(arg0) + 94) = 0;
    *(char *)((char *)(arg0) + 95) = 0;
    *(char *)((char *)(arg0) + 96) = 0;
    *(int *)((char *)(arg0) + 100) = 0x3F800000;
    *(int *)((char *)(arg0) + 104) = 0x3F800000;
    *(int *)((char *)(arg0) + 108) = 0x3F800000;
    *(int *)((char *)(arg0) + 112) = 0x3F800000;
    *(int *)((char *)(arg0) + 116) = 0x3F800000;
    *(int *)((char *)(arg0) + 120) = 0x3F800000;
    *(int *)((char *)(arg0) + 124) = 0x3F800000;
    *(int *)((char *)(arg0) + 128) = 0x3F800000;
    *(float *)((char *)(arg0) + 132) = (float) DAT_004e1170[0];
    *(float *)((char *)(arg0) + 136) = (float) DAT_004e1174[0];
    *(float *)((char *)(arg0) + 140) = (float) DAT_004e1178[0];
    *(float *)((char *)(arg0) + 144) = (float) DAT_004e117c[0];
    *(float *)((char *)(arg0) + 148) = (float) 0.200000003f;
    *(float *)((char *)(arg0) + 152) = (float) 0.200000003f;
    *(float *)((char *)(arg0) + 156) = (float) 0.200000003f;
    *(int *)((char *)(arg0) + 160) = 0x3F800000;
    *(char *)((char *)(arg0) + 164) = 0;
    *(char *)((char *)(arg0) + 165) = 0;
    *(char *)((char *)(arg0) + 166) = 0;
    *(char *)((char *)(arg0) + 167) = 0;
    *(char *)((char *)(arg0) + 168) = 0;
    *(char *)((char *)(arg0) + 169) = 0;
    *(float *)((char *)(arg0) + 172) = (float) 0.100000001f;
    *(int *)((char *)(arg0) + 176) = 0;
    *(char *)((char *)(arg0) + 180) = 1;
    *(char *)((char *)(arg0) + 181) = 0;
    *(char *)((char *)(arg0) + 182) = 0;
    *(int *)((char *)(arg0) + 184) = 0x280;
    *(int *)((char *)(arg0) + 188) = 0x1C0;
    *(int *)((char *)(arg0) + 192) = 0;
    *(int *)((char *)(arg0) + 196) = -1;
    *(int *)((char *)(arg0) + 200) = -1;
    *(int *)((char *)(arg0) + 204) = -1;
    *(int *)((char *)(arg0) + 208) = -1;
    *(char *)((char *)(arg0) + 212) = 1;
    *(char *)((char *)(arg0) + 213) = 1;
    *(char *)((char *)(arg0) + 214) = 1;
    *(char *)((char *)(arg0) + 215) = 0;
    *(char *)((char *)(arg0) + 216) = 0;
    *(int *)((char *)(arg0) + 220) = 5;
    *(int *)((char *)(arg0) + 224) = 0x1E;
    *(char *)((char *)(arg0) + 228) = 0;
    *(char *)((char *)(arg0) + 229) = 0;
    *(int *)((char *)(arg0) + 232) = 0;
    *(int *)((char *)(arg0) + 236) = 0;
    FUN_002382e0((ViewerOptions_2382e0 *)arg0, -1, 0x1C0, 0x280, 0x447A0000, 0x42340000, 0x3F800000, 1);
    return arg0;
}

/* Matching construct: `group` is declared apart from `props` so the property set lands in the first saved register. */
void FUN_002382e0(ViewerOptions_2382e0 *opt, int, int, int, int, int, int, int) {
  int group;
  int props = ((PropertySet *)DAT_00586dc8[0])->props;
  group = FUN_00306360(props, DAT_004e9870, 0);
  if (group < 0) {
    group = FUN_00306360(props, DAT_004e9878, 0);
    if (group < 0) return;
  }
  if (DAT_004e9880) thunk_FUN_00306910(props, group, DAT_004e9880, &opt->extraCommandLine, opt->extraCommandLine, 0);
  if (DAT_004e9898) thunk_FUN_00306e50(props, group, DAT_004e9898, &opt->showBBox, opt->showBBox, 0);
  if (DAT_004e98a8) thunk_FUN_00306e50(props, group, DAT_004e98a8, &opt->showNormals, opt->showNormals, 0);
  if (DAT_004e98b8) FUN_001e71f0(props, group, DAT_004e98b8, &opt->normalsColor, &opt->normalsColor, 0);
  if (DAT_004e98d0) FUN_001e71f0(props, group, DAT_004e98d0, &opt->invalidStoredNormalsColor, &opt->invalidStoredNormalsColor, 0);
  if (DAT_004e98f0) FUN_001e71f0(props, group, DAT_004e98f0, &opt->scaledNormalsColor, &opt->scaledNormalsColor, 0);
  if (DAT_004e9910) thunk_FUN_003066b0(props, group, DAT_004e9910, &opt->invalidNormalsPrecision, 0, opt->invalidNormalsPrecision);
  if (DAT_004e9930) thunk_FUN_00306e50(props, group, DAT_004e9930, &opt->autoSelectCamera, opt->autoSelectCamera, 0);
  if (DAT_004e9950) thunk_FUN_003066b0(props, group, DAT_004e9950, &opt->horizontalFieldOfView, 0, opt->horizontalFieldOfView);
  if (DAT_004e9968) thunk_FUN_00306e50(props, group, DAT_004e9968, &opt->autoPlanes, opt->autoPlanes, 0);
  if (DAT_004e9980) thunk_FUN_003066b0(props, group, DAT_004e9980, &opt->defaultNearPlane, 0, opt->defaultNearPlane);
  if (DAT_004e99a0) thunk_FUN_003066b0(props, group, DAT_004e99a0, &opt->defaultFarPlane, 0, opt->defaultFarPlane);
  if (DAT_004e99b0) FUN_001e70a0(props, group, DAT_004e99b0, &opt->upVector, &opt->upVector, 0);
  if (DAT_004e99c0) thunk_FUN_00306e50(props, group, DAT_004e99c0, &opt->autoSceneLights, opt->autoSceneLights, 0);
  if (DAT_004e99d0) thunk_FUN_00306e50(props, group, DAT_004e99d0, &opt->autoHeadLight, opt->autoHeadLight, 0);
  if (DAT_004e99e0) thunk_FUN_00306e50(props, group, DAT_004e99e0, &opt->useSceneLights, opt->useSceneLights, 0);
  if (DAT_004e99f0) thunk_FUN_00306e50(props, group, DAT_004e99f0, &opt->useHeadLight, opt->useHeadLight, 0);
  if (DAT_004e9a00) thunk_FUN_00306e50(props, group, DAT_004e9a00, &opt->useHeadLightSpecular, opt->useHeadLightSpecular, 0);
  if (DAT_004e9a20) FUN_001e71f0(props, group, DAT_004e9a20, &opt->headLightDiffuse, &opt->headLightDiffuse, 0);
  if (DAT_004e9a40) FUN_001e71f0(props, group, DAT_004e9a40, &opt->headLightSpecular, &opt->headLightSpecular, 0);
  if (DAT_004e9a60) FUN_001e71f0(props, group, DAT_004e9a60, &opt->headLightAmbient, &opt->headLightAmbient, 0);
  if (DAT_004e9a78) FUN_001e71f0(props, group, DAT_004e9a78, &opt->clearColor, &opt->clearColor, 0);
  if (DAT_004e9a88) thunk_FUN_00306e50(props, group, DAT_004e9a88, &opt->wireframeMode, opt->wireframeMode, 0);
  if (DAT_004e9a98) thunk_FUN_00306e50(props, group, DAT_004e9a98, &opt->forceWireframe, opt->forceWireframe, 0);
  if (DAT_004e9ab0) thunk_FUN_00306e50(props, group, DAT_004e9ab0, &opt->backFaceCullingMode, opt->backFaceCullingMode, 0);
  if (DAT_004e9ad0) thunk_FUN_00306e50(props, group, DAT_004e9ad0, &opt->forceBackFaceCulling, opt->forceBackFaceCulling, 0);
  if (DAT_004e9ae8) thunk_FUN_00306e50(props, group, DAT_004e9ae8, &opt->alphaTest, opt->alphaTest, 0);
  if (DAT_004e9af8) thunk_FUN_00306e50(props, group, DAT_004e9af8, &opt->forceAlphaTest, opt->forceAlphaTest, 0);
  if (DAT_004e9b10) thunk_FUN_003066b0(props, group, DAT_004e9b10, &opt->alphaTestReference, 0, opt->alphaTestReference);
  if (DAT_004e9b28) thunk_FUN_003066b0(props, group, DAT_004e9b28, &opt->maxFrameRate, 0, opt->maxFrameRate);
  if (DAT_004e9b40) thunk_FUN_00306e50(props, group, DAT_004e9b40, &opt->optimizeTextures, opt->optimizeTextures, 0);
  if (DAT_004e9b58) thunk_FUN_00306e50(props, group, DAT_004e9b58, &opt->halfBuffer, opt->halfBuffer, 0);
  if (DAT_004e9b68) thunk_FUN_00306e50(props, group, DAT_004e9b68, &opt->palVideoMode, opt->palVideoMode, 0);
  if (DAT_004e9b78) thunk_FUN_003065f0(props, group, DAT_004e9b78, &opt->width, opt->width, 0);
  if (DAT_004e9b80) thunk_FUN_003065f0(props, group, DAT_004e9b80, &opt->height, opt->height, 0);
  if (DAT_004e9b88) thunk_FUN_003065f0(props, group, DAT_004e9b88, &opt->swapInterval, opt->swapInterval, 0);
  if (DAT_004e9b98) thunk_FUN_003065f0(props, group, DAT_004e9b98, &opt->colorBits, opt->colorBits, 0);
  if (DAT_004e9ba8) thunk_FUN_003065f0(props, group, DAT_004e9ba8, &opt->alphaBits, opt->alphaBits, 0);
  if (DAT_004e9bb8) thunk_FUN_003065f0(props, group, DAT_004e9bb8, &opt->depthBits, opt->depthBits, 0);
  if (DAT_004e9bc8) thunk_FUN_003065f0(props, group, DAT_004e9bc8, &opt->stencilBits, opt->stencilBits, 0);
  if (DAT_004e9be0) thunk_FUN_00306e50(props, group, DAT_004e9be0, &opt->reportVideoFormat, opt->reportVideoFormat, 0);
  if (DAT_004e9bf8) thunk_FUN_00306e50(props, group, DAT_004e9bf8, &opt->showLogo, opt->showLogo, 0);
  if (DAT_004e9c08) thunk_FUN_00306e50(props, group, DAT_004e9c08, &opt->showUI, opt->showUI, 0);
  if (DAT_004e9c10) thunk_FUN_00306e50(props, group, DAT_004e9c10, &opt->enableMayaControls, opt->enableMayaControls, 0);
  if (DAT_004e9c28) thunk_FUN_00306e50(props, group, DAT_004e9c28, &opt->benchmark, opt->benchmark, 0);
  if (DAT_004e9c40) thunk_FUN_003065f0(props, group, DAT_004e9c40, &opt->benchmarkSkipFrames, opt->benchmarkSkipFrames, 0);
  if (DAT_004e9c60) thunk_FUN_003065f0(props, group, DAT_004e9c60, &opt->benchmarkFrames, opt->benchmarkFrames, 0);
  if (DAT_004e9c70) thunk_FUN_00306e50(props, group, DAT_004e9c70, &opt->columnStatistics, opt->columnStatistics, 0);
  if (DAT_004e9c90) thunk_FUN_00306e50(props, group, DAT_004e9c90, &opt->allocateVisualContextInScratchPad, opt->allocateVisualContextInScratchPad, 0);
}

int Gap__Insight__igSerialScheduler__vfunc_22(void) {
    return DAT_0056dab0[0];
}

int Gap__Insight__igFilterMessageDispatcher__vfunc_22(void) {
    return DAT_0056db10[0];
}

int Gap__Insight__igMessageDefaultReceiver__vfunc_22(void) {
    return DAT_0056db30[0];
}

int Gap__Insight__igInsightCore__vfunc_22(void) {
    return DAT_0056db60[0];
}

int Gap__Insight__igWindowResizeEventReceiver__vfunc_22(void) {
    return DAT_0056dc00[0];
}

int Gap__Gui__igEventReceiver__vfunc_23(void) {
    return 0;
}

/* Slot 22, empty override returning 0. */
int Gap__Bec__beKeyboardReceiver__vfunc_22(void) {
    return 0;
}

/* Slot 23, empty override returning 0. */
int Gap__Bec__beKeyboardReceiver__vfunc_23(void) {
    return 0;
}

/* Slot 24, empty override returning 0. */
int Gap__Bec__beKeyboardReceiver__vfunc_24(void) {
    return 0;
}

/* Slot 25, empty override returning 0. */
int Gap__Bec__beKeyboardReceiver__vfunc_25(void) {
    return 0;
}

/* Slot 26, empty override returning 0. */
int Gap__Bec__beKeyboardReceiver__vfunc_26(void) {
    return 0;
}

/* Slot 27, empty override returning 0. */
int Gap__Bec__beKeyboardReceiver__vfunc_27(void) {
    return 0;
}

/* Slot 28, empty override returning 0. */
int Gap__Bec__beKeyboardReceiver__vfunc_28(void) {
    return 0;
}

/* Slot 29, empty override returning 0. */
int Gap__Bec__beKeyboardReceiver__vfunc_29(void) {
    return 0;
}

/* Slot 31, empty override returning 0. */
int Gap__Bec__beKeyboardReceiver__vfunc_31(void) {
    return 0;
}

/* Slot 32, empty override returning 0. */
int Gap__Bec__beKeyboardReceiver__vfunc_32(void) {
    return 0;
}

int Gap__Insight__igFlushRenderer__vfunc_22(void) {
    return DAT_0056dc48[0];
}

void Gap__Insight__igFlushRenderer__vfunc_25(void) {

}

void Gap__Insight__igFlushRenderer__vfunc_23(void) {

}

void Gap__Insight__igFlushRenderer__vfunc_24(void) {

}

int Gap__Insight__igInfoManagerList__vfunc_22(void) {
    return DAT_0056dc30[0];
}

int Gap__Insight__igInfoManagerOrderedList__vfunc_22(void) {
    return DAT_0056dc28[0];
}

int Gap__Core__igDependencyOrderedList__vfunc_22(void) {
    return DAT_00586738[0];
}

int Gap__Insight__igViewportResizedMessage__vfunc_22(void) {
    return DAT_0056dc10[0];
}

int Gap__Gui__igEventReceiver__vfunc_22(void) {
    return DAT_0058c570[0];
}

/* Slot 30, empty override returning 0. */
int Gap__Bec__beKeyboardReceiver__vfunc_30(void) {
    return 0;
}

int Gap__Insight__igInsightPluginList__vfunc_22(void) {
    return DAT_0056db50[0];
}

int Gap__Insight__igMessageFilter__vfunc_22(void) {
    return DAT_0056daf8[0];
}

int Gap__Insight__igMessageFilterList__vfunc_22(void) {
    return DAT_0056daf0[0];
}

int Gap__Insight__igMessageReceiverList__vfunc_22(void) {
    return DAT_0056dae0[0];
}

int Gap__Insight__igMessenger__vfunc_22(void) {
    return DAT_0056dac8[0];
}

int Gap__Insight__igMessage__vfunc_22(void) {
    return (int)g_igMessage_metaObject[0];
}

int FUN_00238cf0(void) {
    return g_igRenderer_metaObject[0];
}

int Gap__Insight__igInsightPluginList__vfunc_24(void) {
    return DAT_0056db58[0];
}

int Gap__Insight__igMessageFilterList__vfunc_24(void) {
    return DAT_0056daf8[0];
}

int Gap__Insight__igInfoManagerList__vfunc_24(void) {
    return DAT_0056dc38[0];
}

int Gap__Insight__igMessageReceiverList__vfunc_24(void) {
    return DAT_0056dae8[0];
}

