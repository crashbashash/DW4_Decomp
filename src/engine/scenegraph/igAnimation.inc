int FUN_001a90f0(int arg0) {
    FUN_001a9290();
    return igMetaObject_CreateInstance(*(int *)0x562370, arg0);
}

int FUN_001a9130(void) {
    if (DAT_00562370[0] == 0) {
        DAT_00562370[0] = igMetaObject_Create(Memory_GetAllocatorBySelector(DAT_00587040[0]));
    }
    return DAT_00562370[0];
}

igMetaObject *igAnimation_GetMetaObject(void)
{
    igMetaObject *g = g_igAnimation_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_001a9290();
    return g_igAnimation_metaObject[0];
}

int igAnimation_GetVTable(void) {
    union U_1a91d0 u;
    int temp_s;
    char *p104;
    char *p100;
    char *p96;
    igObject_InitHeader(u.b);
    u.vt = (int)&DAT_0052a9b0[0];
    *(int *)&u.b[8] = 0;
    p96 = &u.b[16];
    *(int *)p96 = 0;
    p100 = &u.b[20];
    *(int *)p100 = 0;
    p104 = &u.b[24];
    *(int *)p104 = 0;
    *(int *)&u.b[56] = 0;
    temp_s = *(int *)&u.b[*(int *)((char *)(DAT_00586dc8[0]) + 916)];
    u.vt = (int)&DAT_0052a9b0[0];
    FUN_00196a50((struct R * *)&u.b[56], -1);
    FUN_0019de50((struct Ref * *)p104, -1);
    FUN_0019ded0((void * *)p100, -1);
    FUN_0019df50((O *)p96, -1);
    FUN_00131bc0(u.b, 0);
    return temp_s;
}

void FUN_001a9290(void)
{
    igMetaObject_RunStaticInit(igAnimation_Register);
}

void igAnimation_Register(void) {
    SceneGraphLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        ((char *)g_igAnimation_metaObject),
        igNamedObject_Register,
        igNamedObject_GetPublishedMetaObject,
        thunk_igAnimation_GetMetaObject,
        igAnimation_className,
        0x40, /* instance size */
        igAnimation_GetVTable,
        &igAnimation_InitFields,
        0, /* extra callback item */
        g_igAnimation_callbackList /* callback list */
    );
}

void thunk_igAnimation_GetMetaObject(void) {
    igAnimation_GetMetaObject();
}

void igAnimation_InitFields(void) {
    int temp_s0;
    void *temp_s2;
    void *temp_s2_2;
    void *temp_s2_3;
    void *temp_s2_4;
    void *temp_s1;

    temp_s1 = (void *)DAT_00562370[0];
    temp_s0 = igMetaObject_GetFieldCount(temp_s1);
    igMetaObject_CreateFields(temp_s1, &DAT_0048d510[0], 8);
    temp_s2 = (void *)(((void *)igMetaObject_GetFieldAt(temp_s1, temp_s0 + 1)));
    ((igObjectRefMetaField *)temp_s2)->_metaObject = FUN_001a8ac0();
    ((igRefMetaField *)temp_s2)->_construct = 1;
    temp_s2_2 = (void *)(((void *)igMetaObject_GetFieldAt(temp_s1, temp_s0 + 2)));
    ((igObjectRefMetaField *)temp_s2_2)->_metaObject = FUN_001a9d90();
    ((igRefMetaField *)temp_s2_2)->_construct = 1;
    temp_s2_3 = (void *)(((void *)igMetaObject_GetFieldAt(temp_s1, temp_s0 + 3)));
    ((igObjectRefMetaField *)temp_s2_3)->_metaObject = FUN_001a9420();
    ((igRefMetaField *)temp_s2_3)->_construct = 1;
    temp_s2_4 = (void *)(((void *)igMetaObject_GetFieldAt(temp_s1, temp_s0 + 7)));
    ((igObjectRefMetaField *)temp_s2_4)->_metaObject = FUN_001a4d90();
    igMetaObject_NameFields(temp_s1, &DAT_0048d530[0], &DAT_0048d550[0], &DAT_0048d570[0], temp_s0);
}

