igMetaObject *g_beModelCtrlInfoDataAIH_metaObject;
int g_beModelCtrlInfoDataAIH_nameStorage;
igMetaField *g_beModelCtrlInfoDataAIH_isXHomingMetaField;
igMetaField *g_beModelCtrlInfoDataAIH_isYHomingMetaField;
igMetaField *g_beModelCtrlInfoDataAIH_firstFrameMetaField;
igMetaField *g_beModelCtrlInfoDataAIH_secondFrameMetaField;
igMetaField *g_beModelCtrlInfoDataAIH_areaSquareMetaField;
igMetaField *g_beModelCtrlInfoDataAIH_limitRotXMetaField;
igMetaField *g_beModelCtrlInfoDataAIH_limitRotYMetaField;
igMetaField *g_beModelCtrlInfoDataAIH_limitCountMetaField;

void *beModelCtrlInfoDataAIH_GetMetaObject(void) {
    unsigned char b;
    if (g_beModelCtrlInfoDataAIH_metaObject != 0) {
        b = (*(int *)((char *)(g_beModelCtrlInfoDataAIH_metaObject) + 36) & 4) != 0;
        if (b != 0) goto done;
    }
    beModelCtrlInfoDataAIH_EnsureRegistered();
done:
    return g_beModelCtrlInfoDataAIH_metaObject;
}

int beModelCtrlInfoDataAIH_GetVTable(void) {
    union U u;
    int temp_s0;
    char *ps;
    int *temp_v1;
    int *temp_a1;
    int temp_v0;

    igObject_InitHeader(u.b);
    ps = &u.b[8];
    *(int *)ps = 0;
    u.vt = (int)&g_igNamedObject_vtable[0];
    u.vt = (int)&g_beModelCtrlInfoDataAIH_vtable[0];
    temp_s0 = *(int *)&u.b[*(int *)((char *)(g_objectSystem[0]) + 916)];
    u.vt = (int)&g_igNamedObject_vtable[0];
    if (ps != 0) {
        temp_v1 = *(int **)ps;
        if (temp_v1 != 0) {
            temp_a1 = temp_v1 - 2;
            temp_v0 = temp_v1[-1] - 1;
            temp_v1[-1] = temp_v0;
            if (temp_v0 == 0) {
                StringChunk_ReleaseHeader(*temp_a1, temp_a1);
            }
        }
    }
    return temp_s0;
}

void beModelCtrlInfoDataAIH_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(beModelCtrlInfoDataAIH_Register);
}

void *beModelCtrlInfoDataAIH_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_beModelCtrlInfoDataAIH_metaObject,
        beBaseInfoData_Register,
        beBaseInfoData_GetPublishedMetaObject,
        beModelCtrlInfoDataAIH_GetMetaObjectFunction,
        "beModelCtrlInfoDataAIH",
        0x2c, /* instance size */
        beModelCtrlInfoDataAIH_GetVTable,
        beModelCtrlInfoDataAIH_InitFields,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void beModelCtrlInfoDataAIH_GetMetaObjectFunction(void)
{
    beModelCtrlInfoDataAIH_GetMetaObject();
}

static FieldFactory g_beModelCtrlInfoDataAIH_ctorTable[] = {
    igBoolMetaField_Create,
    igBoolMetaField_Create,
    igFloatMetaField_Create,
    igFloatMetaField_Create,
    igFloatMetaField_Create,
    igFloatMetaField_Create,
    igFloatMetaField_Create,
    igIntMetaField_Create,
};
static const char *g_beModelCtrlInfoDataAIH_fieldTable[] = {
    "_isXHoming",
    "_isYHoming",
    "_firstFrame",
    "_secondFrame",
    "_areaSquare",
    "_limitRotX",
    "_limitRotY",
    "_limitCount",
};
static igMetaField **g_beModelCtrlInfoDataAIH_fieldHandles[] = {
    &g_beModelCtrlInfoDataAIH_isXHomingMetaField,
    &g_beModelCtrlInfoDataAIH_isYHomingMetaField,
    &g_beModelCtrlInfoDataAIH_firstFrameMetaField,
    &g_beModelCtrlInfoDataAIH_secondFrameMetaField,
    &g_beModelCtrlInfoDataAIH_areaSquareMetaField,
    &g_beModelCtrlInfoDataAIH_limitRotXMetaField,
    &g_beModelCtrlInfoDataAIH_limitRotYMetaField,
    &g_beModelCtrlInfoDataAIH_limitCountMetaField,
};
static int g_beModelCtrlInfoDataAIH_fieldOffsets[] = {
    16,
    17,
    20,
    24,
    28,
    32,
    36,
    40,
};

void beModelCtrlInfoDataAIH_InitFields(void) {
    int temp_s2;
    int temp_s3;
    void **temp_v0;
    void *temp_s1;
    S_ref *temp_v0_2;

    temp_s1 = (void *)(g_beModelCtrlInfoDataAIH_metaObject);
    temp_s2 = igMetaObject_GetFieldCount(temp_s1);
    igMetaObject_CreateFields(temp_s1, g_beModelCtrlInfoDataAIH_ctorTable, 8);
    temp_v0 = (void **)(igMetaObject_FindFieldByName(temp_s1, "_name"));
    temp_s3 = ObjectPointerList_FindIndex(*(int *)((char *)(temp_s1) + 40), temp_v0);
    temp_v0_2 = (S_ref *)(((DW4VC_84_1 *)(temp_v0))->vX((int)(1)));
    igStringMetaField_SetDefaultText(temp_v0_2, "AIH");
    *(int *)((char *)(temp_v0_2) + 28) = (int)(&g_beModelCtrlInfoDataAIH_nameStorage);
    igMetaObject_FinalizeAndReplaceField(temp_s1, temp_s3, temp_v0_2);
    temp_v0_2->f4 = temp_v0_2->f4 - 1;
    if (((unsigned long long) ((long long) temp_v0_2->f4 << 0x29) >> 0x29) == 0) {
        igObject_Destroy(temp_v0_2);
    }
    igMetaObject_NameFields(temp_s1, g_beModelCtrlInfoDataAIH_fieldTable, g_beModelCtrlInfoDataAIH_fieldHandles, g_beModelCtrlInfoDataAIH_fieldOffsets, temp_s2);
}

