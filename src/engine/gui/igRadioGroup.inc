igMetaObject *g_igRadioGroup_metaObject;
igMetaField *g_igRadioGroup_modelMetaField;
igMetaField *g_igRadioGroup_selectedObserverMetaField;
igMetaField *g_igRadioGroup_observerListMetaField;
igMetaField *g_igRadioGroup_alwaysSelectedMetaField;
igMetaField *g_igRadioGroup_lastSelectedMetaField;
igMetaField *g_igRadioGroup_defaultSelectedMetaField;

igMetaObject *igRadioGroup_GetOrCreateMetaObject(void) {
    if (g_igRadioGroup_metaObject == 0) {
        g_igRadioGroup_metaObject = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData));
    }
    return g_igRadioGroup_metaObject;
}

igMetaObject *igRadioGroup_GetMetaObject(void)
{
    igMetaObject *g = g_igRadioGroup_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false)
        igRadioGroup_EnsureRegistered();
    return g_igRadioGroup_metaObject;
}

int igRadioGroup_GetVTable(void) {
    union U_44ce90 u;
    int r;
    int *v1;
    int *a1;
    int v0;
    char *p4C;
    char *p48;
    char *p50;
    igObject_InitHeader((igObject *)u.b);
    u.vt = (int)&g_igRadioGroup_vtable[0];
    p48 = &u.b[8];
    *(int *)p48 = 0;
    p4C = &u.b[12];
    *(int *)p4C = 0;
    p50 = &u.b[16];
    *(int *)p50 = 0;
    r = *(int *)&u.b[g_objectSystem->vtableProbeOffset];
    u.vt = (int)&g_igRadioGroup_vtable[0];
    if (p50 != 0) {
        v1 = *(int **)p50;
        if (v1 != 0) {
            v1[1] = v1[1] - 1;
            if ((v1[1] & 0x7FFFFF) == 0) {
                igObject_Destroy((igObject *)v1);
            }
        }
    }
    if (p4C != 0) {
        v1 = *(int **)p4C;
        if (v1 != 0) {
            v1[1] = v1[1] - 1;
            if ((v1[1] & 0x7FFFFF) == 0) {
                igObject_Destroy((igObject *)v1);
            }
        }
    }
    if (p48 != 0) {
        v1 = *(int **)p48;
        if (v1 != 0) {
            v1[1] = v1[1] - 1;
            if ((v1[1] & 0x7FFFFF) == 0) {
                igObject_Destroy((igObject *)v1);
            }
        }
    }
    return r;
}

void igRadioGroup_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(igRadioGroup_Register);
}

static igMetaObjectCallback g_igRadioGroup_callbackList[] = { igRadioGroupModel_RunStaticInit, igRadioGroupSelectedObserver_EnsureRegistered, igOnOffValueObserverList_EnsureRegistered, 0 };

CallbackArray *igRadioGroup_Register(void) {
    GuiLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_igRadioGroup_metaObject,
        igObject_Register,
        igObject_GetMetaObject_ParentAccessor,
        igRadioGroup_GetMetaObjectFunction,
        "igRadioGroup",
        0x20, /* instance size */
        igRadioGroup_GetVTable,
        &igRadioGroup_InitFields,
        0, /* extra callback item */
        g_igRadioGroup_callbackList /* callback list */
    );
}

void igRadioGroup_GetMetaObjectFunction(void) {
    igRadioGroup_GetMetaObject();
}

static FieldFactory g_igRadioGroup_ctorTable[] = {
    igObjectRefMetaField_Create,
    igObjectRefMetaField_Create,
    igObjectRefMetaField_Create,
    igBoolMetaField_Create,
    igIntMetaField_Create,
    igIntMetaField_Create,
};
static const char *g_igRadioGroup_fieldTable[] = {
    "_model",
    "_selectedObserver",
    "_observerList",
    "_alwaysSelected",
    "_lastSelected",
    "_defaultSelected",
};
static igMetaField **g_igRadioGroup_fieldHandles[] = {
    &g_igRadioGroup_modelMetaField,
    &g_igRadioGroup_selectedObserverMetaField,
    &g_igRadioGroup_observerListMetaField,
    &g_igRadioGroup_alwaysSelectedMetaField,
    &g_igRadioGroup_lastSelectedMetaField,
    &g_igRadioGroup_defaultSelectedMetaField,
};
static int g_igRadioGroup_fieldOffsets[] = {
    8,
    12,
    16,
    20,
    24,
    28,
};

void igRadioGroup_InitFields(void) {
    int temp_s0;
    void *temp_s2;
    void *temp_s2_2;
    void *temp_s2_3;
    void *temp_s1;

    temp_s1 = (void *)g_igRadioGroup_metaObject;
    temp_s0 = igMetaObject_GetFieldCount((igMetaObject *)temp_s1);
    igMetaObject_CreateFields((igMetaObject *)temp_s1, g_igRadioGroup_ctorTable, 6);
    temp_s2 = (void *)(igMetaObject_GetFieldAt((igMetaObject *)temp_s1, temp_s0));
    ((igObjectRefMetaField *)temp_s2)->_metaObject = (int)igRadioGroupModel_GetOrCreateMetaObject();
    ((igRefMetaField *)temp_s2)->_construct = 1;
    temp_s2_2 = (void *)(igMetaObject_GetFieldAt((igMetaObject *)temp_s1, temp_s0 + 1));
    ((igObjectRefMetaField *)temp_s2_2)->_metaObject = (int)igRadioGroupSelectedObserver_GetOrCreateMetaObject();
    ((igRefMetaField *)temp_s2_2)->_construct = 1;
    temp_s2_3 = (void *)(igMetaObject_GetFieldAt((igMetaObject *)temp_s1, temp_s0 + 2));
    ((igObjectRefMetaField *)temp_s2_3)->_metaObject = (int)igOnOffValueObserverList_GetOrCreateMetaObject();
    ((igRefMetaField *)temp_s2_3)->_construct = 1;
    igBoolMetaField_SetDefaultValue(igMetaObject_GetFieldAt((igMetaObject *)temp_s1, temp_s0 + 3), 1);
    igIntMetaField_SetDefault(igMetaObject_GetFieldAt((igMetaObject *)temp_s1, temp_s0 + 4), -1);
    igMetaObject_NameFields((igMetaObject *)temp_s1, g_igRadioGroup_fieldTable, g_igRadioGroup_fieldHandles, g_igRadioGroup_fieldOffsets, temp_s0);
}

