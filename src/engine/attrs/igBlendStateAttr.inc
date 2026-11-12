void FUN_00139600(int arg0) {
    FUN_00139720();
    igMetaObject_CreateInstance(*(int *)0x55F348, arg0);
}

int FUN_00139640(void) {
    if (DAT_0055f348[0] == 0) {
        DAT_0055f348[0] = igMetaObject_Create(Memory_GetAllocatorBySelector(DAT_00587040[0]));
    }
    return DAT_0055f348[0];
}

igMetaObject *igBlendStateAttr_GetMetaObject(void)
{
    igMetaObject *g = g_igBlendStateAttr_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_00139720();
    return g_igBlendStateAttr_metaObject[0];
}

int igBlendStateAttr_GetVTable(void) {
    struct Obj o;
    igObject_InitHeader(&o);
    o.vt = &DAT_00524080[0];
    return *(int *)((char *)&o + *(int *)((char *)(DAT_00586dc8[0]) + 916));
}

void FUN_00139720(void)
{
    igMetaObject_RunStaticInit(igBlendStateAttr_Register);
}

void igBlendStateAttr_Register(void) {
    AttrsLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igBlendStateAttr_metaObject,
        igVisualAttribute_Register,
        igVisualAttribute_GetPublishedMetaObject,
        thunk_igBlendStateAttr_GetMetaObject,
        igBlendStateAttr_className,
        0x10, /* instance size */
        igBlendStateAttr_GetVTable,
        &igBlendStateAttr_InitFields,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void thunk_igBlendStateAttr_GetMetaObject(void) {
    igBlendStateAttr_GetMetaObject();
}

void igBlendStateAttr_InitFields(void) {
    int temp_s1;
    void *temp_s0;

    temp_s0 = (void *)DAT_0055f348[0];
    temp_s1 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &DAT_004869e0[0], 1);
    igMetaObject_NameFields(temp_s0, &DAT_004869e8[0], &DAT_004869f0[0], &DAT_004869f8[0], temp_s1);
}

