char *strcpy(char *, const char *);
char *strcat(char *, const char *);
unsigned int strlen(const char *);
extern char DAT_004ab450[];
extern char DAT_004f03d0[];

void FUN_00275220(const char *path)
{
    char c;

    if (path == 0) {
        DAT_004ab450[0] = 0;
        return;
    }
    if (path[0] != '/' && path[0] != '\\') {
        strcpy(DAT_004ab450, "\\");
    } else {
        DAT_004ab450[0] = 0;
    }
    strcat(DAT_004ab450, path);
    c = path[strlen(path) - 1];
    if (c == '/' || c == '\\') {
        DAT_004ab450[strlen(DAT_004ab450) - 1] = 0;
    }
}
