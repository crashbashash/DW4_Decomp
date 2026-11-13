extern int (*DAT_004bcc48)();

void mpvhook_GetDispSize(void) {
    if (DAT_004bcc48 != 0) {
        DAT_004bcc48();
    }
}
