igMetaObject *g_beActionStarterData2_metaObject;
igMetaField *g_beActionStarterData2_rotationMetaField;

void *beActionStarterData2_GetMetaObject(void) {
    igMetaObject *g = g_beActionStarterData2_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false) {
        beActionStarterData2_EnsureRegistered();
    }
    return g_beActionStarterData2_metaObject;
}

int beActionStarterData2_GetVTable(void) {
    beActionStarterData2 obj;
    int vtable;
    char **messageSlot;
    char **nameSlot;

    igObject_InitHeader(&obj);
    nameSlot = (char **)&obj._name;
    *nameSlot = 0;
    obj._vtable = (int)&g_beActionStarterData_vtable[0];
    messageSlot = (char **)&obj._message;
    *messageSlot = 0;
    obj._vtable = (int)&g_beActionStarterData2_vtable[0];
    vtable = *(int *)((char *)&obj + g_objectSystem->vtableProbeOffset);
    obj._vtable = (int)&g_beActionStarterData_vtable[0];
    igStringRef_Release(messageSlot);
    obj._vtable = (int)&g_igNamedObject_vtable[0];
    igStringRef_Release(nameSlot);
    return vtable;
}

void beActionStarterData2_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(beActionStarterData2_Register);
}

CallbackArray *beActionStarterData2_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_beActionStarterData2_metaObject,
        beActionStarterData_Register,
        beActionStarterData_GetPublishedMetaObject,
        beActionStarterData2_GetMetaObjectFunction,
        "beActionStarterData2",
        0x30, /* instance size */
        beActionStarterData2_GetVTable,
        beActionStarterData2_InitFields,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void beActionStarterData2_GetMetaObjectFunction(void)
{
    beActionStarterData2_GetMetaObject();
}

igMetaObject *beActionStarterData_GetPublishedMetaObject(void) {
    return g_beActionStarterData_metaObject;
}

static FieldFactory g_beActionStarterData2_ctorTable[] = {
    igVec3fMetaField_CreateInstance,
};
static const char *g_beActionStarterData2_fieldTable[] = {
    "_rotation",
};
static igMetaField **g_beActionStarterData2_fieldHandles[] = {
    &g_beActionStarterData2_rotationMetaField,
};
static int g_beActionStarterData2_fieldOffsets[] = {
    36,
};

void beActionStarterData2_InitFields(void) {
    int base;
    igMetaObject *meta;

    meta = g_beActionStarterData2_metaObject;
    base = igMetaObject_GetFieldCount(meta);
    igMetaObject_CreateFields(meta, g_beActionStarterData2_ctorTable, 1);
    igMetaObject_NameFields(meta, g_beActionStarterData2_fieldTable, g_beActionStarterData2_fieldHandles, g_beActionStarterData2_fieldOffsets, base);
}

