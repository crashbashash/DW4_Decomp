/* 0x002706d8 — FUN_002706d8 (100 bytes). Returns the number of bytes transferred through the device interface (entry +56) of a file-system handle; a NULL handle or missing entry is reported through FUN_0026f530 and returns 0. Its error strings name it cvFsGetNumTr (CRI), a name hypothesis. Sony EE GCC 2.96 unit (docs/engine/sd-prologue.md). */
typedef struct CvFsDevice_2706d8 {
    void *pad0[14];
    int (*get_num_tr)(int file);  /* 0x38 */
} CvFsDevice_2706d8;

typedef struct CvFsHandle_2706d8 {
    CvFsDevice_2706d8 *device;  /* 0x00 */
    int file;                  /* 0x04 */
} CvFsHandle_2706d8;

extern char s_cvFsGetNumTr_1_handle_error_004ef480[]; /* 'cvFsGetNumTr #1:handle error' */
extern char s_cvFsGetNumTr_2_vtbl_error_004ef4a0[]; /* 'cvFsGetNumTr #2:vtbl error' */
void FUN_0026f530(const char *message);

int FUN_002706d8(CvFsHandle_2706d8 *handle) {
    int result = 0;

    if (handle == 0) {
        FUN_0026f530(s_cvFsGetNumTr_1_handle_error_004ef480);
        return 0;
    }
    if (handle->device->get_num_tr != 0) {
        result = handle->device->get_num_tr(handle->file);
    } else {
        FUN_0026f530(s_cvFsGetNumTr_2_vtbl_error_004ef4a0);
    }
    return result;
}
