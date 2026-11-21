igMetaObject *g_beModelCtrlData_metaObject;
igMetaField *g_beModelCtrlData_comListMetaField;

igMetaObject *beModelCtrlData_GetOrCreateMetaObject(void) {
    if (g_beModelCtrlData_metaObject == 0) {
        g_beModelCtrlData_metaObject = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData));
    }
    return g_beModelCtrlData_metaObject;
}

igMetaObject *beModelCtrlData_GetMetaObject(void) {
    igMetaObject *g = g_beModelCtrlData_metaObject;
    if (g != 0) {
        int b = !!(g->_validity & 4);
        if (b) goto done;
    }
    beModelCtrlData_EnsureRegistered();
done:
    return g_beModelCtrlData_metaObject;
}

int beModelCtrlData_GetVTable(void) {
    beModelCtrlData obj;
    int vtable;
    igObject **comListSlot;
    char **nameSlot;

    igObject_InitHeader(&obj);
    nameSlot = (char **)&obj._name;
    *nameSlot = 0;
    obj._vtable = (int)&g_beModelCtrlData_vtable[0];
    comListSlot = (igObject **)&obj._comList;
    *comListSlot = 0;
    vtable = *(int *)((char *)&obj + g_objectSystem->vtableProbeOffset);
    obj._vtable = (int)&g_beModelCtrlData_vtable[0];
    igObjectRef_Release(comListSlot);
    obj._vtable = (int)&g_igNamedObject_vtable[0];
    igStringRef_Release(nameSlot);
    return vtable;
}

void beModelCtrlData_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(beModelCtrlData_Register);
}

static igMetaObjectCallback g_beModelCtrlData_callbackList[] = { igNamedObjectList_EnsureRegistered, 0 };

CallbackArray *beModelCtrlData_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_beModelCtrlData_metaObject,
        Gap::Core::igNamedObject::arkRegisterInternal,
        igNamedObject_GetPublishedMetaObject,
        beModelCtrlData_GetMetaObjectFunction,
        "beModelCtrlData",
        0x10, /* instance size */
        beModelCtrlData_GetVTable,
        beModelCtrlData_InitFields,
        0, /* extra callback item */
        g_beModelCtrlData_callbackList /* callback list */
    );
}

void beModelCtrlData_GetMetaObjectFunction(void)
{
    beModelCtrlData_GetMetaObject();
}

static FieldFactory g_beModelCtrlData_ctorTable[] = {
    igObjectRefMetaField_Create,
};
static const char *g_beModelCtrlData_fieldTable[] = {
    "_comList",
};
static igMetaField **g_beModelCtrlData_fieldHandles[] = {
    &g_beModelCtrlData_comListMetaField,
};
static int g_beModelCtrlData_fieldOffsets[] = {
    12,
};

void beModelCtrlData_InitFields(void) {
    int base;
    void *comList;
    igMetaObject *meta;

    meta = g_beModelCtrlData_metaObject;
    base = igMetaObject_GetFieldCount(meta);
    igMetaObject_CreateFields(meta, g_beModelCtrlData_ctorTable, 1);
    comList = (void *)(igMetaObject_GetFieldAt(meta, base));
    ((igObjectRefMetaField *)comList)->_metaObject = (int)igNamedObjectList_GetOrCreateMetaObject();
    ((igRefMetaField *)comList)->_construct = 1;
    igMetaObject_NameFields(meta, g_beModelCtrlData_fieldTable, g_beModelCtrlData_fieldHandles, g_beModelCtrlData_fieldOffsets, base);
}

igMetaEnum *g_beModelCtrlData_msgActionMetaEnum;
static const char *g_beModelCtrlData_msgActionNames[] = {
    "GENERATE", "GENERATE_NDSP", "REMOVE", "GETINFONAME",
    "GETINFONAME_RUN", "SETMATRIX", "CHKBULLET", "SETLABEL",
    "SETEFFECT", "SETSOUND", "GETMATRIX", "GETMATRIX_ALL",
    "GETMATRIX_ACTIVE", "GETTRCDATA", "GETHP", "SETHP",
    "GETRECNO", "ACTION1", "ONCTRL", "OFCTRL",
    "ONFREEZE", "OFFREEZE", "SETLODHIGH", "RESETLODHIGH",
    "MOVETRANS", "SETCONVEYOR", "SETQUICKSAND", "SETSLIPPEDFLOOR",
    "ISRUN", "ISSEQNAME", "ONHITBULLETBOX", "OFHITBULLETBOX",
    "GETSEQNAMELIST",
};
static int g_beModelCtrlData_msgActionValues[] = {
    0, 1, 2, 3, 4, 5, 6, 7,
    8, 9, 0xa, 0xb, 0xc, 0xd, 0xe, 0xf,
    0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17,
    0x18, 0x19, 0x1a, 0x1b, 0x1c, 0x1d, 0x1e, 0x1f,
    0x20,
};

igMetaEnum *beModelCtrl_GetMessageEnum(void) {
    if (g_beModelCtrlData_msgActionMetaEnum == 0) {
        g_beModelCtrlData_msgActionMetaEnum = (igMetaEnum *)Gap::Core::igMetaEnum::createMetaEnum("MsgAction", g_beModelCtrlData_msgActionNames, g_beModelCtrlData_msgActionValues, 0x21);
    }
    return g_beModelCtrlData_msgActionMetaEnum;
}

