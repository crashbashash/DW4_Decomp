/* 0x002701c8 — FUN_002701c8 (88 bytes). Stops the transfer through the device interface (entry +40) of a file-system handle; a NULL handle or missing entry is reported through FUN_0026f530 and nothing happens. Its error strings name it cvFsStopTr (CRI), a name hypothesis. Sony EE GCC 2.96 unit (docs/engine/sd-prologue.md). */
typedef struct CvFsDevice_2701c8 {
    void *pad0[10];
    void (*stop_tr)(int file);  /* 0x28 */
} CvFsDevice_2701c8;

typedef struct CvFsHandle_2701c8 {
    CvFsDevice_2701c8 *device;  /* 0x00 */
    int file;                  /* 0x04 */
} CvFsHandle_2701c8;

extern char s_cvFsStopTr_1_handle_error_004ef1d0[]; /* 'cvFsStopTr #1:handle error' */
extern char s_cvFsStopTr_2_vtbl_error_004ef1f0[]; /* 'cvFsStopTr #2:vtbl error' */
void FUN_0026f530(const char *message);

void FUN_002701c8(CvFsHandle_2701c8 *handle) {
    if (handle == 0) {
        FUN_0026f530(s_cvFsStopTr_1_handle_error_004ef1d0);
        return;
    }
    if (handle->device->stop_tr != 0) {
        handle->device->stop_tr(handle->file);
        return;
    }
    FUN_0026f530(s_cvFsStopTr_2_vtbl_error_004ef1f0);
}
