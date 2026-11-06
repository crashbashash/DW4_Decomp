int FUN_002607e8();
extern int DAT_004ee970[4];
int FUN_0026c9d8(int arg0, int arg1) {
    unsigned int temp_v0;
    void **temp_v0_2;

    if ((arg0 == 0) || (arg1 < 0)) {
        FUN_002607e8(&DAT_004ee970[0]);
        return -1;
    }
    temp_v0_2 = (void **)(*(int *)((char *)(((arg1 * 4) + arg0)) + 24));
    if (temp_v0_2 != 0) {
        temp_v0 = ((int (*)())*(int *)((char *)((*temp_v0_2)) + 36))(temp_v0_2, 1);
        return (int) ((temp_v0 >> 0x1F) + temp_v0) >> 1;
    }
    return 0;
}
