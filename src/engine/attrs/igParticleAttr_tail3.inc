igMetaObject *igParticleAttr_GetMeta(void) {
    return g_igParticleAttr_metaObject;
}

void igParticleAttr_Reset(igParticleAttr *self) {
    void **temp_a0;

    temp_a0 = (void **)(self->_particleArray);
    if (temp_a0 != 0) {
        ((DW4VC_152_0 *)(temp_a0))->vX();
    }
}

