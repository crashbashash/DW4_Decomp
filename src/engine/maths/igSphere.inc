void FUN_00187e10(int arg0) {
    FUN_00187f30();
    igMetaObject_CreateInstance(*(int *)0x560FA0, arg0);
}

igMetaObject *FUN_00187e50(void) {
    if (g_igSphere_metaObject[0] == 0) {
        g_igSphere_metaObject[0] = igMetaObject_Create(Memory_GetAllocatorBySelector(g_metadataAllocatorKey[0]));
    }
    return g_igSphere_metaObject[0];
}

igMetaObject *igSphere_GetMetaObject(void)
{
    igMetaObject *g = g_igSphere_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_00187f30();
    return g_igSphere_metaObject[0];
}

int igSphere_GetVTable(void) {
    union U2 u;
    igObject_InitHeader(u.b);
    u.vt = (int)&DAT_00527fe0[0];
    return *(int *)&u.b[*(int *)((char *)(g_objectSystem[0]) + 916)];
}

void FUN_00187f30(void)
{
    igMetaObject_RunStaticInit(igSphere_Register);
}

void igSphere_Register(void) {
    FUN_00186a40();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igSphere_metaObject,
        igVolume_Register,
        igVolume_GetPublishedMetaObject,
        thunk_igSphere_GetMetaObject,
        igSphere_className,
        0x18, /* instance size */
        igSphere_GetVTable,
        &igSphere_InitFields,
        thunk_FUN_0018d480, /* extra callback item */
        0 /* callback list */
    );
}

void thunk_igSphere_GetMetaObject(void) {
    igSphere_GetMetaObject();
}

igMetaObject *FUN_00187fd0(void) {
    return g_igVolume_metaObject[0];
}

void igSphere_InitFields(void) {
    int temp_s1;
    void *temp_s0;
    int v[3];
    int temp_a0;

    temp_s0 = (void *)g_igSphere_metaObject[0];
    temp_s1 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &g_igSphere_ctorTable[0], 2);
    temp_a0 = igMetaObject_GetFieldAt(temp_s0, temp_s1);
    v[0] = 0;
    v[1] = 0;
    v[2] = 0;
    FUN_0018e470((igVec3fMetaFieldView *)temp_a0, (const float *)v);
    FUN_002e3810(igMetaObject_GetFieldAt(temp_s0, temp_s1 + 1), -1.0f);
    igMetaObject_NameFields(temp_s0, &g_igSphere_fieldTable[0], &DAT_0048adb0[0], &DAT_0048adb8[0], temp_s1);
}

void thunk_FUN_0018d480(void) {
    FUN_0018d480();
}

