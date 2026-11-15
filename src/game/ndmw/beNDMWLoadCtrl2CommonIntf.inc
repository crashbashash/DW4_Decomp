igMetaObject *g_beNDMWLoadCtrl2CommonIntf_metaObject;
int g_beNDMWLoadCtrl2CommonIntf_nameExternalEnumStorage;
igMetaField *g_beNDMWLoadCtrl2CommonIntf_messengerMetaField;
igMetaField *g_beNDMWLoadCtrl2CommonIntf_systemMetaField;
igMetaField *g_beNDMWLoadCtrl2CommonIntf_inforamMetaField;
igMetaField *g_beNDMWLoadCtrl2CommonIntf_insightMetaField;
igMetaField *g_beNDMWLoadCtrl2CommonIntf_slotSaveDataMetaField;
igMetaField *g_beNDMWLoadCtrl2CommonIntf_gameUseDataMetaField;
igMetaField *g_beNDMWLoadCtrl2CommonIntf_flagWorkMetaField;
igMetaField *g_beNDMWLoadCtrl2CommonIntf_nextStatMetaField;
igMetaField *g_beNDMWLoadCtrl2CommonIntf_intfStatMetaField;
igMetaField *g_beNDMWLoadCtrl2CommonIntf_mcUtilCtrlMetaField;
igMetaField *g_beNDMWLoadCtrl2CommonIntf_kindHardMetaField;
igMetaField *g_beNDMWLoadCtrl2CommonIntf_difficultModeMetaField;
igMetaField *g_beNDMWLoadCtrl2CommonIntf_isTitleMetaField;
igMetaField *g_beNDMWLoadCtrl2CommonIntf_utilUsePlNoMetaField;

void beNDMWLoadCtrl2CommonIntf_Create(int arg0) {
    FUN_003c4f00();
    igMetaObject_CreateInstance(g_beNDMWLoadCtrl2CommonIntf_metaObject, arg0);
}

igMetaObject *FUN_003c4c20(void) {
    if (g_beNDMWLoadCtrl2CommonIntf_metaObject == 0) {
        g_beNDMWLoadCtrl2CommonIntf_metaObject = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData[0]));
    }
    return g_beNDMWLoadCtrl2CommonIntf_metaObject;
}

igMetaObject *beNDMWLoadCtrl2CommonIntf_ResolveMetaObject(void)
{
    unsigned char ready;
    if (g_beNDMWLoadCtrl2CommonIntf_metaObject != 0) {
        ready = (g_beNDMWLoadCtrl2CommonIntf_metaObject->_validity & 4) != 0;
        if (ready != 0) goto done;
    }
    FUN_003c4f00();
done:
    return g_beNDMWLoadCtrl2CommonIntf_metaObject;
}

int beNDMWLoadCtrl2CommonIntf_GetVTable(void) {
    struct Obj_3c4cc0 obj;
    int temp_s3;

    igObject_InitHeader(&obj);
    obj.f8 = 0;
    obj.vt = (&DAT_0053ce00[0]);
    obj.f20 = 0;
    obj.f24 = 0;
    obj.f28 = 0;
    obj.f34 = 0;
    temp_s3 = *(int *)((char *)&obj + *(int *)((char *)(g_objectSystem[0]) + 916));
    obj.vt = (&DAT_0053ce00[0]);
    FUN_003b2a10((ObjectRefWord *)&obj.f34, -1);
    FUN_003c4e80((void **)&obj.f28, (short)(-1));
    FUN_003c4e00((void **)&obj.f24, (short)(-1));
    FUN_003c4d80((O *)&obj.f20, (short)(-1));
    FUN_00344030(&obj, 0);
    return temp_s3;
}

O *FUN_003c4d80(O *arg0, short arg1) {
    if (arg0) {
        S_temp_a0 *t = arg0->m;
        if (t) { t->f4 -= 1; if ((t->f4 & 0x7fffff) == 0) igObject_Destroy(t); }
        if (arg1 > 0) __dl__FPv(arg0);
    }
    return arg0;
}

