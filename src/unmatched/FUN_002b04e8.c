int memset();

void FUN_002b04e8(void *arg0) {
    memset((char *)arg0 + 0x18, 0, 0xF0);
    *(int *)((char *)(arg0) + 20) = 0;
    *(int *)((char *)(arg0) + 412) = (int)((int) (*(int *)((char *)(arg0) + 412) + 1));
}
