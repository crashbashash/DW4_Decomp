int iReferSemaStatus();
int iSignalSema();
extern int DAT_00569030[4];
void FUN_001f0520(void) {
    int buf[8];

    iReferSemaStatus(DAT_00569030[0], buf);
    if (buf[0] != buf[1]) {
        iSignalSema(DAT_00569030[0]);
    }
}
