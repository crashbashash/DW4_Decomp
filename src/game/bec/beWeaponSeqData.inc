void *FUN_0033f170(void) {
    igMetaObject *g = g_beWeaponSeqData_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false) {
        FUN_0033f290();
    }
    return g_beWeaponSeqData_metaObject[0];
}

int beWeaponSeqData_GetVTable(void) {
    Obj_33f1c0 obj;
    int r;

    igObject_InitHeader(&obj);
    obj.r1 = 0;
    obj.vt = &DAT_00539c80[0];
    obj.r2 = 0;
    r = *(int *)((char *)&obj + *(int *)((char *)(g_objectSystem[0]) + 916));
    obj.vt = &DAT_00539c80[0];
    obj.rel2();
    obj.vt = &DAT_00524950[0];
    obj.rel1();
    return r;
}

void FUN_0033f290(void)
{
    igMetaObject_RunStaticInit(beWeaponSeqData_Register);
}

void *beWeaponSeqData_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beWeaponSeqData_metaObject,
        igNamedObject_Register,
        igNamedObject_GetPublishedMetaObject,
        beWeaponSeqData_GetMetaObject,
        beWeaponSeqData_className,
        0x10, /* instance size */
        beWeaponSeqData_GetVTable,
        beWeaponSeqData_InitFields,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void beWeaponSeqData_GetMetaObject(void)
{
    FUN_0033f170();
}

void beWeaponSeqData_InitFields(void) {
    int temp_s1;
    void *temp_s0;

    temp_s0 = (void *)g_beWeaponSeqData_metaObject[0];
    temp_s1 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &DAT_004c2fd8[0], 1);
    igMetaObject_NameFields(temp_s0, &DAT_004c2fe0[0], &DAT_004c2fe8[0], &DAT_004c2ff0[0], temp_s1);
}

int FUN_0033f3b0(void) {
    if (DAT_00587a60[0] == 0) {
        DAT_00587a60[0] = igMetaEnum_Create(&DAT_005016f0[0], &DAT_004c2ff8[0], &DAT_004c3008[0], 3);
    }
    return DAT_00587a60[0];
}

