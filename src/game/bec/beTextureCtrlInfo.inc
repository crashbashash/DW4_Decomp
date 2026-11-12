S_341be0 *FUN_00341be0(void) {
    S_341be0 *g = DAT_00587c80[0];
    if (g != 0) {
        int b = !!(g->flags & 4);
        if (b) goto done;
    }
    FUN_00341cb0();
done:
    return DAT_00587c80[0];
}

int beTextureCtrlInfo_GetVTable(void) {
    struct Obj obj;
    int temp_s0;

    igObject_InitHeader(&obj);
    obj.f8 = 0;
    obj.f14 = 0;
    obj.f18 = 0;
    obj.vt = (&DAT_00539620[0]);
    obj.f20 = 0;
    temp_s0 = *(int *)((char *)&obj + *(int *)((char *)(DAT_00586dc8[0]) + 916));
    obj.vt = (&DAT_00539620[0]);
    FUN_00199450(&obj.f20, -1);
    FUN_0033ec80((struct S_33ec80 *)&obj, (short)0);
    return temp_s0;
}

void FUN_00341cb0(void)
{
    igMetaObject_RunStaticInit(beTextureCtrlInfo_Register);
}

void *beTextureCtrlInfo_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beTextureCtrlInfo_metaObject,
        beBaseInfo_Register,
        beBaseInfo_GetPublishedMetaObject,
        beTextureCtrlInfo_GetMetaObject,
        beTextureCtrlInfo_className,
        0x24, /* instance size */
        beTextureCtrlInfo_GetVTable,
        beTextureCtrlInfo_InitFields,
        0, /* extra callback item */
        g_beTextureCtrlInfo_callbackList /* callback list */
    );
}

void beTextureCtrlInfo_GetMetaObject(void)
{
    FUN_00341be0();
}

void beTextureCtrlInfo_InitFields(void) {
    int temp_s2;
    void *temp_s1;
    void *temp_s0;

    temp_s0 = (void *)((int *)DAT_00587c80)[0];
    temp_s2 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &DAT_004c3470[0], 2);
    temp_s1 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 1));
    ((igObjectRefMetaField *)temp_s1)->_metaObject = FUN_002be100();
    ((igRefMetaField *)temp_s1)->_construct = 1;
    igMetaObject_NameFields(temp_s0, &DAT_004c3478[0], &DAT_004c3480[0], &DAT_004c3488[0], temp_s2);
}

