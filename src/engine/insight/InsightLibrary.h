#ifndef DW4_INSIGHT_LIBRARY_H
#define DW4_INSIGHT_LIBRARY_H

#include "dw4/support/reflected.h"
#include "dw4/core/igSmartPointer.h"
#include "dw4/maths/igVec3f.h"
#include "dw4/core/igobject_release.h"
#include "dw4/insight/fun_00235370_refs.h"
#include "dw4/viewer/ViewerOptions.h"
#include "dw4/insight/igInsightCore.h"
#include "dw4/insight/igInfoManager.h"
#include "dw4/insight/igInsightPlugin.h"
#include "dw4/insight/igMessage.h"
#include "dw4/insight/igMessageDefaultReceiver.h"
#include "dw4/insight/igMessenger.h"
#include "dw4/insight/igViewportResizedMessage.h"
#define ReleaseObject(obj) do { igObject *held = (obj); IG_OBJECT_RELEASE(held); } while (0)
#define OPTION_BOOL(name, help, value)  { const char *optionName = name; if (optionName) igCommandLine_PrintOptionBool(optionName, help, value); }
#define OPTION_INT(name, help, value)   { const char *optionName = name; if (optionName) igCommandLine_PrintOptionInt(optionName, help, value); }
#define OPTION_FLOAT(name, help, value) { const char *optionName = name; if (optionName) igCommandLine_PrintOptionFloat(optionName, help, value); }

