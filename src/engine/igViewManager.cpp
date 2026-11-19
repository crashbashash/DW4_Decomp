#include "dw4/support/reflected.h"
#include "dw4/core/igSmartPointer.h"
#include "dw4/viewer/ViewerSetup.h"
#include "dw4/viewer/igViewManager.h"
#include "dw4/maths/igVec3f.h"
#include "dw4/core/igDataLists.h"
#include "dw4/viewer/igViewerParameters.h"

#pragma push
#pragma readonly_strings on

#include "dw4/viewer/igViewerSceneInfoManager.h"
#include "dw4/insight/igInsightCore.h"
#include "dw4/gui/igView.h"
#include "dw4/gui/igModel.h"
#include "dw4/viewer/ViewerOptions.h"
#include "dw4/core/StringPool.h"
#include "dw4/viewer/igViewModel.h"
#include "dw4/core/igReport.h"
#include "dw4/maths/igMatrix44f.h"
#include "dw4/core/igResult.h"
#include "dw4/core/igNamedObject.h"
#include <math.h>
#include "dw4/viewer/igActorManager.h"
#include "dw4/viewer/igLogoRenderer.h"
#include "dw4/viewer/igViewerDataPumpManager.h"
#include "dw4/gui/igFieldSynchronizer.h"
#include "dw4/viewer/igViewModeDispatchView.h"
#include "dw4/windowinput/igWindowDispatchView.h"
extern "C" {

#include "dw4/scenegraph/igBoundingBoxesMaker.h"

extern unsigned char GPR_00554e7c;
extern unsigned char GPR_00554e80;

/* The maker hands back a box that already holds one reference; the smart pointer takes its own. */
static inline void dropCreatedReference(igAABox *box) {
    box->_refCount = box->_refCount - 1;
    if ((box->_refCount & 0x7FFFFF) == 0) igObject_Destroy(box);
}
void igViewManager_GetObjectProps(igNode *scene, float *center, float *size, bool wholeAnimation, long long time);


static inline void releaseString(void *p) {
    if (p != 0) {
        int *h = (int *)((char *)p - 8);
        int rc = *(int *)((char *)p - 4) - 1;
        *(int *)((char *)p - 4) = rc;
        if (rc == 0) StringChunk_ReleaseHeader((StringChunk *)*h, (StringTokenHeader *)h);
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

struct StringRef {
    void *p;
    ~StringRef() { releaseString(p); }
};

ViewerSetup::ViewerSetup(igObject *w)
    : core((InsightCore *)igInsightCore_CreateInstance(0), AdoptReference()), sceneInfo(igViewerSceneInfoManager_Create(0), AdoptReference()),
      actors(igActorManager_Create(0), AdoptReference()), dataPump(igViewerDataPumpManager_Create(0), AdoptReference()), showLogo(1),
      logo(igLogoRenderer_Create(0), AdoptReference()), window(w, kRetainReference) {
    igObject *next = window.p;
    if (next != 0) {
        InsightCore *c = core.p;
        c->window = next;
        if (g_sharedViewerOptions == 0) {
            SharedViewerOptions *f = (SharedViewerOptions *)operator new(sizeof(SharedViewerOptions));
            if (f != 0) f = igViewerDefaults_Construct(f);
            g_sharedViewerOptions = f;
        }
        g_sharedViewerOptions->useCount = g_sharedViewerOptions->useCount + 1;
        {
            SharedViewerOptions *g = g_sharedViewerOptions;
            showLogo = g->showLogo != 0 && !(g->benchmark != 0);
        }
        if (g_sharedViewerOptions != 0) {
            if (--g_sharedViewerOptions->useCount <= 0) {
                SharedViewerOptions *s1 = g_sharedViewerOptions;
                if (s1 != 0) {
                    if (&s1->internedString) releaseString((void *)s1->internedString);
                    if (s1 != 0) releaseString(s1->extraCommandLine);
                    operator delete(s1);
                }
                g_sharedViewerOptions = 0;
            }
        }
        if (showLogo) {
            StringRef scenes;
            StringRef overlays;
            scenes.p = intern("Scenes done");
            overlays.p = intern("Overlays done");
            igInsightCore_AddRendererOrder((igInsightCore *)core.p, (igObject *)scenes.p, logo.p);
            igInsightCore_AddRendererOrder((igInsightCore *)core.p, logo.p, (igObject *)overlays.p);
            igInsightCore_AddRenderer((igInsightCore *)core.p, logo.p);
        }
        igInsightCore_AddManager((igInsightCore *)core.p, sceneInfo.p);
        igInsightCore_AddManager((igInsightCore *)core.p, dataPump.p);
        igNamedObject_SetName((igNamedObject *)actors.p, "Actor manager");
        igInsightCore_AddManager((igInsightCore *)core.p, actors.p);
    }
}

ViewerSetup::~ViewerSetup() {
    if (window.p != 0) {
        igInsightCore_RemoveManager((igInsightCore *)core.p, dataPump.p);
        igInsightCore_RemoveManager((igInsightCore *)core.p, actors.p);
        igInsightCore_RemoveManager((igInsightCore *)core.p, sceneInfo.p);
        if (showLogo != 0) {
            igInsightCore_RemoveRenderer((igInsightCore *)core.p, logo.p);
        }
    }
}

void ViewerSetup_Open(ViewerSetup *setup) {
    igInsightCore_InitializeDrawing((igInsightCore *)setup->core.p);
    igInsightCore_RegisterAllPlugins((igInsightCore *)setup->core.p);
    igInsightCore_Begin((igInsightCore *)setup->core.p);
}

void ViewerSetup_Close(ViewerSetup *setup) {
    igInsightCore_End((igInsightCore *)setup->core.p);
    igInsightCore_UnregisterAllPlugins((igInsightCore *)setup->core.p);
    igInsightCore_TerminateDrawing((igInsightCore *)setup->core.p);
}

void ViewerSetup_RunFrame(ViewerSetup *setup)
{
    igInsightCore_DrawFrame((igInsightCore *)setup->core.p);
}

int ViewerSetup_Update(ViewerSetup *setup) {
    igInsightCore_HandleEvents((igInsightCore *)setup->core.p);
    if (setup->showLogo) {
        igInsightCore *core = (igInsightCore *)setup->core.p;
        long long now = core->_currentTime;
        if (now > 4000000000LL) {
            igInsightCore_RemoveRenderer(core, setup->logo.p);
            setup->showLogo = 0;
        } else {
            ((igLogoRenderer *)setup->logo.p)->_time = now;
        }
    }
    igGuiSystem *gui = (igGuiSystem *)((igViewerSceneInfoManager *)setup->sceneInfo.p)->_gui;
    int running = (((igGuiSystemModel *)gui->_model)->_windowCloseRequested != 0) ^ 1;
    if (running) {
        running = ((igWindowDispatchView *)setup->window.p)->isOpen() != 0;
    }
    return running;
}

void ViewerSetup_ResetView(ViewerSetup *setup)
{
    igViewerSceneInfoManager_ResetView((igViewerSceneInfoManager *)setup->sceneInfo.p);
}

void ViewerSetup_ClearInfos(ViewerSetup *setup)
{
    igInsightCore_RemoveAllInfos((igInsightCore *)setup->core.p);
}

static inline void createSynchronizer(igSmartPointer<igFieldSynchronizer> &synchronizer, AdoptReference) {
    igRelease(synchronizer.p);
    synchronizer.p = igFieldSynchronizer_Create(0);
}

/* Keeps each view-model field and the parameters' field of the same name equal. */
void igViewManager_SynchronizeParameters(igViewManager *manager, igViewerParameters *parameters) {
    igSmartPointer<igFieldSynchronizer> synchronizer;

    createSynchronizer(synchronizer, AdoptReference());
    igFieldSynchronizer_AddField(synchronizer, (igObject *)manager->_viewModel, g_igViewModel_viewMatrixMetaField);
    igFieldSynchronizer_AddField(synchronizer, parameters, g_igViewerParameters_viewMatrixMetaField);
    ObjectList_AppendRetained((igObjectList *)manager->_synchronizers, synchronizer);

    createSynchronizer(synchronizer, AdoptReference());
    igFieldSynchronizer_AddField(synchronizer, (igObject *)manager->_viewModel, g_igViewModel_ratioMetaField);
    igFieldSynchronizer_AddField(synchronizer, parameters, g_igViewerParameters_ratioMetaField);
    ObjectList_AppendRetained((igObjectList *)manager->_synchronizers, synchronizer);

    createSynchronizer(synchronizer, AdoptReference());
    igFieldSynchronizer_AddField(synchronizer, (igObject *)manager->_viewModel, g_igViewModel_hfovMetaField);
    igFieldSynchronizer_AddField(synchronizer, parameters, g_igViewerParameters_hfovMetaField);
    ObjectList_AppendRetained((igObjectList *)manager->_synchronizers, synchronizer);

    createSynchronizer(synchronizer, AdoptReference());
    igFieldSynchronizer_AddField(synchronizer, (igObject *)manager->_viewModel, g_igViewModel_nearPlaneMetaField);
    igFieldSynchronizer_AddField(synchronizer, parameters, g_igViewerParameters_nearPlaneMetaField);
    ObjectList_AppendRetained((igObjectList *)manager->_synchronizers, synchronizer);

    createSynchronizer(synchronizer, AdoptReference());
    igFieldSynchronizer_AddField(synchronizer, (igObject *)manager->_viewModel, g_igViewModel_farPlaneMetaField);
    igFieldSynchronizer_AddField(synchronizer, parameters, g_igViewerParameters_farPlaneMetaField);
    ObjectList_AppendRetained((igObjectList *)manager->_synchronizers, synchronizer);

    createSynchronizer(synchronizer, AdoptReference());
    igFieldSynchronizer_AddField(synchronizer, (igObject *)manager->_viewModel, g_igViewModel_drawTimeMetaField);
    igFieldSynchronizer_AddField(synchronizer, parameters, g_igViewerParameters_drawTimeMetaField);
    ObjectList_AppendRetained((igObjectList *)manager->_synchronizers, synchronizer);
}

void igViewManager_SetViewMode(igViewManager *manager, igViewMode *mode) {
    igObject *previous = (igObject *)manager->_viewMode;
    if (previous != 0) {
        igView_SetModel((igView *)previous, 0);
    }
    if (mode != 0) {
        mode->_refCount = mode->_refCount + 1;
    }
    previous = (igObject *)manager->_viewMode;
    if (previous != 0) {
        previous->_refCount = previous->_refCount - 1;
        if (((unsigned long long)((long long)(int)previous->_refCount << 0x29) >> 0x29) == 0) {
            igObject_Destroy(previous);
        }
    }
    manager->_viewMode = (int)mode;
    if (mode != 0) {
        igView_SetModel((igView *)mode, (igModel *)manager->_viewModel);
    }
}

void igViewManager_SetFrameTime(igViewManager *manager, long long frameTime) {
    int units = frameTime / 0x40000; ((igViewModeDispatchView *)manager->_viewMode)->Update(262144.0f * (1e-9f * units));
}

void igViewMode_Update(void) {

}

void igViewManager_SetSceneUpVector(igViewManager *manager, const float *upVector) {
    ModelChange event;
    igViewModel *model;

    model = (igViewModel *)manager->_viewModel;
    model->_sceneUpVector[0] = upVector[0];
    model->_sceneUpVector[1] = upVector[1];
    model->_sceneUpVector[2] = upVector[2];
    event.type = 2;
    event.source = 0;
    event.field = g_igViewModel_sceneUpVectorMetaField;
    igModel_NotifyViews((igModel *)manager->_viewModel, &event);
}

/* Bounds at one time instead of over the whole animation. */
static inline void setMakerTime(igBoundingBoxesMaker *maker, long long time) {
    maker->_useWholeAnimation = 0;
    maker->_time = time;
}

/* The centre of `scene`'s bounding box and the length of its diagonal, over the whole animation or at `time`. */
void igViewManager_GetObjectProps(igNode *scene, float *center, float *size, bool wholeAnimation, long long time) {
    igSmartPointer<igBoundingBoxesMaker> maker(igBoundingBoxesMaker_Create(0), AdoptReference());
    if (wholeAnimation) {
        maker->_useWholeAnimation = 1;
    } else {
        setMakerTime(maker, time);
    }
    igSmartPointer<igAABox> box(igBoundingBoxesMaker_ComputeBox(maker, scene), kRetainReference);
    dropCreatedReference(box);
    const igAABox *bounds = box;
    float minX = bounds->_min[0];
    float maxX = bounds->_max[0];
    if (!(minX <= maxX)) {
        center[0] = 0.0f;
        center[1] = 0.0f;
        center[2] = 0.0f;
        *size = 0.0f;
    } else {
        center[0] = 0.5f * minX + 0.5f * maxX;
        center[1] = 0.5f * bounds->_min[1] + 0.5f * bounds->_max[1];
        center[2] = 0.5f * bounds->_min[2] + 0.5f * bounds->_max[2];
        float dx = box->_max[0] - box->_min[0];
        float dy = box->_max[1] - box->_min[1];
        float dz = box->_max[2] - box->_min[2];
        *size = sqrtf(dx * dx + dy * dy + dz * dz);
    }
}

int igViewManager_OnKeyEvent(igViewManager *self) {
    ((igViewModeDispatchView *)self->_viewMode)->OnKeyEvent();
    return 1;
}


/* Looks at `object` from one and a half of its sizes away, across the scene's up vector. */
void igViewManager_FrameObject(igViewManager *manager, igNode *object) {
    igVec3f center;
    float size;
    igVec3f eye;
    igVec3f up;
    ModelChange event;

    center.set(0.0f, 0.0f, 0.0f);
    size = 0.0f;
    igViewManager_GetObjectProps(object, &center.x, &size, true, -1);
    if (size == 0.0f) {
        size = 1.0f;
    }
    size *= 1.5f;
    up.copy(((igViewModel *)manager->_viewModel)->_sceneUpVector);
    eye[0] = up[2];
    eye[1] = up[0];
    eye[2] = up[1];
    eye.scale(size);
    eye[0] += center[0];
    eye[1] += center[1];
    eye[2] += center[2];
    igMatrix44f_MakeLookAt(((igViewModel *)manager->_viewModel)->_viewMatrix, (const float *)&eye, (const float *)&center, (const float *)&up);
    event.type = 2;
    event.source = 0;
    event.field = g_igViewModel_viewMatrixMetaField;
    igModel_NotifyViews((igModel *)manager->_viewModel, &event);
    igViewModel *model = (igViewModel *)manager->_viewModel;
    model->_selectedCenter[0] = center[0];
    model->_selectedCenter[1] = center[1];
    model->_selectedCenter[2] = center[2];
    ((igViewModel *)manager->_viewModel)->_selectedLength = size;
}

void igViewManager_ApplyOptions(igViewManager *manager, igObject *scene) {
    float center[3];
    float size;
    ModelChange nearChanged;
    ModelChange farChanged;
    ModelChange hfovChanged;
    SharedViewerOptions *options;
    SharedViewerOptions *f;
    igViewManager_GetObjectProps((igNode *)scene, center, &size, 1, -1);
    if (g_sharedViewerOptions == 0) {
        f = (SharedViewerOptions *)operator new(sizeof(SharedViewerOptions));
        if (f != 0) f = igViewerDefaults_Construct(f);
        g_sharedViewerOptions = f;
    }
    g_sharedViewerOptions->useCount = g_sharedViewerOptions->useCount + 1;
    options = g_sharedViewerOptions;
    if (!(size <= 0.0f) && options->autoPlanes != 0) {
        ((igViewModel *)manager->_viewModel)->_nearPlane = size / 100.0f;
        ((igViewModel *)manager->_viewModel)->_farPlane = 3.0f * size;
    } else {
        ((igViewModel *)manager->_viewModel)->_nearPlane = options->defaultNearPlane;
        ((igViewModel *)manager->_viewModel)->_farPlane = options->defaultFarPlane;
    }
    nearChanged.source = 0;
    nearChanged.type = 2;
    nearChanged.field = g_igViewModel_nearPlaneMetaField;
    igModel_NotifyViews((igModel *)manager->_viewModel, &nearChanged);
    farChanged.type = 2;
    farChanged.source = 0;
    farChanged.field = g_igViewModel_farPlaneMetaField;
    igModel_NotifyViews((igModel *)manager->_viewModel, &farChanged);
    ((igViewModel *)manager->_viewModel)->_hfov = options->horizontalFieldOfView;
    hfovChanged.type = 2;
    hfovChanged.source = 0;
    hfovChanged.field = g_igViewModel_hfovMetaField;
    igModel_NotifyViews((igModel *)manager->_viewModel, &hfovChanged);
    if (g_sharedViewerOptions != 0) {
        if (--g_sharedViewerOptions->useCount <= 0) {
            f = g_sharedViewerOptions;
            if (f != 0) {
                if (&f->internedString) releaseString((void *)f->internedString);
                if (f != 0) releaseString(f->extraCommandLine);
                operator delete(f);
            }
            g_sharedViewerOptions = 0;
        }
    }
}

/* igViewModel's vector fields are igVec3f values (igVec3fMetaField). */
static inline const igVec3f &asVec3f(const float *v) { return *(const igVec3f *)v; }

/* Looks at the selection's centre: from the current eye, or (`resetEye`) from one and a half selection
 * lengths across the scene's up vector. */
void igViewManager_CenterSelection(igViewManager *manager, bool resetEye) {
    igVec3f center(asVec3f(((igViewModel *)manager->_viewModel)->_selectedCenter));
    igVec3f eye;
    igVec3f up;
    ModelChange event;

    if (resetEye) {
        up.copy(((igViewModel *)manager->_viewModel)->_sceneUpVector);
        float distance = 1.5f * ((igViewModel *)manager->_viewModel)->_selectedLength;
        eye[0] = up[2];
        eye[1] = up[0];
        eye[2] = up[1];
        eye.scale(distance);
        eye.add(center);
        igMatrix44f_MakeLookAt(((igViewModel *)manager->_viewModel)->_viewMatrix, (const float *)&eye, (const float *)&center, (const float *)&up);
    } else {
        igViewModel *model = (igViewModel *)manager->_viewModel;
        igMatrix44f_MakeLookAt(model->_viewMatrix, model->_position, (const float *)&center, model->_viewUpVector);
    }
    event.type = 2;
    event.source = 0;
    event.field = g_igViewModel_viewMatrixMetaField;
    igModel_NotifyViews((igModel *)manager->_viewModel, &event);
}

/* Moves the eye along its line to the selection's centre until the selection fills the view. */
void igViewManager_FitSelection(igViewManager *manager) {
    igVec3f center(asVec3f(((igViewModel *)manager->_viewModel)->_selectedCenter));
    igVec3f eye;
    ModelChange event;

    eye.copy(((igViewModel *)manager->_viewModel)->_position);
    eye[0] -= center[0];
    eye[1] -= center[1];
    eye[2] -= center[2];
    float distance = sqrtf(eye.x * eye.x + eye.y * eye.y + eye.z * eye.z);
    if (distance == 0.0) {
        eye.copy(((igViewModel *)manager->_viewModel)->_direction);
        distance = 1.0f;
    }
    eye.scale(1.5f * ((igViewModel *)manager->_viewModel)->_selectedLength / distance);
    eye[0] += center[0];
    eye[1] += center[1];
    eye[2] += center[2];
    igViewModel *model = (igViewModel *)manager->_viewModel;
    igMatrix44f_MakeLookAt(model->_viewMatrix, (const float *)&eye, (const float *)&center, model->_viewUpVector);
    event.type = 2;
    event.source = 0;
    event.field = g_igViewModel_viewMatrixMetaField;
    igModel_NotifyViews((igModel *)manager->_viewModel, &event);
}

int igViewManager_MouseMotionEvent(igViewManager *self) {
    ((igViewModeDispatchView *)self->_viewMode)->OnMouseMove();
    return 1;
}

int igViewManager_MouseButtonEvent(igViewManager *self) {
    ((igViewModeDispatchView *)self->_viewMode)->OnMouseButton();
    return 1;
}

/* Pulls each stick axis `deadZone` towards zero, and to zero inside it. */
static void igViewManager_ApplyDeadZone(float *x, float *y, float deadZone) {
    float value;
    float valueY;

    value = *x;
    if (!(value <= deadZone)) {
        *x = value - deadZone;
    } else if (value < -deadZone) {
        *x = value + deadZone;
    } else {
        *x = 0.0f;
    }
    valueY = *y;
    if (!(valueY <= deadZone)) {
        *y = valueY - deadZone;
        return;
    }
    if (valueY < -deadZone) {
        *y = valueY + deadZone;
        return;
    }
    *y = 0.0f;
}

int igViewManager_ControllerMotionEvent(igViewManager *self, int controller, int stick, float x, float y) {
    float adjustedY;
    float adjustedX;
    adjustedX = x;
    adjustedY = y;
    igViewManager_ApplyDeadZone(&adjustedX, &adjustedY, 0.3f);
    ((igViewModeDispatchView *)self->_viewMode)->OnStickEvent(controller, stick, adjustedX, adjustedY);
    return 1;
}

int igViewManager_ControllerButtonEvent(igViewManager *self) {
    ((igViewModeDispatchView *)self->_viewMode)->OnButtonEvent();
    return 1;
}

int igViewManager_WindowResizeEvent(igViewManager *self, int width, int height)
{
    ModelChange event;

    ((igViewModel *)self->_viewModel)->_ratio = (float)width / (float)height;
    event.type = 2;
    event.source = 0;
    event.field = g_igViewModel_ratioMetaField;
    igModel_NotifyViews((igModel *)self->_viewModel, &event);
    return 0;
}

void igViewManager_PrintViewMatrix(igViewManager *self) {
    float inverse[16];
    float *m;
    int r;

    m = ((igViewModel *)self->_viewModel)->_viewMatrix;
    if (GPR_00554e7c == 0) {
        r = igReport_Info("current view matrix :\n%.8f,\t%.8f,\t%.8f,\t%.8f,\n%.8f,\t%.8f,\t%.8f,\t%.8f,\n%.8f,\t%.8f,\t%.8f,\t%.8f,\n%.8f,\t%.8f,\t%.8f,\t%.8f\n",
                         m[0], m[1], m[2], m[3], m[4], m[5], m[6], m[7],
                         m[8], m[9], m[10], m[11], m[12], m[13], m[14], m[15]);
        if (r != 1 && r == 2) GPR_00554e7c = 1;
    }
    igMatrix44f_SetIdentity(inverse);
    igMatrix44f_Invert(inverse, ((igViewModel *)self->_viewModel)->_viewMatrix);
    m = inverse;
    if (GPR_00554e80 == 0) {
        r = igReport_Info("current inverse view matrix :\n%.8f,\t%.8f,\t%.8f,\t%.8f,\n%.8f,\t%.8f,\t%.8f,\t%.8f,\n%.8f,\t%.8f,\t%.8f,\t%.8f,\n%.8f,\t%.8f,\t%.8f,\t%.8f\n",
                         m[0], m[1], m[2], m[3], m[4], m[5], m[6], m[7],
                         m[8], m[9], m[10], m[11], m[12], m[13], m[14], m[15]);
        if (r != 1 && r == 2) GPR_00554e80 = 1;
    }
}

void igViewManager_resetFields(igViewManager *self) { igView_SetModel((igView *)self->_viewMode, (igModel *)self->_viewModel); }

int igViewManager_GetMeta(void) {
    return (int)g_igViewManager_metaObject;
}

}
#pragma pop
