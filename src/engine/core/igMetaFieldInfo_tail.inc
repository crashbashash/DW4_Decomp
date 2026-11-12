int Gap__Core__igMetaFieldInfo__vfunc_23(VA_2fbf90 *arg0, int arg1, void *arg2) {
    int result = 0;
    igSmartPointer<X_2fbf90> held((X_2fbf90 *)arg2, kRetainReference);
    X_2fbf90 *field = cast0(held.get());
    VB_2fbf90 *allocator = ((VB_2fbf90 *)Memory_GetDefaultAllocator());
    if (field != 0) {
        int name = igMetaField_GetMangledName((igMetaField *)field, (void **)allocator);
        if (ObjectPointerList_FindIndex((char *)(((MetaObjectRegistryView * *)g_objectSystem)[0]->f24), field->f24) != -1 || arg0->v96(name) != 0) {
            result = FUN_002e2d30(arg1, arg0, name, arg2) & 0xFF;
        }
        allocator->v264(name);
    }
    return result;
}

