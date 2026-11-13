igMetaObject *beNDMWLoadCtrl2Info_ResolveMetaObject(void)
{
    unsigned char ready;
    if (g_beNDMWLoadCtrl2Info_metaObject[0] != 0) {
        ready = (g_beNDMWLoadCtrl2Info_metaObject[0]->_validity & 4) != 0;
        if (ready != 0) goto done;
    }
    FUN_003c4a90();
done:
    return g_beNDMWLoadCtrl2Info_metaObject[0];
}

int beNDMWLoadCtrl2Info_GetVTable(void) {
    union U_3c4a10 u;
    int temp_s0;
    int *p;

    igObject_InitHeader(u.b);
    *(int *)&u.b[8] = 0;
    *(int *)&u.b[20] = 0;
    *(int *)&u.b[24] = 0;
    u.vt = (int)&DAT_0053ce60[0];
    p = (int *)&u.b[28];
    *p = 0;
    temp_s0 = *(int *)&u.b[*(int *)((char *)(g_objectSystem[0]) + 916)];
    u.vt = (int)&DAT_0053ce60[0];
    FUN_0014aa70(p, -1);
    FUN_0033ec80(u.b, 0);
    return temp_s0;
}

void FUN_003c4a90(void)
{
    igMetaObject_RunStaticInit(beNDMWLoadCtrl2Info_Register);
}

void *beNDMWLoadCtrl2Info_Register(void) {
    NdmwLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        ((igMetaObject_3c4ab0 * *)g_beNDMWLoadCtrl2Info_metaObject),
        beBaseInfo_Register,
        beBaseInfo_GetPublishedMetaObject,
        beNDMWLoadCtrl2Info_GetMetaObject,
        beNDMWLoadCtrl2Info_className,
        0x20, /* instance size */
        beNDMWLoadCtrl2Info_GetVTable,
        beNDMWLoadCtrl2Info_InitFields,
        0, /* extra callback item */
        g_beNDMWLoadCtrl2Info_callbackList /* callback list */
    );
}

void beNDMWLoadCtrl2Info_GetMetaObject(void)
{
    beNDMWLoadCtrl2Info_ResolveMetaObject();
}

void beNDMWLoadCtrl2Info_InitFields(void) {
    int temp_s2;
    void *temp_s1;
    void *temp_s0;

    temp_s0 = (void *)g_beNDMWLoadCtrl2Info_metaObject[0];
    temp_s2 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &g_beNDMWLoadCtrl2Info_ctorTable[0], 1);
    temp_s1 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2));
    ((igObjectRefMetaField *)temp_s1)->_metaObject = igObjectList_GetOrCreateMetaObject();
    igMetaObject_NameFields(temp_s0, &g_beNDMWLoadCtrl2Info_fieldTable[0], &DAT_004cb7b8[0], &DAT_004cb7c0[0], temp_s2);
}

