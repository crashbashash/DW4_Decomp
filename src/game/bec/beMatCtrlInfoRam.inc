void *FUN_003597c0(void) {
    bool ok;
    if (g_beMatCtrlInfoRam_metaObject[0] == 0) goto make;
    ok = !!(g_beMatCtrlInfoRam_metaObject[0]->_validity & 4);
    if (ok != false) goto done;
make:
    FUN_00359980();
done:;
    return g_beMatCtrlInfoRam_metaObject[0];
}

int beMatCtrlInfoRam_GetVTable(void) {
    Obj_359810 obj;
    int r;

    igObject_InitHeader(&obj);
    obj.r9 = 0;
    obj.vt = &DAT_00536be0[0];
    obj.r10 = 0;
    r = *(int *)((char *)&obj + *(int *)((char *)(g_objectSystem[0]) + 916));
    obj.vt = &DAT_00536be0[0];
    obj.rel10();
    obj.vt = &DAT_00539e90[0];
    obj.rel9();
    return r;
}

O *FUN_00359900(O *arg0, short arg1) {
    if (arg0) {
        S_temp_a0 *t = arg0->m;
        if (t) { t->f4 -= 1; if ((t->f4 & 0x7fffff) == 0) igObject_Destroy(t); }
        if (arg1 > 0) FUN_00100610(arg0);
    }
    return arg0;
}

void FUN_00359980(void)
{
    igMetaObject_RunStaticInit(beMatCtrlInfoRam_Register);
}

void *beMatCtrlInfoRam_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beMatCtrlInfoRam_metaObject,
        beBaseInfoRam_Register,
        beBaseInfoRam_GetPublishedMetaObject,
        beMatCtrlInfoRam_GetMetaObject,
        beMatCtrlInfoRam_className,
        0x30, /* instance size */
        beMatCtrlInfoRam_GetVTable,
        beMatCtrlInfoRam_InitFields,
        0, /* extra callback item */
        g_beMatCtrlInfoRam_callbackList /* callback list */
    );
}

void beMatCtrlInfoRam_GetMetaObject(void)
{
    FUN_003597c0();
}

void beMatCtrlInfoRam_InitFields(void) {
    int temp_s2;
    void *temp_s1;
    void *temp_s0;

    temp_s0 = (void *)g_beMatCtrlInfoRam_metaObject[0];
    temp_s2 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &DAT_004c6000[0], 1);
    temp_s1 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2));
    ((igObjectRefMetaField *)temp_s1)->_metaObject = (int)FUN_003594c0();
    igMetaObject_NameFields(temp_s0, &DAT_004c6008[0], &DAT_004c6010[0], &DAT_004c6018[0], temp_s2);
}

