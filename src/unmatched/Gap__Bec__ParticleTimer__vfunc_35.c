/* 0x001d98f0 — Gap__Bec__ParticleTimer__vfunc_35. Banked by tools/retype_struct_member.py (shape: struct5):
 * the m2c draft plus a mechanical source respelling, verified
 * byte-identical to retail by tools/verify.py. */
#include "dw4/reflected.h"
/* igObject header: the reference count at +4 is not a reflected field */
typedef struct RefCountedHeader { char pad4[4]; int references; } RefCountedHeader;
int igObject_Destroy();

void Gap__Bec__ParticleTimer__vfunc_35(ParticleTimer *arg0, RefCountedHeader *arg1) {
    RefCountedHeader *temp_a0;
    if (arg1 != 0) {
        arg1->references = (int)((int) (arg1->references + 1));
    }
    temp_a0 = (void *)(arg0->_attributes);
    if (temp_a0 != 0) {
        temp_a0->references = (int)((int) (temp_a0->references - 1));
        if (((unsigned long long) ((long long) temp_a0->references << 0x29) >> 0x29) == 0) {
            igObject_Destroy(temp_a0);
        }
    }
    arg0->_attributes = (int)(arg1);
}
