void FUN_0019d3f0(int arg0) {
    FUN_0019d4f0();
    igMetaObject_CreateInstance(*(int *)0x561888, arg0);
}

igMetaObject *igModelViewMatrixBoneSelect_GetMetaObject(void)
{
    igMetaObject *g = g_igModelViewMatrixBoneSelect_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_0019d4f0();
    return g_igModelViewMatrixBoneSelect_metaObject[0];
}

int igModelViewMatrixBoneSelect_GetVTable(void) {
    union U_19d480 u;
    int temp_s0;

    igObject_InitHeader(u.b);
    u.w[2] = 0;
    u.w[3] = 0;
    u.w[4] = 0;
    u.w[7] = 0;
    u.w[0] = (int)(&DAT_0052aa10[0]);
    temp_s0 = *(int *)&u.b[*(int *)((char *)(DAT_00586dc8[0]) + 916)];
    u.w[0] = (int)(&DAT_0052aa10[0]);
    FUN_00195a90((struct T_195a90 *)&u.w[0], 0);
    return temp_s0;
}

void FUN_0019d4f0(void)
{
    igMetaObject_RunStaticInit(igModelViewMatrixBoneSelect_Register);
}

void igModelViewMatrixBoneSelect_Register(void) {
    SceneGraphLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        ((char *)g_igModelViewMatrixBoneSelect_metaObject),
        igGroup_Register,
        igGroup_GetPublishedMetaObject,
        thunk_igModelViewMatrixBoneSelect_GetMetaObject,
        igModelViewMatrixBoneSelect_className,
        0x24, /* instance size */
        igModelViewMatrixBoneSelect_GetVTable,
        &igModelViewMatrixBoneSelect_InitFields,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void thunk_igModelViewMatrixBoneSelect_GetMetaObject(void) {
    igModelViewMatrixBoneSelect_GetMetaObject();
}

void igModelViewMatrixBoneSelect_InitFields(void) {
    int temp_s1;
    void *temp_s0;

    temp_s0 = (void *)DAT_00561888[0];
    temp_s1 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &DAT_0048bcd8[0], 1);
    FUN_002ea4b0(igMetaObject_GetFieldAt(temp_s0, temp_s1), -1);
    igMetaObject_NameFields(temp_s0, &DAT_0048bce0[0], &DAT_0048bce8[0], &DAT_0048bcf0[0], temp_s1);
}

