igMetaObject *igObjectStringMap_GetOrCreateMetaObject(void) {
    if (g_igObjectStringMap_metaObject[0] == 0) {
        g_igObjectStringMap_metaObject[0] = (igMetaObject *)igMetaObject_Create(((int)Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData)));
    }
    return g_igObjectStringMap_metaObject[0];
}

igMetaObject *igObjectStringMap_GetMetaObject(void)
{
    igMetaObject *g = g_igObjectStringMap_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        igObjectStringMap_EnsureRegistered();
    return g_igObjectStringMap_metaObject[0];
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
    vtable = *(int *)((char *)&map + *(int *)((char *)(((void * *)g_objectSystem)[0]) + 916));
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
    igMetaObject_RunStaticInit((StaticInitCallbacks * (*)())igObjectStringMap_Register);
}

void igObjectStringMap_Register(void) {
    CoreLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0,
        g_igObjectStringMap_metaObject,
        (igMetaObjectRegisterFunction)igObject_Register,
        (igMetaObjectGetFunction)igObject_GetMetaObject_ParentAccessor,
        igObjectStringMap_GetMetaObjectFunction,
        igObjectStringMap_className,
        0x10,
        igObjectStringMap_GetVTable,
        igObjectStringMap_InitFields,
        0,
        (igMetaObjectCallback *)g_igObjectStringMap_callbackList
    );
}

void igObjectStringMap_GetMetaObjectFunction(void) {
    igObjectStringMap_GetMetaObject();
}

void igObjectStringMap_InitFields(void) {
    int base;
    void *dataField;
    void *namesField;
    void *meta;

    meta = (void *)g_igObjectStringMap_metaObject[0];
    base = igMetaObject_GetFieldCount((igMetaObject *)meta);
    igMetaObject_CreateFields((igMetaObject *)meta, (igMetaField * (**)(void *))&g_igObjectStringMap_ctorTable[0], 2);
    namesField = (void *)(((void *)igMetaObject_GetFieldAt((igMetaObject *)meta, base)));
    ((igObjectRefMetaField *)namesField)->_metaObject = (int)igNamedObjectList_GetOrCreateMetaObject();
    ((igRefMetaField *)namesField)->_construct = 1;
    dataField = (void *)(((void *)igMetaObject_GetFieldAt((igMetaObject *)meta, base + 1)));
    ((igObjectRefMetaField *)dataField)->_metaObject = igObjectList_GetOrCreateMetaObject();
    ((igRefMetaField *)dataField)->_construct = 1;
    igMetaObject_NameFields((igMetaObject *)meta, (const char **)&g_igObjectStringMap_fieldTable[0], (igMetaField ***)&g_igObjectStringMap_fieldDescriptors[0], &g_igObjectStringMap_fieldOffsets[0], base);
}

