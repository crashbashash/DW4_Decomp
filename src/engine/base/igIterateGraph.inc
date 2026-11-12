void FUN_00227460(int arg0) {
    FUN_00227620();
    igMetaObject_CreateInstance(*(int *)0x56D948, arg0);
}

int FUN_002274a0(void) {
    if (DAT_0056d948[0] == 0) {
        DAT_0056d948[0] = igMetaObject_Create(Memory_GetAllocatorBySelector(DAT_00587040[0]));
    }
    return DAT_0056d948[0];
}

igMetaObject *igIterateGraph_GetMetaObject(void)
{
    igMetaObject *g = g_igIterateGraph_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_00227620();
    return g_igIterateGraph_metaObject[0];
}

extern "C" int igIterateGraph_GetVTable(void) {
    Obj_6 obj;
    int r;

    igObject_InitHeader(&obj);
    obj.vt = &DAT_0052c460[0];
    obj.m12 = 0;
    obj.m16 = 0;
    r = *(int *)((char *)&obj + *(int *)((char *)(DAT_00586dc8[0]) + 916));
    obj.vt = &DAT_0052c460[0];
    obj.rel16();
    obj.rel12();
    return r;
}

void FUN_00227620(void)
{
    igMetaObject_RunStaticInit(igIterateGraph_Register);
}

void igIterateGraph_Register(void) {
    BaseLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igIterateGraph_metaObject,
        igIterator_Register,
        igIterator_GetPublishedMetaObject,
        thunk_igIterateGraph_GetMetaObject,
        igIterateGraph_className,
        0x14, /* instance size */
        igIterateGraph_GetVTable,
        &igIterateGraph_InitFields,
        0, /* extra callback item */
        g_igIterateGraph_callbackList /* callback list */
    );
}

void thunk_igIterateGraph_GetMetaObject(void) {
    igIterateGraph_GetMetaObject();
}

void igIterateGraph_InitFields(void) {
    int temp_s2;
    void *temp_s1_2;
    void *temp_s1;
    void *temp_s0;

    temp_s0 = (void *)DAT_0056d948[0];
    temp_s2 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &DAT_00497d40[0], 3);
    temp_s1 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2));
    ((igObjectRefMetaField *)temp_s1)->_metaObject = FUN_0019c8c0();
    ((igRefMetaField *)temp_s1)->_construct = 1;
    temp_s1_2 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 1));
    ((igObjectRefMetaField *)temp_s1_2)->_metaObject = igIntList_GetOrCreateMetaObject();
    ((igRefMetaField *)temp_s1_2)->_construct = 1;
    igMetaObject_NameFields(temp_s0, &DAT_00497d50[0], &DAT_00497d60[0], &DAT_00497d70[0], temp_s2);
}

