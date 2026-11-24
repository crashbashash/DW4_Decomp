igMetaObject *g_igPickMode_metaObject;
igMetaField *g_igPickMode_parametersMetaField;
igMetaField *g_igPickMode_guiSystemMetaField;
igMetaField *g_igPickMode_cursorMetaField;
igMetaField *g_igPickMode_savedCursorMetaField;
igMetaField *g_igPickMode_savedCursorStateMetaField;
igMetaField *g_igPickMode_intersectTraversalMetaField;
igMetaField *g_igPickMode_rayMetaField;
igMetaField *g_igPickMode_impactLengthMetaField;
igMetaField *g_igPickMode_hitMetaField;
igMetaField *g_igPickMode_hitPathMetaField;
igMetaField *g_igPickMode_inverseProjectionMatrixMetaField;
igMetaField *g_igPickMode_joystickTMetaField;

igPickMode *igPickMode_Create(int allocator) {
    igPickMode_EnsureRegistered();
    return (igPickMode *)igMetaObject_CreateInstance(g_igPickMode_metaObject, (igMemoryPoolView *)allocator);
}

void *igPickMode_GetMetaObject(void) {
    igMetaObject *g = g_igPickMode_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false) {
        igPickMode_EnsureRegistered();
    }
    return g_igPickMode_metaObject;
}

int igPickMode_GetVTable(void) {
    struct Obj_45c200 obj;
    int r;

    igObject_InitHeader((igObject *)&obj);
    obj.vt = &g_igViewMode_vtable[0];
    igMatrix44f_SetIdentity((float *)&obj.w[2]);
    obj.vt = &g_igPickMode_vtable[0];
    obj.w[18] = 0;
    obj.w[19] = 0;
    obj.w[20] = 0;
    obj.w[21] = 0;
    obj.w[23] = 0;
    obj.w[24] = 0;
    obj.w[27] = 0;
    igMatrix44f_SetIdentity((float *)&obj.w[28]);
    r = *(int *)((char *)&obj + g_objectSystem->vtableProbeOffset);
    obj.vt = &g_igPickMode_vtable[0];
    igSmartPointer_igGraphPath_Destruct((igSmartPointer<igObject> *)&obj.w[27], -1);
    igIntersectTraversal_igSmartPointer_igObject_Destruct((igSmartPointer<igObject> *)&obj.w[24], -1);
    FUN_0044ee80((ObjectRefWord *)&obj.w[23], -1);
    igSmartPointer_igMouseCursor_Destruct((igSmartPointer<igObject> *)&obj.w[21], -1);
    igSmartPointer_igMouseCursor_Destruct((igSmartPointer<igObject> *)&obj.w[20], -1);
    FUN_00459ae0((O *)&obj.w[19], -1);
    FUN_00459860((ObjectRefWord *)&obj.w[18], -1);
    return r;
}

void igPickMode_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(igPickMode_Register);
}

static igMetaObjectCallback g_igPickMode_callbackList[] = { igViewerParameters_EnsureRegistered, igGuiSystem_RunStaticInit, igMouseCursor_RunStaticInit, Gap::Sg::igIntersectTraversal::arkRegister, igRay_EnsureRegistered, Gap::Sg::igGraphPath::arkRegister, 0 };

CallbackArray *igPickMode_Register(void) {
    ViewerLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_igPickMode_metaObject,
        igViewMode_Register,
        igViewMode_GetPublishedMetaObject,
        igPickMode_GetMetaObjectFunction,
        "igPickMode",
        0xBC, /* instance size */
        igPickMode_GetVTable,
        &igPickMode_InitFields,
        0, /* extra callback item */
        g_igPickMode_callbackList /* callback list */
    );
}

void igPickMode_GetMetaObjectFunction(void) {
    igPickMode_GetMetaObject();
}

