#include "dw4/support/reflected.h"
#include "dw4/core/igSmartPointer.h"
#include "dw4/maths/igMath.h"
#include "dw4/maths/igVec3f.h"
#include "dw4/scenegraph/igCameraDispatchView.h"
#include "dw4/viewer/igCameraMode.h"

#include "dw4/core/igObject.h"
#include "dw4/scenegraph/igGraphPath.h"
#include "dw4/gui/igModel.h"
#include "dw4/maths/igMatrix44f.h"
#include "dw4/core/igResult.h"
#include "dw4/scenegraph/igProbe.h"
#include "dw4/scenegraph/igIntersectTraversal.h"
#include "dw4/gui/igGuiSystem.h"
#include "dw4/core/igDataLists.h"
#include "dw4/viewer/igViewModel.h"
#include "dw4/scenegraph/igCamera.h"
#include "dw4/viewer/igPickMode.h"
#include "dw4/viewer/igRotateMode.h"
#include "dw4/viewer/igFlyMode.h"
#include "dw4/viewer/igViewMode.h"
#include "dw4/viewer/igViewerParameters.h"
#include <math.h>
#include "dw4/maths/igMathConstants.h"
#include "dw4/maths/igRay.h"
#include "dw4/gui/igGuiSystemModel.h"
extern "C" {

/* The pick mode whose intersect traversal is running, for its hit callback. */
extern igPickMode *g_pickingMode[4];

/* What igModel_NotifyViews tells a model's views: type 2 is a changed field, sent by `sender`. */
typedef struct ViewModelEvent { int type; void *sender; igMetaField *field; } ViewModelEvent;
enum { VIEW_MODEL_FIELD_CHANGED = 2 };

/* igViewMode's own virtual methods past igObject's: slots 29 and 30 are the start and stop every mode
 * overrides (igCameraMode_OnAttach, igCameraMode_OnDetach). ABI view only: never instantiated. */
class igViewModeDispatchView : public igObjectDispatchView {
public:
    virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28();
    virtual void OnAttach();                                                /* slot 29 */
    virtual void OnDetach();                                                /* slot 30 */
};
/* igIntersectTraversal's traversal entry (slot 23) and time setter (slot 25).
 * ABI view only: never instantiated. */
class igIntersectTraversalDispatchView : public igObjectDispatchView {
public:
    virtual void d21(); virtual void d22();
    virtual void Apply(int scene);                                          /* slot 23 */
    virtual void d24();
    virtual void SetTimeAsLong(long long time);                             /* slot 25 */
};

/* What an intersect traversal hands its hit callback. */
struct IntersectHit { char pad0[8]; int nodes; char pad12[8]; float distance; };

void igViewMode_UpdateInverseMatrix(igViewMode *self);
void igViewMode_UpdateModelVectors(igViewMode *self);
void igViewMode_UpdateViewMatrix(igViewMode *self);
void igFlyMode_AimingChanged(igFlyMode *self);
void igFlyMode_ApplyTranslation(igFlyMode *self, float seconds);
void igFlyMode_ApplyRotation(igFlyMode *self, float seconds);
void igFlyMode_ApplyAim(igFlyMode *self);
void igPickMode_RecordHit(igPickMode *self, IntersectHit *hit);
void igPickMode_Pick(igPickMode *self);

static inline igObject *asCamera(igObject *o) {
    if (o != 0 && ((Gap::Core::igObject *)o)->isOfType(g_igCamera_metaObject) != 0) {
        return o;
    }
    return 0;
}

static inline void setVec3(float *v, float x, float y, float z) {
    v[0] = x;
    v[1] = y;
    v[2] = z;
}
static inline void scaleVec3(float *v, float s) {
    v[0] = v[0] * s;
    v[1] = v[1] * s;
    v[2] = v[2] * s;
}

static inline int count_of(const igIntList *list) { return list->_count; }
static inline void setProbe(igPickMode *pickMode, const igSmartPointer<igProbe> &probe) {
    igObject *retained = (igObject *)probe.get();
    igIntersectTraversal *traversal = (igIntersectTraversal *)pickMode->_intersectTraversal;
    igObject *previous;
    if (retained != 0) {
        retained->_refCount = retained->_refCount + 1;
    }
    previous = (igObject *)traversal->_probe;
    if (previous != 0) {
        previous->_refCount = previous->_refCount - 1;
        if ((previous->_refCount & 0x7FFFFF) == 0) {
            igObject_Destroy(previous);
        }
    }
    traversal->_probe = (int)retained;
}

static inline void setHitPath(igPickMode *pickMode, const igSmartPointer<igGraphPath> &path) {
    igGraphPath *held = path.get();
    igGraphPath *previous;
    if (held != 0) {
        held->_refCount = held->_refCount + 1;
    }
    previous = (igGraphPath *)pickMode->_hitPath;
    if (previous != 0) {
        previous->_refCount = previous->_refCount - 1;
        if ((previous->_refCount & 0x7FFFFF) == 0) {
            igObject_Destroy(previous);
        }
    }
    pickMode->_hitPath = (int)held;
}
static inline igGraphPath *createGraphPath() { AdoptReference tag = AdoptReference(); return igGraphPath_Create(0); }

void igViewMode_IsCompatible(igViewMode *self, igObject *model) {
    ((Gap::Core::igObject *)model)->isOfType(g_igViewModel_metaObject);
}

void igViewMode_OnModelChange(igViewModeDispatchView *self, ViewModelEvent *event) {
    igMetaField *field = event->field;
    int type;
    if (field == g_igViewModel_viewMatrixMetaField) {
        igViewMode_UpdateInverseMatrix((igViewMode *)self);
        igViewMode_UpdateModelVectors((igViewMode *)self);
        return;
    }
    if (field == g_igViewModel_positionMetaField || field == g_igViewModel_directionMetaField ||
        field == g_igViewModel_viewUpVectorMetaField) {
        igViewMode_UpdateViewMatrix((igViewMode *)self);
        return;
    }
    type = event->type;
    if (type == 0) {
        igViewMode_UpdateInverseMatrix((igViewMode *)self);
        igViewMode_UpdateModelVectors((igViewMode *)self);
        self->OnAttach();
    } else if (type == 1) {
        self->OnDetach();
    }
}

void igViewMode_OnDetach(void) {

}

void igViewMode_OnAttach(void) {

}

void igViewMode_UpdateInverseMatrix(igViewMode *self) {

    igMatrix44f_Invert(self->_inverseMatrix, ((igViewModel *)self->_model)->_viewMatrix);
}

void igViewMode_UpdateModelVectors(igViewMode *self) {
    float v[3];
    ViewModelEvent positionChanged;
    ViewModelEvent directionChanged;
    ViewModelEvent leftChanged;
    igViewModel *model;

    model = (igViewModel *)self->_model;
    igMatrix44f_GetTranslation(self->_inverseMatrix, v);
    model->_position[0] = v[0];
    model->_position[1] = v[1];
    model->_position[2] = v[2];
    positionChanged.type = VIEW_MODEL_FIELD_CHANGED;
    positionChanged.sender = self;
    positionChanged.field = g_igViewModel_positionMetaField;
    igModel_NotifyViews((igModel *)model, (ModelChange *)&positionChanged);
    Vec3f_TransformDirection(model->_direction, &g_vec3ZAxis.x, self->_inverseMatrix);
    model->_direction[0] = -model->_direction[0];
    model->_direction[1] = -model->_direction[1];
    model->_direction[2] = -model->_direction[2];
    directionChanged.type = VIEW_MODEL_FIELD_CHANGED;
    directionChanged.sender = self;
    directionChanged.field = g_igViewModel_directionMetaField;
    igModel_NotifyViews((igModel *)model, (ModelChange *)&directionChanged);
    Vec3f_TransformDirection(model->_viewLeftVector, &g_vec3XAxis.x, self->_inverseMatrix);
    leftChanged.type = VIEW_MODEL_FIELD_CHANGED;
    leftChanged.sender = self;
    leftChanged.field = g_igViewModel_viewLeftVectorMetaField;
    igModel_NotifyViews((igModel *)model, (ModelChange *)&leftChanged);
}

void igViewMode_UpdateViewMatrix(igViewMode *self) {
    float center[3];
    igViewModel *model;

    model = (igViewModel *)self->_model;
    center[0] = model->_position[0];
    center[1] = model->_position[1];
    center[2] = model->_position[2];
    center[0] = center[0] + model->_direction[0];
    center[1] += model->_direction[1];
    center[2] += model->_direction[2];
    igMatrix44f_MakeLookAt(model->_viewMatrix, model->_position, center, model->_viewUpVector);
}

void igCameraMode_SetCameraPath(igCameraMode *self, igObject *path) {
    igObject *previous;
    igObject *camera;
    if (path != 0) {
        if (path != 0) {
            path->_refCount = path->_refCount + 1;
        }
        previous = (igObject *)self->_cameraPath;
        if (previous != 0) {
            previous->_refCount = previous->_refCount - 1;
            if (((unsigned long long)(long long)(int)previous->_refCount & 0x7fffffULL) == 0) {
                igObject_Destroy(previous);
            }
        }
        self->_cameraPath = (int)path;
        camera = igGraphPath_GetTail((igGraphPath *)path);
        camera = asCamera(camera);
        if (camera != 0) {
            camera->_refCount = camera->_refCount + 1;
        }
        previous = (igObject *)self->_camera;
        if (previous != 0) {
            previous->_refCount = previous->_refCount - 1;
            if (((unsigned long long)(long long)(int)previous->_refCount & 0x7fffffULL) == 0) {
                igObject_Destroy(previous);
            }
        }
        self->_camera = (int)camera;
    }
}

void igCameraMode_OnDetach(igCameraMode *self) {
    igCameraDispatchView *camera;

    camera = (igCameraDispatchView *)self->_camera;
    if (camera != 0) {
        camera->Deactivate();
    }
}

void igCameraMode_OnAttach(igCameraMode *self) {
    int hfovChanged[4];
    int farChanged[4];
    int nearChanged[4];
    float farPlane;
    float nearPlane;
    igCamera *camera;
    igViewModel *model;

    if (self->_camera != 0) {
        ((igCameraDispatchView *)self->_camera)->Activate();
        model = (igViewModel *)self->_model;
        camera = (igCamera *)self->_camera;
        farPlane = camera->_farPlane;
        nearPlane = camera->_nearPlane;
        model->_hfov = (float) camera->_horizontalFieldOfView;
        hfovChanged[0] = VIEW_MODEL_FIELD_CHANGED;
        hfovChanged[1] = 0;
        hfovChanged[2] = (int)g_igViewModel_hfovMetaField;
        igModel_NotifyViews((igModel *)model, (ModelChange *)hfovChanged);
        model->_farPlane = farPlane;
        farChanged[0] = VIEW_MODEL_FIELD_CHANGED;
        farChanged[1] = 0;
        farChanged[2] = (int)g_igViewModel_farPlaneMetaField;
        igModel_NotifyViews((igModel *)model, (ModelChange *)farChanged);
        nearPlane = (nearPlane == 0.0f) ? farPlane / 1000.0f : nearPlane;
        model->_nearPlane = nearPlane;
        nearChanged[0] = VIEW_MODEL_FIELD_CHANGED;
        nearChanged[1] = 0;
        nearChanged[2] = (int)g_igViewModel_nearPlaneMetaField;
        igModel_NotifyViews((igModel *)model, (ModelChange *)nearChanged);
    }
}

void igCameraMode_Update(igCameraMode *self) {
    float x, y, z;
    float translation[4];
    float world[16];
    int changed[4];
    igViewModel *model;
    if (self->_camera != 0) {
        igMatrix44f_SetIdentity(world);
        model = (igViewModel *)self->_model;
        igGraphPath_GetTransform((igGraphPath *)self->_cameraPath, (igMatrix44f *)world, model->_drawTime);
        x = 0; y = 0; z = 0;
        igMatrix44f_GetEulerAngles(world, &x, &y, &z);
        igMatrix44f_GetTranslation(world, translation);
        igMatrix44f_MakeEulerRotation(world, x, y, z);
        igMatrix44f_SetTranslation(world, translation);
        igMatrix44f_InvertOrthonormal(model->_viewMatrix, world);
        changed[0] = VIEW_MODEL_FIELD_CHANGED;
        changed[1] = 0;
        changed[2] = (int)g_igViewModel_viewMatrixMetaField;
        igModel_NotifyViews((igModel *)model, (ModelChange *)changed);
    }
}

void igFlyMode_OnKeyEvent(igFlyMode *self, int key, int down) {
    float f;
    switch (key) {
    case 0x9C:
        if (down) self->_speed *= 1.5f;
        break;    case 0x9D:
        if (down) self->_speed /= 1.5f;
        break;
    case 0x98:
        if (down) f = 1.0f; else f = -1.0f;
        self->_moveDirection[2] += f;
        break;
    case 0x92:
        if (down) f = 1.0f; else f = -1.0f;
        self->_moveDirection[2] -= f;
        break;
    case 0x88:
        if (down) f = 1.0f; else f = -1.0f;
        self->_moveDirection[1] -= f;
        break;
    case 0x89:
        if (down) f = 1.0f; else f = -1.0f;
        self->_moveDirection[1] += f;
        break;
    case 0x94:
        if (down) f = 1.0f; else f = -1.0f;
        self->_moveDirection[0] += f;
        break;
    case 0x96:
        if (down) f = 1.0f; else f = -1.0f;
        self->_moveDirection[0] -= f;
        break;
    case 0x5A:
        if (down) self->_aiming = !self->_aiming;
        igFlyMode_AimingChanged(self);
        break;
    }
}

void igFlyMode_OnMouseButton(igFlyMode *self, int button, int pressed) {
    switch (button) {
    case 0:
        self->_moveDirection[2] += pressed ? 1.0f : -1.0f;
        break;
    case 1:
        self->_moveDirection[2] -= pressed ? 1.0f : -1.0f;
        break;
    case 2:
        if (pressed) {
            self->_aiming = !self->_aiming;
            igFlyMode_AimingChanged(self);
        }
        break;
    }
}

void igFlyMode_OnMouseMove(igFlyMode *self, float x, float y) {
    self->_mousePos[0] = x;
    self->_mousePos[1] = y;
}

void igFlyMode_OnStickEvent(igFlyMode *self, int unused, unsigned short axis, float x, float y)
{
    if (axis == 0) {
        self->_joystickR[0] = x;
        self->_joystickR[1] = y;
    } else if (axis == 1) {
        self->_joystickT[0] = -x;
        self->_joystickT[1] = 0.0f;
        self->_joystickT[2] = y;
    }
}

void igFlyMode_AimingChanged(igFlyMode *self)
{
}

static inline float toRadians(float degrees) { return 0.017453292f * degrees; }
static inline void rotateRef(float *m, const igVec3f *axis, const float &angle) { igMatrix44f_PostRotateAxisAngle(m, &axis->x, angle); }
static inline float vecLength(const igVec3f &v) { return sqrtf(v.x * v.x + v.y * v.y + v.z * v.z); }

/* Turns the eye by the right stick, at most 120 degrees per second more than the last frame: about the
 * scene's up vector, then about the view's x axis. */
void igFlyMode_ApplyRotation(igFlyMode *self, float seconds) {
    float maxStep = 120.0f * seconds;
    float head = self->_joystickR[0];
    float pitch = self->_joystickR[1];
    head *= 60.0f;
    pitch *= 60.0f;
    float dHead = head - self->_lastRotation[0];
    float dPitch = pitch - self->_lastRotation[1];
    float distance = sqrtf(dHead * dHead + dPitch * dPitch);
    if (!(distance <= maxStep)) {
        float limit = maxStep / distance;
        dHead *= limit;
        dPitch *= limit;
        head = dHead + self->_lastRotation[0];
        pitch = dPitch + self->_lastRotation[1];
    }
    self->_lastRotation[0] = head;
    self->_lastRotation[1] = pitch;
    head *= seconds;
    pitch *= seconds;
    igViewModel *model = (igViewModel *)self->_model;
    igVec3f up;
    Vec3f_TransformDirection((float *)&up, model->_sceneUpVector, model->_viewMatrix);
    float scale = 1.0f / vecLength(up);
    up.x *= scale;
    up.y *= scale;
    up.z *= scale;
    igMatrix44f_PostRotateAxisAngle(model->_viewMatrix, &up.x, toRadians(head));
    igMatrix44f_PostRotateAxisAngle(model->_viewMatrix, &g_vec3XAxis.x, toRadians(pitch));
}

/* While aiming, turns the eye by the mouse's movement since the last frame. */
void igFlyMode_ApplyAim(igFlyMode *self) {
    igViewModel *model = (igViewModel *)self->_model;
    if (self->_lastAimValid) {
        float pitch = 30.0f * (self->_mousePos[1] - self->_lastAim[1]);
        float head = 60.0f * (self->_mousePos[0] - self->_lastAim[0]);
        igVec3f up;
        Vec3f_TransformDirection((float *)&up, model->_sceneUpVector, model->_viewMatrix);
        float scale = 1.0f / vecLength(up);
        up.x *= scale;
        up.y *= scale;
        up.z *= scale;
        igMatrix44f_PostRotateAxisAngle(model->_viewMatrix, &up.x, toRadians(head));
        /* matching construct: the (float) cast on the negated pitch orders the pi/180 constant before it. */
        igMatrix44f_PostRotateAxisAngle(model->_viewMatrix, &g_vec3XAxis.x, toRadians((float)(-pitch)));
    }
    self->_lastAim[0] = self->_mousePos[0];
    self->_lastAim[1] = self->_mousePos[1];
    self->_lastAimValid = 1;
}

void igFlyMode_Update(igFlyMode *self, float seconds) {
    int changed[3];
    int model;

    model = self->_model;
    igFlyMode_ApplyTranslation(self, seconds);
    if (self->_aiming != 0) {
        igFlyMode_ApplyAim(self);
    }
    igFlyMode_ApplyRotation(self, seconds);
    changed[0] = VIEW_MODEL_FIELD_CHANGED;
    changed[1] = 0;
    changed[2] = (int)g_igViewModel_viewMatrixMetaField;
    igModel_NotifyViews((igModel *)model, (ModelChange *)changed);
}

void igFlyMode_OnAttach(igFlyMode *self) {
    igViewModel *model;
    float dx;
    float dy;
    float dz;
    self->_aiming = 0;
    self->_lastAim[0] = 0.0f;
    self->_lastAim[1] = 0.0f;
    self->_lastTranslation[0] = 0.0f;
    self->_lastTranslation[1] = 0.0f;
    self->_lastTranslation[2] = 0.0f;
    self->_lastRotation[0] = 0.0f;
    self->_lastRotation[1] = 0.0f;
    self->_lastAimValid = 0;
    model = (igViewModel *)self->_model;
    dx = model->_selectedCenter[0];
    dy = model->_selectedCenter[1];
    dz = model->_selectedCenter[2];
    dx -= model->_position[0];
    dy -= model->_position[1];
    dz -= model->_position[2];
    self->_speed = 0.2f * sqrtf(dx * dx + dy * dy + dz * dz);
}

void igFlyMode_OnDetach(igFlyMode *self) {
    if (self->_aiming != 0) {
        self->_aiming = 0;
        igFlyMode_AimingChanged(self);
    }
}

void igRotateMode_OnKeyEvent(igRotateMode *self, int key, char down) {
    if ((self->_maya != 0) && ((key == 0xC8) || (key == 0xC9))) {
        self->_active = down;
    }
    if (key != 0xCA) {
        if (key == 0xCB) {
            goto constrain;
        }
    } else {
constrain:
        self->_constraint = down;
        self->_constraintAxis = 0;
    }
}

void igRotateMode_OnMouseButton(igRotateMode *self, int button, char pressed) {
    switch (button) {
    case 0:
        self->_leftMouseActive = pressed;
        break;
    case 2:
        self->_middleMouseActive = pressed;
        break;
    case 1:
        self->_rightMouseActive = pressed;
        break;
    }
    self->_constraintAxis = 0;
}

/* igRotateMode's drag handlers past igViewMode's slots: slot 31 the default button layout, slot 32 Maya's.
 * ABI view only: never instantiated. */
class igRotateModeDispatchView : public igViewModeDispatchView {
public:
    virtual void applyDrag(igVec2f *delta);                                 /* slot 31 */
    virtual void applyMayaDrag(igVec2f *delta);                             /* slot 32 */
};

typedef struct FloatBits { unsigned int mantissa : 23; unsigned int exponent : 8; unsigned int sign : 1; } FloatBits;
static inline float absf(float x) { ((FloatBits *)&x)->sign = 0; return x; }

/* While rotating, hands the mouse's movement since the last event to the drag handler; with the
 * constraint key held the drag keeps to the axis it first moved along. */
void igRotateMode_OnMouseMove(igRotateMode *self, float x, float y) {
    igViewModel *model = (igViewModel *)self->_model;
    if (self->_active) {
        igVec2f delta;
        delta[0] = x;
        delta[1] = y;
        delta[0] -= self->_lastMousePos[0];
        delta[1] -= self->_lastMousePos[1];
        if (self->_constraint) {
            if (self->_constraintAxis == 0) {
                if (!(absf(delta[0]) <= absf(delta[1]) * model->_ratio)) {
                    self->_constraintAxis = 1;
                } else {
                    self->_constraintAxis = 2;
                }
            }
            if (self->_constraintAxis == 1) {
                delta[1] = 0.0f;
            } else {
                delta[0] = 0.0f;
            }
        }
        if (self->_maya) {
            ((igRotateModeDispatchView *)self)->applyMayaDrag(&delta);
        } else {
            ((igRotateModeDispatchView *)self)->applyDrag(&delta);
        }
    }
    self->_lastMousePos[0] = x;
    self->_lastMousePos[1] = y;
}

/* Applies a mouse drag of `delta` with the default button layout: the left button rotates, the
 * middle one pans and the right one rolls and zooms. */
void Gap__Viewer__igRotateMode__ApplyDrag(igRotateMode *state, const float *delta) {
    igViewModel *model = (igViewModel *)state->_model;

    if (state->_leftMouseActive) {
        const float pi = 3.1415927f;
        state->_head += pi * delta[0];
        state->_pitch += pi * delta[1];
    }
    if (state->_middleMouseActive) {
        setVec3(state->_translation, delta[0], delta[1] / model->_ratio, 0.0f);
        scaleVec3(state->_translation, state->_distance / 2.0f);
    }
    if (state->_rightMouseActive) {
        float dx = delta[0];
        float dy;
        state->_roll += dx * 3.1415927f;
        dy = delta[1];
        state->_zoom *= 1.0f + dy / 2.0f;
    }
}

void igRotateMode_MouseMotionNormal(igRotateMode *state, const float *delta) {
    igViewModel *model = (igViewModel *)state->_model;

    if (state->_leftMouseActive) {
        if (state->_middleMouseActive) {
            float d = delta[0]; state->_zoom *= 1.0f - d / 2.0f;
        } else {
            const float pi = 3.1415927f;
            state->_head += pi * delta[0];
            state->_pitch += pi * delta[1];
        }
    } else if (state->_middleMouseActive) {
        setVec3(state->_translation, delta[0], delta[1] / model->_ratio, 0.0f);
        scaleVec3(state->_translation, state->_distance / 2.0f);
    }
}

void igRotateMode_OnStickEvent(igRotateMode *self, int unused, int stick, float x, float y) {
    int axis;
    axis = stick & 0xFFFF;
    if (axis == 0) {
        self->_joystickR[0] = x;
        self->_joystickR[1] = y;
    } else if (axis == 1) {
        self->_joystickT[0] = x;
        self->_joystickT[1] = y;
    }
}

void igRotateMode_OnAttach(igRotateMode *state) {
    igViewModel *model = (igViewModel *)state->_model;
    float dx;
    float dy;
    float dz;

    state->_constraint = 0;
    state->_constraintAxis = 0;
    state->_active = !state->_maya;
    state->_head = 0.0f;
    state->_roll = 0.0f;
    state->_pitch = 0.0f;
    state->_zoom = 1.0f;
    state->_translation[0] = g_vec3Zero.x;
    state->_translation[1] = g_vec3Zero.y;
    state->_translation[2] = g_vec3Zero.z;
    dx = model->_selectedCenter[0];
    dy = model->_selectedCenter[1];
    dz = model->_selectedCenter[2];
    dx -= model->_position[0];
    dy -= model->_position[1];
    dz -= model->_position[2];
    state->_distance = sqrtf(dx * dx + dy * dy + dz * dz);
}

/* Applies the stick and the drags gathered since the last frame: turns the view about the selection's
 * centre, zooms towards it and pans, then starts the next frame's gathering from rest. */
void igRotateMode_Update(igRotateMode *self, float seconds) {
    igViewModel *model = (igViewModel *)self->_model;
    float frames = 60.0f * seconds;
    float step = 0.1f * frames;
    self->_head += step * self->_joystickR[0];
    self->_pitch += step * self->_joystickR[1];
    self->_roll += step * self->_joystickT[0];
    self->_zoom *= 1.0f - 0.1f * (frames * self->_joystickT[1]);
    if (self->_active) {
        igVec3f center;
        Vec3f_TransformProjective((float *)&center, model->_selectedCenter, model->_viewMatrix);
        center[0] = -center[0];
        center[1] = -center[1];
        center[2] = -center[2];
        igMatrix44f_TranslateWorld(model->_viewMatrix, center);
        if (self->_maya) {
            if (self->_head != 0.0f) {
                igVec3f up;
                Vec3f_TransformDirection((float *)&up, model->_sceneUpVector, model->_viewMatrix);
                float scale = 1.0f / vecLength(up);
                up.x *= scale;
                up.y *= scale;
                up.z *= scale;
                rotateRef(model->_viewMatrix, &up, self->_head);
            }
        } else if (self->_head != 0.0f) {
            rotateRef(model->_viewMatrix, &g_vec3YAxis, self->_head);
        }
        if (self->_pitch != 0.0f) {
            rotateRef(model->_viewMatrix, &g_vec3XAxis, -self->_pitch);
        }
        if (self->_roll != 0.0f) {
            rotateRef(model->_viewMatrix, &g_vec3ZAxis, self->_roll);
        }
        center.scale(-self->_zoom);
        center[0] += self->_translation[0];
        center[1] += self->_translation[1];
        center[2] += self->_translation[2];
        self->_distance = vecLength(center);
        igMatrix44f_TranslateWorld(model->_viewMatrix, center);
        ViewModelEvent changed;
        changed.type = VIEW_MODEL_FIELD_CHANGED;
        changed.sender = 0;
        changed.field = g_igViewModel_viewMatrixMetaField;
        igModel_NotifyViews((igModel *)model, (ModelChange *)&changed);
    }
    self->_head = 0.0f;
    self->_roll = 0.0f;
    self->_pitch = 0.0f;
    self->_zoom = 1.0f;
    self->_translation[0] = g_vec3Zero[0];
    self->_translation[1] = g_vec3Zero[1];
    self->_translation[2] = g_vec3Zero[2];
}

int igPickMode_HitProc(int traversal, int data, int hit) {
    if (g_pickingMode[0] != 0) {
        igPickMode_RecordHit(g_pickingMode[0], (IntersectHit *)hit);
    }
    return 0;
}

/* Moves the GUI mouse cursor by the joystick's deflection over `seconds` and tells the GUI model's
 * views that the mouse position changed. */
void igPickMode_Update(igPickMode *pickMode, float seconds) {
    igGuiSystemModel *model = (igGuiSystemModel *)((igGuiSystem *)pickMode->_guiSystem)->_model;
    float dx = pickMode->_joystickT[0];
    float dy = pickMode->_joystickT[1];
    ViewModelEvent event;
    bool moving = dx != g_vec2Zero.x || dy != g_vec2Zero.y;

    if (moving) {
        dx *= seconds;
        dy *= seconds;
        model->_mousePosition[0] += dx;
        model->_mousePosition[1] += dy;
        event.type = VIEW_MODEL_FIELD_CHANGED;
        event.sender = 0;
        event.field = g_igGuiSystemModel_mousePositionMetaField;
        igModel_NotifyViews((igModel *)model, (ModelChange *)&event);
    }
}

void igPickMode_OnStickEvent(igPickMode *self, int unused, int stick, float x, float y) {
    if (!(stick & 0xFFFF)) {
        self->_joystickT[0] = x;
        self->_joystickT[1] = y;
    }
}

void igPickMode_OnMouseButton(igPickMode *self, int button, int pressed) {
    ViewModelEvent changed;
    int *selected;
    igObject *object;
    if (pressed != 0) {
        if (button == 0) {
            igPickMode_Pick(self);
        } else if (button == 1) {
            selected = &((igViewerParameters *)self->_parameters)->_selectedObject;
            object = (igObject *)*selected;
            if (object != 0) {
                object->_refCount = object->_refCount - 1;
                if (((unsigned long long)((long long)(int)object->_refCount << 0x29) >> 0x29) == 0) {
                    igObject_Destroy(object);
                }
            }
            *selected = 0;
            changed.type = VIEW_MODEL_FIELD_CHANGED;
            changed.sender = 0;
            changed.field = g_igViewerParameters_selectedObjectMetaField;
            igModel_NotifyViews((igModel *)self->_parameters, (ModelChange *)&changed);
        }
    }
}

void igPickMode_OnButtonEvent(igPickMode *self, void *unused, int key, int down) {
    if ((key == 0xE) && (down != 0)) {
        igPickMode_Pick(self);
    }
}

void igPickMode_OnAttach(igPickMode *pickMode) {
    igProbe *created;
    igIntList *faceTypes;
    int top;
    igIntersectTraversal *traversal;
    igObject *previous;
    igObject *cursor;
    igMatrix44f_Invert(pickMode->_inverseProjectionMatrix, ((igViewerParameters *)pickMode->_parameters)->_projectionMatrix);
    igSmartPointer<igProbe> probe(igProbe_Create(0), AdoptReference());
    created = probe.get();
    ObjectList_AppendRetained((igObjectList *)created->_rays, (igObject *)pickMode->_ray);
    faceTypes = (igIntList *)created->_intersectFaceType;
    top = count_of(faceTypes);
    if (top < faceTypes->_capacity) {
        faceTypes->_count = faceTypes->_count + 1;
    } else {
        List_Resize(faceTypes, top + 1, 4);
    }
    ((int *)faceTypes->_data)[top] = 2;
    setProbe(pickMode, probe);
    ((igIntersectTraversal *)pickMode->_intersectTraversal)->_mode = 0;
    ((igIntersectTraversal *)pickMode->_intersectTraversal)->_mode = ((igIntersectTraversal *)pickMode->_intersectTraversal)->_mode | 4;
    ((igIntersectTraversal *)pickMode->_intersectTraversal)->_hitProc = (int)&igPickMode_HitProc;
    ((igIntersectTraversal *)pickMode->_intersectTraversal)->_userTimeState = 1;
    if (pickMode->_guiSystem != 0) {
        cursor = (igObject *)((igGuiSystem *)pickMode->_guiSystem)->_mouseCursor;
        if (cursor != 0) {
            cursor->_refCount = cursor->_refCount + 1;
        }
        previous = (igObject *)pickMode->_savedCursor;
        if (previous != 0) {
            previous->_refCount = previous->_refCount - 1;
            if ((previous->_refCount & 0x7FFFFF) == 0) {
                igObject_Destroy(previous);
            }
        }
        pickMode->_savedCursor = (int)cursor;
        pickMode->_savedCursorState = ((igGuiSystem *)pickMode->_guiSystem)->_mouseCursorVisible;
        igGuiSystem_SetMouseCursor((igGuiSystem *)pickMode->_guiSystem, (igMouseCursor *)pickMode->_cursor);
        igGuiSystem_SetMouseCursorVisible((igGuiSystem *)pickMode->_guiSystem, true);
    }
}

void igPickMode_OnDetach(igPickMode *self) {
    if (self->_guiSystem != 0) {
        igGuiSystem_SetMouseCursor((igGuiSystem *)self->_guiSystem, (igMouseCursor *)self->_savedCursor);
        /* reflected.h spells the igBool _savedCursorState as unsigned char; showCursor takes the kit's igBool (bool). */
        igGuiSystem_SetMouseCursorVisible((igGuiSystem *)self->_guiSystem, *(bool *)&self->_savedCursorState);
    }
}

void igPickMode_RecordHit(igPickMode *self, IntersectHit *hit) {
    int nodes = hit->nodes;
    if (hit->distance <= self->_impactLength) {
        self->_hit = 1;
        self->_impactLength = hit->distance;
        setHitPath(self, igSmartPointer<igGraphPath>(createGraphPath()));
        igGraphPath_SetNodes((igGraphPath *)self->_hitPath, (igNodeList *)nodes);
    }
}

void igPickMode_Pick(igPickMode *self) {
    float point[3];
    int changed[3];
    igViewModel *model;
    int *selected;
    igObject *previous, *hitPath;
    model = (igViewModel *)self->_model;
    igGuiSystemModel *gui = (igGuiSystemModel *)((igGuiSystem *)self->_guiSystem)->_model;
    float y = *(float *)&gui->_mousePosition[1];
    point[0] = *(float *)&gui->_mousePosition[0];
    point[1] = y;
    *(int *)&point[2] = 0x3F800000;
    Vec3f_TransformProjective(point, point, self->_inverseProjectionMatrix);
    igRay_SetFromPoints((igRay *)self->_ray, &g_vec3Zero.x, point);
    igRay_Transform((igRay *)self->_ray, self->_inverseMatrix);
    self->_impactLength = ((igRay *)self->_ray)->_len;
    self->_hit = 0;
    previous = (igObject *)self->_hitPath;
    if (previous != 0) {
        previous->_refCount = previous->_refCount - 1;
        if (((unsigned long long)(long long)(int)previous->_refCount & 0x7fffffULL) == 0)
            igObject_Destroy(previous);
    }
    self->_hitPath = 0;
    igIntersectTraversal_ResetStacks((igIntersectTraversal *)((igIntersectTraversalDispatchView *)self->_intersectTraversal));
    ((igIntersectTraversalDispatchView *)self->_intersectTraversal)->SetTimeAsLong(model->_drawTime);
    g_pickingMode[0] = self;
    ((igIntersectTraversalDispatchView *)self->_intersectTraversal)->Apply(((igViewerParameters *)self->_parameters)->_scene);
    g_pickingMode[0] = 0;
    selected = &((igViewerParameters *)self->_parameters)->_selectedObject;
    hitPath = (igObject *)self->_hitPath;
    if (hitPath != 0) {
        hitPath->_refCount = hitPath->_refCount + 1;
    }
    previous = (igObject *)*selected;
    if (previous != 0) {
        previous->_refCount = previous->_refCount - 1;
        if (((unsigned long long)(long long)(int)previous->_refCount & 0x7fffffULL) == 0)
            igObject_Destroy(previous);
    }
    *selected = (int)hitPath;
    changed[0] = VIEW_MODEL_FIELD_CHANGED;
    changed[1] = 0;
    changed[2] = (int)g_igViewerParameters_selectedObjectMetaField;
    igModel_NotifyViews((igModel *)((igViewerParameters *)self->_parameters), (ModelChange *)changed);
}

/* Returns the metaobject handle of igPickMode, not of igViewManager. */
igMetaObject *igPickMode_GetMeta(void) {
    return g_igPickMode_metaObject;
}

igMetaObject *igRotateMode_GetMeta(void) {
    return g_igRotateMode_metaObject;
}

igMetaObject *igFlyMode_GetMeta(void) {
    return g_igFlyMode_metaObject;
}

int igCameraMode_GetMeta(void) {
    return (int)g_igCameraMode_metaObject;
}

igMetaObject *igViewMode_GetMeta(void) {
    return g_igViewMode_metaObject;
}

}

igVec4f g_whiteColor(1.0f, 1.0f, 1.0f, 1.0f);
igVec4f g_redColor(1.0f, 0.0f, 0.0f, 1.0f);
