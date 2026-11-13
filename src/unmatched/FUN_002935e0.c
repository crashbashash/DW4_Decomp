void *mwsfd_GetWork();

void FUN_002935e0(int arg0) {
    void *temp_v0;

    temp_v0 = (void *)(mwsfd_GetWork());
    ((int (*)())*(int *)((char *)(temp_v0) + 40))(*(int *)((char *)(temp_v0) + 48), arg0);
}
