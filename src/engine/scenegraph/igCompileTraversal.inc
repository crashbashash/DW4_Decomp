void *FUN_001a2ef0(int arg0) {
    igCompileTraversal_EnsureRegistered();
    return (void *)igMetaObject_CreateInstance((igMetaObject *)g_igCompileTraversal_metaObject, (igMemoryPoolView *)arg0);
}

igMetaObject *g_igCompileTraversal_metaObject;
igMetaField *g_igCompileTraversal_mvmListMetaField;
igMetaField *g_igCompileTraversal_xformInfoListMetaField;
igMetaField *g_igCompileTraversal_moListMetaField;
igMetaField *g_igCompileTraversal_containsShaderMetaField;
igMetaField *g_igCompileTraversal_boundMetaField;
igMetaField *g_igCompileTraversal_transformListMetaField;
igMetaField *g_igCompileTraversal_isSkinMetaField;
igMetaField *g_igCompileTraversal_environmentShader2ListMetaField;
igMetaField *g_igCompileTraversal_bmpaListMetaField;
igMetaField *g_igCompileTraversal_jointChainCountMetaField;
igMetaField *g_igCompileTraversal_jointBaseMvmIndexMetaField;
igMetaField *g_igCompileTraversal_currentBoneIndexMetaField;

igMetaObject *igCompileTraversal_GetMetaObject(void)
{
    igMetaObject *g = g_igCompileTraversal_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false)
        igCompileTraversal_EnsureRegistered();
    return g_igCompileTraversal_metaObject;
}

int igCompileTraversal_GetVTable(void) {
    union U_1a2f80 u;
    int temp_s5;
    char *p6, *p5, *p4, *p3, *p2, *p1, *p0;
    FUN_001a10a0((igCommonTraversal *)u.b);
    u.vt = (int)&g_igCompileTraversal_vtable[0];
    p0 = &u.b[472]; igSmartPointer_igModelViewMatrixAttrList_Construct((int *)p0);
    p1 = &u.b[476]; igSmartPointer_igCompiledTransformList_Construct((int *)p1);
    p2 = &u.b[480]; igSmartPointer_igNonRefCountedMatrixObjectList_Construct((int *)p2);
    p3 = &u.b[488]; igSmartPointer_igAABox_Construct((int *)p3);
    p4 = &u.b[492]; igSmartPointer_igNonRefCountedTransformList_Construct((int *)p4);
    p5 = &u.b[500]; igSmartPointer_igEnvironmentMapShader2List_Construct((int *)p5);
    p6 = &u.b[504]; igSmartPointer_igBlendMatrixPaletteAttrList_Construct((int *)p6);
    temp_s5 = *(int *)&u.b[g_objectSystem->vtableProbeOffset];
    u.vt = (int)&DAT_00529320[4];
    igSmartPointer_igBlendMatrixPaletteAttrList_Destruct((struct R * *)p6, -1);
    igSmartPointer_igEnvironmentMapShader2List_Destruct((ObjectRefWord *)p5, -1);
    igSmartPointer_igNonRefCountedTransformList_Destruct((struct Ref * *)p4, -1);
    igSmartPointer_igAABox_Destruct((igSmartPointer<igObject> *)p3, -1);
    igSmartPointer_igNonRefCountedMatrixObjectList_Destruct((void * *)p2, -1);
    igSmartPointer_igCompiledTransformList_Destruct((void * *)p1, -1);
    igSmartPointer_igModelViewMatrixAttrList_Destruct((struct R * *)p0, -1);
    FUN_001a0910((Obj_19fde0 *)u.b, 0);
    return temp_s5;
}

struct R **igSmartPointer_igBlendMatrixPaletteAttrList_Destruct(struct R **arg0, short arg1) {
    struct R *temp_a0;

    if (arg0 != 0) {
        temp_a0 = *arg0;
        if (temp_a0 != 0) {
            temp_a0->rc = temp_a0->rc - 1;
            if ((temp_a0->rc & 0x7FFFFF) == 0) {
                igObject_Destroy((igObject *)temp_a0);
            }
        }
        if (arg1 > 0) {
            operator delete(arg0);
        }
    }
    return arg0;
}

int *igSmartPointer_igBlendMatrixPaletteAttrList_Construct(int *p)
{
    *(int *)((char *)p + 0) = 0;
    return p;
}

