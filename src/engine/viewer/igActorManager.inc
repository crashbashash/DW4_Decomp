void FUN_0045e230(int arg0) {
    FUN_0045e4a0();
    igMetaObject_CreateInstance(*(int *)0x58CE60, arg0);
}

void *igActorManager_GetMetaObject(void) {
    igMetaObject *g = g_igActorManager_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false) {
        FUN_0045e4a0();
    }
    return g_igActorManager_metaObject[0];
}

int igActorManager_GetVTable(void) {
    struct Obj_45e2c0 obj;
    int t;
    igObject_InitHeader(&obj);
    obj.w2 = 0;
    obj.vt = &DAT_005429f0[0];
    obj.w4 = 0;
    obj.w5 = 0;
    obj.w6 = 0;
    obj.w7 = 0;
    obj.w8 = 0;
    obj.w9 = 0;
    obj.w10 = 0;
    obj.w11 = 0;
    obj.w12 = 0;
    obj.w13 = 0;
    t = *(int *)((char *)&obj + *(int *)((char *)(((void *)g_objectSystem[0])) + 916));
    obj.vt = &DAT_005429f0[0];
    FUN_0014aa70(&obj.w13, -1);
    FUN_004584f0(&obj.w12, -1);
    FUN_0019ab90(&obj.w11, -1);
    FUN_0019ab90(&obj.w10, -1);
    FUN_0013a880(&obj.w9, -1);
    FUN_00135430(&obj.w8, -1);
    FUN_0045e420((O *)&obj.w7, -1);
    FUN_001aa310(&obj.w6, -1);
    FUN_001958f0(&obj.w5, -1);
    FUN_001a7a00(&obj.w4, -1);
    FUN_00231030(&obj, 0);
    return t;
}

O *FUN_0045e420(O *arg0, short arg1) {
    if (arg0) {
        S_temp_a0 *t = arg0->m;
        if (t) { t->f4 -= 1; if ((t->f4 & 0x7fffff) == 0) igObject_Destroy(t); }
        if (arg1 > 0) __dl__FPv(arg0);
    }
    return arg0;
}

void FUN_0045e4a0(void)
{
    igMetaObject_RunStaticInit(igActorManager_Register);
}

void igActorManager_Register(void) {
    ViewerLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igActorManager_metaObject,
        igInfoManager_Register,
        igInfoManager_GetPublishedMetaObject,
        thunk_igActorManager_GetMetaObject,
        igActorManager_className,
        0x38, /* instance size */
        igActorManager_GetVTable,
        &igActorManager_InitFields,
        0, /* extra callback item */
        g_igActorManager_callbackList /* callback list */
    );
}

void thunk_igActorManager_GetMetaObject(void) {
    igActorManager_GetMetaObject();
}

void igActorManager_InitFields(void) {
    int temp_s1;
    void *temp_s2;
    void *temp_s2_10;
    void *temp_s2_2;
    void *temp_s2_3;
    void *temp_s2_4;
    void *temp_s2_5;
    void *temp_s2_6;
    void *temp_s2_7;
    void *temp_s2_8;
    void *temp_s2_9;
    void *temp_s0;

    temp_s0 = (void *)g_igActorManager_metaObject[0];
    temp_s1 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &g_igActorManager_ctorTable[0], 0xA);
    temp_s2 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s1));
    ((igObjectRefMetaField *)temp_s2)->_metaObject = FUN_001a5fe0();
    ((igRefMetaField *)temp_s2)->_construct = 1;
    temp_s2_2 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s1 + 1));
    ((igObjectRefMetaField *)temp_s2_2)->_metaObject = FUN_0019cbe0();
    ((igRefMetaField *)temp_s2_2)->_construct = 1;
    temp_s2_3 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s1 + 2));
    ((igObjectRefMetaField *)temp_s2_3)->_metaObject = FUN_001aa5c0();
    ((igRefMetaField *)temp_s2_3)->_construct = 1;
    temp_s2_4 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s1 + 3));
    ((igObjectRefMetaField *)temp_s2_4)->_metaObject = (int)FUN_0045e6f0();
    ((igRefMetaField *)temp_s2_4)->_construct = 1;
    temp_s2_5 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s1 + 4));
    ((igObjectRefMetaField *)temp_s2_5)->_metaObject = FUN_002c9170();
    ((igRefMetaField *)temp_s2_5)->_construct = 1;
    temp_s2_6 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s1 + 5));
    ((igObjectRefMetaField *)temp_s2_6)->_metaObject = FUN_002c8e50();
    ((igRefMetaField *)temp_s2_6)->_construct = 1;
    temp_s2_7 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s1 + 6));
    ((igObjectRefMetaField *)temp_s2_7)->_metaObject = FUN_00130440();
    ((igRefMetaField *)temp_s2_7)->_construct = 1;
    temp_s2_8 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s1 + 7));
    ((igObjectRefMetaField *)temp_s2_8)->_metaObject = FUN_00130440();
    ((igRefMetaField *)temp_s2_8)->_construct = 1;
    temp_s2_9 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s1 + 8));
    ((igObjectRefMetaField *)temp_s2_9)->_metaObject = (int)FUN_00459380();
    temp_s2_10 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s1 + 9));
    ((igObjectRefMetaField *)temp_s2_10)->_metaObject = igObjectList_GetOrCreateMetaObject();
    ((igRefMetaField *)temp_s2_10)->_construct = 1;
    igMetaObject_NameFields(temp_s0, &g_igActorManager_fieldTable[0], &DAT_004d1a50[0], &DAT_004d1a80[0], temp_s1);
}

