igMetaObject *FUN_00352cd0(void) {
    if (g_beModelCtrlInfo_metaObject[0] == 0 || !isValid(g_beModelCtrlInfo_metaObject[0])) FUN_00352da0();
    return g_beModelCtrlInfo_metaObject[0];
}

int beModelCtrlInfo_GetVTable(void) {
    union U_352d20 u;
    int temp_s0;

    igObject_InitHeader(u.b);
    u.w[2] = 0;
    u.w[5] = 0;
    u.w[6] = 0;
    u.w[0] = (int)(&DAT_00537c10[0]);
    u.w[7] = 0;
    temp_s0 = *(int *)&u.b[*(int *)((char *)(g_objectSystem[0]) + 916)];
    u.w[0] = (int)(&DAT_00537c10[0]);
    StringRef_Destruct_00130720(&u.w[7], -1);
    FUN_0033ec80((struct S_33ec80 *)(&u.w[0]), (short)0);
    return temp_s0;
}

void FUN_00352da0(void)
{
    igMetaObject_RunStaticInit(beModelCtrlInfo_Register);
}

void *beModelCtrlInfo_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beModelCtrlInfo_metaObject,
        beBaseInfo_Register,
        beBaseInfo_GetPublishedMetaObject,
        beModelCtrlInfo_GetMetaObject,
        beModelCtrlInfo_className,
        0x20, /* instance size */
        beModelCtrlInfo_GetVTable,
        beModelCtrlInfo_InitFields,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void beModelCtrlInfo_GetMetaObject(void)
{
    FUN_00352cd0();
}

void beModelCtrlInfo_InitFields(void) {
    int temp_s1;
    void *temp_s0;

    temp_s0 = (void *)g_beModelCtrlInfo_metaObject[0];
    temp_s1 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &DAT_004c5450[0], 1);
    igStringMetaField_SetDefaultText(((int)igMetaObject_GetFieldAt(temp_s0, temp_s1)), 0);
    igMetaObject_NameFields(temp_s0, &DAT_004c5458[0], &DAT_004c5460[0], &DAT_004c5468[0], temp_s1);
}

