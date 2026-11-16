igMetaObject *g_beNDMWStatusCtrl00_metaObject;
igMetaField *g_beNDMWStatusCtrl00_statusMenuMetaField;

void beNDMWStatusCtrl00_Create(int allocator) {
    beNDMWStatusCtrl00_EnsureRegistered();
    igMetaObject_CreateInstance(g_beNDMWStatusCtrl00_metaObject, allocator);
}

void *beNDMWStatusCtrl00_GetMetaObject(void) {
    igMetaObject *g = g_beNDMWStatusCtrl00_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false) {
        beNDMWStatusCtrl00_EnsureRegistered();
    }
    return g_beNDMWStatusCtrl00_metaObject;
}

int beNDMWStatusCtrl00_GetVTable(void) {
    beNDMWStatusCtrl00 obj;
    int vtable;

    igObject_InitHeader(&obj);
    obj._subWindow = 0;
    obj._mother = 0;
    obj._textCloseTypeList = 0;
    obj._textCloseNameList = 0;
    obj._modelCloseInfoNameList = 0;
    obj._modelCloseRamNoList = 0;
    obj._modelCloseSeqNameList = 0;
    obj._vtable = (int)(&g_beNDMWStatusCtrl00_vtable[0]);
    vtable = *(int *)((char *)&obj + *(int *)((char *)(g_objectSystem[0]) + 916));
    obj._vtable = (int)(&g_beNDMWStatusCtrl00_vtable[0]);
    beNDMWWindowCtrl_Destroy((beNDMWWindowCtrl *)&obj, (long long)0);
    return vtable;
}

void beNDMWStatusCtrl00_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(beNDMWStatusCtrl00_Register);
}

void *beNDMWStatusCtrl00_Register(void) {
    NdmwLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_beNDMWStatusCtrl00_metaObject,
        beNDMWWindowCtrl_Register,
        beNDMWWindowCtrl_GetPublishedMetaObject,
        beNDMWStatusCtrl00_GetMetaObjectFunction,
        "beNDMWStatusCtrl00",
        0x58, /* instance size */
        beNDMWStatusCtrl00_GetVTable,
        beNDMWStatusCtrl00_InitFields,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void beNDMWStatusCtrl00_GetMetaObjectFunction(void)
{
    beNDMWStatusCtrl00_GetMetaObject();
}

static FieldFactory g_beNDMWStatusCtrl00_ctorTable[] = {
    igIntMetaField_Create,
};
static const char *g_beNDMWStatusCtrl00_fieldTable[] = {
    "_statusMenu",
};
static igMetaField **g_beNDMWStatusCtrl00_fieldHandles[] = {
    &g_beNDMWStatusCtrl00_statusMenuMetaField,
};
static int g_beNDMWStatusCtrl00_fieldOffsets[] = {
    84,
};

void beNDMWStatusCtrl00_InitFields(void) {
    int base;
    igMetaObject *meta;

    meta = g_beNDMWStatusCtrl00_metaObject;
    base = igMetaObject_GetFieldCount(meta);
    igMetaObject_CreateFields(meta, g_beNDMWStatusCtrl00_ctorTable, 1);
    igMetaObject_NameFields(meta, g_beNDMWStatusCtrl00_fieldTable, g_beNDMWStatusCtrl00_fieldHandles, g_beNDMWStatusCtrl00_fieldOffsets, base);
}

