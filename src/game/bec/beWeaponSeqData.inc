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
    Obj_33f1c0 obj;
    int r;

    igObject_InitHeader(&obj);
    obj.r1 = 0;
    obj.vt = &g_beWeaponSeqData_vtable[0];
    obj.r2 = 0;
    r = *(int *)((char *)&obj + *(int *)((char *)(g_objectSystem[0]) + 916));
    obj.vt = &g_beWeaponSeqData_vtable[0];
    obj.rel2();
    obj.vt = &g_igNamedObject_vtable[0];
    obj.rel1();
    return r;
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
    int temp_s1;
    void *temp_s0;

    temp_s0 = (void *)g_beWeaponSeqData_metaObject;
    temp_s1 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, g_beWeaponSeqData_ctorTable, 1);
    igMetaObject_NameFields(temp_s0, g_beWeaponSeqData_fieldTable, g_beWeaponSeqData_fieldHandles, g_beWeaponSeqData_fieldOffsets, temp_s1);
}

igMetaEnum *g_beWeaponSeqData_msgActionMetaEnum;
static const char *g_beWeaponSeqData_msgActionNames[] = {
    "GENERATE", "REMOVE", "GETINFONAME",
};
static int g_beWeaponSeqData_msgActionValues[] = {
    0, 1, 2,
};

igMetaEnum *FUN_0033f3b0(void) {
    if (g_beWeaponSeqData_msgActionMetaEnum == 0) {
        g_beWeaponSeqData_msgActionMetaEnum = igMetaEnum_Create("MsgAction", g_beWeaponSeqData_msgActionNames, g_beWeaponSeqData_msgActionValues, 3);
    }
    return g_beWeaponSeqData_msgActionMetaEnum;
}

