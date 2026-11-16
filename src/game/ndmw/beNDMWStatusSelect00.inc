igMetaObject *g_beNDMWStatusSelect00_metaObject;

void beNDMWStatusSelect00_Create(int arg0) {
    beNDMWStatusSelect00_EnsureRegistered();
    igMetaObject_CreateInstance(g_beNDMWStatusSelect00_metaObject, arg0);
}

igMetaObject *beNDMWStatusSelect00_GetMetaObject(void) {
    igMetaObject *g = g_beNDMWStatusSelect00_metaObject;
    if (g != 0) {
        int b = !!(g->_validity & 4);
        if (b) goto done;
    }
    beNDMWStatusSelect00_EnsureRegistered();
done:
    return g_beNDMWStatusSelect00_metaObject;
}

int beNDMWStatusSelect00_GetVTable(void) {
    struct F_3b5780 f;
    int temp_s0;

    igObject_InitHeader(&f);
    f.w[12] = 0;
    f.w[13] = 0;
    f.w[14] = 0;
    f.w[15] = 0;
    f.w[16] = 0;
    f.w[17] = 0;
    f.w[18] = 0;
    f.w[19] = 0;
    f.w[26] = 0;
    f.vt = &g_beNDMWStatusSelect00_vtable[0];
    temp_s0 = *(int *)((char *)&f + *(int *)((char *)(g_objectSystem[0]) + 916));
    f.vt = &g_beNDMWStatusSelect00_vtable[0];
    FUN_003b4050((struct S_3b4050 *)&f, (short)0);
    return temp_s0;
}

void beNDMWStatusSelect00_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(beNDMWStatusSelect00_Register);
}

void *beNDMWStatusSelect00_Register(void) {
    NdmwLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_beNDMWStatusSelect00_metaObject,
        beNDMWWindowSelect_Register,
        beNDMWWindowSelect_GetPublishedMetaObject,
        beNDMWStatusSelect00_GetMetaObjectFunction,
        "beNDMWStatusSelect00",
        0x70, /* instance size */
        beNDMWStatusSelect00_GetVTable,
        0,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void beNDMWStatusSelect00_GetMetaObjectFunction(void)
{
    beNDMWStatusSelect00_GetMetaObject();
}

