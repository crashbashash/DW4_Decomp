static const char *g_igThread_priorityNames[] = {
    "kFirst", "kLow", "kNormal", "kHigh",
    "kUrgent", "kLast",
};
static int g_igThread_priorityValues[] = {
    0, 0x32, 0x80, 0xc8, 0xff, 0xff,
};


int igThread_GetPriorityMetaEnum(void) {
    if (g_igThread_priorityMetaEnum == 0) {
        g_igThread_priorityMetaEnum = ((int)igMetaEnum_Create((char *)"Priority", g_igThread_priorityNames, g_igThread_priorityValues, 6));
    }
    return g_igThread_priorityMetaEnum;
}

static const char *g_igThread_stateNames[] = {
    "kJoinable", "kUnJoinable",
};
static int g_igThread_stateValues[] = {
    0, 1,
};


int igThread_GetStateMetaEnum(void) {
    if (g_igThread_stateMetaEnum == 0) {
        g_igThread_stateMetaEnum = ((int)igMetaEnum_Create((char *)"State", g_igThread_stateNames, g_igThread_stateValues, 2));
    }
    return g_igThread_stateMetaEnum;
}

static const char *g_igThread_scopeNames[] = {
    "kLocal", "kGlobal", "kGlobalBound",
};
static int g_igThread_scopeValues[] = {
    0, 1, 2,
};


int igThread_GetScopeMetaEnum(void) {
    if (g_igThread_scopeMetaEnum == 0) {
        g_igThread_scopeMetaEnum = ((int)igMetaEnum_Create((char *)"Scope", g_igThread_scopeNames, g_igThread_scopeValues, 3));
    }
    return g_igThread_scopeMetaEnum;
}

static const char *g_igThread_typeNames[] = {
    "kUser", "kSystem",
};
static int g_igThread_typeValues[] = {
    0, 1,
};


int igThread_GetTypeMetaEnum(void) {
    if (g_igThread_typeMetaEnum == 0) {
        g_igThread_typeMetaEnum = ((int)igMetaEnum_Create((char *)"Type", g_igThread_typeNames, g_igThread_typeValues, 2));
    }
    return g_igThread_typeMetaEnum;
}

igMetaObject *g_igThread_metaObject;
igMetaField *g_igThread_priorityMetaField;
igMetaField *g_igThread_typeMetaField;
igMetaField *g_igThread_scopeMetaField;
igMetaField *g_igThread_stateMetaField;
igMetaField *g_igThread_argMetaField;
igMetaField *g_igThread_stackMetaField;
igMetaField *g_igThread_stackSizeMetaField;
igMetaField *g_igThread_functionMetaField;
igMetaField *g_igThread_isMasterMetaField;
igMetaField *g_igThread_userStackMetaField;

igThread *igThread_Create(int allocator) {
    igThread_EnsureRegistered();
    return (igThread *)igMetaObject_CreateInstance(g_igThread_metaObject, (igMemoryPoolView *)allocator);
}

igMetaObject *igThread_GetOrCreateMetaObject(void) {
    if (g_igThread_metaObject == 0) {
        g_igThread_metaObject = (igMetaObject *)igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData));
    }
    return g_igThread_metaObject;
}

igMetaObject *igThread_GetMetaObject(void)
{
    igMetaObject *g = g_igThread_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false)
        igThread_EnsureRegistered();
    return g_igThread_metaObject;
}

void igThread_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(igThread_Register);
}

CallbackArray *igThread_Register(void) {
    CoreLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        1,
        &g_igThread_metaObject,
        igNamedObject_Register,
        (igMetaObjectGetFunction)igNamedObject_GetPublishedMetaObject,
        igThread_GetMetaObjectFunction,
        "igThread",
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

static FieldFactory g_igThread_ctorTable[] = {
    (FieldFactory)igEnumMetaField_Create,
    (FieldFactory)igEnumMetaField_Create,
    (FieldFactory)igEnumMetaField_Create,
    (FieldFactory)igEnumMetaField_Create,
    (FieldFactory)igRawRefMetaField_Create,
    (FieldFactory)igRawRefMetaField_Create,
    (FieldFactory)igUnsignedIntMetaField_Create,
    (FieldFactory)igRawRefMetaField_Create,
    (FieldFactory)igBoolMetaField_Create,
    (FieldFactory)igBoolMetaField_Create,
};
static const char *g_igThread_fieldTable[] = {
    "_priority",
    "_type",
    "_scope",
    "_state",
    "_arg",
    "_stack",
    "_stackSize",
    "_function",
    "_isMaster",
    "_userStack",
};
static igMetaField **g_igThread_fieldDescriptors[] = {
    &g_igThread_priorityMetaField,
    &g_igThread_typeMetaField,
    &g_igThread_scopeMetaField,
    &g_igThread_stateMetaField,
    &g_igThread_argMetaField,
    &g_igThread_stackMetaField,
    &g_igThread_stackSizeMetaField,
    &g_igThread_functionMetaField,
    &g_igThread_isMasterMetaField,
    &g_igThread_userStackMetaField,
};
static int g_igThread_fieldOffsets[] = {
    24,
    12,
    16,
    20,
    28,
    32,
    36,
    40,
    44,
    45,
};

int g_igThread_defaultPriority = 0x80;

void igThread_InitFields(void) {
    int base;
    void *priority;
    void *type;
    void *scope;
    void *state;
    void *meta;

    meta = (void *)((void *)g_igThread_metaObject);
    base = igMetaObject_GetFieldCount((igMetaObject *)meta);
    igMetaObject_CreateFields((igMetaObject *)meta, g_igThread_ctorTable, 0xA);
    priority = (void *)(((void *)igMetaObject_GetFieldAt((igMetaObject *)meta, base)));
    igEnumMetaField_SetDefaultValue((igMetaField *)priority, g_igThread_defaultPriority);
    ((igEnumMetaField *)priority)->_getMetaEnumFunction = (int)(igThread_GetPriorityMetaEnum);
    type = (void *)(((void *)igMetaObject_GetFieldAt((igMetaObject *)meta, base + 1)));
    igEnumMetaField_SetDefaultValue((igMetaField *)type, 0);
    ((igEnumMetaField *)type)->_getMetaEnumFunction = (int)(&igThread_GetTypeMetaEnum);
    scope = (void *)(((void *)igMetaObject_GetFieldAt((igMetaObject *)meta, base + 2)));
    igEnumMetaField_SetDefaultValue((igMetaField *)scope, 0);
    ((igEnumMetaField *)scope)->_getMetaEnumFunction = (int)(&igThread_GetScopeMetaEnum);
    state = (void *)(((void *)igMetaObject_GetFieldAt((igMetaObject *)meta, base + 3)));
    igEnumMetaField_SetDefaultValue((igMetaField *)state, 0);
    ((igEnumMetaField *)state)->_getMetaEnumFunction = (int)(&igThread_GetStateMetaEnum);
    igUnsignedIntMetaField_SetDefaultValue(igMetaObject_GetFieldAt((igMetaObject *)meta, base + 6), 0x1000);
    igMetaObject_NameFields((igMetaObject *)meta, g_igThread_fieldTable, g_igThread_fieldDescriptors, g_igThread_fieldOffsets, base);
    *(int *)((char *)((void *)g_igThread_metaObject) + 60) = (int)igPsx2Thread_GetMetaObjectFunction;
}

