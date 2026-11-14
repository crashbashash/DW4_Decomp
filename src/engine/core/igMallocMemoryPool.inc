int igMallocMemoryPool_GetMessageLevelMetaEnum(void) {
    if (DAT_00586b78[0] == 0) {
        DAT_00586b78[0] = ((int)igMetaEnum_Create((char *)&text_MessageLevel[0], (char **)&DAT_004c1a10[0], &DAT_004c1a20[0], 4));
    }
    return DAT_00586b78[0];
}

void igMallocMemoryPool_InitDefaults(int extra0) {
    GPR_00554dbc = (GPR_00554dbc + 1);
    igMemoryPool_InitDefaults((void *)extra0);
}

void *igMallocMemoryPool_Clone(void *self, void *src) {
    void *o;
    if (*g_objectSystem[0] != 0) {
        igMallocMemoryPool_EnsureRegistered();
        return ((void *)igObject_CloneViaMetadata((void **)self, (int)src));
    }
    o = igObject_OperatorNew(0xA0, 0, (int)(Memory_GetDefaultAllocator()));
    if (o != 0) {
        o = igMallocMemoryPool_CopyConstruct((igMallocMemoryPool *)o, (int)self);
    }
    return o;
}

igMetaObject *igMallocMemoryPool_GetMetaObject(void)
{
    unsigned char ready;
    if (g_igMallocMemoryPool_metaObject[0] != 0) {
        ready = (g_igMallocMemoryPool_metaObject[0]->_validity & 4) != 0;
        if (ready != 0) goto done;
    }
    igMallocMemoryPool_EnsureRegistered();
done:
    return g_igMallocMemoryPool_metaObject[0];
}

int igMallocMemoryPool_GetVTable(void) {
    igMallocMemoryPool pool;
    int temp_s0;
    igObject *q0;
    igObject *q1;
    igMallocMemoryPool_Initialize(&pool);
    temp_s0 = *(int *)((char *)&pool + *(int *)((char *)(((void * *)g_objectSystem)[0]) + 916));
    pool._vtable = (int)&DAT_00530e90[0];
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

    return temp_s0;
}

void igMallocMemoryPool_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit((StaticInitCallbacks * (*)())igMallocMemoryPool_Register);
}

void igMallocMemoryPool_Register(void) {
    igMetaObject_RegisterClass(
        0, /* abstract */
        ((char *)g_igMallocMemoryPool_metaObject),
        igMemoryPool_Register,
        igMemoryPool_GetPublishedMetaObject,
        igMallocMemoryPool_GetMetaObjectFunction,
        igMallocMemoryPool_className,
        0xA0, /* instance size */
        igMallocMemoryPool_GetVTable,
        &igMallocMemoryPool_InitFields,
        0, /* extra callback item */
        g_igMallocMemoryPool_callbackList /* callback list */
    );
}

void igMallocMemoryPool_GetMetaObjectFunction(void) {
    igMallocMemoryPool_GetMetaObject();
}

void igMallocMemoryPool_InitFields(void) {
    igMetaObject *meta = g_igMallocMemoryPool_metaObject[0];
    int base = igMetaObject_GetFieldCount(meta);
    igObjectRefMetaField *eventTracker;
    igObjectRefMetaField *allocationLock;
    igEnumMetaField *messageLevel;
    int defaultMessageLevel;
    igMetaObject_CreateFields(meta, (FieldFactory *)g_igMallocMemoryPool_ctorTable, 10);
    igIntMetaField_SetDefault((void **)igMetaObject_GetFieldAt(meta, base), -1);
    igUnsignedLongMetaField_SetDefaultValue((void **)igMetaObject_GetFieldAt(meta, base + 2), 0xFFFFFFFFFFFFFFFFULL);
    igUnsignedShortMetaField_SetDefaultValue((void **)igMetaObject_GetFieldAt(meta, base + 4), 4);
    eventTracker = (igObjectRefMetaField *)igMetaObject_GetFieldAt(meta, base + 5);
    eventTracker->_metaObject = (int)igEventTracker_GetOrCreateMetaObject();
    allocationLock = (igObjectRefMetaField *)igMetaObject_GetFieldAt(meta, base + 7);
    allocationLock->_metaObject = (int)igSemaphore_GetOrCreateMetaObject();
    messageLevel = (igEnumMetaField *)igMetaObject_GetFieldAt(meta, base + 8);
    defaultMessageLevel = DAT_004c25f0[0];
    igEnumMetaField_SetDefaultValue((igMetaFieldView *)messageLevel, &defaultMessageLevel);
    messageLevel->_getMetaEnumFunction = (int)igMallocMemoryPool_GetMessageLevelMetaEnum;
    igIntMetaField_SetDefault((void **)igMetaObject_GetFieldAt(meta, base + 9), DAT_004c25f8[0]);
    igMetaObject_NameFields(meta, (const char **)g_igMallocMemoryPool_fieldTable, (igMetaField ***)DAT_004c1aa0, DAT_004c1ad0, base);
    g_igMallocMemoryPool_metaObject[0]->_writeProxy = (int)igMemoryPool_GetMetaObjectFunction;
}

