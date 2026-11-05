int strlen();

int FUN_002404b0(int arg0, char *arg1) {
    int h;
    int n;

    h = 0;
    n = strlen(arg1);
    while (n--) {
        h += (h << 5) + (h << 2) + *arg1;
        arg1++;
    }
    return arg0 ^ h;
}
