int FUN_00136750(void) {
    if (DAT_0055f088[0] == 0) {
        DAT_0055f088[0] = igMetaObject_Create(Memory_GetAllocatorBySelector(DAT_00587040[0]));
    }
    return DAT_0055f088[0];
}

igMetaObject *igLightAttr_GetMetaObject(void)
{
    igMetaObject *g = g_igLightAttr_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_00136880();
    return g_igLightAttr_metaObject[0];
}

int igLightAttr_GetVTable(void) {
    union U_1367f0 u;
    int temp_s0;
    char *ps;
    int *temp_a0;
    igObject_InitHeader(u.b);
    u.vt = (int)&DAT_00523700[0];
    ps = &u.b[140];
    *(int *)ps = 0;
    temp_s0 = *(int *)&u.b[*(int *)((char *)(DAT_00586dc8[0]) + 916)];
    u.vt = (int)&DAT_00523700[0];
    if (ps != 0) {
        temp_a0 = *(int **)ps;
        if (temp_a0 != 0) {
            temp_a0[1] = temp_a0[1] - 1;
            if (((unsigned long long) ((long long) temp_a0[1] << 0x29) >> 0x29) == 0) {
                igObject_Destroy(temp_a0);
            }
        }
    }
    return temp_s0;
}

void FUN_00136880(void)
{
    igMetaObject_RunStaticInit(igLightAttr_Register);
}

void igLightAttr_Register(void) {
    AttrsLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igLightAttr_metaObject,
        igVisualAttribute_Register,
        igVisualAttribute_GetPublishedMetaObject,
        thunk_igLightAttr_GetMetaObject,
        igLightAttr_className,
        0x94, /* instance size */
        igLightAttr_GetVTable,
        &igLightAttr_InitFields,
        0, /* extra callback item */
        g_igLightAttr_callbackList /* callback list */
    );
}

void thunk_igLightAttr_GetMetaObject(void) {
    igLightAttr_GetMetaObject();
}

void igLightAttr_InitFields(void) {
    float vh[4];
    float vg[4];
    float vf[4];
    float ve[4];
    float vd[4];
    float vc[4];
    float vb[4];
    float va[4];
    int temp_s1;
    void *temp_s0;
    struct LightMetaFieldView *temp_s2;
    struct LightMetaFieldView *tv;

    temp_s0 = (void *)DAT_0055f088[0];
    temp_s1 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &DAT_00486370[0], 0x10);
    temp_s2 = (LightMetaFieldView *)igMetaObject_GetFieldAt(temp_s0, temp_s1);
    FUN_002dc7a0(temp_s2, &DAT_00486470[0]);
    temp_s2->f48 = (void (*)())FUN_0013ef20;
    temp_s2->f52 = (void (*)(void))FUN_00149a40;
    temp_s2 = (LightMetaFieldView *)igMetaObject_GetFieldAt(temp_s0, temp_s1 + 1);
    FUN_002ea4b0(temp_s2, -1);
    temp_s2->f38 = 0;
    temp_s2->f40 = 4;
    temp_s2->f39 = 4;
    temp_s2->f44 = 3;
    temp_s2 = (LightMetaFieldView *)igMetaObject_GetFieldAt(temp_s0, temp_s1 + 2);
    vh[0] = 0; vh[1] = 0; vh[2] = 0;
    FUN_0018e470(temp_s2, vh);
    temp_s2->f48 = (void (*)())FUN_0013ef20;
    temp_s2 = (LightMetaFieldView *)igMetaObject_GetFieldAt(temp_s0, temp_s1 + 3);
    vc[3] = 1.0f; vc[0] = 0.6f; vc[1] = 0.6f; vc[2] = 0.6f;
    FUN_0018e670(temp_s2, vc);
    temp_s2->f48 = (void (*)())FUN_0013ef20;
    temp_s2 = (LightMetaFieldView *)igMetaObject_GetFieldAt(temp_s0, temp_s1 + 4);
    vb[0] = 1.0f; vb[1] = 1.0f; vb[2] = 1.0f; vb[3] = 1.0f;
    FUN_0018e670(temp_s2, vb);
    temp_s2->f48 = (void (*)())FUN_0013ef20;
    temp_s2 = (LightMetaFieldView *)igMetaObject_GetFieldAt(temp_s0, temp_s1 + 5);
    va[3] = 1.0f; va[0] = 0; va[1] = 0; va[2] = 0;
    FUN_0018e670(temp_s2, va);
    temp_s2->f48 = (void (*)())FUN_0013ef20;
    temp_s2 = (LightMetaFieldView *)igMetaObject_GetFieldAt(temp_s0, temp_s1 + 6);
    vg[2] = 1.0f; vg[0] = 0; vg[1] = 0;
    FUN_0018e470(temp_s2, vg);
    temp_s2->f48 = (void (*)())FUN_0013ef20;
    tv = (LightMetaFieldView *)igMetaObject_GetFieldAt(temp_s0, temp_s1 + 7);
    tv->f48 = (void (*)())FUN_0013ef20;
    temp_s2 = (LightMetaFieldView *)igMetaObject_GetFieldAt(temp_s0, temp_s1 + 8);
    FUN_002e3810(temp_s2, 180.0f);
    temp_s2->f48 = (void (*)())FUN_0013ef20;
    temp_s2 = (LightMetaFieldView *)igMetaObject_GetFieldAt(temp_s0, temp_s1 + 9);
    vf[0] = 1.0f; vf[1] = 0; vf[2] = 0;
    FUN_0018e470(temp_s2, vf);
    temp_s2->f48 = (void (*)())FUN_0013ef20;
    tv = (LightMetaFieldView *)igMetaObject_GetFieldAt(temp_s0, temp_s1 + 0xA);
    tv->f48 = (void (*)())FUN_0013ef20;
    temp_s2 = (LightMetaFieldView *)igMetaObject_GetFieldAt(temp_s0, temp_s1 + 0xB);
    ve[0] = 0; ve[1] = 0; ve[2] = 0;
    FUN_0018e470(temp_s2, ve);
    temp_s2 = (LightMetaFieldView *)igMetaObject_GetFieldAt(temp_s0, temp_s1 + 0xC);
    vd[0] = 0; vd[2] = -1.0f; vd[1] = 0;
    FUN_0018e470(temp_s2, vd);
    temp_s2 = (LightMetaFieldView *)igMetaObject_GetFieldAt(temp_s0, temp_s1 + 0xD);
    temp_s2->f56 = FUN_0014a040();
    temp_s2->f38 = 0;
    temp_s2->f40 = 1;
    temp_s2->f39 = 1;
    temp_s2->f44 = 3;
    temp_s2 = (LightMetaFieldView *)igMetaObject_GetFieldAt(temp_s0, temp_s1 + 0xE);
    FUN_002d3890(temp_s2, 1);
    temp_s2->f38 = 0;
    temp_s2 = (LightMetaFieldView *)igMetaObject_GetFieldAt(temp_s0, temp_s1 + 0xF);
    FUN_002d3890(temp_s2, 1);
    temp_s2->f38 = 0;
    igMetaObject_NameFields(temp_s0, &DAT_004863b0[0], &DAT_004863f0[0], &DAT_00486430[0], temp_s1);
}

