void igColorAttr_CreateInstance(int arg0) {
    FUN_00139000();
    igMetaObject_CreateInstance(*(int *)0x55F2E0, arg0);
}

igMetaObject *FUN_00138f20(void) {
    if (g_igColorAttr_metaObject[0] == 0) {
        g_igColorAttr_metaObject[0] = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData[0]));
    }
    return g_igColorAttr_metaObject[0];
}

igMetaObject *igColorAttr_GetMetaObject(void)
{
    igMetaObject *g = g_igColorAttr_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_00139000();
    return g_igColorAttr_metaObject[0];
}

int igColorAttr_GetVTable(void) {
    struct Obj_138fc0 obj;

    igObject_InitHeader(&obj);
    obj.vt = &DAT_00523ee0[0];
    return *(int *)((char *)&obj + *(int *)((char *)(g_objectSystem[0]) + 916));
}

void FUN_00139000(void)
{
    igMetaObject_RunStaticInit(igColorAttr_Register);
}

void igColorAttr_Register(void) {
    AttrsLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igColorAttr_metaObject,
        igVisualAttribute_Register,
        igVisualAttribute_GetPublishedMetaObject,
        thunk_igColorAttr_GetMetaObject,
        igColorAttr_className,
        0x20, /* instance size */
        igColorAttr_GetVTable,
        &igColorAttr_InitFields,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void thunk_igColorAttr_GetMetaObject(void) {
    igColorAttr_GetMetaObject();
}

void igColorAttr_InitFields(void) {
    void *temp_a0;
    void *temp_v0;
    int sp40[4];
    int temp_s2;
    void *temp_s1;
    void *temp_s0;

    temp_s0 = (void *)g_igColorAttr_metaObject[0];
    temp_s2 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &g_igColorAttr_ctorTable[0], 2);
    temp_s1 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2));
    temp_a0 = (void *)(temp_s1);
    sp40[0] = 0x3F800000;
    sp40[1] = 0x3F800000;
    sp40[2] = 0x3F800000;
    sp40[3] = 0x3F800000;
    FUN_0018e670(temp_a0, sp40);
    *(int *)((char *)(temp_s1) + 48) = (int)(&FUN_0013c870);
    temp_v0 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 1));
    FUN_0030e9b0(temp_v0, -1);
    *(char *)((char *)(temp_v0) + 38) = 0;
    igMetaObject_NameFields(temp_s0, &g_igColorAttr_fieldTable[0], &DAT_00486928[0], &DAT_00486930[0], temp_s2);
}

