/* 0x00270e40 — FUN_00270e40 (100 bytes). Calls the device option function 2 through the device interface (entry +100) of a file-system handle; a NULL handle or missing entry is reported through FUN_0026f530 and returns 0. Its error strings name it cvFsOptFn2 (CRI), a name hypothesis. Sony EE GCC 2.96 unit (docs/engine/sd-prologue.md). */
typedef struct CvFsDevice_270e40 {
    void *pad0[25];
    int (*opt_fn2)(int file, int code, int arg);  /* 0x64 */
} CvFsDevice_270e40;

typedef struct CvFsHandle_270e40 {
    CvFsDevice_270e40 *device;  /* 0x00 */
    int file;                  /* 0x04 */
} CvFsHandle_270e40;

extern char cvFsOptFn2_1_handle_error[]; /* 'cvFsOptFn2 #1:handle error' */
extern char cvFsOptFn2_2_vtbl_error[]; /* 'cvFsOptFn2 #2:vtbl error' */
void FUN_0026f530(const char *message);

int FUN_00270e40(CvFsHandle_270e40 *handle, int code, int arg) {
    int result = 0;

    if (handle == 0) {
        FUN_0026f530(cvFsOptFn2_1_handle_error);
        return 0;
    }
    if (handle->device->opt_fn2 != 0) {
        result = handle->device->opt_fn2(handle->file, code, arg);
    } else {
        FUN_0026f530(cvFsOptFn2_2_vtbl_error);
    }
    return result;
}
