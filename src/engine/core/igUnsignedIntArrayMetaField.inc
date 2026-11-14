void FUN_002b70b0(int arg0) {
    FUN_002b71d0();
    igMetaObject_CreateInstance((CreateMeta *)(*(int *)0x585748), (MemoryPool *)arg0);
}

igMetaObject *igUnsignedIntArrayMetaField_GetMetaObject(void)
{
    igMetaObject *g = g_igUnsignedIntArrayMetaField_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_002b71d0();
    return g_igUnsignedIntArrayMetaField_metaObject[0];
}

int igUnsignedIntArrayMetaField_GetVTable(void) {
    igUnsignedIntArrayMetaField u;
    int temp_s0;
    char *ps;
    int *temp_v1;
    int *temp_a1;
    int temp_v0;

    igUnsignedIntMetaField_Init((igMetaField *)&u);
    u._vtable = (int)&DAT_0052e430[0];
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

void FUN_002b71d0(void)
{
    igMetaObject_RunStaticInit((StaticInitCallbacks * (*)())igUnsignedIntArrayMetaField_Register);
}

void igUnsignedIntArrayMetaField_Register(void) {
    FUN_002b5d50();
    igMetaObject_RegisterClass(
        0, /* abstract */
        ((char *)g_igUnsignedIntArrayMetaField_metaObject),
        igUnsignedIntMetaField_Register,
        igUnsignedIntMetaField_GetPublishedMetaObject,
        thunk_igUnsignedIntArrayMetaField_GetMetaObject,
        igUnsignedIntArrayMetaField_className,
        0x38, /* instance size */
        igUnsignedIntArrayMetaField_GetVTable,
        &igUnsignedIntArrayMetaField_InitFields,
        0, /* extra callback item */
        g_igUnsignedIntArrayMetaField_callbackList /* callback list */
    );
}

void thunk_igUnsignedIntArrayMetaField_GetMetaObject(void) {
    igUnsignedIntArrayMetaField_GetMetaObject();
}

igMetaObject *FUN_002b7270(void) {
    return g_igUnsignedIntMetaField_metaObject[0];
}

void igUnsignedIntArrayMetaField_InitFields(void) {
    int temp_s1;
    void *temp_s0;

    temp_s0 = (void *)g_igUnsignedIntArrayMetaField_metaObject[0];
    temp_s1 = igMetaObject_GetFieldCount((igMetaObject *)temp_s0);
    igMetaObject_CreateFields((igMetaObject *)temp_s0, (igMetaField * (**)(void *))&g_igUnsignedIntArrayMetaField_ctorTable[0], 1);
    FUN_002ea4b0((void **)(igMetaObject_GetFieldAt((igMetaObject *)temp_s0, temp_s1)), 1);
    igMetaObject_NameFields((igMetaObject *)temp_s0, (const char **)&g_igUnsignedIntArrayMetaField_fieldTable[0], (igMetaField ***)&DAT_004bf328[0], &DAT_004bf330[0], temp_s1);
}

void FUN_002b7310(void) {
    igUnsignedIntArrayMetaField *temp_s0;
    igUnsignedIntArrayMetaField *p;

    if (g_igUnsignedIntArrayMetaField_descriptor[0] == 0) {
        g_igUnsignedIntArrayMetaField_descriptor[0] = ((igUnsignedIntArrayMetaField *)igMetaObject_CreateInstance((CreateMeta *)g_igUnsignedIntArrayMetaField_metaObject[0], (MemoryPool *)(((int)Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData)))));
        temp_s0 = g_igUnsignedIntArrayMetaField_descriptor[0];
        if (temp_s0 != 0) {
            MetaRefList_AppendRetained((PointerList *)(((LST *)FUN_002fc250())), (RefHeader *)temp_s0);
            p = g_igUnsignedIntArrayMetaField_descriptor[0];
            p->_refCount = p->_refCount - 1;
            if (((unsigned long long) ((long long)(int)p->_refCount << 0x29) >> 0x29) == 0) {
                igObject_Destroy(p);
            }
            *(short *)((char *)(g_igUnsignedIntArrayMetaField_descriptor[0]) + 18) = (short) (((LST *)FUN_002fc250())->count - 1);
            igMetaField_FinalizeDescriptor((igMetaField *)g_igUnsignedIntArrayMetaField_descriptor[0]);
        }
    }
}

