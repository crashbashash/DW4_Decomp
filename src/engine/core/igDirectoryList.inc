int FUN_002c7150(void) {
    if (DAT_00586660[0] == 0) {
        DAT_00586660[0] = ((int)igMetaObject_Create(((int)Memory_GetAllocatorBySelector(DAT_00587040[0]))));
    }
    return DAT_00586660[0];
}

igMetaObject *igDirectoryList_GetMetaObject(void)
{
    igMetaObject *g = g_igDirectoryList_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_002c7230();
    return g_igDirectoryList_metaObject[0];
}

int igDirectoryList_GetVTable(void) {
    union U_2c71f0 u;
    igObject_InitHeader((ObjectHeader *)u.b);
    u.vt = (int)&DAT_005323c0[0];
    return *(int *)&u.b[*(int *)((char *)(((void * *)DAT_00586dc8)[0]) + 916)];
}

void FUN_002c7230(void)
{
    igMetaObject_RunStaticInit((StaticInitCallbacks * (*)())igDirectoryList_Register);
}

void igDirectoryList_Register(void) {
    FUN_002b5d50();
    igMetaObject_RegisterClass(
        0, /* abstract */
        ((char *)g_igDirectoryList_metaObject),
        igObjectList_Register,
        igObjectList_GetPublishedMetaObject,
        thunk_igDirectoryList_GetMetaObject,
        igDirectoryList_className,
        0x14, /* instance size */
        igDirectoryList_GetVTable,
        0,
        0, /* extra callback item */
        g_igDirectoryList_callbackList /* callback list */
    );
}

void thunk_igDirectoryList_GetMetaObject(void) {
    igDirectoryList_GetMetaObject();
}

