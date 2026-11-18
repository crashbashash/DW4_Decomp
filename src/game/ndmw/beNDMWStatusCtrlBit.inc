igMetaObject *g_beNDMWStatusCtrlBit_metaObject;
igMetaField *g_beNDMWStatusCtrlBit_playerNoListMetaField;

beNDMWStatusCtrlBit *beNDMWStatusCtrlBit_Create(int allocator) {
    beNDMWStatusCtrlBit_EnsureRegistered();
    return (beNDMWStatusCtrlBit *)igMetaObject_CreateInstance(g_beNDMWStatusCtrlBit_metaObject, (igMemoryPoolView *)allocator);
}

void *beNDMWStatusCtrlBit_GetMetaObject(void) {
    igMetaObject *g = g_beNDMWStatusCtrlBit_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false) {
        beNDMWStatusCtrlBit_EnsureRegistered();
    }
    return g_beNDMWStatusCtrlBit_metaObject;
}

int beNDMWStatusCtrlBit_GetVTable(void) {
    beNDMWStatusCtrlBit obj;
    int vtable;

    igObject_InitHeader(&obj);
    obj._subWindow = 0;
    obj._mother = 0;
    obj._textCloseTypeList = 0;
    obj._textCloseNameList = 0;
    obj._modelCloseInfoNameList = 0;
    obj._modelCloseRamNoList = 0;
    obj._modelCloseSeqNameList = 0;
    *(int **)&obj._vtable = &g_beNDMWStatusCtrlBit_vtable[0];
    obj._playerNoList = 0;
    vtable = *(int *)((char *)&obj + g_objectSystem->vtableProbeOffset);
    *(int **)&obj._vtable = &g_beNDMWStatusCtrlBit_vtable[0];
    igSmartPointer_igIntList_Destruct((igSmartPointer<igObject> *)&obj._playerNoList, -1);
    beNDMWWindowCtrl_Destroy((beNDMWWindowCtrl *)&obj, (long long)0);
    return vtable;
}

void beNDMWStatusCtrlBit_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(beNDMWStatusCtrlBit_Register);
}

static igMetaObjectCallback g_beNDMWStatusCtrlBit_callbackList[] = { igIntList_EnsureRegistered, 0 };

CallbackArray *beNDMWStatusCtrlBit_Register(void) {
    NdmwLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_beNDMWStatusCtrlBit_metaObject,
        beNDMWWindowCtrl_Register,
        beNDMWWindowCtrl_GetPublishedMetaObject,
        beNDMWStatusCtrlBit_GetMetaObjectFunction,
        "beNDMWStatusCtrlBit",
        0x58, /* instance size */
        beNDMWStatusCtrlBit_GetVTable,
        beNDMWStatusCtrlBit_InitFields,
        0, /* extra callback item */
        g_beNDMWStatusCtrlBit_callbackList /* callback list */
    );
}

void beNDMWStatusCtrlBit_GetMetaObjectFunction(void)
{
    beNDMWStatusCtrlBit_GetMetaObject();
}

static FieldFactory g_beNDMWStatusCtrlBit_ctorTable[] = {
    igObjectRefMetaField_Create,
};
static const char *g_beNDMWStatusCtrlBit_fieldTable[] = {
    "_playerNoList",
};
static igMetaField **g_beNDMWStatusCtrlBit_fieldHandles[] = {
    &g_beNDMWStatusCtrlBit_playerNoListMetaField,
};
static int g_beNDMWStatusCtrlBit_fieldOffsets[] = {
    84,
};

void beNDMWStatusCtrlBit_InitFields(void) {
    int base;
    void *playerNoList;
    igMetaObject *meta;

    meta = g_beNDMWStatusCtrlBit_metaObject;
    base = igMetaObject_GetFieldCount(meta);
    igMetaObject_CreateFields(meta, g_beNDMWStatusCtrlBit_ctorTable, 1);
    playerNoList = (void *)(igMetaObject_GetFieldAt(meta, base));
    ((igObjectRefMetaField *)playerNoList)->_metaObject = igIntList_GetOrCreateMetaObject();
    ((igRefMetaField *)playerNoList)->_construct = 1;
    igMetaObject_NameFields(meta, g_beNDMWStatusCtrlBit_fieldTable, g_beNDMWStatusCtrlBit_fieldHandles, g_beNDMWStatusCtrlBit_fieldOffsets, base);
}

