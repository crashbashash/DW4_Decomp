extern int rebootNotifyTable;
extern int rebootNotifyCount;
extern int rebootNotifySysTable;
void memset(int, int, int);
void FUN_00115ed8(void) {
    rebootNotifyTable = 0;
    rebootNotifyCount = 0;
    memset((int)&rebootNotifySysTable, 0, 512);
}
