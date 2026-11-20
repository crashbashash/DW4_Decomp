#ifndef DW4_IGVEC3F_H
#define DW4_IGVEC3F_H

#include <math.h>

/* Alchemy's three-float vector, also used as an RGB colour: an array of three floats with inline
 * accessors (Alchemy 5.0 kit, igMath/igVec3f.h). Returning one by value runs its copy constructor. */
class igVec3f {
public:
    float vec[3];

    /* The factor is taken by reference: a literal factor is read from its own .data constant. */
    igVec3f operator*(const float &t) const { return igVec3f(vec[0] * t, vec[1] * t, vec[2] * t); }
    igVec3f operator+(const igVec3f &vector) const {
        return igVec3f(vec[0] + vector.vec[0], vec[1] + vector.vec[1], vec[2] + vector.vec[2]);
    }
    igVec3f operator-(const igVec3f &vector) const {
        return igVec3f(vec[0] - vector.vec[0], vec[1] - vector.vec[1], vec[2] - vector.vec[2]);
    }
    igVec3f &operator+=(const igVec3f &vector) {
        vec[0] += vector.vec[0];
        vec[1] += vector.vec[1];
        vec[2] += vector.vec[2];
        return *this;
    }
    igVec3f &operator-=(const igVec3f &vector) {
        vec[0] -= vector.vec[0];
        vec[1] -= vector.vec[1];
        vec[2] -= vector.vec[2];
        return *this;
    }
    igVec3f &operator*=(const float &t) {
        vec[0] *= t;
        vec[1] *= t;
        vec[2] *= t;
        return *this;
    }
    igVec3f &operator=(const igVec3f &vector) {
        vec[0] = vector.vec[0];
        vec[1] = vector.vec[1];
        vec[2] = vector.vec[2];
        return *this;
    }
    bool operator!=(const igVec3f &vector) const {
        return (vec[0] != vector.vec[0]) || (vec[1] != vector.vec[1]) || (vec[2] != vector.vec[2]);
    }
    float &operator[](int idx) { return vec[idx]; }
    float operator[](int idx) const { return vec[idx]; }

    igVec3f() {}
    igVec3f(const igVec3f &vector) { set(vector); }
    igVec3f(float x, float y, float z) { set(x, y, z); }

    void set(const igVec3f &vector) {
        vec[0] = vector.vec[0];
        vec[1] = vector.vec[1];
        vec[2] = vector.vec[2];
    }
    void set(float x, float y, float z) {
        vec[0] = x;
        vec[1] = y;
        vec[2] = z;
    }
    void set(const float *vector) {
        vec[0] = vector[0];
        vec[1] = vector[1];
        vec[2] = vector[2];
    }
    void add(const igVec3f &vector) {
        vec[0] += vector.vec[0];
        vec[1] += vector.vec[1];
        vec[2] += vector.vec[2];
    }
    void subtract(const igVec3f &vector1, const igVec3f &vector2) {
        vec[0] = vector1.vec[0] - vector2.vec[0];
        vec[1] = vector1.vec[1] - vector2.vec[1];
        vec[2] = vector1.vec[2] - vector2.vec[2];
    }
    /* Component-wise product in place. */
    void multiply(const igVec3f &vector) {
        vec[0] *= vector.vec[0];
        vec[1] *= vector.vec[1];
        vec[2] *= vector.vec[2];
    }
    float dot(const igVec3f &vector) const {
        return vec[0] * vector.vec[0] + vec[1] * vector.vec[1] + vec[2] * vector.vec[2];
    }
    void scale(const float scalar) {
        vec[0] *= scalar;
        vec[1] *= scalar;
        vec[2] *= scalar;
    }
    void addScaled(const float scalar, const igVec3f &vector) {
        vec[0] += scalar * vector.vec[0];
        vec[1] += scalar * vector.vec[1];
        vec[2] += scalar * vector.vec[2];
    }
    float length2() const { return vec[0] * vec[0] + vec[1] * vec[1] + vec[2] * vec[2]; }
    float length() const { return sqrtf(length2()); }
    float normalize() {
        const float t = length();
        scale(1.0f / t);
        return t;
    }
};

extern "C" {
/* Parses three floats from `text`, by `format` when given; nonzero on success. */
int igConvertString_Vec3f(const char *text, float *vector, const char *format);
void Vec3_Lerp(float *out, float t, const float *from, const float *to);
/* vector = vector x other. */
void Vec3f_CrossInPlace(float *vector, const float *other);
/* out = a x b. */
void FUN_00192dd0(float *out, const float *a, const float *b);
/* out = v through the matrix's rotation part (no translation). */
void Vec3f_TransformDirection(float *out, const float *v, const float *matrix);
/* out = v through the whole matrix, divided by the resulting w. */
void Vec3f_TransformProjective(float *out, const float *v, const float *matrix);
}

#endif
