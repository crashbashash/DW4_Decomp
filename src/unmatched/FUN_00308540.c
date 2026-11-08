int vsnprintf();
extern int (*DAT_004c22e0[4])(int, char *);

int FUN_00308540(int arg0, int arg1, int arg2) {
    char buf[0x1000];
    int r;

    if (DAT_004c22e0[0] == 0) {
        return 0;
    }
    r = vsnprintf(buf, 0x1000, arg1, arg2);
    if ((r < 0) || (r >= 0x1000)) {
        buf[0xFFF] = 0;
    }
    return DAT_004c22e0[0](arg0, buf);
}
