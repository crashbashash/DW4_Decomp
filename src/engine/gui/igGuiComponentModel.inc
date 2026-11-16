igMetaObject *g_igGuiComponentModel_metaObject;
igMetaField *g_igGuiComponentModel_componentMetaField;
igMetaField *g_igGuiComponentModel_enabledMetaField;
igMetaField *g_igGuiComponentModel_hasFocusMetaField;
igMetaField *g_igGuiComponentModel_mouseOverMetaField;
igMetaField *g_igGuiComponentModel_pushedMetaField;
igMetaField *g_igGuiComponentModel_sizeMetaField;
igMetaField *g_igGuiComponentModel_childHasFocusMetaField;

igMetaObject *FUN_0044f790(void) {
    if (g_igGuiComponentModel_metaObject == 0) {
        g_igGuiComponentModel_metaObject = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData));
    }
    return g_igGuiComponentModel_metaObject;
}

igMetaObject *igGuiComponentModel_GetMetaObject(void)
{
    igMetaObject *g = g_igGuiComponentModel_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false)
        igGuiComponentModel_RunStaticInit();
    return g_igGuiComponentModel_metaObject;
}

int igGuiComponentModel_GetVTable(void) {
    union U_44f830 u;
    int temp_s0;
    S_ref *q0;

    igObject_InitHeader((igObject *)u.b);
    q0 = (S_ref *)&u.b[8];
    *(int *)q0 = 0;
    u.vt = (int)&g_igModel_vtable[0];
    u.vt = (int)&g_igGuiComponentModel_vtable[0];
    temp_s0 = *(int *)&u.b[*(int *)((char *)(g_objectSystem) + 916)];
    u.vt = (int)&g_igModel_vtable[0];
    if (q0 != 0) {
        q0 = *(S_ref **)q0;
        if (q0 != 0) {
            q0->f4 = (int)((int) (q0->f4 - 1));
            if (((unsigned long long) ((long long) q0->f4 << 0x29) >> 0x29) == 0) {
                igObject_Destroy(q0);
            }
        }
    }
    return temp_s0;
}

void igGuiComponentModel_RunStaticInit(void)
{
    igMetaObject_RunStaticInit(igGuiComponentModel_Register);
}

static igMetaObjectCallback g_igGuiComponentModel_callbackList[] = { igGuiComponent_EnsureRegistered, 0 };

CallbackArray *igGuiComponentModel_Register(void) {
    GuiLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_igGuiComponentModel_metaObject,
        igModel_Register,
        igModel_GetPublishedMetaObject,
        thunk_igGuiComponentModel_GetMetaObject,
        "igGuiComponentModel",
        0x24, /* instance size */
        igGuiComponentModel_GetVTable,
        &igGuiComponentModel_InitFields,
        0, /* extra callback item */
        g_igGuiComponentModel_callbackList /* callback list */
    );
}

void thunk_igGuiComponentModel_GetMetaObject(void) {
    igGuiComponentModel_GetMetaObject();
}

static FieldFactory g_igGuiComponentModel_ctorTable[] = {
    igObjectRefMetaField_Create,
    igBoolMetaField_Create,
    igBoolMetaField_Create,
    igBoolMetaField_Create,
    igBoolMetaField_Create,
    (FieldFactory)igVec3fMetaField_CreateInstance,
    igBoolMetaField_Create,
};
static const char *g_igGuiComponentModel_fieldTable[] = {
    "_component",
    "_enabled",
    "_hasFocus",
    "_mouseOver",
    "_pushed",
    "_size",
    "_childHasFocus",
};
static igMetaField **g_igGuiComponentModel_fieldHandles[] = {
    &g_igGuiComponentModel_componentMetaField,
    &g_igGuiComponentModel_enabledMetaField,
    &g_igGuiComponentModel_hasFocusMetaField,
    &g_igGuiComponentModel_mouseOverMetaField,
    &g_igGuiComponentModel_pushedMetaField,
    &g_igGuiComponentModel_sizeMetaField,
    &g_igGuiComponentModel_childHasFocusMetaField,
};
static int g_igGuiComponentModel_fieldOffsets[] = {
    32,
    12,
    13,
    14,
    15,
    16,
    28,
};

void igGuiComponentModel_InitFields(void) {
    int temp_s2;
    void *temp_a0;
    void *temp_s1;
    struct { int a; int b; int c; } z;
    void *temp_s0;

    temp_s0 = (void *)g_igGuiComponentModel_metaObject;
    temp_s2 = igMetaObject_GetFieldCount((igMetaObject *)temp_s0);
    igMetaObject_CreateFields((igMetaObject *)temp_s0, g_igGuiComponentModel_ctorTable, 7);
    temp_s1 = (void *)(igMetaObject_GetFieldAt((igMetaObject *)temp_s0, temp_s2));
    *(int *)((char *)(temp_s1) + 56) = (int)igGuiComponent_GetOrCreateMetaObject();
    *(char *)(60 + (char *)(temp_s1)) = 0;
    igBoolMetaField_SetDefaultValue(igMetaObject_GetFieldAt((igMetaObject *)temp_s0, temp_s2 + 1), 1);
    temp_a0 = (void *)(igMetaObject_GetFieldAt((igMetaObject *)temp_s0, temp_s2 + 5));
    z.a = 0;
    z.b = 0;
    z.c = 0;
    igVec3fMetaField_SetDefault(temp_a0, &z);
    igMetaObject_NameFields((igMetaObject *)temp_s0, g_igGuiComponentModel_fieldTable, g_igGuiComponentModel_fieldHandles, g_igGuiComponentModel_fieldOffsets, temp_s2);
}

