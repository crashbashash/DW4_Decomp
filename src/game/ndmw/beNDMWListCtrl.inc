void *FUN_003bb400(void) {
    struct G *g = DAT_0058aff0[0];
    if (!g || ((g->f & 4) != 0) == false) {
        FUN_003bb450();
    }
    return DAT_0058aff0[0];
}

void FUN_003bb450(void)
{
    igMetaObject_RunStaticInit(beNDMWListCtrl_Register);
}

void *beNDMWListCtrl_Register(void) {
    NdmwLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        1, /* abstract */
        g_beNDMWListCtrl_metaObject,
        beNDMWWindowCtrl_Register,
        beNDMWWindowCtrl_GetPublishedMetaObject,
        beNDMWListCtrl_GetMetaObject,
        beNDMWListCtrl_className,
        0x60, /* instance size */
        0,
        beNDMWListCtrl_InitFields,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void beNDMWListCtrl_GetMetaObject(void)
{
    FUN_003bb400();
}

void beNDMWListCtrl_InitFields(void) {
    int temp_s1;
    void *temp_s0;

    temp_s0 = (void *)((int *)DAT_0058aff0)[0];
    temp_s1 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &DAT_004ca030[0], 3);
    igMetaObject_NameFields(temp_s0, &DAT_004ca040[0], &DAT_004ca050[0], &DAT_004ca060[0], temp_s1);
}

