int _sceSifSendCmd(int, int, int, int, int, int, int);
int isceSifSendCmd(int a0, int a1, int a2, int a3, int a4, int a5) {
    return _sceSifSendCmd(a0, 1, a1, a2, a3, a4, a5);
}
