igMetaObject *g_beSeInfo_metaObject;

void *beSeInfo_GetMetaObject(void) {
    igMetaObject *g = g_beSeInfo_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false) {
        beSeInfo_EnsureRegistered();
    }
    return g_beSeInfo_metaObject;
}

int beSeInfo_GetVTable(void) {
    struct W_345d80 o;
    int r;

    igObject_InitHeader(&o);
    o.w[1] = 0;
    o.w[4] = 0;
    o.w[5] = 0;
    o.vt = g_beSeInfo_vtable;
    r = *(int *)((char *)&o + *(int *)(((char * *)g_objectSystem)[0] + 916));
    o.vt = g_beSeInfo_vtable;
    FUN_0033ec80((struct S_33ec80 *)&o, (short)0);
    return r;
}

void beSeInfo_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(beSeInfo_Register);
}

void *beSeInfo_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_beSeInfo_metaObject,
        beBaseInfo_Register,
        beBaseInfo_GetPublishedMetaObject,
        beSeInfo_GetMetaObjectFunction,
        "beSeInfo",
        0x1c, /* instance size */
        beSeInfo_GetVTable,
        0,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void beSeInfo_GetMetaObjectFunction(void)
{
    beSeInfo_GetMetaObject();
}

