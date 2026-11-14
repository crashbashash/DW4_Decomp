igMetaObject *igStandardQueue_GetMetaObject(void)
{
    igMetaObject *g = g_igStandardQueue_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        igStandardQueue_EnsureRegistered();
    return g_igStandardQueue_metaObject[0];
}

int igStandardQueue_GetVTable(void) {
    igStandardQueue queue;
    int temp_s2;
    int *p2;
    int *p1;
    igObject_InitHeader((igObject *)&queue);
    queue._serviceThreads = 0;
    queue._vtable = (int)&DAT_0052ddf0[0];
    p1 = &queue._insertLock;
    *p1 = 0;
    p2 = &queue._removeLock;
    *p2 = 0;
    queue._queueSema = 0;
    temp_s2 = *(int *)((char *)&queue + *(int *)((char *)(((void * *)g_objectSystem)[0]) + 916));
    queue._vtable = (int)&DAT_0052ddf0[0];
    igSmartPointer_igSemaphore_Destruct((igObject **)&queue._queueSema, -1);
    igSmartPointer_igSemaphore_Destruct((igObject **)p2, -1);
    igSmartPointer_igSemaphore_Destruct((igObject **)p1, -1);
    igQueue_Destroy((igQueue *)&queue, 0);
    return temp_s2;
}

void *igQueue_Destroy(igQueue *arg0, short arg1) {
    void *p;
    int rc;

    if (arg0 != 0) {
        arg0->_vtable = (int)&DAT_0052ee50[0];
        if (&arg0->_serviceThreads) {
            p = (void *)arg0->_serviceThreads;
            if (p != 0) {
                rc = *(int *)((char *)(p) + 4) - 1;
                *(int *)((char *)(p) + 4) = rc;
                if (((unsigned long long) ((long long) *(int *)((char *)(p) + 4) << 0x29) >> 0x29) == 0) {
                    igObject_Destroy(p);
                }
            }
        }
        if (arg1 > 0) {
            thunk_Memory_FreeBuffer((int)arg0);
        }
    }
    return arg0;
}

void igStandardQueue_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit((StaticInitCallbacks * (*)())igStandardQueue_Register);
}

void igStandardQueue_Register(void) {
    CoreLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        ((char *)g_igStandardQueue_metaObject),
        igQueue_Register,
        igQueue_GetPublishedMetaObject,
        igStandardQueue_GetMetaObjectFunction,
        igStandardQueue_className,
        0x2C, /* instance size */
        igStandardQueue_GetVTable,
        &igStandardQueue_InitFields,
        0, /* extra callback item */
        g_igStandardQueue_callbackList /* callback list */
    );
}

igMetaObject *igQueue_GetPublishedMetaObject(void) {
    return g_igQueue_metaObject[0];
}

void igStandardQueue_InitFields(void) {
    int temp_s0;
    void *temp_s2;
    void *temp_s2_2;
    void *temp_s2_3;
    void *temp_s2_4;
    void *temp_s1;

    temp_s1 = (void *)(g_igStandardQueue_metaObject[0]);
    temp_s0 = igMetaObject_GetFieldCount((igMetaObject *)temp_s1);
    igMetaObject_CreateFields((igMetaObject *)temp_s1, (igMetaField * (**)(void *))&g_igStandardQueue_ctorTable[0], 8);
    temp_s2 = (void *)(((void *)igMetaObject_GetFieldAt((igMetaObject *)temp_s1, temp_s0)));
    ((igObjectRefMetaField *)temp_s2)->_metaObject = (int)igSemaphore_GetOrCreateMetaObject();
    ((igObjectRefMetaField *)temp_s2)->_construct = 1;
    temp_s2_2 = (void *)(((void *)igMetaObject_GetFieldAt((igMetaObject *)temp_s1, temp_s0 + 1)));
    ((igObjectRefMetaField *)temp_s2_2)->_metaObject = (int)igSemaphore_GetOrCreateMetaObject();
    ((igObjectRefMetaField *)temp_s2_2)->_construct = 1;
    temp_s2_3 = (void *)(((void *)igMetaObject_GetFieldAt((igMetaObject *)temp_s1, temp_s0 + 2)));
    ((igObjectRefMetaField *)temp_s2_3)->_metaObject = (int)igSemaphore_GetOrCreateMetaObject();
    ((igObjectRefMetaField *)temp_s2_3)->_construct = 1;
    igUnsignedIntMetaField_SetDefaultValue((void **)(((void *)igMetaObject_GetFieldAt((igMetaObject *)temp_s1, temp_s0 + 3))), 4);
    temp_s2_4 = (void *)(((void *)igMetaObject_GetFieldAt((igMetaObject *)temp_s1, temp_s0 + 6)));
    ((igMemoryRefMetaField *)temp_s2_4)->_memType = igRawRefMetaField_GetDefaultDescriptor();
    ((igMemoryRefMetaField *)temp_s2_4)->_destruct = 1;
    ((igMemoryRefMetaField *)temp_s2_4)->_releaseOnCopy = 1;
    ((igMemoryRefMetaField *)temp_s2_4)->_releaseOnReset = 1;
    igUnsignedIntMetaField_SetDefaultValue((void **)(((void *)igMetaObject_GetFieldAt((igMetaObject *)temp_s1, temp_s0 + 7))), 0x2000);
    igMetaObject_NameFields((igMetaObject *)temp_s1, (const char **)&g_igStandardQueue_fieldTable[0], (igMetaField ***)&DAT_004c1c30[0], &DAT_004c1c50[0], temp_s0);
    ((igMetaObject *)g_igStandardQueue_metaObject[0])->_writeProxy = (int)igQueue_GetMetaObjectFunction;
}

