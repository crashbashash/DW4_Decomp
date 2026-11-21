igMetaObject *g_igPlanarShadowShader_metaObject;
igMetaField *g_igPlanarShadowShader_lightsMetaField;
igMetaField *g_igPlanarShadowShader_mvmListMetaField;
igMetaField *g_igPlanarShadowShader_shadowPlaneMetaField;
igMetaField *g_igPlanarShadowShader_shadowColorMetaField;
igMetaField *g_igPlanarShadowShader_shadowUseBlendMetaField;
igMetaField *g_igPlanarShadowShader_shadowUseStencilMetaField;
igMetaField *g_igPlanarShadowShader_matsMetaField;
igMetaField *g_igPlanarShadowShader_geomsMetaField;
igMetaField *g_igPlanarShadowShader_blendmatsMetaField;
igMetaField *g_igPlanarShadowShader_savedBoundsMetaField;
igMetaField *g_igPlanarShadowShader_unusedMetaField;
igMetaField *g_igPlanarShadowShader_shadowColorAttrMetaField;
igMetaField *g_igPlanarShadowShader_stencilStateMetaField;

igMetaObject *igPlanarShadowShader_GetMetaObject(void)
{
    igMetaObject *g = g_igPlanarShadowShader_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false)
        igPlanarShadowShader_EnsureRegistered();
    return g_igPlanarShadowShader_metaObject;
}

int igPlanarShadowShader_GetVTable(void) {
    union U_19bf50 u;


    int temp_s5;

    FUN_0019c380((void *)u.b);
    u.vt = (int)&g_igPlanarShadowShader_vtable[0];
    igSmartPointer_igLightList_Construct((int *)&u.b[40]);
    igSmartPointer_igModelViewMatrixAttrList_Construct((int *)&u.b[44]);
    FUN_00151090((int)&u.b[48]);
    FUN_00151090((int)&u.b[64]);
    igSmartPointer_igModelViewMatrixAttrList_Construct((int *)&u.b[80]);
    igSmartPointer_igGeometryList_Construct((int *)&u.b[84]);
    igSmartPointer_igAttrList_Construct((int *)&u.b[88]);
    igSmartPointer_igVolume_Construct((int *)&u.b[92]);
    igSmartPointer_igVolume_Construct((int *)&u.b[96]);
    igSmartPointer_igColorAttr_Construct((int *)&u.b[100]);
    igSmartPointer_igStencilStateAttr_Construct((int *)&u.b[104]);
    temp_s5 = *(int *)&u.b[g_objectSystem->vtableProbeOffset];
    u.vt = (int)&D_005289f0[0];
    igSmartPointer_igStencilStateAttr_Destruct((ObjectRefWord *)&u.b[104], -1);
    igSmartPointer_igColorAttr_Destruct((igSmartPointer<igObject> *)&u.b[100], -1);
    FUN_0018f980((igSmartPointer<igObject> *)&u.b[96], -1);
    FUN_0018f980((igSmartPointer<igObject> *)&u.b[92], -1);
    igSmartPointer_igAttrList_Destruct((igSmartPointer<igObject> *)&u.b[88], -1);
    igSmartPointer_igGeometryList_Destruct((igSmartPointer<igObject> *)&u.b[84], -1);
    igSmartPointer_igModelViewMatrixAttrList_Destruct((struct R * *)&u.b[80], -1);
    igSmartPointer_igModelViewMatrixAttrList_Destruct((struct R * *)&u.b[44], -1);
    igSmartPointer_igLightList_Destruct((igSmartPointer<igObject> *)&u.b[40], -1);
    FUN_0019c0e0((struct S_19c0e0 *)u.b, 0);
    return temp_s5;
}

