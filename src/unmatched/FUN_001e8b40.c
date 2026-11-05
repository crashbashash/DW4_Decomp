extern int DAT_00491478[4];
extern void * DAT_0056ad80[4];
extern long long DAT_0056ae48[4];
void FUN_001e8b40(long long arg0) {
    *(long long *)((char *)(DAT_0056ad80[0]) + 288) = arg0;
    DAT_00491478[0] |= 0x40;
    DAT_0056ae48[0] |= 0x1000000000LL;
}
