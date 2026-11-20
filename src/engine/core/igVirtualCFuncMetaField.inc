igMetaObject *g_igVirtualCFuncMetaField_metaObject;
void *g_igVirtualCFuncMetaField_descriptor;

igMetaObject *igVirtualCFuncMetaField_GetMetaObject(void)
{
    igMetaObject *g = g_igVirtualCFuncMetaField_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false)
        igVirtualCFuncMetaField_EnsureRegistered();
    return g_igVirtualCFuncMetaField_metaObject;
}

ObjectSystemView *g_objectSystem;

int igVirtualCFuncMetaField_GetVTable(void) {
    igVirtualCFuncMetaField f;
    int vtable;
    int *header;
    int references;

    igMetaField_Init((igMetaField *)&f);
    f._vtable = (int)&g_igVirtualCFuncMetaField_vtable[0];
    vtable = *(int *)((char *)&f + g_objectSystem->vtableProbeOffset);
    f._vtable = (int)&g_igMetaField_vtable[0];
    if (&f._fieldName != 0) {
        if (((int *)f._fieldName) != 0) {
            header = ((int *)f._fieldName) - 2;
            references = ((int *)f._fieldName)[-1] - 1;
            ((int *)f._fieldName)[-1] = references;
            if (references == 0) {
                StringChunk_ReleaseHeader((StringChunk *)(*header), (StringTokenHeader *)header);
            }
        }
    }
    return vtable;
}

void igVirtualCFuncMetaField_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(igVirtualCFuncMetaField_Register);
}

static igMetaObjectCallback g_igVirtualCFuncMetaField_callbackList[] = { igVirtualCFuncMetaField_CreateDefaultDescriptor, 0 };

CallbackArray *igVirtualCFuncMetaField_Register(void) {
    CoreLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0,
        &g_igVirtualCFuncMetaField_metaObject,
        Gap::Core::igMetaField::arkRegisterInternal,
        igMetaField_GetPublishedMetaObject,
        igVirtualCFuncMetaField_GetMetaObjectFunction,
        "igVirtualCFuncMetaField",
        0x34,
        igVirtualCFuncMetaField_GetVTable,
        0,
        0,
        g_igVirtualCFuncMetaField_callbackList
    );
}

void igVirtualCFuncMetaField_GetMetaObjectFunction(void) {
    igVirtualCFuncMetaField_GetMetaObject();
}


void igVirtualCFuncMetaField_CreateDefaultDescriptor(void) {
    void *descriptor;

    if (g_igVirtualCFuncMetaField_descriptor == 0) {
        g_igVirtualCFuncMetaField_descriptor = (void *)(((void *)igMetaObject_CreateInstance((igMetaObject *)g_igVirtualCFuncMetaField_metaObject, Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData))));
        descriptor = (void *)(g_igVirtualCFuncMetaField_descriptor);
        if (descriptor != 0) {
            MetaRefList_AppendRetained(Gap::Core::igMetaField::getMetaFieldTypes(), (igObject *)descriptor);
            {
                igMetaField *held = (igMetaField *)g_igVirtualCFuncMetaField_descriptor;
                held->_refCount = (int)held->_refCount - 1;
                if (((unsigned long long) ((long long)(int)held->_refCount << 0x29) >> 0x29) == 0) {
                    igObject_Destroy(held);
                }
            }
            ((igMetaField *)g_igVirtualCFuncMetaField_descriptor)->_internalIndex = (short)(Gap::Core::igMetaField::getMetaFieldTypes()->_count - 1);
            ((Gap::Core::igMetaField *)g_igVirtualCFuncMetaField_descriptor)->validate();
        }
    }
}

