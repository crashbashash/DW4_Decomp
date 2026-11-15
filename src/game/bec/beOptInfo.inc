igMetaObject *g_beOptInfo_metaObject;
igMetaField *g_beOptInfo_buildNoMetaField;
igMetaField *g_beOptInfo_isAsmMetaField;
igMetaField *g_beOptInfo_libOptMetaField;
igMetaField *g_beOptInfo_libAsmMetaField;

igMetaObject *FUN_0034d080(void)
{
    igMetaObject *g = g_beOptInfo_metaObject;
    bool t;
    if (!g || (t = g->_validity & 4) == 0)
        FUN_0034d160();
    return g_beOptInfo_metaObject;
}

int beOptInfo_GetVTable(void) {
    Obj_34d0d0 o;
    int r;

    igObject_InitHeader(&o);
    o.f8 = 0;
    o.vt = &DAT_00538590[0];
    o.a = 0;
    o.b = 0;
    r = *(int *)((char *)&o + *(int *)((char *)(g_objectSystem[0]) + 916));
    o.vt = &DAT_00538590[0];
    igStringRef_Destruct(&o.b, -1);
    igStringRef_Destruct(&o.a, -1);
    igInfo_Destroy(&o, 0);
    return r;
}

void FUN_0034d160(void)
{
    igMetaObject_RunStaticInit(beOptInfo_Register);
}

void *beOptInfo_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_beOptInfo_metaObject,
        igInfo_Register,
        igInfo_GetPublishedMetaObject,
        beOptInfo_GetMetaObject,
        "beOptInfo",
        0x24, /* instance size */
        beOptInfo_GetVTable,
        beOptInfo_InitFields,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void beOptInfo_GetMetaObject(void)
{
    FUN_0034d080();
}

static FieldFactory g_beOptInfo_ctorTable[] = {
    igIntMetaField_Create,
    igBoolMetaField_Create,
    igStringMetaField_Create,
    igStringMetaField_Create,
};
static const char *g_beOptInfo_fieldTable[] = {
    "_buildNo",
    "_isAsm",
    "_libOpt",
    "_libAsm",
};
static igMetaField **g_beOptInfo_fieldHandles[] = {
    &g_beOptInfo_buildNoMetaField,
    &g_beOptInfo_isAsmMetaField,
    &g_beOptInfo_libOptMetaField,
    &g_beOptInfo_libAsmMetaField,
};
static int g_beOptInfo_fieldOffsets[] = {
    20,
    24,
    28,
    32,
};

void beOptInfo_InitFields(void) {
    int temp_s1;
    void *temp_s0;

    temp_s0 = (void *)g_beOptInfo_metaObject;
    temp_s1 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, g_beOptInfo_ctorTable, 4);
    igStringMetaField_SetDefaultText(((int)igMetaObject_GetFieldAt(temp_s0, temp_s1 + 2)), 0);
    igStringMetaField_SetDefaultText(((int)igMetaObject_GetFieldAt(temp_s0, temp_s1 + 3)), 0);
    igMetaObject_NameFields(temp_s0, g_beOptInfo_fieldTable, g_beOptInfo_fieldHandles, g_beOptInfo_fieldOffsets, temp_s1);
}

