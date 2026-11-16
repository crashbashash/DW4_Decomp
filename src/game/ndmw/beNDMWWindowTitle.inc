igMetaObject *g_beNDMWWindowTitle_metaObject;

igMetaObject *beNDMWWindowTitle_GetMetaObject(void) {
    if (g_beNDMWWindowTitle_metaObject == 0 || !isValid(g_beNDMWWindowTitle_metaObject)) beNDMWWindowTitle_EnsureRegistered();
    return g_beNDMWWindowTitle_metaObject;
}

void beNDMWWindowTitle_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(beNDMWWindowTitle_Register);
}

CallbackArray *beNDMWWindowTitle_Register(void) {
    NdmwLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        1, /* abstract */
        &g_beNDMWWindowTitle_metaObject,
        beNDMWWindow_Register,
        beNDMWWindow_GetPublishedMetaObject,
        beNDMWWindowTitle_GetMetaObjectFunction,
        "beNDMWWindowTitle",
        0x50, /* instance size */
        0,
        0,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void beNDMWWindowTitle_GetMetaObjectFunction(void)
{
    beNDMWWindowTitle_GetMetaObject();
}

igMetaObject *beNDMWWindow_GetPublishedMetaObject(void) {
    return g_beNDMWWindow_metaObject;
}

