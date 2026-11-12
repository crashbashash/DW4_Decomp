int FUN_00366fa0(void) {
    if (((int *)DAT_00589a20)[0] == 0) {
        ((int *)DAT_00589a20)[0] = igMetaObject_Create(Memory_GetAllocatorBySelector(DAT_00587040[0]));
    }
    return ((int *)DAT_00589a20)[0];
}

void *FUN_00366ff0(void) {
    struct G *g = DAT_00589a20[0];
    if (!g || ((g->f & 4) != 0) == false) {
        FUN_00367080();
    }
    return DAT_00589a20[0];
}

int beCriFxXbData_GetVTable(void) {
    union U_367040 u;

    igObject_InitHeader(u.b);
    u.w[0] = (int)(&DAT_00534e90[0]);
    return *(int *)&u.b[*(int *)((char *)(DAT_00586dc8[0]) + 916)];
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

    temp_s0 = (void *)((int *)DAT_00589a20)[0];
    temp_s1 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &DAT_004c74f0[0], 0xC);
    igMetaObject_NameFields(temp_s0, &DAT_004c7520[0], &DAT_004c7550[0], &DAT_004c7580[0], temp_s1);
}

