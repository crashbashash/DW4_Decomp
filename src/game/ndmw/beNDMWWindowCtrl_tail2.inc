int FUN_003bb570(void) {
    if (((int *)DAT_0058b010)[0] == 0) {
        ((int *)DAT_0058b010)[0] = igMetaObject_Create(Memory_GetAllocatorBySelector(DAT_00587040[0]));
    }
    return ((int *)DAT_0058b010)[0];
}

void *FUN_003bb5c0(void) {
    struct G *g = DAT_0058b010[0];
    if (!g || ((g->f & 4) != 0) == false) {
        FUN_003bb610();
    }
    return DAT_0058b010[0];
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

    temp_s0 = (void *)((int *)DAT_0058b010)[0];
    temp_s1 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &DAT_004ca070[0], 1);
    igMetaObject_NameFields(temp_s0, &DAT_004ca078[0], &DAT_004ca080[0], &DAT_004ca088[0], temp_s1);
}

int FUN_003bb730(void) {
    if (DAT_0058b020[0] == 0) {
        DAT_0058b020[0] = igMetaEnum_Create(&DAT_00510d58[0], &DAT_004ca090[0], &DAT_004ca0b0[0], 7);
    }
    return DAT_0058b020[0];
}

