int strncpy();

void FUN_002d33c0(void *arg0, int arg1) {
    if (arg1 != 0) {
        strncpy((char *)arg0 + 0x310, arg1, 0x7F);
        *((char *)arg0 + 911) = 0;
        return;
    }
    *((char *)arg0 + 784) = 0;
}
