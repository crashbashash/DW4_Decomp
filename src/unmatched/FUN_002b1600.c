/* Reports error 0xFF000701 for the handle through sfd_ReportError. */
int sfd_ReportError();

void FUN_002b1600(int handle) {
    sfd_ReportError(handle, 0xFF000701);
}
