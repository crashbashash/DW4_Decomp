#include "dw4/reflected.h"
#include "dw4/igobject_release.h"
#include "dw4/igSmartPointer.h"
#include "dw4/DisableFeature.h"

extern "C" {

/* The igMetaField handles of igViewerParameters' fields; a change notification names its field by one. */
extern int g_igViewerParameters_sceneMetaField[4];
extern int g_igViewerParameters_upVectorMetaField[4];
extern int g_igViewerParameters_ratioMetaField[4];
extern int g_igViewerParameters_hfovMetaField[4];
extern int g_igViewerParameters_nearPlaneMetaField[4];
extern int g_igViewerParameters_farPlaneMetaField[4];
extern int g_igViewerParameters_viewMatrixMetaField[4];
extern int g_igViewerParameters_drawTimeMetaField[4];
extern int g_igViewerParameters_sortTextureMetaField[4];
extern int g_igViewerParameters_sortTransparentMetaField[4];
extern int g_igViewerParameters_sortTransparentDistanceMetaField[4];
extern int g_igViewerParameters_transparencyModeMetaField[4];
extern int g_igViewerParameters_useSceneLightsMetaField[4];
extern int g_igViewerParameters_useHeadLightMetaField[4];
extern int g_igViewerParameters_useHeadLightSpecularMetaField[4];
extern int g_igViewerParameters_alphaTestMetaField[4];
extern int g_igViewerParameters_alphaTestForceMetaField[4];
extern int g_igViewerParameters_backFaceCullingMetaField[4];
extern int g_igViewerParameters_backFaceCullingForceMetaField[4];
extern int g_igViewerParameters_wireframeMetaField[4];
extern int g_igViewerParameters_wireframeForceMetaField[4];
extern int g_igViewerParameters_flatShadingMetaField[4];
extern int g_igViewerParameters_flatShadingForceMetaField[4];
extern int g_igViewerParameters_disablesMetaField[4];
extern int g_igViewerParameters_showGuiMetaField[4];
extern int g_igViewerParameters_showBoundingBoxMetaField[4];
extern int g_igViewerParameters_showNormalsMetaField[4];
extern int g_igViewerParameters_flushFramesMetaField[4];
extern int g_igViewerParameters_operationModeMetaField[4];
extern int g_igViewerParameters_camerasMetaField[4];
extern int g_igViewerParameters_beginTimeMetaField[4];
extern int g_igViewerParameters_endTimeMetaField[4];
extern int g_igViewerParameters_selectedObjectMetaField[4];
extern int g_igViewerParameters_timeOperationMetaField[4];
extern int g_igViewerParameters_speedMetaField[4];

int igViewerRenderer_UpdateProjection(...);
int igViewerRenderer_UpdateViewMatrix(...);
int igViewerRenderer_UpdateSorting(...);
int igViewerRenderer_UpdateLighting(...);
int igViewerRenderer_UpdateRenderStates(...);

void igViewerSceneInfoManager_OnPlaybackChanged(igViewerSceneInfoManager *self);
void igViewerSceneInfoManager_HideGui(igViewerSceneInfoManager *self);
void igViewerSceneInfoManager_RemoveNormalsRenderer(igViewerSceneInfoManager *self);
void igViewerSceneInfoManager_RemoveBoundingBoxRenderer(igViewerSceneInfoManager *self);
void igViewerSceneInfoManager_RemoveFlushRenderer(igViewerSceneInfoManager *self);
void igViewerSceneInfoManager_OnSelectionChanged(igViewerSceneInfoManager *self);
void igViewerSceneInfoManager_OnDisablesChanged(igViewerSceneInfoManager *self, int index);
void igViewerSceneInfoManager_ApplyOperationMode(igViewerSceneInfoManager *self);
void igViewerSceneInfoManager_OnCamerasChanged(igViewerSceneInfoManager *self);

/* What an igModel tells its views: the kind of change (2: a field was set), the field's handle and,
 * for a list field, the element. */
struct ModelChange {
    int kind;
    int flags;
    int field;
    int index;
};

typedef struct ViewerMessage { int kind; int flags; int field; } ViewerMessage;

int igModel_NotifyViews(...);

int Gap__Core__igObject__resetFields(...);

int __dl__FPv(...);
void **__nw__FUi(...);

int igBitMask_SetBitCount(...);

void **ViewerOptions_Construct(...);

int igHotKeyEventReceiver_AddKey(...);
int igHotKeyEventReceiver_AddButton(...);
int igHotKeyEventReceiver_AddBinding(...);
int igView_SetModel(...);
int igViewerGuiFactory_CreateAction(...);
int igViewManager_SynchronizeParameters(...);

int StringChunk_ReleaseHeader(...);
void igObject_Destroy(void *);

void *memset(void *, int, unsigned int);

/* The scene-info manager's hot-key handlers, as the member-function pointers igViewerAction calls. */
extern char g_fitSelectionHandler[16];
extern char g_printViewMatrixHandler[16];
extern char g_centerSelectionHandler[16];
extern char g_cycleGuiVisibilityHandler[16];
extern char g_playHandler[16];
extern char g_pauseHandler[16];
extern char g_hotKeyMHandler[16];
extern char g_hotKeyWHandler[16];
extern char g_resetOperationModeHandler[16];
extern char g_hotKeyTHandler[16];
extern char g_hotKeyPHandler[16];
extern char g_button1Handler[16];
extern char g_button2Handler[16];

/* The viewer options every viewer object shares, reference counted and created on first use. */
struct SharedViewerOptions {
    void *extraCommandLine;
    unsigned char showBBox;
    unsigned char showNormals;
    char pad6[54];
    unsigned char autoSelectCamera;
    char pad61[19];
    float upVector[3];
    char pad92[122];
    unsigned char showUI;
    char pad215[17];
    int refCount;
    void *f236;
};

extern SharedViewerOptions *g_sharedViewerOptions[4];

/* igViewerRenderer-family objects: the shared parameters reference sits at +12 */
struct RendererLink {
    char pad[12];
    igObject *parameters;
};
#define BIND(setter, receiver, name, ...)                                                 \
    {                                                                                     \
        igObject *action;                                                                 \
        igViewerGuiFactory_CreateAction(&action, self->_guiFactory, self, name);          \
        setter(receiver, __VA_ARGS__, action);                                            \
        IG_OBJECT_RELEASE(action);                                                        \
    }

int igInsightCore_RemoveFromScheduler(...);
int igInsightCore_RemoveRenderer(...);

int igObject_IsKindOf(...);

extern int g_igParticleAttr_metaObject[4];
extern void *g_igGeometryAttr_metaObject[4];
extern int g_igDisplayListAttr_metaObject[4];

void igViewerSceneInfoManager_OnSceneClipped(igViewerSceneInfoManager *self);

int igViewManager_SetFrameTime(...);

int igGroup_RemoveChildAt(igObject **removed, igGroup *group, int index);

int igViewerRenderer_UpdateScene(...);

/* Releases every object of `list` and empties it. */
#define RELEASE_ALL(list) { \
    igObjectList *l = (igObjectList *)(list); \
    int n = l->_count; \
    int i; \
    int m; \
    int j; \
    igObject *o; \
    for (i = 0; i < n; i++) { \
        o = ((igObject **)l->_data)[i]; \
        IG_OBJECT_RELEASE(o); \
    } \
    m = l->_count; \
    for (j = 0; j < m; j++) { \
        ((igObject **)l->_data)[j] = 0; \
    } \
    l->_count = 0; }

