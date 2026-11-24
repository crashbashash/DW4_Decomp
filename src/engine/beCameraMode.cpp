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
extern "C" {

/* The pick mode whose intersect traversal is running, for its hit callback. */
extern igPickMode *g_pickingMode[4];

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

void igFlyMode_AimingChanged(igFlyMode *self);
void igFlyMode_ApplyTranslation(igFlyMode *self, float seconds);
void igPickMode_RecordHit(igPickMode *self, IntersectHit *hit);

static inline igObject *asCamera(igObject *o) {
    if (o != 0 && ((Gap::Core::igObject *)o)->isOfType(Gap::Sg::igCamera::getClassMeta()) != 0) {
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
static inline void setProbe(igPickMode *pickMode, const igSmartPointer<Gap::Sg::igProbe> &probe) {
    igObject *retained = (igObject *)probe.get();
    igIntersectTraversal *traversal = (igIntersectTraversal *)pickMode->_intersectTraversal;
    igObject *previous;
    ::igObject::ref(retained);
    previous = (igObject *)traversal->_probe;
    ::igObject::release(previous);
    traversal->_probe = (int)retained;
}

static inline void setHitPath(igPickMode *pickMode, const igSmartPointer<igGraphPath> &path) {
    igGraphPath *held = path.get();
    igGraphPath *previous;
    ::igObject::ref(held);
    previous = (igGraphPath *)pickMode->_hitPath;
    ::igObject::release(previous);
    pickMode->_hitPath = (int)held;
}
static inline igGraphPath *createGraphPath() { AdoptReference tag = AdoptReference(); return (igGraphPath *)Gap::Sg::igGraphPath::_instantiateFromPool(0); }

/* Retail's igViewMode::isCompatible is a tail call into isOfType; a void body compiles to it. */
void igViewMode_IsCompatible(igViewMode *self, igObject *model) {
    ((Gap::Core::igObject *)model)->isOfType(Gap::Viewer::igViewModel::getClassMeta());
}

namespace Gap {
namespace Viewer {

void igViewMode::notify(const igNotifyEvent &event) {
    Gap::Core::igMetaField *field = (Gap::Core::igMetaField *)event._field;
    int type;
    if (field == Gap::Viewer::igViewModel::k_viewMatrix) {
        updateInverseMatrix();
        updateModelVectors();
        return;
    }
    if (field == Gap::Viewer::igViewModel::k_position || field == Gap::Viewer::igViewModel::k_direction ||
        field == Gap::Viewer::igViewModel::k_viewUpVector) {
        updateViewMatrix();
        return;
    }
    type = event._eventType;
    if (type == igNotifyEvent::ATTACH) {
        updateInverseMatrix();
        updateModelVectors();
        onAttach();
    } else if (type == igNotifyEvent::DETACH) {
        onDetach();
    }
}

void igViewMode::onDetach() {

}

void igViewMode::onAttach() {

}

void igViewMode::updateInverseMatrix() {

    igMatrix44f_Invert(_inverseMatrix.m, ((::igViewModel *)_model)->_viewMatrix);
}

void igViewMode::updateModelVectors() {
    float v[3];
    ::igViewModel *model;

    model = (::igViewModel *)_model;
    igMatrix44f_GetTranslation(_inverseMatrix.m, v);
    model->_position[0] = v[0];
    model->_position[1] = v[1];
    model->_position[2] = v[2];
    igNotifyEvent positionChanged((Gap::Core::igMetaField *)Gap::Viewer::igViewModel::k_position, (Gap::Gui::igView *)this);
    ((Gap::Gui::igModel *)model)->notifyAllViews(positionChanged);
    Vec3f_TransformDirection(&model->_direction[0], g_vec3ZAxis.vec, _inverseMatrix.m);
    model->_direction[0] = -model->_direction[0];
    model->_direction[1] = -model->_direction[1];
    model->_direction[2] = -model->_direction[2];
    igNotifyEvent directionChanged((Gap::Core::igMetaField *)Gap::Viewer::igViewModel::k_direction, (Gap::Gui::igView *)this);
    ((Gap::Gui::igModel *)model)->notifyAllViews(directionChanged);
    Vec3f_TransformDirection(&model->_viewLeftVector[0], g_vec3XAxis.vec, _inverseMatrix.m);
    igNotifyEvent leftChanged((Gap::Core::igMetaField *)Gap::Viewer::igViewModel::k_viewLeftVector, (Gap::Gui::igView *)this);
    ((Gap::Gui::igModel *)model)->notifyAllViews(leftChanged);
}

void igViewMode::updateViewMatrix() {
    float center[3];
    ::igViewModel *model;

    model = (::igViewModel *)_model;
    center[0] = model->_position[0];
    center[1] = model->_position[1];
    center[2] = model->_position[2];
    center[0] = center[0] + model->_direction[0];
    center[1] += model->_direction[1];
    center[2] += model->_direction[2];
    igMatrix44f_MakeLookAt(model->_viewMatrix, &model->_position[0], center, &model->_viewUpVector[0]);
}

void igCameraMode::setCameraPath(igObject *path) {
    ::igObject *camera;
    if (path != 0) {
        _cameraPath = (Gap::Sg::igGraphPath *)path;
        camera = (::igObject *)((Gap::Sg::igGraphPath *)path)->getTop();
        camera = asCamera(camera);
        _camera = (Gap::Sg::igCamera *)camera;
    }
}

void igCameraMode::onDetach() {
    igCameraDispatchView *camera;

    camera = (igCameraDispatchView *)_camera.get();
    if (camera != 0) {
        camera->Deactivate();
    }
}

void igCameraMode::onAttach() {
    float farPlane;
    float nearPlane;
    ::igCamera *camera;
    ::igViewModel *model;

    if (_camera != 0) {
        ((igCameraDispatchView *)_camera.get())->Activate();
        model = (::igViewModel *)_model;
        camera = (::igCamera *)_camera.get();
        farPlane = camera->_farPlane;
        nearPlane = camera->_nearPlane;
        model->_hfov = (float) camera->_horizontalFieldOfView;
        igNotifyEvent hfovChanged((Gap::Core::igMetaField *)Gap::Viewer::igViewModel::k_hfov);
        ((Gap::Gui::igModel *)model)->notifyAllViews(hfovChanged);
        model->_farPlane = farPlane;
        igNotifyEvent farChanged((Gap::Core::igMetaField *)Gap::Viewer::igViewModel::k_farPlane);
        ((Gap::Gui::igModel *)model)->notifyAllViews(farChanged);
        nearPlane = (nearPlane == 0.0f) ? farPlane / 1000.0f : nearPlane;
        model->_nearPlane = nearPlane;
        igNotifyEvent nearChanged((Gap::Core::igMetaField *)Gap::Viewer::igViewModel::k_nearPlane);
        ((Gap::Gui::igModel *)model)->notifyAllViews(nearChanged);
    }
}

void igCameraMode::update(float seconds) {
    float x, y, z;
    float translation[4];
    float world[16];
    ::igViewModel *model;
    if (_camera != 0) {
        igMatrix44f_SetIdentity(world);
        model = (::igViewModel *)_model;
        ((Gap::Sg::igGraphPath *)_cameraPath.get())->getTransformMatrixInclusive((igMatrix44f *)world, model->_drawTime);
        x = 0; y = 0; z = 0;
        igMatrix44f_GetEulerAngles(world, &x, &y, &z);
        igMatrix44f_GetTranslation(world, translation);
        igMatrix44f_MakeEulerRotation(world, x, y, z);
        igMatrix44f_SetTranslation(world, translation);
        igMatrix44f_InvertOrthonormal(model->_viewMatrix, world);
        igNotifyEvent changed((Gap::Core::igMetaField *)Gap::Viewer::igViewModel::k_viewMatrix);
        ((Gap::Gui::igModel *)model)->notifyAllViews(changed);
    }
}

void igFlyMode::onKeyEvent(int key, int down) {
    float f;
    switch (key) {
    case 0x9C:
        if (down) _speed *= 1.5f;
        break;
    case 0x9D:
        if (down) _speed /= 1.5f;
        break;
    case 0x98:
        if (down) f = 1.0f; else f = -1.0f;
        _moveDirection[2] += f;
        break;
    case 0x92:
        if (down) f = 1.0f; else f = -1.0f;
        _moveDirection[2] -= f;
        break;
    case 0x88:
        if (down) f = 1.0f; else f = -1.0f;
        _moveDirection[1] -= f;
        break;
    case 0x89:
        if (down) f = 1.0f; else f = -1.0f;
        _moveDirection[1] += f;
        break;
    case 0x94:
        if (down) f = 1.0f; else f = -1.0f;
        _moveDirection[0] += f;
        break;
    case 0x96:
        if (down) f = 1.0f; else f = -1.0f;
        _moveDirection[0] -= f;
        break;
    case 0x5A:
        if (down) _aiming = !_aiming;
        igFlyMode_AimingChanged((::igFlyMode *)this);
        break;
    }
}

void igFlyMode::onMouseButton(int button, int pressed) {
    switch (button) {
    case 0:
        _moveDirection[2] += pressed ? 1.0f : -1.0f;
        break;
    case 1:
        _moveDirection[2] -= pressed ? 1.0f : -1.0f;
        break;
    case 2:
        if (pressed) {
            _aiming = !_aiming;
            igFlyMode_AimingChanged((::igFlyMode *)this);
        }
        break;
    }
}

void igFlyMode::onMouseMove(float x, float y) {
    _mousePos[0] = x;
    _mousePos[1] = y;
}

void igFlyMode::onStickEvent(int unused, unsigned short axis, float x, float y)
{
    if (axis == 0) {
        _joystickR[0] = x;
        _joystickR[1] = y;
    } else if (axis == 1) {
        _joystickT[0] = -x;
        _joystickT[1] = 0.0f;
        _joystickT[2] = y;
    }
}
}
}

void igFlyMode_AimingChanged(igFlyMode *self)
{
}

static inline float toRadians(float degrees) { return 0.017453292f * degrees; }
static inline void rotateRef(float *m, const igVec3f *axis, const float &angle) { igMatrix44f_PostRotateAxisAngle(m, axis->vec, angle); }
namespace Gap {
namespace Viewer {

/* Turns the eye by the right stick, at most 120 degrees per second more than the last frame: about the
 * scene's up vector, then about the view's x axis. */
void igFlyMode::applyRotation(float seconds) {
    float maxStep = 120.0f * seconds;
    float head = _joystickR.vec[0];
    float pitch = _joystickR.vec[1];
    head *= 60.0f;
    pitch *= 60.0f;
    float dHead = head - _lastRotation.vec[0];
    float dPitch = pitch - _lastRotation.vec[1];
    float distance = sqrtf(dHead * dHead + dPitch * dPitch);
    if (!(distance <= maxStep)) {
        float limit = maxStep / distance;
        dHead *= limit;
        dPitch *= limit;
        head = dHead + _lastRotation.vec[0];
        pitch = dPitch + _lastRotation.vec[1];
    }
    _lastRotation.vec[0] = head;
    _lastRotation.vec[1] = pitch;
    head *= seconds;
    pitch *= seconds;
    ::igViewModel *model = (::igViewModel *)_model;
    igVec3f up;
    Vec3f_TransformDirection((float *)&up, &model->_sceneUpVector[0], model->_viewMatrix);
    float scale = 1.0f / up.length();
    up[0] *= scale;
    up[1] *= scale;
    up[2] *= scale;
    igMatrix44f_PostRotateAxisAngle(model->_viewMatrix, up.vec, toRadians(head));
    igMatrix44f_PostRotateAxisAngle(model->_viewMatrix, g_vec3XAxis.vec, toRadians(pitch));
}

/* While aiming, turns the eye by the mouse's movement since the last frame. */
void igFlyMode::applyAim() {
    ::igViewModel *model = (::igViewModel *)_model;
    if (_lastAimValid) {
        float pitch = 30.0f * (_mousePos[1] - _lastAim[1]);
        float head = 60.0f * (_mousePos[0] - _lastAim[0]);
        igVec3f up;
        Vec3f_TransformDirection((float *)&up, &model->_sceneUpVector[0], model->_viewMatrix);
        float scale = 1.0f / up.length();
        up[0] *= scale;
        up[1] *= scale;
        up[2] *= scale;
        igMatrix44f_PostRotateAxisAngle(model->_viewMatrix, up.vec, toRadians(head));
        /* matching construct: the (float) cast on the negated pitch orders the pi/180 constant before it. */
        igMatrix44f_PostRotateAxisAngle(model->_viewMatrix, g_vec3XAxis.vec, toRadians((float)(-pitch)));
    }
    _lastAim[0] = _mousePos[0];
    _lastAim[1] = _mousePos[1];
    _lastAimValid = 1;
}

void igFlyMode::update(float seconds) {
    Gap::Gui::igModel *model;

    model = _model;
    igFlyMode_ApplyTranslation((::igFlyMode *)this, seconds);
    if (_aiming != 0) {
        applyAim();
    }
    applyRotation(seconds);
    igNotifyEvent changed((Gap::Core::igMetaField *)Gap::Viewer::igViewModel::k_viewMatrix);
    ((Gap::Gui::igModel *)model)->notifyAllViews(changed);
}

void igFlyMode::onAttach() {
    ::igViewModel *model;
    float dx;
    float dy;
    float dz;
    _aiming = 0;
    _lastAim[0] = 0.0f;
    _lastAim[1] = 0.0f;
    _lastTranslation[0] = 0.0f;
    _lastTranslation[1] = 0.0f;
    _lastTranslation[2] = 0.0f;
    _lastRotation[0] = 0.0f;
    _lastRotation[1] = 0.0f;
    _lastAimValid = 0;
    model = (::igViewModel *)_model;
    dx = model->_selectedCenter[0];
    dy = model->_selectedCenter[1];
    dz = model->_selectedCenter[2];
    dx -= model->_position[0];
    dy -= model->_position[1];
    dz -= model->_position[2];
    _speed = 0.2f * sqrtf(dx * dx + dy * dy + dz * dz);
}

void igFlyMode::onDetach() {
    if (_aiming != 0) {
        _aiming = 0;
        igFlyMode_AimingChanged((::igFlyMode *)this);
    }
}

void igRotateMode::onKeyEvent(int key, int down) {
    if ((_maya != 0) && ((key == 0xC8) || (key == 0xC9))) {
        _active = down;
    }
    if (key != 0xCA) {
        if (key == 0xCB) {
            goto constrain;
        }
    } else {
constrain:
        _constraint = down;
        _constraintAxis = 0;
    }
}

void igRotateMode::onMouseButton(int button, int pressed) {
    switch (button) {
    case 0:
        _leftMouseActive = pressed;
        break;
    case 2:
        _middleMouseActive = pressed;
        break;
    case 1:
        _rightMouseActive = pressed;
        break;
    }
    _constraintAxis = 0;
}
}
}

typedef struct FloatBits { unsigned int mantissa : 23; unsigned int exponent : 8; unsigned int sign : 1; } FloatBits;
static inline float absf(float x) { ((FloatBits *)&x)->sign = 0; return x; }

namespace Gap {
namespace Viewer {

/* While rotating, hands the mouse's movement since the last event to the drag handler; with the
 * constraint key held the drag keeps to the axis it first moved along. */
void igRotateMode::onMouseMove(float x, float y) {
    ::igViewModel *model = (::igViewModel *)_model;
    if (_active) {
        igVec2f delta;
        delta[0] = x;
        delta[1] = y;
        delta[0] -= _lastMousePos[0];
        delta[1] -= _lastMousePos[1];
        if (_constraint) {
            if (_constraintAxis == 0) {
                if (!(absf(delta[0]) <= absf(delta[1]) * model->_ratio)) {
                    _constraintAxis = 1;
                } else {
                    _constraintAxis = 2;
                }
            }
            if (_constraintAxis == 1) {
                delta[1] = 0.0f;
            } else {
                delta[0] = 0.0f;
            }
        }
        if (_maya) {
            mouseMotionNormal((const float *)&delta);
        } else {
            applyDrag((const float *)&delta);
        }
    }
    _lastMousePos[0] = x;
    _lastMousePos[1] = y;
}

/* Applies a mouse drag of `delta` with the default button layout: the left button rotates, the
 * middle one pans and the right one rolls and zooms. */
void igRotateMode::applyDrag(const float *delta) {
    ::igViewModel *model = (::igViewModel *)_model;

    if (_leftMouseActive) {
        const float pi = 3.1415927f;
        _head += pi * delta[0];
        _pitch += pi * delta[1];
    }
    if (_middleMouseActive) {
        setVec3(_translation.vec, delta[0], delta[1] / model->_ratio, 0.0f);
        scaleVec3(_translation.vec, _distance / 2.0f);
    }
    if (_rightMouseActive) {
        float dx = delta[0];
        float dy;
        _roll += dx * 3.1415927f;
        dy = delta[1];
        _zoom *= 1.0f + dy / 2.0f;
    }
}

void igRotateMode::mouseMotionNormal(const float *delta) {
    ::igViewModel *model = (::igViewModel *)_model;

    if (_leftMouseActive) {
        if (_middleMouseActive) {
            float d = delta[0]; _zoom *= 1.0f - d / 2.0f;
        } else {
            const float pi = 3.1415927f;
            _head += pi * delta[0];
            _pitch += pi * delta[1];
        }
    } else if (_middleMouseActive) {
        setVec3(_translation.vec, delta[0], delta[1] / model->_ratio, 0.0f);
        scaleVec3(_translation.vec, _distance / 2.0f);
    }
}

void igRotateMode::onStickEvent(int unused, unsigned short stick, float x, float y) {
    if (stick == 0) {
        _joystickR[0] = x;
        _joystickR[1] = y;
    } else if (stick == 1) {
        _joystickT[0] = x;
        _joystickT[1] = y;
    }
}

void igRotateMode::onAttach() {
    ::igViewModel *model = (::igViewModel *)_model;
    float dx;
    float dy;
    float dz;

    _constraint = 0;
    _constraintAxis = 0;
    _active = !_maya;
    _head = 0.0f;
    _roll = 0.0f;
    _pitch = 0.0f;
    _zoom = 1.0f;
    _translation[0] = g_vec3Zero[0];
    _translation[1] = g_vec3Zero[1];
    _translation[2] = g_vec3Zero[2];
    dx = model->_selectedCenter[0];
    dy = model->_selectedCenter[1];
    dz = model->_selectedCenter[2];
    dx -= model->_position[0];
    dy -= model->_position[1];
    dz -= model->_position[2];
    _distance = sqrtf(dx * dx + dy * dy + dz * dz);
}

/* Applies the stick and the drags gathered since the last frame: turns the view about the selection's
 * centre, zooms towards it and pans, then starts the next frame's gathering from rest. */
void igRotateMode::update(float seconds) {
    ::igViewModel *model = (::igViewModel *)_model;
    float frames = 60.0f * seconds;
    float step = 0.1f * frames;
    _head += step * _joystickR[0];
    _pitch += step * _joystickR[1];
    _roll += step * _joystickT[0];
    _zoom *= 1.0f - 0.1f * (frames * _joystickT[1]);
    if (_active) {
        igVec3f center;
        Vec3f_TransformProjective((float *)&center, &model->_selectedCenter[0], model->_viewMatrix);
        center[0] = -center[0];
        center[1] = -center[1];
        center[2] = -center[2];
        igMatrix44f_TranslateWorld(model->_viewMatrix, center);
        if (_maya) {
            if (_head != 0.0f) {
                igVec3f up;
                Vec3f_TransformDirection((float *)&up, &model->_sceneUpVector[0], model->_viewMatrix);
                float scale = 1.0f / up.length();
                up[0] *= scale;
                up[1] *= scale;
                up[2] *= scale;
                rotateRef(model->_viewMatrix, &up, _head);
            }
        } else if (_head != 0.0f) {
            rotateRef(model->_viewMatrix, &g_vec3YAxis, _head);
        }
        if (_pitch != 0.0f) {
            rotateRef(model->_viewMatrix, &g_vec3XAxis, -_pitch);
        }
        if (_roll != 0.0f) {
            rotateRef(model->_viewMatrix, &g_vec3ZAxis, _roll);
        }
        center.scale(-_zoom);
        center[0] += _translation[0];
        center[1] += _translation[1];
        center[2] += _translation[2];
        _distance = center.length();
        igMatrix44f_TranslateWorld(model->_viewMatrix, center);
        igNotifyEvent changed((Gap::Core::igMetaField *)Gap::Viewer::igViewModel::k_viewMatrix);
        ((Gap::Gui::igModel *)model)->notifyAllViews(changed);
    }
    _head = 0.0f;
    _roll = 0.0f;
    _pitch = 0.0f;
    _zoom = 1.0f;
    _translation[0] = g_vec3Zero[0];
    _translation[1] = g_vec3Zero[1];
    _translation[2] = g_vec3Zero[2];
}
}
}

int igPickMode_HitProc(int traversal, int data, int hit) {
    if (g_pickingMode[0] != 0) {
        igPickMode_RecordHit(g_pickingMode[0], (IntersectHit *)hit);
    }
    return 0;
}

namespace Gap {
namespace Viewer {

/* Moves the GUI mouse cursor by the joystick's deflection over `seconds` and tells the GUI model's
 * views that the mouse position changed. */
void igPickMode::update(float seconds) {
    ::igGuiSystemModel *model = (::igGuiSystemModel *)((igGuiSystem *)_guiSystem.get())->_model.get();
    float dx = _joystickT[0];
    float dy = _joystickT[1];
    bool moving = dx != g_vec2Zero[0] || dy != g_vec2Zero[1];

    if (moving) {
        dx *= seconds;
        dy *= seconds;
        model->_mousePosition[0] += dx;
        model->_mousePosition[1] += dy;
        igNotifyEvent event((Gap::Core::igMetaField *)Gap::Gui::igGuiSystemModel::k_mousePosition);
        ((Gap::Gui::igModel *)model)->notifyAllViews(event);
    }
}

void igPickMode::onStickEvent(int unused, unsigned short stick, float x, float y) {
    if (stick == 0) {
        _joystickT[0] = x;
        _joystickT[1] = y;
    }
}

void igPickMode::onMouseButton(int button, int pressed) {
    int *selected;
    ::igObject *object;
    if (pressed != 0) {
        if (button == 0) {
            pick();
        } else if (button == 1) {
            selected = &((::igViewerParameters *)_parameters.get())->_selectedObject;
            object = (::igObject *)*selected;
            ::igObject::release(object);
            *selected = 0;
            igNotifyEvent changed((Gap::Core::igMetaField *)Gap::Viewer::igViewerParameters::k_selectedObject);
            ((Gap::Gui::igModel *)_parameters.get())->notifyAllViews(changed);
        }
    }
}

void igPickMode::onButtonEvent(void *unused, int key, int down) {
    if ((key == 0xE) && (down != 0)) {
        pick();
    }
}

void igPickMode::onAttach() {
    Gap::Sg::igProbe *created;
    ::igIntList *faceTypes;
    int top;
    ::igIntersectTraversal *traversal;
    ::igObject *previous;
    ::igObject *cursor;
    igMatrix44f_Invert(_inverseProjectionMatrix.m, ((::igViewerParameters *)_parameters.get())->_projectionMatrix);
    igSmartPointer<Gap::Sg::igProbe> probe(Gap::Sg::igProbe::_instantiateFromPool(0), AdoptReference());
    created = probe.get();
    ((Gap::Core::igObjectList *)created->_rays.get())->append((Gap::Core::igObject *)_ray.get());
    faceTypes = (::igIntList *)created->_intersectFaceType.get();
    top = count_of(faceTypes);
    if (top < faceTypes->_capacity) {
        faceTypes->_count = faceTypes->_count + 1;
    } else {
        ((Gap::Core::igDataList *)faceTypes)->resizeAndSetCount(top + 1, 4);
    }
    ((int *)faceTypes->_data)[top] = 2;
    setProbe((::igPickMode *)this, probe);
    ((::igIntersectTraversal *)_intersectTraversal.get())->_mode = 0;
    ((::igIntersectTraversal *)_intersectTraversal.get())->_mode = ((::igIntersectTraversal *)_intersectTraversal.get())->_mode | 4;
    ((::igIntersectTraversal *)_intersectTraversal.get())->_hitProc = (int)&igPickMode_HitProc;
    ((::igIntersectTraversal *)_intersectTraversal.get())->_userTimeState = 1;
    if (_guiSystem != 0) {
        cursor = (::igObject *)((igGuiSystem *)_guiSystem.get())->_mouseCursor.get();
        _savedCursor = (Gap::Gui::igMouseCursor *)cursor;
        _savedCursorState = ((igGuiSystem *)_guiSystem.get())->_mouseCursorVisible;
        ((Gap::Gui::igGuiSystem *)_guiSystem.get())->setMouseCursor((Gap::Gui::igMouseCursor *)_cursor.get());
        ((Gap::Gui::igGuiSystem *)_guiSystem.get())->showCursor(true);
    }
}

void igPickMode::onDetach() {
    if (_guiSystem != 0) {
        ((Gap::Gui::igGuiSystem *)_guiSystem.get())->setMouseCursor((Gap::Gui::igMouseCursor *)_savedCursor.get());
        /* reflected.h spells the igBool _savedCursorState as unsigned char; showCursor takes the kit's igBool (bool). */
        ((Gap::Gui::igGuiSystem *)_guiSystem.get())->showCursor(*(bool *)&_savedCursorState);
    }
}
}
}

void igPickMode_RecordHit(igPickMode *self, IntersectHit *hit) {
    int nodes = hit->nodes;
    if (hit->distance <= self->_impactLength) {
        self->_hit = 1;
        self->_impactLength = hit->distance;
        setHitPath(self, igSmartPointer<igGraphPath>(createGraphPath()));
        ((Gap::Sg::igGraphPath *)self->_hitPath)->configure((Gap::Sg::igNodeList *)nodes);
    }
}

namespace Gap {
namespace Viewer {

void igPickMode::pick() {
    float point[3];
    ::igViewModel *model;
    int *selected;
    ::igObject *previous, *hitPath;
    model = (::igViewModel *)_model;
    ::igGuiSystemModel *gui = (::igGuiSystemModel *)((igGuiSystem *)_guiSystem.get())->_model.get();
    float y = *(float *)&gui->_mousePosition[1];
    point[0] = *(float *)&gui->_mousePosition[0];
    point[1] = y;
    *(int *)&point[2] = 0x3F800000;
    Vec3f_TransformProjective(point, point, _inverseProjectionMatrix.m);
    igRay_SetFromPoints((igRay *)_ray.get(), g_vec3Zero.vec, point);
    igRay_Transform((igRay *)_ray.get(), _inverseMatrix.m);
    _impactLength = ((igRay *)_ray.get())->_len;
    _hit = 0;
    _hitPath.clear();
    ((Gap::Sg::igIntersectTraversal *)((igIntersectTraversalDispatchView *)_intersectTraversal.get()))->reset();
    ((igIntersectTraversalDispatchView *)_intersectTraversal.get())->SetTimeAsLong(model->_drawTime);
    g_pickingMode[0] = (::igPickMode *)this;
    ((igIntersectTraversalDispatchView *)_intersectTraversal.get())->Apply(((::igViewerParameters *)_parameters.get())->_scene);
    g_pickingMode[0] = 0;
    selected = &((::igViewerParameters *)_parameters.get())->_selectedObject;
    hitPath = (::igObject *)_hitPath.get();
    ::igObject::ref(hitPath);
    previous = (::igObject *)*selected;
    ::igObject::release(previous);
    *selected = (int)hitPath;
    igNotifyEvent changed((Gap::Core::igMetaField *)Gap::Viewer::igViewerParameters::k_selectedObject);
    ((Gap::Gui::igModel *)((::igViewerParameters *)_parameters.get()))->notifyAllViews(changed);
}
}
}

/* Returns the metaobject handle of igPickMode, not of igViewManager. */
igMetaObject *igPickMode_GetMeta(void) {
    return Gap::Viewer::igPickMode::getClassMeta();
}

igMetaObject *igRotateMode_GetMeta(void) {
    return Gap::Viewer::igRotateMode::getClassMeta();
}

igMetaObject *igFlyMode_GetMeta(void) {
    return Gap::Viewer::igFlyMode::getClassMeta();
}

int igCameraMode_GetMeta(void) {
    return (int)Gap::Viewer::igCameraMode::getClassMeta();
}

igMetaObject *igViewMode_GetMeta(void) {
    return Gap::Viewer::igViewMode::getClassMeta();
}

}

igVec4f g_whiteColor(1.0f, 1.0f, 1.0f, 1.0f);
igVec4f g_redColor(1.0f, 0.0f, 0.0f, 1.0f);
