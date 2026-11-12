void *beNDMWMdlPEBase_ResolveMetaObject(void) {
    igMetaObject *g = g_beNDMWMdlPEBase_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false) {
        FUN_003c0550();
    }
    return g_beNDMWMdlPEBase_metaObject[0];
}

void FUN_003c0550(void)
{
    igMetaObject_RunStaticInit(beNDMWMdlPEBase_Register);
}

void *beNDMWMdlPEBase_Register(void) {
    NdmwLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        1, /* abstract */
        g_beNDMWMdlPEBase_metaObject,
        beModelCtrl_Register,
        beModelCtrl_GetPublishedMetaObject,
        beNDMWMdlPEBase_GetMetaObject,
        beNDMWMdlPEBase_className,
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