int igGroup_AppendChild(...);
int igSceneInfo_CollectCameras(...);
int igSceneInfo_ComputeAnimationRange(...);
int ObjectList_AppendRetainedList(...);
int igSceneInfo_GetMetaObject(...);

extern float g_vec3Zero[4];

int igEventDispatcher_RemoveReceiver(...);
int igViewManager_SetSceneUpVector(...);
int igViewManager_FrameObject(...);

int igViewerRenderer_ApplyOptions(...);

void igViewerSceneInfoManager_OnButton1(igViewerSceneInfoManager *self);

int igViewManager_ApplyOptions(...);

void igViewManager_CenterSelection(int, int);

void igViewManager_FitSelection(int);

void igViewManager_PrintViewMatrix(int);

int igGuiComponent_AppendChild(int, int);

/* The view mode objects igViewManager_SetViewMode installs; references are counted. */
struct WidgetRef { igObject *object; };
igPickMode *igPickMode_Create(int);
igRotateMode *igRotateMode_Create(int);
igFlyMode *igFlyMode_Create(int);
igCameraMode *igCameraMode_Create(int);
WidgetRef igViewerGuiFactory_CreateEmpty(int, int);
int igViewManager_SetViewMode(int, igObject *);
int igCameraMode_SetCameraPath(igCameraMode *, int);
struct Tag { };
static inline igPickMode *createPickMode() {
    Tag tag = Tag();
    return igPickMode_Create(0);
}
static inline igFlyMode *createFlyMode() {
    Tag tag = Tag();
    return igFlyMode_Create(0);
}
static inline igRotateMode *createRotateMode() {
    Tag tag = Tag();
    return igRotateMode_Create(0);
}
static inline igCameraMode *createCameraMode() {
    Tag tag = Tag();
    return igCameraMode_Create(0);
}
static inline void setCursor(const igSmartPointer<igPickMode> &ref, const WidgetRef &cursor) {
    igObject *value = cursor.object;
    igPickMode *owner = ref.p;
    igObject *previous;
    if (value != 0) {
        value->_refCount = value->_refCount + 1;
    }
    previous = (igObject *)owner->_cursor;
    if (previous != 0) {
        previous->_refCount = previous->_refCount - 1;
        if ((previous->_refCount & 0x7FFFFF) == 0) {
            igObject_Destroy(previous);
        }
    }
    owner->_cursor = (int)value;
    if (cursor.object != 0) {
        cursor.object->_refCount = cursor.object->_refCount - 1;
        if ((cursor.object->_refCount & 0x7FFFFF) == 0) {
            igObject_Destroy(cursor.object);
        }
    }
}
static inline void setParameters(const igSmartPointer<igPickMode> &ref, igObject *value) {
    igPickMode *owner = ref.p;
    igObject *previous;
    if (value != 0) {
        value->_refCount = value->_refCount + 1;
    }
    previous = (igObject *)owner->_parameters;
    if (previous != 0) {
        previous->_refCount = previous->_refCount - 1;
        if ((previous->_refCount & 0x7FFFFF) == 0) {
            igObject_Destroy(previous);
        }
    }
    owner->_parameters = (int)value;
}
static inline void setGuiSystem(const igSmartPointer<igPickMode> &ref, igObject *value) {
    igPickMode *owner = ref.p;
    igObject *previous;
    if (value != 0) {
        value->_refCount = value->_refCount + 1;
    }
    previous = (igObject *)owner->_guiSystem;
    if (previous != 0) {
        previous->_refCount = previous->_refCount - 1;
        if ((previous->_refCount & 0x7FFFFF) == 0) {
            igObject_Destroy(previous);
        }
    }
    owner->_guiSystem = (int)value;
}
static inline void setWindow(const igSmartPointer<igFlyMode> &ref, igObject *value) {
    igFlyMode *owner = ref.p;
    igObject *previous;
    if (value != 0) {
        value->_refCount = value->_refCount + 1;
    }
    previous = (igObject *)owner->_window;
    if (previous != 0) {
        previous->_refCount = previous->_refCount - 1;
        if ((previous->_refCount & 0x7FFFFF) == 0) {
            igObject_Destroy(previous);
        }
    }
    owner->_window = (int)value;
}

/* igViewerAction: calls a member function of the object it holds. */
struct ActionTarget { void run(); };
typedef void (ActionTarget::*ActionFunction)();
struct ViewerActionBinding : igObject { ActionTarget *target; ActionFunction function; };

extern int g_igViewerAction_metaObject[4];

extern int g_igViewerSceneInfoManager_metaObject[4];

extern int g_igViewerSceneInfoManagerController_metaObject[4];

extern int g_igViewerParameters_metaObject;

extern int g_igViewerStatisticsManager_metaObject[4];

extern int g_igStatisticsItem_metaObject[4];

int igOnOffModel_GetMetaObject(...);

