igMetaObject *g_beHitLandModelTraversal_metaObject;
igMetaField *g_beHitLandModelTraversal_orderMetaField;

beHitLandModelTraversal *beHitLandModelTraversal_Create(int allocator) {
    beHitLandModelTraversal_EnsureRegistered();
    return (beHitLandModelTraversal *)igMetaObject_CreateInstance(*(int *)0x589380, allocator);
}

igMetaObject *beHitLandModelTraversal_GetOrCreateMetaObject(void) {
    if (g_beHitLandModelTraversal_metaObject == 0) {
        g_beHitLandModelTraversal_metaObject = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData[0]));
    }
    return g_beHitLandModelTraversal_metaObject;
}

void *beHitLandModelTraversal_GetMetaObject(void) {
    igMetaObject *g = g_beHitLandModelTraversal_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false) {
        beHitLandModelTraversal_EnsureRegistered();
    }
    return g_beHitLandModelTraversal_metaObject;
}

int beHitLandModelTraversal_GetVTable(void) {
    beHitLandModelTraversal obj;
    int vtable;
    char *orderSlot;

    igObject_InitHeader(&obj);
    obj._travProcs = 0;
    obj._matStack = 0;
    obj._nodeStack = 0;
    obj._probe = 0;
    obj._volumes = 0;
    obj._ray = 0;
    obj._vtable = (int)&g_beHitLandModelTraversal_vtable[0];
    orderSlot = (char *)&obj._order;
    *(int *)orderSlot = 0;
    vtable = *(int *)((char *)&obj + *(int *)((char *)(g_objectSystem[0]) + 916));
    obj._vtable = (int)&g_beHitLandModelTraversal_vtable[0];
    igSmartPointer_beHitLandModelOrder_Destruct((igSmartPointer<igObject> *)orderSlot, -1);
    igIntersectTraversal_Destroy((igIntersectTraversal *)&obj, 0);
    return vtable;
}

void beHitLandModelTraversal_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(beHitLandModelTraversal_Register);
}

static igMetaObjectCallback g_beHitLandModelTraversal_callbackList[] = { beHitLandModelOrder_EnsureRegistered, 0 };

void *beHitLandModelTraversal_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_beHitLandModelTraversal_metaObject,
        igIntersectTraversal_Register,
        igIntersectTraversal_GetPublishedMetaObject,
        beHitLandModelTraversal_GetMetaObjectFunction,
        "beHitLandModelTraversal",
        0x48, /* instance size */
        beHitLandModelTraversal_GetVTable,
        beHitLandModelTraversal_InitFields,
        0, /* extra callback item */
        g_beHitLandModelTraversal_callbackList /* callback list */
    );
}

void beHitLandModelTraversal_GetMetaObjectFunction(void)
{
    beHitLandModelTraversal_GetMetaObject();
}

int igIntersectTraversal_GetPublishedMetaObject(void) {
    return g_igIntersectTraversal_metaObject[0];
}

static FieldFactory g_beHitLandModelTraversal_ctorTable[] = {
    igObjectRefMetaField_Create,
};
static const char *g_beHitLandModelTraversal_fieldTable[] = {
    "_order",
};
static igMetaField **g_beHitLandModelTraversal_fieldHandles[] = {
    &g_beHitLandModelTraversal_orderMetaField,
};
static int g_beHitLandModelTraversal_fieldOffsets[] = {
    64,
};

void beHitLandModelTraversal_InitFields(void) {
    int base;
    void *order;
    void *meta;

    meta = (void *)g_beHitLandModelTraversal_metaObject;
    base = igMetaObject_GetFieldCount(meta);
    igMetaObject_CreateFields(meta, g_beHitLandModelTraversal_ctorTable, 1);
    order = (void *)(igMetaObject_GetFieldAt(meta, base));
    ((igObjectRefMetaField *)order)->_metaObject = (int)beHitLandModelOrder_GetOrCreateMetaObject();
    igMetaObject_NameFields(meta, g_beHitLandModelTraversal_fieldTable, g_beHitLandModelTraversal_fieldHandles, g_beHitLandModelTraversal_fieldOffsets, base);
}

