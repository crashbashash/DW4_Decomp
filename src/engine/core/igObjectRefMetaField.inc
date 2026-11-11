/* Same factory shape for an igObjectRefMetaField (68-byte instance). */
void **igObjectRefMetaField_Create(int allocator) {
    void **field;

    if (*g_objectSystem[0] != 0) {
        igObjectRefMetaField_EnsureRegistered();
        field = ((void **)igMetaObject_CreateInstance((CreateMeta *)(((int *)g_igObjectRefMetaField_metaObject)[0]), (MemoryPool *)allocator));
    } else {
        field = ((void **)igObject_AllocateRawStorage(0x44, 0, (void **)allocator));
        if (field != 0) {
            field = ((void **)igObjectRefMetaField_Construct((igObjectRefMetaField *)field, 1));
        }
        ((igObjectSlot09_2b9750 *)field)->vfunc_09();
        ((igObjectSlot07_2b9750 *)field)->vfunc_07(0);
    }
    return field;
}

int Gap__Core__igObjectRefMetaField__vfunc_21(int arg0, int arg1) {
    int temp_v0;

    if (*DAT_00586dc8[0] != 0) {
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
    Obj_2bd000 o;
    int r;
    char *p;
    int *hdr;
    int c;

    igObjectRefMetaField_Init((igObjectRefMetaField *)&o);
    r = *(int *)((char *)&o + *(int *)((char *)(((void * *)DAT_00586dc8)[0]) + 916));
    o.vt = &DAT_00532c80[0];
    if (&o.s2 != 0) {
        p = o.s2;
        if (p != 0) {
            hdr = (int *)(p - 8);
            c = *(int *)(p - 4) - 1;
            *(int *)(p - 4) = c;
            if (c == 0) {
                StringChunk_ReleaseHeader((StringChunkOwnerView *)(*hdr), (int)hdr);
            }
        }
    }
    o.vt = &DAT_0052f230[0];
    if (&o.s1 != 0) {
        p = o.s1;
        if (p != 0) {
            hdr = (int *)(p - 8);
            c = *(int *)(p - 4) - 1;
            *(int *)(p - 4) = c;
            if (c == 0) {
                StringChunk_ReleaseHeader((StringChunkOwnerView *)(*hdr), (int)hdr);
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

    temp_s0 = (void *)DAT_00585b20[0];
    temp_s2 = igMetaObject_GetFieldCount((igMetaObject *)temp_s0);
    igMetaObject_CreateFields((igMetaObject *)temp_s0, (igMetaField * (**)(void *))&DAT_004bfab8[0], 3);
    temp_s1 = (void *)(((void *)igMetaObject_GetFieldAt((igMetaObject *)temp_s0, temp_s2)));
    ((igObjectRefMetaField *)temp_s1)->_metaObject = FUN_002be610();
    ((igObjectRefMetaField *)temp_s1)->_refCounted = 0;
    ((igMetaField *)temp_s1)->_deepCopyMethod = 1;
    ((igMetaField *)temp_s1)->_shallowCopyMethod = 1;
    FUN_002d3890((void **)(((void *)igMetaObject_GetFieldAt((igMetaObject *)temp_s0, temp_s2 + 1))), 1);
    igMetaObject_NameFields((igMetaObject *)temp_s0, (const char **)&DAT_004bfac8[0], (igMetaField ***)&DAT_004bfad8[0], &DAT_004bfae8[0], temp_s2);
}

void FUN_002bd210(void) {
    M_2bd210 *temp_s0;
    M_2bd210 *p;
    int len;

    if (DAT_00585b28[0] == 0) {
        DAT_00585b28[0] = ((M_2bd210 *)igMetaObject_CreateInstance((CreateMeta *)DAT_00585b20[0], (MemoryPool *)(((int)Memory_GetAllocatorBySelector(DAT_00587040[0])))));
        temp_s0 = DAT_00585b28[0];
        if (temp_s0 != 0) {
            MetaRefList_AppendRetained((PointerList *)(((R_2bd210 *)FUN_002fc250())), (RefHeader *)temp_s0);
            p = DAT_00585b28[0];
            p->f4 = p->f4 - 1;
            if (((unsigned long long) ((long long) p->f4 << 0x29) >> 0x29) == 0) {
                igObject_Destroy(p);
            }
            len = ((R_2bd210 *)FUN_002fc250())->f12;
            DAT_00585b28[0]->f18 = len - 1;
            igMetaField_FinalizeDescriptor((igMetaField *)DAT_00585b28[0]);
        }
    }
}

int igObjectRefMetaField_GetDefaultDescriptor(void) {
    if (g_igObjectRefMetaField_descriptor[0] == 0) {
        igObjectRefMetaField_EnsureRegistered();
    }
    return g_igObjectRefMetaField_descriptor[0];
}

