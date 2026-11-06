/* Calls the device option function 1 through the device interface (entry +96) of a file-system
 * handle; a NULL handle or missing entry is reported through FUN_0026f530 and returns 0. Its error
 * strings name it cvFsOptFn1 (CRI). */
typedef struct CvFsDevice_270dd8 {
    void *pad0[24];
    int (*opt_fn1)(int file, int code, int arg);  /* 0x60 */
} CvFsDevice_270dd8;

typedef struct CvFsHandle_270dd8 {
    CvFsDevice_270dd8 *device;  /* 0x00 */
    int file;                  /* 0x04 */
} CvFsHandle_270dd8;

extern char cvFsOptFn1_1_handle_error[]; /* 'cvFsOptFn1 #1:handle error' */
extern char cvFsOptFn1_2_vtbl_error[]; /* 'cvFsOptFn1 #2:vtbl error' */
void FUN_0026f530(const char *message);

int FUN_00270dd8(CvFsHandle_270dd8 *handle, int code, int arg) {
    int result = 0;

    if (handle == 0) {
        FUN_0026f530(cvFsOptFn1_1_handle_error);
        return 0;
    }
    if (handle->device->opt_fn1 != 0) {
        result = handle->device->opt_fn1(handle->file, code, arg);
    } else {
        FUN_0026f530(cvFsOptFn1_2_vtbl_error);
    }
    return result;
}
