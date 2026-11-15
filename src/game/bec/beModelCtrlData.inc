igMetaObject *g_beModelCtrlData_metaObject;
igMetaField *g_beModelCtrlData_comListMetaField;

igMetaObject *FUN_003567d0(void) {
    if (g_beModelCtrlData_metaObject == 0) {
        g_beModelCtrlData_metaObject = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData[0]));
    }
    return g_beModelCtrlData_metaObject;
}

igMetaObject *FUN_00356820(void) {
    igMetaObject *g = g_beModelCtrlData_metaObject;
    if (g != 0) {
        int b = !!(g->_validity & 4);
        if (b) goto done;
    }
    FUN_00356950();
done:
    return g_beModelCtrlData_metaObject;
}

int beModelCtrlData_GetVTable(void) {
    Obj_356870 obj;
    int r;

    igObject_InitHeader(&obj);
    obj.s = 0;
    obj.vt = &DAT_005371c0[0];
    obj.ref = 0;
    r = *(int *)((char *)&obj + *(int *)((char *)(g_objectSystem[0]) + 916));
    obj.vt = &DAT_005371c0[0];
    obj.releaseRef();
    obj.vt = &g_igNamedObject_vtable[0];
    obj.releaseStr();
    return r;
}

void FUN_00356950(void)
{
    igMetaObject_RunStaticInit(beModelCtrlData_Register);
}

static igMetaObjectCallback g_beModelCtrlData_callbackList[] = { igNamedObjectList_EnsureRegistered, 0 };

void *beModelCtrlData_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_beModelCtrlData_metaObject,
        igNamedObject_Register,
        igNamedObject_GetPublishedMetaObject,
        beModelCtrlData_GetMetaObject,
        "beModelCtrlData",
        0x10, /* instance size */
        beModelCtrlData_GetVTable,
        beModelCtrlData_InitFields,
        0, /* extra callback item */
        g_beModelCtrlData_callbackList /* callback list */
    );
}

void beModelCtrlData_GetMetaObject(void)
{
    FUN_00356820();
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
    int temp_s2;
    void *temp_s1;
    void *temp_s0;

    temp_s0 = (void *)g_beModelCtrlData_metaObject;
    temp_s2 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, g_beModelCtrlData_ctorTable, 1);
    temp_s1 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2));
    ((igObjectRefMetaField *)temp_s1)->_metaObject = igNamedObjectList_GetOrCreateMetaObject();
    ((igRefMetaField *)temp_s1)->_construct = 1;
    igMetaObject_NameFields(temp_s0, g_beModelCtrlData_fieldTable, g_beModelCtrlData_fieldHandles, g_beModelCtrlData_fieldOffsets, temp_s2);
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
        g_beModelCtrlData_msgActionMetaEnum = igMetaEnum_Create("MsgAction", g_beModelCtrlData_msgActionNames, g_beModelCtrlData_msgActionValues, 0x21);
    }
    return g_beModelCtrlData_msgActionMetaEnum;
}

