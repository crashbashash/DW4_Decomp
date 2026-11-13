void beNDMWAfsSetup_CreateInstance(int arg0) {
    FUN_003cb020();
    igMetaObject_CreateInstance(*(int *)0x58C158, arg0);
}

igMetaObject *FUN_003cae40(void) {
    if (g_beNDMWAfsSetup_metaObject[0] == 0) {
        g_beNDMWAfsSetup_metaObject[0] = igMetaObject_Create(Memory_GetAllocatorBySelector(g_metadataAllocatorKey[0]));
    }
    return g_beNDMWAfsSetup_metaObject[0];
}

void *beNDMWAfsSetup_ResolveMetaObject(void) {
    igMetaObject *g = g_beNDMWAfsSetup_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false) {
        FUN_003cb020();
    }
    return g_beNDMWAfsSetup_metaObject[0];
}

int beNDMWAfsSetup_GetVTable(void) {
    struct Obj_3caee0 obj;
    int t;
    igObject_InitHeader(&obj);
    obj.w2 = 0;
    obj.vt = &DAT_0053dfa0[0];
    obj.w4 = 0;
    obj.w5 = 0;
    obj.w6 = 0;
    obj.w7 = 0;
    t = *(int *)((char *)&obj + *(int *)((char *)(g_objectSystem[0]) + 916));
    obj.vt = &DAT_0053dfa0[0];
    FUN_003cafa0((igObject **)&obj.w7, (short)(-1));
    FUN_0025a2b0(&obj.w6, -1);
    FUN_0025a2b0(&obj.w5, -1);
    FUN_001d35d0(&obj.w4, -1);
    FUN_00231030(&obj, 0);
    return t;
}

igObject **FUN_003cafa0(igObject **arg0, short arg1) {
    igObject *temp_a0;

    if (arg0 != 0) {
        temp_a0 = *arg0;
        if (temp_a0 != 0) {
            temp_a0->_refCount = temp_a0->_refCount - 1;
            if ((temp_a0->_refCount & 0x7FFFFF) == 0) {
                igObject_Destroy(temp_a0);
            }
        }
        if (arg1 > 0) {
            FUN_00100610(arg0);
        }
    }
    return arg0;
}

void FUN_003cb020(void)
{
    igMetaObject_RunStaticInit(beNDMWAfsSetup_Register);
}

void *beNDMWAfsSetup_Register(void) {
    NdmwLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beNDMWAfsSetup_metaObject,
        igInfoManager_Register,
        igInfoManager_GetPublishedMetaObject,
        beNDMWAfsSetup_GetMetaObject,
        beNDMWAfsSetup_className,
        0x20, /* instance size */
        beNDMWAfsSetup_GetVTable,
        beNDMWAfsSetup_InitFields,
        0, /* extra callback item */
        g_beNDMWAfsSetup_callbackList /* callback list */
    );
}

void beNDMWAfsSetup_GetMetaObject(void)
{
    beNDMWAfsSetup_ResolveMetaObject();
}

void beNDMWAfsSetup_InitFields(void) {
    int temp_s2;
    void *temp_s1_4;
    void *temp_s1_3;
    void *temp_s1_2;
    void *temp_s1;
    void *temp_s0;

    temp_s0 = (void *)g_beNDMWAfsSetup_metaObject[0];
    temp_s2 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &DAT_004cc640[0], 4);
    temp_s1 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2));
    ((igObjectRefMetaField *)temp_s1)->_metaObject = FUN_002c3440();
    ((igRefMetaField *)temp_s1)->_construct = 1;
    temp_s1_2 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 1));
    ((igObjectRefMetaField *)temp_s1_2)->_metaObject = FUN_00452340();
    temp_s1_3 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 2));
    ((igObjectRefMetaField *)temp_s1_3)->_metaObject = FUN_00452340();
    temp_s1_4 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 3));
    ((igObjectRefMetaField *)temp_s1_4)->_metaObject = FUN_0044ff40();
    igMetaObject_NameFields(temp_s0, &DAT_004cc650[0], &DAT_004cc660[0], &DAT_004cc670[0], temp_s2);
}

