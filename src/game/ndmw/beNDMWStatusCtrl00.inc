igMetaObject *g_beNDMWStatusCtrl00_metaObject;
igMetaField *g_beNDMWStatusCtrl00_statusMenuMetaField;

void beNDMWStatusCtrl00_Create(int arg0) {
    FUN_003bb2e0();
    igMetaObject_CreateInstance(g_beNDMWStatusCtrl00_metaObject, arg0);
}

void *FUN_003bb210(void) {
    igMetaObject *g = g_beNDMWStatusCtrl00_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false) {
        FUN_003bb2e0();
    }
    return g_beNDMWStatusCtrl00_metaObject;
}

int beNDMWStatusCtrl00_GetVTable(void) {
    beNDMWStatusCtrl00 obj;
    int temp_s0;

    igObject_InitHeader(&obj);
    obj._subWindow = 0;
    obj._mother = 0;
    obj._textCloseTypeList = 0;
    obj._textCloseNameList = 0;
    obj._modelCloseInfoNameList = 0;
    obj._modelCloseRamNoList = 0;
    obj._modelCloseSeqNameList = 0;
    obj._vtable = (int)(&DAT_0053f260[0]);
    temp_s0 = *(int *)((char *)&obj + *(int *)((char *)(g_objectSystem[0]) + 916));
    obj._vtable = (int)(&DAT_0053f260[0]);
    beNDMWWindowCtrl_Destroy((beNDMWWindowCtrl *)&obj, (long long)0);
    return temp_s0;
}

void FUN_003bb2e0(void)
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
        beNDMWStatusCtrl00_GetMetaObject,
        "beNDMWStatusCtrl00",
        0x58, /* instance size */
        beNDMWStatusCtrl00_GetVTable,
        beNDMWStatusCtrl00_InitFields,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void beNDMWStatusCtrl00_GetMetaObject(void)
{
    FUN_003bb210();
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
    int temp_s1;
    igMetaObject *temp_s0;

    temp_s0 = g_beNDMWStatusCtrl00_metaObject;
    temp_s1 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, g_beNDMWStatusCtrl00_ctorTable, 1);
    igMetaObject_NameFields(temp_s0, g_beNDMWStatusCtrl00_fieldTable, g_beNDMWStatusCtrl00_fieldHandles, g_beNDMWStatusCtrl00_fieldOffsets, temp_s1);
}

