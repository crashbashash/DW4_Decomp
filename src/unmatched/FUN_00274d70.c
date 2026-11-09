unsigned long strtoul(const char *, char **, int);
void FUN_00265928(const char *format, ...);
extern char DAT_004f0460[];
extern char DAT_004f0478[];
extern char DAT_004f0488[];

int FUN_00274d70(char *name, int *lsn, int *size)
{
    char *p;

    p = name;
    *lsn = strtoul(p, &p, 16);
    if (*p != 0) {
        p++;
    }
    if (size != 0) {
        *size = strtoul(p, &p, 16);
    }
    FUN_00265928(DAT_004f0460, name);
    FUN_00265928(DAT_004f0478, *lsn);
    FUN_00265928(DAT_004f0488, *size);
    return 1;
}
