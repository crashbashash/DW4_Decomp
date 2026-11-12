int FUN_00225dc0(void) {
    if (DAT_0056d888[0] == 0) {
        DAT_0056d888[0] = igMetaObject_Create(Memory_GetAllocatorBySelector(DAT_00587040[0]));
    }
    return DAT_0056d888[0];
}

igMetaObject *igOptConfiguration_GetMetaObject(void)
{
    igMetaObject *g = g_igOptConfiguration_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_00225ea0();
    return g_igOptConfiguration_metaObject[0];
}

int igOptConfiguration_GetVTable(void) {
    struct Obj_3 obj;
    igObject_InitHeader(&obj);
    obj.vt = &DAT_0052c610[0];
    return *(int *)((char *)&obj + *(int *)((char *)(DAT_00586dc8[0]) + 916));
}

void FUN_00225ea0(void)
{
    igMetaObject_RunStaticInit(igOptConfiguration_Register);
}

void igOptConfiguration_Register(void) {
    BaseLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igOptConfiguration_metaObject,
        igObject_Register,
        igObject_GetMetaObject_ParentAccessor,
        thunk_igOptConfiguration_GetMetaObject,
        igOptConfiguration_className,
        8, /* instance size */
        igOptConfiguration_GetVTable,
        0,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void thunk_igOptConfiguration_GetMetaObject(void) {
    igOptConfiguration_GetMetaObject();
}

