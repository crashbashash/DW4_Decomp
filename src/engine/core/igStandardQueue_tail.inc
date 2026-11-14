igMetaObject *igStandardQueue_GetMetaObject(void)
{
    igMetaObject *g = g_igStandardQueue_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        igStandardQueue_EnsureRegistered();
    return g_igStandardQueue_metaObject[0];
}

int igStandardQueue_GetVTable(void) {
    igStandardQueue queue;
    int vtable;
    int *p2;
    int *p1;
    igObject_InitHeader((igObject *)&queue);
    queue._serviceThreads = 0;
    queue._vtable = (int)&g_igStandardQueue_vtable[0];
    p1 = &queue._insertLock;
    *p1 = 0;
    p2 = &queue._removeLock;
    *p2 = 0;
    queue._queueSema = 0;
    vtable = *(int *)((char *)&queue + *(int *)((char *)(((void * *)g_objectSystem)[0]) + 916));
    queue._vtable = (int)&g_igStandardQueue_vtable[0];
    igSmartPointer_igSemaphore_Destruct((igObject **)&queue._queueSema, -1);
    igSmartPointer_igSemaphore_Destruct((igObject **)p2, -1);
    igSmartPointer_igSemaphore_Destruct((igObject **)p1, -1);
    igQueue_Destroy((igQueue *)&queue, 0);
    return vtable;
}

void *igQueue_Destroy(igQueue *self, short flags) {
    igObject *p;
    int rc;

    if (self != 0) {
        self->_vtable = (int)&g_igQueue_vtable[0];
        if (&self->_serviceThreads) {
            p = (igObject *)self->_serviceThreads;
            if (p != 0) {
                rc = (int)p->_refCount - 1;
                p->_refCount = rc;
                if (((unsigned long long) ((long long)(int)p->_refCount << 0x29) >> 0x29) == 0) {
                    igObject_Destroy(p);
                }
            }
        }
        if (flags > 0) {
            thunk_Memory_FreeBuffer((int)self);
        }
    }
    return self;
}

void igStandardQueue_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit((StaticInitCallbacks * (*)())igStandardQueue_Register);
}

void igStandardQueue_Register(void) {
    CoreLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0,
        g_igStandardQueue_metaObject,
        (igMetaObjectRegisterFunction)igQueue_Register,
        igQueue_GetPublishedMetaObject,
        igStandardQueue_GetMetaObjectFunction,
        igStandardQueue_className,
        0x2C,
        igStandardQueue_GetVTable,
        igStandardQueue_InitFields,
        0,
        (igMetaObjectCallback *)g_igStandardQueue_callbackList
    );
}

igMetaObject *igQueue_GetPublishedMetaObject(void) {
    return g_igQueue_metaObject[0];
}

void igStandardQueue_InitFields(void) {
    int base;
    void *insertLock;
    void *removeLock;
    void *queueSema;
    void *data;
    void *meta;

    meta = (void *)(g_igStandardQueue_metaObject[0]);
    base = igMetaObject_GetFieldCount((igMetaObject *)meta);
    igMetaObject_CreateFields((igMetaObject *)meta, (igMetaField * (**)(void *))&g_igStandardQueue_ctorTable[0], 8);
    insertLock = (void *)(((void *)igMetaObject_GetFieldAt((igMetaObject *)meta, base)));
    ((igObjectRefMetaField *)insertLock)->_metaObject = (int)igSemaphore_GetOrCreateMetaObject();
    ((igObjectRefMetaField *)insertLock)->_construct = 1;
    removeLock = (void *)(((void *)igMetaObject_GetFieldAt((igMetaObject *)meta, base + 1)));
    ((igObjectRefMetaField *)removeLock)->_metaObject = (int)igSemaphore_GetOrCreateMetaObject();
    ((igObjectRefMetaField *)removeLock)->_construct = 1;
    queueSema = (void *)(((void *)igMetaObject_GetFieldAt((igMetaObject *)meta, base + 2)));
    ((igObjectRefMetaField *)queueSema)->_metaObject = (int)igSemaphore_GetOrCreateMetaObject();
    ((igObjectRefMetaField *)queueSema)->_construct = 1;
    igUnsignedIntMetaField_SetDefaultValue((void **)(((void *)igMetaObject_GetFieldAt((igMetaObject *)meta, base + 3))), 4);
    data = (void *)(((void *)igMetaObject_GetFieldAt((igMetaObject *)meta, base + 6)));
    ((igMemoryRefMetaField *)data)->_memType = igRawRefMetaField_GetDefaultDescriptor();
    ((igMemoryRefMetaField *)data)->_destruct = 1;
    ((igMemoryRefMetaField *)data)->_releaseOnCopy = 1;
    ((igMemoryRefMetaField *)data)->_releaseOnReset = 1;
    igUnsignedIntMetaField_SetDefaultValue((void **)(((void *)igMetaObject_GetFieldAt((igMetaObject *)meta, base + 7))), 0x2000);
    igMetaObject_NameFields((igMetaObject *)meta, (const char **)&g_igStandardQueue_fieldTable[0], (igMetaField ***)&g_igStandardQueue_fieldDescriptors[0], &g_igStandardQueue_fieldOffsets[0], base);
    ((igMetaObject *)g_igStandardQueue_metaObject[0])->_writeProxy = (int)igQueue_GetMetaObjectFunction;
}

