void **FUN_002cdab0(int arg0) {
    void **var_s0;

    if (*g_objectSystem[0] != 0) {
        FUN_002cdcf0();
        var_s0 = (void **)(((void **)igMetaObject_CreateInstance((igMetaObject *)g_igArenaMemoryPool_metaObject[0], (igMemoryPoolView *)arg0)));
    } else {
        var_s0 = (void **)(((void **)FUN_002f0040(0xD0, 0, arg0)));
        if (var_s0 != 0) {
            var_s0 = (void **)(((void **)FUN_0031ebd0((igArenaMemoryPool *)var_s0, 1)));
        }
        ((igObjectDispatchView *)(var_s0))->vfunc_09();
        ((igObjectDispatchView *)(var_s0))->userConstruct((int)(0));
    }
    return var_s0;
}

int Gap__Core__igArenaMemoryPool__vfunc_21(int arg0, int arg1) {
    int temp_v0;
    if (*g_objectSystem[0] != 0) {
        FUN_002cdcf0();
        return igObject_CloneViaMetadata((void **)arg0, arg1);
    }
    temp_v0 = ((int)FUN_002f0040(0xD0, 0, ((int)Memory_GetDefaultAllocator())));
    if (temp_v0 != 0) {
        temp_v0 = ((int)FUN_0031ec20((igArenaMemoryPool *)temp_v0, arg0));
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
    FUN_002cdcf0();
done:
    return g_igArenaMemoryPool_metaObject[0];
}

int igArenaMemoryPool_GetVTable(void) {
    igArenaMemoryPool pool;
    int temp_s0;
    S_ref *p;
    S_ref *r;

    FUN_0031eb90(&pool);
    temp_s0 = *(int *)((char *)&pool + *(int *)((char *)(((void * *)g_objectSystem)[0]) + 916));
    pool._vtable = (int)&DAT_00531030[0];
    p = (S_ref *)&pool._eventTracker;
    if (p != 0) {
        p = *(S_ref **)p;
        if (p != 0) {
            p->f4 = (int)((int) (p->f4 - 1));
            if (((unsigned long long) ((long long) p->f4 << 0x29) >> 0x29) == 0) {
                igObject_Destroy(p);
            }
        }
    }
    r = (S_ref *)&pool._allocationLock;
    if (r != 0) {
        r = *(S_ref **)r;
        if (r != 0) {
            r->f4 = (int)((int) (r->f4 - 1));
            if (((unsigned long long) ((long long) r->f4 << 0x29) >> 0x29) == 0) {
                igObject_Destroy(r);
            }
        }
    }
    return temp_s0;
}

void FUN_002cdcf0(void)
{
    igMetaObject_RunStaticInit((StaticInitCallbacks * (*)())igArenaMemoryPool_Register);
}

void igArenaMemoryPool_Register(void) {
    igMetaObject_RegisterClass(
        0, /* abstract */
        ((char *)g_igArenaMemoryPool_metaObject),
        igMemoryPool_Register,
        igMemoryPool_GetPublishedMetaObject,
        thunk_igArenaMemoryPool_GetMetaObject,
        igArenaMemoryPool_className,
        0xD0, /* instance size */
        igArenaMemoryPool_GetVTable,
        &igArenaMemoryPool_InitFields,
        0, /* extra callback item */
        g_igArenaMemoryPool_callbackList /* callback list */
    );
}

