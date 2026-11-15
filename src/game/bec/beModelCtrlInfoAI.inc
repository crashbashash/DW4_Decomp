igMetaObject *g_beModelCtrlInfoAI_metaObject;
igMetaField *g_beModelCtrlInfoAI_seqNameMetaField;
igMetaField *g_beModelCtrlInfoAI_mapNoMetaField;
igMetaField *g_beModelCtrlInfoAI_worldPosMetaField;
igMetaField *g_beModelCtrlInfoAI_hStatusMetaField;
igMetaField *g_beModelCtrlInfoAI_hCountMetaField;

void beModelCtrlInfoAI_Create(int arg0) {
    FUN_003522b0();
    igMetaObject_CreateInstance(*(int *)0x588AD0, arg0);
}

igMetaObject *FUN_00352180(void) {
    if (g_beModelCtrlInfoAI_metaObject == 0) {
        g_beModelCtrlInfoAI_metaObject = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData[0]));
    }
    return g_beModelCtrlInfoAI_metaObject;
}

void *FUN_003521d0(void) {
    igMetaObject *g = g_beModelCtrlInfoAI_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false) {
        FUN_003522b0();
    }
    return g_beModelCtrlInfoAI_metaObject;
}

int beModelCtrlInfoAI_GetVTable(void) {
    struct F_352220 f;
    int **pr;
    int temp_s0;
    int *temp_a1;
    int temp_v0;

    igObject_InitHeader(&f);
    f.vt = &DAT_00537e20[0];
    pr = &f.ref;
    *pr = 0;
    temp_s0 = *(int *)((char *)&f + *(int *)((char *)(g_objectSystem[0]) + 916));
    f.vt = &DAT_00537e20[0];
    if (pr != 0) {
        if (*pr != 0) {
            temp_a1 = *pr - 2;
            temp_v0 = (*pr)[-1] - 1;
            (*pr)[-1] = temp_v0;
            if (temp_v0 == 0) {
                StringChunk_ReleaseHeader(*temp_a1, temp_a1);
            }
        }
    }
    return temp_s0;
}

void FUN_003522b0(void)
{
    igMetaObject_RunStaticInit(beModelCtrlInfoAI_Register);
}

void *beModelCtrlInfoAI_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_beModelCtrlInfoAI_metaObject,
        igObject_Register,
        igObject_GetMetaObject_ParentAccessor,
        beModelCtrlInfoAI_GetMetaObject,
        "beModelCtrlInfoAI",
        0x24, /* instance size */
        beModelCtrlInfoAI_GetVTable,
        beModelCtrlInfoAI_InitFields,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void beModelCtrlInfoAI_GetMetaObject(void)
{
    FUN_003521d0();
}

static FieldFactory g_beModelCtrlInfoAI_ctorTable[] = {
    igStringMetaField_Create,
    igIntMetaField_Create,
    FUN_00187890,
    igIntMetaField_Create,
    igIntMetaField_Create,
};
static const char *g_beModelCtrlInfoAI_fieldTable[] = {
    "_seqName",
    "_mapNo",
    "_worldPos",
    "_hStatus",
    "_hCount",
};
static igMetaField **g_beModelCtrlInfoAI_fieldHandles[] = {
    &g_beModelCtrlInfoAI_seqNameMetaField,
    &g_beModelCtrlInfoAI_mapNoMetaField,
    &g_beModelCtrlInfoAI_worldPosMetaField,
    &g_beModelCtrlInfoAI_hStatusMetaField,
    &g_beModelCtrlInfoAI_hCountMetaField,
};
static int g_beModelCtrlInfoAI_fieldOffsets[] = {
    8,
    12,
    16,
    28,
    32,
};

void beModelCtrlInfoAI_InitFields(void) {
    int temp_s1;
    void *temp_s0;

    temp_s0 = (void *)g_beModelCtrlInfoAI_metaObject;
    temp_s1 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, g_beModelCtrlInfoAI_ctorTable, 5);
    igMetaObject_NameFields(temp_s0, g_beModelCtrlInfoAI_fieldTable, g_beModelCtrlInfoAI_fieldHandles, g_beModelCtrlInfoAI_fieldOffsets, temp_s1);
}

