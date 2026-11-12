int FUN_003be8e0(void) {
    if (((int *)DAT_0058b2a8)[0] == 0) {
        ((int *)DAT_0058b2a8)[0] = igMetaObject_Create(Memory_GetAllocatorBySelector(DAT_00587040[0]));
    }
    return ((int *)DAT_0058b2a8)[0];
}

S *beNDMWPanelObjectWaza_ResolveMetaObject(void) {
    S *g = DAT_0058b2a8[0];
    if (g != 0) {
        int b = !!(g->flags & 4);
        if (b) goto done;
    }
    FUN_003bea10();
done:
    return DAT_0058b2a8[0];
}

int beNDMWPanelObjectWaza_GetVTable(void) {
    struct Obj_3be980 obj;
    int t;

    igObject_InitHeader(&obj);
    obj.w9 = 0;
    obj.w11 = 0;
    obj.w12 = 0;
    obj.vt = &DAT_0053e1a0[0];
    obj.w15 = 0;
    obj.w16 = 0;
    t = *(int *)((char *)&obj + *(int *)((char *)(DAT_00586dc8[0]) + 916));
    obj.vt = &DAT_0053e1a0[0];
    ObjectRef_Destruct_00150eb0(&obj.w16, -1);
    FUN_0014aa70(&obj.w15, -1);
    FUN_003be240((Obj_3be240 *)&obj, (short)0);
    return t;
}

void FUN_003bea10(void)
{
    igMetaObject_RunStaticInit(beNDMWPanelObjectWaza_Register);
}

void *beNDMWPanelObjectWaza_Register(void) {
    NdmwLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beNDMWPanelObjectWaza_metaObject,
        beNDMWPanelObject_Register,
        beNDMWPanelObject_GetPublishedMetaObject,
        beNDMWPanelObjectWaza_GetMetaObject,
        beNDMWPanelObjectWaza_className,
        0x44, /* instance size */
        beNDMWPanelObjectWaza_GetVTable,
        beNDMWPanelObjectWaza_InitFields,
        0, /* extra callback item */
        g_beNDMWPanelObjectWaza_callbackList /* callback list */
    );
}

void beNDMWPanelObjectWaza_GetMetaObject(void)
{
    beNDMWPanelObjectWaza_ResolveMetaObject();
}

void beNDMWPanelObjectWaza_InitFields(void) {
    int temp_s2;
    int temp_s3;
    void **temp_v0;
    void *temp_s0;
    void *temp_s0_2;
    void *temp_s1;
    igMetaField *temp_v0_2;

    temp_s1 = (void *)(((void * *)DAT_0058b2a8)[0]);
    temp_s2 = igMetaObject_GetFieldCount(temp_s1);
    igMetaObject_CreateFields(temp_s1, &DAT_004ca5f0[0], 2);
    temp_v0 = (void **)(igMetaObject_FindFieldByName(temp_s1, &DAT_00511df8[0]));
    temp_s3 = ObjectPointerList_FindIndex(((igMetaObject *)temp_s1)->_metaFields, temp_v0);
    temp_v0_2 = (igMetaField *)(((DW4VC_84_1 *)(temp_v0))->vX((int)(1)));
    FUN_002ea4b0(temp_v0_2, 0);
    temp_v0_2->_externalEnumStorage = (int)(&DAT_0058b2b0[0]);
    igMetaObject_FinalizeAndReplaceField(temp_s1, temp_s3, temp_v0_2);
    temp_v0_2->_refCount = temp_v0_2->_refCount - 1;
    if (((unsigned long long)(long long)temp_v0_2->_refCount & 0x7fffffULL) == 0) {
        igObject_Destroy(temp_v0_2);
    }
    temp_s0 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s2));
    ((igObjectRefMetaField *)temp_s0)->_metaObject = igObjectList_GetOrCreateMetaObject();
    ((igObjectRefMetaField *)temp_s0)->_construct = 1;
    temp_s0_2 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s2 + 1));
    ((igObjectRefMetaField *)temp_s0_2)->_metaObject = igIntList_GetOrCreateMetaObject();
    ((igObjectRefMetaField *)temp_s0_2)->_construct = 1;
    igMetaObject_NameFields(temp_s1, &DAT_004ca5f8[0], &DAT_004ca600[0], &DAT_004ca608[0], temp_s2);
}

