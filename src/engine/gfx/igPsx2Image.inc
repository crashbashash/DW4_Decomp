void thunk_igPsx2Image_GetMetaObject(void) {
    igPsx2Image_GetMetaObject();
}

void thunk_FUN_00156300(void) {
    FUN_00156300();
}

int FUN_0014e2a0(void) {
    if (DAT_0055fe30[0] == 0) {
        DAT_0055fe30[0] = igMetaEnum_Create(&DAT_004dcbf0[0], &DAT_00488f50[0], &DAT_00488fb0[0], 0x16);
    }
    return DAT_0055fe30[0];
}

