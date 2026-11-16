igMetaObject *g_beSeInfoData_metaObject;
igMetaField *g_beSeInfoData_actionListMetaField;

void *beSeInfoData_GetMetaObject(void) {
    igMetaObject *g = g_beSeInfoData_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false) {
        beSeInfoData_EnsureRegistered();
    }
    return g_beSeInfoData_metaObject;
}

int beSeInfoData_GetVTable(void) {
    beSeInfoData obj;
    int vtable;
    igObject **actionListSlot;
    char **nameSlot;

    igObject_InitHeader(&obj);
    nameSlot = (char **)&obj._name;
    *nameSlot = 0;
    obj._vtable = (int)&g_beSeInfoData_vtable[0];
    actionListSlot = (igObject **)&obj._actionList;
    *actionListSlot = 0;
    vtable = *(int *)((char *)&obj + *(int *)((char *)(g_objectSystem[0]) + 916));
    obj._vtable = (int)&g_beSeInfoData_vtable[0];
    igObjectRef_Release(actionListSlot);
    obj._vtable = (int)&g_igNamedObject_vtable[0];
    igStringRef_Release(nameSlot);
    return vtable;
}

void beSeInfoData_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(beSeInfoData_Register);
}

static igMetaObjectCallback g_beSeInfoData_callbackList[] = { beSeDataList_EnsureRegistered, 0 };

void *beSeInfoData_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_beSeInfoData_metaObject,
        beBaseInfoData_Register,
        beBaseInfoData_GetPublishedMetaObject,
        beSeInfoData_GetMetaObjectFunction,
        "beSeInfoData",
        0x14, /* instance size */
        beSeInfoData_GetVTable,
        beSeInfoData_InitFields,
        0, /* extra callback item */
        g_beSeInfoData_callbackList /* callback list */
    );
}

void beSeInfoData_GetMetaObjectFunction(void)
{
    beSeInfoData_GetMetaObject();
}

static FieldFactory g_beSeInfoData_ctorTable[] = {
    igObjectRefMetaField_Create,
};
static const char *g_beSeInfoData_fieldTable[] = {
    "_actionList",
};
static igMetaField **g_beSeInfoData_fieldHandles[] = {
    &g_beSeInfoData_actionListMetaField,
};
static int g_beSeInfoData_fieldOffsets[] = {
    16,
};

void beSeInfoData_InitFields(void) {
    int base;
    void *actionList;
    void *meta;

    meta = (void *)g_beSeInfoData_metaObject;
    base = igMetaObject_GetFieldCount(meta);
    igMetaObject_CreateFields(meta, g_beSeInfoData_ctorTable, 1);
    actionList = (void *)(igMetaObject_GetFieldAt(meta, base));
    ((igObjectRefMetaField *)actionList)->_metaObject = (int)beSeDataList_GetOrCreateMetaObject();
    igMetaObject_NameFields(meta, g_beSeInfoData_fieldTable, g_beSeInfoData_fieldHandles, g_beSeInfoData_fieldOffsets, base);
}

