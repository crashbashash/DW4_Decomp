igMetaObject *igInsightCore_GetMeta(void) {
    return g_igInsightCore_metaObject;
}

igMetaObject *igWindowResizeEventReceiver_GetMeta(void) {
    return g_igWindowResizeEventReceiver_metaObject;
}

int igEventReceiver_OnKeyEvent(void) {
    return 0;
}

/* Slot 22, empty override returning 0. */
int igEventReceiver_MouseMotionEvent(void) {
    return 0;
}

/* Slot 23, empty override returning 0. */
int igEventReceiver_MouseButtonEvent(void) {
    return 0;
}

/* Slot 24, empty override returning 0. */
int igEventReceiver_ControllerMotionEvent(void) {
    return 0;
}

/* Slot 25, empty override returning 0. */
int igEventReceiver_ControllerButtonEvent(void) {
    return 0;
}

/* Slot 26, empty override returning 0. */
int igEventReceiver_ControllerButtonPressureEvent(void) {
    return 0;
}

/* Slot 27, empty override returning 0. */
int igEventReceiver_ControllerSlider(void) {
    return 0;
}

/* Slot 28, empty override returning 0. */
int igEventReceiver_ControllerPointOfView(void) {
    return 0;
}

/* Slot 29, empty override returning 0. */
int igEventReceiver_ControllerConnectionEvent(void) {
    return 0;
}

/* Slot 31, empty override returning 0. */
int igEventReceiver_WindowMoveEvent(void) {
    return 0;
}

/* Slot 32, empty override returning 0. */
int igEventReceiver_WindowCloseEvent(void) {
    return 0;
}

/* Retail's out-of-line copy of igEventReceiver's inline getMeta. */
igMetaObject *igEventReceiver_GetMeta(void) {
    return Gap::Gui::igEventReceiver::getClassMeta();
}

/* Slot 30, empty override returning 0. */
int igEventReceiver_WindowResizeEvent(void) {
    return 0;
}

