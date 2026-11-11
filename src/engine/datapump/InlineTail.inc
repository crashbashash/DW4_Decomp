int Gap__igMersenneTwisterRandomNumber__vfunc_22(void) {
    return DAT_00562b88[0];
}

unsigned int Gap__igMersenneTwisterRandomNumber__vfunc_24(igMersenneTwisterRandomNumber *self) {
    return FUN_001e6bc0(self);
}

int Gap__igDataPump__vfunc_22(void) {
    return DAT_00562c20[0];
}

int Gap__igBoolObject__vfunc_22(void) {
    return DAT_00562c50[0];
}

int Gap__igDataPumpInfo__vfunc_22(void) {
    return DAT_00562c10[0];
}

int Gap__igDataPumpList__vfunc_22(void) {
    return DAT_00562c00[0];
}

int Gap__igDataPumpManager__vfunc_22(void) {
    return DAT_00562bf0[0];
}

int Gap__igFloatObject__vfunc_22(void) {
    return DAT_00562be0[0];
}

int Gap__igIntObject__vfunc_22(void) {
    return DAT_00562bd0[0];
}

int Gap__igMatrixObject__vfunc_22(void) {
    return DAT_00562bc0[0];
}

int Gap__igMatrixObjectList__vfunc_22(void) {
    return DAT_00562bb8[0];
}

int Gap__igNonRefCountedMatrixObjectList__vfunc_22(void) {
    return DAT_00562bb0[0];
}

int Gap__igMatrixStack__vfunc_22(void) {
    return DAT_00562ba0[0];
}

int Gap__igLongStack__vfunc_22(void) {
    return DAT_00562b60[0];
}

int Gap__igNonRefCountedMatrixObjectList__vfunc_24(void) {
    return DAT_00562bc0[0];
}

int Gap__igDataPumpList__vfunc_24(void) {
    return DAT_00562c20[0];
}

int Gap__igMatrixObjectList__vfunc_24(void) {
    return DAT_00562bc0[0];
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

