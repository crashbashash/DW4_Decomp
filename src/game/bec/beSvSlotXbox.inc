void *FUN_0034a8c0(void) {
    struct G *g = DAT_00588348[0];
    if (!g || ((g->f & 4) != 0) == false) {
        FUN_0034a9a0();
    }
    return DAT_00588348[0];
}

int beSvSlotXbox_GetVTable(void) {
    union U_34a910 u;
    int temp_s0;
    char *ps;
    int *temp_v1;
    int *temp_a1;
    int temp_v0;

    igObject_InitHeader(u.b);
    u.vt = (int)&DAT_00538970[0];
    ps = &u.b[24];
    *(int *)ps = 0;
    temp_s0 = *(int *)&u.b[*(int *)((char *)(DAT_00586dc8[0]) + 916)];
    u.vt = (int)&DAT_00538970[0];
    if (ps != 0) {
        temp_v1 = *(int **)ps;
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

void FUN_0034a9a0(void)
{
    igMetaObject_RunStaticInit(beSvSlotXbox_Register);
}

void *beSvSlotXbox_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beSvSlotXbox_metaObject,
        beSvSlotData_Register,
        beSvSlotData_GetPublishedMetaObject,
        beSvSlotXbox_GetMetaObject,
        beSvSlotXbox_className,
        0x38, /* instance size */
        beSvSlotXbox_GetVTable,
        beSvSlotXbox_InitFields,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void beSvSlotXbox_GetMetaObject(void)
{
    FUN_0034a8c0();
}

void beSvSlotXbox_InitFields(void) {
    int temp_s1;
    void *temp_s0;

    temp_s0 = (void *)((int *)DAT_00588348)[0];
    temp_s1 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &DAT_004c42b0[0], 4);
    igStringMetaField_SetDefaultText(((int)igMetaObject_GetFieldAt(temp_s0, temp_s1)), &DAT_00502a98[0]);
    igMetaObject_NameFields(temp_s0, &DAT_004c42c0[0], &DAT_004c42d0[0], &DAT_004c42e0[0], temp_s1);
}

