void FUN_003c5cf0(int arg0) {
    FUN_003c5dc0();
    igMetaObject_CreateInstance(*(int *)0x58BCA8, arg0);
}

igMetaObject *beNDMWMcSlotGC_GetReadyMetaObject(void) {
    igMetaObject *g = g_beNDMWMcSlotGC_metaObject[0];
    int t;
    if (!g || !(t = (g->_validity & 4) != 0))
        FUN_003c5dc0();
    return g_beNDMWMcSlotGC_metaObject[0];
}

int beNDMWMcSlotGC_GetVTable(void) {
    Obj_3c5d80 o;

    igObject_InitHeader(&o);
    o.vt = &DAT_0053cba0[0];
    return *(int *)((char *)&o + *(int *)((char *)(g_objectSystem[0]) + 916));
}

void FUN_003c5dc0(void)
{
    igMetaObject_RunStaticInit(beNDMWMcSlotGC_Register);
}

void *beNDMWMcSlotGC_Register(void) {
    NdmwLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beNDMWMcSlotGC_metaObject,
        beNDMWMcSlot_Register,
        beNDMWMcSlot_GetPublishedMetaObject,
        beNDMWMcSlotGC_GetMetaObject,
        beNDMWMcSlotGC_className,
        0x20, /* instance size */
        beNDMWMcSlotGC_GetVTable,
        beNDMWMcSlotGC_InitFields,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void beNDMWMcSlotGC_GetMetaObject(void)
{
    beNDMWMcSlotGC_GetReadyMetaObject();
}

void beNDMWMcSlotGC_InitFields(void) {
    int temp_s1;
    void *temp_s0;

    temp_s0 = (void *)g_beNDMWMcSlotGC_metaObject[0];
    temp_s1 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &DAT_004cbb80[0], 2);
    igMetaObject_NameFields(temp_s0, &DAT_004cbb88[0], &DAT_004cbb90[0], &DAT_004cbb98[0], temp_s1);
}

