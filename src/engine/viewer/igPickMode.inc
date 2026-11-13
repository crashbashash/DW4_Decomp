void FUN_0045c170(int arg0) {
    FUN_0045c330();
    igMetaObject_CreateInstance(*(int *)0x58CB88, arg0);
}

void *igPickMode_GetMetaObject(void) {
    igMetaObject *g = g_igPickMode_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false) {
        FUN_0045c330();
    }
    return g_igPickMode_metaObject[0];
}

int igPickMode_GetVTable(void) {
    struct Obj_45c200 obj;
    int r;

    igObject_InitHeader(&obj);
    obj.vt = &DAT_00542960[0];
    igMatrix44f_SetIdentity(&obj.w[2]);
    obj.vt = &DAT_00542720[0];
    obj.w[18] = 0;
    obj.w[19] = 0;
    obj.w[20] = 0;
    obj.w[21] = 0;
    obj.w[23] = 0;
    obj.w[24] = 0;
    obj.w[27] = 0;
    igMatrix44f_SetIdentity(&obj.w[28]);
    r = *(int *)((char *)&obj + *(int *)((char *)(((void *)g_objectSystem[0])) + 916));
    obj.vt = &DAT_00542720[0];
    FUN_001d6560(&obj.w[27], -1);
    FUN_0019e3c0(&obj.w[24], -1);
    FUN_0044ee80(&obj.w[23], -1);
    FUN_0044e1e0(&obj.w[21], -1);
    FUN_0044e1e0(&obj.w[20], -1);
    FUN_00459ae0((O *)&obj.w[19], -1);
    FUN_00459860((ObjectRefWord *)&obj.w[18], -1);
    return r;
}

void FUN_0045c330(void)
{
    igMetaObject_RunStaticInit(igPickMode_Register);
}

void igPickMode_Register(void) {
    ViewerLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igPickMode_metaObject,
        igViewMode_Register,
        igViewMode_GetPublishedMetaObject,
        thunk_igPickMode_GetMetaObject,
        igPickMode_className,
        0xBC, /* instance size */
        igPickMode_GetVTable,
        &igPickMode_InitFields,
        0, /* extra callback item */
        g_igPickMode_callbackList /* callback list */
    );
}

void thunk_igPickMode_GetMetaObject(void) {
    igPickMode_GetMetaObject();
}

void igPickMode_InitFields(void) {
    void *temp_s2;
    void *temp_s2_2;
    void *temp_s2_3;
    void *temp_s2_4;
    void *temp_s2_5;
    void *temp_s2_6;
    void *temp_s2_7;
    void *temp_s1;
    int temp_s0;
    int sp48[2];
    void *temp_a0;

    temp_s1 = (void *)g_igPickMode_metaObject[0];
    temp_s0 = igMetaObject_GetFieldCount(temp_s1);
    igMetaObject_CreateFields(temp_s1, &g_igPickMode_ctorTable[0], 0xC);
    temp_s2 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s0));
    ((igObjectRefMetaField *)temp_s2)->_metaObject = (int)FUN_0045b420();
    temp_s2_2 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s0 + 1));
    ((igObjectRefMetaField *)temp_s2_2)->_metaObject = FUN_0044ded0();
    temp_s2_3 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s0 + 2));
    ((igObjectRefMetaField *)temp_s2_3)->_metaObject = FUN_0044e430();
    temp_s2_4 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s0 + 3));
    ((igObjectRefMetaField *)temp_s2_4)->_metaObject = FUN_0044e430();
    temp_s2_5 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s0 + 5));
    ((igObjectRefMetaField *)temp_s2_5)->_metaObject = FUN_0019dfd0();
    ((igObjectRefMetaField *)temp_s2_5)->_construct = 1;
    temp_s2_6 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s0 + 6));
    ((igObjectRefMetaField *)temp_s2_6)->_metaObject = FUN_00188260();
    ((igObjectRefMetaField *)temp_s2_6)->_construct = 1;
    FUN_002e3810(igMetaObject_GetFieldAt(temp_s1, temp_s0 + 7), 0.0f);
    temp_s2_7 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s0 + 9));
    ((igObjectRefMetaField *)temp_s2_7)->_metaObject = FUN_0019f670();
    temp_a0 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s0 + 0xB));
    sp48[0] = 0;
    sp48[1] = 0;
    FUN_0018e2f0(temp_a0, sp48);
    igMetaObject_NameFields(temp_s1, &g_igPickMode_fieldTable[0], &DAT_004d1400[0], &DAT_004d1430[0], temp_s0);
}

