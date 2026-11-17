igMetaObject *g_igCreateCollisionDatabase_metaObject;
igMetaField *g_igCreateCollisionDatabase_gridTypeMetaField;
igMetaField *g_igCreateCollisionDatabase_staticGroupTypeMetaField;
igMetaField *g_igCreateCollisionDatabase_sizeXMetaField;
igMetaField *g_igCreateCollisionDatabase_sizeYMetaField;
igMetaField *g_igCreateCollisionDatabase_sizeZMetaField;
igMetaField *g_igCreateCollisionDatabase_fileNameMetaField;
igMetaField *g_igCreateCollisionDatabase_gridMetaField;

igMetaObject *igCreateCollisionDatabase_GetMetaObject(void)
{
    igMetaObject *g = g_igCreateCollisionDatabase_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_002395b0();
    return g_igCreateCollisionDatabase_metaObject;
}

int igCreateCollisionDatabase_GetVTable(void) {
    struct W o;
    int *p18;
    int *p17;
    int *p16;
    int r;
    igObject_InitHeader((igObject *)&o);
    o.f[7] = 0;
    o.f[8] = 0;
    o.vt = &g_igCreateCollisionDatabase_vtable[0];
    p16 = &o.f[12];
    *p16 = 0;
    p17 = &o.f[13];
    *p17 = 0;
    p18 = &o.f[14];
    *p18 = 0;
    o.f[15] = 0;
    r = *(int *)((char *)&o + *(int *)((char *)(g_objectSystem) + 916));
    o.vt = &g_igCreateCollisionDatabase_vtable[0];
    igSmartPointer_igMetaObject_Destruct(&o.f[15], -1);
    igSmartPointer_igMetaObject_Destruct(p18, -1);
    FUN_00239530((O *)p17, -1);
    igStringRef_Destruct(p16, -1);
    FUN_00225790(&o, 0);
    return r;
}

O *FUN_00239530(O *arg0, short arg1) {
    if (arg0) {
        S_temp_a0 *t = arg0->m;
        if (t) { t->f4 -= 1; if ((t->f4 & 0x7fffff) == 0) igObject_Destroy(t); }
        if (arg1 > 0) operator delete(arg0);
    }
    return arg0;
}

void FUN_002395b0(void)
{
    igMetaObject_RunStaticInit(igCreateCollisionDatabase_Register);
}

static igMetaObjectCallback g_igCreateCollisionDatabase_callbackList[] = { igMetaObject_EnsureRegistered, FUN_0023a340, 0 };

CallbackArray *igCreateCollisionDatabase_Register(void) {
    CollisionLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_igCreateCollisionDatabase_metaObject,
        igOptBase_Register,
        igOptBase_GetPublishedMetaObject,
        thunk_igCreateCollisionDatabase_GetMetaObject,
        "igCreateCollisionDatabase",
        0x44, /* instance size */
        igCreateCollisionDatabase_GetVTable,
        &igCreateCollisionDatabase_InitFields,
        0, /* extra callback item */
        g_igCreateCollisionDatabase_callbackList /* callback list */
    );
}

void thunk_igCreateCollisionDatabase_GetMetaObject(void) {
    igCreateCollisionDatabase_GetMetaObject();
}

static FieldFactory g_igCreateCollisionDatabase_ctorTable[] = {
    igObjectRefMetaField_Create,
    igObjectRefMetaField_Create,
    igIntMetaField_Create,
    igIntMetaField_Create,
    igIntMetaField_Create,
    igStringMetaField_Create,
    igObjectRefMetaField_Create,
};
static const char *g_igCreateCollisionDatabase_fieldTable[] = {
    "_gridType",
    "_staticGroupType",
    "_sizeX",
    "_sizeY",
    "_sizeZ",
    "_fileName",
    "_grid",
};
static igMetaField **g_igCreateCollisionDatabase_fieldHandles[] = {
    &g_igCreateCollisionDatabase_gridTypeMetaField,
    &g_igCreateCollisionDatabase_staticGroupTypeMetaField,
    &g_igCreateCollisionDatabase_sizeXMetaField,
    &g_igCreateCollisionDatabase_sizeYMetaField,
    &g_igCreateCollisionDatabase_sizeZMetaField,
    &g_igCreateCollisionDatabase_fileNameMetaField,
    &g_igCreateCollisionDatabase_gridMetaField,
};
static int g_igCreateCollisionDatabase_fieldOffsets[] = {
    60,
    64,
    40,
    44,
    48,
    52,
    56,
};

void igCreateCollisionDatabase_InitFields(void) {
    int temp_s2;
    void *temp_s1_3;
    void *temp_s1_2;
    void *temp_s1;
    igMetaObject *temp_s0;

    temp_s0 = g_igCreateCollisionDatabase_metaObject;
    temp_s2 = igMetaObject_GetFieldCount((igMetaObject *)temp_s0);
    igMetaObject_CreateFields((igMetaObject *)temp_s0, g_igCreateCollisionDatabase_ctorTable, 7);
    temp_s1 = (void *)(igMetaObject_GetFieldAt((igMetaObject *)temp_s0, temp_s2));
    ((igObjectRefMetaField *)temp_s1)->_metaObject = (int)(igMetaObject_GetOrCreateMetaObject());
    igObjectRefMetaField_SetDefault(temp_s1, igCollisionGrid_GetMetaObject());
    temp_s1_2 = (void *)(igMetaObject_GetFieldAt((igMetaObject *)temp_s0, temp_s2 + 1));
    ((igObjectRefMetaField *)temp_s1_2)->_metaObject = (int)(igMetaObject_GetOrCreateMetaObject());
    igObjectRefMetaField_SetDefault(temp_s1_2, igCollisionGroup_GetMetaObject());
    igIntMetaField_SetDefault(igMetaObject_GetFieldAt((igMetaObject *)temp_s0, temp_s2 + 2), 1);
    igIntMetaField_SetDefault(igMetaObject_GetFieldAt((igMetaObject *)temp_s0, temp_s2 + 3), 1);
    igIntMetaField_SetDefault(igMetaObject_GetFieldAt((igMetaObject *)temp_s0, temp_s2 + 4), 1);
    igStringMetaField_SetDefaultText(igMetaObject_GetFieldAt((igMetaObject *)temp_s0, temp_s2 + 5), 0);
    temp_s1_3 = (void *)(igMetaObject_GetFieldAt((igMetaObject *)temp_s0, temp_s2 + 6));
    ((igObjectRefMetaField *)temp_s1_3)->_metaObject = (int)FUN_0023a080();
    ((igMetaField *)temp_s1_3)->_persistent = 0;
    igMetaObject_NameFields((igMetaObject *)temp_s0, g_igCreateCollisionDatabase_fieldTable, g_igCreateCollisionDatabase_fieldHandles, g_igCreateCollisionDatabase_fieldOffsets, temp_s2);
}