void igCompileTraversal_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(igCompileTraversal_Register);
}

static igMetaObjectCallback g_igCompileTraversal_callbackList[] = { Gap::Attrs::igModelViewMatrixAttrList::arkRegister, igCompiledTransformList_EnsureRegistered, igNonRefCountedMatrixObjectList_EnsureRegistered, igAABox_EnsureRegistered, igNonRefCountedTransformList_EnsureRegistered, igEnvironmentMapShader2List_EnsureRegistered, Gap::Attrs::igBlendMatrixPaletteAttrList::arkRegister, 0 };

CallbackArray *igCompileTraversal_Register(void) {
    SceneGraphLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_igCompileTraversal_metaObject,
        Gap::Sg::igCommonTraversal::arkRegisterInternal,
        Gap::Sg::igCommonTraversal::getClassMeta,
        igCompileTraversal_GetMetaObjectFunction,
        "igCompileTraversal",
        0x208, /* instance size */
        igCompileTraversal_GetVTable,
        &igCompileTraversal_InitFields,
        &FUN_001a33e0, /* extra callback item */
        g_igCompileTraversal_callbackList /* callback list */
    );
}

void igCompileTraversal_GetMetaObjectFunction(void) {
    igCompileTraversal_GetMetaObject();
}

static FieldFactory g_igCompileTraversal_ctorTable[] = {
    (FieldFactory)igObjectRefMetaField_Create,
    (FieldFactory)igObjectRefMetaField_Create,
    (FieldFactory)igObjectRefMetaField_Create,
    (FieldFactory)igBoolMetaField_Create,
    (FieldFactory)igObjectRefMetaField_Create,
    (FieldFactory)igObjectRefMetaField_Create,
    (FieldFactory)igBoolMetaField_Create,
    (FieldFactory)igObjectRefMetaField_Create,
    (FieldFactory)igObjectRefMetaField_Create,
    (FieldFactory)igIntMetaField_Create,
    (FieldFactory)igIntMetaField_Create,
    (FieldFactory)igIntMetaField_Create,
};
static const char *g_igCompileTraversal_fieldTable[] = {
    "_mvmList",
    "_xformInfoList",
    "_moList",
    "_containsShader",
    "_bound",
    "_transformList",
    "_isSkin",
    "_environmentShader2List",
    "_bmpaList",
    "_jointChainCount",
    "_jointBaseMvmIndex",
    "_currentBoneIndex",
};
static igMetaField **g_igCompileTraversal_fieldHandles[] = {
    &g_igCompileTraversal_mvmListMetaField,
    &g_igCompileTraversal_xformInfoListMetaField,
    &g_igCompileTraversal_moListMetaField,
    &g_igCompileTraversal_containsShaderMetaField,
    &g_igCompileTraversal_boundMetaField,
    &g_igCompileTraversal_transformListMetaField,
    &g_igCompileTraversal_isSkinMetaField,
    &g_igCompileTraversal_environmentShader2ListMetaField,
    &g_igCompileTraversal_bmpaListMetaField,
    &g_igCompileTraversal_jointChainCountMetaField,
    &g_igCompileTraversal_jointBaseMvmIndexMetaField,
    &g_igCompileTraversal_currentBoneIndexMetaField,
};
static int g_igCompileTraversal_fieldOffsets[] = {
    472,
    476,
    480,
    484,
    488,
    492,
    496,
    500,
    504,
    508,
    512,
    516,
};

