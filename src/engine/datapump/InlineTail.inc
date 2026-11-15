igMetaObject *Gap__igMersenneTwisterRandomNumber__vfunc_22(void) {
    return g_igMersenneTwisterRandomNumber_metaObject;
}

unsigned int Gap__igMersenneTwisterRandomNumber__vfunc_24(igMersenneTwisterRandomNumber *self) {
    return FUN_001e6bc0(self);
}

igMetaObject *Gap__igDataPump__vfunc_22(void) {
    return g_igDataPump_metaObject;
}

igMetaObject *Gap__igBoolObject__vfunc_22(void) {
    return g_igBoolObject_metaObject;
}

igMetaObject *Gap__igDataPumpInfo__vfunc_22(void) {
    return g_igDataPumpInfo_metaObject;
}

igMetaObject *Gap__igDataPumpList__vfunc_22(void) {
    return g_igDataPumpList_metaObject;
}

igMetaObject *Gap__igDataPumpManager__vfunc_22(void) {
    return g_igDataPumpManager_metaObject;
}

igMetaObject *Gap__igFloatObject__vfunc_22(void) {
    return g_igFloatObject_metaObject;
}

igMetaObject *Gap__igIntObject__vfunc_22(void) {
    return g_igIntObject_metaObject;
}

igMetaObject *Gap__igMatrixObject__vfunc_22(void) {
    return g_igMatrixObject_metaObject;
}

igMetaObject *Gap__igMatrixObjectList__vfunc_22(void) {
    return g_igMatrixObjectList_metaObject;
}

igMetaObject *Gap__igNonRefCountedMatrixObjectList__vfunc_22(void) {
    return g_igNonRefCountedMatrixObjectList_metaObject;
}

igMetaObject *Gap__igMatrixStack__vfunc_22(void) {
    return g_igMatrixStack_metaObject;
}

igMetaObject *Gap__igLongStack__vfunc_22(void) {
    return g_igLongStack_metaObject;
}

igMetaObject *Gap__igNonRefCountedMatrixObjectList__vfunc_24(void) {
    return g_igMatrixObject_metaObject;
}

igMetaObject *Gap__igDataPumpList__vfunc_24(void) {
    return g_igDataPump_metaObject;
}

igMetaObject *Gap__igMatrixObjectList__vfunc_24(void) {
    return g_igMatrixObject_metaObject;
}

void Gap__igLongStack__vfunc_18(igDataList *arg0) {
    int temp_a1;

    temp_a1 = arg0->_count;
    if (temp_a1 < arg0->_capacity) {
        List_Reserve(arg0, temp_a1, 8);
    }
}

void Gap__igMatrixStack__vfunc_18(igDataList *arg0) {
    int temp_a1;

    temp_a1 = arg0->_count;
    if (temp_a1 < arg0->_capacity) {
        List_Reserve(arg0, temp_a1, 0x40);
    }
}

