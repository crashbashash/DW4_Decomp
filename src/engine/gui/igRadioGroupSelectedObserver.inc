igMetaObject *g_igRadioGroupSelectedObserver_metaObject;
igMetaField *g_igRadioGroupSelectedObserver_groupMetaField;

igMetaObject *igRadioGroupSelectedObserver_GetOrCreateMetaObject(void) {
    if (g_igRadioGroupSelectedObserver_metaObject == 0) {
        g_igRadioGroupSelectedObserver_metaObject = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData));
    }
    return g_igRadioGroupSelectedObserver_metaObject;
}

igMetaObject *igRadioGroupSelectedObserver_GetMetaObject(void)
{
    igMetaObject *g = g_igRadioGroupSelectedObserver_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false)
        igRadioGroupSelectedObserver_EnsureRegistered();
    return g_igRadioGroupSelectedObserver_metaObject;
}

int igRadioGroupSelectedObserver_GetVTable(void) {
    struct O o;
    igObject_InitHeader((igObject *)&o.vt);
    o.vt = g_igRadioGroupSelectedObserver_vtable;
    return *(int *)((char *)&o.vt + g_objectSystem->vtableProbeOffset);
}

void igRadioGroupSelectedObserver_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(igRadioGroupSelectedObserver_Register);
}

static igMetaObjectCallback g_igRadioGroupSelectedObserver_callbackList[] = { igRadioGroup_EnsureRegistered, 0 };

CallbackArray *igRadioGroupSelectedObserver_Register(void) {
    GuiLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_igRadioGroupSelectedObserver_metaObject,
        Gap::Gui::igView::arkRegisterInternal,
        Gap::Gui::igView::getClassMeta,
        igRadioGroupSelectedObserver_GetMetaObjectFunction,
        "igRadioGroupSelectedObserver",
        0x10, /* instance size */
        igRadioGroupSelectedObserver_GetVTable,
        &igRadioGroupSelectedObserver_InitFields,
        0, /* extra callback item */
        g_igRadioGroupSelectedObserver_callbackList /* callback list */
    );
}

void igRadioGroupSelectedObserver_GetMetaObjectFunction(void) {
    igRadioGroupSelectedObserver_GetMetaObject();
}

static FieldFactory g_igRadioGroupSelectedObserver_ctorTable[] = {
    igObjectRefMetaField_Create,
};
static const char *g_igRadioGroupSelectedObserver_fieldTable[] = {
    "_group",
};
static igMetaField **g_igRadioGroupSelectedObserver_fieldHandles[] = {
    &g_igRadioGroupSelectedObserver_groupMetaField,
};
static int g_igRadioGroupSelectedObserver_fieldOffsets[] = {
    12,
};

void igRadioGroupSelectedObserver_InitFields(void) {
    int temp_s2;
    void *temp_s1;
    void *temp_s0;

    temp_s0 = (void *)g_igRadioGroupSelectedObserver_metaObject;
    temp_s2 = igMetaObject_GetFieldCount((igMetaObject *)temp_s0);
    igMetaObject_CreateFields((igMetaObject *)temp_s0, g_igRadioGroupSelectedObserver_ctorTable, 1);
    temp_s1 = (void *)(igMetaObject_GetFieldAt((igMetaObject *)temp_s0, temp_s2));
    ((igObjectRefMetaField *)temp_s1)->_metaObject = (int)igRadioGroup_GetOrCreateMetaObject();
    ((igObjectRefMetaField *)temp_s1)->_refCounted = 0;
    igMetaObject_NameFields((igMetaObject *)temp_s0, g_igRadioGroupSelectedObserver_fieldTable, g_igRadioGroupSelectedObserver_fieldHandles, g_igRadioGroupSelectedObserver_fieldOffsets, temp_s2);
}

