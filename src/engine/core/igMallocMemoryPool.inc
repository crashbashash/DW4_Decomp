int FUN_002ce1b0(void) {
    if (DAT_00586b78[0] == 0) {
        DAT_00586b78[0] = ((int)igMetaEnum_Create((char *)&text_MessageLevel[0], (char **)&DAT_004c1a10[0], &DAT_004c1a20[0], 4));
    }
    return DAT_00586b78[0];
}

void Gap__Core__igMallocMemoryPool__vfunc_11(int extra0) {
    GPR_00554dbc = (GPR_00554dbc + 1);
    FUN_002f00a0((void *)extra0);
}

void *Gap__Core__igMallocMemoryPool__vfunc_21(void *self, void *src) {
    void *o;
    if (*g_objectSystem[0] != 0) {
        FUN_002ce3c0();
        return ((void *)igObject_CloneViaMetadata((void **)self, (int)src));
    }
    o = FUN_002f0040(0xA0, 0, (int)(Memory_GetDefaultAllocator()));
    if (o != 0) {
        o = FUN_00323600((igMallocMemoryPool *)o, (int)self);
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
    FUN_002ce3c0();
done:
    return g_igMallocMemoryPool_metaObject[0];
}

int igMallocMemoryPool_GetVTable(void) {
    igMallocMemoryPool pool;
    int temp_s0;
    S_ref *q0;
    S_ref *q1;
    FUN_003235c0(&pool);
    temp_s0 = *(int *)((char *)&pool + *(int *)((char *)(((void * *)g_objectSystem)[0]) + 916));
    pool._vtable = (int)&DAT_00530e90[0];
    q0 = (S_ref *)&pool._eventTracker;
    if (q0 != 0) {
        q0 = *(S_ref **)q0;
        if (q0 != 0) {
            q0->f4 = (int)((int) (q0->f4 - 1));
            if (((unsigned long long) ((long long) q0->f4 << 0x29) >> 0x29) == 0) {
                igObject_Destroy(q0);
            }
        }
    }
    q1 = (S_ref *)&pool._allocationLock;
    if (q1 != 0) {
        q1 = *(S_ref **)q1;
        if (q1 != 0) {
            q1->f4 = (int)((int) (q1->f4 - 1));
            if (((unsigned long long) ((long long) q1->f4 << 0x29) >> 0x29) == 0) {
                igObject_Destroy(q1);
            }
        }
    }

    return temp_s0;
}

void FUN_002ce3c0(void)
{
    igMetaObject_RunStaticInit((StaticInitCallbacks * (*)())igMallocMemoryPool_Register);
}

void igMallocMemoryPool_Register(void) {
    igMetaObject_RegisterClass(
        0, /* abstract */
        ((char *)g_igMallocMemoryPool_metaObject),
        igMemoryPool_Register,
        igMemoryPool_GetPublishedMetaObject,
        thunk_igMallocMemoryPool_GetMetaObject,
        igMallocMemoryPool_className,
        0xA0, /* instance size */
        igMallocMemoryPool_GetVTable,
        &igMallocMemoryPool_InitFields,
        0, /* extra callback item */
        g_igMallocMemoryPool_callbackList /* callback list */
    );
}

void thunk_igMallocMemoryPool_GetMetaObject(void) {
    igMallocMemoryPool_GetMetaObject();
}

