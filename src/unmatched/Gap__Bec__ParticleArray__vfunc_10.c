/* 0x0015c850 — Gap__Bec__ParticleArray__vfunc_10. Retyped m2c draft, verified byte-identical to retail by tools/verify.py (wave5 shard 8). */
#include "dw4/reflected.h"
/* igPointSpriteInterface-like object referenced by _pointSpriteInterface; class not identified from reflection */
/* matching construct: f24 is volatile so the compare and the release each reload it, as retail does */
typedef struct PointSpriteInterfaceView { char pad[24]; igObject * volatile f24; } PointSpriteInterfaceView;
int Memory_FreeBuffer();
int igObject_Destroy();

void Gap__Bec__ParticleArray__vfunc_10(ParticleArray *arg0) {
    void *temp_a0;
    igObject *temp_a0_2;
    PointSpriteInterfaceView *temp_s0;

    temp_a0 = (void *)arg0->_particleArray;
    if (temp_a0 != 0) {
        Memory_FreeBuffer(temp_a0);
    }
    arg0->_particleArray = 0;
    temp_s0 = (PointSpriteInterfaceView *)arg0->_pointSpriteInterface;
    if ((temp_s0 != 0) && (temp_s0->f24 == (igObject *)arg0->_internalVertexArray)) {
        temp_a0_2 = temp_s0->f24;
        if (temp_a0_2 != 0) {
            temp_a0_2->_refCount = temp_a0_2->_refCount - 1;
            if ((temp_a0_2->_refCount & 0x7FFFFF) == 0) {
                igObject_Destroy(temp_a0_2);
            }
        }
        temp_s0->f24 = 0;
    }
}
