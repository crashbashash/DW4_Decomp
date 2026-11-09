int memset();
void FUN_00261d40(void);
extern int DAT_00499de4;
extern char DAT_00499de8[1088];
extern char DAT_0049a228[1024];
extern int DAT_0049a628;
extern char DAT_0049a630[256];
extern unsigned short DAT_0049a730[16];
extern int DAT_0049a750;
extern int DAT_0049a754;
extern int DAT_0049a758;
extern int DAT_0049a75c;
extern int DAT_0049a760;

void FUN_00260b30(void)
{
    if (--DAT_00499de4 != 0) {
        return;
    }
    FUN_00261d40();
    DAT_0049a760 = 1;
    DAT_0049a75c = -1;
    DAT_0049a758 = 0;
    DAT_0049a754 = 0;
    DAT_0049a628 = 0;
    DAT_0049a750 = 0;
    memset(DAT_0049a730, 0, sizeof(DAT_0049a730));
    memset(DAT_0049a630, 0xFF, sizeof(DAT_0049a630));
    memset(DAT_0049a228, 0, sizeof(DAT_0049a228));
    memset(DAT_00499de8, 0, sizeof(DAT_00499de8));
}
