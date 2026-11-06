/* Returns the number of bytes transferred through the device interface (entry +56) of a file-
 * system handle; a NULL handle or missing entry is reported through FUN_0026f530 and returns 0.
 * */
typedef struct CvFsDevice_2706d8 {
    void *pad0[14];
    int (*get_num_tr)(int file);  /* 0x38 */
} CvFsDevice_2706d8;

typedef struct CvFsHandle_2706d8 {
    CvFsDevice_2706d8 *device;  /* 0x00 */
    int file;                  /* 0x04 */
} CvFsHandle_2706d8;

extern char cvFsGetNumTr_1_handle_error[]; /* 'cvFsGetNumTr #1:handle error' */
extern char cvFsGetNumTr_2_vtbl_error[]; /* 'cvFsGetNumTr #2:vtbl error' */
void FUN_0026f530(const char *message);

int FUN_002706d8(CvFsHandle_2706d8 *handle) {
    int result = 0;

    if (handle == 0) {
        FUN_0026f530(cvFsGetNumTr_1_handle_error);
        return 0;
    }
    if (handle->device->get_num_tr != 0) {
        result = handle->device->get_num_tr(handle->file);
    } else {
        FUN_0026f530(cvFsGetNumTr_2_vtbl_error);
    }
    return result;
}
