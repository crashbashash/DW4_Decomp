void igPsx2ThreadManager_GetMetaObjectFunction(void) {
    igPsx2ThreadManager_GetMetaObject();
}

void igThreadManager_StaticInitCallback(void) {
    igPsx2ThreadManager_CreateGlobal();
}

void igThreadManager_ExitCallback(void) {
    igPsx2ThreadManager_DestroyGlobal();
}