class igMemoryPoolView;
#include "dw4/core/igIntMetaField.h"
#include "dw4/core/igLongMetaField.h"
#include "dw4/core/igObjectRefMetaField.h"
#include "dw4/core/igStructMetaField.h"
#include "dw4/maths/igVec2fMetaField.h"
#include "dw4/core/igMetaObject.h"
#include "dw4/core/igObject.h"
#include "dw4/core/igInfoList.h"
#include "dw4/gui/igRendererOrderedList.h"
#include "dw4/gui/igEventDispatcher.h"
#include "dw4/gui/igClearRenderer.h"
#include "dw4/core/igTimer.h"
#include "dw4/core/igReport.h"
#include "dw4/core/igPluginHelper.h"
extern "C" void igWindow_EnsureRegistered(void);
#include "dw4/gfx/igVisualContext.h"
extern "C" void InsightLibrary_MarkRegistered(void);
struct S {
    void *f0;
    char pad[4];
    void *f8;
};
extern "C" void *FUN_00230f70(struct S *arg0, short arg1);
#include "dw4/gui/igRenderer.h"
extern "C" igMetaObject *FUN_00231010(void);
extern "C" igMetaObject *g_igMessage_metaObject;
extern "C" igMetaObject *igMessage_GetPublishedMetaObject(void);
#include "dw4/core/StringPool.h"
#include "dw4/core/igNamedObject.h"
extern "C" igMetaObject *g_igInfoManager_metaObject;
extern "C" igMetaObject *igInfoManager_GetPublishedMetaObject(void);
extern "C" igMetaObject *g_igSerialScheduler_metaObject;
extern "C" igMetaObject *igSerialScheduler_GetMetaObject(void);
struct T { int word0; int references; };
extern "C" int g_igSerialScheduler_vtable[4];
#include "dw4/core/igObjectSystem.h"
struct Obj {
    int *vt; char p4[4]; T *m8; T *m12; 
    inline void rel8() {
        T **self = &m8;
        if (self) {
            T *object = *self;
            if (object) {
                --object->references;
                if (((unsigned long long)(long long)object->references & 0x7fffffULL) == 0)
                    igObject_Destroy((igObject *)object);
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
                    igObject_Destroy((igObject *)object);
            }
        }
    }
};
extern "C" int igSerialScheduler_GetVTable(void);
extern "C" void **igSmartPointer_igInfoManagerOrderedList_Destruct(void **arg0, long long arg1);
extern "C" void igSerialScheduler_EnsureRegistered(void);
extern "C" igMetaObject *igInsightScheduler_GetPublishedMetaObject(void);
extern "C" CallbackArray *igSerialScheduler_Register(void);
extern "C" void igSerialScheduler_GetMetaObjectFunction(void);
extern "C" igMetaObject *g_igInsightScheduler_metaObject;
extern "C" igMetaObject *igInsightScheduler_GetPublishedMetaObject(void);
extern "C" void igSerialScheduler_InitFields(void);
#include "dw4/core/igMemoryPoolContext.h"
extern "C" igMetaObject *g_igMessenger_metaObject;
extern "C" igMetaObject *igMessenger_GetOrCreateMetaObject(void);
extern "C" igMetaObject *igMessenger_GetMetaObject(void);
struct Ref { int pad; union { int w; struct { unsigned cnt:23; unsigned f:9; } b; } u; };
struct W { int *vt; int f4; struct Ref *ref; int fc; };
extern "C" int g_igMessenger_vtable[4];
extern "C" int igMessenger_GetVTable(void);
extern "C" void igMessenger_EnsureRegistered(void);
extern "C" CallbackArray *igMessenger_Register(void);
extern "C" void igMessenger_GetMetaObjectFunction(void);
extern "C" void igMessenger_InitFields(void);
extern "C" igMetaObject *igMessage_GetMetaObject(void);
extern "C" int g_igMessage_vtable[4];
struct Obj_2316c0 { int *vt; int b; };
extern "C" int igMessage_GetVTable(void);
extern "C" void igMessage_EnsureRegistered(void);
extern "C" void igMessage_GetMetaObjectFunction(void);
extern "C" igMetaObject *g_igMessageReceiverList_metaObject;
extern "C" igMetaObject *igMessageReceiverList_GetOrCreateMetaObject(void);
extern "C" igMetaObject *igMessageReceiverList_GetMetaObject(void);
struct Obj_231830 { int *vt; char pad[28]; };
extern "C" int g_igMessageReceiverList_vtable[4];
extern "C" int igMessageReceiverList_GetVTable(void);
extern "C" void igMessageReceiverList_EnsureRegistered(void);
#include "dw4/core/igObjectList.h"
extern "C" CallbackArray *igMessageReceiverList_Register(void);
extern "C" void igMessageReceiverList_GetMetaObjectFunction(void);
extern "C" igMetaObject *g_igMessageReceiver_metaObject;
extern "C" igMetaObject *igMessageReceiver_GetMetaObject(void);
extern "C" void igMessageReceiver_EnsureRegistered(void);
extern "C" CallbackArray *igMessageReceiver_Register(void);
extern "C" void igMessageReceiver_GetMetaObjectFunction(void);
extern "C" igMetaObject *g_igMessageFilterList_metaObject;
extern "C" igMetaObject *igMessageFilterList_GetOrCreateMetaObject(void);
extern "C" igMetaObject *igMessageFilterList_GetMetaObject(void);
struct Obj_231a70 { int *vt; char pad[28]; };
extern "C" int g_igMessageFilterList_vtable[4];
extern "C" int igMessageFilterList_GetVTable(void);
extern "C" void igMessageFilterList_EnsureRegistered(void);
extern "C" CallbackArray *igMessageFilterList_Register(void);
extern "C" void igMessageFilterList_GetMetaObjectFunction(void);
extern "C" int FUN_00231b40(int arg0);
extern "C" igMetaObject *g_igMessageFilter_metaObject;
extern "C" igMetaObject *igMessageFilter_GetMetaObject(void);
typedef struct S_ref { char pad4[4]; int f4; } S_ref;
union U { int vt; int w[4]; void *p[4]; char b[16]; };
extern "C" int g_igMessageFilter_vtable[4];
extern "C" int igMessageFilter_GetVTable(void);
extern "C" void igMessageFilter_EnsureRegistered(void);
extern "C" CallbackArray *igMessageFilter_Register(void);
extern "C" void igMessageFilter_GetMetaObjectFunction(void);
extern "C" void igMessageFilter_InitFields(void);
extern "C" igMetaObject *g_igFilterMessageDispatcher_metaObject;
extern "C" igMetaObject *igFilterMessageDispatcher_GetMetaObject(void);
extern "C" int g_igFilterMessageDispatcher_vtable[4];
extern "C" int igFilterMessageDispatcher_GetVTable(void);
extern "C" void igFilterMessageDispatcher_EnsureRegistered(void);
extern "C" igMetaObject *igMessageDispatcher_GetPublishedMetaObject(void);
extern "C" CallbackArray *igFilterMessageDispatcher_Register(void);
extern "C" void igFilterMessageDispatcher_GetMetaObjectFunction(void);
extern "C" igMetaObject *g_igMessageDispatcher_metaObject;
extern "C" igMetaObject *igMessageDispatcher_GetPublishedMetaObject(void);
extern "C" void igFilterMessageDispatcher_InitFields(void);
extern "C" igMetaObject *igMessageDispatcher_GetOrCreateMetaObject(void);
extern "C" igMetaObject *igMessageDispatcher_GetMetaObject(void);
extern "C" void igMessageDispatcher_EnsureRegistered(void);
extern "C" void igMessageDispatcher_SetAbstractProxy_002321e0(void);
extern "C" CallbackArray *igMessageDispatcher_Register(void);
extern "C" void igMessageDispatcher_GetMetaObjectFunction(void);
extern "C" void igMessageDispatcher_SetAbstractProxy(void);
extern "C" igMetaObject *g_igMessageDefaultReceiver_metaObject;
extern "C" igMetaObject *igMessageDefaultReceiver_GetMetaObject(void);
extern "C" int g_igMessageDefaultReceiver_vtable[4];
union U_232290 { int vt; char b[32]; };
extern "C" int igMessageDefaultReceiver_GetVTable(void);
extern "C" void igMessageDefaultReceiver_EnsureRegistered(void);
extern "C" igMetaObject *igMessageReceiver_GetPublishedMetaObject(void);
extern "C" CallbackArray *igMessageDefaultReceiver_Register(void);
extern "C" void igMessageDefaultReceiver_GetMetaObjectFunction(void);
extern "C" igMetaObject *igMessageReceiver_GetPublishedMetaObject(void);
extern "C" void igMessageDefaultReceiver_InitFields(void);
extern "C" igMetaObject *igInsightScheduler_GetOrCreateMetaObject(void);
extern "C" igMetaObject *igInsightScheduler_GetMetaObject(void);
extern "C" void igInsightScheduler_EnsureRegistered(void);
extern "C" void igInsightScheduler_SetAbstractProxy_002325a0(void);
extern "C" CallbackArray *igInsightScheduler_Register(void);
extern "C" void igInsightScheduler_GetMetaObjectFunction(void);
extern "C" void igInsightScheduler_SetAbstractProxy(void);
extern "C" igMetaObject *g_igInsightPluginList_metaObject;
extern "C" igMetaObject *igInsightPluginList_GetOrCreateMetaObject(void);
extern "C" igMetaObject *igInsightPluginList_GetMetaObject(void);
struct Obj_232660 { int *vt; char pad[28]; };
extern "C" int g_igInsightPluginList_vtable[4];
extern "C" int igInsightPluginList_GetVTable(void);
extern "C" void igInsightPluginList_EnsureRegistered(void);
extern "C" CallbackArray *igInsightPluginList_Register(void);
extern "C" void igInsightPluginList_GetMetaObjectFunction(void);
extern "C" igMetaObject *igInsightPlugin_GetMetaObject(void);
extern "C" void igInsightPlugin_EnsureRegistered(void);
extern "C" void igInsightPlugin_GetMetaObjectFunction(void);
extern "C" igMetaObject *g_igInsightCore_metaObject;
extern "C" igMetaObject *igInsightCore_GetMetaObject(void);
struct Obj_2328e0 { int *vt; int w1; int w2; int w3; int w4; int w5; int w6; int w7; int w8; int w9; int w10; int w11; int w12; int w13; int w14; int w15; int w16; int w17; int w18; int w19; int w20; int w21; int w22; int w23; int w24; int w25; int w26; int w27; };
extern "C" int igSmartPointer_igWindow_Destruct(...);
extern "C" int igSmartPointer_igTimer_Destruct(...);
extern "C" int g_igInsightCore_vtable[4];
extern "C" int igInsightCore_GetVTable(void);
struct S_temp_a0 { char pad4[4]; int f4; };
struct O { S_temp_a0 *m; };
extern "C" O *igSmartPointer_igInsightScheduler_Destruct(O *arg0, short arg1);
/* Deleting destructor; the deletion flag is a signed short. */
typedef struct ObjectRefTarget { int word0; int references; } ObjectRefTarget;
typedef struct ObjectRefWord { ObjectRefTarget *value; } ObjectRefWord;
typedef struct S_temp_a0_232b60 { char pad4[4]; int f4; } S_temp_a0_232b60;
extern "C" void **igSmartPointer_igEventDispatcher_Destruct(void **arg0, short arg1);
extern "C" ObjectRefWord *igSmartPointer_igWindowResizeEventReceiver_Destruct(ObjectRefWord *self,int delete_storage);
extern "C" void **igSmartPointer_igMessenger_Destruct(void **arg0, short arg1);
extern "C" ObjectRefWord *igSmartPointer_igClearRenderer_Destruct(ObjectRefWord *self,int delete_storage);
struct R { int vt; unsigned int rc; };
extern "C" struct R **igSmartPointer_igInsightPluginList_Destruct(struct R **arg0, short arg1);
extern "C" CallbackArray *igInsightCore_Register(void);
extern "C" void igInsightCore_GetMetaObjectFunction(void);
extern "C" int igWindow_GetOrCreateMetaObject(...);
extern "C" int igClearRenderer_GetOrCreateMetaObject(...);
extern "C" int igEventDispatcher_GetOrCreateMetaObject(...);
extern "C" void igInsightCore_InitFields(void);
extern "C" void igInsightCore_UserRegisterFunction(void);
extern "C" igMetaObject *g_igWindowResizeEventReceiver_metaObject;
extern "C" igMetaObject *igWindowResizeEventReceiver_GetOrCreateMetaObject(void);
extern "C" igMetaObject *igWindowResizeEventReceiver_GetMetaObject(void);
extern "C" int g_igWindowResizeEventReceiver_vtable[4];
struct Obj_233120 { int *vt; char pad[12]; };
extern "C" int igWindowResizeEventReceiver_GetVTable(void);
extern "C" void igWindowResizeEventReceiver_EnsureRegistered(void);
#include "dw4/gui/igEventReceiver.h"
extern "C" CallbackArray *igWindowResizeEventReceiver_Register(void);
extern "C" void igWindowResizeEventReceiver_GetMetaObjectFunction(void);
extern "C" igMetaObject *igEventReceiver_GetPublishedMetaObject(void);
extern "C" void igWindowResizeEventReceiver_InitFields(void);
extern "C" int FUN_002332b0(int arg0);
extern "C" igMetaObject *g_igViewportResizedMessage_metaObject;
struct Obj_233340 { int *vt; char pad[28]; };
extern "C" int g_igViewportResizedMessage_vtable[4];
extern "C" int igViewportResizedMessage_GetVTable(void);
extern "C" void igViewportResizedMessage_EnsureRegistered(void);
extern "C" CallbackArray *igViewportResizedMessage_Register(void);
extern "C" void igViewportResizedMessage_GetMetaObjectFunction(void);
extern "C" void igViewportResizedMessage_InitFields(void);
extern "C" igMetaObject *g_igInfoManagerOrderedList_metaObject;
extern "C" igMetaObject *igInfoManagerOrderedList_GetOrCreateMetaObject(void);
extern "C" igMetaObject *igInfoManagerOrderedList_GetMetaObject(void);
typedef struct { int *vt; int w[5]; } Obj_233520;
extern "C" int g_igInfoManagerOrderedList_vtable[4];
extern "C" int igInfoManagerOrderedList_GetVTable(void);
extern "C" int DAT_0052cbc0[4];
#include "dw4/core/igDependencyOrderedList.h"
#include "dw4/support/list-services.h"
#include "dw4/core/igStringRef.h"
extern "C" int **FUN_00233610(int **arg0, long long arg1);
extern "C" void igInfoManagerOrderedList_EnsureRegistered(void);
extern "C" CallbackArray *igInfoManagerOrderedList_Register(void);
extern "C" void igInfoManagerOrderedList_GetMetaObjectFunction(void);
extern "C" int FUN_00233740(void);
extern "C" igMetaObject *g_igInfoManagerList_metaObject;
extern "C" igMetaObject *igInfoManagerList_GetOrCreateMetaObject(void);
extern "C" igMetaObject *igInfoManagerList_GetMetaObject(void);
struct Obj_2337f0 { int *vt; char pad[28]; };
extern "C" int g_igInfoManagerList_vtable[4];
extern "C" int igInfoManagerList_GetVTable(void);
extern "C" void igInfoManagerList_EnsureRegistered(void);
extern "C" CallbackArray *igInfoManagerList_Register(void);
extern "C" void igInfoManagerList_GetMetaObjectFunction(void);
extern "C" igMetaObject *igInfoManager_GetMetaObject(void);
extern "C" void igInfoManager_EnsureRegistered(void);
extern "C" void igInfoManager_GetMetaObjectFunction(void);
extern "C" void igInfoManager_InitFields(void);
extern "C" igMetaObject *g_igFlushRenderer_metaObject;
extern "C" igMetaObject *igFlushRenderer_GetOrCreateMetaObject(void);
union U_233a90 { int vt; int w[3]; char b[12]; };
extern "C" int g_igFlushRenderer_vtable[4];
extern "C" igMetaObject *igFlushRenderer_GetMetaObject(void);
extern "C" int igFlushRenderer_GetVTable(void);
extern "C" void igFlushRenderer_EnsureRegistered(void);
extern "C" CallbackArray *igFlushRenderer_Register(void);
extern "C" void igFlushRenderer_GetMetaObjectFunction(void);
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
    SharedViewerOptions *shared;
};
struct App {
    void *f0;
    char pad[228];
    igObject *f232;
    igObject *f236;
};
extern "C" void igCommandLine_ParseLine(struct FlushSettings *settings, const char *text);
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "dw4/support/softfloat.h"
#include "dw4/datapump/igRegistryValue.h"
#include "dw4/core/igDataLists.h"
#include "dw4/maths/igMathConstants.h"
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
            if (g_stringPool == 0) {
                int pool = (int)(StringPool_Allocate(0x10));
                if (pool != 0) {
                    pool = (int)(StringPool_Construct((StringPool *)pool));
                }
                g_stringPool = (StringPool *)pool;
            }
            interned = StringPool_Intern(g_stringPool, (const char *)text);
        }
        p = interned;
    }
    ~StringRef() {
        char *s = p;
        if (s != 0) {
            StringTokenHeader *header = (StringTokenHeader *)s - 1;
            int count = ((int *)s)[-1] - 1;
            ((int *)s)[-1] = count;
            if (count == 0) StringChunk_ReleaseHeader((StringChunk *)header->owner, (StringTokenHeader *)header);
        }
    }
};
extern "C" void igCommandLine_PrintUsage(const char *programName);
extern "C" void igCommandLine_PrintOptionBool(const char *command, const char *comment, int value);
extern "C" void igCommandLine_PrintOptionInt(const char *command, const char *comment, int value);
extern "C" void igCommandLine_PrintOptionFloat(const char *command, const char *comment, float value);
extern "C" void igCommandLine_PrintOptionVec3f(const char *command, const char *comment, float *value);
extern "C" void igCommandLine_PrintOptionVec4f(const char *command, const char *comment, float *value);
extern "C" int igCommandLine_GetOption(igStringRefList *args, int *index, const char *option);
extern "C" int igCommandLine_GetOptionInt(igStringRefList *args, int *index, const char *option, int *value);
extern "C" int igCommandLine_GetOptionFloat(igStringRefList *args, int *index, const char *option, double *value);
extern "C" int igCommandLine_GetOptionString(igStringRefList *args, int *index, const char *option, const char **value);
extern "C" int igCommandLine_GetDefaultValueStringRef(igStringRefList *args, int *index, const char *option, char **value);
extern "C" int igCommandLine_GetDefaultValueBool(igStringRefList *args, int *index, const char *option, unsigned char *value);
extern "C" int igCommandLine_GetDefaultValueInt(igStringRefList *args, int *index, const char *option, int *value);
extern "C" int igCommandLine_GetDefaultValueFloat(igStringRefList *args, int *index, const char *option, float *value);
extern "C" int igCommandLine_GetDefaultValueVec3f(igStringRefList *args, int *index, const char *option, float *value);
extern "C" int igCommandLine_GetDefaultValueVec4f(igStringRefList *args, int *index, const char *option, float *value);
extern "C" struct FlushSettings *igCommandLine_Construct(struct FlushSettings *s);
extern "C" void *igCommandLine_Destruct(struct App *arg0, short arg1);
extern "C" void igViewerDefaults_ReleaseInstance(void);
extern "C" void igCommandLine_Setup(ViewerOptions *opts, igStringRefList *args);
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
    virtual void setClearColor(const float *rgba);
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
#include "dw4/windowinput/igWindow.h"
class igFlushRendererView {
public:
    int _vtable;
    unsigned int _refCount;
    igVisualContextView *_visualContext;
};
extern "C" void igFlushRenderer_Render(igFlushRendererView *self);
struct NamedObject : public igObject { int name; };
#include "dw4/core/igFolder.h"
struct G { char p[76]; int f76; };
extern "C" void igInsightCore_UserRegister(void);
struct TextValue : public igObject { char *text; };
#include "dw4/core/igStringObj.h"
extern "C" FrameBufferFormat igInsightCore_CreateRenderDestinationFormat(SharedViewerOptions *options);
#include "dw4/viewer/ViewerSetup.h"
struct ResizeEvent : public igObject { float origin[2]; float size[2]; };
extern "C" float DAT_004e0fa0[4];
extern "C" float DAT_004e0fa4[4];
struct WindowInfo { char p[40]; int f40; };
struct Receiver { char p[8]; WindowInfo *f8; };
extern "C" int igWindowResizeEventReceiver_WindowResizeEvent(Receiver *self, int width, int height);
extern "C" int igInsightCore_IsRegistered(igInsightCore *core, igObject *manager);
class DW4VC_92_0 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual int vX(); };
class DW4VC_96_0 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual int vX(); };
class DW4VC_96_1 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual int vX(int); };
class DW4VC_104_0 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual int vX(); };
class DW4VC_100_1 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual int vX(int); };
struct Instance : public igObject { };
class DW4VC_92_1 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual int vX(int); };
extern "C" void igInsightCore_RegisterAllPlugins(igInsightCore *core);
extern "C" void igInsightCore_UnregisterAllPlugins(igInsightCore *core);
extern "C" void igInsightCore_RemoveAllInfos(igInsightCore *core);
extern "C" void igInsightCore_Begin(igInsightCore *core);
extern "C" void igInsightCore_End(igInsightCore *core);
extern "C" void igInsightCore_InitializeDrawing(igInsightCore *core);
extern "C" void igInsightCore_TerminateDrawing(igInsightCore *core);
extern "C" void igInsightCore_HandleEvents(igInsightCore *core);
extern "C" void igInsightCore_DrawFrame(igInsightCore *core);
extern "C" void igInsightCore_RegisterPlugin(void *arg0, void **arg1);
extern "C" void igInsightCore_UnregisterPlugin(void *arg0, void **arg1);
typedef struct L { char pad8[8]; int cnt; char pad12[4]; int *arr; } L;
typedef struct A { char pad104[104]; L *f68; } A;
extern "C" int FUN_00457ca0(...);
#include "dw4/core/igResult.h"
/* An info manager: its virtual slot 20 returns its meta object. */
struct InfoManagerView { virtual int a0(); virtual int a1(); virtual int a2(); virtual int a3(); virtual int a4(); virtual int a5(); virtual int a6(); virtual int a7(); virtual int a8(); virtual int a9(); virtual int a10(); virtual int a11(); virtual int a12(); virtual int a13(); virtual int a14(); virtual int a15(); virtual int a16(); virtual int a17(); virtual int a18(); virtual int a19(); virtual igMetaObject *getMeta(); };
extern "C" int FUN_00237010(void);
/* Dummy class with 25 virtual slots before vX, so that vX is the manager's
 * vtable slot 27 (matching construct: gives the retail `lw t9,108(t9)` call). */
