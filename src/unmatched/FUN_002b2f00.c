int memset();
extern int DAT_004beb58[4];
void FUN_002b2f00(void) {
    memset(&DAT_004beb58[0], 0, 0xC8);
    *(int *)((char *)&(DAT_004beb58[0]) + 4) = 8;
}
