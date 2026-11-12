void FUN_00349d70(int arg0) {
    FUN_00349e90();
    igMetaObject_CreateInstance(*(int *)0x588280, arg0);
}

void *FUN_00349db0(void) {
    igMetaObject *g = g_beSvFileMakeApi_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false) {
        FUN_00349e90();
    }
    return g_beSvFileMakeApi_metaObject[0];
}

int beSvFileMakeApi_GetVTable(void) {
    struct Obj_349e00 obj;
    int r;

    igObject_InitHeader(&obj);
    obj.w[11] = 0;
    obj.w[12] = 0;
    obj.w[13] = 0;
    obj.vt = &DAT_0053c000[0];
    obj.w[15] = 0;
    obj.w[16] = 0;
    r = *(int *)((char *)&obj + *(int *)((char *)(g_objectSystem[0]) + 916));
    obj.vt = &DAT_0053c000[0];
    FUN_003484b0((struct Ref **)(&obj.w[16]), (short)(-1));
    FUN_00349080((void **)(&obj.w[15]), (long long)(-1));
    FUN_00348390((struct S_348390 *)&obj, (short)0);
    return r;
}

void FUN_00349e90(void)
{
    igMetaObject_RunStaticInit(beSvFileMakeApi_Register);
}

void *beSvFileMakeApi_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beSvFileMakeApi_metaObject,
        beSaveApi_Register,
        beSaveApi_GetPublishedMetaObject,
        beSvFileMakeApi_GetMetaObject,
        beSvFileMakeApi_className,
        0x418, /* instance size */
        beSvFileMakeApi_GetVTable,
        beSvFileMakeApi_InitFields,
        0, /* extra callback item */
        g_beSvFileMakeApi_callbackList /* callback list */
    );
}

void beSvFileMakeApi_GetMetaObject(void)
{
    FUN_00349db0();
}

void beSvFileMakeApi_InitFields(void) {
    int temp_s2;
    void *temp_s1_2;
    void *temp_s1;
    void *temp_s0;

    temp_s0 = (void *)g_beSvFileMakeApi_metaObject[0];
    temp_s2 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &DAT_004c4138[0], 2);
    temp_s1 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2));
    ((igObjectRefMetaField *)temp_s1)->_metaObject = (int)FUN_0034a210();
    temp_s1_2 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 1));
    ((igObjectRefMetaField *)temp_s1_2)->_metaObject = (int)FUN_0034ac90();
    igMetaObject_NameFields(temp_s0, &DAT_004c4140[0], &DAT_004c4148[0], &DAT_004c4150[0], temp_s2);
}

