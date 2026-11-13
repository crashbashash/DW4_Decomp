/* Reports error code 0xFF000D0B for the handle through sfd_ReportError. */
extern int sfd_ReportError(void *handle, int code);

void FUN_002a2d00(void *handle) {
    sfd_ReportError(handle, 0xFF000D0B);
}
