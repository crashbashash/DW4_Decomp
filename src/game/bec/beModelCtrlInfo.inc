igMetaObject *g_beModelCtrlInfo_metaObject;
igMetaField *g_beModelCtrlInfo_kindStringMetaField;

igMetaObject *beModelCtrlInfo_GetMetaObject(void) {
    if (g_beModelCtrlInfo_metaObject == 0 || !isValid(g_beModelCtrlInfo_metaObject)) beModelCtrlInfo_EnsureRegistered();
    return g_beModelCtrlInfo_metaObject;
}

int beModelCtrlInfo_GetVTable(void) {
    beModelCtrlInfo obj;
    int vtable;

    igObject_InitHeader(&obj);
    obj._name = 0;
    obj._dataList = 0;
    obj._ramList = 0;
    obj._vtable = (int)&g_beModelCtrlInfo_vtable[0];
    obj._kindString = 0;
    vtable = *(int *)((char *)&obj + g_objectSystem->vtableProbeOffset);
    obj._vtable = (int)&g_beModelCtrlInfo_vtable[0];
    igStringRef_Destruct((igStringRef *)&obj._kindString, -1);
    beBaseInfo_Destroy((beBaseInfo *)&obj, (short)0);
    return vtable;
}

void beModelCtrlInfo_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(beModelCtrlInfo_Register);
}

CallbackArray *beModelCtrlInfo_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_beModelCtrlInfo_metaObject,
        beBaseInfo_Register,
        beBaseInfo_GetPublishedMetaObject,
        beModelCtrlInfo_GetMetaObjectFunction,
        "beModelCtrlInfo",
        0x20, /* instance size */
        beModelCtrlInfo_GetVTable,
        beModelCtrlInfo_InitFields,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void beModelCtrlInfo_GetMetaObjectFunction(void)
{
    beModelCtrlInfo_GetMetaObject();
}

static FieldFactory g_beModelCtrlInfo_ctorTable[] = {
    igStringMetaField_Create,
};
static const char *g_beModelCtrlInfo_fieldTable[] = {
    "_kindString",
};
static igMetaField **g_beModelCtrlInfo_fieldHandles[] = {
    &g_beModelCtrlInfo_kindStringMetaField,
};
static int g_beModelCtrlInfo_fieldOffsets[] = {
    28,
};

void beModelCtrlInfo_InitFields(void) {
    int base;
    igMetaObject *meta;

    meta = g_beModelCtrlInfo_metaObject;
    base = igMetaObject_GetFieldCount(meta);
    igMetaObject_CreateFields(meta, g_beModelCtrlInfo_ctorTable, 1);
    igStringMetaField_SetDefaultText(igMetaObject_GetFieldAt(meta, base), 0);
    igMetaObject_NameFields(meta, g_beModelCtrlInfo_fieldTable, g_beModelCtrlInfo_fieldHandles, g_beModelCtrlInfo_fieldOffsets, base);
}

