#include "dw4/reflected.h"

typedef enum Intersection {
    kDisjoint,
    kIntersecting
} Intersection;

int FUN_0018ffa0(void *a, void *b);

Intersection FUN_0018d9b0(igSphere *sphere, void *other)
{
    if (sphere->_radius < 0.0f)
        return kDisjoint;
    return FUN_0018ffa0(other, sphere) ? kIntersecting : kDisjoint;
}
