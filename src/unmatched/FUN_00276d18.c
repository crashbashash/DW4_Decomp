char *strcpy(char *, const char *);
extern char DAT_004aba08[];

void FUN_00276d18(const char *path)
{
    if (path == 0) {
        DAT_004aba08[0] = 0;
        return;
    }
    if (path[0] != '/' && path[0] != '\\') {
        strcpy(DAT_004aba08, "/");
    } else {
        DAT_004aba08[0] = 0;
    }
    strcpy(DAT_004aba08, path);
}
