void FUN_001e4c50(int arg0) {
    FUN_001e4d30();
    igMetaObject_CreateInstance(g_igMatrixObject_metaObject[0], arg0);
}

igMetaObject *igMatrixObject_GetMetaObject(void)
{
    igMetaObject *g = g_igMatrixObject_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_001e4d30();
    return g_igMatrixObject_metaObject[0];
}

int igMatrixObject_GetVTable(void) {
    struct Obj_1e4ce0 obj;
    igObject_InitHeader(&obj);
    obj.vt = &DAT_0052bc10[0];
    igMatrix44f_SetIdentity(obj.pad + 4);
    return *(int *)((char *)&obj + *(int *)((char *)(g_objectSystem[0]) + 916));
}

void FUN_001e4d30(void)
{
    igMetaObject_RunStaticInit(igMatrixObject_Register);
}

void igMatrixObject_Register(void) {
    DataPumpLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igMatrixObject_metaObject,
        igObject_Register,
        igObject_GetMetaObject_ParentAccessor,
        thunk_igMatrixObject_GetMetaObject,
        igMatrixObject_className,
        0x48, /* instance size */
        igMatrixObject_GetVTable,
        &igMatrixObject_InitFields,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void thunk_igMatrixObject_GetMetaObject(void) {
    igMatrixObject_GetMetaObject();
}

void igMatrixObject_InitFields(void) {
    int temp_s1;
    void *temp_s0;

    temp_s0 = (void *)g_igMatrixObject_metaObject[0];
    temp_s1 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &DAT_0048db20[0], 1);
    igMetaObject_NameFields(temp_s0, &DAT_0048db28[0], &DAT_0048db30[0], &DAT_0048db38[0], temp_s1);
}

