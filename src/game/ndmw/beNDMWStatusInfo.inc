igMetaObject *g_beNDMWStatusInfo_metaObject;

void *beNDMWStatusInfo_GetMetaObject(void) {
    igMetaObject *g = g_beNDMWStatusInfo_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false) {
        beNDMWStatusInfo_EnsureRegistered();
    }
    return g_beNDMWStatusInfo_metaObject;
}

int beNDMWStatusInfo_GetVTable(void) {
    struct Obj_3b5a90 obj;
    int r;

    igObject_InitHeader(&obj);
    obj.w[1] = 0;
    obj.w[4] = 0;
    obj.w[5] = 0;
    obj.vt = &g_beNDMWStatusInfo_vtable[0];
    r = *(int *)((char *)&obj + *(int *)((char *)(g_objectSystem[0]) + 916));
    obj.vt = &g_beNDMWStatusInfo_vtable[0];
    FUN_0033ec80(&obj, 0);
    return r;
}

void beNDMWStatusInfo_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(beNDMWStatusInfo_Register);
}

void *beNDMWStatusInfo_Register(void) {
    NdmwLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_beNDMWStatusInfo_metaObject,
        beBaseInfo_Register,
        beBaseInfo_GetPublishedMetaObject,
        beNDMWStatusInfo_GetMetaObjectFunction,
        "beNDMWStatusInfo",
        0x1c, /* instance size */
        beNDMWStatusInfo_GetVTable,
        0,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void beNDMWStatusInfo_GetMetaObjectFunction(void)
{
    beNDMWStatusInfo_GetMetaObject();
}

