igMetaObject *g_igBoundingBoxRenderer_metaObject;
igMetaField *g_igBoundingBoxRenderer_parametersMetaField;
igMetaField *g_igBoundingBoxRenderer_displayListMetaField;
igMetaField *g_igBoundingBoxRenderer_attrListMetaField;
igMetaField *g_igBoundingBoxRenderer_modelViewAttrMetaField;
igMetaField *g_igBoundingBoxRenderer_boxMetaField;
igMetaField *g_igBoundingBoxRenderer_borderMetaField;
igMetaField *g_igBoundingBoxRenderer_pathMetaField;
igMetaField *g_igBoundingBoxRenderer_drawMetaField;

igMetaObject *igBoundingBoxRenderer_GetOrCreateMetaObject(void) {
    if (g_igBoundingBoxRenderer_metaObject == 0) {
        g_igBoundingBoxRenderer_metaObject = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData));
    }
    return g_igBoundingBoxRenderer_metaObject;
}

igMetaObject *igBoundingBoxRenderer_GetMetaObject(void)
{
    igMetaObject *g = ((igMetaObject *)g_igBoundingBoxRenderer_metaObject);
    bool t;
    if (!g || (t = g->_validity & 4) == 0)
        igBoundingBoxRenderer_EnsureRegistered();
    return ((igMetaObject *)g_igBoundingBoxRenderer_metaObject);
}

int igBoundingBoxRenderer_GetVTable(void) {
    struct Obj_45df30 obj;
    int t;
    igObject_InitHeader((igObject *)&obj);
    obj.w2 = 0;
    obj.vt = &g_igBoundingBoxRenderer_vtable[0];
    obj.w3 = 0;
    obj.w4 = 0;
    obj.w5 = 0;
    obj.w6 = 0;
    obj.w7 = 0;
    obj.w8 = 0;
    obj.w9 = 0;
    t = *(int *)((char *)&obj + g_objectSystem->vtableProbeOffset);
    obj.vt = &g_igBoundingBoxRenderer_vtable[0];
    igSmartPointer_igGraphPath_Destruct((igSmartPointer<igObject> *)&obj.w9, -1);
    igSmartPointer_igGeometryAttr_Destruct((igSmartPointer<igObject> *)&obj.w8, -1);
    igSmartPointer_igGeometryAttr_Destruct((igSmartPointer<igObject> *)&obj.w7, -1);
    igSmartPointer_igModelViewMatrixAttr_Destruct((igSmartPointer<igObject> *)&obj.w6, -1);
    igSmartPointer_igAttrList_Destruct((igSmartPointer<igObject> *)&obj.w5, -1);
    igSmartPointer_igDisplayListAttr_Destruct((igSmartPointer<igObject> *)&obj.w4, -1);
    FUN_00459860((ObjectRefWord *)&obj.w3, -1);
    igRenderer_Destroy((igRenderer *)&obj, 0);
    return t;
}

void igBoundingBoxRenderer_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(igBoundingBoxRenderer_Register);
}

static igMetaObjectCallback g_igBoundingBoxRenderer_callbackList[] = { igViewerParameters_EnsureRegistered, Gap::Attrs::igDisplayListAttr::arkRegister, Gap::Attrs::igAttrList::arkRegister, Gap::Attrs::igModelViewMatrixAttr::arkRegister, igGeometryAttr_EnsureRegistered, igGraphPath_EnsureRegistered, 0 };

CallbackArray *igBoundingBoxRenderer_Register(void) {
    ViewerLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_igBoundingBoxRenderer_metaObject,
        Gap::Gui::igRenderer::arkRegisterInternal,
        Gap::Gui::igRenderer::getClassMeta,
        igBoundingBoxRenderer_GetMetaObjectFunction,
        "igBoundingBoxRenderer",
        0x2C, /* instance size */
        igBoundingBoxRenderer_GetVTable,
        &igBoundingBoxRenderer_InitFields,
        0, /* extra callback item */
        g_igBoundingBoxRenderer_callbackList /* callback list */
    );
}

void igBoundingBoxRenderer_GetMetaObjectFunction(void) {
    igBoundingBoxRenderer_GetMetaObject();
}

