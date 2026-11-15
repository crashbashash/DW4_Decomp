igMetaObject *g_beSvSlotXbox_metaObject;
igMetaField *g_beSvSlotXbox_nameMetaField;
igMetaField *g_beSvSlotXbox_totalBytesMetaField;
igMetaField *g_beSvSlotXbox_freeBytesMetaField;
igMetaField *g_beSvSlotXbox_useBytesMetaField;

void *FUN_0034a8c0(void) {
    igMetaObject *g = g_beSvSlotXbox_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false) {
        FUN_0034a9a0();
    }
    return g_beSvSlotXbox_metaObject;
}

int beSvSlotXbox_GetVTable(void) {
    union U_34a910 u;
    int temp_s0;
    char *ps;
    int *temp_v1;
    int *temp_a1;
    int temp_v0;

    igObject_InitHeader(u.b);
    u.vt = (int)&DAT_00538970[0];
    ps = &u.b[24];
    *(int *)ps = 0;
    temp_s0 = *(int *)&u.b[*(int *)((char *)(g_objectSystem[0]) + 916)];
    u.vt = (int)&DAT_00538970[0];
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

void FUN_0034a9a0(void)
{
    igMetaObject_RunStaticInit(beSvSlotXbox_Register);
}

void *beSvSlotXbox_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_beSvSlotXbox_metaObject,
        beSvSlotData_Register,
        beSvSlotData_GetPublishedMetaObject,
        beSvSlotXbox_GetMetaObject,
        "beSvSlotXbox",
        0x38, /* instance size */
        beSvSlotXbox_GetVTable,
        beSvSlotXbox_InitFields,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void beSvSlotXbox_GetMetaObject(void)
{
    FUN_0034a8c0();
}

static FieldFactory g_beSvSlotXbox_ctorTable[] = {
    igStringMetaField_Create,
    igUnsignedLongMetaField_Create,
    igUnsignedLongMetaField_Create,
    igUnsignedLongMetaField_Create,
};
static const char *g_beSvSlotXbox_fieldTable[] = {
    "_name",
    "_totalBytes",
    "_freeBytes",
    "_useBytes",
};
static igMetaField **g_beSvSlotXbox_fieldHandles[] = {
    &g_beSvSlotXbox_nameMetaField,
    &g_beSvSlotXbox_totalBytesMetaField,
    &g_beSvSlotXbox_freeBytesMetaField,
    &g_beSvSlotXbox_useBytesMetaField,
};
static int g_beSvSlotXbox_fieldOffsets[] = {
    24,
    32,
    40,
    48,
};

void beSvSlotXbox_InitFields(void) {
    int temp_s1;
    void *temp_s0;

    temp_s0 = (void *)g_beSvSlotXbox_metaObject;
    temp_s1 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, g_beSvSlotXbox_ctorTable, 4);
    igStringMetaField_SetDefaultText(((int)igMetaObject_GetFieldAt(temp_s0, temp_s1)), "");
    igMetaObject_NameFields(temp_s0, g_beSvSlotXbox_fieldTable, g_beSvSlotXbox_fieldHandles, g_beSvSlotXbox_fieldOffsets, temp_s1);
}

