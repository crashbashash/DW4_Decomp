void FUN_0035dbd0(int arg0) {
    FUN_0035dd30();
    igMetaObject_CreateInstance(*(int *)0x589380, arg0);
}

int FUN_0035dc10(void) {
    if (((int *)DAT_00589380)[0] == 0) {
        ((int *)DAT_00589380)[0] = igMetaObject_Create(Memory_GetAllocatorBySelector(DAT_00587040[0]));
    }
    return ((int *)DAT_00589380)[0];
}

void *FUN_0035dc60(void) {
    struct G *g = DAT_00589380[0];
    if (!g || ((g->f & 4) != 0) == false) {
        FUN_0035dd30();
    }
    return DAT_00589380[0];
}

int beHitLandModelTraversal_GetVTable(void) {
    union U_35dcb0 u;
    int t;
    char *ps;

    igObject_InitHeader(u.b);
    *(int *)&u.b[28] = 0;
    *(int *)&u.b[32] = 0;
    *(int *)&u.b[36] = 0;
    *(int *)&u.b[40] = 0;
    *(int *)&u.b[52] = 0;
    *(int *)&u.b[56] = 0;
    u.vt = (int)&DAT_00536360[0];
    ps = &u.b[64];
    *(int *)ps = 0;
    t = *(int *)&u.b[*(int *)((char *)(DAT_00586dc8[0]) + 916)];
    u.vt = (int)&DAT_00536360[0];
    FUN_0035d930((void **)ps, -1);
    FUN_0019e150(u.b, 0);
    return t;
}

void FUN_0035dd30(void)
{
    igMetaObject_RunStaticInit(beHitLandModelTraversal_Register);
}

void *beHitLandModelTraversal_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beHitLandModelTraversal_metaObject,
        igIntersectTraversal_Register,
        igIntersectTraversal_GetPublishedMetaObject,
        beHitLandModelTraversal_GetMetaObject,
        beHitLandModelTraversal_className,
        0x48, /* instance size */
        beHitLandModelTraversal_GetVTable,
        beHitLandModelTraversal_InitFields,
        0, /* extra callback item */
        g_beHitLandModelTraversal_callbackList /* callback list */
    );
}

void beHitLandModelTraversal_GetMetaObject(void)
{
    FUN_0035dc60();
}

int FUN_0035ddf0(void) {
    return DAT_00561930[0];
}

void beHitLandModelTraversal_InitFields(void) {
    int temp_s2;
    void *temp_s1;
    void *temp_s0;

    temp_s0 = (void *)((int *)DAT_00589380)[0];
    temp_s2 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &DAT_004c6670[0], 1);
    temp_s1 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2));
    ((igObjectRefMetaField *)temp_s1)->_metaObject = FUN_0035ded0();
    igMetaObject_NameFields(temp_s0, &DAT_004c6678[0], &DAT_004c6680[0], &DAT_004c6688[0], temp_s2);
}

