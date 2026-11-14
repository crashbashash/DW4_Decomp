void igEnumArrayMetaField_Create(int pool) {
    igEnumArrayMetaField_EnsureRegistered();
    igMetaObject_CreateInstance((igMetaObject *)(*(int *)0x5865B0), (igMemoryPoolView *)pool);
}

igMetaObject *igEnumArrayMetaField_GetMetaObject(void)
{
    igMetaObject *g = g_igEnumArrayMetaField_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        igEnumArrayMetaField_EnsureRegistered();
    return g_igEnumArrayMetaField_metaObject[0];
}

int igEnumArrayMetaField_GetVTable(void) {
    igEnumArrayMetaField field;
    int result;
    char *fieldName;
    int *name;
    int *header;
    int refs;

    igEnumMetaField_Init((int **)&field);
    field._vtable = (int)&g_igEnumArrayMetaField_vtable[0];
    result = *(int *)((char *)&field + *(int *)((char *)(((void * *)g_objectSystem)[0]) + 916));
    field._vtable = (int)&g_igMetaField_vtable[0];
    fieldName = (char *)&field._fieldName;
    if (fieldName != 0) {
        name = *(int **)fieldName;
        if (name != 0) {
            header = name - 2;
            refs = name[-1] - 1;
            name[-1] = refs;
            if (refs == 0) {
                StringChunk_ReleaseHeader((StringChunk *)(*header), (int)header);
            }
        }
    }
    return result;
}

void igEnumArrayMetaField_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit((StaticInitCallbacks * (*)())igEnumArrayMetaField_Register);
}

void igEnumArrayMetaField_Register(void) {
    CoreLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0,
        g_igEnumArrayMetaField_metaObject,
        (igMetaObjectRegisterFunction)igEnumMetaField_Register,
        igEnumMetaField_GetPublishedMetaObject,
        igEnumArrayMetaField_GetMetaObjectFunction,
        igEnumArrayMetaField_className,
        0x3C,
        igEnumArrayMetaField_GetVTable,
        igEnumArrayMetaField_InitFields,
        0,
        (igMetaObjectCallback *)g_igEnumArrayMetaField_callbackList
    );
}

void igEnumArrayMetaField_GetMetaObjectFunction(void) {
    igEnumArrayMetaField_GetMetaObject();
}

igMetaObject *igEnumMetaField_GetPublishedMetaObject(void) {
    return g_igEnumMetaField_metaObject[0];
}

void igEnumArrayMetaField_InitFields(void) {
    int base;
    void *meta;

    meta = (void *)g_igEnumArrayMetaField_metaObject[0];
    base = igMetaObject_GetFieldCount((igMetaObject *)meta);
    igMetaObject_CreateFields((igMetaObject *)meta, (igMetaField * (**)(void *))&g_igEnumArrayMetaField_ctorTable[0], 1);
    igIntMetaField_SetDefault((void **)(igMetaObject_GetFieldAt((igMetaObject *)meta, base)), 1);
    igMetaObject_NameFields((igMetaObject *)meta, (const char **)&g_igEnumArrayMetaField_fieldTable[0], (igMetaField ***)&g_igEnumArrayMetaField_fieldDescriptors[0], &g_igEnumArrayMetaField_fieldOffsets[0], base);
}

void igEnumArrayMetaField_CreateDefaultDescriptor(void) {
    int *s0;
    int *g;

    if (g_igEnumArrayMetaField_descriptor[0] == 0) {
        g_igEnumArrayMetaField_descriptor[0] = ((int *)igMetaObject_CreateInstance((igMetaObject *)g_igEnumArrayMetaField_metaObject[0], (igMemoryPoolView *)(((int)Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData)))));
        s0 = g_igEnumArrayMetaField_descriptor[0];
        if (s0 != 0) {
            MetaRefList_AppendRetained(igMetaField_GetMetaFieldList(), (igObject *)s0);
            g = g_igEnumArrayMetaField_descriptor[0];
            g[1] = g[1] - 1;
            if ((g[1] & 0x7FFFFF) == 0) {
                igObject_Destroy(g);
            }
            *(short *)((char *)g_igEnumArrayMetaField_descriptor[0] + 18) = (short)(((int *)igMetaField_GetMetaFieldList())[3] - 1);
            igMetaField_FinalizeDescriptor((igMetaField *)g_igEnumArrayMetaField_descriptor[0]);
        }
    }
}

