void beModelCtrlInfoRideOn2_Create(int arg0) {
    FUN_00351c60();
    igMetaObject_CreateInstance(*(int *)0x588A90, arg0);
}

void *FUN_00351b10(void) {
    igMetaObject *g = g_beModelCtrlInfoRideOn2_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false) {
        FUN_00351c60();
    }
    return g_beModelCtrlInfoRideOn2_metaObject[0];
}

int beModelCtrlInfoRideOn2_GetVTable(void) {
    RideOn2View info;
    return *(int *)((char *)&info + *(int *)((char *)g_objectSystem[0] + 916));
}

void FUN_00351c60(void)
{
    igMetaObject_RunStaticInit(beModelCtrlInfoRideOn2_Register);
}

void *beModelCtrlInfoRideOn2_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beModelCtrlInfoRideOn2_metaObject,
        beModelCtrlInfoRideOn_Register,
        beModelCtrlInfoRideOn_GetPublishedMetaObject,
        beModelCtrlInfoRideOn2_GetMetaObject,
        beModelCtrlInfoRideOn2_className,
        0x60, /* instance size */
        beModelCtrlInfoRideOn2_GetVTable,
        beModelCtrlInfoRideOn2_InitFields,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void beModelCtrlInfoRideOn2_GetMetaObject(void)
{
    FUN_00351b10();
}

void beModelCtrlInfoRideOn2_InitFields(void) {
    int temp_s2;
    int temp_s3;
    void **temp_v0;
    void *temp_s1;
    T_351d10 *temp_v0_2;

    temp_s1 = (void *)(((void * *)g_beModelCtrlInfoRideOn2_metaObject)[0]);
    temp_s2 = igMetaObject_GetFieldCount(temp_s1);
    igMetaObject_CreateFields(temp_s1, &g_beModelCtrlInfoRideOn2_ctorTable[0], 1);
    temp_v0 = (void **)(igMetaObject_FindFieldByName(temp_s1, &text_modelRamNo[0]));
    temp_s3 = ObjectPointerList_FindIndex(*(int *)((char *)(temp_s1) + 40), temp_v0);
    temp_v0_2 = (T_351d10 *)(((DW4VC_84_1 *)(temp_v0))->vX((int)(1)));
    igIntMetaField_SetDefault(temp_v0_2, 0x66);
    temp_v0_2->f28 = (int)(&DAT_00588a98[0]);
    igMetaObject_FinalizeAndReplaceField(temp_s1, temp_s3, temp_v0_2);
    temp_v0_2->references = temp_v0_2->references - 1;
    if (((unsigned long long)(long long)temp_v0_2->references & 0x7fffffULL) == 0) {
        igObject_Destroy(temp_v0_2);
    }
    igMetaObject_NameFields(temp_s1, &g_beModelCtrlInfoRideOn2_fieldTable[0], &DAT_004c5218[0], &DAT_004c5220[0], temp_s2);
}

