igMetaObject *FUN_0036c680(void) {
    igMetaObject *g = g_beAction2InfoRam_metaObject[0];
    int t;
    if (!g || !(t = (g->_validity & 4) != 0))
        FUN_0036c810();
    return g_beAction2InfoRam_metaObject[0];
}

int beAction2InfoRam_GetVTable(void) {
    union U_36c6d0 u;
    int t;
    char *o;
    int *temp_v1;
    int *temp_a1;
    int temp_v0;

    igObject_InitHeader(u.b);
    *(int *)&u.b[40] = 0;
    u.vt = (int)&DAT_00534350[0];
    *(int *)&u.b[44] = 0;
    *(int *)&u.b[48] = 0;
    *(int *)&u.b[52] = 0;
    *(int *)&u.b[56] = 0;
    t = *(int *)&u.b[*(int *)((char *)(g_objectSystem[0]) + 916)];
    u.vt = (int)&DAT_00534350[0];
    FUN_0036c790((void **)(&u.b[56]), (short)(-1));
    FUN_001aa310(&u.b[52], -1);
    FUN_001a7a00(&u.b[48], -1);
    FUN_0034c1b0((void **)(&u.b[44]), (short)(-1));
    FUN_0033e920((S *)u.b, (long long)0);
    return t;
}

void **FUN_0036c790(void **arg0, short arg1) {
    S_temp_a0_36c790 *temp_a0;

    if (arg0 != 0) {
        temp_a0 = (S_temp_a0_36c790 *)(*arg0);
        if (temp_a0 != 0) {
            temp_a0->f4 = (int)((int) (temp_a0->f4 - 1));
            if ((temp_a0->f4 & 0x7FFFFF) == 0) {
                igObject_Destroy(temp_a0);
            }
        }
        if (arg1 > 0) {
            FUN_00100610(arg0);
        }
    }
    return arg0;
}

void FUN_0036c810(void)
{
    igMetaObject_RunStaticInit(beAction2InfoRam_Register);
}

void *beAction2InfoRam_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beAction2InfoRam_metaObject,
        beBaseInfoRam_Register,
        beBaseInfoRam_GetPublishedMetaObject,
        beAction2InfoRam_GetMetaObject,
        beAction2InfoRam_className,
        0x3c, /* instance size */
        beAction2InfoRam_GetVTable,
        beAction2InfoRam_InitFields,
        0, /* extra callback item */
        g_beAction2InfoRam_callbackList /* callback list */
    );
}

void beAction2InfoRam_GetMetaObject(void)
{
    FUN_0036c680();
}

void beAction2InfoRam_InitFields(void) {
    void *temp_s2;
    void *temp_s2_2;
    void *temp_s2_3;
    void *temp_s2_4;
    void *temp_s1;
    int temp_s0;

    temp_s1 = (void *)g_beAction2InfoRam_metaObject[0];
    temp_s0 = igMetaObject_GetFieldCount(temp_s1);
    igMetaObject_CreateFields(temp_s1, &DAT_004c8060[0], 4);
    temp_s2 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s0));
    ((igObjectRefMetaField *)temp_s2)->_metaObject = (int)FUN_0034fd40();
    temp_s2_2 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s0 + 1));
    ((igObjectRefMetaField *)temp_s2_2)->_metaObject = FUN_001a5fe0();
    ((igRefMetaField *)temp_s2_2)->_construct = 1;
    temp_s2_3 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s0 + 2));
    ((igObjectRefMetaField *)temp_s2_3)->_metaObject = FUN_001aa5c0();
    ((igRefMetaField *)temp_s2_3)->_construct = 1;
    temp_s2_4 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s0 + 3));
    ((igObjectRefMetaField *)temp_s2_4)->_metaObject = (int)FUN_0036c2e0();
    igMetaObject_NameFields(temp_s1, &DAT_004c8070[0], &DAT_004c8080[0], &DAT_004c8090[0], temp_s0);
}

