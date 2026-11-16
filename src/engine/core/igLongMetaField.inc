igMetaObject *g_igLongMetaField_metaObject;
void *g_igLongMetaField_descriptor;

void igLongMetaField_Create(int allocator) {
    igLongMetaField_EnsureRegistered();
    igMetaObject_CreateInstance((igMetaObject *)g_igLongMetaField_metaObject, (igMemoryPoolView *)allocator);
}

igMetaObject *igLongMetaField_GetMetaObject(void)
{
    igMetaObject *g = g_igLongMetaField_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false)
        igLongMetaField_EnsureRegistered();
    return g_igLongMetaField_metaObject;
}

int igLongMetaField_GetVTable(void) {
    igLongMetaField field;
    int *header;
    int vtable;
    int count;
    void *name;

    igMetaField_Init((igMetaField *)&field);
    field._vtable = (int)&g_igLongMetaField_vtable[0];
    vtable = *(int *)((char *)&field + g_objectSystem->vtableProbeOffset);
    field._vtable = (int)&g_igMetaField_vtable[0];
    if ((void **)&field._fieldName != 0) {
        name = (void *)((void *)field._fieldName);
        if (name != 0) {
            header = (int *)((char *)name - 8);
            count = *(int *)((char *)(name) - 4) - 1;
            *(int *)((char *)(name) - 4) = count;
            if (count == 0) {
                StringChunk_ReleaseHeader((StringChunk *)(*header), (StringTokenHeader *)header);
            }
        }
    }
    return vtable;
}

void igLongMetaField_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(igLongMetaField_Register);
}

static igMetaObjectCallback g_igLongMetaField_callbackList[] = { igLongMetaField_CreateDefaultDescriptor, 0 };

CallbackArray *igLongMetaField_Register(void) {
    CoreLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0,
        &g_igLongMetaField_metaObject,
        igMetaField_Register,
        igMetaField_GetPublishedMetaObject,
        igLongMetaField_GetMetaObjectFunction,
        "igLongMetaField",
        0x34,
        igLongMetaField_GetVTable,
        0,
        0,
        g_igLongMetaField_callbackList
    );
}

void igLongMetaField_GetMetaObjectFunction(void) {
    igLongMetaField_GetMetaObject();
}


void igLongMetaField_CreateDefaultDescriptor(void) {
    void *descriptor;

    if (g_igLongMetaField_descriptor == 0) {
        g_igLongMetaField_descriptor = (void *)(((void *)igMetaObject_CreateInstance((igMetaObject *)g_igLongMetaField_metaObject, Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData))));
        descriptor = (void *)(g_igLongMetaField_descriptor);
        if (descriptor != 0) {
            MetaRefList_AppendRetained(igMetaField_GetMetaFieldList(), (igObject *)descriptor);
            {
                igLongMetaField *held = (igLongMetaField *)g_igLongMetaField_descriptor;
                held->_refCount = (int)held->_refCount - 1;
                if (((unsigned long long) ((long long)(int)held->_refCount << 0x29) >> 0x29) == 0) {
                    igObject_Destroy(held);
                }
            }
            ((igLongMetaField *)g_igLongMetaField_descriptor)->_internalIndex = (short) (igMetaField_GetMetaFieldList()->_count - 1);
            igMetaField_FinalizeDescriptor((igMetaField *)g_igLongMetaField_descriptor);
        }
    }
}

int igLongMetaField_GetDefaultDescriptor(void) {
    if ((*(int *)&g_igLongMetaField_descriptor) == 0) {
        igLongMetaField_EnsureRegistered();
    }
    return (*(int *)&g_igLongMetaField_descriptor);
}

