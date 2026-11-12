void FUN_00348c70(int arg0) {
    FUN_00348e40();
    igMetaObject_CreateInstance(*(int *)0x588200, arg0);
}

igMetaObject *FUN_00348cb0(void) {
    igMetaObject *g = g_beSvGetFreeSizeApi_metaObject[0];
    int t;
    if (!g || !(t = (g->_validity & 4) != 0))
        FUN_00348e40();
    return g_beSvGetFreeSizeApi_metaObject[0];
}

int beSvGetFreeSizeApi_GetVTable(void) {
    union U_348d00 u;
    int r;
    int *v1;
    int *a1;
    int v0;
    char *p74;
    char *p70;
    char *p78;

    igObject_InitHeader(u.b);
    u.vt = (int)&DAT_0053c070[0];
    p70 = &u.b[48];
    *(int *)p70 = 0;
    p74 = &u.b[52];
    *(int *)p74 = 0;
    p78 = &u.b[56];
    *(int *)p78 = 0;
    u.vt = (int)&DAT_0053bd60[0];
    r = *(int *)&u.b[*(int *)((char *)(g_objectSystem[0]) + 916)];
    u.vt = (int)&DAT_0053c070[0];
    if (p78 != 0) {
        v1 = *(int **)p78;
        if (v1 != 0) {
            v1[1] = v1[1] - 1;
            if ((v1[1] & 0x7FFFFF) == 0) {
                igObject_Destroy(v1);
            }
        }
    }
    if (p74 != 0) {
        v1 = *(int **)p74;
        if (v1 != 0) {
            v1[1] = v1[1] - 1;
            if ((v1[1] & 0x7FFFFF) == 0) {
                igObject_Destroy(v1);
            }
        }
    }
    if (p70 != 0) {
        v1 = *(int **)p70;
        if (v1 != 0) {
            v1[1] = v1[1] - 1;
            if ((v1[1] & 0x7FFFFF) == 0) {
                igObject_Destroy(v1);
            }
        }
    }
    return r;
}

void FUN_00348e40(void)
{
    igMetaObject_RunStaticInit(beSvGetFreeSizeApi_Register);
}

void *beSvGetFreeSizeApi_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beSvGetFreeSizeApi_metaObject,
        beSaveApi_Register,
        beSaveApi_GetPublishedMetaObject,
        beSvGetFreeSizeApi_GetMetaObject,
        beSvGetFreeSizeApi_className,
        0x58, /* instance size */
        beSvGetFreeSizeApi_GetVTable,
        beSvGetFreeSizeApi_InitFields,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void beSvGetFreeSizeApi_GetMetaObject(void)
{
    FUN_00348cb0();
}

void beSvGetFreeSizeApi_InitFields(void) {
    int temp_s1;
    void *temp_s0;

    temp_s0 = (void *)g_beSvGetFreeSizeApi_metaObject[0];
    temp_s1 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &DAT_004c4028[0], 3);
    igMetaObject_NameFields(temp_s0, &DAT_004c4038[0], &DAT_004c4048[0], &DAT_004c4058[0], temp_s1);
}