void Gap__Viewer__igViewerSceneInfoManagerController__OnModelChange(igViewerSceneInfoManagerController *self, ModelChange *change)
{
  igViewerSceneInfoManager *manager = (igViewerSceneInfoManager *)self->_application;
  int field;
  if (manager == 0) return;
  field = change->field;
  if (field == g_igViewerParameters_drawTimeMetaField[0]) return;
  if (field == g_igViewerParameters_ratioMetaField[0] || field == g_igViewerParameters_hfovMetaField[0] || field == g_igViewerParameters_nearPlaneMetaField[0] || field == g_igViewerParameters_farPlaneMetaField[0]) { igViewerRenderer_UpdateProjection(self->_viewerRenderer); return; }
  if (field == g_igViewerParameters_viewMatrixMetaField[0]) { igViewerRenderer_UpdateViewMatrix(self->_viewerRenderer); return; }
  if (field == g_igViewerParameters_sortTextureMetaField[0] || field == g_igViewerParameters_sortTransparentMetaField[0] || field == g_igViewerParameters_sortTransparentDistanceMetaField[0] || field == g_igViewerParameters_transparencyModeMetaField[0]) { igViewerRenderer_UpdateSorting(self->_viewerRenderer); return; }
  if (field == g_igViewerParameters_useSceneLightsMetaField[0] || field == g_igViewerParameters_useHeadLightMetaField[0] || field == g_igViewerParameters_useHeadLightSpecularMetaField[0]) { igViewerRenderer_UpdateLighting(self->_viewerRenderer); return; }
  if (field == g_igViewerParameters_alphaTestMetaField[0] || field == g_igViewerParameters_alphaTestForceMetaField[0] || field == g_igViewerParameters_backFaceCullingMetaField[0] || field == g_igViewerParameters_backFaceCullingForceMetaField[0] || field == g_igViewerParameters_wireframeMetaField[0] || field == g_igViewerParameters_wireframeForceMetaField[0] || field == g_igViewerParameters_flatShadingMetaField[0] || field == g_igViewerParameters_flatShadingForceMetaField[0]) { igViewerRenderer_UpdateRenderStates(self->_viewerRenderer); return; }
  if (field == g_igViewerParameters_disablesMetaField[0]) { igViewerSceneInfoManager_OnDisablesChanged(manager, change->index); return; }
  if (field == g_igViewerParameters_showGuiMetaField[0]) { igViewerSceneInfoManager_HideGui(manager); return; }
  if (field == g_igViewerParameters_showBoundingBoxMetaField[0]) { igViewerSceneInfoManager_RemoveBoundingBoxRenderer(manager); return; }
  if (field == g_igViewerParameters_showNormalsMetaField[0]) { igViewerSceneInfoManager_RemoveNormalsRenderer(manager); return; }
  if (field == g_igViewerParameters_flushFramesMetaField[0]) { igViewerSceneInfoManager_RemoveFlushRenderer(manager); return; }
  if (field == g_igViewerParameters_operationModeMetaField[0]) { igViewerSceneInfoManager_ApplyOperationMode(manager); return; }
  if (field == g_igViewerParameters_speedMetaField[0] || field == g_igViewerParameters_timeOperationMetaField[0]) { igViewerSceneInfoManager_OnPlaybackChanged(manager); return; }
  if (field == g_igViewerParameters_camerasMetaField[0]) { igViewerSceneInfoManager_OnCamerasChanged(manager); return; }
  if (change->kind == 0) { igViewerSceneInfoManager_ApplyOperationMode(manager); igViewerSceneInfoManager_OnPlaybackChanged((igViewerSceneInfoManager *)self->_application); igViewerSceneInfoManager_OnCamerasChanged((igViewerSceneInfoManager *)self->_application); return; }
  if (field == g_igViewerParameters_selectedObjectMetaField[0]) { igViewerSceneInfoManager_OnSelectionChanged(manager); }
}

void igViewerSceneInfoManager_OnPlaybackChanged(igViewerSceneInfoManager *self)
{
}

/* matching construct: 360 declaration and 120 statement orders */
void igViewerSceneInfoManager_UpdateTime(igViewerSceneInfoManager *self) {
    ViewerMessage rising;
    ViewerMessage falling;
    ViewerMessage changed;
    int *operation;
    long long time;
    long long begin;
    long long end;
    long long length;
    igViewerParameters *parameters;
    parameters = (igViewerParameters *)self->_parameters;
    end = parameters->_endTime;
    begin = parameters->_beginTime;
    time = ((igInsightCore *)self->_insight)->_worldTime;
    length = end - begin;
    if (end != 0) {
        switch (parameters->_loopMode) {
        case 0:
            while (time > end) {
                time -= length;
            }
            while (time < begin) {
                time += length;
            }
            break;
        case 1:
            while (time > end + length) {
                time -= length * 2;
            }
            while (time < begin - length) {
                time += length * 2;
            }
            operation = &parameters->_timeOperation;
            if (*operation == 1 && time > end) {
                time = end * 2 - time;
                *operation = 2;
                rising.kind = 2;
                rising.flags = 0;
                rising.field = g_igViewerParameters_timeOperationMetaField[0];
                igModel_NotifyViews((igViewerParameters *)self->_parameters, &rising);
            }
            operation = &((igViewerParameters *)self->_parameters)->_timeOperation;
            if (*operation == 2 && time < begin) {
                time = begin * 2 - time;
                *operation = 1;
                falling.kind = 2;
                falling.flags = 0;
                falling.field = g_igViewerParameters_timeOperationMetaField[0];
                igModel_NotifyViews((igViewerParameters *)self->_parameters, &falling);
            }
            break;
        }
    }
    ((igViewerParameters *)self->_parameters)->_drawTime = time;
    changed.kind = 2;
    changed.flags = 0;
    changed.field = g_igViewerParameters_drawTimeMetaField[0];
    igModel_NotifyViews((igViewerParameters *)self->_parameters, &changed);
    ((igInsightCore *)self->_insight)->_worldTime = time;
}

