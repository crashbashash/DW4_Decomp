void beModelCtrlInfoRideOn3_Create(int arg0) {
    FUN_00351910();
    igMetaObject_CreateInstance(*(int *)0x588A58, arg0);
}

void *FUN_003517c0(void) {
    igMetaObject *g = g_beModelCtrlInfoRideOn3_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false) {
        FUN_00351910();
    }
    return g_beModelCtrlInfoRideOn3_metaObject[0];
}

int beModelCtrlInfoRideOn3_GetVTable(void) {
    RideOn3View info;
    return *(int *)((char *)&info + *(int *)((char *)g_objectSystem[0] + 916));
}

void FUN_00351910(void)
{
    igMetaObject_RunStaticInit(beModelCtrlInfoRideOn3_Register);
}

void *beModelCtrlInfoRideOn3_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beModelCtrlInfoRideOn3_metaObject,
        beModelCtrlInfoRideOn_Register,
        beModelCtrlInfoRideOn_GetPublishedMetaObject,
        beModelCtrlInfoRideOn3_GetMetaObject,
        beModelCtrlInfoRideOn3_className,
        0x70, /* instance size */
        beModelCtrlInfoRideOn3_GetVTable,
        beModelCtrlInfoRideOn3_InitFields,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void beModelCtrlInfoRideOn3_GetMetaObject(void)
{
    FUN_003517c0();
}

void beModelCtrlInfoRideOn3_InitFields(void) {
    int temp_s2;
    int temp_s3;
    void **temp_v0;
    void *temp_s1;
    T_3519c0 *temp_v0_2;

    temp_s1 = (void *)(((void * *)g_beModelCtrlInfoRideOn3_metaObject)[0]);
    temp_s2 = igMetaObject_GetFieldCount(temp_s1);
    igMetaObject_CreateFields(temp_s1, &DAT_004c5190[0], 5);
    temp_v0 = (void **)(igMetaObject_FindFieldByName(temp_s1, &DAT_00503868[0]));
    temp_s3 = ObjectPointerList_FindIndex(*(int *)((char *)(temp_s1) + 40), temp_v0);
    temp_v0_2 = (T_3519c0 *)(((DW4VC_84_1 *)(temp_v0))->vX((int)(1)));
    FUN_002ea4b0(temp_v0_2, 0x67);
    temp_v0_2->f1c = &DAT_00588a60[0];
    igMetaObject_FinalizeAndReplaceField(temp_s1, temp_s3, temp_v0_2);
    temp_v0_2->refs = temp_v0_2->refs - 1;
    if (((unsigned long long) ((long long) temp_v0_2->refs << 0x29) >> 0x29) == 0) {
        igObject_Destroy(temp_v0_2);
    }
    igMetaObject_NameFields(temp_s1, &DAT_004c51b0[0], &DAT_004c51d0[0], &DAT_004c51f0[0], temp_s2);
}

