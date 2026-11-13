void beModelCtrlInfoHitBody_Create(int arg0) {
    FUN_003525e0();
    igMetaObject_CreateInstance(*(int *)0x588B00, arg0);
}

igMetaObject *FUN_00352410(void) {
    if (g_beModelCtrlInfoHitBody_metaObject[0] == 0) {
        g_beModelCtrlInfoHitBody_metaObject[0] = igMetaObject_Create(Memory_GetAllocatorBySelector(g_metadataAllocatorKey[0]));
    }
    return g_beModelCtrlInfoHitBody_metaObject[0];
}

void *FUN_00352460(void) {
    igMetaObject *g = g_beModelCtrlInfoHitBody_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false) {
        FUN_003525e0();
    }
    return g_beModelCtrlInfoHitBody_metaObject[0];
}

int beModelCtrlInfoHitBody_GetVTable(void) {
    union U u;
    int temp_s0;
    S_ref *q0;
    S_ref *q1;
    S_ref *q2;

    igObject_InitHeader(u.b);
    u.vt = (int)&DAT_00537dc0[0];
    q2 = (S_ref *)&u.b[32];
    *(int *)q2 = 0;
    q1 = (S_ref *)&u.b[36];
    *(int *)q1 = 0;
    q0 = (S_ref *)&u.b[40];
    *(int *)q0 = 0;
    temp_s0 = *(int *)&u.b[*(int *)((char *)(g_objectSystem[0]) + 916)];
    u.vt = (int)&DAT_00537dc0[0];
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

void FUN_003525e0(void)
{
    igMetaObject_RunStaticInit(beModelCtrlInfoHitBody_Register);
}

void *beModelCtrlInfoHitBody_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beModelCtrlInfoHitBody_metaObject,
        igObject_Register,
        igObject_GetMetaObject_ParentAccessor,
        beModelCtrlInfoHitBody_GetMetaObject,
        beModelCtrlInfoHitBody_className,
        0x30, /* instance size */
        beModelCtrlInfoHitBody_GetVTable,
        beModelCtrlInfoHitBody_InitFields,
        0, /* extra callback item */
        g_beModelCtrlInfoHitBody_callbackList /* callback list */
    );
}

void beModelCtrlInfoHitBody_GetMetaObject(void)
{
    FUN_00352460();
}

void beModelCtrlInfoHitBody_InitFields(void) {
    int temp_s0;
    void *temp_s2;
    void *temp_s2_2;
    void *temp_s2_3;
    void *temp_s2_4;
    void *temp_s1;

    temp_s1 = (void *)g_beModelCtrlInfoHitBody_metaObject[0];
    temp_s0 = igMetaObject_GetFieldCount(temp_s1);
    igMetaObject_CreateFields(temp_s1, &DAT_004c5300[0], 7);
    FUN_002d3890(igMetaObject_GetFieldAt(temp_s1, temp_s0), 1);
    temp_s2 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s0 + 3));
    ((igObjectRefMetaField *)temp_s2)->_metaObject = FUN_0018a4f0();
    ((igObjectRefMetaField *)temp_s2)->_refCounted = 0;
    temp_s2_2 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s0 + 4));
    ((igObjectRefMetaField *)temp_s2_2)->_metaObject = FUN_0018a0a0();
    ((igRefMetaField *)temp_s2_2)->_construct = 1;
    temp_s2_3 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s0 + 5));
    ((igObjectRefMetaField *)temp_s2_3)->_metaObject = FUN_0018a0a0();
    ((igRefMetaField *)temp_s2_3)->_construct = 1;
    temp_s2_4 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s0 + 6));
    ((igObjectRefMetaField *)temp_s2_4)->_metaObject = FUN_0018a4f0();
    ((igRefMetaField *)temp_s2_4)->_construct = 1;
    igMetaObject_NameFields(temp_s1, &DAT_004c5320[0], &DAT_004c5340[0], &DAT_004c5360[0], temp_s0);
}

