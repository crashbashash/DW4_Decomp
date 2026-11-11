igMetaObject *igCollisionGroup_GetMetaObject(void)
{
    igMetaObject *g = g_igCollisionGroup_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_00239c80();
    return g_igCollisionGroup_metaObject[0];
}

int igCollisionGroup_GetVTable(void) {
    union U_239c00 u;
    int temp_s0;
    int *p;

    igObject_InitHeader(u.b);
    *(int *)&u.b[8] = 0;
    *(int *)&u.b[12] = 0;
    *(int *)&u.b[16] = 0;
    *(int *)&u.b[28] = 0;
    u.vt = (int)&DAT_0052d3c0[0];
    p = (int *)&u.b[32];
    *p = 0;
    temp_s0 = *(int *)&u.b[*(int *)((char *)(DAT_00586dc8[0]) + 916)];
    u.vt = (int)&DAT_0052d3c0[0];
    FUN_001a7580(p, -1);
    FUN_00195a90(u.b, 0);
    return temp_s0;
}

void FUN_00239c80(void)
{
    igMetaObject_RunStaticInit(igCollisionGroup_Register);
}

void igCollisionGroup_Register(void) {
    CollisionLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igCollisionGroup_metaObject,
        igGroup_Register,
        igGroup_GetPublishedMetaObject,
        thunk_igCollisionGroup_GetMetaObject,
        igCollisionGroup_className,
        0x60, /* instance size */
        igCollisionGroup_GetVTable,
        &igCollisionGroup_InitFields,
        0, /* extra callback item */
        g_igCollisionGroup_callbackList /* callback list */
    );
}

void thunk_igCollisionGroup_GetMetaObject(void) {
    igCollisionGroup_GetMetaObject();
}

void igCollisionGroup_InitFields(void) {
    int temp_s2;
    void *temp_s1;
    void *temp_s0;

    temp_s0 = (void *)DAT_0056dce0[0];
    temp_s2 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &DAT_004983c0[0], 8);
    temp_s1 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2));
    ((igObjectRefMetaField *)temp_s1)->_metaObject = FUN_00196190();
    igMetaObject_NameFields(temp_s0, &DAT_004983e0[0], &DAT_00498400[0], &DAT_00498420[0], temp_s2);
}

