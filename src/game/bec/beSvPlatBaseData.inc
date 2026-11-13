igMetaObject *FUN_0034a210(void) {
    if (g_beSvPlatBaseData_metaObject[0] == 0) {
        g_beSvPlatBaseData_metaObject[0] = igMetaObject_Create(Memory_GetAllocatorBySelector(g_metadataAllocatorKey[0]));
    }
    return g_beSvPlatBaseData_metaObject[0];
}

void *FUN_0034a260(void) {
    igMetaObject *g = g_beSvPlatBaseData_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false) {
        FUN_0034a340();
    }
    return g_beSvPlatBaseData_metaObject[0];
}

int beSvPlatBaseData_GetVTable(void) {
    struct F_34a2b0 f;
    int **pr;
    int temp_s0;
    int *o;

    igObject_InitHeader(&f);
    f.vt = &DAT_00538d40[0];
    pr = &f.ref;
    *pr = 0;
    temp_s0 = *(int *)((char *)&f + *(int *)((char *)(g_objectSystem[0]) + 916));
    f.vt = &DAT_00538d40[0];
    if (pr != 0) {
        if (*pr != 0) {
            o = *pr;
            o[1] = o[1] - 1;
            if ((o[1] & 0x7FFFFF) == 0) {
                igObject_Destroy(o);
            }
        }
    }
    return temp_s0;
}

void FUN_0034a340(void)
{
    igMetaObject_RunStaticInit(beSvPlatBaseData_Register);
}

void *beSvPlatBaseData_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beSvPlatBaseData_metaObject,
        igObject_Register,
        igObject_GetMetaObject_ParentAccessor,
        beSvPlatBaseData_GetMetaObject,
        beSvPlatBaseData_className,
        0x18, /* instance size */
        beSvPlatBaseData_GetVTable,
        beSvPlatBaseData_InitFields,
        0, /* extra callback item */
        g_beSvPlatBaseData_callbackList /* callback list */
    );
}

void beSvPlatBaseData_GetMetaObject(void)
{
    FUN_0034a260();
}

void beSvPlatBaseData_InitFields(void) {
    int temp_s2;
    void *temp_s1;
    void *temp_s0;

    temp_s0 = (void *)g_beSvPlatBaseData_metaObject[0];
    temp_s2 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &g_beSvPlatBaseData_ctorTable[0], 4);
    temp_s1 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 1));
    ((igObjectRefMetaField *)temp_s1)->_metaObject = (int)FUN_0034a4a0();
    ((igRefMetaField *)temp_s1)->_construct = 1;
    igMetaObject_NameFields(temp_s0, &g_beSvPlatBaseData_fieldTable[0], &DAT_004c4280[0], &DAT_004c4290[0], temp_s2);
}

