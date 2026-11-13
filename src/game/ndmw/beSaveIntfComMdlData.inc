void *FUN_003bc710(void) {
    igMetaObject *g = g_beSaveIntfComMdlData_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false) {
        FUN_003bc820();
    }
    return g_beSaveIntfComMdlData_metaObject[0];
}

int beSaveIntfComMdlData_GetVTable(void) {
    Obj_3bc760 obj;
    int r;

    igObject_InitHeader(&obj);
    obj._vtable = (int)&DAT_0053d830[0];
    obj._openSQ = 0;
    obj._infoName = 0;
    r = *(int *)((char *)&obj + *(int *)((char *)(g_objectSystem[0]) + 916));
    obj._vtable = (int)&DAT_0053d830[0];
    obj.rel16();
    obj.rel12();
    return r;
}

void FUN_003bc820(void)
{
    igMetaObject_RunStaticInit(beSaveIntfComMdlData_Register);
}

void *beSaveIntfComMdlData_Register(void) {
    NdmwLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beSaveIntfComMdlData_metaObject,
        igObject_Register,
        igObject_GetMetaObject_ParentAccessor,
        beSaveIntfComMdlData_GetMetaObject,
        beSaveIntfComMdlData_className,
        0x14, /* instance size */
        beSaveIntfComMdlData_GetVTable,
        beSaveIntfComMdlData_InitFields,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void beSaveIntfComMdlData_GetMetaObject(void)
{
    FUN_003bc710();
}

void beSaveIntfComMdlData_InitFields(void) {
    int temp_s1;
    void *temp_s0;

    temp_s0 = (void *)g_beSaveIntfComMdlData_metaObject[0];
    temp_s1 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &g_beSaveIntfComMdlData_ctorTable[0], 3);
    igMetaObject_NameFields(temp_s0, &g_beSaveIntfComMdlData_fieldTable[0], &DAT_004ca1d8[0], &DAT_004ca1e8[0], temp_s1);
}

