void beNDMWMcSlotPS2_Create(int arg0) {
    FUN_003c5fb0();
    igMetaObject_CreateInstance(*(int *)0x58BCC0, arg0);
}

igMetaObject *beNDMWMcSlotPS2_GetReadyMetaObject(void) {
    igMetaObject *g = g_beNDMWMcSlotPS2_metaObject[0];
    if (g != 0) {
        int b = !!(g->_validity & 4);
        if (b) goto done;
    }
    FUN_003c5fb0();
done:
    return g_beNDMWMcSlotPS2_metaObject[0];
}

int beNDMWMcSlotPS2_GetVTable(void) {
    struct Obj obj;

    igObject_InitHeader(&obj);
    obj.vt = &DAT_0053cb40[0];
    return *(int *)((char *)&obj + *(int *)((char *)(g_objectSystem[0]) + 916));
}

void FUN_003c5fb0(void)
{
    igMetaObject_RunStaticInit(beNDMWMcSlotPS2_Register);
}

void *beNDMWMcSlotPS2_Register(void) {
    NdmwLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beNDMWMcSlotPS2_metaObject,
        beNDMWMcSlot_Register,
        beNDMWMcSlot_GetPublishedMetaObject,
        beNDMWMcSlotPS2_GetMetaObject,
        beNDMWMcSlotPS2_className,
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

