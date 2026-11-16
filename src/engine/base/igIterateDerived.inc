igMetaObject *g_igIterateDerived_metaObject;
igMetaField *g_igIterateDerived_iteratedMetaField;
igMetaField *g_igIterateDerived_currentMetaField;

void *FUN_002279d0(int arg0) {
    FUN_00227af0();
    return igMetaObject_CreateInstance(g_igIterateDerived_metaObject, (igMemoryPoolView *)arg0);
}

igMetaObject *igIterateDerived_GetMetaObject(void)
{
    igMetaObject *g = g_igIterateDerived_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_00227af0();
    return g_igIterateDerived_metaObject;
}

int igIterateDerived_GetVTable(void) {
    struct F f;
    int **pr;
    int temp_s0;
    int *o;

    igObject_InitHeader((igObject *)&f);
    f.vt = &g_igIterateDerived_vtable[0];
    pr = &f.ref;
    *pr = 0;
    temp_s0 = *(int *)((char *)&f + *(int *)((char *)g_objectSystem + 916));
    f.vt = &g_igIterateDerived_vtable[0];
    if (pr != 0) {
        if (*pr != 0) {
            o = *pr;
            o[1] = o[1] - 1;
            if ((o[1] & 0x7FFFFF) == 0) {
                igObject_Destroy((igObject *)o);
            }
        }
    }
    return temp_s0;
}

void FUN_00227af0(void)
{
    igMetaObject_RunStaticInit((igMetaObjectRegisterFunction)igIterateDerived_Register);
}

static igMetaObjectCallback g_igIterateDerived_callbackList[] = { igMetaObject_EnsureRegistered, 0 };

CallbackArray *igIterateDerived_Register(void) {
    BaseLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_igIterateDerived_metaObject,
        (igMetaObjectRegisterFunction)igIterator_Register,
        (igMetaObjectGetFunction)igIterator_GetPublishedMetaObject,
        thunk_igIterateDerived_GetMetaObject,
        "igIterateDerived",
        0x10, /* instance size */
        igIterateDerived_GetVTable,
        &igIterateDerived_InitFields,
        0, /* extra callback item */
        (igMetaObjectCallback *)g_igIterateDerived_callbackList /* callback list */
    );
}

void thunk_igIterateDerived_GetMetaObject(void) {
    igIterateDerived_GetMetaObject();
}

static FieldFactory g_igIterateDerived_ctorTable[] = {
    (FieldFactory)igObjectRefMetaField_Create,
    (FieldFactory)igIntMetaField_Create,
};
static const char *g_igIterateDerived_fieldTable[] = {
    "_iterated",
    "_current",
};
static igMetaField **g_igIterateDerived_fieldHandles[] = {
    &g_igIterateDerived_iteratedMetaField,
    &g_igIterateDerived_currentMetaField,
};
static int g_igIterateDerived_fieldOffsets[] = {
    8,
    12,
};

void igIterateDerived_InitFields(void) {
    int temp_s2;
    void *temp_s1;
    igMetaObject *temp_s0;

    temp_s0 = g_igIterateDerived_metaObject;
    temp_s2 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, g_igIterateDerived_ctorTable, 2);
    temp_s1 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2));
    ((igObjectRefMetaField *)temp_s1)->_metaObject = (int)igMetaObject_GetOrCreateMetaObject();
    igMetaObject_NameFields(temp_s0, g_igIterateDerived_fieldTable, g_igIterateDerived_fieldHandles, g_igIterateDerived_fieldOffsets, temp_s2);
}