void *FUN_0019c0e0(struct S_19c0e0 *arg0, short arg1) {
    void *p;
    int rc;

    if (arg0 != 0) {
        arg0->f0 = &g_igAttrSet_vtable[0];
        if (&arg0->f20) {
            p = arg0->f20;
            if (p != 0) {
                rc = *(int *)((char *)(p) + 4) - 1;
                *(int *)((char *)(p) + 4) = rc;
                if (((unsigned long long) ((long long) *(int *)((char *)(p) + 4) << 0x29) >> 0x29) == 0) {
                    igObject_Destroy((igObject *)p);
                }
            }
        }
        if (arg0 != 0) {
            arg0->f0 = &g_igGroup_vtable[0];
            igSmartPointer_igNodeList_Destruct((igSmartPointer<igObject> *)((char *)arg0 + 0x1C), -1);
            igNode_Destroy((igNode *)arg0, 0);
        }
        if (arg1 > 0) {
            Memory_FreeBufferAliasC(arg0);
        }
    }
    return arg0;
}

igSmartPointer<igObject> *igSmartPointer_igLightList_Destruct(igSmartPointer<igObject> *self, short deleteFlag) {
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

igSmartPointer<igObject> *igSmartPointer_igGeometryList_Destruct(igSmartPointer<igObject> *self, short deleteFlag) {
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

ObjectRefWord *igSmartPointer_igStencilStateAttr_Destruct(ObjectRefWord *self,int delete_storage) {
    if(self) {
        ObjectRefTarget *object=self->value;
        if(object) {
            --object->references;
            if(((unsigned long long)(long long)object->references & 0x7fffffULL)==0)
                igObject_Destroy((igObject *)object);
        }
        if((short)delete_storage>0) operator delete(self);
    }
    return self;
}

int *igSmartPointer_igStencilStateAttr_Construct(int *p)
{
    *p = 0;
    return p;
}

int *igSmartPointer_igVolume_Construct(int *p)
{
    *p = 0;
    return p;
}

int *igSmartPointer_igAttrList_Construct(int *p)
{
    *p = 0;
    return p;
}

int *igSmartPointer_igGeometryList_Construct(int *p)
{
    *p = 0;
    return p;
}

int *igSmartPointer_igModelViewMatrixAttrList_Construct(int *p)
{
    *p = 0;
    return p;
}

int *igSmartPointer_igLightList_Construct(int *p)
{
    *p = 0;
    return p;
}

void *FUN_0019c380(void *arg0) {
    igAttrSet *self = (igAttrSet *)arg0;
    igObject_InitHeader((igObject *)arg0);
    self->_vtable = (int)(&g_igNamedObject_vtable[0]);
    self->_name = 0;
    self->_vtable = (int)(&g_igNode_vtable[0]);
    self->_bound = 0;
    self->_parentList = 0;
    self->_vtable = (int)(&g_igGroup_vtable[0]);
    self->_childList = 0;
    self->_vtable = (int)(&g_igAttrSet_vtable[0]);
    self->_attributes = 0;
    return arg0;
}

void igPlanarShadowShader_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(igPlanarShadowShader_Register);
}

static igMetaObjectCallback g_igPlanarShadowShader_callbackList[] = { igLightList_EnsureRegistered, igModelViewMatrixAttrList_EnsureRegistered, igGeometryList_EnsureRegistered, igAttrList_EnsureRegistered, igVolume_EnsureRegistered, igColorAttr_EnsureRegistered, Gap::Attrs::igStencilStateAttr::arkRegister, 0 };

CallbackArray *igPlanarShadowShader_Register(void) {
    SceneGraphLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_igPlanarShadowShader_metaObject,
        igAttrSet_Register,
        igAttrSet_GetPublishedMetaObject,
        igPlanarShadowShader_GetMetaObjectFunction,
        "igPlanarShadowShader",
        0x70, /* instance size */
        igPlanarShadowShader_GetVTable,
        &igPlanarShadowShader_InitFields,
        0, /* extra callback item */
        g_igPlanarShadowShader_callbackList /* callback list */
    );
}

void igPlanarShadowShader_GetMetaObjectFunction(void) {
    igPlanarShadowShader_GetMetaObject();
}

igMetaObject *g_igAttrSet_metaObject;
igMetaField *g_igAttrSet_attributesMetaField;
igMetaField *g_igAttrSet_triggerMetaField;

