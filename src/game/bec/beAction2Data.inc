igMetaObject *FUN_0036d9f0(void) {
    if (g_beAction2Data_metaObject[0] == 0) {
        g_beAction2Data_metaObject[0] = igMetaObject_Create(Memory_GetAllocatorBySelector(g_metadataAllocatorKey[0]));
    }
    return g_beAction2Data_metaObject[0];
}

void *FUN_0036da40(void) {
    igMetaObject *g = g_beAction2Data_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false) {
        FUN_0036db70();
    }
    return g_beAction2Data_metaObject[0];
}

int beAction2Data_GetVTable(void) {
    union U_36da90 u;
    int temp_s1;
    void **q2;
    S_ref *q3;
    int *temp_a1;
    int temp_v0;
    void *temp_a0;
    void *temp_v1;

    igObject_InitHeader(u.b);
    q2 = &u.p[2];
    *q2 = 0;
    u.w[0] = (int)(&DAT_00533fc0[0]);
    q3 = (S_ref *)&u.p[3];
    *(int *)q3 = 0;
    temp_s1 = *(int *)&u.b[*(int *)((char *)(g_objectSystem[0]) + 916)];
    u.w[0] = (int)(&DAT_00533fc0[0]);
    if (q3 != 0) {
        q3 = *(S_ref **)q3;
        if (q3 != 0) {
            q3->f4 = (int)((int) (q3->f4 - 1));
            if (((unsigned long long) ((long long) q3->f4 << 0x29) >> 0x29) == 0) {
                igObject_Destroy(q3);
            }
        }
    }
    u.w[0] = (int)(&g_igNamedObject_vtable[0]);
    if (q2 != 0) {
        temp_v1 = *q2;
        if (temp_v1 != 0) {
            temp_a1 = (int *)((char *)temp_v1 - 8);
            temp_v0 = *(int *)((char *)(temp_v1) - 4) - 1;
            *(int *)((char *)(temp_v1) - 4) = temp_v0;
            if (temp_v0 == 0) {
                StringChunk_ReleaseHeader(*temp_a1, temp_a1);
            }
        }
    }
    return temp_s1;
}

void FUN_0036db70(void)
{
    igMetaObject_RunStaticInit(beAction2Data_Register);
}

void *beAction2Data_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beAction2Data_metaObject,
        igNamedObject_Register,
        igNamedObject_GetPublishedMetaObject,
        beAction2Data_GetMetaObject,
        beAction2Data_className,
        0x10, /* instance size */
        beAction2Data_GetVTable,
        beAction2Data_InitFields,
        0, /* extra callback item */
        g_beAction2Data_callbackList /* callback list */
    );
}

void beAction2Data_GetMetaObject(void)
{
    FUN_0036da40();
}

void beAction2Data_InitFields(void) {
    int temp_s2;
    void *temp_s1;
    void *temp_s0;

    temp_s0 = (void *)g_beAction2Data_metaObject[0];
    temp_s2 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &DAT_004c81d0[0], 1);
    temp_s1 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2));
    ((igObjectRefMetaField *)temp_s1)->_metaObject = FUN_002be100();
    ((igRefMetaField *)temp_s1)->_construct = 1;
    igMetaObject_NameFields(temp_s0, &DAT_004c81d8[0], &DAT_004c81e0[0], &DAT_004c81e8[0], temp_s2);
}

int FUN_0036dcd0(void) {
    if (DAT_0058a020[0] == 0) {
        DAT_0058a020[0] = igMetaEnum_Create(&DAT_005016f0[0], &DAT_004c81f0[0], &DAT_004c8210[0], 7);
    }
    return DAT_0058a020[0];
}

