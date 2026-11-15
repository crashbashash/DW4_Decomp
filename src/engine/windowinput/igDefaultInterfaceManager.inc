igMetaObject *g_igDefaultInterfaceManager_metaObject;
igMetaField *g_igDefaultInterfaceManager_mouseMotionFunctionMetaField;
igMetaField *g_igDefaultInterfaceManager_mouseButtonDownFunctionMetaField;
igMetaField *g_igDefaultInterfaceManager_mouseButtonUpFunctionMetaField;
igMetaField *g_igDefaultInterfaceManager_windowMoveFunctionMetaField;
igMetaField *g_igDefaultInterfaceManager_windowResizeFunctionMetaField;
igMetaField *g_igDefaultInterfaceManager_windowCloseFunctionMetaField;
igMetaField *g_igDefaultInterfaceManager_controllerJoystickMotionFunctionMetaField;
igMetaField *g_igDefaultInterfaceManager_controllerButtonDownFunctionMetaField;
igMetaField *g_igDefaultInterfaceManager_controllerButtonUpFunctionMetaField;
igMetaField *g_igDefaultInterfaceManager_controllerButtonPressureFunctionMetaField;
igMetaField *g_igDefaultInterfaceManager_controllerConnectionFunctionMetaField;
igMetaField *g_igDefaultInterfaceManager_controllerDisconnectionFunctionMetaField;
igMetaField *g_igDefaultInterfaceManager_controllerSliderFunctionMetaField;
igMetaField *g_igDefaultInterfaceManager_controllerPointOfViewFunctionMetaField;
igMetaField *g_igDefaultInterfaceManager_keyDownFunctionMetaField;
igMetaField *g_igDefaultInterfaceManager_keyUpFunctionMetaField;

igMetaObject *FUN_00146470(void)
{
    unsigned char ready;
    if (g_igDefaultInterfaceManager_metaObject != 0) {
        ready = (g_igDefaultInterfaceManager_metaObject->_validity & 4) != 0;
        if (ready != 0) goto done;
    }
    FUN_00146560();
done:
    return g_igDefaultInterfaceManager_metaObject;
}

int igDefaultInterfaceManager_GetVTable(void) {
    union U u;
    int temp_s0;
    S_ref *q0;

    igObject_InitHeader(u.b);
    q0 = (S_ref *)&u.b[8];
    *(int *)q0 = 0;
    u.vt = (int)&DAT_00524da0[0];
    u.vt = (int)&DAT_00524e50[0];
    temp_s0 = *(int *)&u.b[*(int *)((char *)(g_objectSystem[0]) + 916)];
    u.vt = (int)&DAT_00524da0[0];
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

void FUN_00146560(void)
{
    igMetaObject_RunStaticInit(igDefaultInterfaceManager_Register);
}

void igDefaultInterfaceManager_Register(void) {
    WindowInputLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        &g_igDefaultInterfaceManager_metaObject,
        igInterfaceManager_Register,
        igInterfaceManager_GetPublishedMetaObject,
        thunk_FUN_00146470,
        "igDefaultInterfaceManager",
        0x4C, /* instance size */
        igDefaultInterfaceManager_GetVTable,
        &igDefaultInterfaceManager_InitFields,              /* field adder (class InitFields) */
        0, /* extra callback item */
        0 /* callback list */
    );
}

igMetaObject *FUN_001465e0(void) {
    return g_igInterfaceManager_metaObject;
}

static FieldFactory g_igDefaultInterfaceManager_ctorTable[] = {
    igRawRefMetaField_Create,
    igRawRefMetaField_Create,
    igRawRefMetaField_Create,
    igRawRefMetaField_Create,
    igRawRefMetaField_Create,
    igRawRefMetaField_Create,
    igRawRefMetaField_Create,
    igRawRefMetaField_Create,
    igRawRefMetaField_Create,
    igRawRefMetaField_Create,
    igRawRefMetaField_Create,
    igRawRefMetaField_Create,
    igRawRefMetaField_Create,
    igRawRefMetaField_Create,
    igRawRefMetaField_Create,
    igRawRefMetaField_Create,
};
static const char *g_igDefaultInterfaceManager_fieldTable[] = {
    "_mouseMotionFunction",
    "_mouseButtonDownFunction",
    "_mouseButtonUpFunction",
    "_windowMoveFunction",
    "_windowResizeFunction",
    "_windowCloseFunction",
    "_controllerJoystickMotionFunction",
    "_controllerButtonDownFunction",
    "_controllerButtonUpFunction",
    "_controllerButtonPressureFunction",
    "_controllerConnectionFunction",
    "_controllerDisconnectionFunction",
    "_controllerSliderFunction",
    "_controllerPointOfViewFunction",
    "_keyDownFunction",
    "_keyUpFunction",
};
static igMetaField **g_igDefaultInterfaceManager_fieldHandles[] = {
    &g_igDefaultInterfaceManager_mouseMotionFunctionMetaField,
    &g_igDefaultInterfaceManager_mouseButtonDownFunctionMetaField,
    &g_igDefaultInterfaceManager_mouseButtonUpFunctionMetaField,
    &g_igDefaultInterfaceManager_windowMoveFunctionMetaField,
    &g_igDefaultInterfaceManager_windowResizeFunctionMetaField,
    &g_igDefaultInterfaceManager_windowCloseFunctionMetaField,
    &g_igDefaultInterfaceManager_controllerJoystickMotionFunctionMetaField,
    &g_igDefaultInterfaceManager_controllerButtonDownFunctionMetaField,
    &g_igDefaultInterfaceManager_controllerButtonUpFunctionMetaField,
    &g_igDefaultInterfaceManager_controllerButtonPressureFunctionMetaField,
    &g_igDefaultInterfaceManager_controllerConnectionFunctionMetaField,
    &g_igDefaultInterfaceManager_controllerDisconnectionFunctionMetaField,
    &g_igDefaultInterfaceManager_controllerSliderFunctionMetaField,
    &g_igDefaultInterfaceManager_controllerPointOfViewFunctionMetaField,
    &g_igDefaultInterfaceManager_keyDownFunctionMetaField,
    &g_igDefaultInterfaceManager_keyUpFunctionMetaField,
};
static int g_igDefaultInterfaceManager_fieldOffsets[] = {
    12,
    16,
    20,
    24,
    28,
    32,
    36,
    40,
    44,
    48,
    52,
    56,
    60,
    64,
    68,
    72,
};

void igDefaultInterfaceManager_InitFields(void) {
    int temp_s1;
    igMetaObject *temp_s0;

    temp_s0 = g_igDefaultInterfaceManager_metaObject;
    temp_s1 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, g_igDefaultInterfaceManager_ctorTable, 0x10);
    igMetaObject_NameFields(temp_s0, g_igDefaultInterfaceManager_fieldTable, g_igDefaultInterfaceManager_fieldHandles, g_igDefaultInterfaceManager_fieldOffsets, temp_s1);
}

