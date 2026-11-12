void FUN_00369820(int arg0) {
    FUN_00369a20();
    igMetaObject_CreateInstance(*(int *)0x589C90, arg0);
}

int FUN_00369860(void) {
    if (((int *)DAT_00589c90)[0] == 0) {
        ((int *)DAT_00589c90)[0] = igMetaObject_Create(Memory_GetAllocatorBySelector(DAT_00587040[0]));
    }
    return ((int *)DAT_00589c90)[0];
}

void *FUN_003698b0(void) {
    struct G *g = DAT_00589c90[0];
    if (!g || ((g->f & 4) != 0) == false) {
        FUN_00369a20();
    }
    return DAT_00589c90[0];
}

int beCameraCtrl_GetVTable(void) {
    CameraCtrlView camera;
    return *(int *)((char *)&camera + *(int *)((char *)DAT_00586dc8[0] + 916));
}

void **FUN_003699a0(void **arg0, long long arg1) {
    char *o;

    if (arg0 != 0) {
        o = (char *)*arg0;
        if (o != 0) {
            *(int *)(o + 4) = *(int *)(o + 4) - 1;
            if ((*(int *)(o + 4) & 0x7FFFFF) == 0) {
                igObject_Destroy(o);
            }
        }
        if ((short)arg1 > 0) {
            FUN_00100610(arg0);
        }
    }
    return arg0;
}

void FUN_00369a20(void)
{
    igMetaObject_RunStaticInit(beCameraCtrl_Register);
}

void *beCameraCtrl_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beCameraCtrl_metaObject,
        beBaseInfoManager_Register,
        beBaseInfoManager_GetPublishedMetaObject,
        beCameraCtrl_GetMetaObject,
        beCameraCtrl_className,
        0xdc, /* instance size */
        beCameraCtrl_GetVTable,
        beCameraCtrl_InitFields,
        0, /* extra callback item */
        g_beCameraCtrl_callbackList /* callback list */
    );
}

void beCameraCtrl_GetMetaObject(void)
{
    FUN_003698b0();
}

void beCameraCtrl_InitFields(void) {
    int temp_s2;
    void *temp_s1;
    void *temp_s1_2;
    void *temp_s1_3;
    void *temp_s0;

    temp_s0 = (void *)((int *)DAT_00589c90)[0];
    temp_s2 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &DAT_004c7a60[0], 0xD);
    temp_s1 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2));
    *(int *)((char *)(temp_s1) + 56) = FUN_00459380();
    *(char *)((char *)(temp_s1) + 60) = 0;
    temp_s1_2 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 1));
    *(int *)((char *)(temp_s1_2) + 56) = FUN_0045b420();
    *(char *)((char *)(temp_s1_2) + 60) = 0;
    temp_s1_3 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 2));
    *(int *)((char *)(temp_s1_3) + 56) = FUN_00368a30();
    FUN_002e3810(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 0xB), 1.0f);
    FUN_002d3890(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 0xC), 1);
    igMetaObject_NameFields(temp_s0, &DAT_004c7aa0[0], &DAT_004c7ae0[0], &DAT_004c7b20[0], temp_s2);
}

