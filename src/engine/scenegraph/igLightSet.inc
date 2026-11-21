igMetaObject *g_igLightSet_metaObject;
igMetaField *g_igLightSet_lightsMetaField;

igMetaObject *igLightSet_GetOrCreateMetaObject(void) {
    if (g_igLightSet_metaObject == 0) {
        g_igLightSet_metaObject = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData));
    }
    return g_igLightSet_metaObject;
}

igMetaObject *igLightSet_GetMetaObject(void)
{
    igMetaObject *g = g_igLightSet_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false)
        igLightSet_EnsureRegistered();
    return g_igLightSet_metaObject;
}

int igLightSet_GetVTable(void) {
    struct Obj_19dc50 o;
    int r;
    igObject_InitHeader((igObject *)&o);
    o.f8 = 0;
    o.f12 = 0;
    o.f16 = 0;
    o.vt = &g_igLightSet_vtable[0];
    o.f28 = 0;
    r = *(int *)((char *)&o + g_objectSystem->vtableProbeOffset);
    o.vt = &g_igLightSet_vtable[0];
    igSmartPointer_igLightList_Destruct((igSmartPointer<igObject> *)&o.f28, -1);
    igNode_Destroy((igNode *)&o, 0);
    return r;
}

void igLightSet_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(igLightSet_Register);
}

static igMetaObjectCallback g_igLightSet_callbackList[] = { igLightList_EnsureRegistered, 0 };

CallbackArray *igLightSet_Register(void) {
    SceneGraphLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_igLightSet_metaObject,
        igNode_Register,
        igNode_GetPublishedMetaObject,
        igLightSet_GetMetaObjectFunction,
        "igLightSet",
        0x20, /* instance size */
        igLightSet_GetVTable,
        &igLightSet_InitFields,
        0, /* extra callback item */
        g_igLightSet_callbackList /* callback list */
    );
}

void igLightSet_GetMetaObjectFunction(void) {
    igLightSet_GetMetaObject();
}

igMetaObject *igNode_GetPublishedMetaObject(void) {
    return g_igNode_metaObject;
}

static FieldFactory g_igLightSet_ctorTable[] = {
    (FieldFactory)igObjectRefMetaField_Create,
};
static const char *g_igLightSet_fieldTable[] = {
    "_lights",
};
static igMetaField **g_igLightSet_fieldHandles[] = {
    &g_igLightSet_lightsMetaField,
};
static int g_igLightSet_fieldOffsets[] = {
    28,
};

void igLightSet_InitFields(void) {
    int temp_s2;
    void *temp_s1;
    void *temp_s0;

    temp_s0 = (void *)g_igLightSet_metaObject;
    temp_s2 = igMetaObject_GetFieldCount((igMetaObject *)temp_s0);
    igMetaObject_CreateFields((igMetaObject *)temp_s0, g_igLightSet_ctorTable, 1);
    temp_s1 = (void *)(((void *)igMetaObject_GetFieldAt((igMetaObject *)temp_s0, temp_s2)));
    ((igObjectRefMetaField *)temp_s1)->_metaObject = (int)igLightList_GetOrCreateMetaObject();
    ((igRefMetaField *)temp_s1)->_construct = 1;
    ((igMetaField *)temp_s1)->_deepCopyMethod = 0;
    ((igMetaField *)temp_s1)->_shallowCopyMethod = 2;
    igMetaObject_NameFields((igMetaObject *)temp_s0, g_igLightSet_fieldTable, g_igLightSet_fieldHandles, g_igLightSet_fieldOffsets, temp_s2);
}

igMetaObject *igTransform_GetPublishedMetaObject(void) {
    return g_igTransform_metaObject;
}

igMetaObject *g_igAnimationSequence_metaObject;

igMetaObject *igAnimationSequence_GetPublishedMetaObject(void) {
    return g_igAnimationSequence_metaObject;
}

igSmartPointer<igObject> *igSmartPointer_igAnimationTransitionDefinitionList_Destruct(igSmartPointer<igObject> *self, short deleteFlag) {
    if (self) {
        igObject *object = self->p;
        igObject::release(object);
        if (deleteFlag > 0) operator delete(self);
    }
    return self;
}

igSmartPointer<igObject> *igSmartPointer_igAnimationTrackList_Destruct(igSmartPointer<igObject> *self, short deleteFlag) {
    if (self) {
        igObject *object = self->p;
        igObject::release(object);
        if (deleteFlag > 0) operator delete(self);
    }
    return self;
}

igSmartPointer<igObject> *igSmartPointer_igAnimationBindingList_Destruct(igSmartPointer<igObject> *self, short deleteFlag) {
    if (self) {
        igObject *object = self->p;
        igObject::release(object);
        if (deleteFlag > 0) operator delete(self);
    }
    return self;
}

