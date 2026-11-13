struct Enum *FightCom_GetMetaEnum(void)
{
    if (!g_FightCom_metaEnum[0])
        g_FightCom_metaEnum[0] = ((struct Enum *)igMetaEnum_Create(FightCom, g_FightCom_commandNames,
                                          g_FightCom_commandIds, 22));
    return g_FightCom_metaEnum[0];
}

struct Enum *GameRamMessage_GetMetaEnum(void)
{
    if (!g_GameRamMessage_metaEnum[0])
        g_GameRamMessage_metaEnum[0] = ((struct Enum *)igMetaEnum_Create(Message, g_GameRamMessage_commandNames,
                                          g_GameRamMessage_commandIds, 22));
    return g_GameRamMessage_metaEnum[0];
}

void beNDMWGameRam_CreateInstance(int arg0) {
    FUN_003c9f70();
    igMetaObject_CreateInstance(*(int *)0x58C0A0, arg0);
}

igMetaObject *FUN_003c9ce0(void) {
    if (g_beNDMWGameRam_metaObject[0] == 0) {
        g_beNDMWGameRam_metaObject[0] = igMetaObject_Create(Memory_GetAllocatorBySelector(g_metadataAllocatorKey[0]));
    }
    return g_beNDMWGameRam_metaObject[0];
}

igMetaObject *beNDMWGameRam_ResolveMetaObject(void) {
    igMetaObject *g = g_beNDMWGameRam_metaObject[0];
    if (g != 0) {
        int b = !!(g->_validity & 4);
        if (b) goto done;
    }
    FUN_003c9f70();
done:
    return g_beNDMWGameRam_metaObject[0];
}

int beNDMWGameRam_GetVTable(void) {
    struct Obj_3c9d80 obj;
    int t;

    igObject_InitHeader(&obj);
    obj.w2 = 0;
    obj.w6 = 0;
    obj.vt = &DAT_0053ea40[0];
    obj.w8 = 0;
    obj.w9 = 0;
    obj.w10 = 0;
    obj.w11 = 0;
    obj.w12 = 0;
    obj.w13 = 0;
    obj.w14 = 0;
    obj.w15 = 0;
    obj.w16 = 0;
    obj.w17 = 0;
    t = *(int *)((char *)&obj + *(int *)((char *)(g_objectSystem[0]) + 916));
    obj.vt = &DAT_0053ea40[0];
    FUN_003c9ef0((void **)&obj.w17, (short)(-1));
    FUN_003ba350((void **)&obj.w16, (short)(-1));
    FUN_00365e90(&obj.w15, -1);
    FUN_00365e90(&obj.w14, -1);
    FUN_00365e90(&obj.w13, -1);
    FUN_00365e90(&obj.w12, -1);
    FUN_00365e90(&obj.w11, -1);
    FUN_00365e90(&obj.w10, -1);
    FUN_00365e90(&obj.w9, -1);
    FUN_00365e90(&obj.w8, -1);
    FUN_0033f5e0(&obj, 0);
    return t;
}

void **FUN_003c9ef0(void **arg0, short arg1) {
    int *r;
    if (arg0 != 0) {
        r = (int *)*arg0;
        if (r != 0) {
            r[1] = r[1] - 1;
            if ((r[1] & 0x7fffff) == 0) {
                igObject_Destroy(r);
            }
        }
        if (arg1 > 0) {
            __dl__FPv(arg0);
        }
    }
    return arg0;
}

void FUN_003c9f70(void)
{
    igMetaObject_RunStaticInit(beNDMWGameRam_Register);
}

void *beNDMWGameRam_Register(void) {
    NdmwLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beNDMWGameRam_metaObject,
        beBaseInfoManager_Register,
        beBaseInfoManager_GetPublishedMetaObject,
        beNDMWGameRam_GetMetaObject,
        beNDMWGameRam_className,
        0x4c, /* instance size */
        beNDMWGameRam_GetVTable,
        beNDMWGameRam_InitFields,
        0, /* extra callback item */
        g_beNDMWGameRam_callbackList /* callback list */
    );
}

void beNDMWGameRam_GetMetaObject(void)
{
    beNDMWGameRam_ResolveMetaObject();
}

void beNDMWGameRam_InitFields(void) {
    void *temp_s2;
    void *temp_s2_10;
    void *temp_s2_2;
    void *temp_s2_3;
    void *temp_s2_4;
    void *temp_s2_5;
    void *temp_s2_6;
    void *temp_s2_7;
    void *temp_s2_8;
    void *temp_s2_9;
    void *temp_s1;
    int temp_s0;

    temp_s1 = (void *)g_beNDMWGameRam_metaObject[0];
    temp_s0 = igMetaObject_GetFieldCount(temp_s1);
    igMetaObject_CreateFields(temp_s1, &g_beNDMWGameRam_ctorTable[0], 0xB);
    temp_s2 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s0));
    ((igObjectRefMetaField *)temp_s2)->_metaObject = FUN_003658e0();
    temp_s2_2 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s0 + 1));
    ((igObjectRefMetaField *)temp_s2_2)->_metaObject = FUN_003658e0();
    temp_s2_3 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s0 + 2));
    ((igObjectRefMetaField *)temp_s2_3)->_metaObject = FUN_003658e0();
    temp_s2_4 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s0 + 3));
    ((igObjectRefMetaField *)temp_s2_4)->_metaObject = FUN_003658e0();
    temp_s2_5 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s0 + 4));
    ((igObjectRefMetaField *)temp_s2_5)->_metaObject = FUN_003658e0();
    temp_s2_6 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s0 + 5));
    ((igObjectRefMetaField *)temp_s2_6)->_metaObject = FUN_003658e0();
    temp_s2_7 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s0 + 6));
    ((igObjectRefMetaField *)temp_s2_7)->_metaObject = FUN_003658e0();
    temp_s2_8 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s0 + 7));
    ((igObjectRefMetaField *)temp_s2_8)->_metaObject = FUN_003658e0();
    temp_s2_9 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s0 + 8));
    ((igObjectRefMetaField *)temp_s2_9)->_metaObject = FUN_00364090();
    temp_s2_10 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s0 + 9));
    ((igObjectRefMetaField *)temp_s2_10)->_metaObject = FUN_00363ec0();
    igMetaObject_NameFields(temp_s1, &g_beNDMWGameRam_fieldTable[0], &DAT_004cc540[0], &DAT_004cc570[0], temp_s0);
}

