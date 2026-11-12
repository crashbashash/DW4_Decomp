igMetaObject *igCreateCollisionDatabase_GetMetaObject(void)
{
    igMetaObject *g = g_igCreateCollisionDatabase_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_002395b0();
    return g_igCreateCollisionDatabase_metaObject[0];
}

int igCreateCollisionDatabase_GetVTable(void) {
    struct W o;
    int *p18;
    int *p17;
    int *p16;
    int r;
    igObject_InitHeader(&o);
    o.f[7] = 0;
    o.f[8] = 0;
    o.vt = &DAT_0052d130[0];
    p16 = &o.f[12];
    *p16 = 0;
    p17 = &o.f[13];
    *p17 = 0;
    p18 = &o.f[14];
    *p18 = 0;
    o.f[15] = 0;
    r = *(int *)((char *)&o + *(int *)((char *)(g_objectSystem[0]) + 916));
    o.vt = &DAT_0052d130[0];
    FUN_0019c840(&o.f[15], -1);
    FUN_0019c840(p18, -1);
    FUN_00239530((O *)p17, -1);
    StringRef_Destruct_00130720(p16, -1);
    FUN_00225790(&o, 0);
    return r;
}

O *FUN_00239530(O *arg0, short arg1) {
    if (arg0) {
        S_temp_a0 *t = arg0->m;
        if (t) { t->f4 -= 1; if ((t->f4 & 0x7fffff) == 0) igObject_Destroy(t); }
        if (arg1 > 0) FUN_00100610(arg0);
    }
    return arg0;
}

void FUN_002395b0(void)
{
    igMetaObject_RunStaticInit(igCreateCollisionDatabase_Register);
}

void igCreateCollisionDatabase_Register(void) {
    CollisionLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igCreateCollisionDatabase_metaObject,
        igOptBase_Register,
        igOptBase_GetPublishedMetaObject,
        thunk_igCreateCollisionDatabase_GetMetaObject,
        igCreateCollisionDatabase_className,
        0x44, /* instance size */
        igCreateCollisionDatabase_GetVTable,
        &igCreateCollisionDatabase_InitFields,
        0, /* extra callback item */
        g_igCreateCollisionDatabase_callbackList /* callback list */
    );
}

void thunk_igCreateCollisionDatabase_GetMetaObject(void) {
    igCreateCollisionDatabase_GetMetaObject();
}

void igCreateCollisionDatabase_InitFields(void) {
    int temp_s2;
    void *temp_s1_3;
    void *temp_s1_2;
    void *temp_s1;
    void *temp_s0;

    temp_s0 = (void *)g_igCreateCollisionDatabase_metaObject[0];
    temp_s2 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &DAT_00498300[0], 7);
    temp_s1 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2));
    ((igObjectRefMetaField *)temp_s1)->_metaObject = FUN_002be610();
    FUN_00303460(temp_s1, igCollisionGrid_GetMetaObject());
    temp_s1_2 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 1));
    ((igObjectRefMetaField *)temp_s1_2)->_metaObject = FUN_002be610();
    FUN_00303460(temp_s1_2, igCollisionGroup_GetMetaObject());
    FUN_002ea4b0(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 2), 1);
    FUN_002ea4b0(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 3), 1);
    FUN_002ea4b0(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 4), 1);
    igStringMetaField_SetDefaultText(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 5), 0);
    temp_s1_3 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 6));
    ((igObjectRefMetaField *)temp_s1_3)->_metaObject = (int)FUN_0023a080();
    ((igMetaField *)temp_s1_3)->_persistent = 0;
    igMetaObject_NameFields(temp_s0, &DAT_00498320[0], &DAT_00498340[0], &DAT_00498360[0], temp_s2);
}

