igMetaObject *g_beNDMWLoadIntf2MesWin_metaObject;
int g_beNDMWLoadIntf2MesWin_nameExternalEnumStorage;
igMetaField *g_beNDMWLoadIntf2MesWin_messengerMetaField;
igMetaField *g_beNDMWLoadIntf2MesWin_padManagerMetaField;
igMetaField *g_beNDMWLoadIntf2MesWin_textOrderMetaField;
igMetaField *g_beNDMWLoadIntf2MesWin_isWinOpenMetaField;
igMetaField *g_beNDMWLoadIntf2MesWin_isWinCloseMetaField;
igMetaField *g_beNDMWLoadIntf2MesWin_isSelectMetaField;
igMetaField *g_beNDMWLoadIntf2MesWin_isSystemMesMetaField;
igMetaField *g_beNDMWLoadIntf2MesWin_isMesEraseMetaField;
igMetaField *g_beNDMWLoadIntf2MesWin_isMesComMetaField;
igMetaField *g_beNDMWLoadIntf2MesWin_isCtrlMetaField;
igMetaField *g_beNDMWLoadIntf2MesWin_isDispMetaField;
igMetaField *g_beNDMWLoadIntf2MesWin_kindCtrlMetaField;
igMetaField *g_beNDMWLoadIntf2MesWin_statCtrlMetaField;
igMetaField *g_beNDMWLoadIntf2MesWin_ramNoMetaField;
igMetaField *g_beNDMWLoadIntf2MesWin_curPointMetaField;
igMetaField *g_beNDMWLoadIntf2MesWin_mesNoMetaField;
igMetaField *g_beNDMWLoadIntf2MesWin_sysMesNoMetaField;
igMetaField *g_beNDMWLoadIntf2MesWin_sysStatMetaField;

void beNDMWLoadIntf2MesWin_Create(int arg0) {
    beNDMWLoadIntf2MesWin_EnsureRegistered();
    igMetaObject_CreateInstance(g_beNDMWLoadIntf2MesWin_metaObject, arg0);
}

igMetaObject *beNDMWLoadIntf2MesWin_GetOrCreateMetaObject(void) {
    if (g_beNDMWLoadIntf2MesWin_metaObject == 0) {
        g_beNDMWLoadIntf2MesWin_metaObject = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData[0]));
    }
    return g_beNDMWLoadIntf2MesWin_metaObject;
}

void *beNDMWLoadIntf2MesWin_GetReadyMetaObject(void) {
    unsigned char b;
    if (g_beNDMWLoadIntf2MesWin_metaObject != 0) {
        b = (*(int *)((char *)(g_beNDMWLoadIntf2MesWin_metaObject) + 36) & 4) != 0;
        if (b != 0) goto done;
    }
    beNDMWLoadIntf2MesWin_EnsureRegistered();
done:
    return g_beNDMWLoadIntf2MesWin_metaObject;
}

int beNDMWLoadIntf2MesWin_GetVTable(void) {
    union U_3c6be0 u;
    int s0;
    char *ps;
    int *v1;
    int *a1;
    int v0;

    igObject_InitHeader(u.b);
    ps = &u.b[8];
    *(int *)ps = 0;
    u.vt = (int)&g_igNamedObject_vtable[0];
    u.vt = (int)&g_beNDMWLoadIntf2MesWin_vtable[0];
    s0 = *(int *)&u.b[*(int *)((char *)(g_objectSystem[0]) + 916)];
    u.vt = (int)&g_igNamedObject_vtable[0];
    if (ps != 0) {
        v1 = *(int **)ps;
        if (v1 != 0) {
            a1 = v1 - 2;
            v0 = v1[-1] - 1;
            v1[-1] = v0;
            if (v0 == 0) {
                StringChunk_ReleaseHeader(*a1, a1);
            }
        }
    }
    return s0;
}

void beNDMWLoadIntf2MesWin_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(beNDMWLoadIntf2MesWin_Register);
}

static igMetaObjectCallback g_beNDMWLoadIntf2MesWin_callbackList[] = { beMessenger_EnsureRegistered, bePadManager_EnsureRegistered, beNDMWLoadIntf2TextOrder_EnsureRegistered, 0 };

void *beNDMWLoadIntf2MesWin_Register(void) {
    NdmwLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_beNDMWLoadIntf2MesWin_metaObject,
        beBaseInfoData_Register,
        beBaseInfoData_GetPublishedMetaObject,
        beNDMWLoadIntf2MesWin_GetMetaObject,
        "beNDMWLoadIntf2MesWin",
        0x40, /* instance size */
        beNDMWLoadIntf2MesWin_GetVTable,
        beNDMWLoadIntf2MesWin_InitFields,
        0, /* extra callback item */
        g_beNDMWLoadIntf2MesWin_callbackList /* callback list */
    );
}

void beNDMWLoadIntf2MesWin_GetMetaObject(void)
{
    beNDMWLoadIntf2MesWin_GetReadyMetaObject();
}

