void beNDMWLoadSlotPlayer_Create(int arg0) {
    FUN_003c6520();
    igMetaObject_CreateInstance(*(int *)0x58BD00, arg0);
}

igMetaObject *FUN_003c63a0(void) {
    if (g_beNDMWLoadSlotPlayer_metaObject[0] == 0) {
        g_beNDMWLoadSlotPlayer_metaObject[0] = igMetaObject_Create(Memory_GetAllocatorBySelector(g_metadataAllocatorKey[0]));
    }
    return g_beNDMWLoadSlotPlayer_metaObject[0];
}

void *beNDMWLoadSlotPlayer_GetReadyMetaObject(void) {
    igMetaObject *g = g_beNDMWLoadSlotPlayer_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false) {
        FUN_003c6520();
    }
    return g_beNDMWLoadSlotPlayer_metaObject[0];
}

int beNDMWLoadSlotPlayer_GetVTable(void) {
    Obj_3c6440 obj;
    int r;

    igObject_InitHeader(&obj);
    obj.vt = &DAT_0053ca70[0];
    obj.m12 = 0;
    obj.m16 = 0;
    r = *(int *)((char *)&obj + *(int *)((char *)(g_objectSystem[0]) + 916));
    obj.vt = &DAT_0053ca70[0];
    obj.rel16();
    obj.rel12();
    return r;
}

void FUN_003c6520(void)
{
    igMetaObject_RunStaticInit(beNDMWLoadSlotPlayer_Register);
}

void *beNDMWLoadSlotPlayer_Register(void) {
    NdmwLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beNDMWLoadSlotPlayer_metaObject,
        igObject_Register,
        igObject_GetMetaObject_ParentAccessor,
        beNDMWLoadSlotPlayer_GetMetaObject,
        beNDMWLoadSlotPlayer_className,
        0x14, /* instance size */
        beNDMWLoadSlotPlayer_GetVTable,
        beNDMWLoadSlotPlayer_InitFields,
        0, /* extra callback item */
        g_beNDMWLoadSlotPlayer_callbackList /* callback list */
    );
}

void beNDMWLoadSlotPlayer_GetMetaObject(void)
{
    beNDMWLoadSlotPlayer_GetReadyMetaObject();
}

void beNDMWLoadSlotPlayer_InitFields(void) {
    int temp_s2;
    void *temp_s1_2;
    void *temp_s1;
    void *temp_s0;

    temp_s0 = (void *)g_beNDMWLoadSlotPlayer_metaObject[0];
    temp_s2 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &DAT_004cbc30[0], 3);
    temp_s1 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 1));
    ((igObjectRefMetaField *)temp_s1)->_metaObject = (int)FUN_003c66a0();
    ((igRefMetaField *)temp_s1)->_construct = 1;
    temp_s1_2 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 2));
    ((igObjectRefMetaField *)temp_s1_2)->_metaObject = igIntList_GetOrCreateMetaObject();
    ((igRefMetaField *)temp_s1_2)->_construct = 1;
    igMetaObject_NameFields(temp_s0, &DAT_004cbc40[0], &DAT_004cbc50[0], &DAT_004cbc60[0], temp_s2);
}

