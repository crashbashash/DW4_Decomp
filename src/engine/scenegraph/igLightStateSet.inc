igMetaObject *g_igLightStateSet_metaObject;
igMetaField *g_igLightStateSet_lightEnablesMetaField;

igMetaObject *igLightStateSet_GetMetaObject(void)
{
    igMetaObject *g = g_igLightStateSet_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false)
        igLightStateSet_EnsureRegistered();
    return g_igLightStateSet_metaObject;
}

int igLightStateSet_GetVTable(void) {
    struct Obj_19d960 obj;
    int r;

    igObject_InitHeader((igObject *)&obj);
    obj.w[1] = 0;
    obj.w[2] = 0;
    obj.w[3] = 0;
    obj.w[6] = 0;
    obj.vt = &g_igLightStateSet_vtable[0];
    obj.w[7] = 0;
    r = *(int *)((char *)&obj + g_objectSystem->vtableProbeOffset);
    obj.vt = &g_igLightStateSet_vtable[0];
    igSmartPointer_igLightStateAttrList_Destruct((igSmartPointer<igObject> *)&obj.w[7], -1);
    igGroup_Destroy((igGroup *)&obj, 0);
    return r;
}

igSmartPointer<igObject> *igSmartPointer_igLightStateAttrList_Destruct(igSmartPointer<igObject> *self, short deleteFlag) {
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

void igLightStateSet_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(igLightStateSet_Register);
}

static igMetaObjectCallback g_igLightStateSet_callbackList[] = { igLightStateAttrList_EnsureRegistered, 0 };

CallbackArray *igLightStateSet_Register(void) {
    SceneGraphLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_igLightStateSet_metaObject,
        igGroup_Register,
        igGroup_GetPublishedMetaObject,
        igLightStateSet_GetMetaObjectFunction,
        "igLightStateSet",
        0x24, /* instance size */
        igLightStateSet_GetVTable,
        &igLightStateSet_InitFields,
        0, /* extra callback item */
        g_igLightStateSet_callbackList /* callback list */
    );
}

void igLightStateSet_GetMetaObjectFunction(void) {
    igLightStateSet_GetMetaObject();
}

static FieldFactory g_igLightStateSet_ctorTable[] = {
    (FieldFactory)igObjectRefMetaField_Create,
};
static const char *g_igLightStateSet_fieldTable[] = {
    "_lightEnables",
};
static igMetaField **g_igLightStateSet_fieldHandles[] = {
    &g_igLightStateSet_lightEnablesMetaField,
};
static int g_igLightStateSet_fieldOffsets[] = {
    32,
};

void igLightStateSet_InitFields(void) {
    int temp_s2;
    void *temp_s1;
    void *temp_s0;

    temp_s0 = (void *)g_igLightStateSet_metaObject;
    temp_s2 = igMetaObject_GetFieldCount((igMetaObject *)temp_s0);
    igMetaObject_CreateFields((igMetaObject *)temp_s0, g_igLightStateSet_ctorTable, 1);
    temp_s1 = (void *)(((void *)igMetaObject_GetFieldAt((igMetaObject *)temp_s0, temp_s2)));
    ((igObjectRefMetaField *)temp_s1)->_metaObject = (int)igLightStateAttrList_GetOrCreateMetaObject();
    ((igRefMetaField *)temp_s1)->_construct = 1;
    ((igMetaField *)temp_s1)->_deepCopyMethod = 0;
    ((igMetaField *)temp_s1)->_shallowCopyMethod = 2;
    igMetaObject_NameFields((igMetaObject *)temp_s0, g_igLightStateSet_fieldTable, g_igLightStateSet_fieldHandles, g_igLightStateSet_fieldOffsets, temp_s2);
}

