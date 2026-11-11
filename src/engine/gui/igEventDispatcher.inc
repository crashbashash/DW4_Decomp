int FUN_004513b0(void) {
    if (DAT_0058c578[0] == 0) {
        DAT_0058c578[0] = igMetaObject_Create(Memory_GetAllocatorBySelector(DAT_00587040[0]));
    }
    return DAT_0058c578[0];
}

igMetaObject *igEventDispatcher_GetMetaObject(void)
{
    igMetaObject *g = g_igEventDispatcher_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        igEventDispatcher_EnsureRegistered();
    return g_igEventDispatcher_metaObject[0];
}

int igEventDispatcher_GetVTable(void) {
    union U_451450 u;
    int temp_s2;
    S_ref *q2;
    S_ref *q1;
    S_ref *q3;
    
    
    igObject_InitHeader(u.b);
    q1 = (S_ref *)&u.b[8];
    *(int *)q1 = 0;
    u.w[0] = (int)(&DAT_005413d0[0]);
    q2 = (S_ref *)&u.b[12];
    *(int *)q2 = 0;
    q3 = (S_ref *)&u.b[16];
    *(int *)q3 = 0;
    temp_s2 = *(int *)&u.b[*(int *)((char *)(DAT_00586dc8[0]) + 916)];
    u.w[0] = (int)(&DAT_005413d0[0]);
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
    u.w[0] = (int)(&DAT_00524da0[0]);
    if (q1 != 0) {
        q1 = *(S_ref **)q1;
        if (q1 != 0) {
            q1->f4 = (int)((int) (q1->f4 - 1));
            if (((unsigned long long) ((long long) q1->f4 << 0x29) >> 0x29) == 0) {
                igObject_Destroy(q1);
            }
        }
    }
    return temp_s2;
}

void igEventDispatcher_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(igEventDispatcher_Register);
}

void igEventDispatcher_Register(void) {
    GuiLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igEventDispatcher_metaObject,
        igInterfaceManager_Register,
        igInterfaceManager_GetPublishedMetaObject,
        thunk_igEventDispatcher_GetMetaObject,
        igEventDispatcher_className,
        0x14, /* instance size */
        igEventDispatcher_GetVTable,
        &igEventDispatcher_InitFields,
        0, /* extra callback item */
        g_igEventDispatcher_callbackList /* callback list */
    );
}

void thunk_igEventDispatcher_GetMetaObject(void) {
    igEventDispatcher_GetMetaObject();
}

void igEventDispatcher_InitFields(void) {
    int temp_s2;
    void *temp_s1_2;
    void *temp_s1;
    void *temp_s0;

    temp_s0 = (void *)DAT_0058c578[0];
    temp_s2 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &DAT_004d0738[0], 2);
    temp_s1 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2));
    ((igObjectRefMetaField *)temp_s1)->_metaObject = FUN_00451050();
    ((igRefMetaField *)temp_s1)->_construct = 1;
    temp_s1_2 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 1));
    ((igObjectRefMetaField *)temp_s1_2)->_metaObject = FUN_00146660();
    ((igRefMetaField *)temp_s1_2)->_construct = 1;
    igMetaObject_NameFields(temp_s0, &DAT_004d0740[0], &DAT_004d0748[0], &DAT_004d0750[0], temp_s2);
}

