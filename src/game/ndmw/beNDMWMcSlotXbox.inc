void FUN_003c5aa0(int arg0) {
    FUN_003c5bc0();
    igMetaObject_CreateInstance(*(int *)0x58BC98, arg0);
}

igMetaObject *beNDMWMcSlotXbox_GetReadyMetaObject(void)
{
    igMetaObject *g = DAT_0058bc98[0];
    bool t;
    if (!g || (t = g->_validity & 4) == 0)
        FUN_003c5bc0();
    return DAT_0058bc98[0];
}

int beNDMWMcSlotXbox_GetVTable(void) {
    struct W_3c5b30 o;
    int r;

    int *p; int *a1; int t;
    igObject_InitHeader(&o);
    o.vt = DAT_0053cc00;
    *(int *)((char *)&o + 24) = 0;
    r = *(int *)((char *)&o + *(int *)(((char * *)DAT_00586dc8)[0] + 916));
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

int FUN_003c5c70(void) {
    return ((int *)DAT_0058bcc8)[0];
}

void beNDMWMcSlotXbox_InitFields(void) {
    int temp_s1;
    void *temp_s0;

    temp_s0 = (void *)((int *)DAT_0058bc98)[0];
    temp_s1 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &DAT_004cbb60[0], 1);
    igMetaObject_NameFields(temp_s0, &DAT_004cbb68[0], &DAT_004cbb70[0], &DAT_004cbb78[0], temp_s1);
}

