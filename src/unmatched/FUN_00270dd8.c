/* 0x00270dd8 — FUN_00270dd8 (100 bytes). Calls the device option function 1 through the device interface (entry +96) of a file-system handle; a NULL handle or missing entry is reported through FUN_0026f530 and returns 0. Its error strings name it cvFsOptFn1 (CRI), a name hypothesis. Sony EE GCC 2.96 unit (docs/engine/sd-prologue.md). */
typedef struct CvFsDevice_270dd8 {
    void *pad0[24];
    int (*opt_fn1)(int file, int code, int arg);  /* 0x60 */
} CvFsDevice_270dd8;

typedef struct CvFsHandle_270dd8 {
    CvFsDevice_270dd8 *device;  /* 0x00 */
    int file;                  /* 0x04 */
} CvFsHandle_270dd8;

extern char s_cvFsOptFn1_1_handle_error_004ef820[]; /* 'cvFsOptFn1 #1:handle error' */
extern char s_cvFsOptFn1_2_vtbl_error_004ef840[]; /* 'cvFsOptFn1 #2:vtbl error' */
void FUN_0026f530(const char *message);

int FUN_00270dd8(CvFsHandle_270dd8 *handle, int code, int arg) {
    int result = 0;

    if (handle == 0) {
        FUN_0026f530(s_cvFsOptFn1_1_handle_error_004ef820);
        return 0;
    }
    if (handle->device->opt_fn1 != 0) {
        result = handle->device->opt_fn1(handle->file, code, arg);
    } else {
        FUN_0026f530(s_cvFsOptFn1_2_vtbl_error_004ef840);
    }
    return result;
}
