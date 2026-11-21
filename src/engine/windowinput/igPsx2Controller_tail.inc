static const char *g_igPsx2Controller_controllerPhaseNames[] = {
    "SET_TYPE", "SET_ANALOG_SWITCH", "WAIT_SET_ANALOG_SWITCH", "SET_ACTUATORS",
    "WAIT_SET_ACTUATORS", "SET_PRESSURE_BUTTONS", "WAIT_SET_PRESSURE_BUTTONS", "GET_DATA",
};
static int g_igPsx2Controller_controllerPhaseValues[] = {
    0, 1, 2, 3, 4, 5, 6, 7,
};
igMetaEnum *g_igPsx2Controller_controllerPhaseMetaEnum;

igMetaEnum *FUN_00147030(void) {
    if (g_igPsx2Controller_controllerPhaseMetaEnum == 0) {
        g_igPsx2Controller_controllerPhaseMetaEnum = (igMetaEnum *)Gap::Core::igMetaEnum::createMetaEnum("ControllerPhase", g_igPsx2Controller_controllerPhaseNames, g_igPsx2Controller_controllerPhaseValues, 8);
    }
    return g_igPsx2Controller_controllerPhaseMetaEnum;
}

igMetaObject *g_igPsx2Controller_metaObject;
igMetaField *g_igPsx2Controller_idMetaField;
igMetaField *g_igPsx2Controller_curr_idMetaField;
igMetaField *g_igPsx2Controller_term_idMetaField;
igMetaField *g_igPsx2Controller_buttonCountMetaField;
igMetaField *g_igPsx2Controller_joyCountMetaField;
igMetaField *g_igPsx2Controller_attachedWindowMetaField;
igMetaField *g_igPsx2Controller_xMetaField;
igMetaField *g_igPsx2Controller_yMetaField;
igMetaField *g_igPsx2Controller_connectedMetaField;
igMetaField *g_igPsx2Controller_typeMetaField;
igMetaField *g_igPsx2Controller_slotMetaField;
igMetaField *g_igPsx2Controller_portMetaField;
igMetaField *g_igPsx2Controller_buttonStateMetaField;
igMetaField *g_igPsx2Controller_dmaBufferMetaField;
igMetaField *g_igPsx2Controller_oldJoyXMetaField;
igMetaField *g_igPsx2Controller_oldJoyYMetaField;
igMetaField *g_igPsx2Controller_analogStateMetaField;
igMetaField *g_igPsx2Controller_lockStateMetaField;
igMetaField *g_igPsx2Controller_usePressureMetaField;
igMetaField *g_igPsx2Controller_hasPressureMetaField;
igMetaField *g_igPsx2Controller_phaseMetaField;
igMetaField *g_igPsx2Controller_resetingMetaField;
igMetaField *g_igPsx2Controller_userResetMetaField;
igMetaField *g_igPsx2Controller_userResetAnalogOnlyMetaField;

int igPsx2Controller_Create(int arg0) {
    igPsx2Controller_EnsureRegistered();
    return (int)(igMetaObject_CreateInstance(g_igPsx2Controller_metaObject, (igMemoryPoolView *)arg0));
}

igMetaObject *igPsx2Controller_GetMetaObject(void)
{
    igMetaObject *g = g_igPsx2Controller_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false)
        igPsx2Controller_EnsureRegistered();
    return g_igPsx2Controller_metaObject;
}

int igPsx2Controller_GetVTable(void) {
    union U_147120 u;
    void **q8;
    int temp_s0;
    void *temp_a0;

    igObject_InitHeader((igObject *)u.b);
    q8 = &u.p[8];
    u.w[0] = (int)(&g_igPsx2Controller_vtable[0]);
    *q8 = 0;
    temp_s0 = *(int *)&u.b[g_objectSystem->vtableProbeOffset];
    u.w[0] = (int)(&g_igPsx2Controller_vtable[0]);
    if (q8 != 0) {
        temp_a0 = *q8;
        if (temp_a0 != 0) {
            *(int *)((char *)(temp_a0) + 4) = (int)((int) (*(int *)((char *)(temp_a0) + 4) - 1));
            if (((unsigned long long) ((long long) *(int *)((char *)(temp_a0) + 4) << 0x29) >> 0x29) == 0) {
                igObject_Destroy((igObject *)temp_a0);
            }
        }
    }
    return temp_s0;
}

