igMetaObject *igExternalIndexedEntry_GetMetaObject(void)
{
    igMetaObject *g = g_igExternalIndexedEntry_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_002c52d0();
    return g_igExternalIndexedEntry_metaObject[0];
}

int igExternalIndexedEntry_GetVTable(void) {
    igExternalIndexedEntry entry;
    int temp_s1;

    igObject_InitHeader((igObject *)&entry);
    entry._name = 0;
    entry._vtable = (int)(&DAT_005302b0[0]);
    entry._entryType = 0;
    entry._objectType = 0;
    temp_s1 = *(int *)((char *)&entry + *(int *)((char *)(((void * *)g_objectSystem)[0]) + 916));
    entry._vtable = (int)(&DAT_005302b0[0]);
    FUN_0019c840(&entry._objectType, -1);
    FUN_0019c840(&entry._entryType, -1);
    FUN_0014f4e0(&entry, 0);
    return temp_s1;
}

void FUN_002c52d0(void)
{
    igMetaObject_RunStaticInit((StaticInitCallbacks * (*)())igExternalIndexedEntry_Register);
}

void igExternalIndexedEntry_Register(void) {
    FUN_002b5d50();
    igMetaObject_RegisterClass(
        0, /* abstract */
        ((char *)g_igExternalIndexedEntry_metaObject),
        igDirEntry_Register,
        igDirEntry_GetPublishedMetaObject,
        thunk_igExternalIndexedEntry_GetMetaObject,
        igExternalIndexedEntry_className,
        0x34, /* instance size */
        igExternalIndexedEntry_GetVTable,
        &igExternalIndexedEntry_InitFields,
        0, /* extra callback item */
        g_igExternalIndexedEntry_callbackList /* callback list */
    );
}

void thunk_igExternalIndexedEntry_GetMetaObject(void) {
    igExternalIndexedEntry_GetMetaObject();
}

void igExternalIndexedEntry_InitFields(void) {
    int temp_s2;
    void *temp_s1_2;
    void *temp_s1;
    void *temp_s0;

    temp_s0 = (void *)g_igExternalIndexedEntry_metaObject[0];
    temp_s2 = igMetaObject_GetFieldCount((igMetaObject *)temp_s0);
    igMetaObject_CreateFields((igMetaObject *)temp_s0, (igMetaField * (**)(void *))&g_igExternalIndexedEntry_ctorTable[0], 6);
    temp_s1 = (void *)(((void *)igMetaObject_GetFieldAt((igMetaObject *)temp_s0, temp_s2 + 2)));
    ((igObjectRefMetaField *)temp_s1)->_metaObject = (int)FUN_002be610();
    ((igMetaField *)temp_s1)->_persistent = 0;
    FUN_002ea4b0((void **)(((void *)igMetaObject_GetFieldAt((igMetaObject *)temp_s0, temp_s2 + 3))), -1);
    temp_s1_2 = (void *)(((void *)igMetaObject_GetFieldAt((igMetaObject *)temp_s0, temp_s2 + 4)));
    ((igObjectRefMetaField *)temp_s1_2)->_metaObject = (int)FUN_002be610();
    ((igMetaField *)temp_s1_2)->_persistent = 0;
    FUN_002ea4b0((void **)(((void *)igMetaObject_GetFieldAt((igMetaObject *)temp_s0, temp_s2 + 5))), -1);
    igMetaObject_NameFields((igMetaObject *)temp_s0, (const char **)&g_igExternalIndexedEntry_fieldTable[0], (igMetaField ***)&DAT_004c0c90[0], &DAT_004c0cb0[0], temp_s2);
}

