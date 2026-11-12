void FUN_003b5530(int arg0) {
    FUN_003b5640();
    igMetaObject_CreateInstance(*(int *)0x58ABE8, arg0);
}

G_3b5570 *FUN_003b5570(void) {
    G_3b5570 *g = DAT_0058abe8[0];
    int t;
    if (!g || !(t = (g->f & 4) != 0))
        FUN_003b5640();
    return DAT_0058abe8[0];
}

int beNDMWStatusSelect01_GetVTable(void) {
    union U_3b55c0 u;
    int t;

    igObject_InitHeader(u.b);
    *(int *)&u.b[52] = 0;
    *(int *)&u.b[56] = 0;
    *(int *)&u.b[60] = 0;
    *(int *)&u.b[64] = 0;
    *(int *)&u.b[68] = 0;
    *(int *)&u.b[72] = 0;
    *(int *)&u.b[76] = 0;
    *(int *)&u.b[80] = 0;
    *(int *)&u.b[108] = 0;
    u.vt = (int)&DAT_0053f410[0];
    t = *(int *)&u.b[*(int *)((char *)(DAT_00586dc8[0]) + 916)];
    u.vt = (int)&DAT_0053f410[0];
    FUN_003b4050((struct S_3b4050 *)u.b, (short)0);
    return t;
}

void FUN_003b5640(void)
{
    igMetaObject_RunStaticInit(beNDMWStatusSelect01_Register);
}

void *beNDMWStatusSelect01_Register(void) {
    NdmwLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beNDMWStatusSelect01_metaObject,
        beNDMWWindowSelect_Register,
        beNDMWWindowSelect_GetPublishedMetaObject,
        beNDMWStatusSelect01_GetMetaObject,
        beNDMWStatusSelect01_className,
        0x70, /* instance size */
        beNDMWStatusSelect01_GetVTable,
        0,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void beNDMWStatusSelect01_GetMetaObject(void)
{
    FUN_003b5570();
}

