void FUN_00363c20(int arg0) {
    FUN_00363d60();
    igMetaObject_CreateInstance(*(int *)0x5897F8, arg0);
}

G_363c60 *FUN_00363c60(void) {
    G_363c60 *g = DAT_005897f8[0];
    int t;
    if (!g || !(t = (g->f & 4) != 0))
        FUN_00363d60();
    return DAT_005897f8[0];
}

int beDemoKeepMes_GetVTable(void) {
    union U u;
    int r;
    int *v1;
    int *a1;
    int v0;

    igObject_InitHeader(u.b);
    u.vt = (int)&DAT_00535610[0];
    *(int *)&u.b[24] = 0;
    *(int *)&u.b[28] = 0;
    *(int *)&u.b[36] = 0;
    *(int *)&u.b[40] = 0;
    r = *(int *)&u.b[*(int *)((char *)(DAT_00586dc8[0]) + 916)];
    u.vt = (int)&DAT_00535610[0];
    StringRef_Destruct_00130720(&u.b[40], -1);
    StringRef_Destruct_00130720(&u.b[36], -1);
    StringRef_Destruct_00130720(&u.b[28], -1);
    StringRef_Destruct_00130720(&u.b[24], -1);
    return r;
}

void FUN_00363d60(void)
{
    igMetaObject_RunStaticInit(beDemoKeepMes_Register);
}

void *beDemoKeepMes_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beDemoKeepMes_metaObject,
        igObject_Register,
        igObject_GetMetaObject_ParentAccessor,
        beDemoKeepMes_GetMetaObject,
        beDemoKeepMes_className,
        0x30, /* instance size */
        beDemoKeepMes_GetVTable,
        beDemoKeepMes_InitFields,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void beDemoKeepMes_GetMetaObject(void)
{
    FUN_00363c60();
}

void beDemoKeepMes_InitFields(void) {
    int temp_s1;
    void *temp_s0;

    temp_s0 = (void *)((int *)DAT_005897f8)[0];
    temp_s1 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &DAT_004c7080[0], 7);
    igMetaObject_NameFields(temp_s0, &DAT_004c70a0[0], &DAT_004c70c0[0], &DAT_004c70e0[0], temp_s1);
}

