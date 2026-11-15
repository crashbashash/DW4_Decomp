igMetaObject *g_beSeData_metaObject;
igMetaField *g_beSeData_soundMetaField;
igMetaField *g_beSeData_delayMetaField;

igMetaObject *FUN_003462b0(void) {
    igMetaObject *g = g_beSeData_metaObject;
    int t;
    if (!g || !(t = (g->_validity & 4) != 0))
        FUN_003463d0();
    return g_beSeData_metaObject;
}

int beSeData_GetVTable(void) {
    SeDataLocal obj;
    int r;

    igObject_InitHeader(&obj);
    obj._name = 0;
    obj._vtable = (int)&DAT_00538e70[0];
    obj._sound = 0;
    r = *(int *)((char *)&obj + *(int *)((char *)(g_objectSystem[0]) + 916));
    obj._vtable = (int)&DAT_00538e70[0];
    obj.relSound();
    obj._vtable = (int)&g_igNamedObject_vtable[0];
    obj.relName();
    return r;
}

void FUN_003463d0(void)
{
    igMetaObject_RunStaticInit(beSeData_Register);
}

void *beSeData_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_beSeData_metaObject,
        igNamedObject_Register,
        igNamedObject_GetPublishedMetaObject,
        beSeData_GetMetaObject,
        "beSeData",
        0x14, /* instance size */
        beSeData_GetVTable,
        beSeData_InitFields,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void beSeData_GetMetaObject(void)
{
    FUN_003462b0();
}

static FieldFactory g_beSeData_ctorTable[] = {
    igStringMetaField_Create,
    igShortMetaField_Create,
};
static const char *g_beSeData_fieldTable[] = {
    "_sound",
    "_delay",
};
static igMetaField **g_beSeData_fieldHandles[] = {
    &g_beSeData_soundMetaField,
    &g_beSeData_delayMetaField,
};
static int g_beSeData_fieldOffsets[] = {
    12,
    16,
};

void beSeData_InitFields(void) {
    int temp_s1;
    void *temp_s0;

    temp_s0 = (void *)g_beSeData_metaObject;
    temp_s1 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, g_beSeData_ctorTable, 2);
    igMetaObject_NameFields(temp_s0, g_beSeData_fieldTable, g_beSeData_fieldHandles, g_beSeData_fieldOffsets, temp_s1);
}

