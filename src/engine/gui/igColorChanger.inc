int FUN_004521d0(void) {
    if (DAT_0058c608[0] == 0) {
        DAT_0058c608[0] = igMetaObject_Create(Memory_GetAllocatorBySelector(DAT_00587040[0]));
    }
    return DAT_0058c608[0];
}

igMetaObject *igColorChanger_GetMetaObject(void)
{
    igMetaObject *g = g_igColorChanger_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        igColorChanger_RunStaticInit();
    return g_igColorChanger_metaObject[0];
}

int igColorChanger_GetVTable(void) {
    struct Obj_452270 obj;
    igObject_InitHeader(&obj);
    obj.vt = &DAT_005415b0[0];
    return *(int *)((char *)&obj + *(int *)((char *)(DAT_00586dc8[0]) + 916));
}

void igColorChanger_RunStaticInit(void)
{
    igMetaObject_RunStaticInit(igColorChanger_Register);
}

void igColorChanger_Register(void) {
    GuiLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igColorChanger_metaObject,
        igObject_Register,
        igObject_GetMetaObject_ParentAccessor,
        thunk_igColorChanger_GetMetaObject,
        igColorChanger_className,
        8, /* instance size */
        igColorChanger_GetVTable,
        0,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void thunk_igColorChanger_GetMetaObject(void) {
    igColorChanger_GetMetaObject();
}

