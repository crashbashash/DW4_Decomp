/* Factory for an igStringMetaField (60-byte instance). Once the object system is live, ensure the
 * class is registered and let its MetaObject create the instance with the given allocator. Before
 * that, allocate by hand, construct in place (second argument 1 is the flag retail passes) and run
 * the post-construction hooks, vfunc_09 then vfunc_07(0). */
void **igStringMetaField_Create(int allocator) {
    void **field;

    if (*g_objectSystem[0] != 0) {
        igStringMetaField_EnsureRegistered();
        field = ((void **)igMetaObject_CreateInstance((CreateMeta *)(((int *)g_igStringMetaField_metaObject)[0]), (MemoryPool *)allocator));
    } else {
        field = ((void **)igObject_AllocateRawStorage(0x3C, 0, (void **)allocator));
        if (field != 0) {
            field = ((void **)igStringMetaField_Construct((igStringMetaField *)field, 1));
        }
        ((igObjectSlot09_2b9750 *)field)->vfunc_09();
        ((igObjectSlot07_2b9750 *)field)->vfunc_07(0);
    }
    return field;
}

int Gap__Core__igStringMetaField__vfunc_21(int arg0, int arg1) {
    int temp_v0;
    if (*g_objectSystem[0] != 0) {
        igStringMetaField_EnsureRegistered();
        return igObject_CloneViaMetadata((void **)arg0, arg1);
    }
    temp_v0 = ((int)igObject_AllocateRawStorageDefault(0x3C, 0));
    if (temp_v0 != 0) {
        temp_v0 = ((int)FUN_0030b2c0((void *)temp_v0, (void *)arg0));
    }
    return temp_v0;
}

igMetaObject *igStringMetaField_GetMetaObject(void)
{
    unsigned char ready;
    if (g_igStringMetaField_metaObject[0] != 0) {
        ready = (g_igStringMetaField_metaObject[0]->_validity & 4) != 0;
        if (ready != 0) goto done;
    }
    igStringMetaField_EnsureRegistered();
done:
    return g_igStringMetaField_metaObject[0];
}

int igStringMetaField_GetVTable(void) {
    Obj_2b98c0 o;
    int r;
    char *p;
    int *hdr;
    int c;

    igStringMetaField_Init((igStringMetaField *)&o);
    r = *(int *)((char *)&o + *(int *)((char *)(((void * *)g_objectSystem)[0]) + 916));
    o.vt = &g_igMetaField_vtable[0];
    if (&o.str != 0) {
        p = o.str;
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

void igStringMetaField_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit((StaticInitCallbacks * (*)())igStringMetaField_Register);
}

void igStringMetaField_Register(void) {
    igMetaObject_RegisterClass(
        0, /* abstract */
        ((char *)g_igStringMetaField_metaObject),
        igRefMetaField_Register,
        igRefMetaField_GetPublishedMetaObject,
        thunk_igStringMetaField_GetMetaObject,
        igStringMetaField_className,
        0x3C, /* instance size */
        igStringMetaField_GetVTable,
        &igStringMetaField_InitFields,
        0, /* extra callback item */
        g_igStringMetaField_callbackList /* callback list */
    );
}

void thunk_igStringMetaField_GetMetaObject(void) {
    igStringMetaField_GetMetaObject();
}

igMetaObject *FUN_002b99d0(void) {
    return g_igRefMetaField_metaObject[0];
}

void igStringMetaField_InitFields(void) {
    int temp_s2;
    int temp_s3;
    void **temp_v0;
    M_2b99e0 *temp_s1;
    T_2b99e0 *temp_v0_2;
    T_2b99e0 *temp_v0_4;

    temp_s1 = (M_2b99e0 *)(((void * *)g_igStringMetaField_metaObject)[0]);
    temp_s2 = igMetaObject_GetFieldCount((igMetaObject *)temp_s1);
    igMetaObject_CreateFields((igMetaObject *)temp_s1, (igMetaField * (**)(void *))&g_igStringMetaField_ctorTable[0], 1);
    temp_v0 = (void **)(((void **)igMetaObject_FindFieldByName((igMetaObject *)temp_s1, (const char *)&text_shallowCopyMethod[0])));
    temp_s3 = ObjectPointerList_FindIndex((char *)temp_s1->f40, (int)temp_v0);
    temp_v0_2 = (T_2b99e0 *)(((DW4VC_84_1 *)(temp_v0))->vX((int)(1)));
    FUN_002d4e40((void **)temp_v0_2, 2);
    temp_v0_2->f28 = (int)(&DAT_00585918[0]);
    igMetaObject_FinalizeAndReplaceField((igMetaObject *)temp_s1, temp_s3, (igMetaField *)temp_v0_2);
    temp_v0_2->references = temp_v0_2->references - 1;
    if (((unsigned long long)(long long)temp_v0_2->references & 0x7fffffULL) == 0) {
        igObject_Destroy(temp_v0_2);
    }
    temp_v0 = (void **)(((void **)igMetaObject_FindFieldByName((igMetaObject *)temp_s1, (const char *)&text_destruct[0])));
    temp_s3 = ObjectPointerList_FindIndex((char *)temp_s1->f40, (int)temp_v0);
    temp_v0_4 = (T_2b99e0 *)(((DW4VC_84_1 *)(temp_v0))->vX((int)(1)));
    FUN_002d3890((void **)temp_v0_4, 1);
    temp_v0_4->f28 = (int)(&DAT_00585920[0]);
    igMetaObject_FinalizeAndReplaceField((igMetaObject *)temp_s1, temp_s3, (igMetaField *)temp_v0_4);
    temp_v0_4->references = temp_v0_4->references - 1;
    if (((unsigned long long)(long long)temp_v0_4->references & 0x7fffffULL) == 0) {
        igObject_Destroy(temp_v0_4);
    }
    FUN_002d3890((void **)(((void *)igMetaObject_GetFieldAt((igMetaObject *)temp_s1, temp_s2))), 1);
    igMetaObject_NameFields((igMetaObject *)temp_s1, (const char **)&g_igStringMetaField_fieldTable[0], (igMetaField ***)&DAT_004bf6b0[0], &DAT_004bf6b8[0], temp_s2);
}

void FUN_002b9b90(void) {
    int *s0;
    int *o;

    if (DAT_00585910[0] == 0) {
        DAT_00585910[0] = ((int *)igMetaObject_CreateInstance((CreateMeta *)g_igStringMetaField_metaObject[0], (MemoryPool *)(((int)Memory_GetAllocatorBySelector(g_metadataAllocatorKey[0])))));
        s0 = DAT_00585910[0];
        if (s0 != 0) {
            MetaRefList_AppendRetained((PointerList *)(((void *)FUN_002fc250())), (RefHeader *)s0);
            o = DAT_00585910[0];
            o[1] = o[1] - 1;
            if ((o[1] & 0x7FFFFF) == 0) {
                igObject_Destroy(o);
            }
            *(short *)((char *)DAT_00585910[0] + 18) = *(int *)((char *)((void *)FUN_002fc250()) + 12) - 1;
            igMetaField_FinalizeDescriptor((igMetaField *)DAT_00585910[0]);
        }
    }
}

int FUN_002b9c60(void) {
    if (((int *)DAT_00585910)[0] == 0) {
        igStringMetaField_EnsureRegistered();
    }
    return ((int *)DAT_00585910)[0];
}

