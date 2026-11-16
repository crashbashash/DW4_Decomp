igMetaObject *g_igIterateField_metaObject;
igMetaField *g_igIterateField_iteratedMetaField;
igMetaField *g_igIterateField_currentMetaField;

void *FUN_00227780(int arg0) {
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
    t = *(int *)&u.b[*(int *)((char *)g_objectSystem + 916)];
    u.vt = (int)&g_igIterateField_vtable[0];
    if (ps != 0) {
        p = *(int **)ps;
        if (p != 0) {
            v = p[1] - 1;
            p[1] = v;
            if ((p[1] & 0x7fffff) == 0) {
                igObject_Destroy(p);
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
        thunk_igIterateField_GetMetaObject,
        "igIterateField",
        0x10, /* instance size */
        igIterateField_GetVTable,
        &igIterateField_InitFields,
        0, /* extra callback item */
        (igMetaObjectCallback *)g_igIterateField_callbackList /* callback list */
    );
}

void thunk_igIterateField_GetMetaObject(void) {
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
    int temp_s2;
    void *temp_s1;
    igMetaObject *temp_s0;

    temp_s0 = g_igIterateField_metaObject;
    temp_s2 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, g_igIterateField_ctorTable, 2);
    temp_s1 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2));
    ((igObjectRefMetaField *)temp_s1)->_metaObject = (int)igMetaObject_GetOrCreateMetaObject();
    igMetaObject_NameFields(temp_s0, g_igIterateField_fieldTable, g_igIterateField_fieldHandles, g_igIterateField_fieldOffsets, temp_s2);
}

