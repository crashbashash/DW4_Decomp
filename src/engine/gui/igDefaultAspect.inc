igMetaObject *g_igDefaultAspect_metaObject;
igMetaField *g_igDefaultAspect_elementListMetaField;

igMetaObject *FUN_004516e0(void) {
    if (g_igDefaultAspect_metaObject == 0) {
        g_igDefaultAspect_metaObject = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData));
    }
    return g_igDefaultAspect_metaObject;
}

igMetaObject *igDefaultAspect_GetMetaObject(void)
{
    igMetaObject *g = g_igDefaultAspect_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false)
        igDefaultAspect_EnsureRegistered();
    return g_igDefaultAspect_metaObject;
}

int igDefaultAspect_GetVTable(void) {
    Obj_451780 obj;
    int r;

    igObject_InitHeader((igObject *)&obj);
    obj.vt = &g_igDefaultAspect_vtable[0];
    obj.ref = 0;
    r = *(int *)((char *)&obj + g_objectSystem->vtableProbeOffset);
    obj.vt = &g_igDefaultAspect_vtable[0];
    obj.release();
    return r;
}

void igDefaultAspect_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(igDefaultAspect_Register);
}

static igMetaObjectCallback g_igDefaultAspect_callbackList[] = { igDefaultAspectElementList_EnsureRegistered, 0 };

CallbackArray *igDefaultAspect_Register(void) {
    GuiLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_igDefaultAspect_metaObject,
        igGuiComponentAspect_Register,
        igGuiComponentAspect_GetPublishedMetaObject,
        thunk_igDefaultAspect_GetMetaObject,
        "igDefaultAspect",
        0x2C, /* instance size */
        igDefaultAspect_GetVTable,
        &igDefaultAspect_InitFields,
        0, /* extra callback item */
        g_igDefaultAspect_callbackList /* callback list */
    );
}

void thunk_igDefaultAspect_GetMetaObject(void) {
    igDefaultAspect_GetMetaObject();
}

static FieldFactory g_igDefaultAspect_ctorTable[] = {
    igObjectRefMetaField_Create,
};
static const char *g_igDefaultAspect_fieldTable[] = {
    "_elementList",
};
static igMetaField **g_igDefaultAspect_fieldHandles[] = {
    &g_igDefaultAspect_elementListMetaField,
};
static int g_igDefaultAspect_fieldOffsets[] = {
    40,
};

void igDefaultAspect_InitFields(void) {
    int temp_s2;
    void *temp_s1;
    void *temp_s0;

    temp_s0 = (void *)g_igDefaultAspect_metaObject;
    temp_s2 = igMetaObject_GetFieldCount((igMetaObject *)temp_s0);
    igMetaObject_CreateFields((igMetaObject *)temp_s0, g_igDefaultAspect_ctorTable, 1);
    temp_s1 = (void *)(igMetaObject_GetFieldAt((igMetaObject *)temp_s0, temp_s2));
    ((igObjectRefMetaField *)temp_s1)->_metaObject = (int)FUN_00451950();
    ((igRefMetaField *)temp_s1)->_construct = 1;
    igMetaObject_NameFields((igMetaObject *)temp_s0, g_igDefaultAspect_fieldTable, g_igDefaultAspect_fieldHandles, g_igDefaultAspect_fieldOffsets, temp_s2);
}

