void FUN_003c3900(int arg0) {
    FUN_003c3ac0();
    igMetaObject_CreateInstance(*(int *)0x58B958, arg0);
}

igMetaObject *FUN_003c3940(void) {
    if (g_beNDMWLoadIntf2DegiStateCtrl_metaObject[0] == 0) {
        g_beNDMWLoadIntf2DegiStateCtrl_metaObject[0] = igMetaObject_Create(Memory_GetAllocatorBySelector(g_metadataAllocatorKey[0]));
    }
    return g_beNDMWLoadIntf2DegiStateCtrl_metaObject[0];
}

igMetaObject *beNDMWLoadIntf2DegiStateCtrl_ResolveMetaObject(void) {
    igMetaObject *g = g_beNDMWLoadIntf2DegiStateCtrl_metaObject[0];
    if (g != 0) {
        int b = !!(g->_validity & 4);
        if (b) goto done;
    }
    FUN_003c3ac0();
done:
    return g_beNDMWLoadIntf2DegiStateCtrl_metaObject[0];
}

int beNDMWLoadIntf2DegiStateCtrl_GetVTable(void) {
    union U_3c39e0 u;
    int r;
    int *v1;
    int *a1;
    int v0;
    char *p38;
    char *p40;

    igObject_InitHeader(u.b);
    p38 = &u.b[8];
    *(int *)p38 = 0;
    u.vt = (int)&DAT_0053d060[0];
    p40 = &u.b[16];
    *(int *)p40 = 0;
    r = *(int *)&u.b[*(int *)((char *)(g_objectSystem[0]) + 916)];
    u.vt = (int)&DAT_0053d060[0];
    if (p40 != 0) {
        v1 = *(int **)p40;
        if (v1 != 0) {
            v1[1] = v1[1] - 1;
            if ((v1[1] & 0x7FFFFF) == 0) {
                igObject_Destroy(v1);
            }
        }
    }
    u.vt = (int)&g_igNamedObject_vtable[0];
    if (p38 != 0) {
        v1 = *(int **)p38;
        if (v1 != 0) {
            a1 = v1 - 2;
            v0 = v1[-1] - 1;
            v1[-1] = v0;
            if (v0 == 0) {
                StringChunk_ReleaseHeader(*a1, a1);
            }
        }
    }
    return r;
}

void FUN_003c3ac0(void)
{
    igMetaObject_RunStaticInit(beNDMWLoadIntf2DegiStateCtrl_Register);
}

void *beNDMWLoadIntf2DegiStateCtrl_Register(void) {
    NdmwLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beNDMWLoadIntf2DegiStateCtrl_metaObject,
        beBaseInfoData_Register,
        beBaseInfoData_GetPublishedMetaObject,
        beNDMWLoadIntf2DegiStateCtrl_GetMetaObject,
        beNDMWLoadIntf2DegiStateCtrl_className,
        0x14, /* instance size */
        beNDMWLoadIntf2DegiStateCtrl_GetVTable,
        beNDMWLoadIntf2DegiStateCtrl_InitFields,
        0, /* extra callback item */
        g_beNDMWLoadIntf2DegiStateCtrl_callbackList /* callback list */
    );
}

void beNDMWLoadIntf2DegiStateCtrl_GetMetaObject(void)
{
    beNDMWLoadIntf2DegiStateCtrl_ResolveMetaObject();
}

void beNDMWLoadIntf2DegiStateCtrl_InitFields(void) {
    int temp_s2;
    int temp_s3;
    void **temp_v0;
    igObjectRefMetaField *temp_s0;
    igMetaObject *temp_s1;
    igStringMetaField *temp_v0_2;

    temp_s1 = (igMetaObject *)(((void * *)g_beNDMWLoadIntf2DegiStateCtrl_metaObject)[0]);
    temp_s2 = igMetaObject_GetFieldCount(temp_s1);
    igMetaObject_CreateFields(temp_s1, &DAT_004cb488[0], 1);
    temp_v0 = (void **)(igMetaObject_FindFieldByName(temp_s1, &DAT_00510cd8[0]));
    temp_s3 = ObjectPointerList_FindIndex(temp_s1->_metaFields, temp_v0);
    temp_v0_2 = (igStringMetaField *)(((DW4VC_84_1 *)(temp_v0))->vX((int)(1)));
    igStringMetaField_SetDefaultText(temp_v0_2, &DAT_00512a30[0]);
    temp_v0_2->_externalEnumStorage = (int)(&DAT_0058b960[0]);
    igMetaObject_FinalizeAndReplaceField(temp_s1, temp_s3, temp_v0_2);
    temp_v0_2->_refCount = (int)((int) (temp_v0_2->_refCount - 1));
    if (((unsigned long long) ((long long) (int) temp_v0_2->_refCount << 0x29) >> 0x29) == 0) {
        igObject_Destroy(temp_v0_2);
    }
    temp_s0 = (igObjectRefMetaField *)(igMetaObject_GetFieldAt(temp_s1, temp_s2));
    temp_s0->_metaObject = (int)FUN_003c3cb0();
    temp_s0->_construct = 1;
    igMetaObject_NameFields(temp_s1, &DAT_004cb490[0], &DAT_004cb498[0], &DAT_004cb4a0[0], temp_s2);
}