void igCompileTraversal_InitFields(void) {
    int temp_s1;
    void *temp_s2;
    void *temp_s2_2;
    void *temp_s2_3;
    void *temp_s2_4;
    void *temp_s2_5;
    void *temp_s2_6;
    void *temp_s2_7;
    void *temp_s0;

    temp_s0 = (void *)g_igCompileTraversal_metaObject;
    temp_s1 = igMetaObject_GetFieldCount((igMetaObject *)temp_s0);
    igMetaObject_CreateFields((igMetaObject *)temp_s0, g_igCompileTraversal_ctorTable, 0xC);
    temp_s2 = (void *)(((void *)igMetaObject_GetFieldAt((igMetaObject *)temp_s0, temp_s1)));
    ((igObjectRefMetaField *)temp_s2)->_metaObject = (int)Gap::Attrs::igModelViewMatrixAttrList::getClassTypeLazy();
    ((igRefMetaField *)temp_s2)->_construct = 1;
    ((igMetaField *)temp_s2)->_persistent = 0;
    temp_s2_2 = (void *)(((void *)igMetaObject_GetFieldAt((igMetaObject *)temp_s0, temp_s1 + 1)));
    ((igObjectRefMetaField *)temp_s2_2)->_metaObject = (int)igCompiledTransformList_GetOrCreateMetaObject();
    ((igRefMetaField *)temp_s2_2)->_construct = 1;
    ((igMetaField *)temp_s2_2)->_persistent = 0;
    temp_s2_3 = (void *)(((void *)igMetaObject_GetFieldAt((igMetaObject *)temp_s0, temp_s1 + 2)));
    ((igObjectRefMetaField *)temp_s2_3)->_metaObject = (int)igNonRefCountedMatrixObjectList_GetOrCreateMetaObject();
    ((igRefMetaField *)temp_s2_3)->_construct = 1;
    ((igMetaField *)temp_s2_3)->_persistent = 0;
    ((igMetaField *)((void *)igMetaObject_GetFieldAt((igMetaObject *)temp_s0, temp_s1 + 3)))->_persistent = 0;
    temp_s2_4 = (void *)(((void *)igMetaObject_GetFieldAt((igMetaObject *)temp_s0, temp_s1 + 4)));
    ((igObjectRefMetaField *)temp_s2_4)->_metaObject = (int)igAABox_GetOrCreateMetaObject();
    ((igMetaField *)temp_s2_4)->_persistent = 0;
    temp_s2_5 = (void *)(((void *)igMetaObject_GetFieldAt((igMetaObject *)temp_s0, temp_s1 + 5)));
    ((igObjectRefMetaField *)temp_s2_5)->_metaObject = (int)igNonRefCountedTransformList_GetOrCreateMetaObject();
    ((igRefMetaField *)temp_s2_5)->_construct = 1;
    ((igMetaField *)temp_s2_5)->_persistent = 0;
    ((igMetaField *)((void *)igMetaObject_GetFieldAt((igMetaObject *)temp_s0, temp_s1 + 6)))->_persistent = 0;
    temp_s2_6 = (void *)(((void *)igMetaObject_GetFieldAt((igMetaObject *)temp_s0, temp_s1 + 7)));
    ((igObjectRefMetaField *)temp_s2_6)->_metaObject = (int)igEnvironmentMapShader2List_GetOrCreateMetaObject();
    ((igRefMetaField *)temp_s2_6)->_construct = 1;
    ((igMetaField *)temp_s2_6)->_persistent = 0;
    temp_s2_7 = (void *)(((void *)igMetaObject_GetFieldAt((igMetaObject *)temp_s0, temp_s1 + 8)));
    ((igObjectRefMetaField *)temp_s2_7)->_metaObject = (int)Gap::Attrs::igBlendMatrixPaletteAttrList::getClassTypeLazy();
    ((igRefMetaField *)temp_s2_7)->_construct = 1;
    ((igMetaField *)temp_s2_7)->_persistent = 0;
    ((igMetaField *)((void *)igMetaObject_GetFieldAt((igMetaObject *)temp_s0, temp_s1 + 9)))->_persistent = 0;
    ((igMetaField *)((void *)igMetaObject_GetFieldAt((igMetaObject *)temp_s0, temp_s1 + 0xA)))->_persistent = 0;
    ((igMetaField *)((void *)igMetaObject_GetFieldAt((igMetaObject *)temp_s0, temp_s1 + 0xB)))->_persistent = 0;
    igMetaObject_NameFields((igMetaObject *)temp_s0, g_igCompileTraversal_fieldTable, g_igCompileTraversal_fieldHandles, g_igCompileTraversal_fieldOffsets, temp_s1);
    igMetaObject_AddExitCallback((int)&thunk_FUN_001bb230);
}

void FUN_001a33e0(void) {
    FUN_001bb200();
    igMetaObject_AddRegistrationCallback((int)FUN_001bb1f0);
}

void thunk_FUN_001bb230(void) {
    FUN_001bb230();
}

