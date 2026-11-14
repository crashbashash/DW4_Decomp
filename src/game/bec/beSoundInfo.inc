igMetaObject *FUN_00343d20(void)
{
    igMetaObject *g = g_beSoundInfo_metaObject[0];
    bool t;
    if (!g || (t = g->_validity & 4) == 0)
        FUN_00343e00();
    return g_beSoundInfo_metaObject[0];
}

int beSoundInfo_GetVTable(void) {
    union U u;
    int temp_s1;
    char *p1;

    igObject_InitHeader(u.b);
    *(int *)&u.b[8] = 0;
    *(int *)&u.b[20] = 0;
    *(int *)&u.b[24] = 0;
    u.vt = (int)&DAT_005393b0[0];
    p1 = &u.b[28];
    *(int *)p1 = 0;
    *(int *)&u.b[32] = 0;
    temp_s1 = *(int *)&u.b[*(int *)((char *)(g_objectSystem[0]) + 916)];
    u.vt = (int)&DAT_005393b0[0];
    StringRef_Destruct_00130720(&u.b[32], -1);
    FUN_00199450(p1, -1);
    FUN_0033ec80((struct S_33ec80 *)u.b, (short)0);
    return temp_s1;
}

void FUN_00343e00(void)
{
    igMetaObject_RunStaticInit(beSoundInfo_Register);
}

void *beSoundInfo_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beSoundInfo_metaObject,
        beBaseInfo_Register,
        beBaseInfo_GetPublishedMetaObject,
        beSoundInfo_GetMetaObject,
        beSoundInfo_className,
        0x28, /* instance size */
        beSoundInfo_GetVTable,
        beSoundInfo_InitFields,
        0, /* extra callback item */
        g_beSoundInfo_callbackList /* callback list */
    );
}

void beSoundInfo_GetMetaObject(void)
{
    FUN_00343d20();
}

void beSoundInfo_InitFields(void) {
    int temp_s2;
    void *temp_s1;
    void *temp_s0;

    temp_s0 = (void *)g_beSoundInfo_metaObject[0];
    temp_s2 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &g_beSoundInfo_ctorTable[0], 4);
    temp_s1 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2));
    ((igObjectRefMetaField *)temp_s1)->_metaObject = igNamedObjectList_GetOrCreateMetaObject();
    igMetaObject_NameFields(temp_s0, &g_beSoundInfo_fieldTable[0], &DAT_004c3810[0], &DAT_004c3820[0], temp_s2);
}