void igPsx2Controller_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(igPsx2Controller_Register);
}

static igMetaObjectCallback g_igPsx2Controller_callbackList[] = { igWindow_EnsureRegistered, 0 };

CallbackArray *igPsx2Controller_Register(void) {
    WindowInputLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_igPsx2Controller_metaObject,
        igController_Register,
        igController_GetPublishedMetaObject,
        igPsx2Controller_GetMetaObjectFunction,
        "igPsx2Controller",
        0x70, /* instance size */
        igPsx2Controller_GetVTable,
        &igPsx2Controller_InitFields,
        0, /* extra callback item */
        g_igPsx2Controller_callbackList /* callback list */
    );
}

igMetaObject *igController_GetPublishedMetaObject(void) {
    return g_igController_metaObject;
}

static FieldFactory g_igPsx2Controller_ctorTable[] = {
    igUnsignedShortMetaField_Create,
    igUnsignedShortMetaField_Create,
    igUnsignedShortMetaField_Create,
    igIntMetaField_Create,
    igUnsignedShortMetaField_Create,
    igObjectRefMetaField_Create,
    igFloatArrayMetaField_Create,
    igFloatArrayMetaField_Create,
    igBoolMetaField_Create,
    igEnumMetaField_Create,
    igIntMetaField_Create,
    igIntMetaField_Create,
    igUnsignedShortMetaField_Create,
    igRawRefMetaField_Create,
    igUnsignedCharArrayMetaField_Create,
    igUnsignedCharArrayMetaField_Create,
    igBoolMetaField_Create,
    igBoolMetaField_Create,
    igBoolMetaField_Create,
    igBoolMetaField_Create,
    igEnumMetaField_Create,
    igBoolMetaField_Create,
    igBoolMetaField_Create,
    igBoolMetaField_Create,
};
static const char *g_igPsx2Controller_fieldTable[] = {
    "_id",
    "_curr_id",
    "_term_id",
    "_buttonCount",
    "_joyCount",
    "_attachedWindow",
    "_x",
    "_y",
    "_connected",
    "_type",
    "_slot",
    "_port",
    "_buttonState",
    "_dmaBuffer",
    "_oldJoyX",
    "_oldJoyY",
    "_analogState",
    "_lockState",
    "_usePressure",
    "_hasPressure",
    "_phase",
    "_reseting",
    "_userReset",
    "_userResetAnalogOnly",
};
static igMetaField **g_igPsx2Controller_fieldHandles[] = {
    &g_igPsx2Controller_idMetaField,
    &g_igPsx2Controller_curr_idMetaField,
    &g_igPsx2Controller_term_idMetaField,
    &g_igPsx2Controller_buttonCountMetaField,
    &g_igPsx2Controller_joyCountMetaField,
    &g_igPsx2Controller_attachedWindowMetaField,
    &g_igPsx2Controller_xMetaField,
    &g_igPsx2Controller_yMetaField,
    &g_igPsx2Controller_connectedMetaField,
    &g_igPsx2Controller_typeMetaField,
    &g_igPsx2Controller_slotMetaField,
    &g_igPsx2Controller_portMetaField,
    &g_igPsx2Controller_buttonStateMetaField,
    &g_igPsx2Controller_dmaBufferMetaField,
    &g_igPsx2Controller_oldJoyXMetaField,
    &g_igPsx2Controller_oldJoyYMetaField,
    &g_igPsx2Controller_analogStateMetaField,
    &g_igPsx2Controller_lockStateMetaField,
    &g_igPsx2Controller_usePressureMetaField,
    &g_igPsx2Controller_hasPressureMetaField,
    &g_igPsx2Controller_phaseMetaField,
    &g_igPsx2Controller_resetingMetaField,
    &g_igPsx2Controller_userResetMetaField,
    &g_igPsx2Controller_userResetAnalogOnlyMetaField,
};
static int g_igPsx2Controller_fieldOffsets[] = {
    16,
    18,
    20,
    24,
    28,
    32,
    36,
    44,
    52,
    56,
    60,
    64,
    68,
    72,
    76,
    78,
    80,
    81,
    82,
    83,
    84,
    88,
    89,
    90,
};

