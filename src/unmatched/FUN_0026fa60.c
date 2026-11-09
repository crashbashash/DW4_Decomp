int strlen();
void *memcpy();
void FUN_0026f530(const char *message);
void FUN_0026f928(char *text);
int FUN_0026fb28(char *name, int len);
extern char DAT_004eefb0[];
extern char DAT_004eefd8[];
extern char DAT_0056e420[];

void FUN_0026fa60(char *name)
{
    int len;

    if (name == 0) {
        FUN_0026f530(DAT_004eefb0);
        return;
    }
    len = strlen(name);
    if (len == 0) {
        DAT_0056e420[0] = 0;
        return;
    }
    FUN_0026f928(name);
    if (FUN_0026fb28(name, len) == 1) {
        memcpy(DAT_0056e420, name, len + 1);
        return;
    }
    FUN_0026f530(DAT_004eefd8);
}
