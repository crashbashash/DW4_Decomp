void **FUN_002bba00(int arg0) {
    void **var_s0;

    if (*DAT_00586dc8[0] != 0) {
        igRawRefMetaField_EnsureRegistered();
        var_s0 = (void **)(((void **)igMetaObject_CreateInstance((CreateMeta *)DAT_00585a80[0], (MemoryPool *)arg0)));
    } else {
        var_s0 = (void **)(((void **)igObject_AllocateRawStorage(0x38, 0, (void **)arg0)));
        if (var_s0 != 0) {
            var_s0 = (void **)(((void **)FUN_00305400((int **)var_s0, 1)));
        }
        ((DW4VC_44_0 *)(var_s0))->vX();
        ((DW4VC_36_1 *)(var_s0))->vX((int)(0));
    }
    return var_s0;
}

int Gap__Core__igRawRefMetaField__vfunc_21(int arg0, int arg1) {
    int temp_v0;

    if (*DAT_00586dc8[0] != 0) {
        igRawRefMetaField_EnsureRegistered();
        return igObject_CloneViaMetadata((void **)arg0, arg1);
    }
    temp_v0 = ((int)igObject_AllocateRawStorageDefault(0x38, 0));
    if (temp_v0 != 0) {
        temp_v0 = ((int)FUN_00305480((int **)temp_v0, arg0));
    }
    return temp_v0;
}

int FUN_002bbb20(void) {
    if (DAT_00585a80[0] == 0) {
        DAT_00585a80[0] = ((int)igMetaObject_Create(((int)Memory_GetAllocatorBySelector(DAT_00587040[0]))));
    }
    return DAT_00585a80[0];
}

igMetaObject *igRawRefMetaField_GetMetaObject(void)
{
    igMetaObject *g = g_igRawRefMetaField_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        igRawRefMetaField_EnsureRegistered();
    return g_igRawRefMetaField_metaObject[0];
}

int igRawRefMetaField_GetVTable(void) {
    Obj_2bbbc0 o;
    int r;
    int *temp_a1;
    int temp_v0;
    void *temp_v1;

    FUN_00305440((int **)&o);
    r = *(int *)((char *)&o + *(int *)((char *)(((void * *)DAT_00586dc8)[0]) + 916));
    o.vt = &DAT_0052f230[0];
    if (&o.str != 0) {
        temp_v1 = o.str;
        if (temp_v1 != 0) {
            temp_a1 = (int *)((char *)temp_v1 - 8);
            temp_v0 = *(int *)((char *)(temp_v1) - 4) - 1;
            *(int *)((char *)(temp_v1) - 4) = temp_v0;
            if (temp_v0 == 0) {
                StringChunk_ReleaseHeader((StringChunkOwnerView *)(*temp_a1), (int)temp_a1);
            }
        }
    }
    return r;
}

void igRawRefMetaField_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit((StaticInitCallbacks * (*)())igRawRefMetaField_Register);
}

void igRawRefMetaField_Register(void) {
    igMetaObject_RegisterClass(
        0, /* abstract */
        ((char *)g_igRawRefMetaField_metaObject),
        igRefMetaField_Register,
        igRefMetaField_GetPublishedMetaObject,
        thunk_igRawRefMetaField_GetMetaObject,
        igRawRefMetaField_className,
        0x38, /* instance size */
        igRawRefMetaField_GetVTable,
        0,
        0, /* extra callback item */
        g_igRawRefMetaField_callbackList /* callback list */
    );
}

void thunk_igRawRefMetaField_GetMetaObject(void) {
    igRawRefMetaField_GetMetaObject();
}

void FUN_002bbcd0(void) {
    void *temp_s0;

    if (DAT_00585a88[0] == 0) {
        DAT_00585a88[0] = (void *)(((void *)igMetaObject_CreateInstance((CreateMeta *)DAT_00585a80[0], (MemoryPool *)(((int)Memory_GetAllocatorBySelector(DAT_00587040[0]))))));
        temp_s0 = (void *)(DAT_00585a88[0]);
        if (temp_s0 != 0) {
            MetaRefList_AppendRetained((PointerList *)(((void *)FUN_002fc250())), (RefHeader *)temp_s0);
            {
                void *held = (void *)DAT_00585a88[0];
                *(int *)((char *)(held) + 4) = *(int *)((char *)(held) + 4) - 1;
                if (((unsigned long long) ((long long) *(int *)((char *)(held) + 4) << 0x29) >> 0x29) == 0) {
                    igObject_Destroy(held);
                }
            }
            *(short *)((char *)(DAT_00585a88[0]) + 18) = (short) (*(int *)((char *)(((void *)FUN_002fc250())) + 12) - 1);
            igMetaField_FinalizeDescriptor((igMetaField *)DAT_00585a88[0]);
        }
    }
}

int igRawRefMetaField_GetDefaultDescriptor(void) {
    if (((int *)DAT_00585a88)[0] == 0) {
        igRawRefMetaField_EnsureRegistered();
    }
    return ((int *)DAT_00585a88)[0];
}

