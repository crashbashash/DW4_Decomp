void FUN_0034ac50(int arg0) {
    FUN_0034ad70();
    igMetaObject_CreateInstance(*(int *)0x5883A0, arg0);
}

int FUN_0034ac90(void) {
    if (((int *)DAT_005883a0)[0] == 0) {
        ((int *)DAT_005883a0)[0] = igMetaObject_Create(Memory_GetAllocatorBySelector(DAT_00587040[0]));
    }
    return ((int *)DAT_005883a0)[0];
}

G_34ace0 *FUN_0034ace0(void) {
    G_34ace0 *g = DAT_005883a0[0];
    int t;
    if (!g || !(t = (g->f & 4) != 0))
        FUN_0034ad70();
    return DAT_005883a0[0];
}

int beSaveMemoryObj_GetVTable(void) {
    struct Obj_34ad30 obj;

    igObject_InitHeader(&obj);
    obj.vt = &DAT_0053c0e0[0];
    return *(int *)((char *)&obj + *(int *)((char *)(DAT_00586dc8[0]) + 916));
}

void FUN_0034ad70(void)
{
    igMetaObject_RunStaticInit(beSaveMemoryObj_Register);
}

void *beSaveMemoryObj_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beSaveMemoryObj_metaObject,
        igObject_Register,
        igObject_GetMetaObject_ParentAccessor,
        beSaveMemoryObj_GetMetaObject,
        beSaveMemoryObj_className,
        0xc, /* instance size */
        beSaveMemoryObj_GetVTable,
        beSaveMemoryObj_InitFields,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void beSaveMemoryObj_GetMetaObject(void)
{
    FUN_0034ace0();
}

void beSaveMemoryObj_InitFields(void) {
    int temp_s2;
    void *temp_s1;
    void *temp_s0;

    temp_s0 = (void *)((int *)DAT_005883a0)[0];
    temp_s2 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &DAT_004c4368[0], 1);
    temp_s1 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2));
    ((igMemoryRefMetaField *)temp_s1)->_memType = FUN_002cc2c0();
    igMetaObject_NameFields(temp_s0, &DAT_004c4370[0], &DAT_004c4378[0], &DAT_004c4380[0], temp_s2);
}

