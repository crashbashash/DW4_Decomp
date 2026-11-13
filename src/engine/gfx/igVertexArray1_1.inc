int FUN_0014b680(int arg0) {
    FUN_0014b710();
    return igMetaObject_CreateInstance(*(int *)0x55FA90, arg0);
}

igMetaObject *igVertexArray1_1_GetMetaObject(void)
{
    igMetaObject *g = g_igVertexArray1_1_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_0014b710();
    return g_igVertexArray1_1_metaObject[0];
}

void FUN_0014b710(void)
{
    igMetaObject_RunStaticInit(igVertexArray1_1_Register);
}

void igVertexArray1_1_Register(void) {
    FUN_00149bc0();
    igMetaObject_RegisterClass(
        1, /* abstract */
        g_igVertexArray1_1_metaObject,
        igVertexArray_Register,
        igVertexArray_GetPublishedMetaObject,
        thunk_igVertexArray1_1_GetMetaObject,
        igVertexArray1_1_className,
        0x30, /* instance size */
        0,
        &igVertexArray1_1_InitFields,
        thunk_FUN_0015e010, /* extra callback item */
        g_igVertexArray1_1_callbackList /* callback list */
    );
}

void thunk_igVertexArray1_1_GetMetaObject(void) {
    igVertexArray1_1_GetMetaObject();
}

igMetaObject *FUN_0014b7b0(void) {
    return g_igVertexArray_metaObject[0];
}

void igVertexArray1_1_InitFields(void) {
    void *temp_s1;
    struct F *temp_s2;
    struct F *temp_s2_3;
    struct F *temp_s2_4;
    int temp_s0;
    struct F *temp_s2_2;

    temp_s1 = (void *)(g_igVertexArray1_1_metaObject[0]);
    temp_s0 = igMetaObject_GetFieldCount(temp_s1);
    igMetaObject_CreateFields(temp_s1, &g_igVertexArray1_1_ctorTable[0], 6);
    temp_s2 = (struct F *)(igMetaObject_GetFieldAt(temp_s1, temp_s0));
    temp_s2->f20 = 4;
    temp_s2 = (struct F *)(igMetaObject_GetFieldAt(temp_s1, temp_s0 + 1));
    temp_s2->f60 = FUN_002c4870();
    temp_s2->f53 = 1;
    temp_s2->f64 = 1;
    temp_s2->f65 = 1;
    temp_s2_2 = (struct F *)(igMetaObject_GetFieldAt(temp_s1, temp_s0 + 2));
    temp_s2_2->f60 = igUnsignedCharMetaField_GetDefaultDescriptor();
    temp_s2_2->f53 = 1;
    temp_s2_2->f64 = 1;
    temp_s2_2->f65 = 1;
    *(char *)((char *)(igMetaObject_GetFieldAt(temp_s1, temp_s0 + 3)) + 38) = 0;
    temp_s2_3 = (struct F *)(igMetaObject_GetFieldAt(temp_s1, temp_s0 + 4));
    temp_s2_3->f60 = FUN_002c4870();
    temp_s2_3->f53 = 1;
    temp_s2_3->f64 = 1;
    temp_s2_3->f65 = 1;
    temp_s2_4 = (struct F *)(igMetaObject_GetFieldAt(temp_s1, temp_s0 + 5));
    temp_s2_4->f56 = igMemoryPool_GetOrCreateMetaObject();
    temp_s2_4->f36 = 3;
    temp_s2_4->f38 = 0;
    temp_s2_4->f40 = 1;
    temp_s2_4->f39 = 1;
    igMetaObject_NameFields(temp_s1, &g_igVertexArray1_1_fieldTable[0], &DAT_00488790[0], &DAT_004887b0[0], temp_s0);
    *(int *)((char *)(g_igVertexArray1_1_metaObject[0]) + 60) = (int)(&thunk_igPsx2VertexArray1_1_GetMetaObject);
}

