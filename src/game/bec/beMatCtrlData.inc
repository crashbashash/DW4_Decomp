igMetaObject *g_beMatCtrlData_metaObject;
igMetaField *g_beMatCtrlData_chkBoxMetaField;

void *beMatCtrlData_GetMetaObject(void) {
    igMetaObject *g = g_beMatCtrlData_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false) {
        beMatCtrlData_EnsureRegistered();
    }
    return g_beMatCtrlData_metaObject;
}

int beMatCtrlData_GetVTable(void) {
    beMatCtrlData obj;
    int vtable;
    igObject **chkBoxSlot;
    char **nameSlot;

    igObject_InitHeader(&obj);
    nameSlot = (char **)&obj._name;
    *nameSlot = 0;
    obj._vtable = (int)&g_beMatCtrlData_vtable[0];
    chkBoxSlot = (igObject **)&obj._chkBox;
    *chkBoxSlot = 0;
    vtable = *(int *)((char *)&obj + g_objectSystem->vtableProbeOffset);
    obj._vtable = (int)&g_beMatCtrlData_vtable[0];
    igObjectRef_Release(chkBoxSlot);
    obj._vtable = (int)&g_igNamedObject_vtable[0];
    igStringRef_Release(nameSlot);
    return vtable;
}

void beMatCtrlData_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(beMatCtrlData_Register);
}

static igMetaObjectCallback g_beMatCtrlData_callbackList[] = { igAABox_EnsureRegistered, 0 };

CallbackArray *beMatCtrlData_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_beMatCtrlData_metaObject,
        Gap::Core::igNamedObject::arkRegisterInternal,
        igNamedObject_GetPublishedMetaObject,
        beMatCtrlData_GetMetaObjectFunction,
        "beMatCtrlData",
        0x10, /* instance size */
        beMatCtrlData_GetVTable,
        beMatCtrlData_InitFields,
        0, /* extra callback item */
        g_beMatCtrlData_callbackList /* callback list */
    );
}

void beMatCtrlData_GetMetaObjectFunction(void)
{
    beMatCtrlData_GetMetaObject();
}

static FieldFactory g_beMatCtrlData_ctorTable[] = {
    igObjectRefMetaField_Create,
};
static const char *g_beMatCtrlData_fieldTable[] = {
    "_chkBox",
};
static igMetaField **g_beMatCtrlData_fieldHandles[] = {
    &g_beMatCtrlData_chkBoxMetaField,
};
static int g_beMatCtrlData_fieldOffsets[] = {
    12,
};

void beMatCtrlData_InitFields(void) {
    int base;
    void *chkBox;
    igMetaObject *meta;

    meta = g_beMatCtrlData_metaObject;
    base = igMetaObject_GetFieldCount(meta);
    igMetaObject_CreateFields(meta, g_beMatCtrlData_ctorTable, 1);
    chkBox = (void *)(igMetaObject_GetFieldAt(meta, base));
    ((igObjectRefMetaField *)chkBox)->_metaObject = (int)igAABox_GetOrCreateMetaObject();
    igMetaObject_NameFields(meta, g_beMatCtrlData_fieldTable, g_beMatCtrlData_fieldHandles, g_beMatCtrlData_fieldOffsets, base);
}

igMetaEnum *g_beMatCtrlData_messageMetaEnum;
static const char *g_beMatCtrlData_messageNames[] = {
    "SHOWMAT", "HIDEMAT", "SHOW_LUACALL", "HIDE_LUACALL",
    "PAUSE", "RESTART",
};
static int g_beMatCtrlData_messageValues[] = {
    0, 1, 2, 3, 4, 5,
};

igMetaEnum *beMatCtrl_GetMessageEnum(void) {
    if (g_beMatCtrlData_messageMetaEnum == 0) {
        g_beMatCtrlData_messageMetaEnum = (igMetaEnum *)Gap::Core::igMetaEnum::createMetaEnum("Message", g_beMatCtrlData_messageNames, g_beMatCtrlData_messageValues, 6);
    }
    return g_beMatCtrlData_messageMetaEnum;
}