void igPsx2Controller_InitFields(void) {
    int temp_s1;
    void *temp_s2;
    void *temp_v0;
    void *temp_v0_2;
    igMetaObject *temp_s0;

    temp_s0 = g_igPsx2Controller_metaObject;
    temp_s1 = igMetaObject_GetFieldCount((igMetaObject *)temp_s0);
    igMetaObject_CreateFields((igMetaObject *)temp_s0, g_igPsx2Controller_ctorTable, 0x18);
    ((Gap::Core::igIntMetaField *)(igMetaObject_GetFieldAt((igMetaObject *)temp_s0, temp_s1 + 3)))->setDefault(0x10);
    ((Gap::Core::igUnsignedShortMetaField *)(igMetaObject_GetFieldAt((igMetaObject *)temp_s0, temp_s1 + 4)))->setDefault(2);
    temp_s2 = (void *)(igMetaObject_GetFieldAt((igMetaObject *)temp_s0, temp_s1 + 5));
    *(int *)((char *)(temp_s2) + 56) = (int)igWindow_GetOrCreateMetaObject();
    { struct Fld *q = (struct Fld *)igMetaObject_GetFieldAt((igMetaObject *)temp_s0, temp_s1 + 6); q->f52 = 2; }
    { struct Fld *q = (struct Fld *)igMetaObject_GetFieldAt((igMetaObject *)temp_s0, temp_s1 + 7); q->f52 = 2; }
    temp_v0 = (void *)(igMetaObject_GetFieldAt((igMetaObject *)temp_s0, temp_s1 + 9));
    ((Gap::Core::igEnumMetaField *)temp_v0)->setDefault(1);
    *(int *)((char *)(temp_v0) + 52) = (int)(&igMetaEnum_GetEmpty);
    ((Gap::Core::igUnsignedShortMetaField *)(igMetaObject_GetFieldAt((igMetaObject *)temp_s0, temp_s1 + 0xC)))->setDefault(0xFFFF);
    { struct Fld *q = (struct Fld *)igMetaObject_GetFieldAt((igMetaObject *)temp_s0, temp_s1 + 0xE); q->f52 = 2; }
    { struct Fld *q = (struct Fld *)igMetaObject_GetFieldAt((igMetaObject *)temp_s0, temp_s1 + 0xF); q->f52 = 2; }
    ((Gap::Core::igBoolMetaField *)(igMetaObject_GetFieldAt((igMetaObject *)temp_s0, temp_s1 + 0x10)))->setDefault(1);
    ((Gap::Core::igBoolMetaField *)(igMetaObject_GetFieldAt((igMetaObject *)temp_s0, temp_s1 + 0x11)))->setDefault(1);
    ((Gap::Core::igBoolMetaField *)(igMetaObject_GetFieldAt((igMetaObject *)temp_s0, temp_s1 + 0x12)))->setDefault(1);
    temp_v0_2 = (void *)(igMetaObject_GetFieldAt((igMetaObject *)temp_s0, temp_s1 + 0x14));
    ((Gap::Core::igEnumMetaField *)temp_v0_2)->setDefault(0);
    *(int *)((char *)(temp_v0_2) + 52) = (int)(&FUN_00147030);
    ((Gap::Core::igBoolMetaField *)(igMetaObject_GetFieldAt((igMetaObject *)temp_s0, temp_s1 + 0x15)))->setDefault(1);
    igMetaObject_NameFields((igMetaObject *)temp_s0, g_igPsx2Controller_fieldTable, g_igPsx2Controller_fieldHandles, g_igPsx2Controller_fieldOffsets, temp_s1);
}

int FUN_00147430(void *arg0, int arg1) {
    return *(int *)(*(int *)((char *)arg0 + 8) + (arg1 * 4));
}

int FUN_00147450(void *arg0, int arg1) {
    int i;
    int *list;

    for (i = 0; i < 0x20; i++) {
        if (arg1 == *(int *)(*(int *)((char *)(arg0) + 8) + (i * 4))) {
            return i;
        }
    }
    return -1;
}

void FUN_001474a0(O *arg0, int arg1) {
    int n;
    int i;
    n = arg0->list->count;
    for (i = 0; i < n; i++) {
        arg0->list->items[i]->vX(arg1);
    }
}

