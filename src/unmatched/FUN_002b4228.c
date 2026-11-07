int FUN_002b4b88();
int memset();
extern int DAT_004bf010[4];
void FUN_002b4228(void) {
    memset(&DAT_004bf010[0], 0, 0x26C);
    *(int *)((char *)&(DAT_004bf010[0]) + 8) = 8;
    FUN_002b4b88(0);
}
