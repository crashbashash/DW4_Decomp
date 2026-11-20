#ifndef DW4_IGVEC2F_H
#define DW4_IGVEC2F_H

#include <math.h>

/* Alchemy's two-float vector: an array of two floats with inline accessors (Alchemy 5.0 kit,
 * igMath/igVec2f.h). Returning one by value runs its copy constructor. */
class igVec2f {
public:
    float vec[2];

    igVec2f operator+(const igVec2f &vector) const { return igVec2f(vec[0] + vector[0], vec[1] + vector[1]); }
    igVec2f operator*(const float &t) const { return igVec2f(vec[0] * t, vec[1] * t); }
    igVec2f &operator=(const igVec2f &vector) {
        vec[0] = vector.vec[0];
        vec[1] = vector.vec[1];
        return *this;
    }
    float &operator[](int idx) { return vec[idx]; }
    float operator[](int idx) const { return vec[idx]; }

    igVec2f() {}
    igVec2f(const igVec2f &vector) { set(vector); }
    igVec2f(float x, float y) { set(x, y); }

    void set(const igVec2f &vector) {
        vec[0] = vector.vec[0];
        vec[1] = vector.vec[1];
    }
    void set(float x, float y) {
        vec[0] = x;
        vec[1] = y;
    }
    float length2() const { return vec[0] * vec[0] + vec[1] * vec[1]; }
    float length() const { return sqrtf(length2()); }
};

#endif
