igMetaObject *g_igUnsignedCharMetaField_metaObject;
void *g_igUnsignedCharMetaField_descriptor;

void igUnsignedCharMetaField_Create(int pool) {
    igUnsignedCharMetaField_EnsureRegistered();
    igMetaObject_CreateInstance(g_igUnsignedCharMetaField_metaObject, (igMemoryPoolView *)pool);
}

igMetaObject *igUnsignedCharMetaField_GetMetaObject(void)
{
    igMetaObject *g = g_igUnsignedCharMetaField_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false)
        igUnsignedCharMetaField_EnsureRegistered();
    return g_igUnsignedCharMetaField_metaObject;
}

int igUnsignedCharMetaField_GetVTable(void) {
    igUnsignedCharMetaField obj;
    char *o;
    int *a1;
    int v0;
    int t;
    igMetaField_Init((igMetaField *)&obj);
    obj._vtable = (int)&g_igUnsignedCharMetaField_vtable[0];
    t = *(int *)((char *)&obj + g_objectSystem->vtableProbeOffset);
    obj._vtable = (int)&g_igMetaField_vtable[0];
    if (&obj._fieldName != 0) {
        o = (char *)obj._fieldName;
        if (o != 0) {
            a1 = (int *)(o - 8);
            v0 = *(int *)(o - 4) - 1;
            *(int *)(o - 4) = v0;
            if (v0 == 0) {
                StringChunk_ReleaseHeader((StringChunk *)(*a1), (StringTokenHeader *)a1);
            }
        }
    }
    return t;
}

void igUnsignedCharMetaField_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(igUnsignedCharMetaField_Register);
}

static igMetaObjectCallback g_igUnsignedCharMetaField_callbackList[] = { igUnsignedCharMetaField_CreateDefaultDescriptor, 0 };

CallbackArray *igUnsignedCharMetaField_Register(void) {
    CoreLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0,
        &g_igUnsignedCharMetaField_metaObject,
        igMetaField_Register,
        igMetaField_GetPublishedMetaObject,
        igUnsignedCharMetaField_GetMetaObjectFunction,
        "igUnsignedCharMetaField",
        0x34,
        igUnsignedCharMetaField_GetVTable,
        0,
        0,
        g_igUnsignedCharMetaField_callbackList
    );
}

void igUnsignedCharMetaField_GetMetaObjectFunction(void) {
    igUnsignedCharMetaField_GetMetaObject();
}


void igUnsignedCharMetaField_CreateDefaultDescriptor(void) {
    void *descriptor;

    if (g_igUnsignedCharMetaField_descriptor == 0) {
        g_igUnsignedCharMetaField_descriptor = (void *)(((void *)igMetaObject_CreateInstance((igMetaObject *)g_igUnsignedCharMetaField_metaObject, Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData))));
        descriptor = (void *)(g_igUnsignedCharMetaField_descriptor);
        if (descriptor != 0) {
            MetaRefList_AppendRetained(igMetaField_GetMetaFieldList(), (igObject *)descriptor);
            {
                void *held = (void *)g_igUnsignedCharMetaField_descriptor;
                ((igObject *)held)->_refCount = ((igObject *)held)->_refCount - 1;
                if (((unsigned long long) ((long long) (int) ((igObject *)held)->_refCount << 0x29) >> 0x29) == 0) {
                    igObject_Destroy(held);
                }
            }
            ((igMetaField *)g_igUnsignedCharMetaField_descriptor)->_internalIndex = (short) (igMetaField_GetMetaFieldList()->_count - 1);
            igMetaField_FinalizeDescriptor((igMetaField *)g_igUnsignedCharMetaField_descriptor);
        }
    }
}

int igUnsignedCharMetaField_GetDefaultDescriptor(void) {
    if (g_igUnsignedCharMetaField_descriptor == 0) {
        igUnsignedCharMetaField_EnsureRegistered();
    }
    return (int)g_igUnsignedCharMetaField_descriptor;
}

