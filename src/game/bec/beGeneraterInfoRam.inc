igMetaObject *FUN_0035f410(void) {
    igMetaObject *g = g_beGeneraterInfoRam_metaObject[0];
    int t;
    if (!g || !(t = (g->_validity & 4) != 0))
        FUN_0035f5d0();
    return g_beGeneraterInfoRam_metaObject[0];
}

int beGeneraterInfoRam_GetVTable(void) {
    Obj_35f460 obj;
    int r;

    igObject_InitHeader(&obj);
    obj.m40 = 0;
    obj.vt = &DAT_00535ff0[0];
    obj.m44 = 0;
    r = *(int *)((char *)&obj + *(int *)((char *)(g_objectSystem[0]) + 916));
    obj.vt = &DAT_00535ff0[0];
    obj.rel44();
    obj.vt = &DAT_00539e90[0];
    obj.rel40();
    return r;
}

void **FUN_0035f550(struct Ref **self, short flag) {
    struct Ref *p;
    if (self != 0) {
        p = *self;
        if (p != 0) {
            p->u.w = p->u.w - 1;
            if (p->u.b.cnt == 0) igObject_Destroy(p);
        }
        if (flag > 0) __dl__FPv(self);
    }
    return (void **)self;
}

void FUN_0035f5d0(void)
{
    igMetaObject_RunStaticInit(beGeneraterInfoRam_Register);
}

void *beGeneraterInfoRam_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beGeneraterInfoRam_metaObject,
        beBaseInfoRam_Register,
        beBaseInfoRam_GetPublishedMetaObject,
        beGeneraterInfoRam_GetMetaObject,
        beGeneraterInfoRam_className,
        0x30, /* instance size */
        beGeneraterInfoRam_GetVTable,
        beGeneraterInfoRam_InitFields,
        0, /* extra callback item */
        g_beGeneraterInfoRam_callbackList /* callback list */
    );
}

void beGeneraterInfoRam_GetMetaObject(void)
{
    FUN_0035f410();
}

void beGeneraterInfoRam_InitFields(void) {
    int temp_s2;
    void *temp_s1;
    void *temp_s0;

    temp_s0 = (void *)g_beGeneraterInfoRam_metaObject[0];
    temp_s2 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &g_beGeneraterInfoRam_ctorTable[0], 1);
    temp_s1 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2));
    ((igObjectRefMetaField *)temp_s1)->_metaObject = (int)FUN_0035f140();
    igMetaObject_NameFields(temp_s0, &g_beGeneraterInfoRam_fieldTable[0], &DAT_004c6970[0], &DAT_004c6978[0], temp_s2);
}

