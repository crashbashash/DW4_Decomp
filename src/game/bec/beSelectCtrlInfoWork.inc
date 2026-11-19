igMetaObject *g_beSelectCtrlInfoWork_metaObject;
igMetaField *g_beSelectCtrlInfoWork_offsetPosMetaField;
igMetaField *g_beSelectCtrlInfoWork_selectMaxMetaField;
igMetaField *g_beSelectCtrlInfoWork_isCancelMetaField;
igMetaField *g_beSelectCtrlInfoWork_svSeqNameMetaField;
igMetaField *g_beSelectCtrlInfoWork_decideListMetaField;

beSelectCtrlInfoWork *beSelectCtrlInfoWork_Create(int allocator) {
    beSelectCtrlInfoWork_EnsureRegistered();
    return (beSelectCtrlInfoWork *)igMetaObject_CreateInstance(g_beSelectCtrlInfoWork_metaObject, (igMemoryPoolView *)allocator);
}

igMetaObject *beSelectCtrlInfoWork_GetOrCreateMetaObject(void) {
    if (g_beSelectCtrlInfoWork_metaObject == 0) {
        g_beSelectCtrlInfoWork_metaObject = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData));
    }
    return g_beSelectCtrlInfoWork_metaObject;
}

void *beSelectCtrlInfoWork_GetMetaObject(void) {
    igMetaObject *g = g_beSelectCtrlInfoWork_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false) {
        beSelectCtrlInfoWork_EnsureRegistered();
    }
    return g_beSelectCtrlInfoWork_metaObject;
}

int beSelectCtrlInfoWork_GetVTable(void) {
    beSelectCtrlInfoWork obj;
    int vtable;
    igObject **decideListSlot;
    char **svSeqNameSlot;

    igObject_InitHeader(&obj);
    svSeqNameSlot = (char **)&obj._svSeqName;
    decideListSlot = (igObject **)&obj._decideList;
    obj._vtable = (int)&g_beSelectCtrlInfoWork_vtable[0];
    *svSeqNameSlot = 0;
    *decideListSlot = 0;
    vtable = *(int *)((char *)&obj + g_objectSystem->vtableProbeOffset);
    obj._vtable = (int)&g_beSelectCtrlInfoWork_vtable[0];
    igObjectRef_Release(decideListSlot);
    igStringRef_Release(svSeqNameSlot);
    return vtable;
}

void beSelectCtrlInfoWork_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(beSelectCtrlInfoWork_Register);
}

static igMetaObjectCallback g_beSelectCtrlInfoWork_callbackList[] = { igBoolList_EnsureRegistered, 0 };

CallbackArray *beSelectCtrlInfoWork_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_beSelectCtrlInfoWork_metaObject,
        Gap::Core::igObject::arkRegisterInternal,
        igObject_GetMetaObject_ParentAccessor,
        beSelectCtrlInfoWork_GetMetaObjectFunction,
        "beSelectCtrlInfoWork",
        0x24, /* instance size */
        beSelectCtrlInfoWork_GetVTable,
        beSelectCtrlInfoWork_InitFields,
        0, /* extra callback item */
        g_beSelectCtrlInfoWork_callbackList /* callback list */
    );
}

void beSelectCtrlInfoWork_GetMetaObjectFunction(void)
{
    beSelectCtrlInfoWork_GetMetaObject();
}

static FieldFactory g_beSelectCtrlInfoWork_ctorTable[] = {
    igVec3fMetaField_CreateInstance,
    igIntMetaField_Create,
    igBoolMetaField_Create,
    igStringMetaField_Create,
    igObjectRefMetaField_Create,
};
static const char *g_beSelectCtrlInfoWork_fieldTable[] = {
    "_offsetPos",
    "_selectMax",
    "_isCancel",
    "_svSeqName",
    "_decideList",
};
static igMetaField **g_beSelectCtrlInfoWork_fieldHandles[] = {
    &g_beSelectCtrlInfoWork_offsetPosMetaField,
    &g_beSelectCtrlInfoWork_selectMaxMetaField,
    &g_beSelectCtrlInfoWork_isCancelMetaField,
    &g_beSelectCtrlInfoWork_svSeqNameMetaField,
    &g_beSelectCtrlInfoWork_decideListMetaField,
};
static int g_beSelectCtrlInfoWork_fieldOffsets[] = {
    8,
    20,
    24,
    28,
    32,
};

void beSelectCtrlInfoWork_InitFields(void) {
    int base;
    void *decideList;
    igMetaObject *meta;

    meta = g_beSelectCtrlInfoWork_metaObject;
    base = igMetaObject_GetFieldCount(meta);
    igMetaObject_CreateFields(meta, g_beSelectCtrlInfoWork_ctorTable, 5);
    igBoolMetaField_SetDefaultValue(igMetaObject_GetFieldAt(meta, base + 2), 1);
    decideList = (void *)(igMetaObject_GetFieldAt(meta, base + 4));
    ((igObjectRefMetaField *)decideList)->_metaObject = (int)igBoolList_GetOrCreateMetaObject();
    igMetaObject_NameFields(meta, g_beSelectCtrlInfoWork_fieldTable, g_beSelectCtrlInfoWork_fieldHandles, g_beSelectCtrlInfoWork_fieldOffsets, base);
}

igMetaEnum *g_beSelectCtrlInfoWork_msgActionMetaEnum;
static const char *g_beSelectCtrlInfoWork_msgActionNames[] = {
    "GENERATE", "ISEND", "GETSELECT", "ISSELECTNOW",
    "FO2TOP", "ISFO2TOP", "REMOVE",
};
static int g_beSelectCtrlInfoWork_msgActionValues[] = {
    0, 1, 2, 3, 4, 5, 6,
};

igMetaEnum *beSelectCtrl_GetMessageEnum(void) {
    if (g_beSelectCtrlInfoWork_msgActionMetaEnum == 0) {
        g_beSelectCtrlInfoWork_msgActionMetaEnum = igMetaEnum_Create("MsgAction", g_beSelectCtrlInfoWork_msgActionNames, g_beSelectCtrlInfoWork_msgActionValues, 7);
    }
    return g_beSelectCtrlInfoWork_msgActionMetaEnum;
}

