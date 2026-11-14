igMetaObject *igDependencyOrderedList_GetMetaObject(void)
{
    igMetaObject *g = g_igDependencyOrderedList_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        igDependencyOrderedList_EnsureRegistered();
    return g_igDependencyOrderedList_metaObject[0];
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
    t = *(int *)((char *)&list + *(int *)((char *)(((void * *)g_objectSystem)[0]) + 916));
    list._vtable = (int)&g_igDependencyOrderedList_vtable[0];
    ObjectRef_Destruct_001c6460(&list._checkPoints, -1);
    FUN_00135430(&list._order, -1);
    FUN_00233590(&list._dependencies, -1);
    FUN_0014aa70(&list._objectList, -1);
    return t;
}

void igDependencyOrderedList_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit((StaticInitCallbacks * (*)())igDependencyOrderedList_Register);
}

void igDependencyOrderedList_Register(void) {
    CoreLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0,
        g_igDependencyOrderedList_metaObject,
        (igMetaObjectRegisterFunction)igObject_Register,
        (igMetaObjectGetFunction)igObject_GetMetaObject_ParentAccessor,
        igDependencyOrderedList_GetMetaObjectFunction,
        igDependencyOrderedList_className,
        0x1C,
        igDependencyOrderedList_GetVTable,
        igDependencyOrderedList_InitFields,
        0,
        (igMetaObjectCallback *)g_igDependencyOrderedList_callbackList
    );
}

void igDependencyOrderedList_GetMetaObjectFunction(void) {
    igDependencyOrderedList_GetMetaObject();
}

void igDependencyOrderedList_InitFields(void) {
    int base;
    void *objectListField;
    void *dependenciesField;
    void *orderField;
    void *checkPointsField;
    void *meta;

    meta = (void *)g_igDependencyOrderedList_metaObject[0];
    base = igMetaObject_GetFieldCount((igMetaObject *)meta);
    igMetaObject_CreateFields((igMetaObject *)meta, (igMetaField * (**)(void *))&g_igDependencyOrderedList_ctorTable[0], 5);
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
    igMetaObject_NameFields((igMetaObject *)meta, (const char **)&g_igDependencyOrderedList_fieldTable[0], (igMetaField ***)&g_igDependencyOrderedList_fieldDescriptors[0], &g_igDependencyOrderedList_fieldOffsets[0], base);
}

