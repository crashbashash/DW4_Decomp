void igPsx2Media_GetMetaObjectFunction(void) {
    igPsx2Media_GetMetaObject();
}

void igMedia_StaticInitCallback(void) {
    igMedia_CreateMediaList();
}

void igMedia_ExitCallback(void) {
    igMedia_ReleaseMediaList();
}

