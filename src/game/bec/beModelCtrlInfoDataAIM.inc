void *FUN_00353e90(void) {
    igMetaObject *g = g_beModelCtrlInfoDataAIM_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false) {
        FUN_00353fc0();
    }
    return g_beModelCtrlInfoDataAIM_metaObject[0];
}

int beModelCtrlInfoDataAIM_GetVTable(void) {
    union U_353ee0 u;
    int t;
    char *o;
    int *a1;
    int v0;
    S_ref *p0, *p1;

    igObject_InitHeader(u.b);
    p0 = (S_ref *)&u.b[8];
    *(int *)p0 = 0;
    u.vt = (int)&DAT_005379d0[0];
    p1 = (S_ref *)&u.b[16];
    *(int *)p1 = 0;
    t = *(int *)&u.b[*(int *)((char *)(g_objectSystem[0]) + 916)];
    u.vt = (int)&DAT_005379d0[0];
    if (p1 != 0) {
        p1 = *(S_ref **)p1;
        if (p1 != 0) {
            p1->f4 = (int)((int) (p1->f4 - 1));
            if (((unsigned long long) ((long long) p1->f4 << 0x29) >> 0x29) == 0) {
                igObject_Destroy(p1);
            }
        }
    }
    u.vt = (int)&g_igNamedObject_vtable[0];
    if (p0 != 0) {
        o = *(char **)p0;
        if (o != 0) {
            a1 = (int *)(o - 8);
            v0 = *(int *)(o - 4) - 1;
            *(int *)(o - 4) = v0;
            if (v0 == 0) {
                StringChunk_ReleaseHeader(*a1, a1);
            }
        }
    }
    return t;
}

void FUN_00353fc0(void)
{
    igMetaObject_RunStaticInit(beModelCtrlInfoDataAIM_Register);
}

void *beModelCtrlInfoDataAIM_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beModelCtrlInfoDataAIM_metaObject,
        beBaseInfoData_Register,
        beBaseInfoData_GetPublishedMetaObject,
        beModelCtrlInfoDataAIM_GetMetaObject,
        beModelCtrlInfoDataAIM_className,
        0x14, /* instance size */
        beModelCtrlInfoDataAIM_GetVTable,
        beModelCtrlInfoDataAIM_InitFields,
        0, /* extra callback item */
        g_beModelCtrlInfoDataAIM_callbackList /* callback list */
    );
}

void beModelCtrlInfoDataAIM_GetMetaObject(void)
{
    FUN_00353e90();
}

void beModelCtrlInfoDataAIM_InitFields(void) {
    int temp_s2;
    int temp_s3;
    void **temp_v0;
    void *temp_s0;
    void *temp_s1;
    T_temp_v0_2 *temp_v0_2;

    temp_s1 = (void *)(((void * *)g_beModelCtrlInfoDataAIM_metaObject)[0]);
    temp_s2 = igMetaObject_GetFieldCount(temp_s1);
    igMetaObject_CreateFields(temp_s1, &DAT_004c55c8[0], 1);
    temp_v0 = (void **)(igMetaObject_FindFieldByName(temp_s1, &DAT_00502218[0]));
    temp_s3 = ObjectPointerList_FindIndex(*(int *)((char *)(temp_s1) + 40), temp_v0);
    temp_v0_2 = (T_temp_v0_2 *)(((DW4VC_84_1 *)(temp_v0))->vX((int)(1)));
    igStringMetaField_SetDefaultText(temp_v0_2, &DAT_00503cc8[0]);
    temp_v0_2->f28 = (int)(&DAT_00588c88[0]);
    igMetaObject_FinalizeAndReplaceField(temp_s1, temp_s3, temp_v0_2);
    temp_v0_2->references = temp_v0_2->references - 1;
    if (((unsigned long long)(long long)temp_v0_2->references & 0x7fffffULL) == 0) {
        igObject_Destroy(temp_v0_2);
    }
    temp_s0 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s2));
    *(int *)((char *)(temp_s0) + 56) = (int)FUN_003541b0();
    *(char *)((char *)(temp_s0) + 52) = 1;
    igMetaObject_NameFields(temp_s1, &DAT_004c55d0[0], &DAT_004c55d8[0], &DAT_004c55e0[0], temp_s2);
}

