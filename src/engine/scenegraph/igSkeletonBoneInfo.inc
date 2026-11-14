igMetaObject *FUN_00198960(void)
{
    igMetaObject *g = ((igMetaObject * *)g_igSkeletonBoneInfo_metaObject)[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_00198a40();
    return ((igMetaObject * *)g_igSkeletonBoneInfo_metaObject)[0];
}

int igSkeletonBoneInfo_GetVTable(void) {
    union U u;
    int temp_s0;
    char *ps;
    int *temp_v1;
    int *temp_a1;
    int temp_v0;
    igObject_InitHeader(u.b);
    ps = &u.b[8];
    *(int *)ps = 0;
    u.vt = (int)&g_igNamedObject_vtable[0];
    u.vt = (int)&DAT_0052b270[0];
    temp_s0 = *(int *)&u.b[*(int *)((char *)(g_objectSystem[0]) + 916)];
    u.vt = (int)&g_igNamedObject_vtable[0];
    if (ps != 0) {
        temp_v1 = *(int **)ps;
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

void FUN_00198a40(void)
{
    igMetaObject_RunStaticInit(igSkeletonBoneInfo_Register);
}

void igSkeletonBoneInfo_Register(void) {
    SceneGraphLibrary_MarkRegistered();  /* one-shot static-init latch (sets a gp-relative byte flag once) */
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igSkeletonBoneInfo_metaObject,
        igNamedObject_Register,
        igNamedObject_GetPublishedMetaObject,
        thunk_igSkeletonBoneInfo_GetMetaObject_00198ac0,
        igSkeletonBoneInfo_className,
        0x18, /* instance size */
        igSkeletonBoneInfo_GetVTable,
        &igSkeletonBoneInfo_InitFields,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void thunk_FUN_00198960(void) {
    FUN_00198960();
}

void igSkeletonBoneInfo_InitFields(void) {
    int temp_s1;
    void *temp_s0;

    temp_s0 = (void *)g_igSkeletonBoneInfo_metaObject[0];
    temp_s1 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &g_igSkeletonBoneInfo_ctorTable[0], 3);
    igIntMetaField_SetDefault(igMetaObject_GetFieldAt(temp_s0, temp_s1 + 1), -1);
    igMetaObject_NameFields(temp_s0, &g_igSkeletonBoneInfo_fieldTable[0], &DAT_0048b5f8[0], &DAT_0048b608[0], temp_s1);
}

