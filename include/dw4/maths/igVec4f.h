#ifndef DW4_IGVEC4F_H
#define DW4_IGVEC4F_H

#ifdef __cplusplus
#include "dw4/maths/igVec3f.h"

/* Alchemy's four-float vector, also used as an RGBA colour: an array of four floats with inline
 * accessors (Alchemy 5.0 kit, igMath/igVec4f.h). Returning one by value runs its copy constructor. */
class igVec4f {
public:
    float vec[4];

    igVec4f operator+(const igVec4f &vector) const {
        return igVec4f(vec[0] + vector.vec[0], vec[1] + vector.vec[1], vec[2] + vector.vec[2], vec[3] + vector.vec[3]);
    }
    igVec4f operator*(const float &t) const { return igVec4f(vec[0] * t, vec[1] * t, vec[2] * t, vec[3] * t); }
    igVec4f &operator=(const igVec4f &vector) {
        vec[0] = vector.vec[0];
        vec[1] = vector.vec[1];
        vec[2] = vector.vec[2];
        vec[3] = vector.vec[3];
        return *this;
    }
    bool operator==(const igVec4f &vector) const {
        return (vec[0] == vector.vec[0]) && (vec[1] == vector.vec[1]) && (vec[2] == vector.vec[2]) &&
               (vec[3] == vector.vec[3]);
    }
    float &operator[](int idx) { return vec[idx]; }
    float operator[](int idx) const { return vec[idx]; }

    igVec4f() {}
    igVec4f(const igVec4f &vector) { set(vector); }
    igVec4f(float x, float y, float z, float w) { set(x, y, z, w); }

    void set(const igVec4f &vector) {
        vec[0] = vector.vec[0];
        vec[1] = vector.vec[1];
        vec[2] = vector.vec[2];
        vec[3] = vector.vec[3];
    }
    /* The first three elements; the fourth is left as it is. */
    void set(const igVec3f &vector) {
        vec[0] = vector.vec[0];
        vec[1] = vector.vec[1];
        vec[2] = vector.vec[2];
    }
    void set(float x, float y, float z, float w) {
        vec[0] = x;
        vec[1] = y;
        vec[2] = z;
        vec[3] = w;
    }
    void set(const float *vector) {
        vec[0] = vector[0];
        vec[1] = vector[1];
        vec[2] = vector[2];
        vec[3] = vector[3];
    }
    void makeMin(const igVec4f &vector) {
        if (vec[0] > vector.vec[0]) vec[0] = vector.vec[0];
        if (vec[1] > vector.vec[1]) vec[1] = vector.vec[1];
        if (vec[2] > vector.vec[2]) vec[2] = vector.vec[2];
        if (vec[3] > vector.vec[3]) vec[3] = vector.vec[3];
    }
    void makeMax(const igVec4f &vector) {
        if (vec[0] < vector.vec[0]) vec[0] = vector.vec[0];
        if (vec[1] < vector.vec[1]) vec[1] = vector.vec[1];
        if (vec[2] < vector.vec[2]) vec[2] = vector.vec[2];
        if (vec[3] < vector.vec[3]) vec[3] = vector.vec[3];
    }
};
#endif

#ifdef __cplusplus
extern "C" {
#endif
int igVec4f_PackColor(const float *color, unsigned int format);
void Color4f_Unpack(struct igVec4f *out, unsigned int format, unsigned int packed);
#ifdef __cplusplus
}
#endif

#endif