igMetaObject *igAttrSet_GetPublishedMetaObject(void) {
    return g_igAttrSet_metaObject;
}

static FieldFactory g_igPlanarShadowShader_ctorTable[] = {
    (FieldFactory)igObjectRefMetaField_Create,
    (FieldFactory)igObjectRefMetaField_Create,
    (FieldFactory)Gap::Math::igVec4fMetaField::_instantiateFromPool,
    (FieldFactory)Gap::Math::igVec4fMetaField::_instantiateFromPool,
    (FieldFactory)igBoolMetaField_Create,
    (FieldFactory)igBoolMetaField_Create,
    (FieldFactory)igObjectRefMetaField_Create,
    (FieldFactory)igObjectRefMetaField_Create,
    (FieldFactory)igObjectRefMetaField_Create,
    (FieldFactory)igObjectRefMetaField_Create,
    (FieldFactory)igObjectRefMetaField_Create,
    (FieldFactory)igObjectRefMetaField_Create,
    (FieldFactory)igObjectRefMetaField_Create,
};
static const char *g_igPlanarShadowShader_fieldTable[] = {
    "_lights",
    "_mvmList",
    "_shadowPlane",
    "_shadowColor",
    "_shadowUseBlend",
    "_shadowUseStencil",
    "_mats",
    "_geoms",
    "_blendmats",
    "_savedBounds",
    "_unused",
    "_shadowColorAttr",
    "_stencilState",
};
static igMetaField **g_igPlanarShadowShader_fieldHandles[] = {
    &g_igPlanarShadowShader_lightsMetaField,
    &g_igPlanarShadowShader_mvmListMetaField,
    &g_igPlanarShadowShader_shadowPlaneMetaField,
    &g_igPlanarShadowShader_shadowColorMetaField,
    &g_igPlanarShadowShader_shadowUseBlendMetaField,
    &g_igPlanarShadowShader_shadowUseStencilMetaField,
    &g_igPlanarShadowShader_matsMetaField,
    &g_igPlanarShadowShader_geomsMetaField,
    &g_igPlanarShadowShader_blendmatsMetaField,
    &g_igPlanarShadowShader_savedBoundsMetaField,
    &g_igPlanarShadowShader_unusedMetaField,
    &g_igPlanarShadowShader_shadowColorAttrMetaField,
    &g_igPlanarShadowShader_stencilStateMetaField,
};
static int g_igPlanarShadowShader_fieldOffsets[] = {
    40,
    44,
    48,
    64,
    108,
    109,
    80,
    84,
    88,
    92,
    96,
    100,
    104,
};

