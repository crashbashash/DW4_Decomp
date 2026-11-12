void *FUN_00345ea0(void) {
    igMetaObject *g = g_beSeInfoData_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false) {
        FUN_00345fd0();
    }
    return g_beSeInfoData_metaObject[0];
}

int beSeInfoData_GetVTable(void) {
    Obj_345ef0 obj;
    int r;

    igObject_InitHeader(&obj);
    obj.m8 = 0;
    obj.vt = &DAT_00538f40[0];
    obj.m16 = 0;
    r = *(int *)((char *)&obj + *(int *)((char *)(g_objectSystem[0]) + 916));
    obj.vt = &DAT_00538f40[0];
    obj.rel16();
    obj.vt = &DAT_00524950[0];
    obj.rel8();
    return r;
}

void FUN_00345fd0(void)
{
    igMetaObject_RunStaticInit(beSeInfoData_Register);
}

void *beSeInfoData_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beSeInfoData_metaObject,
        beBaseInfoData_Register,
        beBaseInfoData_GetPublishedMetaObject,
        beSeInfoData_GetMetaObject,
        beSeInfoData_className,
        0x14, /* instance size */
        beSeInfoData_GetVTable,
        beSeInfoData_InitFields,
        0, /* extra callback item */
        g_beSeInfoData_callbackList /* callback list */
    );
}

void beSeInfoData_GetMetaObject(void)
{
    FUN_00345ea0();
}

void beSeInfoData_InitFields(void) {
    int temp_s2;
    void *temp_s1;
    void *temp_s0;

    temp_s0 = (void *)g_beSeInfoData_metaObject[0];
    temp_s2 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &DAT_004c3bb0[0], 1);
    temp_s1 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2));
    ((igObjectRefMetaField *)temp_s1)->_metaObject = (int)FUN_00346120();
    igMetaObject_NameFields(temp_s0, &DAT_004c3bb8[0], &DAT_004c3bc0[0], &DAT_004c3bc8[0], temp_s2);
}

