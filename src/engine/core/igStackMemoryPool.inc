void igStackMemoryPool_Create(int arg0) {
    igStackMemoryPool_EnsureRegistered();
    igMetaObject_CreateInstance((igMetaObject *)(*(int *)0x586B20), (igMemoryPoolView *)arg0);
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
    pool._vtable = (int)&DAT_0052de80[0];
    pool._eventTracker = 0;
    r = *(int *)((char *)&pool + *(int *)((char *)(((void * *)g_objectSystem)[0]) + 916));
    pool._vtable = (int)&DAT_0052de80[0];
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
        0, /* abstract */
        ((char *)g_igStackMemoryPool_metaObject),
        igMemoryPool_Register,
        igMemoryPool_GetPublishedMetaObject,
        igStackMemoryPool_GetMetaObjectFunction,
        igStackMemoryPool_className,
        0x98, /* instance size */
        igStackMemoryPool_GetVTable,
        &igStackMemoryPool_InitFields,
        0, /* extra callback item */
        g_igStackMemoryPool_callbackList /* callback list */
    );
}

void igStackMemoryPool_GetMetaObjectFunction(void) {
    igStackMemoryPool_GetMetaObject();
}

void igStackMemoryPool_InitFields(void) {
    int temp_s2;
    void *temp_s1;
    void *temp_s0;

    temp_s0 = (void *)g_igStackMemoryPool_metaObject[0];
    temp_s2 = igMetaObject_GetFieldCount((igMetaObject *)temp_s0);
    igMetaObject_CreateFields((igMetaObject *)temp_s0, (igMetaField * (**)(void *))&g_igStackMemoryPool_ctorTable[0], 0xA);
    igIntMetaField_SetDefault((void **)(((void *)igMetaObject_GetFieldAt((igMetaObject *)temp_s0, temp_s2))), -1);
    igUnsignedShortMetaField_SetDefaultValue((void **)(((void *)igMetaObject_GetFieldAt((igMetaObject *)temp_s0, temp_s2 + 1))), 4);
    temp_s1 = (void *)(((void *)igMetaObject_GetFieldAt((igMetaObject *)temp_s0, temp_s2 + 9)));
    ((igObjectRefMetaField *)temp_s1)->_metaObject = (int)igEventTracker_GetOrCreateMetaObject();
    igMetaObject_NameFields((igMetaObject *)temp_s0, (const char **)&g_igStackMemoryPool_fieldTable[0], (igMetaField ***)&DAT_004c19b0[0], &DAT_004c19e0[0], temp_s2);
}

