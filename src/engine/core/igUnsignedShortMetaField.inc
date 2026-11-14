void **FUN_002b5fe0(int arg0) {
    void **var_s0;

    if (*g_objectSystem[0] != 0) {
        FUN_002b61d0();
        var_s0 = (void **)(((void **)igMetaObject_CreateInstance((CreateMeta *)g_igUnsignedShortMetaField_metaObject[0], (MemoryPool *)arg0)));
    } else {
        var_s0 = (void **)(((void **)igObject_AllocateRawStorage(0x34, 0, (igMemoryPoolView *)arg0)));
        if (var_s0 != 0) {
            var_s0 = (void **)(((void **)FUN_0030edd0((int **)var_s0, 1)));
        }
        ((DW4VC_44_0 *)(var_s0))->vX();
        ((DW4VC_36_1 *)(var_s0))->vX((int)(0));
    }
    return var_s0;
}

int Gap__Core__igUnsignedShortMetaField__vfunc_21(int arg0, int arg1) {
    int temp_v0;

    if (*g_objectSystem[0] != 0) {
        FUN_002b61d0();
        return igObject_CloneViaMetadata((void **)arg0, arg1);
    }
    temp_v0 = ((int)igObject_AllocateRawStorageDefault(0x34, 0));
    if (temp_v0 != 0) {
        temp_v0 = ((int)FUN_0030ee50((int **)temp_v0, arg0));
    }
    return temp_v0;
}

igMetaObject *igUnsignedShortMetaField_GetMetaObject(void)
{
    igMetaObject *g = g_igUnsignedShortMetaField_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_002b61d0();
    return g_igUnsignedShortMetaField_metaObject[0];
}

int igUnsignedShortMetaField_GetVTable(void) {
    Obj_2b6150 o;
    int r;
    char *p;
    int *hdr;
    int c;

    FUN_0030ee10((int **)&o);
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

void FUN_002b61d0(void)
{
    igMetaObject_RunStaticInit((StaticInitCallbacks * (*)())igUnsignedShortMetaField_Register);
}

void igUnsignedShortMetaField_Register(void) {
    igMetaObject_RegisterClass(
        0, /* abstract */
        ((char *)g_igUnsignedShortMetaField_metaObject),
        igMetaField_Register,
        igMetaField_GetPublishedMetaObject,
        thunk_igUnsignedShortMetaField_GetMetaObject,
        igUnsignedShortMetaField_className,
        0x34, /* instance size */
        igUnsignedShortMetaField_GetVTable,
        0,
        0, /* extra callback item */
        g_igUnsignedShortMetaField_callbackList /* callback list */
    );
}

void thunk_igUnsignedShortMetaField_GetMetaObject(void) {
    igUnsignedShortMetaField_GetMetaObject();
}

void FUN_002b6260(void) {
    void *temp_s0;

    if (DAT_005856f0[0] == 0) {
        DAT_005856f0[0] = (void *)(((void *)igMetaObject_CreateInstance((CreateMeta *)g_igUnsignedShortMetaField_metaObject[0], (MemoryPool *)(((int)Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData))))));
        temp_s0 = (void *)(DAT_005856f0[0]);
        if (temp_s0 != 0) {
            MetaRefList_AppendRetained((PointerList *)(((void *)FUN_002fc250())), (RefHeader *)temp_s0);
            {
                void *held = (void *)DAT_005856f0[0];
                *(int *)((char *)(held) + 4) = *(int *)((char *)(held) + 4) - 1;
                if (((unsigned long long) ((long long) *(int *)((char *)(held) + 4) << 0x29) >> 0x29) == 0) {
                    igObject_Destroy(held);
                }
            }
            *(short *)((char *)(DAT_005856f0[0]) + 18) = (short) (*(int *)((char *)(((void *)FUN_002fc250())) + 12) - 1);
            igMetaField_FinalizeDescriptor((igMetaField *)DAT_005856f0[0]);
        }
    }
}

int FUN_002b6330(void) {
    if (((int *)DAT_005856f0)[0] == 0) {
        FUN_002b61d0();
    }
    return ((int *)DAT_005856f0)[0];
}

