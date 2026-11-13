void beNDMWStatusCtrlD0_Create(int arg0) {
    FUN_003bb040();
    igMetaObject_CreateInstance(*(int *)0x58AF98, arg0);
}

void *FUN_003baf50(void) {
    unsigned char b;
    if (g_beNDMWStatusCtrlD0_metaObject[0] != 0) {
        b = (*(int *)((char *)(g_beNDMWStatusCtrlD0_metaObject[0]) + 36) & 4) != 0;
        if (b != 0) goto done;
    }
    FUN_003bb040();
done:
    return g_beNDMWStatusCtrlD0_metaObject[0];
}

int beNDMWStatusCtrlD0_GetVTable(void) {
    struct Obj_3bafa0 obj;
    int temp_s1;

    igObject_InitHeader(&obj);
    obj.f34 = 0;
    obj.f38 = 0;
    obj.f3C = 0;
    obj.f40 = 0;
    obj.f44 = 0;
    obj.f48 = 0;
    obj.f4C = 0;
    obj.vt = (&DAT_0053eed0[0]);
    obj.f64 = 0;
    obj.f70 = 0;
    temp_s1 = *(int *)((char *)&obj + *(int *)((char *)(g_objectSystem[0]) + 916));
    obj.vt = (&DAT_0053eed0[0]);
    FUN_00226990(&obj.f70, -1);
    ObjectRef_Destruct_00150eb0(&obj.f64, -1);
    FUN_003b6770((int **)&obj, (long long)0);
    return temp_s1;
}

void FUN_003bb040(void)
{
    igMetaObject_RunStaticInit(beNDMWStatusCtrlD0_Register);
}

void *beNDMWStatusCtrlD0_Register(void) {
    NdmwLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beNDMWStatusCtrlD0_metaObject,
        beNDMWListCtrl_Register,
        beNDMWListCtrl_GetPublishedMetaObject,
        beNDMWStatusCtrlD0_GetMetaObject,
        beNDMWStatusCtrlD0_className,
        0x74, /* instance size */
        beNDMWStatusCtrlD0_GetVTable,
        beNDMWStatusCtrlD0_InitFields,
        0, /* extra callback item */
        g_beNDMWStatusCtrlD0_callbackList /* callback list */
    );
}

void beNDMWStatusCtrlD0_GetMetaObject(void)
{
    FUN_003baf50();
}

void beNDMWStatusCtrlD0_InitFields(void) {
    int temp_s2;
    void *temp_s1_2;
    void *temp_s1;
    void *temp_s0;

    temp_s0 = (void *)g_beNDMWStatusCtrlD0_metaObject[0];
    temp_s2 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &DAT_004c9f90[0], 8);
    temp_s1 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 1));
    ((igObjectRefMetaField *)temp_s1)->_metaObject = igIntList_GetOrCreateMetaObject();
    ((igRefMetaField *)temp_s1)->_construct = 1;
    FUN_002d3890(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 6), 1);
    temp_s1_2 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 7));
    ((igObjectRefMetaField *)temp_s1_2)->_metaObject = FUN_002cb110();
    ((igRefMetaField *)temp_s1_2)->_construct = 1;
    igMetaObject_NameFields(temp_s0, &DAT_004c9fb0[0], &DAT_004c9fd0[0], &DAT_004c9ff0[0], temp_s2);
}

