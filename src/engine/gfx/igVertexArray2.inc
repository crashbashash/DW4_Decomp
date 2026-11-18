igMetaObject *g_igVertexArray2_metaObject;
igMetaField *g_igVertexArray2_objListMetaField;
igMetaField *g_igVertexArray2_vertexStreamMetaField;
igMetaField *g_igVertexArray2_internalBufferMetaField;

int igVertexArray2_Create(int arg0) {
    igVertexArray2_EnsureRegistered();
    return (int)igMetaObject_CreateInstance(g_igVertexArray2_metaObject, (igMemoryPoolView *)arg0);
}

igMetaObject *igVertexArray2_GetOrCreateMetaObject(void) {
    if (g_igVertexArray2_metaObject == 0) {
        g_igVertexArray2_metaObject = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData));
    }
    return g_igVertexArray2_metaObject;
}

igMetaObject *igVertexArray2_GetMetaObject(void)
{
    igMetaObject *g = g_igVertexArray2_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false)
        igVertexArray2_EnsureRegistered();
    return g_igVertexArray2_metaObject;
}

int igVertexArray2_GetVTable(void) {
    struct Obj_14a860 obj;
    int r;

    igObject_InitHeader((igObject *)&obj);
    obj.w[1] = 0;
    obj.vt = &g_igVertexArray2_vtable[0];
    obj.w[2] = 0;
    obj.w[3] = 0;
    obj.w[4] = 0;
    r = *(int *)((char *)&obj + g_objectSystem->vtableProbeOffset);
    obj.vt = &g_igVertexArray2_vtable[0];
    FUN_0014aaf0((ObjectRefWord *)&obj.w[4], -1);
    igSmartPointer_igObjectList_Destruct((igSmartPointer<igObject> *)&obj.w[3], -1);
    igSmartPointer_igObject_Destruct((igSmartPointer<igObject> *)&obj.w[2], -1);
    igNamedObject_Destroy((igNamedObject *)&obj, 0);
    return r;
}

Obj_14a910 *FUN_0014a910(Obj_14a910 *arg0, short arg1) {
    if (arg0) {
        arg0->vt = &g_igVertexArray2_vtable[0];
        arg0->rel(&arg0->m20);
        arg0->rel(&arg0->m16);
        arg0->rel(&arg0->m12);
        if (arg0) {
            arg0->vt = &g_igNamedObject_vtable[0];
            arg0->relS(&arg0->m8);
        }
        if (arg1 > 0) {
            Memory_FreeBufferAliasC(arg0);
        }
    }
    return arg0;
}

igSmartPointer<igObject> *igSmartPointer_igObjectList_Destruct(igSmartPointer<igObject> *self, short deleteFlag) {
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

ObjectRefWord *FUN_0014aaf0(ObjectRefWord *self,int delete_storage) {
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

void igVertexArray2_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(igVertexArray2_Register);
}

static igMetaObjectCallback g_igVertexArray2_callbackList[] = { igObjectList_EnsureRegistered, igVertexStream_EnsureRegistered, igObject_EnsureRegistered, 0 };

CallbackArray *igVertexArray2_Register(void) {
    FUN_00149bc0();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_igVertexArray2_metaObject,
        igNamedObject_Register,
        igNamedObject_GetPublishedMetaObject,
        igVertexArray2_GetMetaObjectFunction,
        "igVertexArray2",
        0x18, /* instance size */
        igVertexArray2_GetVTable,
        &igVertexArray2_InitFields,
        0, /* extra callback item */
        g_igVertexArray2_callbackList /* callback list */
    );
}

void igVertexArray2_GetMetaObjectFunction(void) {
    igVertexArray2_GetMetaObject();
}

static FieldFactory g_igVertexArray2_ctorTable[] = {
    (FieldFactory)igObjectRefMetaField_Create,
    (FieldFactory)igObjectRefMetaField_Create,
    (FieldFactory)igObjectRefMetaField_Create,
};
static const char *g_igVertexArray2_fieldTable[] = {
    "_objList",
    "_vertexStream",
    "_internalBuffer",
};
static igMetaField **g_igVertexArray2_fieldHandles[] = {
    &g_igVertexArray2_objListMetaField,
    &g_igVertexArray2_vertexStreamMetaField,
    &g_igVertexArray2_internalBufferMetaField,
};
static int g_igVertexArray2_fieldOffsets[] = {
    16,
    20,
    12,
};

void igVertexArray2_InitFields(void) {
    int fieldStart;
    void *temp_v0;
    void *temp_s1_2;
    void *temp_s1;
    igMetaObject *meta;

    meta = g_igVertexArray2_metaObject;
    fieldStart = igMetaObject_GetFieldCount(meta);
    igMetaObject_CreateFields(meta, g_igVertexArray2_ctorTable, 3);
    temp_s1 = (void *)(igMetaObject_GetFieldAt(meta, fieldStart));
    ((igObjectRefMetaField *)temp_s1)->_metaObject = igObjectList_GetOrCreateMetaObject();
    ((igRefMetaField *)temp_s1)->_construct = 1;
    temp_s1_2 = (void *)(igMetaObject_GetFieldAt(meta, fieldStart + 1));
    ((igObjectRefMetaField *)temp_s1_2)->_metaObject = (int)igVertexStream_GetOrCreateMetaObject();
    temp_v0 = (void *)(igMetaObject_GetFieldAt(meta, fieldStart + 2));
    ((igObjectRefMetaField *)temp_v0)->_metaObject = (int)g_igObject_metaObject;
    ((igMetaField *)temp_v0)->_persistent = 0;
    igMetaObject_NameFields(meta, g_igVertexArray2_fieldTable, g_igVertexArray2_fieldHandles, g_igVertexArray2_fieldOffsets, fieldStart);
    *(int *)((char *)(g_igVertexArray2_metaObject) + 60) = (int)(igPsx2VertexArray2_GetMetaObjectFunction);
}

void igPsx2VertexArray2_GetMetaObjectFunction(void) {
    igPsx2VertexArray2_GetMetaObject();
}