void Gap__Viewer__igViewerSceneInfoManager__resetFields(igViewerSceneInfoManager *self) {
    Gap__Core__igObject__resetFields(self);
    if (g_sharedViewerOptions[0] == 0) {
        void **v = __nw__FUi(0xF0);
        if (v != 0) {
            v = ViewerOptions_Construct(v);
        }
        g_sharedViewerOptions[0] = (SharedViewerOptions *)v;
    }
    g_sharedViewerOptions[0]->refCount = g_sharedViewerOptions[0]->refCount + 1;
    {
        SharedViewerOptions *options = g_sharedViewerOptions[0];
        ((igViewerParameters *)self->_parameters)->_showBoundingBox = options->showBBox;
        ((igViewerParameters *)self->_parameters)->_showNormals = options->showNormals;
        ((igViewerParameters *)self->_parameters)->_showGui = options->showUI;
        if (options->showUI == 0) {
            self->_guiVisibility = 2;
        }
    }
    if (g_sharedViewerOptions[0] != 0) {
        int rc = g_sharedViewerOptions[0]->refCount - 1;
        g_sharedViewerOptions[0]->refCount = rc;
        if (rc <= 0) {
            SharedViewerOptions *f = g_sharedViewerOptions[0];
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
                    void *p = f->extraCommandLine;
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
            g_sharedViewerOptions[0] = 0;
        }
    }
    igViewManager_SynchronizeParameters(self->_viewManager, self->_parameters);
    {
        igObject *s2 = (igObject *)self->_parameters;
        RendererLink *s1 = (RendererLink *)self->_viewerRenderer;
        if (s2 != 0) {
            s2->_refCount = (int)s2->_refCount + 1;
        }
        igObject *a0 = s1->parameters;
        IG_OBJECT_RELEASE(a0);
        s1->parameters = s2;
    }
    {
        igObject *s2 = (igObject *)self->_parameters;
        RendererLink *s1 = (RendererLink *)self->_bboxRenderer;
        if (s2 != 0) {
            s2->_refCount = (int)s2->_refCount + 1;
        }
        igObject *a0 = s1->parameters;
        IG_OBJECT_RELEASE(a0);
        s1->parameters = s2;
    }
    {
        igObject *s2 = (igObject *)self->_parameters;
        RendererLink *s1 = (RendererLink *)self->_normalsRenderer;
        if (s2 != 0) {
            s2->_refCount = (int)s2->_refCount + 1;
        }
        igObject *a0 = s1->parameters;
        IG_OBJECT_RELEASE(a0);
        s1->parameters = s2;
    }
    ((igViewerSceneInfoManagerController *)self->_applicationController)->_viewerRenderer = self->_viewerRenderer;
    ((igViewerSceneInfoManagerController *)self->_applicationController)->_application = (int)self;
    igView_SetModel(self->_applicationController, self->_parameters);
    igBitMask_SetBitCount(((igViewerParameters *)self->_parameters)->_disables, 0xC);
    {
        igBitMask *disables = (igBitMask *)((igViewerParameters *)self->_parameters)->_disables;
        memset((void *)disables->_data, 0, disables->_count * 4);
    }
    BIND(igHotKeyEventReceiver_AddKey, self->_hotKeyReceiver, g_fitSelectionHandler, 'F')
    BIND(igHotKeyEventReceiver_AddKey, self->_hotKeyReceiver, g_printViewMatrixHandler, 'D')
    BIND(igHotKeyEventReceiver_AddBinding, self->_hotKeyReceiver, g_centerSelectionHandler, 'C', 0xF)
    BIND(igHotKeyEventReceiver_AddBinding, self->_hotKeyReceiver, g_cycleGuiVisibilityHandler, 'H', 0xC)
    BIND(igHotKeyEventReceiver_AddButton, self->_hotKeyReceiver, g_playHandler, 3)
    BIND(igHotKeyEventReceiver_AddButton, self->_hotKeyReceiver, g_pauseHandler, 0)
    BIND(igHotKeyEventReceiver_AddKey, self->_hotKeyReceiver, g_hotKeyMHandler, 'M')
    BIND(igHotKeyEventReceiver_AddKey, self->_hotKeyReceiver, g_hotKeyWHandler, 'W')
    BIND(igHotKeyEventReceiver_AddBinding, self->_hotKeyReceiver, g_resetOperationModeHandler, 'R', 0xA)
    BIND(igHotKeyEventReceiver_AddBinding, self->_hotKeyReceiver, g_hotKeyTHandler, 'T', 0xB)
    BIND(igHotKeyEventReceiver_AddKey, self->_hotKeyReceiver, g_hotKeyPHandler, 'P')
    BIND(igHotKeyEventReceiver_AddButton, self->_hotKeyReceiver, g_button1Handler, 1)
    BIND(igHotKeyEventReceiver_AddButton, self->_hotKeyReceiver, g_button2Handler, 2)
}

void igViewerSceneInfoManager_OnActivate(void);
int igGuiSystem_SetRootComponent(...);
int igEventDispatcher_AddReceiverOrder(...);
int igEventDispatcher_AddReceiver(...);
int igInsightCore_AddRendererOrder(...);
int igInsightCore_AddRenderer(...);
int igInsightCore_AddToScheduler(...);
int igViewportResizedMessage_GetMetaObject(void);
int igMessenger_AddReceiver(...);
int StringPool_Allocate(...);
int StringPool_Construct(...);
void *StringPool_Intern(...);
extern int g_stringPool[4];

/* What precedes an interned string's characters: its chunk and its reference count. */
struct StringHeader {
    int chunk;
    int refCount;
};

static inline void releaseString(void *p) {
    if (p != 0) {
        StringHeader *h = (StringHeader *)p - 1;
        int rc = h->refCount - 1;
        h->refCount = rc;
        if (rc == 0) StringChunk_ReleaseHeader(h->chunk, h);
    }
}

static inline void *intern(const char *s) {
    if (s == 0) return 0;
    if (g_stringPool[0] == 0) {
        int pool = StringPool_Allocate(16);
        if (pool != 0) pool = StringPool_Construct(pool);
        g_stringPool[0] = pool;
    }
    return StringPool_Intern(g_stringPool[0], s);
}

/* An interned (pooled) string reference, released when it goes out of scope. */
struct StringRef {
    void *p;
    ~StringRef() { releaseString(p); }
};

/* igViewerRenderer's viewport-resize handler, called through a member pointer. */
struct ResizeHandler { void onViewportResized(); };
typedef void (ResizeHandler::*ResizeFunction)();
extern ResizeFunction g_viewerRendererResizeHandler;

/* igMessageDefaultReceiver: forwards a message to a member function of its handler object. */
struct MessageReceiver : igObject {
    igObject *handler;
    ResizeFunction function;
    void setHandler(igObject *object, ResizeFunction f) {
        if (object != 0) {
            object->_refCount = object->_refCount + 1;
        }
        igRelease(handler);
        handler = object;
        function = f;
    }
};
MessageReceiver *igMessageDefaultReceiver_CreateInstance(int);

/* Registers the manager with the insight core: GUI receivers, the render order of the viewer's
 * renderers between the "Clear done" / "Scenes done" / "Overlays done" markers, the renderer's
 * viewport-resize receiver, and the renderers themselves; the GUI starts hidden. */
