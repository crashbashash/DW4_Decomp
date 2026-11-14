void *igStringTable_Create(int pool) {
    igStringTable_EnsureRegistered();
    return (void *)igMetaObject_CreateInstance((igMetaObject *)(*(int *)0x5858B0), (igMemoryPoolView *)pool);
}

igMetaObject *igStringTable_GetOrCreateMetaObject(void) {
    if (g_igStringTable_metaObject[0] == 0) {
        g_igStringTable_metaObject[0] = (igMetaObject *)igMetaObject_Create(((int)Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData)));
    }
    return g_igStringTable_metaObject[0];
}

igMetaObject *igStringTable_GetMetaObject(void)
{
    igMetaObject *g = g_igStringTable_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        igStringTable_EnsureRegistered();
    return g_igStringTable_metaObject[0];
}

int igStringTable_GetVTable(void) {
    igStringTable table;
    int r;
    int *strings;
    int *hashIndex;

    igObject_InitHeader((igObject *)&table);
    table._vtable = (int)&g_igStringTable_vtable[0];
    strings = &table._strings;
    *strings = 0;
    hashIndex = &table._hashIndex;
    *hashIndex = 0;
    r = *(int *)((char *)&table + *(int *)((char *)(((void * *)g_objectSystem)[0]) + 916));
    table._vtable = (int)&g_igStringTable_vtable[0];
    ReleaseObjectField(hashIndex);
    ReleaseObjectField(strings);
    return r;
}

igObject **igSmartPointer_igCharListNoClean_Destruct(igObject **self, short flags) {
    igObject *object;

    if (self != 0) {
        object = *self;
        if (object != 0) {
            object->_refCount = object->_refCount - 1;
            if ((object->_refCount & 0x7FFFFF) == 0) {
                igObject_Destroy(object);
            }
        }
        if (flags > 0) {
            __dl__FPv(self);
        }
    }
    return self;
}

void igStringTable_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit((StaticInitCallbacks * (*)())igStringTable_Register);
}

void igStringTable_Register(void) {
    CoreLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0,
        g_igStringTable_metaObject,
        (igMetaObjectRegisterFunction)igObject_Register,
        (igMetaObjectGetFunction)igObject_GetMetaObject_ParentAccessor,
        igStringTable_GetMetaObjectFunction,
        igStringTable_className,
        0x18,
        igStringTable_GetVTable,
        igStringTable_InitFields,
        0,
        (igMetaObjectCallback *)g_igStringTable_callbackList
    );
}

void igStringTable_GetMetaObjectFunction(void) {
    igStringTable_GetMetaObject();
}

void igStringTable_InitFields(void) {
    int base;
    void *field2;
    void *field;
    void *meta;

    meta = (void *)g_igStringTable_metaObject[0];
    base = igMetaObject_GetFieldCount((igMetaObject *)meta);
    igMetaObject_CreateFields((igMetaObject *)meta, (igMetaField * (**)(void *))&g_igStringTable_ctorTable[0], 4);
    field = (void *)(((void *)igMetaObject_GetFieldAt((igMetaObject *)meta, base + 2)));
    ((igObjectRefMetaField *)field)->_metaObject = (int)igCharListNoClean_GetOrCreateMetaObject();
    ((igRefMetaField *)field)->_construct = 1;
    field2 = (void *)(((void *)igMetaObject_GetFieldAt((igMetaObject *)meta, base + 3)));
    ((igObjectRefMetaField *)field2)->_metaObject = (int)igIntListNoClean_GetOrCreateMetaObject();
    igMetaObject_NameFields((igMetaObject *)meta, (const char **)&g_igStringTable_fieldTable[0], (igMetaField ***)&g_igStringTable_fieldDescriptors[0], &g_igStringTable_fieldOffsets[0], base);
}

