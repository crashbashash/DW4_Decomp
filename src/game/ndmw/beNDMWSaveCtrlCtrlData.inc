igMetaObject *g_beNDMWSaveCtrlCtrlData_metaObject;
int g_beNDMWSaveCtrlCtrlData_nameExternalEnumStorage;
igMetaField *g_beNDMWSaveCtrlCtrlData_orderMetaField;
igMetaField *g_beNDMWSaveCtrlCtrlData_tgPlayerMetaField;
igMetaField *g_beNDMWSaveCtrlCtrlData_isSelectMetaField;
igMetaField *g_beNDMWSaveCtrlCtrlData_st0MetaField;
igMetaField *g_beNDMWSaveCtrlCtrlData_st1MetaField;
igMetaField *g_beNDMWSaveCtrlCtrlData_st2MetaField;
igMetaField *g_beNDMWSaveCtrlCtrlData_st3MetaField;
igMetaEnum *g_beNDMWSaveCtrlCtrlData_messageMetaEnum;

void beNDMWSaveCtrlCtrlData_Create(int allocator) {
    beNDMWSaveCtrlCtrlData_EnsureRegistered();
    igMetaObject_CreateInstance(g_beNDMWSaveCtrlCtrlData_metaObject, allocator);
}

void *beNDMWSaveCtrlCtrlData_GetMetaObject(void) {
    igMetaObject *g = g_beNDMWSaveCtrlCtrlData_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false) {
        beNDMWSaveCtrlCtrlData_EnsureRegistered();
    }
    return g_beNDMWSaveCtrlCtrlData_metaObject;
}

int beNDMWSaveCtrlCtrlData_GetVTable(void) {
    union U_3bd140 u;
    int temp_s0;
    char *ps;
    int *temp_v1;
    int *temp_a1;
    int temp_v0;

    igObject_InitHeader(u.b);
    ps = &u.b[8];
    *(int *)ps = 0;
    u.vt = (int)&g_igNamedObject_vtable[0];
    u.vt = (int)&g_beNDMWSaveCtrlCtrlData_vtable[0];
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

void beNDMWSaveCtrlCtrlData_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(beNDMWSaveCtrlCtrlData_Register);
}

void *beNDMWSaveCtrlCtrlData_Register(void) {
    NdmwLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_beNDMWSaveCtrlCtrlData_metaObject,
        beBaseInfoData_Register,
        beBaseInfoData_GetPublishedMetaObject,
        beNDMWSaveCtrlCtrlData_GetMetaObjectFunction,
        "beNDMWSaveCtrlCtrlData",
        0x2c, /* instance size */
        beNDMWSaveCtrlCtrlData_GetVTable,
        beNDMWSaveCtrlCtrlData_InitFields,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void beNDMWSaveCtrlCtrlData_GetMetaObjectFunction(void)
{
    beNDMWSaveCtrlCtrlData_GetMetaObject();
}

static FieldFactory g_beNDMWSaveCtrlCtrlData_ctorTable[] = {
    igIntMetaField_Create,
    igIntMetaField_Create,
    igBoolMetaField_Create,
    igIntMetaField_Create,
    igIntMetaField_Create,
    igIntMetaField_Create,
    igIntMetaField_Create,
};
static const char *g_beNDMWSaveCtrlCtrlData_fieldTable[] = {
    "_order",
    "_tgPlayer",
    "_isSelect",
    "_st0",
    "_st1",
    "_st2",
    "_st3",
};
static igMetaField **g_beNDMWSaveCtrlCtrlData_fieldHandles[] = {
    &g_beNDMWSaveCtrlCtrlData_orderMetaField,
    &g_beNDMWSaveCtrlCtrlData_tgPlayerMetaField,
    &g_beNDMWSaveCtrlCtrlData_isSelectMetaField,
    &g_beNDMWSaveCtrlCtrlData_st0MetaField,
    &g_beNDMWSaveCtrlCtrlData_st1MetaField,
    &g_beNDMWSaveCtrlCtrlData_st2MetaField,
    &g_beNDMWSaveCtrlCtrlData_st3MetaField,
};
static int g_beNDMWSaveCtrlCtrlData_fieldOffsets[] = {
    16,
    20,
    24,
    28,
    32,
    36,
    40,
};

void beNDMWSaveCtrlCtrlData_InitFields(void) {
    int base;
    int nameIndex;
    void **inheritedName;
    void *meta;
    igStringMetaField *nameField;

    /* matching construct: variant search - the handle stays a void * (typed igMetaObject * swaps s0/s1) */

    meta = (void *)(g_beNDMWSaveCtrlCtrlData_metaObject);
    base = igMetaObject_GetFieldCount(meta);
    igMetaObject_CreateFields((igMetaObject *)meta, g_beNDMWSaveCtrlCtrlData_ctorTable, 7);
    inheritedName = (void **)(igMetaObject_FindFieldByName(meta, "_name"));
    nameIndex = ObjectPointerList_FindIndex(((igMetaObject *)meta)->_metaFields, inheritedName);
    nameField = (igStringMetaField *)(((DW4VC_84_1 *)(inheritedName))->vX((int)(1)));
    igStringMetaField_SetDefaultText(nameField, "CTRL");
    nameField->_externalEnumStorage = (int)(&g_beNDMWSaveCtrlCtrlData_nameExternalEnumStorage);
    igMetaObject_FinalizeAndReplaceField(meta, nameIndex, nameField);
    nameField->_refCount = nameField->_refCount - 1;
    if (((unsigned long long)(long long)nameField->_refCount & 0x7fffffULL) == 0) {
        igObject_Destroy(nameField);
    }
    igMetaObject_NameFields((igMetaObject *)meta, g_beNDMWSaveCtrlCtrlData_fieldTable, g_beNDMWSaveCtrlCtrlData_fieldHandles, g_beNDMWSaveCtrlCtrlData_fieldOffsets, base);
}

static const char *g_beNDMWSaveCtrlCtrlData_messageNames[] = {
    "GENERATE",
    "GENERATE_PS",
    "CLOSE_WIN",
    "GETCOMMON",
};
static int g_beNDMWSaveCtrlCtrlData_messageValues[] = {
    0,
    1,
    2,
    3,
};

igMetaEnum *SaveCtrlMessage_GetMetaEnum(void) {
    if (g_beNDMWSaveCtrlCtrlData_messageMetaEnum == 0) {
        g_beNDMWSaveCtrlCtrlData_messageMetaEnum = igMetaEnum_Create("Message", g_beNDMWSaveCtrlCtrlData_messageNames, g_beNDMWSaveCtrlCtrlData_messageValues, 4);
    }
    return g_beNDMWSaveCtrlCtrlData_messageMetaEnum;
}