void Gap__Viewer__igViewerSceneInfoManager__Activate(igViewerSceneInfoManager *self) {
    igViewerSceneInfoManager_OnActivate();
    igGuiSystem_SetRootComponent(self->_gui, self->_rootComponent);
    int dispatcher = ((igInsightCore *)self->_insight)->_dispatcher;
    igEventDispatcher_AddReceiverOrder(dispatcher, ((igInsightCore *)self->_insight)->_windowResizeReceiver, self->_gui);
    igEventDispatcher_AddReceiverOrder(dispatcher, self->_gui, self->_hotKeyReceiver);
    igEventDispatcher_AddReceiverOrder(dispatcher, self->_hotKeyReceiver, self->_viewManager);
    igEventDispatcher_AddReceiver(dispatcher, self->_viewManager);
    igEventDispatcher_AddReceiver(dispatcher, self->_hotKeyReceiver);
    StringRef clearDone;
    StringRef scenesDone;
    StringRef overlaysDone;
    clearDone.p = intern("Clear done");
    scenesDone.p = intern("Scenes done");
    overlaysDone.p = intern("Overlays done");
    igInsightCore_AddRendererOrder(self->_insight, clearDone.p, self->_normalsRenderer);
    igInsightCore_AddRendererOrder(self->_insight, self->_normalsRenderer, self->_viewerRenderer);
    igInsightCore_AddRendererOrder(self->_insight, self->_viewerRenderer, self->_bboxRenderer);
    igInsightCore_AddRendererOrder(self->_insight, self->_bboxRenderer, scenesDone.p);
    igInsightCore_AddRendererOrder(self->_insight, scenesDone.p, ((igGuiSystem *)self->_gui)->_renderer);
    igInsightCore_AddRendererOrder(self->_insight, ((igGuiSystem *)self->_gui)->_renderer, overlaysDone.p);
    igInsightCore_AddRendererOrder(self->_insight, overlaysDone.p, self->_flushRenderer);
    igSmartPointer<MessageReceiver> receiver(igMessageDefaultReceiver_CreateInstance(0), AdoptReference());
    ResizeFunction resized = g_viewerRendererResizeHandler;
    receiver->setHandler((igObject *)self->_viewerRenderer, resized);
    igMessenger_AddReceiver(((igInsightCore *)self->_insight)->_messenger, receiver.p, igViewportResizedMessage_GetMetaObject());
    igInsightCore_AddRenderer(self->_insight, self->_viewerRenderer);
    if (((igViewerParameters *)self->_parameters)->_showNormals != 0) {
        igInsightCore_AddRenderer(self->_insight, self->_normalsRenderer);
    }
    if (((igViewerParameters *)self->_parameters)->_showBoundingBox != 0) {
        igInsightCore_AddRenderer(self->_insight, self->_bboxRenderer);
    }
    if (((igViewerParameters *)self->_parameters)->_flushFrames != 0) {
        igInsightCore_AddRenderer(self->_insight, self->_flushRenderer);
    }
    igViewerSceneInfoManager_HideGui(self);
    igInsightCore_AddToScheduler(self->_insight, self);
}

void Gap__Viewer__igViewerSceneInfoManager__Deactivate(igViewerSceneInfoManager *self) {
    igInsightCore_RemoveRenderer(self->_insight, ((igGuiSystem *)self->_gui)->_renderer);
    igInsightCore_RemoveRenderer(self->_insight, self->_bboxRenderer);
    igInsightCore_RemoveRenderer(self->_insight, self->_normalsRenderer);
    igInsightCore_RemoveRenderer(self->_insight, self->_viewerRenderer);
    igInsightCore_RemoveRenderer(self->_insight, self->_flushRenderer);
    igInsightCore_RemoveFromScheduler(self->_insight, self);
}

/* True when `attr` draws geometry: a geometry or particle attribute, or a display list holding one. */
int igViewerSceneInfoManager_HasGeometry(igDisplayListAttr *attr) {
    int i;
    int n;
    int off;

    if (attr == 0) {
        return 0;
    }
    if (igObject_IsKindOf(attr, g_igGeometryAttr_metaObject[0]) != 0) {
        return 1;
    }
    if (igObject_IsKindOf(attr, g_igParticleAttr_metaObject[0]) != 0) {
        return 1;
    }
    if (igObject_IsKindOf(attr, g_igDisplayListAttr_metaObject[0]) != 0) {
        n = ((igObjectList *)attr->_contents)->_count;
        i = 0;
        if (0 < n) {
            off = 0;
            do {
                if (!!igViewerSceneInfoManager_HasGeometry(*(igDisplayListAttr **)((char *)((igObjectList *)attr->_contents)->_data + off))) {
                    return 1;
                }
                i += 1;
                off += 4;
            } while (i < n);
        }
    }
    return 0;
}

void igViewerSceneInfoManager_CheckClipping(igViewerSceneInfoManager *self) {
    if (igViewerSceneInfoManager_HasGeometry((igDisplayListAttr *)((igViewerRenderer *)self->_viewerRenderer)->_sceneOutput) == 0) {
        igViewerSceneInfoManager_OnSceneClipped(self);
    }
}

void Gap__Viewer__igViewerSceneInfoManager__Update(igViewerSceneInfoManager *self) {
    long long frameTime;
    igInsightCore *insight;

    igViewerSceneInfoManager_UpdateTime(self);
    insight = (igInsightCore *)self->_insight;
    frameTime = insight->_frameTime;
    if (self->_clippingCheckFrame == insight->_frames) {
        igViewerSceneInfoManager_CheckClipping(self);
    }
    igViewManager_SetFrameTime(self->_viewManager, frameTime);
}

void Gap__Viewer__igViewerSceneInfoManager__RemoveAllInfo(igViewerSceneInfoManager *self) {
    igGroup *scene;
    int index;
    igObject *removed;
    igObject *child;
    ModelChange sceneChanged, camerasChanged, beginChanged, endChanged;
    scene = (igGroup *)((igViewerParameters *)self->_parameters)->_scene;
    index = (scene->_childList != 0 ? ((igNodeList *)scene->_childList)->_count : 0) - 1;
    while (index >= 0) {
        igGroup_RemoveChildAt(&removed, scene, index);
        child = removed;
        if (child != 0) {
            child->_refCount = (int)child->_refCount - 1;
            child = removed;
            if (((unsigned long long)((long long)(int)child->_refCount << 0x29) >> 0x29) == 0) igObject_Destroy(child);
        }
        index -= 1;
    }
    sceneChanged.flags = 0;
    sceneChanged.kind = 2;
    sceneChanged.field = g_igViewerParameters_sceneMetaField[0];
    igModel_NotifyViews(self->_parameters, &sceneChanged);
    igViewerRenderer_UpdateScene(self->_viewerRenderer);
    RELEASE_ALL(((igViewerParameters *)self->_parameters)->_cameras)
    camerasChanged.kind = 2;
    camerasChanged.flags = 0;
    camerasChanged.field = g_igViewerParameters_camerasMetaField[0];
    igModel_NotifyViews(self->_parameters, &camerasChanged);
    ((igViewerParameters *)self->_parameters)->_beginTime = 0;
    beginChanged.kind = 2;
    beginChanged.flags = 0;
    beginChanged.field = g_igViewerParameters_beginTimeMetaField[0];
    igModel_NotifyViews(self->_parameters, &beginChanged);
    ((igViewerParameters *)self->_parameters)->_endTime = 0;
    endChanged.kind = 2;
    endChanged.flags = 0;
    endChanged.field = g_igViewerParameters_endTimeMetaField[0];
    igModel_NotifyViews(self->_parameters, &endChanged);
    RELEASE_ALL(self->_textureList)
}

