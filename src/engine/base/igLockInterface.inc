igMetaObject *FUN_002267c0(void) {
    if (g_igLockInterface_metaObject[0] == 0) {
        g_igLockInterface_metaObject[0] = igMetaObject_Create(Memory_GetAllocatorBySelector(g_metadataAllocatorKey[0]));
    }
    return g_igLockInterface_metaObject[0];
}

igMetaObject *igLockInterface_GetMetaObject(void)
{
    igMetaObject *g = g_igLockInterface_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_00226a10();
    return g_igLockInterface_metaObject[0];
}

int igLockInterface_GetVTable(void) {
    union U_3 u;
    int temp_s0;
    S_ref *q0;
    S_ref *q1;
    S_ref *q2;

    igObject_InitHeader(u.b);
    u.vt = (int)&DAT_0052c010[0];
    q2 = (S_ref *)&u.b[32];
    *(int *)q2 = 0;
    q1 = (S_ref *)&u.b[36];
    *(int *)q1 = 0;
    q0 = (S_ref *)&u.b[40];
    *(int *)q0 = 0;
    temp_s0 = *(int *)&u.b[*(int *)((char *)(g_objectSystem[0]) + 916)];
    u.vt = (int)&DAT_0052c010[0];
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

extern "C" O *FUN_00226990(O *arg0, short arg1) {
    if (arg0) {
        S_temp_a0 *t = arg0->m;
        if (t) { t->f4 -= 1; if ((t->f4 & 0x7fffff) == 0) igObject_Destroy(t); }
        if (arg1 > 0) FUN_00100610(arg0);
    }
    return arg0;
}

void FUN_00226a10(void)
{
    igMetaObject_RunStaticInit(igLockInterface_Register);
}

void igLockInterface_Register(void) {
    BaseLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igLockInterface_metaObject,
        igInterface_Register,
        igInterface_GetPublishedMetaObject,
        thunk_igLockInterface_GetMetaObject,
        igLockInterface_className,
        0x2C, /* instance size */
        igLockInterface_GetVTable,
        &igLockInterface_InitFields,
        0, /* extra callback item */
        g_igLockInterface_callbackList /* callback list */
    );
}

void thunk_igLockInterface_GetMetaObject(void) {
    igLockInterface_GetMetaObject();
}

void igLockInterface_InitFields(void) {
    int temp_s2;
    void *temp_s1_3;
    void *temp_s1_2;
    void *temp_s1;
    void *temp_s0;

    temp_s0 = (void *)g_igLockInterface_metaObject[0];
    temp_s2 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &DAT_00497c90[0], 3);
    temp_s1 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2));
    ((igObjectRefMetaField *)temp_s1)->_metaObject = FUN_002b9120();
    ((igRefMetaField *)temp_s1)->_construct = 1;
    temp_s1_2 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 1));
    ((igObjectRefMetaField *)temp_s1_2)->_metaObject = FUN_002cb110();
    ((igRefMetaField *)temp_s1_2)->_construct = 1;
    temp_s1_3 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 2));
    ((igObjectRefMetaField *)temp_s1_3)->_metaObject = FUN_002c8810();
    ((igRefMetaField *)temp_s1_3)->_construct = 1;
    igMetaObject_NameFields(temp_s0, &DAT_00497ca0[0], &DAT_00497cb0[0], &DAT_00497cc0[0], temp_s2);
}

