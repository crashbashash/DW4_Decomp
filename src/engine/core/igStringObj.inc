void * igStringObj_Create(int arg0) {
    igStringObj_EnsureRegistered();
    return (void *)(igMetaObject_CreateInstance((igMetaObject *)(*(int *)0x5858F0), (igMemoryPoolView *)arg0));
}

igMetaObject *igStringObj_GetOrCreateMetaObject(void) {
    if (g_igStringObj_metaObject[0] == 0) {
        g_igStringObj_metaObject[0] = (igMetaObject *)igMetaObject_Create(((int)Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData)));
    }
    return g_igStringObj_metaObject[0];
}

igMetaObject *igStringObj_GetMetaObject(void)
{
    igMetaObject *g = g_igStringObj_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        igStringObj_EnsureRegistered();
    return g_igStringObj_metaObject[0];
}

int igStringObj_GetVTable(void) {
    igStringObj string;

    igObject_InitHeader((igObject *)&string);
    string._vtable = (int)(&DAT_00533280[0]);
    return *(int *)((char *)&string + *(int *)((char *)(((void * *)g_objectSystem)[0]) + 916));
}

void igStringObj_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit((StaticInitCallbacks * (*)())igStringObj_Register);
}

void igStringObj_Register(void) {
    CoreLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        ((char *)g_igStringObj_metaObject),
        igObject_Register,
        igObject_GetMetaObject_ParentAccessor,
        igStringObj_GetMetaObjectFunction,
        igStringObj_className,
        0x10, /* instance size */
        igStringObj_GetVTable,
        &igStringObj_InitFields,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void igStringObj_GetMetaObjectFunction(void) {
    igStringObj_GetMetaObject();
}

void igStringObj_InitFields(void) {
    int temp_s2;
    void *temp_s1;
    void *temp_s0;

    temp_s0 = (void *)g_igStringObj_metaObject[0];
    temp_s2 = igMetaObject_GetFieldCount((igMetaObject *)temp_s0);
    igMetaObject_CreateFields((igMetaObject *)temp_s0, (igMetaField * (**)(void *))&g_igStringObj_ctorTable[0], 2);
    temp_s1 = (void *)(((void *)igMetaObject_GetFieldAt((igMetaObject *)temp_s0, temp_s2)));
    ((igMemoryRefMetaField *)temp_s1)->_memType = igCharMetaField_GetDefaultDescriptor();
    ((igRefMetaField *)temp_s1)->_destruct = 1;
    ((igMemoryRefMetaField *)temp_s1)->_releaseOnCopy = 1;
    ((igMemoryRefMetaField *)temp_s1)->_releaseOnReset = 1;
    igMetaObject_NameFields((igMetaObject *)temp_s0, (const char **)&g_igStringObj_fieldTable[0], (igMetaField ***)&DAT_004bf688[0], &DAT_004bf690[0], temp_s2);
}

