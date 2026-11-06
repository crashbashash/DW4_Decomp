/* Requests a write through the device interface (entry +36) of a file-system handle; a NULL handle
 * or missing entry is reported through FUN_0026f530 and returns 0. Its error strings name it
 * cvFsReqWr (CRI), a name hypothesis. */
typedef struct CvFsDevice_270160 {
    void *pad0[9];
    int (*req_wr)(int file, int sectors, void *buffer);  /* 0x24 */
} CvFsDevice_270160;

typedef struct CvFsHandle_270160 {
    CvFsDevice_270160 *device;  /* 0x00 */
    int file;                  /* 0x04 */
} CvFsHandle_270160;

extern char cvFsReqWr_1_handle_error[]; /* 'cvFsReqWr #1:handle error' */
extern char cvFsReqWr_2_vtbl_error[]; /* 'cvFsReqWr #2:vtbl error' */
void FUN_0026f530(const char *message);

int FUN_00270160(CvFsHandle_270160 *handle, int sectors, void *buffer) {
    int result = 0;

    if (handle == 0) {
        FUN_0026f530(cvFsReqWr_1_handle_error);
        return 0;
    }
    if (handle->device->req_wr != 0) {
        result = handle->device->req_wr(handle->file, sectors, buffer);
    } else {
        FUN_0026f530(cvFsReqWr_2_vtbl_error);
    }
    return result;
}