static FieldFactory g_igPickMode_ctorTable[] = {
    igObjectRefMetaField_Create,
    igObjectRefMetaField_Create,
    igObjectRefMetaField_Create,
    igObjectRefMetaField_Create,
    igBoolMetaField_Create,
    igObjectRefMetaField_Create,
    igObjectRefMetaField_Create,
    igFloatMetaField_Create,
    igBoolMetaField_Create,
    igObjectRefMetaField_Create,
    (FieldFactory)Gap::Math::igMatrix44fMetaField::_instantiateFromPool,
    (FieldFactory)Gap::Math::igVec2fMetaField::_instantiateFromPool,
};
static const char *g_igPickMode_fieldTable[] = {
    "_parameters",
    "_guiSystem",
    "_cursor",
    "_savedCursor",
    "_savedCursorState",
    "_intersectTraversal",
    "_ray",
    "_impactLength",
    "_hit",
    "_hitPath",
    "_inverseProjectionMatrix",
    "_joystickT",
};
static igMetaField **g_igPickMode_fieldHandles[] = {
    &g_igPickMode_parametersMetaField,
    &g_igPickMode_guiSystemMetaField,
    &g_igPickMode_cursorMetaField,
    &g_igPickMode_savedCursorMetaField,
    &g_igPickMode_savedCursorStateMetaField,
    &g_igPickMode_intersectTraversalMetaField,
    &g_igPickMode_rayMetaField,
    &g_igPickMode_impactLengthMetaField,
    &g_igPickMode_hitMetaField,
    &g_igPickMode_hitPathMetaField,
    &g_igPickMode_inverseProjectionMatrixMetaField,
    &g_igPickMode_joystickTMetaField,
};
static int g_igPickMode_fieldOffsets[] = {
    76,
    80,
    84,
    88,
    92,
    96,
    100,
    104,
    108,
    112,
    116,
    180,
};

void igPickMode_InitFields(void) {
    void *temp_s2;
    void *temp_s2_2;
    void *temp_s2_3;
    void *temp_s2_4;
    void *temp_s2_5;
    void *temp_s2_6;
    void *temp_s2_7;
    void *temp_s1;
    int temp_s0;
    int sp48[2];
    void *temp_a0;

    temp_s1 = g_igPickMode_metaObject;
    temp_s0 = igMetaObject_GetFieldCount((igMetaObject *)temp_s1);
    igMetaObject_CreateFields((igMetaObject *)temp_s1, g_igPickMode_ctorTable, 0xC);
    temp_s2 = (void *)(igMetaObject_GetFieldAt((igMetaObject *)temp_s1, temp_s0));
    ((igObjectRefMetaField *)temp_s2)->_metaObject = (int)igViewerParameters_GetOrCreateMetaObject();
    temp_s2_2 = (void *)(igMetaObject_GetFieldAt((igMetaObject *)temp_s1, temp_s0 + 1));
    ((igObjectRefMetaField *)temp_s2_2)->_metaObject = (int)igGuiSystem_GetOrCreateMetaObject();
    temp_s2_3 = (void *)(igMetaObject_GetFieldAt((igMetaObject *)temp_s1, temp_s0 + 2));
    ((igObjectRefMetaField *)temp_s2_3)->_metaObject = (int)igMouseCursor_GetOrCreateMetaObject();
    temp_s2_4 = (void *)(igMetaObject_GetFieldAt((igMetaObject *)temp_s1, temp_s0 + 3));
    ((igObjectRefMetaField *)temp_s2_4)->_metaObject = (int)igMouseCursor_GetOrCreateMetaObject();
    temp_s2_5 = (void *)(igMetaObject_GetFieldAt((igMetaObject *)temp_s1, temp_s0 + 5));
    ((igObjectRefMetaField *)temp_s2_5)->_metaObject = (int)Gap::Sg::igIntersectTraversal::getClassTypeLazy();
    ((igObjectRefMetaField *)temp_s2_5)->_construct = 1;
    temp_s2_6 = (void *)(igMetaObject_GetFieldAt((igMetaObject *)temp_s1, temp_s0 + 6));
    ((igObjectRefMetaField *)temp_s2_6)->_metaObject = (int)igRay_GetOrCreateMetaObject();
    ((igObjectRefMetaField *)temp_s2_6)->_construct = 1;
    ((Gap::Core::igFloatMetaField *)(igMetaObject_GetFieldAt((igMetaObject *)temp_s1, temp_s0 + 7)))->setDefault(0.0f);
    temp_s2_7 = (void *)(igMetaObject_GetFieldAt((igMetaObject *)temp_s1, temp_s0 + 9));
    ((igObjectRefMetaField *)temp_s2_7)->_metaObject = (int)(Gap::Sg::igGraphPath::getClassTypeLazy());
    temp_a0 = (void *)(igMetaObject_GetFieldAt((igMetaObject *)temp_s1, temp_s0 + 0xB));
    sp48[0] = 0;
    sp48[1] = 0;
    ((Gap::Math::igVec2fMetaField *)temp_a0)->setDefault(*(const igVec2f *)sp48);
    igMetaObject_NameFields((igMetaObject *)temp_s1, g_igPickMode_fieldTable, g_igPickMode_fieldHandles, g_igPickMode_fieldOffsets, temp_s0);
}

