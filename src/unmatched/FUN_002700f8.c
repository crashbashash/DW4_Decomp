/* Requests a read through the device interface (entry +32) of a file-system handle; a NULL handle
 * or missing entry is reported through FUN_0026f530 and returns 0. Its error strings name it
 * cvFsReqRd (CRI), a name hypothesis. */
typedef struct CvFsDevice_2700f8 {
    void *pad0[8];
    int (*req_rd)(int file, int sectors, void *buffer);  /* 0x20 */
} CvFsDevice_2700f8;

typedef struct CvFsHandle_2700f8 {
    CvFsDevice_2700f8 *device;  /* 0x00 */
    int file;                  /* 0x04 */
} CvFsHandle_2700f8;

extern char cvFsReqRd_1_handle_error[]; /* 'cvFsReqRd #1:handle error' */
extern char cvFsReqRd_2_vtbl_error[]; /* 'cvFsReqRd #2:vtbl error' */
void FUN_0026f530(const char *message);

int FUN_002700f8(CvFsHandle_2700f8 *handle, int sectors, void *buffer) {
    int result;

    if (handle == 0) {
        FUN_0026f530(cvFsReqRd_1_handle_error);
        return 0;
    }
    if (handle->device->req_rd != 0) {
        result = handle->device->req_rd(handle->file, sectors, buffer);
    } else {
        result = 0;
        FUN_0026f530(cvFsReqRd_2_vtbl_error);
    }
    return result;
}
