int FUN_0034aeb0(void) {
    if (((int *)DAT_005883b0)[0] == 0) {
        ((int *)DAT_005883b0)[0] = igMetaObject_Create(Memory_GetAllocatorBySelector(DAT_00587040[0]));
    }
    return ((int *)DAT_005883b0)[0];
}

S_34af00 *FUN_0034af00(void) {
    S_34af00 *g = DAT_005883b0[0];
    if (g != 0) {
        int b = !!(g->flags & 4);
        if (b) goto done;
    }
    FUN_0034af90();
done:
    return DAT_005883b0[0];
}

int beSaveDataDeliver_GetVTable(void) {
    struct Obj_34af50 obj;

    igObject_InitHeader(&obj);
    obj.vt = &DAT_00538910[0];
    return *(int *)((char *)&obj + *(int *)((char *)(DAT_00586dc8[0]) + 916));
}

void FUN_0034af90(void)
{
    igMetaObject_RunStaticInit(beSaveDataDeliver_Register);
}

void *beSaveDataDeliver_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beSaveDataDeliver_metaObject,
        igObject_Register,
        igObject_GetMetaObject_ParentAccessor,
        beSaveDataDeliver_GetMetaObject,
        beSaveDataDeliver_className,
        0x10, /* instance size */
        beSaveDataDeliver_GetVTable,
        beSaveDataDeliver_InitFields,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void beSaveDataDeliver_GetMetaObject(void)
{
    FUN_0034af00();
}

void beSaveDataDeliver_InitFields(void) {
    int temp_s2;
    void *temp_s1;
    void *temp_s0;

    temp_s0 = (void *)((int *)DAT_005883b0)[0];
    temp_s2 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &DAT_004c4388[0], 2);
    temp_s1 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 1));
    ((igMemoryRefMetaField *)temp_s1)->_memType = FUN_002cc2c0();
    igMetaObject_NameFields(temp_s0, &DAT_004c4390[0], &DAT_004c4398[0], &DAT_004c43a0[0], temp_s2);
}

