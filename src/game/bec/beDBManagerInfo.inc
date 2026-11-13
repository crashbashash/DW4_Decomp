igMetaObject *FUN_00365dc0(void)
{
    igMetaObject *g = g_beDBManagerInfo_metaObject[0];
    bool t;
    if (!g || (t = g->_validity & 4) == 0)
        FUN_00365f10();
    return g_beDBManagerInfo_metaObject[0];
}

int beDBManagerInfo_GetVTable(void) {
    struct Obj_365e10 o;
    int r;
    igObject_InitHeader(&o);
    o.f8 = 0;
    o.f20 = 0;
    o.f24 = 0;
    o.vt = &DAT_005350f0[0];
    o.f28 = 0;
    r = *(int *)((char *)&o + *(int *)((char *)(g_objectSystem[0]) + 916));
    o.vt = &DAT_005350f0[0];
    FUN_00365e90((void **)&o.f28, (long long)(-1));
    FUN_0033ec80((struct S_33ec80 *)&o, (short)0);
    return r;
}

void **FUN_00365e90(void **arg0, long long arg1) {
    struct Rc *a;
    if (arg0 != 0) {
        a = (struct Rc *)*arg0;
        if (a != 0) { a->rc = a->rc - 1; if ((a->rc & 0x7FFFFF) == 0) { igObject_Destroy(a); } }
        if ((short)arg1 > 0) {
            __dl__FPv(arg0);
        }
    }
    return arg0;
}

void FUN_00365f10(void)
{
    igMetaObject_RunStaticInit(beDBManagerInfo_Register);
}

void *beDBManagerInfo_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beDBManagerInfo_metaObject,
        beBaseInfo_Register,
        beBaseInfo_GetPublishedMetaObject,
        beDBManagerInfo_GetMetaObject,
        beDBManagerInfo_className,
        0x20, /* instance size */
        beDBManagerInfo_GetVTable,
        beDBManagerInfo_InitFields,
        0, /* extra callback item */
        g_beDBManagerInfo_callbackList /* callback list */
    );
}

void beDBManagerInfo_GetMetaObject(void)
{
    FUN_00365dc0();
}

void beDBManagerInfo_InitFields(void) {
    int temp_s2;
    void *temp_s1;
    void *temp_s0;

    temp_s0 = (void *)g_beDBManagerInfo_metaObject[0];
    temp_s2 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &g_beDBManagerInfo_ctorTable[0], 1);
    temp_s1 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2));
    ((igObjectRefMetaField *)temp_s1)->_metaObject = (int)FUN_003658e0();
    ((igRefMetaField *)temp_s1)->_construct = 1;
    igMetaObject_NameFields(temp_s0, &g_beDBManagerInfo_fieldTable[0], &DAT_004c7338[0], &DAT_004c7340[0], temp_s2);
}

int FUN_00366070(void) {
    if (DAT_00589948[0] == 0) {
        DAT_00589948[0] = igMetaEnum_Create(&text_MsgAction[0], &DAT_004c7348[0], &DAT_00589950[0], 1);
    }
    return DAT_00589948[0];
}

