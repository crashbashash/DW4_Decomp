void FUN_00348930(int arg0) {
    FUN_00348b00();
    igMetaObject_CreateInstance(*(int *)0x5881F0, arg0);
}

igMetaObject *FUN_00348970(void)
{
    igMetaObject *g = g_beSvStartApi_metaObject[0];
    bool t;
    if (!g || (t = g->_validity & 4) == 0)
        FUN_00348b00();
    return g_beSvStartApi_metaObject[0];
}

int beSvStartApi_GetVTable(void) {
    union U_3489c0 u;
    int r;

    int *v1; int *a1; int v0; int *a0;
    char *pc; char *pb; char *pa;
    igObject_InitHeader(u.b);
    u.vt = (int)&DAT_0053c070[0];
    pa = &u.b[48];
    *(int *)pa = 0;
    pb = &u.b[52];
    *(int *)pb = 0;
    pc = &u.b[56];
    *(int *)pc = 0;
    u.vt = (int)&DAT_0053bcf0[0];
    r = *(int *)&u.b[*(int *)((char *)(g_objectSystem[0]) + 916)];
    u.vt = (int)&DAT_0053c070[0];
    if (pc != 0) {
        a0 = *(int **)pc;
        if (a0 != 0) {
            a0[1] = a0[1] - 1;
            if ((a0[1] & 0x7FFFFF) == 0) {
                igObject_Destroy(a0);
            }
        }
    }
    if (pb != 0) {
        a0 = *(int **)pb;
        if (a0 != 0) {
            a0[1] = a0[1] - 1;
            if ((a0[1] & 0x7FFFFF) == 0) {
                igObject_Destroy(a0);
            }
        }
    }
    if (pa != 0) {
        a0 = *(int **)pa;
        if (a0 != 0) {
            a0[1] = a0[1] - 1;
            if ((a0[1] & 0x7FFFFF) == 0) {
                igObject_Destroy(a0);
            }
        }
    }
    return r;
}

void FUN_00348b00(void)
{
    igMetaObject_RunStaticInit(beSvStartApi_Register);
}

void *beSvStartApi_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beSvStartApi_metaObject,
        beSaveApi_Register,
        beSaveApi_GetPublishedMetaObject,
        beSvStartApi_GetMetaObject,
        beSvStartApi_className,
        0x40, /* instance size */
        beSvStartApi_GetVTable,
        beSvStartApi_InitFields,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void beSvStartApi_GetMetaObject(void)
{
    FUN_00348970();
}

void beSvStartApi_InitFields(void) {
    int temp_s2;
    void *temp_s1;
    void **temp_v0;
    T_348bb0 *temp_v0_2;

    temp_s1 = (void *)(((void * *)g_beSvStartApi_metaObject)[0]);
    temp_v0 = (void **)(igMetaObject_FindFieldByName(temp_s1, &text_orderType[0]));
    temp_s2 = ObjectPointerList_FindIndex(*(int *)((char *)(temp_s1) + 40), temp_v0);
    temp_v0_2 = (T_348bb0 *)(((DW4VC_84_1 *)(temp_v0))->vX((int)(1)));
    FUN_002ea4b0(temp_v0_2, 0xA);
    temp_v0_2->f28 = (int)(&DAT_005881f8[0]);
    igMetaObject_FinalizeAndReplaceField(temp_s1, temp_s2, temp_v0_2);
    temp_v0_2->references = temp_v0_2->references - 1;
    if (((unsigned long long)(long long)temp_v0_2->references & 0x7fffffULL) == 0) {
        igObject_Destroy(temp_v0_2);
    }
}

