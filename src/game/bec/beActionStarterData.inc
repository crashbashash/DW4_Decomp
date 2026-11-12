void *FUN_0036bdf0(void) {
    struct G *g = DAT_00589e60[0];
    if (!g || ((g->f & 4) != 0) == false) {
        FUN_0036bf10();
    }
    return DAT_00589e60[0];
}

int beActionStarterData_GetVTable(void) {
    Obj_36be40 obj;
    int r;

    igObject_InitHeader(&obj);
    obj._name = 0;
    obj._vtable = (int)&DAT_005344e0[0];
    obj._message = 0;
    r = *(int *)((char *)&obj + *(int *)((char *)(DAT_00586dc8[0]) + 916));
    obj._vtable = (int)&DAT_005344e0[0];
    obj.rel12();
    obj._vtable = (int)&DAT_00524950[0];
    obj.rel8();
    return r;
}

void FUN_0036bf10(void)
{
    igMetaObject_RunStaticInit(beActionStarterData_Register);
}

void *beActionStarterData_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beActionStarterData_metaObject,
        igNamedObject_Register,
        igNamedObject_GetPublishedMetaObject,
        beActionStarterData_GetMetaObject,
        beActionStarterData_className,
        0x24, /* instance size */
        beActionStarterData_GetVTable,
        beActionStarterData_InitFields,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void beActionStarterData_GetMetaObject(void)
{
    FUN_0036bdf0();
}

void beActionStarterData_InitFields(void) {
    int temp_s1;
    void *temp_s0;

    temp_s0 = (void *)((int *)DAT_00589e60)[0];
    temp_s1 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &DAT_004c7e20[0], 5);
    igMetaObject_NameFields(temp_s0, &DAT_004c7e40[0], &DAT_004c7e60[0], &DAT_004c7e80[0], temp_s1);
}

