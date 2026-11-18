igMetaObject *g_beModelCtrlMOVERL_metaObject;
igMetaField *g_beModelCtrlMOVERL_modelNameMetaField;
igMetaField *g_beModelCtrlMOVERL_boneNameMetaField;

void *beModelCtrlMOVERL_GetMetaObject(void) {
    igMetaObject *g = g_beModelCtrlMOVERL_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false) {
        beModelCtrlMOVERL_EnsureRegistered();
    }
    return g_beModelCtrlMOVERL_metaObject;
}

int beModelCtrlMOVERL_GetVTable(void) {
    beModelCtrlMOVERL obj;
    int vtable;
    char **boneNameSlot;
    char **modelNameSlot;
    char **nameSlot;

    igObject_InitHeader(&obj);
    nameSlot = (char **)&obj._name;
    *nameSlot = 0;
    obj._vtable = (int)&g_beModelCtrlMOVERL_vtable[0];
    modelNameSlot = (char **)&obj._modelName;
    *modelNameSlot = 0;
    boneNameSlot = (char **)&obj._boneName;
    *boneNameSlot = 0;
    vtable = *(int *)((char *)&obj + g_objectSystem->vtableProbeOffset);
    obj._vtable = (int)&g_beModelCtrlMOVERL_vtable[0];
    igStringRef_Release(boneNameSlot);
    igStringRef_Release(modelNameSlot);
    obj._vtable = (int)&g_igNamedObject_vtable[0];
    igStringRef_Release(nameSlot);
    return vtable;
}

void beModelCtrlMOVERL_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(beModelCtrlMOVERL_Register);
}

CallbackArray *beModelCtrlMOVERL_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_beModelCtrlMOVERL_metaObject,
        igNamedObject_Register,
        igNamedObject_GetPublishedMetaObject,
        beModelCtrlMOVERL_GetMetaObjectFunction,
        "beModelCtrlMOVERL",
        0x14, /* instance size */
        beModelCtrlMOVERL_GetVTable,
        beModelCtrlMOVERL_InitFields,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void beModelCtrlMOVERL_GetMetaObjectFunction(void)
{
    beModelCtrlMOVERL_GetMetaObject();
}

static FieldFactory g_beModelCtrlMOVERL_ctorTable[] = {
    igStringMetaField_Create,
    igStringMetaField_Create,
};
static const char *g_beModelCtrlMOVERL_fieldTable[] = {
    "_modelName",
    "_boneName",
};
static igMetaField **g_beModelCtrlMOVERL_fieldHandles[] = {
    &g_beModelCtrlMOVERL_modelNameMetaField,
    &g_beModelCtrlMOVERL_boneNameMetaField,
};
static int g_beModelCtrlMOVERL_fieldOffsets[] = {
    12,
    16,
};

void beModelCtrlMOVERL_InitFields(void) {
    int base;
    igMetaObject *meta;

    meta = g_beModelCtrlMOVERL_metaObject;
    base = igMetaObject_GetFieldCount(meta);
    igMetaObject_CreateFields(meta, g_beModelCtrlMOVERL_ctorTable, 2);
    igMetaObject_NameFields(meta, g_beModelCtrlMOVERL_fieldTable, g_beModelCtrlMOVERL_fieldHandles, g_beModelCtrlMOVERL_fieldOffsets, base);
}

