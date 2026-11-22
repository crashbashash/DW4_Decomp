igMetaObject *g_igNormalsRenderer_metaObject;
igMetaField *g_igNormalsRenderer_parametersMetaField;
igMetaField *g_igNormalsRenderer_attrListMetaField;
igMetaField *g_igNormalsRenderer_defaultAttrListMetaField;
igMetaField *g_igNormalsRenderer_modelViewAttrMetaField;
igMetaField *g_igNormalsRenderer_colorAttrMetaField;
igMetaField *g_igNormalsRenderer_normalsMetaField;
igMetaField *g_igNormalsRenderer_invalidStoredNormalsMetaField;
igMetaField *g_igNormalsRenderer_pathMetaField;
igMetaField *g_igNormalsRenderer_drawMetaField;

igMetaObject *igNormalsRenderer_GetOrCreateMetaObject(void) {
    if (g_igNormalsRenderer_metaObject == 0) {
        g_igNormalsRenderer_metaObject = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData));
    }
    return g_igNormalsRenderer_metaObject;
}

void *igNormalsRenderer_GetMetaObject(void) {
    igMetaObject *g = g_igNormalsRenderer_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false) {
        igNormalsRenderer_EnsureRegistered();
    }
    return g_igNormalsRenderer_metaObject;
}

int igNormalsRenderer_GetVTable(void) {
    struct Obj_45d8d0 obj;
    int t;
    igObject_InitHeader((igObject *)&obj);
    obj.w2 = 0;
    obj.vt = &g_igNormalsRenderer_vtable[0];
    obj.w3 = 0;
    obj.w4 = 0;
    obj.w5 = 0;
    obj.w6 = 0;
    obj.w7 = 0;
    obj.w8 = 0;
    obj.w10 = 0;
    t = *(int *)((char *)&obj + g_objectSystem->vtableProbeOffset);
    obj.vt = &g_igNormalsRenderer_vtable[0];
    igSmartPointer_igGraphPath_Destruct((igSmartPointer<igObject> *)&obj.w10, -1);
    FUN_00136e10((void **)&obj.w8, -1);
    igSmartPointer_igColorAttr_Destruct((igSmartPointer<igObject> *)&obj.w7, -1);
    igSmartPointer_igModelViewMatrixAttr_Destruct((igSmartPointer<igObject> *)&obj.w6, -1);
    igSmartPointer_igAttrList_Destruct((igSmartPointer<igObject> *)&obj.w5, -1);
    igSmartPointer_igAttrList_Destruct((igSmartPointer<igObject> *)&obj.w4, -1);
    FUN_00459860((ObjectRefWord *)&obj.w3, -1);
    igRenderer_Destroy((igRenderer *)&obj, 0);
    return t;
}

void igNormalsRenderer_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(igNormalsRenderer_Register);
}

static igMetaObjectCallback g_igNormalsRenderer_callbackList[] = { igViewerParameters_EnsureRegistered, Gap::Attrs::igAttrList::arkRegister, Gap::Attrs::igModelViewMatrixAttr::arkRegister, Gap::Attrs::igColorAttr::arkRegister, Gap::Attrs::igGeometryAttrList::arkRegister, igGraphPath_EnsureRegistered, 0 };

CallbackArray *igNormalsRenderer_Register(void) {
    ViewerLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_igNormalsRenderer_metaObject,
        Gap::Gui::igRenderer::arkRegisterInternal,
        Gap::Gui::igRenderer::getClassMeta,
        igNormalsRenderer_GetMetaObjectFunction,
        "igNormalsRenderer",
        0x30, /* instance size */
        igNormalsRenderer_GetVTable,
        &igNormalsRenderer_InitFields,
        0, /* extra callback item */
        g_igNormalsRenderer_callbackList /* callback list */
    );
}

void igNormalsRenderer_GetMetaObjectFunction(void) {
    igNormalsRenderer_GetMetaObject();
}

