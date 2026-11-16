igMetaObject *g_beCameraCtrlInfoRamShake_metaObject;
int g_beCameraCtrlInfoRamShake_nameStorage;
igMetaField *g_beCameraCtrlInfoRamShake_isFirstMetaField;
igMetaField *g_beCameraCtrlInfoRamShake_svEyePosMetaField;
igMetaField *g_beCameraCtrlInfoRamShake_svIntPosMetaField;
igMetaField *g_beCameraCtrlInfoRamShake_moveCodeMetaField;
igMetaField *g_beCameraCtrlInfoRamShake_valueMetaField;
igMetaField *g_beCameraCtrlInfoRamShake_oneTimeMetaField;
igMetaField *g_beCameraCtrlInfoRamShake_endTimeMetaField;
igMetaField *g_beCameraCtrlInfoRamShake_movePointMetaField;

void beCameraCtrlInfoRamShake_Create(int allocator) {
    beCameraCtrlInfoRamShake_EnsureRegistered();
    igMetaObject_CreateInstance(*(int *)0x589C38, allocator);
}

void *beCameraCtrlInfoRamShake_GetMetaObject(void) {
    unsigned char b;
    if (g_beCameraCtrlInfoRamShake_metaObject != 0) {
        b = (g_beCameraCtrlInfoRamShake_metaObject->_validity & 4) != 0;
        if (b != 0) goto done;
    }
    beCameraCtrlInfoRamShake_EnsureRegistered();
done:
    return g_beCameraCtrlInfoRamShake_metaObject;
}

int beCameraCtrlInfoRamShake_GetVTable(void) {
    union U_369530 u;
    int t;
    char *o;
    int *a1;
    int v0;
    igObject *p0, *p1;

    igObject_InitHeader(u.b);
    p0 = (igObject *)&u.b[8];
    *(int *)p0 = 0;
    u.vt = (int)&g_beCameraCtrlInfoRamShake_vtable[0];
    p1 = (igObject *)&u.b[44];
    *(int *)p1 = 0;
    t = *(int *)&u.b[*(int *)((char *)(g_objectSystem[0]) + 916)];
    u.vt = (int)&g_beCameraCtrlInfoRamShake_vtable[0];
    if (p1 != 0) {
        o = *(char **)p1;
        if (o != 0) {
            a1 = (int *)(o - 8);
            v0 = *(int *)(o - 4) - 1;
            *(int *)(o - 4) = v0;
            if (v0 == 0) {
                StringChunk_ReleaseHeader(*a1, a1);
            }
        }
    }
    u.vt = (int)&g_igNamedObject_vtable[0];
    if (p0 != 0) {
        o = *(char **)p0;
        if (o != 0) {
            a1 = (int *)(o - 8);
            v0 = *(int *)(o - 4) - 1;
            *(int *)(o - 4) = v0;
            if (v0 == 0) {
                StringChunk_ReleaseHeader(*a1, a1);
            }
        }
    }
    return t;
}

void beCameraCtrlInfoRamShake_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(beCameraCtrlInfoRamShake_Register);
}

void *beCameraCtrlInfoRamShake_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_beCameraCtrlInfoRamShake_metaObject,
        beBaseInfoData_Register,
        beBaseInfoData_GetPublishedMetaObject,
        beCameraCtrlInfoRamShake_GetMetaObjectFunction,
        "beCameraCtrlInfoRamShake",
        0x40, /* instance size */
        beCameraCtrlInfoRamShake_GetVTable,
        beCameraCtrlInfoRamShake_InitFields,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void beCameraCtrlInfoRamShake_GetMetaObjectFunction(void)
{
    beCameraCtrlInfoRamShake_GetMetaObject();
}

