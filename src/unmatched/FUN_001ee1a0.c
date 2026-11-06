extern void * DAT_00568e58[4];
void FUN_001ee1a0(void *arg0) {
    *(int *)((char *)arg0 + 20) = (int) DAT_00568e58[0];
    *(int *)((char *)arg0 + 24) = 0;
    DAT_00568e58[0] = arg0;
}
