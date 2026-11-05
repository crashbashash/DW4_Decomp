int FUN_004578c0();
extern int DAT_0058cad8[4];
void FUN_00462dc0(void *arg0) {
    int buf[3];

    *(int *)((char *)(*(int *)((char *)(arg0) + 20)) + 212) = 1;
    buf[0] = 2;
    buf[1] = 0;
    buf[2] = DAT_0058cad8[0];
    FUN_004578c0(*(int *)((char *)(arg0) + 20), buf, 1);
}
