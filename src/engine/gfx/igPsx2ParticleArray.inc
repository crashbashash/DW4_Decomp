igMetaObject *g_igPsx2ParticleArray_metaObject;
igMetaField *g_igPsx2ParticleArray_hardwareSupportMetaField;
igMetaField *g_igPsx2ParticleArray_currentEditIndexMetaField;
igMetaField *g_igPsx2ParticleArray_ps2ParticleFormatMetaField;
igMetaField *g_igPsx2ParticleArray_bSynchronizeMetaField;
igMetaField *g_igPsx2ParticleArray_lSequenceMetaField;

void igPsx2ParticleArray_GetMetaObjectFunction(void) {
    igPsx2ParticleArray_GetMetaObject();
}

static const char *g_igPsx2ParticleArray_particleCoordNames[] = {
    "IG_GFX_PARTICLE_COORD_NONE", "IG_GFX_PARTICLE_COORD_CONSTANT", "IG_GFX_PARTICLE_COORD_LINEAR", "IG_GFX_PARTICLE_COORD_QUADRATIC",
};
static int g_igPsx2ParticleArray_particleCoordValues[] = {
    0, 1, 2, 3,
};
igMetaEnum *g_igPsx2ParticleArray_particleCoordMetaEnum;

int IG_GFX_PARTICLE_COORD_GetMetaEnum(void) {
    if (g_igPsx2ParticleArray_particleCoordMetaEnum == 0) {
        g_igPsx2ParticleArray_particleCoordMetaEnum = (igMetaEnum *)Gap::Core::igMetaEnum::createMetaEnum("IG_GFX_PARTICLE_COORD", g_igPsx2ParticleArray_particleCoordNames, g_igPsx2ParticleArray_particleCoordValues, 4);
    }
    return (int)g_igPsx2ParticleArray_particleCoordMetaEnum;
}

