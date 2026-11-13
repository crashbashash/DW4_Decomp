void beNDMWStatusCtrlSkill_Create(int arg0) {
    FUN_003b93e0();
    igMetaObject_CreateInstance(*(int *)0x58AE68, arg0);
}

void *FUN_003b92f0(void) {
    igMetaObject *g = g_beNDMWStatusCtrlSkill_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false) {
        FUN_003b93e0();
    }
    return g_beNDMWStatusCtrlSkill_metaObject[0];
}

int beNDMWStatusCtrlSkill_GetVTable(void) {
    union U_3b9340 u;
    int temp_s1;
    char *p1;

    igObject_InitHeader(u.b);
    *(int *)&u.b[52] = 0;
    *(int *)&u.b[56] = 0;
    *(int *)&u.b[60] = 0;
    *(int *)&u.b[64] = 0;
    *(int *)&u.b[68] = 0;
    *(int *)&u.b[72] = 0;
    *(int *)&u.b[76] = 0;
    u.vt = (int)&DAT_0053ec80[0];
    p1 = &u.b[100];
    *(int *)p1 = 0;
    *(int *)&u.b[104] = 0;
    temp_s1 = *(int *)&u.b[*(int *)((char *)(g_objectSystem[0]) + 916)];
    u.vt = (int)&DAT_0053ec80[0];
    ObjectRef_Destruct_00150eb0(&u.b[104], -1);
    FUN_003b8980((ObjectRefWord *)p1, -1);
    FUN_003b6770((int **)u.b, (long long)0);
    return temp_s1;
}

void FUN_003b93e0(void)
{
    igMetaObject_RunStaticInit(beNDMWStatusCtrlSkill_Register);
}

void *beNDMWStatusCtrlSkill_Register(void) {
    NdmwLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beNDMWStatusCtrlSkill_metaObject,
        beNDMWListCtrl_Register,
        beNDMWListCtrl_GetPublishedMetaObject,
        beNDMWStatusCtrlSkill_GetMetaObject,
        beNDMWStatusCtrlSkill_className,
        0x6c, /* instance size */
        beNDMWStatusCtrlSkill_GetVTable,
        beNDMWStatusCtrlSkill_InitFields,
        0, /* extra callback item */
        g_beNDMWStatusCtrlSkill_callbackList /* callback list */
    );
}

void beNDMWStatusCtrlSkill_GetMetaObject(void)
{
    FUN_003b92f0();
}

void beNDMWStatusCtrlSkill_InitFields(void) {
    int temp_s2;
    void *temp_s1_2;
    void *temp_s1;
    void *temp_s0;

    temp_s0 = (void *)g_beNDMWStatusCtrlSkill_metaObject[0];
    temp_s2 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &DAT_004c9d08[0], 3);
    temp_s1 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 1));
    ((igObjectRefMetaField *)temp_s1)->_metaObject = (int)FUN_003c9480();
    ((igRefMetaField *)temp_s1)->_construct = 1;
    temp_s1_2 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 2));
    ((igObjectRefMetaField *)temp_s1_2)->_metaObject = igIntList_GetOrCreateMetaObject();
    ((igRefMetaField *)temp_s1_2)->_construct = 1;
    igMetaObject_NameFields(temp_s0, &DAT_004c9d18[0], &DAT_004c9d28[0], &DAT_004c9d38[0], temp_s2);
}

