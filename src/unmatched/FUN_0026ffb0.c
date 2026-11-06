/* Closes a file-system handle: calls the device's close entry (vtable +20) on the device file,
 * then releases the handle with FUN_0026fdf0; a NULL handle or missing entry is reported through
 * FUN_0026f530. */
typedef struct FsDevice_26ffb0 {
    int pad0[5];
    void (*close)(int file);    /* 0x14 */
} FsDevice_26ffb0;

typedef struct FsHandle_26ffb0 {
    FsDevice_26ffb0 *device;    /* 0x00 */
    int file;                   /* 0x04 */
} FsHandle_26ffb0;

extern char cvFsClose_1_handle_error[]; /* 'cvFsClose #1:handle error' */
extern char cvFsClose_2_vtbl_error[];   /* 'cvFsClose #2:vtbl error' */
void FUN_0026f530(const char *message);
void FUN_0026fdf0(FsHandle_26ffb0 *handle);

void FUN_0026ffb0(FsHandle_26ffb0 *handle) {
    if (handle == 0) {
        FUN_0026f530(cvFsClose_1_handle_error);
        return;
    }
    if (handle->device->close != 0) {
        handle->device->close(handle->file);
        FUN_0026fdf0(handle);
        return;
    }
    FUN_0026f530(cvFsClose_2_vtbl_error);
}
