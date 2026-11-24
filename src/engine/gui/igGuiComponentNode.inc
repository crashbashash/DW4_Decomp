igMetaObject *g_igGuiComponentNode_metaObject;
igMetaField *g_igGuiComponentNode_componentMetaField;

igMetaObject *igGuiComponentNode_GetOrCreateMetaObject(void) {
    if (g_igGuiComponentNode_metaObject == 0) {
        g_igGuiComponentNode_metaObject = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData));
    }
    return g_igGuiComponentNode_metaObject;
}

igMetaObject *igGuiComponentNode_GetMetaObject(void)
{
    igMetaObject *g = g_igGuiComponentNode_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false)
        igGuiComponentNode_RunStaticInit();
    return g_igGuiComponentNode_metaObject;
}

int igGuiComponentNode_GetVTable(void) {
    struct Obj_44f5e0 obj;
    int t;
    igObject_InitHeader((igObject *)&obj);
    obj.w2 = 0;
    obj.w3 = 0;
    obj.w4 = 0;
    obj.w7 = 0;
    obj.vt = &g_igGuiComponentNode_vtable[0];
    t = *(int *)((char *)&obj + g_objectSystem->vtableProbeOffset);
    obj.vt = &g_igGuiComponentNode_vtable[0];
    igGroup_Destroy((igGroup *)&obj, 0);
    return t;
}

void igGuiComponentNode_RunStaticInit(void)
{
    igMetaObject_RunStaticInit(igGuiComponentNode_Register);
}

static igMetaObjectCallback g_igGuiComponentNode_callbackList[] = { Gap::Gui::igGuiComponent::arkRegister, 0 };

CallbackArray *igGuiComponentNode_Register(void) {
    GuiLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_igGuiComponentNode_metaObject,
        Gap::Sg::igGroup::arkRegisterInternal,
        Gap::Sg::igGroup::getClassMeta,
        thunk_igGuiComponentNode_GetMetaObject,
        "igGuiComponentNode",
        0x24, /* instance size */
        igGuiComponentNode_GetVTable,
        &igGuiComponentNode_InitFields,
        0, /* extra callback item */
        g_igGuiComponentNode_callbackList /* callback list */
    );
}

void thunk_igGuiComponentNode_GetMetaObject(void) {
    igGuiComponentNode_GetMetaObject();
}

static FieldFactory g_igGuiComponentNode_ctorTable[] = {
    igObjectRefMetaField_Create,
};
static const char *g_igGuiComponentNode_fieldTable[] = {
    "_component",
};
static igMetaField **g_igGuiComponentNode_fieldHandles[] = {
    &g_igGuiComponentNode_componentMetaField,
};
static int g_igGuiComponentNode_fieldOffsets[] = {
    32,
};

void igGuiComponentNode_InitFields(void) {
    int temp_s2;
    void *temp_s1;
    void *temp_s0;

    temp_s0 = (void *)g_igGuiComponentNode_metaObject;
    temp_s2 = igMetaObject_GetFieldCount((igMetaObject *)temp_s0);
    igMetaObject_CreateFields((igMetaObject *)temp_s0, g_igGuiComponentNode_ctorTable, 1);
    temp_s1 = (void *)(igMetaObject_GetFieldAt((igMetaObject *)temp_s0, temp_s2));
    ((igObjectRefMetaField *)temp_s1)->_metaObject = (int)Gap::Gui::igGuiComponent::getClassTypeLazy();
    ((igObjectRefMetaField *)temp_s1)->_refCounted = 0;
    igMetaObject_NameFields((igMetaObject *)temp_s0, g_igGuiComponentNode_fieldTable, g_igGuiComponentNode_fieldHandles, g_igGuiComponentNode_fieldOffsets, temp_s2);
}

