void *FUN_0036b360(void) {
    struct G *g = DAT_00589e20[0];
    if (!g || ((g->f & 4) != 0) == false) {
        FUN_0036b4b0();
    }
    return DAT_00589e20[0];
}

int beActionStarterInfo_GetVTable(void) {
    struct Obj_36b3b0 obj;
    int t;

    igObject_InitHeader(&obj);
    obj.f8 = 0;
    obj.f14 = 0;
    obj.f18 = 0;
    obj.vt = &DAT_00534610[0];
    obj.f1c = 0;
    t = *(int *)((char *)&obj + *(int *)((char *)(DAT_00586dc8[0]) + 916));
    obj.vt = &DAT_00534610[0];
    FUN_0036b430((O *)&obj.f1c, (short)(-1));
    FUN_0033ec80((struct S_33ec80 *)&obj, (short)0);
    return t;
}

O *FUN_0036b430(O *arg0, short arg1) {
    if (arg0) {
        S_temp_a0 *t = arg0->m;
        if (t) { t->f4 -= 1; if ((t->f4 & 0x7fffff) == 0) igObject_Destroy(t); }
        if (arg1 > 0) FUN_00100610(arg0);
    }
    return arg0;
}

void FUN_0036b4b0(void)
{
    igMetaObject_RunStaticInit(beActionStarterInfo_Register);
}

void *beActionStarterInfo_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beActionStarterInfo_metaObject,
        beBaseInfo_Register,
        beBaseInfo_GetPublishedMetaObject,
        beActionStarterInfo_GetMetaObject,
        beActionStarterInfo_className,
        0x20, /* instance size */
        beActionStarterInfo_GetVTable,
        beActionStarterInfo_InitFields,
        0, /* extra callback item */
        g_beActionStarterInfo_callbackList /* callback list */
    );
}

void beActionStarterInfo_GetMetaObject(void)
{
    FUN_0036b360();
}

void beActionStarterInfo_InitFields(void) {
    int temp_s2;
    void *temp_s1;
    void *temp_s0;

    temp_s0 = (void *)((int *)DAT_00589e20)[0];
    temp_s2 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &DAT_004c7da8[0], 1);
    temp_s1 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2));
    ((igObjectRefMetaField *)temp_s1)->_metaObject = FUN_0036b600();
    igMetaObject_NameFields(temp_s0, &DAT_004c7db0[0], &DAT_004c7db8[0], &DAT_004c7dc0[0], temp_s2);
}

