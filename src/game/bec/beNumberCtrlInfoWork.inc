void FUN_0034d2b0(int arg0) {
    FUN_0034d3d0();
    igMetaObject_CreateInstance(*(int *)0x588630, arg0);
}

int FUN_0034d2f0(void) {
    if (((int *)DAT_00588630)[0] == 0) {
        ((int *)DAT_00588630)[0] = igMetaObject_Create(Memory_GetAllocatorBySelector(DAT_00587040[0]));
    }
    return ((int *)DAT_00588630)[0];
}

G_34d340 *FUN_0034d340(void) {
    G_34d340 *g = DAT_00588630[0];
    int t;
    if (!g || !(t = (g->f & 4) != 0))
        FUN_0034d3d0();
    return DAT_00588630[0];
}

int beNumberCtrlInfoWork_GetVTable(void) {
    int obj[8];

    igObject_InitHeader(obj);
    obj[0] = (int)&DAT_00538530[0];
    return *(int *)((char *)obj + *(int *)((char *)DAT_00586dc8[0] + 916));
}

void FUN_0034d3d0(void)
{
    igMetaObject_RunStaticInit(beNumberCtrlInfoWork_Register);
}

void *beNumberCtrlInfoWork_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beNumberCtrlInfoWork_metaObject,
        igObject_Register,
        igObject_GetMetaObject_ParentAccessor,
        beNumberCtrlInfoWork_GetMetaObject,
        beNumberCtrlInfoWork_className,
        0x14, /* instance size */
        beNumberCtrlInfoWork_GetVTable,
        beNumberCtrlInfoWork_InitFields,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void beNumberCtrlInfoWork_GetMetaObject(void)
{
    FUN_0034d340();
}

void beNumberCtrlInfoWork_InitFields(void) {
    int temp_s1;
    void *temp_s0;

    temp_s0 = (void *)((int *)DAT_00588630)[0];
    temp_s1 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &DAT_004c4900[0], 3);
    FUN_002ea4b0(((int)igMetaObject_GetFieldAt(temp_s0, temp_s1)), -1);
    FUN_002ea4b0(((int)igMetaObject_GetFieldAt(temp_s0, temp_s1 + 1)), -1);
    FUN_002ea4b0(((int)igMetaObject_GetFieldAt(temp_s0, temp_s1 + 2)), -1);
    igMetaObject_NameFields(temp_s0, &DAT_004c4910[0], &DAT_004c4920[0], &DAT_004c4930[0], temp_s1);
}

