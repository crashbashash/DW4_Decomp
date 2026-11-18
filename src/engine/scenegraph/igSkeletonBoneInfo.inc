igMetaObject *g_igSkeletonBoneInfo_metaObject;
igMetaField *g_igSkeletonBoneInfo_parentIdxMetaField;
igMetaField *g_igSkeletonBoneInfo_bmIdxMetaField;
igMetaField *g_igSkeletonBoneInfo_flagsMetaField;

igMetaObject *FUN_00198960(void)
{
    igMetaObject *g = g_igSkeletonBoneInfo_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false)
        igSkeletonBoneInfo_EnsureRegistered();
    return g_igSkeletonBoneInfo_metaObject;
}

int igSkeletonBoneInfo_GetVTable(void) {
    union U u;
    int temp_s0;
    char *ps;
    int *temp_v1;
    int *temp_a1;
    int temp_v0;
    igObject_InitHeader((igObject *)u.b);
    ps = &u.b[8];
    *(int *)ps = 0;
    u.vt = (int)&g_igNamedObject_vtable[0];
    u.vt = (int)&g_igSkeletonBoneInfo_vtable[0];
    temp_s0 = *(int *)&u.b[g_objectSystem->vtableProbeOffset];
    u.vt = (int)&g_igNamedObject_vtable[0];
    if (ps != 0) {
        temp_v1 = *(int **)ps;
        if (temp_v1 != 0) {
            temp_a1 = temp_v1 - 2;
            temp_v0 = temp_v1[-1] - 1;
            temp_v1[-1] = temp_v0;
            if (temp_v0 == 0) {
                StringChunk_ReleaseHeader((StringChunk *)*temp_a1, (StringTokenHeader *)temp_a1);
            }
        }
    }
    return temp_s0;
}

void igSkeletonBoneInfo_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(igSkeletonBoneInfo_Register);
}

CallbackArray *igSkeletonBoneInfo_Register(void) {
    SceneGraphLibrary_MarkRegistered();  /* one-shot static-init latch (sets a gp-relative byte flag once) */
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_igSkeletonBoneInfo_metaObject,
        igNamedObject_Register,
        igNamedObject_GetPublishedMetaObject,
        thunk_igSkeletonBoneInfo_GetMetaObject_00198ac0,
        "igSkeletonBoneInfo",
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

static FieldFactory g_igSkeletonBoneInfo_ctorTable[] = {
    (FieldFactory)igIntMetaField_Create,
    (FieldFactory)igIntMetaField_Create,
    (FieldFactory)igIntMetaField_Create,
};
static const char *g_igSkeletonBoneInfo_fieldTable[] = {
    "_parentIdx",
    "_bmIdx",
    "_flags",
};
static igMetaField **g_igSkeletonBoneInfo_fieldHandles[] = {
    &g_igSkeletonBoneInfo_parentIdxMetaField,
    &g_igSkeletonBoneInfo_bmIdxMetaField,
    &g_igSkeletonBoneInfo_flagsMetaField,
};
static int g_igSkeletonBoneInfo_fieldOffsets[] = {
    12,
    16,
    20,
};

void igSkeletonBoneInfo_InitFields(void) {
    int temp_s1;
    void *temp_s0;

    temp_s0 = (void *)g_igSkeletonBoneInfo_metaObject;
    temp_s1 = igMetaObject_GetFieldCount((igMetaObject *)temp_s0);
    igMetaObject_CreateFields((igMetaObject *)temp_s0, g_igSkeletonBoneInfo_ctorTable, 3);
    igIntMetaField_SetDefault(igMetaObject_GetFieldAt((igMetaObject *)temp_s0, temp_s1 + 1), -1);
    igMetaObject_NameFields((igMetaObject *)temp_s0, g_igSkeletonBoneInfo_fieldTable, g_igSkeletonBoneInfo_fieldHandles, g_igSkeletonBoneInfo_fieldOffsets, temp_s1);
}

