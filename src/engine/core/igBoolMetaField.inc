void **FUN_002ccab0(int arg0) {
    void **var_s0;

    if (*g_objectSystem[0] != 0) {
        FUN_002ccca0();
        var_s0 = (void **)(((void **)igMetaObject_CreateInstance((igMetaObject *)g_igBoolMetaField_metaObject[0], (igMemoryPoolView *)arg0)));
    } else {
        var_s0 = (void **)(((void **)igObject_AllocateRawStorage(0x34, 0, (igMemoryPoolView *)arg0)));
        if (var_s0 != 0) {
            var_s0 = (void **)(((void **)FUN_002d37b0((int **)var_s0, 1)));
        }
        ((igObjectDispatchView *)(var_s0))->vfunc_09();
        ((igObjectDispatchView *)(var_s0))->userConstruct((int)(0));
    }
    return var_s0;
}

int Gap__Core__igBoolMetaField__vfunc_21(int arg0, int arg1) {
    int t;
    if (*g_objectSystem[0]) {
        FUN_002ccca0();
        FUN_00300c60(arg0, arg1);
        return;
    }
    t = FUN_002ff800(0x34, 0);
    if (t) t = ((int)FUN_002d3830((int **)t, arg0));
    return t;
}

igMetaObject *igBoolMetaField_GetMetaObject(void)
{
    igMetaObject *g = g_igBoolMetaField_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_002ccca0();
    return g_igBoolMetaField_metaObject[0];
}

int igBoolMetaField_GetVTable(void) {
    igBoolMetaField u;
    int temp_s0;
    char *ps;
    int *temp_v1;
    int *temp_a1;
    int temp_v0;

    FUN_002d37f0((int **)&u);
    temp_s0 = *(int *)((char *)&u + *(int *)((char *)(((void * *)g_objectSystem)[0]) + 916));
    u._vtable = (int)&g_igMetaField_vtable[0];
    ps = (char *)&u._fieldName;
    if (ps != 0) {
        temp_v1 = *(int **)ps;
        if (temp_v1 != 0) {
            temp_a1 = temp_v1 - 2;
            temp_v0 = temp_v1[-1] - 1;
            temp_v1[-1] = temp_v0;
            if (temp_v0 == 0) {
                StringChunk_ReleaseHeader((StringChunkOwnerView *)(*temp_a1), (int)temp_a1);
            }
        }
    }
    return temp_s0;
}

void FUN_002ccca0(void)
{
    igMetaObject_RunStaticInit((StaticInitCallbacks * (*)())igBoolMetaField_Register);
}

void igBoolMetaField_Register(void) {
    igMetaObject_RegisterClass(
        0, /* abstract */
        ((char *)g_igBoolMetaField_metaObject),
        igMetaField_Register,
        igMetaField_GetPublishedMetaObject,
        thunk_igBoolMetaField_GetMetaObject,
        igBoolMetaField_className,
        0x34, /* instance size */
        igBoolMetaField_GetVTable,
        0,
        0, /* extra callback item */
        g_igBoolMetaField_callbackList /* callback list */
    );
}

void thunk_igBoolMetaField_GetMetaObject(void) {
    igBoolMetaField_GetMetaObject();
}

void FUN_002ccd30(void) {
    void *temp_s0;

    if (DAT_00586990[0] == 0) {
        DAT_00586990[0] = (void *)(((void *)igMetaObject_CreateInstance((igMetaObject *)g_igBoolMetaField_metaObject[0], (igMemoryPoolView *)(((int)Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData))))));
        temp_s0 = (void *)(DAT_00586990[0]);
        if (temp_s0 != 0) {
            MetaRefList_AppendRetained(FUN_002fc250(), (igObject *)temp_s0);
            {
                void *held = (void *)DAT_00586990[0];
                *(int *)((char *)(held) + 4) = *(int *)((char *)(held) + 4) - 1;
                if (((unsigned long long) ((long long) *(int *)((char *)(held) + 4) << 0x29) >> 0x29) == 0) {
                    igObject_Destroy(held);
                }
            }
            *(short *)((char *)(DAT_00586990[0]) + 18) = (short) (*(int *)((char *)(((void *)FUN_002fc250())) + 12) - 1);
            igMetaField_FinalizeDescriptor((igMetaField *)DAT_00586990[0]);
        }
    }
}

int FUN_002cce00(void) {
    if (((int *)DAT_00586990)[0] == 0) {
        FUN_002ccca0();
    }
    return ((int *)DAT_00586990)[0];
}

