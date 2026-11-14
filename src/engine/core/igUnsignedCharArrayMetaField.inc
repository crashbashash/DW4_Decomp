void igUnsignedCharArrayMetaField_Create(int arg0) {
    igUnsignedCharArrayMetaField_EnsureRegistered();
    igMetaObject_CreateInstance((igMetaObject *)(*(int *)0x585770), (igMemoryPoolView *)arg0);
}

igMetaObject *igUnsignedCharArrayMetaField_GetMetaObject(void)
{
    igMetaObject *g = g_igUnsignedCharArrayMetaField_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        igUnsignedCharArrayMetaField_EnsureRegistered();
    return g_igUnsignedCharArrayMetaField_metaObject[0];
}

int igUnsignedCharArrayMetaField_GetVTable(void) {
    igUnsignedCharArrayMetaField o;
    int *temp_a1;
    int temp_s0;
    int temp_v0;
    void *temp_v1;

    igMetaField_Init((igMetaField *)&o);
    o._vtable = (int)&DAT_0052e630[0];
    temp_s0 = *(int *)((char *)&o + *(int *)((char *)(((void * *)g_objectSystem)[0]) + 916));
    o._vtable = (int)&g_igMetaField_vtable[0];
    if (&o._fieldName != 0) {
        temp_v1 = (void *)((char *)o._fieldName);
        if (temp_v1 != 0) {
            temp_a1 = (int *)((char *)temp_v1 - 8);
            temp_v0 = *(int *)((char *)(temp_v1) - 4) - 1;
            *(int *)((char *)(temp_v1) - 4) = temp_v0;
            if (temp_v0 == 0) {
                StringChunk_ReleaseHeader((StringChunk *)(*temp_a1), (int)temp_a1);
            }
        }
    }
    return temp_s0;
}

void igUnsignedCharArrayMetaField_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit((StaticInitCallbacks * (*)())igUnsignedCharArrayMetaField_Register);
}

void igUnsignedCharArrayMetaField_Register(void) {
    CoreLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        ((char *)g_igUnsignedCharArrayMetaField_metaObject),
        igUnsignedCharMetaField_Register,
        igUnsignedCharMetaField_GetPublishedMetaObject,
        igUnsignedCharArrayMetaField_GetMetaObjectFunction,
        igUnsignedCharArrayMetaField_className,
        0x38, /* instance size */
        igUnsignedCharArrayMetaField_GetVTable,
        &igUnsignedCharArrayMetaField_InitFields,
        0, /* extra callback item */
        g_igUnsignedCharArrayMetaField_callbackList /* callback list */
    );
}

void igUnsignedCharArrayMetaField_GetMetaObjectFunction(void) {
    igUnsignedCharArrayMetaField_GetMetaObject();
}

igMetaObject *igUnsignedCharMetaField_GetPublishedMetaObject(void) {
    return g_igUnsignedCharMetaField_metaObject[0];
}

void igUnsignedCharArrayMetaField_InitFields(void) {
    int temp_s1;
    void *temp_s0;

    temp_s0 = (void *)g_igUnsignedCharArrayMetaField_metaObject[0];
    temp_s1 = igMetaObject_GetFieldCount((igMetaObject *)temp_s0);
    igMetaObject_CreateFields((igMetaObject *)temp_s0, (igMetaField * (**)(void *))&g_igUnsignedCharArrayMetaField_ctorTable[0], 1);
    igIntMetaField_SetDefault((void **)(igMetaObject_GetFieldAt((igMetaObject *)temp_s0, temp_s1)), 1);
    igMetaObject_NameFields((igMetaObject *)temp_s0, (const char **)&g_igUnsignedCharArrayMetaField_fieldTable[0], (igMetaField ***)&DAT_004bf358[0], &DAT_004bf360[0], temp_s1);
}

void igUnsignedCharArrayMetaField_CreateDefaultDescriptor(void) {
    igUnsignedCharArrayMetaField *temp_s0;
    igUnsignedCharArrayMetaField *g;

    if (g_igUnsignedCharArrayMetaField_descriptor[0] == 0) {
        g_igUnsignedCharArrayMetaField_descriptor[0] = (igUnsignedCharArrayMetaField *)(((void *)igMetaObject_CreateInstance((igMetaObject *)g_igUnsignedCharArrayMetaField_metaObject[0], (igMemoryPoolView *)(((int)Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData))))));
        temp_s0 = g_igUnsignedCharArrayMetaField_descriptor[0];
        if (temp_s0 != 0) {
            MetaRefList_AppendRetained(igMetaField_GetMetaFieldList(), (igObject *)temp_s0);
            g = g_igUnsignedCharArrayMetaField_descriptor[0];
            g->_refCount = g->_refCount - 1;
            if ((g->_refCount & 0x7FFFFF) == 0) {
                igObject_Destroy(g);
            }
            g_igUnsignedCharArrayMetaField_descriptor[0]->_internalIndex = igMetaField_GetMetaFieldList()->_count - 1;
            igMetaField_FinalizeDescriptor((igMetaField *)g_igUnsignedCharArrayMetaField_descriptor[0]);
        }
    }
}

