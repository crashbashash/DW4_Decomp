/* Opens a file by name: rejects a NULL name or a non-zero rw mode, takes a free handle
 * (FUN_00277fc0), copies the name to +28 and initialises it (FUN_00278038); failures are reported
 * through FUN_00277de8 and return 0. Its error strings name it mfCiOpen (CRI), a name hypothesis. */
typedef struct MfCi_2780a8 {
    char pad0[28];
    char name[1];   /* 0x1c */
} MfCi_2780a8;

extern char E01100301_fname_is_null_mfCiOpen[];                 /* 'E01100301:fname is null.(mfCiOpen)' */
extern char E01100302_rw_is_illigal_mfCiOpen[];                 /* 'E01100302:rw is illigal.(mfCiOpen)' */
extern char E01100303_not_enough_handle_resource_mfCiOpen[];    /* 'E01100303:not enough handle resource.(mfCiOpen)' */
void FUN_00277de8(void *handle, const char *message);
MfCi_2780a8 *FUN_00277fc0(void);
void FUN_00278038(MfCi_2780a8 *handle);
char *strcpy(char *dst, const char *src);

MfCi_2780a8 *FUN_002780a8(const char *fname, int reserved, int rw) {
    MfCi_2780a8 *handle;

    if (fname == 0) {
        FUN_00277de8(0, E01100301_fname_is_null_mfCiOpen);
        return 0;
    }
    if (rw != 0) {
        FUN_00277de8(0, E01100302_rw_is_illigal_mfCiOpen);
        return 0;
    }
    handle = FUN_00277fc0();
    if (handle == 0) {
        FUN_00277de8(0, E01100303_not_enough_handle_resource_mfCiOpen);
        return 0;
    }
    strcpy(handle->name, fname);
    FUN_00278038(handle);
    return handle;
}

