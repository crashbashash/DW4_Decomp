void FUN_00135190(int arg0) {
    FUN_001352b0();
    igMetaObject_CreateInstance(*(int *)0x55EFD0, arg0);
}

int FUN_001351d0(void) {
    if (DAT_0055efd0[0] == 0) {
        DAT_0055efd0[0] = igMetaObject_Create(Memory_GetAllocatorBySelector(DAT_00587040[0]));
    }
    return DAT_0055efd0[0];
}

igMetaObject *igMultiPassStateAttr_GetMetaObject(void)
{
    igMetaObject *g = g_igMultiPassStateAttr_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_001352b0();
    return g_igMultiPassStateAttr_metaObject[0];
}

int igMultiPassStateAttr_GetVTable(void) {
    struct O_135270 o;
    igObject_InitHeader(&o.vt);
    o.vt = DAT_00523390;
    return *(int *)((char *)&o.vt + *(int *)(DAT_00586dc8[0] + 916));
}

void FUN_001352b0(void)
{
    igMetaObject_RunStaticInit(igMultiPassStateAttr_Register);
}

void igMultiPassStateAttr_Register(void) {
    AttrsLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igMultiPassStateAttr_metaObject,
        igVisualAttribute_Register,
        igVisualAttribute_GetPublishedMetaObject,
        thunk_igMultiPassStateAttr_GetMetaObject,
        igMultiPassStateAttr_className,
        0x10, /* instance size */
        igMultiPassStateAttr_GetVTable,
        &igMultiPassStateAttr_InitFields,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void thunk_igMultiPassStateAttr_GetMetaObject(void) {
    igMultiPassStateAttr_GetMetaObject();
}

void igMultiPassStateAttr_InitFields(void) {
    int temp_s1;
    void *temp_s0;

    temp_s0 = (void *)DAT_0055efd0[0];
    temp_s1 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &DAT_00486200[0], 1);
    igMetaObject_NameFields(temp_s0, &DAT_00486208[0], &DAT_00486210[0], &DAT_00486218[0], temp_s1);
}

