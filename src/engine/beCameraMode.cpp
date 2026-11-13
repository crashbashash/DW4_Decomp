#include "dw4/reflected.h"
#include "dw4/igSmartPointer.h"
#include "dw4/igMath.h"

extern "C" {

int igObject_IsKindOf(...);
igObject *igGraphPath_GetTail(...);
int igModel_NotifyViews(...);

int Matrix44_Invert(...);
int Matrix44_InvertOrthonormal(int *status, float *out, float *matrix);
int Matrix44_MakeLookAt(...);
int Matrix44_MakeEulerRotation(float *matrix, float x, float y, float z);
int Matrix44_GetEulerAngles(float *matrix, float *x, float *y, float *z);
int Matrix44_GetTranslation(...);
int Matrix44_SetTranslation(float *matrix, float *translation);
int igMatrix44f_SetIdentity(float *matrix);
int Vec3f_TransformDirection(...);
int Vec3f_TransformProjective(...);
int igGraphPath_GetTransform(int path, float *matrix, long long time);
int igGraphPath_SetNodes(igGraphPath *path, int nodes);
igGraphPath *igGraphPath_Create(int);
igProbe *igProbe_Create(int);
int igRay_SetFromPoints(...);
int igRay_Transform(...);
int igIntersectTraversal_ResetStacks(...);
int igGuiSystem_SetMouseCursorVisible(int guiSystem, unsigned char visible);
int igGuiSystem_SetMouseCursor(...);
int List_Resize(...);
int ObjectList_AppendRetained(...);
extern float sqrtf(float);

extern int g_igViewModel_metaObject[4];
extern int g_igCamera_metaObject[4];
extern int g_igPickMode_metaObject[4];
extern int g_igRotateMode_metaObject[4];
extern int g_igFlyMode_metaObject[4];
extern int g_igCameraMode_metaObject[4];
extern int g_igViewMode_metaObject[4];

/* igViewModel's field handles, which a change notification names. */
extern int g_igViewModel_viewMatrixMetaField[4];
extern int g_igViewModel_hfovMetaField[4];
extern int g_igViewModel_nearPlaneMetaField[4];
extern int g_igViewModel_farPlaneMetaField[4];
extern int g_igViewModel_positionMetaField[4];
extern int g_igViewModel_directionMetaField[4];
extern int g_igViewModel_viewUpVectorMetaField[4];
extern int g_igViewModel_viewLeftVectorMetaField[4];
extern int g_igViewerParameters_selectedObjectMetaField[4];
extern int g_igGuiSystemModelMousePositionField[4];

extern int g_vec3XAxis[4];
extern int g_vec3ZAxis[4];
extern const float g_vec3Zero[4];
extern const float g_vec2Zero[2];

/* The pick mode whose intersect traversal is running, for its hit callback. */
extern igPickMode *g_pickingMode[4];

/* What igModel_NotifyViews tells a model's views: type 2 is a changed field, sent by `sender`. */
typedef struct ViewModelEvent { int type; int sender; int field; } ViewModelEvent;
enum { VIEW_MODEL_FIELD_CHANGED = 2 };

/* igViewMode's own virtual methods past igObject's, by vtable slot; what slots 29 and 30 are for has
 * not been named. */
class igViewModeVirtuals { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void v124(); virtual void v128(); };
/* igCamera's virtual slots 33 and 34 (unnamed). */
class igCameraVirtuals { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual void d32(); virtual int vX(); virtual int vY(); };
/* igIntersectTraversal's virtual slots 23 and 25 (unnamed). */
class igIntersectTraversalVirtuals { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void v23(int); virtual void d24(); virtual void v25(long long); };

/* What an intersect traversal hands its hit callback. */
struct IntersectHit { char pad0[8]; int nodes; char pad12[8]; float distance; };

void igViewMode_UpdateInverseMatrix(igViewMode *self);
void igViewMode_UpdateModelVectors(igViewMode *self);
void igViewMode_UpdateViewMatrix(igViewMode *self);
void igFlyMode_AimingChanged(igFlyMode *self);
void igFlyMode_ApplyTranslation(igFlyMode *self);
void igFlyMode_ApplyRotation(igFlyMode *self, float seconds);
void igFlyMode_ApplyAim(igFlyMode *self);
void igPickMode_RecordHit(igPickMode *self, IntersectHit *hit);
void igPickMode_Pick(igPickMode *self);

static inline igObject *asCamera(igObject *o) {
    if (o != 0 && igObject_IsKindOf(o, g_igCamera_metaObject[0]) != 0) {
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

void Gap__Bec__beCameraMode__vfunc_21(igViewMode *self, igObject *model) {
    igObject_IsKindOf(model, g_igViewModel_metaObject[0]);
}

void Gap__Bec__beCameraMode__vfunc_22(igViewModeVirtuals *self, ViewModelEvent *event) {
    int field = event->field;
    int type;
    if (field == g_igViewModel_viewMatrixMetaField[0]) {
        igViewMode_UpdateInverseMatrix((igViewMode *)self);
        igViewMode_UpdateModelVectors((igViewMode *)self);
        return;
    }
    if (field == g_igViewModel_positionMetaField[0] || field == g_igViewModel_directionMetaField[0] ||
        field == g_igViewModel_viewUpVectorMetaField[0]) {
        igViewMode_UpdateViewMatrix((igViewMode *)self);
        return;
    }
    type = event->type;
    if (type == 0) {
        igViewMode_UpdateInverseMatrix((igViewMode *)self);
        igViewMode_UpdateModelVectors((igViewMode *)self);
        self->v124();
    } else if (type == 1) {
        self->v128();
    }
}

void FUN_00465080(void) {

}

void FUN_00465090(void) {

}

void igViewMode_UpdateInverseMatrix(igViewMode *self) {
    int status;

    Matrix44_Invert(&status, self->_inverseMatrix, ((igViewModel *)self->_model)->_viewMatrix);
}

void igViewMode_UpdateModelVectors(igViewMode *self) {
    float v[3];
    ViewModelEvent positionChanged;
    ViewModelEvent directionChanged;
    ViewModelEvent leftChanged;
    igViewModel *model;

    model = (igViewModel *)self->_model;
    Matrix44_GetTranslation(self->_inverseMatrix, v);
    model->_position[0] = v[0];
    model->_position[1] = v[1];
    model->_position[2] = v[2];
    positionChanged.type = VIEW_MODEL_FIELD_CHANGED;
    positionChanged.sender = (int)self;
    positionChanged.field = g_igViewModel_positionMetaField[0];
    igModel_NotifyViews(model, &positionChanged);
    Vec3f_TransformDirection(model->_direction, &g_vec3ZAxis[0], self->_inverseMatrix);
    model->_direction[0] = -model->_direction[0];
    model->_direction[1] = -model->_direction[1];
    model->_direction[2] = -model->_direction[2];
    directionChanged.type = VIEW_MODEL_FIELD_CHANGED;
    directionChanged.sender = (int)self;
    directionChanged.field = g_igViewModel_directionMetaField[0];
    igModel_NotifyViews(model, &directionChanged);
    Vec3f_TransformDirection(model->_viewLeftVector, &g_vec3XAxis[0], self->_inverseMatrix);
    leftChanged.type = VIEW_MODEL_FIELD_CHANGED;
    leftChanged.sender = (int)self;
    leftChanged.field = g_igViewModel_viewLeftVectorMetaField[0];
    igModel_NotifyViews(model, &leftChanged);
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
    Matrix44_MakeLookAt(model->_viewMatrix, model->_position, center, model->_viewUpVector, model);
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
        camera = igGraphPath_GetTail(path);
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

void FUN_00465380(igCameraMode *self) {
    igCameraVirtuals *camera;

    camera = (igCameraVirtuals *)self->_camera;
    if (camera != 0) {
        camera->vY();
    }
}

void FUN_004653c0(igCameraMode *self) {
    int hfovChanged[4];
    int farChanged[4];
    int nearChanged[4];
    float farPlane;
    float nearPlane;
    igCamera *camera;
    igViewModel *model;

    if (self->_camera != 0) {
        ((igCameraVirtuals *)self->_camera)->vX();
        model = (igViewModel *)self->_model;
        camera = (igCamera *)self->_camera;
        farPlane = camera->_farPlane;
        nearPlane = camera->_nearPlane;
        model->_hfov = (float) camera->_horizontalFieldOfView;
        hfovChanged[0] = VIEW_MODEL_FIELD_CHANGED;
        hfovChanged[1] = 0;
        hfovChanged[2] = g_igViewModel_hfovMetaField[0];
        igModel_NotifyViews(model, hfovChanged);
        model->_farPlane = farPlane;
        farChanged[0] = VIEW_MODEL_FIELD_CHANGED;
        farChanged[1] = 0;
        farChanged[2] = g_igViewModel_farPlaneMetaField[0];
        igModel_NotifyViews(model, farChanged);
        nearPlane = (nearPlane == 0.0f) ? farPlane / 1000.0f : nearPlane;
        model->_nearPlane = nearPlane;
        nearChanged[0] = VIEW_MODEL_FIELD_CHANGED;
        nearChanged[1] = 0;
        nearChanged[2] = g_igViewModel_nearPlaneMetaField[0];
        igModel_NotifyViews(model, nearChanged);
    }
}

void FUN_004654d0(igCameraMode *self) {
    float x, y, z;
    int status;
    float translation[4];
    float world[16];
    int changed[4];
    igViewModel *model;
    if (self->_camera != 0) {
        igMatrix44f_SetIdentity(world);
        model = (igViewModel *)self->_model;
        igGraphPath_GetTransform(self->_cameraPath, world, model->_drawTime);
        x = 0; y = 0; z = 0;
        Matrix44_GetEulerAngles(world, &x, &y, &z);
        Matrix44_GetTranslation(world, translation);
        Matrix44_MakeEulerRotation(world, x, y, z);
        Matrix44_SetTranslation(world, translation);
        Matrix44_InvertOrthonormal(&status, model->_viewMatrix, world);
        changed[0] = VIEW_MODEL_FIELD_CHANGED;
        changed[1] = 0;
        changed[2] = g_igViewModel_viewMatrixMetaField[0];
        igModel_NotifyViews(model, changed);
    }
}

void FUN_004655a0(igFlyMode *self, int key, int down) {
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

void FUN_004657b0(igFlyMode *self, int button, int pressed) {
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

void FUN_00465870(igFlyMode *self, float x, float y) {
    self->_mousePos[0] = x;
    self->_mousePos[1] = y;
}

void FUN_00465880(igFlyMode *self, int unused, unsigned short axis, float x, float y)
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

void FUN_00465cc0(igFlyMode *self, float seconds) {
    int changed[3];
    int model;

    model = self->_model;
    igFlyMode_ApplyTranslation(self);
    if (self->_aiming != 0) {
        igFlyMode_ApplyAim(self);
    }
    igFlyMode_ApplyRotation(self, seconds);
    changed[0] = VIEW_MODEL_FIELD_CHANGED;
    changed[1] = 0;
    changed[2] = g_igViewModel_viewMatrixMetaField[0];
    igModel_NotifyViews(model, changed);
}

void FUN_00465d40(igFlyMode *self) {
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

void FUN_00465dc0(igFlyMode *self) {
    if (self->_aiming != 0) {
        self->_aiming = 0;
        igFlyMode_AimingChanged(self);
    }
}

void FUN_00465df0(igRotateMode *self, int key, char down) {
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

void FUN_00465e40(igRotateMode *self, int button, char pressed) {
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

void FUN_004660f0(igRotateMode *state, const float *delta) {
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

void FUN_004661e0(igRotateMode *self, int unused, int stick, float x, float y) {
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

void FUN_00466220(igRotateMode *state) {
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
    state->_translation[0] = g_vec3Zero[0];
    state->_translation[1] = g_vec3Zero[1];
    state->_translation[2] = g_vec3Zero[2];
    dx = model->_selectedCenter[0];
    dy = model->_selectedCenter[1];
    dz = model->_selectedCenter[2];
    dx -= model->_position[0];
    dy -= model->_position[1];
    dz -= model->_position[2];
    state->_distance = sqrtf(dx * dx + dy * dy + dz * dz);
}

int igPickMode_HitProc(int traversal, int data, int hit) {
    if (g_pickingMode[0] != 0) {
        igPickMode_RecordHit(g_pickingMode[0], (IntersectHit *)hit);
    }
    return 0;
}

/* Moves the GUI mouse cursor by the joystick's deflection over `seconds` and tells the GUI model's
 * views that the mouse position changed. */
void Gap__Viewer__igPickMode__MoveCursor(igPickMode *pickMode, float seconds) {
    igGuiSystemModel *model = (igGuiSystemModel *)((igGuiSystem *)pickMode->_guiSystem)->_model;
    float dx = pickMode->_joystickT[0];
    float dy = pickMode->_joystickT[1];
    ViewModelEvent event;
    bool moving = dx != g_vec2Zero[0] || dy != g_vec2Zero[1];

    if (moving) {
        dx *= seconds;
        dy *= seconds;
        model->_mousePosition[0] += dx;
        model->_mousePosition[1] += dy;
        event.type = VIEW_MODEL_FIELD_CHANGED;
        event.sender = 0;
        event.field = g_igGuiSystemModelMousePositionField[0];
        igModel_NotifyViews(model, &event);
    }
}

void FUN_004666c0(igPickMode *self, int unused, int stick, float x, float y) {
    if (!(stick & 0xFFFF)) {
        self->_joystickT[0] = x;
        self->_joystickT[1] = y;
    }
}

void FUN_004666e0(igPickMode *self, int button, int pressed) {
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
            changed.field = g_igViewerParameters_selectedObjectMetaField[0];
            igModel_NotifyViews(self->_parameters, &changed);
        }
    }
}

void FUN_004667a0(igPickMode *self, void *unused, int key, int down) {
    if ((key == 0xE) && (down != 0)) {
        igPickMode_Pick(self);
    }
}

void FUN_004667d0(igPickMode *pickMode) {
    struct { int pad; char b; int w; } unprojected;
    igProbe *created;
    igIntList *faceTypes;
    int top;
    igIntersectTraversal *traversal;
    igObject *previous;
    igObject *cursor;
    Matrix44_Invert(&unprojected.w, pickMode->_inverseProjectionMatrix, ((igViewerParameters *)pickMode->_parameters)->_projectionMatrix);
    unprojected.b = 0;
    igSmartPointer<igProbe> probe(igProbe_Create(0));
    created = probe.get();
    ObjectList_AppendRetained(created->_rays, pickMode->_ray);
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
        igGuiSystem_SetMouseCursor(pickMode->_guiSystem, pickMode->_cursor);
        igGuiSystem_SetMouseCursorVisible(pickMode->_guiSystem, 1);
    }
}

void FUN_004669d0(igPickMode *self) {
    if (self->_guiSystem != 0) {
        igGuiSystem_SetMouseCursor(self->_guiSystem, self->_savedCursor);
        igGuiSystem_SetMouseCursorVisible(self->_guiSystem, self->_savedCursorState);
    }
}

void igPickMode_RecordHit(igPickMode *self, IntersectHit *hit) {
    int nodes = hit->nodes;
    if (hit->distance <= self->_impactLength) {
        self->_hit = 1;
        self->_impactLength = hit->distance;
        setHitPath(self, igSmartPointer<igGraphPath>(createGraphPath()));
        igGraphPath_SetNodes((igGraphPath *)self->_hitPath, nodes);
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
    igRay_SetFromPoints(self->_ray, &g_vec3Zero[0], point);
    igRay_Transform(self->_ray, self->_inverseMatrix);
    self->_impactLength = ((igRay *)self->_ray)->_len;
    self->_hit = 0;
    previous = (igObject *)self->_hitPath;
    if (previous != 0) {
        previous->_refCount = previous->_refCount - 1;
        if (((unsigned long long)(long long)(int)previous->_refCount & 0x7fffffULL) == 0)
            igObject_Destroy(previous);
    }
    self->_hitPath = 0;
    igIntersectTraversal_ResetStacks((igIntersectTraversalVirtuals *)self->_intersectTraversal);
    ((igIntersectTraversalVirtuals *)self->_intersectTraversal)->v25(model->_drawTime);
    g_pickingMode[0] = self;
    ((igIntersectTraversalVirtuals *)self->_intersectTraversal)->v23(((igViewerParameters *)self->_parameters)->_scene);
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
    changed[2] = g_igViewerParameters_selectedObjectMetaField[0];
    igModel_NotifyViews((igViewerParameters *)self->_parameters, changed);
}

/* Returns the metaobject handle of igPickMode, not of igViewManager. */
int igPickMode_GetMeta(void) {
    return g_igPickMode_metaObject[0];
}

int igRotateMode_GetMeta(void) {
    return g_igRotateMode_metaObject[0];
}

int igFlyMode_GetMeta(void) {
    return g_igFlyMode_metaObject[0];
}

int igCameraMode_GetMeta(void) {
    return g_igCameraMode_metaObject[0];
}

int igViewMode_GetMeta(void) {
    return g_igViewMode_metaObject[0];
}

}

igVec4f g_whiteColor(1.0f, 1.0f, 1.0f, 1.0f);
igVec4f g_redColor(1.0f, 0.0f, 0.0f, 1.0f);
