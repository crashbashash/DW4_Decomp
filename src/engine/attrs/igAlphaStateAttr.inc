void FUN_0013b270(int arg0) {
    FUN_0013b390();
    igMetaObject_CreateInstance(*(int *)0x55F480, arg0);
}

int FUN_0013b2b0(void) {
    if (DAT_0055f480[0] == 0) {
        DAT_0055f480[0] = igMetaObject_Create(Memory_GetAllocatorBySelector(DAT_00587040[0]));
    }
    return DAT_0055f480[0];
}

igMetaObject *igAlphaStateAttr_GetMetaObject(void)
{
    igMetaObject *g = g_igAlphaStateAttr_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_0013b390();
    return g_igAlphaStateAttr_metaObject[0];
}

int igAlphaStateAttr_GetVTable(void) {
    struct Obj obj;
    igObject_InitHeader(&obj);
    obj.vt = &DAT_00524300[0];
    return *(int *)((char *)&obj + *(int *)((char *)(DAT_00586dc8[0]) + 916));
}

void FUN_0013b390(void)
{
    igMetaObject_RunStaticInit(igAlphaStateAttr_Register);
}

void igAlphaStateAttr_Register(void) {
    AttrsLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igAlphaStateAttr_metaObject,
        igVisualAttribute_Register,
        igVisualAttribute_GetPublishedMetaObject,
        thunk_igAlphaStateAttr_GetMetaObject,
        igAlphaStateAttr_className,
        0x10, /* instance size */
        igAlphaStateAttr_GetVTable,
        &igAlphaStateAttr_InitFields,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void thunk_igAlphaStateAttr_GetMetaObject(void) {
    igAlphaStateAttr_GetMetaObject();
}

void igAlphaStateAttr_InitFields(void) {
    int temp_s1;
    void *temp_s0;

    temp_s0 = (void *)DAT_0055f480[0];
    temp_s1 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &DAT_00486c70[0], 1);
    igMetaObject_NameFields(temp_s0, &DAT_00486c78[0], &DAT_00486c80[0], &DAT_00486c88[0], temp_s1);
}

