int FUN_0034a000(void) {
    if (DAT_00588298[0] == 0) {
        DAT_00588298[0] = igMetaObject_Create(Memory_GetAllocatorBySelector(DAT_00587040[0]));
    }
    return DAT_00588298[0];
}

void *FUN_0034a050(void) {
    unsigned char b;
    if (((void * *)DAT_00588298)[0] != 0) {
        b = (*(int *)((char *)(((void * *)DAT_00588298)[0]) + 36) & 4) != 0;
        if (b != 0) goto done;
    }
    FUN_0034a0a0();
done:
    return ((void * *)DAT_00588298)[0];
}

void FUN_0034a0a0(void)
{
    igMetaObject_RunStaticInit(beSaveApi_Register);
}

void *beSaveApi_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        1, /* abstract */
        g_beSaveApi_metaObject,
        igObject_Register,
        igObject_GetMetaObject_ParentAccessor,
        beSaveApi_GetMetaObject,
        beSaveApi_className,
        0x40, /* instance size */
        0,
        beSaveApi_InitFields,
        0, /* extra callback item */
        g_beSaveApi_callbackList /* callback list */
    );
}

void beSaveApi_GetMetaObject(void)
{
    FUN_0034a050();
}

void beSaveApi_InitFields(void) {
    int temp_s2;
    void *temp_s1_3;
    void *temp_s1_2;
    void *temp_s1;
    void *temp_s0;

    temp_s0 = (void *)DAT_00588298[0];
    temp_s2 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &DAT_004c4160[0], 0xD);
    temp_s1 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 0xA));
    ((igObjectRefMetaField *)temp_s1)->_metaObject = FUN_0034ac90();
    temp_s1_2 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 0xB));
    ((igObjectRefMetaField *)temp_s1_2)->_metaObject = FUN_0034ac90();
    temp_s1_3 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 0xC));
    ((igObjectRefMetaField *)temp_s1_3)->_metaObject = FUN_0034ac90();
    igMetaObject_NameFields(temp_s0, &DAT_004c41a0[0], &DAT_004c41e0[0], &DAT_004c4220[0], temp_s2);
}

