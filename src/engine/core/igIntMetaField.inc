/* Same factory shape for an igIntMetaField (52-byte instance). */
void **igIntMetaField_Create(int allocator) {
    void **field;

    if (*g_objectSystem[0] != 0) {
        igIntMetaField_EnsureRegistered();
        field = ((void **)igMetaObject_CreateInstance((igMetaObject *)(((int *)g_igIntMetaField_metaObject)[0]), (igMemoryPoolView *)allocator));
    } else {
        field = ((void **)igObject_AllocateRawStorage(0x34, 0, (igMemoryPoolView *)allocator));
        if (field != 0) {
            field = ((void **)igIntMetaField_Construct((igMetaField *)field, 1));
        }
        ((igObjectDispatchView *)field)->vfunc_09();
        ((igObjectDispatchView *)field)->userConstruct(0);
    }
    return field;
}

void *Gap__Core__igIntMetaField__vfunc_21(void *self, void *src) {
    void *o;
    if (*g_objectSystem[0] != 0) {
        igIntMetaField_EnsureRegistered();
        return ((void *)igObject_CloneViaMetadata((void **)self, (int)src));
    }
    o = igObject_AllocateRawStorageDefault(0x34, 0);
    if (o != 0) {
        o = ((void *)FUN_002ea460((int **)o, (int)self));
    }
    return o;
}

igMetaObject *FUN_002c2e10(void) {
    if (g_igIntMetaField_metaObject[0] == 0) {
        g_igIntMetaField_metaObject[0] = (igMetaObject *)igMetaObject_Create(((int)Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData)));
    }
    return g_igIntMetaField_metaObject[0];
}

igMetaObject *igIntMetaField_GetMetaObject(void)
{
    igMetaObject *g = g_igIntMetaField_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        igIntMetaField_EnsureRegistered();
    return g_igIntMetaField_metaObject[0];
}

int igIntMetaField_GetVTable(void) {
    igIntMetaField u;
    int temp_s0;
    char *ps;
    int *temp_v1;
    int *temp_a1;
    int temp_v0;

    FUN_002ea420((char *)&u);
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

void igIntMetaField_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit((StaticInitCallbacks * (*)())igIntMetaField_Register);
}

void igIntMetaField_Register(void) {
    igMetaObject_RegisterClass(
        0, /* abstract */
        ((char *)g_igIntMetaField_metaObject),
        igMetaField_Register,
        igMetaField_GetPublishedMetaObject,
        thunk_igIntMetaField_GetMetaObject,
        igIntMetaField_className,
        0x34, /* instance size */
        igIntMetaField_GetVTable,
        0,
        0, /* extra callback item */
        g_igIntMetaField_callbackList /* callback list */
    );
}

void thunk_igIntMetaField_GetMetaObject(void) {
    igIntMetaField_GetMetaObject();
}

void FUN_002c2fc0(void) {
    void *temp_s0;

    if (g_igIntMetaField_descriptor[0] == 0) {
        g_igIntMetaField_descriptor[0] = (void *)(((void *)igMetaObject_CreateInstance((igMetaObject *)g_igIntMetaField_metaObject[0], (igMemoryPoolView *)(((int)Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData))))));
        temp_s0 = (void *)(g_igIntMetaField_descriptor[0]);
        if (temp_s0 != 0) {
            MetaRefList_AppendRetained(FUN_002fc250(), (igObject *)temp_s0);
            {
                void *held = (void *)g_igIntMetaField_descriptor[0];
                *(int *)((char *)(held) + 4) = *(int *)((char *)(held) + 4) - 1;
                if (((unsigned long long) ((long long) *(int *)((char *)(held) + 4) << 0x29) >> 0x29) == 0) {
                    igObject_Destroy(held);
                }
            }
            *(short *)((char *)(g_igIntMetaField_descriptor[0]) + 18) = (short) (*(int *)((char *)(((void *)FUN_002fc250())) + 12) - 1);
            igMetaField_FinalizeDescriptor((igMetaField *)g_igIntMetaField_descriptor[0]);
        }
    }
}

int igIntMetaField_GetDefaultDescriptor(void) {
    if (g_igIntMetaField_descriptor[0] == 0) {
        igIntMetaField_EnsureRegistered();
    }
    return (int)g_igIntMetaField_descriptor[0];
}

