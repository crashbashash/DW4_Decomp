void Gap__Core__igExternalInfoEntry__vfunc_31(igExternalInfoEntry *self, igDirectory *directory) {
    void **info;

    info = (void **)(((void **)igDirectory_FindInfoByName((int *)(*(int *)(((igDirectoryList *)directory->_externalDirectoryList)->_data + (self->_directoryIndex * 4))), self->_infoName)));
    if (info != 0) {
        FUN_002d7da0((igDirectoryView *)directory, self->_index, ((igInfoView *)(info))->GetFieldValueByName((int)(self->_key)));
        return;
    }
    FUN_002d7da0((igDirectoryView *)directory, self->_index, 0);
}

/* Adds a directory entry that finds `object` again on load through `info`, under `key`; an object
 * already in the directory is not added twice. */
bool FUN_002e2d30(igDirectoryView *directory, igInfoView *info, char *key, igObject *object) {
    int index = FUN_002d86b0(directory, (igMetaField *)DAT_00586730[0], (unsigned int)object);
    if (index >= 0 && index < directory->_count && (igObject *)FUN_002d7d60(directory, index) == object) {
        return 0;
    }
    igSmartPointer<igExternalInfoEntryView> entry((igExternalInfoEntryView *)FUN_002c4f80(FUN_00301000(directory)));
    entry.get()->setDirectoryIndex(((igSmartPointer<igTDataList<igDirectoryView *> > &)directory->_externalDirectoryList)->find((igDirectoryView *)info->_directory));
    entry.get()->setInfoName(info->_name != 0 ? (char *)info->_name : (char *)emptyString);
    entry.get()->setKey(key);
    entry.get()->vfunc_23((int)object);
    entry.get()->_index = index;
    insertObject((igDataList *)directory, index, entry.get());
    return 1;
}
