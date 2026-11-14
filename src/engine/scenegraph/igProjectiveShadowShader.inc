igMetaObject *FUN_0019b440(void) {
    if (g_igProjectiveShadowShader_metaObject[0] == 0) {
        g_igProjectiveShadowShader_metaObject[0] = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData[0]));
    }
    return g_igProjectiveShadowShader_metaObject[0];
}

igMetaObject *igProjectiveShadowShader_GetMetaObject(void)
{
    unsigned char ready;
    if (g_igProjectiveShadowShader_metaObject[0] != 0) {
        ready = (g_igProjectiveShadowShader_metaObject[0]->_validity & 4) != 0;
        if (ready != 0) goto done;
    }
    FUN_0019b800();
done:
    return g_igProjectiveShadowShader_metaObject[0];
}

int igProjectiveShadowShader_GetVTable(void) {
    struct S_19b4e0 s;
    char *p392;
    int r;
    char *p388;
    char *p384;
    char *p380;
    char *p376;
    char *p372;
    char *p368;
    char *p364;
    char *p360;
    char *p356;
    char *p352;
    char *p348;
    char *p344;
    char *p340;
    FUN_0019acf0((igGroup *)&s);
    s.vt = &DAT_00528950[0];
    FUN_0019ace0((int)((char *)&s + 32));
    FUN_0019ace0((int)((char *)&s + 44));
    FUN_0019acd0((int *)((char *)&s + 60));
    FUN_0019acd0((int *)((char *)&s + 64));
    FUN_00197330((int *)((char *)&s + 84));
    FUN_0019acc0((int *)((char *)&s + 88));
    FUN_0019acb0((int *)((char *)&s + 92));
    FUN_0019acc0((int *)((char *)&s + 96));
    FUN_0019acb0((int *)((char *)&s + 100));
    FUN_001972e0((int *)((char *)&s + 108));
    FUN_0019b7f0((int *)((char *)&s + 112));
    FUN_0019ac10((int *)((char *)&s + 116));
    FUN_0019ace0((int)((char *)&s + 132));
    FUN_0019aca0((int *)((char *)&s + 144));
    FUN_0019ac90((int *)((char *)&s + 152));
    FUN_0019ac80((int *)((char *)&s + 156));
    FUN_0019ac70((int *)((char *)&s + 160));
    FUN_0019ac60((int *)((char *)&s + 164));
    FUN_0019ac90((int *)((char *)&s + 168));
    FUN_0019ac80((int *)((char *)&s + 172));
    FUN_0019ac70((int *)((char *)&s + 176));
    p340 = (char *)&s + 180;
    FUN_0019ac60((int *)p340);
    p344 = (char *)&s + 184;
    FUN_0019ac50((int *)p344);
    p348 = (char *)&s + 188;
    FUN_00132410(p348);
    p352 = (char *)&s + 192;
    FUN_0019ac40((int *)p352);
    p356 = (char *)&s + 196;
    FUN_0019ac40((int *)p356);
    p360 = (char *)&s + 200;
    FUN_0019ac30((int *)p360);
    p364 = (char *)&s + 204;
    FUN_0019ac60((int *)p364);
    p388 = (char *)&s + 228;
    FUN_0019b7e0((int *)p388);
    p392 = (char *)&s + 232;
    FUN_0019b7e0((int *)p392);
    r = *(int *)((char *)&s + *(int *)((char *)(g_objectSystem[0]) + 916));
    s.vt = &DAT_00528950[0];
    FUN_001321b0(p392, -1);
    FUN_001321b0(p388, -1);
    FUN_0019aa10((struct Ref * *)p364, -1);
    FUN_00136370(p360, -1);
    FUN_0019ab90((ObjectRefWord *)p356, -1);
    FUN_0019ab90((ObjectRefWord *)p352, -1);
    FUN_00132390(p348, -1);
    FUN_0019a990((void * *)p344, -1);
    FUN_0019aa10((struct Ref * *)p340, -1);
    FUN_00132980((char *)&s + 176, -1);
    FUN_0019a910((void * *)((char *)&s + 172), -1);
    FUN_00133ca0((char *)&s + 168, -1);
    FUN_0019aa10((struct Ref * *)((char *)&s + 164), -1);
    FUN_00132980((char *)&s + 160, -1);
    FUN_0019a910((void * *)((char *)&s + 156), -1);
    FUN_00133ca0((char *)&s + 152, -1);
    FUN_001966b0((ObjectRefWord *)((char *)&s + 144), -1);
    FUN_0019ab10((O *)((char *)&s + 116), -1);
    FUN_001353b0((char *)&s + 112, -1);
    FUN_001971e0((O *)((char *)&s + 108), -1);
    FUN_0019a890((ObjectRefWord *)((char *)&s + 100), -1);
    FUN_00142d10((char *)&s + 96, -1);
    FUN_0019a890((ObjectRefWord *)((char *)&s + 92), -1);
    FUN_00142d10((char *)&s + 88, -1);
    FUN_001380e0((char *)&s + 84, -1);
    FUN_001958f0((void * *)((char *)&s + 64), -1);
    FUN_001958f0((void * *)((char *)&s + 60), -1);
    FUN_00195a90((struct T_195a90 *)&s, 0);
    return r;
}

