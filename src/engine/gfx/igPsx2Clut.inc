void thunk_igPsx2Clut_GetMetaObject(void) {
    igPsx2Clut_GetMetaObject();
}

int FUN_0014fd40(void) {
    if (DAT_0055fef8[0] == 0) {
        DAT_0055fef8[0] = (int)igMetaObject_Create(Memory_GetAllocatorBySelector(DAT_00587040[0]));
    }
    return DAT_0055fef8[0];
}

