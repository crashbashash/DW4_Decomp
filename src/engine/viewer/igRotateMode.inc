int FUN_0045c540(void) {
    if (DAT_0058cbf0[0] == 0) {
        DAT_0058cbf0[0] = igMetaEnum_Create(&DAT_0051f630[0], &DAT_004d1460[0], &DAT_004d1470[0], 3);
    }
    return DAT_0058cbf0[0];
}

void FUN_0045c5a0(int arg0) {
    FUN_0045c680();
    igMetaObject_CreateInstance(*(int *)0x58CBF8, arg0);
}

void *igRotateMode_GetMetaObject(void) {
    bool ok;
    if (((S_45c5e0 *)g_igRotateMode_metaObject[0]) == 0) goto make;
    ok = !!(((S_45c5e0 *)g_igRotateMode_metaObject[0])->f & 4);
    if (ok != false) goto done;
make:
    FUN_0045c680();
done:;
    return ((S_45c5e0 *)g_igRotateMode_metaObject[0]);
}

int igRotateMode_GetVTable(void) {
    union U_45c630 u;
    igObject_InitHeader(u.b);
    u.vt = (int)&DAT_00542960[0];
    igMatrix44f_SetIdentity(&u.b[12]);
    u.vt = (int)&DAT_005427b0[0];
    return *(int *)&u.b[*(int *)((char *)((void *)g_objectSystem[0]) + 916)];
}

void FUN_0045c680(void)
{
    igMetaObject_RunStaticInit(igRotateMode_Register);
}

void igRotateMode_Register(void) {
    ViewerLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igRotateMode_metaObject,
        igViewMode_Register,
        igViewMode_GetPublishedMetaObject,
        thunk_igRotateMode_GetMetaObject,
        igRotateMode_className,
        0x94, /* instance size */
        igRotateMode_GetVTable,
        &igRotateMode_InitFields,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void thunk_igRotateMode_GetMetaObject(void) {
    igRotateMode_GetMetaObject();
}

void igRotateMode_InitFields(void) {
    int temp_s2;
    int spA[2];
    int spB[2];
    int spC[2];
    int spD[3];
    void *temp_v0;
    void *temp_a0_4;
    void *temp_a0_3;
    void *temp_a0_2;
    void *temp_a0;
    void *temp_s0;

    temp_s0 = (void *)g_igRotateMode_metaObject[0];
    temp_s2 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &DAT_004d1480[0], 0x10);
    FUN_002e3810(igMetaObject_GetFieldAt(temp_s0, temp_s2), 1.0f);
    temp_a0 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 1));
    spA[0] = 0;
    spA[1] = 0;
    FUN_0018e2f0(temp_a0, spA);
    temp_a0_2 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 5));
    spB[0] = 0;
    spB[1] = 0;
    FUN_0018e2f0(temp_a0_2, spB);
    temp_a0_3 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 6));
    spC[0] = 0;
    spC[1] = 0;
    FUN_0018e2f0(temp_a0_3, spC);
    temp_v0 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 8));
    FUN_002dc7a0(temp_v0, &DAT_004d1580[0]);
    *(int *)((char *)(temp_v0) + 52) = (int)(&FUN_0045c540);
    FUN_002d3890(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 9), 1);
    FUN_002e3810(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 0xB), 0.0f);
    FUN_002e3810(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 0xC), 0.0f);
    FUN_002e3810(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 0xD), 0.0f);
    FUN_002e3810(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 0xE), 1.0f);
    temp_a0_4 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 0xF));
    spD[0] = 0;
    spD[1] = 0;
    spD[2] = 0;
    FUN_0018e470(temp_a0_4, spD);
    igMetaObject_NameFields(temp_s0, &DAT_004d14c0[0], &DAT_004d1500[0], &DAT_004d1540[0], temp_s2);
}

