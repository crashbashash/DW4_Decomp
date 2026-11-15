igMetaObject *g_igBasicColorChanger_metaObject;
igMetaField *g_igBasicColorChanger_colorsMetaField;
igMetaField *g_igBasicColorChanger_disabledColorMetaField;

igMetaObject *FUN_00451fb0(void) {
    return g_igBasicColorChanger_metaObject;
}

igMetaObject *FUN_00451fc0(void) {
    if (g_igBasicColorChanger_metaObject == 0) {
        g_igBasicColorChanger_metaObject = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData[0]));
    }
    return g_igBasicColorChanger_metaObject;
}

igMetaObject *igBasicColorChanger_GetMetaObject(void)
{
    igMetaObject *g = g_igBasicColorChanger_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false)
        igBasicColorChanger_RunStaticInit();
    return g_igBasicColorChanger_metaObject;
}

int igBasicColorChanger_GetVTable(void) {
    struct Obj_452060 obj;
    igObject_InitHeader(&obj);
    obj.vt = &DAT_00541550[0];
    return *(int *)((char *)&obj + *(int *)((char *)(g_objectSystem[0]) + 916));
}

void igBasicColorChanger_RunStaticInit(void)
{
    igMetaObject_RunStaticInit(igBasicColorChanger_Register);
}

void igBasicColorChanger_Register(void) {
    GuiLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        &g_igBasicColorChanger_metaObject,
        igColorChanger_Register,
        igColorChanger_GetPublishedMetaObject,
        thunk_igBasicColorChanger_GetMetaObject,
        "igBasicColorChanger",
        0x58, /* instance size */
        igBasicColorChanger_GetVTable,
        &igBasicColorChanger_InitFields,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void thunk_igBasicColorChanger_GetMetaObject(void) {
    igBasicColorChanger_GetMetaObject();
}

igMetaObject *FUN_00452130(void) {
    return g_igColorChanger_metaObject;
}

static FieldFactory g_igBasicColorChanger_ctorTable[] = {
    FUN_00187560,
    FUN_001872a0,
};
static const char *g_igBasicColorChanger_fieldTable[] = {
    "_colors",
    "_disabledColor",
};
static igMetaField **g_igBasicColorChanger_fieldHandles[] = {
    &g_igBasicColorChanger_colorsMetaField,
    &g_igBasicColorChanger_disabledColorMetaField,
};
static int g_igBasicColorChanger_fieldOffsets[] = {
    8,
    72,
};

void igBasicColorChanger_InitFields(void) {
    int temp_s1;
    void *f;
    void *temp_s0;
    temp_s0 = (void *)g_igBasicColorChanger_metaObject;
    temp_s1 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, g_igBasicColorChanger_ctorTable, 2);
    f = igMetaObject_GetFieldAt(temp_s0, temp_s1);
    *(int *)((char *)f + 52) = 4;
    igMetaObject_NameFields(temp_s0, g_igBasicColorChanger_fieldTable, g_igBasicColorChanger_fieldHandles, g_igBasicColorChanger_fieldOffsets, temp_s1);
}

