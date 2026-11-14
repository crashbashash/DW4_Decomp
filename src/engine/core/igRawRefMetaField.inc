void **igRawRefMetaField_Create(int arg0) {
    void **var_s0;

    if (*g_objectSystem[0] != 0) {
        igRawRefMetaField_EnsureRegistered();
        var_s0 = (void **)(((void **)igMetaObject_CreateInstance((igMetaObject *)g_igRawRefMetaField_metaObject[0], (igMemoryPoolView *)arg0)));
    } else {
        var_s0 = (void **)(((void **)igObject_AllocateRawStorage(0x38, 0, (igMemoryPoolView *)arg0)));
        if (var_s0 != 0) {
            var_s0 = (void **)(((void **)igRawRefMetaField_Construct((int **)var_s0, 1)));
        }
        ((igObjectDispatchView *)(var_s0))->vfunc_09();
        ((igObjectDispatchView *)(var_s0))->userConstruct((int)(0));
    }
    return var_s0;
}

int igRawRefMetaField_Clone(int arg0, int arg1) {
    int temp_v0;

    if (*g_objectSystem[0] != 0) {
        igRawRefMetaField_EnsureRegistered();
        return igObject_CloneViaMetadata((void **)arg0, arg1);
    }
    temp_v0 = ((int)igObject_AllocateRawStorageDefault(0x38, 0));
    if (temp_v0 != 0) {
        temp_v0 = ((int)igRawRefMetaField_CopyConstruct((int **)temp_v0, arg0));
    }
    return temp_v0;
}

igMetaObject *igRawRefMetaField_GetOrCreateMetaObject(void) {
    if (g_igRawRefMetaField_metaObject[0] == 0) {
        g_igRawRefMetaField_metaObject[0] = (igMetaObject *)igMetaObject_Create(((int)Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData)));
    }
    return g_igRawRefMetaField_metaObject[0];
}

igMetaObject *igRawRefMetaField_GetMetaObject(void)
{
    igMetaObject *g = g_igRawRefMetaField_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        igRawRefMetaField_EnsureRegistered();
    return g_igRawRefMetaField_metaObject[0];
}

int igRawRefMetaField_GetVTable(void) {
    igRawRefMetaField o;
    int r;
    int *temp_a1;
    int temp_v0;
    void *temp_v1;

    igRawRefMetaField_Init((int **)&o);
    r = *(int *)((char *)&o + *(int *)((char *)(((void * *)g_objectSystem)[0]) + 916));
    o._vtable = (int)&g_igMetaField_vtable[0];
    if (&o._fieldName != 0) {
        temp_v1 = (char *)o._fieldName;
        if (temp_v1 != 0) {
            temp_a1 = (int *)((char *)temp_v1 - 8);
            temp_v0 = *(int *)((char *)(temp_v1) - 4) - 1;
            *(int *)((char *)(temp_v1) - 4) = temp_v0;
            if (temp_v0 == 0) {
                StringChunk_ReleaseHeader((StringChunk *)(*temp_a1), (int)temp_a1);
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
        igRawRefMetaField_GetMetaObjectFunction,
        igRawRefMetaField_className,
        0x38, /* instance size */
        igRawRefMetaField_GetVTable,
        0,
        0, /* extra callback item */
        g_igRawRefMetaField_callbackList /* callback list */
    );
}

void igRawRefMetaField_GetMetaObjectFunction(void) {
    igRawRefMetaField_GetMetaObject();
}

void igRawRefMetaField_CreateDefaultDescriptor(void) {
    void *temp_s0;

    if (g_igRawRefMetaField_descriptor[0] == 0) {
        g_igRawRefMetaField_descriptor[0] = (void *)(((void *)igMetaObject_CreateInstance((igMetaObject *)g_igRawRefMetaField_metaObject[0], (igMemoryPoolView *)(((int)Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData))))));
        temp_s0 = (void *)(g_igRawRefMetaField_descriptor[0]);
        if (temp_s0 != 0) {
            MetaRefList_AppendRetained(igMetaField_GetMetaFieldList(), (igObject *)temp_s0);
            {
                void *held = (void *)g_igRawRefMetaField_descriptor[0];
                *(int *)((char *)(held) + 4) = *(int *)((char *)(held) + 4) - 1;
                if (((unsigned long long) ((long long) *(int *)((char *)(held) + 4) << 0x29) >> 0x29) == 0) {
                    igObject_Destroy(held);
                }
            }
            *(short *)((char *)(g_igRawRefMetaField_descriptor[0]) + 18) = (short) (*(int *)((char *)(((void *)igMetaField_GetMetaFieldList())) + 12) - 1);
            igMetaField_FinalizeDescriptor((igMetaField *)g_igRawRefMetaField_descriptor[0]);
        }
    }
}

int igRawRefMetaField_GetDefaultDescriptor(void) {
    if (((int *)g_igRawRefMetaField_descriptor)[0] == 0) {
        igRawRefMetaField_EnsureRegistered();
    }
    return ((int *)g_igRawRefMetaField_descriptor)[0];
}

