void FUN_00352940(int arg0) {
    FUN_00352a10();
    igMetaObject_CreateInstance(*(int *)0x588B48, arg0);
}

G_352980 *FUN_00352980(void) {
    G_352980 *g = DAT_00588b48[0];
    int t;
    if (!g || !(t = (g->f & 4) != 0))
        FUN_00352a10();
    return DAT_00588b48[0];
}

int beModelCtrlMoveObject_GetVTable(void) {
    struct Obj_3529d0 obj;

    igObject_InitHeader(&obj);
    obj.vt = &DAT_00537cf0[0];
    return *(int *)((char *)&obj + *(int *)((char *)(DAT_00586dc8[0]) + 916));
}

void FUN_00352a10(void)
{
    igMetaObject_RunStaticInit(beModelCtrlMoveObject_Register);
}

void *beModelCtrlMoveObject_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beModelCtrlMoveObject_metaObject,
        igObject_Register,
        igObject_GetMetaObject_ParentAccessor,
        beModelCtrlMoveObject_GetMetaObject,
        beModelCtrlMoveObject_className,
        0x2c, /* instance size */
        beModelCtrlMoveObject_GetVTable,
        beModelCtrlMoveObject_InitFields,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void beModelCtrlMoveObject_GetMetaObject(void)
{
    FUN_00352980();
}

void beModelCtrlMoveObject_InitFields(void) {
    int temp_s1;
    void *temp_s0;

    temp_s0 = (void *)((int *)DAT_00588b48)[0];
    temp_s1 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &DAT_004c5390[0], 9);
    FUN_002e3810((void *)(((int)igMetaObject_GetFieldAt(temp_s0, temp_s1 + 1))), 0.0f);
    FUN_002e3810((void *)(((int)igMetaObject_GetFieldAt(temp_s0, temp_s1 + 3))), 0.0f);
    FUN_002e3810((void *)(((int)igMetaObject_GetFieldAt(temp_s0, temp_s1 + 4))), 0.0f);
    FUN_002e3810((void *)(((int)igMetaObject_GetFieldAt(temp_s0, temp_s1 + 5))), 0.0f);
    igMetaObject_NameFields(temp_s0, &DAT_004c53c0[0], &DAT_004c53f0[0], &DAT_004c5420[0], temp_s1);
}

