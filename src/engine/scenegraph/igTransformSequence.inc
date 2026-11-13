igMetaObject *FUN_00195330(void) {
    return g_igTransformSequence_metaObject[0];
}

void igTransformSequence1_5_InitFields(void) {
    int temp_s2;
    int temp_s3;
    igUnsignedCharArrayMetaField *t5;
    void **temp_v0;
    igObjectRefMetaField *temp_s0;
    igObjectRefMetaField *temp_s0_2;
    igObjectRefMetaField *temp_s0_3;
    igObjectRefMetaField *temp_s0_4;
    igObjectRefMetaField *temp_s0_5;
    igMetaObject *temp_s1;
    igMetaField *temp_v0_2;

    temp_s1 = (igMetaObject *)(g_igTransformSequence1_5_metaObject[0]);
    temp_s2 = igMetaObject_GetFieldCount(temp_s1);
    igMetaObject_CreateFields(temp_s1, &g_igTransformSequence1_5_ctorTable[0], 9);
    temp_s0 = (igObjectRefMetaField *)(igMetaObject_GetFieldAt(temp_s1, temp_s2));
    temp_s0->_metaObject = FUN_002ca680();
    temp_s0->_construct = 1;
    temp_v0 = (void **)(igMetaObject_FindFieldByName(temp_s1, &text_timeList[0]));
    temp_s3 = ObjectPointerList_FindIndex(temp_s1->_metaFields, temp_v0);
    temp_v0_2 = (igMetaField *)(((DW4VC_84_1 *)(temp_v0))->vX((int)(1)));
    FUN_00303460(temp_v0_2, 0);
    *(char *)((char *)(temp_v0_2) + 52) = 0;
    temp_v0_2->_externalEnumStorage = (int)(&DAT_005611e8[0]);
    igMetaObject_FinalizeAndReplaceField(temp_s1, temp_s3, temp_v0_2);
    temp_v0_2->_refCount = (int)((int) (temp_v0_2->_refCount - 1));
    if ((temp_v0_2->_refCount & 0x7FFFFF) == 0) {
        igObject_Destroy(temp_v0_2);
    }
    temp_s0_2 = (igObjectRefMetaField *)(igMetaObject_GetFieldAt(temp_s1, temp_s2 + 1));
    temp_s0_2->_metaObject = FUN_0018a0a0();
    temp_s0_3 = (igObjectRefMetaField *)(igMetaObject_GetFieldAt(temp_s1, temp_s2 + 2));
    temp_s0_3->_metaObject = FUN_0018a0a0();
    temp_s0_4 = (igObjectRefMetaField *)(igMetaObject_GetFieldAt(temp_s1, temp_s2 + 3));
    temp_s0_4->_metaObject = FUN_0018a0a0();
    FUN_0030e750(igMetaObject_GetFieldAt(temp_s1, temp_s2 + 4), 0xB);
    t5 = (igUnsignedCharArrayMetaField *)igMetaObject_GetFieldAt(temp_s1, temp_s2 + 5);
    t5->_num = 3;
    FUN_002ebc00(igMetaObject_GetFieldAt(temp_s1, temp_s2 + 7), -1);
    temp_s0_5 = (igObjectRefMetaField *)(igMetaObject_GetFieldAt(temp_s1, temp_s2 + 8));
    temp_s0_5->_metaObject = (int)FUN_001a24f0();
    igMetaObject_NameFields(temp_s1, &g_igTransformSequence1_5_fieldTable[0], &DAT_0048b010[0], &DAT_0048b040[0], temp_s2);
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

igMetaObject *FUN_00195610(void) {
    return g_igTransformSource_metaObject[0];
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

    temp_s0 = (void *)(((void * *)g_igTransformSequence_metaObject)[0]);
    temp_s1 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &g_igTransformSequence_ctorTable[0], 9);
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
    igMetaObject_NameFields(temp_s0, &g_igTransformSequence_fieldTable[0], &DAT_0048b0e0[0], &DAT_0048b110[0], temp_s1);
    *(int *)((char *)(((void * *)g_igTransformSequence_metaObject)[0]) + 60) = (int)(thunk_FUN_00194ef0);
}

