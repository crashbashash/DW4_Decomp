igMetaObject *g_beSvPlatBaseData_metaObject;
igMetaField *g_beSvPlatBaseData_connectMaxMetaField;
igMetaField *g_beSvPlatBaseData_slotListMetaField;
igMetaField *g_beSvPlatBaseData_dataSizeMetaField;
igMetaField *g_beSvPlatBaseData_memNeedMetaField;

igMetaObject *FUN_0034a210(void) {
    if (g_beSvPlatBaseData_metaObject == 0) {
        g_beSvPlatBaseData_metaObject = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData[0]));
    }
    return g_beSvPlatBaseData_metaObject;
}

void *FUN_0034a260(void) {
    igMetaObject *g = g_beSvPlatBaseData_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false) {
        FUN_0034a340();
    }
    return g_beSvPlatBaseData_metaObject;
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

static igMetaObjectCallback g_beSvPlatBaseData_callbackList[] = { FUN_0034a580, 0 };

void *beSvPlatBaseData_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_beSvPlatBaseData_metaObject,
        igObject_Register,
        igObject_GetMetaObject_ParentAccessor,
        beSvPlatBaseData_GetMetaObject,
        "beSvPlatBaseData",
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

static FieldFactory g_beSvPlatBaseData_ctorTable[] = {
    igIntMetaField_Create,
    igObjectRefMetaField_Create,
    igUnsignedIntMetaField_Create,
    igUnsignedIntMetaField_Create,
};
static const char *g_beSvPlatBaseData_fieldTable[] = {
    "_connectMax",
    "_slotList",
    "_dataSize",
    "_memNeed",
};
static igMetaField **g_beSvPlatBaseData_fieldHandles[] = {
    &g_beSvPlatBaseData_connectMaxMetaField,
    &g_beSvPlatBaseData_slotListMetaField,
    &g_beSvPlatBaseData_dataSizeMetaField,
    &g_beSvPlatBaseData_memNeedMetaField,
};
static int g_beSvPlatBaseData_fieldOffsets[] = {
    8,
    12,
    16,
    20,
};

void beSvPlatBaseData_InitFields(void) {
    int temp_s2;
    void *temp_s1;
    void *temp_s0;

    temp_s0 = (void *)g_beSvPlatBaseData_metaObject;
    temp_s2 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, g_beSvPlatBaseData_ctorTable, 4);
    temp_s1 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 1));
    ((igObjectRefMetaField *)temp_s1)->_metaObject = (int)FUN_0034a4a0();
    ((igRefMetaField *)temp_s1)->_construct = 1;
    igMetaObject_NameFields(temp_s0, g_beSvPlatBaseData_fieldTable, g_beSvPlatBaseData_fieldHandles, g_beSvPlatBaseData_fieldOffsets, temp_s2);
}

