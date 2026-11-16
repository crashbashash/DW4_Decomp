igMetaObject *g_beNDMWStatusCtrlSkill_metaObject;
igMetaField *g_beNDMWStatusCtrlSkill_skillMenuMetaField;
igMetaField *g_beNDMWStatusCtrlSkill_shinkaCtrlMetaField;
igMetaField *g_beNDMWStatusCtrlSkill_skillListMetaField;

void beNDMWStatusCtrlSkill_Create(int arg0) {
    beNDMWStatusCtrlSkill_EnsureRegistered();
    igMetaObject_CreateInstance(g_beNDMWStatusCtrlSkill_metaObject, arg0);
}

void *beNDMWStatusCtrlSkill_GetMetaObject(void) {
    igMetaObject *g = g_beNDMWStatusCtrlSkill_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false) {
        beNDMWStatusCtrlSkill_EnsureRegistered();
    }
    return g_beNDMWStatusCtrlSkill_metaObject;
}

int beNDMWStatusCtrlSkill_GetVTable(void) {
    union U_3b9340 u;
    int temp_s1;
    char *p1;

    igObject_InitHeader(u.b);
    *(int *)&u.b[52] = 0;
    *(int *)&u.b[56] = 0;
    *(int *)&u.b[60] = 0;
    *(int *)&u.b[64] = 0;
    *(int *)&u.b[68] = 0;
    *(int *)&u.b[72] = 0;
    *(int *)&u.b[76] = 0;
    u.vt = (int)&g_beNDMWStatusCtrlSkill_vtable[0];
    p1 = &u.b[100];
    *(int *)p1 = 0;
    *(int *)&u.b[104] = 0;
    temp_s1 = *(int *)&u.b[*(int *)((char *)(g_objectSystem[0]) + 916)];
    u.vt = (int)&g_beNDMWStatusCtrlSkill_vtable[0];
    igSmartPointer_igIntList_Destruct(&u.b[104], -1);
    FUN_003b8980((ObjectRefWord *)p1, -1);
    FUN_003b6770((int **)u.b, (long long)0);
    return temp_s1;
}

void beNDMWStatusCtrlSkill_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(beNDMWStatusCtrlSkill_Register);
}

static igMetaObjectCallback g_beNDMWStatusCtrlSkill_callbackList[] = { beNDMWShinkaCtrl_EnsureRegistered, igIntList_EnsureRegistered, 0 };

void *beNDMWStatusCtrlSkill_Register(void) {
    NdmwLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_beNDMWStatusCtrlSkill_metaObject,
        beNDMWListCtrl_Register,
        beNDMWListCtrl_GetPublishedMetaObject,
        beNDMWStatusCtrlSkill_GetMetaObjectFunction,
        "beNDMWStatusCtrlSkill",
        0x6c, /* instance size */
        beNDMWStatusCtrlSkill_GetVTable,
        beNDMWStatusCtrlSkill_InitFields,
        0, /* extra callback item */
        g_beNDMWStatusCtrlSkill_callbackList /* callback list */
    );
}

void beNDMWStatusCtrlSkill_GetMetaObjectFunction(void)
{
    beNDMWStatusCtrlSkill_GetMetaObject();
}

static FieldFactory g_beNDMWStatusCtrlSkill_ctorTable[] = {
    igIntMetaField_Create,
    igObjectRefMetaField_Create,
    igObjectRefMetaField_Create,
};
static const char *g_beNDMWStatusCtrlSkill_fieldTable[] = {
    "_skillMenu",
    "_shinkaCtrl",
    "_skillList",
};
static igMetaField **g_beNDMWStatusCtrlSkill_fieldHandles[] = {
    &g_beNDMWStatusCtrlSkill_skillMenuMetaField,
    &g_beNDMWStatusCtrlSkill_shinkaCtrlMetaField,
    &g_beNDMWStatusCtrlSkill_skillListMetaField,
};
static int g_beNDMWStatusCtrlSkill_fieldOffsets[] = {
    96,
    100,
    104,
};

void beNDMWStatusCtrlSkill_InitFields(void) {
    int temp_s2;
    void *temp_s1_2;
    void *temp_s1;
    igMetaObject *temp_s0;

    temp_s0 = g_beNDMWStatusCtrlSkill_metaObject;
    temp_s2 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, g_beNDMWStatusCtrlSkill_ctorTable, 3);
    temp_s1 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 1));
    ((igObjectRefMetaField *)temp_s1)->_metaObject = (int)beNDMWShinkaCtrl_GetOrCreateMetaObject();
    ((igRefMetaField *)temp_s1)->_construct = 1;
    temp_s1_2 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 2));
    ((igObjectRefMetaField *)temp_s1_2)->_metaObject = igIntList_GetOrCreateMetaObject();
    ((igRefMetaField *)temp_s1_2)->_construct = 1;
    igMetaObject_NameFields(temp_s0, g_beNDMWStatusCtrlSkill_fieldTable, g_beNDMWStatusCtrlSkill_fieldHandles, g_beNDMWStatusCtrlSkill_fieldOffsets, temp_s2);
}

