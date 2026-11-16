igMetaObject *g_beNDMWTitle2Info_metaObject;

void *beNDMWTitle2Info_GetMetaObject(void) {
    igMetaObject *g = g_beNDMWTitle2Info_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false) {
        beNDMWTitle2Info_EnsureRegistered();
    }
    return g_beNDMWTitle2Info_metaObject;
}

int beNDMWTitle2Info_GetVTable(void) {
    struct Obj_3b2130 obj;
    int t;

    igObject_InitHeader(&obj);
    obj.w2 = 0;
    obj.w5 = 0;
    obj.w6 = 0;
    obj.vt = &g_beNDMWTitle2Info_vtable[0];
    t = *(int *)((char *)&obj + *(int *)((char *)(g_objectSystem[0]) + 916));
    obj.vt = &g_beNDMWTitle2Info_vtable[0];
    FUN_0033ec80(&obj, 0);
    return t;
}

void beNDMWTitle2Info_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(beNDMWTitle2Info_Register);
}

void *beNDMWTitle2Info_Register(void) {
    NdmwLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_beNDMWTitle2Info_metaObject,
        beBaseInfo_Register,
        beBaseInfo_GetPublishedMetaObject,
        beNDMWTitle2Info_GetMetaObjectFunction,
        "beNDMWTitle2Info",
        0x1c, /* instance size */
        beNDMWTitle2Info_GetVTable,
        0,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void beNDMWTitle2Info_GetMetaObjectFunction(void)
{
    beNDMWTitle2Info_GetMetaObject();
}

