void FUN_003bbda0(int arg0) {
    FUN_003bbf60();
    igMetaObject_CreateInstance(*(int *)0x58B060, arg0);
}

igMetaObject *FUN_003bbde0(void) {
    if (g_beNDMWStageCtl_metaObject[0] == 0) {
        g_beNDMWStageCtl_metaObject[0] = igMetaObject_Create(Memory_GetAllocatorBySelector(g_metadataAllocatorKey[0]));
    }
    return g_beNDMWStageCtl_metaObject[0];
}

igMetaObject *FUN_003bbe30(void) {
    igMetaObject *g = g_beNDMWStageCtl_metaObject[0];
    int t;
    if (!g || !(t = (g->_validity & 4) != 0))
        FUN_003bbf60();
    return g_beNDMWStageCtl_metaObject[0];
}

int beNDMWStageCtl_GetVTable(void) {
    struct F_3bbe80 o;
    int r;
    int *s;
    int *h;
    int c;
    struct T_3bbe80 *a;

    igObject_InitHeader(&o);
    o.vt = DAT_0053a0d0;
    o.str = 0;
    o.ref = 0;
    o.vt = DAT_0053dea0;
    r = *(int *)((char *)&o + *(int *)(((char * *)g_objectSystem)[0] + 916));
    o.vt = DAT_0053a0d0;
    if (&o.ref != 0) {
        a = o.ref;
        if (a != 0) {
            a->references = a->references - 1;
            if ((((unsigned long long)((long long)a->references << 0x29)) >> 0x29) == 0) igObject_Destroy(a);
        }
    }
    o.vt = DAT_00524950;
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

void FUN_003bbf60(void)
{
    igMetaObject_RunStaticInit(beNDMWStageCtl_Register);
}

void *beNDMWStageCtl_Register(void) {
    NdmwLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beNDMWStageCtl_metaObject,
        beBaseInfoManager_Register,
        beBaseInfoManager_GetPublishedMetaObject,
        beNDMWStageCtl_GetMetaObject,
        beNDMWStageCtl_className,
        0x28, /* instance size */
        beNDMWStageCtl_GetVTable,
        beNDMWStageCtl_InitFields,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void beNDMWStageCtl_GetMetaObject(void)
{
    FUN_003bbe30();
}

void beNDMWStageCtl_InitFields(void) {
    int temp_s1;
    void *temp_s0;

    temp_s0 = (void *)g_beNDMWStageCtl_metaObject[0];
    temp_s1 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &DAT_004ca138[0], 1);
    igMetaObject_NameFields(temp_s0, &DAT_004ca140[0], &DAT_004ca148[0], &DAT_004ca150[0], temp_s1);
}

