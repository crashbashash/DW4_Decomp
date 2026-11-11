int FUN_00149320(void) {
    return DAT_0055f5e8[0];
}

void FUN_00149330(int a0) {
    ObjectList_AppendRetained(*(int *)((char *)a0 + 8));
}

int Gap__igDefaultInterfaceManager__vfunc_22(void) {
    return (int)g_igDefaultInterfaceManager_metaObject[0];
}

int FUN_00149350(void) {
    return DAT_0055f698[0];
}

int Gap__igControllerList__vfunc_22(void) {
    return (int)g_igControllerList_metaObject[0];
}

int Gap__igNonRefCountedObjectStack__vfunc_22(void) {
    return DAT_00562b78[0];
}

int Gap__igEventProducerList__vfunc_22(void) {
    return DAT_0055f5f8[0];
}

int Gap__igControllerList__vfunc_24(void) {
    return (int)g_igController_metaObject[0];
}

int Gap__igEventProducerList__vfunc_24(void) {
    return DAT_0055f600[0];
}

void Gap__igNonRefCountedObjectStack__vfunc_18(igDataList *arg0) {
    int temp_a1;

    temp_a1 = arg0->_count;
    if (temp_a1 < arg0->_capacity) {
        List_Reserve(arg0, temp_a1, 4);
    }
}

