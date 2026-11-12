void FUN_00351e20(int arg0) {
    FUN_00351ff0();
    igMetaObject_CreateInstance(*(int *)0x588AA8, arg0);
}

int FUN_00351e60(void) {
    if (((int *)DAT_00588aa8)[0] == 0) {
        ((int *)DAT_00588aa8)[0] = igMetaObject_Create(Memory_GetAllocatorBySelector(DAT_00587040[0]));
    }
    return ((int *)DAT_00588aa8)[0];
}

void *FUN_00351eb0(void) {
    struct G *g = DAT_00588aa8[0];
    if (!g || ((g->f & 4) != 0) == false) {
        FUN_00351ff0();
    }
    return DAT_00588aa8[0];
}

int beModelCtrlInfoRideOn_GetVTable(void) {
    RideOnView info;
    return *(int *)((char *)&info + *(int *)((char *)DAT_00586dc8[0] + 916));
}

void FUN_00351ff0(void)
{
    igMetaObject_RunStaticInit(beModelCtrlInfoRideOn_Register);
}

void *beModelCtrlInfoRideOn_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beModelCtrlInfoRideOn_metaObject,
        igObject_Register,
        igObject_GetMetaObject_ParentAccessor,
        beModelCtrlInfoRideOn_GetMetaObject,
        beModelCtrlInfoRideOn_className,
        0x54, /* instance size */
        beModelCtrlInfoRideOn_GetVTable,
        beModelCtrlInfoRideOn_InitFields,
        0, /* extra callback item */
        g_beModelCtrlInfoRideOn_callbackList /* callback list */
    );
}

void beModelCtrlInfoRideOn_GetMetaObject(void)
{
    FUN_00351eb0();
}

void beModelCtrlInfoRideOn_InitFields(void) {
    int temp_s2;
    void *temp_s1;
    void *temp_s0;

    temp_s0 = (void *)((int *)DAT_00588aa8)[0];
    temp_s2 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &DAT_004c5230[0], 4);
    temp_s1 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 2));
    ((igObjectRefMetaField *)temp_s1)->_metaObject = FUN_0034fd40();
    igMetaObject_NameFields(temp_s0, &DAT_004c5240[0], &DAT_004c5250[0], &DAT_004c5260[0], temp_s2);
}

