igMetaObject *g_beOptInfo_metaObject;
igMetaField *g_beOptInfo_buildNoMetaField;
igMetaField *g_beOptInfo_isAsmMetaField;
igMetaField *g_beOptInfo_libOptMetaField;
igMetaField *g_beOptInfo_libAsmMetaField;

igMetaObject *beOptInfo_GetMetaObject(void)
{
    igMetaObject *g = g_beOptInfo_metaObject;
    bool t;
    if (!g || (t = g->_validity & 4) == 0)
        beOptInfo_EnsureRegistered();
    return g_beOptInfo_metaObject;
}

int beOptInfo_GetVTable(void) {
    beOptInfo obj;
    int vtable;

    igObject_InitHeader(&obj);
    obj._name = 0;
    obj._vtable = (int)&g_beOptInfo_vtable[0];
    obj._libOpt = 0;
    obj._libAsm = 0;
    vtable = *(int *)((char *)&obj + g_objectSystem->vtableProbeOffset);
    obj._vtable = (int)&g_beOptInfo_vtable[0];
    igStringRef_Destruct((igStringRef *)&obj._libAsm, -1);
    igStringRef_Destruct((igStringRef *)&obj._libOpt, -1);
    igInfo_Destroy((igInfo *)&obj, 0);
    return vtable;
}

void beOptInfo_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(beOptInfo_Register);
}

CallbackArray *beOptInfo_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_beOptInfo_metaObject,
        igInfo_Register,
        igInfo_GetPublishedMetaObject,
        beOptInfo_GetMetaObjectFunction,
        "beOptInfo",
        0x24, /* instance size */
        beOptInfo_GetVTable,
        beOptInfo_InitFields,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void beOptInfo_GetMetaObjectFunction(void)
{
    beOptInfo_GetMetaObject();
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
    int base;
    igMetaObject *meta;

    meta = g_beOptInfo_metaObject;
    base = igMetaObject_GetFieldCount(meta);
    igMetaObject_CreateFields(meta, g_beOptInfo_ctorTable, 4);
    igStringMetaField_SetDefaultText(igMetaObject_GetFieldAt(meta, base + 2), 0);
    igStringMetaField_SetDefaultText(igMetaObject_GetFieldAt(meta, base + 3), 0);
    igMetaObject_NameFields(meta, g_beOptInfo_fieldTable, g_beOptInfo_fieldHandles, g_beOptInfo_fieldOffsets, base);
}

