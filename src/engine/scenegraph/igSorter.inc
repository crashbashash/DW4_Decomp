igMetaObject *g_igSorter_metaObject;
igMetaField *g_igSorter_dlistMetaField;
igMetaField *g_igSorter_modeMetaField;
igMetaField *g_igSorter_renderPackagePoolMetaField;
igMetaField *g_igSorter_tmpAttrsMetaField;
igMetaField *g_igSorter_transpPackagesMetaField;
igMetaField *g_igSorter_opaquePackagesMetaField;
igMetaField *g_igSorter_firstPackagesMetaField;
igMetaField *g_igSorter_lightAttrsMetaField;
igMetaField *g_igSorter_firstAttrsMetaField;
igMetaField *g_igSorter_transpAttrsMetaField;
igMetaField *g_igSorter_opaqueAttrsMetaField;
igMetaField *g_igSorter_firstPackageIndicesMetaField;
igMetaField *g_igSorter_transpPackageIndicesMetaField;
igMetaField *g_igSorter_opaquePackageIndicesMetaField;
igMetaField *g_igSorter_depthWriteDisableMetaField;
igMetaField *g_igSorter_cullFaceFrontMetaField;
igMetaField *g_igSorter_cullFaceBackMetaField;
igMetaField *g_igSorter_transparencyDrawModeMetaField;
igMetaField *g_igSorter_emptyRenderPackageMetaField;
igMetaField *g_igSorter_emptyRenderPackageListMetaField;
igMetaField *g_igSorter_emptyRenderPackageIndicesMetaField;
igMetaField *g_igSorter_lastEmptyRenderPackageAttrsMetaField;
igMetaField *g_igSorter_firstEmptyRenderPackageAttrsMetaField;
igMetaField *g_igSorter_emptyGeometryMetaField;
igMetaField *g_igSorter_curListMetaField;
igMetaField *g_igSorter_prevListMetaField;
igMetaField *g_igSorter_isCompoundPackageOpenMetaField;
igMetaField *g_igSorter_isCompoundPackageTransparentMetaField;
igMetaField *g_igSorter_isCompoundPackageFirstMetaField;
igMetaField *g_igSorter_compoundPackageMetaField;
igMetaField *g_igSorter_compoundPackageNestCountMetaField;
igMetaField *g_igSorter_cachedPackageMetaField;
igMetaField *g_igSorter_outputCreatedMetaField;
igMetaField *g_igSorter_useZSortMetaField;
igMetaField *g_igSorter_forceNoSeparateMetaField;
igMetaField *g_igSorter_printOutputStateMetaField;

igMetaObject *FUN_00196c10(void) {
    if (g_igSorter_metaObject == 0) {
        g_igSorter_metaObject = ((igMetaObject *)igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData)));
    }
    return g_igSorter_metaObject;
}

igMetaObject *igSorter_GetMetaObject(void)
{
    igMetaObject *g = g_igSorter_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false)
        igSorter_EnsureRegistered();
    return g_igSorter_metaObject;
}

