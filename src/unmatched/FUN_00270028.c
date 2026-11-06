/* Returns the current file position through the device interface (entry +28) of a file-system
 * handle; a NULL handle or missing entry is reported through FUN_0026f530 and returns 0. Its error
 * strings name it cvFsTell (CRI). */
typedef struct CvFsDevice_270028 {
    void *pad0[7];
    int (*tell)(int file);  /* 0x1c */
} CvFsDevice_270028;

typedef struct CvFsHandle_270028 {
    CvFsDevice_270028 *device;  /* 0x00 */
    int file;                  /* 0x04 */
} CvFsHandle_270028;

extern char cvFsTell_1_handle_error[]; /* 'cvFsTell #1:handle error' */
extern char cvFsTell_2_vtbl_error[]; /* 'cvFsTell #2:vtbl error' */
void FUN_0026f530(const char *message);

int FUN_00270028(CvFsHandle_270028 *handle) {
    int result;

    if (handle == 0) {
        FUN_0026f530(cvFsTell_1_handle_error);
        return 0;
    }
    if (handle->device->tell != 0) {
        result = handle->device->tell(handle->file);
    } else {
        result = 0;
        FUN_0026f530(cvFsTell_2_vtbl_error);
    }
    return result;
}
