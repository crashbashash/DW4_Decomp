igMetaObject *g_igObjectStringMap_metaObject;
igMetaField *g_igObjectStringMap_namesMetaField;
igMetaField *g_igObjectStringMap_dataMetaField;

igMetaObject *igObjectStringMap_GetOrCreateMetaObject(void) {
    if (g_igObjectStringMap_metaObject == 0) {
        g_igObjectStringMap_metaObject = (igMetaObject *)igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData));
    }
    return g_igObjectStringMap_metaObject;
}

igMetaObject *igObjectStringMap_GetMetaObject(void)
{
    igMetaObject *g = g_igObjectStringMap_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false)
        igObjectStringMap_EnsureRegistered();
    return g_igObjectStringMap_metaObject;
}

int igObjectStringMap_GetVTable(void) {
    igObjectStringMap map;
    int vtable;
    igObject *object;
    int *text;
    int *header;
    int count;
    int *namesSlot;
    int *dataSlot;
    igObject_InitHeader((igObject *)&map);
    map._vtable = (int)&g_igObjectStringMap_vtable[0];
    namesSlot = &map._names;
    *namesSlot = 0;
    dataSlot = &map._data;
    *dataSlot = 0;
    vtable = *(int *)((char *)&map + g_objectSystem->vtableProbeOffset);
    map._vtable = (int)&g_igObjectStringMap_vtable[0];
    if (dataSlot != 0) {
        object = (igObject *)*dataSlot;
        if (object != 0) {
            object->_refCount = object->_refCount - 1;
            if ((object->_refCount & 0x7FFFFF) == 0) {
                igObject_Destroy(object);
            }
        }
    }
    if (namesSlot != 0) {
        object = (igObject *)*namesSlot;
        if (object != 0) {
            object->_refCount = object->_refCount - 1;
            if ((object->_refCount & 0x7FFFFF) == 0) {
                igObject_Destroy(object);
            }
        }
    }
    return vtable;
}

void igObjectStringMap_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(igObjectStringMap_Register);
}

static igMetaObjectCallback g_igObjectStringMap_callbackList[] = { igNamedObjectList_EnsureRegistered, Gap::Core::igObjectList::arkRegister, 0 };

CallbackArray *igObjectStringMap_Register(void) {
    CoreLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0,
        &g_igObjectStringMap_metaObject,
        Gap::Core::igObject::arkRegisterInternal,
        igObject_GetMetaObject_ParentAccessor,
        igObjectStringMap_GetMetaObjectFunction,
        "igObjectStringMap",
        0x10,
        igObjectStringMap_GetVTable,
        igObjectStringMap_InitFields,
        0,
        g_igObjectStringMap_callbackList
    );
}

void igObjectStringMap_GetMetaObjectFunction(void) {
    igObjectStringMap_GetMetaObject();
}

static FieldFactory g_igObjectStringMap_ctorTable[] = {
    (FieldFactory)igObjectRefMetaField_Create,
    (FieldFactory)igObjectRefMetaField_Create,
};
static const char *g_igObjectStringMap_fieldTable[] = {
    "_names",
    "_data",
};
static igMetaField **g_igObjectStringMap_fieldDescriptors[] = {
    &g_igObjectStringMap_namesMetaField,
    &g_igObjectStringMap_dataMetaField,
};
static int g_igObjectStringMap_fieldOffsets[] = {
    8,
    12,
};

void igObjectStringMap_InitFields(void) {
    int base;
    void *dataField;
    void *namesField;
    void *meta;

    meta = (void *)g_igObjectStringMap_metaObject;
    base = igMetaObject_GetFieldCount((igMetaObject *)meta);
    igMetaObject_CreateFields((igMetaObject *)meta, g_igObjectStringMap_ctorTable, 2);
    namesField = (void *)(((void *)igMetaObject_GetFieldAt((igMetaObject *)meta, base)));
    ((igObjectRefMetaField *)namesField)->_metaObject = (int)igNamedObjectList_GetOrCreateMetaObject();
    ((igRefMetaField *)namesField)->_construct = 1;
    dataField = (void *)(((void *)igMetaObject_GetFieldAt((igMetaObject *)meta, base + 1)));
    ((igObjectRefMetaField *)dataField)->_metaObject = (int)Gap::Core::igObjectList::getClassTypeLazy();
    ((igRefMetaField *)dataField)->_construct = 1;
    igMetaObject_NameFields((igMetaObject *)meta, g_igObjectStringMap_fieldTable, g_igObjectStringMap_fieldDescriptors, g_igObjectStringMap_fieldOffsets, base);
}

