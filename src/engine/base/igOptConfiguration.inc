igMetaObject *g_igOptConfiguration_metaObject;

igMetaObject *FUN_00225dc0(void) {
    if (g_igOptConfiguration_metaObject == 0) {
        g_igOptConfiguration_metaObject = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData));
    }
    return g_igOptConfiguration_metaObject;
}

igMetaObject *igOptConfiguration_GetMetaObject(void)
{
    igMetaObject *g = g_igOptConfiguration_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_00225ea0();
    return g_igOptConfiguration_metaObject;
}

int igOptConfiguration_GetVTable(void) {
    struct Obj_3 obj;
    igObject_InitHeader((igObject *)&obj);
    obj.vt = &g_igOptConfiguration_vtable[0];
    return *(int *)((char *)&obj + g_objectSystem->vtableProbeOffset);
}

void FUN_00225ea0(void)
{
    igMetaObject_RunStaticInit((igMetaObjectRegisterFunction)igOptConfiguration_Register);
}

CallbackArray *igOptConfiguration_Register(void) {
    BaseLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_igOptConfiguration_metaObject,
        igObject_Register,
        igObject_GetMetaObject_ParentAccessor,
        thunk_igOptConfiguration_GetMetaObject,
        "igOptConfiguration",
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

