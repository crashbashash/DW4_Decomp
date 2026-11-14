void * igMemoryPoolInfo_Create(int pool) {
    igMemoryPoolInfo_EnsureRegistered();
    return (void *)(igMetaObject_CreateInstance((igMetaObject *)(*(int *)0x585E00), (igMemoryPoolView *)pool));
}

igMetaObject *igMemoryPoolInfo_GetMetaObject(void)
{
    igMetaObject *g = g_igMemoryPoolInfo_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        igMemoryPoolInfo_EnsureRegistered();
    return g_igMemoryPoolInfo_metaObject[0];
}

int igMemoryPoolInfo_GetVTable(void) {
    igMemoryPoolInfo info;
    int t;
    igObject_InitHeader((igObject *)&info);
    info._name = 0;
    info._vtable = (int)&g_igMemoryPoolInfo_vtable[0];
    info._handleName = 0;
    info._aliasedTo = 0;
    info._class = 0;
    info._arenaType = 0;
    info._source = 0;
    info._scope = 0;
    info._debugOptions = 0;
    info._releaseOptions = 0;
    info._debugChecking = 0;
    info._releaseChecking = 0;
    info._debugMessages = 0;
    info._releaseMessages = 0;
    t = *(int *)((char *)&info + *(int *)((char *)(((void * *)g_objectSystem)[0]) + 916));
    info._vtable = (int)&g_igMemoryPoolInfo_vtable[0];
    StringRef_Destruct_00130720(&info._releaseMessages, -1);
    StringRef_Destruct_00130720(&info._debugMessages, -1);
    StringRef_Destruct_00130720(&info._releaseChecking, -1);
    StringRef_Destruct_00130720(&info._debugChecking, -1);
    StringRef_Destruct_00130720(&info._releaseOptions, -1);
    StringRef_Destruct_00130720(&info._debugOptions, -1);
    StringRef_Destruct_00130720(&info._scope, -1);
    StringRef_Destruct_00130720(&info._source, -1);
    StringRef_Destruct_00130720(&info._arenaType, -1);
    StringRef_Destruct_00130720(&info._class, -1);
    StringRef_Destruct_00130720(&info._aliasedTo, -1);
    StringRef_Destruct_00130720(&info._handleName, -1);
    FUN_00131b20(&info, 0);
    return t;
}

void igMemoryPoolInfo_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit((StaticInitCallbacks * (*)())igMemoryPoolInfo_Register);
}

void igMemoryPoolInfo_Register(void) {
    CoreLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0,
        g_igMemoryPoolInfo_metaObject,
        (igMetaObjectRegisterFunction)igInfo_Register,
        (igMetaObjectGetFunction)igInfo_GetPublishedMetaObject,
        igMemoryPoolInfo_GetMetaObjectFunction,
        igMemoryPoolInfo_className,
        0x54,
        igMemoryPoolInfo_GetVTable,
        igMemoryPoolInfo_InitFields,
        0,
        0
    );
}

void igMemoryPoolInfo_GetMetaObjectFunction(void) {
    igMemoryPoolInfo_GetMetaObject();
}

void igMemoryPoolInfo_InitFields(void) {
    int base;
    void *meta;

    meta = (void *)g_igMemoryPoolInfo_metaObject[0];
    base = igMetaObject_GetFieldCount((igMetaObject *)meta);
    igMetaObject_CreateFields((igMetaObject *)meta, (igMetaField * (**)(void *))&g_igMemoryPoolInfo_ctorTable[0], 0x10);
    igMetaObject_NameFields((igMetaObject *)meta, (const char **)&g_igMemoryPoolInfo_fieldTable[0], (igMetaField ***)&g_igMemoryPoolInfo_fieldDescriptors[0], &g_igMemoryPoolInfo_fieldOffsets[0], base);
}

