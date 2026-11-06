/* Returns the maximum byte rate through the device interface (entry +76) of a file-system handle;
 * a NULL handle or missing entry is reported through FUN_0026f530 and returns 0. Its error strings
 * name it cvFsGetMaxByteRate (CRI), a name hypothesis. */
typedef struct CvFsDevice_270a90 {
    void *pad0[19];
    int (*get_max_byte_rate)(int file);  /* 0x4c */
} CvFsDevice_270a90;

typedef struct CvFsHandle_270a90 {
    CvFsDevice_270a90 *device;  /* 0x00 */
    int file;                  /* 0x04 */
} CvFsHandle_270a90;

extern char cvFsGetMaxByteRate_1_handle_error[]; /* 'cvFsGetMaxByteRate #1:handle error' */
extern char cvFsGetMaxByteRate_2_vtbl_error[]; /* 'cvFsGetMaxByteRate #2:vtbl error' */
void FUN_0026f530(const char *message);

int FUN_00270a90(CvFsHandle_270a90 *handle) {
    if (handle == 0) {
        FUN_0026f530(cvFsGetMaxByteRate_1_handle_error);
    } else if (handle->device->get_max_byte_rate != 0) {
        return handle->device->get_max_byte_rate(handle->file);
    } else {
        FUN_0026f530(cvFsGetMaxByteRate_2_vtbl_error);
    }
    return 0;
}
