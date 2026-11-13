igMetaObject *FUN_0045d100(void) {
    if (g_igViewManager_metaObject[0] == 0) {
        g_igViewManager_metaObject[0] = igMetaObject_Create(Memory_GetAllocatorBySelector(g_metadataAllocatorKey[0]));
    }
    return g_igViewManager_metaObject[0];
}

void *igViewManager_GetMetaObject(void) {
    igMetaObject *g = g_igViewManager_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false) {
        FUN_0045d2f0();
    }
    return g_igViewManager_metaObject[0];
}

int igViewManager_GetVTable(void) {
    union U_45d1a0 u;
    int temp_s3;
    S_ref *q3;
    S_ref *q2;
    S_ref *q1;
    
    
    igObject_InitHeader(u.b);
    u.w[0] = (int)(&DAT_00542690[0]);
    q1 = (S_ref *)&u.b[8];
    *(int *)q1 = 0;
    q2 = (S_ref *)&u.b[12];
    *(int *)q2 = 0;
    q3 = (S_ref *)&u.b[16];
    *(int *)q3 = 0;
    igMatrix44f_SetIdentity(&u.w[5]);
    temp_s3 = *(int *)&u.b[*(int *)((char *)(((void *)g_objectSystem[0])) + 916)];
    u.w[0] = (int)(&DAT_00542680[4]);
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
    if (q1 != 0) {
        q1 = *(S_ref **)q1;
        if (q1 != 0) {
            q1->f4 = (int)((int) (q1->f4 - 1));
            if (((unsigned long long) ((long long) q1->f4 << 0x29) >> 0x29) == 0) {
                igObject_Destroy(q1);
            }
        }
    }
    return temp_s3;
}

void FUN_0045d2f0(void)
{
    igMetaObject_RunStaticInit(igViewManager_Register);
}

void igViewManager_Register(void) {
    ViewerLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igViewManager_metaObject,
        igEventReceiver_Register,
        igEventReceiver_GetPublishedMetaObject,
        thunk_igViewManager_GetMetaObject,
        igViewManager_className,
        0x54, /* instance size */
        igViewManager_GetVTable,
        &igViewManager_InitFields,
        0, /* extra callback item */
        g_igViewManager_callbackList /* callback list */
    );
}

void thunk_igViewManager_GetMetaObject(void) {
    igViewManager_GetMetaObject();
}

void igViewManager_InitFields(void) {
    int temp_s2;
    void *temp_s1_3;
    void *temp_s1_2;
    void *temp_s1;
    void *temp_s0;

    temp_s0 = (void *)g_igViewManager_metaObject[0];
    temp_s2 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &g_igViewManager_ctorTable[0], 4);
    temp_s1 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2));
    ((igObjectRefMetaField *)temp_s1)->_metaObject = (int)FUN_0045cf10();
    ((igRefMetaField *)temp_s1)->_construct = 1;
    temp_s1_2 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 1));
    ((igObjectRefMetaField *)temp_s1_2)->_metaObject = (int)FUN_0045d470();
    ((igRefMetaField *)temp_s1_2)->_construct = 1;
    temp_s1_3 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 2));
    ((igObjectRefMetaField *)temp_s1_3)->_metaObject = igObjectList_GetOrCreateMetaObject();
    ((igRefMetaField *)temp_s1_3)->_construct = 1;
    igMetaObject_NameFields(temp_s0, &g_igViewManager_fieldTable[0], &DAT_004d16d0[0], &DAT_004d16e0[0], temp_s2);
}

