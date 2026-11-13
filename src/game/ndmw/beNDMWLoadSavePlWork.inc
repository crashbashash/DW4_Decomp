void beNDMWLoadSavePlWork_Create(int arg0) {
    FUN_003c5780();
    igMetaObject_CreateInstance(*(int *)0x58BC18, arg0);
}

void *beNDMWLoadSavePlWork_ResolveMetaObject(void) {
    igMetaObject *g = g_beNDMWLoadSavePlWork_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false) {
        FUN_003c5780();
    }
    return g_beNDMWLoadSavePlWork_metaObject[0];
}

int beNDMWLoadSavePlWork_GetVTable(void) {
    struct O_3c5740 o;

    igObject_InitHeader(&o.vt);
    o.vt = DAT_0053ccd0;
    return *(int *)((char *)&o.vt + *(int *)(((char * *)g_objectSystem)[0] + 916));
}

void FUN_003c5780(void)
{
    igMetaObject_RunStaticInit(beNDMWLoadSavePlWork_Register);
}

void *beNDMWLoadSavePlWork_Register(void) {
    NdmwLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beNDMWLoadSavePlWork_metaObject,
        igObject_Register,
        igObject_GetMetaObject_ParentAccessor,
        beNDMWLoadSavePlWork_GetMetaObject,
        beNDMWLoadSavePlWork_className,
        0x34, /* instance size */
        beNDMWLoadSavePlWork_GetVTable,
        beNDMWLoadSavePlWork_InitFields,
        0, /* extra callback item */
        g_beNDMWLoadSavePlWork_callbackList /* callback list */
    );
}

void beNDMWLoadSavePlWork_GetMetaObject(void)
{
    beNDMWLoadSavePlWork_ResolveMetaObject();
}

void beNDMWLoadSavePlWork_InitFields(void) {
    int temp_s2;
    void *temp_s1;
    void *temp_s0;

    temp_s0 = (void *)g_beNDMWLoadSavePlWork_metaObject[0];
    temp_s2 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &DAT_004cba60[0], 0xE);
    FUN_002d3890(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 3), 1);
    FUN_002d3890(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 4), 1);
    temp_s1 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 8));
    ((igObjectRefMetaField *)temp_s1)->_metaObject = (int)FUN_003c63a0();
    ((igObjectRefMetaField *)temp_s1)->_refCounted = 0;
    igMetaObject_NameFields(temp_s0, &DAT_004cbaa0[0], &DAT_004cbae0[0], &DAT_004cbb20[0], temp_s2);
}

