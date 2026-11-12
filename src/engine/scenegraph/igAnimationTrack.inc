igMetaObject *igAnimationTrack_GetMetaObject(void)
{
    igMetaObject *g = g_igAnimationTrack_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_001aa030();
    return g_igAnimationTrack_metaObject[0];
}

int igAnimationTrack_GetVTable(void) {
    union U_1a9f50 u;
    int temp_s0;
    S_ref *q0;
    char *q1;
    int *temp_v1;
    int *temp_a1;
    int temp_v0;

    igObject_InitHeader(u.b);
    q1 = &u.b[8];
    *(int *)q1 = 0;
    u.vt = (int)&DAT_00529830[0];
    q0 = (S_ref *)&u.b[12];
    *(int *)q0 = 0;
    temp_s0 = *(int *)&u.b[*(int *)((char *)(g_objectSystem[0]) + 916)];
    u.vt = (int)&DAT_00529830[0];
    if (q0 != 0) {
        q0 = *(S_ref **)q0;
        if (q0 != 0) {
            q0->f4 = (int)((int) (q0->f4 - 1));
            if (((unsigned long long) ((long long) q0->f4 << 0x29) >> 0x29) == 0) {
                igObject_Destroy((void *)q0);
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

void FUN_001aa030(void)
{
    igMetaObject_RunStaticInit(igAnimationTrack_Register);
}

void igAnimationTrack_Register(void) {
    SceneGraphLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        ((char *)g_igAnimationTrack_metaObject),
        igNamedObject_Register,
        igNamedObject_GetPublishedMetaObject,
        thunk_igAnimationTrack_GetMetaObject,
        igAnimationTrack_className,
        0x2C, /* instance size */
        igAnimationTrack_GetVTable,
        &igAnimationTrack_InitFields,
        0, /* extra callback item */
        g_igAnimationTrack_callbackList /* callback list */
    );
}

void thunk_igAnimationTrack_GetMetaObject(void) {
    igAnimationTrack_GetMetaObject();
}

void igAnimationTrack_InitFields(void) {
    int temp_s2;
    void *temp_s1;
    void *temp_s0;

    temp_s0 = (void *)g_igAnimationTrack_metaObject[0];
    temp_s2 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &DAT_0048d670[0], 3);
    temp_s1 = (void *)(((void *)igMetaObject_GetFieldAt(temp_s0, temp_s2)));
    ((igObjectRefMetaField *)temp_s1)->_metaObject = (int)FUN_00194dd0();
    igMetaObject_NameFields(temp_s0, &DAT_0048d680[0], &DAT_0048d690[0], &DAT_0048d6a0[0], temp_s2);
}

