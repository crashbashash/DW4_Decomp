igMetaObject *g_beNDMWStatusCtrlEquip_metaObject;
igMetaField *g_beNDMWStatusCtrlEquip_equipMenuMetaField;

void beNDMWStatusCtrlEquip_Create(int allocator) {
    beNDMWStatusCtrlEquip_EnsureRegistered();
    igMetaObject_CreateInstance(g_beNDMWStatusCtrlEquip_metaObject, allocator);
}

void *beNDMWStatusCtrlEquip_GetMetaObject(void) {
    igMetaObject *g = g_beNDMWStatusCtrlEquip_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false) {
        beNDMWStatusCtrlEquip_EnsureRegistered();
    }
    return g_beNDMWStatusCtrlEquip_metaObject;
}

int beNDMWStatusCtrlEquip_GetVTable(void) {
    struct Obj_3bad70 o;
    int r;
    igObject_InitHeader(&o);
    o.f52 = 0;
    o.f56 = 0;
    o.f60 = 0;
    o.f64 = 0;
    o.f68 = 0;
    o.f72 = 0;
    o.f76 = 0;
    o.vt = &g_beNDMWStatusCtrlEquip_vtable[0];
    r = *(int *)((char *)&o + *(int *)((char *)(g_objectSystem[0]) + 916));
    o.vt = &g_beNDMWStatusCtrlEquip_vtable[0];
    
    beNDMWWindowCtrl_Destroy((beNDMWWindowCtrl *)&o, (long long)0);
    return r;
}

void beNDMWStatusCtrlEquip_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(beNDMWStatusCtrlEquip_Register);
}

void *beNDMWStatusCtrlEquip_Register(void) {
    NdmwLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_beNDMWStatusCtrlEquip_metaObject,
        beNDMWWindowCtrl_Register,
        beNDMWWindowCtrl_GetPublishedMetaObject,
        beNDMWStatusCtrlEquip_GetMetaObjectFunction,
        "beNDMWStatusCtrlEquip",
        0x58, /* instance size */
        beNDMWStatusCtrlEquip_GetVTable,
        beNDMWStatusCtrlEquip_InitFields,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void beNDMWStatusCtrlEquip_GetMetaObjectFunction(void)
{
    beNDMWStatusCtrlEquip_GetMetaObject();
}

static FieldFactory g_beNDMWStatusCtrlEquip_ctorTable[] = {
    igIntMetaField_Create,
};
static const char *g_beNDMWStatusCtrlEquip_fieldTable[] = {
    "_equipMenu",
};
static igMetaField **g_beNDMWStatusCtrlEquip_fieldHandles[] = {
    &g_beNDMWStatusCtrlEquip_equipMenuMetaField,
};
static int g_beNDMWStatusCtrlEquip_fieldOffsets[] = {
    84,
};

void beNDMWStatusCtrlEquip_InitFields(void) {
    int base;
    igMetaObject *meta;

    meta = g_beNDMWStatusCtrlEquip_metaObject;
    base = igMetaObject_GetFieldCount(meta);
    igMetaObject_CreateFields(meta, g_beNDMWStatusCtrlEquip_ctorTable, 1);
    igMetaObject_NameFields(meta, g_beNDMWStatusCtrlEquip_fieldTable, g_beNDMWStatusCtrlEquip_fieldHandles, g_beNDMWStatusCtrlEquip_fieldOffsets, base);
}