class DW4VC { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual int vX(int); };
/* matching construct: dummy virtual slots so the vX() call dispatches through the retail vtable offset 112 */
class VC112 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual int vX(); };
class V100 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void vX(); };
class V108 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void vY(); };
struct L_2371f0 { char pad8[8]; unsigned int cnt; char pad12[4]; V100 **arr; };
struct M { char pad8[8]; L_2371f0 *l; };
struct S_2371f0 { char pad8[8]; M *m; char pad12[36]; V108 *f48; char pad52[4]; long long f56; long long f64; };
class A_237280 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void vX(); };
class B { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void vX(); };
struct Q { int p0; int p1; int count; int p3; B **data; };
struct A_237300 { char pad[28]; int f28; int f32; int f36; char pad40[4]; int f44; char pad48[24]; int f72; };
struct StringRef_237300 {
    int *p;
    StringRef_237300(const char *text) {
        int *interned;
        if (text == 0) {
            interned = 0;
        } else {
            if (g_stringPool == 0) {
                StringPool *pool = (StringPool *)StringPool_Allocate(16);
                if (pool != 0) pool = StringPool_Construct(pool);
                g_stringPool = pool;
            }
            interned = (int *)StringPool_Intern(g_stringPool, text);
        }
        p = interned;
    }
    ~StringRef_237300() {
        int *s = p;
        if (s != 0) {
            int *hd = s - 2;
            int cnt = s[-1] - 1;
            s[-1] = cnt;
            if (cnt == 0) StringChunk_ReleaseHeader((StringChunk *)(*hd), (StringTokenHeader *)hd);
        }
    }
};
extern "C" void igInsightCore_resetFields(struct A_237300 *arg0, int flags);
extern "C" int FUN_004541f0(...);
struct OO;
struct R_237530;
class DW4VC_152 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual void d32(); virtual void d33(); virtual void d34(); virtual void d35(); virtual R_237530 *vX(); };
struct R_237530 { int w0; int rc; };
struct Lst { char pad[8]; int n; int w12; int *items; };
struct Wr { char pad[8]; Lst *f8; };
struct OO { char pad[20]; DW4VC_152 *f20; R_237530 *f24; Wr *f28; int f32; };
struct L_2376b0 { char pad[8]; int count; int pad2; int *items; };
struct M_2376b0 { char pad[8]; struct L_2376b0 *list; };
struct H { char pad[28]; struct M_2376b0 *m; };
extern "C" int igAttrPool_UserUnregister(...);
class A21 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void vX(); };
class A24 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual long long vX(); };
struct S_237730 { char pad12[12]; A21 *f12; char pad16[16]; A21 *f32; char pad36[12]; A24 *f48; char pad52[4]; long long f56; long long f64; int f72; char pad76[4]; long long f80; };
class ProfiledObject { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual int v23(); virtual long long v24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual void d32(); virtual void d33(); virtual int v34(); virtual void d35(); virtual void d36(); virtual void d37(); virtual void d38(); virtual void d39(); virtual void d40(); virtual void d41(); virtual void d42(); virtual void d43(); virtual void d44(); virtual void d45(); virtual void d46(); virtual void d47(); virtual void d48(); virtual void d49(); virtual void d50(); virtual void d51(); virtual void d52(); virtual void d53(); virtual void d54(); virtual void d55(); virtual void d56(); virtual void d57(); virtual void d58(); virtual void d59(); virtual void d60(); virtual void d61(); virtual void d62(); virtual void d63(); virtual void d64(); virtual void d65(); virtual void d66(); virtual void d67(); virtual void d68(); virtual void d69(); virtual void d70(); virtual void d71(); virtual void d72(); virtual void d73(); virtual void d74(); virtual void d75(); virtual void d76(); virtual void d77(); virtual void d78(); virtual void d79(); virtual void d80(); virtual void d81(); virtual void d82(); virtual void d83(); virtual void d84(); virtual void d85(); virtual void d86(); virtual void d87(); virtual void d88(); virtual void d89(); virtual void d90(); virtual void d91(); virtual void d92(); virtual void d93(); virtual void d94(); virtual void d95(); virtual void d96(); virtual void d97(); virtual void d98(); virtual void d99(); virtual void d100(); virtual void d101(); virtual void d102(); virtual void d103(); virtual void d104(); virtual void d105(); virtual void d106(); virtual void d107(); virtual void d108(); virtual void d109(); virtual void d110(); virtual void d111(); virtual void d112(); virtual void d113(); virtual void d114(); virtual void d115(); virtual void d116(); virtual void d117(); virtual void d118(); virtual void d119(); virtual void d120(); virtual void d121(); virtual void d122(); virtual void d123(); virtual void d124(); virtual void d125(); virtual void d126(); virtual void d127(); virtual void d128(); virtual void d129(); virtual void d130(); virtual void d131(); virtual void d132(); virtual void d133(); virtual void d134(); virtual void d135(); virtual void d136(); virtual void d137(); virtual void d138(); virtual void d139(); virtual void d140(); virtual void d141(); virtual void d142(); virtual void d143(); virtual void d144(); virtual void d145(); virtual void d146(); virtual void d147(); virtual void d148(); virtual void d149(); virtual void d150(); virtual void d151(); virtual void d152(); virtual void d153(); virtual void d154(); virtual void d155(); virtual void d156(); virtual void d157(); virtual void d158(); virtual void d159(); virtual void d160(); virtual void d161(); virtual void d162(); virtual void d163(); virtual void d164(); virtual void d165(); virtual void d166(); virtual void d167(); virtual void d168(); virtual void d169(); virtual void d170(); virtual int v171(); virtual int v172(); };
struct ProfiledObjectList { char pad[8]; int cnt; char pad2[4]; ProfiledObject **arr; };
struct ProfiledObjectHolder { char pad[8]; ProfiledObjectList *l; };
struct ProfilerState { char p0[24]; ProfiledObject *a; ProfiledObjectHolder *m; char p1[16]; ProfiledObject *b; int cnt; char p2[32]; long long d1; long long d2; };
struct T_237940 { void m(); };
typedef void (T_237940::*PM)();
struct S_237940 { char pad[8]; T_237940 *obj; PM pm; };
extern "C" void igMessageDefaultReceiver_MessageHandler(S_237940 *s);
typedef struct E { int pad[2]; int f8; } E;
typedef struct L_237990 { int pad[2]; int f8; int pad2; E **f16; } L_237990;
typedef struct A_237990 { int pad[2]; L_237990 *f8; } A_237990;
extern "C" E *igFilterMessageDispatcher_GetFilter(const A_237990 *arg0, int arg1);
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
extern "C" igSmartPointer<MessageFilter> igFilterMessageDispatcher_GetFilterOrCreate(FilterDispatcher *self, igObject *target);
class N;
struct L_237b50 { char pad[8]; int cnt; int cap; N **data; };
class N { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual int vX(int); char pad[8]; L_237b50 *f12; };
extern "C" void igFilterMessageDispatcher_PostMessage(N *arg0, int arg1);
extern "C" void igMessageFilter_AcceptMessage(int arg0, int arg1);
class FilterDispatcherSlots {
public:
    virtual void vfunc_2(); virtual void vfunc_3(); virtual void vfunc_4(); virtual void vfunc_5(); virtual void vfunc_6(); virtual void vfunc_7();
    virtual void vfunc_8(); virtual void vfunc_9(); virtual void vfunc_10(); virtual void vfunc_11(); virtual void vfunc_12(); virtual void vfunc_13();
    virtual void vfunc_14(); virtual void vfunc_15(); virtual void vfunc_16(); virtual void vfunc_17(); virtual void vfunc_18(); virtual void vfunc_19();
    virtual void vfunc_20(); virtual void vfunc_21(); virtual void vfunc_22(); virtual void vfunc_23();
    virtual void dispatch(int message, igObject *filter);
};
extern "C" void igFilterMessageDispatcher_AddFilteringForType(FilterDispatcherSlots *self, int message, igObject *target);
extern "C" void igFilterMessageDispatcher_AddFiltering(void *arg0, void *arg1, void *arg2);
class DW4VC_108_2 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual int vX(int, int); };
extern "C" void igFilterMessageDispatcher_RemoveFilteringForType(void **arg0, int arg1, int arg2);
struct L_237d80 { int p0; int p1; int n; int p3; int *arr; };
class V { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void vX(int, int);
  char pad[8]; L_237d80 *list; };
