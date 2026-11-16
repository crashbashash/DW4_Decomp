igMetaObject *g_beSvPlatDataPS2_metaObject;
int g_beSvPlatDataPS2_connectMaxStorage;
igMetaField *g_beSvPlatDataPS2_dirNameMetaField;
igMetaField *g_beSvPlatDataPS2_titleMetaField;
igMetaField *g_beSvPlatDataPS2_offsLFMetaField;
igMetaField *g_beSvPlatDataPS2_transRateMetaField;
igMetaField *g_beSvPlatDataPS2_bgColor0MetaField;
igMetaField *g_beSvPlatDataPS2_bgColor1MetaField;
igMetaField *g_beSvPlatDataPS2_bgColor2MetaField;
igMetaField *g_beSvPlatDataPS2_bgColor3MetaField;
igMetaField *g_beSvPlatDataPS2_lightDir0MetaField;
igMetaField *g_beSvPlatDataPS2_lightDir1MetaField;
igMetaField *g_beSvPlatDataPS2_lightDir2MetaField;
igMetaField *g_beSvPlatDataPS2_lightColor0MetaField;
igMetaField *g_beSvPlatDataPS2_lightColor1MetaField;
igMetaField *g_beSvPlatDataPS2_lightColor2MetaField;
igMetaField *g_beSvPlatDataPS2_ambientMetaField;
igMetaField *g_beSvPlatDataPS2_fnameIcon0MetaField;
igMetaField *g_beSvPlatDataPS2_fnameIcon1MetaField;
igMetaField *g_beSvPlatDataPS2_fnameIcon2MetaField;
igMetaField *g_beSvPlatDataPS2_saveDataSizeMetaField;
igMetaField *g_beSvPlatDataPS2_dataOffSetMetaField;
igMetaField *g_beSvPlatDataPS2_iconCountMetaField;
igMetaField *g_beSvPlatDataPS2_imageMetaField;

void *beSvPlatDataPS2_GetMetaObject(void) {
    igMetaObject *g = g_beSvPlatDataPS2_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false) {
        beSvPlatDataPS2_EnsureRegistered();
    }
    return g_beSvPlatDataPS2_metaObject;
}

int beSvPlatDataPS2_GetVTable(void) {
    union U_347870 u;
    int t;
    char *o;
    int *temp_v1;
    int *temp_a1;
    int temp_v0;

    igObject_InitHeader(u.b);
    *(int *)&u.b[12] = 0;
    u.vt = (int)&g_beSvPlatDataPS2_vtable[0];
    *(int *)&u.b[24] = 0;
    *(int *)&u.b[28] = 0;
    *(int *)&u.b[184] = 0;
    *(int *)&u.b[188] = 0;
    *(int *)&u.b[192] = 0;
    *(int *)&u.b[212] = 0;
    t = *(int *)&u.b[*(int *)((char *)(g_objectSystem[0]) + 916)];
    u.vt = (int)&g_beSvPlatDataPS2_vtable[0];
    igSmartPointer_igObjectList_Destruct(&u.b[212], -1);
    igStringRef_Destruct(&u.b[192], -1);
    igStringRef_Destruct(&u.b[188], -1);
    igStringRef_Destruct(&u.b[184], -1);
    igStringRef_Destruct(&u.b[28], -1);
    igStringRef_Destruct(&u.b[24], -1);
    FUN_00347150((O_347150 *)u.b, (short)0);
    return t;
}

void beSvPlatDataPS2_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(beSvPlatDataPS2_Register);
}

static igMetaObjectCallback g_beSvPlatDataPS2_callbackList[] = { igObjectList_EnsureRegistered, 0 };

void *beSvPlatDataPS2_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_beSvPlatDataPS2_metaObject,
        beSvPlatBaseData_Register,
        beSvPlatBaseData_GetPublishedMetaObject,
        beSvPlatDataPS2_GetMetaObjectFunction,
        "beSvPlatDataPS2",
        0xd8, /* instance size */
        beSvPlatDataPS2_GetVTable,
        beSvPlatDataPS2_InitFields,
        0, /* extra callback item */
        g_beSvPlatDataPS2_callbackList /* callback list */
    );
}

