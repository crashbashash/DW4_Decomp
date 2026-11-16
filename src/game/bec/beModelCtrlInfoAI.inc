igMetaObject *g_beModelCtrlInfoAI_metaObject;
igMetaField *g_beModelCtrlInfoAI_seqNameMetaField;
igMetaField *g_beModelCtrlInfoAI_mapNoMetaField;
igMetaField *g_beModelCtrlInfoAI_worldPosMetaField;
igMetaField *g_beModelCtrlInfoAI_hStatusMetaField;
igMetaField *g_beModelCtrlInfoAI_hCountMetaField;

void beModelCtrlInfoAI_Create(int allocator) {
    beModelCtrlInfoAI_EnsureRegistered();
    igMetaObject_CreateInstance(*(int *)0x588AD0, allocator);
}

igMetaObject *beModelCtrlInfoAI_GetOrCreateMetaObject(void) {
    if (g_beModelCtrlInfoAI_metaObject == 0) {
        g_beModelCtrlInfoAI_metaObject = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData[0]));
    }
    return g_beModelCtrlInfoAI_metaObject;
}

void *beModelCtrlInfoAI_GetMetaObject(void) {
    igMetaObject *g = g_beModelCtrlInfoAI_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false) {
        beModelCtrlInfoAI_EnsureRegistered();
    }
    return g_beModelCtrlInfoAI_metaObject;
}

int beModelCtrlInfoAI_GetVTable(void) {
    beModelCtrlInfoAI obj;
    int vtable;
    char **seqNameSlot;

    igObject_InitHeader(&obj);
    obj._vtable = (int)&g_beModelCtrlInfoAI_vtable[0];
    seqNameSlot = (char **)&obj._seqName;
    *seqNameSlot = 0;
    vtable = *(int *)((char *)&obj + *(int *)((char *)(g_objectSystem[0]) + 916));
    obj._vtable = (int)&g_beModelCtrlInfoAI_vtable[0];
    igStringRef_Release(seqNameSlot);
    return vtable;
}

void beModelCtrlInfoAI_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(beModelCtrlInfoAI_Register);
}

void *beModelCtrlInfoAI_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_beModelCtrlInfoAI_metaObject,
        igObject_Register,
        igObject_GetMetaObject_ParentAccessor,
        beModelCtrlInfoAI_GetMetaObjectFunction,
        "beModelCtrlInfoAI",
        0x24, /* instance size */
        beModelCtrlInfoAI_GetVTable,
        beModelCtrlInfoAI_InitFields,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void beModelCtrlInfoAI_GetMetaObjectFunction(void)
{
    beModelCtrlInfoAI_GetMetaObject();
}

static FieldFactory g_beModelCtrlInfoAI_ctorTable[] = {
    igStringMetaField_Create,
    igIntMetaField_Create,
    igVec3fMetaField_CreateInstance,
    igIntMetaField_Create,
    igIntMetaField_Create,
};
static const char *g_beModelCtrlInfoAI_fieldTable[] = {
    "_seqName",
    "_mapNo",
    "_worldPos",
    "_hStatus",
    "_hCount",
};
static igMetaField **g_beModelCtrlInfoAI_fieldHandles[] = {
    &g_beModelCtrlInfoAI_seqNameMetaField,
    &g_beModelCtrlInfoAI_mapNoMetaField,
    &g_beModelCtrlInfoAI_worldPosMetaField,
    &g_beModelCtrlInfoAI_hStatusMetaField,
    &g_beModelCtrlInfoAI_hCountMetaField,
};
static int g_beModelCtrlInfoAI_fieldOffsets[] = {
    8,
    12,
    16,
    28,
    32,
};

void beModelCtrlInfoAI_InitFields(void) {
    int base;
    void *meta;

    meta = (void *)g_beModelCtrlInfoAI_metaObject;
    base = igMetaObject_GetFieldCount(meta);
    igMetaObject_CreateFields(meta, g_beModelCtrlInfoAI_ctorTable, 5);
    igMetaObject_NameFields(meta, g_beModelCtrlInfoAI_fieldTable, g_beModelCtrlInfoAI_fieldHandles, g_beModelCtrlInfoAI_fieldOffsets, base);
}

