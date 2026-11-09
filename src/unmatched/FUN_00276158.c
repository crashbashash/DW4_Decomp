unsigned int strlen();

int FUN_00276158(char *path)
{
    unsigned int len;
    unsigned int i;

    len = strlen(path);
    if (len > 16) {
        len = 16;
    }
    for (i = 0; i < len; i++) {
        if (path[i] == ':') {
            return 1;
        }
    }
    return 0;
}
