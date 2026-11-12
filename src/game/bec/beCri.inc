void FUN_00367860(int arg0) {
    FUN_00367b20();
    igMetaObject_CreateInstance(*(int *)0x589AD8, arg0);
}

igMetaObject *FUN_003678a0(void) {
    if (g_beCri_metaObject[0] == 0) {
        g_beCri_metaObject[0] = igMetaObject_Create(Memory_GetAllocatorBySelector(g_metadataAllocatorKey[0]));
    }
    return g_beCri_metaObject[0];
}

void *FUN_003678f0(void) {
    igMetaObject *g = g_beCri_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false) {
        FUN_00367b20();
    }
    return g_beCri_metaObject[0];
}

int beCri_GetVTable(void) {
    struct Obj_367940 obj;
    int r;

    igObject_InitHeader(&obj);
    obj.w[1] = 0;
    obj.vt = &DAT_0053a3e0[0];
    obj.w[7] = 0;
    obj.w[8] = 0;
    obj.w[9] = 0;
    obj.w[10] = 0;
    obj.w[11] = 0;
    r = *(int *)((char *)&obj + *(int *)((char *)(g_objectSystem[0]) + 916));
    obj.vt = &DAT_0053a3e0[0];
    FUN_0014aa70(&obj.w[11], -1);
    FUN_001d35d0(&obj.w[10], -1);
    FUN_00367aa0((struct Ref **)(&obj.w[9]), (short)(-1));
    FUN_00367a20((void **)(&obj.w[8]), (short)(-1));
    FUN_00367a20((void **)(&obj.w[7]), (short)(-1));
    FUN_00231030(&obj, 0);
    return r;
}

void **FUN_00367a20(void **arg0, short arg1) {
    int *o;

    if (arg0 != 0) {
        o = (int *)*arg0;
        if (o != 0) {
            o[1] = o[1] - 1;
            if ((o[1] & 0x7FFFFF) == 0) {
                igObject_Destroy(o);
            }
        }
        if (arg1 > 0) {
            FUN_00100610(arg0);
        }
    }
    return arg0;
}

void **FUN_00367aa0(struct Ref **self, short flag) {
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

void FUN_00367b20(void)
{
    igMetaObject_RunStaticInit(beCri_Register);
}

void *beCri_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beCri_metaObject,
        igInfoManager_Register,
        igInfoManager_GetPublishedMetaObject,
        beCri_GetMetaObject,
        beCri_className,
        0x48, /* instance size */
        beCri_GetVTable,
        beCri_InitFields,
        0, /* extra callback item */
        g_beCri_callbackList /* callback list */
    );
}

void beCri_GetMetaObject(void)
{
    FUN_003678f0();
}

void beCri_InitFields(void) {
    void *temp_s2;
    void *temp_s2_2;
    void *temp_s2_3;
    void *temp_s2_4;
    void *temp_s2_5;
    void *temp_s2_6;
    void *temp_s1;
    int temp_s0;

    temp_s1 = (void *)g_beCri_metaObject[0];
    temp_s0 = igMetaObject_GetFieldCount(temp_s1);
    igMetaObject_CreateFields(temp_s1, &DAT_004c7660[0], 0xC);
    temp_s2 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s0));
    ((igObjectRefMetaField *)temp_s2)->_metaObject = (int)FUN_00342ce0();
    ((igObjectRefMetaField *)temp_s2)->_refCounted = 0;
    temp_s2_2 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s0 + 3));
    ((igObjectRefMetaField *)temp_s2_2)->_metaObject = (int)FUN_00366950();
    temp_s2_3 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s0 + 4));
    ((igObjectRefMetaField *)temp_s2_3)->_metaObject = (int)FUN_00366950();
    temp_s2_4 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s0 + 5));
    ((igObjectRefMetaField *)temp_s2_4)->_metaObject = (int)FUN_00366780();
    ((igRefMetaField *)temp_s2_4)->_construct = 1;
    temp_s2_5 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s0 + 6));
    ((igObjectRefMetaField *)temp_s2_5)->_metaObject = FUN_002c3440();
    ((igRefMetaField *)temp_s2_5)->_construct = 1;
    temp_s2_6 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s0 + 7));
    ((igObjectRefMetaField *)temp_s2_6)->_metaObject = igObjectList_GetOrCreateMetaObject();
    ((igRefMetaField *)temp_s2_6)->_construct = 1;
    igMetaObject_NameFields(temp_s1, &DAT_004c7690[0], &DAT_004c76c0[0], &DAT_004c76f0[0], temp_s0);
}

