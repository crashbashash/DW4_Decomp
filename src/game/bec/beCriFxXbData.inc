igMetaObject *FUN_00366fa0(void) {
    if (g_beCriFxXbData_metaObject[0] == 0) {
        g_beCriFxXbData_metaObject[0] = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData[0]));
    }
    return g_beCriFxXbData_metaObject[0];
}

void *FUN_00366ff0(void) {
    igMetaObject *g = g_beCriFxXbData_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false) {
        FUN_00367080();
    }
    return g_beCriFxXbData_metaObject[0];
}

int beCriFxXbData_GetVTable(void) {
    union U_367040 u;

    igObject_InitHeader(u.b);
    u.w[0] = (int)(&DAT_00534e90[0]);
    return *(int *)&u.b[*(int *)((char *)(g_objectSystem[0]) + 916)];
}

void FUN_00367080(void)
{
    igMetaObject_RunStaticInit(beCriFxXbData_Register);
}

void *beCriFxXbData_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beCriFxXbData_metaObject,
        igObject_Register,
        igObject_GetMetaObject_ParentAccessor,
        beCriFxXbData_GetMetaObject,
        beCriFxXbData_className,
        0x38, /* instance size */
        beCriFxXbData_GetVTable,
        beCriFxXbData_InitFields,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void beCriFxXbData_GetMetaObject(void)
{
    FUN_00366ff0();
}

void beCriFxXbData_InitFields(void) {
    int temp_s1;
    void *temp_s0;

    temp_s0 = (void *)g_beCriFxXbData_metaObject[0];
    temp_s1 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &g_beCriFxXbData_ctorTable[0], 0xC);
    igMetaObject_NameFields(temp_s0, &g_beCriFxXbData_fieldTable[0], &DAT_004c7550[0], &DAT_004c7580[0], temp_s1);
}

