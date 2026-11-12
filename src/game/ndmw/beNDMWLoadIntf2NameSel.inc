void FUN_003c27c0(int arg0) {
    FUN_003c28e0();
    igMetaObject_CreateInstance(*(int *)0x58B5D8, arg0);
}

void *beNDMWLoadIntf2NameSel_GetReadyMetaObject(void) {
    igMetaObject *g = g_beNDMWLoadIntf2NameSel_metaObject[0];
    bool ready;
    if (g) {
        /* matching construct: the bool compared against false keeps the retail sltu normalisation under the
         * unit profile (exceptions on); `if (ready = ...)` folds it away */
        ready = g->_validity & 4;
        if (ready != false) goto end;
    }
    FUN_003c28e0();
end:
    return g_beNDMWLoadIntf2NameSel_metaObject[0];
}

int beNDMWLoadIntf2NameSel_GetVTable(void) {
    union U_3c2850 u;
    int temp_s0;
    char *ps;
    int *temp_v1;
    int *temp_a1;
    int temp_v0;

    igObject_InitHeader(u.b);
    ps = &u.b[8];
    *(int *)ps = 0;
    u.vt = (int)&g_igNamedObject_vtable[0];
    u.vt = (int)&DAT_0053d240[0];
    temp_s0 = *(int *)&u.b[*(int *)((char *)(g_objectSystem[0]) + 916)];
    u.vt = (int)&g_igNamedObject_vtable[0];
    if (ps != 0) {
        temp_v1 = *(int **)ps;
        if (temp_v1 != 0) {
            temp_a1 = temp_v1 - 2;
            temp_v0 = temp_v1[-1] - 1;
            temp_v1[-1] = temp_v0;
            if (temp_v0 == 0) {
                StringChunk_ReleaseHeader(*temp_a1, temp_a1);
            }
        }
    }
    return temp_s0;
}

void FUN_003c28e0(void)
{
    igMetaObject_RunStaticInit(beNDMWLoadIntf2NameSel_Register);
}

void *beNDMWLoadIntf2NameSel_Register(void) {
    NdmwLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beNDMWLoadIntf2NameSel_metaObject,
        beBaseInfoData_Register,
        beBaseInfoData_GetPublishedMetaObject,
        beNDMWLoadIntf2NameSel_GetMetaObject,
        beNDMWLoadIntf2NameSel_className,
        0x120, /* instance size */
        beNDMWLoadIntf2NameSel_GetVTable,
        beNDMWLoadIntf2NameSel_InitFields,
        0, /* extra callback item */
        g_beNDMWLoadIntf2NameSel_callbackList /* callback list */
    );
}

void beNDMWLoadIntf2NameSel_GetMetaObject(void)
{
    beNDMWLoadIntf2NameSel_GetReadyMetaObject();
}

void beNDMWLoadIntf2NameSel_InitFields(void) {
    int temp_s2;
    int temp_s3;
    void **temp_v0;
    void *temp_s0;
    void *temp_s0_2;
    void *temp_s0_3;
    void *temp_s0_4;
    void *temp_s1;
    igStringMetaField *temp_v0_2;

    temp_s1 = (void *)(((void * *)g_beNDMWLoadIntf2NameSel_metaObject)[0]);
    temp_s2 = igMetaObject_GetFieldCount(temp_s1);
    igMetaObject_CreateFields(temp_s1, &DAT_004cad40[0], 0x19);
    temp_v0 = (void **)(igMetaObject_FindFieldByName(temp_s1, &DAT_00510cd8[0]));
    temp_s3 = ObjectPointerList_FindIndex(((igMetaObject *)temp_s1)->_metaFields, temp_v0);
    temp_v0_2 = (igStringMetaField *)(((DW4VC_84_1 *)(temp_v0))->vX((int)(1)));
    igStringMetaField_SetDefaultText(temp_v0_2, &DAT_00512818[0]);
    temp_v0_2->_externalEnumStorage = (int)(&DAT_0058b5e0[0]);
    igMetaObject_FinalizeAndReplaceField(temp_s1, temp_s3, temp_v0_2);
    temp_v0_2->_refCount = temp_v0_2->_refCount - 1;
    if (((unsigned long long)(long long)temp_v0_2->_refCount & 0x7fffffULL) == 0) {
        igObject_Destroy(temp_v0_2);
    }
    temp_s0 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s2));
    ((igObjectRefMetaField *)temp_s0)->_metaObject = FUN_00357910();
    ((igObjectRefMetaField *)temp_s0)->_refCounted = 0;
    temp_s0_2 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s2 + 1));
    ((igObjectRefMetaField *)temp_s0_2)->_metaObject = FUN_0034c8e0();
    ((igObjectRefMetaField *)temp_s0_2)->_refCounted = 0;
    temp_s0_3 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s2 + 2));
    ((igObjectRefMetaField *)temp_s0_3)->_metaObject = (int)FUN_003c6ee0();
    ((igObjectRefMetaField *)temp_s0_3)->_refCounted = 0;
    temp_s0_4 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s2 + 3));
    ((igObjectRefMetaField *)temp_s0_4)->_metaObject = (int)FUN_003c7700();
    ((igObjectRefMetaField *)temp_s0_4)->_refCounted = 0;
    FUN_002ea4b0(igMetaObject_GetFieldAt(temp_s1, temp_s2 + 0xE), -1);
    igMetaObject_NameFields(temp_s1, &DAT_004cadb0[0], &DAT_004cae20[0], &DAT_004cae90[0], temp_s2);
}

