void FUN_003b9db0(int arg0) {
    FUN_003b9ed0();
    igMetaObject_CreateInstance(*(int *)0x58AEF8, arg0);
}

G_3b9df0 *FUN_003b9df0(void) {
    G_3b9df0 *g = DAT_0058aef8[0];
    int t;
    if (!g || !(t = (g->f & 4) != 0))
        FUN_003b9ed0();
    return DAT_0058aef8[0];
}

int beNDMWStatusCtrlFlag_GetVTable(void) {
    union U_3b9e40 u;
    int temp_s0;
    char *ps;

    igObject_InitHeader(u.b);
    *(int *)&u.b[52] = 0;
    *(int *)&u.b[56] = 0;
    *(int *)&u.b[60] = 0;
    *(int *)&u.b[64] = 0;
    *(int *)&u.b[68] = 0;
    *(int *)&u.b[72] = 0;
    *(int *)&u.b[76] = 0;
    u.vt = (int)&DAT_0053ee10[0];
    ps = &u.b[84];
    *(int *)ps = 0;
    temp_s0 = *(int *)&u.b[*(int *)((char *)(DAT_00586dc8[0]) + 916)];
    u.vt = (int)&DAT_0053ee10[0];
    ObjectRef_Destruct_00150eb0(ps, -1);
    beNDMWWindowCtrl_Destroy((beNDMWWindowCtrl *)u.b, (long long)0);
    return temp_s0;
}

void FUN_003b9ed0(void)
{
    igMetaObject_RunStaticInit(beNDMWStatusCtrlFlag_Register);
}

void *beNDMWStatusCtrlFlag_Register(void) {
    NdmwLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beNDMWStatusCtrlFlag_metaObject,
        beNDMWWindowCtrl_Register,
        beNDMWWindowCtrl_GetPublishedMetaObject,
        beNDMWStatusCtrlFlag_GetMetaObject,
        beNDMWStatusCtrlFlag_className,
        0x58, /* instance size */
        beNDMWStatusCtrlFlag_GetVTable,
        beNDMWStatusCtrlFlag_InitFields,
        0, /* extra callback item */
        g_beNDMWStatusCtrlFlag_callbackList /* callback list */
    );
}

void beNDMWStatusCtrlFlag_GetMetaObject(void)
{
    FUN_003b9df0();
}

void beNDMWStatusCtrlFlag_InitFields(void) {
    int temp_s2;
    void *temp_s1;
    void *temp_s0;

    temp_s0 = (void *)((int *)DAT_0058aef8)[0];
    temp_s2 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &DAT_004c9e50[0], 1);
    temp_s1 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2));
    ((igObjectRefMetaField *)temp_s1)->_metaObject = igIntList_GetOrCreateMetaObject();
    ((igRefMetaField *)temp_s1)->_construct = 1;
    igMetaObject_NameFields(temp_s0, &DAT_004c9e58[0], &DAT_004c9e60[0], &DAT_004c9e68[0], temp_s2);
}