int igSorter_GetVTable(void) {
    union U_196c10 u;
    int temp_s5;
    char *p276, *p268, *p264, *p260, *p256, *p252, *p248, *p244, *p240;
    igObject_InitHeader((igObject *)u.b);
    u.vt = (int)&g_igSorter_vtable[0];
    igSmartPointer_igDisplayListAttr_Construct((int *)&u.b[8]);
    igSmartPointer_igRenderPackagePool_Construct((int *)&u.b[16]);
    igSmartPointer_igNonRefCountedAttrList_Construct((int *)&u.b[20]);
    igSmartPointer_igRenderPackageList_Construct((int *)&u.b[24]);
    igSmartPointer_igRenderPackageList_Construct((int *)&u.b[28]);
    igSmartPointer_igRenderPackageList_Construct((int *)&u.b[32]);
    igSmartPointer_igDisplayListAttr_Construct((int *)&u.b[36]);
    igSmartPointer_igDisplayListAttr_Construct((int *)&u.b[40]);
    igSmartPointer_igDisplayListAttr_Construct((int *)&u.b[44]);
    igSmartPointer_igDisplayListAttr_Construct((int *)&u.b[48]);
    igSmartPointer_igIntList_Construct((int *)&u.b[52]);
    igSmartPointer_igIntList_Construct((int *)&u.b[56]);
    igSmartPointer_igIntList_Construct((int *)&u.b[60]);
    igSmartPointer_igDepthWriteStateAttr_Construct((int *)&u.b[64]);
    igSmartPointer_igCullFaceAttr_Construct((int *)&u.b[68]);
    igSmartPointer_igCullFaceAttr_Construct((int *)&u.b[72]);
    p240 = &u.b[80];
    igSmartPointer_igRenderPackage_Construct((int *)p240);
    p244 = &u.b[84];
    igSmartPointer_igRenderPackageList_Construct((int *)p244);
    p248 = &u.b[88];
    igSmartPointer_igIntList_Construct((int *)p248);
    p252 = &u.b[92];
    igSmartPointer_igDisplayListAttr_Construct((int *)p252);
    p256 = &u.b[96];
    igSmartPointer_igDisplayListAttr_Construct((int *)p256);
    p260 = &u.b[100];
    igSmartPointer_igGeometry_Construct((int *)p260);
    p264 = &u.b[104];
    igSmartPointer_igIntList_Construct((int *)p264);
    p268 = &u.b[108];
    igSmartPointer_igIntList_Construct((int *)p268);
    p276 = &u.b[116];
    igSmartPointer_igRenderPackage_Construct((int *)p276);
    temp_s5 = *(int *)&u.b[g_objectSystem->vtableProbeOffset];
    u.vt = (int)&DAT_00528620[4];
    igSmartPointer_igRenderPackage_Destruct((igSmartPointer<igObject> *)p276, -1);
    igSmartPointer_igIntList_Destruct((igSmartPointer<igObject> *)p268, -1);
    igSmartPointer_igIntList_Destruct((igSmartPointer<igObject> *)p264, -1);
    igSmartPointer_igGeometry_Destruct((igSmartPointer<igObject> *)p260, -1);
    igSmartPointer_igDisplayListAttr_Destruct((igSmartPointer<igObject> *)p256, -1);
    igSmartPointer_igDisplayListAttr_Destruct((igSmartPointer<igObject> *)p252, -1);
    igSmartPointer_igIntList_Destruct((igSmartPointer<igObject> *)p248, -1);
    igSmartPointer_igRenderPackageList_Destruct((igSmartPointer<igObject> *)p244, -1);
    igSmartPointer_igRenderPackage_Destruct((igSmartPointer<igObject> *)p240, -1);
    igSmartPointer_igCullFaceAttr_Destruct((igSmartPointer<igObject> *)&u.b[72], -1);
    igSmartPointer_igCullFaceAttr_Destruct((igSmartPointer<igObject> *)&u.b[68], -1);
    igSmartPointer_igDepthWriteStateAttr_Destruct((igSmartPointer<igObject> *)&u.b[64], -1);
    igSmartPointer_igIntList_Destruct((igSmartPointer<igObject> *)&u.b[60], -1);
    igSmartPointer_igIntList_Destruct((igSmartPointer<igObject> *)&u.b[56], -1);
    igSmartPointer_igIntList_Destruct((igSmartPointer<igObject> *)&u.b[52], -1);
    igSmartPointer_igDisplayListAttr_Destruct((igSmartPointer<igObject> *)&u.b[48], -1);
    igSmartPointer_igDisplayListAttr_Destruct((igSmartPointer<igObject> *)&u.b[44], -1);
    igSmartPointer_igDisplayListAttr_Destruct((igSmartPointer<igObject> *)&u.b[40], -1);
    igSmartPointer_igDisplayListAttr_Destruct((igSmartPointer<igObject> *)&u.b[36], -1);
    igSmartPointer_igRenderPackageList_Destruct((igSmartPointer<igObject> *)&u.b[32], -1);
    igSmartPointer_igRenderPackageList_Destruct((igSmartPointer<igObject> *)&u.b[28], -1);
    igSmartPointer_igRenderPackageList_Destruct((igSmartPointer<igObject> *)&u.b[24], -1);
    FUN_001380e0((void **)&u.b[20], (short)-1);
    igSmartPointer_igRenderPackagePool_Destruct((igSmartPointer<igObject> *)&u.b[16], -1);
    igSmartPointer_igDisplayListAttr_Destruct((igSmartPointer<igObject> *)&u.b[8], -1);
    return temp_s5;
}

