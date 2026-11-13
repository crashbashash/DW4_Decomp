void igGroup_CreateInstance(int arg0) {
    FUN_0019f330();
    igMetaObject_CreateInstance(*(int *)0x5619F8, arg0);
}

igMetaObject *FUN_0019f210(void) {
    if (g_igGroup_metaObject[0] == 0) {
        g_igGroup_metaObject[0] = igMetaObject_Create(Memory_GetAllocatorBySelector(g_metadataAllocatorKey[0]));
    }
    return g_igGroup_metaObject[0];
}

igMetaObject *igGroup_GetMetaObject(void)
{
    igMetaObject *g = g_igGroup_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_0019f330();
    return g_igGroup_metaObject[0];
}

int igGroup_GetVTable(void) {
    struct Obj_19f2b0 obj;
    int temp_s0;

    igObject_InitHeader(&obj);
    obj.f8 = 0;
    obj.fC = 0;
    obj.f10 = 0;
    obj.vt = (&DAT_00528dd0[0]);
    obj.f1C = 0;
    temp_s0 = *(int *)((char *)&obj + *(int *)((char *)(g_objectSystem[0]) + 916));
    obj.vt = (&DAT_00528dd0[0]);
    FUN_001958f0((void * *)&obj.f1C, -1);
    FUN_00195970((struct T_195970 *)&obj, 0);
    return temp_s0;
}

void FUN_0019f330(void)
{
    igMetaObject_RunStaticInit(igGroup_Register);
}

void igGroup_Register(void) {
    SceneGraphLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        ((char *)g_igGroup_metaObject),
        igNode_Register,
        igNode_GetPublishedMetaObject,
        thunk_igGroup_GetMetaObject,
        igGroup_className,
        0x20, /* instance size */
        igGroup_GetVTable,
        &igGroup_InitFields,
        0, /* extra callback item */
        g_igGroup_callbackList /* callback list */
    );
}

void thunk_igGroup_GetMetaObject(void) {
    igGroup_GetMetaObject();
}

void igGroup_InitFields(void) {
    int temp_s2;
    void *temp_s1;
    void *temp_s0;

    temp_s0 = (void *)g_igGroup_metaObject[0];
    temp_s2 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &g_igGroup_ctorTable[0], 1);
    temp_s1 = (void *)(((void *)igMetaObject_GetFieldAt(temp_s0, temp_s2)));
    ((igObjectRefMetaField *)temp_s1)->_metaObject = (int)FUN_0019cbe0();
    ((igMetaField *)temp_s1)->_resetMethod = 3;
    ((igRefMetaField *)temp_s1)->_construct = 1;
    ((igMetaField *)temp_s1)->_deepCopyMethod = 0;
    ((igMetaField *)temp_s1)->_shallowCopyMethod = 2;
    igMetaObject_NameFields(temp_s0, &g_igGroup_fieldTable[0], &DAT_0048bff0[0], &DAT_0048bff8[0], temp_s2);
}

