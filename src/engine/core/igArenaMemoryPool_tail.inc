void **igArenaMemoryPool_Create(int allocator) {
    void **pool;

    if (*g_objectSystem[0] != 0) {
        igArenaMemoryPool_EnsureRegistered();
        pool = (void **)(((void **)igMetaObject_CreateInstance((igMetaObject *)g_igArenaMemoryPool_metaObject[0], (igMemoryPoolView *)allocator)));
    } else {
        pool = (void **)(((void **)igObject_OperatorNew(0xD0, 0, allocator)));
        if (pool != 0) {
            pool = (void **)(((void **)igArenaMemoryPool_Construct((igArenaMemoryPool *)pool, 1)));
        }
        ((igObjectDispatchView *)(pool))->InitDefaults();
        ((igObjectDispatchView *)(pool))->userConstruct((int)(0));
    }
    return pool;
}

int igArenaMemoryPool_Clone(int source, int copyMode) {
    int copy;
    if (*g_objectSystem[0] != 0) {
        igArenaMemoryPool_EnsureRegistered();
        return igObject_CloneViaMetadata((void **)source, copyMode);
    }
    copy = ((int)igObject_OperatorNew(0xD0, 0, ((int)Memory_GetDefaultAllocator())));
    if (copy != 0) {
        copy = ((int)igArenaMemoryPool_CopyConstruct((igArenaMemoryPool *)copy, source));
    }
    return copy;
}

igMetaObject *igArenaMemoryPool_GetMetaObject(void)
{
    unsigned char ready;
    if (g_igArenaMemoryPool_metaObject[0] != 0) {
        ready = (g_igArenaMemoryPool_metaObject[0]->_validity & 4) != 0;
        if (ready != 0) goto done;
    }
    igArenaMemoryPool_EnsureRegistered();
done:
    return g_igArenaMemoryPool_metaObject[0];
}

int igArenaMemoryPool_GetVTable(void) {
    igArenaMemoryPool pool;
    int vtable;
    igObject *p;
    igObject *r;

    igArenaMemoryPool_Initialize(&pool);
    vtable = *(int *)((char *)&pool + *(int *)((char *)(((void * *)g_objectSystem)[0]) + 916));
    pool._vtable = (int)&g_igArenaMemoryPool_vtable[0];
    p = (igObject *)&pool._eventTracker;
    if (p != 0) {
        p = *(igObject **)p;
        if (p != 0) {
            p->_refCount = (int)((int) (p->_refCount - 1));
            if (((unsigned long long) ((long long)(int) p->_refCount << 0x29) >> 0x29) == 0) {
                igObject_Destroy(p);
            }
        }
    }
    r = (igObject *)&pool._allocationLock;
    if (r != 0) {
        r = *(igObject **)r;
        if (r != 0) {
            r->_refCount = (int)((int) (r->_refCount - 1));
            if (((unsigned long long) ((long long)(int) r->_refCount << 0x29) >> 0x29) == 0) {
                igObject_Destroy(r);
            }
        }
    }
    return vtable;
}

void igArenaMemoryPool_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit((StaticInitCallbacks * (*)())igArenaMemoryPool_Register);
}

void igArenaMemoryPool_Register(void) {
    igMetaObject_RegisterClass(
        0,
        g_igArenaMemoryPool_metaObject,
        (igMetaObjectRegisterFunction)igMemoryPool_Register,
        igMemoryPool_GetPublishedMetaObject,
        igArenaMemoryPool_GetMetaObjectFunction,
        igArenaMemoryPool_className,
        0xD0,
        igArenaMemoryPool_GetVTable,
        igArenaMemoryPool_InitFields,
        0,
        (igMetaObjectCallback *)g_igArenaMemoryPool_callbackList
    );
}

void igArenaMemoryPool_InitFields(void) {
    int base;
    igMetaObject *meta = g_igArenaMemoryPool_metaObject[0];
    int defaultHeapCheck;
    int defaultMessageLevel;
    igRawRefMetaField *arenaState;
    igObjectRefMetaField *eventTracker;
    igObjectRefMetaField *allocationLock;
    igEnumMetaField *heapIntegrityCheckLevel;
    igEnumMetaField *messageLevel;
    base = igMetaObject_GetFieldCount(meta);
    igMetaObject_CreateFields(meta, (FieldFactory *)g_igArenaMemoryPool_ctorTable, 18);
    arenaState = (igRawRefMetaField *)igMetaObject_GetFieldAt(meta, base);
    arenaState->_resetMethod = 3;
    arenaState->_persistent = 0;
    igUnsignedLongMetaField_SetDefaultValue((void **)igMetaObject_GetFieldAt(meta, base + 5), 0xFFFFFFFFFFFFFFFFULL);
    igUnsignedShortMetaField_SetDefaultValue((void **)igMetaObject_GetFieldAt(meta, base + 8), 8);
    eventTracker = (igObjectRefMetaField *)igMetaObject_GetFieldAt(meta, base + 9);
    eventTracker->_metaObject = (int)igEventTracker_GetOrCreateMetaObject();
    allocationLock = (igObjectRefMetaField *)igMetaObject_GetFieldAt(meta, base + 11);
    allocationLock->_metaObject = (int)igSemaphore_GetOrCreateMetaObject();
    igIntMetaField_SetDefault((void **)igMetaObject_GetFieldAt(meta, base + 12), -1);
    heapIntegrityCheckLevel = (igEnumMetaField *)igMetaObject_GetFieldAt(meta, base + 13);
    defaultHeapCheck = g_igArenaMemoryPool_defaultHeapIntegrityCheckLevel[0];
    igEnumMetaField_SetDefaultValue((igMetaFieldView *)heapIntegrityCheckLevel, &defaultHeapCheck);
    heapIntegrityCheckLevel->_getMetaEnumFunction = (int)igArenaMemoryPool_GetHeapIntegrityCheckLevelMetaEnum;
    messageLevel = (igEnumMetaField *)igMetaObject_GetFieldAt(meta, base + 14);
    defaultMessageLevel = g_igArenaMemoryPool_defaultMessageLevel[0];
    igEnumMetaField_SetDefaultValue((igMetaFieldView *)messageLevel, &defaultMessageLevel);
    messageLevel->_getMetaEnumFunction = (int)igArenaMemoryPool_GetMessageLevelMetaEnum;
    igIntMetaField_SetDefault((void **)igMetaObject_GetFieldAt(meta, base + 15), g_igArenaMemoryPool_defaultPoolOptionFlags[0]);
    igUnsignedIntMetaField_SetDefaultValue((void **)igMetaObject_GetFieldAt(meta, base + 17), 16);
    igMetaObject_NameFields(meta, (const char **)g_igArenaMemoryPool_fieldTable, (igMetaField ***)g_igArenaMemoryPool_fieldDescriptors, g_igArenaMemoryPool_fieldOffsets, base);
    g_igArenaMemoryPool_metaObject[0]->_writeProxy = (int)igMemoryPool_GetMetaObjectFunction;
}

