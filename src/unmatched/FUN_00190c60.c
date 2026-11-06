int igMatrix44f_SetIdentity();

void FUN_00190c60(void *arg0, void *arg1) {
    igMatrix44f_SetIdentity();
    *(float *)((char *)(arg0) + 0) = (float) *(float *)((char *)(arg1) + 0);
    *(float *)((char *)(arg0) + 20) = (float) *(float *)((char *)(arg1) + 4);
    *(float *)((char *)(arg0) + 40) = (float) *(float *)((char *)(arg1) + 8);
}
