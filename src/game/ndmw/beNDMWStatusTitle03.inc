igMetaObject *g_beNDMWStatusTitle03_metaObject;

void beNDMWStatusTitle03_Create(int arg0) {
    beNDMWStatusTitle03_EnsureRegistered();
    igMetaObject_CreateInstance(g_beNDMWStatusTitle03_metaObject, arg0);
}

igMetaObject *beNDMWStatusTitle03_GetOrCreateMetaObject(void) {
    if (g_beNDMWStatusTitle03_metaObject == 0) {
        g_beNDMWStatusTitle03_metaObject = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData[0]));
    }
    return g_beNDMWStatusTitle03_metaObject;
}

void *beNDMWStatusTitle03_GetMetaObject(void) {
    igMetaObject *g = g_beNDMWStatusTitle03_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false) {
        beNDMWStatusTitle03_EnsureRegistered();
    }
    return g_beNDMWStatusTitle03_metaObject;
}

int beNDMWStatusTitle03_GetVTable(void) {
    struct Obj_3b37d0 obj;
    int t;

    igObject_InitHeader(&obj);
    obj.w13 = 0;
    obj.w14 = 0;
    obj.w15 = 0;
    obj.w16 = 0;
    obj.w17 = 0;
    obj.w18 = 0;
    obj.w19 = 0;
    obj.vt = &g_beNDMWStatusTitle03_vtable[0];
    t = *(int *)((char *)&obj + *(int *)((char *)(g_objectSystem[0]) + 916));
    obj.vt = &g_beNDMWStatusTitle03_vtable[0];
    FUN_003b3030((int **)&obj, (long long)0);
    return t;
}

void beNDMWStatusTitle03_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(beNDMWStatusTitle03_Register);
}

void *beNDMWStatusTitle03_Register(void) {
    NdmwLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_beNDMWStatusTitle03_metaObject,
        beNDMWWindowTitle_Register,
        beNDMWWindowTitle_GetPublishedMetaObject,
        beNDMWStatusTitle03_GetMetaObjectFunction,
        "beNDMWStatusTitle03",
        0x50, /* instance size */
        beNDMWStatusTitle03_GetVTable,
        0,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void beNDMWStatusTitle03_GetMetaObjectFunction(void)
{
    beNDMWStatusTitle03_GetMetaObject();
}

