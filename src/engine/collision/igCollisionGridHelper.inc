igMetaObject *igCollisionGridHelper_GetMetaObject(void)
{
    igMetaObject *g = g_igCollisionGridHelper_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_00239ee0();
    return g_igCollisionGridHelper_metaObject[0];
}

int igCollisionGridHelper_GetVTable(void) {
    union U_239e00 u;
    int temp_s1;
    S_ref *q2;
    S_ref *q3;

    void *temp_a0;
    void *temp_a0_2;

    igObject_InitHeader(u.b);
    q2 = (S_ref *)&u.p[2];
    q3 = (S_ref *)&u.p[3];
    u.w[0] = (int)(&DAT_0052d360[0]);
    *(int *)q2 = 0;
    *(int *)q3 = 0;
    temp_s1 = *(int *)&u.b[*(int *)((char *)(g_objectSystem[0]) + 916)];
    u.w[0] = (int)(&DAT_0052d360[0]);
    if (q3 != 0) {
        q3 = *(S_ref **)q3;
        if (q3 != 0) {
            q3->f4 = (int)((int) (q3->f4 - 1));
            if (((unsigned long long) ((long long) q3->f4 << 0x29) >> 0x29) == 0) {
                igObject_Destroy(q3);
            }
        }
    }
    if (q2 != 0) {
        q2 = *(S_ref **)q2;
        if (q2 != 0) {
            q2->f4 = (int)((int) (q2->f4 - 1));
            if (((unsigned long long) ((long long) q2->f4 << 0x29) >> 0x29) == 0) {
                igObject_Destroy(q2);
            }
        }
    }
    return temp_s1;
}

void FUN_00239ee0(void)
{
    igMetaObject_RunStaticInit(igCollisionGridHelper_Register);
}

void igCollisionGridHelper_Register(void) {
    CollisionLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igCollisionGridHelper_metaObject,
        igObject_Register,
        igObject_GetMetaObject_ParentAccessor,
        thunk_igCollisionGridHelper_GetMetaObject,
        igCollisionGridHelper_className,
        0x10, /* instance size */
        igCollisionGridHelper_GetVTable,
        &igCollisionGridHelper_InitFields,
        0, /* extra callback item */
        g_igCollisionGridHelper_callbackList /* callback list */
    );
}

void thunk_igCollisionGridHelper_GetMetaObject(void) {
    igCollisionGridHelper_GetMetaObject();
}

void igCollisionGridHelper_InitFields(void) {
    int temp_s2;
    void *temp_s1_2;
    void *temp_s1;
    void *temp_s0;

    temp_s0 = (void *)g_igCollisionGridHelper_metaObject[0];
    temp_s2 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &g_igCollisionGridHelper_ctorTable[0], 2);
    temp_s1 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2));
    ((igObjectRefMetaField *)temp_s1)->_metaObject = (int)FUN_0023a080();
    temp_s1_2 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 1));
    ((igObjectRefMetaField *)temp_s1_2)->_metaObject = FUN_002be610();
    FUN_00303460(temp_s1_2, igCollisionGroup_GetMetaObject());
    igMetaObject_NameFields(temp_s0, &g_igCollisionGridHelper_fieldTable[0], &DAT_00498460[0], &DAT_00498468[0], temp_s2);
}

