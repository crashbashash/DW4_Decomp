void Gap__Core__igExternalInfoEntry__vfunc_31(igExternalInfoEntry *self, igDirectory *directory) {
    void **info;

    info = (void **)(((void **)igDirectory_FindInfoByName((int *)(*(int *)(((igDirectoryList *)directory->_externalDirectoryList)->_data + (self->_directoryIndex * 4))), self->_infoName)));
    if (info != 0) {
        FUN_002d7da0((A7da0 *)directory, self->_index, ((DW4VC_96_1 *)(info))->vX((int)(self->_key)));
        return;
    }
    FUN_002d7da0((A7da0 *)directory, self->_index, 0);
}

