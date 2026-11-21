/* Returns the published default descriptor of igVec4fMetaField: the cached instance that the
 * class's registration wrapper creates on first use. */

/* Returns the published default descriptor of igVec4fArrayMetaField: the cached instance that the
 * class's registration wrapper creates on first use. */

/* Returns the published default descriptor of igVec3fMetaField: the cached instance that the
 * class's registration wrapper creates on first use. */

/* Returns the published default descriptor of igVec2fMetaField: the cached instance that the
 * class's registration wrapper creates on first use. */

/* Returns the published default descriptor of igMatrix44fMetaField: the cached instance that the
 * class's registration wrapper creates on first use. */

igMetaObject *igAABox_GetMeta(void) {
    return g_igAABox_metaObject;
}

igMetaObject *igAABoxList_GetMeta(void) {
    return g_igAABoxList_metaObject;
}

igMetaObject *igVec2fList_GetMeta(void) {
    return g_igVec2fList_metaObject;
}

igMetaObject *igVec4ucList_GetMeta(void) {
    return g_igVec4ucList_metaObject;
}

igMetaObject *igQuaternionfList_GetMeta(void) {
    return g_igQuaternionfList_metaObject;
}

igMetaObject *igMatrix44fList_GetMeta(void) {
    return g_igMatrix44fList_metaObject;
}

igMetaObject *igIntersectionFunctionList_GetMeta(void) {
    return g_igIntersectionFunctionList_metaObject;
}

igMetaObject *igExtendByFunctionList_GetMeta(void) {
    return g_igExtendByFunctionList_metaObject;
}

igMetaObject *igContainsFunctionList_GetMeta(void) {
    return g_igContainsFunctionList_metaObject;
}

igMetaObject *igRayIntersectionFunctionList_GetMeta(void) {
    return g_igRayIntersectionFunctionList_metaObject;
}

igMetaObject *igExtendByRayFunctionList_GetMeta(void) {
    return g_igExtendByRayFunctionList_metaObject;
}

igMetaObject *igContainsRayFunctionList_GetMeta(void) {
    return g_igContainsRayFunctionList_metaObject;
}

igMetaObject *igExtendByVecFunctionList_GetMeta(void) {
    return g_igExtendByVecFunctionList_metaObject;
}

igMetaObject *igContainsVecFunctionList_GetMeta(void) {
    return g_igContainsVecFunctionList_metaObject;
}

igMetaObject *igTransformFunctionList_GetMeta(void) {
    return g_igTransformFunctionList_metaObject;
}

igMetaObject *igEmptyFunctionList_GetMeta(void) {
    return g_igEmptyFunctionList_metaObject;
}

igMetaObject *igIsEmptyFunctionList_GetMeta(void) {
    return g_igIsEmptyFunctionList_metaObject;
}

igMetaObject *igGetCenterFunctionList_GetMeta(void) {
    return g_igGetCenterFunctionList_metaObject;
}

igMetaObject *igPlane_GetMeta(void) {
    return g_igPlane_metaObject;
}

igMetaObject *igRay_GetMeta(void) {
    return g_igRay_metaObject;
}

igMetaObject *igRayList_GetMeta(void) {
    return g_igRayList_metaObject;
}

igMetaObject *igSphere_GetMeta(void) {
    return g_igSphere_metaObject;
}

igMetaObject *igVectorBlending_GetMeta(void) {
    return g_igVectorBlending_metaObject;
}

igMetaObject *igVectorMorphing_GetMeta(void) {
    return g_igVectorMorphing_metaObject;
}

igMetaObject *igVolumeList_GetMeta(void) {
    return g_igVolumeList_metaObject;
}

int igMatrix44fList_GetElementSize(void) {
    return 0x40;
}

int igQuaternionfList_GetElementSize(void) {
    return 0x10;
}

int igVec4ucList_GetElementSize(void) {
    return 4;
}

int igVec2fList_GetElementSize(void) {
    return 8;
}

int igGetCenterFunctionList_GetElementSize(void) {
    return 4;
}

int igIsEmptyFunctionList_GetElementSize(void) {
    return 4;
}

int igEmptyFunctionList_GetElementSize(void) {
    return 4;
}

int igTransformFunctionList_GetElementSize(void) {
    return 4;
}

int igContainsVecFunctionList_GetElementSize(void) {
    return 4;
}

int igExtendByVecFunctionList_GetElementSize(void) {
    return 4;
}

int igContainsRayFunctionList_GetElementSize(void) {
    return 4;
}

int igExtendByRayFunctionList_GetElementSize(void) {
    return 4;
}

int igRayIntersectionFunctionList_GetElementSize(void) {
    return 4;
}

int igContainsFunctionList_GetElementSize(void) {
    return 4;
}

int igExtendByFunctionList_GetElementSize(void) {
    return 4;
}

int igIntersectionFunctionList_GetElementSize(void) {
    return 4;
}

igMetaObject *igAABoxList_GetElementMeta(void) {
    return g_igAABox_metaObject;
}

