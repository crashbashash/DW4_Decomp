void **FUN_002b66a0(int arg0) {
    void **var_s0;

    if (*g_objectSystem[0] != 0) {
        FUN_002b6890();
        var_s0 = (void **)(((void **)igMetaObject_CreateInstance((CreateMeta *)g_igUnsignedLongMetaField_metaObject[0], (MemoryPool *)arg0)));
    } else {
        var_s0 = (void **)(((void **)igObject_AllocateRawStorage(0x34, 0, (void **)arg0)));
        if (var_s0 != 0) {
            var_s0 = (void **)(((void **)FUN_0030eb40((int **)var_s0, 1)));
        }
        ((DW4VC_44_0 *)(var_s0))->vX();
        ((DW4VC_36_1 *)(var_s0))->vX((int)(0));
    }
    return var_s0;
}

int Gap__Core__igUnsignedLongMetaField__vfunc_21(int arg0, int arg1) {
    int temp_v0;

    if (*g_objectSystem[0] != 0) {
        FUN_002b6890();
        return igObject_CloneViaMetadata((void **)arg0, arg1);
    }
    temp_v0 = ((int)igObject_AllocateRawStorageDefault(0x34, 0));
    if (temp_v0 != 0) {
        temp_v0 = ((int)FUN_0030ebc0((int **)temp_v0, arg0));
    }
    return temp_v0;
}

igMetaObject *igUnsignedLongMetaField_GetMetaObject(void)
{
    igMetaObject *g = g_igUnsignedLongMetaField_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_002b6890();
    return g_igUnsignedLongMetaField_metaObject[0];
}

int igUnsignedLongMetaField_GetVTable(void) {
    union U_2b6810 u;
    int temp_s0;
    char *ps;
    int *temp_v1;
    int *temp_a1;
    int temp_v0;

    FUN_0030eb80((int **)u.b);
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

void FUN_002b6890(void)
{
    igMetaObject_RunStaticInit((StaticInitCallbacks * (*)())igUnsignedLongMetaField_Register);
}

void igUnsignedLongMetaField_Register(void) {
    igMetaObject_RegisterClass(
        0, /* abstract */
        ((char *)g_igUnsignedLongMetaField_metaObject),
        igMetaField_Register,
        igMetaField_GetPublishedMetaObject,
        thunk_igUnsignedLongMetaField_GetMetaObject,
        igUnsignedLongMetaField_className,
        0x34, /* instance size */
        igUnsignedLongMetaField_GetVTable,
        0,
        0, /* extra callback item */
        g_igUnsignedLongMetaField_callbackList /* callback list */
    );
}

void thunk_igUnsignedLongMetaField_GetMetaObject(void) {
    igUnsignedLongMetaField_GetMetaObject();
}

void FUN_002b6920(void) {
    void *temp_s0;

    if (DAT_00585718[0] == 0) {
        DAT_00585718[0] = (void *)(((void *)igMetaObject_CreateInstance((CreateMeta *)g_igUnsignedLongMetaField_metaObject[0], (MemoryPool *)(((int)Memory_GetAllocatorBySelector(g_metadataAllocatorKey[0]))))));
        temp_s0 = (void *)(DAT_00585718[0]);
        if (temp_s0 != 0) {
            MetaRefList_AppendRetained((PointerList *)(((void *)FUN_002fc250())), (RefHeader *)temp_s0);
            {
                void *held = (void *)DAT_00585718[0];
                *(int *)((char *)(held) + 4) = *(int *)((char *)(held) + 4) - 1;
                if (((unsigned long long) ((long long) *(int *)((char *)(held) + 4) << 0x29) >> 0x29) == 0) {
                    igObject_Destroy(held);
                }
            }
            *(short *)((char *)(DAT_00585718[0]) + 18) = (short) (*(int *)((char *)(((void *)FUN_002fc250())) + 12) - 1);
            igMetaField_FinalizeDescriptor((igMetaField *)DAT_00585718[0]);
        }
    }
}

int FUN_002b69f0(void) {
    if (((int *)DAT_00585718)[0] == 0) {
        FUN_002b6890();
    }
    return ((int *)DAT_00585718)[0];
}

