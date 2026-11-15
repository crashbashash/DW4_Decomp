igMetaObject *g_beWeaponAttachData_metaObject;
igMetaField *g_beWeaponAttachData_boneSelectListMetaField;
igMetaField *g_beWeaponAttachData_appearanceListListMetaField;

void FUN_0033fa80(int arg0) {
    FUN_0033fbf0();
    igMetaObject_CreateInstance(*(int *)0x587A80, arg0);
}

igMetaObject *FUN_0033fac0(void) {
    igMetaObject *g = g_beWeaponAttachData_metaObject;
    int t;
    if (!g || !(t = (g->_validity & 4) != 0))
        FUN_0033fbf0();
    return g_beWeaponAttachData_metaObject;
}

int beWeaponAttachData_GetVTable(void) {
    Obj_33fb10 obj;
    int r;

    igObject_InitHeader(&obj);
    obj.vt = &DAT_00539bb0[0];
    obj.m8 = 0;
    obj.m12 = 0;
    r = *(int *)((char *)&obj + *(int *)((char *)(g_objectSystem[0]) + 916));
    obj.vt = &DAT_00539bb0[0];
    obj.rel12();
    obj.rel8();
    return r;
}

void FUN_0033fbf0(void)
{
    igMetaObject_RunStaticInit(beWeaponAttachData_Register);
}

static igMetaObjectCallback g_beWeaponAttachData_callbackList[] = { FUN_0033ffe0, FUN_0033fe50, 0 };

void *beWeaponAttachData_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_beWeaponAttachData_metaObject,
        igObject_Register,
        igObject_GetMetaObject_ParentAccessor,
        beWeaponAttachData_GetMetaObject,
        "beWeaponAttachData",
        0x10, /* instance size */
        beWeaponAttachData_GetVTable,
        beWeaponAttachData_InitFields,
        0, /* extra callback item */
        g_beWeaponAttachData_callbackList /* callback list */
    );
}

void beWeaponAttachData_GetMetaObject(void)
{
    FUN_0033fac0();
}

static FieldFactory g_beWeaponAttachData_ctorTable[] = {
    igObjectRefMetaField_Create,
    igObjectRefMetaField_Create,
};
static const char *g_beWeaponAttachData_fieldTable[] = {
    "_boneSelectList",
    "_appearanceListList",
};
static igMetaField **g_beWeaponAttachData_fieldHandles[] = {
    &g_beWeaponAttachData_boneSelectListMetaField,
    &g_beWeaponAttachData_appearanceListListMetaField,
};
static int g_beWeaponAttachData_fieldOffsets[] = {
    8,
    12,
};

void beWeaponAttachData_InitFields(void) {
    int temp_s2;
    void *temp_s1_2;
    void *temp_s1;
    void *temp_s0;

    temp_s0 = (void *)g_beWeaponAttachData_metaObject;
    temp_s2 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, g_beWeaponAttachData_ctorTable, 2);
    temp_s1 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2));
    ((igObjectRefMetaField *)temp_s1)->_metaObject = (int)FUN_0033ff00();
    ((igRefMetaField *)temp_s1)->_construct = 1;
    temp_s1_2 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 1));
    ((igObjectRefMetaField *)temp_s1_2)->_metaObject = (int)FUN_0033fd70();
    ((igRefMetaField *)temp_s1_2)->_construct = 1;
    igMetaObject_NameFields(temp_s0, g_beWeaponAttachData_fieldTable, g_beWeaponAttachData_fieldHandles, g_beWeaponAttachData_fieldOffsets, temp_s2);
}

