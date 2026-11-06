/* ADXT_EntryFnameRange (name from the error string at DAT_004ee0d0): adds a file-name range to the
 * play handle file list through FUN_00277038, reporting "Can't entry file" with the name through
 * FUN_00260840 on failure. */
typedef struct AdxtHandle {
    char f0[148];
    void *fileList;
} AdxtHandle;

int FUN_00277038(void *fileList, const char *name, int a, int b, int c);
void FUN_002607e8(const char *message);
void FUN_00260840(const char *message, const char *detail);
extern char DAT_004ee0d0[]; /* "E02080848 ADXT_EntryFnameRange: parameter error" */
extern char DAT_004ee100[]; /* "E4063001:Can't entry file " */

void FUN_00263768(AdxtHandle *handle, const char *name, int first, int last) {
    /* the file list is read before the null check (retail loads it in the branch delay slot) */
    void *fileList = handle->fileList;

    if (handle == 0) {
        FUN_002607e8(DAT_004ee0d0);
        return;
    }
    if (FUN_00277038(fileList, name, 0, first, last) < 0) {
        FUN_00260840(DAT_004ee100, name);
    }
}
