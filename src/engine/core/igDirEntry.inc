static const char *g_igDirEntry_refTypeNames[] = {
    "kObjectRef", "kMemoryRef", "kRawRef",
};
static int g_igDirEntry_refTypeValues[] = {
    0, 1, 2,
};


int igDirEntry_GetRefTypeMetaEnum(void) {
    if (g_igDirEntry_refTypeMetaEnum == 0) {
        g_igDirEntry_refTypeMetaEnum = ((int)igMetaEnum_Create((char *)"RefType", g_igDirEntry_refTypeNames, g_igDirEntry_refTypeValues, 3));
    }
    return g_igDirEntry_refTypeMetaEnum;
}

static const char *g_igDirEntry_resolveMethodNames[] = {
    "kLocal", "kNameSpace", "kGlobal",
};
static int g_igDirEntry_resolveMethodValues[] = {
    0, 1, 2,
};


int igDirEntry_GetResolveMethodMetaEnum(void) {
    if (g_igDirEntry_resolveMethodMetaEnum == 0) {
        g_igDirEntry_resolveMethodMetaEnum = ((int)igMetaEnum_Create((char *)"ResolveMethod", g_igDirEntry_resolveMethodNames, g_igDirEntry_resolveMethodValues, 3));
    }
    return g_igDirEntry_resolveMethodMetaEnum;
}

void * igDirEntry_Create(int pool) {
    igDirEntry_EnsureRegistered();
    return (void *)(igMetaObject_CreateInstance(g_igDirEntry_metaObject, (igMemoryPoolView *)pool));
}

igMetaObject *igDirEntry_GetMetaObject(void)
{
    igMetaObject *g = g_igDirEntry_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false)
        igDirEntry_EnsureRegistered();
    return g_igDirEntry_metaObject;
}

int igDirEntry_GetVTable(void) {
    igDirEntry entry;
    int vtable;
    char *ps;
    int *chars;
    int *header;
    int refCount;
    igObject_InitHeader((igObject *)&entry);
    ps = (char *)&entry._name;
    *(int *)ps = 0;
    entry._vtable = (int)&g_igNamedObject_vtable[0];
    entry._vtable = (int)&g_igDirEntry_vtable[0];
    vtable = *(int *)((char *)&entry + *(int *)((char *)((*(void * *)&g_objectSystem)) + 916));
    entry._vtable = (int)&g_igNamedObject_vtable[0];
    if (ps != 0) {
        chars = *(int **)ps;
        if (chars != 0) {
            header = chars - 2;
            refCount = chars[-1] - 1;
            chars[-1] = refCount;
            if (refCount == 0) {
                StringChunk_ReleaseHeader((StringChunk *)(*header), (int)header);
            }
        }
    }
    return vtable;
}

void igDirEntry_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit((StaticInitCallbacks * (*)())igDirEntry_Register);
}

void igDirEntry_Register(void) {
    CoreLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0,
        &g_igDirEntry_metaObject,
        (igMetaObjectRegisterFunction)igNamedObject_Register,
        (igMetaObjectGetFunction)igNamedObject_GetPublishedMetaObject,
        igDirEntry_GetMetaObjectFunction,
        "igDirEntry",
        0x1C,
        igDirEntry_GetVTable,
        igDirEntry_InitFields,
        0,
        0
    );
}

void igDirEntry_GetMetaObjectFunction(void) {
    igDirEntry_GetMetaObject();
}

static FieldFactory g_igDirEntry_ctorTable[] = {
    (FieldFactory)igIntMetaField_Create,
    (FieldFactory)igEnumMetaField_Create,
    (FieldFactory)igEnumMetaField_Create,
    (FieldFactory)igRawRefMetaField_Create,
};
static const char *g_igDirEntry_fieldTable[] = {
    "_index",
    "_resolveMethod",
    "_refType",
    "_ref",
};
static igMetaField **g_igDirEntry_fieldDescriptors[] = {
    &g_igDirEntry_indexMetaField,
    &g_igDirEntry_resolveMethodMetaField,
    &g_igDirEntry_refTypeMetaField,
    &g_igDirEntry_refField,
};
static int g_igDirEntry_fieldOffsets[] = {
    12,
    16,
    20,
    24,
};

void igDirEntry_InitFields(void) {
    int first;
    void *refTypeField;
    void *resolveMethodField;
    void *indexField;
    void *meta;

    meta = (void *)g_igDirEntry_metaObject;
    first = igMetaObject_GetFieldCount((igMetaObject *)meta);
    igMetaObject_CreateFields((igMetaObject *)meta, g_igDirEntry_ctorTable, 4);
    indexField = (void *)(((void *)igMetaObject_GetFieldAt((igMetaObject *)meta, first)));
    igIntMetaField_SetDefault((void **)indexField, -1);
    ((igIntMetaField *)indexField)->_persistent = 0;
    resolveMethodField = (void *)(((void *)igMetaObject_GetFieldAt((igMetaObject *)meta, first + 1)));
    igEnumMetaField_SetDefaultValue((igMetaFieldView *)resolveMethodField, (const int *)&g_igDirEntry_resolveMethodDefault[0]);
    ((igEnumMetaField *)resolveMethodField)->_persistent = 0;
    ((igEnumMetaField *)resolveMethodField)->_getMetaEnumFunction = (int)(&igDirEntry_GetResolveMethodMetaEnum);
    refTypeField = (void *)(((void *)igMetaObject_GetFieldAt((igMetaObject *)meta, first + 2)));
    igEnumMetaField_SetDefaultValue((igMetaFieldView *)refTypeField, (const int *)&g_igDirEntry_refTypeDefault[0]);
    ((igEnumMetaField *)refTypeField)->_persistent = 0;
    ((igEnumMetaField *)refTypeField)->_getMetaEnumFunction = (int)(igDirEntry_GetRefTypeMetaEnum);
    *(char *)((char *)(((void *)igMetaObject_GetFieldAt((igMetaObject *)meta, first + 3))) + 38) = 0;
    igMetaObject_NameFields((igMetaObject *)meta, g_igDirEntry_fieldTable, g_igDirEntry_fieldDescriptors, g_igDirEntry_fieldOffsets, first);
}

