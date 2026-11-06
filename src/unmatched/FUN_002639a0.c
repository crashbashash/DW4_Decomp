/* ADXT_StartFnameRangeLp (name from the error string at DAT_004ee1d8): resets the play handle file
 * list, enters the name range with FUN_00263768, enables looping on the list and starts playback
 * with FUN_002638a0. */
typedef struct AdxtHandle {
    char f0[148];
    void *fileList;
} AdxtHandle;

void FUN_00277278(void *fileList);
void FUN_00263768(AdxtHandle *handle, const char *name, int first, int last);
void FUN_00277768(void *fileList, int enable);
void FUN_002638a0(AdxtHandle *handle);
void FUN_002607e8(const char *message);
extern char DAT_004ee1d8[]; /* "E02080852 ADXT_StartFnameRangeLp: parameter error" */

void FUN_002639a0(AdxtHandle *handle, const char *name, int first, int last) {
    void *fileList;

    if (handle == 0 || name == 0) {
        FUN_002607e8(DAT_004ee1d8);
        return;
    }
    fileList = handle->fileList;
    FUN_00277278(fileList);
    FUN_00263768(handle, name, first, last);
    FUN_00277768(fileList, 1);
    FUN_002638a0(handle);
}
