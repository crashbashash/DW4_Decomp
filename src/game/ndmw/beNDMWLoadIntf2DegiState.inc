void FUN_003c3e40(int arg0) {
    FUN_003c3f10();
    igMetaObject_CreateInstance(*(int *)0x58B978, arg0);
}

void *beNDMWLoadIntf2DegiState_ResolveMetaObject(void) {
    igMetaObject *g = g_beNDMWLoadIntf2DegiState_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false) {
        FUN_003c3f10();
    }
    return g_beNDMWLoadIntf2DegiState_metaObject[0];
}

int beNDMWLoadIntf2DegiState_GetVTable(void) {
    struct Obj_3c3ed0 o;
    igObject_InitHeader(&o);
    o.vt = &DAT_0053cf90[0];
    return *(int *)((char *)&o + *(int *)((char *)(g_objectSystem[0]) + 916));
}

void FUN_003c3f10(void)
{
    igMetaObject_RunStaticInit(beNDMWLoadIntf2DegiState_Register);
}

void *beNDMWLoadIntf2DegiState_Register(void) {
    NdmwLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beNDMWLoadIntf2DegiState_metaObject,
        igObject_Register,
        igObject_GetMetaObject_ParentAccessor,
        beNDMWLoadIntf2DegiState_GetMetaObject,
        beNDMWLoadIntf2DegiState_className,
        0x44, /* instance size */
        beNDMWLoadIntf2DegiState_GetVTable,
        beNDMWLoadIntf2DegiState_InitFields,
        0, /* extra callback item */
        g_beNDMWLoadIntf2DegiState_callbackList /* callback list */
    );
}

void beNDMWLoadIntf2DegiState_GetMetaObject(void)
{
    beNDMWLoadIntf2DegiState_ResolveMetaObject();
}

void beNDMWLoadIntf2DegiState_InitFields(void) {
    int temp_s2;
    void *temp_s1_4;
    void *temp_s1_3;
    void *temp_s1_2;
    void *temp_s1;
    void *temp_s0;

    temp_s0 = (void *)g_beNDMWLoadIntf2DegiState_metaObject[0];
    temp_s2 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &DAT_004cb4d0[0], 0x10);
    temp_s1 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2));
    ((igObjectRefMetaField *)temp_s1)->_metaObject = (int)FUN_003c6ee0();
    ((igObjectRefMetaField *)temp_s1)->_refCounted = 0;
    temp_s1_2 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 1));
    ((igObjectRefMetaField *)temp_s1_2)->_metaObject = (int)FUN_003c7700();
    ((igObjectRefMetaField *)temp_s1_2)->_refCounted = 0;
    temp_s1_3 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 2));
    ((igObjectRefMetaField *)temp_s1_3)->_metaObject = (int)FUN_003c4c20();
    ((igObjectRefMetaField *)temp_s1_3)->_refCounted = 0;
    temp_s1_4 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 3));
    ((igObjectRefMetaField *)temp_s1_4)->_metaObject = FUN_00357910();
    ((igObjectRefMetaField *)temp_s1_4)->_refCounted = 0;
    igMetaObject_NameFields(temp_s0, &DAT_004cb510[0], &DAT_004cb550[0], &DAT_004cb590[0], temp_s2);
}

