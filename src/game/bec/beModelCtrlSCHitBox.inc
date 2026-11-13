void beModelCtrlSCHitBox_Create(int arg0) {
    FUN_0034f7c0();
    igMetaObject_CreateInstance(*(int *)0x5887C8, arg0);
}

igMetaObject *FUN_0034f730(void) {
    if (g_beModelCtrlSCHitBox_metaObject[0] == 0 || !isValid(g_beModelCtrlSCHitBox_metaObject[0])) FUN_0034f7c0();
    return g_beModelCtrlSCHitBox_metaObject[0];
}

int beModelCtrlSCHitBox_GetVTable(void) {
    struct Obj_34f780 obj;

    igObject_InitHeader(&obj);
    obj.vt = &DAT_0053af60[0];
    return *(int *)((char *)&obj + *(int *)((char *)(g_objectSystem[0]) + 916));
}

void FUN_0034f7c0(void)
{
    igMetaObject_RunStaticInit(beModelCtrlSCHitBox_Register);
}

void *beModelCtrlSCHitBox_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beModelCtrlSCHitBox_metaObject,
        beModelCtrlSubComBase_Register,
        beModelCtrlSubComBase_GetPublishedMetaObject,
        beModelCtrlSCHitBox_GetMetaObject,
        beModelCtrlSCHitBox_className,
        0x3c, /* instance size */
        beModelCtrlSCHitBox_GetVTable,
        beModelCtrlSCHitBox_InitFields,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void beModelCtrlSCHitBox_GetMetaObject(void)
{
    FUN_0034f730();
}

void beModelCtrlSCHitBox_InitFields(void) {
    int temp_s1;
    void *temp_s0;

    temp_s0 = (void *)g_beModelCtrlSCHitBox_metaObject[0];
    temp_s1 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &DAT_004c4c00[0], 6);
    igMetaObject_NameFields(temp_s0, &DAT_004c4c20[0], &DAT_004c4c40[0], &DAT_004c4c60[0], temp_s1);
}

