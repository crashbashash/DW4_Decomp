igMetaObject *FUN_00356450(void)
{
    igMetaObject *g = g_beModelCtrlLUACALL_metaObject[0];
    bool t;
    if (!g || (t = g->_validity & 4) == 0)
        FUN_00356570();
    return g_beModelCtrlLUACALL_metaObject[0];
}

int beModelCtrlLUACALL_GetVTable(void) {
    Obj_3564a0 obj;
    int r;

    igObject_InitHeader(&obj);
    obj.m8 = 0;
    obj.vt = &DAT_00537290[0];
    obj.m12 = 0;
    r = *(int *)((char *)&obj + *(int *)((char *)(g_objectSystem[0]) + 916));
    obj.vt = &DAT_00537290[0];
    obj.rel12();
    obj.vt = &DAT_00524950[0];
    obj.rel8();
    return r;
}

void FUN_00356570(void)
{
    igMetaObject_RunStaticInit(beModelCtrlLUACALL_Register);
}

void *beModelCtrlLUACALL_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beModelCtrlLUACALL_metaObject,
        igNamedObject_Register,
        igNamedObject_GetPublishedMetaObject,
        beModelCtrlLUACALL_GetMetaObject,
        beModelCtrlLUACALL_className,
        0x10, /* instance size */
        beModelCtrlLUACALL_GetVTable,
        beModelCtrlLUACALL_InitFields,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void beModelCtrlLUACALL_GetMetaObject(void)
{
    FUN_00356450();
}

void beModelCtrlLUACALL_InitFields(void) {
    int temp_s1;
    void *temp_s0;

    temp_s0 = (void *)g_beModelCtrlLUACALL_metaObject[0];
    temp_s1 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &DAT_004c5898[0], 1);
    igMetaObject_NameFields(temp_s0, &DAT_004c58a0[0], &DAT_004c58a8[0], &DAT_004c58b0[0], temp_s1);
}

