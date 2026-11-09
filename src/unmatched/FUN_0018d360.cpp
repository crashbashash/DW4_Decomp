#include "dw4/reflected.h"

struct igVec3f {
    float x;
    float y;
    float z;
    void subtractInto(float *out, const float *o) const { out[0] = x - o[0]; out[1] = y - o[1]; out[2] = z - o[2]; }
};

extern "C" {
float sqrtf(float);
void FUN_00192fc0(void *dst, const void *src, const void *matrix);
void FUN_0018d360(igRay *ray, const void *matrix);
}

static inline float lengthOf(const float *v) {
    return sqrtf(v[0] * v[0] + v[1] * v[1] + v[2] * v[2]);
}

void FUN_0018d360(igRay *ray, const void *matrix) {
    igVec3f end;
    float len;
    float scale;

    len = ray->_len;
    end.x = ray->_pos[0] + len * ray->_dir[0];
    end.y = ray->_pos[1] + len * ray->_dir[1];
    end.z = ray->_pos[2] + len * ray->_dir[2];
    FUN_00192fc0(ray->_pos, ray->_pos, matrix);
    FUN_00192fc0(&end, &end, matrix);
    end.subtractInto(ray->_dir, ray->_pos);
    len = lengthOf(ray->_dir);
    scale = 1.0f / len;
    ray->_dir[0] = ray->_dir[0] * scale;
    ray->_dir[1] = ray->_dir[1] * scale;
    ray->_dir[2] = ray->_dir[2] * scale;
    ray->_len = len;
}