void beSvPlatDataPS2_GetMetaObjectFunction(void)
{
    beSvPlatDataPS2_GetMetaObject();
}

static FieldFactory g_beSvPlatDataPS2_ctorTable[] = {
    igStringMetaField_Create,
    igStringMetaField_Create,
    igUnsignedShortMetaField_Create,
    igUnsignedIntMetaField_Create,
    igShortArrayMetaField_Create,
    igShortArrayMetaField_Create,
    igShortArrayMetaField_Create,
    igShortArrayMetaField_Create,
    igFloatArrayMetaField_Create,
    igFloatArrayMetaField_Create,
    igFloatArrayMetaField_Create,
    igFloatArrayMetaField_Create,
    igFloatArrayMetaField_Create,
    igFloatArrayMetaField_Create,
    igFloatArrayMetaField_Create,
    igStringMetaField_Create,
    igStringMetaField_Create,
    igStringMetaField_Create,
    igUnsignedIntMetaField_Create,
    igIntArrayMetaField_Create,
    igIntMetaField_Create,
    igObjectRefMetaField_Create,
};
static const char *g_beSvPlatDataPS2_fieldTable[] = {
    "_dirName",
    "_title",
    "_offsLF",
    "_transRate",
    "_bgColor0",
    "_bgColor1",
    "_bgColor2",
    "_bgColor3",
    "_lightDir0",
    "_lightDir1",
    "_lightDir2",
    "_lightColor0",
    "_lightColor1",
    "_lightColor2",
    "_ambient",
    "_fnameIcon0",
    "_fnameIcon1",
    "_fnameIcon2",
    "_saveDataSize",
    "_dataOffSet",
    "_iconCount",
    "_image",
};
static igMetaField **g_beSvPlatDataPS2_fieldHandles[] = {
    &g_beSvPlatDataPS2_dirNameMetaField,
    &g_beSvPlatDataPS2_titleMetaField,
    &g_beSvPlatDataPS2_offsLFMetaField,
    &g_beSvPlatDataPS2_transRateMetaField,
    &g_beSvPlatDataPS2_bgColor0MetaField,
    &g_beSvPlatDataPS2_bgColor1MetaField,
    &g_beSvPlatDataPS2_bgColor2MetaField,
    &g_beSvPlatDataPS2_bgColor3MetaField,
    &g_beSvPlatDataPS2_lightDir0MetaField,
    &g_beSvPlatDataPS2_lightDir1MetaField,
    &g_beSvPlatDataPS2_lightDir2MetaField,
    &g_beSvPlatDataPS2_lightColor0MetaField,
    &g_beSvPlatDataPS2_lightColor1MetaField,
    &g_beSvPlatDataPS2_lightColor2MetaField,
    &g_beSvPlatDataPS2_ambientMetaField,
    &g_beSvPlatDataPS2_fnameIcon0MetaField,
    &g_beSvPlatDataPS2_fnameIcon1MetaField,
    &g_beSvPlatDataPS2_fnameIcon2MetaField,
    &g_beSvPlatDataPS2_saveDataSizeMetaField,
    &g_beSvPlatDataPS2_dataOffSetMetaField,
    &g_beSvPlatDataPS2_iconCountMetaField,
    &g_beSvPlatDataPS2_imageMetaField,
};
static int g_beSvPlatDataPS2_fieldOffsets[] = {
    24,
    28,
    32,
    36,
    40,
    48,
    56,
    64,
    72,
    88,
    104,
    120,
    136,
    152,
    168,
    184,
    188,
    192,
    204,
    196,
    208,
    212,
};

