int strncpy();
extern void * DAT_004c1ec8[4];
struct O { char pad[400]; char buf[128]; };
void FUN_002d32b0(struct O *arg0, char *arg1) {
    if (arg1 != 0) {
        strncpy(arg0->buf, arg1, 0x7F);
        arg0->buf[127] = 0;
    } else {
        arg0->buf[0] = 0;
    }
    if ((arg1 != 0) && (*arg1 != 0)) {
        DAT_004c1ec8[0] = arg0->buf;
    }
}
