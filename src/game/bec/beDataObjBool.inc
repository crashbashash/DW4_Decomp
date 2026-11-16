igMetaObject *g_beDataObjBool_metaObject;
igMetaField *g_beDataObjBool_dataMetaField;

beDataObjBool *beDataObjBool_Create(int allocator) {
    beDataObjBool_EnsureRegistered();
    return (beDataObjBool *)igMetaObject_CreateInstance(*(int *)0x589898, allocator);
}

void *beDataObjBool_GetMetaObject(void) {
    igMetaObject *g = g_beDataObjBool_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false) {
        beDataObjBool_EnsureRegistered();
    }
    return g_beDataObjBool_metaObject;
}

int beDataObjBool_GetVTable(void) {
    beDataObjBool obj;
    int r;
    char **nameSlot;

    igObject_InitHeader(&obj);
    obj._vtable = (int)&g_igNamedObject_vtable[0];
    nameSlot = (char **)&obj._name;
    *nameSlot = 0;
    obj._vtable = (int)&g_beDataObjBool_vtable[0];
    r = *(int *)((char *)&obj + *(int *)(((char * *)g_objectSystem)[0] + 916));
    obj._vtable = (int)&g_igNamedObject_vtable[0];
    igStringRef_Release(nameSlot);
    return r;
}

void beDataObjBool_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(beDataObjBool_Register);
}

void *beDataObjBool_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_beDataObjBool_metaObject,
        igNamedObject_Register,
        igNamedObject_GetPublishedMetaObject,
        beDataObjBool_GetMetaObjectFunction,
        "beDataObjBool",
        0x10, /* instance size */
        beDataObjBool_GetVTable,
        beDataObjBool_InitFields,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void beDataObjBool_GetMetaObjectFunction(void)
{
    beDataObjBool_GetMetaObject();
}

static FieldFactory g_beDataObjBool_ctorTable[] = {
    igBoolMetaField_Create,
};
static const char *g_beDataObjBool_fieldTable[] = {
    "_data",
};
static igMetaField **g_beDataObjBool_fieldHandles[] = {
    &g_beDataObjBool_dataMetaField,
};
static int g_beDataObjBool_fieldOffsets[] = {
    12,
};

void beDataObjBool_InitFields(void) {
    int base;
    void *meta;

    meta = (void *)g_beDataObjBool_metaObject;
    base = igMetaObject_GetFieldCount(meta);
    igMetaObject_CreateFields(meta, g_beDataObjBool_ctorTable, 1);
    igMetaObject_NameFields(meta, g_beDataObjBool_fieldTable, g_beDataObjBool_fieldHandles, g_beDataObjBool_fieldOffsets, base);
}

