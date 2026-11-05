int FUN_004578c0();
extern int DAT_0058cd80[4];
void FUN_00464110(void *arg0, void *arg1) {
    int buf[3];
    void *temp_v1;

    temp_v1 = (void *)(*(int *)((char *)(arg0) + 12));
    *(float *)((char *)(temp_v1) + 140) = *(float *)((char *)(arg1) + 0);
    *(float *)((char *)(temp_v1) + 144) = *(float *)((char *)(arg1) + 4);
    *(float *)((char *)(temp_v1) + 148) = *(float *)((char *)(arg1) + 8);
    buf[0] = 2;
    buf[1] = 0;
    buf[2] = DAT_0058cd80[0];
    FUN_004578c0(*(int *)((char *)(arg0) + 12), buf);
}
