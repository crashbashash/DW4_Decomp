void beNDMWMcSlotXbox_Create(int arg0) {
    FUN_003c5bc0();
    igMetaObject_CreateInstance(*(int *)0x58BC98, arg0);
}

igMetaObject *beNDMWMcSlotXbox_GetReadyMetaObject(void)
{
    igMetaObject *g = g_beNDMWMcSlotXbox_metaObject[0];
    bool t;
    if (!g || (t = g->_validity & 4) == 0)
        FUN_003c5bc0();
    return g_beNDMWMcSlotXbox_metaObject[0];
}

int beNDMWMcSlotXbox_GetVTable(void) {
    struct W_3c5b30 o;
    int r;

    int *p; int *a1; int t;
    igObject_InitHeader(&o);
    o.vt = DAT_0053cc00;
    *(int *)((char *)&o + 24) = 0;
    r = *(int *)((char *)&o + *(int *)(((char * *)g_objectSystem)[0] + 916));
    o.vt = DAT_0053cc00;
    if (&*(int *)((char *)&o + 24) != 0) { p = *(int **)((char *)&o + 24); if (p != 0) { a1 = p - 2; t = p[-1] - 1; p[-1] = t; if (t == 0) StringChunk_ReleaseHeader(*a1, a1); } }
    return r;
}

void FUN_003c5bc0(void)
{
    igMetaObject_RunStaticInit(beNDMWMcSlotXbox_Register);
}

void *beNDMWMcSlotXbox_Register(void) {
    NdmwLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beNDMWMcSlotXbox_metaObject,
        beNDMWMcSlot_Register,
        beNDMWMcSlot_GetPublishedMetaObject,
        beNDMWMcSlotXbox_GetMetaObject,
        beNDMWMcSlotXbox_className,
        0x1c, /* instance size */
        beNDMWMcSlotXbox_GetVTable,
        beNDMWMcSlotXbox_InitFields,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void beNDMWMcSlotXbox_GetMetaObject(void)
{
    beNDMWMcSlotXbox_GetReadyMetaObject();
}

igMetaObject *FUN_003c5c70(void) {
    return g_beNDMWMcSlot_metaObject[0];
}

void beNDMWMcSlotXbox_InitFields(void) {
    int temp_s1;
    void *temp_s0;

    temp_s0 = (void *)g_beNDMWMcSlotXbox_metaObject[0];
    temp_s1 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &g_beNDMWMcSlotXbox_ctorTable[0], 1);
    igMetaObject_NameFields(temp_s0, &g_beNDMWMcSlotXbox_fieldTable[0], &DAT_004cbb70[0], &DAT_004cbb78[0], temp_s1);
}

