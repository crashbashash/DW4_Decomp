igMetaObject *g_igNamedObjectInfo_metaObject;
igMetaField *g_igNamedObjectInfo_objectsMetaField;

igMetaObject *igNamedObjectInfo_GetMetaObject(void)
{
    igMetaObject *g = g_igNamedObjectInfo_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false)
        igNamedObjectInfo_EnsureRegistered();
    return g_igNamedObjectInfo_metaObject;
}

int igNamedObjectInfo_GetVTable(void) {
    igNamedObjectInfo info;
    int vtable;
    igObject *q0;
    int *q1;
    int *text;
    int *header;
    int refCount;

    igObject_InitHeader((igObject *)&info);
    q1 = &info._name;
    *(int *)q1 = 0;
    info._vtable = (int)&g_igNamedObjectInfo_vtable[0];
    q0 = (igObject *)&info._objects;
    *(int *)q0 = 0;
    vtable = *(int *)((char *)&info + *(int *)((char *)((*(void * *)&g_objectSystem)) + 916));
    info._vtable = (int)&g_igNamedObjectInfo_vtable[0];
    if (q0 != 0) {
        q0 = *(igObject **)q0;
        if (q0 != 0) {
            q0->_refCount = (int)((int) (q0->_refCount - 1));
            if (((unsigned long long) ((long long)(int) q0->_refCount << 0x29) >> 0x29) == 0) {
                igObject_Destroy(q0);
            }
        }
    }
    info._vtable = (int)&g_igNamedObject_vtable[0];
    if (q1 != 0) {
        text = *(int **)q1;
        if (text != 0) {
            header = text - 2;
            refCount = text[-1] - 1;
            text[-1] = refCount;
            if (refCount == 0) {
                StringChunk_ReleaseHeader((StringChunk *)(*header), (int)header);
            }
        }
    }
    return vtable;
}

void igNamedObjectInfo_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit((StaticInitCallbacks * (*)())igNamedObjectInfo_Register);
}

static igMetaObjectCallback g_igNamedObjectInfo_callbackList[] = { igNamedObjectList_EnsureRegistered, 0 };

void igNamedObjectInfo_Register(void) {
    CoreLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0,
        &g_igNamedObjectInfo_metaObject,
        (igMetaObjectRegisterFunction)igInfo_Register,
        (igMetaObjectGetFunction)igInfo_GetPublishedMetaObject,
        igNamedObjectInfo_GetMetaObjectFunction,
        "igNamedObjectInfo",
        0x18,
        igNamedObjectInfo_GetVTable,
        igNamedObjectInfo_InitFields,
        0,
        g_igNamedObjectInfo_callbackList
    );
}

void igNamedObjectInfo_GetMetaObjectFunction(void) {
    igNamedObjectInfo_GetMetaObject();
}

static FieldFactory g_igNamedObjectInfo_ctorTable[] = {
    (FieldFactory)igObjectRefMetaField_Create,
};
static const char *g_igNamedObjectInfo_fieldTable[] = {
    "_objects",
};
static igMetaField **g_igNamedObjectInfo_fieldDescriptors[] = {
    &g_igNamedObjectInfo_objectsMetaField,
};
static int g_igNamedObjectInfo_fieldOffsets[] = {
    20,
};

void igNamedObjectInfo_InitFields(void) {
    int base;
    void *field;
    void *meta;

    meta = (void *)g_igNamedObjectInfo_metaObject;
    base = igMetaObject_GetFieldCount((igMetaObject *)meta);
    igMetaObject_CreateFields((igMetaObject *)meta, g_igNamedObjectInfo_ctorTable, 1);
    field = (void *)(((void *)igMetaObject_GetFieldAt((igMetaObject *)meta, base)));
    ((igObjectRefMetaField *)field)->_metaObject = (int)igNamedObjectList_GetOrCreateMetaObject();
    ((igRefMetaField *)field)->_construct = 1;
    igMetaObject_NameFields((igMetaObject *)meta, g_igNamedObjectInfo_fieldTable, g_igNamedObjectInfo_fieldDescriptors, g_igNamedObjectInfo_fieldOffsets, base);
}

