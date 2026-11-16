igMetaObject *g_beNDMWStatusSelectE1_metaObject;

void beNDMWStatusSelectE1_Create(int allocator) {
    beNDMWStatusSelectE1_EnsureRegistered();
    igMetaObject_CreateInstance(g_beNDMWStatusSelectE1_metaObject, allocator);
}

void *beNDMWStatusSelectE1_GetMetaObject(void) {
    igMetaObject *g = g_beNDMWStatusSelectE1_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false) {
        beNDMWStatusSelectE1_EnsureRegistered();
    }
    return g_beNDMWStatusSelectE1_metaObject;
}

int beNDMWStatusSelectE1_GetVTable(void) {
    struct Obj_3b5240 obj;
    int t;

    igObject_InitHeader(&obj);
    obj.w13 = 0;
    obj.w14 = 0;
    obj.w15 = 0;
    obj.w16 = 0;
    obj.w17 = 0;
    obj.w18 = 0;
    obj.w19 = 0;
    obj.w20 = 0;
    obj.w27 = 0;
    obj.vt = &g_beNDMWStatusSelectE1_vtable[0];
    t = *(int *)((char *)&obj + *(int *)((char *)(g_objectSystem[0]) + 916));
    obj.vt = &g_beNDMWStatusSelectE1_vtable[0];
    FUN_003b4050((struct S_3b4050 *)&obj, (short)0);
    return t;
}

void beNDMWStatusSelectE1_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(beNDMWStatusSelectE1_Register);
}

void *beNDMWStatusSelectE1_Register(void) {
    NdmwLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_beNDMWStatusSelectE1_metaObject,
        beNDMWWindowSelect_Register,
        beNDMWWindowSelect_GetPublishedMetaObject,
        beNDMWStatusSelectE1_GetMetaObjectFunction,
        "beNDMWStatusSelectE1",
        0x70, /* instance size */
        beNDMWStatusSelectE1_GetVTable,
        0,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void beNDMWStatusSelectE1_GetMetaObjectFunction(void)
{
    beNDMWStatusSelectE1_GetMetaObject();
}

