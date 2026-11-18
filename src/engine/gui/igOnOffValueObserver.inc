igMetaObject *g_igOnOffValueObserver_metaObject;
igMetaField *g_igOnOffValueObserver_groupMetaField;

igMetaObject *igOnOffValueObserver_GetMetaObject(void)
{
    igMetaObject *g = g_igOnOffValueObserver_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false)
        igOnOffValueObserver_EnsureRegistered();
    return g_igOnOffValueObserver_metaObject;
}

int igOnOffValueObserver_GetVTable(void) {
    struct Obj_44ca40 obj;
    igObject_InitHeader((igObject *)&obj);
    obj.vt = &g_igOnOffValueObserver_vtable[0];
    return *(int *)((char *)&obj + g_objectSystem->vtableProbeOffset);
}

void igOnOffValueObserver_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(igOnOffValueObserver_Register);
}

static igMetaObjectCallback g_igOnOffValueObserver_callbackList[] = { igRadioGroup_EnsureRegistered, 0 };

CallbackArray *igOnOffValueObserver_Register(void) {
    GuiLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_igOnOffValueObserver_metaObject,
        igView_Register,
        igView_GetPublishedMetaObject,
        thunk_igOnOffValueObserver_GetMetaObject,
        "igOnOffValueObserver",
        0x10, /* instance size */
        igOnOffValueObserver_GetVTable,
        &igOnOffValueObserver_InitFields,
        0, /* extra callback item */
        g_igOnOffValueObserver_callbackList /* callback list */
    );
}

void thunk_igOnOffValueObserver_GetMetaObject(void) {
    igOnOffValueObserver_GetMetaObject();
}

igMetaObject *FUN_0044cb20(void) {
    return g_igView_metaObject;
}

static FieldFactory g_igOnOffValueObserver_ctorTable[] = {
    igObjectRefMetaField_Create,
};
static const char *g_igOnOffValueObserver_fieldTable[] = {
    "_group",
};
static igMetaField **g_igOnOffValueObserver_fieldHandles[] = {
    &g_igOnOffValueObserver_groupMetaField,
};
static int g_igOnOffValueObserver_fieldOffsets[] = {
    12,
};

void igOnOffValueObserver_InitFields(void) {
    int temp_s2;
    void *temp_s1;
    void *temp_s0;

    temp_s0 = (void *)g_igOnOffValueObserver_metaObject;
    temp_s2 = igMetaObject_GetFieldCount((igMetaObject *)temp_s0);
    igMetaObject_CreateFields((igMetaObject *)temp_s0, g_igOnOffValueObserver_ctorTable, 1);
    temp_s1 = (void *)(igMetaObject_GetFieldAt((igMetaObject *)temp_s0, temp_s2));
    ((igObjectRefMetaField *)temp_s1)->_metaObject = (int)FUN_0044cdf0();
    ((igObjectRefMetaField *)temp_s1)->_refCounted = 0;
    igMetaObject_NameFields((igMetaObject *)temp_s0, g_igOnOffValueObserver_fieldTable, g_igOnOffValueObserver_fieldHandles, g_igOnOffValueObserver_fieldOffsets, temp_s2);
}

