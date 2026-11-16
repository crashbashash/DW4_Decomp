igMetaObject *g_beDataObjIntList_metaObject;
igMetaField *g_beDataObjIntList_dataMetaField;

void beDataObjIntList_Create(int arg0) {
    beDataObjIntList_EnsureRegistered();
    igMetaObject_CreateInstance(*(int *)0x5898A8, arg0);
}

void *beDataObjIntList_GetMetaObject(void) {
    igMetaObject *g = g_beDataObjIntList_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false) {
        beDataObjIntList_EnsureRegistered();
    }
    return g_beDataObjIntList_metaObject;
}

int beDataObjIntList_GetVTable(void) {
    Obj_3652d0 obj;
    int r;

    igObject_InitHeader(&obj);
    obj.m8 = 0;
    obj.vt = &g_beDataObjIntList_vtable[0];
    obj.m12 = 0;
    r = *(int *)((char *)&obj + *(int *)((char *)(g_objectSystem[0]) + 916));
    obj.vt = &g_beDataObjIntList_vtable[0];
    obj.rel12();
    obj.vt = &g_igNamedObject_vtable[0];
    obj.rel8();
    return r;
}

void beDataObjIntList_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(beDataObjIntList_Register);
}

static igMetaObjectCallback g_beDataObjIntList_callbackList[] = { igIntList_EnsureRegistered, 0 };

void *beDataObjIntList_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_beDataObjIntList_metaObject,
        igNamedObject_Register,
        igNamedObject_GetPublishedMetaObject,
        beDataObjIntList_GetMetaObjectFunction,
        "beDataObjIntList",
        0x10, /* instance size */
        beDataObjIntList_GetVTable,
        beDataObjIntList_InitFields,
        0, /* extra callback item */
        g_beDataObjIntList_callbackList /* callback list */
    );
}

void beDataObjIntList_GetMetaObjectFunction(void)
{
    beDataObjIntList_GetMetaObject();
}

static FieldFactory g_beDataObjIntList_ctorTable[] = {
    igObjectRefMetaField_Create,
};
static const char *g_beDataObjIntList_fieldTable[] = {
    "_data",
};
static igMetaField **g_beDataObjIntList_fieldHandles[] = {
    &g_beDataObjIntList_dataMetaField,
};
static int g_beDataObjIntList_fieldOffsets[] = {
    12,
};

void beDataObjIntList_InitFields(void) {
    int temp_s2;
    void *temp_s1;
    void *temp_s0;

    temp_s0 = (void *)g_beDataObjIntList_metaObject;
    temp_s2 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, g_beDataObjIntList_ctorTable, 1);
    temp_s1 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2));
    ((igObjectRefMetaField *)temp_s1)->_metaObject = igIntList_GetOrCreateMetaObject();
    ((igRefMetaField *)temp_s1)->_construct = 1;
    igMetaObject_NameFields(temp_s0, g_beDataObjIntList_fieldTable, g_beDataObjIntList_fieldHandles, g_beDataObjIntList_fieldOffsets, temp_s2);
}