static FieldFactory g_igNormalsRenderer_ctorTable[] = {
    igObjectRefMetaField_Create,
    igObjectRefMetaField_Create,
    igObjectRefMetaField_Create,
    igObjectRefMetaField_Create,
    igObjectRefMetaField_Create,
    igObjectRefMetaField_Create,
    igBoolMetaField_Create,
    igObjectRefMetaField_Create,
    igBoolMetaField_Create,
};
static const char *g_igNormalsRenderer_fieldTable[] = {
    "_parameters",
    "_attrList",
    "_defaultAttrList",
    "_modelViewAttr",
    "_colorAttr",
    "_normals",
    "_invalidStoredNormals",
    "_path",
    "_draw",
};
static igMetaField **g_igNormalsRenderer_fieldHandles[] = {
    &g_igNormalsRenderer_parametersMetaField,
    &g_igNormalsRenderer_attrListMetaField,
    &g_igNormalsRenderer_defaultAttrListMetaField,
    &g_igNormalsRenderer_modelViewAttrMetaField,
    &g_igNormalsRenderer_colorAttrMetaField,
    &g_igNormalsRenderer_normalsMetaField,
    &g_igNormalsRenderer_invalidStoredNormalsMetaField,
    &g_igNormalsRenderer_pathMetaField,
    &g_igNormalsRenderer_drawMetaField,
};
static int g_igNormalsRenderer_fieldOffsets[] = {
    12,
    16,
    20,
    24,
    28,
    32,
    36,
    40,
    44,
};

void igNormalsRenderer_InitFields(void) {
    int temp_s0;
    void *temp_s2;
    void *temp_s2_2;
    void *temp_s2_3;
    void *temp_s2_4;
    void *temp_s2_5;
    void *temp_s2_6;
    void *temp_s2_7;
    void *temp_s1;

    temp_s1 = g_igNormalsRenderer_metaObject;
    temp_s0 = igMetaObject_GetFieldCount((igMetaObject *)temp_s1);
    igMetaObject_CreateFields((igMetaObject *)temp_s1, g_igNormalsRenderer_ctorTable, 9);
    temp_s2 = (void *)(igMetaObject_GetFieldAt((igMetaObject *)temp_s1, temp_s0));
    ((igObjectRefMetaField *)temp_s2)->_metaObject = (int)igViewerParameters_GetOrCreateMetaObject();
    temp_s2_2 = (void *)(igMetaObject_GetFieldAt((igMetaObject *)temp_s1, temp_s0 + 1));
    ((igObjectRefMetaField *)temp_s2_2)->_metaObject = (int)(Gap::Attrs::igAttrList::getClassTypeLazy());
    ((igRefMetaField *)temp_s2_2)->_construct = 1;
    temp_s2_3 = (void *)(igMetaObject_GetFieldAt((igMetaObject *)temp_s1, temp_s0 + 2));
    ((igObjectRefMetaField *)temp_s2_3)->_metaObject = (int)(Gap::Attrs::igAttrList::getClassTypeLazy());
    ((igRefMetaField *)temp_s2_3)->_construct = 1;
    temp_s2_4 = (void *)(igMetaObject_GetFieldAt((igMetaObject *)temp_s1, temp_s0 + 3));
    ((igObjectRefMetaField *)temp_s2_4)->_metaObject = (int)Gap::Attrs::igModelViewMatrixAttr::getClassTypeLazy();
    ((igRefMetaField *)temp_s2_4)->_construct = 1;
    temp_s2_5 = (void *)(igMetaObject_GetFieldAt((igMetaObject *)temp_s1, temp_s0 + 4));
    ((igObjectRefMetaField *)temp_s2_5)->_metaObject = (int)(Gap::Attrs::igColorAttr::getClassTypeLazy());
    ((igRefMetaField *)temp_s2_5)->_construct = 1;
    temp_s2_6 = (void *)(igMetaObject_GetFieldAt((igMetaObject *)temp_s1, temp_s0 + 5));
    ((igObjectRefMetaField *)temp_s2_6)->_metaObject = (int)(Gap::Attrs::igGeometryAttrList::getClassTypeLazy());
    ((igRefMetaField *)temp_s2_6)->_construct = 1;
    temp_s2_7 = (void *)(igMetaObject_GetFieldAt((igMetaObject *)temp_s1, temp_s0 + 7));
    ((igObjectRefMetaField *)temp_s2_7)->_metaObject = (int)(igGraphPath_GetOrCreateMetaObject());
    igMetaObject_NameFields((igMetaObject *)temp_s1, g_igNormalsRenderer_fieldTable, g_igNormalsRenderer_fieldHandles, g_igNormalsRenderer_fieldOffsets, temp_s0);
}

