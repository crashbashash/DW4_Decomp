#ifndef DW4_IGMATH_H
#define DW4_IGMATH_H

/* Alchemy's two-component, double-precision and four-float vector value types (the three-float
 * igVec3f is in dw4/igVec3f.h). */

struct igVec2f {
    float x;
    float y;

    igVec2f() {}
    igVec2f(float x_, float y_) {
        x = x_;
        y = y_;
    }
    void set(float x_, float y_) {
        x = x_;
        y = y_;
    }
};

struct igVec2d {
    double x;
    double y;

    igVec2d(double x_, double y_) {
        x = x_;
        y = y_;
    }
};

struct igVec4f {
    float x;
    float y;
    float z;
    float w;

    igVec4f() {}
    igVec4f(float x_, float y_, float z_, float w_) {
        x = x_;
        y = y_;
        z = z_;
        w = w_;
    }
    void set(float x_, float y_, float z_, float w_) {
        x = x_;
        y = y_;
        z = z_;
        w = w_;
    }
};

struct igVec3d {
    double x;
    double y;
    double z;

    igVec3d(double x_, double y_, double z_) {
        x = x_;
        y = y_;
        z = z_;
    }
};

struct igVec4d {
    double x;
    double y;
    double z;
    double w;

    igVec4d() {}
    igVec4d(double x_, double y_, double z_, double w_) {
        x = x_;
        y = y_;
        z = z_;
        w = w_;
    }
};

#endif
