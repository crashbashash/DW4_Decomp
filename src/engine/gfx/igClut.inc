int FUN_0014fa50(int arg0) {
    FUN_0014fb70();
    return igMetaObject_CreateInstance(*(int *)0x55FEB8, arg0);
}

igMetaObject *FUN_0014fa90(void) {
    if (g_igClut_metaObject[0] == 0) {
        g_igClut_metaObject[0] = igMetaObject_Create(Memory_GetAllocatorBySelector(g_metadataAllocatorKey[0]));
    }
    return g_igClut_metaObject[0];
}

igMetaObject *igClut_GetMetaObject(void)
{
    igMetaObject *g = g_igClut_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_0014fb70();
    return g_igClut_metaObject[0];
}

int igClut_GetVTable(void) {
    struct Obj_14fb30 obj;

    igObject_InitHeader(&obj);
    obj.vt = &DAT_005269f0[0];
    return *(int *)((char *)&obj + *(int *)((char *)(g_objectSystem[0]) + 916));
}

void FUN_0014fb70(void)
{
    igMetaObject_RunStaticInit(igClut_Register);
}

void igClut_Register(void) {
    FUN_00149bc0();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igClut_metaObject,
        igObject_Register,
        igObject_GetMetaObject_ParentAccessor,
        thunk_igClut_GetMetaObject,
        igClut_className,
        0x20, /* instance size */
        igClut_GetVTable,
        &igClut_InitFields,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void thunk_igClut_GetMetaObject(void) {
    igClut_GetMetaObject();
}

void igClut_InitFields(void) {
    int temp_s2;
    void *temp_v0_2;
    void *temp_v0;
    void *temp_s1;
    void *temp_s0;

    temp_s0 = (void *)(g_igClut_metaObject[0]);
    temp_s2 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &g_igClut_ctorTable[0], 7);
    temp_v0 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2));
    FUN_002dc7a0(temp_v0, &DAT_00489110[0]);
    *(int *)((char *)(temp_v0) + 52) = (int)(&FUN_002d1870);
    FUN_002ea4b0(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 2), -1);
    temp_s1 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 3));
    *(int *)((char *)(temp_s1) + 60) = igUnsignedCharMetaField_GetDefaultDescriptor();
    FUN_002ea4b0(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 4), -1);
    temp_v0_2 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 5));
    FUN_002d3890(temp_v0_2, 1);
    *(char *)((char *)(temp_v0_2) + 38) = 0;
    *(char *)((char *)(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 6)) + 38) = 0;
    igMetaObject_NameFields(temp_s0, &g_igClut_fieldTable[0], &DAT_004890d0[0], &DAT_004890f0[0], temp_s2);
    *(int *)((char *)(g_igClut_metaObject[0]) + 60) = (int)(&thunk_igPsx2Clut_GetMetaObject);
}

