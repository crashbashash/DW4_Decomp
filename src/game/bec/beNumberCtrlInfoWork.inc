void FUN_0034d2b0(int arg0) {
    FUN_0034d3d0();
    igMetaObject_CreateInstance(*(int *)0x588630, arg0);
}

igMetaObject *FUN_0034d2f0(void) {
    if (g_beNumberCtrlInfoWork_metaObject[0] == 0) {
        g_beNumberCtrlInfoWork_metaObject[0] = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData[0]));
    }
    return g_beNumberCtrlInfoWork_metaObject[0];
}

igMetaObject *FUN_0034d340(void) {
    igMetaObject *g = g_beNumberCtrlInfoWork_metaObject[0];
    int t;
    if (!g || !(t = (g->_validity & 4) != 0))
        FUN_0034d3d0();
    return g_beNumberCtrlInfoWork_metaObject[0];
}

int beNumberCtrlInfoWork_GetVTable(void) {
    int obj[8];

    igObject_InitHeader(obj);
    obj[0] = (int)&DAT_00538530[0];
    return *(int *)((char *)obj + *(int *)((char *)g_objectSystem[0] + 916));
}

void FUN_0034d3d0(void)
{
    igMetaObject_RunStaticInit(beNumberCtrlInfoWork_Register);
}

void *beNumberCtrlInfoWork_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beNumberCtrlInfoWork_metaObject,
        igObject_Register,
        igObject_GetMetaObject_ParentAccessor,
        beNumberCtrlInfoWork_GetMetaObject,
        beNumberCtrlInfoWork_className,
        0x14, /* instance size */
        beNumberCtrlInfoWork_GetVTable,
        beNumberCtrlInfoWork_InitFields,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void beNumberCtrlInfoWork_GetMetaObject(void)
{
    FUN_0034d340();
}

void beNumberCtrlInfoWork_InitFields(void) {
    int temp_s1;
    void *temp_s0;

    temp_s0 = (void *)g_beNumberCtrlInfoWork_metaObject[0];
    temp_s1 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &g_beNumberCtrlInfoWork_ctorTable[0], 3);
    igIntMetaField_SetDefault(((int)igMetaObject_GetFieldAt(temp_s0, temp_s1)), -1);
    igIntMetaField_SetDefault(((int)igMetaObject_GetFieldAt(temp_s0, temp_s1 + 1)), -1);
    igIntMetaField_SetDefault(((int)igMetaObject_GetFieldAt(temp_s0, temp_s1 + 2)), -1);
    igMetaObject_NameFields(temp_s0, &g_beNumberCtrlInfoWork_fieldTable[0], &DAT_004c4920[0], &DAT_004c4930[0], temp_s1);
}

