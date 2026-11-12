int FUN_00451ac0(void) {
    if (DAT_0058c5a8[0] == 0) {
        DAT_0058c5a8[0] = igMetaEnum_Create(&DAT_0051e648[0], &DAT_004d0790[0], &DAT_004d07a0[0], 4);
    }
    return DAT_0058c5a8[0];
}

igMetaObject *igDefaultAspectElement_GetMetaObject(void)
{
    igMetaObject *g = g_igDefaultAspectElement_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        igDefaultAspectElement_EnsureRegistered();
    return g_igDefaultAspectElement_metaObject[0];
}

int igDefaultAspectElement_GetVTable(void) {
    union U_451b70 u;
    int t;
    struct Rc *a;
    int *a1;
    int v0;
    char *c;
    void **q4c;
    void **q48;
    void **q50;
    igObject_InitHeader(u.b);
    q48 = &u.p[2];
    q4c = &u.p[3];
    q50 = &u.p[4];
    u.w[0] = (int)(&DAT_00541840[0]);
    *q48 = 0;
    *q4c = 0;
    *q50 = 0;
    t = *(int *)&u.b[*(int *)((char *)(g_objectSystem[0]) + 916)];
    u.w[0] = (int)(&DAT_00541840[0]);
    if (q50 != 0) {
        a = (struct Rc *)*q50;
        if (a != 0) {
            a->rc = a->rc - 1;
            if ((a->rc & 0x7FFFFF) == 0) {
                igObject_Destroy(a);
            }
        }
    }
    if (q4c != 0) {
        a = (struct Rc *)*q4c;
        if (a != 0) {
            a->rc = a->rc - 1;
            if ((a->rc & 0x7FFFFF) == 0) {
                igObject_Destroy(a);
            }
        }
    }
    if (q48 != 0) {
        a = (struct Rc *)*q48;
        if (a != 0) {
            a->rc = a->rc - 1;
            if ((a->rc & 0x7FFFFF) == 0) {
                igObject_Destroy(a);
            }
        }
    }
    return t;
}

void igDefaultAspectElement_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(igDefaultAspectElement_Register);
}

void igDefaultAspectElement_Register(void) {
    GuiLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igDefaultAspectElement_metaObject,
        igObject_Register,
        igObject_GetMetaObject_ParentAccessor,
        thunk_igDefaultAspectElement_GetMetaObject,
        igDefaultAspectElement_className,
        0x20, /* instance size */
        igDefaultAspectElement_GetVTable,
        &igDefaultAspectElement_InitFields,
        0, /* extra callback item */
        g_igDefaultAspectElement_callbackList /* callback list */
    );
}

void thunk_igDefaultAspectElement_GetMetaObject(void) {
    igDefaultAspectElement_GetMetaObject();
}

void igDefaultAspectElement_InitFields(void) {
    int temp_s2;
    void *temp_v0;
    void *temp_s1_3;
    void *temp_s1_2;
    void *temp_s1;
    void *temp_s0;

    temp_s0 = (void *)g_igDefaultAspectElement_metaObject[0];
    temp_s2 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &DAT_004d07c0[0], 6);
    temp_s1 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2));
    *(int *)((char *)(temp_s1) + 56) = (int)FUN_004505b0();
    temp_s1_2 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 1));
    *(int *)((char *)(temp_s1_2) + 56) = (int)FUN_004521d0();
    temp_s1_3 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 2));
    *(int *)((char *)(temp_s1_3) + 56) = FUN_00196190();
    *(unsigned char *)((char *)(temp_s1_3) + 52) = 1;
    temp_v0 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 3));
    FUN_002dc7a0(temp_v0, &DAT_004d0838[0]);
    *(int *)((char *)(temp_v0) + 52) = (int)(FUN_00451ac0);
    igMetaObject_NameFields(temp_s0, &DAT_004d07e0[0], &DAT_004d0800[0], &DAT_004d0820[0], temp_s2);
}

