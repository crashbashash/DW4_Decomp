igMetaObject *g_igFloatMetaField_metaObject;
void *g_igFloatMetaField_descriptor;

igMetaField *igFloatMetaField_Create(igMemoryPoolView *pool) {
    igFloatMetaField_EnsureRegistered();
    return (igMetaField *)igMetaObject_CreateInstance(g_igFloatMetaField_metaObject, pool);
}

igMetaObject *igFloatMetaField_GetMetaObject(void)
{
    igMetaObject *g = g_igFloatMetaField_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false)
        igFloatMetaField_EnsureRegistered();
    return g_igFloatMetaField_metaObject;
}

int igFloatMetaField_GetVTable(void) {
    igFloatMetaField o;
    int r;
    int *header;
    int count;
    void *text;

    igMetaField_Init((igMetaField *)&o);
    o._vtable = (int)&g_igFloatMetaField_vtable[0];
    r = *(int *)((char *)&o + g_objectSystem->vtableProbeOffset);
    o._vtable = (int)&g_igMetaField_vtable[0];
    if (&o._fieldName != 0) {
        text = (char *)o._fieldName;
        if (text != 0) {
            header = (int *)((char *)text - 8);
            count = *(int *)((char *)(text) - 4) - 1;
            *(int *)((char *)(text) - 4) = count;
            if (count == 0) {
                StringChunk_ReleaseHeader((StringChunk *)(*header), (StringTokenHeader *)header);
            }
        }
    }
    return r;
}

void igFloatMetaField_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(igFloatMetaField_Register);
}

static igMetaObjectCallback g_igFloatMetaField_callbackList[] = { igFloatMetaField_CreateDefaultDescriptor, 0 };

CallbackArray *igFloatMetaField_Register(void) {
    CoreLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0,
        &g_igFloatMetaField_metaObject,
        Gap::Core::igMetaField::arkRegisterInternal,
        igMetaField_GetPublishedMetaObject,
        igFloatMetaField_GetMetaObjectFunction,
        "igFloatMetaField",
        0x34,
        igFloatMetaField_GetVTable,
        0,
        0,
        g_igFloatMetaField_callbackList
    );
}

void igFloatMetaField_GetMetaObjectFunction(void) {
    igFloatMetaField_GetMetaObject();
}


void igFloatMetaField_CreateDefaultDescriptor(void) {
    void *descriptor;

    if (g_igFloatMetaField_descriptor == 0) {
        g_igFloatMetaField_descriptor = (void *)(((void *)igMetaObject_CreateInstance((igMetaObject *)g_igFloatMetaField_metaObject, Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData))));
        descriptor = (void *)(g_igFloatMetaField_descriptor);
        if (descriptor != 0) {
            MetaRefList_AppendRetained(Gap::Core::igMetaField::getMetaFieldTypes(), (igObject *)descriptor);
            {
                igObject *held = (igObject *)g_igFloatMetaField_descriptor;
                held->_refCount = (int)held->_refCount - 1;
                if (((unsigned long long) ((long long)(int)held->_refCount << 0x29) >> 0x29) == 0) {
                    igObject_Destroy(held);
                }
            }
            ((igMetaField *)g_igFloatMetaField_descriptor)->_internalIndex = (short) (Gap::Core::igMetaField::getMetaFieldTypes()->_count - 1);
            ((Gap::Core::igMetaField *)g_igFloatMetaField_descriptor)->validate();
        }
    }
}

int igFloatMetaField_GetDefaultDescriptor(void) {
    if ((*(int *)&g_igFloatMetaField_descriptor) == 0) {
        igFloatMetaField_EnsureRegistered();
    }
    return (*(int *)&g_igFloatMetaField_descriptor);
}

