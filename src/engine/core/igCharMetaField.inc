void **FUN_002cbf70(int arg0) {
    void **var_s0;

    if (*g_objectSystem[0] != 0) {
        FUN_002cc160();
        var_s0 = (void **)(((void **)igMetaObject_CreateInstance((CreateMeta *)g_igCharMetaField_metaObject[0], (MemoryPool *)arg0)));
    } else {
        var_s0 = (void **)(((void **)igObject_AllocateRawStorage(0x34, 0, (void **)arg0)));
        if (var_s0 != 0) {
            var_s0 = (void **)(((void **)FUN_002d4d60((int **)var_s0, 1)));
        }
        ((DW4VC_44_0 *)(var_s0))->vX();
        ((DW4VC_36_1 *)(var_s0))->vX((int)(0));
    }
    return var_s0;
}

void *Gap__Core__igCharMetaField__vfunc_21(void *arg0, void *arg1) {
    void *p;
    if (*g_objectSystem[0] != 0) {
        FUN_002cc160();
        return ((void *)igObject_CloneViaMetadata((void **)arg0, (int)arg1));
    }
    p = igObject_AllocateRawStorageDefault(0x34, 0);
    if (p) p = ((void *)FUN_002d4de0((int **)p, (int)arg0));
    return p;
}

igMetaObject *igCharMetaField_GetMetaObject(void)
{
    igMetaObject *g = g_igCharMetaField_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_002cc160();
    return g_igCharMetaField_metaObject[0];
}

int igCharMetaField_GetVTable(void) {
    union U_2cc0e0 u;
    int temp_s0;
    char *ps;
    int *temp_v1;
    int *temp_a1;
    int temp_v0;

    FUN_002d4da0((int **)u.b);
    temp_s0 = *(int *)&u.b[*(int *)((char *)(((void * *)g_objectSystem)[0]) + 916)];
    u.vt = (int)&g_igMetaField_vtable[0];
    ps = &u.b[12];
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

void FUN_002cc160(void)
{
    igMetaObject_RunStaticInit((StaticInitCallbacks * (*)())igCharMetaField_Register);
}

void igCharMetaField_Register(void) {
    igMetaObject_RegisterClass(
        0, /* abstract */
        ((char *)g_igCharMetaField_metaObject),
        igMetaField_Register,
        igMetaField_GetPublishedMetaObject,
        thunk_igCharMetaField_GetMetaObject,
        igCharMetaField_className,
        0x34, /* instance size */
        igCharMetaField_GetVTable,
        0,
        0, /* extra callback item */
        g_igCharMetaField_callbackList /* callback list */
    );
}

void thunk_igCharMetaField_GetMetaObject(void) {
    igCharMetaField_GetMetaObject();
}

void FUN_002cc1f0(void) {
    void *temp_s0;

    if (DAT_00586938[0] == 0) {
        DAT_00586938[0] = (void *)(((void *)igMetaObject_CreateInstance((CreateMeta *)g_igCharMetaField_metaObject[0], (MemoryPool *)(((int)Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData))))));
        temp_s0 = (void *)(DAT_00586938[0]);
        if (temp_s0 != 0) {
            MetaRefList_AppendRetained((PointerList *)(((void *)FUN_002fc250())), (RefHeader *)temp_s0);
            {
                void *held = (void *)DAT_00586938[0];
                *(int *)((char *)(held) + 4) = *(int *)((char *)(held) + 4) - 1;
                if (((unsigned long long) ((long long) *(int *)((char *)(held) + 4) << 0x29) >> 0x29) == 0) {
                    igObject_Destroy(held);
                }
            }
            *(short *)((char *)(DAT_00586938[0]) + 18) = (short) (*(int *)((char *)(((void *)FUN_002fc250())) + 12) - 1);
            igMetaField_FinalizeDescriptor((igMetaField *)DAT_00586938[0]);
        }
    }
}

int FUN_002cc2c0(void) {
    if (((int *)DAT_00586938)[0] == 0) {
        FUN_002cc160();
    }
    return ((int *)DAT_00586938)[0];
}

