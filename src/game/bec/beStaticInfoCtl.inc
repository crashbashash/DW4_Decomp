void beStaticInfoCtl_CreateInstance(int arg0) {
    FUN_003438b0();
    igMetaObject_CreateInstance(*(int *)0x587E10, arg0);
}

igMetaObject *FUN_003437a0(void) {
    if (g_beStaticInfoCtl_metaObject[0] == 0) {
        g_beStaticInfoCtl_metaObject[0] = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData[0]));
    }
    return g_beStaticInfoCtl_metaObject[0];
}

void *FUN_003437f0(void) {
    igMetaObject *g = g_beStaticInfoCtl_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false) {
        FUN_003438b0();
    }
    return g_beStaticInfoCtl_metaObject[0];
}

int beStaticInfoCtl_GetVTable(void) {
    struct Obj_343840 obj;
    int t;

    igObject_InitHeader(&obj);
    obj.w2 = 0;
    obj.w6 = 0;
    obj.vt = &DAT_0053b9b0[0];
    obj.w8 = 0;
    t = *(int *)((char *)&obj + *(int *)((char *)(g_objectSystem[0]) + 916));
    obj.vt = &DAT_0053b9b0[0];
    FUN_0033f560((void **)&obj.w8, -1);
    FUN_0033f5e0((O_33f5e0 *)&obj, (short)0);
    return t;
}

void FUN_003438b0(void)
{
    igMetaObject_RunStaticInit(beStaticInfoCtl_Register);
}

void *beStaticInfoCtl_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beStaticInfoCtl_metaObject,
        beBaseInfoManager_Register,
        beBaseInfoManager_GetPublishedMetaObject,
        beStaticInfoCtl_GetMetaObject,
        beStaticInfoCtl_className,
        0x24, /* instance size */
        beStaticInfoCtl_GetVTable,
        beStaticInfoCtl_InitFields,
        0, /* extra callback item */
        g_beStaticInfoCtl_callbackList /* callback list */
    );
}

void beStaticInfoCtl_GetMetaObject(void)
{
    FUN_003437f0();
}

void beStaticInfoCtl_InitFields(void) {
    int temp_s2;
    void *temp_s1;
    void *temp_s0;

    temp_s0 = (void *)g_beStaticInfoCtl_metaObject[0];
    temp_s2 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &g_beStaticInfoCtl_ctorTable[0], 1);
    temp_s1 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2));
    ((igObjectRefMetaField *)temp_s1)->_metaObject = (int)FUN_0036aaf0();
    ((igRefMetaField *)temp_s1)->_construct = 1;
    igMetaObject_NameFields(temp_s0, &g_beStaticInfoCtl_fieldTable[0], &DAT_004c37b0[0], &DAT_004c37b8[0], temp_s2);
}

