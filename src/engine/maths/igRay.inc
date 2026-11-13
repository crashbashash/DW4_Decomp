void FUN_00188220(int arg0) {
    FUN_00188340();
    igMetaObject_CreateInstance(*(int *)0x560FC0, arg0);
}

igMetaObject *FUN_00188260(void) {
    if (g_igRay_metaObject[0] == 0) {
        g_igRay_metaObject[0] = igMetaObject_Create(Memory_GetAllocatorBySelector(g_metadataAllocatorKey[0]));
    }
    return g_igRay_metaObject[0];
}

igMetaObject *igRay_GetMetaObject(void)
{
    igMetaObject *g = g_igRay_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_00188340();
    return g_igRay_metaObject[0];
}

int igRay_GetVTable(void) {
    struct Obj7 obj;
    igObject_InitHeader(&obj);
    obj.vt = &DAT_00527f10[0];
    return *(int *)((char *)&obj + *(int *)((char *)(g_objectSystem[0]) + 916));
}

void FUN_00188340(void)
{
    igMetaObject_RunStaticInit(igRay_Register);
}

void igRay_Register(void) {
    FUN_00186a40();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igRay_metaObject,
        igObject_Register,
        igObject_GetMetaObject_ParentAccessor,
        thunk_igRay_GetMetaObject,
        igRay_className,
        0x24, /* instance size */
        igRay_GetVTable,
        &igRay_InitFields,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void thunk_igRay_GetMetaObject(void) {
    igRay_GetMetaObject();
}

void igRay_InitFields(void) {
    int temp_s1;
    void *temp_s0;
    int temp_a0_2;
    int temp_a0;
    int sp40[4];
    int sp30[4];

    temp_s0 = (void *)g_igRay_metaObject[0];
    temp_s1 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &g_igRay_ctorTable[0], 3);
    temp_a0 = igMetaObject_GetFieldAt(temp_s0, temp_s1);
    sp40[0] = 0;
    sp40[1] = 0;
    sp40[2] = 0;
    FUN_0018e470((igVec3fMetaFieldView *)temp_a0, (const float *)&sp40[0]);
    temp_a0_2 = igMetaObject_GetFieldAt(temp_s0, temp_s1 + 1);
    sp30[0] = 0;
    sp30[1] = 0x3F800000;
    sp30[2] = 0;
    FUN_0018e470((igVec3fMetaFieldView *)temp_a0_2, (const float *)&sp30[0]);
    igMetaObject_NameFields(temp_s0, &g_igRay_fieldTable[0], &DAT_0048ade8[0], &DAT_0048adf8[0], temp_s1);
}

