void beNDMWLoadIntf2Diffselect_Create(int arg0) {
    FUN_003c3300();
    igMetaObject_CreateInstance(*(int *)0x58B800, arg0);
}

igMetaObject *beNDMWLoadIntf2Diffselect_ResolveMetaObject(void)
{
    igMetaObject *g = g_beNDMWLoadIntf2Diffselect_metaObject[0];
    bool t;
    if (!g || (t = g->_validity & 4) == 0)
        FUN_003c3300();
    return g_beNDMWLoadIntf2Diffselect_metaObject[0];
}

int beNDMWLoadIntf2Diffselect_GetVTable(void) {
    struct F_3c3270 o;
    int r;
    int *s;
    int *h;
    int c;

    igObject_InitHeader(&o);
    o.vt = g_igNamedObject_vtable;
    o.str = 0;
    o.vt = DAT_0053d120;
    r = *(int *)((char *)&o + *(int *)(((char * *)g_objectSystem)[0] + 916));
    o.vt = g_igNamedObject_vtable;
    if (&o.str != 0) {
        s = o.str;
        if (s != 0) {
            h = s - 2;
            c = s[-1] - 1;
            s[-1] = c;
            if (c == 0) StringChunk_ReleaseHeader(*h, h);
        }
    }
    return r;
}

void FUN_003c3300(void)
{
    igMetaObject_RunStaticInit(beNDMWLoadIntf2Diffselect_Register);
}

void *beNDMWLoadIntf2Diffselect_Register(void) {
    NdmwLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beNDMWLoadIntf2Diffselect_metaObject,
        beBaseInfoData_Register,
        beBaseInfoData_GetPublishedMetaObject,
        beNDMWLoadIntf2Diffselect_GetMetaObject,
        beNDMWLoadIntf2Diffselect_className,
        0x4c, /* instance size */
        beNDMWLoadIntf2Diffselect_GetVTable,
        beNDMWLoadIntf2Diffselect_InitFields,
        0, /* extra callback item */
        g_beNDMWLoadIntf2Diffselect_callbackList /* callback list */
    );
}

void beNDMWLoadIntf2Diffselect_GetMetaObject(void)
{
    beNDMWLoadIntf2Diffselect_ResolveMetaObject();
}

void beNDMWLoadIntf2Diffselect_InitFields(void) {
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

    temp_s1 = (void *)(((void * *)g_beNDMWLoadIntf2Diffselect_metaObject)[0]);
    temp_s2 = igMetaObject_GetFieldCount(temp_s1);
    igMetaObject_CreateFields(temp_s1, &DAT_004cb1e0[0], 0x10);
    temp_v0 = (void **)(igMetaObject_FindFieldByName(temp_s1, &DAT_00510cd8[0]));
    temp_s3 = ObjectPointerList_FindIndex(((igMetaObject *)temp_s1)->_metaFields, temp_v0);
    temp_v0_2 = (void *)(((DW4VC_84_1 *)(temp_v0))->vX((int)(1)));
    igStringMetaField_SetDefaultText(temp_v0_2, &DAT_00512940[0]);
    ((igStringMetaField *)temp_v0_2)->_externalEnumStorage = (int)(&DAT_0058b808[0]);
    igMetaObject_FinalizeAndReplaceField(temp_s1, temp_s3, temp_v0_2);
    ((igStringMetaField *)temp_v0_2)->_refCount = (int)((int) (((igStringMetaField *)temp_v0_2)->_refCount - 1));
    if (((unsigned long long) ((long long) (int) ((igStringMetaField *)temp_v0_2)->_refCount << 0x29) >> 0x29) == 0) {
        igObject_Destroy(temp_v0_2);
    }
    temp_s0 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s2 + 7));
    ((igObjectRefMetaField *)temp_s0)->_metaObject = FUN_0034c8e0();
    ((igObjectRefMetaField *)temp_s0)->_refCounted = 0;
    temp_s0_2 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s2 + 8));
    ((igObjectRefMetaField *)temp_s0_2)->_metaObject = (int)FUN_003c6ee0();
    ((igObjectRefMetaField *)temp_s0_2)->_refCounted = 0;
    temp_s0_3 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s2 + 9));
    ((igObjectRefMetaField *)temp_s0_3)->_metaObject = (int)FUN_003c7700();
    ((igObjectRefMetaField *)temp_s0_3)->_refCounted = 0;
    temp_s0_4 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s2 + 0xA));
    ((igObjectRefMetaField *)temp_s0_4)->_metaObject = (int)FUN_003c4c20();
    ((igObjectRefMetaField *)temp_s0_4)->_refCounted = 0;
    temp_s0_5 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s2 + 0xB));
    ((igObjectRefMetaField *)temp_s0_5)->_metaObject = (int)FUN_003c6b40();
    ((igObjectRefMetaField *)temp_s0_5)->_refCounted = 0;
    igMetaObject_NameFields(temp_s1, &DAT_004cb220[0], &DAT_004cb260[0], &DAT_004cb2a0[0], temp_s2);
}

