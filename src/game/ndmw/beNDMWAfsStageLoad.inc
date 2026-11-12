igMetaObject *beNDMWAfsStageLoad_ResolveMetaObject(void)
{
    unsigned char ready;
    if (g_beNDMWAfsStageLoad_metaObject[0] != 0) {
        ready = (g_beNDMWAfsStageLoad_metaObject[0]->_validity & 4) != 0;
        if (ready != 0) goto done;
    }
    FUN_003cac70();
done:
    return g_beNDMWAfsStageLoad_metaObject[0];
}

int beNDMWAfsStageLoad_GetVTable(void) {
    union U_3cabe0 u;
    int temp_s0;
    char *ps;
    int *temp_a0;

    igObject_InitHeader(u.b);
    u.vt = (int)&DAT_0053df40[0];
    ps = &u.b[12];
    *(int *)ps = 0;
    temp_s0 = *(int *)&u.b[*(int *)((char *)(g_objectSystem[0]) + 916)];
    u.vt = (int)&DAT_0053df40[0];
    if (ps != 0) {
        temp_a0 = *(int **)ps;
        if (temp_a0 != 0) {
            temp_a0[1] = temp_a0[1] - 1;
            if (((unsigned long long) ((long long) temp_a0[1] << 0x29) >> 0x29) == 0) {
                igObject_Destroy(temp_a0);
            }
        }
    }
    return temp_s0;
}

void FUN_003cac70(void)
{
    igMetaObject_RunStaticInit(beNDMWAfsStageLoad_Register);
}

void *beNDMWAfsStageLoad_Register(void) {
    NdmwLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        ((igMetaObject_3cac90 * *)g_beNDMWAfsStageLoad_metaObject),
        igAction_Register,
        igAction_GetPublishedMetaObject,
        beNDMWAfsStageLoad_GetMetaObject,
        beNDMWAfsStageLoad_className,
        0x10, /* instance size */
        beNDMWAfsStageLoad_GetVTable,
        beNDMWAfsStageLoad_InitFields,
        0, /* extra callback item */
        g_beNDMWAfsStageLoad_callbackList /* callback list */
    );
}

void beNDMWAfsStageLoad_GetMetaObject(void)
{
    beNDMWAfsStageLoad_ResolveMetaObject();
}

int FUN_003cad30(void) {
    return g_igAction_metaObject[0];
}

void beNDMWAfsStageLoad_InitFields(void) {
    int temp_s2;
    void *temp_s1;
    void *temp_s1_2;
    void *temp_s0;

    temp_s0 = (void *)g_beNDMWAfsStageLoad_metaObject[0];
    temp_s2 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &DAT_004cc608[0], 2);
    temp_s1 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2));
    ((igObjectRefMetaField *)temp_s1)->_metaObject = FUN_00232840();
    ((igObjectRefMetaField *)temp_s1)->_refCounted = 0;
    temp_s1_2 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 1));
    ((igObjectRefMetaField *)temp_s1_2)->_metaObject = FUN_002be2b0();
    ((igRefMetaField *)temp_s1_2)->_construct = 1;
    igMetaObject_NameFields(temp_s0, &DAT_004cc610[0], &DAT_004cc618[0], &DAT_004cc620[0], temp_s2);
}