static FieldFactory g_beNDMWLoadIntf2MesWin_ctorTable[] = {
    igObjectRefMetaField_Create,
    igObjectRefMetaField_Create,
    igObjectRefMetaField_Create,
    igBoolMetaField_Create,
    igBoolMetaField_Create,
    igBoolMetaField_Create,
    igBoolMetaField_Create,
    igBoolMetaField_Create,
    igBoolMetaField_Create,
    igBoolMetaField_Create,
    igBoolMetaField_Create,
    igIntMetaField_Create,
    igIntMetaField_Create,
    igIntMetaField_Create,
    igIntMetaField_Create,
    igIntMetaField_Create,
    igIntMetaField_Create,
    igIntMetaField_Create,
};
static const char *g_beNDMWLoadIntf2MesWin_fieldTable[] = {
    "_messenger",
    "_padManager",
    "_textOrder",
    "_isWinOpen",
    "_isWinClose",
    "_isSelect",
    "_isSystemMes",
    "_isMesErase",
    "_isMesCom",
    "_isCtrl",
    "_isDisp",
    "_kindCtrl",
    "_statCtrl",
    "_ramNo",
    "_curPoint",
    "_mesNo",
    "_sysMesNo",
    "_sysStat",
};
static igMetaField **g_beNDMWLoadIntf2MesWin_fieldHandles[] = {
    &g_beNDMWLoadIntf2MesWin_messengerMetaField,
    &g_beNDMWLoadIntf2MesWin_padManagerMetaField,
    &g_beNDMWLoadIntf2MesWin_textOrderMetaField,
    &g_beNDMWLoadIntf2MesWin_isWinOpenMetaField,
    &g_beNDMWLoadIntf2MesWin_isWinCloseMetaField,
    &g_beNDMWLoadIntf2MesWin_isSelectMetaField,
    &g_beNDMWLoadIntf2MesWin_isSystemMesMetaField,
    &g_beNDMWLoadIntf2MesWin_isMesEraseMetaField,
    &g_beNDMWLoadIntf2MesWin_isMesComMetaField,
    &g_beNDMWLoadIntf2MesWin_isCtrlMetaField,
    &g_beNDMWLoadIntf2MesWin_isDispMetaField,
    &g_beNDMWLoadIntf2MesWin_kindCtrlMetaField,
    &g_beNDMWLoadIntf2MesWin_statCtrlMetaField,
    &g_beNDMWLoadIntf2MesWin_ramNoMetaField,
    &g_beNDMWLoadIntf2MesWin_curPointMetaField,
    &g_beNDMWLoadIntf2MesWin_mesNoMetaField,
    &g_beNDMWLoadIntf2MesWin_sysMesNoMetaField,
    &g_beNDMWLoadIntf2MesWin_sysStatMetaField,
};
static int g_beNDMWLoadIntf2MesWin_fieldOffsets[] = {
    16,
    20,
    24,
    28,
    29,
    30,
    31,
    32,
    33,
    34,
    35,
    36,
    40,
    44,
    48,
    52,
    56,
    60,
};

void beNDMWLoadIntf2MesWin_InitFields(void) {
    int temp_s2;
    int temp_s3;
    void **temp_v0;
    igObjectRefMetaField *temp_s0;
    igObjectRefMetaField *temp_s0_2;
    igObjectRefMetaField *temp_s0_3;
    igMetaObject *temp_s1;
    igStringMetaField *temp_v0_2;

    /* matching construct: variant search - the handle stays a void * (typed igMetaObject * swaps s0/s1) */

    temp_s1 = (igMetaObject *)(g_beNDMWLoadIntf2MesWin_metaObject);
    temp_s2 = igMetaObject_GetFieldCount(temp_s1);
    igMetaObject_CreateFields((igMetaObject *)temp_s1, g_beNDMWLoadIntf2MesWin_ctorTable, 0x12);
    temp_v0 = (void **)(igMetaObject_FindFieldByName(temp_s1, "_name"));
    temp_s3 = ObjectPointerList_FindIndex(temp_s1->_metaFields, temp_v0);
    temp_v0_2 = (igStringMetaField *)(((DW4VC_84_1 *)(temp_v0))->vX((int)(1)));
    igStringMetaField_SetDefaultText(temp_v0_2, "MESWIN");
    temp_v0_2->_externalEnumStorage = (int)(&g_beNDMWLoadIntf2MesWin_nameExternalEnumStorage);
    igMetaObject_FinalizeAndReplaceField(temp_s1, temp_s3, temp_v0_2);
    temp_v0_2->_refCount = temp_v0_2->_refCount - 1;
    if (((unsigned long long)(long long)temp_v0_2->_refCount & 0x7fffffULL) == 0) {
        igObject_Destroy(temp_v0_2);
    }
    temp_s0 = (igObjectRefMetaField *)(igMetaObject_GetFieldAt(temp_s1, temp_s2));
    temp_s0->_metaObject = beMessenger_GetOrCreateMetaObject();
    temp_s0->_refCounted = 0;
    temp_s0_2 = (igObjectRefMetaField *)(igMetaObject_GetFieldAt(temp_s1, temp_s2 + 1));
    temp_s0_2->_metaObject = bePadManager_GetOrCreateMetaObject();
    temp_s0_2->_refCounted = 0;
    temp_s0_3 = (igObjectRefMetaField *)(igMetaObject_GetFieldAt(temp_s1, temp_s2 + 2));
    temp_s0_3->_metaObject = (int)beNDMWLoadIntf2TextOrder_GetOrCreateMetaObject();
    temp_s0_3->_refCounted = 0;
    igMetaObject_NameFields((igMetaObject *)temp_s1, g_beNDMWLoadIntf2MesWin_fieldTable, g_beNDMWLoadIntf2MesWin_fieldHandles, g_beNDMWLoadIntf2MesWin_fieldOffsets, temp_s2);
}

