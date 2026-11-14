int igThread_GetPriorityMetaEnum(void) {
    if (g_igThread_priorityMetaEnum[0] == 0) {
        g_igThread_priorityMetaEnum[0] = ((int)igMetaEnum_Create((char *)&text_Priority[0], (char **)&g_igThread_priorityNames[0], &g_igThread_priorityValues[0], 6));
    }
    return g_igThread_priorityMetaEnum[0];
}

int igThread_GetStateMetaEnum(void) {
    if (g_igThread_stateMetaEnum[0] == 0) {
        g_igThread_stateMetaEnum[0] = ((int)igMetaEnum_Create((char *)&text_State[0], (char **)&g_igThread_stateNames[0], &g_igThread_stateValues[0], 2));
    }
    return g_igThread_stateMetaEnum[0];
}

int igThread_GetScopeMetaEnum(void) {
    if (g_igThread_scopeMetaEnum[0] == 0) {
        g_igThread_scopeMetaEnum[0] = ((int)igMetaEnum_Create((char *)&text_Scope[0], (char **)&g_igThread_scopeNames[0], &g_igThread_scopeValues[0], 3));
    }
    return g_igThread_scopeMetaEnum[0];
}

int igThread_GetTypeMetaEnum(void) {
    if (g_igThread_typeMetaEnum[0] == 0) {
        g_igThread_typeMetaEnum[0] = ((int)igMetaEnum_Create((char *)&text_Type[0], (char **)&g_igThread_typeNames[0], &g_igThread_typeValues[0], 2));
    }
    return g_igThread_typeMetaEnum[0];
}

void * igThread_Create(int allocator) {
    igThread_EnsureRegistered();
    return (void *)(igMetaObject_CreateInstance((igMetaObject *)(*(int *)0x5857C8), (igMemoryPoolView *)allocator));
}

igMetaObject *igThread_GetOrCreateMetaObject(void) {
    if (g_igThread_metaObject[0] == 0) {
        g_igThread_metaObject[0] = (igMetaObject *)igMetaObject_Create(((int)Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData)));
    }
    return g_igThread_metaObject[0];
}

igMetaObject *igThread_GetMetaObject(void)
{
    igMetaObject *g = g_igThread_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        igThread_EnsureRegistered();
    return g_igThread_metaObject[0];
}

void igThread_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit((StaticInitCallbacks * (*)())igThread_Register);
}

void igThread_Register(void) {
    CoreLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        1,
        g_igThread_metaObject,
        (igMetaObjectRegisterFunction)igNamedObject_Register,
        (igMetaObjectGetFunction)igNamedObject_GetPublishedMetaObject,
        igThread_GetMetaObjectFunction,
        igThread_className,
        0x30,
        0,
        igThread_InitFields,
        0,
        0
    );
}

void igThread_GetMetaObjectFunction(void) {
    igThread_GetMetaObject();
}

void igThread_InitFields(void) {
    int base;
    void *priority;
    void *type;
    void *scope;
    void *state;
    void *meta;

    meta = (void *)(((void * *)g_igThread_metaObject)[0]);
    base = igMetaObject_GetFieldCount((igMetaObject *)meta);
    igMetaObject_CreateFields((igMetaObject *)meta, (igMetaField * (**)(void *))&g_igThread_ctorTable[0], 0xA);
    priority = (void *)(((void *)igMetaObject_GetFieldAt((igMetaObject *)meta, base)));
    igEnumMetaField_SetDefaultValue((igMetaFieldView *)priority, (const int *)&g_igThread_defaultPriority[0]);
    ((igEnumMetaField *)priority)->_getMetaEnumFunction = (int)(igThread_GetPriorityMetaEnum);
    type = (void *)(((void *)igMetaObject_GetFieldAt((igMetaObject *)meta, base + 1)));
    igEnumMetaField_SetDefaultValue((igMetaFieldView *)type, (const int *)&g_igThread_defaultType[0]);
    ((igEnumMetaField *)type)->_getMetaEnumFunction = (int)(&igThread_GetTypeMetaEnum);
    scope = (void *)(((void *)igMetaObject_GetFieldAt((igMetaObject *)meta, base + 2)));
    igEnumMetaField_SetDefaultValue((igMetaFieldView *)scope, (const int *)&g_igThread_defaultScope[0]);
    ((igEnumMetaField *)scope)->_getMetaEnumFunction = (int)(&igThread_GetScopeMetaEnum);
    state = (void *)(((void *)igMetaObject_GetFieldAt((igMetaObject *)meta, base + 3)));
    igEnumMetaField_SetDefaultValue((igMetaFieldView *)state, (const int *)&g_igThread_defaultState[0]);
    ((igEnumMetaField *)state)->_getMetaEnumFunction = (int)(&igThread_GetStateMetaEnum);
    igUnsignedIntMetaField_SetDefaultValue((void **)(((void *)igMetaObject_GetFieldAt((igMetaObject *)meta, base + 6))), 0x1000);
    igMetaObject_NameFields((igMetaObject *)meta, (const char **)&g_igThread_fieldTable[0], (igMetaField ***)&g_igThread_fieldDescriptors[0], &g_igThread_fieldOffsets[0], base);
    *(int *)((char *)(((void * *)g_igThread_metaObject)[0]) + 60) = (int)igPsx2Thread_GetMetaObjectFunction;
}

