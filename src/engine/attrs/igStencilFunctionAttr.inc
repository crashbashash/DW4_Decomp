igMetaObject *g_igStencilFunctionAttr_metaObject;
igMetaField *g_igStencilFunctionAttr_refValMetaField;
igMetaField *g_igStencilFunctionAttr_funcMetaField;
igMetaField *g_igStencilFunctionAttr_writeMaskMetaField;
igMetaField *g_igStencilFunctionAttr_readMaskMetaField;
igMetaField *g_igStencilFunctionAttr_stenFailOpMetaField;
igMetaField *g_igStencilFunctionAttr_stenPassZPassOpMetaField;
igMetaField *g_igStencilFunctionAttr_stenPassZFailOpMetaField;

igStencilFunctionAttr *igStencilFunctionAttr_Create(igMemoryPoolView *pool) {
    igStencilFunctionAttr_EnsureRegistered();
    return (igStencilFunctionAttr *)igMetaObject_CreateInstance(g_igStencilFunctionAttr_metaObject, pool);
}

igMetaObject *igStencilFunctionAttr_GetMetaObject(void)
{
    igMetaObject *g = g_igStencilFunctionAttr_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false)
        igStencilFunctionAttr_EnsureRegistered();
    return g_igStencilFunctionAttr_metaObject;
}

int igStencilFunctionAttr_GetVTable(void) {
    struct Obj_1336a0 obj;
    igObject_InitHeader((igObject *)&obj);
    obj.vt = &g_igStencilFunctionAttr_vtable[0];
    return *(int *)((char *)&obj + g_objectSystem->vtableProbeOffset);
}

void igStencilFunctionAttr_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(igStencilFunctionAttr_Register);
}

CallbackArray *igStencilFunctionAttr_Register(void) {
    AttrsLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_igStencilFunctionAttr_metaObject,
        igVisualAttribute_Register,
        igVisualAttribute_GetPublishedMetaObject,
        igStencilFunctionAttr_GetMetaObjectFunction,
        "igStencilFunctionAttr",
        0x28, /* instance size */
        igStencilFunctionAttr_GetVTable,
        &igStencilFunctionAttr_InitFields,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void igStencilFunctionAttr_GetMetaObjectFunction(void) {
    igStencilFunctionAttr_GetMetaObject();
}

static FieldFactory g_igStencilFunctionAttr_ctorTable[] = {
    (FieldFactory)igUnsignedIntMetaField_Create,
    (FieldFactory)igEnumMetaField_Create,
    (FieldFactory)igUnsignedIntMetaField_Create,
    (FieldFactory)igUnsignedIntMetaField_Create,
    (FieldFactory)igEnumMetaField_Create,
    (FieldFactory)igEnumMetaField_Create,
    (FieldFactory)igEnumMetaField_Create,
};
static const char *g_igStencilFunctionAttr_fieldTable[] = {
    "_refVal",
    "_func",
    "_writeMask",
    "_readMask",
    "_stenFailOp",
    "_stenPassZPassOp",
    "_stenPassZFailOp",
};
static igMetaField **g_igStencilFunctionAttr_fieldHandles[] = {
    &g_igStencilFunctionAttr_refValMetaField,
    &g_igStencilFunctionAttr_funcMetaField,
    &g_igStencilFunctionAttr_writeMaskMetaField,
    &g_igStencilFunctionAttr_readMaskMetaField,
    &g_igStencilFunctionAttr_stenFailOpMetaField,
    &g_igStencilFunctionAttr_stenPassZPassOpMetaField,
    &g_igStencilFunctionAttr_stenPassZFailOpMetaField,
};
static int g_igStencilFunctionAttr_fieldOffsets[] = {
    12,
    16,
    20,
    24,
    28,
    32,
    36,
};

int g_igStencilFunctionAttr_funcDefault = 7;

void igStencilFunctionAttr_InitFields(void) {
    void *meta;
    int base;
    void *field;

    meta = (void *)g_igStencilFunctionAttr_metaObject;
    base = igMetaObject_GetFieldCount((igMetaObject *)meta);
    igMetaObject_CreateFields((igMetaObject *)meta, g_igStencilFunctionAttr_ctorTable, 7);
    field = (void *)(igMetaObject_GetFieldAt((igMetaObject *)meta, base + 1));
    igEnumMetaField_SetDefaultValue((igMetaField *)field, g_igStencilFunctionAttr_funcDefault);
    *(void **)&((igEnumMetaField *)field)->_getMetaEnumFunction = (void *)IG_GFX_STENCIL_FUNCTION_GetMetaEnum;
    igUnsignedIntMetaField_SetDefaultValue(igMetaObject_GetFieldAt((igMetaObject *)meta, base + 2), -1);
    igUnsignedIntMetaField_SetDefaultValue(igMetaObject_GetFieldAt((igMetaObject *)meta, base + 3), -1);
    field = (void *)(igMetaObject_GetFieldAt((igMetaObject *)meta, base + 4));
    igEnumMetaField_SetDefaultValue((igMetaField *)field, 0);
    *(void **)&((igEnumMetaField *)field)->_getMetaEnumFunction = (void *)IG_GFX_STENCIL_OPERATION_GetMetaEnum;
    field = (void *)(igMetaObject_GetFieldAt((igMetaObject *)meta, base + 5));
    igEnumMetaField_SetDefaultValue((igMetaField *)field, 0);
    *(void **)&((igEnumMetaField *)field)->_getMetaEnumFunction = (void *)IG_GFX_STENCIL_OPERATION_GetMetaEnum;
    field = (void *)(igMetaObject_GetFieldAt((igMetaObject *)meta, base + 6));
    igEnumMetaField_SetDefaultValue((igMetaField *)field, 0);
    *(void **)&((igEnumMetaField *)field)->_getMetaEnumFunction = (void *)IG_GFX_STENCIL_OPERATION_GetMetaEnum;
    igMetaObject_NameFields((igMetaObject *)meta, g_igStencilFunctionAttr_fieldTable, g_igStencilFunctionAttr_fieldHandles, g_igStencilFunctionAttr_fieldOffsets, base);
}

igSmartPointer<igObject> *igSmartPointer_igVertexArray_Destruct(igSmartPointer<igObject> *self, short deleteFlag) {
    if (self) {
        igObject *object = self->p;
        if (object) {
            --object->_refCount;
            if ((object->_refCount & 0x7fffff) == 0)
                igObject_Destroy(object);
        }
        if (deleteFlag > 0) operator delete(self);
    }
    return self;
}

