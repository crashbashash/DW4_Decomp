igMetaObject *igIntObject_GetMetaObject(void)
{
    igMetaObject *g = g_igIntObject_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_001e4ec0();
    return g_igIntObject_metaObject[0];
}

int igIntObject_GetVTable(void) {
    struct Obj_1e4e80 obj;
    igObject_InitHeader(&obj);
    obj.vt = &DAT_0052bbb0[0];
    return *(int *)((char *)&obj + *(int *)((char *)(DAT_00586dc8[0]) + 916));
}

void FUN_001e4ec0(void)
{
    igMetaObject_RunStaticInit(igIntObject_Register);
}

void igIntObject_Register(void) {
    DataPumpLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igIntObject_metaObject,
        igObject_Register,
        igObject_GetMetaObject_ParentAccessor,
        thunk_igIntObject_GetMetaObject,
        igIntObject_className,
        0xC, /* instance size */
        igIntObject_GetVTable,
        &igIntObject_InitFields,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void thunk_igIntObject_GetMetaObject(void) {
    igIntObject_GetMetaObject();
}

void igIntObject_InitFields(void) {
    int temp_s1;
    void *temp_s0;

    temp_s0 = (void *)DAT_00562bd0[0];
    temp_s1 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &DAT_0048db40[0], 1);
    igMetaObject_NameFields(temp_s0, &DAT_0048db48[0], &DAT_0048db50[0], &DAT_0048db58[0], temp_s1);
}

