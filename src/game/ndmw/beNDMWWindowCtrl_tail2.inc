igMetaObject *g_beNDMWWindowCtrl_metaObject;
igMetaField *g_beNDMWWindowCtrl_nowProcKazuMetaField;
igMetaEnum *g_beNDMWWindowCtrl_messageMetaEnum;

igMetaObject *FUN_003bb570(void) {
    if (g_beNDMWWindowCtrl_metaObject == 0) {
        g_beNDMWWindowCtrl_metaObject = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData[0]));
    }
    return g_beNDMWWindowCtrl_metaObject;
}

void *FUN_003bb5c0(void) {
    igMetaObject *g = g_beNDMWWindowCtrl_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false) {
        FUN_003bb610();
    }
    return g_beNDMWWindowCtrl_metaObject;
}

void FUN_003bb610(void)
{
    igMetaObject_RunStaticInit(beNDMWWindowCtrl_Register);
}

void *beNDMWWindowCtrl_Register(void) {
    NdmwLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        1, /* abstract */
        &g_beNDMWWindowCtrl_metaObject,
        beNDMWWindow_Register,
        beNDMWWindow_GetPublishedMetaObject,
        beNDMWWindowCtrl_GetMetaObject,
        "beNDMWWindowCtrl",
        0x54, /* instance size */
        0,
        beNDMWWindowCtrl_InitFields,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void beNDMWWindowCtrl_GetMetaObject(void)
{
    FUN_003bb5c0();
}

static FieldFactory g_beNDMWWindowCtrl_ctorTable[] = {
    igIntMetaField_Create,
};
static const char *g_beNDMWWindowCtrl_fieldTable[] = {
    "_nowProcKazu",
};
static igMetaField **g_beNDMWWindowCtrl_fieldHandles[] = {
    &g_beNDMWWindowCtrl_nowProcKazuMetaField,
};
static int g_beNDMWWindowCtrl_fieldOffsets[] = {
    80,
};

void beNDMWWindowCtrl_InitFields(void) {
    int temp_s1;
    igMetaObject *temp_s0;

    temp_s0 = g_beNDMWWindowCtrl_metaObject;
    temp_s1 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, g_beNDMWWindowCtrl_ctorTable, 1);
    igMetaObject_NameFields(temp_s0, g_beNDMWWindowCtrl_fieldTable, g_beNDMWWindowCtrl_fieldHandles, g_beNDMWWindowCtrl_fieldOffsets, temp_s1);
}

static const char *g_beNDMWWindowCtrl_messageNames[] = {
    "GENERATE",
    "REMOVE",
    "UPDATE",
    "GETSHOPDATA",
    "ONPREVIEW",
    "OFPREVIEW",
    "ISRUN",
};
static int g_beNDMWWindowCtrl_messageValues[] = {
    0,
    1,
    2,
    3,
    4,
    5,
    6,
};

igMetaEnum *StatusMessage_GetMetaEnum(void) {
    if (g_beNDMWWindowCtrl_messageMetaEnum == 0) {
        g_beNDMWWindowCtrl_messageMetaEnum = igMetaEnum_Create("Message", g_beNDMWWindowCtrl_messageNames, g_beNDMWWindowCtrl_messageValues, 7);
    }
    return g_beNDMWWindowCtrl_messageMetaEnum;
}

