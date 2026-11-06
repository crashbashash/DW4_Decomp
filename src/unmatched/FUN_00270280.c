/* Returns the transfer status through the device interface (entry +44) of a file-system handle; a
 * NULL handle or missing entry is reported through FUN_0026f530 and returns status 3 (error). Its
 * error strings name it cvFsGetStat (CRI), a name hypothesis. */
typedef struct CvFsDevice_270280 {
    void *pad0[11];
    int (*get_stat)(int file);  /* 0x2c */
} CvFsDevice_270280;

typedef struct CvFsHandle_270280 {
    CvFsDevice_270280 *device;  /* 0x00 */
    int file;                  /* 0x04 */
} CvFsHandle_270280;

extern char cvFsGetStat_1_handle_error[]; /* 'cvFsGetStat #1:handle error' */
extern char cvFsGetStat_2_vtbl_error[]; /* 'cvFsGetStat #2:vtbl error' */
void FUN_0026f530(const char *message);

int FUN_00270280(CvFsHandle_270280 *handle) {
    int result = 3; /* error status */

    if (handle == 0) {
        FUN_0026f530(cvFsGetStat_1_handle_error);
        return 3;
    }
    if (handle->device->get_stat != 0) {
        result = handle->device->get_stat(handle->file);
    } else {
        FUN_0026f530(cvFsGetStat_2_vtbl_error);
    }
    return result;
}
