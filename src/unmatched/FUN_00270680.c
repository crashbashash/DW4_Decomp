/* 0x00270680 — FUN_00270680 (88 bytes). Sets the sector length through the device interface (entry +52) of a file-system handle; a NULL handle or missing entry is reported through FUN_0026f530 and nothing happens. Its error strings name it cvFsSetSctLen (CRI), a name hypothesis. Sony EE GCC 2.96 unit (docs/engine/sd-prologue.md). */
typedef struct CvFsDevice_270680 {
    void *pad0[13];
    void (*set_sct_len)(int file, int length);  /* 0x34 */
} CvFsDevice_270680;

typedef struct CvFsHandle_270680 {
    CvFsDevice_270680 *device;  /* 0x00 */
    int file;                  /* 0x04 */
} CvFsHandle_270680;

extern char cvFsSetSctLen_3_handle_error[]; /* 'cvFsSetSctLen #3:handle error' */
extern char cvFsSetSctLen_4_vtbl_error[]; /* 'cvFsSetSctLen #4:vtbl error' */
void FUN_0026f530(const char *message);

void FUN_00270680(CvFsHandle_270680 *handle, int length) {
    if (handle == 0) {
        FUN_0026f530(cvFsSetSctLen_3_handle_error);
        return;
    }
    if (handle->device->set_sct_len != 0) {
        handle->device->set_sct_len(handle->file, length);
        return;
    }
    FUN_0026f530(cvFsSetSctLen_4_vtbl_error);
}