int Gap__Viewer__igViewerSceneInfoManager__AddInfo(igViewerSceneInfoManager *self, igSceneInfo *info) {
    ViewerMessage sceneChanged, upVectorChanged, camerasChanged, beginChanged, endChanged;
    SharedViewerOptions *options;
    bool useSceneUpVector;
    bool upVectorUnset;
    if (igObject_IsKindOf(info, igSceneInfo_GetMetaObject()) != 0) {
        if (info->_sceneGraph == 0) {
            return 0;
        }
        if (g_sharedViewerOptions[0] == 0) {
            void **v = __nw__FUi(0xF0);
            if (v != 0) {
                v = ViewerOptions_Construct(v);
            }
            g_sharedViewerOptions[0] = (SharedViewerOptions *)v;
        }
        g_sharedViewerOptions[0]->refCount = g_sharedViewerOptions[0]->refCount + 1;
        options = g_sharedViewerOptions[0];
        if (info != 0 && info->_animationBegin == 0 && info->_animationEnd == 0) {
            igSceneInfo_ComputeAnimationRange(info);
        }
        if (info->_cameras == 0) {
            igSceneInfo_CollectCameras(info);
        }
        igGroup_AppendChild(((igViewerParameters *)self->_parameters)->_scene, info->_sceneGraph);
        sceneChanged.kind = 2;
        sceneChanged.flags = 0;
        sceneChanged.field = g_igViewerParameters_sceneMetaField[0];
        igModel_NotifyViews(self->_parameters, &sceneChanged);
        igViewerRenderer_UpdateScene(self->_viewerRenderer);
        useSceneUpVector = false;
        float x = options->upVector[0];
        upVectorUnset = false;
        if (!(x != g_vec3Zero[0])) { if (!(options->upVector[1] != g_vec3Zero[1])) { upVectorUnset = true; } }
        if (upVectorUnset && options->upVector[2] == g_vec3Zero[2]) {
            useSceneUpVector = true;
        }
        if (useSceneUpVector) {
            igViewerParameters *parameters = (igViewerParameters *)self->_parameters;
            *(float *)&parameters->_upVector[0] = *(float *)&info->_upVector[0];
            *(float *)&parameters->_upVector[1] = *(float *)&info->_upVector[1];
            *(float *)&parameters->_upVector[2] = *(float *)&info->_upVector[2];
        } else {
            igViewerParameters *parameters = (igViewerParameters *)self->_parameters;
            *(float *)&parameters->_upVector[0] = x;
            *(float *)&parameters->_upVector[1] = options->upVector[1];
            *(float *)&parameters->_upVector[2] = options->upVector[2];
        }
        upVectorChanged.kind = 2;
        upVectorChanged.flags = 0;
        upVectorChanged.field = g_igViewerParameters_upVectorMetaField[0];
        igModel_NotifyViews(self->_parameters, &upVectorChanged);
        ObjectList_AppendRetainedList(((igViewerParameters *)self->_parameters)->_cameras, info->_cameras);
        camerasChanged.kind = 2;
        camerasChanged.flags = 0;
        camerasChanged.field = g_igViewerParameters_camerasMetaField[0];
        igModel_NotifyViews(self->_parameters, &camerasChanged);
        {
            igViewerParameters *parameters = (igViewerParameters *)self->_parameters;
            long long *time = &parameters->_beginTime;
            if (parameters->_beginTime == 0) {
                *time = info->_animationBegin;
            }
        }
        beginChanged.kind = 2;
        beginChanged.flags = 0;
        beginChanged.field = g_igViewerParameters_beginTimeMetaField[0];
        igModel_NotifyViews(self->_parameters, &beginChanged);
        {
            igViewerParameters *parameters = (igViewerParameters *)self->_parameters;
            long long *time = &parameters->_endTime;
            if (parameters->_endTime == 0) {
                *time = info->_animationEnd;
            }
        }
        endChanged.kind = 2;
        endChanged.flags = 0;
        endChanged.field = g_igViewerParameters_endTimeMetaField[0];
        igModel_NotifyViews(self->_parameters, &endChanged);
        if (g_sharedViewerOptions[0] != 0) {
            int rc = g_sharedViewerOptions[0]->refCount - 1;
            g_sharedViewerOptions[0]->refCount = rc;
            if (rc <= 0) {
                SharedViewerOptions *f = g_sharedViewerOptions[0];
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
                        void *p = f->extraCommandLine;
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
                g_sharedViewerOptions[0] = 0;
            }
        }
        return 1;
    }
    return 0;
}

void igViewerSceneInfoManager_HideGui(igViewerSceneInfoManager *self) {
    igInsightCore *insight;

    insight = (igInsightCore *)self->_insight;
    if (insight != 0) {
        igInsightCore_RemoveRenderer(insight, ((igGuiSystem *)self->_gui)->_renderer);
        igEventDispatcher_RemoveReceiver(((igInsightCore *)self->_insight)->_dispatcher, self->_gui);
        self->_guiVisibility = 2;
    }
}

void igViewerSceneInfoManager_RemoveNormalsRenderer(igViewerSceneInfoManager *self) {
    igInsightCore_RemoveRenderer(self->_insight, self->_normalsRenderer);
}

void igViewerSceneInfoManager_RemoveBoundingBoxRenderer(igViewerSceneInfoManager *self) {
    igInsightCore_RemoveRenderer(self->_insight, self->_bboxRenderer);
}

void igViewerSceneInfoManager_RemoveFlushRenderer(igViewerSceneInfoManager *self) {
    igInsightCore_RemoveRenderer(self->_insight, self->_flushRenderer);
}

void igViewerSceneInfoManager_OnSelectionChanged(igViewerSceneInfoManager *self)
{
}

