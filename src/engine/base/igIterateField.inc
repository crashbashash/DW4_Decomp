igMetaObject *g_igIterateField_metaObject;
igMetaField *g_igIterateField_iteratedMetaField;
igMetaField *g_igIterateField_currentMetaField;

void *igIterateField_Create(int arg0) {
    FUN_002278a0();
    return igMetaObject_CreateInstance(g_igIterateField_metaObject, (igMemoryPoolView *)arg0);
}

igMetaObject *igIterateField_GetMetaObject(void)
{
    igMetaObject *g = g_igIterateField_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_002278a0();
    return g_igIterateField_metaObject;
}

int igIterateField_GetVTable(void) {
    union U_4 u;
    int t;
    char *ps;
    int *p;
    int *q;
    int v;
    igObject_InitHeader((igObject *)u.b);
    u.vt = (int)&g_igIterateField_vtable[0];
    ps = &u.b[8];
    *(int *)ps = 0;
    t = *(int *)&u.b[g_objectSystem->vtableProbeOffset];
    u.vt = (int)&g_igIterateField_vtable[0];
    if (ps != 0) {
        p = *(int **)ps;
        if (p != 0) {
            v = p[1] - 1;
            p[1] = v;
            if ((p[1] & 0x7fffff) == 0) {
                igObject_Destroy((igObject *)p);
            }
        }
    }
    return t;
}

void FUN_002278a0(void)
{
    igMetaObject_RunStaticInit((igMetaObjectRegisterFunction)igIterateField_Register);
}

static igMetaObjectCallback g_igIterateField_callbackList[] = { igMetaObject_EnsureRegistered, 0 };

CallbackArray *igIterateField_Register(void) {
    BaseLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_igIterateField_metaObject,
        (igMetaObjectRegisterFunction)igIterator_Register,
        (igMetaObjectGetFunction)igIterator_GetPublishedMetaObject,
        igIterateField_GetMetaObjectFunction,
        "igIterateField",
        0x10, /* instance size */
        igIterateField_GetVTable,
        &igIterateField_InitFields,
        0, /* extra callback item */
        (igMetaObjectCallback *)g_igIterateField_callbackList /* callback list */
    );
}

void igIterateField_GetMetaObjectFunction(void) {
    igIterateField_GetMetaObject();
}

static FieldFactory g_igIterateField_ctorTable[] = {
    (FieldFactory)igObjectRefMetaField_Create,
    (FieldFactory)igIntMetaField_Create,
};
static const char *g_igIterateField_fieldTable[] = {
    "_iterated",
    "_current",
};
static igMetaField **g_igIterateField_fieldHandles[] = {
    &g_igIterateField_iteratedMetaField,
    &g_igIterateField_currentMetaField,
};
static int g_igIterateField_fieldOffsets[] = {
    8,
    12,
};

void igIterateField_InitFields(void) {
    int base;
    void *field;
    igMetaObject *meta;

    meta = g_igIterateField_metaObject;
    base = igMetaObject_GetFieldCount(meta);
    igMetaObject_CreateFields(meta, g_igIterateField_ctorTable, 2);
    field = (void *)(igMetaObject_GetFieldAt(meta, base));
    ((igObjectRefMetaField *)field)->_metaObject = (int)igMetaObject_GetOrCreateMetaObject();
    igMetaObject_NameFields(meta, g_igIterateField_fieldTable, g_igIterateField_fieldHandles, g_igIterateField_fieldOffsets, base);
}

