igMetaObject *g_beNDMWShopCtrl40_metaObject;
igMetaField *g_beNDMWShopCtrl40_selectCursorMetaField;

void beNDMWShopCtrl40_Create(int arg0) {
    beNDMWShopCtrl40_EnsureRegistered();
    igMetaObject_CreateInstance(g_beNDMWShopCtrl40_metaObject, arg0);
}

void *beNDMWShopCtrl40_GetMetaObject(void) {
    bool ok;
    if (g_beNDMWShopCtrl40_metaObject == 0) goto make;
    ok = !!(g_beNDMWShopCtrl40_metaObject->_validity & 4);
    if (ok != false) goto done;
make:
    beNDMWShopCtrl40_EnsureRegistered();
done:;
    return g_beNDMWShopCtrl40_metaObject;
}

int beNDMWShopCtrl40_GetVTable(void) {
    union U_3b8490 u;
    int t;

    igObject_InitHeader(u.b);
    *(int *)&u.b[52] = 0;
    *(int *)&u.b[56] = 0;
    *(int *)&u.b[60] = 0;
    *(int *)&u.b[64] = 0;
    *(int *)&u.b[68] = 0;
    *(int *)&u.b[72] = 0;
    *(int *)&u.b[76] = 0;
    u.vt = (int)&g_beNDMWShopCtrl40_vtable[0];
    t = *(int *)&u.b[*(int *)((char *)(g_objectSystem[0]) + 916)];
    u.vt = (int)&g_beNDMWShopCtrl40_vtable[0];
    beNDMWWindowCtrl_Destroy((beNDMWWindowCtrl *)u.b, (long long)0);
    return t;
}

void beNDMWShopCtrl40_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(beNDMWShopCtrl40_Register);
}

void *beNDMWShopCtrl40_Register(void) {
    NdmwLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_beNDMWShopCtrl40_metaObject,
        beNDMWWindowCtrl_Register,
        beNDMWWindowCtrl_GetPublishedMetaObject,
        beNDMWShopCtrl40_GetMetaObjectFunction,
        "beNDMWShopCtrl40",
        0x58, /* instance size */
        beNDMWShopCtrl40_GetVTable,
        beNDMWShopCtrl40_InitFields,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void beNDMWShopCtrl40_GetMetaObjectFunction(void)
{
    beNDMWShopCtrl40_GetMetaObject();
}

static FieldFactory g_beNDMWShopCtrl40_ctorTable[] = {
    igIntMetaField_Create,
};
static const char *g_beNDMWShopCtrl40_fieldTable[] = {
    "_selectCursor",
};
static igMetaField **g_beNDMWShopCtrl40_fieldHandles[] = {
    &g_beNDMWShopCtrl40_selectCursorMetaField,
};
static int g_beNDMWShopCtrl40_fieldOffsets[] = {
    84,
};

void beNDMWShopCtrl40_InitFields(void) {
    int temp_s1;
    igMetaObject *temp_s0;

    temp_s0 = g_beNDMWShopCtrl40_metaObject;
    temp_s1 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, g_beNDMWShopCtrl40_ctorTable, 1);
    igMetaObject_NameFields(temp_s0, g_beNDMWShopCtrl40_fieldTable, g_beNDMWShopCtrl40_fieldHandles, g_beNDMWShopCtrl40_fieldOffsets, temp_s1);
}

