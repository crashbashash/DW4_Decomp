igMetaObject *igFogStateAttr_GetMetaObject(void)
{
    igMetaObject *g = g_igFogStateAttr_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_00137ca0();
    return g_igFogStateAttr_metaObject[0];
}

int igFogStateAttr_GetVTable(void) {
    struct Obj o;
    igObject_InitHeader(&o);
    o.vt = &DAT_00523a90[0];
    return *(int *)((char *)&o + *(int *)((char *)(g_objectSystem[0]) + 916));
}

void FUN_00137ca0(void)
{
    igMetaObject_RunStaticInit(igFogStateAttr_Register);
}

void igFogStateAttr_Register(void) {
    AttrsLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igFogStateAttr_metaObject,
        igVisualAttribute_Register,
        igVisualAttribute_GetPublishedMetaObject,
        thunk_igFogStateAttr_GetMetaObject,
        igFogStateAttr_className,
        0x10, /* instance size */
        igFogStateAttr_GetVTable,
        &igFogStateAttr_InitFields,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void thunk_igFogStateAttr_GetMetaObject(void) {
    igFogStateAttr_GetMetaObject();
}

void igFogStateAttr_InitFields(void) {
    int temp_s1;
    void *temp_s0;

    temp_s0 = (void *)g_igFogStateAttr_metaObject[0];
    temp_s1 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &g_igFogStateAttr_ctorTable[0], 1);
    igMetaObject_NameFields(temp_s0, &g_igFogStateAttr_fieldTable[0], &DAT_00486670[0], &DAT_00486678[0], temp_s1);
}

