void *FUN_0034b4a0(void) {
    igMetaObject *g = g_beResetNode_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false) {
        FUN_0034b560();
    }
    return g_beResetNode_metaObject[0];
}

int beResetNode_GetVTable(void) {
    struct W_34b4f0 o;
    int r;

    igObject_InitHeader(&o);
    o.w[1] = 0;
    o.w[2] = 0;
    o.w[3] = 0;
    o.w[6] = 0;
    o.vt = DAT_00538810;
    r = *(int *)((char *)&o + *(int *)(((char * *)g_objectSystem)[0] + 916));
    o.vt = DAT_00538810;
    FUN_00195a90(&o, 0);
    return r;
}

void FUN_0034b560(void)
{
    igMetaObject_RunStaticInit(beResetNode_Register);
}

void *beResetNode_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beResetNode_metaObject,
        igGroup_Register,
        igGroup_GetPublishedMetaObject,
        beResetNode_GetMetaObject,
        beResetNode_className,
        0x24, /* instance size */
        beResetNode_GetVTable,
        beResetNode_InitFields,
        FUN_0034b690, /* extra callback item */
        0 /* callback list */
    );
}

void beResetNode_GetMetaObject(void)
{
    FUN_0034b4a0();
}

void beResetNode_InitFields(void) {
    int temp_s1;
    void *temp_s0;

    temp_s0 = (void *)g_beResetNode_metaObject[0];
    temp_s1 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &g_beResetNode_ctorTable[0], 2);
    igMetaObject_NameFields(temp_s0, &g_beResetNode_fieldTable[0], &DAT_004c4508[0], &DAT_004c4510[0], temp_s1);
}

void FUN_0034b690(void)
{
    FUN_0039c8c0();
}

