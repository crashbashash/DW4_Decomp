igMetaObject *FUN_00343f50(void) {
    igMetaObject *g = g_beSoundData_metaObject[0];
    int t;
    if (!g || !(t = (g->_validity & 4) != 0))
        FUN_003440d0();
    return g_beSoundData_metaObject[0];
}

int beSoundData_GetVTable(void) {
    union U_343fa0 u;
    int temp_s0;
    char *q1;
    int *tv1, *ta1;
    int tc1;

    igObject_InitHeader(u.b);
    u.w[0] = (int)(&g_igNamedObject_vtable[0]);
    q1 = &u.b[8];
    *(int *)q1 = 0;
    u.w[0] = (int)(&DAT_005392f0[0]);
    temp_s0 = *(int *)&u.b[*(int *)((char *)(g_objectSystem[0]) + 916)];
    u.w[0] = (int)(&g_igNamedObject_vtable[0]);
    if (q1 != 0) {
        tv1 = *(int **)q1;
        if (tv1 != 0) {
            ta1 = tv1 - 2;
            tc1 = tv1[-1] - 1;
            tv1[-1] = tc1;
            if (tc1 == 0) {
                StringChunk_ReleaseHeader(*ta1, ta1);
            }
        }
    }
    return temp_s0;
}

struct W_344030 *FUN_00344030(struct W_344030 *arg0, short arg1) {
    int *temp_a1;
    int temp_v0;
    int *temp_v1;

    if (arg0 != 0) {
        arg0->vt = &DAT_00539350[0];
        if (arg0 != 0) {
            arg0->vt = &g_igNamedObject_vtable[0];
            if (&arg0->name != 0) {
                temp_v1 = arg0->name;
                if (temp_v1 != 0) {
                    temp_a1 = temp_v1 - 2;
                    temp_v0 = temp_v1[-1] - 1;
                    temp_v1[-1] = temp_v0;
                    if (temp_v0 == 0) {
                        StringChunk_ReleaseHeader(*temp_a1, temp_a1);
                    }
                }
            }
        }
        if (arg1 > 0) {
            thunk_Memory_FreeBuffer(arg0);
        }
    }
    return arg0;
}

void FUN_003440d0(void)
{
    igMetaObject_RunStaticInit(beSoundData_Register);
}

void *beSoundData_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beSoundData_metaObject,
        beBaseInfoData_Register,
        beBaseInfoData_GetPublishedMetaObject,
        beSoundData_GetMetaObject,
        beSoundData_className,
        0x20, /* instance size */
        beSoundData_GetVTable,
        beSoundData_InitFields,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void beSoundData_GetMetaObject(void)
{
    FUN_00343f50();
}

void beSoundData_InitFields(void) {
    int temp_s1;
    void *temp_s0;

    temp_s0 = (void *)g_beSoundData_metaObject[0];
    temp_s1 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &g_beSoundData_ctorTable[0], 6);
    igShortMetaField_SetDefault(((int)igMetaObject_GetFieldAt(temp_s0, temp_s1)), -1);
    igShortMetaField_SetDefault(((int)igMetaObject_GetFieldAt(temp_s0, temp_s1 + 1)), -1);
    igIntMetaField_SetDefault(((int)igMetaObject_GetFieldAt(temp_s0, temp_s1 + 2)), -1);
    igShortMetaField_SetDefault(((int)igMetaObject_GetFieldAt(temp_s0, temp_s1 + 3)), 1);
    igMetaObject_NameFields(temp_s0, &g_beSoundData_fieldTable[0], &DAT_004c3870[0], &DAT_004c3890[0], temp_s1);
}

int beSound_GetMessageEnum(void) {
    if (DAT_00587ea0[0] == 0) {
        DAT_00587ea0[0] = igMetaEnum_Create(&text_Message[0], &DAT_004c38b0[0], &DAT_004c3910[0], 0x17);
    }
    return DAT_00587ea0[0];
}

