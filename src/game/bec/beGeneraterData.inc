void *FUN_0035fb60(void) {
    igMetaObject *g = g_beGeneraterData_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false) {
        FUN_0035fd50();
    }
    return g_beGeneraterData_metaObject[0];
}

int beGeneraterData_GetVTable(void) {
    struct Obj_35fbb0 obj;
    int t;

    igObject_InitHeader(&obj);
    obj.w2 = 0;
    obj.vt = &DAT_00535eb0[0];
    obj.w7 = 0;
    obj.w8 = 0;
    obj.w10 = 0;
    obj.w11 = 0;
    obj.w13 = 0;
    obj.w15 = 0;
    obj.w16 = 0;
    t = *(int *)((char *)&obj + *(int *)((char *)(g_objectSystem[0]) + 916));
    obj.vt = &DAT_00535eb0[0];
    FUN_0035fcd0((O *)&obj.w16, (short)(-1));
    StringRef_Destruct_00130720(&obj.w15, -1);
    StringRef_Destruct_00130720(&obj.w13, -1);
    StringRef_Destruct_00130720(&obj.w11, -1);
    StringRef_Destruct_00130720(&obj.w10, -1);
    FUN_001354b0(&obj.w8, -1);
    FUN_001374b0(&obj.w7, -1);
    FUN_00131bc0(&obj, 0);
    return t;
}

O *FUN_0035fcd0(O *arg0, short arg1) {
    if (arg0) {
        S_temp_a0 *t = arg0->m;
        if (t) { t->f4 -= 1; if ((t->f4 & 0x7fffff) == 0) igObject_Destroy(t); }
        if (arg1 > 0) __dl__FPv(arg0);
    }
    return arg0;
}

void FUN_0035fd50(void)
{
    igMetaObject_RunStaticInit(beGeneraterData_Register);
}

void *beGeneraterData_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beGeneraterData_metaObject,
        igNamedObject_Register,
        igNamedObject_GetPublishedMetaObject,
        beGeneraterData_GetMetaObject,
        beGeneraterData_className,
        0x44, /* instance size */
        beGeneraterData_GetVTable,
        beGeneraterData_InitFields,
        0, /* extra callback item */
        g_beGeneraterData_callbackList /* callback list */
    );
}

void beGeneraterData_GetMetaObject(void)
{
    FUN_0035fb60();
}

void beGeneraterData_InitFields(void) {
    int temp_s2;
    void *temp_s1;
    void *temp_s1_2;
    void *temp_s1_3;
    void *temp_s0;

    temp_s0 = (void *)g_beGeneraterData_metaObject[0];
    temp_s2 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &g_beGeneraterData_ctorTable[0], 0xC);
    temp_s1 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 2));
    ((igObjectRefMetaField *)temp_s1)->_metaObject = FUN_0018a0a0();
    ((igRefMetaField *)temp_s1)->_construct = 1;
    temp_s1_2 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 3));
    ((igObjectRefMetaField *)temp_s1_2)->_metaObject = FUN_002c9780();
    ((igRefMetaField *)temp_s1_2)->_construct = 1;
    igStringMetaField_SetDefaultText(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 5), 0);
    igStringMetaField_SetDefaultText(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 0xA), 0);
    temp_s1_3 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 0xB));
    ((igObjectRefMetaField *)temp_s1_3)->_metaObject = (int)FUN_0035ff20();
    ((igRefMetaField *)temp_s1_3)->_construct = 1;
    igMetaObject_NameFields(temp_s0, &g_beGeneraterData_fieldTable[0], &DAT_004c6a20[0], &DAT_004c6a50[0], temp_s2);
}

