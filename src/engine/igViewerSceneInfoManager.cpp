#include "dw4/support/reflected.h"
#include "dw4/core/igobject_release.h"
#include "dw4/core/igSmartPointer.h"
#include "dw4/viewer/DisableFeature.h"
#include "dw4/viewer/igViewerSceneInfoManager.h"


#include "dw4/viewer/igViewerParameters.h"
#include "dw4/viewer/igViewerRenderer.h"
#include "dw4/gui/igModel.h"
#include "dw4/core/igObject.h"
#include "dw4/scenegraph/igBitMask.h"
#include "dw4/viewer/ViewerOptions.h"
#include "dw4/gui/igHotKeyEventReceiver.h"
#include "dw4/gui/igView.h"
#include "dw4/core/StringPool.h"
#include <string.h>
#include "dw4/insight/igInsightCore.h"
#include "dw4/attrs/igParticleAttr.h"
#include "dw4/attrs/igGeometryAttr.h"
#include "dw4/attrs/igDisplayListAttr.h"
#include "dw4/viewer/igViewManager.h"
#include "dw4/scenegraph/igGroup.h"
#include "dw4/scenegraph/igSceneInfo.h"
#include "dw4/gui/igEventDispatcher.h"
#include "dw4/gui/igGuiComponent.h"
#include "dw4/viewer/igPickMode.h"
#include "dw4/viewer/igRotateMode.h"
#include "dw4/viewer/igFlyMode.h"
#include "dw4/viewer/igCameraMode.h"
#include "dw4/maths/igMathConstants.h"
#include "dw4/support/list-services.h"
#include "dw4/viewer/igViewerGuiFactory.h"
extern "C" {

/* The igMetaField handles of igViewerParameters' fields; a change notification names its field by one. */


void igViewerSceneInfoManager_OnPlaybackChanged(igViewerSceneInfoManager *self);
void igViewerSceneInfoManager_HideGui(igViewerSceneInfoManager *self);
void igViewerSceneInfoManager_RemoveNormalsRenderer(igViewerSceneInfoManager *self);
void igViewerSceneInfoManager_RemoveBoundingBoxRenderer(igViewerSceneInfoManager *self);
void igViewerSceneInfoManager_RemoveFlushRenderer(igViewerSceneInfoManager *self);
void igViewerSceneInfoManager_OnSelectionChanged(igViewerSceneInfoManager *self);
void igViewerSceneInfoManager_OnDisablesChanged(igViewerSceneInfoManager *self, int index);
void igViewerSceneInfoManager_ApplyOperationMode(igViewerSceneInfoManager *self);
void igViewerSceneInfoManager_OnCamerasChanged(igViewerSceneInfoManager *self);

/* The three-word head of a ModelChange (type 2: a field was set), all a field-change message fills. */
typedef struct ViewerMessage { int type; void *source; igMetaField *field; } ViewerMessage;









/* The scene-info manager's hot-key handlers, as the igViewerFunction words igViewerAction calls: this adjustment,
 * virtual slot (-1 for a plain function), function. The handlers are C-named, so the words are spelled out. */
struct MemberFunctionPointer { int adjust; int virtualSlot; void *function; };
void igViewerSceneInfoManager_FitSelection(igViewerSceneInfoManager *self);
void igViewerSceneInfoManager_PrintViewMatrix(igViewerSceneInfoManager *self);
void igViewerSceneInfoManager_CenterSelection(igViewerSceneInfoManager *self);
void igViewerSceneInfoManager_CycleGuiVisibility(igViewerSceneInfoManager *self);
void igViewerSceneInfoManager_Play(igViewerSceneInfoManager *self);
void igViewerSceneInfoManager_Pause(igViewerSceneInfoManager *self);
void igViewerSceneInfoManager_OnHotKeyM(igViewerSceneInfoManager *self);
void igViewerSceneInfoManager_OnHotKeyW(igViewerSceneInfoManager *self);
void igViewerSceneInfoManager_ResetOperationMode(igViewerSceneInfoManager *self);
void igViewerSceneInfoManager_OnHotKeyT(igViewerSceneInfoManager *self);
void igViewerSceneInfoManager_OnHotKeyP(igViewerSceneInfoManager *self);
void igViewerSceneInfoManager_OnButton1(igViewerSceneInfoManager *self);
void igViewerSceneInfoManager_OnButton2(igViewerSceneInfoManager *self);
MemberFunctionPointer g_fitSelectionHandler = {0, -1, (void *)igViewerSceneInfoManager_FitSelection};
MemberFunctionPointer g_printViewMatrixHandler = {0, -1, (void *)igViewerSceneInfoManager_PrintViewMatrix};
MemberFunctionPointer g_centerSelectionHandler = {0, -1, (void *)igViewerSceneInfoManager_CenterSelection};
MemberFunctionPointer g_cycleGuiVisibilityHandler = {0, -1, (void *)igViewerSceneInfoManager_CycleGuiVisibility};
MemberFunctionPointer g_playHandler = {0, -1, (void *)igViewerSceneInfoManager_Play};
MemberFunctionPointer g_pauseHandler = {0, -1, (void *)igViewerSceneInfoManager_Pause};
MemberFunctionPointer g_hotKeyMHandler = {0, -1, (void *)igViewerSceneInfoManager_OnHotKeyM};
MemberFunctionPointer g_hotKeyWHandler = {0, -1, (void *)igViewerSceneInfoManager_OnHotKeyW};
MemberFunctionPointer g_resetOperationModeHandler = {0, -1, (void *)igViewerSceneInfoManager_ResetOperationMode};
MemberFunctionPointer g_hotKeyTHandler = {0, -1, (void *)igViewerSceneInfoManager_OnHotKeyT};
MemberFunctionPointer g_hotKeyPHandler = {0, -1, (void *)igViewerSceneInfoManager_OnHotKeyP};
MemberFunctionPointer g_button1Handler = {0, -1, (void *)igViewerSceneInfoManager_OnButton1};
MemberFunctionPointer g_button2Handler = {0, -1, (void *)igViewerSceneInfoManager_OnButton2};



/* igViewerRenderer-family objects: the shared parameters reference sits at +12 */
struct RendererLink {
    char pad[12];
    igObject *parameters;
};
#define BIND(setter, receiver, name, ...)                                                 \
    {                                                                                     \
        igSmartPointer<igViewerAction> action(igViewerGuiFactory_CreateAction((igViewerGuiFactory *)self->_guiFactory, self, *(igViewerFunction *)&name)); \
        setter(receiver, __VA_ARGS__, action.p);                                          \
    }




void igViewerSceneInfoManager_OnSceneClipped(igViewerSceneInfoManager *self);




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











/* The view mode objects igViewManager_SetViewMode installs; references are counted. */
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
static inline void setCursor(const igSmartPointer<igPickMode> &ref, const igSmartPointer<igObject> &cursor) {
    igObject *value = cursor.p;
    igPickMode *owner = ref.p;
    igObject *previous;
    igObject::ref(value);
    previous = (igObject *)owner->_cursor;
    igObject::release(previous);
    owner->_cursor = (int)value;
}
static inline void setParameters(const igSmartPointer<igPickMode> &ref, igObject *value) {
    igPickMode *owner = ref.p;
    igObject *previous;
    igObject::ref(value);
    previous = (igObject *)owner->_parameters;
    igObject::release(previous);
    owner->_parameters = (int)value;
}
static inline void setGuiSystem(const igSmartPointer<igPickMode> &ref, igObject *value) {
    igPickMode *owner = ref.p;
    igObject *previous;
    igObject::ref(value);
    previous = (igObject *)owner->_guiSystem;
    igObject::release(previous);
    owner->_guiSystem = (int)value;
}
static inline void setWindow(const igSmartPointer<igFlyMode> &ref, igObject *value) {
    igFlyMode *owner = ref.p;
    igObject *previous;
    igObject::ref(value);
    previous = (igObject *)owner->_window;
    igObject::release(previous);
    owner->_window = (int)value;
}

/* igViewerAction: calls a member function of the object it holds. */
struct ActionTarget { void run(); };
typedef void (ActionTarget::*ActionFunction)();
struct ViewerActionBinding : igObject { ActionTarget *target; ActionFunction function; };

#include "dw4/viewer/igViewerAction.h"


#include "dw4/viewer/igViewerSceneInfoManagerController.h"


#include "dw4/viewer/igViewerStatisticsManager.h"

#include "dw4/viewer/igStatisticsItem.h"

#include "dw4/gui/igOnOffModel.h"

void Gap__Viewer__igViewerSceneInfoManagerController__OnModelChange(igViewerSceneInfoManagerController *self, ModelChange *change)
{
  igViewerSceneInfoManager *manager = (igViewerSceneInfoManager *)self->_application;
  igMetaField *field;
  if (manager == 0) return;
  field = change->field;
  if (field == g_igViewerParameters_drawTimeMetaField) return;
  if (field == g_igViewerParameters_ratioMetaField || field == g_igViewerParameters_hfovMetaField || field == g_igViewerParameters_nearPlaneMetaField || field == g_igViewerParameters_farPlaneMetaField) { igViewerRenderer_UpdateProjection((igViewerRenderer *)self->_viewerRenderer); return; }
  if (field == g_igViewerParameters_viewMatrixMetaField) { igViewerRenderer_UpdateViewMatrix((igViewerRenderer *)self->_viewerRenderer); return; }
  if (field == g_igViewerParameters_sortTextureMetaField || field == g_igViewerParameters_sortTransparentMetaField || field == g_igViewerParameters_sortTransparentDistanceMetaField || field == g_igViewerParameters_transparencyModeMetaField) { igViewerRenderer_UpdateSorting((igViewerRenderer *)self->_viewerRenderer); return; }
  if (field == g_igViewerParameters_useSceneLightsMetaField || field == g_igViewerParameters_useHeadLightMetaField || field == g_igViewerParameters_useHeadLightSpecularMetaField) { igViewerRenderer_UpdateLighting((igViewerRenderer *)self->_viewerRenderer); return; }
  if (field == g_igViewerParameters_alphaTestMetaField || field == g_igViewerParameters_alphaTestForceMetaField || field == g_igViewerParameters_backFaceCullingMetaField || field == g_igViewerParameters_backFaceCullingForceMetaField || field == g_igViewerParameters_wireframeMetaField || field == g_igViewerParameters_wireframeForceMetaField || field == g_igViewerParameters_flatShadingMetaField || field == g_igViewerParameters_flatShadingForceMetaField) { igViewerRenderer_UpdateRenderStates((igViewerRenderer *)self->_viewerRenderer); return; }
  if (field == g_igViewerParameters_disablesMetaField) { igViewerSceneInfoManager_OnDisablesChanged(manager, change->reserved); return; }
  if (field == g_igViewerParameters_showGuiMetaField) { igViewerSceneInfoManager_HideGui(manager); return; }
  if (field == g_igViewerParameters_showBoundingBoxMetaField) { igViewerSceneInfoManager_RemoveBoundingBoxRenderer(manager); return; }
  if (field == g_igViewerParameters_showNormalsMetaField) { igViewerSceneInfoManager_RemoveNormalsRenderer(manager); return; }
  if (field == g_igViewerParameters_flushFramesMetaField) { igViewerSceneInfoManager_RemoveFlushRenderer(manager); return; }
  if (field == g_igViewerParameters_operationModeMetaField) { igViewerSceneInfoManager_ApplyOperationMode(manager); return; }
  if (field == g_igViewerParameters_speedMetaField || field == g_igViewerParameters_timeOperationMetaField) { igViewerSceneInfoManager_OnPlaybackChanged(manager); return; }
  if (field == g_igViewerParameters_camerasMetaField) { igViewerSceneInfoManager_OnCamerasChanged(manager); return; }
  if (change->type == 0) { igViewerSceneInfoManager_ApplyOperationMode(manager); igViewerSceneInfoManager_OnPlaybackChanged((igViewerSceneInfoManager *)self->_application); igViewerSceneInfoManager_OnCamerasChanged((igViewerSceneInfoManager *)self->_application); return; }
  if (field == g_igViewerParameters_selectedObjectMetaField) { igViewerSceneInfoManager_OnSelectionChanged(manager); }
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
                rising.type = 2;
                rising.source = 0;
                rising.field = g_igViewerParameters_timeOperationMetaField;
                igModel_NotifyViews((igModel *)((igViewerParameters *)self->_parameters), (ModelChange *)&rising);
            }
            operation = &((igViewerParameters *)self->_parameters)->_timeOperation;
            if (*operation == 2 && time < begin) {
                time = begin * 2 - time;
                *operation = 1;
                falling.type = 2;
                falling.source = 0;
                falling.field = g_igViewerParameters_timeOperationMetaField;
                igModel_NotifyViews((igModel *)((igViewerParameters *)self->_parameters), (ModelChange *)&falling);
            }
            break;
        }
    }
    ((igViewerParameters *)self->_parameters)->_drawTime = time;
    changed.type = 2;
    changed.source = 0;
    changed.field = g_igViewerParameters_drawTimeMetaField;
    igModel_NotifyViews((igModel *)((igViewerParameters *)self->_parameters), (ModelChange *)&changed);
    ((igInsightCore *)self->_insight)->_worldTime = time;
}

