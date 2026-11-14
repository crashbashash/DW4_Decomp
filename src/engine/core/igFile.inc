void igFile_GetMetaObjectFunction(void) {
    igFile_GetMetaObject();
}

void igMemoryFile_StaticInitCallback(void) {
    igMemoryFile_CreateEntryList();
}

void igMemoryFile_ExitCallback(void) {
    igMemoryFile_ReleaseEntryList();
}

