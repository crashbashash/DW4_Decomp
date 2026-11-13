igMetaObject *FUN_003bb570(void) {
    if (g_beNDMWWindowCtrl_metaObject[0] == 0) {
        g_beNDMWWindowCtrl_metaObject[0] = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData[0]));
    }
    return g_beNDMWWindowCtrl_metaObject[0];
}

void *FUN_003bb5c0(void) {
    igMetaObject *g = g_beNDMWWindowCtrl_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false) {
        FUN_003bb610();
    }
    return g_beNDMWWindowCtrl_metaObject[0];
}

void FUN_003bb610(void)
{
    igMetaObject_RunStaticInit(beNDMWWindowCtrl_Register);
}

void *beNDMWWindowCtrl_Register(void) {
    NdmwLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        1, /* abstract */
        ((igMetaObject_3bb630 * *)g_beNDMWWindowCtrl_metaObject),
        beNDMWWindow_Register,
        beNDMWWindow_GetPublishedMetaObject,
        beNDMWWindowCtrl_GetMetaObject,
        beNDMWWindowCtrl_className,
        0x54, /* instance size */
        0,
        beNDMWWindowCtrl_InitFields,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void beNDMWWindowCtrl_GetMetaObject(void)
{
    FUN_003bb5c0();
}

void beNDMWWindowCtrl_InitFields(void) {
    int temp_s1;
    void *temp_s0;

    temp_s0 = (void *)g_beNDMWWindowCtrl_metaObject[0];
    temp_s1 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &g_beNDMWWindowCtrl_ctorTable[0], 1);
    igMetaObject_NameFields(temp_s0, &g_beNDMWWindowCtrl_fieldTable[0], &DAT_004ca080[0], &DAT_004ca088[0], temp_s1);
}

int StatusMessage_GetMetaEnum(void) {
    if (DAT_0058b020[0] == 0) {
        DAT_0058b020[0] = igMetaEnum_Create(Message, &DAT_004ca090[0], &DAT_004ca0b0[0], 7);
    }
    return DAT_0058b020[0];
}

