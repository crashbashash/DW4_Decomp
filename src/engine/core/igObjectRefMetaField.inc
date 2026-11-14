/* Same factory shape for an igObjectRefMetaField (68-byte instance). */
void **igObjectRefMetaField_Create(int allocator) {
    void **field;

    if (*g_objectSystem[0] != 0) {
        igObjectRefMetaField_EnsureRegistered();
        field = ((void **)igMetaObject_CreateInstance((igMetaObject *)(((int *)g_igObjectRefMetaField_metaObject)[0]), (igMemoryPoolView *)allocator));
    } else {
        field = ((void **)igObject_AllocateRawStorage(0x44, 0, (igMemoryPoolView *)allocator));
        if (field != 0) {
            field = ((void **)igObjectRefMetaField_Construct((igObjectRefMetaField *)field, 1));
        }
        ((igObjectDispatchView *)field)->vfunc_09();
        ((igObjectDispatchView *)field)->userConstruct(0);
    }
    return field;
}

int Gap__Core__igObjectRefMetaField__vfunc_21(int arg0, int arg1) {
    int temp_v0;

    if (*g_objectSystem[0] != 0) {
        igObjectRefMetaField_EnsureRegistered();
        return igObject_CloneViaMetadata((void **)arg0, arg1);
    }
    temp_v0 = ((int)igObject_AllocateRawStorageDefault(0x44, 0));
    if (temp_v0 != 0) {
        temp_v0 = ((int)FUN_00303c60((igObjectRefMetaField *)temp_v0, (void *)arg0));
    }
    return temp_v0;
}

igMetaObject *igObjectRefMetaField_GetMetaObject(void)
{
    igMetaObject *g = g_igObjectRefMetaField_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        igObjectRefMetaField_EnsureRegistered();
    return g_igObjectRefMetaField_metaObject[0];
}

int igObjectRefMetaField_GetVTable(void) {
    igObjectRefMetaField o;
    int r;
    char *p;
    int *hdr;
    int c;

    igObjectRefMetaField_Init((igObjectRefMetaField *)&o);
    r = *(int *)((char *)&o + *(int *)((char *)(((void * *)g_objectSystem)[0]) + 916));
    o._vtable = (int)&g_igObjectRefMetaField_vtable[0];
    if (&o._poolName != 0) {
        p = (char *)o._poolName;
        if (p != 0) {
            hdr = (int *)(p - 8);
            c = *(int *)(p - 4) - 1;
            *(int *)(p - 4) = c;
            if (c == 0) {
                StringChunk_ReleaseHeader((StringChunk *)(*hdr), (int)hdr);
            }
        }
    }
    o._vtable = (int)&g_igMetaField_vtable[0];
    if (&o._fieldName != 0) {
        p = (char *)o._fieldName;
        if (p != 0) {
            hdr = (int *)(p - 8);
            c = *(int *)(p - 4) - 1;
            *(int *)(p - 4) = c;
            if (c == 0) {
                StringChunk_ReleaseHeader((StringChunk *)(*hdr), (int)hdr);
            }
        }
    }
    return r;
}

void igObjectRefMetaField_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit((StaticInitCallbacks * (*)())igObjectRefMetaField_Register);
}

void igObjectRefMetaField_Register(void) {
    igMetaObject_RegisterClass(
        0, /* abstract */
        ((char *)g_igObjectRefMetaField_metaObject),
        igRefMetaField_Register,
        igRefMetaField_GetPublishedMetaObject,
        thunk_igObjectRefMetaField_GetMetaObject,
        igObjectRefMetaField_className,
        0x44, /* instance size */
        igObjectRefMetaField_GetVTable,
        &igObjectRefMetaField_InitFields,
        0, /* extra callback item */
        g_igObjectRefMetaField_callbackList /* callback list */
    );
}

void thunk_igObjectRefMetaField_GetMetaObject(void) {
    igObjectRefMetaField_GetMetaObject();
}

void igObjectRefMetaField_InitFields(void) {
    int temp_s2;
    void *temp_s1;
    void *temp_s0;

    temp_s0 = (void *)g_igObjectRefMetaField_metaObject[0];
    temp_s2 = igMetaObject_GetFieldCount((igMetaObject *)temp_s0);
    igMetaObject_CreateFields((igMetaObject *)temp_s0, (igMetaField * (**)(void *))&g_igObjectRefMetaField_ctorTable[0], 3);
    temp_s1 = (void *)(((void *)igMetaObject_GetFieldAt((igMetaObject *)temp_s0, temp_s2)));
    ((igObjectRefMetaField *)temp_s1)->_metaObject = (int)FUN_002be610();
    ((igObjectRefMetaField *)temp_s1)->_refCounted = 0;
    ((igMetaField *)temp_s1)->_deepCopyMethod = 1;
    ((igMetaField *)temp_s1)->_shallowCopyMethod = 1;
    FUN_002d3890((void **)(((void *)igMetaObject_GetFieldAt((igMetaObject *)temp_s0, temp_s2 + 1))), 1);
    igMetaObject_NameFields((igMetaObject *)temp_s0, (const char **)&g_igObjectRefMetaField_fieldTable[0], (igMetaField ***)&DAT_004bfad8[0], &DAT_004bfae8[0], temp_s2);
}

void FUN_002bd210(void) {
    igObjectRefMetaField *temp_s0;
    igObjectRefMetaField *p;
    int len;

    if (g_igObjectRefMetaField_descriptor[0] == 0) {
        g_igObjectRefMetaField_descriptor[0] = ((igObjectRefMetaField *)igMetaObject_CreateInstance((igMetaObject *)g_igObjectRefMetaField_metaObject[0], (igMemoryPoolView *)(((int)Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData)))));
        temp_s0 = g_igObjectRefMetaField_descriptor[0];
        if (temp_s0 != 0) {
            MetaRefList_AppendRetained(FUN_002fc250(), (igObject *)temp_s0);
            p = g_igObjectRefMetaField_descriptor[0];
            p->_refCount = p->_refCount - 1;
            if (((unsigned long long) ((long long)(int)p->_refCount << 0x29) >> 0x29) == 0) {
                igObject_Destroy(p);
            }
            len = FUN_002fc250()->_count;
            g_igObjectRefMetaField_descriptor[0]->_internalIndex = len - 1;
            igMetaField_FinalizeDescriptor((igMetaField *)g_igObjectRefMetaField_descriptor[0]);
        }
    }
}

int igObjectRefMetaField_GetDefaultDescriptor(void) {
    if (g_igObjectRefMetaField_descriptor[0] == 0) {
        igObjectRefMetaField_EnsureRegistered();
    }
    return (int)g_igObjectRefMetaField_descriptor[0];
}

