void thunk_igPsx2ParticleArray_GetMetaObject(void) {
    igPsx2ParticleArray_GetMetaObject();
}

int FUN_0014d010(void) {
    if (DAT_0055fc98[0] == 0) {
        DAT_0055fc98[0] = igMetaEnum_Create(&IG_GFX_PARTICLE_COORD[0], &DAT_00488b80[0], &DAT_00488b90[0], 4);
    }
    return DAT_0055fc98[0];
}

