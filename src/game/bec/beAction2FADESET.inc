igMetaObject *g_beAction2FADESET_metaObject;
igMetaField *g_beAction2FADESET_fadeTimeMetaField;
igMetaField *g_beAction2FADESET_fadeValueMetaField;

void *beAction2FADESET_GetMetaObject(void) {
    bool ok;
    if (g_beAction2FADESET_metaObject == 0) goto make;
    ok = !!(g_beAction2FADESET_metaObject->_validity & 4);
    if (ok != false) goto done;
make:
    beAction2FADESET_EnsureRegistered();
done:;
    return g_beAction2FADESET_metaObject;
}

int beAction2FADESET_GetVTable(void) {
    beAction2FADESET obj;
    int vtable;
    char **nameSlot;

    igObject_InitHeader(&obj);
    nameSlot = (char **)&obj._name;
    *nameSlot = 0;
    obj._vtable = (int)&g_igNamedObject_vtable[0];
    obj._vtable = (int)&g_beAction2FADESET_vtable[0];
    vtable = *(int *)((char *)&obj + *(int *)((char *)(g_objectSystem[0]) + 916));
    obj._vtable = (int)&g_igNamedObject_vtable[0];
    igStringRef_Release(nameSlot);
    return vtable;
}

void beAction2FADESET_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(beAction2FADESET_Register);
}

void *beAction2FADESET_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_beAction2FADESET_metaObject,
        igNamedObject_Register,
        igNamedObject_GetPublishedMetaObject,
        beAction2FADESET_GetMetaObjectFunction,
        "beAction2FADESET",
        0x14, /* instance size */
        beAction2FADESET_GetVTable,
        beAction2FADESET_InitFields,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void beAction2FADESET_GetMetaObjectFunction(void)
{
    beAction2FADESET_GetMetaObject();
}

static FieldFactory g_beAction2FADESET_ctorTable[] = {
    igFloatMetaField_Create,
    igFloatMetaField_Create,
};
static const char *g_beAction2FADESET_fieldTable[] = {
    "_fadeTime",
    "_fadeValue",
};
static igMetaField **g_beAction2FADESET_fieldHandles[] = {
    &g_beAction2FADESET_fadeTimeMetaField,
    &g_beAction2FADESET_fadeValueMetaField,
};
static int g_beAction2FADESET_fieldOffsets[] = {
    12,
    16,
};

void beAction2FADESET_InitFields(void) {
    int base;
    void *meta;

    meta = (void *)g_beAction2FADESET_metaObject;
    base = igMetaObject_GetFieldCount(meta);
    igMetaObject_CreateFields(meta, g_beAction2FADESET_ctorTable, 2);
    igMetaObject_NameFields(meta, g_beAction2FADESET_fieldTable, g_beAction2FADESET_fieldHandles, g_beAction2FADESET_fieldOffsets, base);
}

