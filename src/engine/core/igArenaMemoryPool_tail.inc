void **igArenaMemoryPool_Create(int arg0) {
    void **var_s0;

    if (*g_objectSystem[0] != 0) {
        igArenaMemoryPool_EnsureRegistered();
        var_s0 = (void **)(((void **)igMetaObject_CreateInstance((igMetaObject *)g_igArenaMemoryPool_metaObject[0], (igMemoryPoolView *)arg0)));
    } else {
        var_s0 = (void **)(((void **)igObject_OperatorNew(0xD0, 0, arg0)));
        if (var_s0 != 0) {
            var_s0 = (void **)(((void **)igArenaMemoryPool_Construct((igArenaMemoryPool *)var_s0, 1)));
        }
        ((igObjectDispatchView *)(var_s0))->vfunc_09();
        ((igObjectDispatchView *)(var_s0))->userConstruct((int)(0));
    }
    return var_s0;
}

int igArenaMemoryPool_Clone(int arg0, int arg1) {
    int temp_v0;
    if (*g_objectSystem[0] != 0) {
        igArenaMemoryPool_EnsureRegistered();
        return igObject_CloneViaMetadata((void **)arg0, arg1);
    }
    temp_v0 = ((int)igObject_OperatorNew(0xD0, 0, ((int)Memory_GetDefaultAllocator())));
    if (temp_v0 != 0) {
        temp_v0 = ((int)igArenaMemoryPool_CopyConstruct((igArenaMemoryPool *)temp_v0, arg0));
    }
    return temp_v0;
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
    int temp_s0;
    igObject *p;
    igObject *r;

    igArenaMemoryPool_Initialize(&pool);
    temp_s0 = *(int *)((char *)&pool + *(int *)((char *)(((void * *)g_objectSystem)[0]) + 916));
    pool._vtable = (int)&DAT_00531030[0];
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
    return temp_s0;
}

void igArenaMemoryPool_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit((StaticInitCallbacks * (*)())igArenaMemoryPool_Register);
}

void igArenaMemoryPool_Register(void) {
    igMetaObject_RegisterClass(
        0, /* abstract */
        ((char *)g_igArenaMemoryPool_metaObject),
        igMemoryPool_Register,
        igMemoryPool_GetPublishedMetaObject,
        igArenaMemoryPool_GetMetaObjectFunction,
        igArenaMemoryPool_className,
        0xD0, /* instance size */
        igArenaMemoryPool_GetVTable,
        &igArenaMemoryPool_InitFields,
        0, /* extra callback item */
        g_igArenaMemoryPool_callbackList /* callback list */
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
    defaultHeapCheck = DAT_005871f8[0];
    igEnumMetaField_SetDefaultValue((igMetaFieldView *)heapIntegrityCheckLevel, &defaultHeapCheck);
    heapIntegrityCheckLevel->_getMetaEnumFunction = (int)igArenaMemoryPool_GetHeapIntegrityCheckLevelMetaEnum;
    messageLevel = (igEnumMetaField *)igMetaObject_GetFieldAt(meta, base + 14);
    defaultMessageLevel = DAT_004c2368[0];
    igEnumMetaField_SetDefaultValue((igMetaFieldView *)messageLevel, &defaultMessageLevel);
    messageLevel->_getMetaEnumFunction = (int)igArenaMemoryPool_GetMessageLevelMetaEnum;
    igIntMetaField_SetDefault((void **)igMetaObject_GetFieldAt(meta, base + 15), DAT_004c2370[0]);
    igUnsignedIntMetaField_SetDefaultValue((void **)igMetaObject_GetFieldAt(meta, base + 17), 16);
    igMetaObject_NameFields(meta, (const char **)g_igArenaMemoryPool_fieldTable, (igMetaField ***)DAT_004c18b0, DAT_004c1900, base);
    g_igArenaMemoryPool_metaObject[0]->_writeProxy = (int)igMemoryPool_GetMetaObjectFunction;
}

