igMetaObject *g_beAction2JOINTSET_metaObject;
igMetaField *g_beAction2JOINTSET_startTimeMetaField;
igMetaField *g_beAction2JOINTSET_endTimeMetaField;
igMetaField *g_beAction2JOINTSET_loopModeMetaField;

void *beAction2JOINTSET_GetMetaObject(void) {
    igMetaObject *g = g_beAction2JOINTSET_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false) {
        beAction2JOINTSET_EnsureRegistered();
    }
    return g_beAction2JOINTSET_metaObject;
}

int beAction2JOINTSET_GetVTable(void) {
    beAction2JOINTSET obj;
    int vtable;
    char **loopModeSlot;
    char **nameSlot;

    igObject_InitHeader(&obj);
    nameSlot = (char **)&obj._name;
    *nameSlot = 0;
    obj._vtable = (int)&g_beAction2JOINTSET_vtable[0];
    loopModeSlot = (char **)&obj._loopMode;
    *loopModeSlot = 0;
    vtable = *(int *)((char *)&obj + g_objectSystem->vtableProbeOffset);
    obj._vtable = (int)&g_beAction2JOINTSET_vtable[0];
    igStringRef_Release(loopModeSlot);
    obj._vtable = (int)&g_igNamedObject_vtable[0];
    igStringRef_Release(nameSlot);
    return vtable;
}

void beAction2JOINTSET_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(beAction2JOINTSET_Register);
}

CallbackArray *beAction2JOINTSET_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_beAction2JOINTSET_metaObject,
        igNamedObject_Register,
        igNamedObject_GetPublishedMetaObject,
        beAction2JOINTSET_GetMetaObjectFunction,
        "beAction2JOINTSET",
        0x18, /* instance size */
        beAction2JOINTSET_GetVTable,
        beAction2JOINTSET_InitFields,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void beAction2JOINTSET_GetMetaObjectFunction(void)
{
    beAction2JOINTSET_GetMetaObject();
}

static FieldFactory g_beAction2JOINTSET_ctorTable[] = {
    igFloatMetaField_Create,
    igFloatMetaField_Create,
    igStringMetaField_Create,
};
static const char *g_beAction2JOINTSET_fieldTable[] = {
    "_startTime",
    "_endTime",
    "_loopMode",
};
static igMetaField **g_beAction2JOINTSET_fieldHandles[] = {
    &g_beAction2JOINTSET_startTimeMetaField,
    &g_beAction2JOINTSET_endTimeMetaField,
    &g_beAction2JOINTSET_loopModeMetaField,
};
static int g_beAction2JOINTSET_fieldOffsets[] = {
    12,
    16,
    20,
};

void beAction2JOINTSET_InitFields(void) {
    int base;
    igMetaObject *meta;

    meta = g_beAction2JOINTSET_metaObject;
    base = igMetaObject_GetFieldCount(meta);
    igMetaObject_CreateFields(meta, g_beAction2JOINTSET_ctorTable, 3);
    igMetaObject_NameFields(meta, g_beAction2JOINTSET_fieldTable, g_beAction2JOINTSET_fieldHandles, g_beAction2JOINTSET_fieldOffsets, base);
}

