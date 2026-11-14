#ifndef DW4_INSIGHT_LIBRARY_H
#define DW4_INSIGHT_LIBRARY_H

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
extern "C" int thunk_Memory_FreeBuffer(...);
extern "C" int DAT_0052d060[4];
struct S {
    void *f0;
    char pad[4];
    void *f8;
};
extern "C" void *FUN_00230f70(struct S *arg0, short arg1);
extern "C" int g_igRenderer_metaObject[4];
extern "C" int FUN_00231010(void);
extern "C" igMetaObject *g_igMessage_metaObject[4];
extern "C" igMetaObject *FUN_00231020(void);
extern "C" int StringChunk_ReleaseHeader(...);
extern "C" int DAT_0052cf80[4];
extern "C" int g_igNamedObject_vtable[4];
extern "C" void *FUN_00231030(struct S *arg0, short arg1);
extern "C" igMetaObject *g_igInfoManager_metaObject[4];
extern "C" igMetaObject *FUN_002310d0(void);
extern "C" igMetaObject *g_igSerialScheduler_metaObject[4];
extern "C" igMetaObject *igSerialScheduler_GetMetaObject(void);
struct T { int word0; int references; };
extern "C" int DAT_0052c830[4];
extern "C" char *g_objectSystem[4];
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
extern "C" int __dl__FPv(...);
extern "C" void **FUN_00231210(void **arg0, long long arg1);
extern "C" void FUN_00231290(void);
extern "C" char igInsightScheduler_GetPublishedMetaObject[];
extern "C" char g_igSerialScheduler_callbackList[];
extern "C" char igSerialScheduler_className[];
extern "C" int igMetaObject_RegisterClass(...);
extern "C" void igSerialScheduler_Register(void);
extern "C" void thunk_igSerialScheduler_GetMetaObject(void);
extern "C" igMetaObject *g_igInsightScheduler_metaObject[4];
extern "C" igMetaObject *FUN_00231330(void);
extern "C" int igMetaObject_CreateFields(...);
extern "C" void *igMetaObject_GetFieldAt(...);
extern "C" int igMetaObject_GetFieldCount(...);
extern "C" int igMetaObject_NameFields(...);
extern "C" int g_igSerialScheduler_ctorTable[4];
extern "C" int g_igSerialScheduler_fieldTable[4];
extern "C" int DAT_00497fa0[4];
extern "C" int DAT_00497fa8[4];
extern "C" void igSerialScheduler_InitFields(void);
extern "C" igMetaObject *igMetaObject_Create(...);
extern "C" int Memory_GetAllocatorBySelector(...);
extern "C" igMetaObject *g_igMessenger_metaObject[4];
extern "C" int kIGMemoryPoolHandleMetaData[4];
extern "C" igMetaObject *FUN_00231400(void);
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
extern "C" int g_igMessenger_ctorTable[4];
extern "C" int g_igMessenger_fieldTable[4];
extern "C" int DAT_00497fc8[4];
extern "C" int DAT_00497fd0[4];
extern "C" void igMessenger_InitFields(void);
extern "C" igMetaObject *igMessage_GetMetaObject(void);
extern "C" int DAT_0052d000[4];
struct Obj_2316c0 { int *vt; int b; };
extern "C" int igMessage_GetVTable(void);
extern "C" void FUN_00231700(void);
extern "C" char igMessage_className[];
extern "C" void igMessage_Register(void);
extern "C" void thunk_igMessage_GetMetaObject(void);
extern "C" igMetaObject *g_igMessageReceiverList_metaObject[4];
extern "C" igMetaObject *FUN_00231790(void);
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
extern "C" igMetaObject *g_igMessageFilterList_metaObject[4];
extern "C" igMetaObject *FUN_002319d0(void);
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
extern "C" int igMetaObject_GetOrCreateMetaObject(...);
extern "C" int g_igMessageFilter_ctorTable[4];
extern "C" int g_igMessageFilter_fieldTable[4];
extern "C" int DAT_00498008[4];
extern "C" int DAT_00498010[4];
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
extern "C" igMetaObject *g_igMessageDispatcher_metaObject[4];
extern "C" igMetaObject *FUN_00231fe0(void);
extern "C" int g_igFilterMessageDispatcher_ctorTable[4];
extern "C" int g_igFilterMessageDispatcher_fieldTable[4];
extern "C" int DAT_00498030[4];
extern "C" int DAT_00498038[4];
extern "C" void igFilterMessageDispatcher_InitFields(void);
extern "C" igMetaObject *FUN_002320b0(void);
extern "C" igMetaObject *igMessageDispatcher_GetMetaObject(void);
extern "C" void FUN_00232150(void);
extern "C" char igMessageDispatcher_className[];
extern "C" int igMessageDispatcher_SetAbstractProxy_002321e0[4];
extern "C" void igMessageDispatcher_Register(void);
extern "C" void thunk_igMessageDispatcher_GetMetaObject(void);
extern "C" void FUN_002321e0(void);
extern "C" void igMessageDefaultReceiver_CreateInstance(int arg0);
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
extern "C" igMetaObject *FUN_002323c0(void);
extern "C" int g_igMessageDefaultReceiver_ctorTable[4];
extern "C" int g_igMessageDefaultReceiver_fieldTable[4];
extern "C" int DAT_00498058[4];
extern "C" int DAT_00498060[4];
extern "C" int g_igObject_metaObject[4];
extern "C" void igMessageDefaultReceiver_InitFields(void);
extern "C" igMetaObject *FUN_00232470(void);
extern "C" igMetaObject *igInsightScheduler_GetMetaObject(void);
extern "C" void FUN_00232510(void);
extern "C" char igInsightScheduler_className[];
extern "C" int igInsightScheduler_SetAbstractProxy_002325a0[4];
extern "C" void igInsightScheduler_Register(void);
extern "C" void thunk_igInsightScheduler_GetMetaObject(void);
extern "C" void FUN_002325a0(void);
extern "C" igMetaObject *g_igInsightPluginList_metaObject[4];
extern "C" igMetaObject *FUN_002325c0(void);
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
extern "C" igMetaObject *g_igInsightCore_metaObject[4];
extern "C" igMetaObject *FUN_00232840(void);
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
extern "C" int igTimer_GetOrCreateMetaObject(...);
extern "C" int igInfoList_GetOrCreateMetaObject(...);
extern "C" int FUN_0044c250(...);
extern "C" int FUN_0044c4d0(...);
extern "C" int FUN_004513b0(...);
extern "C" int g_igInsightCore_ctorTable[4];
extern "C" int g_igInsightCore_fieldTable[4];
extern "C" int DAT_00498150[4];
extern "C" int DAT_004981a0[4];
extern "C" void igInsightCore_InitFields(void);
extern "C" void thunk_FUN_00236140(void);
extern "C" igMetaObject *g_igWindowResizeEventReceiver_metaObject[4];
extern "C" igMetaObject *FUN_00233080(void);
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
extern "C" int g_igEventReceiver_metaObject[4];
extern "C" int FUN_00233200(void);
extern "C" int g_igWindowResizeEventReceiver_ctorTable[4];
extern "C" int g_igWindowResizeEventReceiver_fieldTable[4];
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
extern "C" int g_igViewportResizedMessage_ctorTable[4];
extern "C" int g_igViewportResizedMessage_fieldTable[4];
extern "C" int DAT_00498228[4];
extern "C" int DAT_00498230[4];
extern "C" void igViewportResizedMessage_InitFields(void);
extern "C" igMetaObject *g_igInfoManagerOrderedList_metaObject[4];
extern "C" igMetaObject *FUN_00233480(void);
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
extern "C" int g_igDependencyOrderedList_metaObject[4];
extern "C" int FUN_00233740(void);
extern "C" igMetaObject *g_igInfoManagerList_metaObject[4];
extern "C" igMetaObject *FUN_00233750(void);
extern "C" igMetaObject *igInfoManagerList_GetMetaObject(void);
struct Obj_2337f0 { int *vt; char pad[28]; };
extern "C" int DAT_0052caf0[4];
extern "C" int igInfoManagerList_GetVTable(void);
extern "C" void FUN_00233830(void);
extern "C" char g_igInfoManagerList_callbackList[];
extern "C" char igInfoManagerList_className[];
extern "C" void igInfoManagerList_Register(void);
extern "C" void thunk_igInfoManagerList_GetMetaObject(void);
extern "C" igMetaObject *igInfoManager_GetMetaObject(void);
extern "C" void FUN_00233910(void);
extern "C" char igNamedObject_GetPublishedMetaObject[];
extern "C" char igNamedObject_Register[];
extern "C" char g_igInfoManager_callbackList[];
extern "C" char igInfoManager_className[];
extern "C" void igInfoManager_Register(void);
extern "C" void thunk_igInfoManager_GetMetaObject(void);
extern "C" int g_igInfoManager_ctorTable[4];
extern "C" int g_igInfoManager_fieldTable[4];
extern "C" int DAT_00498260[4];
extern "C" int DAT_00498268[4];
extern "C" void igInfoManager_InitFields(void);
extern "C" igMetaObject *g_igFlushRenderer_metaObject[4];
extern "C" igMetaObject *FUN_00233a40(void);
union U_233a90 { int vt; int w[3]; char b[12]; };
extern "C" void igMetaObject_RunStaticInit(...);
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
extern "C" struct FlushShared *__nw__FUi(int size);
extern "C" int Vec3f_FromString(...);
extern "C" int FUN_001e6d80(...);
extern "C" void *igIntList_Create(int allocator);
extern "C" InternedStringList *igStringRefList_Create(int allocator);
extern "C" int StringPool_Allocate(...);
extern "C" int StringPool_Construct(...);
extern "C" char *StringPool_Intern(...);
extern "C" int StringList_CopyRetained(...);
extern "C" int StringList_AppendRetained(...);
extern "C" int List_Resize(IntList *list, int newCount, int elementSize);
extern "C" unsigned char g_useOwnerAllocator;
extern "C" int g_stringPool[4];
extern "C" int kIGMemoryPoolHandleCurrent[4];
extern "C" int kIGMemoryPoolHandleTemporary[4];
extern "C" struct FlushShared *DAT_0056dc50[4];
extern "C" int DAT_004e95d0[4];
extern "C" int text_true[4];
extern "C" int text_false[4];
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
            if (g_stringPool[0] == 0) {
                int pool = StringPool_Allocate(0x10);
                if (pool != 0) {
                    pool = StringPool_Construct(pool);
                }
                g_stringPool[0] = pool;
            }
            interned = StringPool_Intern(g_stringPool[0], text);
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
extern "C" void ViewerOptions_ReleaseShared(void);
extern "C" void FUN_00234d70(int self, int count, int *names);
extern "C" void FUN_00235370(ViewerOptions *opts, igStringRefList *args);
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
/* The frame-buffer format the viewer options request, and the one the visual context reports. */
struct FrameBufferFormat { int enabled; int width; int height; int colorBits; int alphaBits; int depthBits; int stencilBits; float scale; };
/* The video mode a visual context is set to: the NTSC or PAL refresh rate, the swap interval and
 * whether the frame keeps its full height. */
