igMetaObject *igPsx2DisableExt_GetMetaObject(void)
{
    igMetaObject *g = g_igPsx2DisableExt_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_00154040();
    return g_igPsx2DisableExt_metaObject[0];
}

int igPsx2DisableExt_GetVTable(void) {
    union U_153f60 u;
    int r;
    int *v1;
    int *a1;
    int v0;
    char *p38;
    char *p40;
    igObject_InitHeader(u.b);
    u.vt = (int)&DAT_00530a10[0];
    p38 = &u.b[8];
    *(int *)p38 = 0;
    p40 = &u.b[16];
    *(int *)p40 = 0;
    u.vt = (int)&DAT_005257f0[0];
    r = *(int *)&u.b[*(int *)((char *)(g_objectSystem[0]) + 916)];
    u.vt = (int)&DAT_00530a10[0];
    if (p40 != 0) {
        v1 = *(int **)p40;
        if (v1 != 0) {
            v1[1] = v1[1] - 1;
            if ((v1[1] & 0x7FFFFF) == 0) {
                igObject_Destroy(v1);
            }
        }
    }
    if (p38 != 0) {
        v1 = *(int **)p38;
        if (v1 != 0) {
            v1[1] = v1[1] - 1;
            if ((v1[1] & 0x7FFFFF) == 0) {
                igObject_Destroy(v1);
            }
        }
    }
    return r;
}

void FUN_00154040(void)
{
    igMetaObject_RunStaticInit(igPsx2DisableExt_Register);
}

void igPsx2DisableExt_Register(void) {
    FUN_00149bc0();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igPsx2DisableExt_metaObject,
        igDisableExt_Register,
        igDisableExt_GetPublishedMetaObject,
        thunk_igPsx2DisableExt_GetMetaObject,
        igPsx2DisableExt_className,
        0x18, /* instance size */
        igPsx2DisableExt_GetVTable,
        &igPsx2DisableExt_InitFields,
        0, /* extra callback item */
        g_igPsx2DisableExt_callbackList /* callback list */
    );
}

igMetaObject *FUN_001540d0(void) {
    return g_igDisableExt_metaObject[0];
}

void igPsx2DisableExt_InitFields(void) {
    int temp_s2;
    void *temp_s1;
    void *temp_s0;

    temp_s0 = (void *)g_igPsx2DisableExt_metaObject[0];
    temp_s2 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &g_igPsx2DisableExt_ctorTable[0], 1);
    temp_s1 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2));
    ((igObjectRefMetaField *)temp_s1)->_metaObject = (int)FUN_00150770();
    ((igObjectRefMetaField *)temp_s1)->_refCounted = 0;
    igMetaObject_NameFields(temp_s0, &g_igPsx2DisableExt_fieldTable[0], &DAT_0048a0a0[0], &DAT_0048a0a8[0], temp_s2);
}

