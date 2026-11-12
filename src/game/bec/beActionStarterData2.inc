void *FUN_0036ba10(void) {
    igMetaObject *g = g_beActionStarterData2_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false) {
        FUN_0036bb30();
    }
    return g_beActionStarterData2_metaObject[0];
}

int beActionStarterData2_GetVTable(void) {
    union U_36ba60 u;
    int temp_s1;
    void **q2;
    void **q3;
    int *temp_a1;
    int *temp_a1_2;
    int temp_v0;
    int temp_v0_2;
    void *temp_v1;
    void *temp_v1_2;

    igObject_InitHeader(u.b);
    q2 = &u.p[2];
    *q2 = 0;
    u.w[0] = (int)(&DAT_005344e0[0]);
    q3 = &u.p[3];
    *q3 = 0;
    u.w[0] = (int)(&DAT_00534480[0]);
    temp_s1 = *(int *)&u.b[*(int *)((char *)(g_objectSystem[0]) + 916)];
    u.w[0] = (int)(&DAT_005344e0[0]);
    if (q3 != 0) {
        temp_v1 = *q3;
        if (temp_v1 != 0) {
            temp_a1 = (int *)((char *)temp_v1 - 8);
            temp_v0 = *(int *)((char *)(temp_v1) - 4) - 1;
            *(int *)((char *)(temp_v1) - 4) = temp_v0;
            if (temp_v0 == 0) {
                StringChunk_ReleaseHeader(*temp_a1, temp_a1);
            }
        }
    }
    u.w[0] = (int)(&g_igNamedObject_vtable[0]);
    if (q2 != 0) {
        temp_v1_2 = *q2;
        if (temp_v1_2 != 0) {
            temp_a1_2 = (int *)((char *)temp_v1_2 - 8);
            temp_v0_2 = *(int *)((char *)(temp_v1_2) - 4) - 1;
            *(int *)((char *)(temp_v1_2) - 4) = temp_v0_2;
            if (temp_v0_2 == 0) {
                StringChunk_ReleaseHeader(*temp_a1_2, temp_a1_2);
            }
        }
    }
    return temp_s1;
}

void FUN_0036bb30(void)
{
    igMetaObject_RunStaticInit(beActionStarterData2_Register);
}

void *beActionStarterData2_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beActionStarterData2_metaObject,
        beActionStarterData_Register,
        beActionStarterData_GetPublishedMetaObject,
        beActionStarterData2_GetMetaObject,
        beActionStarterData2_className,
        0x30, /* instance size */
        beActionStarterData2_GetVTable,
        beActionStarterData2_InitFields,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void beActionStarterData2_GetMetaObject(void)
{
    FUN_0036ba10();
}

igMetaObject *FUN_0036bbe0(void) {
    return g_beActionStarterData_metaObject[0];
}

void beActionStarterData2_InitFields(void) {
    int temp_s1;
    void *temp_s0;

    temp_s0 = (void *)g_beActionStarterData2_metaObject[0];
    temp_s1 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &DAT_004c7df8[0], 1);
    igMetaObject_NameFields(temp_s0, &DAT_004c7e00[0], &DAT_004c7e08[0], &DAT_004c7e10[0], temp_s1);
}

