void beModelCtrlInfoRideOn4_Create(int arg0) {
    FUN_003515b0();
    igMetaObject_CreateInstance(*(int *)0x588A20, arg0);
}

void *FUN_00351460(void) {
    unsigned char b;
    if (g_beModelCtrlInfoRideOn4_metaObject[0] != 0) {
        b = (*(int *)((char *)(g_beModelCtrlInfoRideOn4_metaObject[0]) + 36) & 4) != 0;
        if (b != 0) goto done;
    }
    FUN_003515b0();
done:
    return g_beModelCtrlInfoRideOn4_metaObject[0];
}

int beModelCtrlInfoRideOn4_GetVTable(void) {
    RideOn4View info;
    return *(int *)((char *)&info + *(int *)((char *)g_objectSystem[0] + 916));
}

void FUN_003515b0(void)
{
    igMetaObject_RunStaticInit(beModelCtrlInfoRideOn4_Register);
}

void *beModelCtrlInfoRideOn4_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beModelCtrlInfoRideOn4_metaObject,
        beModelCtrlInfoRideOn_Register,
        beModelCtrlInfoRideOn_GetPublishedMetaObject,
        beModelCtrlInfoRideOn4_GetMetaObject,
        beModelCtrlInfoRideOn4_className,
        0x78, /* instance size */
        beModelCtrlInfoRideOn4_GetVTable,
        beModelCtrlInfoRideOn4_InitFields,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void beModelCtrlInfoRideOn4_GetMetaObject(void)
{
    FUN_00351460();
}

igMetaObject *FUN_00351660(void) {
    return g_beModelCtrlInfoRideOn_metaObject[0];
}

void beModelCtrlInfoRideOn4_InitFields(void) {
    int temp_s2;
    int temp_s3;
    void **temp_v0;
    void *temp_s1;
    T_351670 *temp_v0_2;

    temp_s1 = (void *)(g_beModelCtrlInfoRideOn4_metaObject[0]);
    temp_s2 = igMetaObject_GetFieldCount(temp_s1);
    igMetaObject_CreateFields(temp_s1, &g_beModelCtrlInfoRideOn4_ctorTable[0], 5);
    temp_v0 = (void **)(igMetaObject_FindFieldByName(temp_s1, &text_modelRamNo[0]));
    temp_s3 = ObjectPointerList_FindIndex(*(int *)((char *)(temp_s1) + 40), temp_v0);
    temp_v0_2 = (T_351670 *)(((DW4VC_84_1 *)(temp_v0))->vX((int)(1)));
    igIntMetaField_SetDefault(temp_v0_2, 0x68);
    temp_v0_2->f1c = &DAT_00588a28[0];
    igMetaObject_FinalizeAndReplaceField(temp_s1, temp_s3, temp_v0_2);
    temp_v0_2->refs = temp_v0_2->refs - 1;
    if (((unsigned long long) ((long long) temp_v0_2->refs << 0x29) >> 0x29) == 0) {
        igObject_Destroy(temp_v0_2);
    }
    igMetaObject_NameFields(temp_s1, &g_beModelCtrlInfoRideOn4_fieldTable[0], &DAT_004c5150[0], &DAT_004c5170[0], temp_s2);
}

