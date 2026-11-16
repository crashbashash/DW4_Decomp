igMetaObject *g_beSoundData_metaObject;
igMetaField *g_beSoundData_typeMetaField;
igMetaField *g_beSoundData_fnameIdxMetaField;
igMetaField *g_beSoundData_memoryIdxMetaField;
igMetaField *g_beSoundData_channelMetaField;
igMetaField *g_beSoundData_volumeMetaField;
igMetaField *g_beSoundData_priorityMetaField;

igMetaObject *beSoundData_GetMetaObject(void) {
    igMetaObject *g = g_beSoundData_metaObject;
    int t;
    if (!g || !(t = (g->_validity & 4) != 0))
        beSoundData_EnsureRegistered();
    return g_beSoundData_metaObject;
}

int beSoundData_GetVTable(void) {
    beSoundData obj;
    int vtable;
    char **nameSlot;

    igObject_InitHeader(&obj);
    obj._vtable = (int)&g_igNamedObject_vtable[0];
    nameSlot = (char **)&obj._name;
    *nameSlot = 0;
    obj._vtable = (int)&g_beSoundData_vtable[0];
    vtable = *(int *)((char *)&obj + *(int *)((char *)(g_objectSystem[0]) + 916));
    obj._vtable = (int)&g_igNamedObject_vtable[0];
    igStringRef_Release(nameSlot);
    return vtable;
}

beBaseInfoData *beBaseInfoData_Destroy(beBaseInfoData *self, short delete_storage) {
    if (self != 0) {
        self->_vtable = (int)&g_beBaseInfoData_vtable[0];
        /* ~igNamedObject is inlined here with its own null check on `this` */
        if (self != 0) {
            self->_vtable = (int)&g_igNamedObject_vtable[0];
            igStringRef_Release((char **)&self->_name);
        }
        if (delete_storage > 0) {
            Memory_FreeBufferAliasC(self);
        }
    }
    return self;
}

void beSoundData_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(beSoundData_Register);
}

void *beSoundData_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_beSoundData_metaObject,
        beBaseInfoData_Register,
        beBaseInfoData_GetPublishedMetaObject,
        beSoundData_GetMetaObjectFunction,
        "beSoundData",
        0x20, /* instance size */
        beSoundData_GetVTable,
        beSoundData_InitFields,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void beSoundData_GetMetaObjectFunction(void)
{
    beSoundData_GetMetaObject();
}

static FieldFactory g_beSoundData_ctorTable[] = {
    igShortMetaField_Create,
    igShortMetaField_Create,
    igIntMetaField_Create,
    igShortMetaField_Create,
    igShortMetaField_Create,
    igShortMetaField_Create,
};
static const char *g_beSoundData_fieldTable[] = {
    "_type",
    "_fnameIdx",
    "_memoryIdx",
    "_channel",
    "_volume",
    "_priority",
};
static igMetaField **g_beSoundData_fieldHandles[] = {
    &g_beSoundData_typeMetaField,
    &g_beSoundData_fnameIdxMetaField,
    &g_beSoundData_memoryIdxMetaField,
    &g_beSoundData_channelMetaField,
    &g_beSoundData_volumeMetaField,
    &g_beSoundData_priorityMetaField,
};
static int g_beSoundData_fieldOffsets[] = {
    16,
    18,
    20,
    24,
    26,
    28,
};

void beSoundData_InitFields(void) {
    int base;
    void *meta;

    meta = (void *)g_beSoundData_metaObject;
    base = igMetaObject_GetFieldCount(meta);
    igMetaObject_CreateFields(meta, g_beSoundData_ctorTable, 6);
    igShortMetaField_SetDefault(((int)igMetaObject_GetFieldAt(meta, base)), -1);
    igShortMetaField_SetDefault(((int)igMetaObject_GetFieldAt(meta, base + 1)), -1);
    igIntMetaField_SetDefault(((int)igMetaObject_GetFieldAt(meta, base + 2)), -1);
    igShortMetaField_SetDefault(((int)igMetaObject_GetFieldAt(meta, base + 3)), 1);
    igMetaObject_NameFields(meta, g_beSoundData_fieldTable, g_beSoundData_fieldHandles, g_beSoundData_fieldOffsets, base);
}

igMetaEnum *g_beSoundData_messageMetaEnum;
static const char *g_beSoundData_messageNames[] = {
    "MODENONE", "STOP", "PLAY", "PLAYatPAUSE",
    "PAUSEOFF", "VOLUMECTL", "BGMSTOP", "ENVSTOP",
    "SESTOP", "GETWORDLIST", "VOLUMECTL2", "FXCTL",
    "ISREADY", "ISBGMREADY", "ISENVREADY", "ISALLREADY",
    "GETCURRENTBGM", "SNDFVOLUME", "OFFREEZE", "ONFREEZE",
    "MAKEBINLIST", "ISDONETRANS", "FREESFPDATA",
};
static int g_beSoundData_messageValues[] = {
    0, 1, 2, 3, 4, 5, 6, 7,
    8, 9, 0xa, 0xb, 0xc, 0xd, 0xe, 0xf,
    0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16,
};

igMetaEnum *beSound_GetMessageEnum(void) {
    if (g_beSoundData_messageMetaEnum == 0) {
        g_beSoundData_messageMetaEnum = igMetaEnum_Create("Message", g_beSoundData_messageNames, g_beSoundData_messageValues, 0x17);
    }
    return g_beSoundData_messageMetaEnum;
}

