int FUN_001a3590(int arg0) {
    FUN_001a3700();
    return igMetaObject_CreateInstance(*(int *)0x561D30, arg0);
}

igMetaObject *igCompiledTransform_GetMetaObject(void)
{
    igMetaObject *g = g_igCompiledTransform_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_001a3700();
    return g_igCompiledTransform_metaObject[0];
}

int igCompiledTransform_GetVTable(void) {
    union U_1a3620 u;
    int temp_s1;
    void **q1;
    void **q2;
    struct Rc *temp_a0;
    struct Rc *temp_a0_2;

    igObject_InitHeader(u.b);
    q1 = &u.p[3];
    q2 = &u.p[6];
    u.w[0] = (int)(&DAT_0052a5a0[0]);
    *q1 = 0;
    *q2 = 0;
    temp_s1 = *(int *)&u.b[*(int *)((char *)(g_objectSystem[0]) + 916)];
    u.w[0] = (int)(&DAT_0052a5a0[0]);
    if (q2 != 0) {
        temp_a0 = (struct Rc *)*q2;
        if (temp_a0 != 0) {
            temp_a0->rc = temp_a0->rc - 1;
            if ((temp_a0->rc & 0x7FFFFF) == 0) {
                igObject_Destroy((void *)temp_a0);
            }
        }
    }
    if (q1 != 0) {
        temp_a0_2 = (struct Rc *)*q1;
        if (temp_a0_2 != 0) {
            temp_a0_2->rc = temp_a0_2->rc - 1;
            if ((temp_a0_2->rc & 0x7FFFFF) == 0) {
                igObject_Destroy((void *)temp_a0_2);
            }
        }
    }
    return temp_s1;
}

void FUN_001a3700(void)
{
    igMetaObject_RunStaticInit(igCompiledTransform_Register);
}

void igCompiledTransform_Register(void) {
    SceneGraphLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        ((char *)g_igCompiledTransform_metaObject),
        igObject_Register,
        igObject_GetMetaObject_ParentAccessor,
        thunk_igCompiledTransform_GetMetaObject,
        igCompiledTransform_className,
        0x24, /* instance size */
        igCompiledTransform_GetVTable,
        &igCompiledTransform_InitFields,
        0, /* extra callback item */
        g_igCompiledTransform_callbackList /* callback list */
    );
}

void thunk_igCompiledTransform_GetMetaObject(void) {
    igCompiledTransform_GetMetaObject();
}

void igCompiledTransform_InitFields(void) {
    int temp_s2;
    struct Fld_1a37a0 *temp_v0_2;
    struct Fld_1a37a0 *temp_v0;
    struct Fld_1a37a0 *temp_s1_2;
    struct Fld_1a37a0 *temp_s1;
    void *temp_s0;

    temp_s0 = (void *)g_igCompiledTransform_metaObject[0];
    temp_s2 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &DAT_0048c6e0[0], 8);
    ((struct Fld_1a37a0 *)igMetaObject_GetFieldAt(temp_s0, temp_s2))->f38 = 0;
    temp_s1 = ((struct Fld_1a37a0 *)igMetaObject_GetFieldAt(temp_s0, temp_s2 + 1));
    temp_s1->f56 = (int)FUN_00194dd0();
    temp_s1->f38 = 0;
    temp_v0 = ((struct Fld_1a37a0 *)igMetaObject_GetFieldAt(temp_s0, temp_s2 + 2));
    FUN_002ea4b0(temp_v0, -1);
    temp_v0->f38 = 0;
    ((struct Fld_1a37a0 *)igMetaObject_GetFieldAt(temp_s0, temp_s2 + 3))->f38 = 0;
    temp_s1_2 = ((struct Fld_1a37a0 *)igMetaObject_GetFieldAt(temp_s0, temp_s2 + 4));
    temp_s1_2->f56 = FUN_002b9540();
    temp_s1_2->f52 = 1;
    temp_s1_2->f38 = 0;
    temp_v0_2 = ((struct Fld_1a37a0 *)igMetaObject_GetFieldAt(temp_s0, temp_s2 + 5));
    FUN_002d3890(temp_v0_2, 1);
    temp_v0_2->f38 = 0;
    ((struct Fld_1a37a0 *)igMetaObject_GetFieldAt(temp_s0, temp_s2 + 6))->f38 = 0;
    ((struct Fld_1a37a0 *)igMetaObject_GetFieldAt(temp_s0, temp_s2 + 7))->f38 = 0;
    igMetaObject_NameFields(temp_s0, &DAT_0048c700[0], &DAT_0048c720[0], &DAT_0048c740[0], temp_s2);
}

