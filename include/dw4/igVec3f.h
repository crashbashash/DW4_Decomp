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
};

#endif
