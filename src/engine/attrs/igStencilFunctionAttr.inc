igMetaObject *g_igStencilFunctionAttr_metaObject;
igMetaField *g_igStencilFunctionAttr_refValMetaField;
igMetaField *g_igStencilFunctionAttr_funcMetaField;
igMetaField *g_igStencilFunctionAttr_writeMaskMetaField;
igMetaField *g_igStencilFunctionAttr_readMaskMetaField;
igMetaField *g_igStencilFunctionAttr_stenFailOpMetaField;
igMetaField *g_igStencilFunctionAttr_stenPassZPassOpMetaField;
igMetaField *g_igStencilFunctionAttr_stenPassZFailOpMetaField;

void FUN_00133610(int arg0) {
    FUN_001336e0();
    igMetaObject_CreateInstance(*(igMetaObject * *)0x55EE50, (igMemoryPoolView *)arg0);
}

igMetaObject *igStencilFunctionAttr_GetMetaObject(void)
{
    igMetaObject *g = g_igStencilFunctionAttr_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_001336e0();
    return g_igStencilFunctionAttr_metaObject;
}

int igStencilFunctionAttr_GetVTable(void) {
    struct Obj_1336a0 obj;
    igObject_InitHeader((igObject *)&obj);
    obj.vt = &g_igStencilFunctionAttr_vtable[0];
    return *(int *)((char *)&obj + *(int *)((char *)g_objectSystem + 916));
}

void FUN_001336e0(void)
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
        thunk_igStencilFunctionAttr_GetMetaObject,
        "igStencilFunctionAttr",
        0x28, /* instance size */
        igStencilFunctionAttr_GetVTable,
        &igStencilFunctionAttr_InitFields,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void thunk_igStencilFunctionAttr_GetMetaObject(void) {
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
    void *temp_s1;
    int temp_s0;
    void *temp_v0;

    temp_s1 = (void *)g_igStencilFunctionAttr_metaObject;
    temp_s0 = igMetaObject_GetFieldCount((igMetaObject *)temp_s1);
    igMetaObject_CreateFields((igMetaObject *)temp_s1, g_igStencilFunctionAttr_ctorTable, 7);
    temp_v0 = (void *)(igMetaObject_GetFieldAt((igMetaObject *)temp_s1, temp_s0 + 1));
    igEnumMetaField_SetDefaultValue(temp_v0, g_igStencilFunctionAttr_funcDefault);
    *(void **)&((igEnumMetaField *)temp_v0)->_getMetaEnumFunction = (void *)FUN_00149500;
    igUnsignedIntMetaField_SetDefaultValue(igMetaObject_GetFieldAt((igMetaObject *)temp_s1, temp_s0 + 2), -1);
    igUnsignedIntMetaField_SetDefaultValue(igMetaObject_GetFieldAt((igMetaObject *)temp_s1, temp_s0 + 3), -1);
    temp_v0 = (void *)(igMetaObject_GetFieldAt((igMetaObject *)temp_s1, temp_s0 + 4));
    igEnumMetaField_SetDefaultValue(temp_v0, 0);
    *(void **)&((igEnumMetaField *)temp_v0)->_getMetaEnumFunction = (void *)FUN_001494a0;
    temp_v0 = (void *)(igMetaObject_GetFieldAt((igMetaObject *)temp_s1, temp_s0 + 5));
    igEnumMetaField_SetDefaultValue(temp_v0, 0);
    *(void **)&((igEnumMetaField *)temp_v0)->_getMetaEnumFunction = (void *)FUN_001494a0;
    temp_v0 = (void *)(igMetaObject_GetFieldAt((igMetaObject *)temp_s1, temp_s0 + 6));
    igEnumMetaField_SetDefaultValue(temp_v0, 0);
    *(void **)&((igEnumMetaField *)temp_v0)->_getMetaEnumFunction = (void *)FUN_001494a0;
    igMetaObject_NameFields((igMetaObject *)temp_s1, g_igStencilFunctionAttr_fieldTable, g_igStencilFunctionAttr_fieldHandles, g_igStencilFunctionAttr_fieldOffsets, temp_s0);
}

void **igSmartPointer_igVertexArray_Destruct(void **arg0, short arg1) {
    S_temp_a0_1338d0 *temp_a0;

    if (arg0 != 0) {
        temp_a0 = (S_temp_a0_1338d0 *)((void *)(*arg0));
        if (temp_a0 != 0) {
            temp_a0->f4 = (int)((int) (temp_a0->f4 - 1));
            if ((temp_a0->f4 & 0x7FFFFF) == 0) {
                igObject_Destroy(temp_a0);
            }
        }
        if (arg1 > 0) {
            __dl__FPv(arg0);
        }
    }
    return arg0;
}

