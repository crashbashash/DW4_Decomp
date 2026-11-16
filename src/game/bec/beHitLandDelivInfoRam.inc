igMetaObject *g_beHitLandDelivInfoRam_metaObject;
igMetaField *g_beHitLandDelivInfoRam_transformMetaField;
igMetaField *g_beHitLandDelivInfoRam_checkFlagMetaField;
igMetaField *g_beHitLandDelivInfoRam_halfWidthMetaField;
igMetaField *g_beHitLandDelivInfoRam_upRangeMetaField;
igMetaField *g_beHitLandDelivInfoRam_downRangeMetaField;
igMetaField *g_beHitLandDelivInfoRam_posMetaField;
igMetaField *g_beHitLandDelivInfoRam_oldPosMetaField;
igMetaField *g_beHitLandDelivInfoRam_landPosMetaField;
igMetaField *g_beHitLandDelivInfoRam_landPosOKMetaField;

void *beHitLandDelivInfoRam_GetMetaObject(void) {
    igMetaObject *g = g_beHitLandDelivInfoRam_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false) {
        beHitLandDelivInfoRam_EnsureRegistered();
    }
    return g_beHitLandDelivInfoRam_metaObject;
}

int beHitLandDelivInfoRam_GetVTable(void) {
    union U_35e6b0 u;
    int temp_s0;
    igObject *q0;
    igObject *q1;

    igObject_InitHeader(u.b);
    q1 = (igObject *)&u.b[40];
    *(int *)q1 = 0;
    u.vt = (int)&g_beHitLandDelivInfoRam_vtable[0];
    q0 = (igObject *)&u.b[44];
    *(int *)q0 = 0;
    temp_s0 = *(int *)&u.b[*(int *)((char *)(g_objectSystem[0]) + 916)];
    u.vt = (int)&g_beHitLandDelivInfoRam_vtable[0];
    if (q0 != 0) {
        q0 = *(igObject **)q0;
        if (q0 != 0) {
            q0->_refCount = (int)q0->_refCount - 1;
            if (((unsigned long long) ((long long)(int)q0->_refCount << 0x29) >> 0x29) == 0) {
                igObject_Destroy(q0);
            }
        }
    }
    u.vt = (int)&g_beBaseInfoRam_vtable[0];
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

void beHitLandDelivInfoRam_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(beHitLandDelivInfoRam_Register);
}

static igMetaObjectCallback g_beHitLandDelivInfoRam_callbackList[] = { igTransform_EnsureRegistered, 0 };

void *beHitLandDelivInfoRam_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_beHitLandDelivInfoRam_metaObject,
        beBaseInfoRam_Register,
        beBaseInfoRam_GetPublishedMetaObject,
        beHitLandDelivInfoRam_GetMetaObjectFunction,
        "beHitLandDelivInfoRam",
        0x68, /* instance size */
        beHitLandDelivInfoRam_GetVTable,
        beHitLandDelivInfoRam_InitFields,
        0, /* extra callback item */
        g_beHitLandDelivInfoRam_callbackList /* callback list */
    );
}

void beHitLandDelivInfoRam_GetMetaObjectFunction(void)
{
    beHitLandDelivInfoRam_GetMetaObject();
}

static FieldFactory g_beHitLandDelivInfoRam_ctorTable[] = {
    igObjectRefMetaField_Create,
    igIntMetaField_Create,
    igFloatMetaField_Create,
    igFloatMetaField_Create,
    igFloatMetaField_Create,
    FUN_00187890,
    FUN_00187890,
    FUN_00187890,
    igBoolMetaField_Create,
};
static const char *g_beHitLandDelivInfoRam_fieldTable[] = {
    "_transform",
    "_checkFlag",
    "_halfWidth",
    "_upRange",
    "_downRange",
    "_pos",
    "_oldPos",
    "_landPos",
    "_landPosOK",
};
static igMetaField **g_beHitLandDelivInfoRam_fieldHandles[] = {
    &g_beHitLandDelivInfoRam_transformMetaField,
    &g_beHitLandDelivInfoRam_checkFlagMetaField,
    &g_beHitLandDelivInfoRam_halfWidthMetaField,
    &g_beHitLandDelivInfoRam_upRangeMetaField,
    &g_beHitLandDelivInfoRam_downRangeMetaField,
    &g_beHitLandDelivInfoRam_posMetaField,
    &g_beHitLandDelivInfoRam_oldPosMetaField,
    &g_beHitLandDelivInfoRam_landPosMetaField,
    &g_beHitLandDelivInfoRam_landPosOKMetaField,
};
static int g_beHitLandDelivInfoRam_fieldOffsets[] = {
    44,
    48,
    52,
    56,
    60,
    64,
    76,
    88,
    100,
};

void beHitLandDelivInfoRam_InitFields(void) {
    void *pos;
    int base;
    void *transform;
    int va[3];
    int vb[3];
    int vc[3];
    void *landPos;
    void *oldPos;
    void *meta;

    meta = (void *)g_beHitLandDelivInfoRam_metaObject;
    base = igMetaObject_GetFieldCount(meta);
    igMetaObject_CreateFields(meta, g_beHitLandDelivInfoRam_ctorTable, 9);
    transform = (void *)(igMetaObject_GetFieldAt(meta, base));
    ((igObjectRefMetaField *)transform)->_metaObject = igTransform_GetOrCreateMetaObject();
    igFloatMetaField_SetDefault(igMetaObject_GetFieldAt(meta, base + 2), 3.0f);
    igFloatMetaField_SetDefault(igMetaObject_GetFieldAt(meta, 3 + base), 4.0f);
    igFloatMetaField_SetDefault(igMetaObject_GetFieldAt(meta, 4 + base), 4.0f);
    pos = (void *)(igMetaObject_GetFieldAt(meta, base + 5));
    va[0] = 0;
    va[1] = 0;
    va[2] = 0;
    FUN_0018e470(pos, va);
    oldPos = (void *)(igMetaObject_GetFieldAt(meta, 6 + base));
    vb[0] = 0;
    vb[1] = 0;
    vb[2] = 0;
    FUN_0018e470(oldPos, vb);
    landPos = (void *)(igMetaObject_GetFieldAt(meta, 7 + base));
    vc[0] = 0;
    vc[1] = 0;
    vc[2] = 0;
    FUN_0018e470(landPos, vc);
    igMetaObject_NameFields(meta, g_beHitLandDelivInfoRam_fieldTable, g_beHitLandDelivInfoRam_fieldHandles, g_beHitLandDelivInfoRam_fieldOffsets, base);
}

