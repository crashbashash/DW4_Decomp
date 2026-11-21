igMetaObject *FUN_00149320(void) {
    return g_igInterfaceManager_metaObject;
}

void igInterfaceManager_AddEventProducer(void *a0, igObject *object) {
    ((Gap::Core::igObjectList *)(*(igObjectList **)((char *)a0 + 8)))->append((Gap::Core::igObject *)object);
}

int igDefaultInterfaceManager_GetMeta(void) {
    return (int)g_igDefaultInterfaceManager_metaObject;
}

igMetaObject *FUN_00149350(void) {
    return g_igControllerManager_metaObject;
}

int igControllerList_GetMeta(void) {
    return (int)g_igControllerList_metaObject;
}

igMetaObject *igNonRefCountedObjectStack_GetMeta(void) {
    return g_igNonRefCountedObjectStack_metaObject;
}

igMetaObject *igEventProducerList_GetMeta(void) {
    return g_igEventProducerList_metaObject;
}

int igControllerList_GetElementMeta(void) {
    return (int)g_igController_metaObject;
}

igMetaObject *igEventProducerList_GetElementMeta(void) {
    return g_igEventProducer_metaObject;
}

void igNonRefCountedObjectStack_TrimCapacity(igDataList *arg0) {
    int temp_a1;

    temp_a1 = arg0->_count;
    if (temp_a1 < arg0->_capacity) {
        ((Gap::Core::igDataList *)arg0)->setCapacity(temp_a1, 4);
    }
}

