int sfd_ReportError();
int FUN_002a2cc8();

void FUN_002a2c78(void *arg0) {
    if (FUN_002a2cc8(**(int **)((char *)(arg0) + 8052)) != 0) {
        sfd_ReportError(arg0, 0xFF000D0A);
    }
}
