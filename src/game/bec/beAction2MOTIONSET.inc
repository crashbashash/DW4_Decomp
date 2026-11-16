igMetaObject *g_beAction2MOTIONSET_metaObject;
igMetaField *g_beAction2MOTIONSET_hokanModeMetaField;
igMetaField *g_beAction2MOTIONSET_hokanTimeMetaField;
igMetaField *g_beAction2MOTIONSET_loopModeMetaField;

void *beAction2MOTIONSET_GetMetaObject(void) {
    unsigned char b;
    if (g_beAction2MOTIONSET_metaObject != 0) {
        b = (g_beAction2MOTIONSET_metaObject->_validity & 4) != 0;
        if (b != 0) goto done;
    }
    beAction2MOTIONSET_EnsureRegistered();
done:
    return g_beAction2MOTIONSET_metaObject;
}

int beAction2MOTIONSET_GetVTable(void) {
    beAction2MOTIONSET obj;
    int vtable;
    char **loopModeSlot;
    char **hokanModeSlot;
    char **nameSlot;

    igObject_InitHeader(&obj);
    nameSlot = (char **)&obj._name;
    *nameSlot = 0;
    obj._vtable = (int)&g_beAction2MOTIONSET_vtable[0];
    hokanModeSlot = (char **)&obj._hokanMode;
    *hokanModeSlot = 0;
    loopModeSlot = (char **)&obj._loopMode;
    *loopModeSlot = 0;
    vtable = *(int *)((char *)&obj + *(int *)((char *)g_objectSystem + 916));
    obj._vtable = (int)&g_beAction2MOTIONSET_vtable[0];
    igStringRef_Release(loopModeSlot);
    igStringRef_Release(hokanModeSlot);
    obj._vtable = (int)&g_igNamedObject_vtable[0];
    igStringRef_Release(nameSlot);
    return vtable;
}

void beAction2MOTIONSET_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(beAction2MOTIONSET_Register);
}

CallbackArray *beAction2MOTIONSET_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_beAction2MOTIONSET_metaObject,
        igNamedObject_Register,
        igNamedObject_GetPublishedMetaObject,
        beAction2MOTIONSET_GetMetaObjectFunction,
        "beAction2MOTIONSET",
        0x18, /* instance size */
        beAction2MOTIONSET_GetVTable,
        beAction2MOTIONSET_InitFields,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void beAction2MOTIONSET_GetMetaObjectFunction(void)
{
    beAction2MOTIONSET_GetMetaObject();
}

static FieldFactory g_beAction2MOTIONSET_ctorTable[] = {
    igStringMetaField_Create,
    igFloatMetaField_Create,
    igStringMetaField_Create,
};
static const char *g_beAction2MOTIONSET_fieldTable[] = {
    "_hokanMode",
    "_hokanTime",
    "_loopMode",
};
static igMetaField **g_beAction2MOTIONSET_fieldHandles[] = {
    &g_beAction2MOTIONSET_hokanModeMetaField,
    &g_beAction2MOTIONSET_hokanTimeMetaField,
    &g_beAction2MOTIONSET_loopModeMetaField,
};
static int g_beAction2MOTIONSET_fieldOffsets[] = {
    12,
    16,
    20,
};

void beAction2MOTIONSET_InitFields(void) {
    int base;
    igMetaObject *meta;

    meta = g_beAction2MOTIONSET_metaObject;
    base = igMetaObject_GetFieldCount(meta);
    igMetaObject_CreateFields(meta, g_beAction2MOTIONSET_ctorTable, 3);
    igMetaObject_NameFields(meta, g_beAction2MOTIONSET_fieldTable, g_beAction2MOTIONSET_fieldHandles, g_beAction2MOTIONSET_fieldOffsets, base);
}

