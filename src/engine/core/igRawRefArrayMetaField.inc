igMetaObject *igRawRefArrayMetaField_GetMetaObject(void)
{
    igMetaObject *g = g_igRawRefArrayMetaField_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        igRawRefArrayMetaField_EnsureRegistered();
    return g_igRawRefArrayMetaField_metaObject[0];
}

int igRawRefArrayMetaField_GetVTable(void) {
    igRawRefArrayMetaField f;
    int temp_s0;
    int *temp_a1;
    int temp_v0;

    igRawRefMetaField_Init((int **)&f);
    f._vtable = (int)&DAT_0052ed50[0];
    temp_s0 = *(int *)((char *)&f + *(int *)((char *)(((void * *)g_objectSystem)[0]) + 916));
    f._vtable = (int)&g_igMetaField_vtable[0];
    if (&f._fieldName != 0) {
        if (((int *)f._fieldName) != 0) {
            temp_a1 = ((int *)f._fieldName) - 2;
            temp_v0 = ((int *)f._fieldName)[-1] - 1;
            ((int *)f._fieldName)[-1] = temp_v0;
            if (temp_v0 == 0) {
                StringChunk_ReleaseHeader((StringChunk *)(*temp_a1), (int)temp_a1);
            }
        }
    }
    return temp_s0;
}

void igRawRefArrayMetaField_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit((StaticInitCallbacks * (*)())igRawRefArrayMetaField_Register);
}

void igRawRefArrayMetaField_Register(void) {
    CoreLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        ((char *)g_igRawRefArrayMetaField_metaObject),
        igRawRefMetaField_Register,
        igRawRefMetaField_GetPublishedMetaObject,
        igRawRefArrayMetaField_GetMetaObjectFunction,
        igRawRefArrayMetaField_className,
        0x3C, /* instance size */
        igRawRefArrayMetaField_GetVTable,
        &igRawRefArrayMetaField_InitFields,
        0, /* extra callback item */
        g_igRawRefArrayMetaField_callbackList /* callback list */
    );
}

void igRawRefArrayMetaField_GetMetaObjectFunction(void) {
    igRawRefArrayMetaField_GetMetaObject();
}

igMetaObject *igRawRefMetaField_GetPublishedMetaObject(void) {
    return g_igRawRefMetaField_metaObject[0];
}

void igRawRefArrayMetaField_InitFields(void) {
    int temp_s1;
    void *temp_s0;

    temp_s0 = (void *)g_igRawRefArrayMetaField_metaObject[0];
    temp_s1 = igMetaObject_GetFieldCount((igMetaObject *)temp_s0);
    igMetaObject_CreateFields((igMetaObject *)temp_s0, (igMetaField * (**)(void *))&g_igRawRefArrayMetaField_ctorTable[0], 1);
    igIntMetaField_SetDefault((void **)(igMetaObject_GetFieldAt((igMetaObject *)temp_s0, temp_s1)), 1);
    igMetaObject_NameFields((igMetaObject *)temp_s0, (const char **)&g_igRawRefArrayMetaField_fieldTable[0], (igMetaField ***)&DAT_004bf9a0[0], &DAT_004bf9a8[0], temp_s1);
}

void igRawRefArrayMetaField_CreateDefaultDescriptor(void) {
    igRawRefArrayMetaField *temp_s0;
    igRawRefArrayMetaField *p;

    if (g_igRawRefArrayMetaField_descriptor[0] == 0) {
        g_igRawRefArrayMetaField_descriptor[0] = ((igRawRefArrayMetaField *)igMetaObject_CreateInstance((igMetaObject *)g_igRawRefArrayMetaField_metaObject[0], (igMemoryPoolView *)(((int)Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData)))));
        temp_s0 = g_igRawRefArrayMetaField_descriptor[0];
        if (temp_s0 != 0) {
            MetaRefList_AppendRetained(igMetaField_GetMetaFieldList(), (igObject *)temp_s0);
            p = g_igRawRefArrayMetaField_descriptor[0];
            p->_refCount -= 1;
            if ((p->_refCount & 0x7fffff) == 0) {
                igObject_Destroy(p);
            }
            g_igRawRefArrayMetaField_descriptor[0]->_internalIndex = igMetaField_GetMetaFieldList()->_count - 1;
            igMetaField_FinalizeDescriptor((igMetaField *)g_igRawRefArrayMetaField_descriptor[0]);
        }
    }
}