extern "C" void igFilterMessageDispatcher_RemoveFilteringForReceiver(V *arg0, int arg1);
typedef struct S_arg0 { char pad0[8]; int f8; int f12; } S_arg0;
typedef struct S_arg2 { char pad0[12]; int f12; } S_arg2;
extern "C" void igFilterMessageDispatcher_RemoveFiltering(S_arg0 *arg0, void *arg1, S_arg2 *arg2);
class igFilterMessageDispatcherView {
public:
    virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7();
    virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15();
    virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20();
    virtual void vfunc_21(igObject *receiver, igMetaObject *messageType);
    virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25();
    virtual void vfunc_26(void *message);
};
struct igMessageDispatcherOwnerView {
    char _pad0[8];
    igFilterMessageDispatcherView *f8;
};
extern "C" void igMessenger_PostMessage(igMessageDispatcherOwnerView *self, void *message);
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
extern "C" void igSerialScheduler_Update(igSerialScheduler *scheduler);
extern "C" void igSerialScheduler_Schedule(void *arg0, int arg1);
typedef struct Obj_238020 { char pad[8]; int f8; } Obj_238020;
extern "C" void igSerialScheduler_Unschedule(Obj_238020 *arg0, int arg1);
extern "C" int igSerialScheduler_IsScheduled(igSerialScheduler *scheduler, igObject *manager);
typedef struct S0 { char pad8[8]; int f8; } S0;
extern "C" void igSerialScheduler_AppendDependency(S0 *arg0, void *arg1, void *arg2);
extern "C" void igSerialScheduler_RemoveDependency(S0 *arg0, void *arg1, void *arg2);
extern "C" void igSerialScheduler_RemoveAllDependencies(S0 *arg0, void *arg1);
/* Saves the Alchemy viewer (INSIGHT) options into the property tree: the INSIGHT group is looked
 * up in the property set held by the global (+56), falling back to 'Viewer', and each option is
 * written under its string name. Every write is guarded by its name pointer (the original option
 * table can drop a name); the guards are kept because the compiler does not fold them. Callee
 * names come from their roles: StoreString (igGetRegistryValue_String), StoreByte (igGetRegistryValue_Bool),
 * StoreFloat (igGetRegistryValue_Float), StoreInt (igGetRegistryValue_Int), StoreVec4 (igGetRegistryValue_Vec4f),
 * StoreVec3 (igGetRegistryValue_Vec3f). */
