void * igNamedObject_Create(int pool) {
    igNamedObject_EnsureRegistered();
    return (void *)(igMetaObject_CreateInstance((igMetaObject *)(*(int *)0x585BD8), (igMemoryPoolView *)pool));
}

igMetaObject *igNamedObject_GetOrCreateMetaObject(void) {
    if (g_igNamedObject_metaObject[0] == 0) {
        g_igNamedObject_metaObject[0] = (igMetaObject *)igMetaObject_Create(((int)Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData)));
    }
    return g_igNamedObject_metaObject[0];
}

igMetaObject *igNamedObject_GetMetaObject(void)
{
    igMetaObject *g = g_igNamedObject_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        igNamedObject_EnsureRegistered();
    return g_igNamedObject_metaObject[0];
}

int igNamedObject_GetVTable(void) {
    igNamedObject object;
    int vtable;
    int *ps;
    int *chars;
    int *header;
    int refCount;

    igObject_InitHeader((igObject *)&object);
    ps = &object._name;
    object._vtable = (int)&g_igNamedObject_vtable[0];
    *ps = 0;
    vtable = *(int *)((char *)&object + *(int *)((char *)(((void * *)g_objectSystem)[0]) + 916));
    object._vtable = (int)&g_igNamedObject_vtable[0];
    if (ps != 0) {
        chars = (int *)*ps;
        if (chars != 0) {
            header = chars - 2;
            refCount = chars[-1] - 1;
            chars[-1] = refCount;
            if (refCount == 0) {
                StringChunk_ReleaseHeader((StringChunk *)(*header), (int)header);
            }
        }
    }
    return vtable;
}

void igNamedObject_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit((StaticInitCallbacks * (*)())igNamedObject_Register);
}

void igNamedObject_Register(void) {
    CoreLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0,
        g_igNamedObject_metaObject,
        (igMetaObjectRegisterFunction)igObject_Register,
        (igMetaObjectGetFunction)igObject_GetMetaObject_ParentAccessor,
        igNamedObject_GetMetaObjectFunction,
        igNamedObject_className,
        0xC,
        igNamedObject_GetVTable,
        igNamedObject_InitFields,
        0,
        0
    );
}

void igNamedObject_GetMetaObjectFunction(void) {
    igNamedObject_GetMetaObject();
}

void igNamedObject_InitFields(void) {
    int first;
    void *meta;

    meta = (void *)g_igNamedObject_metaObject[0];
    first = igMetaObject_GetFieldCount((igMetaObject *)meta);
    igMetaObject_CreateFields((igMetaObject *)meta, (igMetaField * (**)(void *))&g_igNamedObject_ctorTable[0], 1);
    igStringMetaField_SetDefaultText((int *)(igMetaObject_GetFieldAt((igMetaObject *)meta, first)), 0);
    igMetaObject_NameFields((igMetaObject *)meta, (const char **)&g_igNamedObject_fieldTable[0], (igMetaField ***)&g_igNamedObject_fieldDescriptors[0], &g_igNamedObject_fieldOffsets[0], first);
}