void igViewerSceneInfoManager_HomeView(igViewerSceneInfoManager *self) {
    ViewerMessage modeChanged;
    ((igViewerParameters *)self->_parameters)->_operationMode = 1;
    modeChanged.kind = 2;
    modeChanged.flags = 0;
    modeChanged.field = g_igViewerParameters_operationModeMetaField[0];
    igModel_NotifyViews(self->_parameters, &modeChanged, 1);
    igViewManager_SetSceneUpVector(self->_viewManager, ((igViewerParameters *)self->_parameters)->_upVector);
    igViewManager_FrameObject(self->_viewManager, ((igViewerParameters *)self->_parameters)->_scene);
}

void igViewerSceneInfoManager_ResetView(igViewerSceneInfoManager *self) {
    ViewerMessage selectionChanged;
    ViewerMessage playbackChanged;
    ViewerMessage modeChanged;
    SharedViewerOptions *f;
    SharedViewerOptions *options;
    igViewerParameters *parameters;
    igObject *selected;
    int *slot;
    void *p;
    int *h;
    int rc;
    igViewerSceneInfoManager_HomeView(self);
    igViewManager_ApplyOptions(self->_viewManager, ((igViewerParameters *)self->_parameters)->_scene);
    igViewerSceneInfoManager_OnButton1(self);
    igViewerRenderer_ApplyOptions(self->_viewerRenderer);
    parameters = (igViewerParameters *)self->_parameters;
    slot = &parameters->_selectedObject;
    selected = (igObject *)*slot;
    IG_OBJECT_RELEASE(selected);
    *slot = 0;
    selectionChanged.kind = 2;
    selectionChanged.flags = 0;
    selectionChanged.field = g_igViewerParameters_selectedObjectMetaField[0];
    igModel_NotifyViews(self->_parameters, &selectionChanged);
    ((igViewerParameters *)self->_parameters)->_timeOperation = 1;
    playbackChanged.kind = 2;
    playbackChanged.flags = 0;
    playbackChanged.field = g_igViewerParameters_timeOperationMetaField[0];
    igModel_NotifyViews(self->_parameters, &playbackChanged);
    if (g_sharedViewerOptions[0] == 0) {
        f = (SharedViewerOptions *)__nw__FUi(240);
        if (f != 0) f = (SharedViewerOptions *)ViewerOptions_Construct(f);
        g_sharedViewerOptions[0] = f;
    }
    g_sharedViewerOptions[0]->refCount = g_sharedViewerOptions[0]->refCount + 1;
    parameters = (igViewerParameters *)self->_parameters;
    options = g_sharedViewerOptions[0];
    if (((igObjectList *)parameters->_cameras)->_count > 0 && options->autoSelectCamera != 0) {
        parameters->_operationMode = parameters->_firstCameraMode;
    } else {
        parameters->_operationMode = 1;
    }
    modeChanged.flags = 0;
    modeChanged.kind = 2;
    modeChanged.field = g_igViewerParameters_operationModeMetaField[0];
    igModel_NotifyViews(self->_parameters, &modeChanged);
    if (g_sharedViewerOptions[0] != 0) {
        if (--g_sharedViewerOptions[0]->refCount <= 0) {
            f = g_sharedViewerOptions[0];
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
                    p = f->extraCommandLine;
                    if (p != 0) {
                        h = (int *)((char *)(p) - 8);
                        rc = *(int *)((char *)(p) - 4) - 1;
                        *(int *)((char *)(p) - 4) = rc;
                        if (rc == 0) {
                            StringChunk_ReleaseHeader(*h, h);
                        }
                    }
                }
                __dl__FPv(f);
            }
            g_sharedViewerOptions[0] = 0;
        }
    }
}

void igViewerSceneInfoManager_OnButton1(igViewerSceneInfoManager *self)
{
}

void igViewerSceneInfoManager_OnButton2(igViewerSceneInfoManager *self)
{
}

void igViewerSceneInfoManager_OnSceneClipped(igViewerSceneInfoManager *self)
{
}

void igViewerSceneInfoManager_DebugZoomOut(void)
{
}

void igViewerSceneInfoManager_Play(igViewerSceneInfoManager *self) {
    ViewerMessage playbackChanged;
    ((igViewerParameters *)self->_parameters)->_timeOperation = 1;
    playbackChanged.kind = 2;
    playbackChanged.flags = 0;
    playbackChanged.field = g_igViewerParameters_timeOperationMetaField[0];
    igModel_NotifyViews(self->_parameters, &playbackChanged);
}

void igViewerSceneInfoManager_Pause(igViewerSceneInfoManager *self) {
    ViewerMessage playbackChanged;

    ((igViewerParameters *)self->_parameters)->_timeOperation = 0;
    playbackChanged.kind = 2;
    playbackChanged.flags = 0;
    playbackChanged.field = g_igViewerParameters_timeOperationMetaField[0];
    igModel_NotifyViews(self->_parameters, &playbackChanged);
}

void igViewerSceneInfoManager_ResetOperationMode(igViewerSceneInfoManager *self) {
    ViewerMessage modeChanged;

    ((igViewerParameters *)self->_parameters)->_operationMode = 1;
    modeChanged.kind = 2;
    modeChanged.flags = 0;
    modeChanged.field = g_igViewerParameters_operationModeMetaField[0];
    igModel_NotifyViews(self->_parameters, &modeChanged, 1);
}

void igViewerSceneInfoManager_OnHotKeyT(igViewerSceneInfoManager *self)
{
}

void igViewerSceneInfoManager_OnHotKeyP(igViewerSceneInfoManager *self)
{
}

void igViewerSceneInfoManager_OnHotKeyM(igViewerSceneInfoManager *self)
{
}

void igViewerSceneInfoManager_OnHotKeyW(igViewerSceneInfoManager *self)
{
}

void igViewerSceneInfoManager_OnGuiShown(igViewerSceneInfoManager *self)
{
}

void igViewerSceneInfoManager_CenterSelection(igViewerSceneInfoManager *self) {
    igViewManager_CenterSelection(self->_viewManager, 0);
}

void igViewerSceneInfoManager_FitSelection(igViewerSceneInfoManager *self) {
    igViewManager_FitSelection(self->_viewManager);
}

void igViewerSceneInfoManager_PrintViewMatrix(igViewerSceneInfoManager *self) {
    igViewManager_PrintViewMatrix(self->_viewManager);
}

