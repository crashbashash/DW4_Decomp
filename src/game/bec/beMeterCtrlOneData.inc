void *FUN_003572d0(void) {
    igMetaObject *g = g_beMeterCtrlOneData_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false) {
        FUN_00357450();
    }
    return g_beMeterCtrlOneData_metaObject[0];
}

int beMeterCtrlOneData_GetVTable(void) {
    struct Obj_357320 obj;
    int t;

    igObject_InitHeader(&obj);
    obj.w2 = 0;
    obj.vt = &DAT_00536fe0[0];
    obj.w3 = 0;
    obj.w16 = 0;
    obj.w17 = 0;
    t = *(int *)((char *)&obj + *(int *)((char *)(g_objectSystem[0]) + 916));
    obj.vt = &DAT_00536fe0[0];
    FUN_00350b10((void **)&obj.w17, (short)(-1));
    FUN_00350b10((void **)&obj.w16, (short)(-1));
    FUN_003573d0((void **)&obj.w3, (long long)(-1));
    FUN_00131bc0(&obj, 0);
    return t;
}

void **FUN_003573d0(void **arg0, long long arg1) {
    char *o;

    if (arg0 != 0) {
        o = (char *)*arg0;
        if (o != 0) {
            *(int *)(o + 4) = *(int *)(o + 4) - 1;
            if ((*(int *)(o + 4) & 0x7FFFFF) == 0) {
                igObject_Destroy(o);
            }
        }
        if ((short)arg1 > 0) {
            __dl__FPv(arg0);
        }
    }
    return arg0;
}

void FUN_00357450(void)
{
    igMetaObject_RunStaticInit(beMeterCtrlOneData_Register);
}

void *beMeterCtrlOneData_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beMeterCtrlOneData_metaObject,
        igNamedObject_Register,
        igNamedObject_GetPublishedMetaObject,
        beMeterCtrlOneData_GetMetaObject,
        beMeterCtrlOneData_className,
        0x48, /* instance size */
        beMeterCtrlOneData_GetVTable,
        beMeterCtrlOneData_InitFields,
        0, /* extra callback item */
        g_beMeterCtrlOneData_callbackList /* callback list */
    );
}

void beMeterCtrlOneData_GetMetaObject(void)
{
    FUN_003572d0();
}

void beMeterCtrlOneData_InitFields(void) {
    int temp_s2;
    void *temp_s1;
    void *temp_s1_2;
    void *temp_s1_3;
    void *temp_s0;

    temp_s0 = (void *)g_beMeterCtrlOneData_metaObject[0];
    temp_s2 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &g_beMeterCtrlOneData_ctorTable[0], 0xE);
    temp_s1 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2));
    *(int *)((char *)(temp_s1) + 56) = (int)FUN_00356cc0();
    FUN_002e3810(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 4), 0.0f);
    FUN_002e3810(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 5), 0.0f);
    temp_s1_2 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 0xC));
    *(int *)((char *)(temp_s1_2) + 56) = (int)FUN_00365550();
    temp_s1_3 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 0xD));
    *(int *)((char *)(temp_s1_3) + 56) = (int)FUN_00365550();
    igMetaObject_NameFields(temp_s0, &g_beMeterCtrlOneData_fieldTable[0], &DAT_004c5b60[0], &DAT_004c5ba0[0], temp_s2);
}

int FUN_00357600(void) {
    if (DAT_00588f28[0] == 0) {
        DAT_00588f28[0] = igMetaEnum_Create(&text_MsgAction[0], &DAT_004c5be0[0], &DAT_004c5c00[0], 8);
    }
    return DAT_00588f28[0];
}

