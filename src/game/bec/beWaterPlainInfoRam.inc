void *FUN_00340090(void) {
    struct G *g = DAT_00587aa8[0];
    if (!g || ((g->f & 4) != 0) == false) {
        FUN_003402c0();
    }
    return DAT_00587aa8[0];
}

int beWaterPlainInfoRam_GetVTable(void) {
    struct Obj_3400e0 obj;
    int t;

    igObject_InitHeader(&obj);
    obj.w10 = 0;
    obj.vt = &DAT_00539a70[0];
    obj.w21 = 0;
    obj.w22 = 0;
    obj.w23 = 0;
    obj.w38 = 0;
    obj.w44 = 0;
    t = *(int *)((char *)&obj + *(int *)((char *)(DAT_00586dc8[0]) + 916));
    obj.vt = &DAT_00539a70[0];
    FUN_00340240((void **)&obj.w44, (long long)(-1));
    FUN_003401c0((struct Ref **)&obj.w38, (short)(-1));
    ObjectRef_Destruct_00150eb0(&obj.w23, -1);
    FUN_001354b0(&obj.w22, -1);
    FUN_001338d0(&obj.w21, -1);
    FUN_0033e920((S *)&obj, (long long)0);
    return t;
}

void **FUN_003401c0(struct Ref **self, short flag) {
    struct Ref *p;
    if (self != 0) {
        p = *self;
        if (p != 0) {
            p->u.w = p->u.w - 1;
            if (p->u.b.cnt == 0) igObject_Destroy(p);
        }
        if (flag > 0) FUN_00100610(self);
    }
    return (void **)self;
}

void **FUN_00340240(void **arg0, long long arg1) {
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
            FUN_00100610(arg0);
        }
    }
    return arg0;
}

void FUN_003402c0(void)
{
    igMetaObject_RunStaticInit(beWaterPlainInfoRam_Register);
}

void *beWaterPlainInfoRam_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beWaterPlainInfoRam_metaObject,
        beBaseInfoRam_Register,
        beBaseInfoRam_GetPublishedMetaObject,
        beWaterPlainInfoRam_GetMetaObject,
        beWaterPlainInfoRam_className,
        0xb8, /* instance size */
        beWaterPlainInfoRam_GetVTable,
        beWaterPlainInfoRam_InitFields,
        0, /* extra callback item */
        g_beWaterPlainInfoRam_callbackList /* callback list */
    );
}

void beWaterPlainInfoRam_GetMetaObject(void)
{
    FUN_00340090();
}

void beWaterPlainInfoRam_InitFields(void) {
    void *temp_s2;
    void *temp_s2_2;
    void *temp_s2_3;
    void *temp_s2_4;
    void *temp_s2_5;
    void *temp_s1;
    int temp_s0;

    temp_s1 = (void *)((int *)DAT_00587aa8)[0];
    temp_s0 = igMetaObject_GetFieldCount(temp_s1);
    igMetaObject_CreateFields(temp_s1, &DAT_004c30b0[0], 0x1B);
    temp_s2 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s0 + 0xA));
    ((igObjectRefMetaField *)temp_s2)->_metaObject = FUN_0014b980();
    temp_s2_2 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s0 + 0xB));
    ((igObjectRefMetaField *)temp_s2_2)->_metaObject = FUN_002c9780();
    ((igRefMetaField *)temp_s2_2)->_construct = 1;
    temp_s2_3 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s0 + 0xC));
    ((igObjectRefMetaField *)temp_s2_3)->_metaObject = igIntList_GetOrCreateMetaObject();
    ((igRefMetaField *)temp_s2_3)->_construct = 1;
    temp_s2_4 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s0 + 0x15));
    ((igObjectRefMetaField *)temp_s2_4)->_metaObject = FUN_002c95d0();
    ((igRefMetaField *)temp_s2_4)->_construct = 1;
    temp_s2_5 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s0 + 0x1A));
    ((igObjectRefMetaField *)temp_s2_5)->_metaObject = FUN_00340490();
    igMetaObject_NameFields(temp_s1, &DAT_004c3120[0], &DAT_004c3190[0], &DAT_004c3200[0], temp_s0);
}

