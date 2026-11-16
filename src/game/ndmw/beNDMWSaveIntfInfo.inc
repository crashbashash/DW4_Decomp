igMetaObject *g_beNDMWSaveIntfInfo_metaObject;

igMetaObject *beNDMWSaveIntfInfo_GetMetaObject(void) {
    igMetaObject *g = g_beNDMWSaveIntfInfo_metaObject;
    if (g != 0) {
        int b = !!(g->_validity & 4);
        if (b) goto done;
    }
    beNDMWSaveIntfInfo_EnsureRegistered();
done:
    return g_beNDMWSaveIntfInfo_metaObject;
}

int beNDMWSaveIntfInfo_GetVTable(void) {
    union U_3bc0d0 u;
    int temp_s0;

    igObject_InitHeader(u.b);
    u.w[2] = 0;
    u.w[5] = 0;
    u.w[6] = 0;
    u.w[0] = (int)(&g_beNDMWSaveIntfInfo_vtable[0]);
    temp_s0 = *(int *)&u.b[*(int *)((char *)(g_objectSystem[0]) + 916)];
    u.w[0] = (int)(&g_beNDMWSaveIntfInfo_vtable[0]);
    FUN_0033ec80(&u.w[0], 0);
    return temp_s0;
}

void beNDMWSaveIntfInfo_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(beNDMWSaveIntfInfo_Register);
}

void *beNDMWSaveIntfInfo_Register(void) {
    NdmwLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_beNDMWSaveIntfInfo_metaObject,
        beBaseInfo_Register,
        beBaseInfo_GetPublishedMetaObject,
        beNDMWSaveIntfInfo_GetMetaObjectFunction,
        "beNDMWSaveIntfInfo",
        0x1c, /* instance size */
        beNDMWSaveIntfInfo_GetVTable,
        0,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void beNDMWSaveIntfInfo_GetMetaObjectFunction(void)
{
    beNDMWSaveIntfInfo_GetMetaObject();
}

