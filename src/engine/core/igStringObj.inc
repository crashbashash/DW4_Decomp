void * igStringObj_Create(int arg0) {
    FUN_002b9620();
    return (void *)(igMetaObject_CreateInstance((CreateMeta *)(*(int *)0x5858F0), (MemoryPool *)arg0));
}

igMetaObject *FUN_002b9540(void) {
    if (g_igStringObj_metaObject[0] == 0) {
        g_igStringObj_metaObject[0] = (igMetaObject *)igMetaObject_Create(((int)Memory_GetAllocatorBySelector(g_memoryContextMetaData)));
    }
    return g_igStringObj_metaObject[0];
}

igMetaObject *igStringObj_GetMetaObject(void)
{
    igMetaObject *g = g_igStringObj_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_002b9620();
    return g_igStringObj_metaObject[0];
}

int igStringObj_GetVTable(void) {
    union U_2b95e0 u;

    igObject_InitHeader((ObjectHeader *)u.b);
    u.w[0] = (int)(&DAT_00533280[0]);
    return *(int *)&u.b[*(int *)((char *)(((void * *)g_objectSystem)[0]) + 916)];
}

void FUN_002b9620(void)
{
    igMetaObject_RunStaticInit((StaticInitCallbacks * (*)())igStringObj_Register);
}

void igStringObj_Register(void) {
    FUN_002b5d50();
    igMetaObject_RegisterClass(
        0, /* abstract */
        ((char *)g_igStringObj_metaObject),
        igObject_Register,
        igObject_GetMetaObject_ParentAccessor,
        thunk_igStringObj_GetMetaObject,
        igStringObj_className,
        0x10, /* instance size */
        igStringObj_GetVTable,
        &igStringObj_InitFields,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void thunk_igStringObj_GetMetaObject(void) {
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
    ((igMemoryRefMetaField *)temp_s1)->_memType = FUN_002cc2c0();
    ((igRefMetaField *)temp_s1)->_destruct = 1;
    ((igMemoryRefMetaField *)temp_s1)->_releaseOnCopy = 1;
    ((igMemoryRefMetaField *)temp_s1)->_releaseOnReset = 1;
    igMetaObject_NameFields((igMetaObject *)temp_s0, (const char **)&g_igStringObj_fieldTable[0], (igMetaField ***)&DAT_004bf688[0], &DAT_004bf690[0], temp_s2);
}

