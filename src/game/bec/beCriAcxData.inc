void *FUN_003676d0(void) {
    igMetaObject *g = g_beCriAcxData_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false) {
        FUN_003677b0();
    }
    return g_beCriAcxData_metaObject[0];
}

int beCriAcxData_GetVTable(void) {
    union U_367720 u;
    int temp_s0;
    int temp_v0;
    int *temp_a1;
    int *temp_v1;
    char *q0;

    igObject_InitHeader(u.b);
    u.vt = (int)&DAT_00524950[0];
    q0 = &u.b[8];
    *(int *)q0 = 0;
    u.vt = (int)&DAT_00534d70[0];
    temp_s0 = *(int *)&u.b[*(int *)((char *)(g_objectSystem[0]) + 916)];
    u.vt = (int)&DAT_00524950[0];
    if (q0 != 0) {
        temp_v1 = *(int **)q0;
        if (temp_v1 != 0) {
            temp_a1 = temp_v1 - 2;
            temp_v0 = temp_v1[-1] - 1;
            temp_v1[-1] = temp_v0;
            if (temp_v0 == 0) {
                StringChunk_ReleaseHeader(*temp_a1, temp_a1);
            }
        }
    }
    return temp_s0;
}

void FUN_003677b0(void)
{
    igMetaObject_RunStaticInit(beCriAcxData_Register);
}

void *beCriAcxData_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beCriAcxData_metaObject,
        beBinDataObject_Register,
        beBinDataObject_GetPublishedMetaObject,
        beCriAcxData_GetMetaObject,
        beCriAcxData_className,
        0x18, /* instance size */
        beCriAcxData_GetVTable,
        0,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void beCriAcxData_GetMetaObject(void)
{
    FUN_003676d0();
}

