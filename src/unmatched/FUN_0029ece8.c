int sfd_ReportError();
int sfd_CheckHn();
int FUN_002ada78();

int FUN_0029ece8(int arg0) {
    if (sfd_CheckHn() != 0) {
        return sfd_ReportError(0, 0xFF000161, 1);
    }
    FUN_002ada78(arg0, 0x31, 1);
    return 0;
}
