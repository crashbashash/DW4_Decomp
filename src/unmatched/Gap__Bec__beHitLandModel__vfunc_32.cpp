#include "dw4/reflected.h"
typedef struct { char vtable[4]; int refs; } RefCountedObject;
extern "C" {
int FUN_00190ed0(void *, float, float, float);
int igObject_Destroy(RefCountedObject *);
void Gap__Bec__beHitLandModel__vfunc_32(beHitLandModel *arg0);
}
void Gap__Bec__beHitLandModel__vfunc_32(beHitLandModel *arg0) {
    RefCountedObject *t;
    t = (RefCountedObject *)arg0->_order;
    if (t != 0) {
        /* matching construct: redundant inner null test is present in the retail code */
        if (t != 0) {
            t->refs = t->refs - 1;
            if (((unsigned long long)((long long)t->refs << 0x29) >> 0x29) == 0) {
                igObject_Destroy(t);
            }
        }
        arg0->_order = 0;
    }
    t = (RefCountedObject *)arg0->_hitTraversal;
    if (t != 0) {
        /* matching construct: redundant inner null test is present in the retail code */
        if (t != 0) {
            t->refs = t->refs - 1;
            if (((unsigned long long)((long long)t->refs << 0x29) >> 0x29) == 0) {
                igObject_Destroy(t);
            }
        }
        arg0->_hitTraversal = 0;
    }
    t = (RefCountedObject *)arg0->_probe;
    if (t != 0) {
        /* matching construct: redundant inner null test is present in the retail code */
        if (t != 0) {
            t->refs = t->refs - 1;
            if (((unsigned long long)((long long)t->refs << 0x29) >> 0x29) == 0) {
                igObject_Destroy(t);
            }
        }
        arg0->_probe = 0;
    }
    arg0->_isHitWall = 1;
    FUN_00190ed0((char *)arg0 + 0x30, 0.0f, 1.5707964f, 0.0f);
}
