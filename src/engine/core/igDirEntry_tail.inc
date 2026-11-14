void igDirEntry_RetainSharedRef(void) {

}

void igDirEntry_ReleaseSharedRef(void) {

}

int igDirEntry_GetSharedEntry(int arg0) {
    return arg0;
}

int igDirEntry_IsRefMemory(void) {
    return 0;
}

void igDirEntry_SetMemoryPoolHandle(void) {

}

int igDirEntry_GetMemoryPoolHandle(void) {
    return -1;
}

void igDirEntry_WriteMemory(void) {

}

void igDirEntry_WriteObject(void) {

}

void igDirEntry_PrepareWrite(void) {

}

void igDirEntry_ComputeWriteSize(void) {

}

void igDirEntry_ReadMemory(void) {

}

void igDirEntry_RegisterRef(void) {

}

void igDirEntry_PostProcess(void) {

}

void igDirEntry_ResolveRefOld(void) {

}

void igDirEntry_ResolveRef(void) {

}

void igDirEntry_Resolve(void) {

}

void igDirEntry_CreateRef(void) {

}

void igDirEntry_InitDefaults(int arg0) {
    igObject_InitDefaults(arg0);
    igNamedObject_SetName((igNamedObject *)arg0, 0);
}

void igDirEntry_SetRef(void *arg0, int arg1) {
    *(int *)((char *)(arg0) + 24) = arg1;
}

void igDirEntry_RetainRef(void) {

}

void igDirEntry_ReleaseRef(void) {

}

