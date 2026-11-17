igMetaObject *g_igViewerRenderer_metaObject;
igMetaField *g_igViewerRenderer_parametersMetaField;
igMetaField *g_igViewerRenderer_backFaceCullingAttrMetaField;
igMetaField *g_igViewerRenderer_alphaTestAttrMetaField;
igMetaField *g_igViewerRenderer_shadeModelAttrMetaField;
igMetaField *g_igViewerRenderer_polygonModeAttrMetaField;
igMetaField *g_igViewerRenderer_lightingAttrMetaField;
igMetaField *g_igViewerRenderer_headlightAttrMetaField;
igMetaField *g_igViewerRenderer_headlightStateAttrMetaField;
igMetaField *g_igViewerRenderer_attrSetMetaField;
igMetaField *g_igViewerRenderer_attrSetOverrideMetaField;
igMetaField *g_igViewerRenderer_headlightTransformMetaField;
igMetaField *g_igViewerRenderer_headlightSetMetaField;
igMetaField *g_igViewerRenderer_lightListMetaField;
igMetaField *g_igViewerRenderer_lightStateListMetaField;
igMetaField *g_igViewerRenderer_lightingStateMetaField;
igMetaField *g_igViewerRenderer_lightTraversalMetaField;
igMetaField *g_igViewerRenderer_lightOutputMetaField;
igMetaField *g_igViewerRenderer_sceneTraversalMetaField;
igMetaField *g_igViewerRenderer_sceneOutputMetaField;
igMetaField *g_igViewerRenderer_disableExtensionMetaField;

igMetaObject *FUN_0045aaf0(void) {
    if (g_igViewerRenderer_metaObject == 0) {
        g_igViewerRenderer_metaObject = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData));
    }
    return g_igViewerRenderer_metaObject;
}

igMetaObject *igViewerRenderer_GetMetaObject(void)
{
    unsigned char ready;
    if (g_igViewerRenderer_metaObject != 0) {
        ready = (g_igViewerRenderer_metaObject->_validity & 4) != 0;
        if (ready != 0) goto done;
    }
    FUN_0045b0d0();
done:
    return g_igViewerRenderer_metaObject;
}

int igViewerRenderer_GetVTable(void) {
    union U_45aaf0 u;
    int r;
    FUN_0045b090(&u.b[0]);
    u.pv = &g_igViewerRenderer_vtable[0];
    FUN_00459e20((int *)&u.b[12]);
    FUN_00197300(&u.b[16]);
    FUN_0045b080((int *)&u.b[20]);
    FUN_0045b070((int *)&u.b[24]);
    FUN_0045b060((int *)&u.b[28]);
    FUN_0045b050((int *)&u.b[32]);
    FUN_0019ac30(&u.b[36]);
    FUN_0045b040((int *)&u.b[40]);
    FUN_0045b030((int *)&u.b[44]);
    FUN_0045b020((int *)&u.b[48]);
    FUN_0045b010((int *)&u.b[52]);
    FUN_0045b000((int *)&u.b[56]);
    FUN_0019c370(&u.b[60]);
    FUN_0045aff0((int *)&u.b[64]);
    FUN_0045afe0((int *)&u.b[72]);
    FUN_00197350(&u.b[76]);
    FUN_0045afe0((int *)&u.b[80]);
    FUN_00197350(&u.b[84]);
    FUN_0045afd0((int *)&u.b[88]);
    r = *(int *)&u.b[*(int *)((char *)(((void *)g_objectSystem)) + 916)];
    u.pv = &g_igViewerRenderer_vtable[0];
    FUN_0045af50((void **)&u.b[88], -1);
    FUN_00197160(&u.b[84], -1);
    FUN_001d9870(&u.b[80], -1);
    FUN_00197160(&u.b[76], -1);
    FUN_001d9870(&u.b[72], -1);
    FUN_0019d9e0(&u.b[64], -1);
    FUN_0019c1a0(&u.b[60], -1);
    FUN_00239280(&u.b[56], -1);
    igSmartPointer_igTransform_Destruct(&u.b[52], -1);
    FUN_0045aed0((void **)&u.b[48], -1);
    igSmartPointer_igAttrSet_Destruct(&u.b[44], -1);
    FUN_00229460(&u.b[40], -1);
    FUN_00136370(&u.b[36], -1);
    igSmartPointer_igLightingStateAttr_Destruct(&u.b[32], -1);
    FUN_0045ae50((struct R **)&u.b[28], -1);
    FUN_0045add0((ObjectRefWord *)&u.b[24], -1);
    FUN_001d3090(&u.b[20], -1);
    FUN_00197060(&u.b[16], -1);
    FUN_00459860((ObjectRefWord *)&u.b[12], -1);
    FUN_00230f70(&u.b[0], 0);
    return r;
}

