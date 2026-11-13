void *FUN_0036d5e0(void) {
    unsigned char b;
    if (g_beAction2MOTIONSET_metaObject[0] != 0) {
        b = (*(int *)((char *)(g_beAction2MOTIONSET_metaObject[0]) + 36) & 4) != 0;
        if (b != 0) goto done;
    }
    FUN_0036d740();
done:
    return g_beAction2MOTIONSET_metaObject[0];
}

int beAction2MOTIONSET_GetVTable(void) {
    union U_36d630 u;
    int temp_s0;
    char *q0;
    char *q1;
    char *q2;
    int *temp_v1;
    int *temp_a1;
    int temp_v0;

    igObject_InitHeader(u.b);
    q2 = &u.b[8];
    *(int *)q2 = 0;
    u.vt = (int)&DAT_00534090[0];
    q1 = &u.b[12];
    *(int *)q1 = 0;
    q0 = &u.b[20];
    *(int *)q0 = 0;
    temp_s0 = *(int *)&u.b[*(int *)((char *)(g_objectSystem[0]) + 916)];
    u.vt = (int)&DAT_00534090[0];
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
    u.vt = (int)&g_igNamedObject_vtable[0];
    if (q2 != 0) {
        temp_v1 = *(int **)q2;
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

void FUN_0036d740(void)
{
    igMetaObject_RunStaticInit(beAction2MOTIONSET_Register);
}

void *beAction2MOTIONSET_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beAction2MOTIONSET_metaObject,
        igNamedObject_Register,
        igNamedObject_GetPublishedMetaObject,
        beAction2MOTIONSET_GetMetaObject,
        beAction2MOTIONSET_className,
        0x18, /* instance size */
        beAction2MOTIONSET_GetVTable,
        beAction2MOTIONSET_InitFields,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void beAction2MOTIONSET_GetMetaObject(void)
{
    FUN_0036d5e0();
}

void beAction2MOTIONSET_InitFields(void) {
    int temp_s1;
    void *temp_s0;

    temp_s0 = (void *)g_beAction2MOTIONSET_metaObject[0];
    temp_s1 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &g_beAction2MOTIONSET_ctorTable[0], 3);
    igMetaObject_NameFields(temp_s0, &g_beAction2MOTIONSET_fieldTable[0], &DAT_004c81a0[0], &DAT_004c81b0[0], temp_s1);
}

