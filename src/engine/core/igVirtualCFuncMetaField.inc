igMetaObject *igVirtualCFuncMetaField_GetMetaObject(void)
{
    igMetaObject *g = g_igVirtualCFuncMetaField_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        igVirtualCFuncMetaField_EnsureRegistered();
    return g_igVirtualCFuncMetaField_metaObject[0];
}

int igVirtualCFuncMetaField_GetVTable(void) {
    igVirtualCFuncMetaField f;
    int vtable;
    int *header;
    int references;

    igMetaField_Init((igMetaField *)&f);
    f._vtable = (int)&g_igVirtualCFuncMetaField_vtable[0];
    vtable = *(int *)((char *)&f + *(int *)((char *)(((void * *)g_objectSystem)[0]) + 916));
    f._vtable = (int)&g_igMetaField_vtable[0];
    if (&f._fieldName != 0) {
        if (((int *)f._fieldName) != 0) {
            header = ((int *)f._fieldName) - 2;
            references = ((int *)f._fieldName)[-1] - 1;
            ((int *)f._fieldName)[-1] = references;
            if (references == 0) {
                StringChunk_ReleaseHeader((StringChunk *)(*header), (int)header);
            }
        }
    }
    return vtable;
}

void igVirtualCFuncMetaField_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit((StaticInitCallbacks * (*)())igVirtualCFuncMetaField_Register);
}

void igVirtualCFuncMetaField_Register(void) {
    CoreLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0,
        g_igVirtualCFuncMetaField_metaObject,
        (igMetaObjectRegisterFunction)igMetaField_Register,
        (igMetaObjectGetFunction)igMetaField_GetPublishedMetaObject,
        igVirtualCFuncMetaField_GetMetaObjectFunction,
        igVirtualCFuncMetaField_className,
        0x34,
        igVirtualCFuncMetaField_GetVTable,
        0,
        0,
        (igMetaObjectCallback *)g_igVirtualCFuncMetaField_callbackList
    );
}

void igVirtualCFuncMetaField_GetMetaObjectFunction(void) {
    igVirtualCFuncMetaField_GetMetaObject();
}

void igVirtualCFuncMetaField_CreateDefaultDescriptor(void) {
    void *descriptor;

    if (g_igVirtualCFuncMetaField_descriptor[0] == 0) {
        g_igVirtualCFuncMetaField_descriptor[0] = (void *)(((void *)igMetaObject_CreateInstance((igMetaObject *)g_igVirtualCFuncMetaField_metaObject[0], (igMemoryPoolView *)(((int)Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData))))));
        descriptor = (void *)(g_igVirtualCFuncMetaField_descriptor[0]);
        if (descriptor != 0) {
            MetaRefList_AppendRetained(igMetaField_GetMetaFieldList(), (igObject *)descriptor);
            {
                igMetaField *held = (igMetaField *)g_igVirtualCFuncMetaField_descriptor[0];
                held->_refCount = (int)held->_refCount - 1;
                if (((unsigned long long) ((long long)(int)held->_refCount << 0x29) >> 0x29) == 0) {
                    igObject_Destroy(held);
                }
            }
            ((igMetaField *)g_igVirtualCFuncMetaField_descriptor[0])->_internalIndex = (short)(igMetaField_GetMetaFieldList()->_count - 1);
            igMetaField_FinalizeDescriptor((igMetaField *)g_igVirtualCFuncMetaField_descriptor[0]);
        }
    }
}

