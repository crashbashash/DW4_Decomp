int FUN_00195330(void) {
    return DAT_00561230[0];
}

void thunk_FUN_001ddfd0(void) {
    FUN_001ddfd0();
}

igMetaObject *igTransformSequence_GetMetaObject(void)
{
    igMetaObject *g = g_igTransformSequence_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_00195580();
    return g_igTransformSequence_metaObject[0];
}

void FUN_00195580(void)
{
    igMetaObject_RunStaticInit(igTransformSequence_Register);
}

void igTransformSequence_Register(void) {
    SceneGraphLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        1, /* abstract */
        ((char *)g_igTransformSequence_metaObject),
        igTransformSource_Register,
        igTransformSource_GetPublishedMetaObject,
        thunk_igTransformSequence_GetMetaObject,
        igTransformSequence_className,
        0x38, /* instance size */
        0,
        &igTransformSequence_InitFields,
        0, /* extra callback item */
        g_igTransformSequence_callbackList /* callback list */
    );
}

void thunk_igTransformSequence_GetMetaObject(void) {
    igTransformSequence_GetMetaObject();
}

int FUN_00195610(void) {
    return DAT_005611d0[0];
}

void igTransformSequence_InitFields(void) {
    int temp_s1;
    struct Fld *temp_a0;
    void *temp_s0;
    struct Fld *temp_s2;
    struct Fld *temp_s2_2;
    struct Fld *temp_s2_3;
    struct Fld *temp_s2_4;
    struct Fld *temp_v0;
    struct Fld *temp_v0_2;
    int sp40[3];

    temp_s0 = (void *)(((void * *)DAT_00561230)[0]);
    temp_s1 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &DAT_0048b080[0], 9);
    temp_s2 = ((struct Fld *)igMetaObject_GetFieldAt(temp_s0, temp_s1));
    temp_s2->f56 = FUN_0018a0a0();
    temp_s2->f52 = 1;
    temp_s2_2 = ((struct Fld *)igMetaObject_GetFieldAt(temp_s0, temp_s1 + 1));
    temp_s2_2->f56 = FUN_00189c10();
    temp_s2_2->f52 = 1;
    temp_s2_3 = ((struct Fld *)igMetaObject_GetFieldAt(temp_s0, temp_s1 + 2));
    temp_s2_3->f56 = FUN_0018a0a0();
    temp_s2_3->f52 = 1;
    temp_s2_4 = ((struct Fld *)igMetaObject_GetFieldAt(temp_s0, temp_s1 + 3));
    temp_s2_4->f56 = FUN_002c93a0();
    temp_s2_4->f52 = 1;
    FUN_002d9500(((struct Fld *)igMetaObject_GetFieldAt(temp_s0, temp_s1 + 4)), -1.0);
    temp_v0 = ((struct Fld *)igMetaObject_GetFieldAt(temp_s0, temp_s1 + 6));
    FUN_002dc7a0(temp_v0, &DAT_0048b138[0]);
    *(int *)((char *)temp_v0 + 52) = (int)&FUN_002d1870;
    temp_v0_2 = ((struct Fld *)igMetaObject_GetFieldAt(temp_s0, temp_s1 + 7));
    FUN_002ea4b0(temp_v0_2, 1);
    temp_v0_2->f38 = 0;
    temp_a0 = ((struct Fld *)igMetaObject_GetFieldAt(temp_s0, temp_s1 + 8));
    sp40[0] = 0;
    sp40[1] = 0;
    sp40[2] = 0;
    FUN_0018e470(temp_a0, sp40);
    igMetaObject_NameFields(temp_s0, &DAT_0048b0b0[0], &DAT_0048b0e0[0], &DAT_0048b110[0], temp_s1);
    *(int *)((char *)(((void * *)DAT_00561230)[0]) + 60) = (int)(thunk_FUN_00194ef0);
}

