igMetaObject *g_igWindow_metaObject;

igWindow *igWindow_CreateInstance(int allocator) {
    FUN_00145de0();
    return (igWindow *)igMetaObject_CreateInstance(g_igWindow_metaObject, (igMemoryPoolView *)allocator);
}

igMetaObject *FUN_00145d40(void) {
    if (g_igWindow_metaObject == 0) {
        g_igWindow_metaObject = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData));
    }
    return g_igWindow_metaObject;
}

igMetaObject *igWindow_GetMetaObject(void)
{
    igMetaObject *g = g_igWindow_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_00145de0();
    return g_igWindow_metaObject;
}

void FUN_00145de0(void)
{
    igMetaObject_RunStaticInit(igWindow_Register);
}

CallbackArray *igWindow_Register(void) {
    WindowInputLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        1, /* abstract */
        &g_igWindow_metaObject,
        igEventProducer_Register,
        igEventProducer_GetPublishedMetaObject,
        thunk_igWindow_GetMetaObject,
        "igWindow",
        8, /* instance size */
        0,
        FUN_00145e80,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void thunk_igWindow_GetMetaObject(void) {
    igWindow_GetMetaObject();
}

igMetaObject *FUN_00145e70(void) {
    return g_igEventProducer_metaObject;
}

void FUN_00145e80(void) {
    *(int *)((char *)(g_igWindow_metaObject) + 60) = (int)(&thunk_FUN_00146a60);
}

void thunk_FUN_00146a60(void) {
    FUN_00146a60();
}

static const char *g_igInterfaceManager_keyValuesNames[] = {
    "UNKNOWN", "BACKSPACE", "TAB", "RETURN",
    "CAPS_LOCK", "ESCAPE", "SPACE", "APOSTROPHE",
    "TILDE", "COMMA", "MINUS", "DECIMAL",
    "SLASH", "SEMICOLON", "EQUAL", "LEFT_BRACKET",
    "BACKSLASH", "RIGHT_BRACKET", "KEYBOARD_0", "KEYBOARD_1",
    "KEYBOARD_2", "KEYBOARD_3", "KEYBOARD_4", "KEYBOARD_5",
    "KEYBOARD_6", "KEYBOARD_7", "KEYBOARD_8", "KEYBOARD_9",
    "A", "B", "C", "D",
    "E", "F", "G", "H",
    "I", "J", "K", "L",
    "M", "N", "O", "P",
    "Q", "R", "S", "T",
    "U", "V", "W", "X",
    "Y", "Z", "LEFT_ARROW", "UP_ARROW",
    "RIGHT_ARROW", "DOWN_ARROW", "INSERT", "DELETE_KEY",
    "HOME", "END", "PAGE_UP", "PAGE_DOWN",
    "KEYPAD_0", "KEYPAD_1", "KEYPAD_2", "KEYPAD_3",
    "KEYPAD_4", "KEYPAD_5", "KEYPAD_6", "KEYPAD_7",
    "KEYPAD_8", "KEYPAD_9", "KEYPAD_DECIMAL", "KEYPAD_ENTER",
    "KEYPAD_ADD", "KEYPAD_SUBTRACT", "KEYPAD_MULTIPLY", "KEYPAD_DIVIDE",
    "F1", "F2", "F3", "F4",
    "F5", "F6", "F7", "F8",
    "F9", "F10", "F11", "F12",
    "NUM_LOCK", "PRINT_SCREEN", "SCROLL_LOCK", "BREAK",
    "LEFT_ALT", "RIGHT_ALT", "LEFT_SHIFT", "RIGHT_SHIFT",
    "LEFT_CTRL", "RIGHT_CTRL", "LEFT_WINDOWSKEY", "RIGHT_WINDOWSKEY",
    "CONTEXTMENU_WINDOWSKEY",
};
static int g_igInterfaceManager_keyValuesValues[] = {
    0, 8, 9, 0xd, 0x14, 0x1b, ' ', '\'',
    '`', ',', '-', '.', '/', ';', '=', '[',
    '\\', ']', '0', '1', '2', '3', '4', '5',
    '6', '7', '8', '9', 'A', 'B', 'C', 'D',
    'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L',
    'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T',
    'U', 'V', 'W', 'X', 'Y', 'Z', 0x80, 0x81,
    0x82, 0x83, 0x84, 0x85, 0x86, 0x87, 0x88, 0x89,
    0x90, 0x91, 0x92, 0x93, 0x94, 0x95, 0x96, 0x97,
    0x98, 0x99, 0x9a, 0x9b, 0x9c, 0x9d, 0x9e, 0x9f,
    0xac, 0xad, 0xae, 0xaf, 0xb0, 0xb1, 0xb2, 0xb3,
    0xb4, 0xb5, 0xb6, 0xb7, 0xb8, 0xb9, 0xba, 0xbb,
    0xc8, 0xc9, 0xca, 0xcb, 0xcc, 0xcd, 0xce, 0xcf,
    0xd0,
};
igMetaEnum *g_igInterfaceManager_keyValuesMetaEnum;

igMetaEnum *FUN_00145eb0(void) {
    if (g_igInterfaceManager_keyValuesMetaEnum == 0) {
        g_igInterfaceManager_keyValuesMetaEnum = igMetaEnum_Create("KEY_VALUES", g_igInterfaceManager_keyValuesNames, g_igInterfaceManager_keyValuesValues, 0x69);
    }
    return g_igInterfaceManager_keyValuesMetaEnum;
}

