igMetaObject *g_beNDMWShopSelect00_metaObject;
igMetaField *g_beNDMWShopSelect00_panelNameMetaField;

void beNDMWShopSelect00_Create(int arg0) {
    beNDMWShopSelect00_EnsureRegistered();
    igMetaObject_CreateInstance(g_beNDMWShopSelect00_metaObject, arg0);
}

void *beNDMWShopSelect00_GetMetaObject(void) {
    igMetaObject *g = g_beNDMWShopSelect00_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false) {
        beNDMWShopSelect00_EnsureRegistered();
    }
    return g_beNDMWShopSelect00_metaObject;
}

int beNDMWShopSelect00_GetVTable(void) {
    struct Obj_3b4fe0 obj;
    int temp_s0;

    igObject_InitHeader(&obj);
    obj.f34 = 0;
    obj.f38 = 0;
    obj.f3C = 0;
    obj.f40 = 0;
    obj.f44 = 0;
    obj.f48 = 0;
    obj.f4C = 0;
    obj.f50 = 0;
    obj.f6C = 0;
    obj.vt = (&g_beNDMWShopSelect00_vtable[0]);
    obj.f70 = 0;
    temp_s0 = *(int *)((char *)&obj + *(int *)((char *)(g_objectSystem[0]) + 916));
    obj.vt = (&g_beNDMWShopSelect00_vtable[0]);
    igStringRef_Destruct(&obj.f70, -1);
    FUN_003b4050((struct S_3b4050 *)&obj, (short)0);
    return temp_s0;
}

void beNDMWShopSelect00_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(beNDMWShopSelect00_Register);
}

void *beNDMWShopSelect00_Register(void) {
    NdmwLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_beNDMWShopSelect00_metaObject,
        beNDMWWindowSelect_Register,
        beNDMWWindowSelect_GetPublishedMetaObject,
        beNDMWShopSelect00_GetMetaObjectFunction,
        "beNDMWShopSelect00",
        0x74, /* instance size */
        beNDMWShopSelect00_GetVTable,
        beNDMWShopSelect00_InitFields,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void beNDMWShopSelect00_GetMetaObjectFunction(void)
{
    beNDMWShopSelect00_GetMetaObject();
}

static FieldFactory g_beNDMWShopSelect00_ctorTable[] = {
    igStringMetaField_Create,
};
static const char *g_beNDMWShopSelect00_fieldTable[] = {
    "_panelName",
};
static igMetaField **g_beNDMWShopSelect00_fieldHandles[] = {
    &g_beNDMWShopSelect00_panelNameMetaField,
};
static int g_beNDMWShopSelect00_fieldOffsets[] = {
    112,
};

void beNDMWShopSelect00_InitFields(void) {
    int temp_s1;
    igMetaObject *temp_s0;

    temp_s0 = g_beNDMWShopSelect00_metaObject;
    temp_s1 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, g_beNDMWShopSelect00_ctorTable, 1);
    igStringMetaField_SetDefaultText(((int)igMetaObject_GetFieldAt(temp_s0, temp_s1)), 0);
    igMetaObject_NameFields(temp_s0, g_beNDMWShopSelect00_fieldTable, g_beNDMWShopSelect00_fieldHandles, g_beNDMWShopSelect00_fieldOffsets, temp_s1);
}

