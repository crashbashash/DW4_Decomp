igMetaObject *g_beNDMWMdlPEBase_metaObject;

void *beNDMWMdlPEBase_ResolveMetaObject(void) {
    igMetaObject *g = g_beNDMWMdlPEBase_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false) {
        beNDMWMdlPEBase_EnsureRegistered();
    }
    return g_beNDMWMdlPEBase_metaObject;
}

void beNDMWMdlPEBase_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(beNDMWMdlPEBase_Register);
}

void *beNDMWMdlPEBase_Register(void) {
    NdmwLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        1, /* abstract */
        &g_beNDMWMdlPEBase_metaObject,
        beModelCtrl_Register,
        beModelCtrl_GetPublishedMetaObject,
        beNDMWMdlPEBase_GetMetaObject,
        "beNDMWMdlPEBase",
        0x2c, /* instance size */
        0,
        0,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void beNDMWMdlPEBase_GetMetaObject(void)
{
    beNDMWMdlPEBase_ResolveMetaObject();
}

