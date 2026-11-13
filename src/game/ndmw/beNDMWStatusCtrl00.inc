void beNDMWStatusCtrl00_Create(int arg0) {
    FUN_003bb2e0();
    igMetaObject_CreateInstance(*(int *)0x58AFE0, arg0);
}

void *FUN_003bb210(void) {
    igMetaObject *g = g_beNDMWStatusCtrl00_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false) {
        FUN_003bb2e0();
    }
    return g_beNDMWStatusCtrl00_metaObject[0];
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
        g_beNDMWStatusCtrl00_metaObject,
        beNDMWWindowCtrl_Register,
        beNDMWWindowCtrl_GetPublishedMetaObject,
        beNDMWStatusCtrl00_GetMetaObject,
        beNDMWStatusCtrl00_className,
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

void beNDMWStatusCtrl00_InitFields(void) {
    int temp_s1;
    void *temp_s0;

    temp_s0 = (void *)g_beNDMWStatusCtrl00_metaObject[0];
    temp_s1 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &DAT_004ca010[0], 1);
    igMetaObject_NameFields(temp_s0, &DAT_004ca018[0], &DAT_004ca020[0], &DAT_004ca028[0], temp_s1);
}

