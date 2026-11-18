igMetaObject *g_igBoxComponent_metaObject;

igMetaObject *igBoxComponent_GetOrCreateMetaObject(void) {
    if (g_igBoxComponent_metaObject == 0) {
        g_igBoxComponent_metaObject = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData));
    }
    return g_igBoxComponent_metaObject;
}

igMetaObject *igBoxComponent_GetMetaObject(void)
{
    igMetaObject *g = g_igBoxComponent_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false)
        igBoxComponent_RunStaticInit();
    return g_igBoxComponent_metaObject;
}

int igBoxComponent_GetVTable(void) {
    struct F f;
    int temp_s0;

    igObject_InitHeader((igObject *)&f);
    f.w[2] = 0;
    f.w[3] = 0;
    f.w[4] = 0;
    f.w[6] = 0;
    f.vt = &g_igBoxComponent_vtable[0];
    temp_s0 = *(int *)((char *)&f + g_objectSystem->vtableProbeOffset);
    f.vt = &g_igBoxComponent_vtable[0];
    FUN_00450090((O_450090 *)&f, 0);
    return temp_s0;
}

void igBoxComponent_RunStaticInit(void)
{
    igMetaObject_RunStaticInit(igBoxComponent_Register);
}

CallbackArray *igBoxComponent_Register(void) {
    GuiLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_igBoxComponent_metaObject,
        igGuiComponent_Register,
        igGuiComponent_GetPublishedMetaObject,
        thunk_igBoxComponent_GetMetaObject,
        "igBoxComponent",
        0x24, /* instance size */
        igBoxComponent_GetVTable,
        0,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void thunk_igBoxComponent_GetMetaObject(void) {
    igBoxComponent_GetMetaObject();
}

igMetaObject *FUN_004524e0(void) {
    return g_igGuiComponent_metaObject;
}

