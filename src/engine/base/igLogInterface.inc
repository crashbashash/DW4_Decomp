igMetaObject *FUN_002265e0(void) {
    if (g_igLogInterface_metaObject[0] == 0) {
        g_igLogInterface_metaObject[0] = igMetaObject_Create(Memory_GetAllocatorBySelector(g_metadataAllocatorKey[0]));
    }
    return g_igLogInterface_metaObject[0];
}

igMetaObject *igLogInterface_GetMetaObject(void)
{
    igMetaObject *g = g_igLogInterface_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_002266c0();
    return g_igLogInterface_metaObject[0];
}

int igLogInterface_GetVTable(void) {
    union U_2 u;

    igObject_InitHeader(u.b);
    u.w[0] = (int)(&DAT_0052bfa0[0]);
    return *(int *)&u.b[*(int *)((char *)(g_objectSystem[0]) + 916)];
}

void FUN_002266c0(void)
{
    igMetaObject_RunStaticInit(igLogInterface_Register);
}

void igLogInterface_Register(void) {
    BaseLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igLogInterface_metaObject,
        igInterface_Register,
        igInterface_GetPublishedMetaObject,
        thunk_igLogInterface_GetMetaObject,
        igLogInterface_className,
        0x24, /* instance size */
        igLogInterface_GetVTable,
        &igLogInterface_InitFields,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void thunk_igLogInterface_GetMetaObject(void) {
    igLogInterface_GetMetaObject();
}

void igLogInterface_InitFields(void) {
    int temp_s1;
    void *temp_s0;

    temp_s0 = (void *)g_igLogInterface_metaObject[0];
    temp_s1 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &DAT_00497c60[0], 1);
    igMetaObject_NameFields(temp_s0, &DAT_00497c68[0], &DAT_00497c70[0], &DAT_00497c78[0], temp_s1);
}

