igAliasMemoryPoolView *igAliasMemoryPool_Create(void *allocator) {
    igAliasMemoryPoolView *pool;
    if (*g_objectSystem[0]) {
        igAliasMemoryPool_EnsureRegistered();
        pool=((igAliasMemoryPoolView *)igMetaObject_CreateInstance((igMetaObject *)(((void * *)g_igAliasMemoryPool_metaObject)[0]), (igMemoryPoolView *)allocator));
    } else {
        pool=((igAliasMemoryPoolView *)igObject_OperatorNew(184, 0, (int)allocator));
        if(pool)pool=((igAliasMemoryPoolView *)igAliasMemoryPool_Construct((igAliasMemoryPool *)pool, 1));
        pool->InitDefaults();
        pool->userConstruct(0);
    }
    return pool;
}

void *igAliasMemoryPool_Clone(int source, int flags) {
    void *copy;
    if (*g_objectSystem[0] != 0) {
        igAliasMemoryPool_EnsureRegistered();
        return (void *)igObject_CloneViaMetadata((void **)source, flags);
    }
    copy = igObject_OperatorNew(0xB8, 0, (int)(Memory_GetDefaultAllocator()));
    if (copy != 0) {
        copy = igAliasMemoryPool_CopyConstruct((igAliasMemoryPool *)copy, source);
    }
    return copy;
}

igMetaObject *igAliasMemoryPool_GetMetaObject(void)
{
    unsigned char ready;
    if (g_igAliasMemoryPool_metaObject[0] != 0) {
        ready = (g_igAliasMemoryPool_metaObject[0]->_validity & 4) != 0;
        if (ready != 0) goto done;
    }
    igAliasMemoryPool_EnsureRegistered();
done:
    return g_igAliasMemoryPool_metaObject[0];
}

int igAliasMemoryPool_GetVTable(void) {
    igAliasMemoryPool pool;
    int vtable;
    igObject *lockSlot;
    igObject *trackerSlot;
    igObject *aliasedSlot;

    FUN_002d1500(&pool);
    vtable = *(int *)((char *)&pool + *(int *)((char *)(((void * *)g_objectSystem)[0]) + 916));
    pool._vtable = (int)&g_igAliasMemoryPool_vtable[0];
    aliasedSlot = (igObject *)&pool._aliasedMemoryPool;
    if (aliasedSlot != 0) {
        aliasedSlot = *(igObject **)aliasedSlot;
        if (aliasedSlot != 0) {
            aliasedSlot->_refCount = (int)((int) (aliasedSlot->_refCount - 1));
            if (((unsigned long long) ((long long)(int) aliasedSlot->_refCount << 0x29) >> 0x29) == 0) {
                igObject_Destroy(aliasedSlot);
            }
        }
    }
    trackerSlot = (igObject *)&pool._eventTracker;
    if (trackerSlot != 0) {
        trackerSlot = *(igObject **)trackerSlot;
        if (trackerSlot != 0) {
            trackerSlot->_refCount = (int)((int) (trackerSlot->_refCount - 1));
            if (((unsigned long long) ((long long)(int) trackerSlot->_refCount << 0x29) >> 0x29) == 0) {
                igObject_Destroy(trackerSlot);
            }
        }
    }
    lockSlot = (igObject *)&pool._allocationLock;
    if (lockSlot != 0) {
        lockSlot = *(igObject **)lockSlot;
        if (lockSlot != 0) {
            lockSlot->_refCount = (int)((int) (lockSlot->_refCount - 1));
            if (((unsigned long long) ((long long)(int) lockSlot->_refCount << 0x29) >> 0x29) == 0) {
                igObject_Destroy(lockSlot);
            }
        }
    }
    return vtable;
}

void igAliasMemoryPool_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit((StaticInitCallbacks * (*)())igAliasMemoryPool_Register);
}

void igAliasMemoryPool_Register(void) {
    igMetaObject_RegisterClass(
        0,
        g_igAliasMemoryPool_metaObject,
        (igMetaObjectRegisterFunction)igMemoryPool_Register,
        igMemoryPool_GetPublishedMetaObject,
        igAliasMemoryPool_GetMetaObjectFunction,
        igAliasMemoryPool_className,
        0xB8,
        igAliasMemoryPool_GetVTable,
        igAliasMemoryPool_InitFields,
        0,
        (igMetaObjectCallback *)g_igAliasMemoryPool_callbackList
    );
}

void igAliasMemoryPool_GetMetaObjectFunction(void) {
    igAliasMemoryPool_GetMetaObject();
}

igMetaObject *igMemoryPool_GetPublishedMetaObject(void) {
    return g_igMemoryPool_metaObject[0];
}

void igAliasMemoryPool_InitFields(void) {
    igObjectRefMetaField *eventTracker;
    igObjectRefMetaField *allocationLock;
    int base;
    igObjectRefMetaField *aliasedPool;
    igMetaObject *meta = g_igAliasMemoryPool_metaObject[0];
    base = igMetaObject_GetFieldCount(meta);
    igMetaObject_CreateFields(meta, (FieldFactory *)g_igAliasMemoryPool_ctorTable, 14);
    igIntMetaField_SetDefault((void **)igMetaObject_GetFieldAt(meta, base), -1);
    igUnsignedLongMetaField_SetDefaultValue((void **)igMetaObject_GetFieldAt(meta, base + 4), 0xFFFFFFFFFFFFFFFFULL);
    eventTracker = (igObjectRefMetaField *)igMetaObject_GetFieldAt(meta, base + 5);
    eventTracker->_metaObject = (int)igEventTracker_GetOrCreateMetaObject();
    allocationLock = (igObjectRefMetaField *)igMetaObject_GetFieldAt(meta, base + 10);
    allocationLock->_metaObject = (int)igSemaphore_GetOrCreateMetaObject();
    igUnsignedShortMetaField_SetDefaultValue((void **)igMetaObject_GetFieldAt(meta, base + 12), 8);
    aliasedPool = (igObjectRefMetaField *)igMetaObject_GetFieldAt(meta, base + 13);
    aliasedPool->_metaObject = (int)igMemoryPool_GetOrCreateMetaObject();
    aliasedPool->_construct = 0;
    aliasedPool->_destruct = 0;
    igMetaObject_NameFields(meta, (const char **)g_igAliasMemoryPool_fieldTable, (igMetaField ***)g_igAliasMemoryPool_fieldDescriptors, g_igAliasMemoryPool_fieldOffsets, base);
    g_igAliasMemoryPool_metaObject[0]->_writeProxy = (int)igMemoryPool_GetMetaObjectFunction;
}

int igPageMemoryPool_GetMessageLevelMetaEnum(void) {
    if (g_igPageMemoryPool_messageLevelMetaEnum[0] == 0) {
        g_igPageMemoryPool_messageLevelMetaEnum[0] = ((int)igMetaEnum_Create((char *)&text_MessageLevel[0], (char **)&g_igPageMemoryPool_messageLevelNames[0], &g_igPageMemoryPool_messageLevelValues[0], 4));
    }
    return g_igPageMemoryPool_messageLevelMetaEnum[0];
}

