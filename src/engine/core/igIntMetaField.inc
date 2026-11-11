/* Same factory shape for an igIntMetaField (52-byte instance). */
void **igIntMetaField_Create(int allocator) {
    void **field;

    if (*g_objectSystem[0] != 0) {
        igIntMetaField_EnsureRegistered();
        field = ((void **)igMetaObject_CreateInstance((CreateMeta *)(((int *)g_igIntMetaField_metaObject)[0]), (MemoryPool *)allocator));
    } else {
        field = ((void **)igObject_AllocateRawStorage(0x34, 0, (void **)allocator));
        if (field != 0) {
            field = ((void **)igIntMetaField_Construct((igMetaField *)field, 1));
        }
        ((igObjectSlot09_2b9750 *)field)->vfunc_09();
        ((igObjectSlot07_2b9750 *)field)->vfunc_07(0);
    }
    return field;
}

void *Gap__Core__igIntMetaField__vfunc_21(void *self, void *src) {
    void *o;
    if (*DAT_00586dc8[0] != 0) {
        igIntMetaField_EnsureRegistered();
        return ((void *)igObject_CloneViaMetadata((void **)self, (int)src));
    }
    o = igObject_AllocateRawStorageDefault(0x34, 0);
    if (o != 0) {
        o = ((void *)FUN_002ea460((int **)o, (int)self));
    }
    return o;
}

int FUN_002c2e10(void) {
    if (DAT_005860f8[0] == 0) {
        DAT_005860f8[0] = ((int)igMetaObject_Create(((int)Memory_GetAllocatorBySelector(DAT_00587040[0]))));
    }
    return DAT_005860f8[0];
}

igMetaObject *igIntMetaField_GetMetaObject(void)
{
    igMetaObject *g = g_igIntMetaField_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        igIntMetaField_EnsureRegistered();
    return g_igIntMetaField_metaObject[0];
}

int igIntMetaField_GetVTable(void) {
    union U_2c2eb0 u;
    int temp_s0;
    char *ps;
    int *temp_v1;
    int *temp_a1;
    int temp_v0;

    FUN_002ea420(u.b);
    temp_s0 = *(int *)&u.b[*(int *)((char *)(((void * *)DAT_00586dc8)[0]) + 916)];
    u.vt = (int)&DAT_0052f230[0];
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

    if (DAT_00586100[0] == 0) {
        DAT_00586100[0] = (void *)(((void *)igMetaObject_CreateInstance((CreateMeta *)DAT_005860f8[0], (MemoryPool *)(((int)Memory_GetAllocatorBySelector(DAT_00587040[0]))))));
        temp_s0 = (void *)(DAT_00586100[0]);
        if (temp_s0 != 0) {
            MetaRefList_AppendRetained((PointerList *)(((void *)FUN_002fc250())), (RefHeader *)temp_s0);
            {
                void *held = (void *)DAT_00586100[0];
                *(int *)((char *)(held) + 4) = *(int *)((char *)(held) + 4) - 1;
                if (((unsigned long long) ((long long) *(int *)((char *)(held) + 4) << 0x29) >> 0x29) == 0) {
                    igObject_Destroy(held);
                }
            }
            *(short *)((char *)(DAT_00586100[0]) + 18) = (short) (*(int *)((char *)(((void *)FUN_002fc250())) + 12) - 1);
            igMetaField_FinalizeDescriptor((igMetaField *)DAT_00586100[0]);
        }
    }
}

int igIntMetaField_GetDefaultDescriptor(void) {
    if (g_igIntMetaField_descriptor[0] == 0) {
        igIntMetaField_EnsureRegistered();
    }
    return g_igIntMetaField_descriptor[0];
}

