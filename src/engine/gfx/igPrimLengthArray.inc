void FUN_0014bff0(int arg0) {
    FUN_0014c0d0();
    igMetaObject_CreateInstance(*(int *)0x55FB10, arg0);
}

igMetaObject *FUN_0014c030(void) {
    if (g_igPrimLengthArray_metaObject[0] == 0) {
        g_igPrimLengthArray_metaObject[0] = igMetaObject_Create(Memory_GetAllocatorBySelector(g_metadataAllocatorKey[0]));
    }
    return g_igPrimLengthArray_metaObject[0];
}

igMetaObject *igPrimLengthArray_GetMetaObject(void)
{
    igMetaObject *g = g_igPrimLengthArray_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_0014c0d0();
    return g_igPrimLengthArray_metaObject[0];
}

void FUN_0014c0d0(void)
{
    igMetaObject_RunStaticInit(igPrimLengthArray_Register);
}

void igPrimLengthArray_Register(void) {
    FUN_00149bc0();
    igMetaObject_RegisterClass(
        1, /* abstract */
        g_igPrimLengthArray_metaObject,
        igObject_Register,
        igObject_GetMetaObject_ParentAccessor,
        thunk_igPrimLengthArray_GetMetaObject,
        igPrimLengthArray_className,
        0x14, /* instance size */
        0,
        &igPrimLengthArray_InitFields,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void thunk_igPrimLengthArray_GetMetaObject(void) {
    igPrimLengthArray_GetMetaObject();
}

void igPrimLengthArray_InitFields(void) {
    int temp_s2;
    void *temp_s1;
    void *temp_s0;

    temp_s0 = (void *)(g_igPrimLengthArray_metaObject[0]);
    temp_s2 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &DAT_00488810[0], 3);
    temp_s1 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2));
    ((igMemoryRefMetaField *)temp_s1)->_memType = igUnsignedCharMetaField_GetDefaultDescriptor();
    ((igRefMetaField *)temp_s1)->_destruct = 1;
    ((igMemoryRefMetaField *)temp_s1)->_releaseOnCopy = 1;
    ((igMemoryRefMetaField *)temp_s1)->_releaseOnReset = 1;
    FUN_0030e9b0(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 2), 0x20);
    igMetaObject_NameFields(temp_s0, &DAT_00488820[0], &DAT_00488830[0], &DAT_00488840[0], temp_s2);
    *(int *)((char *)(g_igPrimLengthArray_metaObject[0]) + 60) = (int)(thunk_FUN_0014bde0);
}

int FUN_0014c230(void) {
    if (DAT_0055fb30[0] == 0) {
        DAT_0055fb30[0] = igMetaEnum_Create(&DAT_004dbf60[0], &DAT_00488850[0], &DAT_00488858[0], 2);
    }
    return DAT_0055fb30[0];
}

