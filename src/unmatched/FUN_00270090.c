/* 0x00270090 — FUN_00270090 (104 bytes). Moves the file position through the device interface (entry +24) of a file-system handle; a NULL handle or missing entry is reported through FUN_0026f530 and returns 0. Its error strings name it cvFsSeek (CRI), a name hypothesis. Sony EE GCC 2.96 unit (docs/engine/sd-prologue.md). */
typedef struct CvFsDevice_270090 {
    void *pad0[6];
    int (*seek)(int file, int offset, int origin);  /* 0x18 */
} CvFsDevice_270090;

typedef struct CvFsHandle_270090 {
    CvFsDevice_270090 *device;  /* 0x00 */
    int file;                  /* 0x04 */
} CvFsHandle_270090;

extern char s_cvFsSeek_1_handle_error_004ef128[]; /* 'cvFsSeek #1:handle error' */
extern char s_cvFsSeek_2_vtbl_error_004ef148[]; /* 'cvFsSeek #2:vtbl error' */
void FUN_0026f530(const char *message);

int FUN_00270090(CvFsHandle_270090 *handle, int offset, int origin) {
    int result;

    if (handle == 0) {
        FUN_0026f530(s_cvFsSeek_1_handle_error_004ef128);
        return 0;
    }
    if (handle->device->seek != 0) {
        result = handle->device->seek(handle->file, offset, origin);
    } else {
        result = 0;
        FUN_0026f530(s_cvFsSeek_2_vtbl_error_004ef148);
    }
    return result;
}
