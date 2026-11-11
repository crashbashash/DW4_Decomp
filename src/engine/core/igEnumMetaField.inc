void **FUN_002c5fb0(int arg0) {
    void **var_s0;

    if (*DAT_00586dc8[0] != 0) {
        igEnumMetaField_EnsureRegistered();
        var_s0 = (void **)(((void **)igMetaObject_CreateInstance((CreateMeta *)DAT_00586598[0], (MemoryPool *)arg0)));
    } else {
        var_s0 = (void **)(((void **)igObject_AllocateRawStorage(0x38, 0, (void **)arg0)));
        if (var_s0 != 0) {
            var_s0 = (void **)(((void **)FUN_002dc8c0((int **)var_s0, 1)));
        }
        ((DW4VC_44_0 *)(var_s0))->vX();
        ((DW4VC_36_1 *)(var_s0))->vX((int)(0));
    }
    return var_s0;
}

int Gap__Core__igEnumMetaField__vfunc_21(int arg0, int arg1) {
    int temp_v0;

    if (*DAT_00586dc8[0] != 0) {
        igEnumMetaField_EnsureRegistered();
        return igObject_CloneViaMetadata((void **)arg0, arg1);
    }
    temp_v0 = ((int)igObject_AllocateRawStorageDefault(0x38, 0));
    if (temp_v0 != 0) {
        temp_v0 = ((int)FUN_002dc940((int **)temp_v0, arg0));
    }
    return temp_v0;
}

igMetaObject *igEnumMetaField_GetMetaObject(void)
{
    igMetaObject *g = g_igEnumMetaField_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        igEnumMetaField_EnsureRegistered();
    return g_igEnumMetaField_metaObject[0];
}

int igEnumMetaField_GetVTable(void) {
    Obj_2c6120 o;
    int *temp_a1;
    int temp_s0;
    int temp_v0;
    void *temp_v1;

    FUN_002dc900((int **)&o);
    temp_s0 = *(int *)((char *)&o + *(int *)((char *)(((void * *)DAT_00586dc8)[0]) + 916));
    o.vt = &DAT_0052f230[0];
    if (&o.str != 0) {
        temp_v1 = (void *)(o.str);
        if (temp_v1 != 0) {
            temp_a1 = (int *)((char *)temp_v1 - 8);
            temp_v0 = *(int *)((char *)(temp_v1) - 4) - 1;
            *(int *)((char *)(temp_v1) - 4) = temp_v0;
            if (temp_v0 == 0) {
                StringChunk_ReleaseHeader((StringChunkOwnerView *)(*temp_a1), (int)temp_a1);
            }
        }
    }
    return temp_s0;
}

void igEnumMetaField_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit((StaticInitCallbacks * (*)())igEnumMetaField_Register);
}

void igEnumMetaField_Register(void) {
    igMetaObject_RegisterClass(
        0, /* abstract */
        ((char *)g_igEnumMetaField_metaObject),
        igMetaField_Register,
        igMetaField_GetPublishedMetaObject,
        thunk_igEnumMetaField_GetMetaObject,
        igEnumMetaField_className,
        0x38, /* instance size */
        igEnumMetaField_GetVTable,
        &igEnumMetaField_InitFields,
        0, /* extra callback item */
        g_igEnumMetaField_callbackList /* callback list */
    );
}

void thunk_igEnumMetaField_GetMetaObject(void) {
    igEnumMetaField_GetMetaObject();
}

void igEnumMetaField_InitFields(void) {
    int temp_s1;
    void *temp_s0;

    temp_s0 = (void *)DAT_00586598[0];
    temp_s1 = igMetaObject_GetFieldCount((igMetaObject *)temp_s0);
    igMetaObject_CreateFields((igMetaObject *)temp_s0, (igMetaField * (**)(void *))&DAT_004c0f70[0], 1);
    *(char *)((char *)(((void *)igMetaObject_GetFieldAt((igMetaObject *)temp_s0, temp_s1))) + 38) = 0;
    igMetaObject_NameFields((igMetaObject *)temp_s0, (const char **)&DAT_004c0f78[0], (igMetaField ***)&DAT_004c0f80[0], &DAT_004c0f88[0], temp_s1);
}

void FUN_002c62b0(void) {
    int *s0;
    int *o;
    int count;

    if (DAT_005865a0[0] == 0) {
        DAT_005865a0[0] = ((int *)igMetaObject_CreateInstance((CreateMeta *)DAT_00586598[0], (MemoryPool *)(((int)Memory_GetAllocatorBySelector(DAT_00587040[0])))));
        s0 = DAT_005865a0[0];
        if (s0 != 0) {
            MetaRefList_AppendRetained((PointerList *)(((void *)FUN_002fc250())), (RefHeader *)s0);
            o = DAT_005865a0[0];
            o[1] = o[1] - 1;
            if ((o[1] & 0x7FFFFF) == 0) {
                igObject_Destroy(o);
            }
            count = *(int *)((char *)((void *)FUN_002fc250()) + 12); /* Read as a whole word first; a direct `short = int - 1` store would be narrowed to an lh. */
            *(short *)((char *)DAT_005865a0[0] + 18) = count - 1;
            igMetaField_FinalizeDescriptor((igMetaField *)DAT_005865a0[0]);
        }
    }
}

int igEnumMetaField_GetDefaultDescriptor(void) {
    if (((int *)DAT_005865a0)[0] == 0) {
        igEnumMetaField_EnsureRegistered();
    }
    return ((int *)DAT_005865a0)[0];
}

