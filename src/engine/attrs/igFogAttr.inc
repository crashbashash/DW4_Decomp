igMetaObject *igFogAttr_GetMetaObject(void)
{
    igMetaObject *g = g_igFogAttr_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_00137e30();
    return g_igFogAttr_metaObject[0];
}

int igFogAttr_GetVTable(void) {
    struct Obj_137df0 obj;
    igObject_InitHeader(&obj);
    obj.vt = &DAT_00523b20[0];
    return *(int *)((char *)&obj + *(int *)((char *)(g_objectSystem[0]) + 916));
}

void FUN_00137e30(void)
{
    igMetaObject_RunStaticInit(igFogAttr_Register);
}

void igFogAttr_Register(void) {
    AttrsLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igFogAttr_metaObject,
        igVisualAttribute_Register,
        igVisualAttribute_GetPublishedMetaObject,
        thunk_igFogAttr_GetMetaObject,
        igFogAttr_className,
        0x2C, /* instance size */
        igFogAttr_GetVTable,
        &igFogAttr_InitFields,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void thunk_igFogAttr_GetMetaObject(void) {
    igFogAttr_GetMetaObject();
}

void igFogAttr_InitFields(void) {
    int temp_s2;
    float sp[4];
    void *temp_v0;
    void *temp_a0;
    void *temp_s0;

    temp_s0 = (void *)g_igFogAttr_metaObject[0];
    temp_s2 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &g_igFogAttr_ctorTable[0], 5);
    temp_v0 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2));
    FUN_002dc7a0(temp_v0, &DAT_004866f8[0]);
    *(int *)((char *)(temp_v0) + 52) = (int)(&FUN_00149560);
    FUN_002e3810(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 2), 1000.0f);
    temp_a0 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 4));
    sp[0] = 0.0f;
    sp[3] = 1.0f;
    sp[1] = 0.0f;
    sp[2] = 0.0f;
    FUN_0018e670(temp_a0, sp);
    igMetaObject_NameFields(temp_s0, &g_igFogAttr_fieldTable[0], &DAT_004866c0[0], &DAT_004866e0[0], temp_s2);
}