igSmartPointer<igObject> *igSmartPointer_igRenderPackagePool_Destruct(igSmartPointer<igObject> *self, short deleteFlag) {
    if (self) {
        igObject *object = self->p;
        igObject::release(object);
        if (deleteFlag > 0) operator delete(self);
    }
    return self;
}

igSmartPointer<igObject> *igSmartPointer_igDepthWriteStateAttr_Destruct(igSmartPointer<igObject> *self, short deleteFlag) {
    if (self) {
        igObject *object = self->p;
        igObject::release(object);
        if (deleteFlag > 0) operator delete(self);
    }
    return self;
}

igSmartPointer<igObject> *igSmartPointer_igCullFaceAttr_Destruct(igSmartPointer<igObject> *self, short deleteFlag) {
    if (self) {
        igObject *object = self->p;
        igObject::release(object);
        if (deleteFlag > 0) operator delete(self);
    }
    return self;
}

igSmartPointer<igObject> *igSmartPointer_igRenderPackageList_Destruct(igSmartPointer<igObject> *self, short deleteFlag) {
    if (self) {
        igObject *object = self->p;
        igObject::release(object);
        if (deleteFlag > 0) operator delete(self);
    }
    return self;
}

igSmartPointer<igObject> *igSmartPointer_igDisplayListAttr_Destruct(igSmartPointer<igObject> *self, short deleteFlag) {
    if (self) {
        igObject *object = self->p;
        igObject::release(object);
        if (deleteFlag > 0) operator delete(self);
    }
    return self;
}

igSmartPointer<igObject> *igSmartPointer_igGeometry_Destruct(igSmartPointer<igObject> *self, short deleteFlag) {
    if (self) {
        igObject *object = self->p;
        igObject::release(object);
        if (deleteFlag > 0) operator delete(self);
    }
    return self;
}

igSmartPointer<igObject> *igSmartPointer_igRenderPackage_Destruct(igSmartPointer<igObject> *self, short deleteFlag) {
    if (self) {
        igObject *object = self->p;
        igObject::release(object);
        if (deleteFlag > 0) operator delete(self);
    }
    return self;
}

int *igSmartPointer_igGeometry_Construct(int *p)
{
    *(int *)((char *)p + 0) = 0;
    return p;
}

int *igSmartPointer_igRenderPackage_Construct(int *p)
{
    *(int *)((char *)p + 0) = 0;
    return p;
}

int *igSmartPointer_igCullFaceAttr_Construct(int *p)
{
    *(int *)((char *)p + 0) = 0;
    return p;
}

int *igSmartPointer_igDepthWriteStateAttr_Construct(int *p)
{
    *(int *)((char *)p + 0) = 0;
    return p;
}

int *igSmartPointer_igRenderPackageList_Construct(int *p)
{
    *(int *)((char *)p + 0) = 0;
    return p;
}

int *igSmartPointer_igNonRefCountedAttrList_Construct(int *p)
{
    *(int *)((char *)p + 0) = 0;
    return p;
}

int *igSmartPointer_igRenderPackagePool_Construct(int *p)
{
    *(int *)((char *)p + 0) = 0;
    return p;
}

int *igSmartPointer_igDisplayListAttr_Construct(int *p)
{
    *(int *)((char *)p + 0) = 0;
    return p;
}

void igSorter_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(igSorter_Register);
}

static igMetaObjectCallback g_igSorter_callbackList[] = { Gap::Attrs::igDisplayListAttr::arkRegister, igRenderPackagePool_EnsureRegistered, igNonRefCountedAttrList_EnsureRegistered, igRenderPackageList_EnsureRegistered, Gap::Core::igIntList::arkRegister, Gap::Attrs::igDepthWriteStateAttr::arkRegister, Gap::Attrs::igCullFaceAttr::arkRegister, igRenderPackage_EnsureRegistered, igGeometry_EnsureRegistered, 0 };

CallbackArray *igSorter_Register(void) {
    SceneGraphLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_igSorter_metaObject,
        Gap::Core::igObject::arkRegisterInternal,
        igObject_GetMetaObject_ParentAccessor,
        igSorter_GetMetaObjectFunction,
        "igSorter",
        0x84, /* instance size */
        igSorter_GetVTable,
        &igSorter_InitFields,
        0, /* extra callback item */
        g_igSorter_callbackList /* callback list */
    );
}

