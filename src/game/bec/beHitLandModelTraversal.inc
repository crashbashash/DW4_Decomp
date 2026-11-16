igMetaObject *g_beHitLandModelTraversal_metaObject;
igMetaField *g_beHitLandModelTraversal_orderMetaField;

void beHitLandModelTraversal_Create(int arg0) {
    beHitLandModelTraversal_EnsureRegistered();
    igMetaObject_CreateInstance(*(int *)0x589380, arg0);
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
    union U_35dcb0 u;
    int t;
    char *ps;

    igObject_InitHeader(u.b);
    *(int *)&u.b[28] = 0;
    *(int *)&u.b[32] = 0;
    *(int *)&u.b[36] = 0;
    *(int *)&u.b[40] = 0;
    *(int *)&u.b[52] = 0;
    *(int *)&u.b[56] = 0;
    u.vt = (int)&g_beHitLandModelTraversal_vtable[0];
    ps = &u.b[64];
    *(int *)ps = 0;
    t = *(int *)&u.b[*(int *)((char *)(g_objectSystem[0]) + 916)];
    u.vt = (int)&g_beHitLandModelTraversal_vtable[0];
    FUN_0035d930((void **)ps, -1);
    FUN_0019e150(u.b, 0);
    return t;
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
    int temp_s2;
    void *temp_s1;
    void *temp_s0;

    temp_s0 = (void *)g_beHitLandModelTraversal_metaObject;
    temp_s2 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, g_beHitLandModelTraversal_ctorTable, 1);
    temp_s1 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2));
    ((igObjectRefMetaField *)temp_s1)->_metaObject = (int)beHitLandModelOrder_GetOrCreateMetaObject();
    igMetaObject_NameFields(temp_s0, g_beHitLandModelTraversal_fieldTable, g_beHitLandModelTraversal_fieldHandles, g_beHitLandModelTraversal_fieldOffsets, temp_s2);
}

