void igUnsignedCharMetaField_Create(int pool) {
    igUnsignedCharMetaField_EnsureRegistered();
    igMetaObject_CreateInstance((igMetaObject *)(*(int *)0x585760), (igMemoryPoolView *)pool);
}

igMetaObject *igUnsignedCharMetaField_GetMetaObject(void)
{
    igMetaObject *g = g_igUnsignedCharMetaField_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        igUnsignedCharMetaField_EnsureRegistered();
    return g_igUnsignedCharMetaField_metaObject[0];
}

int igUnsignedCharMetaField_GetVTable(void) {
    igUnsignedCharMetaField obj;
    char *o;
    int *a1;
    int v0;
    int t;
    igMetaField_Init((igMetaField *)&obj);
    obj._vtable = (int)&g_igUnsignedCharMetaField_vtable[0];
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

void igUnsignedCharMetaField_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit((StaticInitCallbacks * (*)())igUnsignedCharMetaField_Register);
}

void igUnsignedCharMetaField_Register(void) {
    CoreLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0,
        g_igUnsignedCharMetaField_metaObject,
        (igMetaObjectRegisterFunction)igMetaField_Register,
        (igMetaObjectGetFunction)igMetaField_GetPublishedMetaObject,
        igUnsignedCharMetaField_GetMetaObjectFunction,
        igUnsignedCharMetaField_className,
        0x34,
        igUnsignedCharMetaField_GetVTable,
        0,
        0,
        (igMetaObjectCallback *)g_igUnsignedCharMetaField_callbackList
    );
}

void igUnsignedCharMetaField_GetMetaObjectFunction(void) {
    igUnsignedCharMetaField_GetMetaObject();
}

void igUnsignedCharMetaField_CreateDefaultDescriptor(void) {
    void *descriptor;

    if (g_igUnsignedCharMetaField_descriptor[0] == 0) {
        g_igUnsignedCharMetaField_descriptor[0] = (void *)(((void *)igMetaObject_CreateInstance((igMetaObject *)g_igUnsignedCharMetaField_metaObject[0], (igMemoryPoolView *)(((int)Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData))))));
        descriptor = (void *)(g_igUnsignedCharMetaField_descriptor[0]);
        if (descriptor != 0) {
            MetaRefList_AppendRetained(igMetaField_GetMetaFieldList(), (igObject *)descriptor);
            {
                void *held = (void *)g_igUnsignedCharMetaField_descriptor[0];
                ((igObject *)held)->_refCount = ((igObject *)held)->_refCount - 1;
                if (((unsigned long long) ((long long) (int) ((igObject *)held)->_refCount << 0x29) >> 0x29) == 0) {
                    igObject_Destroy(held);
                }
            }
            ((igMetaField *)g_igUnsignedCharMetaField_descriptor[0])->_internalIndex = (short) (igMetaField_GetMetaFieldList()->_count - 1);
            igMetaField_FinalizeDescriptor((igMetaField *)g_igUnsignedCharMetaField_descriptor[0]);
        }
    }
}

int igUnsignedCharMetaField_GetDefaultDescriptor(void) {
    if (g_igUnsignedCharMetaField_descriptor[0] == 0) {
        igUnsignedCharMetaField_EnsureRegistered();
    }
    return (int)g_igUnsignedCharMetaField_descriptor[0];
}

