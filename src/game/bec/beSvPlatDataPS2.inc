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
    beSvPlatDataPS2 obj;
    int vtable;

    igObject_InitHeader(&obj);
    obj._slotList = 0;
    obj._vtable = (int)&g_beSvPlatDataPS2_vtable[0];
    obj._dirName = 0;
    obj._title = 0;
    obj._fnameIcon0 = 0;
    obj._fnameIcon1 = 0;
    obj._fnameIcon2 = 0;
    obj._image = 0;
    vtable = *(int *)((char *)&obj + *(int *)((char *)(g_objectSystem[0]) + 916));
    obj._vtable = (int)&g_beSvPlatDataPS2_vtable[0];
    igSmartPointer_igObjectList_Destruct(&obj._image, -1);
    igStringRef_Destruct(&obj._fnameIcon2, -1);
    igStringRef_Destruct(&obj._fnameIcon1, -1);
    igStringRef_Destruct(&obj._fnameIcon0, -1);
    igStringRef_Destruct(&obj._title, -1);
    igStringRef_Destruct(&obj._dirName, -1);
    beSvPlatBaseData_Destroy((beSvPlatBaseData *)&obj, (short)0);
    return vtable;
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
    int base;
    int index;
    void **found;
    igEnumMetaField *field;
    void *meta;
    igIntMetaField *clone;

    meta = (igMetaObject *)(((void * *)&g_beSvPlatDataPS2_metaObject)[0]);
    base = igMetaObject_GetFieldCount(meta);
    igMetaObject_CreateFields(meta, g_beSvPlatDataPS2_ctorTable, 0x16);
    found = (void **)(igMetaObject_FindFieldByName(meta, "_connectMax"));
    index = ObjectPointerList_FindIndex(((igMetaObject *)meta)->_metaFields, found);
    clone = (igIntMetaField *)(((igObjectDispatchView *)found)->CloneViaMetadata(1));
    igIntMetaField_SetDefault(clone, 5);
    clone->_externalEnumStorage = (int)(&g_beSvPlatDataPS2_connectMaxStorage);
    igMetaObject_FinalizeAndReplaceField(meta, index, clone);
    clone->_refCount = (int)clone->_refCount - 1;
    if (((unsigned long long) ((long long)(int)clone->_refCount << 0x29) >> 0x29) == 0) {
        igObject_Destroy(clone);
    }
    field = (igEnumMetaField *)igMetaObject_GetFieldAt(meta, base + 4); field->_getMetaEnumFunction = 4;
    field = (igEnumMetaField *)igMetaObject_GetFieldAt(meta, base + 5); field->_getMetaEnumFunction = 4;
    field = (igEnumMetaField *)igMetaObject_GetFieldAt(meta, base + 6); field->_getMetaEnumFunction = 4;
    field = (igEnumMetaField *)igMetaObject_GetFieldAt(meta, base + 7); field->_getMetaEnumFunction = 4;
    field = (igEnumMetaField *)igMetaObject_GetFieldAt(meta, base + 8); field->_getMetaEnumFunction = 4;
    field = (igEnumMetaField *)igMetaObject_GetFieldAt(meta, base + 9); field->_getMetaEnumFunction = 4;
    field = (igEnumMetaField *)igMetaObject_GetFieldAt(meta, base + 0xA); field->_getMetaEnumFunction = 4;
    field = (igEnumMetaField *)igMetaObject_GetFieldAt(meta, base + 0xB); field->_getMetaEnumFunction = 4;
    field = (igEnumMetaField *)igMetaObject_GetFieldAt(meta, base + 0xC); field->_getMetaEnumFunction = 4;
    field = (igEnumMetaField *)igMetaObject_GetFieldAt(meta, base + 0xD); field->_getMetaEnumFunction = 4;
    field = (igEnumMetaField *)igMetaObject_GetFieldAt(meta, base + 0xE); field->_getMetaEnumFunction = 4;
    field = (igEnumMetaField *)igMetaObject_GetFieldAt(meta, base + 0x13); field->_getMetaEnumFunction = 2;
    igObjectRefMetaField *image = (igObjectRefMetaField *)(igMetaObject_GetFieldAt(meta, base + 0x15));
    image->_metaObject = igObjectList_GetOrCreateMetaObject();
    image->_construct = 1;
    igMetaObject_NameFields(meta, g_beSvPlatDataPS2_fieldTable, g_beSvPlatDataPS2_fieldHandles, g_beSvPlatDataPS2_fieldOffsets, base);
}

