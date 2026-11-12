igMetaObject *FUN_003c9480(void) {
    if (g_beNDMWShinkaCtrl_metaObject[0] == 0) {
        g_beNDMWShinkaCtrl_metaObject[0] = igMetaObject_Create(Memory_GetAllocatorBySelector(g_metadataAllocatorKey[0]));
    }
    return g_beNDMWShinkaCtrl_metaObject[0];
}

void *beNDMWShinkaCtrl_ResolveMetaObject(void) {
    igMetaObject *g = g_beNDMWShinkaCtrl_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false) {
        FUN_003c9650();
    }
    return g_beNDMWShinkaCtrl_metaObject[0];
}

int beNDMWShinkaCtrl_GetVTable(void) {
    union U_3c9520 u;
    int temp_s2;
    S_ref * q1;
    S_ref * q0;
    S_ref * q2;
    int *temp_a1;
    int temp_v0;
    void *temp_a0;
    void *temp_v1;

    igObject_InitHeader(u.b);
    u.vt = (int)(&DAT_0053c680[0]);
    q0 = (S_ref *)&u.b[20];
    *(int *)q0 = 0;
    q1 = (S_ref *)&u.b[24];
    *(int *)q1 = 0;
    q2 = (S_ref *)&u.b[28];
    *(int *)q2 = 0;
    temp_s2 = *(int *)&u.b[*(int *)((char *)(g_objectSystem[0]) + 916)];
    u.vt = (int)(&DAT_0053c680[0]);
    if (q2 != 0) {
        q2 = *(S_ref **)q2;
        if (q2 != 0) {
            q2->f4 = (int)((int) (q2->f4 - 1));
            if (((unsigned long long) ((long long) q2->f4 << 0x29) >> 0x29) == 0) {
                igObject_Destroy(q2);
            }
        }
    }
    if (q1 != 0) {
        q1 = *(S_ref **)q1;
        if (q1 != 0) {
            q1->f4 = (int)((int) (q1->f4 - 1));
            if (((unsigned long long) ((long long) q1->f4 << 0x29) >> 0x29) == 0) {
                igObject_Destroy(q1);
            }
        }
    }
    if (q0 != 0) {
        q0 = *(S_ref **)q0;
        if (q0 != 0) {
            q0->f4 = (int)((int) (q0->f4 - 1));
            if (((unsigned long long) ((long long) q0->f4 << 0x29) >> 0x29) == 0) {
                igObject_Destroy(q0);
            }
        }
    }
    return temp_s2;
}

void FUN_003c9650(void)
{
    igMetaObject_RunStaticInit(beNDMWShinkaCtrl_Register);
}

void *beNDMWShinkaCtrl_Register(void) {
    NdmwLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beNDMWShinkaCtrl_metaObject,
        igObject_Register,
        igObject_GetMetaObject_ParentAccessor,
        beNDMWShinkaCtrl_GetMetaObject,
        beNDMWShinkaCtrl_className,
        0x20, /* instance size */
        beNDMWShinkaCtrl_GetVTable,
        beNDMWShinkaCtrl_InitFields,
        0, /* extra callback item */
        g_beNDMWShinkaCtrl_callbackList /* callback list */
    );
}

void beNDMWShinkaCtrl_GetMetaObject(void)
{
    beNDMWShinkaCtrl_ResolveMetaObject();
}

void beNDMWShinkaCtrl_InitFields(void) {
    int temp_s2;
    void *temp_s1_5;
    void *temp_s1_4;
    void *temp_s1_3;
    void *temp_s1_2;
    void *temp_s1;
    void *temp_s0;

    temp_s0 = (void *)g_beNDMWShinkaCtrl_metaObject[0];
    temp_s2 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &DAT_004cc190[0], 6);
    temp_s1 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2));
    ((igObjectRefMetaField *)temp_s1)->_metaObject = FUN_00357910();
    ((igObjectRefMetaField *)temp_s1)->_refCounted = 0;
    temp_s1_2 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 1));
    ((igObjectRefMetaField *)temp_s1_2)->_metaObject = (int)FUN_003c9ce0();
    ((igObjectRefMetaField *)temp_s1_2)->_refCounted = 0;
    temp_s1_3 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 3));
    ((igObjectRefMetaField *)temp_s1_3)->_metaObject = FUN_00364090();
    temp_s1_4 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 4));
    ((igObjectRefMetaField *)temp_s1_4)->_metaObject = FUN_003658e0();
    temp_s1_5 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 5));
    ((igObjectRefMetaField *)temp_s1_5)->_metaObject = (int)FUN_003c9810();
    ((igRefMetaField *)temp_s1_5)->_construct = 1;
    igMetaObject_NameFields(temp_s0, &DAT_004cc1b0[0], &DAT_004cc1d0[0], &DAT_004cc1f0[0], temp_s2);
}

