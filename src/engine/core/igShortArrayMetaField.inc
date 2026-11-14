void igShortArrayMetaField_Create(int arg0) {
    igShortArrayMetaField_EnsureRegistered();
    igMetaObject_CreateInstance((igMetaObject *)(*(int *)0x585958), (igMemoryPoolView *)arg0);
}

igMetaObject *igShortArrayMetaField_GetMetaObject(void)
{
    igMetaObject *g = g_igShortArrayMetaField_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        igShortArrayMetaField_EnsureRegistered();
    return g_igShortArrayMetaField_metaObject[0];
}

int igShortArrayMetaField_GetVTable(void) {
    igShortArrayMetaField u;
    int temp_s0;
    char *ps;
    int *temp_v1;
    int *temp_a1;
    int temp_v0;

    igShortMetaField_Init((int **)&u);
    u._vtable = (int)&DAT_0052ea90[0];
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
                StringChunk_ReleaseHeader((StringChunk *)(*temp_a1), (int)temp_a1);
            }
        }
    }
    return temp_s0;
}

void igShortArrayMetaField_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit((StaticInitCallbacks * (*)())igShortArrayMetaField_Register);
}

void igShortArrayMetaField_Register(void) {
    CoreLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        ((char *)g_igShortArrayMetaField_metaObject),
        igShortMetaField_Register,
        igShortMetaField_GetPublishedMetaObject,
        igShortArrayMetaField_GetMetaObjectFunction,
        igShortArrayMetaField_className,
        0x38, /* instance size */
        igShortArrayMetaField_GetVTable,
        &igShortArrayMetaField_InitFields,
        0, /* extra callback item */
        g_igShortArrayMetaField_callbackList /* callback list */
    );
}

void igShortArrayMetaField_GetMetaObjectFunction(void) {
    igShortArrayMetaField_GetMetaObject();
}

igMetaObject *igShortMetaField_GetPublishedMetaObject(void) {
    return g_igShortMetaField_metaObject[0];
}

void igShortArrayMetaField_InitFields(void) {
    int temp_s1;
    void *temp_s0;

    temp_s0 = (void *)g_igShortArrayMetaField_metaObject[0];
    temp_s1 = igMetaObject_GetFieldCount((igMetaObject *)temp_s0);
    igMetaObject_CreateFields((igMetaObject *)temp_s0, (igMetaField * (**)(void *))&g_igShortArrayMetaField_ctorTable[0], 1);
    igIntMetaField_SetDefault((void **)(igMetaObject_GetFieldAt((igMetaObject *)temp_s0, temp_s1)), 1);
    igMetaObject_NameFields((igMetaObject *)temp_s0, (const char **)&g_igShortArrayMetaField_fieldTable[0], (igMetaField ***)&DAT_004bf708[0], &DAT_004bf710[0], temp_s1);
}

void igShortArrayMetaField_CreateDefaultDescriptor(void) {
    igShortArrayMetaField *temp_s0;
    igShortArrayMetaField *p;

    if (g_igShortArrayMetaField_descriptor[0] == 0) {
        g_igShortArrayMetaField_descriptor[0] = ((igShortArrayMetaField *)igMetaObject_CreateInstance((igMetaObject *)g_igShortArrayMetaField_metaObject[0], (igMemoryPoolView *)(((int)Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData)))));
        temp_s0 = g_igShortArrayMetaField_descriptor[0];
        if (temp_s0 != 0) {
            MetaRefList_AppendRetained(igMetaField_GetMetaFieldList(), (igObject *)temp_s0);
            p = g_igShortArrayMetaField_descriptor[0];
            p->_refCount -= 1;
            if ((p->_refCount & 0x7fffff) == 0) {
                igObject_Destroy(p);
            }
            g_igShortArrayMetaField_descriptor[0]->_internalIndex = igMetaField_GetMetaFieldList()->_count - 1;
            igMetaField_FinalizeDescriptor((igMetaField *)g_igShortArrayMetaField_descriptor[0]);
        }
    }
}

