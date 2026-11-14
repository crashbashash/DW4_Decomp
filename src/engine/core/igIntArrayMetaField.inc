void igIntArrayMetaField_Create(int pool) {
    igIntArrayMetaField_EnsureRegistered();
    igMetaObject_CreateInstance((igMetaObject *)(*(int *)0x586108), (igMemoryPoolView *)pool);
}

igMetaObject *igIntArrayMetaField_GetMetaObject(void)
{
    igMetaObject *g = g_igIntArrayMetaField_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        igIntArrayMetaField_EnsureRegistered();
    return g_igIntArrayMetaField_metaObject[0];
}

int igIntArrayMetaField_GetVTable(void) {
    igIntArrayMetaField obj;
    char *o;
    int *a1;
    int v0;
    int t;
    igIntMetaField_Init((igMetaField *)&obj);
    obj._vtable = (int)&g_igIntArrayMetaField_vtable[0];
    t = *(int *)((char *)&obj + *(int *)((char *)(((void * *)g_objectSystem)[0]) + 916));
    obj._vtable = (int)&g_igMetaField_vtable[0];
    if (&obj._fieldName != 0) {
        o = (char *)obj._fieldName;
        if (o != 0) {
            a1 = (int *)(o - 8);
            v0 = *(int *)(o - 4) - 1;
            *(int *)(o - 4) = v0;
            if (v0 == 0) {
                StringChunk_ReleaseHeader((StringChunk *)(*a1), (int)a1);
            }
        }
    }
    return t;
}

void igIntArrayMetaField_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit((StaticInitCallbacks * (*)())igIntArrayMetaField_Register);
}

void igIntArrayMetaField_Register(void) {
    CoreLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0,
        g_igIntArrayMetaField_metaObject,
        (igMetaObjectRegisterFunction)igIntMetaField_Register,
        igIntMetaField_GetPublishedMetaObject,
        igIntArrayMetaField_GetMetaObjectFunction,
        igIntArrayMetaField_className,
        0x38,
        igIntArrayMetaField_GetVTable,
        igIntArrayMetaField_InitFields,
        0,
        (igMetaObjectCallback *)g_igIntArrayMetaField_callbackList
    );
}

void igIntArrayMetaField_GetMetaObjectFunction(void) {
    igIntArrayMetaField_GetMetaObject();
}

igMetaObject *igIntMetaField_GetPublishedMetaObject(void) {
    return g_igIntMetaField_metaObject[0];
}

void igIntArrayMetaField_InitFields(void) {
    int first;
    void *meta;

    meta = (void *)g_igIntArrayMetaField_metaObject[0];
    first = igMetaObject_GetFieldCount((igMetaObject *)meta);
    igMetaObject_CreateFields((igMetaObject *)meta, (igMetaField * (**)(void *))&g_igIntArrayMetaField_ctorTable[0], 1);
    igIntMetaField_SetDefault((void **)(igMetaObject_GetFieldAt((igMetaObject *)meta, first)), 1);
    igMetaObject_NameFields((igMetaObject *)meta, (const char **)&g_igIntArrayMetaField_fieldTable[0], (igMetaField ***)&g_igIntArrayMetaField_fieldDescriptors[0], &g_igIntArrayMetaField_fieldOffsets[0], first);
}

void igIntArrayMetaField_CreateDefaultDescriptor(void) {
    igIntArrayMetaField *descriptor;
    igIntArrayMetaField *held;

    if (g_igIntArrayMetaField_descriptor[0] == 0) {
        g_igIntArrayMetaField_descriptor[0] = (igIntArrayMetaField *)(((void *)igMetaObject_CreateInstance((igMetaObject *)g_igIntArrayMetaField_metaObject[0], (igMemoryPoolView *)(((int)Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData))))));
        descriptor = g_igIntArrayMetaField_descriptor[0];
        if (descriptor != 0) {
            MetaRefList_AppendRetained(igMetaField_GetMetaFieldList(), (igObject *)descriptor);
            held = g_igIntArrayMetaField_descriptor[0];
            held->_refCount = held->_refCount - 1;
            if ((held->_refCount & 0x7FFFFF) == 0) {
                igObject_Destroy(held);
            }
            g_igIntArrayMetaField_descriptor[0]->_internalIndex = igMetaField_GetMetaFieldList()->_count - 1;
            igMetaField_FinalizeDescriptor((igMetaField *)g_igIntArrayMetaField_descriptor[0]);
        }
    }
}

