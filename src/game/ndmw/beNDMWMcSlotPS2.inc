igMetaObject *g_beNDMWMcSlotPS2_metaObject;

void beNDMWMcSlotPS2_Create(int allocator) {
    beNDMWMcSlotPS2_EnsureRegistered();
    igMetaObject_CreateInstance(g_beNDMWMcSlotPS2_metaObject, allocator);
}

igMetaObject *beNDMWMcSlotPS2_GetReadyMetaObject(void) {
    igMetaObject *g = g_beNDMWMcSlotPS2_metaObject;
    if (g != 0) {
        int b = !!(g->_validity & 4);
        if (b) goto done;
    }
    beNDMWMcSlotPS2_EnsureRegistered();
done:
    return g_beNDMWMcSlotPS2_metaObject;
}

int beNDMWMcSlotPS2_GetVTable(void) {
    beNDMWMcSlotPS2 obj;

    igObject_InitHeader(&obj);
    *(int **)&obj._vtable = &g_beNDMWMcSlotPS2_vtable[0];
    return *(int *)((char *)&obj + *(int *)((char *)(g_objectSystem[0]) + 916));
}

void beNDMWMcSlotPS2_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(beNDMWMcSlotPS2_Register);
}

void *beNDMWMcSlotPS2_Register(void) {
    NdmwLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_beNDMWMcSlotPS2_metaObject,
        beNDMWMcSlot_Register,
        beNDMWMcSlot_GetPublishedMetaObject,
        beNDMWMcSlotPS2_GetMetaObject,
        "beNDMWMcSlotPS2",
        0x18, /* instance size */
        beNDMWMcSlotPS2_GetVTable,
        0,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void beNDMWMcSlotPS2_GetMetaObject(void)
{
    beNDMWMcSlotPS2_GetReadyMetaObject();
}

