igMetaObject *g_beSeData_metaObject;
igMetaField *g_beSeData_soundMetaField;
igMetaField *g_beSeData_delayMetaField;

igMetaObject *beSeData_GetMetaObject(void) {
    igMetaObject *g = g_beSeData_metaObject;
    int t;
    if (!g || !(t = (g->_validity & 4) != 0))
        beSeData_EnsureRegistered();
    return g_beSeData_metaObject;
}

int beSeData_GetVTable(void) {
    SeDataLocal obj;
    int vtable;

    igObject_InitHeader(&obj);
    obj._name = 0;
    obj._vtable = (int)&g_beSeData_vtable[0];
    obj._sound = 0;
    vtable = *(int *)((char *)&obj + *(int *)((char *)g_objectSystem + 916));
    obj._vtable = (int)&g_beSeData_vtable[0];
    obj.relSound();
    obj._vtable = (int)&g_igNamedObject_vtable[0];
    obj.relName();
    return vtable;
}

void beSeData_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(beSeData_Register);
}

CallbackArray *beSeData_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_beSeData_metaObject,
        igNamedObject_Register,
        igNamedObject_GetPublishedMetaObject,
        beSeData_GetMetaObjectFunction,
        "beSeData",
        0x14, /* instance size */
        beSeData_GetVTable,
        beSeData_InitFields,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void beSeData_GetMetaObjectFunction(void)
{
    beSeData_GetMetaObject();
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
    int base;
    igMetaObject *meta;

    meta = g_beSeData_metaObject;
    base = igMetaObject_GetFieldCount(meta);
    igMetaObject_CreateFields(meta, g_beSeData_ctorTable, 2);
    igMetaObject_NameFields(meta, g_beSeData_fieldTable, g_beSeData_fieldHandles, g_beSeData_fieldOffsets, base);
}

