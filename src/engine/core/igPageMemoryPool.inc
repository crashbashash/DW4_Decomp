int igPageMemoryPool_Clone(int source, int copyMode) {
    int clone;

    if (*g_objectSystem[0] != 0) {
        igPageMemoryPool_EnsureRegistered();
        return igObject_CloneViaMetadata((void **)source, copyMode);
    }
    clone = ((int)igObject_OperatorNew(0x110, 0, ((int)Memory_GetDefaultAllocator())));
    if (clone != 0) {
        clone = ((int)igPageMemoryPool_CopyConstruct((igPageMemoryPool *)clone, source));
    }
    return clone;
}

igMetaObject *igPageMemoryPool_GetMetaObject(void)
{
    unsigned char ready;
    if (g_igPageMemoryPool_metaObject[0] != 0) {
        ready = (g_igPageMemoryPool_metaObject[0]->_validity & 4) != 0;
        if (ready != 0) goto done;
    }
    igPageMemoryPool_EnsureRegistered();
done:
    return g_igPageMemoryPool_metaObject[0];
}

int igPageMemoryPool_GetVTable(void) {
    igPageMemoryPool pool;
    int result;
    igObject *q0;
    igObject *q1;
    igPageMemoryPool_Initialize(&pool);
    result = *(int *)((char *)&pool + *(int *)((char *)(((void * *)g_objectSystem)[0]) + 916));
    pool._vtable = (int)&g_igPageMemoryPool_vtable[0];
    q0 = (igObject *)&pool._eventTracker;
    if (q0 != 0) {
        q0 = *(igObject **)q0;
        if (q0 != 0) {
            q0->_refCount = (int)((int) (q0->_refCount - 1));
            if (((unsigned long long) ((long long)(int) q0->_refCount << 0x29) >> 0x29) == 0) {
                igObject_Destroy(q0);
            }
        }
    }
    q1 = (igObject *)&pool._allocationLock;
    if (q1 != 0) {
        q1 = *(igObject **)q1;
        if (q1 != 0) {
            q1->_refCount = (int)((int) (q1->_refCount - 1));
            if (((unsigned long long) ((long long)(int) q1->_refCount << 0x29) >> 0x29) == 0) {
                igObject_Destroy(q1);
            }
        }
    }

    return result;
}

void igPageMemoryPool_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit((StaticInitCallbacks * (*)())igPageMemoryPool_Register);
}

void igPageMemoryPool_Register(void) {
    igMetaObject_RegisterClass(
        0,
        g_igPageMemoryPool_metaObject,
        (igMetaObjectRegisterFunction)igMemoryPool_Register,
        igMemoryPool_GetPublishedMetaObject,
        igPageMemoryPool_GetMetaObjectFunction,
        igPageMemoryPool_className,
        0x110,
        igPageMemoryPool_GetVTable,
        igPageMemoryPool_InitFields,
        0,
        (igMetaObjectCallback *)g_igPageMemoryPool_callbackList
    );
}

void igPageMemoryPool_GetMetaObjectFunction(void) {
    igPageMemoryPool_GetMetaObject();
}

void igPageMemoryPool_InitFields(void) {
    igMetaObject *meta = g_igPageMemoryPool_metaObject[0];
    int base = igMetaObject_GetFieldCount(meta);
    int defaultMessageLevel;
    igObjectRefMetaField *eventTracker;
    igObjectRefMetaField *allocationLock;
    igEnumMetaField *messageLevel;
    igMetaObject_CreateFields(meta, (FieldFactory *)g_igPageMemoryPool_ctorTable, 7);
    igUnsignedLongMetaField_SetDefaultValue((void **)igMetaObject_GetFieldAt(meta, base), 0xFFFFFFFFFFFFFFFFULL);
    eventTracker = (igObjectRefMetaField *)igMetaObject_GetFieldAt(meta, base + 1);
    eventTracker->_metaObject = (int)igEventTracker_GetOrCreateMetaObject();
    allocationLock = (igObjectRefMetaField *)igMetaObject_GetFieldAt(meta, base + 3);
    allocationLock->_metaObject = (int)igSemaphore_GetOrCreateMetaObject();
    igIntMetaField_SetDefault((void **)igMetaObject_GetFieldAt(meta, base + 4), -1);
    messageLevel = (igEnumMetaField *)igMetaObject_GetFieldAt(meta, base + 5);
    defaultMessageLevel = g_igPageMemoryPool_defaultMessageLevel[0];
    igEnumMetaField_SetDefaultValue((igMetaFieldView *)messageLevel, &defaultMessageLevel);
    messageLevel->_getMetaEnumFunction = (int)igPageMemoryPool_GetMessageLevelMetaEnum;
    igIntMetaField_SetDefault((void **)igMetaObject_GetFieldAt(meta, base + 6), g_igPageMemoryPool_defaultPoolOptionFlags[0]);
    igMetaObject_NameFields(meta, (const char **)g_igPageMemoryPool_fieldTable, (igMetaField ***)g_igPageMemoryPool_fieldDescriptors, g_igPageMemoryPool_fieldOffsets, base);
    g_igPageMemoryPool_metaObject[0]->_writeProxy = (int)igMemoryPool_GetMetaObjectFunction;
}

int igArenaMemoryPool_GetArenaMemoryPoolFlagsMetaEnum(void) {
    if (g_arenaMemoryPoolFlagsMetaEnum[0] == 0) {
        g_arenaMemoryPoolFlagsMetaEnum[0] = ((int)igMetaEnum_Create((char *)&text_ArenaMemoryPoolFlags[0], (char **)&g_arenaMemoryPoolFlagsNames[0], &g_arenaMemoryPoolFlagsValues[0], 0xA));
    }
    return g_arenaMemoryPoolFlagsMetaEnum[0];
}

int igArenaMemoryPool_GetMessageLevelMetaEnum(void) {
    if (g_messageLevelMetaEnum[0] == 0) {
        g_messageLevelMetaEnum[0] = ((int)igMetaEnum_Create((char *)&text_MessageLevel[0], (char **)&g_messageLevelNames[0], &g_messageLevelValues[0], 4));
    }
    return g_messageLevelMetaEnum[0];
}

int igArenaMemoryPool_GetHeapIntegrityCheckLevelMetaEnum(void) {
    if (g_heapIntegrityCheckLevelMetaEnum[0] == 0) {
        g_heapIntegrityCheckLevelMetaEnum[0] = ((int)igMetaEnum_Create((char *)&text_HeapIntegrityCheckLevel[0], (char **)&g_heapIntegrityCheckLevelNames[0], &g_heapIntegrityCheckLevelValues[0], 4));
    }
    return g_heapIntegrityCheckLevelMetaEnum[0];
}

