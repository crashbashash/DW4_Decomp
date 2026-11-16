igMetaObject *g_beWeaponSeqData_metaObject;
igMetaField *g_beWeaponSeqData_labelMetaField;

void *beWeaponSeqData_GetMetaObject(void) {
    igMetaObject *g = g_beWeaponSeqData_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false) {
        beWeaponSeqData_EnsureRegistered();
    }
    return g_beWeaponSeqData_metaObject;
}

int beWeaponSeqData_GetVTable(void) {
    beWeaponSeqData obj;
    int vtable;
    char **nameSlot;
    char **labelSlot;

    igObject_InitHeader(&obj);
    nameSlot = (char **)&obj._name;
    *nameSlot = 0;
    obj._vtable = (int)&g_beWeaponSeqData_vtable[0];
    labelSlot = (char **)&obj._label;
    *labelSlot = 0;
    vtable = *(int *)((char *)&obj + *(int *)((char *)(g_objectSystem[0]) + 916));
    obj._vtable = (int)&g_beWeaponSeqData_vtable[0];
    igStringRef_Release(labelSlot);
    obj._vtable = (int)&g_igNamedObject_vtable[0];
    igStringRef_Release(nameSlot);
    return vtable;
}

void beWeaponSeqData_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(beWeaponSeqData_Register);
}

void *beWeaponSeqData_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_beWeaponSeqData_metaObject,
        igNamedObject_Register,
        igNamedObject_GetPublishedMetaObject,
        beWeaponSeqData_GetMetaObjectFunction,
        "beWeaponSeqData",
        0x10, /* instance size */
        beWeaponSeqData_GetVTable,
        beWeaponSeqData_InitFields,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void beWeaponSeqData_GetMetaObjectFunction(void)
{
    beWeaponSeqData_GetMetaObject();
}

static FieldFactory g_beWeaponSeqData_ctorTable[] = {
    igStringMetaField_Create,
};
static const char *g_beWeaponSeqData_fieldTable[] = {
    "_label",
};
static igMetaField **g_beWeaponSeqData_fieldHandles[] = {
    &g_beWeaponSeqData_labelMetaField,
};
static int g_beWeaponSeqData_fieldOffsets[] = {
    12,
};

void beWeaponSeqData_InitFields(void) {
    int base;
    void *meta;

    meta = (void *)g_beWeaponSeqData_metaObject;
    base = igMetaObject_GetFieldCount(meta);
    igMetaObject_CreateFields(meta, g_beWeaponSeqData_ctorTable, 1);
    igMetaObject_NameFields(meta, g_beWeaponSeqData_fieldTable, g_beWeaponSeqData_fieldHandles, g_beWeaponSeqData_fieldOffsets, base);
}

igMetaEnum *g_beWeaponSeqData_msgActionMetaEnum;
static const char *g_beWeaponSeqData_msgActionNames[] = {
    "GENERATE", "REMOVE", "GETINFONAME",
};
static int g_beWeaponSeqData_msgActionValues[] = {
    0, 1, 2,
};

igMetaEnum *beWeaponSeqData_GetMsgActionEnum(void) {
    if (g_beWeaponSeqData_msgActionMetaEnum == 0) {
        g_beWeaponSeqData_msgActionMetaEnum = igMetaEnum_Create("MsgAction", g_beWeaponSeqData_msgActionNames, g_beWeaponSeqData_msgActionValues, 3);
    }
    return g_beWeaponSeqData_msgActionMetaEnum;
}

