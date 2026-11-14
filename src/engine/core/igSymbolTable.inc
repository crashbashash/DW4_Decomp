void * igSymbolTable_Create(int arg0) {
    igSymbolTable_EnsureRegistered();
    return (void *)(igMetaObject_CreateInstance((igMetaObject *)(*(int *)0x585830), (igMemoryPoolView *)arg0));
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

    int temp_s3;

    igObject_InitHeader((igObject *)&table);
    table._vtable = (int)(&DAT_0052e730[0]);
    table._symbols = 0;
    table._hashIndex = 0;
    table._symbolNames = 0;
    table._sourceFileNames = 0;
    temp_s3 = *(int *)((char *)&table + *(int *)((char *)(((void * *)g_objectSystem)[0]) + 916));
    table._vtable = (int)(&DAT_0052e730[0]);
    igSmartPointer_igStringTable_Destruct((igSmartPointer<igObject> *)&table._sourceFileNames, -1);
    igSmartPointer_igStringTable_Destruct((igSmartPointer<igObject> *)&table._symbolNames, -1);
    igSmartPointer_igIntListNoClean_Destruct((void **)&table._hashIndex, -1);
    igSmartPointer_igUnsignedIntListNoClean_Destruct((igSmartPointer<igObject> *)&table._symbols, -1);
    return temp_s3;
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

void **igSmartPointer_igIntListNoClean_Destruct(void **arg0, short arg1) {
    int *r;
    if (arg0 != 0) {
        r = (int *)*arg0;
        if (r != 0) {
            r[1] = r[1] - 1;
            if ((r[1] & 0x7fffff) == 0) {
                igObject_Destroy(r);
            }
        }
        if (arg1 > 0) {
            __dl__FPv(arg0);
        }
    }
    return arg0;
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
        0, /* abstract */
        ((char *)g_igSymbolTable_metaObject),
        igObject_Register,
        igObject_GetMetaObject_ParentAccessor,
        igSymbolTable_GetMetaObjectFunction,
        igSymbolTable_className,
        0x2C, /* instance size */
        igSymbolTable_GetVTable,
        &igSymbolTable_InitFields,
        0, /* extra callback item */
        g_igSymbolTable_callbackList /* callback list */
    );
}

void igSymbolTable_GetMetaObjectFunction(void) {
    igSymbolTable_GetMetaObject();
}

void igSymbolTable_InitFields(void) {
    int temp_s0;
    void *temp_s2;
    void *temp_s2_2;
    void *temp_s2_3;
    void *temp_s2_4;
    void *temp_s1;

    temp_s1 = (void *)g_igSymbolTable_metaObject[0];
    temp_s0 = igMetaObject_GetFieldCount((igMetaObject *)temp_s1);
    igMetaObject_CreateFields((igMetaObject *)temp_s1, (igMetaField * (**)(void *))&g_igSymbolTable_ctorTable[0], 9);
    igUnsignedIntMetaField_SetDefaultValue((void **)(((void *)igMetaObject_GetFieldAt((igMetaObject *)temp_s1, temp_s0 + 3))), -1);
    igUnsignedIntMetaField_SetDefaultValue((void **)(((void *)igMetaObject_GetFieldAt((igMetaObject *)temp_s1, temp_s0 + 4))), 1);
    temp_s2 = (void *)(((void *)igMetaObject_GetFieldAt((igMetaObject *)temp_s1, temp_s0 + 5)));
    ((igObjectRefMetaField *)temp_s2)->_metaObject = (int)igUnsignedIntListNoClean_GetOrCreateMetaObject();
    ((igRefMetaField *)temp_s2)->_construct = 1;
    temp_s2_2 = (void *)(((void *)igMetaObject_GetFieldAt((igMetaObject *)temp_s1, temp_s0 + 6)));
    ((igObjectRefMetaField *)temp_s2_2)->_metaObject = (int)igIntListNoClean_GetOrCreateMetaObject();
    ((igRefMetaField *)temp_s2_2)->_construct = 1;
    temp_s2_3 = (void *)(((void *)igMetaObject_GetFieldAt((igMetaObject *)temp_s1, temp_s0 + 7)));
    ((igObjectRefMetaField *)temp_s2_3)->_metaObject = (int)igStringTable_GetOrCreateMetaObject();
    ((igRefMetaField *)temp_s2_3)->_construct = 1;
    temp_s2_4 = (void *)(((void *)igMetaObject_GetFieldAt((igMetaObject *)temp_s1, temp_s0 + 8)));
    ((igObjectRefMetaField *)temp_s2_4)->_metaObject = (int)igStringTable_GetOrCreateMetaObject();
    ((igRefMetaField *)temp_s2_4)->_construct = 1;
    igMetaObject_NameFields((igMetaObject *)temp_s1, (const char **)&g_igSymbolTable_fieldTable[0], (igMetaField ***)&DAT_004bf580[0], &DAT_004bf5b0[0], temp_s0);
}

