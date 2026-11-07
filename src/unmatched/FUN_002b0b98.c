struct B { char b[274]; };
extern struct B DAT_004f50d0;
extern char *DAT_004beb44;
extern int DAT_004beb40;
extern char *DAT_004beb4c;
extern char *DAT_004beb50;
void *memset();
char *strcpy();
int strlen();
void FUN_002b0b98(void) {
    struct B s = DAT_004f50d0;
    if (DAT_004beb44 != 0) {
        memset(DAT_004beb44, 0, DAT_004beb40);
DAT_004beb4c = DAT_004beb44;
strcpy(DAT_004beb4c, s.b);
DAT_004beb4c += strlen(s.b);
DAT_004beb50 = DAT_004beb4c;
    }
}
