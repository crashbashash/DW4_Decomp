int FUN_0036e5c0(void) {
    if (((int *)DAT_0058a0a0)[0] == 0) {
        ((int *)DAT_0058a0a0)[0] = igMetaObject_Create(Memory_GetAllocatorBySelector(DAT_00587040[0]));
    }
    return ((int *)DAT_0058a0a0)[0];
}

igMetaObject *FUN_0036e610(void)
{
    igMetaObject *g = DAT_0058a0a0[0];
    bool t;
    if (!g || (t = g->_validity & 4) == 0)
        FUN_0036e6d0();
    return DAT_0058a0a0[0];
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
    t = *(int *)((char *)&obj + *(int *)((char *)(DAT_00586dc8[0]) + 916));
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

    temp_s0 = (void *)((int *)DAT_0058a0a0)[0];
    temp_s2 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &DAT_004c8320[0], 3);
    FUN_002d3890(igMetaObject_GetFieldAt(temp_s0, temp_s2), 1);
    temp_v0 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 1));
    FUN_002ebc00(temp_v0, 0);
    *(char *)((char *)(temp_v0) + 38) = 0;
    temp_v0_2 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 2));
    FUN_002ebc00(temp_v0_2, 0);
    *(char *)((char *)(temp_v0_2) + 38) = 0;
    igMetaObject_NameFields(temp_s0, &DAT_004c8330[0], &DAT_004c8340[0], &DAT_004c8350[0], temp_s2);
}

void FUN_0036e860(void)
{
    FUN_003a3900();
}

