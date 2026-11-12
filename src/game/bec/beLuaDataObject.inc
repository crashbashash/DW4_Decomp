int FUN_0035b510(void) {
    if (((int *)DAT_005891f0)[0] == 0) {
        ((int *)DAT_005891f0)[0] = igMetaObject_Create(Memory_GetAllocatorBySelector(DAT_00587040[0]));
    }
    return ((int *)DAT_005891f0)[0];
}

void *FUN_0035b560(void) {
    struct G *g = DAT_005891f0[0];
    if (!g || ((g->f & 4) != 0) == false) {
        FUN_0035b5f0();
    }
    return DAT_005891f0[0];
}

int beLuaDataObject_GetVTable(void) {
    struct Obj_35b5b0 obj;

    igObject_InitHeader(&obj);
    obj.vt = &DAT_005367c0[0];
    return *(int *)((char *)&obj + *(int *)((char *)(DAT_00586dc8[0]) + 916));
}

void FUN_0035b5f0(void)
{
    igMetaObject_RunStaticInit(beLuaDataObject_Register);
}

void *beLuaDataObject_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beLuaDataObject_metaObject,
        igObject_Register,
        igObject_GetMetaObject_ParentAccessor,
        beLuaDataObject_GetMetaObject,
        beLuaDataObject_className,
        0x10, /* instance size */
        beLuaDataObject_GetVTable,
        beLuaDataObject_InitFields,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void beLuaDataObject_GetMetaObject(void)
{
    FUN_0035b560();
}

void beLuaDataObject_InitFields(void) {
    int temp_s2;
    void *temp_s1;
    void *temp_s0;

    temp_s0 = (void *)((int *)DAT_005891f0)[0];
    temp_s2 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &DAT_004c62b8[0], 2);
    temp_s1 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 1));
    ((igMemoryRefMetaField *)temp_s1)->_memType = FUN_002cc2c0();
    igMetaObject_NameFields(temp_s0, &DAT_004c62c0[0], &DAT_004c62c8[0], &DAT_004c62d0[0], temp_s2);
}

