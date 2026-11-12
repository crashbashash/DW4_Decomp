igMetaObject *igFloatObject_GetMetaObject(void)
{
    igMetaObject *g = g_igFloatObject_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_001e5050();
    return g_igFloatObject_metaObject[0];
}

int igFloatObject_GetVTable(void) {
    struct Obj_1e5010 obj;
    igObject_InitHeader(&obj);
    obj.vt = &DAT_0052bb50[0];
    return *(int *)((char *)&obj + *(int *)((char *)(g_objectSystem[0]) + 916));
}

void FUN_001e5050(void)
{
    igMetaObject_RunStaticInit(igFloatObject_Register);
}

void igFloatObject_Register(void) {
    DataPumpLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igFloatObject_metaObject,
        igObject_Register,
        igObject_GetMetaObject_ParentAccessor,
        thunk_igFloatObject_GetMetaObject,
        igFloatObject_className,
        0xC, /* instance size */
        igFloatObject_GetVTable,
        &igFloatObject_InitFields,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void thunk_igFloatObject_GetMetaObject(void) {
    igFloatObject_GetMetaObject();
}

void igFloatObject_InitFields(void) {
    int temp_s1;
    void *temp_s0;

    temp_s0 = (void *)g_igFloatObject_metaObject[0];
    temp_s1 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &DAT_0048db60[0], 1);
    igMetaObject_NameFields(temp_s0, &DAT_0048db68[0], &DAT_0048db70[0], &DAT_0048db78[0], temp_s1);
}

