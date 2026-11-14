void igStackMemoryPool_Create(int pool) {
    igStackMemoryPool_EnsureRegistered();
    igMetaObject_CreateInstance((igMetaObject *)(*(int *)0x586B20), (igMemoryPoolView *)pool);
}

igMetaObject *igStackMemoryPool_GetMetaObject(void)
{
    igMetaObject *g = g_igStackMemoryPool_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        igStackMemoryPool_EnsureRegistered();
    return g_igStackMemoryPool_metaObject[0];
}

int igStackMemoryPool_GetVTable(void) {
    igStackMemoryPool pool;
    int r;
    igObject **tracker;
    igObject *object;

    igMemoryPool_Initialize((int **)&pool);
    pool._vtable = (int)&g_igStackMemoryPool_vtable[0];
    pool._eventTracker = 0;
    r = *(int *)((char *)&pool + *(int *)((char *)(((void * *)g_objectSystem)[0]) + 916));
    pool._vtable = (int)&g_igStackMemoryPool_vtable[0];
    tracker = (igObject **)&pool._eventTracker;
    if (tracker) {
        object = *tracker;
        if (object) {
            --*(int *)&object->_refCount;
            if (((unsigned long long)(long long)*(int *)&object->_refCount & 0x7fffffULL) == 0)
                igObject_Destroy((void *)object);
        }
    }
    return r;
}

void igStackMemoryPool_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit((StaticInitCallbacks * (*)())igStackMemoryPool_Register);
}

void igStackMemoryPool_Register(void) {
    CoreLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0,
        g_igStackMemoryPool_metaObject,
        (igMetaObjectRegisterFunction)igMemoryPool_Register,
        igMemoryPool_GetPublishedMetaObject,
        igStackMemoryPool_GetMetaObjectFunction,
        igStackMemoryPool_className,
        0x98,
        igStackMemoryPool_GetVTable,
        igStackMemoryPool_InitFields,
        0,
        (igMetaObjectCallback *)g_igStackMemoryPool_callbackList
    );
}

void igStackMemoryPool_GetMetaObjectFunction(void) {
    igStackMemoryPool_GetMetaObject();
}

void igStackMemoryPool_InitFields(void) {
    int base;
    void *field;
    void *meta;

    meta = (void *)g_igStackMemoryPool_metaObject[0];
    base = igMetaObject_GetFieldCount((igMetaObject *)meta);
    igMetaObject_CreateFields((igMetaObject *)meta, (igMetaField * (**)(void *))&g_igStackMemoryPool_ctorTable[0], 0xA);
    igIntMetaField_SetDefault((void **)(((void *)igMetaObject_GetFieldAt((igMetaObject *)meta, base))), -1);
    igUnsignedShortMetaField_SetDefaultValue((void **)(((void *)igMetaObject_GetFieldAt((igMetaObject *)meta, base + 1))), 4);
    field = (void *)(((void *)igMetaObject_GetFieldAt((igMetaObject *)meta, base + 9)));
    ((igObjectRefMetaField *)field)->_metaObject = (int)igEventTracker_GetOrCreateMetaObject();
    igMetaObject_NameFields((igMetaObject *)meta, (const char **)&g_igStackMemoryPool_fieldTable[0], (igMetaField ***)&g_igStackMemoryPool_fieldDescriptors[0], &g_igStackMemoryPool_fieldOffsets[0], base);
}