void Gap__Viewer__igViewerSceneInfoManager__resetFields(igViewerSceneInfoManager *self, int flags) {
    Gap__Core__igObject__resetFields((igObject *)self, flags);
    if (g_sharedViewerOptions == 0) {
        SharedViewerOptions *v = (SharedViewerOptions *)operator new(sizeof(SharedViewerOptions));
        if (v != 0) {
            v = igViewerDefaults_Construct(v);
        }
        g_sharedViewerOptions = v;
    }
    g_sharedViewerOptions->useCount = g_sharedViewerOptions->useCount + 1;
    {
        SharedViewerOptions *options = g_sharedViewerOptions;
        ((igViewerParameters *)self->_parameters)->_showBoundingBox = options->showBBox;
        ((igViewerParameters *)self->_parameters)->_showNormals = options->showNormals;
        ((igViewerParameters *)self->_parameters)->_showGui = options->showUI;
        if (options->showUI == 0) {
            self->_guiVisibility = 2;
        }
    }
    if (g_sharedViewerOptions != 0) {
        int rc = g_sharedViewerOptions->useCount - 1;
        g_sharedViewerOptions->useCount = rc;
        if (rc <= 0) {
            SharedViewerOptions *f = g_sharedViewerOptions;
            if (f != 0) {
                if (&f->internedString) {
                    void *p = (void *)f->internedString;
                    if (p != 0) {
                        int *h = (int *)((char *)p - 8);
                        int r = *(int *)((char *)p - 4) - 1;
                        *(int *)((char *)p - 4) = r;
                        if (r == 0) {
                            StringChunk_ReleaseHeader((StringChunk *)(*h), (StringTokenHeader *)h);
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
                            StringChunk_ReleaseHeader((StringChunk *)(*h), (StringTokenHeader *)h);
                        }
                    }
                }
                operator delete(f);
            }
            g_sharedViewerOptions = 0;
        }
    }
    igViewManager_SynchronizeParameters((igViewManager *)self->_viewManager, (igViewerParameters *)self->_parameters);
    {
        igObject *s2 = (igObject *)self->_parameters;
        RendererLink *s1 = (RendererLink *)self->_viewerRenderer;
        igObject::ref(s2);
        igObject *a0 = s1->parameters;
        IG_OBJECT_RELEASE(a0);
        s1->parameters = s2;
    }
    {
        igObject *s2 = (igObject *)self->_parameters;
        RendererLink *s1 = (RendererLink *)self->_bboxRenderer;
        igObject::ref(s2);
        igObject *a0 = s1->parameters;
        IG_OBJECT_RELEASE(a0);
        s1->parameters = s2;
    }
    {
        igObject *s2 = (igObject *)self->_parameters;
        RendererLink *s1 = (RendererLink *)self->_normalsRenderer;
        igObject::ref(s2);
        igObject *a0 = s1->parameters;
        IG_OBJECT_RELEASE(a0);
        s1->parameters = s2;
    }
    ((igViewerSceneInfoManagerController *)self->_applicationController)->_viewerRenderer = self->_viewerRenderer;
    ((igViewerSceneInfoManagerController *)self->_applicationController)->_application = (int)self;
    igView_SetModel((igView *)self->_applicationController, (igModel *)self->_parameters);
    igBitMask_SetBitCount((igBitMask *)(((igViewerParameters *)self->_parameters)->_disables), (unsigned int)0xC);
    {
        igBitMask *disables = (igBitMask *)((igViewerParameters *)self->_parameters)->_disables;
        memset((void *)disables->_data, 0, disables->_count * 4);
    }
    BIND(igHotKeyEventReceiver_AddKey, (igHotKeyEventReceiver *)self->_hotKeyReceiver, g_fitSelectionHandler, 'F')
    BIND(igHotKeyEventReceiver_AddKey, (igHotKeyEventReceiver *)self->_hotKeyReceiver, g_printViewMatrixHandler, 'D')
    BIND(igHotKeyEventReceiver_AddBinding, (igHotKeyEventReceiver *)self->_hotKeyReceiver, g_centerSelectionHandler, 'C', 0xF)
    BIND(igHotKeyEventReceiver_AddBinding, (igHotKeyEventReceiver *)self->_hotKeyReceiver, g_cycleGuiVisibilityHandler, 'H', 0xC)
    BIND(igHotKeyEventReceiver_AddButton, (igHotKeyEventReceiver *)self->_hotKeyReceiver, g_playHandler, 3)
    BIND(igHotKeyEventReceiver_AddButton, (igHotKeyEventReceiver *)self->_hotKeyReceiver, g_pauseHandler, 0)
    BIND(igHotKeyEventReceiver_AddKey, (igHotKeyEventReceiver *)self->_hotKeyReceiver, g_hotKeyMHandler, 'M')
    BIND(igHotKeyEventReceiver_AddKey, (igHotKeyEventReceiver *)self->_hotKeyReceiver, g_hotKeyWHandler, 'W')
    BIND(igHotKeyEventReceiver_AddBinding, (igHotKeyEventReceiver *)self->_hotKeyReceiver, g_resetOperationModeHandler, 'R', 0xA)
    BIND(igHotKeyEventReceiver_AddBinding, (igHotKeyEventReceiver *)self->_hotKeyReceiver, g_hotKeyTHandler, 'T', 0xB)
    BIND(igHotKeyEventReceiver_AddKey, (igHotKeyEventReceiver *)self->_hotKeyReceiver, g_hotKeyPHandler, 'P')
    BIND(igHotKeyEventReceiver_AddButton, (igHotKeyEventReceiver *)self->_hotKeyReceiver, g_button1Handler, 1)
    BIND(igHotKeyEventReceiver_AddButton, (igHotKeyEventReceiver *)self->_hotKeyReceiver, g_button2Handler, 2)
}