int *FUN_0019b7e0(int *p)
{
    *(int *)((char *)p + 0) = 0;
    return p;
}

int *FUN_0019b7f0(int *p)
{
    *(int *)((char *)p + 0) = 0;
    return p;
}

void FUN_0019b800(void)
{
    igMetaObject_RunStaticInit(igProjectiveShadowShader_Register);
}

void igProjectiveShadowShader_Register(void) {
    SceneGraphLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        ((char *)g_igProjectiveShadowShader_metaObject),
        igGroup_Register,
        igGroup_GetPublishedMetaObject,
        thunk_igProjectiveShadowShader_GetMetaObject,
        igProjectiveShadowShader_className,
        0xF0, /* instance size */
        igProjectiveShadowShader_GetVTable,
        &igProjectiveShadowShader_InitFields,
        0, /* extra callback item */
        g_igProjectiveShadowShader_callbackList /* callback list */
    );
}

void thunk_igProjectiveShadowShader_GetMetaObject(void) {
    igProjectiveShadowShader_GetMetaObject();
}

void igProjectiveShadowShader_InitFields(void) {
    float v1[4];
    float v2[4];
    float v3[4];
    int temp_s1;
    void *temp_s0;
    struct Fld_19b8a0 *temp_a0;
    struct Fld_19b8a0 *temp_s2;
    struct Fld_19b8a0 *temp_v0;

    temp_s0 = (void *)g_igProjectiveShadowShader_metaObject[0];
    temp_s1 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &g_igProjectiveShadowShader_ctorTable[0], 0x30);
    temp_a0 = ((struct Fld_19b8a0 *)igMetaObject_GetFieldAt(temp_s0, temp_s1));
    v1[0] = 0; v1[1] = 4.0f; v1[2] = 0;
    FUN_0018e470(temp_a0, v1);
    temp_a0 = ((struct Fld_19b8a0 *)igMetaObject_GetFieldAt(temp_s0, temp_s1 + 1));
    v2[0] = 0; v2[1] = -1.0f; v2[2] = 0;
    FUN_0018e470(temp_a0, v2);
    igFloatMetaField_SetDefault(((struct Fld_19b8a0 *)igMetaObject_GetFieldAt(temp_s0, temp_s1 + 2)), 30.0f);
    temp_s2 = ((struct Fld_19b8a0 *)igMetaObject_GetFieldAt(temp_s0, temp_s1 + 3));
    temp_s2->f56 = (int)FUN_0019cbe0();
    temp_s2->f52 = 1;
    temp_s2 = ((struct Fld_19b8a0 *)igMetaObject_GetFieldAt(temp_s0, temp_s1 + 4));
    temp_s2->f56 = (int)FUN_0019cbe0();
    igFloatMetaField_SetDefault(((struct Fld_19b8a0 *)igMetaObject_GetFieldAt(temp_s0, temp_s1 + 5)), 0.300000012f);
    igIntMetaField_SetDefault(((struct Fld_19b8a0 *)igMetaObject_GetFieldAt(temp_s0, temp_s1 + 6)), 0x80);
    igIntMetaField_SetDefault(((struct Fld_19b8a0 *)igMetaObject_GetFieldAt(temp_s0, temp_s1 + 7)), 0x80);
    igFloatMetaField_SetDefault(((struct Fld_19b8a0 *)igMetaObject_GetFieldAt(temp_s0, temp_s1 + 8)), 0.5f);
    temp_s2 = ((struct Fld_19b8a0 *)igMetaObject_GetFieldAt(temp_s0, temp_s1 + 9));
    temp_s2->f56 = FUN_0013ad40();
    temp_s2->f52 = 1;
    temp_s2->f38 = 0;
    temp_s2 = ((struct Fld_19b8a0 *)igMetaObject_GetFieldAt(temp_s0, temp_s1 + 0xA));
    temp_s2->f56 = FUN_001356f0();
    temp_s2->f52 = 1;
    temp_s2->f38 = 0;
    temp_s2 = ((struct Fld_19b8a0 *)igMetaObject_GetFieldAt(temp_s0, temp_s1 + 0xB));
    temp_s2->f56 = FUN_001346d0();
    temp_s2->f52 = 1;
    temp_s2->f38 = 0;
    temp_s2 = ((struct Fld_19b8a0 *)igMetaObject_GetFieldAt(temp_s0, temp_s1 + 0xC));
    temp_s2->f56 = FUN_001356f0();
    temp_s2->f52 = 1;
    temp_s2->f38 = 0;
    temp_s2 = ((struct Fld_19b8a0 *)igMetaObject_GetFieldAt(temp_s0, temp_s1 + 0xD));
    temp_s2->f56 = FUN_001346d0();
    temp_s2->f52 = 1;
    temp_s2->f38 = 0;
    temp_v0 = ((struct Fld_19b8a0 *)igMetaObject_GetFieldAt(temp_s0, temp_s1 + 0xE));
    igIntMetaField_SetDefault(temp_v0, 0);
    temp_v0->f38 = 0;
    temp_s2 = ((struct Fld_19b8a0 *)igMetaObject_GetFieldAt(temp_s0, temp_s1 + 0xF));
    temp_s2->f56 = (int)FUN_0019fae0();
    temp_s2->f52 = 1;
    temp_s2->f38 = 0;
    temp_s2 = ((struct Fld_19b8a0 *)igMetaObject_GetFieldAt(temp_s0, temp_s1 + 0x10));
    temp_s2->f56 = FUN_00137850();
    temp_s2->f38 = 0;
    temp_s2 = ((struct Fld_19b8a0 *)igMetaObject_GetFieldAt(temp_s0, temp_s1 + 0x11));
    temp_s2->f56 = FUN_00138f20();
    temp_s2->f52 = 1;
    temp_s2->f38 = 0;
    igBoolMetaField_SetDefaultValue(((struct Fld_19b8a0 *)igMetaObject_GetFieldAt(temp_s0, temp_s1 + 0x12)), 1);
    igFloatMetaField_SetDefault(((struct Fld_19b8a0 *)igMetaObject_GetFieldAt(temp_s0, temp_s1 + 0x13)), 0.100000001f);
    igFloatMetaField_SetDefault(((struct Fld_19b8a0 *)igMetaObject_GetFieldAt(temp_s0, temp_s1 + 0x14)), 1000.0f);
    temp_a0 = ((struct Fld_19b8a0 *)igMetaObject_GetFieldAt(temp_s0, temp_s1 + 0x15));
    v3[0] = 1.0f; v3[1] = 0; v3[2] = 0;
    FUN_0018e470(temp_a0, v3);
    temp_s2 = ((struct Fld_19b8a0 *)igMetaObject_GetFieldAt(temp_s0, temp_s1 + 0x16));
    temp_s2->f56 = FUN_00131800();
    temp_s2->f52 = 1;
    temp_s2->f38 = 0;
    igBoolMetaField_SetDefaultValue(((struct Fld_19b8a0 *)igMetaObject_GetFieldAt(temp_s0, temp_s1 + 0x17)), 1);
    igBoolMetaField_SetDefaultValue(((struct Fld_19b8a0 *)igMetaObject_GetFieldAt(temp_s0, temp_s1 + 0x18)), 1);
    temp_s2 = ((struct Fld_19b8a0 *)igMetaObject_GetFieldAt(temp_s0, temp_s1 + 0x19));
    temp_s2->f56 = FUN_001341f0();
    temp_s2->f52 = 1;
    temp_s2->f38 = 0;
    temp_s2 = ((struct Fld_19b8a0 *)igMetaObject_GetFieldAt(temp_s0, temp_s1 + 0x1A));
    temp_s2->f56 = FUN_00133b70();
    temp_s2->f52 = 1;
    temp_s2->f38 = 0;
    temp_s2 = ((struct Fld_19b8a0 *)igMetaObject_GetFieldAt(temp_s0, temp_s1 + 0x1B));
    temp_s2->f56 = FUN_00132ba0();
    temp_s2->f52 = 1;
    temp_s2->f38 = 0;
    temp_s2 = ((struct Fld_19b8a0 *)igMetaObject_GetFieldAt(temp_s0, temp_s1 + 0x1C));
    temp_s2->f56 = FUN_00132850();
    temp_s2->f52 = 1;
    temp_s2->f38 = 0;
    temp_s2 = ((struct Fld_19b8a0 *)igMetaObject_GetFieldAt(temp_s0, temp_s1 + 0x1D));
    temp_s2->f56 = FUN_001341f0();
    temp_s2->f52 = 1;
    temp_s2->f38 = 0;
    temp_s2 = ((struct Fld_19b8a0 *)igMetaObject_GetFieldAt(temp_s0, temp_s1 + 0x1E));
    temp_s2->f56 = FUN_00133b70();
    temp_s2->f52 = 1;
    temp_s2->f38 = 0;
    temp_s2 = ((struct Fld_19b8a0 *)igMetaObject_GetFieldAt(temp_s0, temp_s1 + 0x1F));
    temp_s2->f56 = FUN_00132ba0();
    temp_s2->f52 = 1;
    temp_s2->f38 = 0;
    temp_s2 = ((struct Fld_19b8a0 *)igMetaObject_GetFieldAt(temp_s0, temp_s1 + 0x20));
    temp_s2->f56 = FUN_00132850();
    temp_s2->f52 = 1;
    temp_s2->f38 = 0;
    temp_s2 = ((struct Fld_19b8a0 *)igMetaObject_GetFieldAt(temp_s0, temp_s1 + 0x21));
    temp_s2->f56 = FUN_00138950();
    temp_s2->f52 = 1;
    temp_s2->f38 = 0;
    temp_s2 = ((struct Fld_19b8a0 *)igMetaObject_GetFieldAt(temp_s0, temp_s1 + 0x22));
    temp_s2->f56 = FUN_0014dfb0();
    temp_s2->f52 = 1;
    temp_s2->f38 = 0;
    temp_s2 = ((struct Fld_19b8a0 *)igMetaObject_GetFieldAt(temp_s0, temp_s1 + 0x23));
    temp_s2->f56 = FUN_00130440();
    temp_s2->f52 = 1;
    temp_s2->f38 = 0;
    temp_s2 = ((struct Fld_19b8a0 *)igMetaObject_GetFieldAt(temp_s0, temp_s1 + 0x24));
    temp_s2->f56 = FUN_00130440();
    temp_s2->f52 = 1;
    temp_s2->f38 = 0;
    temp_s2 = ((struct Fld_19b8a0 *)igMetaObject_GetFieldAt(temp_s0, temp_s1 + 0x25));
    temp_s2->f56 = FUN_00136750();
    temp_s2 = ((struct Fld_19b8a0 *)igMetaObject_GetFieldAt(temp_s0, temp_s1 + 0x26));
    temp_s2->f56 = FUN_00132850();
    temp_s2->f52 = 1;
    temp_s2->f38 = 0;
    igFloatMetaField_SetDefault(((struct Fld_19b8a0 *)igMetaObject_GetFieldAt(temp_s0, temp_s1 + 0x28)), 5.0f);
    igFloatMetaField_SetDefault(((struct Fld_19b8a0 *)igMetaObject_GetFieldAt(temp_s0, temp_s1 + 0x29)), -5.0f);
    igFloatMetaField_SetDefault(((struct Fld_19b8a0 *)igMetaObject_GetFieldAt(temp_s0, temp_s1 + 0x2A)), 5.0f);
    igFloatMetaField_SetDefault(((struct Fld_19b8a0 *)igMetaObject_GetFieldAt(temp_s0, temp_s1 + 0x2B)), -5.0f);
    temp_s2 = ((struct Fld_19b8a0 *)igMetaObject_GetFieldAt(temp_s0, temp_s1 + 0x2C));
    temp_s2->f56 = FUN_00131160();
    temp_s2->f52 = 1;
    temp_s2->f38 = 0;
    temp_s2 = ((struct Fld_19b8a0 *)igMetaObject_GetFieldAt(temp_s0, temp_s1 + 0x2D));
    temp_s2->f56 = FUN_00131160();
    temp_s2->f52 = 1;
    temp_s2->f38 = 0;
    temp_v0 = ((struct Fld_19b8a0 *)igMetaObject_GetFieldAt(temp_s0, temp_s1 + 0x2F));
    igBoolMetaField_SetDefaultValue(temp_v0, 1);
    temp_v0->f38 = 0;
    igMetaObject_NameFields(temp_s0, &g_igProjectiveShadowShader_fieldTable[0], &DAT_0048b9d0[0], &DAT_0048ba90[0], temp_s1);
}

