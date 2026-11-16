igMetaObject *g_beNDMWShopSelect02_metaObject;
igMetaField *g_beNDMWShopSelect02_playerNoListMetaField;

void beNDMWShopSelect02_Create(int allocator) {
    beNDMWShopSelect02_EnsureRegistered();
    igMetaObject_CreateInstance(g_beNDMWShopSelect02_metaObject, allocator);
}

void *beNDMWShopSelect02_GetMetaObject(void) {
    igMetaObject *g = g_beNDMWShopSelect02_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false) {
        beNDMWShopSelect02_EnsureRegistered();
    }
    return g_beNDMWShopSelect02_metaObject;
}

int beNDMWShopSelect02_GetVTable(void) {
    struct Obj_3b4ba0 o;
    int r;
    igObject_InitHeader(&o);
    o.f52 = 0;
    o.f56 = 0;
    o.f60 = 0;
    o.f64 = 0;
    o.f68 = 0;
    o.f72 = 0;
    o.f76 = 0;
    o.f80 = 0;
    o.f108 = 0;
    o.vt = &g_beNDMWShopSelect02_vtable[0];
    o.f112 = 0;
    r = *(int *)((char *)&o + *(int *)((char *)(g_objectSystem[0]) + 916));
    o.vt = &g_beNDMWShopSelect02_vtable[0];
    igSmartPointer_igIntList_Destruct(&o.f112, -1);
    FUN_003b4050((struct S_3b4050 *)&o, (short)0);
    return r;
}

void beNDMWShopSelect02_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(beNDMWShopSelect02_Register);
}

static igMetaObjectCallback g_beNDMWShopSelect02_callbackList[] = { igIntList_EnsureRegistered, 0 };

void *beNDMWShopSelect02_Register(void) {
    NdmwLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_beNDMWShopSelect02_metaObject,
        beNDMWWindowSelect_Register,
        beNDMWWindowSelect_GetPublishedMetaObject,
        beNDMWShopSelect02_GetMetaObjectFunction,
        "beNDMWShopSelect02",
        0x74, /* instance size */
        beNDMWShopSelect02_GetVTable,
        beNDMWShopSelect02_InitFields,
        0, /* extra callback item */
        g_beNDMWShopSelect02_callbackList /* callback list */
    );
}

void beNDMWShopSelect02_GetMetaObjectFunction(void)
{
    beNDMWShopSelect02_GetMetaObject();
}

static FieldFactory g_beNDMWShopSelect02_ctorTable[] = {
    igObjectRefMetaField_Create,
};
static const char *g_beNDMWShopSelect02_fieldTable[] = {
    "_playerNoList",
};
static igMetaField **g_beNDMWShopSelect02_fieldHandles[] = {
    &g_beNDMWShopSelect02_playerNoListMetaField,
};
static int g_beNDMWShopSelect02_fieldOffsets[] = {
    112,
};

void beNDMWShopSelect02_InitFields(void) {
    int base;
    void *playerNoList;
    igMetaObject *meta;

    meta = g_beNDMWShopSelect02_metaObject;
    base = igMetaObject_GetFieldCount(meta);
    igMetaObject_CreateFields(meta, g_beNDMWShopSelect02_ctorTable, 1);
    playerNoList = (void *)(igMetaObject_GetFieldAt(meta, base));
    ((igObjectRefMetaField *)playerNoList)->_metaObject = igIntList_GetOrCreateMetaObject();
    ((igRefMetaField *)playerNoList)->_construct = 1;
    igMetaObject_NameFields(meta, g_beNDMWShopSelect02_fieldTable, g_beNDMWShopSelect02_fieldHandles, g_beNDMWShopSelect02_fieldOffsets, base);
}