void igViewerSceneInfoManager_OnActivate(void);
#include "dw4/gui/igGuiSystem.h"
#include "dw4/insight/igViewportResizedMessage.h"
#include "dw4/insight/igMessenger.h"

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
        if (rc == 0) StringChunk_ReleaseHeader((StringChunk *)h->chunk, (StringTokenHeader *)h);
    }
}

static inline void *intern(const char *s) {
    if (s == 0) return 0;
    if (g_stringPool == 0) {
        StringPool *pool = (StringPool *)StringPool_Allocate(16);
        if (pool != 0) pool = StringPool_Construct(pool);
        g_stringPool = pool;
    }
    return StringPool_Intern(g_stringPool, s);
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
        igObject::ref(object);
        igRelease(handler);
        handler = object;
        function = f;
    }
};
#include "dw4/insight/igMessageDefaultReceiver.h"

/* Registers the manager with the insight core: GUI receivers, the render order of the viewer's
 * renderers between the "Clear done" / "Scenes done" / "Overlays done" markers, the renderer's
 * viewport-resize receiver, and the renderers themselves; the GUI starts hidden. */
void igViewerSceneInfoManager_Activate(igViewerSceneInfoManager *self) {
    igViewerSceneInfoManager_OnActivate();
    igGuiSystem_SetRootComponent((igGuiSystem *)self->_gui, (igGuiComponent *)self->_rootComponent);
    int dispatcher = ((igInsightCore *)self->_insight)->_dispatcher;
    igEventDispatcher_AddReceiverOrder((igEventDispatcher *)dispatcher, (igObject *)(((igInsightCore *)self->_insight)->_windowResizeReceiver), (igObject *)self->_gui);
    igEventDispatcher_AddReceiverOrder((igEventDispatcher *)dispatcher, (igObject *)self->_gui, (igObject *)self->_hotKeyReceiver);
    igEventDispatcher_AddReceiverOrder((igEventDispatcher *)dispatcher, (igObject *)self->_hotKeyReceiver, (igObject *)self->_viewManager);
    igEventDispatcher_AddReceiver((igEventDispatcher *)dispatcher, (igObject *)self->_viewManager);
    igEventDispatcher_AddReceiver((igEventDispatcher *)dispatcher, (igObject *)self->_hotKeyReceiver);
    StringRef clearDone;
    StringRef scenesDone;
    StringRef overlaysDone;
    clearDone.p = intern("Clear done");
    scenesDone.p = intern("Scenes done");
    overlaysDone.p = intern("Overlays done");
    igInsightCore_AddRendererOrder((igInsightCore *)self->_insight, (igObject *)clearDone.p, (igObject *)self->_normalsRenderer);
    igInsightCore_AddRendererOrder((igInsightCore *)self->_insight, (igObject *)self->_normalsRenderer, (igObject *)self->_viewerRenderer);
    igInsightCore_AddRendererOrder((igInsightCore *)self->_insight, (igObject *)self->_viewerRenderer, (igObject *)self->_bboxRenderer);
    igInsightCore_AddRendererOrder((igInsightCore *)self->_insight, (igObject *)self->_bboxRenderer, (igObject *)scenesDone.p);
    igInsightCore_AddRendererOrder((igInsightCore *)self->_insight, (igObject *)scenesDone.p, (igObject *)(((igGuiSystem *)self->_gui)->_renderer));
    igInsightCore_AddRendererOrder((igInsightCore *)self->_insight, (igObject *)(((igGuiSystem *)self->_gui)->_renderer), (igObject *)overlaysDone.p);
    igInsightCore_AddRendererOrder((igInsightCore *)self->_insight, (igObject *)overlaysDone.p, (igObject *)self->_flushRenderer);
    igSmartPointer<MessageReceiver> receiver((MessageReceiver *)igMessageDefaultReceiver_CreateInstance(0), AdoptReference());
    ResizeFunction resized = g_viewerRendererResizeHandler;
    receiver->setHandler((igObject *)self->_viewerRenderer, resized);
    igMessenger_AddReceiver((igMessenger *)(((igInsightCore *)self->_insight)->_messenger), (igObject *)receiver.p, igViewportResizedMessage_GetMetaObject());
    igInsightCore_AddRenderer((igInsightCore *)self->_insight, (igObject *)self->_viewerRenderer);
    if (((igViewerParameters *)self->_parameters)->_showNormals != 0) {
        igInsightCore_AddRenderer((igInsightCore *)self->_insight, (igObject *)self->_normalsRenderer);
    }
    if (((igViewerParameters *)self->_parameters)->_showBoundingBox != 0) {
        igInsightCore_AddRenderer((igInsightCore *)self->_insight, (igObject *)self->_bboxRenderer);
    }
    if (((igViewerParameters *)self->_parameters)->_flushFrames != 0) {
        igInsightCore_AddRenderer((igInsightCore *)self->_insight, (igObject *)self->_flushRenderer);
    }
    igViewerSceneInfoManager_HideGui(self);
    igInsightCore_AddToScheduler((igInsightCore *)self->_insight, (igObject *)self);
}