static FieldFactory g_igBoundingBoxRenderer_ctorTable[] = {
    igObjectRefMetaField_Create,
    igObjectRefMetaField_Create,
    igObjectRefMetaField_Create,
    igObjectRefMetaField_Create,
    igObjectRefMetaField_Create,
    igObjectRefMetaField_Create,
    igObjectRefMetaField_Create,
    igBoolMetaField_Create,
};
static const char *g_igBoundingBoxRenderer_fieldTable[] = {
    "_parameters",
    "_displayList",
    "_attrList",
    "_modelViewAttr",
    "_box",
    "_border",
    "_path",
    "_draw",
};
static igMetaField **g_igBoundingBoxRenderer_fieldHandles[] = {
    &g_igBoundingBoxRenderer_parametersMetaField,
    &g_igBoundingBoxRenderer_displayListMetaField,
    &g_igBoundingBoxRenderer_attrListMetaField,
    &g_igBoundingBoxRenderer_modelViewAttrMetaField,
    &g_igBoundingBoxRenderer_boxMetaField,
    &g_igBoundingBoxRenderer_borderMetaField,
    &g_igBoundingBoxRenderer_pathMetaField,
    &g_igBoundingBoxRenderer_drawMetaField,
};
static int g_igBoundingBoxRenderer_fieldOffsets[] = {
    12,
    16,
    20,
    24,
    28,
    32,
    36,
    40,
};

void igBoundingBoxRenderer_InitFields(void) {
    void *temp_s2;
    void *temp_s2_2;
    void *temp_s2_3;
    void *temp_s2_4;
    void *temp_s2_5;
    void *temp_s2_6;
    void *temp_s2_7;
    void *temp_s1;
    int temp_s0;

    temp_s1 = g_igBoundingBoxRenderer_metaObject;
    temp_s0 = igMetaObject_GetFieldCount((igMetaObject *)temp_s1);
    igMetaObject_CreateFields((igMetaObject *)temp_s1, g_igBoundingBoxRenderer_ctorTable, 8);
    temp_s2 = (void *)(igMetaObject_GetFieldAt((igMetaObject *)temp_s1, temp_s0));
    ((igObjectRefMetaField *)temp_s2)->_metaObject = (int)igViewerParameters_GetOrCreateMetaObject();
    temp_s2_2 = (void *)(igMetaObject_GetFieldAt((igMetaObject *)temp_s1, temp_s0 + 1));
    ((igObjectRefMetaField *)temp_s2_2)->_metaObject = (int)Gap::Attrs::igDisplayListAttr::getClassTypeLazy();
    ((igRefMetaField *)temp_s2_2)->_construct = 1;
    temp_s2_3 = (void *)(igMetaObject_GetFieldAt((igMetaObject *)temp_s1, temp_s0 + 2));
    ((igObjectRefMetaField *)temp_s2_3)->_metaObject = (int)(Gap::Attrs::igAttrList::getClassTypeLazy());
    ((igRefMetaField *)temp_s2_3)->_construct = 1;
    temp_s2_4 = (void *)(igMetaObject_GetFieldAt((igMetaObject *)temp_s1, temp_s0 + 3));
    ((igObjectRefMetaField *)temp_s2_4)->_metaObject = (int)Gap::Attrs::igModelViewMatrixAttr::getClassTypeLazy();
    ((igRefMetaField *)temp_s2_4)->_construct = 1;
    temp_s2_5 = (void *)(igMetaObject_GetFieldAt((igMetaObject *)temp_s1, temp_s0 + 4));
    ((igObjectRefMetaField *)temp_s2_5)->_metaObject = (int)igGeometryAttr_GetOrCreateMetaObject();
    temp_s2_6 = (void *)(igMetaObject_GetFieldAt((igMetaObject *)temp_s1, temp_s0 + 5));
    ((igObjectRefMetaField *)temp_s2_6)->_metaObject = (int)igGeometryAttr_GetOrCreateMetaObject();
    temp_s2_7 = (void *)(igMetaObject_GetFieldAt((igMetaObject *)temp_s1, temp_s0 + 6));
    ((igObjectRefMetaField *)temp_s2_7)->_metaObject = (int)(igGraphPath_GetOrCreateMetaObject());
    igMetaObject_NameFields((igMetaObject *)temp_s1, g_igBoundingBoxRenderer_fieldTable, g_igBoundingBoxRenderer_fieldHandles, g_igBoundingBoxRenderer_fieldOffsets, temp_s0);
}

