igMetaObject *FUN_001a24f0(void) {
    if (g_igCompressedTransformSequence1_5Data_metaObject[0] == 0) {
        g_igCompressedTransformSequence1_5Data_metaObject[0] = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData[0]));
    }
    return g_igCompressedTransformSequence1_5Data_metaObject[0];
}

igMetaObject *igCompressedTransformSequence1_5Data_GetMetaObject(void)
{
    igMetaObject *g = g_igCompressedTransformSequence1_5Data_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_001a2640();
    return g_igCompressedTransformSequence1_5Data_metaObject[0];
}

int igCompressedTransformSequence1_5Data_GetVTable(void) {
    struct Obj_1a2590 obj;
    int t;
    igObject_InitHeader(&obj);
    obj.vt = &DAT_0052a6d0[0];
    obj.w2 = 0;
    obj.w3 = 0;
    obj.w4 = 0;
    obj.w5 = 0;
    t = *(int *)((char *)&obj + *(int *)((char *)(g_objectSystem[0]) + 916));
    obj.vt = &DAT_0052a6d0[0];
    FUN_00164870(&obj.w5, -1);
    FUN_00164870(&obj.w4, -1);
    FUN_00164870(&obj.w3, -1);
    FUN_00164870(&obj.w2, -1);
    return t;
}

void FUN_001a2640(void)
{
    igMetaObject_RunStaticInit(igCompressedTransformSequence1_5Data_Register);
}

void igCompressedTransformSequence1_5Data_Register(void) {
    SceneGraphLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        ((char *)g_igCompressedTransformSequence1_5Data_metaObject),
        igObject_Register,
        igObject_GetMetaObject_ParentAccessor,
        thunk_igCompressedTransformSequence1_5Data_GetMetaObject,
        igCompressedTransformSequence1_5Data_className,
        0x30, /* instance size */
        igCompressedTransformSequence1_5Data_GetVTable,
        &igCompressedTransformSequence1_5Data_InitFields,
        0, /* extra callback item */
        g_igCompressedTransformSequence1_5Data_callbackList /* callback list */
    );
}

void thunk_igCompressedTransformSequence1_5Data_GetMetaObject(void) {
    igCompressedTransformSequence1_5Data_GetMetaObject();
}

void igCompressedTransformSequence1_5Data_InitFields(void) {
    int temp_s2;
    void *temp_s1_4;
    void *temp_s1_3;
    void *temp_s1_2;
    void *temp_s1;
    void *temp_s0;

    temp_s0 = (void *)g_igCompressedTransformSequence1_5Data_metaObject[0];
    temp_s2 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &g_igCompressedTransformSequence1_5Data_ctorTable[0], 0xA);
    temp_s1 = (void *)(((void *)igMetaObject_GetFieldAt(temp_s0, temp_s2)));
    ((igObjectRefMetaField *)temp_s1)->_metaObject = igUnsignedShortList_GetOrCreateMetaObject();
    temp_s1_2 = (void *)(((void *)igMetaObject_GetFieldAt(temp_s0, temp_s2 + 1)));
    ((igObjectRefMetaField *)temp_s1_2)->_metaObject = igUnsignedShortList_GetOrCreateMetaObject();
    temp_s1_3 = (void *)(((void *)igMetaObject_GetFieldAt(temp_s0, temp_s2 + 2)));
    ((igObjectRefMetaField *)temp_s1_3)->_metaObject = igUnsignedShortList_GetOrCreateMetaObject();
    temp_s1_4 = (void *)(((void *)igMetaObject_GetFieldAt(temp_s0, temp_s2 + 3)));
    ((igObjectRefMetaField *)temp_s1_4)->_metaObject = igUnsignedShortList_GetOrCreateMetaObject();
    igMetaObject_NameFields(temp_s0, &g_igCompressedTransformSequence1_5Data_fieldTable[0], &DAT_0048c480[0], &DAT_0048c4b0[0], temp_s2);
}