struct VideoMode {
    unsigned char enable;
    unsigned char interlace;
    int outputFormat;
    int fullHeight;
    float refreshRate;
    int swapInterval;
    int pal;
};
struct VideoModeResult { int code; };
class igVisualContextView : public igVirtualObject {
public:
    virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7();
    virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15();
    virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23();
    virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31();
    virtual void d32(); virtual void d33(); virtual void d34(); virtual void d35(); virtual void d36(); virtual void d37(); virtual void d38(); virtual void d39();
    virtual void d40(); virtual void d41(); virtual void d42(); virtual void d43();
    /* Adds a frame buffer of the given format and returns its index. */
    virtual int addFrameBuffer(FrameBufferFormat *format);
    virtual void d45(); virtual void d46(); virtual void d47();
    virtual void d48(); virtual void d49(); virtual void d50(); virtual void d51();
    virtual int getColorBits(int frameBuffer) const;
    virtual int getAlphaBits(int frameBuffer) const;
    virtual int getDepthBits(int frameBuffer) const;
    virtual int getStencilBits(int frameBuffer) const;
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
    virtual void setClearColor(const Vec4 *color);
    virtual void d176(); virtual void d177(); virtual void d178(); virtual void d179(); virtual void d180(); virtual void d181(); virtual void d182(); virtual void d183();
    virtual void d184(); virtual void d185(); virtual void d186(); virtual void d187(); virtual void d188(); virtual void d189(); virtual void d190(); virtual void d191();
    virtual void d192(); virtual void d193(); virtual void d194(); virtual void d195(); virtual void d196(); virtual void d197(); virtual void d198(); virtual void d199();
    virtual void d200(); virtual void d201(); virtual void d202(); virtual void d203(); virtual void d204(); virtual void d205(); virtual void d206(); virtual void d207();
    virtual void d208(); virtual void d209(); virtual void d210(); virtual void d211(); virtual void d212(); virtual void d213(); virtual void d214(); virtual void d215();
    virtual void d216(); virtual void d217(); virtual void d218(); virtual void d219(); virtual void d220(); virtual void d221(); virtual void d222(); virtual void d223();
    virtual void d224(); virtual void d225(); virtual void d226(); virtual void d227(); virtual void d228(); virtual void d229(); virtual void d230();
    /* Turns p2 capability 0 on or off. */
    virtual void setCapability0(int enable);
    virtual void d232(); virtual void d233(); virtual void d234(); virtual void d235(); virtual void d236(); virtual void d237(); virtual void d238(); virtual void d239();
    virtual void d240(); virtual void d241(); virtual void d242(); virtual void d243(); virtual void d244(); virtual void d245(); virtual void d246(); virtual void d247();
    virtual void d248(); virtual void d249(); virtual void d250();
    virtual VideoModeResult setVideoMode(VideoMode *mode);
};
class igWindowView : public igVirtualObject {
public:
    virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7();
    virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15();
    virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21();
    /* Opens the window with its title and size; 0 when it cannot. */
    virtual int open(const char *title, int width, int height);
    virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30();
    virtual void d31(); virtual void d32(); virtual void d33(); virtual void d34(); virtual void d35(); virtual void d36();
    virtual int setVisualContext(igVisualContextView *context);
};
extern "C" igWindowView *igWindow_CreateInstance(int allocator);
extern "C" igVisualContextView *igVisualContext_CreateInstance(int allocator);
extern "C" int igReportError(const char *format, ...);
extern "C" unsigned char GPR_00554bd0;
extern "C" char DAT_004e96f8[];
extern "C" char DAT_004e97d0[];
extern "C" char DAT_004e9800[];
extern "C" int kIGMemoryPoolHandleFast[4];
/* The head of newlib's struct _reent. */
struct _reent { int _errno; struct __sFILE *_stdin, *_stdout, *_stderr; };
extern "C" struct _reent *_impure_ptr;
extern "C" int fflush(struct __sFILE *stream);
class igFlushRendererView {
public:
    int _vtable;
    unsigned int _refCount;
    igVisualContextView *_visualContext;
};
extern "C" void Gap__Insight__igFlushRenderer__vfunc_26(igFlushRendererView *self);
struct NamedObject : public igObject { int name; };
extern "C" NamedObject *igFolder_Create(...);
extern "C" int igFolder_SetFolderName(...);
extern "C" int igPluginHelper_AddRepository(...);
extern "C" int text_plugins[4];
extern "C" int text_insight[4];
extern "C" int text_Insight[4];
extern "C" int kIGMemoryPoolHandleSystem[4];
struct G { char p[76]; int f76; };
extern "C" void FUN_00236140(void);
struct TextValue : public igObject { char *text; };
extern "C" TextValue *igStringObj_Create(int allocator);
extern "C" void igStringObj_Set(TextValue *value, const char *text);
extern "C" void igStringObj_SetInt(TextValue *value, int number, const char *format);
extern "C" int kIGMemoryPoolHandleString[4];
extern "C" char *g_stringObjEmptyText[4];
extern "C" char text_Requested_format[];
extern "C" char text_default[];
extern "C" char DAT_004e9780[];
extern "C" char text_color_s[];
extern "C" char text_alpha_s[];
extern "C" char text_depth_s[];
extern "C" char DAT_004e97b8[];
extern "C" FrameBufferFormat ViewerOptions_GetRequestedFormat(ViewerOptions_2382e0 *options);
extern "C" igSmartPointer<igWindowView> Viewer_CreateDisplay(int allocator);
struct ResizeEvent : public igObject { float origin[2]; float size[2]; };
extern "C" int igObject_GetAllocator(...);
extern "C" float DAT_004e0fa0[4];
extern "C" float DAT_004e0fa4[4];
struct WindowInfo { char p[40]; int f40; };
struct Receiver { char p[8]; WindowInfo *f8; };
extern "C" int Gap__Insight__igWindowResizeEventReceiver__vfunc_32(Receiver *self, int width, int height);
extern "C" int FUN_00236b70(...);
extern "C" int igRendererOrderedList_Append(...);
class DW4VC_92_0 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual int vX(); };
extern "C" void igInsightCore_AddManager(void *arg0, void *arg1);
extern "C" int igObjectList_RemoveRetained(...);
class DW4VC_96_0 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual int vX(); };
extern "C" void igInsightCore_RemoveManager(void *arg0, void *arg1);
struct S12 { char pad[12]; void *f12; };
class DW4VC_96_1 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual int vX(int); };
class DW4VC_104_0 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual int vX(); };
extern "C" void igInsightCore_AddToScheduler(S12 *arg0, int arg1);
struct S236;
class DW4VC_100_1 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual int vX(int); };
struct S236 { int a, b, c; void *p; };
extern "C" void igInsightCore_RemoveFromScheduler(S236 *arg0, int arg1);
struct Instance : public igObject { };
extern "C" int igMetaObject_CountTree(int);
extern "C" int igMetaObject_GetTreeNode(int, int);
extern "C" igSmartPointer<Instance> igMetaObject_CreateInstanceRef(int, int);
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
extern "C" void igInsightCore_AddRenderer(void *arg0, int arg1);
extern "C" int g_resultSuccess[4];
typedef struct Obj_236f30 { char pad[28]; int f28; } Obj_236f30;
extern "C" void igInsightCore_RemoveRenderer(Obj_236f30 *arg0, int arg1);
struct Obj_236f80 { virtual int a0(); virtual int a1(); virtual int a2(); virtual int a3(); virtual int a4(); virtual int a5(); virtual int a6(); virtual int a7(); virtual int a8(); virtual int a9(); virtual int a10(); virtual int a11(); virtual int a12(); virtual int a13(); virtual int a14(); virtual int a15(); virtual int a16(); virtual int a17(); virtual int a18(); virtual int a19(); virtual int v20(); };
struct List { int pad[2]; unsigned int count; int pad2; Obj_236f80 **arr; };
struct Mid { int pad[2]; List *list; };
struct Self { int pad[2]; Mid *mid; };
extern "C" Obj_236f80 *igInsightCore_FindManager(Self *arg0, int arg1);
extern "C" int FUN_00237010(void);
extern "C" int igInsightCore_AddRendererOrder(int *p);
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
extern "C" int igDependencyOrderedList_AddDependency(...);
extern "C" int igDependencyOrderedList_AddCheckPoint(...);
extern "C" int igEventDispatcher_AddReceiver(...);
extern "C" int Gap__Core__igObject__resetFields(...);
extern "C" int text_Clear_done[4];
extern "C" int text_Scenes_done[4];
extern "C" int text_Overlays_done[4];
struct A_237300 { char pad[28]; int f28; int f32; int f36; char pad40[4]; int f44; char pad48[24]; int f72; };
struct StringRef_237300 {
    int *p;
    StringRef_237300(int *text) {
        int *interned;
        if (text == 0) {
            interned = 0;
        } else {
            if (g_stringPool[0] == 0) {
                int pool = StringPool_Allocate(16);
                if (pool != 0) pool = StringPool_Construct(pool);
                g_stringPool[0] = pool;
            }
            interned = (int *)StringPool_Intern(g_stringPool[0], text);
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
extern "C" void igMessenger_AddReceiver(igMessageDispatcherOwnerView *self);
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
extern "C" int igDependencyOrderedList_RemoveDependency(...);
extern "C" void Gap__Insight__igSerialScheduler__vfunc_28(S0 *arg0, int arg1, int arg2);
extern "C" int igDependencyOrderedList_RemoveDependencies(...);
extern "C" void Gap__Insight__igSerialScheduler__vfunc_29(int a0);
extern "C" float DAT_004e105c[4];
extern "C" float DAT_004e1060[4];
extern "C" float DAT_004e1174[4];
extern "C" float DAT_004e1178[4];
extern "C" float DAT_004e117c[4];
extern "C" void *ViewerOptions_Construct(void *arg0);
/* Saves the Alchemy viewer (INSIGHT) options into the property tree: the INSIGHT group is looked
 * up in the property set held by the global (+56), falling back to 'Viewer', and each option is
 * written under its string name. Every write is guarded by its name pointer (the original option
 * table can drop a name); the guards are kept because the compiler does not fold them. Callee
 * names come from their roles: StoreString (thunk_igRegistry_GetValueString), StoreByte (thunk_igRegistry_GetValueBool),
 * StoreFloat (thunk_igRegistry_GetValueFloat), StoreInt (thunk_igRegistry_GetValueInt), StoreVec4 (FUN_001e71f0),
 * StoreVec3 (FUN_001e70a0). */
typedef struct PropertySet { char pad[56]; int props; } PropertySet;
extern "C" char INSIGHT[];
extern "C" char text_Viewer[];
extern "C" char text_extraCommandLine[];
extern "C" char text_showBBox[];
extern "C" char text_showNormals[];
extern "C" char text_normalsColor[];
extern "C" char text_invalidStoredNormalsColor[];
extern "C" char text_scaledNormalsColor[];
extern "C" char text_invalidNormalsPrecision[];
extern "C" char text_autoSelectCamera[];
extern "C" char text_horizontalFieldOfView[];
extern "C" char text_autoPlanes[];
extern "C" char text_defaultNearPlane[];
extern "C" char text_defaultFarPlane[];
extern "C" char text_upVector[];
extern "C" char text_autoSceneLights[];
extern "C" char text_autoHeadLight[];
extern "C" char text_useSceneLights[];
extern "C" char text_useHeadLight[];
extern "C" char text_useHeadLightSpecular[];
extern "C" char text_headLightDiffuse[];
extern "C" char text_headLightSpecular[];
extern "C" char text_headLightAmbient[];
extern "C" char text_clearColor[];
extern "C" char text_wireframeMode[];
extern "C" char text_forceWireframe[];
extern "C" char text_backFaceCullingMode[];
extern "C" char text_forceBackFaceCulling[];
extern "C" char text_alphaTest[];
extern "C" char text_forceAlphaTest[];
extern "C" char text_alphaTestReference[];
extern "C" char text_maxFrameRate[];
extern "C" char text_optimizeTextures[];
extern "C" char text_halfBuffer[];
extern "C" char text_palVideoMode[];
extern "C" char text_width[];
extern "C" char text_height[];
extern "C" char text_swapInterval[];
extern "C" char text_colorBits[];
extern "C" char text_alphaBits[];
extern "C" char text_depthBits[];
extern "C" char text_stencilBits[];
extern "C" char text_reportVideoFormat[];
extern "C" char text_showLogo[];
extern "C" char text_showUI[];
extern "C" char text_enableMayaControls[];
extern "C" char text_benchmark[];
extern "C" char text_benchmarkSkipFrames[];
extern "C" char text_benchmarkFrames[];
extern "C" char text_columnStatistics[];
extern "C" char text_allocateVisualContextInScratchPa[];
extern "C" int igRegistry_GetSectionIndex(int, char *, int);
extern "C" int thunk_igRegistry_GetValueString(int, int, char *, char **, char *, int);
extern "C" int thunk_igRegistry_GetValueBool(int, int, char *, unsigned char *, int, int);
extern "C" int thunk_igRegistry_GetValueFloat(int, int, char *, float *, int, float);
extern "C" int thunk_igRegistry_GetValueInt(int, int, char *, int *, int, int);
extern "C" int FUN_001e71f0(int, int, char *, Vec4 *, Vec4 *, int);
extern "C" int FUN_001e70a0(int, int, char *, Vec3 *, Vec3 *, int);
extern "C" void FUN_002382e0(ViewerOptions_2382e0 *opt, int, int, int, int, int, int, int);
extern "C" igMetaObject *Gap__Insight__igSerialScheduler__vfunc_22(void);
extern "C" igMetaObject *Gap__Insight__igFilterMessageDispatcher__vfunc_22(void);
extern "C" igMetaObject *Gap__Insight__igMessageDefaultReceiver__vfunc_22(void);
extern "C" igMetaObject *Gap__Insight__igInsightCore__vfunc_22(void);
extern "C" igMetaObject *Gap__Insight__igWindowResizeEventReceiver__vfunc_22(void);
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
extern "C" igMetaObject *Gap__Insight__igFlushRenderer__vfunc_22(void);
extern "C" void Gap__Insight__igFlushRenderer__vfunc_25(void);
extern "C" void Gap__Insight__igFlushRenderer__vfunc_23(void);
extern "C" void Gap__Insight__igFlushRenderer__vfunc_24(void);
extern "C" igMetaObject *Gap__Insight__igInfoManagerList__vfunc_22(void);
extern "C" igMetaObject *Gap__Insight__igInfoManagerOrderedList__vfunc_22(void);
extern "C" int Gap__Core__igDependencyOrderedList__vfunc_22(void);
extern "C" igMetaObject *Gap__Insight__igViewportResizedMessage__vfunc_22(void);
extern "C" int Gap__Gui__igEventReceiver__vfunc_22(void);
extern "C" igMetaObject *Gap__Insight__igInsightPluginList__vfunc_22(void);
extern "C" igMetaObject *Gap__Insight__igMessageFilter__vfunc_22(void);
extern "C" igMetaObject *Gap__Insight__igMessageFilterList__vfunc_22(void);
extern "C" igMetaObject *Gap__Insight__igMessageReceiverList__vfunc_22(void);
extern "C" igMetaObject *Gap__Insight__igMessenger__vfunc_22(void);
extern "C" int Gap__Insight__igMessage__vfunc_22(void);
extern "C" int g_igRenderer_metaObject[4];
extern "C" int FUN_00238cf0(void);
extern "C" igMetaObject *Gap__Insight__igInsightPluginList__vfunc_24(void);
extern "C" igMetaObject *Gap__Insight__igMessageFilterList__vfunc_24(void);
extern "C" igMetaObject *Gap__Insight__igInfoManagerList__vfunc_24(void);
extern "C" igMetaObject *Gap__Insight__igMessageReceiverList__vfunc_24(void);

#endif
