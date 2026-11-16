igMetaObject *g_beAction2Data_metaObject;
igMetaField *g_beAction2Data_comListMetaField;

igMetaObject *beAction2Data_GetOrCreateMetaObject(void) {
    if (g_beAction2Data_metaObject == 0) {
        g_beAction2Data_metaObject = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData));
    }
    return g_beAction2Data_metaObject;
}

void *beAction2Data_GetMetaObject(void) {
    igMetaObject *g = g_beAction2Data_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false) {
        beAction2Data_EnsureRegistered();
    }
    return g_beAction2Data_metaObject;
}

int beAction2Data_GetVTable(void) {
    beAction2Data obj;
    int vtable;
    igObject **comListSlot;
    char **nameSlot;

    igObject_InitHeader(&obj);
    nameSlot = (char **)&obj._name;
    *nameSlot = 0;
    obj._vtable = (int)&g_beAction2Data_vtable[0];
    comListSlot = (igObject **)&obj._comList;
    *comListSlot = 0;
    vtable = *(int *)((char *)&obj + *(int *)((char *)g_objectSystem + 916));
    obj._vtable = (int)&g_beAction2Data_vtable[0];
    igObjectRef_Release(comListSlot);
    obj._vtable = (int)&g_igNamedObject_vtable[0];
    igStringRef_Release(nameSlot);
    return vtable;
}

void beAction2Data_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(beAction2Data_Register);
}

static igMetaObjectCallback g_beAction2Data_callbackList[] = { igNamedObjectList_EnsureRegistered, 0 };

CallbackArray *beAction2Data_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_beAction2Data_metaObject,
        igNamedObject_Register,
        igNamedObject_GetPublishedMetaObject,
        beAction2Data_GetMetaObjectFunction,
        "beAction2Data",
        0x10, /* instance size */
        beAction2Data_GetVTable,
        beAction2Data_InitFields,
        0, /* extra callback item */
        g_beAction2Data_callbackList /* callback list */
    );
}

void beAction2Data_GetMetaObjectFunction(void)
{
    beAction2Data_GetMetaObject();
}

static FieldFactory g_beAction2Data_ctorTable[] = {
    igObjectRefMetaField_Create,
};
static const char *g_beAction2Data_fieldTable[] = {
    "_comList",
};
static igMetaField **g_beAction2Data_fieldHandles[] = {
    &g_beAction2Data_comListMetaField,
};
static int g_beAction2Data_fieldOffsets[] = {
    12,
};

void beAction2Data_InitFields(void) {
    int base;
    void *comList;
    igMetaObject *meta;

    meta = g_beAction2Data_metaObject;
    base = igMetaObject_GetFieldCount(meta);
    igMetaObject_CreateFields(meta, g_beAction2Data_ctorTable, 1);
    comList = (void *)(igMetaObject_GetFieldAt(meta, base));
    ((igObjectRefMetaField *)comList)->_metaObject = (int)igNamedObjectList_GetOrCreateMetaObject();
    ((igRefMetaField *)comList)->_construct = 1;
    igMetaObject_NameFields(meta, g_beAction2Data_fieldTable, g_beAction2Data_fieldHandles, g_beAction2Data_fieldOffsets, base);
}

igMetaEnum *g_beAction2Data_msgActionMetaEnum;
static const char *g_beAction2Data_msgActionNames[] = {
    "ISCOMEND", "ISRUN", "GETNAMELIST", "GETAPPEARANCELIST",
    "GETBONEMATRIX", "ONFREEZE", "OFFREEZE",
};
static int g_beAction2Data_msgActionValues[] = {
    0, 1, 2, 3, 4, 5, 6,
};

igMetaEnum *beAction2_GetMessageEnum(void) {
    if (g_beAction2Data_msgActionMetaEnum == 0) {
        g_beAction2Data_msgActionMetaEnum = igMetaEnum_Create("MsgAction", g_beAction2Data_msgActionNames, g_beAction2Data_msgActionValues, 7);
    }
    return g_beAction2Data_msgActionMetaEnum;
}

