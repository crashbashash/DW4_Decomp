int igEnbayaContextPool_Create(int allocator) {
    igEnbayaContextPool_RunStaticInit();
    return igMetaObject_CreateInstance(g_igEnbayaContextPool_metaObject[0], allocator);
}

igMetaObject *igEnbayaContextPool_GetMetaObject(void)
{
    igMetaObject *g = ((igMetaObject * *)g_igEnbayaContextPool_metaObject)[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        igEnbayaContextPool_RunStaticInit();
    return ((igMetaObject * *)g_igEnbayaContextPool_metaObject)[0];
}

int igEnbayaContextPool_GetVTable(void) {
    union U u;
    int temp_s0;
    S_ref *q0;
    S_ref *q1;
    S_ref *q2;

    igObject_InitHeader(u.b);
    u.vt = (int)&DAT_00529110[0];
    q2 = (S_ref *)&u.b[8];
    *(int *)q2 = 0;
    q1 = (S_ref *)&u.b[12];
    *(int *)q1 = 0;
    q0 = (S_ref *)&u.b[16];
    *(int *)q0 = 0;
    temp_s0 = *(int *)&u.b[*(int *)((char *)(g_objectSystem[0]) + 916)];
    u.vt = (int)&DAT_00529110[0];
    if (q0 != 0) {
        q0 = *(S_ref **)q0;
        if (q0 != 0) {
            q0->f4 = (int)((int) (q0->f4 - 1));
            if (((unsigned long long) ((long long) q0->f4 << 0x29) >> 0x29) == 0) {
                igObject_Destroy((void *)q0);
            }
        }
    }
    if (q1 != 0) {
        q1 = *(S_ref **)q1;
        if (q1 != 0) {
            q1->f4 = (int)((int) (q1->f4 - 1));
            if (((unsigned long long) ((long long) q1->f4 << 0x29) >> 0x29) == 0) {
                igObject_Destroy((void *)q1);
            }
        }
    }
    if (q2 != 0) {
        q2 = *(S_ref **)q2;
        if (q2 != 0) {
            q2->f4 = (int)((int) (q2->f4 - 1));
            if (((unsigned long long) ((long long) q2->f4 << 0x29) >> 0x29) == 0) {
                igObject_Destroy((void *)q2);
            }
        }
    }
    return temp_s0;
}

void igEnbayaContextPool_RunStaticInit(void)
{
    igMetaObject_RunStaticInit(igEnbayaContextPool_Register);
}

void igEnbayaContextPool_Register(void) {
    SceneGraphLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        ((char *)g_igEnbayaContextPool_metaObject),
        igObject_Register,
        igObject_GetMetaObject_ParentAccessor,
        thunk_igEnbayaContextPool_GetMetaObject,
        igEnbayaContextPool_className,
        0x14, /* instance size */
        igEnbayaContextPool_GetVTable,
        &igEnbayaContextPool_InitFields,
        0, /* extra callback item */
        g_igEnbayaContextPool_callbackList /* callback list */
    );
}

void thunk_igEnbayaContextPool_GetMetaObject(void) {
    igEnbayaContextPool_GetMetaObject();
}

void igEnbayaContextPool_InitFields(void) {
    int temp_s2;
    void *temp_s1_3;
    void *temp_s1_2;
    void *temp_s1;
    void *temp_s0;

    temp_s0 = (void *)g_igEnbayaContextPool_metaObject[0];
    temp_s2 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &DAT_0048c300[0], 3);
    temp_s1 = (void *)(((void *)igMetaObject_GetFieldAt(temp_s0, temp_s2)));
    ((igObjectRefMetaField *)temp_s1)->_metaObject = FUN_002c8fc0();
    ((igRefMetaField *)temp_s1)->_construct = 1;
    ((igMetaField *)temp_s1)->_persistent = 0;
    temp_s1_2 = (void *)(((void *)igMetaObject_GetFieldAt(temp_s0, temp_s2 + 1)));
    ((igObjectRefMetaField *)temp_s1_2)->_metaObject = FUN_002ca450();
    ((igRefMetaField *)temp_s1_2)->_construct = 1;
    ((igMetaField *)temp_s1_2)->_persistent = 0;
    temp_s1_3 = (void *)(((void *)igMetaObject_GetFieldAt(temp_s0, temp_s2 + 2)));
    ((igObjectRefMetaField *)temp_s1_3)->_metaObject = FUN_002ca450();
    ((igRefMetaField *)temp_s1_3)->_construct = 1;
    ((igMetaField *)temp_s1_3)->_persistent = 0;
    igMetaObject_NameFields(temp_s0, &DAT_0048c310[0], &DAT_0048c320[0], &DAT_0048c330[0], temp_s2);
}

