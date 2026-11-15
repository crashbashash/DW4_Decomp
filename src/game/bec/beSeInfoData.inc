igMetaObject *g_beSeInfoData_metaObject;
igMetaField *g_beSeInfoData_actionListMetaField;

void *FUN_00345ea0(void) {
    igMetaObject *g = g_beSeInfoData_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false) {
        FUN_00345fd0();
    }
    return g_beSeInfoData_metaObject;
}

int beSeInfoData_GetVTable(void) {
    Obj_345ef0 obj;
    int r;

    igObject_InitHeader(&obj);
    obj.m8 = 0;
    obj.vt = &DAT_00538f40[0];
    obj.m16 = 0;
    r = *(int *)((char *)&obj + *(int *)((char *)(g_objectSystem[0]) + 916));
    obj.vt = &DAT_00538f40[0];
    obj.rel16();
    obj.vt = &g_igNamedObject_vtable[0];
    obj.rel8();
    return r;
}

void FUN_00345fd0(void)
{
    igMetaObject_RunStaticInit(beSeInfoData_Register);
}

static igMetaObjectCallback g_beSeInfoData_callbackList[] = { FUN_00346200, 0 };

void *beSeInfoData_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_beSeInfoData_metaObject,
        beBaseInfoData_Register,
        beBaseInfoData_GetPublishedMetaObject,
        beSeInfoData_GetMetaObject,
        "beSeInfoData",
        0x14, /* instance size */
        beSeInfoData_GetVTable,
        beSeInfoData_InitFields,
        0, /* extra callback item */
        g_beSeInfoData_callbackList /* callback list */
    );
}

void beSeInfoData_GetMetaObject(void)
{
    FUN_00345ea0();
}

static FieldFactory g_beSeInfoData_ctorTable[] = {
    igObjectRefMetaField_Create,
};
static const char *g_beSeInfoData_fieldTable[] = {
    "_actionList",
};
static igMetaField **g_beSeInfoData_fieldHandles[] = {
    &g_beSeInfoData_actionListMetaField,
};
static int g_beSeInfoData_fieldOffsets[] = {
    16,
};

void beSeInfoData_InitFields(void) {
    int temp_s2;
    void *temp_s1;
    void *temp_s0;

    temp_s0 = (void *)g_beSeInfoData_metaObject;
    temp_s2 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, g_beSeInfoData_ctorTable, 1);
    temp_s1 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2));
    ((igObjectRefMetaField *)temp_s1)->_metaObject = (int)FUN_00346120();
    igMetaObject_NameFields(temp_s0, g_beSeInfoData_fieldTable, g_beSeInfoData_fieldHandles, g_beSeInfoData_fieldOffsets, temp_s2);
}

