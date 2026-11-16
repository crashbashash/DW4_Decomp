igMetaObject *g_beSvPlatDataGC_metaObject;
int g_beSvPlatDataGC_connectMaxStorage;
igMetaField *g_beSvPlatDataGC_fileNameMetaField;
igMetaField *g_beSvPlatDataGC_imageSizeMetaField;
igMetaField *g_beSvPlatDataGC_dataOffSetMetaField;
igMetaField *g_beSvPlatDataGC_bannerTypeMetaField;
igMetaField *g_beSvPlatDataGC_iconTypeMetaField;
igMetaField *g_beSvPlatDataGC_iconKazMetaField;
igMetaField *g_beSvPlatDataGC_iconSpeedMetaField;
igMetaField *g_beSvPlatDataGC_iconLoopTypeMetaField;
igMetaField *g_beSvPlatDataGC_banTplSizeMetaField;
igMetaField *g_beSvPlatDataGC_banTplDataMetaField;
igMetaField *g_beSvPlatDataGC_iconTplSizeMetaField;
igMetaField *g_beSvPlatDataGC_iconTplDataMetaField;
igMetaField *g_beSvPlatDataGC_commentMetaField;

void *beSvPlatDataGC_GetMetaObject(void) {
    igMetaObject *g = g_beSvPlatDataGC_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false) {
        beSvPlatDataGC_EnsureRegistered();
    }
    return g_beSvPlatDataGC_metaObject;
}

int beSvPlatDataGC_GetVTable(void) {
    union U_347e70 u;
    int temp_s0;
    char *q0;
    igObject *q1;
    int *temp_v1;
    int *temp_a1;
    int temp_v0;

    igObject_InitHeader(u.b);
    q1 = (igObject *)&u.b[12];
    *(int *)q1 = 0;
    u.vt = (int)&g_beSvPlatDataGC_vtable[0];
    q0 = &u.b[104];
    *(int *)q0 = 0;
    temp_s0 = *(int *)&u.b[*(int *)((char *)(g_objectSystem[0]) + 916)];
    u.vt = (int)&g_beSvPlatDataGC_vtable[0];
    if (q0 != 0) {
        temp_v1 = *(int **)q0;
        if (temp_v1 != 0) {
            temp_a1 = temp_v1 - 2;
            temp_v0 = temp_v1[-1] - 1;
            temp_v1[-1] = temp_v0;
            if (temp_v0 == 0) {
                StringChunk_ReleaseHeader(*temp_a1, temp_a1);
            }
        }
    }
    u.vt = (int)&g_beSvPlatBaseData_vtable[0];
    if (q1 != 0) {
        q1 = *(igObject **)q1;
        if (q1 != 0) {
            q1->_refCount = (int)q1->_refCount - 1;
            if (((unsigned long long) ((long long)(int)q1->_refCount << 0x29) >> 0x29) == 0) {
                igObject_Destroy(q1);
            }
        }
    }
    return temp_s0;
}

void beSvPlatDataGC_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(beSvPlatDataGC_Register);
}

void *beSvPlatDataGC_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_beSvPlatDataGC_metaObject,
        beSvPlatBaseData_Register,
        beSvPlatBaseData_GetPublishedMetaObject,
        beSvPlatDataGC_GetMetaObjectFunction,
        "beSvPlatDataGC",
        0x8c, /* instance size */
        beSvPlatDataGC_GetVTable,
        beSvPlatDataGC_InitFields,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void beSvPlatDataGC_GetMetaObjectFunction(void)
{
    beSvPlatDataGC_GetMetaObject();
}

static FieldFactory g_beSvPlatDataGC_ctorTable[] = {
    igStringMetaField_Create,
    igIntMetaField_Create,
    igIntArrayMetaField_Create,
    igIntMetaField_Create,
    igIntMetaField_Create,
    igIntMetaField_Create,
    igIntMetaField_Create,
    igIntMetaField_Create,
    igIntMetaField_Create,
    igMemoryRefMetaField_Create,
    igIntMetaField_Create,
    igMemoryRefMetaField_Create,
    igCharArrayMetaField_Create,
};
static const char *g_beSvPlatDataGC_fieldTable[] = {
    "_fileName",
    "_imageSize",
    "_dataOffSet",
    "_bannerType",
    "_iconType",
    "_iconKaz",
    "_iconSpeed",
    "_iconLoopType",
    "_banTplSize",
    "_banTplData",
    "_iconTplSize",
    "_iconTplData",
    "_comment",
};
static igMetaField **g_beSvPlatDataGC_fieldHandles[] = {
    &g_beSvPlatDataGC_fileNameMetaField,
    &g_beSvPlatDataGC_imageSizeMetaField,
    &g_beSvPlatDataGC_dataOffSetMetaField,
    &g_beSvPlatDataGC_bannerTypeMetaField,
    &g_beSvPlatDataGC_iconTypeMetaField,
    &g_beSvPlatDataGC_iconKazMetaField,
    &g_beSvPlatDataGC_iconSpeedMetaField,
    &g_beSvPlatDataGC_iconLoopTypeMetaField,
    &g_beSvPlatDataGC_banTplSizeMetaField,
    &g_beSvPlatDataGC_banTplDataMetaField,
    &g_beSvPlatDataGC_iconTplSizeMetaField,
    &g_beSvPlatDataGC_iconTplDataMetaField,
    &g_beSvPlatDataGC_commentMetaField,
};
static int g_beSvPlatDataGC_fieldOffsets[] = {
    104,
    108,
    24,
    112,
    116,
    120,
    124,
    128,
    132,
    32,
    136,
    36,
    40,
};

void beSvPlatDataGC_InitFields(void) {
    int base;
    int index;
    void **found;
    H *banTplData;
    G_348000 *tg;
    H *iconTplData;
    void *meta;
    igIntMetaField *clone;

    meta = (void *)g_beSvPlatDataGC_metaObject;
    base = igMetaObject_GetFieldCount(meta);
    igMetaObject_CreateFields(meta, g_beSvPlatDataGC_ctorTable, 0xD);
    found = (void **)(igMetaObject_FindFieldByName(meta, "_connectMax"));
    index = ObjectPointerList_FindIndex(((igMetaObject *)meta)->_metaFields, found);
    clone = (igIntMetaField *)(((DW4VC_84_1 *)(found))->vX((int)(1)));
    igIntMetaField_SetDefault(clone, 2);
    clone->_externalEnumStorage = (int)(&g_beSvPlatDataGC_connectMaxStorage);
    igMetaObject_FinalizeAndReplaceField(meta, index, clone);
    clone->_refCount = (int)clone->_refCount - 1;
    if (((unsigned long long) ((long long)(int)clone->_refCount << 0x29) >> 0x29) == 0) {
        igObject_Destroy(clone);
    }
    tg = (G_348000 *)igMetaObject_GetFieldAt(meta, base + 2);
    tg->w52 = 2;
    banTplData = (H *)(igMetaObject_GetFieldAt(meta, base + 9));
    banTplData->f60 = igCharMetaField_GetDefaultDescriptor();
    iconTplData = (H *)(igMetaObject_GetFieldAt(meta, base + 0xB));
    iconTplData->f60 = igCharMetaField_GetDefaultDescriptor();
    tg = (G_348000 *)igMetaObject_GetFieldAt(meta, base + 0xC);
    tg->w52 = 0x40;
    igMetaObject_NameFields(meta, g_beSvPlatDataGC_fieldTable, g_beSvPlatDataGC_fieldHandles, g_beSvPlatDataGC_fieldOffsets, base);
}

