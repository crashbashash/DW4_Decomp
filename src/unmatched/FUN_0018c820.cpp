#include "dw4/reflected.h"

struct igVec3f {
    float x;
    float y;
    float z;
    float dot(const float *o) const { return o[0] * x + o[1] * y + o[2] * z; }
};

extern "C" {
float sqrtf(float);
void FUN_00192f50(float *dst, const float *src, const void *matrix);
void FUN_00192fc0(igVec3f *dst, const igVec3f *src, const void *matrix);
int FUN_00192e50(const float *normal);
void FUN_0018c820(igPlane *plane, const void *matrix);
}

static inline float lengthOf(const float *v) {
    return sqrtf(v[0] * v[0] + v[1] * v[1] + v[2] * v[2]);
}

void FUN_0018c820(igPlane *plane, const void *matrix) {
    igVec3f point;
    float d;
    float scale;

    d = plane->_offset;
    point.x = d * plane->_norm[0];
    point.y = d * plane->_norm[1];
    point.z = d * plane->_norm[2];
    FUN_00192f50(plane->_norm, plane->_norm, matrix);
    FUN_00192fc0(&point, &point, matrix);
    scale = 1.0f / lengthOf(plane->_norm);
    plane->_norm[0] = plane->_norm[0] * scale;
    plane->_norm[1] = plane->_norm[1] * scale;
    plane->_norm[2] = plane->_norm[2] * scale;
    plane->_offset = point.dot(plane->_norm);
    plane->_octant = FUN_00192e50(plane->_norm);
}