#include "dw4/core/igRegistry.h"
extern "C" void igViewerDefaults_LoadFromRegistry(SharedViewerOptions *self);
extern "C" igMetaObject *igSerialScheduler_GetMeta(void);
extern "C" igMetaObject *igFilterMessageDispatcher_GetMeta(void);
extern "C" igMetaObject *igMessageDefaultReceiver_GetMeta(void);
extern "C" igMetaObject *igInsightCore_GetMeta(void);
extern "C" igMetaObject *igWindowResizeEventReceiver_GetMeta(void);
extern "C" int igEventReceiver_OnKeyEvent(void);
extern "C" int igEventReceiver_MouseMotionEvent(void);
extern "C" int igEventReceiver_MouseButtonEvent(void);
extern "C" int igEventReceiver_ControllerMotionEvent(void);
extern "C" int igEventReceiver_ControllerButtonEvent(void);
extern "C" int igEventReceiver_ControllerButtonPressureEvent(void);
extern "C" int igEventReceiver_ControllerSlider(void);
extern "C" int igEventReceiver_ControllerPointOfView(void);
extern "C" int igEventReceiver_ControllerConnectionEvent(void);
extern "C" int igEventReceiver_WindowMoveEvent(void);
extern "C" int igEventReceiver_WindowCloseEvent(void);
extern "C" int igEventReceiver_WindowResizeEvent(void);
extern "C" igMetaObject *igFlushRenderer_GetMeta(void);
extern "C" void igFlushRenderer_Traverse(void);
extern "C" void igFlushRenderer_InitializeDrawing(void);
extern "C" void igFlushRenderer_ReleaseDrawing(void);
extern "C" igMetaObject *igInfoManagerList_GetMeta(void);
extern "C" igMetaObject *igInfoManagerOrderedList_GetMeta(void);
extern "C" int igDependencyOrderedList_GetMeta(void);
extern "C" igMetaObject *igViewportResizedMessage_GetMeta(void);
extern "C" igMetaObject *igEventReceiver_GetMeta(void);
extern "C" igMetaObject *igInsightPluginList_GetMeta(void);
extern "C" igMetaObject *igMessageFilter_GetMeta(void);
extern "C" igMetaObject *igMessageFilterList_GetMeta(void);
extern "C" igMetaObject *igMessageReceiverList_GetMeta(void);
extern "C" igMetaObject *igMessenger_GetMeta(void);
extern "C" int igMessage_GetMeta(void);
extern "C" igMetaObject *FUN_00238cf0(void);
extern "C" igMetaObject *igInsightPluginList_GetElementMeta(void);
extern "C" igMetaObject *igMessageFilterList_GetElementMeta(void);
extern "C" igMetaObject *igInfoManagerList_GetElementMeta(void);
extern "C" igMetaObject *igMessageReceiverList_GetElementMeta(void);

#endif
