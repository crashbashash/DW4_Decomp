igMetaObject *g_beNDMWStatusCtrlFlag_metaObject;
igMetaField *g_beNDMWStatusCtrlFlag_impItemsMetaField;

void beNDMWStatusCtrlFlag_Create(int allocator) {
    beNDMWStatusCtrlFlag_EnsureRegistered();
    igMetaObject_CreateInstance(g_beNDMWStatusCtrlFlag_metaObject, allocator);
}

igMetaObject *beNDMWStatusCtrlFlag_GetMetaObject(void) {
    igMetaObject *g = g_beNDMWStatusCtrlFlag_metaObject;
    int t;
    if (!g || !(t = (g->_validity & 4) != 0))
        beNDMWStatusCtrlFlag_EnsureRegistered();
    return g_beNDMWStatusCtrlFlag_metaObject;
}

int beNDMWStatusCtrlFlag_GetVTable(void) {
    union U_3b9e40 u;
    int temp_s0;
    char *ps;

    igObject_InitHeader(u.b);
    *(int *)&u.b[52] = 0;
    *(int *)&u.b[56] = 0;
    *(int *)&u.b[60] = 0;
    *(int *)&u.b[64] = 0;
    *(int *)&u.b[68] = 0;
    *(int *)&u.b[72] = 0;
    *(int *)&u.b[76] = 0;
    u.vt = (int)&g_beNDMWStatusCtrlFlag_vtable[0];
    ps = &u.b[84];
    *(int *)ps = 0;
    temp_s0 = *(int *)&u.b[*(int *)((char *)(g_objectSystem[0]) + 916)];
    u.vt = (int)&g_beNDMWStatusCtrlFlag_vtable[0];
    igSmartPointer_igIntList_Destruct(ps, -1);
    beNDMWWindowCtrl_Destroy((beNDMWWindowCtrl *)u.b, (long long)0);
    return temp_s0;
}

void beNDMWStatusCtrlFlag_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(beNDMWStatusCtrlFlag_Register);
}

static igMetaObjectCallback g_beNDMWStatusCtrlFlag_callbackList[] = { igIntList_EnsureRegistered, 0 };

void *beNDMWStatusCtrlFlag_Register(void) {
    NdmwLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_beNDMWStatusCtrlFlag_metaObject,
        beNDMWWindowCtrl_Register,
        beNDMWWindowCtrl_GetPublishedMetaObject,
        beNDMWStatusCtrlFlag_GetMetaObjectFunction,
        "beNDMWStatusCtrlFlag",
        0x58, /* instance size */
        beNDMWStatusCtrlFlag_GetVTable,
        beNDMWStatusCtrlFlag_InitFields,
        0, /* extra callback item */
        g_beNDMWStatusCtrlFlag_callbackList /* callback list */
    );
}

void beNDMWStatusCtrlFlag_GetMetaObjectFunction(void)
{
    beNDMWStatusCtrlFlag_GetMetaObject();
}

static FieldFactory g_beNDMWStatusCtrlFlag_ctorTable[] = {
    igObjectRefMetaField_Create,
};
static const char *g_beNDMWStatusCtrlFlag_fieldTable[] = {
    "_impItems",
};
static igMetaField **g_beNDMWStatusCtrlFlag_fieldHandles[] = {
    &g_beNDMWStatusCtrlFlag_impItemsMetaField,
};
static int g_beNDMWStatusCtrlFlag_fieldOffsets[] = {
    84,
};

void beNDMWStatusCtrlFlag_InitFields(void) {
    int base;
    void *impItems;
    igMetaObject *meta;

    meta = g_beNDMWStatusCtrlFlag_metaObject;
    base = igMetaObject_GetFieldCount(meta);
    igMetaObject_CreateFields(meta, g_beNDMWStatusCtrlFlag_ctorTable, 1);
    impItems = (void *)(igMetaObject_GetFieldAt(meta, base));
    ((igObjectRefMetaField *)impItems)->_metaObject = igIntList_GetOrCreateMetaObject();
    ((igRefMetaField *)impItems)->_construct = 1;
    igMetaObject_NameFields(meta, g_beNDMWStatusCtrlFlag_fieldTable, g_beNDMWStatusCtrlFlag_fieldHandles, g_beNDMWStatusCtrlFlag_fieldOffsets, base);
}