static FieldFactory g_beCameraCtrlInfoRamShake_ctorTable[] = {
    igBoolMetaField_Create,
    FUN_00187890,
    FUN_00187890,
    igStringMetaField_Create,
    igFloatMetaField_Create,
    igFloatMetaField_Create,
    igFloatMetaField_Create,
    igIntMetaField_Create,
};
static const char *g_beCameraCtrlInfoRamShake_fieldTable[] = {
    "_isFirst",
    "_svEyePos",
    "_svIntPos",
    "_moveCode",
    "_value",
    "_oneTime",
    "_endTime",
    "_movePoint",
};
static igMetaField **g_beCameraCtrlInfoRamShake_fieldHandles[] = {
    &g_beCameraCtrlInfoRamShake_isFirstMetaField,
    &g_beCameraCtrlInfoRamShake_svEyePosMetaField,
    &g_beCameraCtrlInfoRamShake_svIntPosMetaField,
    &g_beCameraCtrlInfoRamShake_moveCodeMetaField,
    &g_beCameraCtrlInfoRamShake_valueMetaField,
    &g_beCameraCtrlInfoRamShake_oneTimeMetaField,
    &g_beCameraCtrlInfoRamShake_endTimeMetaField,
    &g_beCameraCtrlInfoRamShake_movePointMetaField,
};
static int g_beCameraCtrlInfoRamShake_fieldOffsets[] = {
    16,
    20,
    32,
    44,
    48,
    52,
    56,
    60,
};

void beCameraCtrlInfoRamShake_InitFields(void) {
    int base;
    int index;
    void **found;
    void *meta;
    igStringMetaField *clone;

    meta = (void *)g_beCameraCtrlInfoRamShake_metaObject;
    base = igMetaObject_GetFieldCount(meta);
    igMetaObject_CreateFields(meta, g_beCameraCtrlInfoRamShake_ctorTable, 8);
    found = (void **)(igMetaObject_FindFieldByName(meta, "_name"));
    index = ObjectPointerList_FindIndex(((igMetaObject *)meta)->_metaFields, found);
    clone = (igStringMetaField *)(((DW4VC_84_1 *)(found))->vX((int)(1)));
    igStringMetaField_SetDefaultText(clone, "SHK");
    clone->_externalEnumStorage = (int)(&g_beCameraCtrlInfoRamShake_nameStorage);
    igMetaObject_FinalizeAndReplaceField(meta, index, clone);
    clone->_refCount = (int)clone->_refCount - 1;
    if (((unsigned long long) ((long long)(int)clone->_refCount << 0x29) >> 0x29) == 0) {
        igObject_Destroy(clone);
    }
    igMetaObject_NameFields(meta, g_beCameraCtrlInfoRamShake_fieldTable, g_beCameraCtrlInfoRamShake_fieldHandles, g_beCameraCtrlInfoRamShake_fieldOffsets, base);
}

igMetaEnum *g_beCameraCtrlInfoRamShake_msgActionMetaEnum;
static const char *g_beCameraCtrlInfoRamShake_msgActionNames[] = {
    "SHOWPOLYGON", "HIDEPOLYGON", "GETPOSITION", "ENABLE",
    "DISABLE", "SETBOXCAMERA", "SETDEMOCAMERA", "GETDEMONAME",
    "ISDEMOCAMERA", "SHAKE", "ONFREEZE", "OFFREEZE",
    "DBGZOOMCLEAR", "DBGZOOMIN", "DBGZOOMOUT",
};
static int g_beCameraCtrlInfoRamShake_msgActionValues[] = {
    0, 1, 2, 3, 4, 5, 6, 7,
    8, 9, 0xa, 0xb, 0xc, 0xd, 0xe,
};

igMetaEnum *beCameraCtrl_GetMessageEnum(void) {
    if (g_beCameraCtrlInfoRamShake_msgActionMetaEnum == 0) {
        g_beCameraCtrlInfoRamShake_msgActionMetaEnum = igMetaEnum_Create("MsgAction", g_beCameraCtrlInfoRamShake_msgActionNames, g_beCameraCtrlInfoRamShake_msgActionValues, 0xF);
    }
    return g_beCameraCtrlInfoRamShake_msgActionMetaEnum;
}

