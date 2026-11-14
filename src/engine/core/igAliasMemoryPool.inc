igAliasMemoryPoolView *igAliasMemoryPool_Create(void *allocator) {
    igAliasMemoryPoolView *pool;
    if (*g_objectSystem[0]) {
        igAliasMemoryPool_EnsureRegistered();
        pool=((igAliasMemoryPoolView *)igMetaObject_CreateInstance((igMetaObject *)(((void * *)g_igAliasMemoryPool_metaObject)[0]), (igMemoryPoolView *)allocator));
    } else {
        pool=((igAliasMemoryPoolView *)FUN_002f0040(184, 0, (int)allocator));
        if(pool)pool=((igAliasMemoryPoolView *)igAliasMemoryPool_Construct((igAliasMemoryPool *)pool, 1));
        pool->vfunc_09();
        pool->userConstruct(0);
    }
    return pool;
}

void *Gap__Core__igAliasMemoryPool__vfunc_21(int arg0, int arg1) {
    void *p;
    if (*g_objectSystem[0] != 0) {
        igAliasMemoryPool_EnsureRegistered();
        return (void *)igObject_CloneViaMetadata((void **)arg0, arg1);
    }
    p = FUN_002f0040(0xB8, 0, (int)(Memory_GetDefaultAllocator()));
    if (p != 0) {
        p = igAliasMemoryPool_CopyConstruct((igAliasMemoryPool *)p, arg0);
    }
    return p;
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
    int temp_s0;
    igObject *q0;
    igObject *q1;
    igObject *q2;

    FUN_002d1500(&pool);
    temp_s0 = *(int *)((char *)&pool + *(int *)((char *)(((void * *)g_objectSystem)[0]) + 916));
    pool._vtable = (int)&g_igAliasMemoryPool_vtable[0];
    q2 = (igObject *)&pool._aliasedMemoryPool;
    if (q2 != 0) {
        q2 = *(igObject **)q2;
        if (q2 != 0) {
            q2->_refCount = (int)((int) (q2->_refCount - 1));
            if (((unsigned long long) ((long long)(int) q2->_refCount << 0x29) >> 0x29) == 0) {
                igObject_Destroy(q2);
            }
        }
    }
    q1 = (igObject *)&pool._eventTracker;
    if (q1 != 0) {
        q1 = *(igObject **)q1;
        if (q1 != 0) {
            q1->_refCount = (int)((int) (q1->_refCount - 1));
            if (((unsigned long long) ((long long)(int) q1->_refCount << 0x29) >> 0x29) == 0) {
                igObject_Destroy(q1);
            }
        }
    }
    q0 = (igObject *)&pool._allocationLock;
    if (q0 != 0) {
        q0 = *(igObject **)q0;
        if (q0 != 0) {
            q0->_refCount = (int)((int) (q0->_refCount - 1));
            if (((unsigned long long) ((long long)(int) q0->_refCount << 0x29) >> 0x29) == 0) {
                igObject_Destroy(q0);
            }
        }
    }
    return temp_s0;
}

void igAliasMemoryPool_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit((StaticInitCallbacks * (*)())igAliasMemoryPool_Register);
}

void igAliasMemoryPool_Register(void) {
    igMetaObject_RegisterClass(
        0, /* abstract */
        ((char *)g_igAliasMemoryPool_metaObject),
        igMemoryPool_Register,
        igMemoryPool_GetPublishedMetaObject,
        thunk_igAliasMemoryPool_GetMetaObject,
        igAliasMemoryPool_className,
        0xB8, /* instance size */
        igAliasMemoryPool_GetVTable,
        &igAliasMemoryPool_InitFields,
        0, /* extra callback item */
        g_igAliasMemoryPool_callbackList /* callback list */
    );
}

void thunk_igAliasMemoryPool_GetMetaObject(void) {
    igAliasMemoryPool_GetMetaObject();
}

igMetaObject *FUN_002cd480(void) {
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
    FUN_002ea4b0((void **)igMetaObject_GetFieldAt(meta, base), -1);
    FUN_0030ec10((void **)igMetaObject_GetFieldAt(meta, base + 4), 0xFFFFFFFFFFFFFFFFULL);
    eventTracker = (igObjectRefMetaField *)igMetaObject_GetFieldAt(meta, base + 5);
    eventTracker->_metaObject = (int)FUN_002c57c0();
    allocationLock = (igObjectRefMetaField *)igMetaObject_GetFieldAt(meta, base + 10);
    allocationLock->_metaObject = (int)FUN_002ba690();
    FUN_0030eda0((void **)igMetaObject_GetFieldAt(meta, base + 12), 8);
    aliasedPool = (igObjectRefMetaField *)igMetaObject_GetFieldAt(meta, base + 13);
    aliasedPool->_metaObject = (int)igMemoryPool_GetOrCreateMetaObject();
    aliasedPool->_construct = 0;
    aliasedPool->_destruct = 0;
    igMetaObject_NameFields(meta, (const char **)g_igAliasMemoryPool_fieldTable, (igMetaField ***)DAT_004c1630, DAT_004c1670, base);
    g_igAliasMemoryPool_metaObject[0]->_writeProxy = (int)thunk_igMemoryPool_GetMetaObject;
}

int FUN_002cd5c0(void) {
    if (DAT_00586a28[0] == 0) {
        DAT_00586a28[0] = ((int)igMetaEnum_Create((char *)&text_MessageLevel[0], (char **)&DAT_004c16b0[0], &DAT_004c16c0[0], 4));
    }
    return DAT_00586a28[0];
}