void igViewerSceneInfoManager_CycleGuiVisibility(igViewerSceneInfoManager *self) {
    switch (self->_guiVisibility) {
    case 0: {
        ViewerMessage guiChanged;
        ((igViewerParameters *)self->_parameters)->_showGui = 0;
        guiChanged.kind = 2;
        guiChanged.flags = 0;
        guiChanged.field = g_igViewerParameters_showGuiMetaField[0];
        igModel_NotifyViews(self->_parameters, &guiChanged);
        break;
    }
    case 1: {
        ViewerMessage guiChanged;
        igGuiComponent_AppendChild(self->_rootComponent, self->_operationBoxHolder);
        igGuiComponent_AppendChild(self->_rootComponent, self->_timeBoxHolder);
        igGuiComponent_AppendChild(self->_rootComponent, self->_menuHolder);
        ((igViewerParameters *)self->_parameters)->_showGui = 0;
        guiChanged.kind = 2;
        guiChanged.flags = 0;
        guiChanged.field = g_igViewerParameters_showGuiMetaField[0];
        igModel_NotifyViews(self->_parameters, &guiChanged);
        break;
    }
    case 2: {
        ViewerMessage guiChanged;
        ((igViewerParameters *)self->_parameters)->_showGui = 1;
        guiChanged.kind = 2;
        guiChanged.flags = 0;
        guiChanged.field = g_igViewerParameters_showGuiMetaField[0];
        igModel_NotifyViews(self->_parameters, &guiChanged);
        igViewerSceneInfoManager_OnGuiShown(self);
        break;
    }
    }
}

void igViewerSceneInfoManager_OnDisablesChanged(igViewerSceneInfoManager *self, int index)
{
}

/* Installs the view mode `_operationMode` selects: 0 picks, 1 rotates, 2 flies, 3 rotates the Maya way,
 * and from `_firstCameraMode` on, follows the scene's cameras in order. */
void igViewerSceneInfoManager_ApplyOperationMode(igViewerSceneInfoManager *self) {
    igViewerParameters *parameters = (igViewerParameters *)self->_parameters;
    int mode = parameters->_operationMode;
    switch (mode) {
    case 0: {
        igSmartPointer<igPickMode> pick(createPickMode());
        setCursor(pick, igViewerGuiFactory_CreateEmpty(self->_guiFactory, 1));
        setParameters(pick, (igObject *)self->_parameters);
        setGuiSystem(pick, (igObject *)self->_gui);
        igViewManager_SetViewMode(self->_viewManager, pick.p);
        break;
    }
    case 2: {
        igSmartPointer<igFlyMode> fly(createFlyMode());
        setWindow(fly, (igObject *)((igInsightCore *)self->_insight)->_window);
        igViewManager_SetViewMode(self->_viewManager, fly.p);
        break;
    }
    case 1: {
        igSmartPointer<igRotateMode> rotate(createRotateMode());
        igViewManager_SetViewMode(self->_viewManager, rotate.p);
        break;
    }
    case 3: {
        igSmartPointer<igRotateMode> rotate(createRotateMode());
        rotate.p->_maya = 1;
        igViewManager_SetViewMode(self->_viewManager, rotate.p);
        break;
    }
    default: {
        int first = parameters->_firstCameraMode;
        if (mode >= first) {
                first = mode - first;
            igSmartPointer<igCameraMode> camera(createCameraMode());
            igCameraMode_SetCameraPath(camera.p, ((int *)((igObjectList *)((igViewerParameters *)self->_parameters)->_cameras)->_data)[first]);
            igViewManager_SetViewMode(self->_viewManager, camera.p);
            self->_clippingCheckFrame = ((igInsightCore *)self->_insight)->_frames + 1;
        }
        break;
    }
    }
}

void Gap__Viewer__igViewerSceneInfoManager__vfunc_25(void) {

}

void Gap__Viewer__igViewerSceneInfoManager__vfunc_26(void) {

}

void igViewerSceneInfoManager_OnActivate(void)
{
}

void igViewerSceneInfoManager_OnCamerasChanged(igViewerSceneInfoManager *self)
{
}

void Gap__Viewer__igViewerAction__Execute(ViewerActionBinding *action) {
    ActionFunction function = action->function;
    (action->target->*function)();
}

int Gap__Viewer__igViewerAction__vfunc_22(void) {
    return g_igViewerAction_metaObject[0];
}

int Gap__Viewer__igViewerSceneInfoManager__vfunc_22(void) {
    return g_igViewerSceneInfoManager_metaObject[0];
}

int Gap__Viewer__igViewerSceneInfoManagerController__vfunc_22(void) {
    return g_igViewerSceneInfoManagerController_metaObject[0];
}

void Gap__Viewer__igViewerSceneInfoManagerController__vfunc_23(igViewerSceneInfoManagerController *self, igObject *model) {
    igObject_IsKindOf(model, g_igViewerParameters_metaObject);
}

void Gap__Viewer__igStatisticsItem__vfunc_24(void) {

}

void Gap__Viewer__igViewerStatisticsManager__vfunc_03(void) {

}

void Gap__Viewer__igViewerStatisticsManager__vfunc_04(void) {

}

float Gap__Viewer__igViewerStatisticsManager__vfunc_23(void) {
    return 0.0f;
}

float Gap__Viewer__igViewerStatisticsManager__vfunc_25(void) {
    return -1.0f;
}

void Gap__Viewer__igViewerStatisticsManager__vfunc_27(void) {

}

float Gap__Viewer__igViewerStatisticsManager__vfunc_24(void) {
    return 0.0f;
}

float Gap__Viewer__igViewerStatisticsManager__vfunc_26(void) {
    return -1.0f;
}

int Gap__Viewer__igViewerStatisticsManager__vfunc_22(void) {
    return g_igViewerStatisticsManager_metaObject[0];
}

int Gap__Viewer__igStatisticsItem__vfunc_22(void) {
    return g_igStatisticsItem_metaObject[0];
}

void Gap__Viewer__igStatisticsItem__vfunc_23(igStatisticsItem *self, igObject *model) {
    igObject_IsKindOf(model, igOnOffModel_GetMetaObject());
}

}

DisableFeature g_viewerDisableFeatures[12] = {
    DisableFeature(true, 0, "texture"),
    DisableFeature(true, 1, "lighting"),
    DisableFeature(true, 2, "blending"),
    DisableFeature(true, 3, "texture matrix"),
    DisableFeature(true, 4, "fog"),
    DisableFeature(true, 5, "depth test"),
    DisableFeature(true, 6, "vertex blending"),
    DisableFeature(true, 10, "VU1 vertex blending"),
    DisableFeature(true, 12, "VU1 particle rendering"),
    DisableFeature(true, 7, "alpha test"),
    DisableFeature(true, 8, "clipping"),
    DisableFeature(true, 9, "cullface")
};
