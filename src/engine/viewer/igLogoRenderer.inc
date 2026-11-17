igMetaObject *g_igLogoRenderer_metaObject;
igMetaField *g_igLogoRenderer_timeMetaField;
igMetaField *g_igLogoRenderer_geometryAttrMetaField;
igMetaField *g_igLogoRenderer_colorAttrMetaField;
igMetaField *g_igLogoRenderer_attrListMetaField;

void FUN_0045dbe0(int arg0) {
    FUN_0045dd20();
    igMetaObject_CreateInstance(g_igLogoRenderer_metaObject, (igMemoryPoolView *)arg0);
}

SigLogoRenderer_GetMetaObject *igLogoRenderer_GetMetaObject(void) {
    if (((SigLogoRenderer_GetMetaObject *)g_igLogoRenderer_metaObject) == 0 || !((SigLogoRenderer_GetMetaObject *)g_igLogoRenderer_metaObject)->ok()) FUN_0045dd20();
    return ((SigLogoRenderer_GetMetaObject *)g_igLogoRenderer_metaObject);
}

int igLogoRenderer_GetVTable(void) {
    struct Obj_45dc70 obj;
    int t;
    igObject_InitHeader((igObject *)&obj);
    obj.w2 = 0;
    obj.vt = &g_igLogoRenderer_vtable[0];
    obj.w6 = 0;
    obj.w7 = 0;
    obj.w8 = 0;
    t = *(int *)((char *)&obj + *(int *)((char *)(((void *)g_objectSystem)) + 916));
    obj.vt = &g_igLogoRenderer_vtable[0];
    igSmartPointer_igAttrList_Destruct((igSmartPointer<igObject> *)&obj.w8, -1);
    igSmartPointer_igColorAttr_Destruct((igSmartPointer<igObject> *)&obj.w7, -1);
    FUN_001353b0(&obj.w6, -1);
    FUN_00230f70(&obj, 0);
    return t;
}

void FUN_0045dd20(void)
{
    igMetaObject_RunStaticInit(igLogoRenderer_Register);
}

static igMetaObjectCallback g_igLogoRenderer_callbackList[] = { FUN_001378f0, igColorAttr_EnsureRegistered, igAttrList_EnsureRegistered, 0 };

CallbackArray *igLogoRenderer_Register(void) {
    ViewerLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_igLogoRenderer_metaObject,
        igRenderer_Register,
        igRenderer_GetPublishedMetaObject,
        thunk_igLogoRenderer_GetMetaObject,
        "igLogoRenderer",
        0x28, /* instance size */
        igLogoRenderer_GetVTable,
        &igLogoRenderer_InitFields,
        0, /* extra callback item */
        g_igLogoRenderer_callbackList /* callback list */
    );
}

void thunk_igLogoRenderer_GetMetaObject(void) {
    igLogoRenderer_GetMetaObject();
}

static FieldFactory g_igLogoRenderer_ctorTable[] = {
    igLongMetaField_Create,
    igObjectRefMetaField_Create,
    igObjectRefMetaField_Create,
    igObjectRefMetaField_Create,
};
static const char *g_igLogoRenderer_fieldTable[] = {
    "_time",
    "_geometryAttr",
    "_colorAttr",
    "_attrList",
};
static igMetaField **g_igLogoRenderer_fieldHandles[] = {
    &g_igLogoRenderer_timeMetaField,
    &g_igLogoRenderer_geometryAttrMetaField,
    &g_igLogoRenderer_colorAttrMetaField,
    &g_igLogoRenderer_attrListMetaField,
};
static int g_igLogoRenderer_fieldOffsets[] = {
    16,
    24,
    28,
    32,
};

void igLogoRenderer_InitFields(void) {
    int temp_s2;
    void *temp_s1;
    void *temp_s1_2;
    void *temp_s1_3;
    void *temp_s0;

    temp_s0 = g_igLogoRenderer_metaObject;
    temp_s2 = igMetaObject_GetFieldCount((igMetaObject *)temp_s0);
    igMetaObject_CreateFields((igMetaObject *)temp_s0, g_igLogoRenderer_ctorTable, 4);
    temp_s1 = (void *)(igMetaObject_GetFieldAt((igMetaObject *)temp_s0, temp_s2 + 1));
    ((igObjectRefMetaField *)temp_s1)->_metaObject = FUN_00137850();
    temp_s1_2 = (void *)(igMetaObject_GetFieldAt((igMetaObject *)temp_s0, temp_s2 + 2));
    ((igObjectRefMetaField *)temp_s1_2)->_metaObject = (int)(igColorAttr_GetOrCreateMetaObject());
    ((igRefMetaField *)temp_s1_2)->_construct = 1;
    temp_s1_3 = (void *)(igMetaObject_GetFieldAt((igMetaObject *)temp_s0, temp_s2 + 3));
    ((igObjectRefMetaField *)temp_s1_3)->_metaObject = (int)(igAttrList_GetOrCreateMetaObject());
    ((igRefMetaField *)temp_s1_3)->_construct = 1;
    igMetaObject_NameFields((igMetaObject *)temp_s0, g_igLogoRenderer_fieldTable, g_igLogoRenderer_fieldHandles, g_igLogoRenderer_fieldOffsets, temp_s2);
}