void igSorter_GetMetaObjectFunction(void) {
    igSorter_GetMetaObject();
}

static FieldFactory g_igSorter_ctorTable[] = {
    (FieldFactory)igObjectRefMetaField_Create,
    (FieldFactory)igIntMetaField_Create,
    (FieldFactory)igObjectRefMetaField_Create,
    (FieldFactory)igObjectRefMetaField_Create,
    (FieldFactory)igObjectRefMetaField_Create,
    (FieldFactory)igObjectRefMetaField_Create,
    (FieldFactory)igObjectRefMetaField_Create,
    (FieldFactory)igObjectRefMetaField_Create,
    (FieldFactory)igObjectRefMetaField_Create,
    (FieldFactory)igObjectRefMetaField_Create,
    (FieldFactory)igObjectRefMetaField_Create,
    (FieldFactory)igObjectRefMetaField_Create,
    (FieldFactory)igObjectRefMetaField_Create,
    (FieldFactory)igObjectRefMetaField_Create,
    (FieldFactory)igObjectRefMetaField_Create,
    (FieldFactory)igObjectRefMetaField_Create,
    (FieldFactory)igObjectRefMetaField_Create,
    (FieldFactory)igIntMetaField_Create,
    (FieldFactory)igObjectRefMetaField_Create,
    (FieldFactory)igObjectRefMetaField_Create,
    (FieldFactory)igObjectRefMetaField_Create,
    (FieldFactory)igObjectRefMetaField_Create,
    (FieldFactory)igObjectRefMetaField_Create,
    (FieldFactory)igObjectRefMetaField_Create,
    (FieldFactory)igObjectRefMetaField_Create,
    (FieldFactory)igObjectRefMetaField_Create,
    (FieldFactory)igBoolMetaField_Create,
    (FieldFactory)igBoolMetaField_Create,
    (FieldFactory)igBoolMetaField_Create,
    (FieldFactory)igObjectRefMetaField_Create,
    (FieldFactory)igIntMetaField_Create,
    (FieldFactory)igObjectRefMetaField_Create,
    (FieldFactory)igBoolMetaField_Create,
    (FieldFactory)igBoolMetaField_Create,
    (FieldFactory)igBoolMetaField_Create,
    (FieldFactory)igBoolMetaField_Create,
};
static const char *g_igSorter_fieldTable[] = {
    "_dlist",
    "_mode",
    "_renderPackagePool",
    "_tmpAttrs",
    "_transpPackages",
    "_opaquePackages",
    "_firstPackages",
    "_lightAttrs",
    "_firstAttrs",
    "_transpAttrs",
    "_opaqueAttrs",
    "_firstPackageIndices",
    "_transpPackageIndices",
    "_opaquePackageIndices",
    "_depthWriteDisable",
    "_cullFaceFront",
    "_cullFaceBack",
    "_transparencyDrawMode",
    "_emptyRenderPackage",
    "_emptyRenderPackageList",
    "_emptyRenderPackageIndices",
    "_lastEmptyRenderPackageAttrs",
    "_firstEmptyRenderPackageAttrs",
    "_emptyGeometry",
    "_curList",
    "_prevList",
    "_isCompoundPackageOpen",
    "_isCompoundPackageTransparent",
    "_isCompoundPackageFirst",
    "_compoundPackage",
    "_compoundPackageNestCount",
    "_cachedPackage",
    "_outputCreated",
    "_useZSort",
    "_forceNoSeparate",
    "_printOutputState",
};
static igMetaField **g_igSorter_fieldHandles[] = {
    &g_igSorter_dlistMetaField,
    &g_igSorter_modeMetaField,
    &g_igSorter_renderPackagePoolMetaField,
    &g_igSorter_tmpAttrsMetaField,
    &g_igSorter_transpPackagesMetaField,
    &g_igSorter_opaquePackagesMetaField,
    &g_igSorter_firstPackagesMetaField,
    &g_igSorter_lightAttrsMetaField,
    &g_igSorter_firstAttrsMetaField,
    &g_igSorter_transpAttrsMetaField,
    &g_igSorter_opaqueAttrsMetaField,
    &g_igSorter_firstPackageIndicesMetaField,
    &g_igSorter_transpPackageIndicesMetaField,
    &g_igSorter_opaquePackageIndicesMetaField,
    &g_igSorter_depthWriteDisableMetaField,
    &g_igSorter_cullFaceFrontMetaField,
    &g_igSorter_cullFaceBackMetaField,
    &g_igSorter_transparencyDrawModeMetaField,
    &g_igSorter_emptyRenderPackageMetaField,
    &g_igSorter_emptyRenderPackageListMetaField,
    &g_igSorter_emptyRenderPackageIndicesMetaField,
    &g_igSorter_lastEmptyRenderPackageAttrsMetaField,
    &g_igSorter_firstEmptyRenderPackageAttrsMetaField,
    &g_igSorter_emptyGeometryMetaField,
    &g_igSorter_curListMetaField,
    &g_igSorter_prevListMetaField,
    &g_igSorter_isCompoundPackageOpenMetaField,
    &g_igSorter_isCompoundPackageTransparentMetaField,
    &g_igSorter_isCompoundPackageFirstMetaField,
    &g_igSorter_compoundPackageMetaField,
    &g_igSorter_compoundPackageNestCountMetaField,
    &g_igSorter_cachedPackageMetaField,
    &g_igSorter_outputCreatedMetaField,
    &g_igSorter_useZSortMetaField,
    &g_igSorter_forceNoSeparateMetaField,
    &g_igSorter_printOutputStateMetaField,
};
static int g_igSorter_fieldOffsets[] = {
    8,
    12,
    16,
    20,
    24,
    28,
    32,
    36,
    40,
    44,
    48,
    52,
    56,
    60,
    64,
    68,
    72,
    76,
    80,
    84,
    88,
    92,
    96,
    100,
    104,
    108,
    112,
    113,
    114,
    116,
    120,
    124,
    128,
    129,
    130,
    131,
};