igMetaObject *igRayList_GetElementMeta(void) {
    return g_igRay_metaObject;
}

igMetaObject *igVolumeList_GetElementMeta(void) {
    return g_igVolume_metaObject;
}

void igIntersectionFunctionList_TrimCapacity(igDataList *arg0) {
    int temp_a1;

    temp_a1 = arg0->_count;
    if (temp_a1 < arg0->_capacity) {
        ((Gap::Core::igDataList *)arg0)->setCapacity(temp_a1, 4);
    }
}

void igExtendByFunctionList_TrimCapacity(igDataList *arg0) {
    int temp_a1;

    temp_a1 = arg0->_count;
    if (temp_a1 < arg0->_capacity) {
        ((Gap::Core::igDataList *)arg0)->setCapacity(temp_a1, 4);
    }
}

void igContainsFunctionList_TrimCapacity(igDataList *arg0) {
    int temp_a1;

    temp_a1 = arg0->_count;
    if (temp_a1 < arg0->_capacity) {
        ((Gap::Core::igDataList *)arg0)->setCapacity(temp_a1, 4);
    }
}

void igRayIntersectionFunctionList_TrimCapacity(igDataList *arg0) {
    int temp_a1;

    temp_a1 = arg0->_count;
    if (temp_a1 < arg0->_capacity) {
        ((Gap::Core::igDataList *)arg0)->setCapacity(temp_a1, 4);
    }
}

void igExtendByRayFunctionList_TrimCapacity(igDataList *arg0) {
    int temp_a1;

    temp_a1 = arg0->_count;
    if (temp_a1 < arg0->_capacity) {
        ((Gap::Core::igDataList *)arg0)->setCapacity(temp_a1, 4);
    }
}

void igContainsRayFunctionList_TrimCapacity(igDataList *arg0) {
    int temp_a1;

    temp_a1 = arg0->_count;
    if (temp_a1 < arg0->_capacity) {
        ((Gap::Core::igDataList *)arg0)->setCapacity(temp_a1, 4);
    }
}

void igExtendByVecFunctionList_TrimCapacity(igDataList *arg0) {
    int temp_a1;

    temp_a1 = arg0->_count;
    if (temp_a1 < arg0->_capacity) {
        ((Gap::Core::igDataList *)arg0)->setCapacity(temp_a1, 4);
    }
}

void igContainsVecFunctionList_TrimCapacity(igDataList *arg0) {
    int temp_a1;

    temp_a1 = arg0->_count;
    if (temp_a1 < arg0->_capacity) {
        ((Gap::Core::igDataList *)arg0)->setCapacity(temp_a1, 4);
    }
}

void igTransformFunctionList_TrimCapacity(igDataList *arg0) {
    int temp_a1;

    temp_a1 = arg0->_count;
    if (temp_a1 < arg0->_capacity) {
        ((Gap::Core::igDataList *)arg0)->setCapacity(temp_a1, 4);
    }
}

void igEmptyFunctionList_TrimCapacity(igDataList *arg0) {
    int temp_a1;

    temp_a1 = arg0->_count;
    if (temp_a1 < arg0->_capacity) {
        ((Gap::Core::igDataList *)arg0)->setCapacity(temp_a1, 4);
    }
}

void igIsEmptyFunctionList_TrimCapacity(igDataList *arg0) {
    int temp_a1;

    temp_a1 = arg0->_count;
    if (temp_a1 < arg0->_capacity) {
        ((Gap::Core::igDataList *)arg0)->setCapacity(temp_a1, 4);
    }
}

void igGetCenterFunctionList_TrimCapacity(igDataList *arg0) {
    int temp_a1;

    temp_a1 = arg0->_count;
    if (temp_a1 < arg0->_capacity) {
        ((Gap::Core::igDataList *)arg0)->setCapacity(temp_a1, 4);
    }
}

void igVec2fList_TrimCapacity(igDataList *arg0) {
    int temp_a1;

    temp_a1 = arg0->_count;
    if (temp_a1 < arg0->_capacity) {
        ((Gap::Core::igDataList *)arg0)->setCapacity(temp_a1, 8);
    }
}

void igVec4ucList_TrimCapacity(igDataList *arg0) {
    int temp_a1;

    temp_a1 = arg0->_count;
    if (temp_a1 < arg0->_capacity) {
        ((Gap::Core::igDataList *)arg0)->setCapacity(temp_a1, 4);
    }
}

void igQuaternionfList_TrimCapacity(igDataList *arg0) {
    int temp_a1;

    temp_a1 = arg0->_count;
    if (temp_a1 < arg0->_capacity) {
        ((Gap::Core::igDataList *)arg0)->setCapacity(temp_a1, 0x10);
    }
}

void igMatrix44fList_TrimCapacity(igDataList *arg0) {
    int temp_a1;

    temp_a1 = arg0->_count;
    if (temp_a1 < arg0->_capacity) {
        ((Gap::Core::igDataList *)arg0)->setCapacity(temp_a1, 0x40);
    }
}

}
