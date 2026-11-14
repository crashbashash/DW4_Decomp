int Gap__Core__igMetaFieldInfo__vfunc_23(igMetaFieldInfoView *arg0, int arg1, void *arg2) {
    int result = 0;
    igSmartPointer<igMetaField> held((igMetaField *)arg2, kRetainReference);
    igMetaField *field = cast0(held.get());
    igMemoryPoolView *allocator = ((igMemoryPoolView *)Memory_GetDefaultAllocator());
    if (field != 0) {
        int name = igMetaField_GetMangledName(field, (void **)allocator);
        if (ObjectPointerList_FindIndex((char *)(((ObjectSystemView **)g_objectSystem)[0]->metaRegistry), field->_parentMetaObject) != -1 || arg0->FindByName(name) != 0) {
            result = FUN_002e2d30(arg1, arg0, name, arg2) & 0xFF;
        }
        allocator->Free((void *)name);
    }
    return result;
}

