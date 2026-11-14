void * igMemoryPoolContextInfo_Create(int allocator) {
    igMemoryPoolContextInfo_EnsureRegistered();
    return (void *)(igMetaObject_CreateInstance((igMetaObject *)(*(int *)0x585E88), (igMemoryPoolView *)allocator));
}

igMetaObject *igMemoryPoolContextInfo_GetMetaObject(void)
{
    igMetaObject *g = g_igMemoryPoolContextInfo_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        igMemoryPoolContextInfo_EnsureRegistered();
    return g_igMemoryPoolContextInfo_metaObject[0];
}

int igMemoryPoolContextInfo_GetVTable(void) {
    igMemoryPoolContextInfo info;
    char *o;
    igObject *r;
    int *a1;
    int v0;
    int t;
    igObject_InitHeader((igObject *)&info);
    info._name = 0;
    *(int **)&info._vtable = &g_igMemoryPoolContextInfo_vtable[0];
    info._memoryPoolInfos = 0;
    t = *(int *)((char *)&info + *(int *)((char *)(((void * *)g_objectSystem)[0]) + 916));
    info._vtable = (int)&g_igMemoryPoolContextInfo_vtable[0];
    if (&info._memoryPoolInfos != 0) {
        r = (igObject *)info._memoryPoolInfos;
        if (r != 0) {
            r->_refCount = r->_refCount - 1;
            if ((r->_refCount & 0x7FFFFF) == 0) {
                igObject_Destroy(r);
            }
        }
    }
    info._vtable = (int)&g_igNamedObject_vtable[0];
    if (&info._name != 0) {
        o = (char *)info._name;
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

void igMemoryPoolContextInfo_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit((StaticInitCallbacks * (*)())igMemoryPoolContextInfo_Register);
}

void igMemoryPoolContextInfo_Register(void) {
    CoreLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0,
        g_igMemoryPoolContextInfo_metaObject,
        (igMetaObjectRegisterFunction)igInfo_Register,
        (igMetaObjectGetFunction)igInfo_GetPublishedMetaObject,
        igMemoryPoolContextInfo_GetMetaObjectFunction,
        igMemoryPoolContextInfo_className,
        0x18,
        igMemoryPoolContextInfo_GetVTable,
        igMemoryPoolContextInfo_InitFields,
        0,
        (igMetaObjectCallback *)g_igMemoryPoolContextInfo_callbackList
    );
}

void igMemoryPoolContextInfo_GetMetaObjectFunction(void) {
    igMemoryPoolContextInfo_GetMetaObject();
}

void igMemoryPoolContextInfo_InitFields(void) {
    int base;
    void *memoryPoolInfos;
    void *meta;

    meta = (void *)g_igMemoryPoolContextInfo_metaObject[0];
    base = igMetaObject_GetFieldCount((igMetaObject *)meta);
    igMetaObject_CreateFields((igMetaObject *)meta, (igMetaField * (**)(void *))&g_igMemoryPoolContextInfo_ctorTable[0], 1);
    memoryPoolInfos = (void *)(((void *)igMetaObject_GetFieldAt((igMetaObject *)meta, base)));
    ((igObjectRefMetaField *)memoryPoolInfos)->_metaObject = (int)igMemoryPoolInfoList_GetOrCreateMetaObject();
    ((igRefMetaField *)memoryPoolInfos)->_construct = 1;
    igMetaObject_NameFields((igMetaObject *)meta, (const char **)&g_igMemoryPoolContextInfo_fieldTable[0], (igMetaField ***)&g_igMemoryPoolContextInfo_fieldDescriptors[0], &g_igMemoryPoolContextInfo_fieldOffsets[0], base);
}

