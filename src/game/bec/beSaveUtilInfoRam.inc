igMetaObject *g_beSaveUtilInfoRam_metaObject;
igMetaField *g_beSaveUtilInfoRam_isRdyMetaField;
igMetaField *g_beSaveUtilInfoRam_deliverMetaField;

igMetaObject *beSaveUtilInfoRam_GetMetaObject(void) {
    if (g_beSaveUtilInfoRam_metaObject == 0 || !isValid(g_beSaveUtilInfoRam_metaObject)) beSaveUtilInfoRam_EnsureRegistered();
    return g_beSaveUtilInfoRam_metaObject;
}

int beSaveUtilInfoRam_GetVTable(void) {
    struct Obj_346860 obj;
    igObject *o;
    int *a1;
    int v0;
    int t;

    igObject_InitHeader(&obj);
    obj.w10 = 0;
    obj.vt = &g_beSaveUtilInfoRam_vtable[0];
    obj.w12 = 0;
    t = *(int *)((char *)&obj + *(int *)((char *)(g_objectSystem[0]) + 916));
    obj.vt = &g_beSaveUtilInfoRam_vtable[0];
    if (&obj.w12 != 0) {
        o = (igObject *)obj.w12;
        if (o != 0) {
            o->_refCount = o->_refCount - 1;
            if ((o->_refCount & 0x7FFFFF) == 0) {
                igObject_Destroy(o);
            }
        }
    }
    obj.vt = &g_beBaseInfoRam_vtable[0];
    if (&obj.w10 != 0) {
        o = (igObject *)obj.w10;
        if (o != 0) {
            o->_refCount = o->_refCount - 1;
            if ((o->_refCount & 0x7FFFFF) == 0) {
                igObject_Destroy(o);
            }
        }
    }
    return t;
}

void beSaveUtilInfoRam_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(beSaveUtilInfoRam_Register);
}

static igMetaObjectCallback g_beSaveUtilInfoRam_callbackList[] = { beSvDeliver_EnsureRegistered, 0 };

void *beSaveUtilInfoRam_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_beSaveUtilInfoRam_metaObject,
        beBaseInfoRam_Register,
        beBaseInfoRam_GetPublishedMetaObject,
        beSaveUtilInfoRam_GetMetaObjectFunction,
        "beSaveUtilInfoRam",
        0x34, /* instance size */
        beSaveUtilInfoRam_GetVTable,
        beSaveUtilInfoRam_InitFields,
        0, /* extra callback item */
        g_beSaveUtilInfoRam_callbackList /* callback list */
    );
}

void beSaveUtilInfoRam_GetMetaObjectFunction(void)
{
    beSaveUtilInfoRam_GetMetaObject();
}

static FieldFactory g_beSaveUtilInfoRam_ctorTable[] = {
    igBoolMetaField_Create,
    igObjectRefMetaField_Create,
};
static const char *g_beSaveUtilInfoRam_fieldTable[] = {
    "_isRdy",
    "_deliver",
};
static igMetaField **g_beSaveUtilInfoRam_fieldHandles[] = {
    &g_beSaveUtilInfoRam_isRdyMetaField,
    &g_beSaveUtilInfoRam_deliverMetaField,
};
static int g_beSaveUtilInfoRam_fieldOffsets[] = {
    44,
    48,
};

void beSaveUtilInfoRam_InitFields(void) {
    int temp_s2;
    void *temp_s1;
    void *temp_s0;

    temp_s0 = (void *)g_beSaveUtilInfoRam_metaObject;
    temp_s2 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, g_beSaveUtilInfoRam_ctorTable, 2);
    temp_s1 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 1));
    ((igObjectRefMetaField *)temp_s1)->_metaObject = (int)beSvDeliver_GetOrCreateMetaObject();
    ((igRefMetaField *)temp_s1)->_construct = 1;
    igMetaObject_NameFields(temp_s0, g_beSaveUtilInfoRam_fieldTable, g_beSaveUtilInfoRam_fieldHandles, g_beSaveUtilInfoRam_fieldOffsets, temp_s2);
}

