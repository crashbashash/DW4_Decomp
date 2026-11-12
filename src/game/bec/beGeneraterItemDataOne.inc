void *FUN_00360910(void) {
    igMetaObject *g = g_beGeneraterItemDataOne_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false) {
        FUN_003609f0();
    }
    return g_beGeneraterItemDataOne_metaObject[0];
}

int beGeneraterItemDataOne_GetVTable(void) {
    union U_360960 u;
    int s0;
    char *ps;
    int *v1;
    int *a1;
    int v0;

    igObject_InitHeader(u.b);
    ps = &u.b[8];
    *(int *)ps = 0;
    u.vt = (int)&DAT_00524950[0];
    u.vt = (int)&DAT_00535c40[0];
    s0 = *(int *)&u.b[*(int *)((char *)(g_objectSystem[0]) + 916)];
    u.vt = (int)&DAT_00524950[0];
    if (ps != 0) {
        v1 = *(int **)ps;
        if (v1 != 0) {
            a1 = v1 - 2;
            v0 = v1[-1] - 1;
            v1[-1] = v0;
            if (v0 == 0) {
                StringChunk_ReleaseHeader(*a1, a1);
            }
        }
    }
    return s0;
}

void FUN_003609f0(void)
{
    igMetaObject_RunStaticInit(beGeneraterItemDataOne_Register);
}

void *beGeneraterItemDataOne_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beGeneraterItemDataOne_metaObject,
        igNamedObject_Register,
        igNamedObject_GetPublishedMetaObject,
        beGeneraterItemDataOne_GetMetaObject,
        beGeneraterItemDataOne_className,
        0x18, /* instance size */
        beGeneraterItemDataOne_GetVTable,
        beGeneraterItemDataOne_InitFields,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void beGeneraterItemDataOne_GetMetaObject(void)
{
    FUN_00360910();
}

void beGeneraterItemDataOne_InitFields(void) {
    int temp_s1;
    void *temp_s0;

    temp_s0 = (void *)g_beGeneraterItemDataOne_metaObject[0];
    temp_s1 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &DAT_004c6b08[0], 3);
    igMetaObject_NameFields(temp_s0, &DAT_004c6b18[0], &DAT_004c6b28[0], &DAT_004c6b38[0], temp_s1);
}

int FUN_00360b10(void) {
    if (DAT_005895c8[0] == 0) {
        DAT_005895c8[0] = igMetaEnum_Create(&DAT_005016f0[0], &DAT_004c6b50[0], &DAT_004c6b70[0], 8);
    }
    return DAT_005895c8[0];
}

