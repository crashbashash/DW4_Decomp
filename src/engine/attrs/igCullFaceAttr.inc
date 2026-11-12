void FUN_00138690(int arg0) {
    FUN_001387b0();
    igMetaObject_CreateInstance(*(int *)0x55F238, arg0);
}

int FUN_001386d0(void) {
    if (DAT_0055f238[0] == 0) {
        DAT_0055f238[0] = igMetaObject_Create(Memory_GetAllocatorBySelector(DAT_00587040[0]));
    }
    return DAT_0055f238[0];
}

igMetaObject *igCullFaceAttr_GetMetaObject(void)
{
    igMetaObject *g = g_igCullFaceAttr_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_001387b0();
    return g_igCullFaceAttr_metaObject[0];
}

int igCullFaceAttr_GetVTable(void) {
    struct Obj_138770 obj;

    igObject_InitHeader(&obj);
    obj.vt = &DAT_00523d40[0];
    return *(int *)((char *)&obj + *(int *)((char *)(DAT_00586dc8[0]) + 916));
}

void FUN_001387b0(void)
{
    igMetaObject_RunStaticInit(igCullFaceAttr_Register);
}

void igCullFaceAttr_Register(void) {
    AttrsLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igCullFaceAttr_metaObject,
        igVisualAttribute_Register,
        igVisualAttribute_GetPublishedMetaObject,
        thunk_igCullFaceAttr_GetMetaObject,
        igCullFaceAttr_className,
        0x14, /* instance size */
        igCullFaceAttr_GetVTable,
        &igCullFaceAttr_InitFields,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void thunk_igCullFaceAttr_GetMetaObject(void) {
    igCullFaceAttr_GetMetaObject();
}

void igCullFaceAttr_InitFields(void) {
    int temp_s2;
    void *temp_v0;
    void *temp_s0;

    temp_s0 = (void *)DAT_0055f238[0];
    temp_s2 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &DAT_00486768[0], 2);
    temp_v0 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 1));
    FUN_002dc7a0(temp_v0, &DAT_00486788[0]);
    ((igEnumMetaField *)temp_v0)->_getMetaEnumFunction = (int)(&FUN_00149620);
    igMetaObject_NameFields(temp_s0, &DAT_00486770[0], &DAT_00486778[0], &DAT_00486780[0], temp_s2);
}

