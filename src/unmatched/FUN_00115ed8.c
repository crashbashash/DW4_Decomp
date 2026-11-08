extern int DAT_00483528;
extern int DAT_0048352c;
extern int DAT_0055cd48;
void memset(int, int, int);
void FUN_00115ed8(void) {
    DAT_00483528 = 0;
    DAT_0048352c = 0;
    memset((int)&DAT_0055cd48, 0, 512);
}
