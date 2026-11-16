igMetaObject *g_beCameraCtrlInfo_metaObject;
igMetaField *g_beCameraCtrlInfo_dataMetaField;

void *beCameraCtrlInfo_GetMetaObject(void) {
    igMetaObject *g = g_beCameraCtrlInfo_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false) {
        beCameraCtrlInfo_EnsureRegistered();
    }
    return g_beCameraCtrlInfo_metaObject;
}

int beCameraCtrlInfo_GetVTable(void) {
    struct Obj_368db0 obj;
    int temp_s0;

    igObject_InitHeader(&obj);
    obj.f8 = 0;
    obj.f14 = 0;
    obj.f18 = 0;
    obj.vt = (&g_beCameraCtrlInfo_vtable[0]);
    obj.f1C = 0;
    temp_s0 = *(int *)((char *)&obj + *(int *)((char *)(g_objectSystem[0]) + 916));
    obj.vt = (&g_beCameraCtrlInfo_vtable[0]);
    ObjectRef_Destruct_001363f0(&obj.f1C, -1);
    FUN_0033ec80((struct S_33ec80 *)&obj, (short)0);
    return temp_s0;
}

void beCameraCtrlInfo_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(beCameraCtrlInfo_Register);
}

static igMetaObjectCallback g_beCameraCtrlInfo_callbackList[] = { igObject_EnsureRegistered, 0 };

void *beCameraCtrlInfo_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_beCameraCtrlInfo_metaObject,
        beBaseInfo_Register,
        beBaseInfo_GetPublishedMetaObject,
        beCameraCtrlInfo_GetMetaObjectFunction,
        "beCameraCtrlInfo",
        0x20, /* instance size */
        beCameraCtrlInfo_GetVTable,
        beCameraCtrlInfo_InitFields,
        0, /* extra callback item */
        g_beCameraCtrlInfo_callbackList /* callback list */
    );
}

void beCameraCtrlInfo_GetMetaObjectFunction(void)
{
    beCameraCtrlInfo_GetMetaObject();
}

static FieldFactory g_beCameraCtrlInfo_ctorTable[] = {
    igObjectRefMetaField_Create,
};
static const char *g_beCameraCtrlInfo_fieldTable[] = {
    "_data",
};
static igMetaField **g_beCameraCtrlInfo_fieldHandles[] = {
    &g_beCameraCtrlInfo_dataMetaField,
};
static int g_beCameraCtrlInfo_fieldOffsets[] = {
    28,
};

void beCameraCtrlInfo_InitFields(void) {
    int base;
    void *f;
    void *meta;

    meta = (void *)g_beCameraCtrlInfo_metaObject;
    base = igMetaObject_GetFieldCount(meta);
    igMetaObject_CreateFields(meta, g_beCameraCtrlInfo_ctorTable, 1);
    f = igMetaObject_GetFieldAt(meta, base);
    ((igObjectRefMetaField *)f)->_metaObject = g_igObject_metaObject[0];
    igMetaObject_NameFields(meta, g_beCameraCtrlInfo_fieldTable, g_beCameraCtrlInfo_fieldHandles, g_beCameraCtrlInfo_fieldOffsets, base);
}

