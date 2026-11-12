void FUN_001a5d30(int arg0) {
    FUN_001a5e90();
    igMetaObject_CreateInstance(*(int *)0x562078, arg0);
}

int FUN_001a5d70(void) {
    if (DAT_00562078[0] == 0) {
        DAT_00562078[0] = igMetaObject_Create(Memory_GetAllocatorBySelector(DAT_00587040[0]));
    }
    return DAT_00562078[0];
}

igMetaObject *igAttrSet_GetMetaObject(void)
{
    igMetaObject *g = g_igAttrSet_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_001a5e90();
    return g_igAttrSet_metaObject[0];
}

int igAttrSet_GetVTable(void) {
    Obj_1a5e10 o;
    int r;

    igObject_InitHeader(&o);
    o.w[1] = 0;
    o.w[2] = 0;
    o.w[3] = 0;
    o.w[6] = 0;
    o.vt = &DAT_005294b0[0];
    o.s = 0;
    r = *(int *)((char *)&o + *(int *)((char *)(DAT_00586dc8[0]) + 916));
    o.vt = &DAT_005294b0[0];
    FUN_0013bfe0(&o.s, -1);
    FUN_00195a90((struct T_195a90 *)&o, 0);
    return r;
}

void FUN_001a5e90(void)
{
    igMetaObject_RunStaticInit(igAttrSet_Register);
}

void igAttrSet_Register(void) {
    SceneGraphLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        ((char *)g_igAttrSet_metaObject),
        igGroup_Register,
        igGroup_GetPublishedMetaObject,
        thunk_igAttrSet_GetMetaObject,
        igAttrSet_className,
        0x28, /* instance size */
        igAttrSet_GetVTable,
        &igAttrSet_InitFields,
        0, /* extra callback item */
        g_igAttrSet_callbackList /* callback list */
    );
}

void thunk_igAttrSet_GetMetaObject(void) {
    igAttrSet_GetMetaObject();
}

void igAttrSet_InitFields(void) {
    int temp_s2;
    void *temp_s1;
    void *temp_s0;

    temp_s0 = (void *)DAT_00562078[0];
    temp_s2 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &DAT_0048ce18[0], 2);
    temp_s1 = (void *)(((void *)igMetaObject_GetFieldAt(temp_s0, temp_s2)));
    ((igObjectRefMetaField *)temp_s1)->_metaObject = FUN_0013af00();
    ((igRefMetaField *)temp_s1)->_construct = 1;
    ((igMetaField *)temp_s1)->_deepCopyMethod = 0;
    ((igMetaField *)temp_s1)->_shallowCopyMethod = 2;
    igMetaObject_NameFields(temp_s0, &DAT_0048ce20[0], &DAT_0048ce28[0], &DAT_0048ce30[0], temp_s2);
}

