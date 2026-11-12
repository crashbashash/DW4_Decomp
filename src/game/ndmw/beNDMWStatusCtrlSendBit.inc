void FUN_003b9560(int arg0) {
    FUN_003b9680();
    igMetaObject_CreateInstance(*(int *)0x58AE88, arg0);
}

void *FUN_003b95a0(void) {
    igMetaObject *g = g_beNDMWStatusCtrlSendBit_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false) {
        FUN_003b9680();
    }
    return g_beNDMWStatusCtrlSendBit_metaObject[0];
}

int beNDMWStatusCtrlSendBit_GetVTable(void) {
    struct F_3b95f0 f;
    int temp_s0;

    igObject_InitHeader(&f);
    f.w[12] = 0;
    f.w[13] = 0;
    f.w[14] = 0;
    f.w[15] = 0;
    f.w[16] = 0;
    f.w[17] = 0;
    f.w[18] = 0;
    f.vt = &DAT_0053ecf0[0];
    f.w[22] = 0;
    temp_s0 = *(int *)((char *)&f + *(int *)((char *)(g_objectSystem[0]) + 916));
    f.vt = &DAT_0053ecf0[0];
    FUN_00150eb0(&f.w[22], -1);
    FUN_003b6430(&f, 0);
    return temp_s0;
}

void FUN_003b9680(void)
{
    igMetaObject_RunStaticInit(beNDMWStatusCtrlSendBit_Register);
}

void *beNDMWStatusCtrlSendBit_Register(void) {
    NdmwLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beNDMWStatusCtrlSendBit_metaObject,
        beNDMWWindowCtrl_Register,
        beNDMWWindowCtrl_GetPublishedMetaObject,
        beNDMWStatusCtrlSendBit_GetMetaObject,
        beNDMWStatusCtrlSendBit_className,
        0x64, /* instance size */
        beNDMWStatusCtrlSendBit_GetVTable,
        beNDMWStatusCtrlSendBit_InitFields,
        0, /* extra callback item */
        g_beNDMWStatusCtrlSendBit_callbackList /* callback list */
    );
}

void beNDMWStatusCtrlSendBit_GetMetaObject(void)
{
    FUN_003b95a0();
}

void beNDMWStatusCtrlSendBit_InitFields(void) {
    int temp_s2;
    void *temp_s1;
    void *temp_s0;

    temp_s0 = (void *)g_beNDMWStatusCtrlSendBit_metaObject[0];
    temp_s2 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &DAT_004c9d50[0], 4);
    temp_s1 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 2));
    ((igObjectRefMetaField *)temp_s1)->_metaObject = igIntList_GetOrCreateMetaObject();
    igMetaObject_NameFields(temp_s0, &DAT_004c9d60[0], &DAT_004c9d70[0], &DAT_004c9d80[0], temp_s2);
}

