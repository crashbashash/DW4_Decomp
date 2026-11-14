igMetaObject *FUN_0036e5c0(void) {
    if (g_ParticleTimer_metaObject[0] == 0) {
        g_ParticleTimer_metaObject[0] = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData[0]));
    }
    return g_ParticleTimer_metaObject[0];
}

igMetaObject *FUN_0036e610(void)
{
    igMetaObject *g = g_ParticleTimer_metaObject[0];
    bool t;
    if (!g || (t = g->_validity & 4) == 0)
        FUN_0036e6d0();
    return g_ParticleTimer_metaObject[0];
}

int ParticleTimer_GetVTable(void) {
    struct Obj_36e660 obj;
    int t;

    igObject_InitHeader(&obj);
    obj.w2 = 0;
    obj.w3 = 0;
    obj.w4 = 0;
    obj.w7 = 0;
    obj.w8 = 0;
    obj.w10 = 0;
    obj.vt = &DAT_0053b7f0[0];
    t = *(int *)((char *)&obj + *(int *)((char *)(g_objectSystem[0]) + 916));
    obj.vt = &DAT_0053b7f0[0];
    FUN_0019d120(&obj, 0);
    return t;
}

void FUN_0036e6d0(void)
{
    igMetaObject_RunStaticInit(ParticleTimer_Register);
}

void *ParticleTimer_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_ParticleTimer_metaObject,
        igGeometry_Register,
        igGeometry_GetPublishedMetaObject,
        ParticleTimer_GetMetaObject,
        ParticleTimer_className,
        0x40, /* instance size */
        ParticleTimer_GetVTable,
        ParticleTimer_InitFields,
        FUN_0036e860, /* extra callback item */
        0 /* callback list */
    );
}

void ParticleTimer_GetMetaObject(void)
{
    FUN_0036e610();
}

void ParticleTimer_InitFields(void) {
    int temp_s2;
    void *temp_v0_2;
    void *temp_v0;
    void *temp_s0;

    temp_s0 = (void *)g_ParticleTimer_metaObject[0];
    temp_s2 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &g_ParticleTimer_ctorTable[0], 3);
    igBoolMetaField_SetDefaultValue(igMetaObject_GetFieldAt(temp_s0, temp_s2), 1);
    temp_v0 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 1));
    igLongMetaField_SetDefault(temp_v0, 0);
    *(char *)((char *)(temp_v0) + 38) = 0;
    temp_v0_2 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 2));
    igLongMetaField_SetDefault(temp_v0_2, 0);
    *(char *)((char *)(temp_v0_2) + 38) = 0;
    igMetaObject_NameFields(temp_s0, &g_ParticleTimer_fieldTable[0], &DAT_004c8340[0], &DAT_004c8350[0], temp_s2);
}

void FUN_0036e860(void)
{
    FUN_003a3900();
}

