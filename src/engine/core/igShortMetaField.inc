void **igShortMetaField_Create(int pool) {
    void **instance;

    if (*g_objectSystem[0] != 0) {
        igShortMetaField_EnsureRegistered();
        instance = (void **)(((void **)igMetaObject_CreateInstance((igMetaObject *)g_igShortMetaField_metaObject[0], (igMemoryPoolView *)pool)));
    } else {
        instance = (void **)(((void **)igObject_AllocateRawStorage(0x34, 0, (igMemoryPoolView *)pool)));
        if (instance != 0) {
            instance = (void **)(((void **)igShortMetaField_Construct((int **)instance, 1)));
        }
        ((igObjectDispatchView *)(instance))->initDefaults();
        ((igObjectDispatchView *)(instance))->userConstruct((int)(0));
    }
    return instance;
}

int igShortMetaField_Clone(int source, int pool) {
    int p;

    if (*g_objectSystem[0] != 0) {
        igShortMetaField_EnsureRegistered();
        return igObject_CloneViaMetadata((void **)source, pool);
    }
    p = ((int)igObject_AllocateRawStorageDefault(0x34, 0));
    if (p != 0) {
        p = ((int)igShortMetaField_CopyConstruct((int **)p, source));
    }
    return p;
}

igMetaObject *igShortMetaField_GetMetaObject(void)
{
    igMetaObject *g = g_igShortMetaField_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        igShortMetaField_EnsureRegistered();
    return g_igShortMetaField_metaObject[0];
}

int igShortMetaField_GetVTable(void) {
    igShortMetaField obj;
    char *o;
    int *a1;
    int v0;
    int t;
    igShortMetaField_Init((int **)&obj);
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

void igShortMetaField_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit((StaticInitCallbacks * (*)())igShortMetaField_Register);
}

void igShortMetaField_Register(void) {
    igMetaObject_RegisterClass(
        0,
        g_igShortMetaField_metaObject,
        (igMetaObjectRegisterFunction)igMetaField_Register,
        (igMetaObjectGetFunction)igMetaField_GetPublishedMetaObject,
        igShortMetaField_GetMetaObjectFunction,
        igShortMetaField_className,
        0x34,
        igShortMetaField_GetVTable,
        0,
        0,
        (igMetaObjectCallback *)g_igShortMetaField_callbackList
    );
}

void igShortMetaField_GetMetaObjectFunction(void) {
    igShortMetaField_GetMetaObject();
}

void igShortMetaField_CreateDefaultDescriptor(void) {
    void *descriptor;

    if (g_igShortMetaField_descriptor[0] == 0) {
        g_igShortMetaField_descriptor[0] = (void *)(((void *)igMetaObject_CreateInstance((igMetaObject *)g_igShortMetaField_metaObject[0], (igMemoryPoolView *)(((int)Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData))))));
        descriptor = (void *)(g_igShortMetaField_descriptor[0]);
        if (descriptor != 0) {
            MetaRefList_AppendRetained(igMetaField_GetMetaFieldList(), (igObject *)descriptor);
            {
                igObject *held = (igObject *)g_igShortMetaField_descriptor[0];
                held->_refCount = held->_refCount - 1;
                if (((unsigned long long) ((long long)(int)held->_refCount << 0x29) >> 0x29) == 0) {
                    igObject_Destroy(held);
                }
            }
            *(short *)((char *)(g_igShortMetaField_descriptor[0]) + 18) = (short) (*(int *)((char *)(((void *)igMetaField_GetMetaFieldList())) + 12) - 1);
            igMetaField_FinalizeDescriptor((igMetaField *)g_igShortMetaField_descriptor[0]);
        }
    }
}

int igShortMetaField_GetDefaultDescriptor(void) {
    if (((int *)g_igShortMetaField_descriptor)[0] == 0) {
        igShortMetaField_EnsureRegistered();
    }
    return ((int *)g_igShortMetaField_descriptor)[0];
}

