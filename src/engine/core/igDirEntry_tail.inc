void igDirEntry_RetainSharedRef(void) {

}

void igDirEntry_ReleaseSharedRef(void) {

}

int igDirEntry_GetSharedEntry(int self) {
    return self;
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

void igDirEntry_InitDefaults(int self) {
    igObject_InitDefaults((igObject *)self);
    igNamedObject_SetName((igNamedObject *)self, 0);
}

void igDirEntry_SetRef(igDirEntry *self, int ref) {
    self->_ref = ref;
}

void igDirEntry_RetainRef(void) {

}

void igDirEntry_ReleaseRef(void) {

}

