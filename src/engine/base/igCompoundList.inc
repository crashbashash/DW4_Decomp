igMetaObject *igCompoundList_GetMetaObject(void)
{
    igMetaObject *g = g_igCompoundList_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_00225900();
    return g_igCompoundList_metaObject[0];
}

int igCompoundList_GetVTable(void) {
    struct Obj obj;

    igObject_InitHeader(&obj);
    obj.vt = &DAT_0052c750[0];
    return *(int *)((char *)&obj + *(int *)((char *)(g_objectSystem[0]) + 916));
}

void FUN_00225900(void)
{
    igMetaObject_RunStaticInit(igCompoundList_Register);
}

void igCompoundList_Register(void) {
    BaseLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igCompoundList_metaObject,
        igObject_Register,
        igObject_GetMetaObject_ParentAccessor,
        thunk_igCompoundList_GetMetaObject,
        igCompoundList_className,
        0x14, /* instance size */
        igCompoundList_GetVTable,
        &igCompoundList_InitFields,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void thunk_igCompoundList_GetMetaObject(void) {
    igCompoundList_GetMetaObject();
}

void igCompoundList_InitFields(void) {
    int temp_s2;
    void *temp_s1;
    void *temp_s0;

    temp_s0 = (void *)g_igCompoundList_metaObject[0];
    temp_s2 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &g_igCompoundList_ctorTable[0], 3);
    temp_s1 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 2));
    ((igMemoryRefMetaField *)temp_s1)->_memType = igUnsignedCharMetaField_GetDefaultDescriptor();
    ((igRefMetaField *)temp_s1)->_destruct = 1;
    ((igMemoryRefMetaField *)temp_s1)->_releaseOnCopy = 1;
    ((igMemoryRefMetaField *)temp_s1)->_releaseOnReset = 1;
    igMetaObject_NameFields(temp_s0, &g_igCompoundList_fieldTable[0], &DAT_00497b88[0], &DAT_00497b98[0], temp_s2);
}

igMetaObject *FUN_00225a30(void) {
    return g_igOptBase_metaObject[0];
}

