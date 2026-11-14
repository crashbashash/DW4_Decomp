void * FUN_002bfed0(int arg0) {
    FUN_002c00f0();
    return (void *)(igMetaObject_CreateInstance((igMetaObject *)(*(int *)0x585E00), (igMemoryPoolView *)arg0));
}

igMetaObject *igMemoryPoolInfo_GetMetaObject(void)
{
    igMetaObject *g = g_igMemoryPoolInfo_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_002c00f0();
    return g_igMemoryPoolInfo_metaObject[0];
}

int igMemoryPoolInfo_GetVTable(void) {
    igMemoryPoolInfo info;
    int t;
    igObject_InitHeader((igObject *)&info);
    info._name = 0;
    info._vtable = (int)&DAT_0052f430[0];
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
    info._vtable = (int)&DAT_0052f430[0];
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

void FUN_002c00f0(void)
{
    igMetaObject_RunStaticInit((StaticInitCallbacks * (*)())igMemoryPoolInfo_Register);
}

void igMemoryPoolInfo_Register(void) {
    FUN_002b5d50();
    igMetaObject_RegisterClass(
        0, /* abstract */
        ((char *)g_igMemoryPoolInfo_metaObject),
        igInfo_Register,
        igInfo_GetPublishedMetaObject,
        thunk_igMemoryPoolInfo_GetMetaObject,
        igMemoryPoolInfo_className,
        0x54, /* instance size */
        igMemoryPoolInfo_GetVTable,
        &igMemoryPoolInfo_InitFields,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void thunk_igMemoryPoolInfo_GetMetaObject(void) {
    igMemoryPoolInfo_GetMetaObject();
}

void igMemoryPoolInfo_InitFields(void) {
    int temp_s1;
    void *temp_s0;

    temp_s0 = (void *)g_igMemoryPoolInfo_metaObject[0];
    temp_s1 = igMetaObject_GetFieldCount((igMetaObject *)temp_s0);
    igMetaObject_CreateFields((igMetaObject *)temp_s0, (igMetaField * (**)(void *))&g_igMemoryPoolInfo_ctorTable[0], 0x10);
    igMetaObject_NameFields((igMetaObject *)temp_s0, (const char **)&g_igMemoryPoolInfo_fieldTable[0], (igMetaField ***)&DAT_004c00e0[0], &DAT_004c0120[0], temp_s1);
}

