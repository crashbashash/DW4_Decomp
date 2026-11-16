igMetaObject *g_beGeneraterItemDataOne_metaObject;
igMetaField *g_beGeneraterItemDataOne_idMetaField;
igMetaField *g_beGeneraterItemDataOne_rankMetaField;
igMetaField *g_beGeneraterItemDataOne_rateMetaField;

void *beGeneraterItemDataOne_GetMetaObject(void) {
    igMetaObject *g = g_beGeneraterItemDataOne_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false) {
        beGeneraterItemDataOne_EnsureRegistered();
    }
    return g_beGeneraterItemDataOne_metaObject;
}

int beGeneraterItemDataOne_GetVTable(void) {
    beGeneraterItemDataOne obj;
    int vtable;
    char **nameSlot;

    igObject_InitHeader(&obj);
    nameSlot = (char **)&obj._name;
    *nameSlot = 0;
    obj._vtable = (int)&g_igNamedObject_vtable[0];
    obj._vtable = (int)&g_beGeneraterItemDataOne_vtable[0];
    vtable = *(int *)((char *)&obj + *(int *)((char *)(g_objectSystem[0]) + 916));
    obj._vtable = (int)&g_igNamedObject_vtable[0];
    igStringRef_Release(nameSlot);
    return vtable;
}

void beGeneraterItemDataOne_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(beGeneraterItemDataOne_Register);
}

void *beGeneraterItemDataOne_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_beGeneraterItemDataOne_metaObject,
        igNamedObject_Register,
        igNamedObject_GetPublishedMetaObject,
        beGeneraterItemDataOne_GetMetaObjectFunction,
        "beGeneraterItemDataOne",
        0x18, /* instance size */
        beGeneraterItemDataOne_GetVTable,
        beGeneraterItemDataOne_InitFields,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void beGeneraterItemDataOne_GetMetaObjectFunction(void)
{
    beGeneraterItemDataOne_GetMetaObject();
}

static FieldFactory g_beGeneraterItemDataOne_ctorTable[] = {
    igIntMetaField_Create,
    igIntMetaField_Create,
    igIntMetaField_Create,
};
static const char *g_beGeneraterItemDataOne_fieldTable[] = {
    "_id",
    "_rank",
    "_rate",
};
static igMetaField **g_beGeneraterItemDataOne_fieldHandles[] = {
    &g_beGeneraterItemDataOne_idMetaField,
    &g_beGeneraterItemDataOne_rankMetaField,
    &g_beGeneraterItemDataOne_rateMetaField,
};
static int g_beGeneraterItemDataOne_fieldOffsets[] = {
    12,
    16,
    20,
};

void beGeneraterItemDataOne_InitFields(void) {
    int base;
    void *meta;

    meta = (void *)g_beGeneraterItemDataOne_metaObject;
    base = igMetaObject_GetFieldCount(meta);
    igMetaObject_CreateFields(meta, g_beGeneraterItemDataOne_ctorTable, 3);
    igMetaObject_NameFields(meta, g_beGeneraterItemDataOne_fieldTable, g_beGeneraterItemDataOne_fieldHandles, g_beGeneraterItemDataOne_fieldOffsets, base);
}

igMetaEnum *g_beGeneraterItemDataOne_msgActionMetaEnum;
static const char *g_beGeneraterItemDataOne_msgActionNames[] = {
    "START", "STOP", "STOPREVERS", "RESET",
    "RESTART", "PERFECTDROP", "ONFREEZE", "OFFREEZE",
};
static int g_beGeneraterItemDataOne_msgActionValues[] = {
    0, 1, 2, 3, 4, 5, 6, 7,
};

igMetaEnum *beGenerater_GetMsgActionEnum(void) {
    if (g_beGeneraterItemDataOne_msgActionMetaEnum == 0) {
        g_beGeneraterItemDataOne_msgActionMetaEnum = igMetaEnum_Create("MsgAction", g_beGeneraterItemDataOne_msgActionNames, g_beGeneraterItemDataOne_msgActionValues, 8);
    }
    return g_beGeneraterItemDataOne_msgActionMetaEnum;
}

