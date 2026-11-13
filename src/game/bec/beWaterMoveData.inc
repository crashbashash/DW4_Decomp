void *FUN_003408b0(void) {
    igMetaObject *g = g_beWaterMoveData_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false) {
        FUN_00340990();
    }
    return g_beWaterMoveData_metaObject[0];
}

int beWaterMoveData_GetVTable(void) {
    union U_340900 u;
    int temp_s0;
    char *ps;
    int *p;
    int v;

    igObject_InitHeader(u.b);
    u.vt = (int)&DAT_00539940[0];
    ps = &u.b[20];
    *(int *)ps = 0;
    temp_s0 = *(int *)&u.b[*(int *)((char *)(g_objectSystem[0]) + 916)];
    u.vt = (int)&DAT_00539940[0];
    if (ps != 0) {
        p = *(int **)ps;
        if (p != 0) {
            v = p[1] - 1;
            p[1] = v;
            if ((p[1] & 0x7fffff) == 0) {
                igObject_Destroy(p);
            }
        }
    }
    return temp_s0;
}

void FUN_00340990(void)
{
    igMetaObject_RunStaticInit(beWaterMoveData_Register);
}

void *beWaterMoveData_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beWaterMoveData_metaObject,
        igObject_Register,
        igObject_GetMetaObject_ParentAccessor,
        beWaterMoveData_GetMetaObject,
        beWaterMoveData_className,
        0x18, /* instance size */
        beWaterMoveData_GetVTable,
        beWaterMoveData_InitFields,
        0, /* extra callback item */
        g_beWaterMoveData_callbackList /* callback list */
    );
}

void beWaterMoveData_GetMetaObject(void)
{
    FUN_003408b0();
}

void beWaterMoveData_InitFields(void) {
    int temp_s2;
    void *temp_s1;
    void *temp_s0;

    temp_s0 = (void *)g_beWaterMoveData_metaObject[0];
    temp_s2 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &g_beWaterMoveData_ctorTable[0], 3);
    temp_s1 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 2));
    ((igObjectRefMetaField *)temp_s1)->_metaObject = FUN_0018a0a0();
    ((igRefMetaField *)temp_s1)->_construct = 1;
    igMetaObject_NameFields(temp_s0, &g_beWaterMoveData_fieldTable[0], &DAT_004c3328[0], &DAT_004c3338[0], temp_s2);
}

