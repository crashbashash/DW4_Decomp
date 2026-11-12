void *FUN_003600b0(void) {
    bool ok;
    if (DAT_00589560[0] == 0) goto make;
    ok = !!(DAT_00589560[0]->f & 4);
    if (ok != false) goto done;
make:
    FUN_003601e0();
done:;
    return DAT_00589560[0];
}

int beGeneraterPlayerData_GetVTable(void) {
    Obj_360100 obj;
    int r;

    igObject_InitHeader(&obj);
    obj.vt = &DAT_00535de0[0];
    obj.r3 = 0;
    obj.r4 = 0;
    r = *(int *)((char *)&obj + *(int *)((char *)(DAT_00586dc8[0]) + 916));
    obj.vt = &DAT_00535de0[0];
    obj.rel4();
    obj.rel3();
    return r;
}

void FUN_003601e0(void)
{
    igMetaObject_RunStaticInit(beGeneraterPlayerData_Register);
}

void *beGeneraterPlayerData_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beGeneraterPlayerData_metaObject,
        igObject_Register,
        igObject_GetMetaObject_ParentAccessor,
        beGeneraterPlayerData_GetMetaObject,
        beGeneraterPlayerData_className,
        0x18, /* instance size */
        beGeneraterPlayerData_GetVTable,
        beGeneraterPlayerData_InitFields,
        0, /* extra callback item */
        g_beGeneraterPlayerData_callbackList /* callback list */
    );
}

void beGeneraterPlayerData_GetMetaObject(void)
{
    FUN_003600b0();
}

void beGeneraterPlayerData_InitFields(void) {
    int temp_s2;
    void *temp_s1_2;
    void *temp_s1;
    void *temp_s0;

    temp_s0 = (void *)((int *)DAT_00589560)[0];
    temp_s2 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &DAT_004c6a90[0], 4);
    temp_s1 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 2));
    ((igObjectRefMetaField *)temp_s1)->_metaObject = FUN_00360360();
    ((igRefMetaField *)temp_s1)->_construct = 1;
    temp_s1_2 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 3));
    ((igObjectRefMetaField *)temp_s1_2)->_metaObject = FUN_00360360();
    ((igRefMetaField *)temp_s1_2)->_construct = 1;
    igMetaObject_NameFields(temp_s0, &DAT_004c6aa0[0], &DAT_004c6ab0[0], &DAT_004c6ac0[0], temp_s2);
}

