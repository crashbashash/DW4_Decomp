igMetaObject *igParticleAttr_GetMeta(void) {
    return g_igParticleAttr_metaObject;
}

void igParticleAttr_Reset(void *arg0) {
    void **temp_a0;

    temp_a0 = (void **)(*(int *)((char *)(arg0) + 16));
    if (temp_a0 != 0) {
        ((DW4VC_152_0 *)(temp_a0))->vX();
    }
}

