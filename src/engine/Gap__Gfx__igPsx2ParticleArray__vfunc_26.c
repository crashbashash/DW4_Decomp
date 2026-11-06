/* Decode the particle at `index` into a shared scratch record and return it. The software
 * ParticleArray (Gap::Bec::ParticleArray::vfunc_24) returns a pointer straight into
 * _particleArray; here the data lives packed in the PS2 vertex format, so each component is
 * unpacked by a helper into a 0x90-byte record (the layout that vfunc_27, the setter, takes as a
 * stack buffer). Without hardware support the base implementation is used. */
#include "dw4/reflected.h"
/* Reset the 0x90-byte record to defaults (zero, with 1.0f at +0x74/+0x78). */
int FUN_0015b1e0();
int FUN_001fdca0();
int FUN_001fdd60();
int FUN_001fdeb0();
int FUN_001fe100();
int FUN_001fe260();
int FUN_001fe320();
int *Gap__Bec__ParticleArray__vfunc_24();
/* The shared decoded-particle record at 0x560ac0, one symbol per output the
 * unpack helpers fill, each passed as its own absolute address (the form that
 * matches retail), so they stay separate symbols.  The address in a name gives
 * its offset from the record base. */
extern int g_decodedParticle_00560ac0[4];
extern int g_decodedParticle_00560acc[4];
extern int g_decodedParticle_00560ad8[4];
extern int g_decodedParticle_00560ae4[4];
extern int g_decodedParticle_00560af4[4];
extern int g_decodedParticle_00560b04[4];
extern int g_decodedParticle_00560b14[4];
extern int g_decodedParticle_00560b1c[4];
extern int g_decodedParticle_00560b24[4];
extern int g_decodedParticle_00560b2c[4];
extern int g_decodedParticle_00560b3c[4];
extern int g_decodedParticle_00560b40[4];
extern int g_decodedParticle_00560b44[4];
extern int g_decodedParticle_00560b48[4];
extern int g_decodedParticle_00560b4c[4];
int *Gap__Gfx__igPsx2ParticleArray__vfunc_26(igPsx2ParticleArray *self, unsigned int index) {
    int ps2Format;

    self->_currentEditIndex = index;
    if (self->_hardwareSupport == 0) {
        return Gap__Bec__ParticleArray__vfunc_24();
    }
    if (index >= (unsigned int) self->_arrayIndex) {
        return 0;
    }
    FUN_0015b1e0(&g_decodedParticle_00560ac0[0]);
    ps2Format = self->_ps2ParticleFormat;
    FUN_001fdca0(ps2Format, index, &g_decodedParticle_00560ac0[0], &g_decodedParticle_00560acc[0], &g_decodedParticle_00560ad8[0]);
    FUN_001fdd60(ps2Format, index, &g_decodedParticle_00560ae4[0], &g_decodedParticle_00560af4[0], &g_decodedParticle_00560b04[0]);
    FUN_001fdeb0(ps2Format, index, &g_decodedParticle_00560b14[0], &g_decodedParticle_00560b1c[0], &g_decodedParticle_00560b24[0]);
    FUN_001fe100(ps2Format, index, &g_decodedParticle_00560b44[0], &g_decodedParticle_00560b40[0], &g_decodedParticle_00560b3c[0]);
    FUN_001fe260(ps2Format, index, &g_decodedParticle_00560b4c[0], &g_decodedParticle_00560b48[0]);
    FUN_001fe320(ps2Format, index, &g_decodedParticle_00560b2c[0]);
    return &g_decodedParticle_00560ac0[0];
}
