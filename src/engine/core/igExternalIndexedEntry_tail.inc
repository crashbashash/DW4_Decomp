void igExternalIndexedEntry_Resolve(igExternalIndexedEntry *arg0, void *arg1) {
    ((igDirEntryView *)(((char *)(arg0) + 0)))->vfunc_23((int)(igDirectory_GetObject((void *)(*(int *)(*(int *)((char *)(*(int *)((char *)(arg1) + 24)) + 16) + (arg0->_directoryIndex * 4))), arg0->_entryIndex)));
    igDirectory_SetEntryRef((igDirectoryView *)arg1, arg0->_index, arg0->_ref);
}

