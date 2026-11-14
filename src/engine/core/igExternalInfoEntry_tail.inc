void Gap__Core__igExternalInfoEntry__vfunc_31(igExternalInfoEntry *self, igDirectory *directory) {
    void **info;

    info = (void **)(((void **)igDirectory_FindInfoByName((int *)(*(int *)(((igDirectoryList *)directory->_externalDirectoryList)->_data + (self->_directoryIndex * 4))), self->_infoName)));
    if (info != 0) {
        FUN_002d7da0((igDirectoryView *)directory, self->_index, ((igInfoView *)(info))->GetFieldValueByName((int)(self->_key)));
        return;
    }
    FUN_002d7da0((igDirectoryView *)directory, self->_index, 0);
}

