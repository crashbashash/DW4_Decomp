igMetaObject *igStringArrayMetaField_GetMetaObject(void)
{
    igMetaObject *g = g_igStringArrayMetaField_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_002b9d80();
    return g_igStringArrayMetaField_metaObject[0];
}

int igStringArrayMetaField_GetVTable(void) {
    Obj_2b9cf0 o;
    int r;
    char *p;
    int *hdr;
    int c;

    igStringMetaField_Init((igStringMetaField *)&o);
    o.vt = &DAT_0052e990[0];
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

void FUN_002b9d80(void)
{
    igMetaObject_RunStaticInit((StaticInitCallbacks * (*)())igStringArrayMetaField_Register);
}

void igStringArrayMetaField_Register(void) {
    FUN_002b5d50();
    igMetaObject_RegisterClass(
        0, /* abstract */
        ((char *)g_igStringArrayMetaField_metaObject),
        igStringMetaField_Register,
        igStringMetaField_GetPublishedMetaObject,
        thunk_igStringArrayMetaField_GetMetaObject,
        igStringArrayMetaField_className,
        0x40, /* instance size */
        igStringArrayMetaField_GetVTable,
        &igStringArrayMetaField_InitFields,
        0, /* extra callback item */
        g_igStringArrayMetaField_callbackList /* callback list */
    );
}

void thunk_igStringArrayMetaField_GetMetaObject(void) {
    igStringArrayMetaField_GetMetaObject();
}

igMetaObject *FUN_002b9e20(void) {
    return g_igStringMetaField_metaObject[0];
}

void igStringArrayMetaField_InitFields(void) {
    int temp_s1;
    void *temp_s0;

    temp_s0 = (void *)g_igStringArrayMetaField_metaObject[0];
    temp_s1 = igMetaObject_GetFieldCount((igMetaObject *)temp_s0);
    igMetaObject_CreateFields((igMetaObject *)temp_s0, (igMetaField * (**)(void *))&DAT_004bf6c8[0], 1);
    FUN_002ea4b0((void **)(igMetaObject_GetFieldAt((igMetaObject *)temp_s0, temp_s1)), 1);
    igMetaObject_NameFields((igMetaObject *)temp_s0, (const char **)&DAT_004bf6d0[0], (igMetaField ***)&DAT_004bf6d8[0], &DAT_004bf6e0[0], temp_s1);
}

void FUN_002b9ec0(void) {
    int *s0;
    int *g;

    if (DAT_00585938[0] == 0) {
        DAT_00585938[0] = ((int *)igMetaObject_CreateInstance((CreateMeta *)g_igStringArrayMetaField_metaObject[0], (MemoryPool *)(((int)Memory_GetAllocatorBySelector(g_metadataAllocatorKey[0])))));
        s0 = DAT_00585938[0];
        if (s0 != 0) {
            MetaRefList_AppendRetained((PointerList *)(((int *)FUN_002fc250())), (RefHeader *)s0);
            g = DAT_00585938[0];
            g[1] = g[1] - 1;
            if ((g[1] & 0x7FFFFF) == 0) {
                igObject_Destroy(g);
            }
            *(short *)((char *)DAT_00585938[0] + 18) = (short)(((int *)FUN_002fc250())[3] - 1);
            igMetaField_FinalizeDescriptor((igMetaField *)DAT_00585938[0]);
        }
    }
}

