int FUN_00231b40(int arg0) {
    FUN_00231cb0();
    return igMetaObject_CreateInstance(*(int *)0x56DAF8, arg0);
}

igMetaObject *igMessageFilter_GetMetaObject(void)
{
    igMetaObject *g = g_igMessageFilter_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_00231cb0();
    return g_igMessageFilter_metaObject[0];
}

int igMessageFilter_GetVTable(void) {
    union U u;
    int temp_s1;
    S_ref *q2;
    S_ref *q3;

    void *temp_a0;
    void *temp_a0_2;

    igObject_InitHeader(u.b);
    q2 = (S_ref *)&u.p[2];
    q3 = (S_ref *)&u.p[3];
    u.w[0] = (int)(&DAT_0052cde0[0]);
    *(int *)q2 = 0;
    *(int *)q3 = 0;
    temp_s1 = *(int *)&u.b[*(int *)((char *)(DAT_00586dc8[0]) + 916)];
    u.w[0] = (int)(&DAT_0052cde0[0]);
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

void FUN_00231cb0(void)
{
    igMetaObject_RunStaticInit(igMessageFilter_Register);
}

void igMessageFilter_Register(void) {
    InsightLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igMessageFilter_metaObject,
        igObject_Register,
        igObject_GetMetaObject_ParentAccessor,
        thunk_igMessageFilter_GetMetaObject,
        igMessageFilter_className,
        0x10, /* instance size */
        igMessageFilter_GetVTable,
        &igMessageFilter_InitFields,
        0, /* extra callback item */
        g_igMessageFilter_callbackList /* callback list */
    );
}

void thunk_igMessageFilter_GetMetaObject(void) {
    igMessageFilter_GetMetaObject();
}

void igMessageFilter_InitFields(void) {
    int temp_s2;
    void *temp_s1_2;
    void *temp_s1;
    void *temp_s0;

    temp_s0 = (void *)DAT_0056daf8[0];
    temp_s2 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &DAT_00497ff8[0], 2);
    temp_s1 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2));
    ((igObjectRefMetaField *)temp_s1)->_metaObject = FUN_002be610();
    ((igRefMetaField *)temp_s1)->_construct = 1;
    temp_s1_2 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 1));
    ((igObjectRefMetaField *)temp_s1_2)->_metaObject = FUN_00231790();
    ((igRefMetaField *)temp_s1_2)->_construct = 1;
    igMetaObject_NameFields(temp_s0, &DAT_00498000[0], &DAT_00498008[0], &DAT_00498010[0], temp_s2);
}

