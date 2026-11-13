void **igUnsignedIntMetaField_Create(int allocator) {
    void **field;

    if (*g_objectSystem[0] != 0) {
        igUnsignedIntMetaField_EnsureRegistered();
        field = (void **)(((void **)igMetaObject_CreateInstance((CreateMeta *)(((int *)g_igUnsignedIntMetaField_metaObject)[0]), (MemoryPool *)allocator)));
    } else {
        field = (void **)(((void **)igObject_AllocateRawStorage(0x34, 0, (void **)allocator)));
        if (field != 0) {
            field = (void **)(((void **)igUnsignedIntMetaField_Construct((igMetaField *)field, 1)));
        }
        ((igObjectSlot09 *)(field))->vfunc_09();
        ((igObjectSlot07 *)(field))->vfunc_07((int)(0));
    }
    return field;
}

int Gap__Core__igUnsignedIntMetaField__vfunc_21(int arg0, int arg1) {
    int temp_v0;

    if (*g_objectSystem[0] != 0) {
        igUnsignedIntMetaField_EnsureRegistered();
        return igObject_CloneViaMetadata((void **)arg0, arg1);
    }
    temp_v0 = ((int)igObject_AllocateRawStorageDefault(0x34, 0));
    if (temp_v0 != 0) {
        temp_v0 = ((int)FUN_0030e960((int **)temp_v0, arg0));
    }
    return temp_v0;
}

igMetaObject *igUnsignedIntMetaField_GetMetaObject(void)
{
    igMetaObject *g = g_igUnsignedIntMetaField_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        igUnsignedIntMetaField_EnsureRegistered();
    return g_igUnsignedIntMetaField_metaObject[0];
}

int igUnsignedIntMetaField_GetVTable(void) {
    union U_2b6e90 u;
    int *temp_a1;
    int temp_s0;
    int temp_v0;
    void *temp_v1;

    igUnsignedIntMetaField_Init((igMetaField *)u.b);
    temp_s0 = *(int *)&u.b[*(int *)((char *)(((void * *)g_objectSystem)[0]) + 916)];
    u.w[0] = (int)(&g_igMetaField_vtable[0]);
    if (&u.p[3] != 0) {
        temp_v1 = (void *)(u.p[3]);
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

void igUnsignedIntMetaField_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit((StaticInitCallbacks * (*)())igUnsignedIntMetaField_Register);
}

void igUnsignedIntMetaField_Register(void) {
    igMetaObject_RegisterClass(
        0, /* abstract */
        ((char *)g_igUnsignedIntMetaField_metaObject),
        igMetaField_Register,
        igMetaField_GetPublishedMetaObject,
        thunk_igUnsignedIntMetaField_GetMetaObject,
        igUnsignedIntMetaField_className,
        0x34, /* instance size */
        igUnsignedIntMetaField_GetVTable,
        0,
        0, /* extra callback item */
        g_igUnsignedIntMetaField_callbackList /* callback list */
    );
}

void thunk_igUnsignedIntMetaField_GetMetaObject(void) {
    igUnsignedIntMetaField_GetMetaObject();
}

void FUN_002b6fa0(void) {
    void *temp_s0;

    if (g_igUnsignedIntMetaField_descriptor[0] == 0) {
        g_igUnsignedIntMetaField_descriptor[0] = (void *)(((void *)igMetaObject_CreateInstance((CreateMeta *)g_igUnsignedIntMetaField_metaObject[0], (MemoryPool *)(((int)Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData))))));
        temp_s0 = (void *)(g_igUnsignedIntMetaField_descriptor[0]);
        if (temp_s0 != 0) {
            MetaRefList_AppendRetained((PointerList *)(((void *)FUN_002fc250())), (RefHeader *)temp_s0);
            {
                void *held = (void *)g_igUnsignedIntMetaField_descriptor[0];
                *(int *)((char *)(held) + 4) = *(int *)((char *)(held) + 4) - 1;
                if (((unsigned long long) ((long long) *(int *)((char *)(held) + 4) << 0x29) >> 0x29) == 0) {
                    igObject_Destroy(held);
                }
            }
            *(short *)((char *)(g_igUnsignedIntMetaField_descriptor[0]) + 18) = (short) (*(int *)((char *)(((void *)FUN_002fc250())) + 12) - 1);
            igMetaField_FinalizeDescriptor((igMetaField *)g_igUnsignedIntMetaField_descriptor[0]);
        }
    }
}

int igUnsignedIntMetaField_GetDefaultDescriptor(void) {
    if (((int *)g_igUnsignedIntMetaField_descriptor)[0] == 0) {
        igUnsignedIntMetaField_EnsureRegistered();
    }
    return ((int *)g_igUnsignedIntMetaField_descriptor)[0];
}

