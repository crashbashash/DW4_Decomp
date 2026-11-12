void FUN_003b3ac0(int arg0) {
    FUN_003b3bd0();
    igMetaObject_CreateInstance(*(int *)0x58AB68, arg0);
}

G_3b3b00 *FUN_003b3b00(void) {
    G_3b3b00 *g = DAT_0058ab68[0];
    int t;
    if (!g || !(t = (g->f & 4) != 0))
        FUN_003b3bd0();
    return DAT_0058ab68[0];
}

int beNDMWStatusTitle01_GetVTable(void) {
    union U_3b3b50 u;
    int t;

    igObject_InitHeader(u.b);
    *(int *)&u.b[52] = 0;
    *(int *)&u.b[56] = 0;
    *(int *)&u.b[60] = 0;
    *(int *)&u.b[64] = 0;
    *(int *)&u.b[68] = 0;
    *(int *)&u.b[72] = 0;
    *(int *)&u.b[76] = 0;
    u.vt = (int)&DAT_0053f6b0[0];
    t = *(int *)&u.b[*(int *)((char *)(DAT_00586dc8[0]) + 916)];
    u.vt = (int)&DAT_0053f6b0[0];
    FUN_003b3030((int **)u.b, (long long)0);
    return t;
}

void FUN_003b3bd0(void)
{
    igMetaObject_RunStaticInit(beNDMWStatusTitle01_Register);
}

void *beNDMWStatusTitle01_Register(void) {
    NdmwLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beNDMWStatusTitle01_metaObject,
        beNDMWWindowTitle_Register,
        beNDMWWindowTitle_GetPublishedMetaObject,
        beNDMWStatusTitle01_GetMetaObject,
        beNDMWStatusTitle01_className,
        0x50, /* instance size */
        beNDMWStatusTitle01_GetVTable,
        0,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void beNDMWStatusTitle01_GetMetaObject(void)
{
    FUN_003b3b00();
}

