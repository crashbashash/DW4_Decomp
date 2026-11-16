igMetaObject *FUN_00149320(void) {
    return g_igInterfaceManager_metaObject;
}

void FUN_00149330(void *a0, igObject *object) {
    ObjectList_AppendRetained(*(igObjectList **)((char *)a0 + 8), object);
}

int Gap__igDefaultInterfaceManager__vfunc_22(void) {
    return (int)g_igDefaultInterfaceManager_metaObject;
}

igMetaObject *FUN_00149350(void) {
    return g_igControllerManager_metaObject;
}

int Gap__igControllerList__vfunc_22(void) {
    return (int)g_igControllerList_metaObject;
}

igMetaObject *Gap__igNonRefCountedObjectStack__vfunc_22(void) {
    return g_igNonRefCountedObjectStack_metaObject;
}

igMetaObject *Gap__igEventProducerList__vfunc_22(void) {
    return g_igEventProducerList_metaObject;
}

int Gap__igControllerList__vfunc_24(void) {
    return (int)g_igController_metaObject;
}

igMetaObject *Gap__igEventProducerList__vfunc_24(void) {
    return g_igEventProducer_metaObject;
}

void Gap__igNonRefCountedObjectStack__vfunc_18(igDataList *arg0) {
    int temp_a1;

    temp_a1 = arg0->_count;
    if (temp_a1 < arg0->_capacity) {
        List_Reserve(arg0, temp_a1, 4);
    }
}

