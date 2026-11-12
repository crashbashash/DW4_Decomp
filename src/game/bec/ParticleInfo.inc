int FUN_0036e880(void) {
    if (DAT_0058a0c0[0] == 0) {
        DAT_0058a0c0[0] = igMetaEnum_Create(&DAT_005064d0[0], &DAT_004c8360[0], &DAT_004c8370[0], 3);
    }
    return DAT_0058a0c0[0];
}

int FUN_0036e8e0(void) {
    if (DAT_0058a0c8[0] == 0) {
        DAT_0058a0c8[0] = igMetaEnum_Create(&DAT_00506530[0], &DAT_004c8380[0], &DAT_004c8388[0], 2);
    }
    return DAT_0058a0c8[0];
}

int FUN_0036e940(void) {
    if (DAT_0058a0d0[0] == 0) {
        DAT_0058a0d0[0] = igMetaEnum_Create(&DAT_005065b0[0], &DAT_004c8390[0], &DAT_004c83a0[0], 3);
    }
    return DAT_0058a0d0[0];
}

int FUN_0036e9a0(void) {
    if (DAT_0058a0d8[0] == 0) {
        DAT_0058a0d8[0] = igMetaEnum_Create(&DAT_00506670[0], &DAT_004c83b0[0], &DAT_004c83d0[0], 5);
    }
    return DAT_0058a0d8[0];
}

G_36ea00 *FUN_0036ea00(void) {
    G_36ea00 *g = DAT_0058a0e0[0];
    int t;
    if (!g || !(t = (g->f & 4) != 0))
        FUN_0036eaf0();
    return DAT_0058a0e0[0];
}

int ParticleInfo_GetVTable(void) {
    struct Obj_36ea50 obj;
    int t;

    igObject_InitHeader(&obj);
    obj.w2 = 0;
    obj.w5 = 0;
    obj.w6 = 0;
    obj.w7 = 0;
    obj.w15 = 0;
    obj.vt = &DAT_00533f50[0];
    obj.w242 = 0;
    obj.w254 = 0;
    t = *(int *)((char *)&obj + *(int *)((char *)(DAT_00586dc8[0]) + 916));
    obj.vt = &DAT_00533f50[0];
    FUN_001971e0(&obj.w254, -1);
    FUN_00132390(&obj.w242, -1);
    FUN_0019b040(&obj, 0);
    return t;
}

void FUN_0036eaf0(void)
{
    igMetaObject_RunStaticInit(ParticleInfo_Register);
}

void *ParticleInfo_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_ParticleInfo_metaObject,
        igSceneInfo_Register,
        igSceneInfo_GetPublishedMetaObject,
        ParticleInfo_GetMetaObject,
        ParticleInfo_className,
        0x400, /* instance size */
        ParticleInfo_GetVTable,
        ParticleInfo_InitFields,
        0, /* extra callback item */
        g_ParticleInfo_callbackList /* callback list */
    );
}

void ParticleInfo_GetMetaObject(void)
{
    FUN_0036ea00();
}

int FUN_0036ebb0(void) {
    return DAT_005615e0[0];
}

void ParticleInfo_InitFields(void) {
    int temp_s1;
    void *f;
    void *temp_s0;

    temp_s0 = (void *)((int *)DAT_0058a0e0)[0];
    temp_s1 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &DAT_004c8400[0], 0x12);
    f = igMetaObject_GetFieldAt(temp_s0, temp_s1);
    ((igFloatArrayMetaField *)f)->_num = 0xC0;
    ((igFloatArrayMetaField *)f)->_resetMethod = 3;
    f = igMetaObject_GetFieldAt(temp_s0, temp_s1 + 1);
    ((igIntArrayMetaField *)f)->_num = 0x20;
    ((igIntArrayMetaField *)f)->_resetMethod = 3;
    FUN_002e3810((void *)((int)igMetaObject_GetFieldAt(temp_s0, temp_s1 + 2)), 10.0f);
    FUN_002ea4b0(igMetaObject_GetFieldAt(temp_s0, temp_s1 + 3), 0xA);
    f = igMetaObject_GetFieldAt(temp_s0, temp_s1 + 4);
    ((igObjectRefMetaField *)f)->_metaObject = FUN_0014dfb0();
    f = igMetaObject_GetFieldAt(temp_s0, temp_s1 + 5);
    FUN_002dc7a0(f, &DAT_004c8538[0]);
    ((igEnumMetaField *)f)->_getMetaEnumFunction = (int)&FUN_0036e940;
    f = igMetaObject_GetFieldAt(temp_s0, temp_s1 + 6);
    FUN_002dc7a0(f, &DAT_004c8540[0]);
    ((igEnumMetaField *)f)->_getMetaEnumFunction = (int)&FUN_0036e8e0;
    f = igMetaObject_GetFieldAt(temp_s0, temp_s1 + 9);
    FUN_002dc7a0(f, &DAT_004c8548[0]);
    ((igEnumMetaField *)f)->_getMetaEnumFunction = (int)&FUN_0036e880;
    f = igMetaObject_GetFieldAt(temp_s0, temp_s1 + 0xB);
    FUN_002dc7a0(f, &DAT_004c8550[0]);
    ((igEnumMetaField *)f)->_getMetaEnumFunction = (int)&FUN_0036e9a0;
    FUN_002ea4b0(igMetaObject_GetFieldAt(temp_s0, temp_s1 + 0xD), 1);
    FUN_002ea4b0(igMetaObject_GetFieldAt(temp_s0, temp_s1 + 0xE), 1);
    FUN_002e3810((void *)((int)igMetaObject_GetFieldAt(temp_s0, temp_s1 + 0x10)), 0.0f);
    f = igMetaObject_GetFieldAt(temp_s0, temp_s1 + 0x11);
    ((igObjectRefMetaField *)f)->_metaObject = FUN_0019fae0();
    igMetaObject_NameFields(temp_s0, &DAT_004c8450[0], &DAT_004c84a0[0], &DAT_004c84f0[0], temp_s1);
}

