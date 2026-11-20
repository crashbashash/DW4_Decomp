void igNonRefCountedObjectList_UserPreWrite(igNonRefCountedObjectListView *self)
{
    self->vfunc_16();
}

int igNonRefCountedObjectList_GetMeta(void) {
    return (int)g_igNonRefCountedObjectList_metaObject;
}

igMetaObject *igNonRefCountedObjectList_GetElementMeta(void) {
    return Gap::Core::igObject::getClassMeta();
}