void beSvPlatDataPS2_InitFields(void) {
    int temp_s2;
    int temp_s3;
    void **temp_v0;
    igEnumMetaField *temp_s0;
    igMetaObject *temp_s1;
    igEnumMetaField *temp_v0_2;

    temp_s1 = (igMetaObject *)(((void * *)&g_beSvPlatDataPS2_metaObject)[0]);
    temp_s2 = igMetaObject_GetFieldCount(temp_s1);
    igMetaObject_CreateFields(temp_s1, g_beSvPlatDataPS2_ctorTable, 0x16);
    temp_v0 = (void **)(igMetaObject_FindFieldByName(temp_s1, "_connectMax"));
    temp_s3 = ObjectPointerList_FindIndex(temp_s1->_metaFields, temp_v0);
    temp_v0_2 = (igEnumMetaField *)(((DW4VC_84_1 *)(temp_v0))->vX((int)(1)));
    igIntMetaField_SetDefault(temp_v0_2, 5);
    temp_v0_2->_externalEnumStorage = (int)(&g_beSvPlatDataPS2_connectMaxStorage);
    igMetaObject_FinalizeAndReplaceField(temp_s1, temp_s3, temp_v0_2);
    temp_v0_2->_refCount = (int)temp_v0_2->_refCount - 1;
    if (((unsigned long long) ((long long)(int)temp_v0_2->_refCount << 0x29) >> 0x29) == 0) {
        igObject_Destroy(temp_v0_2);
    }
    temp_s0 = (igEnumMetaField *)igMetaObject_GetFieldAt(temp_s1, temp_s2 + 4); temp_s0->_getMetaEnumFunction = 4;
    temp_s0 = (igEnumMetaField *)igMetaObject_GetFieldAt(temp_s1, temp_s2 + 5); temp_s0->_getMetaEnumFunction = 4;
    temp_s0 = (igEnumMetaField *)igMetaObject_GetFieldAt(temp_s1, temp_s2 + 6); temp_s0->_getMetaEnumFunction = 4;
    temp_s0 = (igEnumMetaField *)igMetaObject_GetFieldAt(temp_s1, temp_s2 + 7); temp_s0->_getMetaEnumFunction = 4;
    temp_s0 = (igEnumMetaField *)igMetaObject_GetFieldAt(temp_s1, temp_s2 + 8); temp_s0->_getMetaEnumFunction = 4;
    temp_s0 = (igEnumMetaField *)igMetaObject_GetFieldAt(temp_s1, temp_s2 + 9); temp_s0->_getMetaEnumFunction = 4;
    temp_s0 = (igEnumMetaField *)igMetaObject_GetFieldAt(temp_s1, temp_s2 + 0xA); temp_s0->_getMetaEnumFunction = 4;
    temp_s0 = (igEnumMetaField *)igMetaObject_GetFieldAt(temp_s1, temp_s2 + 0xB); temp_s0->_getMetaEnumFunction = 4;
    temp_s0 = (igEnumMetaField *)igMetaObject_GetFieldAt(temp_s1, temp_s2 + 0xC); temp_s0->_getMetaEnumFunction = 4;
    temp_s0 = (igEnumMetaField *)igMetaObject_GetFieldAt(temp_s1, temp_s2 + 0xD); temp_s0->_getMetaEnumFunction = 4;
    temp_s0 = (igEnumMetaField *)igMetaObject_GetFieldAt(temp_s1, temp_s2 + 0xE); temp_s0->_getMetaEnumFunction = 4;
    temp_s0 = (igEnumMetaField *)igMetaObject_GetFieldAt(temp_s1, temp_s2 + 0x13); temp_s0->_getMetaEnumFunction = 2;
    igObjectRefMetaField *temp_s4 = (igObjectRefMetaField *)(igMetaObject_GetFieldAt(temp_s1, temp_s2 + 0x15));
    temp_s4->_metaObject = igObjectList_GetOrCreateMetaObject();
    temp_s4->_construct = 1;
    igMetaObject_NameFields(temp_s1, g_beSvPlatDataPS2_fieldTable, g_beSvPlatDataPS2_fieldHandles, g_beSvPlatDataPS2_fieldOffsets, temp_s2);
}

