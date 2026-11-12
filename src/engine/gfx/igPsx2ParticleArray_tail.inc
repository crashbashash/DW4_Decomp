igMetaObject *igPsx2ParticleArray_GetMetaObject(void)
{
    igMetaObject *g = g_igPsx2ParticleArray_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_00153460();
    return g_igPsx2ParticleArray_metaObject[0];
}

int igPsx2ParticleArray_GetVTable(void) {
    union U_1533f0 u;
    int t;
    igObject_InitHeader(u.b);
    *(int *)&u.b[8] = 0;
    *(int *)&u.b[40] = 0;
    *(int *)&u.b[44] = 0;
    *(int *)&u.b[48] = 0;
    *(int *)&u.b[68] = 0;
    u.vt = (int)&DAT_005253e0[0];
    t = *(int *)&u.b[*(int *)((char *)(g_objectSystem[0]) + 916)];
    u.vt = (int)&DAT_005253e0[0];
    FUN_0014caf0((igParticleArray *)u.b, 0);
    return t;
}

void FUN_00153460(void)
{
    igMetaObject_RunStaticInit(igPsx2ParticleArray_Register);
}

void igPsx2ParticleArray_Register(void) {
    FUN_00149bc0();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igPsx2ParticleArray_metaObject,
        igParticleArray_Register,
        igParticleArray_GetPublishedMetaObject,
        thunk_igPsx2ParticleArray_GetMetaObject,
        igPsx2ParticleArray_className,
        0x78, /* instance size */
        igPsx2ParticleArray_GetVTable,
        &igPsx2ParticleArray_InitFields,
        0, /* extra callback item */
        0 /* callback list */
    );
}

igMetaObject *FUN_001534e0(void) {
    return g_igParticleArray_metaObject[0];
}

void igPsx2ParticleArray_InitFields(void) {
    int temp_s1;
    void *temp_s0;

    temp_s0 = (void *)(g_igPsx2ParticleArray_metaObject[0]);
    temp_s1 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &DAT_00489eb0[0], 5);
    *(char *)((char *)(igMetaObject_GetFieldAt(temp_s0, temp_s1)) + 38) = 0;
    *(char *)((char *)(igMetaObject_GetFieldAt(temp_s0, temp_s1 + 1)) + 38) = 0;
    *(char *)((char *)(igMetaObject_GetFieldAt(temp_s0, temp_s1 + 2)) + 38) = 0;
    FUN_002d3890(igMetaObject_GetFieldAt(temp_s0, temp_s1 + 3), 1);
    *(char *)((char *)(igMetaObject_GetFieldAt(temp_s0, temp_s1 + 4)) + 38) = 0;
    igMetaObject_NameFields(temp_s0, &DAT_00489ed0[0], &DAT_00489ef0[0], &DAT_00489f10[0], temp_s1);
    *(int *)((char *)(g_igPsx2ParticleArray_metaObject[0]) + 64) = (int)(&thunk_igParticleArray_GetMetaObject);
}

