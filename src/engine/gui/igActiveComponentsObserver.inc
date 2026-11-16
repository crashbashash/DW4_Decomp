igMetaObject *g_igActiveComponentsObserver_metaObject;
igMetaField *g_igActiveComponentsObserver_oldComponentUnderMouseMetaField;
igMetaField *g_igActiveComponentsObserver_oldFocusedComponentMetaField;
igMetaField *g_igActiveComponentsObserver_oldPushedComponentMetaField;

int FUN_0044e990(int arg0) {
    igActiveComponentsObserver_RunStaticInit();
    return (int)(igMetaObject_CreateInstance(g_igActiveComponentsObserver_metaObject, (igMemoryPoolView *)arg0));
}

igMetaObject *igActiveComponentsObserver_GetMetaObject(void)
{
    igMetaObject *g = g_igActiveComponentsObserver_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false)
        igActiveComponentsObserver_RunStaticInit();
    return g_igActiveComponentsObserver_metaObject;
}

int igActiveComponentsObserver_GetVTable(void) {
    union U_44ea20 u;
    int r;
    int *v1;
    int *a1;
    int v0;
    char *p4C;
    char *p48;
    char *p50;
    igObject_InitHeader((igObject *)u.b);
    u.vt = (int)&g_igActiveComponentsObserver_vtable[0];
    p48 = &u.b[12];
    *(int *)p48 = 0;
    p4C = &u.b[16];
    *(int *)p4C = 0;
    p50 = &u.b[20];
    *(int *)p50 = 0;
    r = *(int *)&u.b[*(int *)((char *)(g_objectSystem) + 916)];
    u.vt = (int)&g_igActiveComponentsObserver_vtable[0];
    if (p50 != 0) {
        v1 = *(int **)p50;
        if (v1 != 0) {
            v1[1] = v1[1] - 1;
            if ((v1[1] & 0x7FFFFF) == 0) {
                igObject_Destroy(v1);
            }
        }
    }
    if (p4C != 0) {
        v1 = *(int **)p4C;
        if (v1 != 0) {
            v1[1] = v1[1] - 1;
            if ((v1[1] & 0x7FFFFF) == 0) {
                igObject_Destroy(v1);
            }
        }
    }
    if (p48 != 0) {
        v1 = *(int **)p48;
        if (v1 != 0) {
            v1[1] = v1[1] - 1;
            if ((v1[1] & 0x7FFFFF) == 0) {
                igObject_Destroy(v1);
            }
        }
    }
    return r;
}

void igActiveComponentsObserver_RunStaticInit(void)
{
    igMetaObject_RunStaticInit(igActiveComponentsObserver_Register);
}

static igMetaObjectCallback g_igActiveComponentsObserver_callbackList[] = { igGuiComponent_EnsureRegistered, 0 };

CallbackArray *igActiveComponentsObserver_Register(void) {
    GuiLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_igActiveComponentsObserver_metaObject,
        igView_Register,
        igView_GetPublishedMetaObject,
        thunk_igActiveComponentsObserver_GetMetaObject,
        "igActiveComponentsObserver",
        0x18, /* instance size */
        igActiveComponentsObserver_GetVTable,
        &igActiveComponentsObserver_InitFields,
        0, /* extra callback item */
        g_igActiveComponentsObserver_callbackList /* callback list */
    );
}

void thunk_igActiveComponentsObserver_GetMetaObject(void) {
    igActiveComponentsObserver_GetMetaObject();
}

static FieldFactory g_igActiveComponentsObserver_ctorTable[] = {
    igObjectRefMetaField_Create,
    igObjectRefMetaField_Create,
    igObjectRefMetaField_Create,
};
static const char *g_igActiveComponentsObserver_fieldTable[] = {
    "_oldComponentUnderMouse",
    "_oldFocusedComponent",
    "_oldPushedComponent",
};
static igMetaField **g_igActiveComponentsObserver_fieldHandles[] = {
    &g_igActiveComponentsObserver_oldComponentUnderMouseMetaField,
    &g_igActiveComponentsObserver_oldFocusedComponentMetaField,
    &g_igActiveComponentsObserver_oldPushedComponentMetaField,
};
static int g_igActiveComponentsObserver_fieldOffsets[] = {
    12,
    16,
    20,
};

void igActiveComponentsObserver_InitFields(void) {
    int temp_s2;
    void *temp_s1_3;
    void *temp_s1_2;
    void *temp_s1;
    void *temp_s0;

    temp_s0 = (void *)g_igActiveComponentsObserver_metaObject;
    temp_s2 = igMetaObject_GetFieldCount((igMetaObject *)temp_s0);
    igMetaObject_CreateFields((igMetaObject *)temp_s0, g_igActiveComponentsObserver_ctorTable, 3);
    temp_s1 = (void *)(igMetaObject_GetFieldAt((igMetaObject *)temp_s0, temp_s2));
    ((igObjectRefMetaField *)temp_s1)->_metaObject = (int)igGuiComponent_GetOrCreateMetaObject();
    temp_s1_2 = (void *)(igMetaObject_GetFieldAt((igMetaObject *)temp_s0, temp_s2 + 1));
    ((igObjectRefMetaField *)temp_s1_2)->_metaObject = (int)igGuiComponent_GetOrCreateMetaObject();
    temp_s1_3 = (void *)(igMetaObject_GetFieldAt((igMetaObject *)temp_s0, temp_s2 + 2));
    ((igObjectRefMetaField *)temp_s1_3)->_metaObject = (int)igGuiComponent_GetOrCreateMetaObject();
    igMetaObject_NameFields((igMetaObject *)temp_s0, g_igActiveComponentsObserver_fieldTable, g_igActiveComponentsObserver_fieldHandles, g_igActiveComponentsObserver_fieldOffsets, temp_s2);
}

