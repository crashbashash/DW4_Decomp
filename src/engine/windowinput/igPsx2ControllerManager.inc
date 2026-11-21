void igPsx2ControllerManager_GetMetaObjectFunction(void) {
    igPsx2ControllerManager_GetMetaObject();
}

static const char *g_igController_buttonsNames[] = {
    "BUTTON_0", "SELECT_BUTTON", "BUTTON_1", "LEFT_JOYSTICK_BUTTON",
    "BUTTON_2", "RIGHT_JOYSTICK_BUTTON", "BUTTON_3", "START_BUTTON",
    "BUTTON_4", "LEFT_PAD_UP_BUTTON", "BUTTON_5", "LEFT_PAD_RIGHT_BUTTON",
    "BUTTON_6", "LEFT_PAD_DOWN_BUTTON", "BUTTON_7", "LEFT_PAD_LEFT_BUTTON",
    "BUTTON_8", "LOWER_LEFT_TRIGGER", "BUTTON_9", "LOWER_RIGHT_TRIGGER",
    "BUTTON_10", "UPPER_LEFT_TRIGGER", "BUTTON_11", "UPPER_RIGHT_TRIGGER",
    "BUTTON_12", "RIGHT_PAD_UP_BUTTON", "BUTTON_13", "RIGHT_PAD_RIGHT_BUTTON",
    "BUTTON_14", "RIGHT_PAD_DOWN_BUTTON", "BUTTON_15", "RIGHT_PAD_LEFT_BUTTON",
    "BUTTON_16", "BUTTON_17", "BUTTON_18", "BUTTON_19",
    "BUTTON_20", "BUTTON_21", "BUTTON_22", "BUTTON_23",
    "BUTTON_24", "BUTTON_25", "BUTTON_26", "BUTTON_27",
    "BUTTON_28", "BUTTON_29", "BUTTON_30", "BUTTON_31",
    "MAX_BUTTONS",
};
static int g_igController_buttonsValues[] = {
    0, 0, 1, 1, 2, 2, 3, 3,
    4, 4, 5, 5, 6, 6, 7, 7,
    8, 8, 9, 9, 0xa, 0xa, 0xb, 0xb,
    0xc, 0xc, 0xd, 0xd, 0xe, 0xe, 0xf, 0xf,
    0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17,
    0x18, 0x19, 0x1a, 0x1b, 0x1c, 0x1d, 0x1e, 0x1f,
    0x20,
};
igMetaEnum *g_igController_buttonsMetaEnum;

igMetaEnum *FUN_00146850(void) {
    if (g_igController_buttonsMetaEnum == 0) {
        g_igController_buttonsMetaEnum = (igMetaEnum *)Gap::Core::igMetaEnum::createMetaEnum("BUTTONS", g_igController_buttonsNames, g_igController_buttonsValues, 0x31);
    }
    return g_igController_buttonsMetaEnum;
}

