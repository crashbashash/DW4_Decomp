igMetaObject *g_beDataObjInt_metaObject;
igMetaField *g_beDataObjInt_dataMetaField;

beDataObjInt *beDataObjInt_Create(int allocator) {
    beDataObjInt_EnsureRegistered();
    return (beDataObjInt *)igMetaObject_CreateInstance(g_beDataObjInt_metaObject, (igMemoryPoolView *)allocator);
}

igMetaObject *beDataObjInt_GetOrCreateMetaObject(void) {
    if (g_beDataObjInt_metaObject == 0) {
        g_beDataObjInt_metaObject = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData));
    }
    return g_beDataObjInt_metaObject;
}

void *beDataObjInt_GetMetaObject(void) {
    igMetaObject *g = g_beDataObjInt_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false) {
        beDataObjInt_EnsureRegistered();
    }
    return g_beDataObjInt_metaObject;
}

int beDataObjInt_GetVTable(void) {
    beDataObjInt obj;
    int vtable;
    char **nameSlot;

    igObject_InitHeader(&obj);
    obj._vtable = (int)&g_igNamedObject_vtable[0];
    nameSlot = (char **)&obj._name;
    *nameSlot = 0;
    obj._vtable = (int)&g_beDataObjInt_vtable[0];
    vtable = *(int *)((char *)&obj + *(int *)((char *)g_objectSystem + 916));
    obj._vtable = (int)&g_igNamedObject_vtable[0];
    igStringRef_Release(nameSlot);
    return vtable;
}

void beDataObjInt_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(beDataObjInt_Register);
}

CallbackArray *beDataObjInt_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_beDataObjInt_metaObject,
        igNamedObject_Register,
        igNamedObject_GetPublishedMetaObject,
        beDataObjInt_GetMetaObjectFunction,
        "beDataObjInt",
        0x10, /* instance size */
        beDataObjInt_GetVTable,
        beDataObjInt_InitFields,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void beDataObjInt_GetMetaObjectFunction(void)
{
    beDataObjInt_GetMetaObject();
}

static FieldFactory g_beDataObjInt_ctorTable[] = {
    igIntMetaField_Create,
};
static const char *g_beDataObjInt_fieldTable[] = {
    "_data",
};
static igMetaField **g_beDataObjInt_fieldHandles[] = {
    &g_beDataObjInt_dataMetaField,
};
static int g_beDataObjInt_fieldOffsets[] = {
    12,
};

void beDataObjInt_InitFields(void) {
    int base;
    igMetaObject *meta;

    meta = g_beDataObjInt_metaObject;
    base = igMetaObject_GetFieldCount(meta);
    igMetaObject_CreateFields(meta, g_beDataObjInt_ctorTable, 1);
    igMetaObject_NameFields(meta, g_beDataObjInt_fieldTable, g_beDataObjInt_fieldHandles, g_beDataObjInt_fieldOffsets, base);
}

