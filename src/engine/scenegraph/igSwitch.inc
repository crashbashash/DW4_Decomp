igSwitch *igSwitch_CreateInstance(int allocator) {
    igSwitch_EnsureRegistered();
    return (igSwitch *)igMetaObject_CreateInstance((igMetaObject *)g_igSwitch_metaObject, (igMemoryPoolView *)allocator);
}

igMetaObject *g_igSwitch_metaObject;
igMetaField *g_igSwitch_childMaskMetaField;

igMetaObject *igSwitch_GetOrCreateMetaObject(void) {
    if (g_igSwitch_metaObject == 0) {
        g_igSwitch_metaObject = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData));
    }
    return g_igSwitch_metaObject;
}

igMetaObject *igSwitch_GetMetaObject(void)
{
    igMetaObject *g = g_igSwitch_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false)
        igSwitch_EnsureRegistered();
    return g_igSwitch_metaObject;
}

int igSwitch_GetVTable(void) {
    union U_1969d0 u;
    int temp_s0;
    char *ps;
    igObject_InitHeader((igObject *)u.b);
    *(int *)&u.b[8] = 0;
    *(int *)&u.b[12] = 0;
    *(int *)&u.b[16] = 0;
    *(int *)&u.b[28] = 0;
    u.vt = (int)&g_igSwitch_vtable[0];
    ps = &u.b[32];
    *(int *)ps = 0;
    temp_s0 = *(int *)&u.b[g_objectSystem->vtableProbeOffset];
    u.vt = (int)&g_igSwitch_vtable[0];
    igSmartPointer_igBitMask_Destruct((igSmartPointer<igObject> *)ps, -1);
    igGroup_Destroy((igGroup *)u.b, 0);
    return temp_s0;
}

igSmartPointer<igObject> *igSmartPointer_igBitMask_Destruct(igSmartPointer<igObject> *self, short deleteFlag) {
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

void igSwitch_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(igSwitch_Register);
}

static igMetaObjectCallback g_igSwitch_callbackList[] = { igBitMask_EnsureRegistered, 0 };

CallbackArray *igSwitch_Register(void) {
    SceneGraphLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_igSwitch_metaObject,
        igGroup_Register,
        igGroup_GetPublishedMetaObject,
        igSwitch_GetMetaObjectFunction,
        "igSwitch",
        0x24, /* instance size */
        igSwitch_GetVTable,
        &igSwitch_InitFields,
        0, /* extra callback item */
        g_igSwitch_callbackList /* callback list */
    );
}

void igSwitch_GetMetaObjectFunction(void) {
    igSwitch_GetMetaObject();
}

static FieldFactory g_igSwitch_ctorTable[] = {
    (FieldFactory)igObjectRefMetaField_Create,
};
static const char *g_igSwitch_fieldTable[] = {
    "_childMask",
};
static igMetaField **g_igSwitch_fieldHandles[] = {
    &g_igSwitch_childMaskMetaField,
};
static int g_igSwitch_fieldOffsets[] = {
    32,
};

void igSwitch_InitFields(void) {
    int base;
    void *childMaskField;
    void *meta;

    meta = (void *)g_igSwitch_metaObject;
    base = igMetaObject_GetFieldCount((igMetaObject *)meta);
    igMetaObject_CreateFields((igMetaObject *)meta, g_igSwitch_ctorTable, 1);
    childMaskField = (void *)(((void *)igMetaObject_GetFieldAt((igMetaObject *)meta, base)));
    ((igObjectRefMetaField *)childMaskField)->_metaObject = (int)igBitMask_GetOrCreateMetaObject();
    ((igRefMetaField *)childMaskField)->_construct = 1;
    igMetaObject_NameFields((igMetaObject *)meta, g_igSwitch_fieldTable, g_igSwitch_fieldHandles, g_igSwitch_fieldOffsets, base);
}

