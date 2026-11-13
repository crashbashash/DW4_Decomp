igMetaObject *FUN_0045b420(void) {
    if (g_igViewerParameters_metaObject[0] == 0) {
        g_igViewerParameters_metaObject[0] = igMetaObject_Create(Memory_GetAllocatorBySelector(g_metadataAllocatorKey[0]));
    }
    return g_igViewerParameters_metaObject[0];
}

SigViewerParameters_GetMetaObject *igViewerParameters_GetMetaObject(void) {
    if (((SigViewerParameters_GetMetaObject *)g_igViewerParameters_metaObject[0]) == 0 || !((SigViewerParameters_GetMetaObject *)g_igViewerParameters_metaObject[0])->ok()) FUN_0045b590();
    return ((SigViewerParameters_GetMetaObject *)g_igViewerParameters_metaObject[0]);
}

int igViewerParameters_GetVTable(void) {
    union U_45b4c0 u;
    int temp_s1;
    int pi = (int)u.b;
    char *p;
    igObject_InitHeader(pi);
    *(int *)&u.b[8] = 0;
    u.vt = (int)&DAT_005420a0[0];
    p = &u.b[12];
    *(int *)p = 0;
    igMatrix44f_SetIdentity(&u.b[44]);
    igMatrix44f_SetIdentity(pi + 108);
    *(int *)(pi + 204) = 0;
    *(int *)(pi + 220) = 0;
    *(int *)(pi + 240) = 0;
    temp_s1 = *(int *)&u.b[*(int *)((char *)(((void *)g_objectSystem[0])) + 916)];
    u.vt = (int)&DAT_00542090[4];
    FUN_001d6560(&u.b[240], -1);
    FUN_0019b1f0(&u.b[220], -1);
    FUN_00196a50(&u.b[204], -1);
    FUN_00229350(p, -1);
    FUN_0044c110(u.b, 0);
    return temp_s1;
}

void FUN_0045b590(void)
{
    igMetaObject_RunStaticInit(igViewerParameters_Register);
}

void igViewerParameters_Register(void) {
    ViewerLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igViewerParameters_metaObject,
        igModel_Register,
        igModel_GetPublishedMetaObject,
        thunk_igViewerParameters_GetMetaObject,
        igViewerParameters_className,
        0x108, /* instance size */
        igViewerParameters_GetVTable,
        &igViewerParameters_InitFields,
        0, /* extra callback item */
        g_igViewerParameters_callbackList /* callback list */
    );
}

void thunk_igViewerParameters_GetMetaObject(void) {
    igViewerParameters_GetMetaObject();
}

void igViewerParameters_InitFields(void) {
    struct Fld *temp_s2_4;
    struct Fld *temp_s2_3;
    struct Fld *temp_s2_2;
    struct Fld *temp_s2;
    void *temp_a0_2;
    void *temp_a0;
    int temp_s1;
    void *temp_s0;
    int sp50[3];
    int sp48[2];

    temp_s0 = (void *)g_igViewerParameters_metaObject[0];
    temp_s1 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &g_igViewerParameters_ctorTable[0], 0x27);
    temp_s2 = (struct Fld *)igMetaObject_GetFieldAt(temp_s0, temp_s1);
    temp_s2->f56 = FUN_0019f210();
    temp_s2->f52 = 1;
    temp_a0 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s1 + 1));
    sp50[0] = 0;
    sp50[1] = 0x3F800000;
    sp50[2] = 0;
    FUN_0018e470(temp_a0, sp50);
    FUN_002e3810(igMetaObject_GetFieldAt(temp_s0, temp_s1 + 2), 1.0f);
    FUN_002e3810(igMetaObject_GetFieldAt(temp_s0, temp_s1 + 3), 45.0f);
    FUN_002e3810(igMetaObject_GetFieldAt(temp_s0, temp_s1 + 4), 1.0f);
    FUN_002e3810(igMetaObject_GetFieldAt(temp_s0, temp_s1 + 5), 1000.0f);
    FUN_002ea4b0(igMetaObject_GetFieldAt(temp_s0, temp_s1 + 0xC), 0);
    FUN_002d3890(igMetaObject_GetFieldAt(temp_s0, temp_s1 + 0x10), 1);
    temp_s2_2 = (struct Fld *)igMetaObject_GetFieldAt(temp_s0, temp_s1 + 0x18);
    temp_s2_2->f56 = FUN_001a4d90();
    temp_s2_2->f52 = 1;
    FUN_002d3890(igMetaObject_GetFieldAt(temp_s0, temp_s1 + 0x19), 1);
    FUN_002d3890(igMetaObject_GetFieldAt(temp_s0, temp_s1 + 0x1A), 1);
    FUN_002ea4b0(igMetaObject_GetFieldAt(temp_s0, temp_s1 + 0x1D), 1);
    FUN_002ea4b0(igMetaObject_GetFieldAt(temp_s0, temp_s1 + 0x1E), 4);
    temp_s2_3 = (struct Fld *)igMetaObject_GetFieldAt(temp_s0, temp_s1 + 0x1F);
    temp_s2_3->f56 = FUN_0019f4c0();
    temp_s2_3->f52 = 1;
    temp_s2_4 = (struct Fld *)igMetaObject_GetFieldAt(temp_s0, temp_s1 + 0x22);
    temp_s2_4->f56 = FUN_0019f670();
    FUN_002ea4b0(igMetaObject_GetFieldAt(temp_s0, temp_s1 + 0x23), 1);
    FUN_002ea4b0(igMetaObject_GetFieldAt(temp_s0, temp_s1 + 0x24), 2);
    FUN_002e3810(igMetaObject_GetFieldAt(temp_s0, temp_s1 + 0x25), 1.0f);
    temp_a0_2 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s1 + 0x26));
    sp48[0] = 0;
    sp48[1] = 0;
    FUN_0018e2f0(temp_a0_2, sp48);
    igMetaObject_NameFields(temp_s0, &g_igViewerParameters_fieldTable[0], &DAT_004d1180[0], &DAT_004d1220[0], temp_s1);
}

