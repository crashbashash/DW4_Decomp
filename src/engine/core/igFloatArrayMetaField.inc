void FUN_002c48b0(int arg0) {
    FUN_002c49d0();
    igMetaObject_CreateInstance((CreateMeta *)(*(int *)0x586388), (MemoryPool *)arg0);
}

igMetaObject *igFloatArrayMetaField_GetMetaObject(void)
{
    igMetaObject *g = g_igFloatArrayMetaField_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_002c49d0();
    return g_igFloatArrayMetaField_metaObject[0];
}

int igFloatArrayMetaField_GetVTable(void) {
    igFloatArrayMetaField u;
    int temp_s0;
    char *ps;
    int *temp_v1;
    int *temp_a1;
    int temp_v0;

    FUN_002fbfe0((char *)&u);
    u._vtable = (int)&DAT_00530050[0];
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

void FUN_002c49d0(void)
{
    igMetaObject_RunStaticInit((StaticInitCallbacks * (*)())igFloatArrayMetaField_Register);
}

void igFloatArrayMetaField_Register(void) {
    FUN_002b5d50();
    igMetaObject_RegisterClass(
        0, /* abstract */
        ((char *)g_igFloatArrayMetaField_metaObject),
        igFloatMetaField_Register,
        igFloatMetaField_GetPublishedMetaObject,
        thunk_igFloatArrayMetaField_GetMetaObject,
        igFloatArrayMetaField_className,
        0x38, /* instance size */
        igFloatArrayMetaField_GetVTable,
        &igFloatArrayMetaField_InitFields,
        0, /* extra callback item */
        g_igFloatArrayMetaField_callbackList /* callback list */
    );
}

void thunk_igFloatArrayMetaField_GetMetaObject(void) {
    igFloatArrayMetaField_GetMetaObject();
}

igMetaObject *FUN_002c4a70(void) {
    return g_igFloatMetaField_metaObject[0];
}

void igFloatArrayMetaField_InitFields(void) {
    int temp_s1;
    void *temp_s0;

    temp_s0 = (void *)g_igFloatArrayMetaField_metaObject[0];
    temp_s1 = igMetaObject_GetFieldCount((igMetaObject *)temp_s0);
    igMetaObject_CreateFields((igMetaObject *)temp_s0, (igMetaField * (**)(void *))&g_igFloatArrayMetaField_ctorTable[0], 1);
    FUN_002ea4b0((void **)(igMetaObject_GetFieldAt((igMetaObject *)temp_s0, temp_s1)), 1);
    igMetaObject_NameFields((igMetaObject *)temp_s0, (const char **)&g_igFloatArrayMetaField_fieldTable[0], (igMetaField ***)&DAT_004c0ad8[0], &DAT_004c0ae0[0], temp_s1);
}

void FUN_002c4b10(void) {
    igFloatArrayMetaField *temp_s0;
    igFloatArrayMetaField *temp_a0;
    int n;

    if (g_igFloatArrayMetaField_descriptor[0] == 0) {
        g_igFloatArrayMetaField_descriptor[0] = ((igFloatArrayMetaField *)igMetaObject_CreateInstance((CreateMeta *)g_igFloatArrayMetaField_metaObject[0], (MemoryPool *)(((int)Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData)))));
        temp_s0 = g_igFloatArrayMetaField_descriptor[0];
        if (temp_s0 != 0) {
            MetaRefList_AppendRetained((PointerList *)FUN_002fc250(), (RefHeader *)temp_s0);
            temp_a0 = g_igFloatArrayMetaField_descriptor[0];
            temp_a0->_refCount = (int)((int) (temp_a0->_refCount - 1));
            if (((unsigned long long) ((long long)(int)temp_a0->_refCount << 0x29) >> 0x29) == 0) {
                igObject_Destroy(temp_a0);
            }
            n = ((PointerList *)FUN_002fc250())->count - 1;
            g_igFloatArrayMetaField_descriptor[0]->_internalIndex = n;
            igMetaField_FinalizeDescriptor((igMetaField *)g_igFloatArrayMetaField_descriptor[0]);
        }
    }
}

