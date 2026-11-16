igMetaObject *g_beNDMWLogoCtrlData_metaObject;
int g_beNDMWLogoCtrlData_nameExternalEnumStorage;
igMetaField *g_beNDMWLogoCtrlData_st0MetaField;
igMetaField *g_beNDMWLogoCtrlData_st1MetaField;
igMetaField *g_beNDMWLogoCtrlData_st2MetaField;
igMetaField *g_beNDMWLogoCtrlData_st3MetaField;
igMetaEnum *g_beNDMWLogoCtrlData_messageMetaEnum;

void beNDMWLogoCtrlData_Create(int allocator) {
    beNDMWLogoCtrlData_EnsureRegistered();
    igMetaObject_CreateInstance(g_beNDMWLogoCtrlData_metaObject, allocator);
}

void *beNDMWLogoCtrlData_GetReadyMetaObject(void) {
    unsigned char b;
    if (g_beNDMWLogoCtrlData_metaObject != 0) {
        b = (*(int *)((char *)(g_beNDMWLogoCtrlData_metaObject) + 36) & 4) != 0;
        if (b != 0) goto done;
    }
    beNDMWLogoCtrlData_EnsureRegistered();
done:
    return g_beNDMWLogoCtrlData_metaObject;
}

int beNDMWLogoCtrlData_GetVTable(void) {
    union U_3c2090 u;
    int s0;
    char *ps;
    int *v1;
    int *a1;
    int v0;

    igObject_InitHeader(u.b);
    ps = &u.b[8];
    *(int *)ps = 0;
    u.vt = (int)&g_igNamedObject_vtable[0];
    u.vt = (int)&g_beNDMWLogoCtrlData_vtable[0];
    s0 = *(int *)&u.b[*(int *)((char *)(g_objectSystem[0]) + 916)];
    u.vt = (int)&g_igNamedObject_vtable[0];
    if (ps != 0) {
        v1 = *(int **)ps;
        if (v1 != 0) {
            a1 = v1 - 2;
            v0 = v1[-1] - 1;
            v1[-1] = v0;
            if (v0 == 0) {
                StringChunk_ReleaseHeader(*a1, a1);
            }
        }
    }
    return s0;
}

void beNDMWLogoCtrlData_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(beNDMWLogoCtrlData_Register);
}

void *beNDMWLogoCtrlData_Register(void) {
    NdmwLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_beNDMWLogoCtrlData_metaObject,
        beBaseInfoData_Register,
        beBaseInfoData_GetPublishedMetaObject,
        beNDMWLogoCtrlData_GetMetaObject,
        "beNDMWLogoCtrlData",
        0x20, /* instance size */
        beNDMWLogoCtrlData_GetVTable,
        beNDMWLogoCtrlData_InitFields,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void beNDMWLogoCtrlData_GetMetaObject(void)
{
    beNDMWLogoCtrlData_GetReadyMetaObject();
}

static FieldFactory g_beNDMWLogoCtrlData_ctorTable[] = {
    igIntMetaField_Create,
    igIntMetaField_Create,
    igIntMetaField_Create,
    igIntMetaField_Create,
};
static const char *g_beNDMWLogoCtrlData_fieldTable[] = {
    "_st0",
    "_st1",
    "_st2",
    "_st3",
};
static igMetaField **g_beNDMWLogoCtrlData_fieldHandles[] = {
    &g_beNDMWLogoCtrlData_st0MetaField,
    &g_beNDMWLogoCtrlData_st1MetaField,
    &g_beNDMWLogoCtrlData_st2MetaField,
    &g_beNDMWLogoCtrlData_st3MetaField,
};
static int g_beNDMWLogoCtrlData_fieldOffsets[] = {
    16,
    20,
    24,
    28,
};

void beNDMWLogoCtrlData_InitFields(void) {
    int base;
    int nameIndex;
    void **inheritedName;
    void *meta;
    igStringMetaField *nameField;

    /* matching construct: variant search - the handle stays a void * (typed igMetaObject * swaps s0/s1) */

    meta = (void *)(g_beNDMWLogoCtrlData_metaObject);
    base = igMetaObject_GetFieldCount(meta);
    igMetaObject_CreateFields((igMetaObject *)meta, g_beNDMWLogoCtrlData_ctorTable, 4);
    inheritedName = (void **)(igMetaObject_FindFieldByName(meta, "_name"));
    nameIndex = ObjectPointerList_FindIndex(((igMetaObject *)meta)->_metaFields, inheritedName);
    nameField = (igStringMetaField *)(((DW4VC_84_1 *)(inheritedName))->vX((int)(1)));
    igStringMetaField_SetDefaultText(nameField, "CTRL");
    nameField->_externalEnumStorage = (int)(&g_beNDMWLogoCtrlData_nameExternalEnumStorage);
    igMetaObject_FinalizeAndReplaceField(meta, nameIndex, nameField);
    nameField->_refCount = nameField->_refCount - 1;
    if (((unsigned long long)(long long)nameField->_refCount & 0x7fffffULL) == 0) {
        igObject_Destroy(nameField);
    }
    igMetaObject_NameFields((igMetaObject *)meta, g_beNDMWLogoCtrlData_fieldTable, g_beNDMWLogoCtrlData_fieldHandles, g_beNDMWLogoCtrlData_fieldOffsets, base);
}

static const char *g_beNDMWLogoCtrlData_messageNames[] = {
    "RUN",
};
static int g_beNDMWLogoCtrlData_messageValues[] = {
    0,
};

igMetaEnum *beNDMWLogoCtrlData_GetMessageEnum(void) {
    if (g_beNDMWLogoCtrlData_messageMetaEnum == 0) {
        g_beNDMWLogoCtrlData_messageMetaEnum = igMetaEnum_Create("Message", g_beNDMWLogoCtrlData_messageNames, g_beNDMWLogoCtrlData_messageValues, 1);
    }
    return g_beNDMWLogoCtrlData_messageMetaEnum;
}

