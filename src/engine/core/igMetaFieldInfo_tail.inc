int igMetaFieldInfo_FindObjectReference(igMetaFieldInfoView *self, int directory, void *target) {
    int result = 0;
    igSmartPointer<igMetaField> held((igMetaField *)target, kRetainReference);
    igMetaField *field = cast0(held.get());
    igMemoryPoolView *allocator = ((igMemoryPoolView *)Memory_GetDefaultAllocator());
    if (field != 0) {
        int name = igMetaField_GetMangledName(field, (void **)allocator);
        if (ObjectPointerList_FindIndex((char *)((*(ObjectSystemView * *)&g_objectSystem)->metaRegistry), field->_parentMetaObject) != -1 || self->FindByName(name) != 0) {
            result = igDirectory_AddExternalInfoRef((igDirectoryView *)directory, (igInfoView *)self, (char *)name, (igObject *)target) & 0xFF;
        }
        allocator->Free((void *)name);
    }
    return result;
}

