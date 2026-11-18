igMetaObject *g_igSerialScheduler_metaObject;
igMetaField *g_igSerialScheduler_managerListMetaField;
igMetaField *g_igSerialScheduler_cachedManagerListMetaField;

igMetaObject *igSerialScheduler_GetMetaObject(void)
{
    igMetaObject *g = g_igSerialScheduler_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false)
        igSerialScheduler_EnsureRegistered();
    return g_igSerialScheduler_metaObject;
}

int igSerialScheduler_GetVTable(void) {
    Obj obj;
    int r;

    igObject_InitHeader((igObject *)&obj);
    obj.vt = &g_igSerialScheduler_vtable[0];
    obj.m8 = 0;
    obj.m12 = 0;
    r = *(int *)((char *)&obj + g_objectSystem->vtableProbeOffset);
    obj.vt = &g_igSerialScheduler_vtable[0];
    obj.rel12();
    obj.rel8();
    return r;
}

void **igSmartPointer_igInfoManagerOrderedList_Destruct(void **arg0, long long arg1) {
    char *o;

    if (arg0 != 0) {
        o = (char *)*arg0;
        if (o != 0) {
            *(int *)(o + 4) = *(int *)(o + 4) - 1;
            if ((*(int *)(o + 4) & 0x7FFFFF) == 0) {
                igObject_Destroy((igObject *)o);
            }
        }
        if ((short)arg1 > 0) {
            operator delete(arg0);
        }
    }
    return arg0;
}

void igSerialScheduler_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(igSerialScheduler_Register);
}

static igMetaObjectCallback g_igSerialScheduler_callbackList[] = { igInfoManagerOrderedList_EnsureRegistered, igInfoManagerList_EnsureRegistered, 0 };

CallbackArray *igSerialScheduler_Register(void) {
    InsightLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_igSerialScheduler_metaObject,
        igInsightScheduler_Register,
        igInsightScheduler_GetPublishedMetaObject,
        igSerialScheduler_GetMetaObjectFunction,
        "igSerialScheduler",
        0x10, /* instance size */
        igSerialScheduler_GetVTable,
        &igSerialScheduler_InitFields,
        0, /* extra callback item */
        g_igSerialScheduler_callbackList /* callback list */
    );
}

void igSerialScheduler_GetMetaObjectFunction(void) {
    igSerialScheduler_GetMetaObject();
}

igMetaObject *igInsightScheduler_GetPublishedMetaObject(void) {
    return g_igInsightScheduler_metaObject;
}

static FieldFactory g_igSerialScheduler_ctorTable[] = {
    igObjectRefMetaField_Create,
    igObjectRefMetaField_Create,
};
static const char *g_igSerialScheduler_fieldTable[] = {
    "_managerList",
    "_cachedManagerList",
};
static igMetaField **g_igSerialScheduler_fieldHandles[] = {
    &g_igSerialScheduler_managerListMetaField,
    &g_igSerialScheduler_cachedManagerListMetaField,
};
static int g_igSerialScheduler_fieldOffsets[] = {
    8,
    12,
};

void igSerialScheduler_InitFields(void) {
    int temp_s2;
    void *temp_s1_2;
    void *temp_s1;
    igMetaObject *temp_s0;

    temp_s0 = g_igSerialScheduler_metaObject;
    temp_s2 = igMetaObject_GetFieldCount((igMetaObject *)temp_s0);
    igMetaObject_CreateFields((igMetaObject *)temp_s0, g_igSerialScheduler_ctorTable, 2);
    temp_s1 = (void *)(igMetaObject_GetFieldAt((igMetaObject *)temp_s0, temp_s2));
    ((igObjectRefMetaField *)temp_s1)->_metaObject = (int)igInfoManagerOrderedList_GetOrCreateMetaObject();
    ((igRefMetaField *)temp_s1)->_construct = 1;
    temp_s1_2 = (void *)(igMetaObject_GetFieldAt((igMetaObject *)temp_s0, temp_s2 + 1));
    ((igObjectRefMetaField *)temp_s1_2)->_metaObject = (int)igInfoManagerList_GetOrCreateMetaObject();
    ((igRefMetaField *)temp_s1_2)->_construct = 1;
    igMetaObject_NameFields((igMetaObject *)temp_s0, g_igSerialScheduler_fieldTable, g_igSerialScheduler_fieldHandles, g_igSerialScheduler_fieldOffsets, temp_s2);
}

