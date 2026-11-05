typedef struct NamedEntry { int p0[2]; char *name; } NamedEntry;
typedef struct LogoSeqState { char p0[60]; int mode; int sub; char p68[150]; unsigned char flag; } LogoSeqState;
extern "C" {
int igStrCmp(char *, int *);
extern int DAT_004e0858[4];
extern int DAT_0050efa8[4];
extern int DAT_0050efb0[4];
extern int DAT_0050efb8[4];
extern int DAT_0050efc0[4];
extern int DAT_0050efc8[4];
extern int DAT_0050efd0[4];
int FUN_00391a10(int arg0, LogoSeqState *arg1, NamedEntry *arg2);
}
int FUN_00391a10(int arg0, LogoSeqState *arg1, NamedEntry *arg2) {
    char *s;
    if (arg2->name != 0) s = arg2->name;
    else s = (char *)&DAT_004e0858[0];
    if (igStrCmp(s, &DAT_0050efa8[0]) == 0) {
        arg1->mode = 1;
        arg1->sub = 0;
    } else if (igStrCmp(s, &DAT_0050efb0[0]) == 0) {
        arg1->mode = 2;
        arg1->sub = 0;
    } else if (igStrCmp(s, &DAT_0050efb8[0]) == 0) {
        arg1->mode = 3;
        arg1->sub = 0;
    } else if (igStrCmp(s, &DAT_0050efc0[0]) == 0) {
        arg1->mode = 4;
        arg1->sub = 0;
    } else if (igStrCmp(s, &DAT_0050efc8[0]) == 0) {
        arg1->flag = 1;
    } else if (igStrCmp(s, &DAT_0050efd0[0]) == 0) {
        arg1->flag = 0;
    }
    return 1;
}
