igMetaObject *g_igGuiSystemRenderer_metaObject;
igMetaField *g_igGuiSystemRenderer_rootMetaField;
igMetaField *g_igGuiSystemRenderer_modelMetaField;
igMetaField *g_igGuiSystemRenderer_commonTraversalMetaField;
igMetaField *g_igGuiSystemRenderer_displayListAttrMetaField;

igMetaObject *igGuiSystemRenderer_GetOrCreateMetaObject(void) {
    if (g_igGuiSystemRenderer_metaObject == 0) {
        g_igGuiSystemRenderer_metaObject = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData));
    }
    return g_igGuiSystemRenderer_metaObject;
}

igMetaObject *igGuiSystemRenderer_GetMetaObject(void)
{
    igMetaObject *g = g_igGuiSystemRenderer_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false)
        igGuiSystemRenderer_RunStaticInit();
    return g_igGuiSystemRenderer_metaObject;
}

int igGuiSystemRenderer_GetVTable(void) {
    struct Obj_44e750 obj;
    int t;
    igObject_InitHeader((igObject *)&obj);
    obj.w2 = 0;
    obj.vt = &g_igGuiSystemRenderer_vtable[0];
    obj.w3 = 0;
    obj.w4 = 0;
    obj.w5 = 0;
    obj.w6 = 0;
    t = *(int *)((char *)&obj + g_objectSystem->vtableProbeOffset);
    obj.vt = &g_igGuiSystemRenderer_vtable[0];
    igSmartPointer_igDisplayListAttr_Destruct((igSmartPointer<igObject> *)&obj.w6, -1);
    FUN_001d9870((void **)&obj.w5, (short)-1);
    FUN_0044e0e0((Ref **)&obj.w4, -1);
    igSmartPointer_igNode_Destruct((igSmartPointer<igObject> *)&obj.w3, -1);
    igRenderer_Destroy((igRenderer *)&obj, 0);
    return t;
}

void igGuiSystemRenderer_RunStaticInit(void)
{
    igMetaObject_RunStaticInit(igGuiSystemRenderer_Register);
}

static igMetaObjectCallback g_igGuiSystemRenderer_callbackList[] = { igNode_EnsureRegistered, igGuiSystemModel_RunStaticInit, igCommonTraversal_EnsureRegistered, igDisplayListAttr_EnsureRegistered, 0 };

CallbackArray *igGuiSystemRenderer_Register(void) {
    GuiLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_igGuiSystemRenderer_metaObject,
        Gap::Gui::igRenderer::arkRegisterInternal,
        Gap::Gui::igRenderer::getClassMeta,
        thunk_igGuiSystemRenderer_GetMetaObject,
        "igGuiSystemRenderer",
        0x1C, /* instance size */
        igGuiSystemRenderer_GetVTable,
        &igGuiSystemRenderer_InitFields,
        0, /* extra callback item */
        g_igGuiSystemRenderer_callbackList /* callback list */
    );
}

void thunk_igGuiSystemRenderer_GetMetaObject(void) {
    igGuiSystemRenderer_GetMetaObject();
}

static FieldFactory g_igGuiSystemRenderer_ctorTable[] = {
    igObjectRefMetaField_Create,
    igObjectRefMetaField_Create,
    igObjectRefMetaField_Create,
    igObjectRefMetaField_Create,
};
static const char *g_igGuiSystemRenderer_fieldTable[] = {
    "_root",
    "_model",
    "_commonTraversal",
    "_displayListAttr",
};
static igMetaField **g_igGuiSystemRenderer_fieldHandles[] = {
    &g_igGuiSystemRenderer_rootMetaField,
    &g_igGuiSystemRenderer_modelMetaField,
    &g_igGuiSystemRenderer_commonTraversalMetaField,
    &g_igGuiSystemRenderer_displayListAttrMetaField,
};
static int g_igGuiSystemRenderer_fieldOffsets[] = {
    12,
    16,
    20,
    24,
};

void igGuiSystemRenderer_InitFields(void) {
    int temp_s2;
    void *temp_s1_4;
    void *temp_s1_3;
    void *temp_s1_2;
    void *temp_s1;
    void *temp_s0;

    temp_s0 = (void *)g_igGuiSystemRenderer_metaObject;
    temp_s2 = igMetaObject_GetFieldCount((igMetaObject *)temp_s0);
    igMetaObject_CreateFields((igMetaObject *)temp_s0, g_igGuiSystemRenderer_ctorTable, 4);
    temp_s1 = (void *)(igMetaObject_GetFieldAt((igMetaObject *)temp_s0, temp_s2));
    ((igObjectRefMetaField *)temp_s1)->_metaObject = (int)(igNode_GetOrCreateMetaObject());
    temp_s1_2 = (void *)(igMetaObject_GetFieldAt((igMetaObject *)temp_s0, temp_s2 + 1));
    ((igObjectRefMetaField *)temp_s1_2)->_metaObject = (int)igGuiSystemModel_GetOrCreateMetaObject();
    temp_s1_3 = (void *)(igMetaObject_GetFieldAt((igMetaObject *)temp_s0, temp_s2 + 2));
    ((igObjectRefMetaField *)temp_s1_3)->_metaObject = (int)FUN_001a38e0();
    ((igRefMetaField *)temp_s1_3)->_construct = 1;
    temp_s1_4 = (void *)(igMetaObject_GetFieldAt((igMetaObject *)temp_s0, temp_s2 + 3));
    ((igObjectRefMetaField *)temp_s1_4)->_metaObject = (int)igDisplayListAttr_GetOrCreateMetaObject();
    igMetaObject_NameFields((igMetaObject *)temp_s0, g_igGuiSystemRenderer_fieldTable, g_igGuiSystemRenderer_fieldHandles, g_igGuiSystemRenderer_fieldOffsets, temp_s2);
}

