Rc *FUN_002397a0(int arg0) {
    FUN_00239910();
    return (Rc *)igMetaObject_CreateInstance(*(int *)0x56DCC8, arg0);
}

igMetaObject *igCollisionInfo_GetMetaObject(void)
{
    igMetaObject *g = g_igCollisionInfo_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_00239910();
    return g_igCollisionInfo_metaObject[0];
}

int igCollisionInfo_GetVTable(void) {
    union U u;
    int temp_s0;
    S_ref *q0;
    char *q1;
    int *temp_v1;
    int *temp_a1;
    int temp_v0;

    igObject_InitHeader(u.b);
    q1 = &u.b[8];
    *(int *)q1 = 0;
    u.vt = (int)&DAT_0052d4d0[0];
    q0 = (S_ref *)&u.b[20];
    *(int *)q0 = 0;
    temp_s0 = *(int *)&u.b[*(int *)((char *)(g_objectSystem[0]) + 916)];
    u.vt = (int)&DAT_0052d4d0[0];
    if (q0 != 0) {
        q0 = *(S_ref **)q0;
        if (q0 != 0) {
            q0->f4 = (int)((int) (q0->f4 - 1));
            if (((unsigned long long) ((long long) q0->f4 << 0x29) >> 0x29) == 0) {
                igObject_Destroy(q0);
            }
        }
    }
    u.vt = (int)&g_igNamedObject_vtable[0];
    if (q1 != 0) {
        temp_v1 = *(int **)q1;
        if (temp_v1 != 0) {
            temp_a1 = temp_v1 - 2;
            temp_v0 = temp_v1[-1] - 1;
            temp_v1[-1] = temp_v0;
            if (temp_v0 == 0) {
                StringChunk_ReleaseHeader(*temp_a1, temp_a1);
            }
        }
    }
    return temp_s0;
}

void FUN_00239910(void)
{
    igMetaObject_RunStaticInit(igCollisionInfo_Register);
}

void igCollisionInfo_Register(void) {
    CollisionLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igCollisionInfo_metaObject,
        igInfo_Register,
        igInfo_GetPublishedMetaObject,
        thunk_igCollisionInfo_GetMetaObject,
        igCollisionInfo_className,
        0x18, /* instance size */
        igCollisionInfo_GetVTable,
        &igCollisionInfo_InitFields,
        0, /* extra callback item */
        g_igCollisionInfo_callbackList /* callback list */
    );
}

void thunk_igCollisionInfo_GetMetaObject(void) {
    igCollisionInfo_GetMetaObject();
}

void igCollisionInfo_InitFields(void) {
    int temp_s2;
    void *temp_s1;
    void *temp_s0;

    temp_s0 = (void *)g_igCollisionInfo_metaObject[0];
    temp_s2 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &DAT_00498388[0], 1);
    temp_s1 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2));
    ((igObjectRefMetaField *)temp_s1)->_metaObject = (int)FUN_0023a080();
    igMetaObject_NameFields(temp_s0, &DAT_00498390[0], &DAT_00498398[0], &DAT_004983a0[0], temp_s2);
}

