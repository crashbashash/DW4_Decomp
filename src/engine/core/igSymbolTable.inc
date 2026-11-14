void * igSymbolTable_Create(int allocator) {
    igSymbolTable_EnsureRegistered();
    return (void *)(igMetaObject_CreateInstance((igMetaObject *)(*(int *)0x585830), (igMemoryPoolView *)allocator));
}

igMetaObject *igSymbolTable_GetMetaObject(void)
{
    igMetaObject *g = g_igSymbolTable_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        igSymbolTable_EnsureRegistered();
    return g_igSymbolTable_metaObject[0];
}

int igSymbolTable_GetVTable(void) {
    igSymbolTable table;

    int vtable;

    igObject_InitHeader((igObject *)&table);
    table._vtable = (int)(&g_igSymbolTable_vtable[0]);
    table._symbols = 0;
    table._hashIndex = 0;
    table._symbolNames = 0;
    table._sourceFileNames = 0;
    vtable = *(int *)((char *)&table + *(int *)((char *)(((void * *)g_objectSystem)[0]) + 916));
    table._vtable = (int)(&g_igSymbolTable_vtable[0]);
    igSmartPointer_igStringTable_Destruct((igSmartPointer<igObject> *)&table._sourceFileNames, -1);
    igSmartPointer_igStringTable_Destruct((igSmartPointer<igObject> *)&table._symbolNames, -1);
    igSmartPointer_igIntListNoClean_Destruct((void **)&table._hashIndex, -1);
    igSmartPointer_igUnsignedIntListNoClean_Destruct((igSmartPointer<igObject> *)&table._symbols, -1);
    return vtable;
}

igSmartPointer<igObject> *igSmartPointer_igUnsignedIntListNoClean_Destruct(igSmartPointer<igObject> *self,int delete_storage) {
    if(self) {
        igObject *object=self->p;
        if(object) {
            --object->_refCount;
            if(((unsigned long long)(long long)(int)object->_refCount & 0x7fffffULL)==0)
                igObject_Destroy((void *)object);
        }
        if((short)delete_storage>0) __dl__FPv(self);
    }
    return self;
}

void **igSmartPointer_igIntListNoClean_Destruct(void **pointer, short deleteFlags) {
    int *object;
    if (pointer != 0) {
        object = (int *)*pointer;
        if (object != 0) {
            object[1] = object[1] - 1;
            if ((object[1] & 0x7fffff) == 0) {
                igObject_Destroy(object);
            }
        }
        if (deleteFlags > 0) {
            __dl__FPv(pointer);
        }
    }
    return pointer;
}

igSmartPointer<igObject> *igSmartPointer_igStringTable_Destruct(igSmartPointer<igObject> *self,int delete_storage) {
    if(self) {
        igObject *object=self->p;
        if(object) {
            --object->_refCount;
            if(((unsigned long long)(long long)(int)object->_refCount & 0x7fffffULL)==0)
                igObject_Destroy((void *)object);
        }
        if((short)delete_storage>0) __dl__FPv(self);
    }
    return self;
}

void igSymbolTable_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit((StaticInitCallbacks * (*)())igSymbolTable_Register);
}

void igSymbolTable_Register(void) {
    CoreLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0,
        g_igSymbolTable_metaObject,
        (igMetaObjectRegisterFunction)igObject_Register,
        (igMetaObjectGetFunction)igObject_GetMetaObject_ParentAccessor,
        igSymbolTable_GetMetaObjectFunction,
        igSymbolTable_className,
        0x2C,
        igSymbolTable_GetVTable,
        igSymbolTable_InitFields,
        0,
        (igMetaObjectCallback *)g_igSymbolTable_callbackList
    );
}

void igSymbolTable_GetMetaObjectFunction(void) {
    igSymbolTable_GetMetaObject();
}

void igSymbolTable_InitFields(void) {
    int base;
    void *symbolsField;
    void *hashIndexField;
    void *symbolNamesField;
    void *sourceFileNamesField;
    void *meta;

    meta = (void *)g_igSymbolTable_metaObject[0];
    base = igMetaObject_GetFieldCount((igMetaObject *)meta);
    igMetaObject_CreateFields((igMetaObject *)meta, (igMetaField * (**)(void *))&g_igSymbolTable_ctorTable[0], 9);
    igUnsignedIntMetaField_SetDefaultValue((void **)(((void *)igMetaObject_GetFieldAt((igMetaObject *)meta, base + 3))), -1);
    igUnsignedIntMetaField_SetDefaultValue((void **)(((void *)igMetaObject_GetFieldAt((igMetaObject *)meta, base + 4))), 1);
    symbolsField = (void *)(((void *)igMetaObject_GetFieldAt((igMetaObject *)meta, base + 5)));
    ((igObjectRefMetaField *)symbolsField)->_metaObject = (int)igUnsignedIntListNoClean_GetOrCreateMetaObject();
    ((igRefMetaField *)symbolsField)->_construct = 1;
    hashIndexField = (void *)(((void *)igMetaObject_GetFieldAt((igMetaObject *)meta, base + 6)));
    ((igObjectRefMetaField *)hashIndexField)->_metaObject = (int)igIntListNoClean_GetOrCreateMetaObject();
    ((igRefMetaField *)hashIndexField)->_construct = 1;
    symbolNamesField = (void *)(((void *)igMetaObject_GetFieldAt((igMetaObject *)meta, base + 7)));
    ((igObjectRefMetaField *)symbolNamesField)->_metaObject = (int)igStringTable_GetOrCreateMetaObject();
    ((igRefMetaField *)symbolNamesField)->_construct = 1;
    sourceFileNamesField = (void *)(((void *)igMetaObject_GetFieldAt((igMetaObject *)meta, base + 8)));
    ((igObjectRefMetaField *)sourceFileNamesField)->_metaObject = (int)igStringTable_GetOrCreateMetaObject();
    ((igRefMetaField *)sourceFileNamesField)->_construct = 1;
    igMetaObject_NameFields((igMetaObject *)meta, (const char **)&g_igSymbolTable_fieldTable[0], (igMetaField ***)&g_igSymbolTable_fieldDescriptors[0], &g_igSymbolTable_fieldOffsets[0], base);
}

