void FUN_0014d070(int arg0) {
    FUN_0014d190();
    igMetaObject_CreateInstance(*(int *)0x55FCA0, arg0);
}

int FUN_0014d0b0(void) {
    if (DAT_0055fca0[0] == 0) {
        DAT_0055fca0[0] = (int)igMetaObject_Create(Memory_GetAllocatorBySelector(DAT_00587040[0]));
    }
    return DAT_0055fca0[0];
}

igMetaObject *igParticleFormat_GetMetaObject(void)
{
    igMetaObject *g = g_igParticleFormat_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_0014d190();
    return g_igParticleFormat_metaObject[0];
}

int igParticleFormat_GetVTable(void) {
    struct Obj_14d150 obj;
    igObject_InitHeader(&obj);
    obj.vt = &DAT_00526fc0[0];
    return *(int *)((char *)&obj + *(int *)((char *)(DAT_00586dc8[0]) + 916));
}

void FUN_0014d190(void)
{
    igMetaObject_RunStaticInit(igParticleFormat_Register);
}

void igParticleFormat_Register(void) {
    FUN_00149bc0();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igParticleFormat_metaObject,
        igObject_Register,
        igObject_GetMetaObject_ParentAccessor,
        thunk_igParticleFormat_GetMetaObject,
        igParticleFormat_className,
        0x30, /* instance size */
        igParticleFormat_GetVTable,
        &igParticleFormat_InitFields,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void thunk_igParticleFormat_GetMetaObject(void) {
    igParticleFormat_GetMetaObject();
}

void igParticleFormat_InitFields(void) {
    void *temp_v0;
    void *temp_v0_10;
    void *temp_v0_2;
    void *temp_v0_3;
    void *temp_v0_4;
    void *temp_v0_5;
    void *temp_v0_6;
    void *temp_v0_7;
    void *temp_v0_8;
    void *temp_v0_9;
    int temp_s1;
    void *temp_s0;

    temp_s0 = (void *)DAT_0055fca0[0];
    temp_s1 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &DAT_00488ba0[0], 0xA);
    temp_v0 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s1));
    FUN_002dc7a0(temp_v0, &DAT_00488c58[0]);
    ((igEnumMetaField *)temp_v0)->_getMetaEnumFunction = (int)(&X0_0014d010[0]);
    temp_v0_2 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s1 + 1));
    FUN_002dc7a0(temp_v0_2, &DAT_00488c60[0]);
    ((igEnumMetaField *)temp_v0_2)->_getMetaEnumFunction = (int)(&X1_0014d010[0]);
    temp_v0_3 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s1 + 2));
    FUN_002dc7a0(temp_v0_3, &DAT_00488c68[0]);
    ((igEnumMetaField *)temp_v0_3)->_getMetaEnumFunction = (int)(&X2_0014d010[0]);
    temp_v0_4 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s1 + 3));
    FUN_002dc7a0(temp_v0_4, &DAT_00488c70[0]);
    ((igEnumMetaField *)temp_v0_4)->_getMetaEnumFunction = (int)(&X3_0014d010[0]);
    temp_v0_5 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s1 + 4));
    FUN_002dc7a0(temp_v0_5, &DAT_00488c78[0]);
    ((igEnumMetaField *)temp_v0_5)->_getMetaEnumFunction = (int)(&X4_0014d010[0]);
    temp_v0_6 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s1 + 5));
    FUN_002dc7a0(temp_v0_6, &DAT_00488c80[0]);
    ((igEnumMetaField *)temp_v0_6)->_getMetaEnumFunction = (int)(&FUN_00149aa0);
    temp_v0_7 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s1 + 6));
    FUN_002dc7a0(temp_v0_7, &DAT_00488c88[0]);
    ((igEnumMetaField *)temp_v0_7)->_getMetaEnumFunction = (int)(&FUN_0014c230);
    temp_v0_8 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s1 + 7));
    FUN_002dc7a0(temp_v0_8, &DAT_00488c90[0]);
    ((igEnumMetaField *)temp_v0_8)->_getMetaEnumFunction = (int)(&FUN_0014c290);
    temp_v0_9 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s1 + 8));
    FUN_002dc7a0(temp_v0_9, &DAT_00488c98[0]);
    ((igEnumMetaField *)temp_v0_9)->_getMetaEnumFunction = (int)(&X5_0014d010[0]);
    temp_v0_10 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s1 + 9));
    FUN_002dc7a0(temp_v0_10, &DAT_00488ca0[0]);
    ((igEnumMetaField *)temp_v0_10)->_getMetaEnumFunction = (int)(&X6_0014d010[0]);
    igMetaObject_NameFields(temp_s0, &DAT_00488bd0[0], &DAT_00488c00[0], &DAT_00488c30[0], temp_s1);
}

int FUN_0014d450(void) {
    if (DAT_0055fcf8[0] == 0) {
        DAT_0055fcf8[0] = igMetaEnum_Create(&DAT_004dc640[0], &DAT_00488cb0[0], &DAT_00488cc0[0], 4);
    }
    return DAT_0055fcf8[0];
}

int FUN_0014d4b0(void) {
    if (DAT_0055fd00[0] == 0) {
        DAT_0055fd00[0] = igMetaEnum_Create(&DAT_004dc710[0], &DAT_00488cd0[0], &DAT_00488ce0[0], 3);
    }
    return DAT_0055fd00[0];
}

int FUN_0014d510(void) {
    if (DAT_0055fd08[0] == 0) {
        DAT_0055fd08[0] = igMetaEnum_Create(&DAT_004dc7c0[0], &DAT_00488cf0[0], &DAT_00488d00[0], 3);
    }
    return DAT_0055fd08[0];
}

