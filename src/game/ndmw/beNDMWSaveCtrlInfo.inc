igMetaObject *g_beNDMWSaveCtrlInfo_metaObject;

void *beNDMWSaveCtrlInfo_GetMetaObject(void) {
    unsigned char b;
    if (g_beNDMWSaveCtrlInfo_metaObject != 0) {
        b = (*(int *)((char *)(g_beNDMWSaveCtrlInfo_metaObject) + 36) & 4) != 0;
        if (b != 0) goto done;
    }
    beNDMWSaveCtrlInfo_EnsureRegistered();
done:
    return g_beNDMWSaveCtrlInfo_metaObject;
}

int beNDMWSaveCtrlInfo_GetVTable(void) {
    Obj_3bcf90 o;
    int r;

    igObject_InitHeader(&o);
    o.f8 = 0;
    o.f20 = 0;
    o.f24 = 0;
    o.vt = &g_beNDMWSaveCtrlInfo_vtable[0];
    r = *(int *)((char *)&o + *(int *)((char *)(g_objectSystem[0]) + 916));
    o.vt = &g_beNDMWSaveCtrlInfo_vtable[0];
    FUN_0033ec80(&o, 0);
    return r;
}

void beNDMWSaveCtrlInfo_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(beNDMWSaveCtrlInfo_Register);
}

void *beNDMWSaveCtrlInfo_Register(void) {
    NdmwLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_beNDMWSaveCtrlInfo_metaObject,
        beBaseInfo_Register,
        beBaseInfo_GetPublishedMetaObject,
        beNDMWSaveCtrlInfo_GetMetaObjectFunction,
        "beNDMWSaveCtrlInfo",
        0x1c, /* instance size */
        beNDMWSaveCtrlInfo_GetVTable,
        0,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void beNDMWSaveCtrlInfo_GetMetaObjectFunction(void)
{
    beNDMWSaveCtrlInfo_GetMetaObject();
}

