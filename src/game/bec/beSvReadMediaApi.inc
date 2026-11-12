void FUN_00349270(int arg0) {
    FUN_00349430();
    igMetaObject_CreateInstance(*(int *)0x588238, arg0);
}

igMetaObject *FUN_003492b0(void) {
    if (g_beSvReadMediaApi_metaObject[0] == 0 || !isValid(g_beSvReadMediaApi_metaObject[0])) FUN_00349430();
    return g_beSvReadMediaApi_metaObject[0];
}

int beSvReadMediaApi_GetVTable(void) {
    struct Obj_349300 obj;
    int t;

    igObject_InitHeader(&obj);
    obj.w12 = 0;
    obj.w13 = 0;
    obj.w14 = 0;
    obj.vt = &DAT_0053be40[0];
    obj.w17 = 0;
    obj.w19 = 0;
    obj.w20 = 0;
    t = *(int *)((char *)&obj + *(int *)((char *)(g_objectSystem[0]) + 916));
    obj.vt = &DAT_0053be40[0];
    FUN_0014aa70(&obj.w20, -1);
    FUN_003493b0((O *)&obj.w19, (short)(-1));
    FUN_00349080((void **)&obj.w17, (long long)(-1));
    FUN_00348390((struct S_348390 *)&obj, (short)0);
    return t;
}

O *FUN_003493b0(O *arg0, short arg1) {
    if (arg0) {
        S_temp_a0 *t = arg0->m;
        if (t) { t->f4 -= 1; if ((t->f4 & 0x7fffff) == 0) igObject_Destroy(t); }
        if (arg1 > 0) FUN_00100610(arg0);
    }
    return arg0;
}

void FUN_00349430(void)
{
    igMetaObject_RunStaticInit(beSvReadMediaApi_Register);
}

void *beSvReadMediaApi_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beSvReadMediaApi_metaObject,
        beSaveApi_Register,
        beSaveApi_GetPublishedMetaObject,
        beSvReadMediaApi_GetMetaObject,
        beSvReadMediaApi_className,
        0x58, /* instance size */
        beSvReadMediaApi_GetVTable,
        beSvReadMediaApi_InitFields,
        0, /* extra callback item */
        g_beSvReadMediaApi_callbackList /* callback list */
    );
}

void beSvReadMediaApi_GetMetaObject(void)
{
    FUN_003492b0();
}

void beSvReadMediaApi_InitFields(void) {
    int temp_s2;
    void *temp_s1;
    void *temp_s1_2;
    void *temp_s1_3;
    void *temp_s1_4;
    void *temp_s0;

    temp_s0 = (void *)g_beSvReadMediaApi_metaObject[0];
    temp_s2 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &DAT_004c40b0[0], 5);
    temp_s1 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2));
    ((igObjectRefMetaField *)temp_s1)->_metaObject = (int)FUN_0034a210();
    temp_s1_2 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 1));
    ((igObjectRefMetaField *)temp_s1_2)->_metaObject = (int)FUN_0034aeb0();
    ((igObjectRefMetaField *)temp_s1_2)->_refCounted = 0;
    FUN_002ea4b0(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 2), 0x10);
    temp_s1_3 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 3));
    ((igObjectRefMetaField *)temp_s1_3)->_metaObject = (int)FUN_0034aeb0();
    temp_s1_4 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 4));
    ((igObjectRefMetaField *)temp_s1_4)->_metaObject = igObjectList_GetOrCreateMetaObject();
    ((igRefMetaField *)temp_s1_4)->_construct = 1;
    igMetaObject_NameFields(temp_s0, &DAT_004c40d0[0], &DAT_004c40f0[0], &DAT_004c4110[0], temp_s2);
}

