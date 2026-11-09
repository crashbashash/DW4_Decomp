int strlen();
int FUN_002746a0();

int FUN_002746f8(char *a, char *b)
{
    int len;
    int i;

    len = strlen(a);
    if (len != strlen(b)) {
        return -1;
    }
    for (i = 0; i < len; i++) {
        if (FUN_002746a0(a[i], b[i]) != 0) {
            return -1;
        }
    }
    return 0;
}
