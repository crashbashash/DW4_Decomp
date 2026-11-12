int FUN_001388f0(void) {
    if (DAT_0055f250[0] == 0) {
        DAT_0055f250[0] = igMetaEnum_Create(&DAT_004d58b8[0], &DAT_00486790[0], &DAT_004867b0[0], 5);
    }
    return DAT_0055f250[0];
}

igMetaObject *FUN_00138950(void) {
    if (g_igCopyRenderDestinationAttr_metaObject[0] == 0) {
        g_igCopyRenderDestinationAttr_metaObject[0] = igMetaObject_Create(Memory_GetAllocatorBySelector(g_metadataAllocatorKey[0]));
    }
    return g_igCopyRenderDestinationAttr_metaObject[0];
}

igMetaObject *igCopyRenderDestinationAttr_GetMetaObject(void)
{
    igMetaObject *g = g_igCopyRenderDestinationAttr_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_00138b20();
    return g_igCopyRenderDestinationAttr_metaObject[0];
}

int igCopyRenderDestinationAttr_GetVTable(void) {
    union U_1389f0 u;
    int temp_s0;
    S_ref *q0;
    S_ref *q1;
    S_ref *q2;

    igObject_InitHeader(u.b);
    u.vt = (int)&DAT_00523dd0[0];
    q2 = (S_ref *)&u.b[16];
    *(int *)q2 = 0;
    q1 = (S_ref *)&u.b[20];
    *(int *)q1 = 0;
    q0 = (S_ref *)&u.b[24];
    *(int *)q0 = 0;
    temp_s0 = *(int *)&u.b[*(int *)((char *)(g_objectSystem[0]) + 916)];
    u.vt = (int)&DAT_00523dd0[0];
    if (q0 != 0) {
        q0 = *(S_ref **)q0;
        if (q0 != 0) {
            q0->f4 = (int)((int) (q0->f4 - 1));
            if (((unsigned long long) ((long long) q0->f4 << 0x29) >> 0x29) == 0) {
                igObject_Destroy(q0);
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
    if (q2 != 0) {
        q2 = *(S_ref **)q2;
        if (q2 != 0) {
            q2->f4 = (int)((int) (q2->f4 - 1));
            if (((unsigned long long) ((long long) q2->f4 << 0x29) >> 0x29) == 0) {
                igObject_Destroy(q2);
            }
        }
    }
    return temp_s0;
}

void FUN_00138b20(void)
{
    igMetaObject_RunStaticInit(igCopyRenderDestinationAttr_Register);
}

void igCopyRenderDestinationAttr_Register(void) {
    AttrsLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igCopyRenderDestinationAttr_metaObject,
        igVisualAttribute_Register,
        igVisualAttribute_GetPublishedMetaObject,
        thunk_igCopyRenderDestinationAttr_GetMetaObject,
        igCopyRenderDestinationAttr_className,
        0x34, /* instance size */
        igCopyRenderDestinationAttr_GetVTable,
        &igCopyRenderDestinationAttr_InitFields,
        0, /* extra callback item */
        g_igCopyRenderDestinationAttr_callbackList /* callback list */
    );
}

void thunk_igCopyRenderDestinationAttr_GetMetaObject(void) {
    igCopyRenderDestinationAttr_GetMetaObject();
}

void igCopyRenderDestinationAttr_InitFields(void) {
    int temp_s2;
    void *temp_v0;
    void *temp_s1_3;
    void *temp_s1_2;
    void *temp_s1;
    void *temp_s0;

    temp_s0 = (void *)g_igCopyRenderDestinationAttr_metaObject[0];
    temp_s2 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &DAT_004867e0[0], 0xA);
    temp_v0 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2));
    FUN_002dc7a0(temp_v0, &DAT_00486898[0]);
    ((igEnumMetaField *)temp_v0)->_getMetaEnumFunction = (int)(&FUN_001388f0);
    temp_s1 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 1));
    ((igObjectRefMetaField *)temp_s1)->_metaObject = (int)FUN_001341f0();
    temp_s1_2 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 2));
    ((igObjectRefMetaField *)temp_s1_2)->_metaObject = FUN_0014dfb0();
    temp_s1_3 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 3));
    ((igObjectRefMetaField *)temp_s1_3)->_metaObject = (int)FUN_00132ba0();
    igMetaObject_NameFields(temp_s0, &DAT_00486810[0], &DAT_00486840[0], &DAT_00486870[0], temp_s2);
}

