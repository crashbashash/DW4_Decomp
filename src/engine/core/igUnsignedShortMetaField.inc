void **igUnsignedShortMetaField_Create(int arg0) {
    void **var_s0;

    if (*g_objectSystem[0] != 0) {
        igUnsignedShortMetaField_EnsureRegistered();
        var_s0 = (void **)(((void **)igMetaObject_CreateInstance((igMetaObject *)g_igUnsignedShortMetaField_metaObject[0], (igMemoryPoolView *)arg0)));
    } else {
        var_s0 = (void **)(((void **)igObject_AllocateRawStorage(0x34, 0, (igMemoryPoolView *)arg0)));
        if (var_s0 != 0) {
            var_s0 = (void **)(((void **)igUnsignedShortMetaField_Construct((int **)var_s0, 1)));
        }
        ((igObjectDispatchView *)(var_s0))->vfunc_09();
        ((igObjectDispatchView *)(var_s0))->userConstruct((int)(0));
    }
    return var_s0;
}

int igUnsignedShortMetaField_Clone(int arg0, int arg1) {
    int temp_v0;

    if (*g_objectSystem[0] != 0) {
        igUnsignedShortMetaField_EnsureRegistered();
        return igObject_CloneViaMetadata((void **)arg0, arg1);
    }
    temp_v0 = ((int)igObject_AllocateRawStorageDefault(0x34, 0));
    if (temp_v0 != 0) {
        temp_v0 = ((int)igUnsignedShortMetaField_CopyConstruct((int **)temp_v0, arg0));
    }
    return temp_v0;
}

igMetaObject *igUnsignedShortMetaField_GetMetaObject(void)
{
    igMetaObject *g = g_igUnsignedShortMetaField_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        igUnsignedShortMetaField_EnsureRegistered();
    return g_igUnsignedShortMetaField_metaObject[0];
}

int igUnsignedShortMetaField_GetVTable(void) {
    igUnsignedShortMetaField o;
    int r;
    char *p;
    int *hdr;
    int c;

    igUnsignedShortMetaField_Init((int **)&o);
    r = *(int *)((char *)&o + *(int *)((char *)(((void * *)g_objectSystem)[0]) + 916));
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

void igUnsignedShortMetaField_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit((StaticInitCallbacks * (*)())igUnsignedShortMetaField_Register);
}

void igUnsignedShortMetaField_Register(void) {
    igMetaObject_RegisterClass(
        0, /* abstract */
        ((char *)g_igUnsignedShortMetaField_metaObject),
        igMetaField_Register,
        igMetaField_GetPublishedMetaObject,
        igUnsignedShortMetaField_GetMetaObjectFunction,
        igUnsignedShortMetaField_className,
        0x34, /* instance size */
        igUnsignedShortMetaField_GetVTable,
        0,
        0, /* extra callback item */
        g_igUnsignedShortMetaField_callbackList /* callback list */
    );
}

void igUnsignedShortMetaField_GetMetaObjectFunction(void) {
    igUnsignedShortMetaField_GetMetaObject();
}

void igUnsignedShortMetaField_CreateDefaultDescriptor(void) {
    void *temp_s0;

    if (DAT_005856f0[0] == 0) {
        DAT_005856f0[0] = (void *)(((void *)igMetaObject_CreateInstance((igMetaObject *)g_igUnsignedShortMetaField_metaObject[0], (igMemoryPoolView *)(((int)Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData))))));
        temp_s0 = (void *)(DAT_005856f0[0]);
        if (temp_s0 != 0) {
            MetaRefList_AppendRetained(igMetaField_GetMetaFieldList(), (igObject *)temp_s0);
            {
                void *held = (void *)DAT_005856f0[0];
                *(int *)((char *)(held) + 4) = *(int *)((char *)(held) + 4) - 1;
                if (((unsigned long long) ((long long) *(int *)((char *)(held) + 4) << 0x29) >> 0x29) == 0) {
                    igObject_Destroy(held);
                }
            }
            *(short *)((char *)(DAT_005856f0[0]) + 18) = (short) (*(int *)((char *)(((void *)igMetaField_GetMetaFieldList())) + 12) - 1);
            igMetaField_FinalizeDescriptor((igMetaField *)DAT_005856f0[0]);
        }
    }
}

int igUnsignedShortMetaField_GetDefaultDescriptor(void) {
    if (((int *)DAT_005856f0)[0] == 0) {
        igUnsignedShortMetaField_EnsureRegistered();
    }
    return ((int *)DAT_005856f0)[0];
}

