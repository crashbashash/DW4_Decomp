extern int DAT_00481cd8[];
void FUN_001064c8(char *d, unsigned int cmd) {
    *(volatile unsigned int *)0x10002000 = cmd;
    *(int *)(d + 2096) = DAT_00481cd8[cmd >> 28];
}
