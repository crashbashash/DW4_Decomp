void igExternalInfoEntry_Resolve(igExternalInfoEntry *self, igDirectory *directory) {
    void **info;

    info = (void **)(((void **)igDirectory_FindInfoByName((int *)(*(int *)(((igDirectoryList *)directory->_externalDirectoryList)->_data + (self->_directoryIndex * 4))), self->_infoName)));
    if (info != 0) {
        igDirectory_SetEntryRef((igDirectoryView *)directory, self->_index, ((igInfoView *)(info))->GetFieldValueByName((int)(self->_key)));
        return;
    }
    igDirectory_SetEntryRef((igDirectoryView *)directory, self->_index, 0);
}

/* Adds a directory entry that finds `object` again on load through `info`, under `key`; an object
 * already in the directory is not added twice. */
bool FUN_002e2d30(igDirectoryView *directory, igInfoView *info, char *key, igObject *object) {
    int index = igDirectory_FindSortedInsertIndex(directory, (igMetaField *)DAT_00586730[0], (unsigned int)object);
    if (index >= 0 && index < directory->_count && (igObject *)igDirectory_GetObject(directory, index) == object) {
        return 0;
    }
    igSmartPointer<igExternalInfoEntryView> entry((igExternalInfoEntryView *)igExternalInfoEntry_Create(FUN_00301000(directory)));
    entry.get()->setDirectoryIndex(((igSmartPointer<igTDataList<igDirectoryView *> > &)directory->_externalDirectoryList)->find((igDirectoryView *)info->_directory));
    entry.get()->setInfoName(info->_name != 0 ? (char *)info->_name : (char *)emptyString);
    entry.get()->setKey(key);
    entry.get()->vfunc_23((int)object);
    entry.get()->_index = index;
    insertObject((igDataList *)directory, index, entry.get());
    return 1;
}
