void beNDMWLoadIntf2TextOrder_Create(int arg0) {
    FUN_003c7830();
    igMetaObject_CreateInstance(*(int *)0x58BE90, arg0);
}

igMetaObject *FUN_003c7700(void) {
    if (g_beNDMWLoadIntf2TextOrder_metaObject[0] == 0) {
        g_beNDMWLoadIntf2TextOrder_metaObject[0] = igMetaObject_Create(Memory_GetAllocatorBySelector(g_metadataAllocatorKey[0]));
    }
    return g_beNDMWLoadIntf2TextOrder_metaObject[0];
}

void *beNDMWLoadIntf2TextOrder_GetReadyMetaObject(void) {
    igMetaObject *g = g_beNDMWLoadIntf2TextOrder_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false) {
        FUN_003c7830();
    }
    return g_beNDMWLoadIntf2TextOrder_metaObject[0];
}

int beNDMWLoadIntf2TextOrder_GetVTable(void) {
    union U_3c77a0 u;
    int temp_s0;
    char *ps;
    int *temp_v1;
    int *temp_a1;
    int temp_v0;

    igObject_InitHeader(u.b);
    ps = &u.b[8];
    *(int *)ps = 0;
    u.vt = (int)&g_igNamedObject_vtable[0];
    u.vt = (int)&DAT_0053c7b0[0];
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

void FUN_003c7830(void)
{
    igMetaObject_RunStaticInit(beNDMWLoadIntf2TextOrder_Register);
}

void *beNDMWLoadIntf2TextOrder_Register(void) {
    NdmwLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beNDMWLoadIntf2TextOrder_metaObject,
        beBaseInfoData_Register,
        beBaseInfoData_GetPublishedMetaObject,
        beNDMWLoadIntf2TextOrder_GetMetaObject,
        beNDMWLoadIntf2TextOrder_className,
        0x18, /* instance size */
        beNDMWLoadIntf2TextOrder_GetVTable,
        beNDMWLoadIntf2TextOrder_InitFields,
        0, /* extra callback item */
        g_beNDMWLoadIntf2TextOrder_callbackList /* callback list */
    );
}

void beNDMWLoadIntf2TextOrder_GetMetaObject(void)
{
    beNDMWLoadIntf2TextOrder_GetReadyMetaObject();
}

void beNDMWLoadIntf2TextOrder_InitFields(void) {
    int temp_s2;
    int temp_s3;
    void **temp_v0;
    void *temp_s0;
    void *temp_s0_2;
    void *temp_s1;
    igStringMetaField *temp_v0_2;

    temp_s1 = (void *)(((void * *)g_beNDMWLoadIntf2TextOrder_metaObject)[0]);
    temp_s2 = igMetaObject_GetFieldCount(temp_s1);
    igMetaObject_CreateFields(temp_s1, &g_beNDMWLoadIntf2TextOrder_ctorTable[0], 2);
    temp_v0 = (void **)(igMetaObject_FindFieldByName(temp_s1, &text_name_2[0]));
    temp_s3 = ObjectPointerList_FindIndex(((igMetaObject *)temp_s1)->_metaFields, temp_v0);
    temp_v0_2 = (igStringMetaField *)(((DW4VC_84_1 *)(temp_v0))->vX((int)(1)));
    igStringMetaField_SetDefaultText(temp_v0_2, &TEXTORDER_4[0]);
    temp_v0_2->_externalEnumStorage = (int)(&DAT_0058be98[0]);
    igMetaObject_FinalizeAndReplaceField(temp_s1, temp_s3, temp_v0_2);
    temp_v0_2->_refCount = temp_v0_2->_refCount - 1;
    if (((unsigned long long)(long long)temp_v0_2->_refCount & 0x7fffffULL) == 0) {
        igObject_Destroy(temp_v0_2);
    }
    temp_s0 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s2));
    ((igObjectRefMetaField *)temp_s0)->_metaObject = FUN_00357910();
    ((igObjectRefMetaField *)temp_s0)->_refCounted = 0;
    temp_s0_2 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s2 + 1));
    ((igObjectRefMetaField *)temp_s0_2)->_metaObject = FUN_0035b770();
    ((igObjectRefMetaField *)temp_s0_2)->_refCounted = 0;
    igMetaObject_NameFields(temp_s1, &g_beNDMWLoadIntf2TextOrder_fieldTable[0], &DAT_004cbf88[0], &DAT_004cbf90[0], temp_s2);
}