void **FUN_003c4e00(void **arg0, short arg1) {
    S_temp_a0_3c4e00 *temp_a0;

    if (arg0 != 0) {
        temp_a0 = (S_temp_a0_3c4e00 *)(*arg0);
        if (temp_a0 != 0) {
            temp_a0->f4 = (int)((int) (temp_a0->f4 - 1));
            if ((temp_a0->f4 & 0x7FFFFF) == 0) {
                igObject_Destroy(temp_a0);
            }
        }
        if (arg1 > 0) {
            __dl__FPv(arg0);
        }
    }
    return arg0;
}

void **FUN_003c4e80(void **arg0, short arg1) {
    S_temp_a0_3c4e80 *temp_a0;

    if (arg0 != 0) {
        temp_a0 = (S_temp_a0_3c4e80 *)(*arg0);
        if (temp_a0 != 0) {
            temp_a0->f4 = (int)((int) (temp_a0->f4 - 1));
            if ((temp_a0->f4 & 0x7FFFFF) == 0) {
                igObject_Destroy(temp_a0);
            }
        }
        if (arg1 > 0) {
            __dl__FPv(arg0);
        }
    }
    return arg0;
}

void FUN_003c4f00(void)
{
    igMetaObject_RunStaticInit(beNDMWLoadCtrl2CommonIntf_Register);
}

static igMetaObjectCallback g_beNDMWLoadCtrl2CommonIntf_callbackList[] = { FUN_00357d10, FUN_00342f30, FUN_0036a360, FUN_00232de0, FUN_003c62b0, FUN_003c6780, FUN_003c5600, FUN_003c5380, 0 };

void *beNDMWLoadCtrl2CommonIntf_Register(void) {
    NdmwLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_beNDMWLoadCtrl2CommonIntf_metaObject,
        beBaseInfoData_Register,
        beBaseInfoData_GetPublishedMetaObject,
        beNDMWLoadCtrl2CommonIntf_GetMetaObject,
        "beNDMWLoadCtrl2CommonIntf",
        0x48, /* instance size */
        beNDMWLoadCtrl2CommonIntf_GetVTable,
        beNDMWLoadCtrl2CommonIntf_InitFields,
        0, /* extra callback item */
        g_beNDMWLoadCtrl2CommonIntf_callbackList /* callback list */
    );
}

void beNDMWLoadCtrl2CommonIntf_GetMetaObject(void)
{
    beNDMWLoadCtrl2CommonIntf_ResolveMetaObject();
}

static FieldFactory g_beNDMWLoadCtrl2CommonIntf_ctorTable[] = {
    igObjectRefMetaField_Create,
    igObjectRefMetaField_Create,
    igObjectRefMetaField_Create,
    igObjectRefMetaField_Create,
    igObjectRefMetaField_Create,
    igObjectRefMetaField_Create,
    igObjectRefMetaField_Create,
    igIntMetaField_Create,
    igIntMetaField_Create,
    igObjectRefMetaField_Create,
    igIntMetaField_Create,
    igIntMetaField_Create,
    igBoolMetaField_Create,
    igIntMetaField_Create,
};
static const char *g_beNDMWLoadCtrl2CommonIntf_fieldTable[] = {
    "_messenger",
    "_system",
    "_inforam",
    "_insight",
    "_slotSaveData",
    "_gameUseData",
    "_flagWork",
    "_nextStat",
    "_intfStat",
    "_mcUtilCtrl",
    "_kindHard",
    "_difficultMode",
    "_isTitle",
    "_utilUsePlNo",
};
static igMetaField **g_beNDMWLoadCtrl2CommonIntf_fieldHandles[] = {
    &g_beNDMWLoadCtrl2CommonIntf_messengerMetaField,
    &g_beNDMWLoadCtrl2CommonIntf_systemMetaField,
    &g_beNDMWLoadCtrl2CommonIntf_inforamMetaField,
    &g_beNDMWLoadCtrl2CommonIntf_insightMetaField,
    &g_beNDMWLoadCtrl2CommonIntf_slotSaveDataMetaField,
    &g_beNDMWLoadCtrl2CommonIntf_gameUseDataMetaField,
    &g_beNDMWLoadCtrl2CommonIntf_flagWorkMetaField,
    &g_beNDMWLoadCtrl2CommonIntf_nextStatMetaField,
    &g_beNDMWLoadCtrl2CommonIntf_intfStatMetaField,
    &g_beNDMWLoadCtrl2CommonIntf_mcUtilCtrlMetaField,
    &g_beNDMWLoadCtrl2CommonIntf_kindHardMetaField,
    &g_beNDMWLoadCtrl2CommonIntf_difficultModeMetaField,
    &g_beNDMWLoadCtrl2CommonIntf_isTitleMetaField,
    &g_beNDMWLoadCtrl2CommonIntf_utilUsePlNoMetaField,
};
static int g_beNDMWLoadCtrl2CommonIntf_fieldOffsets[] = {
    16,
    20,
    24,
    28,
    32,
    36,
    40,
    44,
    48,
    52,
    56,
    60,
    64,
    68,
};

