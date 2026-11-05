int strlen();

int FUN_0015ad50(char *arg0) {
    int n = strlen();

    while (n > 0) {
        n--;
        if (arg0[n] == 0x2E) {
            return (int)arg0 + n;
        }
    }
    return 0;
}
