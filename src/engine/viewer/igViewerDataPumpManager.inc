void FUN_0045be30(int arg0) {
    FUN_0045bfa0();
    igMetaObject_CreateInstance(*(int *)0x58CB70, arg0);
}

void *igViewerDataPumpManager_GetMetaObject(void) {
    igMetaObject *g = g_igViewerDataPumpManager_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false) {
        FUN_0045bfa0();
    }
    return g_igViewerDataPumpManager_metaObject[0];
}

int igViewerDataPumpManager_GetVTable(void) {
    union U_45bec0 u;
    int temp_s1;
    void **q2;
    S_ref *q4;

    int *temp_a1;
    int temp_v0;
    void *temp_a0;
    void *temp_v1;

    igObject_InitHeader(u.b);
    q2 = &u.p[2];
    *q2 = 0;
    u.w[0] = (int)(&DAT_00542310[0]);
    q4 = (S_ref *)&u.p[4];
    *(int *)q4 = 0;
    temp_s1 = *(int *)&u.b[*(int *)((char *)(((void *)g_objectSystem[0])) + 916)];
    u.w[0] = (int)(&DAT_00542310[0]);
    if (q4 != 0) {
        q4 = *(S_ref **)q4;
        if (q4 != 0) {
            q4->f4 = (int)((int) (q4->f4 - 1));
            if (((unsigned long long) ((long long) q4->f4 << 0x29) >> 0x29) == 0) {
                igObject_Destroy(q4);
            }
        }
    }
    u.w[0] = (int)(&DAT_00524950[0]);
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

void FUN_0045bfa0(void)
{
    igMetaObject_RunStaticInit(igViewerDataPumpManager_Register);
}

void igViewerDataPumpManager_Register(void) {
    ViewerLibrary_MarkRegistered();  /* one-shot static-init latch (sets a gp-relative byte flag once) */
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igViewerDataPumpManager_metaObject,
        igInfoManager_Register,
        igInfoManager_GetPublishedMetaObject,
        thunk_igViewerDataPumpManager_GetMetaObject,
        igViewerDataPumpManager_className,
        0x14, /* instance size */
        igViewerDataPumpManager_GetVTable,
        &igViewerDataPumpManager_InitFields_0045c040[0],                              /* field adder: InitFields, registers the reflected fields */
        0, /* extra callback item */
        g_igViewerDataPumpManager_callbackList /* callback list */
    );
}

void thunk_igViewerDataPumpManager_GetMetaObject(void) {
    igViewerDataPumpManager_GetMetaObject();
}

void FUN_0045c040(void) {
    int temp_s2;
    int temp_s3;
    void **temp_v0;
    void *temp_s0;
    void *temp_s1;
    void *temp_v0_2;

    temp_s1 = (void *)(((void *)g_igViewerDataPumpManager_metaObject[0]));
    temp_s2 = igMetaObject_GetFieldCount(temp_s1);
    igMetaObject_CreateFields(temp_s1, &DAT_004d1358[0], 1);
    temp_v0 = (void **)(igMetaObject_FindFieldByName(temp_s1, &DAT_0051ee50[0]));
    temp_s3 = ObjectPointerList_FindIndex(*(int *)((char *)(temp_s1) + 40), temp_v0);
    temp_v0_2 = (void *)(((DW4VC_84_1 *)(temp_v0))->vX((int)(1)));
    igStringMetaField_SetDefaultText(temp_v0_2, &DAT_0051f500[0]);
    *(int *)((char *)(temp_v0_2) + 28) = (int)(&DAT_0058cb78[0]);
    igMetaObject_FinalizeAndReplaceField(temp_s1, temp_s3, temp_v0_2);
    *(int *)((char *)(temp_v0_2) + 4) = (int)((int) (*(int *)((char *)(temp_v0_2) + 4) - 1));
    if (((unsigned long long) ((long long) *(int *)((char *)(temp_v0_2) + 4) << 0x29) >> 0x29) == 0) {
        igObject_Destroy(temp_v0_2);
    }
    temp_s0 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s2));
    *(int *)((char *)(temp_s0) + 56) = FUN_001e5150();
    *(char *)((char *)(temp_s0) + 52) = 1;
    igMetaObject_NameFields(temp_s1, &DAT_004d1360[0], &DAT_004d1368[0], &DAT_004d1370[0], temp_s2);
}

