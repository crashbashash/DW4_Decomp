void beNDMWStatusCtrlEquip_Create(int arg0) {
    FUN_003badf0();
    igMetaObject_CreateInstance(*(int *)0x58AF88, arg0);
}

void *FUN_003bad20(void) {
    igMetaObject *g = g_beNDMWStatusCtrlEquip_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false) {
        FUN_003badf0();
    }
    return g_beNDMWStatusCtrlEquip_metaObject[0];
}

int beNDMWStatusCtrlEquip_GetVTable(void) {
    struct Obj_3bad70 o;
    int r;
    igObject_InitHeader(&o);
    o.f52 = 0;
    o.f56 = 0;
    o.f60 = 0;
    o.f64 = 0;
    o.f68 = 0;
    o.f72 = 0;
    o.f76 = 0;
    o.vt = &DAT_0053f200[0];
    r = *(int *)((char *)&o + *(int *)((char *)(g_objectSystem[0]) + 916));
    o.vt = &DAT_0053f200[0];
    
    beNDMWWindowCtrl_Destroy((beNDMWWindowCtrl *)&o, (long long)0);
    return r;
}

void FUN_003badf0(void)
{
    igMetaObject_RunStaticInit(beNDMWStatusCtrlEquip_Register);
}

void *beNDMWStatusCtrlEquip_Register(void) {
    NdmwLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beNDMWStatusCtrlEquip_metaObject,
        beNDMWWindowCtrl_Register,
        beNDMWWindowCtrl_GetPublishedMetaObject,
        beNDMWStatusCtrlEquip_GetMetaObject,
        beNDMWStatusCtrlEquip_className,
        0x58, /* instance size */
        beNDMWStatusCtrlEquip_GetVTable,
        beNDMWStatusCtrlEquip_InitFields,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void beNDMWStatusCtrlEquip_GetMetaObject(void)
{
    FUN_003bad20();
}

void beNDMWStatusCtrlEquip_InitFields(void) {
    int temp_s1;
    void *temp_s0;

    temp_s0 = (void *)g_beNDMWStatusCtrlEquip_metaObject[0];
    temp_s1 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &DAT_004c9f58[0], 1);
    igMetaObject_NameFields(temp_s0, &DAT_004c9f60[0], &DAT_004c9f68[0], &DAT_004c9f70[0], temp_s1);
}

