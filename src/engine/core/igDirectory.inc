void * FUN_002c72c0(int arg0) {
    FUN_002c74b0();
    return (void *)(igMetaObject_CreateInstance((CreateMeta *)(*(int *)0x586668), (MemoryPool *)arg0));
}

igMetaObject *FUN_002c7300(void) {
    if (g_igDirectory_metaObject[0] == 0) {
        g_igDirectory_metaObject[0] = (igMetaObject *)igMetaObject_Create(((int)Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData)));
    }
    return g_igDirectory_metaObject[0];
}

igMetaObject *igDirectory_GetMetaObject(void)
{
    igMetaObject *g = g_igDirectory_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_002c74b0();
    return g_igDirectory_metaObject[0];
}

int igDirectory_GetVTable(void) {
    igDirectory dir;
    int temp_s;
    char *p188;
    char *p172;
    char *p168;
    char *p156;
    char *p152;
    char *p148;
    igObject_InitHeader((ObjectHeader *)&dir);
    dir._vtable = (int)&DAT_00530890[0];
    p148 = (char *)&dir._name;
    *(int *)p148 = 0;
    p152 = (char *)&dir._externalDirectoryList;
    *(int *)p152 = 0;
    p156 = (char *)&dir._infoList;
    *(int *)p156 = 0;
    p168 = (char *)&dir._uniqueEntryList;
    *(int *)p168 = 0;
    p172 = (char *)&dir._refList;
    *(int *)p172 = 0;
    p188 = (char *)&dir._metaFieldPerObjectIndices;
    *(int *)p188 = 0;
    dir._loadingSemaphore = 0;
    temp_s = *(int *)((char *)&dir + *(int *)((char *)(((void * *)g_objectSystem)[0]) + 916));
    dir._vtable = (int)&DAT_00530890[0];
    FUN_002ba970((Ref **)&dir._loadingSemaphore, -1);
    FUN_002c3a80((ObjectRefWord *)p188, -1);
    FUN_00135430(p172, -1);
    FUN_001d36d0(p168, -1);
    FUN_001d35d0(p156, -1);
    FUN_002bac40((void **)p152, -1);
    StringRef_Destruct_00130720(p148, -1);
    return temp_s;
}

void FUN_002c74b0(void)
{
    igMetaObject_RunStaticInit((StaticInitCallbacks * (*)())igDirectory_Register);
}

void igDirectory_Register(void) {
    FUN_002b5d50();
    igMetaObject_RegisterClass(
        0, /* abstract */
        ((char *)g_igDirectory_metaObject),
        igObjectList_Register,
        igObjectList_GetPublishedMetaObject,
        thunk_igDirectory_GetMetaObject,
        igDirectory_className,
        0x48, /* instance size */
        igDirectory_GetVTable,
        &igDirectory_InitFields,
        thunk_FUN_002d7b00, /* extra callback item */
        g_igDirectory_callbackList /* callback list */
    );
}

void thunk_igDirectory_GetMetaObject(void) {
    igDirectory_GetMetaObject();
}

void igDirectory_InitFields(void) {
    int temp_s0;
    void *temp_s2;
    void *temp_s2_2;
    void *temp_s2_3;
    void *temp_s2_4;
    void *temp_s2_5;
    void *temp_s2_6;
    void *temp_s2_7;
    void *temp_v0;
    void *temp_s1;

    temp_s1 = (void *)g_igDirectory_metaObject[0];
    temp_s0 = igMetaObject_GetFieldCount((igMetaObject *)temp_s1);
    igMetaObject_CreateFields((igMetaObject *)temp_s1, (igMetaField * (**)(void *))&g_igDirectory_ctorTable[0], 0x12);
    temp_v0 = (void *)(((void *)igMetaObject_GetFieldAt((igMetaObject *)temp_s1, temp_s0)));
    igStringMetaField_SetDefaultText((int *)temp_v0, 0);
    ((igStringMetaField *)temp_v0)->_destruct = 1;
    temp_s2 = (void *)(((void *)igMetaObject_GetFieldAt((igMetaObject *)temp_s1, temp_s0 + 1)));
    ((igObjectRefMetaField *)temp_s2)->_metaObject = (int)FUN_002c7150();
    ((igObjectRefMetaField *)temp_s2)->_construct = 1;
    temp_s2_2 = (void *)(((void *)igMetaObject_GetFieldAt((igMetaObject *)temp_s1, temp_s0 + 2)));
    ((igObjectRefMetaField *)temp_s2_2)->_metaObject = (int)FUN_002c3440();
    ((igObjectRefMetaField *)temp_s2_2)->_construct = 1;
    temp_s2_3 = (void *)(((void *)igMetaObject_GetFieldAt((igMetaObject *)temp_s1, temp_s0 + 3)));
    ((igObjectRefMetaField *)temp_s2_3)->_metaObject = (int)FUN_002baa30();
    ((igObjectRefMetaField *)temp_s2_3)->_refCounted = 0;
    FUN_002d3890((void **)(((void *)igMetaObject_GetFieldAt((igMetaObject *)temp_s1, temp_s0 + 5))), 1);
    temp_s2_4 = (void *)(((void *)igMetaObject_GetFieldAt((igMetaObject *)temp_s1, temp_s0 + 8)));
    ((igObjectRefMetaField *)temp_s2_4)->_metaObject = (int)FUN_002c9c10();
    FUN_002d3890((void **)(((void *)igMetaObject_GetFieldAt((igMetaObject *)temp_s1, temp_s0 + 0xA))), 1);
    temp_s2_5 = (void *)(((void *)igMetaObject_GetFieldAt((igMetaObject *)temp_s1, temp_s0 + 0xC)));
    ((igObjectRefMetaField *)temp_s2_5)->_metaObject = (int)FUN_002c7300();
    temp_s2_6 = (void *)(((void *)igMetaObject_GetFieldAt((igMetaObject *)temp_s1, temp_s0 + 0xD)));
    ((igObjectRefMetaField *)temp_s2_6)->_metaObject = (int)FUN_002c9170();
    FUN_002d3890((void **)(((void *)igMetaObject_GetFieldAt((igMetaObject *)temp_s1, temp_s0 + 0xE))), 1);
    FUN_002d3890((void **)(((void *)igMetaObject_GetFieldAt((igMetaObject *)temp_s1, temp_s0 + 0xF))), 1);
    temp_s2_7 = (void *)(((void *)igMetaObject_GetFieldAt((igMetaObject *)temp_s1, temp_s0 + 0x11)));
    ((igObjectRefMetaField *)temp_s2_7)->_metaObject = (int)FUN_002ba690();
    ((igObjectRefMetaField *)temp_s2_7)->_persistent = 0;
    igMetaObject_NameFields((igMetaObject *)temp_s1, (const char **)&g_igDirectory_fieldTable[0], (igMetaField ***)&DAT_004c11b0[0], &DAT_004c1200[0], temp_s0);
}

void thunk_FUN_002d7b00(void) {
    FUN_002d7b00();
}