void beNDMWLoadCtrl2CommonIntf_InitFields(void) {
    void **temp_v0;
    int temp_s3;
    int temp_s2;
    void *temp_s1;
    igStringMetaField *temp_v0_2;

    /* matching construct: variant search - the handle stays a void * (typed igMetaObject * swaps s0/s1) */

    temp_s1 = (void *)(g_beNDMWLoadCtrl2CommonIntf_metaObject);
    temp_s2 = igMetaObject_GetFieldCount(temp_s1);
    igMetaObject_CreateFields((igMetaObject *)temp_s1, g_beNDMWLoadCtrl2CommonIntf_ctorTable, 0xE);
    temp_v0 = (void **)(igMetaObject_FindFieldByName(temp_s1, "_name"));
    temp_s3 = ObjectPointerList_FindIndex(((igMetaObject *)temp_s1)->_metaFields, temp_v0);
    temp_v0_2 = (igStringMetaField *)(((DW4VC_84_1 *)(temp_v0))->vX((int)(1)));
    igStringMetaField_SetDefaultText(temp_v0_2, "COMMONINTF");
    temp_v0_2->_externalEnumStorage = (int)(&g_beNDMWLoadCtrl2CommonIntf_nameExternalEnumStorage);
    igMetaObject_FinalizeAndReplaceField(temp_s1, temp_s3, temp_v0_2);
    temp_v0_2->_refCount = temp_v0_2->_refCount - 1;
    if (((unsigned long long)(long long)temp_v0_2->_refCount & 0x7fffffULL) == 0) {
        igObject_Destroy(temp_v0_2);
    }
    void *temp_s0 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s2));
    ((igObjectRefMetaField *)temp_s0)->_metaObject = FUN_00357910();
    ((igObjectRefMetaField *)temp_s0)->_refCounted = 0;
    void *temp_s0_2 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s2 + 1));
    ((igObjectRefMetaField *)temp_s0_2)->_metaObject = FUN_00342ce0();
    ((igObjectRefMetaField *)temp_s0_2)->_refCounted = 0;
    void *temp_s0_3 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s2 + 2));
    ((igObjectRefMetaField *)temp_s0_3)->_metaObject = FUN_0036a230();
    ((igObjectRefMetaField *)temp_s0_3)->_refCounted = 0;
    void *temp_s0_4 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s2 + 3));
    ((igObjectRefMetaField *)temp_s0_4)->_metaObject = FUN_00232840();
    ((igObjectRefMetaField *)temp_s0_4)->_refCounted = 0;
    void *temp_s0_5 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s2 + 4));
    ((igObjectRefMetaField *)temp_s0_5)->_metaObject = (int)FUN_003c61d0();
    ((igRefMetaField *)temp_s0_5)->_construct = 1;
    void *temp_s0_6 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s2 + 5));
    ((igObjectRefMetaField *)temp_s0_6)->_metaObject = (int)FUN_003c66a0();
    ((igRefMetaField *)temp_s0_6)->_construct = 1;
    void *temp_s0_7 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s2 + 6));
    ((igObjectRefMetaField *)temp_s0_7)->_metaObject = (int)FUN_003c5520();
    ((igRefMetaField *)temp_s0_7)->_construct = 1;
    void *temp_s0_8 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s2 + 9));
    ((igObjectRefMetaField *)temp_s0_8)->_metaObject = (int)FUN_003c5200();
    ((igRefMetaField *)temp_s0_8)->_construct = 1;
    igMetaObject_NameFields((igMetaObject *)temp_s1, g_beNDMWLoadCtrl2CommonIntf_fieldTable, g_beNDMWLoadCtrl2CommonIntf_fieldHandles, g_beNDMWLoadCtrl2CommonIntf_fieldOffsets, temp_s2);
}

