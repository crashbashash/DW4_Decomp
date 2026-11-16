igMetaObject *g_igGuiSystemModel_metaObject;
igMetaField *g_igGuiSystemModel_windowSizeMetaField;
igMetaField *g_igGuiSystemModel_mousePositionMetaField;
igMetaField *g_igGuiSystemModel_mousePressedMetaField;
igMetaField *g_igGuiSystemModel_viewMatrixMetaField;
igMetaField *g_igGuiSystemModel_projectionMatrixMetaField;
igMetaField *g_igGuiSystemModel_activeMetaField;
igMetaField *g_igGuiSystemModel_rootComponentMetaField;
igMetaField *g_igGuiSystemModel_focusedComponentMetaField;
igMetaField *g_igGuiSystemModel_componentUnderMouseMetaField;
igMetaField *g_igGuiSystemModel_pushedComponentMetaField;
igMetaField *g_igGuiSystemModel_windowCloseRequestedMetaField;

igMetaObject *FUN_0044f210(void) {
    if (g_igGuiSystemModel_metaObject == 0) {
        g_igGuiSystemModel_metaObject = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData[0]));
    }
    return g_igGuiSystemModel_metaObject;
}

igMetaObject *igGuiSystemModel_GetMetaObject(void)
{
    igMetaObject *g = g_igGuiSystemModel_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false)
        igGuiSystemModel_RunStaticInit();
    return g_igGuiSystemModel_metaObject;
}

int igGuiSystemModel_GetVTable(void) {
    struct igGuiSystemModel s;
    char *p;
    int r;
    p = (char *)&s;
    igObject_InitHeader(p);
    s._views = 0;
    *(int **)&s._vtable = &g_igGuiSystemModel_vtable[0];
    igMatrix44f_SetIdentity(s._viewMatrix);
    igMatrix44f_SetIdentity(((struct igGuiSystemModel *)p)->_projectionMatrix);
    ((struct igGuiSystemModel *)p)->_rootComponent = 0;
    ((struct igGuiSystemModel *)p)->_focusedComponent = 0;
    ((struct igGuiSystemModel *)p)->_componentUnderMouse = 0;
    ((struct igGuiSystemModel *)p)->_pushedComponent = 0;
    r = *(int *)((char *)&s + *(int *)((char *)(g_objectSystem[0]) + 916));
    *(int **)&s._vtable = &g_igGuiSystemModel_vtable[0];
    igSmartPointer_igGuiComponent_Destruct(&s._pushedComponent, -1);
    igSmartPointer_igGuiComponent_Destruct(&s._componentUnderMouse, -1);
    igSmartPointer_igGuiComponent_Destruct(&s._focusedComponent, -1);
    igSmartPointer_igGuiComponent_Destruct(&s._rootComponent, -1);
    FUN_0044c110((S *)&s, 0);
    return r;
}

void igGuiSystemModel_RunStaticInit(void)
{
    igMetaObject_RunStaticInit(igGuiSystemModel_Register);
}

static igMetaObjectCallback g_igGuiSystemModel_callbackList[] = { igGuiComponent_EnsureRegistered, 0 };

void igGuiSystemModel_Register(void) {
    GuiLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        &g_igGuiSystemModel_metaObject,
        igModel_Register,
        igModel_GetPublishedMetaObject,
        thunk_igGuiSystemModel_GetMetaObject,
        "igGuiSystemModel",
        0xB8, /* instance size */
        igGuiSystemModel_GetVTable,
        &igGuiSystemModel_InitFields,
        0, /* extra callback item */
        g_igGuiSystemModel_callbackList /* callback list */
    );
}

void thunk_igGuiSystemModel_GetMetaObject(void) {
    igGuiSystemModel_GetMetaObject();
}

static FieldFactory g_igGuiSystemModel_ctorTable[] = {
    igVec2fMetaField_CreateInstance,
    igVec2fMetaField_CreateInstance,
    igBoolMetaField_Create,
    igMatrix44fMetaField_CreateInstance,
    igMatrix44fMetaField_CreateInstance,
    igBoolMetaField_Create,
    igObjectRefMetaField_Create,
    igObjectRefMetaField_Create,
    igObjectRefMetaField_Create,
    igObjectRefMetaField_Create,
    igBoolMetaField_Create,
};
static const char *g_igGuiSystemModel_fieldTable[] = {
    "_windowSize",
    "_mousePosition",
    "_mousePressed",
    "_viewMatrix",
    "_projectionMatrix",
    "_active",
    "_rootComponent",
    "_focusedComponent",
    "_componentUnderMouse",
    "_pushedComponent",
    "_windowCloseRequested",
};
static igMetaField **g_igGuiSystemModel_fieldHandles[] = {
    &g_igGuiSystemModel_windowSizeMetaField,
    &g_igGuiSystemModel_mousePositionMetaField,
    &g_igGuiSystemModel_mousePressedMetaField,
    &g_igGuiSystemModel_viewMatrixMetaField,
    &g_igGuiSystemModel_projectionMatrixMetaField,
    &g_igGuiSystemModel_activeMetaField,
    &g_igGuiSystemModel_rootComponentMetaField,
    &g_igGuiSystemModel_focusedComponentMetaField,
    &g_igGuiSystemModel_componentUnderMouseMetaField,
    &g_igGuiSystemModel_pushedComponentMetaField,
    &g_igGuiSystemModel_windowCloseRequestedMetaField,
};
static int g_igGuiSystemModel_fieldOffsets[] = {
    12,
    20,
    28,
    32,
    96,
    160,
    164,
    168,
    172,
    176,
    180,
};

void igGuiSystemModel_InitFields(void) {
    int temp_s2;
    int sp48[2];
    int sp40[2];
    void *temp_s1_4;
    void *temp_s1_3;
    void *temp_s1_2;
    void *temp_s1;
    void *temp_a0_2;
    void *temp_a0;
    void *temp_s0;

    temp_s0 = (void *)g_igGuiSystemModel_metaObject;
    temp_s2 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, g_igGuiSystemModel_ctorTable, 0xB);
    temp_a0 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2));
    sp48[0] = 0;
    sp48[1] = 0;
    igVec2fMetaField_SetDefault(temp_a0, sp48);
    temp_a0_2 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 1));
    sp40[0] = 0;
    sp40[1] = 0;
    igVec2fMetaField_SetDefault(temp_a0_2, sp40);
    igBoolMetaField_SetDefaultValue(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 5), 1);
    temp_s1 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 6));
    *(int *)((char *)(temp_s1) + 56) = (int)igGuiComponent_GetOrCreateMetaObject();
    temp_s1_2 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 7));
    *(int *)((char *)(temp_s1_2) + 56) = (int)igGuiComponent_GetOrCreateMetaObject();
    temp_s1_3 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 8));
    *(int *)((char *)(temp_s1_3) + 56) = (int)igGuiComponent_GetOrCreateMetaObject();
    temp_s1_4 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 9));
    *(int *)((char *)(temp_s1_4) + 56) = (int)igGuiComponent_GetOrCreateMetaObject();
    igMetaObject_NameFields(temp_s0, g_igGuiSystemModel_fieldTable, g_igGuiSystemModel_fieldHandles, g_igGuiSystemModel_fieldOffsets, temp_s2);
}

