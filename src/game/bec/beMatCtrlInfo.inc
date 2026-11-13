void *FUN_00359ad0(void) {
    igMetaObject *g = g_beMatCtrlInfo_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false) {
        FUN_00359cd0();
    }
    return g_beMatCtrlInfo_metaObject[0];
}

int beMatCtrlInfo_GetVTable(void) {
    struct Obj_359b20 obj;
    int t;

    igObject_InitHeader(&obj);
    obj.w[1] = 0;
    obj.w[4] = 0;
    obj.w[5] = 0;
    obj.vt = &DAT_00536b70[0];
    obj.w[6] = 0;
    obj.w[7] = 0;
    obj.w[8] = 0;
    t = *(int *)((char *)&obj + *(int *)((char *)(g_objectSystem[0]) + 916));
    obj.vt = &DAT_00536b70[0];
    FUN_00359c50((void **)(&obj.w[8]), (short)(-1));
    FUN_00359bd0((void **)(&obj.w[7]), (long long)(-1));
    FUN_00343260((ObjectRefWord *)(&obj.w[6]), -1);
    FUN_0033ec80((struct S_33ec80 *)((int *)&obj), (short)0);
    return t;
}

void **FUN_00359bd0(void **arg0, long long arg1) {
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

void **FUN_00359c50(void **arg0, short arg1) {
    S_temp_a0_359c50 *temp_a0;

    if (arg0 != 0) {
        temp_a0 = (S_temp_a0_359c50 *)(*arg0);
        if (temp_a0 != 0) {
            temp_a0->f4 = (int)((int) (temp_a0->f4 - 1));
            if ((temp_a0->f4 & 0x7FFFFF) == 0) {
                igObject_Destroy(temp_a0);
            }
        }
        if (arg1 > 0) {
            __dl__FPv(arg0);
        }
    }
    return arg0;
}

void FUN_00359cd0(void)
{
    igMetaObject_RunStaticInit(beMatCtrlInfo_Register);
}

void *beMatCtrlInfo_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beMatCtrlInfo_metaObject,
        beBaseInfo_Register,
        beBaseInfo_GetPublishedMetaObject,
        beMatCtrlInfo_GetMetaObject,
        beMatCtrlInfo_className,
        0x28, /* instance size */
        beMatCtrlInfo_GetVTable,
        beMatCtrlInfo_InitFields,
        0, /* extra callback item */
        g_beMatCtrlInfo_callbackList /* callback list */
    );
}

void beMatCtrlInfo_GetMetaObject(void)
{
    FUN_00359ad0();
}

void beMatCtrlInfo_InitFields(void) {
    int temp_s2;
    void *temp_s1;
    void *temp_s1_2;
    void *temp_s1_3;
    void *temp_s0;

    temp_s0 = (void *)g_beMatCtrlInfo_metaObject[0];
    temp_s2 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &g_beMatCtrlInfo_ctorTable[0], 3);
    temp_s1 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2));
    ((igObjectRefMetaField *)temp_s1)->_metaObject = FUN_00196930();
    temp_s1_2 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 1));
    ((igObjectRefMetaField *)temp_s1_2)->_metaObject = (int)FUN_0035a2a0();
    ((igRefMetaField *)temp_s1_2)->_construct = 1;
    temp_s1_3 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 2));
    ((igObjectRefMetaField *)temp_s1_3)->_metaObject = (int)FUN_00359e60();
    ((igRefMetaField *)temp_s1_3)->_construct = 1;
    igMetaObject_NameFields(temp_s0, &g_beMatCtrlInfo_fieldTable[0], &DAT_004c6050[0], &DAT_004c6060[0], temp_s2);
}

