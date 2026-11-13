void FUN_0045cc40(int arg0) {
    FUN_0045cdc0();
    igMetaObject_CreateInstance(*(int *)0x58CCE0, arg0);
}

igMetaObject *igCameraMode_GetMetaObject(void) {
    igMetaObject *g = g_igCameraMode_metaObject[0];
    int t;
    if (!g || !(t = (g->_validity & 4) != 0))
        FUN_0045cdc0();
    return g_igCameraMode_metaObject[0];
}

int igCameraMode_GetVTable(void) {
    union U_45ccd0 u;
    int temp_s1;
    S_ref *q1;
    S_ref *q2;
    
    
    igObject_InitHeader(u.b);
    u.w[0] = (int)(&DAT_00542960[0]);
    igMatrix44f_SetIdentity(&u.w[3]);
    u.w[0] = (int)(&DAT_005428d0[0]);
    q1 = (S_ref *)&u.b[76];
    *(int *)q1 = 0;
    q2 = (S_ref *)&u.b[80];
    *(int *)q2 = 0;
    temp_s1 = *(int *)&u.b[*(int *)((char *)(((void *)g_objectSystem[0])) + 916)];
    u.w[0] = (int)(&DAT_005428d0[0]);
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
    return temp_s1;
}

void FUN_0045cdc0(void)
{
    igMetaObject_RunStaticInit(igCameraMode_Register);
}

void igCameraMode_Register(void) {
    ViewerLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igCameraMode_metaObject,
        igViewMode_Register,
        igViewMode_GetPublishedMetaObject,
        thunk_igCameraMode_GetMetaObject,
        igCameraMode_className,
        0x54, /* instance size */
        igCameraMode_GetVTable,
        &igCameraMode_InitFields,
        0, /* extra callback item */
        g_igCameraMode_callbackList /* callback list */
    );
}

void thunk_igCameraMode_GetMetaObject(void) {
    igCameraMode_GetMetaObject();
}

void igCameraMode_InitFields(void) {
    int temp_s2;
    void *temp_s1;
    void *temp_s1_2;
    void *temp_s0;

    temp_s0 = (void *)g_igCameraMode_metaObject[0];
    temp_s2 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &g_igCameraMode_ctorTable[0], 2);
    temp_s1 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2));
    ((igObjectRefMetaField *)temp_s1)->_metaObject = FUN_0019f670();
    temp_s1_2 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 1));
    ((igObjectRefMetaField *)temp_s1_2)->_metaObject = FUN_001a4560();
    igMetaObject_NameFields(temp_s0, &g_igCameraMode_fieldTable[0], &DAT_004d1670[0], &DAT_004d1678[0], temp_s2);
}

