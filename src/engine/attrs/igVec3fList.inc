int igVec3fList_GetMeta(void) {
    return (int)g_igVec3fList_metaObject;
}

int igDataList_GetMetaObject_Virtual(void) {
    return (int)Gap::Core::igDataList::getClassMeta();
}

