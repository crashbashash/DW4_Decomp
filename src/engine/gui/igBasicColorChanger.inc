int FUN_00451fb0(void) {
    return DAT_0058c5f0[0];
}

int FUN_00451fc0(void) {
    if (DAT_0058c5f0[0] == 0) {
        DAT_0058c5f0[0] = igMetaObject_Create(Memory_GetAllocatorBySelector(DAT_00587040[0]));
    }
    return DAT_0058c5f0[0];
}

igMetaObject *igBasicColorChanger_GetMetaObject(void)
{
    igMetaObject *g = g_igBasicColorChanger_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        igBasicColorChanger_RunStaticInit();
    return g_igBasicColorChanger_metaObject[0];
}

int igBasicColorChanger_GetVTable(void) {
    struct Obj_452060 obj;
    igObject_InitHeader(&obj);
    obj.vt = &DAT_00541550[0];
    return *(int *)((char *)&obj + *(int *)((char *)(DAT_00586dc8[0]) + 916));
}

void igBasicColorChanger_RunStaticInit(void)
{
    igMetaObject_RunStaticInit(igBasicColorChanger_Register);
}

void igBasicColorChanger_Register(void) {
    GuiLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igBasicColorChanger_metaObject,
        igColorChanger_Register,
        igColorChanger_GetPublishedMetaObject,
        thunk_igBasicColorChanger_GetMetaObject,
        igBasicColorChanger_className,
        0x58, /* instance size */
        igBasicColorChanger_GetVTable,
        &igBasicColorChanger_InitFields,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void thunk_igBasicColorChanger_GetMetaObject(void) {
    igBasicColorChanger_GetMetaObject();
}

int FUN_00452130(void) {
    return DAT_0058c608[0];
}

void igBasicColorChanger_InitFields(void) {
    int temp_s1;
    void *f;
    void *temp_s0;
    temp_s0 = (void *)DAT_0058c5f0[0];
    temp_s1 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &DAT_004d0840[0], 2);
    f = igMetaObject_GetFieldAt(temp_s0, temp_s1);
    *(int *)((char *)f + 52) = 4;
    igMetaObject_NameFields(temp_s0, &DAT_004d0848[0], &DAT_004d0850[0], &DAT_004d0858[0], temp_s1);
}

