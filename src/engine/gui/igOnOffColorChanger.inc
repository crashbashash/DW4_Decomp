igMetaObject *g_igOnOffColorChanger_metaObject;

igMetaObject *FUN_00451e40(void) {
    if (g_igOnOffColorChanger_metaObject == 0) {
        g_igOnOffColorChanger_metaObject = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData[0]));
    }
    return g_igOnOffColorChanger_metaObject;
}

igMetaObject *igOnOffColorChanger_GetMetaObject(void)
{
    igMetaObject *g = g_igOnOffColorChanger_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false)
        igOnOffColorChanger_RunStaticInit();
    return g_igOnOffColorChanger_metaObject;
}

int igOnOffColorChanger_GetVTable(void) {
    struct Obj_451ee0 obj;

    igObject_InitHeader(&obj);
    obj.vt = &g_igOnOffColorChanger_vtable[0];
    return *(int *)((char *)&obj + *(int *)((char *)(g_objectSystem[0]) + 916));
}

void igOnOffColorChanger_RunStaticInit(void)
{
    igMetaObject_RunStaticInit(igOnOffColorChanger_Register);
}

void igOnOffColorChanger_Register(void) {
    GuiLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        &g_igOnOffColorChanger_metaObject,
        igBasicColorChanger_Register,
        igBasicColorChanger_GetPublishedMetaObject,
        thunk_igOnOffColorChanger_GetMetaObject,
        "igOnOffColorChanger",
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

