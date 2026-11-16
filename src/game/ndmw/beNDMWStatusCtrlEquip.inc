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
    beNDMWStatusCtrlEquip obj;
    int vtable;

    igObject_InitHeader(&obj);
    obj._subWindow = 0;
    obj._mother = 0;
    obj._textCloseTypeList = 0;
    obj._textCloseNameList = 0;
    obj._modelCloseInfoNameList = 0;
    obj._modelCloseRamNoList = 0;
    obj._modelCloseSeqNameList = 0;
    *(int **)&obj._vtable = &g_beNDMWStatusCtrlEquip_vtable[0];
    vtable = *(int *)((char *)&obj + *(int *)((char *)(g_objectSystem[0]) + 916));
    *(int **)&obj._vtable = &g_beNDMWStatusCtrlEquip_vtable[0];
    beNDMWWindowCtrl_Destroy((beNDMWWindowCtrl *)&obj, (long long)0);
    return vtable;
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

