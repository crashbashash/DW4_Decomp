igMetaObject *igSerialScheduler_GetMeta(void) {
    return g_igSerialScheduler_metaObject;
}

igMetaObject *igFilterMessageDispatcher_GetMeta(void) {
    return g_igFilterMessageDispatcher_metaObject;
}

igMetaObject *igMessageDefaultReceiver_GetMeta(void) {
    return g_igMessageDefaultReceiver_metaObject;
}

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

igMetaObject *igInfoManagerList_GetMeta(void) {
    return g_igInfoManagerList_metaObject;
}

igMetaObject *igInfoManagerOrderedList_GetMeta(void) {
    return g_igInfoManagerOrderedList_metaObject;
}

int igDependencyOrderedList_GetMeta(void) {
    return (int)g_igDependencyOrderedList_metaObject;
}

igMetaObject *igViewportResizedMessage_GetMeta(void) {
    return g_igViewportResizedMessage_metaObject;
}

igMetaObject *igEventReceiver_GetMeta(void) {
    return g_igEventReceiver_metaObject;
}

/* Slot 30, empty override returning 0. */
int igEventReceiver_WindowResizeEvent(void) {
    return 0;
}

igMetaObject *igInsightPluginList_GetMeta(void) {
    return g_igInsightPluginList_metaObject;
}

igMetaObject *igMessageFilter_GetMeta(void) {
    return g_igMessageFilter_metaObject;
}

igMetaObject *igMessageFilterList_GetMeta(void) {
    return g_igMessageFilterList_metaObject;
}

igMetaObject *igMessageReceiverList_GetMeta(void) {
    return g_igMessageReceiverList_metaObject;
}

igMetaObject *igMessenger_GetMeta(void) {
    return g_igMessenger_metaObject;
}

int igMessage_GetMeta(void) {
    return (int)g_igMessage_metaObject;
}

igMetaObject *igInsightPluginList_GetElementMeta(void) {
    return g_igInsightPlugin_metaObject;
}

igMetaObject *igMessageFilterList_GetElementMeta(void) {
    return g_igMessageFilter_metaObject;
}

igMetaObject *igInfoManagerList_GetElementMeta(void) {
    return g_igInfoManager_metaObject;
}

igMetaObject *igMessageReceiverList_GetElementMeta(void) {
    return g_igMessageReceiver_metaObject;
}