void igViewerSceneInfoManager_Deactivate(igViewerSceneInfoManager *self) {
    igInsightCore_RemoveRenderer((igInsightCore *)self->_insight, (igObject *)(((igGuiSystem *)self->_gui)->_renderer));
    igInsightCore_RemoveRenderer((igInsightCore *)self->_insight, (igObject *)self->_bboxRenderer);
    igInsightCore_RemoveRenderer((igInsightCore *)self->_insight, (igObject *)self->_normalsRenderer);
    igInsightCore_RemoveRenderer((igInsightCore *)self->_insight, (igObject *)self->_viewerRenderer);
    igInsightCore_RemoveRenderer((igInsightCore *)self->_insight, (igObject *)self->_flushRenderer);
    igInsightCore_RemoveFromScheduler((igInsightCore *)self->_insight, (igObject *)self);
}

/* True when `attr` draws geometry: a geometry or particle attribute, or a display list holding one. */
int igViewerSceneInfoManager_HasGeometry(igDisplayListAttr *attr) {
    int i;
    int n;
    int off;

    if (attr == 0) {
        return 0;
    }
    if (((Gap::Core::igObject *)attr)->isOfType(g_igGeometryAttr_metaObject) != 0) {
        return 1;
    }
    if (((Gap::Core::igObject *)attr)->isOfType(g_igParticleAttr_metaObject) != 0) {
        return 1;
    }
    if (((Gap::Core::igObject *)attr)->isOfType(Gap::Attrs::igDisplayListAttr::getClassMeta()) != 0) {
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

void igViewerSceneInfoManager_Update(igViewerSceneInfoManager *self) {
    long long frameTime;
    igInsightCore *insight;

    igViewerSceneInfoManager_UpdateTime(self);
    insight = (igInsightCore *)self->_insight;
    frameTime = insight->_frameTime;
    if (self->_clippingCheckFrame == insight->_frames) {
        igViewerSceneInfoManager_CheckClipping(self);
    }
    igViewManager_SetFrameTime((igViewManager *)self->_viewManager, frameTime);
}

void igViewerSceneInfoManager_RemoveAllInfo(igViewerSceneInfoManager *self) {
    igGroup *scene;
    int index;
    ModelChange sceneChanged, camerasChanged, beginChanged, endChanged;
    scene = (igGroup *)((igViewerParameters *)self->_parameters)->_scene;
    index = (scene->_childList != 0 ? ((igNodeList *)scene->_childList)->_count : 0) - 1;
    while (index >= 0) {
        igGroup_RemoveChildAt(scene, index);
        index -= 1;
    }
    sceneChanged.source = 0;
    sceneChanged.type = 2;
    sceneChanged.field = g_igViewerParameters_sceneMetaField;
    igModel_NotifyViews((igModel *)self->_parameters, &sceneChanged);
    igViewerRenderer_UpdateScene((igViewerRenderer *)self->_viewerRenderer);
    RELEASE_ALL(((igViewerParameters *)self->_parameters)->_cameras)
    camerasChanged.type = 2;
    camerasChanged.source = 0;
    camerasChanged.field = g_igViewerParameters_camerasMetaField;
    igModel_NotifyViews((igModel *)self->_parameters, &camerasChanged);
    ((igViewerParameters *)self->_parameters)->_beginTime = 0;
    beginChanged.type = 2;
    beginChanged.source = 0;
    beginChanged.field = g_igViewerParameters_beginTimeMetaField;
    igModel_NotifyViews((igModel *)self->_parameters, &beginChanged);
    ((igViewerParameters *)self->_parameters)->_endTime = 0;
    endChanged.type = 2;
    endChanged.source = 0;
    endChanged.field = g_igViewerParameters_endTimeMetaField;
    igModel_NotifyViews((igModel *)self->_parameters, &endChanged);
    RELEASE_ALL(self->_textureList)
}

int igViewerSceneInfoManager_AddInfo(igViewerSceneInfoManager *self, igSceneInfo *info) {
    ViewerMessage sceneChanged, upVectorChanged, camerasChanged, beginChanged, endChanged;
    SharedViewerOptions *options;
    bool useSceneUpVector;
    bool upVectorUnset;
    if (((Gap::Core::igObject *)info)->isOfType(igSceneInfo_GetMetaObject()) != 0) {
        if (info->_sceneGraph == 0) {
            return 0;
        }
        if (g_sharedViewerOptions == 0) {
            SharedViewerOptions *v = (SharedViewerOptions *)operator new(sizeof(SharedViewerOptions));
            if (v != 0) {
                v = igViewerDefaults_Construct(v);
            }
            g_sharedViewerOptions = v;
        }
        g_sharedViewerOptions->useCount = g_sharedViewerOptions->useCount + 1;
        options = g_sharedViewerOptions;
        if (info != 0 && info->_animationBegin == 0 && info->_animationEnd == 0) {
            igSceneInfo_ComputeAnimationRange(info);
        }
        if (info->_cameras == 0) {
            igSceneInfo_CollectCameras(info);
        }
        igGroup_AppendChild((igGroup *)(((igViewerParameters *)self->_parameters)->_scene), (igNode *)info->_sceneGraph);
        sceneChanged.type = 2;
        sceneChanged.source = 0;
        sceneChanged.field = g_igViewerParameters_sceneMetaField;
        igModel_NotifyViews((igModel *)self->_parameters, (ModelChange *)&sceneChanged);
        igViewerRenderer_UpdateScene((igViewerRenderer *)self->_viewerRenderer);
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
        upVectorChanged.type = 2;
        upVectorChanged.source = 0;
        upVectorChanged.field = g_igViewerParameters_upVectorMetaField;
        igModel_NotifyViews((igModel *)self->_parameters, (ModelChange *)&upVectorChanged);
        ((Gap::Core::igObjectList *)((igTDataList<igObject *> *)(((igViewerParameters *)self->_parameters)->_cameras)))->concatenate((Gap::Core::igObjectList *)((igTDataList<igObject *> *)info->_cameras));
        camerasChanged.type = 2;
        camerasChanged.source = 0;
        camerasChanged.field = g_igViewerParameters_camerasMetaField;
        igModel_NotifyViews((igModel *)self->_parameters, (ModelChange *)&camerasChanged);
        {
            igViewerParameters *parameters = (igViewerParameters *)self->_parameters;
            long long *time = &parameters->_beginTime;
            if (parameters->_beginTime == 0) {
                *time = info->_animationBegin;
            }
        }
        beginChanged.type = 2;
        beginChanged.source = 0;
        beginChanged.field = g_igViewerParameters_beginTimeMetaField;
        igModel_NotifyViews((igModel *)self->_parameters, (ModelChange *)&beginChanged);
        {
            igViewerParameters *parameters = (igViewerParameters *)self->_parameters;
            long long *time = &parameters->_endTime;
            if (parameters->_endTime == 0) {
                *time = info->_animationEnd;
            }
        }
        endChanged.type = 2;
        endChanged.source = 0;
        endChanged.field = g_igViewerParameters_endTimeMetaField;
        igModel_NotifyViews((igModel *)self->_parameters, (ModelChange *)&endChanged);
        if (g_sharedViewerOptions != 0) {
            int rc = g_sharedViewerOptions->useCount - 1;
            g_sharedViewerOptions->useCount = rc;
            if (rc <= 0) {
                SharedViewerOptions *f = g_sharedViewerOptions;
                if (f != 0) {
                    if (&f->internedString) {
                        void *p = (void *)f->internedString;
                        if (p != 0) {
                            int *h = (int *)((char *)p - 8);
                            int r = *(int *)((char *)p - 4) - 1;
                            *(int *)((char *)p - 4) = r;
                            if (r == 0) {
                                StringChunk_ReleaseHeader((StringChunk *)(*h), (StringTokenHeader *)h);
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
                                StringChunk_ReleaseHeader((StringChunk *)(*h), (StringTokenHeader *)h);
                            }
                        }
                    }
                    operator delete(f);
                }
                g_sharedViewerOptions = 0;
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
        igInsightCore_RemoveRenderer(insight, (igObject *)(((igGuiSystem *)self->_gui)->_renderer));
        igEventDispatcher_RemoveReceiver((igEventDispatcher *)(((igInsightCore *)self->_insight)->_dispatcher), (igObject *)self->_gui);
        self->_guiVisibility = 2;
    }
}

void igViewerSceneInfoManager_RemoveNormalsRenderer(igViewerSceneInfoManager *self) {
    igInsightCore_RemoveRenderer((igInsightCore *)self->_insight, (igObject *)self->_normalsRenderer);
}

void igViewerSceneInfoManager_RemoveBoundingBoxRenderer(igViewerSceneInfoManager *self) {
    igInsightCore_RemoveRenderer((igInsightCore *)self->_insight, (igObject *)self->_bboxRenderer);
}

void igViewerSceneInfoManager_RemoveFlushRenderer(igViewerSceneInfoManager *self) {
    igInsightCore_RemoveRenderer((igInsightCore *)self->_insight, (igObject *)self->_flushRenderer);
}

void igViewerSceneInfoManager_OnSelectionChanged(igViewerSceneInfoManager *self)
{
}

void igViewerSceneInfoManager_HomeView(igViewerSceneInfoManager *self) {
    ViewerMessage modeChanged;
    ((igViewerParameters *)self->_parameters)->_operationMode = 1;
    modeChanged.type = 2;
    modeChanged.source = 0;
    modeChanged.field = g_igViewerParameters_operationModeMetaField;
    igModel_NotifyViews((igModel *)self->_parameters, (ModelChange *)&modeChanged);
    igViewManager_SetSceneUpVector((igViewManager *)self->_viewManager, (const float *)(((igViewerParameters *)self->_parameters)->_upVector.vec));
    igViewManager_FrameObject((igViewManager *)self->_viewManager, (igNode *)(((igViewerParameters *)self->_parameters)->_scene));
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
    igViewManager_ApplyOptions((igViewManager *)self->_viewManager, (igObject *)(((igViewerParameters *)self->_parameters)->_scene));
    igViewerSceneInfoManager_OnButton1(self);
    igViewerRenderer_ApplyOptions((igViewerRenderer *)self->_viewerRenderer);
    parameters = (igViewerParameters *)self->_parameters;
    slot = &parameters->_selectedObject;
    selected = (igObject *)*slot;
    IG_OBJECT_RELEASE(selected);
    *slot = 0;
    selectionChanged.type = 2;
    selectionChanged.source = 0;
    selectionChanged.field = g_igViewerParameters_selectedObjectMetaField;
    igModel_NotifyViews((igModel *)self->_parameters, (ModelChange *)&selectionChanged);
    ((igViewerParameters *)self->_parameters)->_timeOperation = 1;
    playbackChanged.type = 2;
    playbackChanged.source = 0;
    playbackChanged.field = g_igViewerParameters_timeOperationMetaField;
    igModel_NotifyViews((igModel *)self->_parameters, (ModelChange *)&playbackChanged);
    if (g_sharedViewerOptions == 0) {
        f = (SharedViewerOptions *)operator new(sizeof(SharedViewerOptions));
        if (f != 0) f = igViewerDefaults_Construct(f);
        g_sharedViewerOptions = f;
    }
    g_sharedViewerOptions->useCount = g_sharedViewerOptions->useCount + 1;
    parameters = (igViewerParameters *)self->_parameters;
    options = g_sharedViewerOptions;
    if (((igObjectList *)parameters->_cameras)->_count > 0 && options->autoSelectCamera != 0) {
        parameters->_operationMode = parameters->_firstCameraMode;
    } else {
        parameters->_operationMode = 1;
    }
    modeChanged.source = 0;
    modeChanged.type = 2;
    modeChanged.field = g_igViewerParameters_operationModeMetaField;
    igModel_NotifyViews((igModel *)self->_parameters, (ModelChange *)&modeChanged);
    if (g_sharedViewerOptions != 0) {
        if (--g_sharedViewerOptions->useCount <= 0) {
            f = g_sharedViewerOptions;
            if (f != 0) {
                if (&f->internedString) {
                    p = (void *)f->internedString;
                    if (p != 0) {
                        h = (int *)((char *)(p) - 8);
                        rc = *(int *)((char *)(p) - 4) - 1;
                        *(int *)((char *)(p) - 4) = rc;
                        if (rc == 0) {
                            StringChunk_ReleaseHeader((StringChunk *)(*h), (StringTokenHeader *)h);
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
                            StringChunk_ReleaseHeader((StringChunk *)(*h), (StringTokenHeader *)h);
                        }
                    }
                }
                operator delete(f);
            }
            g_sharedViewerOptions = 0;
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

void igViewerSceneInfoManager_DebugZoomOut(igViewerSceneInfoManager *self)
{
}

void igViewerSceneInfoManager_Play(igViewerSceneInfoManager *self) {
    ViewerMessage playbackChanged;
    ((igViewerParameters *)self->_parameters)->_timeOperation = 1;
    playbackChanged.type = 2;
    playbackChanged.source = 0;
    playbackChanged.field = g_igViewerParameters_timeOperationMetaField;
    igModel_NotifyViews((igModel *)self->_parameters, (ModelChange *)&playbackChanged);
}

void igViewerSceneInfoManager_Pause(igViewerSceneInfoManager *self) {
    ViewerMessage playbackChanged;

    ((igViewerParameters *)self->_parameters)->_timeOperation = 0;
    playbackChanged.type = 2;
    playbackChanged.source = 0;
    playbackChanged.field = g_igViewerParameters_timeOperationMetaField;
    igModel_NotifyViews((igModel *)self->_parameters, (ModelChange *)&playbackChanged);
}

void igViewerSceneInfoManager_ResetOperationMode(igViewerSceneInfoManager *self) {
    ViewerMessage modeChanged;

    ((igViewerParameters *)self->_parameters)->_operationMode = 1;
    modeChanged.type = 2;
    modeChanged.source = 0;
    modeChanged.field = g_igViewerParameters_operationModeMetaField;
    igModel_NotifyViews((igModel *)self->_parameters, (ModelChange *)&modeChanged);
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
    igViewManager_CenterSelection((igViewManager *)self->_viewManager, (bool)0);
}

void igViewerSceneInfoManager_FitSelection(igViewerSceneInfoManager *self) {
    igViewManager_FitSelection((igViewManager *)self->_viewManager);
}

void igViewerSceneInfoManager_PrintViewMatrix(igViewerSceneInfoManager *self) {
    igViewManager_PrintViewMatrix((igViewManager *)self->_viewManager);
}

void igViewerSceneInfoManager_CycleGuiVisibility(igViewerSceneInfoManager *self) {
    switch (self->_guiVisibility) {
    case 0: {
        ViewerMessage guiChanged;
        ((igViewerParameters *)self->_parameters)->_showGui = 0;
        guiChanged.type = 2;
        guiChanged.source = 0;
        guiChanged.field = g_igViewerParameters_showGuiMetaField;
        igModel_NotifyViews((igModel *)self->_parameters, (ModelChange *)&guiChanged);
        break;
    }
    case 1: {
        ViewerMessage guiChanged;
        igGuiComponent_AppendChild((igGuiComponent *)self->_rootComponent, (igGuiComponent *)self->_operationBoxHolder);
        igGuiComponent_AppendChild((igGuiComponent *)self->_rootComponent, (igGuiComponent *)self->_timeBoxHolder);
        igGuiComponent_AppendChild((igGuiComponent *)self->_rootComponent, (igGuiComponent *)self->_menuHolder);
        ((igViewerParameters *)self->_parameters)->_showGui = 0;
        guiChanged.type = 2;
        guiChanged.source = 0;
        guiChanged.field = g_igViewerParameters_showGuiMetaField;
        igModel_NotifyViews((igModel *)self->_parameters, (ModelChange *)&guiChanged);
        break;
    }
    case 2: {
        ViewerMessage guiChanged;
        ((igViewerParameters *)self->_parameters)->_showGui = 1;
        guiChanged.type = 2;
        guiChanged.source = 0;
        guiChanged.field = g_igViewerParameters_showGuiMetaField;
        igModel_NotifyViews((igModel *)self->_parameters, (ModelChange *)&guiChanged);
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
        setCursor(pick, igViewerGuiFactory_CreateEmpty((igViewerGuiFactory *)self->_guiFactory, 1));
        setParameters(pick, (igObject *)self->_parameters);
        setGuiSystem(pick, (igObject *)self->_gui);
        igViewManager_SetViewMode((igViewManager *)self->_viewManager, (igViewMode *)pick.p);
        break;
    }
    case 2: {
        igSmartPointer<igFlyMode> fly(createFlyMode());
        setWindow(fly, (igObject *)((igInsightCore *)self->_insight)->_window);
        igViewManager_SetViewMode((igViewManager *)self->_viewManager, (igViewMode *)fly.p);
        break;
    }
    case 1: {
        igSmartPointer<igRotateMode> rotate(createRotateMode());
        igViewManager_SetViewMode((igViewManager *)self->_viewManager, (igViewMode *)rotate.p);
        break;
    }
    case 3: {
        igSmartPointer<igRotateMode> rotate(createRotateMode());
        rotate.p->_maya = 1;
        igViewManager_SetViewMode((igViewManager *)self->_viewManager, (igViewMode *)rotate.p);
        break;
    }
    default: {
        int first = parameters->_firstCameraMode;
        if (mode >= first) {
                first = mode - first;
            igSmartPointer<igCameraMode> camera(createCameraMode());
            igCameraMode_SetCameraPath(camera.p, (igObject *)(((int *)((igObjectList *)((igViewerParameters *)self->_parameters)->_cameras)->_data)[first]));
            igViewManager_SetViewMode((igViewManager *)self->_viewManager, (igViewMode *)camera.p);
            self->_clippingCheckFrame = ((igInsightCore *)self->_insight)->_frames + 1;
        }
        break;
    }
    }
}

void igViewerSceneInfoManager_Start(void) {

}

void igViewerSceneInfoManager_Stop(void) {

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

igMetaObject *igViewerAction_GetMeta(void) {
    return g_igViewerAction_metaObject;
}

int igViewerSceneInfoManager_GetMeta(void) {
    return (int)g_igViewerSceneInfoManager_metaObject;
}

igMetaObject *igViewerSceneInfoManagerController_GetMeta(void) {
    return g_igViewerSceneInfoManagerController_metaObject;
}

void igViewerSceneInfoManagerController_IsCompatible(igViewerSceneInfoManagerController *self, igObject *model) {
    ((Gap::Core::igObject *)model)->isOfType(g_igViewerParameters_metaObject);
}

void igStatisticsItem_OnModelChange(void) {

}

void igViewerStatisticsManager_constructFields(void) {

}

void igViewerStatisticsManager_destructFields(void) {

}

float igViewerStatisticsManager_GetStatisticValue(void) {
    return 0.0f;
}

float igViewerStatisticsManager_GetStatisticMaximumValue(void) {
    return -1.0f;
}

void igViewerStatisticsManager_SetStatisticMaximumValue(void) {

}

float igViewerStatisticsManager_GetGroupStatisticValue(void) {
    return 0.0f;
}

float igViewerStatisticsManager_GetGroupStatisticMaximumValue(void) {
    return -1.0f;
}

igMetaObject *igViewerStatisticsManager_GetMeta(void) {
    return g_igViewerStatisticsManager_metaObject;
}

igMetaObject *igStatisticsItem_GetMeta(void) {
    return g_igStatisticsItem_metaObject;
}

void igStatisticsItem_IsCompatible(igStatisticsItem *self, igObject *model) {
    ((Gap::Core::igObject *)model)->isOfType(igOnOffModel_GetMetaObject());
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
