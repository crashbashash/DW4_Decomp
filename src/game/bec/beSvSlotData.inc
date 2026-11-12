igMetaObject *FUN_0034aae0(void)
{
    igMetaObject *g = g_beSvSlotData_metaObject[0];
    bool t;
    if (!g || (t = g->_validity & 4) == 0)
        FUN_0034ab30();
    return g_beSvSlotData_metaObject[0];
}

void FUN_0034ab30(void)
{
    igMetaObject_RunStaticInit(beSvSlotData_Register);
}

void *beSvSlotData_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        1, /* abstract */
        g_beSvSlotData_metaObject,
        igObject_Register,
        igObject_GetMetaObject_ParentAccessor,
        beSvSlotData_GetMetaObject,
        beSvSlotData_className,
        0x18, /* instance size */
        0,
        beSvSlotData_InitFields,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void beSvSlotData_GetMetaObject(void)
{
    FUN_0034aae0();
}

void beSvSlotData_InitFields(void) {
    int temp_s1;
    void *temp_s0;

    temp_s0 = (void *)g_beSvSlotData_metaObject[0];
    temp_s1 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &DAT_004c42f0[0], 5);
    igMetaObject_NameFields(temp_s0, &DAT_004c4310[0], &DAT_004c4330[0], &DAT_004c4350[0], temp_s1);
}

