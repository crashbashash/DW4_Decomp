igMetaObject *g_beNDMWWindowTitle_metaObject;

igMetaObject *FUN_003b3e40(void) {
    if (g_beNDMWWindowTitle_metaObject == 0 || !isValid(g_beNDMWWindowTitle_metaObject)) FUN_003b3e90();
    return g_beNDMWWindowTitle_metaObject;
}

void FUN_003b3e90(void)
{
    igMetaObject_RunStaticInit(beNDMWWindowTitle_Register);
}

void *beNDMWWindowTitle_Register(void) {
    NdmwLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        1, /* abstract */
        &g_beNDMWWindowTitle_metaObject,
        beNDMWWindow_Register,
        beNDMWWindow_GetPublishedMetaObject,
        beNDMWWindowTitle_GetMetaObject,
        "beNDMWWindowTitle",
        0x50, /* instance size */
        0,
        0,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void beNDMWWindowTitle_GetMetaObject(void)
{
    FUN_003b3e40();
}

igMetaObject *FUN_003b3f30(void) {
    return g_beNDMWWindow_metaObject;
}

