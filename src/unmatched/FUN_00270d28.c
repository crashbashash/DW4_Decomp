/* 0x00270d28 — FUN_00270d28 (132 bytes). Returns the name of the device a file-system handle uses, found by matching its interface in the 32-entry device table DAT_0056e220; a NULL handle is reported through FUN_0026f530 and returns 0. Its error string names it cvFsGetDevName (CRI), a name hypothesis. Sony EE GCC 2.96 unit (docs/engine/sd-prologue.md). */
typedef struct CvFsDevEntry_270d28 {
    void *device;   /* 0x00: interface table */
    char name[12];  /* 0x04 */
} CvFsDevEntry_270d28;  /* 0x10 bytes */

typedef struct CvFsHandle_270d28 {
    void *device;   /* 0x00 */
    int file;       /* 0x04 */
} CvFsHandle_270d28;

extern CvFsDevEntry_270d28 DAT_0056e220[32];
extern char s_cvFsGetDevName_1_vtbl_error_004ef800[]; /* 'cvFsGetDevName #1:vtbl error' */
void FUN_0026f530(const char *message);

char *FUN_00270d28(CvFsHandle_270d28 *handle) {
    int i;

    if (handle == 0) {
        FUN_0026f530(s_cvFsGetDevName_1_vtbl_error_004ef800);
        return 0;
    }
    for (i = 0; i < 32; i++) {
        if (DAT_0056e220[i].device == handle->device) {
            break;
        }
    }
    /* Retail does not check for a miss: it returns the name past the table. */
    return DAT_0056e220[i].name;
}
