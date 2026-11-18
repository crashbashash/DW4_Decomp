igMetaObject *igMersenneTwisterRandomNumber_GetMeta(void) {
    return g_igMersenneTwisterRandomNumber_metaObject;
}

unsigned int igMersenneTwisterRandomNumber_GetNumber(igMersenneTwisterRandomNumber *self) {
    return igMersenneTwisterRandomNumber_GetNumberNonVirtual(self);
}

igMetaObject *igDataPump_GetMeta(void) {
    return g_igDataPump_metaObject;
}

igMetaObject *igBoolObject_GetMeta(void) {
    return g_igBoolObject_metaObject;
}

igMetaObject *igDataPumpInfo_GetMeta(void) {
    return g_igDataPumpInfo_metaObject;
}

igMetaObject *igDataPumpList_GetMeta(void) {
    return g_igDataPumpList_metaObject;
}

igMetaObject *igDataPumpManager_GetMeta(void) {
    return g_igDataPumpManager_metaObject;
}

igMetaObject *igFloatObject_GetMeta(void) {
    return g_igFloatObject_metaObject;
}

igMetaObject *igIntObject_GetMeta(void) {
    return g_igIntObject_metaObject;
}

igMetaObject *igMatrixObject_GetMeta(void) {
    return g_igMatrixObject_metaObject;
}

igMetaObject *igMatrixObjectList_GetMeta(void) {
    return g_igMatrixObjectList_metaObject;
}

igMetaObject *igNonRefCountedMatrixObjectList_GetMeta(void) {
    return g_igNonRefCountedMatrixObjectList_metaObject;
}

igMetaObject *igMatrixStack_GetMeta(void) {
    return g_igMatrixStack_metaObject;
}

igMetaObject *igLongStack_GetMeta(void) {
    return g_igLongStack_metaObject;
}

igMetaObject *igNonRefCountedMatrixObjectList_GetElementMeta(void) {
    return g_igMatrixObject_metaObject;
}

igMetaObject *igDataPumpList_GetElementMeta(void) {
    return g_igDataPump_metaObject;
}

igMetaObject *igMatrixObjectList_GetElementMeta(void) {
    return g_igMatrixObject_metaObject;
}

void igLongStack_TrimCapacity(igDataList *arg0) {
    int temp_a1;

    temp_a1 = arg0->_count;
    if (temp_a1 < arg0->_capacity) {
        List_Reserve(arg0, temp_a1, 8);
    }
}

void igMatrixStack_TrimCapacity(igDataList *arg0) {
    int temp_a1;

    temp_a1 = arg0->_count;
    if (temp_a1 < arg0->_capacity) {
        List_Reserve(arg0, temp_a1, 0x40);
    }
}

