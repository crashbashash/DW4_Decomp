#include "dw4/reflected.h"
extern "C" {
extern float DAT_004e1058[4];
extern float sqrtf(float);
}
typedef struct { float x, y, z; } Vec3Float;
extern "C" {
extern int Matrix44_GetTranslation(void *, Vec3Float *);
extern int Matrix44_SetTranslation(void *, void *);
void Gap__Bec__beModelCtrlInfoRideOn3__vfunc_21(beModelCtrlInfoRideOn3 *self, void *m);
}
void Gap__Bec__beModelCtrlInfoRideOn3__vfunc_21(beModelCtrlInfoRideOn3 *self, void *m) {
    Vec3Float t;
    Vec3Float d;
    float e, x, g, k, b, z, len, inv, y, c, a;
    Matrix44_SetTranslation((char *)self->_oldMatrix, DAT_004e1058);
    Matrix44_GetTranslation(m, &t);
    d.x = ((Vec3Float *)self->_worldPosition)->x;
    d.y = ((Vec3Float *)self->_worldPosition)->y;
    d.z = ((Vec3Float *)self->_worldPosition)->z;
    d.x = d.x - t.x;
    d.y = d.y - t.y;
    d.z = d.z - t.z;
    y = ((volatile Vec3Float *)&d)->y; x = d.x; z = ((volatile Vec3Float *)&d)->z; /* matching construct: volatile spill slot reproduces the retail stack traffic */
    len = sqrtf(x * x + y * y + z * z);
    inv = 1.0f / len;
    d.x = d.x * inv;
    d.y = d.y * inv;
    d.z = d.z * inv;
    k = self->_minSpeed;
    a = self->_maxSpeed;
    b = self->_minKyori;
    c = self->_maxKyori;
    e = a - k;
    g = c - b;
    if (len < 0.0f) {
        len = -len;
    }
    if (!(len < c)) {
        k = k;
    } else {
        k = a;
        if (len <= b) {
            k = k;
        } else {
            k = a - ((len - b) / (g / e));
        }
    }
    d.x = d.x * k;
    d.y = d.y * k;
    d.z = d.z * k;
    Matrix44_SetTranslation((char *)self->_modelNode + 32, &d);
}
