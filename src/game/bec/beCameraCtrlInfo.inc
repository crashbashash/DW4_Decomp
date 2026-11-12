void *FUN_00368d60(void) {
    igMetaObject *g = g_beCameraCtrlInfo_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false) {
        FUN_00368e30();
    }
    return g_beCameraCtrlInfo_metaObject[0];
}

int beCameraCtrlInfo_GetVTable(void) {
    struct Obj_368db0 obj;
    int temp_s0;

    igObject_InitHeader(&obj);
    obj.f8 = 0;
    obj.f14 = 0;
    obj.f18 = 0;
    obj.vt = (&DAT_00534a90[0]);
    obj.f1C = 0;
    temp_s0 = *(int *)((char *)&obj + *(int *)((char *)(g_objectSystem[0]) + 916));
    obj.vt = (&DAT_00534a90[0]);
    ObjectRef_Destruct_001363f0(&obj.f1C, -1);
    FUN_0033ec80((struct S_33ec80 *)&obj, (short)0);
    return temp_s0;
}

void FUN_00368e30(void)
{
    igMetaObject_RunStaticInit(beCameraCtrlInfo_Register);
}

void *beCameraCtrlInfo_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beCameraCtrlInfo_metaObject,
        beBaseInfo_Register,
        beBaseInfo_GetPublishedMetaObject,
        beCameraCtrlInfo_GetMetaObject,
        beCameraCtrlInfo_className,
        0x20, /* instance size */
        beCameraCtrlInfo_GetVTable,
        beCameraCtrlInfo_InitFields,
        0, /* extra callback item */
        g_beCameraCtrlInfo_callbackList /* callback list */
    );
}

void beCameraCtrlInfo_GetMetaObject(void)
{
    FUN_00368d60();
}

void beCameraCtrlInfo_InitFields(void) {
    int temp_s1;
    void *f;
    void *temp_s0;

    temp_s0 = (void *)g_beCameraCtrlInfo_metaObject[0];
    temp_s1 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &DAT_004c7858[0], 1);
    f = igMetaObject_GetFieldAt(temp_s0, temp_s1);
    *(int *)((char *)f + 56) = g_igObject_metaObject[0];
    igMetaObject_NameFields(temp_s0, &DAT_004c7860[0], &DAT_004c7868[0], &DAT_004c7870[0], temp_s1);
}

