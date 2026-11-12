void FUN_001a4830(int arg0) {
    FUN_001a4970();
    igMetaObject_CreateInstance(*(int *)0x561EF0, arg0);
}

igMetaObject *igBoundingBoxesMaker_GetMetaObject(void)
{
    igMetaObject *g = g_igBoundingBoxesMaker_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_001a4970();
    return g_igBoundingBoxesMaker_metaObject[0];
}

int igBoundingBoxesMaker_GetVTable(void) {
    struct Obj_1a48c0 obj;
    int r;

    igObject_InitHeader(&obj);
    obj.vt = &DAT_0052a4a0[0];
    obj.w[4] = 0;
    obj.w[5] = 0;
    obj.w[7] = 0;
    obj.w[8] = 0;
    r = *(int *)((char *)&obj + *(int *)((char *)(g_objectSystem[0]) + 916));
    obj.vt = &DAT_0052a4a0[0];
    FUN_0013a880(&obj.w[8], -1);
    FUN_001489a0(&obj.w[7], -1);
    FUN_0014dd40(&obj.w[5], -1);
    FUN_00198190((void * *)&obj.w[4], -1);
    return r;
}

void FUN_001a4970(void)
{
    igMetaObject_RunStaticInit(igBoundingBoxesMaker_Register);
}

void igBoundingBoxesMaker_Register(void) {
    SceneGraphLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        ((char *)g_igBoundingBoxesMaker_metaObject),
        igObject_Register,
        igObject_GetMetaObject_ParentAccessor,
        thunk_igBoundingBoxesMaker_GetMetaObject,
        igBoundingBoxesMaker_className,
        0x28, /* instance size */
        igBoundingBoxesMaker_GetVTable,
        &igBoundingBoxesMaker_InitFields,
        0, /* extra callback item */
        g_igBoundingBoxesMaker_callbackList /* callback list */
    );
}

void thunk_igBoundingBoxesMaker_GetMetaObject(void) {
    igBoundingBoxesMaker_GetMetaObject();
}

void igBoundingBoxesMaker_InitFields(void) {
    int temp_s2;
    void *temp_s1_4;
    void *temp_s1_3;
    void *temp_s1_2;
    void *temp_s1;
    void *temp_s0;

    temp_s0 = (void *)g_igBoundingBoxesMaker_metaObject[0];
    temp_s2 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &DAT_0048cad0[0], 8);
    FUN_002ebc00(((void *)igMetaObject_GetFieldAt(temp_s0, temp_s2)), -1);
    FUN_002d3890(((void *)igMetaObject_GetFieldAt(temp_s0, temp_s2 + 1)), 1);
    FUN_002d3890(((void *)igMetaObject_GetFieldAt(temp_s0, temp_s2 + 2)), 1);
    temp_s1 = (void *)(((void *)igMetaObject_GetFieldAt(temp_s0, temp_s2 + 3)));
    ((igObjectRefMetaField *)temp_s1)->_metaObject = FUN_0018a6a0();
    ((igRefMetaField *)temp_s1)->_construct = 1;
    temp_s1_2 = (void *)(((void *)igMetaObject_GetFieldAt(temp_s0, temp_s2 + 4)));
    ((igObjectRefMetaField *)temp_s1_2)->_metaObject = FUN_002bcbb0();
    FUN_002d3890(((void *)igMetaObject_GetFieldAt(temp_s0, temp_s2 + 5)), 1);
    temp_s1_3 = (void *)(((void *)igMetaObject_GetFieldAt(temp_s0, temp_s2 + 6)));
    ((igObjectRefMetaField *)temp_s1_3)->_metaObject = FUN_002b9540();
    temp_s1_4 = (void *)(((void *)igMetaObject_GetFieldAt(temp_s0, temp_s2 + 7)));
    ((igObjectRefMetaField *)temp_s1_4)->_metaObject = FUN_002c8e50();
    igMetaObject_NameFields(temp_s0, &DAT_0048caf0[0], &DAT_0048cb10[0], &DAT_0048cb30[0], temp_s2);
}

