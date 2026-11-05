/* 0x00270618 — FUN_00270618 (100 bytes). Returns the sector length through the device interface (entry +48) of a file-system handle; a NULL handle or missing entry is reported through FUN_0026f530 and returns 0. Its error strings name it cvFsGetSctLen (CRI), a name hypothesis. Sony EE GCC 2.96 unit (docs/engine/sd-prologue.md). */
typedef struct CvFsDevice_270618 {
    void *pad0[12];
    int (*get_sct_len)(int file);  /* 0x30 */
} CvFsDevice_270618;

typedef struct CvFsHandle_270618 {
    CvFsDevice_270618 *device;  /* 0x00 */
    int file;                  /* 0x04 */
} CvFsHandle_270618;

extern char s_cvFsGetSctLen_1_handle_error_004ef400[]; /* 'cvFsGetSctLen #1:handle error' */
extern char s_cvFsGetSctLen_2_vtbl_error_004ef420[]; /* 'cvFsGetSctLen #2:vtbl error' */
void FUN_0026f530(const char *message);

int FUN_00270618(CvFsHandle_270618 *handle) {
    int result = 0;

    if (handle == 0) {
        FUN_0026f530(s_cvFsGetSctLen_1_handle_error_004ef400);
        return 0;
    }
    if (handle->device->get_sct_len != 0) {
        result = handle->device->get_sct_len(handle->file);
    } else {
        FUN_0026f530(s_cvFsGetSctLen_2_vtbl_error_004ef420);
    }
    return result;
}
