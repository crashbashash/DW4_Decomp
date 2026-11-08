int strlen();
extern char _ctype_[400];
void FUN_002db4e0(int arg0, char *arg1) {
    int i;

    i = strlen(arg1) - 1;
    while (i >= 0 && (_ctype_[arg1[i] + 1] & 8)) {
        arg1[i] = 0;
        i--;
    }
}
