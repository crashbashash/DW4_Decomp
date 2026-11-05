/* 0x0026ffb0 — FUN_0026ffb0 (116 bytes). Closes a file-system handle: calls the device's close entry (vtable +20) on the device file, then releases the handle with FUN_0026fdf0; a NULL handle or missing entry is reported through FUN_0026f530. Its error strings name it cvFsClose (CRI), a name hypothesis. Sony EE GCC 2.96 unit (docs/engine/sd-prologue.md). */
typedef struct FsDevice_26ffb0 {
    int pad0[5];
    void (*close)(int file);    /* 0x14 */
} FsDevice_26ffb0;

typedef struct FsHandle_26ffb0 {
    FsDevice_26ffb0 *device;    /* 0x00 */
    int file;                   /* 0x04 */
} FsHandle_26ffb0;

extern char s_cvFsClose_1_handle_error_004ef0b8[]; /* 'cvFsClose #1:handle error' */
extern char s_cvFsClose_2_vtbl_error_004ef0d8[];   /* 'cvFsClose #2:vtbl error' */
void FUN_0026f530(const char *message);
void FUN_0026fdf0(FsHandle_26ffb0 *handle);

void FUN_0026ffb0(FsHandle_26ffb0 *handle) {
    if (handle == 0) {
        FUN_0026f530(s_cvFsClose_1_handle_error_004ef0b8);
        return;
    }
    if (handle->device->close != 0) {
        handle->device->close(handle->file);
        FUN_0026fdf0(handle);
        return;
    }
    FUN_0026f530(s_cvFsClose_2_vtbl_error_004ef0d8);
}
