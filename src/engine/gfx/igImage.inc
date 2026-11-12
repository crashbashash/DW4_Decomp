int FUN_0014df70(int arg0) {
    FUN_0014e050();
    return igMetaObject_CreateInstance(*(int *)0x55FD80, arg0);
}

igMetaObject *FUN_0014dfb0(void) {
    if (g_igImage_metaObject[0] == 0) {
        g_igImage_metaObject[0] = igMetaObject_Create(Memory_GetAllocatorBySelector(g_metadataAllocatorKey[0]));
    }
    return g_igImage_metaObject[0];
}

igMetaObject *igImage_GetMetaObject(void)
{
    igMetaObject *g = g_igImage_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_0014e050();
    return g_igImage_metaObject[0];
}

void FUN_0014e050(void)
{
    igMetaObject_RunStaticInit(igImage_Register);
}

void igImage_Register(void) {
    FUN_00149bc0();
    igMetaObject_RegisterClass(
        1, /* abstract */
        g_igImage_metaObject,
        igObject_Register,
        igObject_GetMetaObject_ParentAccessor,
        thunk_igImage_GetMetaObject,
        igImage_className,
        0x5C, /* instance size */
        0,
        &igImage_InitFields,
        thunk_FUN_00156300, /* extra callback item */
        g_igImage_callbackList /* callback list */
    );
}

void thunk_igImage_GetMetaObject(void) {
    igImage_GetMetaObject();
}

void igImage_InitFields(void) {
    void *temp_s1;
    int temp_s2;
    void *temp_s1_2;
    void *temp_s1_3;
    void *temp_v0;
    void *temp_s0;

    temp_s0 = (void *)(g_igImage_metaObject[0]);
    temp_s2 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &DAT_00488dd0[0], 0x15);
    FUN_0030e9b0(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 3), 1);
    FUN_0030e9b0(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 4), 0x64);
    temp_v0 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 9));
    FUN_002dc7a0(temp_v0, &DAT_00488f48[0]);
    *(int *)((char *)(temp_v0) + 52) = (int)(&FUN_001499e0);
    FUN_002ea4b0(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 0xA), -2);
    temp_s1 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 0xB));
    *(int *)((char *)(temp_s1) + 60) = igUnsignedCharMetaField_GetDefaultDescriptor();
    igMemoryRefMetaField_SetPoolName(temp_s1, &DAT_004dc9a8[0]);
    temp_s1_2 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 0xC));
    *(int *)((char *)(temp_s1_2) + 60) = FUN_002cc2c0();
    FUN_002d3890(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 0xD), 1);
    temp_s1_3 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 0xF));
    *(int *)((char *)(temp_s1_3) + 56) = (int)FUN_0014fa90();
    FUN_002ea4b0(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 0x11), -1);
    igMetaObject_NameFields(temp_s0, &DAT_00488e30[0], &DAT_00488e90[0], &DAT_00488ef0[0], temp_s2);
    *(int *)((char *)(g_igImage_metaObject[0]) + 60) = (int)thunk_igPsx2Image_GetMetaObject;
}

