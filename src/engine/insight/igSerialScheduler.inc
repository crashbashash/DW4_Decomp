igMetaObject *igSerialScheduler_GetMetaObject(void)
{
    igMetaObject *g = g_igSerialScheduler_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_00231290();
    return g_igSerialScheduler_metaObject[0];
}

int igSerialScheduler_GetVTable(void) {
    Obj obj;
    int r;

    igObject_InitHeader(&obj);
    obj.vt = &DAT_0052c830[0];
    obj.m8 = 0;
    obj.m12 = 0;
    r = *(int *)((char *)&obj + *(int *)((char *)(g_objectSystem[0]) + 916));
    obj.vt = &DAT_0052c830[0];
    obj.rel12();
    obj.rel8();
    return r;
}

void **FUN_00231210(void **arg0, long long arg1) {
    char *o;

    if (arg0 != 0) {
        o = (char *)*arg0;
        if (o != 0) {
            *(int *)(o + 4) = *(int *)(o + 4) - 1;
            if ((*(int *)(o + 4) & 0x7FFFFF) == 0) {
                igObject_Destroy(o);
            }
        }
        if ((short)arg1 > 0) {
            __dl__FPv(arg0);
        }
    }
    return arg0;
}

void FUN_00231290(void)
{
    igMetaObject_RunStaticInit(igSerialScheduler_Register);
}

void igSerialScheduler_Register(void) {
    InsightLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igSerialScheduler_metaObject,
        igInsightScheduler_Register,
        igInsightScheduler_GetPublishedMetaObject,
        thunk_igSerialScheduler_GetMetaObject,
        igSerialScheduler_className,
        0x10, /* instance size */
        igSerialScheduler_GetVTable,
        &igSerialScheduler_InitFields,
        0, /* extra callback item */
        g_igSerialScheduler_callbackList /* callback list */
    );
}

void thunk_igSerialScheduler_GetMetaObject(void) {
    igSerialScheduler_GetMetaObject();
}

igMetaObject *FUN_00231330(void) {
    return g_igInsightScheduler_metaObject[0];
}

void igSerialScheduler_InitFields(void) {
    int temp_s2;
    void *temp_s1_2;
    void *temp_s1;
    void *temp_s0;

    temp_s0 = (void *)g_igSerialScheduler_metaObject[0];
    temp_s2 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &g_igSerialScheduler_ctorTable[0], 2);
    temp_s1 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2));
    ((igObjectRefMetaField *)temp_s1)->_metaObject = (int)FUN_00233480();
    ((igRefMetaField *)temp_s1)->_construct = 1;
    temp_s1_2 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 1));
    ((igObjectRefMetaField *)temp_s1_2)->_metaObject = (int)FUN_00233750();
    ((igRefMetaField *)temp_s1_2)->_construct = 1;
    igMetaObject_NameFields(temp_s0, &g_igSerialScheduler_fieldTable[0], &DAT_00497fa0[0], &DAT_00497fa8[0], temp_s2);
}

