int FUN_00451e40(void) {
    if (DAT_0058c5e8[0] == 0) {
        DAT_0058c5e8[0] = igMetaObject_Create(Memory_GetAllocatorBySelector(DAT_00587040[0]));
    }
    return DAT_0058c5e8[0];
}

igMetaObject *igOnOffColorChanger_GetMetaObject(void)
{
    igMetaObject *g = g_igOnOffColorChanger_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        igOnOffColorChanger_RunStaticInit();
    return g_igOnOffColorChanger_metaObject[0];
}

int igOnOffColorChanger_GetVTable(void) {
    struct Obj_451ee0 obj;

    igObject_InitHeader(&obj);
    obj.vt = &DAT_005414f0[0];
    return *(int *)((char *)&obj + *(int *)((char *)(DAT_00586dc8[0]) + 916));
}

void igOnOffColorChanger_RunStaticInit(void)
{
    igMetaObject_RunStaticInit(igOnOffColorChanger_Register);
}

void igOnOffColorChanger_Register(void) {
    GuiLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igOnOffColorChanger_metaObject,
        igBasicColorChanger_Register,
        igBasicColorChanger_GetPublishedMetaObject,
        thunk_igOnOffColorChanger_GetMetaObject,
        igOnOffColorChanger_className,
        0x58, /* instance size */
        igOnOffColorChanger_GetVTable,
        0,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void thunk_igOnOffColorChanger_GetMetaObject(void) {
    igOnOffColorChanger_GetMetaObject();
}

