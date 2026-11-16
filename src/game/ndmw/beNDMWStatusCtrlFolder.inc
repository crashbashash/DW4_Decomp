igMetaObject *g_beNDMWStatusCtrlFolder_metaObject;
igMetaField *g_beNDMWStatusCtrlFolder_folderMenuMetaField;

void beNDMWStatusCtrlFolder_Create(int allocator) {
    beNDMWStatusCtrlFolder_EnsureRegistered();
    igMetaObject_CreateInstance(g_beNDMWStatusCtrlFolder_metaObject, allocator);
}

igMetaObject *beNDMWStatusCtrlFolder_GetMetaObject(void) {
    igMetaObject *g = g_beNDMWStatusCtrlFolder_metaObject;
    if (g != 0) {
        int b = !!(g->_validity & 4);
        if (b) goto done;
    }
    beNDMWStatusCtrlFolder_EnsureRegistered();
done:
    return g_beNDMWStatusCtrlFolder_metaObject;
}

int beNDMWStatusCtrlFolder_GetVTable(void) {
    beNDMWStatusCtrlFolder obj;
    int vtable;

    igObject_InitHeader(&obj);
    obj._subWindow = 0;
    obj._mother = 0;
    obj._textCloseTypeList = 0;
    obj._textCloseNameList = 0;
    obj._modelCloseInfoNameList = 0;
    obj._modelCloseRamNoList = 0;
    obj._modelCloseSeqNameList = 0;
    *(int **)&obj._vtable = &g_beNDMWStatusCtrlFolder_vtable[0];
    vtable = *(int *)((char *)&obj + *(int *)((char *)(g_objectSystem[0]) + 916));
    *(int **)&obj._vtable = &g_beNDMWStatusCtrlFolder_vtable[0];
    beNDMWWindowCtrl_Destroy((beNDMWWindowCtrl *)&obj, (long long)0);
    return vtable;
}

void beNDMWStatusCtrlFolder_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(beNDMWStatusCtrlFolder_Register);
}

void *beNDMWStatusCtrlFolder_Register(void) {
    NdmwLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_beNDMWStatusCtrlFolder_metaObject,
        beNDMWWindowCtrl_Register,
        beNDMWWindowCtrl_GetPublishedMetaObject,
        beNDMWStatusCtrlFolder_GetMetaObjectFunction,
        "beNDMWStatusCtrlFolder",
        0x58, /* instance size */
        beNDMWStatusCtrlFolder_GetVTable,
        beNDMWStatusCtrlFolder_InitFields,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void beNDMWStatusCtrlFolder_GetMetaObjectFunction(void)
{
    beNDMWStatusCtrlFolder_GetMetaObject();
}

static FieldFactory g_beNDMWStatusCtrlFolder_ctorTable[] = {
    igIntMetaField_Create,
};
static const char *g_beNDMWStatusCtrlFolder_fieldTable[] = {
    "_folderMenu",
};
static igMetaField **g_beNDMWStatusCtrlFolder_fieldHandles[] = {
    &g_beNDMWStatusCtrlFolder_folderMenuMetaField,
};
static int g_beNDMWStatusCtrlFolder_fieldOffsets[] = {
    84,
};

void beNDMWStatusCtrlFolder_InitFields(void) {
    int base;
    igMetaObject *meta;

    meta = g_beNDMWStatusCtrlFolder_metaObject;
    base = igMetaObject_GetFieldCount(meta);
    igMetaObject_CreateFields(meta, g_beNDMWStatusCtrlFolder_ctorTable, 1);
    igMetaObject_NameFields(meta, g_beNDMWStatusCtrlFolder_fieldTable, g_beNDMWStatusCtrlFolder_fieldHandles, g_beNDMWStatusCtrlFolder_fieldOffsets, base);
}

