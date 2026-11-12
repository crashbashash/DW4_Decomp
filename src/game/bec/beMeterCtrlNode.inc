int FUN_00356cc0(void) {
    if (((int *)DAT_00588e78)[0] == 0) {
        ((int *)DAT_00588e78)[0] = igMetaObject_Create(Memory_GetAllocatorBySelector(DAT_00587040[0]));
    }
    return ((int *)DAT_00588e78)[0];
}

void *FUN_00356d10(void) {
    struct G *g = DAT_00588e78[0];
    if (!g || ((g->f & 4) != 0) == false) {
        FUN_00356de0();
    }
    return DAT_00588e78[0];
}

int beMeterCtrlNode_GetVTable(void) {
    struct Obj_356d60 obj;
    int t;

    igObject_InitHeader(&obj);
    obj.w2 = 0;
    obj.w3 = 0;
    obj.w4 = 0;
    obj.w7 = 0;
    obj.vt = &DAT_00537120[0];
    obj.w9 = 0;
    t = *(int *)((char *)&obj + *(int *)((char *)(DAT_00586dc8[0]) + 916));
    obj.vt = &DAT_00537120[0];
    FUN_00195190(&obj.w9, -1);
    FUN_00195a90(&obj, 0);
    return t;
}

void FUN_00356de0(void)
{
    igMetaObject_RunStaticInit(beMeterCtrlNode_Register);
}

void *beMeterCtrlNode_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beMeterCtrlNode_metaObject,
        igGroup_Register,
        igGroup_GetPublishedMetaObject,
        beMeterCtrlNode_GetMetaObject,
        beMeterCtrlNode_className,
        0x34, /* instance size */
        beMeterCtrlNode_GetVTable,
        beMeterCtrlNode_InitFields,
        FUN_00356f40, /* extra callback item */
        g_beMeterCtrlNode_callbackList /* callback list */
    );
}

void beMeterCtrlNode_GetMetaObject(void)
{
    FUN_00356d10();
}

void beMeterCtrlNode_InitFields(void) {
    int temp_s2;
    void *temp_s1;
    void *temp_s0;

    temp_s0 = (void *)((int *)DAT_00588e78)[0];
    temp_s2 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &DAT_004c5a60[0], 3);
    temp_s1 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 1));
    ((igObjectRefMetaField *)temp_s1)->_metaObject = FUN_002ca680();
    ((igRefMetaField *)temp_s1)->_construct = 1;
    igMetaObject_NameFields(temp_s0, &DAT_004c5a70[0], &DAT_004c5a80[0], &DAT_004c5a90[0], temp_s2);
}

void FUN_00356f40(void)
{
    FUN_00390890();
}

