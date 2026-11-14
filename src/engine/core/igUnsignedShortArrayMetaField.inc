void igUnsignedShortArrayMetaField_Create(int arg0) {
    igUnsignedShortArrayMetaField_EnsureRegistered();
    igMetaObject_CreateInstance((igMetaObject *)(*(int *)0x5856F8), (igMemoryPoolView *)arg0);
}

igMetaObject *igUnsignedShortArrayMetaField_GetMetaObject(void)
{
    igMetaObject *g = g_igUnsignedShortArrayMetaField_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        igUnsignedShortArrayMetaField_EnsureRegistered();
    return g_igUnsignedShortArrayMetaField_metaObject[0];
}

int igUnsignedShortArrayMetaField_GetVTable(void) {
    igUnsignedShortArrayMetaField o;
    int r;
    int *temp_a1;
    int temp_v0;
    void *temp_v1;

    igUnsignedShortMetaField_Init((int **)&o);
    o._vtable = (int)&DAT_0052e230[0];
    r = *(int *)((char *)&o + *(int *)((char *)(((void * *)g_objectSystem)[0]) + 916));
    o._vtable = (int)&g_igMetaField_vtable[0];
    if (&o._fieldName != 0) {
        temp_v1 = (char *)o._fieldName;
        if (temp_v1 != 0) {
            temp_a1 = (int *)((char *)temp_v1 - 8);
            temp_v0 = *(int *)((char *)(temp_v1) - 4) - 1;
            *(int *)((char *)(temp_v1) - 4) = temp_v0;
            if (temp_v0 == 0) {
                StringChunk_ReleaseHeader((StringChunk *)(*temp_a1), (int)temp_a1);
            }
        }
    }
    return r;
}

void igUnsignedShortArrayMetaField_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit((StaticInitCallbacks * (*)())igUnsignedShortArrayMetaField_Register);
}

void igUnsignedShortArrayMetaField_Register(void) {
    CoreLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        ((char *)g_igUnsignedShortArrayMetaField_metaObject),
        igUnsignedShortMetaField_Register,
        igUnsignedShortMetaField_GetPublishedMetaObject,
        igUnsignedShortArrayMetaField_GetMetaObjectFunction,
        igUnsignedShortArrayMetaField_className,
        0x38, /* instance size */
        igUnsignedShortArrayMetaField_GetVTable,
        &igUnsignedShortArrayMetaField_InitFields,
        0, /* extra callback item */
        g_igUnsignedShortArrayMetaField_callbackList /* callback list */
    );
}

void igUnsignedShortArrayMetaField_GetMetaObjectFunction(void) {
    igUnsignedShortArrayMetaField_GetMetaObject();
}

igMetaObject *igUnsignedShortMetaField_GetPublishedMetaObject(void) {
    return g_igUnsignedShortMetaField_metaObject[0];
}

void igUnsignedShortArrayMetaField_InitFields(void) {
    int temp_s1;
    void *temp_s0;

    temp_s0 = (void *)g_igUnsignedShortArrayMetaField_metaObject[0];
    temp_s1 = igMetaObject_GetFieldCount((igMetaObject *)temp_s0);
    igMetaObject_CreateFields((igMetaObject *)temp_s0, (igMetaField * (**)(void *))&g_igUnsignedShortArrayMetaField_ctorTable[0], 1);
    igIntMetaField_SetDefault((void **)(igMetaObject_GetFieldAt((igMetaObject *)temp_s0, temp_s1)), 1);
    igMetaObject_NameFields((igMetaObject *)temp_s0, (const char **)&g_igUnsignedShortArrayMetaField_fieldTable[0], (igMetaField ***)&DAT_004bf2c8[0], &DAT_004bf2d0[0], temp_s1);
}

void igUnsignedShortArrayMetaField_CreateDefaultDescriptor(void) {
    igUnsignedShortArrayMetaField *temp_s0;
    igUnsignedShortArrayMetaField *p;

    if (g_igUnsignedShortArrayMetaField_descriptor[0] == 0) {
        g_igUnsignedShortArrayMetaField_descriptor[0] = ((igUnsignedShortArrayMetaField *)igMetaObject_CreateInstance((igMetaObject *)g_igUnsignedShortArrayMetaField_metaObject[0], (igMemoryPoolView *)(((int)Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData)))));
        temp_s0 = g_igUnsignedShortArrayMetaField_descriptor[0];
        if (temp_s0 != 0) {
            MetaRefList_AppendRetained(igMetaField_GetMetaFieldList(), (igObject *)temp_s0);
            p = g_igUnsignedShortArrayMetaField_descriptor[0];
            p->_refCount = p->_refCount - 1;
            if (((unsigned long long)(long long)p->_refCount & 0x7fffffULL) == 0) {
                igObject_Destroy(p);
            }
            g_igUnsignedShortArrayMetaField_descriptor[0]->_internalIndex = igMetaField_GetMetaFieldList()->_count - 1;
            igMetaField_FinalizeDescriptor((igMetaField *)g_igUnsignedShortArrayMetaField_descriptor[0]);
        }
    }
}

