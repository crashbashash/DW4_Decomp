#ifndef DW4_IGMATH_H
#define DW4_IGMATH_H

/* Alchemy's double-precision vector value types; the float vectors are in their own headers. */
#include "dw4/maths/igVec2f.h"
#include "dw4/maths/igVec4f.h"

struct igVec2d {
    double x;
    double y;

    igVec2d(double x_, double y_) {
        x = x_;
        y = y_;
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
