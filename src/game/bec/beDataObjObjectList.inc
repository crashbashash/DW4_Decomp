igMetaObject *g_beDataObjObjectList_metaObject;
igMetaField *g_beDataObjObjectList_dataMetaField;

void beDataObjObjectList_Create(int arg0) {
    beDataObjObjectList_EnsureRegistered();
    igMetaObject_CreateInstance(*(int *)0x589858, arg0);
}

void *beDataObjObjectList_GetMetaObject(void) {
    igMetaObject *g = g_beDataObjObjectList_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false) {
        beDataObjObjectList_EnsureRegistered();
    }
    return g_beDataObjObjectList_metaObject;
}

int beDataObjObjectList_GetVTable(void) {
    Obj_364580 obj;
    int r;

    igObject_InitHeader(&obj);
    obj.r1 = 0;
    obj.vt = &g_beDataObjObjectList_vtable[0];
    obj.r2 = 0;
    r = *(int *)((char *)&obj + *(int *)((char *)(g_objectSystem[0]) + 916));
    obj.vt = &g_beDataObjObjectList_vtable[0];
    obj.rel2();
    obj.vt = &g_igNamedObject_vtable[0];
    obj.rel1();
    return r;
}

void beDataObjObjectList_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(beDataObjObjectList_Register);
}

static igMetaObjectCallback g_beDataObjObjectList_callbackList[] = { igObjectList_EnsureRegistered, 0 };

void *beDataObjObjectList_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_beDataObjObjectList_metaObject,
        igNamedObject_Register,
        igNamedObject_GetPublishedMetaObject,
        beDataObjObjectList_GetMetaObjectFunction,
        "beDataObjObjectList",
        0x10, /* instance size */
        beDataObjObjectList_GetVTable,
        beDataObjObjectList_InitFields,
        0, /* extra callback item */
        g_beDataObjObjectList_callbackList /* callback list */
    );
}

void beDataObjObjectList_GetMetaObjectFunction(void)
{
    beDataObjObjectList_GetMetaObject();
}

static FieldFactory g_beDataObjObjectList_ctorTable[] = {
    igObjectRefMetaField_Create,
};
static const char *g_beDataObjObjectList_fieldTable[] = {
    "_data",
};
static igMetaField **g_beDataObjObjectList_fieldHandles[] = {
    &g_beDataObjObjectList_dataMetaField,
};
static int g_beDataObjObjectList_fieldOffsets[] = {
    12,
};

void beDataObjObjectList_InitFields(void) {
    int temp_s2;
    void *temp_s1;
    void *temp_s0;

    temp_s0 = (void *)g_beDataObjObjectList_metaObject;
    temp_s2 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, g_beDataObjObjectList_ctorTable, 1);
    temp_s1 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2));
    ((igObjectRefMetaField *)temp_s1)->_metaObject = igObjectList_GetOrCreateMetaObject();
    ((igRefMetaField *)temp_s1)->_construct = 1;
    igMetaObject_NameFields(temp_s0, g_beDataObjObjectList_fieldTable, g_beDataObjObjectList_fieldHandles, g_beDataObjObjectList_fieldOffsets, temp_s2);
}

