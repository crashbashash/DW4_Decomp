void **FUN_002b9f90(int arg0) {
    void **var_s0;

    if (*g_objectSystem[0] != 0) {
        igShortMetaField_EnsureRegistered();
        var_s0 = (void **)(((void **)igMetaObject_CreateInstance((CreateMeta *)g_igShortMetaField_metaObject[0], (MemoryPool *)arg0)));
    } else {
        var_s0 = (void **)(((void **)igObject_AllocateRawStorage(0x34, 0, (void **)arg0)));
        if (var_s0 != 0) {
            var_s0 = (void **)(((void **)FUN_0030a440((int **)var_s0, 1)));
        }
        ((DW4VC_44_0 *)(var_s0))->vX();
        ((DW4VC_36_1 *)(var_s0))->vX((int)(0));
    }
    return var_s0;
}

int Gap__Core__igShortMetaField__vfunc_21(int arg0, int arg1) {
    int p;

    if (*g_objectSystem[0] != 0) {
        igShortMetaField_EnsureRegistered();
        return igObject_CloneViaMetadata((void **)arg0, arg1);
    }
    p = ((int)igObject_AllocateRawStorageDefault(0x34, 0));
    if (p != 0) {
        p = ((int)FUN_0030a4c0((int **)p, arg0));
    }
    return p;
}

igMetaObject *igShortMetaField_GetMetaObject(void)
{
    igMetaObject *g = g_igShortMetaField_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        igShortMetaField_EnsureRegistered();
    return g_igShortMetaField_metaObject[0];
}

int igShortMetaField_GetVTable(void) {
    struct Obj_2ba100 obj;
    char *o;
    int *a1;
    int v0;
    int t;
    FUN_0030a480((int **)&obj);
    t = *(int *)((char *)&obj + *(int *)((char *)(((void * *)g_objectSystem)[0]) + 916));
    obj.vt = &g_igMetaField_vtable[0];
    if (&obj.m != 0) {
        o = obj.m;
        if (o != 0) {
            a1 = (int *)(o - 8);
            v0 = *(int *)(o - 4) - 1;
            *(int *)(o - 4) = v0;
            if (v0 == 0) {
                StringChunk_ReleaseHeader((StringChunkOwnerView *)(*a1), (int)a1);
            }
        }
    }
    return t;
}

void igShortMetaField_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit((StaticInitCallbacks * (*)())igShortMetaField_Register);
}

void igShortMetaField_Register(void) {
    igMetaObject_RegisterClass(
        0, /* abstract */
        ((char *)g_igShortMetaField_metaObject),
        igMetaField_Register,
        igMetaField_GetPublishedMetaObject,
        thunk_igShortMetaField_GetMetaObject,
        igShortMetaField_className,
        0x34, /* instance size */
        igShortMetaField_GetVTable,
        0,
        0, /* extra callback item */
        g_igShortMetaField_callbackList /* callback list */
    );
}

void thunk_igShortMetaField_GetMetaObject(void) {
    igShortMetaField_GetMetaObject();
}

void FUN_002ba210(void) {
    void *temp_s0;

    if (g_igShortMetaField_descriptor[0] == 0) {
        g_igShortMetaField_descriptor[0] = (void *)(((void *)igMetaObject_CreateInstance((CreateMeta *)g_igShortMetaField_metaObject[0], (MemoryPool *)(((int)Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData))))));
        temp_s0 = (void *)(g_igShortMetaField_descriptor[0]);
        if (temp_s0 != 0) {
            MetaRefList_AppendRetained((PointerList *)(((void *)FUN_002fc250())), (RefHeader *)temp_s0);
            {
                void *held = (void *)g_igShortMetaField_descriptor[0];
                *(int *)((char *)(held) + 4) = *(int *)((char *)(held) + 4) - 1;
                if (((unsigned long long) ((long long) *(int *)((char *)(held) + 4) << 0x29) >> 0x29) == 0) {
                    igObject_Destroy(held);
                }
            }
            *(short *)((char *)(g_igShortMetaField_descriptor[0]) + 18) = (short) (*(int *)((char *)(((void *)FUN_002fc250())) + 12) - 1);
            igMetaField_FinalizeDescriptor((igMetaField *)g_igShortMetaField_descriptor[0]);
        }
    }
}

int igShortMetaField_GetDefaultDescriptor(void) {
    if (((int *)g_igShortMetaField_descriptor)[0] == 0) {
        igShortMetaField_EnsureRegistered();
    }
    return ((int *)g_igShortMetaField_descriptor)[0];
}

