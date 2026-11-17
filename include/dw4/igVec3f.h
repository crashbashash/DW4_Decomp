#ifndef DW4_IGVEC3F_H
#define DW4_IGVEC3F_H

/* Alchemy's three-float vector, also used as an RGB colour. Returning one by value runs its copy
 * constructor. */
struct igVec3f {
    float x;
    float y;
    float z;

    igVec3f() {}
    igVec3f(float x_, float y_, float z_) {
        x = x_;
        y = y_;
        z = z_;
    }
    igVec3f(const igVec3f &other) {
        x = other.x;
        y = other.y;
        z = other.z;
    }

    float operator[](int i) const { return (&x)[i]; }
    float &operator[](int i) { return (&x)[i]; }
    void copy(const float *v) {
        (*this)[0] = v[0];
        (*this)[1] = v[1];
        (*this)[2] = v[2];
    }
    void add(const igVec3f &o) {
        (*this)[0] += o[0];
        (*this)[1] += o[1];
        (*this)[2] += o[2];
    }
    void scale(const float &s) {
        (*this)[0] *= s;
        (*this)[1] *= s;
        (*this)[2] *= s;
    }
    /* The factor is taken by reference: a literal factor is read from its own .data constant. */
    igVec3f operator*(const float &s) const { return igVec3f(x * s, y * s, z * s); }
    igVec3f operator+(const igVec3f &o) const { return igVec3f(x + o.x, y + o.y, z + o.z); }
    igVec3f operator-(const igVec3f &o) const { return igVec3f(x - o.x, y - o.y, z - o.z); }
    /* Component-wise scale in place. */
    void scale(const igVec3f &s) {
        x *= s.x;
        y *= s.y;
        z *= s.z;
    }
    float dot(const float *o) const { return o[0] * x + o[1] * y + o[2] * z; }
    float dot(const igVec3f &o) const { return x * o.x + y * o.y + z * o.z; }
    void set(float x_, float y_, float z_) {
        x = x_;
        y = y_;
        z = z_;
    }
};

/* Parses three floats from `text`, by `format` when given; nonzero on success. */
extern "C" int Vec3f_FromString(const char *text, float *vector, const char *format);

#endif
