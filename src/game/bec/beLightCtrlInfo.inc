void *FUN_0035bd00(void) {
    igMetaObject *g = g_beLightCtrlInfo_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false) {
        FUN_0035be50();
    }
    return g_beLightCtrlInfo_metaObject[0];
}

int beLightCtrlInfo_GetVTable(void) {
    struct W_35bd50 o;
    int r;

    igObject_InitHeader(&o);
    o.f[1] = 0;
    o.f[4] = 0;
    o.f[5] = 0;
    o.vt = DAT_005366e0;
    o.f[6] = 0;
    r = *(int *)((char *)&o + *(int *)(((char * *)g_objectSystem)[0] + 916));
    o.vt = DAT_005366e0;
    FUN_0035bdd0((struct R **)(&o.f[6]), (short)(-1));
    FUN_0033ec80((struct S_33ec80 *)&o, (short)0);
    return r;
}

struct R **FUN_0035bdd0(struct R **arg0, short arg1) {
    struct R *temp_a0;

    if (arg0 != 0) {
        temp_a0 = *arg0;
        if (temp_a0 != 0) {
            temp_a0->rc = temp_a0->rc - 1;
            if ((temp_a0->rc & 0x7FFFFF) == 0) {
                igObject_Destroy(temp_a0);
            }
        }
        if (arg1 > 0) {
            FUN_00100610(arg0);
        }
    }
    return arg0;
}

void FUN_0035be50(void)
{
    igMetaObject_RunStaticInit(beLightCtrlInfo_Register);
}

void *beLightCtrlInfo_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beLightCtrlInfo_metaObject,
        beBaseInfo_Register,
        beBaseInfo_GetPublishedMetaObject,
        beLightCtrlInfo_GetMetaObject,
        beLightCtrlInfo_className,
        0x20, /* instance size */
        beLightCtrlInfo_GetVTable,
        beLightCtrlInfo_InitFields,
        0, /* extra callback item */
        g_beLightCtrlInfo_callbackList /* callback list */
    );
}

void beLightCtrlInfo_GetMetaObject(void)
{
    FUN_0035bd00();
}

void beLightCtrlInfo_InitFields(void) {
    int temp_s2;
    void *temp_s1;
    void *temp_s0;

    temp_s0 = (void *)g_beLightCtrlInfo_metaObject[0];
    temp_s2 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &DAT_004c6350[0], 1);
    temp_s1 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2));
    ((igObjectRefMetaField *)temp_s1)->_metaObject = (int)FUN_0035bb70();
    ((igRefMetaField *)temp_s1)->_construct = 1;
    igMetaObject_NameFields(temp_s0, &DAT_004c6358[0], &DAT_004c6360[0], &DAT_004c6368[0], temp_s2);
}

int FUN_0035bfb0(void) {
    if (DAT_00589248[0] == 0) {
        DAT_00589248[0] = igMetaEnum_Create(&DAT_005016f0[0], &DAT_004c6370[0], &DAT_00589250[0], 1);
    }
    return DAT_00589248[0];
}

