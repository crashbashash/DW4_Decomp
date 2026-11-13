void beNDMWLoadIntf2SelSlot_Create(int arg0) {
    FUN_003c2f80();
    igMetaObject_CreateInstance(*(int *)0x58B740, arg0);
}

igMetaObject *beNDMWLoadIntf2SelSlot_ResolveMetaObject(void)
{
    unsigned char ready;
    if (g_beNDMWLoadIntf2SelSlot_metaObject[0] != 0) {
        ready = (g_beNDMWLoadIntf2SelSlot_metaObject[0]->_validity & 4) != 0;
        if (ready != 0) goto done;
    }
    FUN_003c2f80();
done:
    return g_beNDMWLoadIntf2SelSlot_metaObject[0];
}

int beNDMWLoadIntf2SelSlot_GetVTable(void) {
    union U_3c2ef0 u;
    int temp_s0;
    char *ps;
    int *temp_v1;
    int *temp_a1;
    int temp_v0;

    igObject_InitHeader(u.b);
    ps = &u.b[8];
    *(int *)ps = 0;
    u.vt = (int)&g_igNamedObject_vtable[0];
    u.vt = (int)&DAT_0053d180[0];
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

void FUN_003c2f80(void)
{
    igMetaObject_RunStaticInit(beNDMWLoadIntf2SelSlot_Register);
}

void *beNDMWLoadIntf2SelSlot_Register(void) {
    NdmwLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        ((igMetaObject_3c2fa0 * *)g_beNDMWLoadIntf2SelSlot_metaObject),
        beBaseInfoData_Register,
        beBaseInfoData_GetPublishedMetaObject,
        beNDMWLoadIntf2SelSlot_GetMetaObject,
        beNDMWLoadIntf2SelSlot_className,
        0x5c, /* instance size */
        beNDMWLoadIntf2SelSlot_GetVTable,
        beNDMWLoadIntf2SelSlot_InitFields,
        0, /* extra callback item */
        g_beNDMWLoadIntf2SelSlot_callbackList /* callback list */
    );
}

void beNDMWLoadIntf2SelSlot_GetMetaObject(void)
{
    beNDMWLoadIntf2SelSlot_ResolveMetaObject();
}

void beNDMWLoadIntf2SelSlot_InitFields(void) {
    int temp_s2;
    int temp_s3;
    void **temp_v0;
    void *temp_s0;
    void *temp_s0_2;
    void *temp_s0_3;
    void *temp_s0_4;
    void *temp_s0_5;
    void *temp_s1;
    void *temp_v0_2;

    temp_s1 = (void *)(g_beNDMWLoadIntf2SelSlot_metaObject[0]);
    temp_s2 = igMetaObject_GetFieldCount(temp_s1);
    igMetaObject_CreateFields(temp_s1, &g_beNDMWLoadIntf2SelSlot_ctorTable[0], 0x16);
    temp_v0 = (void **)(igMetaObject_FindFieldByName(temp_s1, &text_name_2[0]));
    temp_s3 = ObjectPointerList_FindIndex(((igMetaObject *)temp_s1)->_metaFields, temp_v0);
    temp_v0_2 = (void *)(((DW4VC_84_1 *)(temp_v0))->vX((int)(1)));
    igStringMetaField_SetDefaultText(temp_v0_2, &SELSLOT_3[0]);
    ((igMetaField *)temp_v0_2)->_externalEnumStorage = (int)(&DAT_0058b748[0]);
    igMetaObject_FinalizeAndReplaceField(temp_s1, temp_s3, temp_v0_2);
    ((igMetaField *)temp_v0_2)->_refCount = (int)((int) ((int)((igMetaField *)temp_v0_2)->_refCount - 1));
    if (((unsigned long long) ((long long) (int)((igMetaField *)temp_v0_2)->_refCount << 0x29) >> 0x29) == 0) {
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
    temp_s0_5 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s2 + 4));
    ((igObjectRefMetaField *)temp_s0_5)->_metaObject = (int)FUN_003c4c20();
    ((igObjectRefMetaField *)temp_s0_5)->_refCounted = 0;
    igMetaObject_NameFields(temp_s1, &g_beNDMWLoadIntf2SelSlot_fieldTable[0], &DAT_004cb100[0], &DAT_004cb160[0], temp_s2);
}

