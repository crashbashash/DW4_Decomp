void igFloatArrayMetaField_Create(int pool) {
    igFloatArrayMetaField_EnsureRegistered();
    igMetaObject_CreateInstance((igMetaObject *)(*(int *)0x586388), (igMemoryPoolView *)pool);
}

igMetaObject *igFloatArrayMetaField_GetMetaObject(void)
{
    igMetaObject *g = g_igFloatArrayMetaField_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        igFloatArrayMetaField_EnsureRegistered();
    return g_igFloatArrayMetaField_metaObject[0];
}

int igFloatArrayMetaField_GetVTable(void) {
    igFloatArrayMetaField prototype;
    int vtable;
    char *nameSlot;
    int *text;
    int *header;
    int refCount;

    igMetaField_Init((igMetaField *)&prototype);
    prototype._vtable = (int)&g_igFloatArrayMetaField_vtable[0];
    vtable = *(int *)((char *)&prototype + *(int *)((char *)(((void * *)g_objectSystem)[0]) + 916));
    prototype._vtable = (int)&g_igMetaField_vtable[0];
    nameSlot = (char *)&prototype._fieldName;
    if (nameSlot != 0) {
        text = *(int **)nameSlot;
        if (text != 0) {
            header = text - 2;
            refCount = text[-1] - 1;
            text[-1] = refCount;
            if (refCount == 0) {
                StringChunk_ReleaseHeader((StringChunk *)(*header), (int)header);
            }
        }
    }
    return vtable;
}

void igFloatArrayMetaField_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit((StaticInitCallbacks * (*)())igFloatArrayMetaField_Register);
}

void igFloatArrayMetaField_Register(void) {
    CoreLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0,
        g_igFloatArrayMetaField_metaObject,
        (igMetaObjectRegisterFunction)igFloatMetaField_Register,
        igFloatMetaField_GetPublishedMetaObject,
        igFloatArrayMetaField_GetMetaObjectFunction,
        igFloatArrayMetaField_className,
        0x38,
        igFloatArrayMetaField_GetVTable,
        igFloatArrayMetaField_InitFields,
        0,
        (igMetaObjectCallback *)g_igFloatArrayMetaField_callbackList
    );
}

void igFloatArrayMetaField_GetMetaObjectFunction(void) {
    igFloatArrayMetaField_GetMetaObject();
}

igMetaObject *igFloatMetaField_GetPublishedMetaObject(void) {
    return g_igFloatMetaField_metaObject[0];
}

void igFloatArrayMetaField_InitFields(void) {
    int base;
    void *meta;

    meta = (void *)g_igFloatArrayMetaField_metaObject[0];
    base = igMetaObject_GetFieldCount((igMetaObject *)meta);
    igMetaObject_CreateFields((igMetaObject *)meta, (igMetaField * (**)(void *))&g_igFloatArrayMetaField_ctorTable[0], 1);
    igIntMetaField_SetDefault((void **)(igMetaObject_GetFieldAt((igMetaObject *)meta, base)), 1);
    igMetaObject_NameFields((igMetaObject *)meta, (const char **)&g_igFloatArrayMetaField_fieldTable[0], (igMetaField ***)&g_igFloatArrayMetaField_fieldDescriptors[0], &g_igFloatArrayMetaField_fieldOffsets[0], base);
}

void igFloatArrayMetaField_CreateDefaultDescriptor(void) {
    igFloatArrayMetaField *descriptor;
    igFloatArrayMetaField *held;
    int n;

    if (g_igFloatArrayMetaField_descriptor[0] == 0) {
        g_igFloatArrayMetaField_descriptor[0] = ((igFloatArrayMetaField *)igMetaObject_CreateInstance((igMetaObject *)g_igFloatArrayMetaField_metaObject[0], (igMemoryPoolView *)(((int)Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData)))));
        descriptor = g_igFloatArrayMetaField_descriptor[0];
        if (descriptor != 0) {
            MetaRefList_AppendRetained(igMetaField_GetMetaFieldList(), (igObject *)descriptor);
            held = g_igFloatArrayMetaField_descriptor[0];
            held->_refCount = (int)((int) (held->_refCount - 1));
            if (((unsigned long long) ((long long)(int)held->_refCount << 0x29) >> 0x29) == 0) {
                igObject_Destroy(held);
            }
            n = igMetaField_GetMetaFieldList()->_count - 1;
            g_igFloatArrayMetaField_descriptor[0]->_internalIndex = n;
            igMetaField_FinalizeDescriptor((igMetaField *)g_igFloatArrayMetaField_descriptor[0]);
        }
    }
}

