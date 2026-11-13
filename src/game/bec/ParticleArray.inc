void *FUN_0036e2c0(void) {
    igMetaObject *g = g_ParticleArray_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false) {
        FUN_0036e3b0();
    }
    return g_ParticleArray_metaObject[0];
}

int ParticleArray_GetVTable(void) {
    struct Obj_36e310 obj;
    int t;

    igObject_InitHeader(&obj);
    obj.w2 = 0;
    obj.w10 = 0;
    obj.w11 = 0;
    obj.w12 = 0;
    obj.w17 = 0;
    obj.vt = &DAT_0053b740[0];
    obj.w28 = 0;
    obj.w29 = 0;
    t = *(int *)((char *)&obj + *(int *)((char *)(g_objectSystem[0]) + 916));
    obj.vt = &DAT_0053b740[0];
    FUN_001338d0(&obj.w29, -1);
    FUN_001338d0(&obj.w28, -1);
    FUN_0014caf0(&obj, 0);
    return t;
}

void FUN_0036e3b0(void)
{
    igMetaObject_RunStaticInit(ParticleArray_Register);
}

void *ParticleArray_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_ParticleArray_metaObject,
        igParticleArray_Register,
        igParticleArray_GetPublishedMetaObject,
        ParticleArray_GetMetaObject,
        ParticleArray_className,
        0x7c, /* instance size */
        ParticleArray_GetVTable,
        ParticleArray_InitFields,
        0, /* extra callback item */
        g_ParticleArray_callbackList /* callback list */
    );
}

void ParticleArray_GetMetaObject(void)
{
    FUN_0036e2c0();
}

void ParticleArray_InitFields(void) {
    int temp_s2;
    void *temp_s1_2;
    void *temp_s1;
    void *temp_s0;

    temp_s0 = (void *)g_ParticleArray_metaObject[0];
    temp_s2 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &g_ParticleArray_ctorTable[0], 0xB);
    FUN_002e3810(igMetaObject_GetFieldAt(temp_s0, temp_s2), 1.0f);
    FUN_002e3810(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 1), 1.0f);
    FUN_002d3890(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 2), 1);
    FUN_002e3810(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 4), 0.0f);
    temp_s1 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 6));
    ((igObjectRefMetaField *)temp_s1)->_metaObject = FUN_0014b980();
    ((igMetaField *)temp_s1)->_persistent = 0;
    temp_s1_2 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 7));
    ((igObjectRefMetaField *)temp_s1_2)->_metaObject = FUN_0014b980();
    ((igMetaField *)temp_s1_2)->_persistent = 0;
    ((igMetaField *)igMetaObject_GetFieldAt(temp_s0, temp_s2 + 8))->_persistent = 0;
    ((igMetaField *)igMetaObject_GetFieldAt(temp_s0, temp_s2 + 9))->_persistent = 0;
    ((igMetaField *)igMetaObject_GetFieldAt(temp_s0, temp_s2 + 0xA))->_persistent = 0;
    igMetaObject_NameFields(temp_s0, &g_ParticleArray_fieldTable[0], &DAT_004c82c0[0], &DAT_004c82f0[0], temp_s2);
}