/* Deleting destructor; the deletion flag is a signed short. */
ObjectRefWord *FUN_0045add0(ObjectRefWord *self,int delete_storage) {
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

struct R **FUN_0045ae50(struct R **arg0, short arg1) {
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

void **FUN_0045aed0(void **arg0, long long arg1) {
    char *o;

    if (arg0 != 0) {
        o = (char *)*arg0;
        if (o != 0) {
            *(int *)(o + 4) = *(int *)(o + 4) - 1;
            if ((*(int *)(o + 4) & 0x7FFFFF) == 0) {
                igObject_Destroy((igObject *)o);
            }
        }
        if ((short)arg1 > 0) {
            operator delete(arg0);
        }
    }
    return arg0;
}

void **FUN_0045af50(void **arg0, int arg1) {
    int *o;

    if (arg0 != 0) {
        o = (int *)(*arg0);
        if (o != 0) {
            o[1] = o[1] - 1;
            if ((o[1] & 0x7FFFFF) == 0) {
                igObject_Destroy((igObject *)o);
            }
        }
        if ((short)arg1 > 0) {
            operator delete(arg0);
        }
    }
    return arg0;
}

int *FUN_0045afd0(int *p)
{
    *(int *)((char *)p + 0) = 0;
    return p;
}

int *FUN_0045afe0(int *p)
{
    *(int *)((char *)p + 0) = 0;
    return p;
}

int *FUN_0045aff0(int *p)
{
    *(int *)((char *)p + 0) = 0;
    return p;
}

int *FUN_0045b000(int *p)
{
    *(int *)((char *)p + 0) = 0;
    return p;
}

int *FUN_0045b010(int *p)
{
    *(int *)((char *)p + 0) = 0;
    return p;
}

int *FUN_0045b020(int *p)
{
    *(int *)((char *)p + 0) = 0;
    return p;
}

int *FUN_0045b030(int *p)
{
    *(int *)((char *)p + 0) = 0;
    return p;
}

int *FUN_0045b040(int *p)
{
    *(int *)((char *)p + 0) = 0;
    return p;
}

int *FUN_0045b050(int *p)
{
    *(int *)((char *)p + 0) = 0;
    return p;
}

int *FUN_0045b060(int *p)
{
    *(int *)((char *)p + 0) = 0;
    return p;
}

int *FUN_0045b070(int *p)
{
    *(int *)((char *)p + 0) = 0;
    return p;
}

int *FUN_0045b080(int *p)
{
    *(int *)((char *)p + 0) = 0;
    return p;
}

void *FUN_0045b090(void *arg0) {
    igObject_InitHeader((igObject *)arg0);
    *(int *)((char *)(arg0) + 0) = (int)(&g_igRenderer_vtable[0]);
    *(int *)((char *)(arg0) + 8) = 0;
    return arg0;
}

void FUN_0045b0d0(void)
{
    igMetaObject_RunStaticInit(igViewerRenderer_Register);
}

static igMetaObjectCallback g_igViewerRenderer_callbackList[] = { igViewerParameters_EnsureRegistered, igCullFaceAttr_EnsureRegistered, igAlphaStateAttr_EnsureRegistered, igShadeModelAttr_EnsureRegistered, FUN_00134a20, igLightingStateAttr_EnsureRegistered, igLightAttr_EnsureRegistered, igLightStateAttr_EnsureRegistered, igAttrSet_EnsureRegistered, FUN_0019c7b0, igTransform_EnsureRegistered, igLightSet_EnsureRegistered, igLightList_EnsureRegistered, igLightStateAttrList_EnsureRegistered, igCommonTraversal_EnsureRegistered, FUN_00138160, FUN_0014f810, 0 };

CallbackArray *igViewerRenderer_Register(void) {
    ViewerLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_igViewerRenderer_metaObject,
        igRenderer_Register,
        igRenderer_GetPublishedMetaObject,
        thunk_igViewerRenderer_GetMetaObject,
        "igViewerRenderer",
        0x5C, /* instance size */
        igViewerRenderer_GetVTable,
        &igViewerRenderer_InitFields,
        0, /* extra callback item */
        g_igViewerRenderer_callbackList /* callback list */
    );
}

void thunk_igViewerRenderer_GetMetaObject(void) {
    igViewerRenderer_GetMetaObject();
}

static FieldFactory g_igViewerRenderer_ctorTable[] = {
    igObjectRefMetaField_Create,
    igObjectRefMetaField_Create,
    igObjectRefMetaField_Create,
    igObjectRefMetaField_Create,
    igObjectRefMetaField_Create,
    igObjectRefMetaField_Create,
    igObjectRefMetaField_Create,
    igObjectRefMetaField_Create,
    igObjectRefMetaField_Create,
    igObjectRefMetaField_Create,
    igObjectRefMetaField_Create,
    igObjectRefMetaField_Create,
    igObjectRefMetaField_Create,
    igObjectRefMetaField_Create,
    igBoolMetaField_Create,
    igObjectRefMetaField_Create,
    igObjectRefMetaField_Create,
    igObjectRefMetaField_Create,
    igObjectRefMetaField_Create,
    igObjectRefMetaField_Create,
};
static const char *g_igViewerRenderer_fieldTable[] = {
    "_parameters",
    "_backFaceCullingAttr",
    "_alphaTestAttr",
    "_shadeModelAttr",
    "_polygonModeAttr",
    "_lightingAttr",
    "_headlightAttr",
    "_headlightStateAttr",
    "_attrSet",
    "_attrSetOverride",
    "_headlightTransform",
    "_headlightSet",
    "_lightList",
    "_lightStateList",
    "_lightingState",
    "_lightTraversal",
    "_lightOutput",
    "_sceneTraversal",
    "_sceneOutput",
    "_disableExtension",
};
static igMetaField **g_igViewerRenderer_fieldHandles[] = {
    &g_igViewerRenderer_parametersMetaField,
    &g_igViewerRenderer_backFaceCullingAttrMetaField,
    &g_igViewerRenderer_alphaTestAttrMetaField,
    &g_igViewerRenderer_shadeModelAttrMetaField,
    &g_igViewerRenderer_polygonModeAttrMetaField,
    &g_igViewerRenderer_lightingAttrMetaField,
    &g_igViewerRenderer_headlightAttrMetaField,
    &g_igViewerRenderer_headlightStateAttrMetaField,
    &g_igViewerRenderer_attrSetMetaField,
    &g_igViewerRenderer_attrSetOverrideMetaField,
    &g_igViewerRenderer_headlightTransformMetaField,
    &g_igViewerRenderer_headlightSetMetaField,
    &g_igViewerRenderer_lightListMetaField,
    &g_igViewerRenderer_lightStateListMetaField,
    &g_igViewerRenderer_lightingStateMetaField,
    &g_igViewerRenderer_lightTraversalMetaField,
    &g_igViewerRenderer_lightOutputMetaField,
    &g_igViewerRenderer_sceneTraversalMetaField,
    &g_igViewerRenderer_sceneOutputMetaField,
    &g_igViewerRenderer_disableExtensionMetaField,
};
static int g_igViewerRenderer_fieldOffsets[] = {
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
};

void igViewerRenderer_InitFields(void) {
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
    void *temp_s2_2;
    void *temp_s2_3;
    void *temp_s2_4;
    void *temp_s2_5;
    void *temp_s2_6;
    void *temp_s2_7;
    void *temp_s2_8;
    void *temp_s2_9;
    int temp_s1;
    void *temp_s0;

    temp_s0 = g_igViewerRenderer_metaObject;
    temp_s1 = igMetaObject_GetFieldCount((igMetaObject *)temp_s0);
    igMetaObject_CreateFields((igMetaObject *)temp_s0, g_igViewerRenderer_ctorTable, 0x14);
    temp_s2 = (void *)(igMetaObject_GetFieldAt((igMetaObject *)temp_s0, temp_s1));
    ((igObjectRefMetaField *)temp_s2)->_metaObject = (int)igViewerParameters_GetOrCreateMetaObject();
    temp_s2_2 = (void *)(igMetaObject_GetFieldAt((igMetaObject *)temp_s0, temp_s1 + 1));
    ((igObjectRefMetaField *)temp_s2_2)->_metaObject = FUN_001386d0();
    ((igRefMetaField *)temp_s2_2)->_construct = 1;
    temp_s2_3 = (void *)(igMetaObject_GetFieldAt((igMetaObject *)temp_s0, temp_s1 + 2));
    ((igObjectRefMetaField *)temp_s2_3)->_metaObject = FUN_0013b2b0();
    ((igRefMetaField *)temp_s2_3)->_construct = 1;
    temp_s2_4 = (void *)(igMetaObject_GetFieldAt((igMetaObject *)temp_s0, temp_s1 + 3));
    ((igObjectRefMetaField *)temp_s2_4)->_metaObject = FUN_00133950();
    ((igRefMetaField *)temp_s2_4)->_construct = 1;
    temp_s2_5 = (void *)(igMetaObject_GetFieldAt((igMetaObject *)temp_s0, temp_s1 + 4));
    ((igObjectRefMetaField *)temp_s2_5)->_metaObject = FUN_00134940();
    ((igRefMetaField *)temp_s2_5)->_construct = 1;
    temp_s2_6 = (void *)(igMetaObject_GetFieldAt((igMetaObject *)temp_s0, temp_s1 + 5));
    ((igObjectRefMetaField *)temp_s2_6)->_metaObject = (int)(igLightingStateAttr_GetOrCreateMetaObject());
    ((igRefMetaField *)temp_s2_6)->_construct = 1;
    temp_s2_7 = (void *)(igMetaObject_GetFieldAt((igMetaObject *)temp_s0, temp_s1 + 6));
    ((igObjectRefMetaField *)temp_s2_7)->_metaObject = FUN_00136750();
    ((igRefMetaField *)temp_s2_7)->_construct = 1;
    temp_s2_8 = (void *)(igMetaObject_GetFieldAt((igMetaObject *)temp_s0, temp_s1 + 7));
    ((igObjectRefMetaField *)temp_s2_8)->_metaObject = FUN_001361f0();
    ((igRefMetaField *)temp_s2_8)->_construct = 1;
    temp_s2_9 = (void *)(igMetaObject_GetFieldAt((igMetaObject *)temp_s0, temp_s1 + 8));
    ((igObjectRefMetaField *)temp_s2_9)->_metaObject = (int)(igAttrSet_GetOrCreateMetaObject());
    ((igRefMetaField *)temp_s2_9)->_construct = 1;
    temp_s2_10 = (void *)(igMetaObject_GetFieldAt((igMetaObject *)temp_s0, temp_s1 + 9));
    ((igObjectRefMetaField *)temp_s2_10)->_metaObject = FUN_0019c6a0();
    ((igRefMetaField *)temp_s2_10)->_construct = 1;
    temp_s2_11 = (void *)(igMetaObject_GetFieldAt((igMetaObject *)temp_s0, temp_s1 + 0xA));
    ((igObjectRefMetaField *)temp_s2_11)->_metaObject = (int)(igTransform_GetOrCreateMetaObject());
    ((igRefMetaField *)temp_s2_11)->_construct = 1;
    temp_s2_12 = (void *)(igMetaObject_GetFieldAt((igMetaObject *)temp_s0, temp_s1 + 0xB));
    ((igObjectRefMetaField *)temp_s2_12)->_metaObject = FUN_0019dbb0();
    ((igRefMetaField *)temp_s2_12)->_construct = 1;
    temp_s2_13 = (void *)(igMetaObject_GetFieldAt((igMetaObject *)temp_s0, temp_s1 + 0xC));
    ((igObjectRefMetaField *)temp_s2_13)->_metaObject = FUN_001365e0();
    ((igRefMetaField *)temp_s2_13)->_construct = 1;
    temp_s2_14 = (void *)(igMetaObject_GetFieldAt((igMetaObject *)temp_s0, temp_s1 + 0xD));
    ((igObjectRefMetaField *)temp_s2_14)->_metaObject = FUN_00136040();
    ((igRefMetaField *)temp_s2_14)->_construct = 1;
    temp_s2_15 = (void *)(igMetaObject_GetFieldAt((igMetaObject *)temp_s0, temp_s1 + 0xF));
    ((igObjectRefMetaField *)temp_s2_15)->_metaObject = FUN_001a38e0();
    ((igRefMetaField *)temp_s2_15)->_construct = 1;
    temp_s2_16 = (void *)(igMetaObject_GetFieldAt((igMetaObject *)temp_s0, temp_s1 + 0x10));
    ((igObjectRefMetaField *)temp_s2_16)->_metaObject = FUN_00137fb0();
    temp_s2_17 = (void *)(igMetaObject_GetFieldAt((igMetaObject *)temp_s0, temp_s1 + 0x11));
    ((igObjectRefMetaField *)temp_s2_17)->_metaObject = FUN_001a38e0();
    temp_s2_18 = (void *)(igMetaObject_GetFieldAt((igMetaObject *)temp_s0, temp_s1 + 0x12));
    ((igObjectRefMetaField *)temp_s2_18)->_metaObject = FUN_00137fb0();
    temp_s2_19 = (void *)(igMetaObject_GetFieldAt((igMetaObject *)temp_s0, temp_s1 + 0x13));
    ((igObjectRefMetaField *)temp_s2_19)->_metaObject = FUN_0014f770();
    igMetaObject_NameFields((igMetaObject *)temp_s0, g_igViewerRenderer_fieldTable, g_igViewerRenderer_fieldHandles, g_igViewerRenderer_fieldOffsets, temp_s1);
}