void igPlanarShadowShader_InitFields(void) {
    void *temp_s2_9;
    void *temp_s2_8;
    void *temp_s2_7;
    void *temp_s2_6;
    void *temp_s2_5;
    void *temp_s2_4;
    void *temp_s2_3;
    void *temp_s2_2;
    void *temp_s2;
    void *temp_a0_2;
    void *temp_a0;
    int temp_s1;
    void *temp_s0;
    V4 spA;
    V4 spB;

    temp_s0 = (void *)g_igPlanarShadowShader_metaObject;
    temp_s1 = igMetaObject_GetFieldCount((igMetaObject *)temp_s0);
    igMetaObject_CreateFields((igMetaObject *)temp_s0, g_igPlanarShadowShader_ctorTable, 0xD);
    temp_s2 = (void *)(((void *)igMetaObject_GetFieldAt((igMetaObject *)temp_s0, temp_s1)));
    ((igObjectRefMetaField *)temp_s2)->_metaObject = (int)igLightList_GetOrCreateMetaObject();
    ((igRefMetaField *)temp_s2)->_construct = 1;
    temp_s2_2 = (void *)(((void *)igMetaObject_GetFieldAt((igMetaObject *)temp_s0, temp_s1 + 1)));
    ((igObjectRefMetaField *)temp_s2_2)->_metaObject = (int)igModelViewMatrixAttrList_GetOrCreateMetaObject();
    ((igRefMetaField *)temp_s2_2)->_construct = 1;
    temp_a0 = (void *)(((void *)igMetaObject_GetFieldAt((igMetaObject *)temp_s0, temp_s1 + 2)));
    spA.x = 0; spA.y = 1.0f; spA.z = 0; spA.w = 0;
    ((Gap::Math::igVec4fMetaField *)temp_a0)->setDefault(*(const igVec4f *)&spA);
    temp_a0_2 = (void *)(((void *)igMetaObject_GetFieldAt((igMetaObject *)temp_s0, temp_s1 + 3)));
    spB.x = 0; spB.w = 1.0f; spB.y = 0; spB.z = 0;
    ((Gap::Math::igVec4fMetaField *)temp_a0_2)->setDefault(*(const igVec4f *)&spB);
    temp_s2_3 = (void *)(((void *)igMetaObject_GetFieldAt((igMetaObject *)temp_s0, temp_s1 + 6)));
    ((igObjectRefMetaField *)temp_s2_3)->_metaObject = (int)igModelViewMatrixAttrList_GetOrCreateMetaObject();
    ((igRefMetaField *)temp_s2_3)->_construct = 1;
    ((igMetaField *)temp_s2_3)->_persistent = 0;
    temp_s2_4 = (void *)(((void *)igMetaObject_GetFieldAt((igMetaObject *)temp_s0, temp_s1 + 7)));
    ((igObjectRefMetaField *)temp_s2_4)->_metaObject = (int)igGeometryList_GetOrCreateMetaObject();
    ((igRefMetaField *)temp_s2_4)->_construct = 1;
    ((igMetaField *)temp_s2_4)->_persistent = 0;
    temp_s2_5 = (void *)(((void *)igMetaObject_GetFieldAt((igMetaObject *)temp_s0, temp_s1 + 8)));
    ((igObjectRefMetaField *)temp_s2_5)->_metaObject = (int)igAttrList_GetOrCreateMetaObject();
    ((igRefMetaField *)temp_s2_5)->_construct = 1;
    ((igMetaField *)temp_s2_5)->_persistent = 0;
    temp_s2_6 = (void *)(((void *)igMetaObject_GetFieldAt((igMetaObject *)temp_s0, temp_s1 + 9)));
    ((igObjectRefMetaField *)temp_s2_6)->_metaObject = (int)igVolume_GetOrCreateMetaObject();
    ((igMetaField *)temp_s2_6)->_persistent = 0;
    temp_s2_7 = (void *)(((void *)igMetaObject_GetFieldAt((igMetaObject *)temp_s0, temp_s1 + 0xA)));
    ((igObjectRefMetaField *)temp_s2_7)->_metaObject = (int)igVolume_GetOrCreateMetaObject();
    ((igMetaField *)temp_s2_7)->_persistent = 0;
    temp_s2_8 = (void *)(((void *)igMetaObject_GetFieldAt((igMetaObject *)temp_s0, temp_s1 + 0xB)));
    ((igObjectRefMetaField *)temp_s2_8)->_metaObject = (int)igColorAttr_GetOrCreateMetaObject();
    ((igRefMetaField *)temp_s2_8)->_construct = 1;
    ((igMetaField *)temp_s2_8)->_persistent = 0;
    temp_s2_9 = (void *)(((void *)igMetaObject_GetFieldAt((igMetaObject *)temp_s0, temp_s1 + 0xC)));
    ((igObjectRefMetaField *)temp_s2_9)->_metaObject = (int)Gap::Attrs::igStencilStateAttr::getClassTypeLazy();
    ((igRefMetaField *)temp_s2_9)->_construct = 1;
    ((igMetaField *)temp_s2_9)->_persistent = 0;
    igMetaObject_NameFields((igMetaObject *)temp_s0, g_igPlanarShadowShader_fieldTable, g_igPlanarShadowShader_fieldHandles, g_igPlanarShadowShader_fieldOffsets, temp_s1);
}

