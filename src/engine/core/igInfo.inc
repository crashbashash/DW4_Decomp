igMetaObject *igInfo_GetMetaObject(void)
{
    igMetaObject *g = g_igInfo_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        igInfo_EnsureRegistered();
    return g_igInfo_metaObject[0];
}

int igInfo_GetVTable(void) {
    igInfo info;
    int s0;
    int *ps;
    int *v1;
    int *a1;
    int v0;
    igObject_InitHeader((igObject *)&info);
    ps = &info._name;
    *(int *)ps = 0;
    info._vtable = (int)&g_igNamedObject_vtable[0];
    info._vtable = (int)&g_igInfo_vtable[0];
    s0 = *(int *)((char *)&info + *(int *)((char *)(((void * *)g_objectSystem)[0]) + 916));
    info._vtable = (int)&g_igNamedObject_vtable[0];
    if (ps != 0) {
        v1 = *(int **)ps;
        if (v1 != 0) {
            a1 = v1 - 2;
            v0 = v1[-1] - 1;
            v1[-1] = v0;
            if (v0 == 0) {
                StringChunk_ReleaseHeader((StringChunk *)(*a1), (int)a1);
            }
        }
    }
    return s0;
}

void igInfo_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit((StaticInitCallbacks * (*)())igInfo_Register);
}

void igInfo_Register(void) {
    CoreLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0,
        g_igInfo_metaObject,
        (igMetaObjectRegisterFunction)igNamedObject_Register,
        (igMetaObjectGetFunction)igNamedObject_GetPublishedMetaObject,
        igInfo_GetMetaObjectFunction,
        igInfo_className,
        0x14,
        igInfo_GetVTable,
        igInfo_InitFields,
        0,
        (igMetaObjectCallback *)g_igInfo_callbackList
    );
}

void igInfo_GetMetaObjectFunction(void) {
    igInfo_GetMetaObject();
}

void igInfo_InitFields(void) {
    int base;
    void *field;
    void *meta;

    meta = (void *)g_igInfo_metaObject[0];
    base = igMetaObject_GetFieldCount((igMetaObject *)meta);
    igMetaObject_CreateFields((igMetaObject *)meta, (igMetaField * (**)(void *))&g_igInfo_ctorTable[0], 2);
    field = (void *)(((void *)igMetaObject_GetFieldAt((igMetaObject *)meta, base)));
    ((igObjectRefMetaField *)field)->_metaObject = (int)igDirectory_GetOrCreateMetaObject();
    ((igObjectRefMetaField *)field)->_refCounted = 0;
    ((igMetaField *)field)->_persistent = 0;
    igBoolMetaField_SetDefaultValue((void **)(((void *)igMetaObject_GetFieldAt((igMetaObject *)meta, base + 1))), 1);
    igMetaObject_NameFields((igMetaObject *)meta, (const char **)&g_igInfo_fieldTable[0], (igMetaField ***)&g_igInfo_fieldDescriptors[0], &g_igInfo_fieldOffsets[0], base);
}

