igMetaObject *g_beAction2WAITCHECK_metaObject;
igMetaField *g_beAction2WAITCHECK_waitTimeMetaField;

void *beAction2WAITCHECK_GetMetaObject(void) {
    igMetaObject *g = g_beAction2WAITCHECK_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false) {
        beAction2WAITCHECK_EnsureRegistered();
    }
    return g_beAction2WAITCHECK_metaObject;
}

int beAction2WAITCHECK_GetVTable(void) {
    beAction2WAITCHECK obj;
    int vtable;
    char **nameSlot;

    igObject_InitHeader(&obj);
    nameSlot = (char **)&obj._name;
    *nameSlot = 0;
    obj._vtable = (int)&g_igNamedObject_vtable[0];
    obj._vtable = (int)&g_beAction2WAITCHECK_vtable[0];
    vtable = *(int *)((char *)&obj + *(int *)((char *)(g_objectSystem[0]) + 916));
    obj._vtable = (int)&g_igNamedObject_vtable[0];
    igStringRef_Release(nameSlot);
    return vtable;
}

void beAction2WAITCHECK_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(beAction2WAITCHECK_Register);
}

void *beAction2WAITCHECK_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_beAction2WAITCHECK_metaObject,
        igNamedObject_Register,
        igNamedObject_GetPublishedMetaObject,
        beAction2WAITCHECK_GetMetaObjectFunction,
        "beAction2WAITCHECK",
        0x10, /* instance size */
        beAction2WAITCHECK_GetVTable,
        beAction2WAITCHECK_InitFields,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void beAction2WAITCHECK_GetMetaObjectFunction(void)
{
    beAction2WAITCHECK_GetMetaObject();
}

static FieldFactory g_beAction2WAITCHECK_ctorTable[] = {
    igFloatMetaField_Create,
};
static const char *g_beAction2WAITCHECK_fieldTable[] = {
    "_waitTime",
};
static igMetaField **g_beAction2WAITCHECK_fieldHandles[] = {
    &g_beAction2WAITCHECK_waitTimeMetaField,
};
static int g_beAction2WAITCHECK_fieldOffsets[] = {
    12,
};

void beAction2WAITCHECK_InitFields(void) {
    int base;
    void *meta;

    meta = (void *)g_beAction2WAITCHECK_metaObject;
    base = igMetaObject_GetFieldCount(meta);
    igMetaObject_CreateFields(meta, g_beAction2WAITCHECK_ctorTable, 1);
    igMetaObject_NameFields(meta, g_beAction2WAITCHECK_fieldTable, g_beAction2WAITCHECK_fieldHandles, g_beAction2WAITCHECK_fieldOffsets, base);
}