void igSorter_InitFields(void) {
    int temp_s1;
    void *temp_s2;
    void *temp_s2_10;
    void *temp_s2_11;
    void *temp_s2_12;
    void *temp_s2_13;
    void *temp_s2_14;
    void *temp_s2_15;
    void *temp_s2_16;
    void *temp_s2_17;
    void *temp_s2_18;
    void *temp_s2_19;
    void *temp_s2_20;
    void *temp_s2_21;
    void *temp_s2_22;
    void *temp_s2_23;
    void *temp_s2_24;
    void *temp_s2_25;
    void *temp_s2_26;
    void *temp_s2_2;
    void *temp_s2_3;
    void *temp_s2_4;
    void *temp_s2_5;
    void *temp_s2_6;
    void *temp_s2_7;
    void *temp_s2_8;
    void *temp_s2_9;
    void *temp_s0;

    temp_s0 = (void *)g_igSorter_metaObject;
    temp_s1 = igMetaObject_GetFieldCount((igMetaObject *)temp_s0);
    igMetaObject_CreateFields((igMetaObject *)temp_s0, g_igSorter_ctorTable, 0x24);
    temp_s2 = (void *)(((void *)igMetaObject_GetFieldAt((igMetaObject *)temp_s0, temp_s1)));
    ((igObjectRefMetaField *)temp_s2)->_metaObject = (int)Gap::Attrs::igDisplayListAttr::getClassTypeLazy();
    ((igObjectRefMetaField *)temp_s2)->_construct = 1;
    temp_s2_2 = (void *)(((void *)igMetaObject_GetFieldAt((igMetaObject *)temp_s0, temp_s1 + 2)));
    ((igObjectRefMetaField *)temp_s2_2)->_metaObject = (int)igRenderPackagePool_GetOrCreateMetaObject();
    ((igObjectRefMetaField *)temp_s2_2)->_construct = 1;
    temp_s2_3 = (void *)(((void *)igMetaObject_GetFieldAt((igMetaObject *)temp_s0, temp_s1 + 3)));
    ((igObjectRefMetaField *)temp_s2_3)->_metaObject = (int)igNonRefCountedAttrList_GetOrCreateMetaObject();
    ((igObjectRefMetaField *)temp_s2_3)->_construct = 1;
    temp_s2_4 = (void *)(((void *)igMetaObject_GetFieldAt((igMetaObject *)temp_s0, temp_s1 + 4)));
    ((igObjectRefMetaField *)temp_s2_4)->_metaObject = (int)igRenderPackageList_GetOrCreateMetaObject();
    ((igObjectRefMetaField *)temp_s2_4)->_construct = 1;
    temp_s2_5 = (void *)(((void *)igMetaObject_GetFieldAt((igMetaObject *)temp_s0, temp_s1 + 5)));
    ((igObjectRefMetaField *)temp_s2_5)->_metaObject = (int)igRenderPackageList_GetOrCreateMetaObject();
    ((igObjectRefMetaField *)temp_s2_5)->_construct = 1;
    temp_s2_6 = (void *)(((void *)igMetaObject_GetFieldAt((igMetaObject *)temp_s0, temp_s1 + 6)));
    ((igObjectRefMetaField *)temp_s2_6)->_metaObject = (int)igRenderPackageList_GetOrCreateMetaObject();
    ((igObjectRefMetaField *)temp_s2_6)->_construct = 1;
    temp_s2_7 = (void *)(((void *)igMetaObject_GetFieldAt((igMetaObject *)temp_s0, temp_s1 + 7)));
    ((igObjectRefMetaField *)temp_s2_7)->_metaObject = (int)Gap::Attrs::igDisplayListAttr::getClassTypeLazy();
    ((igObjectRefMetaField *)temp_s2_7)->_construct = 1;
    temp_s2_8 = (void *)(((void *)igMetaObject_GetFieldAt((igMetaObject *)temp_s0, temp_s1 + 8)));
    ((igObjectRefMetaField *)temp_s2_8)->_metaObject = (int)Gap::Attrs::igDisplayListAttr::getClassTypeLazy();
    ((igObjectRefMetaField *)temp_s2_8)->_construct = 1;
    temp_s2_9 = (void *)(((void *)igMetaObject_GetFieldAt((igMetaObject *)temp_s0, temp_s1 + 9)));
    ((igObjectRefMetaField *)temp_s2_9)->_metaObject = (int)Gap::Attrs::igDisplayListAttr::getClassTypeLazy();
    ((igObjectRefMetaField *)temp_s2_9)->_construct = 1;
    temp_s2_10 = (void *)(((void *)igMetaObject_GetFieldAt((igMetaObject *)temp_s0, temp_s1 + 0xA)));
    ((igObjectRefMetaField *)temp_s2_10)->_metaObject = (int)Gap::Attrs::igDisplayListAttr::getClassTypeLazy();
    ((igObjectRefMetaField *)temp_s2_10)->_construct = 1;
    temp_s2_11 = (void *)(((void *)igMetaObject_GetFieldAt((igMetaObject *)temp_s0, temp_s1 + 0xB)));
    ((igObjectRefMetaField *)temp_s2_11)->_metaObject = (int)Gap::Core::igIntList::getClassTypeLazy();
    ((igObjectRefMetaField *)temp_s2_11)->_construct = 1;
    temp_s2_12 = (void *)(((void *)igMetaObject_GetFieldAt((igMetaObject *)temp_s0, temp_s1 + 0xC)));
    ((igObjectRefMetaField *)temp_s2_12)->_metaObject = (int)Gap::Core::igIntList::getClassTypeLazy();
    ((igObjectRefMetaField *)temp_s2_12)->_construct = 1;
    temp_s2_13 = (void *)(((void *)igMetaObject_GetFieldAt((igMetaObject *)temp_s0, temp_s1 + 0xD)));
    ((igObjectRefMetaField *)temp_s2_13)->_metaObject = (int)Gap::Core::igIntList::getClassTypeLazy();
    ((igObjectRefMetaField *)temp_s2_13)->_construct = 1;
    temp_s2_14 = (void *)(((void *)igMetaObject_GetFieldAt((igMetaObject *)temp_s0, temp_s1 + 0xE)));
    ((igObjectRefMetaField *)temp_s2_14)->_metaObject = (int)Gap::Attrs::igDepthWriteStateAttr::getClassTypeLazy();
    ((igObjectRefMetaField *)temp_s2_14)->_construct = 1;
    temp_s2_15 = (void *)(((void *)igMetaObject_GetFieldAt((igMetaObject *)temp_s0, temp_s1 + 0xF)));
    ((igObjectRefMetaField *)temp_s2_15)->_metaObject = (int)Gap::Attrs::igCullFaceAttr::getClassTypeLazy();
    ((igObjectRefMetaField *)temp_s2_15)->_construct = 1;
    temp_s2_16 = (void *)(((void *)igMetaObject_GetFieldAt((igMetaObject *)temp_s0, temp_s1 + 0x10)));
    ((igObjectRefMetaField *)temp_s2_16)->_metaObject = (int)Gap::Attrs::igCullFaceAttr::getClassTypeLazy();
    ((igObjectRefMetaField *)temp_s2_16)->_construct = 1;
    temp_s2_17 = (void *)(((void *)igMetaObject_GetFieldAt((igMetaObject *)temp_s0, temp_s1 + 0x12)));
    ((igObjectRefMetaField *)temp_s2_17)->_metaObject = (int)igRenderPackage_GetOrCreateMetaObject();
    ((igObjectRefMetaField *)temp_s2_17)->_construct = 1;
    temp_s2_18 = (void *)(((void *)igMetaObject_GetFieldAt((igMetaObject *)temp_s0, temp_s1 + 0x13)));
    ((igObjectRefMetaField *)temp_s2_18)->_metaObject = (int)igRenderPackageList_GetOrCreateMetaObject();
    ((igObjectRefMetaField *)temp_s2_18)->_construct = 1;
    temp_s2_19 = (void *)(((void *)igMetaObject_GetFieldAt((igMetaObject *)temp_s0, temp_s1 + 0x14)));
    ((igObjectRefMetaField *)temp_s2_19)->_metaObject = (int)Gap::Core::igIntList::getClassTypeLazy();
    ((igObjectRefMetaField *)temp_s2_19)->_construct = 1;
    temp_s2_20 = (void *)(((void *)igMetaObject_GetFieldAt((igMetaObject *)temp_s0, temp_s1 + 0x15)));
    ((igObjectRefMetaField *)temp_s2_20)->_metaObject = (int)Gap::Attrs::igDisplayListAttr::getClassTypeLazy();
    ((igObjectRefMetaField *)temp_s2_20)->_construct = 1;
    temp_s2_21 = (void *)(((void *)igMetaObject_GetFieldAt((igMetaObject *)temp_s0, temp_s1 + 0x16)));
    ((igObjectRefMetaField *)temp_s2_21)->_metaObject = (int)Gap::Attrs::igDisplayListAttr::getClassTypeLazy();
    ((igObjectRefMetaField *)temp_s2_21)->_construct = 1;
    temp_s2_22 = (void *)(((void *)igMetaObject_GetFieldAt((igMetaObject *)temp_s0, temp_s1 + 0x17)));
    ((igObjectRefMetaField *)temp_s2_22)->_metaObject = (int)igGeometry_GetOrCreateMetaObject();
    ((igObjectRefMetaField *)temp_s2_22)->_construct = 1;
    temp_s2_23 = (void *)(((void *)igMetaObject_GetFieldAt((igMetaObject *)temp_s0, temp_s1 + 0x18)));
    ((igObjectRefMetaField *)temp_s2_23)->_metaObject = (int)Gap::Core::igIntList::getClassTypeLazy();
    ((igObjectRefMetaField *)temp_s2_23)->_construct = 1;
    temp_s2_24 = (void *)(((void *)igMetaObject_GetFieldAt((igMetaObject *)temp_s0, temp_s1 + 0x19)));
    ((igObjectRefMetaField *)temp_s2_24)->_metaObject = (int)Gap::Core::igIntList::getClassTypeLazy();
    ((igObjectRefMetaField *)temp_s2_24)->_construct = 1;
    temp_s2_25 = (void *)(((void *)igMetaObject_GetFieldAt((igMetaObject *)temp_s0, temp_s1 + 0x1D)));
    ((igObjectRefMetaField *)temp_s2_25)->_metaObject = (int)igRenderPackage_GetOrCreateMetaObject();
    temp_s2_26 = (void *)(((void *)igMetaObject_GetFieldAt((igMetaObject *)temp_s0, temp_s1 + 0x1F)));
    ((igObjectRefMetaField *)temp_s2_26)->_metaObject = (int)igRenderPackage_GetOrCreateMetaObject();
    ((igObjectRefMetaField *)temp_s2_26)->_refCounted = 0;
    *(char *)((char *)(((void *)igMetaObject_GetFieldAt((igMetaObject *)temp_s0, temp_s1 + 0x23))) + 38) = 0;
    igMetaObject_NameFields((igMetaObject *)temp_s0, g_igSorter_fieldTable, g_igSorter_fieldHandles, g_igSorter_fieldOffsets, temp_s1);
}

