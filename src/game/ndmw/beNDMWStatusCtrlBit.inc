void FUN_003b97d0(int arg0) {
    FUN_003b98f0();
    igMetaObject_CreateInstance(*(int *)0x58AEB0, arg0);
}

void *FUN_003b9810(void) {
    igMetaObject *g = g_beNDMWStatusCtrlBit_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false) {
        FUN_003b98f0();
    }
    return g_beNDMWStatusCtrlBit_metaObject[0];
}

int beNDMWStatusCtrlBit_GetVTable(void) {
    struct Obj_3b9860 o;
    int r;
    igObject_InitHeader(&o);
    o.f52 = 0;
    o.f56 = 0;
    o.f60 = 0;
    o.f64 = 0;
    o.f68 = 0;
    o.f72 = 0;
    o.f76 = 0;
    o.vt = &DAT_0053ed50[0];
    o.f84 = 0;
    r = *(int *)((char *)&o + *(int *)((char *)(g_objectSystem[0]) + 916));
    o.vt = &DAT_0053ed50[0];
    ObjectRef_Destruct_00150eb0(&o.f84, -1);
    beNDMWWindowCtrl_Destroy((beNDMWWindowCtrl *)&o, (long long)0);
    return r;
}

void FUN_003b98f0(void)
{
    igMetaObject_RunStaticInit(beNDMWStatusCtrlBit_Register);
}

void *beNDMWStatusCtrlBit_Register(void) {
    NdmwLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beNDMWStatusCtrlBit_metaObject,
        beNDMWWindowCtrl_Register,
        beNDMWWindowCtrl_GetPublishedMetaObject,
        beNDMWStatusCtrlBit_GetMetaObject,
        beNDMWStatusCtrlBit_className,
        0x58, /* instance size */
        beNDMWStatusCtrlBit_GetVTable,
        beNDMWStatusCtrlBit_InitFields,
        0, /* extra callback item */
        g_beNDMWStatusCtrlBit_callbackList /* callback list */
    );
}

void beNDMWStatusCtrlBit_GetMetaObject(void)
{
    FUN_003b9810();
}

void beNDMWStatusCtrlBit_InitFields(void) {
    int temp_s2;
    void *temp_s1;
    void *temp_s0;

    temp_s0 = (void *)g_beNDMWStatusCtrlBit_metaObject[0];
    temp_s2 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &DAT_004c9d98[0], 1);
    temp_s1 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2));
    ((igObjectRefMetaField *)temp_s1)->_metaObject = igIntList_GetOrCreateMetaObject();
    ((igRefMetaField *)temp_s1)->_construct = 1;
    igMetaObject_NameFields(temp_s0, &DAT_004c9da0[0], &DAT_004c9da8[0], &DAT_004c9db0[0], temp_s2);
}

