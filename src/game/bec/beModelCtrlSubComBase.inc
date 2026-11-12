void *FUN_0034fb70(void) {
    igMetaObject *g = g_beModelCtrlSubComBase_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false) {
        FUN_0034fbc0();
    }
    return g_beModelCtrlSubComBase_metaObject[0];
}

void FUN_0034fbc0(void)
{
    igMetaObject_RunStaticInit(beModelCtrlSubComBase_Register);
}

void *beModelCtrlSubComBase_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        1, /* abstract */
        g_beModelCtrlSubComBase_metaObject,
        igObject_Register,
        igObject_GetMetaObject_ParentAccessor,
        beModelCtrlSubComBase_GetMetaObject,
        beModelCtrlSubComBase_className,
        0x14, /* instance size */
        0,
        beModelCtrlSubComBase_InitFields,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void beModelCtrlSubComBase_GetMetaObject(void)
{
    FUN_0034fb70();
}

void beModelCtrlSubComBase_InitFields(void) {
    int temp_s1;
    void *temp_s0;

    temp_s0 = (void *)g_beModelCtrlSubComBase_metaObject[0];
    temp_s1 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &DAT_004c4d00[0], 3);
    FUN_002e3810((void *)(((int)igMetaObject_GetFieldAt(temp_s0, temp_s1 + 1))), 0.0f);
    igMetaObject_NameFields(temp_s0, &DAT_004c4d10[0], &DAT_004c4d20[0], &DAT_004c4d30[0], temp_s1);
}

