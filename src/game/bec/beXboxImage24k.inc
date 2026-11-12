int FUN_00347600(void) {
    if (DAT_00588070[0] == 0) {
        DAT_00588070[0] = igMetaObject_Create(Memory_GetAllocatorBySelector(DAT_00587040[0]));
    }
    return DAT_00588070[0];
}

void *FUN_00347650(void) {
    unsigned char b;
    if (((void * *)DAT_00588070)[0] != 0) {
        b = (*(int *)((char *)(((void * *)DAT_00588070)[0]) + 36) & 4) != 0;
        if (b != 0) goto done;
    }
    FUN_003476e0();
done:
    return ((void * *)DAT_00588070)[0];
}

int beXboxImage24k_GetVTable(void) {
    struct Obj_3476a0 obj;

    igObject_InitHeader(&obj);
    obj.vt = &DAT_00538c20[0];
    return *(int *)((char *)&obj + *(int *)((char *)(DAT_00586dc8[0]) + 916));
}

void FUN_003476e0(void)
{
    igMetaObject_RunStaticInit(beXboxImage24k_Register);
}

void *beXboxImage24k_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beXboxImage24k_metaObject,
        igObject_Register,
        igObject_GetMetaObject_ParentAccessor,
        beXboxImage24k_GetMetaObject,
        beXboxImage24k_className,
        0x10, /* instance size */
        beXboxImage24k_GetVTable,
        beXboxImage24k_InitFields,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void beXboxImage24k_GetMetaObject(void)
{
    FUN_00347650();
}

void beXboxImage24k_InitFields(void) {
    int temp_s2;
    void *temp_s1;
    void *temp_s0;

    temp_s0 = (void *)DAT_00588070[0];
    temp_s2 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &DAT_004c3d60[0], 2);
    temp_s1 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 1));
    ((igMemoryRefMetaField *)temp_s1)->_memType = FUN_002cc2c0();
    igMetaObject_NameFields(temp_s0, &DAT_004c3d68[0], &DAT_004c3d70[0], &DAT_004c3d78[0], temp_s2);
}

