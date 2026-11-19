igMetaObject *g_igDependencyOrderedList_metaObject;
igMetaField *g_igDependencyOrderedList_objectListMetaField;
igMetaField *g_igDependencyOrderedList_dependenciesMetaField;
igMetaField *g_igDependencyOrderedList_orderMetaField;
igMetaField *g_igDependencyOrderedList_checkPointsMetaField;
igMetaField *g_igDependencyOrderedList_hasCircularDependenciesMetaField;

igMetaObject *igDependencyOrderedList_GetMetaObject(void)
{
    igMetaObject *g = g_igDependencyOrderedList_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false)
        igDependencyOrderedList_EnsureRegistered();
    return g_igDependencyOrderedList_metaObject;
}

int igDependencyOrderedList_GetVTable(void) {
    igDependencyOrderedList list;
    int t;
    igObject_InitHeader((igObject *)&list);
    list._vtable = (int)&g_igDependencyOrderedList_vtable[0];
    list._objectList = 0;
    list._dependencies = 0;
    list._order = 0;
    list._checkPoints = 0;
    t = *(int *)((char *)&list + g_objectSystem->vtableProbeOffset);
    list._vtable = (int)&g_igDependencyOrderedList_vtable[0];
    igSmartPointer_igStringRefList_Destruct((igSmartPointer<igObject> *)&list._checkPoints, -1);
    igSmartPointer_igPointerList_Destruct((igSmartPointer<igObject> *)&list._order, -1);
    igSmartPointer_igDependencyList_Destruct((igSmartPointer<igObject> *)&list._dependencies, -1);
    igSmartPointer_igObjectList_Destruct((igSmartPointer<igObject> *)&list._objectList, -1);
    return t;
}

void igDependencyOrderedList_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(igDependencyOrderedList_Register);
}

static igMetaObjectCallback g_igDependencyOrderedList_callbackList[] = { igObjectList_EnsureRegistered, igDependencyList_EnsureRegistered, igPointerList_EnsureRegistered, igStringRefList_EnsureRegistered, 0 };

CallbackArray *igDependencyOrderedList_Register(void) {
    CoreLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0,
        &g_igDependencyOrderedList_metaObject,
        Gap::Core::igObject::arkRegisterInternal,
        igObject_GetMetaObject_ParentAccessor,
        igDependencyOrderedList_GetMetaObjectFunction,
        "igDependencyOrderedList",
        0x1C,
        igDependencyOrderedList_GetVTable,
        igDependencyOrderedList_InitFields,
        0,
        g_igDependencyOrderedList_callbackList
    );
}

void igDependencyOrderedList_GetMetaObjectFunction(void) {
    igDependencyOrderedList_GetMetaObject();
}

static FieldFactory g_igDependencyOrderedList_ctorTable[] = {
    (FieldFactory)igObjectRefMetaField_Create,
    (FieldFactory)igObjectRefMetaField_Create,
    (FieldFactory)igObjectRefMetaField_Create,
    (FieldFactory)igObjectRefMetaField_Create,
    (FieldFactory)igBoolMetaField_Create,
};
static const char *g_igDependencyOrderedList_fieldTable[] = {
    "_objectList",
    "_dependencies",
    "_order",
    "_checkPoints",
    "_hasCircularDependencies",
};
static igMetaField **g_igDependencyOrderedList_fieldDescriptors[] = {
    &g_igDependencyOrderedList_objectListMetaField,
    &g_igDependencyOrderedList_dependenciesMetaField,
    &g_igDependencyOrderedList_orderMetaField,
    &g_igDependencyOrderedList_checkPointsMetaField,
    &g_igDependencyOrderedList_hasCircularDependenciesMetaField,
};
static int g_igDependencyOrderedList_fieldOffsets[] = {
    8,
    12,
    16,
    20,
    24,
};

void igDependencyOrderedList_InitFields(void) {
    int base;
    void *objectListField;
    void *dependenciesField;
    void *orderField;
    void *checkPointsField;
    void *meta;

    meta = (void *)g_igDependencyOrderedList_metaObject;
    base = igMetaObject_GetFieldCount((igMetaObject *)meta);
    igMetaObject_CreateFields((igMetaObject *)meta, g_igDependencyOrderedList_ctorTable, 5);
    objectListField = (void *)(((void *)igMetaObject_GetFieldAt((igMetaObject *)meta, base)));
    ((igObjectRefMetaField *)objectListField)->_metaObject = igObjectList_GetOrCreateMetaObject();
    ((igRefMetaField *)objectListField)->_construct = 1;
    dependenciesField = (void *)(((void *)igMetaObject_GetFieldAt((igMetaObject *)meta, base + 1)));
    ((igObjectRefMetaField *)dependenciesField)->_metaObject = (int)igDependencyList_GetOrCreateMetaObject();
    ((igRefMetaField *)dependenciesField)->_construct = 1;
    orderField = (void *)(((void *)igMetaObject_GetFieldAt((igMetaObject *)meta, base + 2)));
    ((igObjectRefMetaField *)orderField)->_metaObject = (int)igPointerList_GetOrCreateMetaObject();
    ((igRefMetaField *)orderField)->_construct = 1;
    checkPointsField = (void *)(((void *)igMetaObject_GetFieldAt((igMetaObject *)meta, base + 3)));
    ((igObjectRefMetaField *)checkPointsField)->_metaObject = (int)igStringRefList_GetOrCreateMetaObject();
    ((igRefMetaField *)checkPointsField)->_construct = 1;
    igMetaObject_NameFields((igMetaObject *)meta, g_igDependencyOrderedList_fieldTable, g_igDependencyOrderedList_fieldDescriptors, g_igDependencyOrderedList_fieldOffsets, base);
}

