void *FUN_003604f0(void) {
    unsigned char b;
    if (g_beGeneraterItemData_metaObject[0] != 0) {
        b = (*(int *)((char *)(g_beGeneraterItemData_metaObject[0]) + 36) & 4) != 0;
        if (b != 0) goto done;
    }
    FUN_00360620();
done:
    return g_beGeneraterItemData_metaObject[0];
}

int beGeneraterItemData_GetVTable(void) {
    union U_360540 u;
    int temp_s0;
    S_ref *q0;
    char *q1;
    int *temp_v1;
    int *temp_a1;
    int temp_v0;

    igObject_InitHeader(u.b);
    q1 = &u.b[8];
    *(int *)q1 = 0;
    u.vt = (int)&DAT_00535d10[0];
    q0 = (S_ref *)&u.b[12];
    *(int *)q0 = 0;
    temp_s0 = *(int *)&u.b[*(int *)((char *)(g_objectSystem[0]) + 916)];
    u.vt = (int)&DAT_00535d10[0];
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

void FUN_00360620(void)
{
    igMetaObject_RunStaticInit(beGeneraterItemData_Register);
}

void *beGeneraterItemData_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beGeneraterItemData_metaObject,
        igNamedObject_Register,
        igNamedObject_GetPublishedMetaObject,
        beGeneraterItemData_GetMetaObject,
        beGeneraterItemData_className,
        0x10, /* instance size */
        beGeneraterItemData_GetVTable,
        beGeneraterItemData_InitFields,
        0, /* extra callback item */
        g_beGeneraterItemData_callbackList /* callback list */
    );
}

void beGeneraterItemData_GetMetaObject(void)
{
    FUN_003604f0();
}

void beGeneraterItemData_InitFields(void) {
    int temp_s2;
    void *temp_s1;
    void *temp_s0;

    temp_s0 = (void *)g_beGeneraterItemData_metaObject[0];
    temp_s2 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &DAT_004c6ae0[0], 1);
    temp_s1 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2));
    ((igObjectRefMetaField *)temp_s1)->_metaObject = (int)FUN_00360780();
    ((igRefMetaField *)temp_s1)->_construct = 1;
    igMetaObject_NameFields(temp_s0, &DAT_004c6ae8[0], &DAT_004c6af0[0], &DAT_004c6af8[0], temp_s2);
}

