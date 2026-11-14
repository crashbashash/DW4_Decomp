void * igMemoryDictionary_Create(int pool) {
    igMemoryDictionary_EnsureRegistered();
    return (void *)(igMetaObject_CreateInstance((igMetaObject *)(*(int *)0x585FA0), (igMemoryPoolView *)pool));
}

igMetaObject *igMemoryDictionary_GetMetaObject(void)
{
    igMetaObject *g = g_igMemoryDictionary_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        igMemoryDictionary_EnsureRegistered();
    return g_igMemoryDictionary_metaObject[0];
}

int igMemoryDictionary_GetVTable(void) {
    igMemoryDictionary dictionary;
    int **pr;
    int vtable;
    int *o;

    igObject_InitHeader((igObject *)&dictionary);
    dictionary._vtable = (int)&g_igMemoryDictionary_vtable[0];
    pr = (int **)&dictionary._memoryEntries;
    *pr = 0;
    vtable = *(int *)((char *)&dictionary + *(int *)((char *)(((void * *)g_objectSystem)[0]) + 916));
    dictionary._vtable = (int)&g_igMemoryDictionary_vtable[0];
    if (pr != 0) {
        if (*pr != 0) {
            o = *pr;
            o[1] = o[1] - 1;
            if ((o[1] & 0x7FFFFF) == 0) {
                igObject_Destroy(o);
            }
        }
    }
    return vtable;
}

void igMemoryDictionary_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit((StaticInitCallbacks * (*)())igMemoryDictionary_Register);
}

void igMemoryDictionary_Register(void) {
    CoreLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0,
        g_igMemoryDictionary_metaObject,
        (igMetaObjectRegisterFunction)igObject_Register,
        (igMetaObjectGetFunction)igObject_GetMetaObject_ParentAccessor,
        igMemoryDictionary_GetMetaObjectFunction,
        igMemoryDictionary_className,
        0x18,
        igMemoryDictionary_GetVTable,
        igMemoryDictionary_InitFields,
        0,
        (igMetaObjectCallback *)g_igMemoryDictionary_callbackList
    );
}

void igMemoryDictionary_GetMetaObjectFunction(void) {
    igMemoryDictionary_GetMetaObject();
}

void igMemoryDictionary_InitFields(void) {
    int base;
    void *field;
    void *meta;

    meta = (void *)g_igMemoryDictionary_metaObject[0];
    base = igMetaObject_GetFieldCount((igMetaObject *)meta);
    igMetaObject_CreateFields((igMetaObject *)meta, (igMetaField * (**)(void *))&g_igMemoryDictionary_ctorTable[0], 4);
    field = (void *)(((void *)igMetaObject_GetFieldAt((igMetaObject *)meta, base + 2)));
    ((igObjectRefMetaField *)field)->_metaObject = (int)igUnsignedIntListNoClean_GetOrCreateMetaObject();
    ((igObjectRefMetaField *)field)->_construct = 1;
    *(char *)((char *)(((void *)igMetaObject_GetFieldAt((igMetaObject *)meta, base + 3))) + 38) = 0;
    igMetaObject_NameFields((igMetaObject *)meta, (const char **)&g_igMemoryDictionary_fieldTable[0], (igMetaField ***)&g_igMemoryDictionary_fieldDescriptors[0], &g_igMemoryDictionary_fieldOffsets[0], base);
}

