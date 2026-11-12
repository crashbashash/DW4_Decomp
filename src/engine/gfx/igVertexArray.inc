int FUN_0014b940(int arg0) {
    FUN_0014ba20();
    return igMetaObject_CreateInstance(*(int *)0x55FAC8, arg0);
}

igMetaObject *FUN_0014b980(void) {
    if (g_igVertexArray_metaObject[0] == 0) {
        g_igVertexArray_metaObject[0] = igMetaObject_Create(Memory_GetAllocatorBySelector(g_metadataAllocatorKey[0]));
    }
    return g_igVertexArray_metaObject[0];
}

igMetaObject *igVertexArray_GetMetaObject(void)
{
    igMetaObject *g = g_igVertexArray_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_0014ba20();
    return g_igVertexArray_metaObject[0];
}

void FUN_0014ba20(void)
{
    igMetaObject_RunStaticInit(igVertexArray_Register);
}

void igVertexArray_Register(void) {
    FUN_00149bc0();
    igMetaObject_RegisterClass(
        1, /* abstract */
        g_igVertexArray_metaObject,
        igObject_Register,
        igObject_GetMetaObject_ParentAccessor,
        thunk_igVertexArray_GetMetaObject,
        igVertexArray_className,
        0x18, /* instance size */
        0,
        &igVertexArray_InitFields,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void thunk_igVertexArray_GetMetaObject(void) {
    igVertexArray_GetMetaObject();
}

void igVertexArray_InitFields(void) {
    int temp_s2;
    void *temp_s1;
    void *temp_s0;

    temp_s0 = (void *)(g_igVertexArray_metaObject[0]);
    temp_s2 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &DAT_004887d0[0], 4);
    temp_s1 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2));
    *(int *)((char *)(temp_s1) + 60) = FUN_002bfa60();
    *(char *)((char *)(temp_s1) + 40) = 0;
    igMetaObject_NameFields(temp_s0, &DAT_004887e0[0], &DAT_004887f0[0], &DAT_00488800[0], temp_s2);
    *(int *)((char *)(g_igVertexArray_metaObject[0]) + 60) = (int)(&thunk_igPsx2VertexArray1_1_GetMetaObject);
}

