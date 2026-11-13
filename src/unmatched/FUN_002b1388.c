/* Reports error 0xFF000601 for the handle through sfd_ReportError. */
int sfd_ReportError();

void FUN_002b1388(int handle) {
    sfd_ReportError(handle, 0xFF000601);
}
