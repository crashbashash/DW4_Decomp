igMetaObject *FUN_003b58b0(void) {
    if (g_beNDMWWindowSelect_metaObject[0] == 0 || !isValid(g_beNDMWWindowSelect_metaObject[0])) FUN_003b5900();
    return g_beNDMWWindowSelect_metaObject[0];
}

void FUN_003b5900(void)
{
    igMetaObject_RunStaticInit(beNDMWWindowSelect_Register);
}

void *beNDMWWindowSelect_Register(void) {
    NdmwLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        1, /* abstract */
        g_beNDMWWindowSelect_metaObject,
        beNDMWWindow_Register,
        beNDMWWindow_GetPublishedMetaObject,
        beNDMWWindowSelect_GetMetaObject,
        beNDMWWindowSelect_className,
        0x70, /* instance size */
        0,
        beNDMWWindowSelect_InitFields,
        0, /* extra callback item */
        g_beNDMWWindowSelect_callbackList /* callback list */
    );
}

void beNDMWWindowSelect_GetMetaObject(void)
{
    FUN_003b58b0();
}

void beNDMWWindowSelect_InitFields(void) {
    int temp_s2;
    void *temp_s1;
    void *temp_s0;

    temp_s0 = (void *)g_beNDMWWindowSelect_metaObject[0];
    temp_s2 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &g_beNDMWWindowSelect_ctorTable[0], 6);
    temp_s1 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 5));
    ((igObjectRefMetaField *)temp_s1)->_metaObject = FUN_002cb110();
    igMetaObject_NameFields(temp_s0, &g_beNDMWWindowSelect_fieldTable[0], &DAT_004c9800[0], &DAT_004c9820[0], temp_s2);
}

