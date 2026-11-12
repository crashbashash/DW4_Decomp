void *FUN_0036d3a0(void) {
    igMetaObject *g = g_beAction2JOINTSET_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false) {
        FUN_0036d4c0();
    }
    return g_beAction2JOINTSET_metaObject[0];
}

int beAction2JOINTSET_GetVTable(void) {
    union U_36d3f0 u;
    int temp_s0;
    char *q0;
    char *q1;
    int *temp_v1;
    int *temp_a1;
    int temp_v0;

    igObject_InitHeader(u.b);
    q1 = &u.b[8];
    *(int *)q1 = 0;
    u.vt = (int)&DAT_005340f0[0];
    q0 = &u.b[20];
    *(int *)q0 = 0;
    temp_s0 = *(int *)&u.b[*(int *)((char *)(g_objectSystem[0]) + 916)];
    u.vt = (int)&DAT_005340f0[0];
    if (q0 != 0) {
        temp_v1 = *(int **)q0;
        if (temp_v1 != 0) {
            temp_a1 = temp_v1 - 2;
            temp_v0 = temp_v1[-1] - 1;
            temp_v1[-1] = temp_v0;
            if (temp_v0 == 0) {
                StringChunk_ReleaseHeader(*temp_a1, temp_a1);
            }
        }
    }
    u.vt = (int)&DAT_00524950[0];
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

void FUN_0036d4c0(void)
{
    igMetaObject_RunStaticInit(beAction2JOINTSET_Register);
}

void *beAction2JOINTSET_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beAction2JOINTSET_metaObject,
        igNamedObject_Register,
        igNamedObject_GetPublishedMetaObject,
        beAction2JOINTSET_GetMetaObject,
        beAction2JOINTSET_className,
        0x18, /* instance size */
        beAction2JOINTSET_GetVTable,
        beAction2JOINTSET_InitFields,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void beAction2JOINTSET_GetMetaObject(void)
{
    FUN_0036d3a0();
}

void beAction2JOINTSET_InitFields(void) {
    int temp_s1;
    void *temp_s0;

    temp_s0 = (void *)g_beAction2JOINTSET_metaObject[0];
    temp_s1 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &DAT_004c8140[0], 3);
    igMetaObject_NameFields(temp_s0, &DAT_004c8150[0], &DAT_004c8160[0], &DAT_004c8170[0], temp_s1);
}

