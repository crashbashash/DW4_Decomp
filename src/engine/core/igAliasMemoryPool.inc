FactoryPoolView *igAliasMemoryPool_Create(void *allocator) {
    FactoryPoolView *pool;
    if (*g_objectSystem[0]) {
        igAliasMemoryPool_EnsureRegistered();
        pool=((FactoryPoolView *)igMetaObject_CreateInstance((CreateMeta *)(((void * *)g_igAliasMemoryPool_metaObject)[0]), (MemoryPool *)allocator));
    } else {
        pool=((FactoryPoolView *)FUN_002f0040(184, 0, (int)allocator));
        if(pool)pool=((FactoryPoolView *)igAliasMemoryPool_Construct((igAliasMemoryPool *)pool, 1));
        pool->Init();
        pool->Set(0);
    }
    return pool;
}

void *Gap__Core__igAliasMemoryPool__vfunc_21(int arg0, int arg1) {
    void *p;
    if (*DAT_00586dc8[0] != 0) {
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
    union U_2cd2e0 u;
    int temp_s0;
    S_ref *q0;
    S_ref *q1;
    S_ref *q2;

    FUN_002d1500(u.b);
    temp_s0 = *(int *)&u.b[*(int *)((char *)(((void * *)DAT_00586dc8)[0]) + 916)];
    u.vt = (int)&DAT_005313a0[0];
    q2 = (S_ref *)&u.b[180];
    if (q2 != 0) {
        q2 = *(S_ref **)q2;
        if (q2 != 0) {
            q2->f4 = (int)((int) (q2->f4 - 1));
            if (((unsigned long long) ((long long) q2->f4 << 0x29) >> 0x29) == 0) {
                igObject_Destroy(q2);
            }
        }
    }
    q1 = (S_ref *)&u.b[152];
    if (q1 != 0) {
        q1 = *(S_ref **)q1;
        if (q1 != 0) {
            q1->f4 = (int)((int) (q1->f4 - 1));
            if (((unsigned long long) ((long long) q1->f4 << 0x29) >> 0x29) == 0) {
                igObject_Destroy(q1);
            }
        }
    }
    q0 = (S_ref *)&u.b[116];
    if (q0 != 0) {
        q0 = *(S_ref **)q0;
        if (q0 != 0) {
            q0->f4 = (int)((int) (q0->f4 - 1));
            if (((unsigned long long) ((long long) q0->f4 << 0x29) >> 0x29) == 0) {
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

int FUN_002cd480(void) {
    return DAT_00585ea0[0];
}

int FUN_002cd5c0(void) {
    if (DAT_00586a28[0] == 0) {
        DAT_00586a28[0] = ((int)igMetaEnum_Create((char *)&DAT_004f89f8[0], (char **)&DAT_004c16b0[0], &DAT_004c16c0[0], 4));
    }
    return DAT_00586a28[0];
}

