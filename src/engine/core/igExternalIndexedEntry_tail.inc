void igExternalIndexedEntry_Resolve(igExternalIndexedEntry *self, void *directory) {
    ((igDirEntryView *)self)->setRef((int)(igDirectory_GetObject((void *)((int *)((igObjectList *)((igDirectory *)directory)->_externalDirectoryList)->_data)[self->_directoryIndex], self->_entryIndex)));
    igDirectory_SetEntryRef((igDirectoryView *)directory, self->_index, self->_ref);
}

