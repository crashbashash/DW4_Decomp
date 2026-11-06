/* Reports whether the named file exists: splits the path into device and file names
 * (FUN_0026fe00), finds the device interface (FUN_0026fbb8) and calls its entry +64; errors are
 * reported through FUN_0026f530 and return 0. */
typedef struct CvFsDevice_270800 {
    void *pad0[16];
    int (*is_exist_file)(const char *name);  /* 0x40 */
} CvFsDevice_270800;

extern char cvFsIsExistFile_1_illegal_file_name[]; /* 'cvFsIsExistFile #1:illegal file name' */
extern char cvFsIsExistFile_3_device_not_found[]; /* 'cvFsIsExistFile #3:device not found' */
extern char cvFsIsExistFile_4_vtbl_error[]; /* 'cvFsIsExistFile #4:vtbl error' */
void FUN_0026f530(const char *message);
void FUN_0026fe00(char *device_name, char *file_name, const char *path);
CvFsDevice_270800 *FUN_0026fbb8(const char *device_name, const char *file_name, const char *path);

int FUN_00270800(const char *path) {
    char device_name[304];
    char file_name[304];
    CvFsDevice_270800 *device;

    FUN_0026fe00(device_name, file_name, path);
    if (file_name[0] == 0) {
        FUN_0026f530(cvFsIsExistFile_1_illegal_file_name);
        return 0;
    }
    device = FUN_0026fbb8(device_name, file_name, path);
    if (device == 0) {
        /* Retail reports the miss and still reads the interface entry. */
        FUN_0026f530(cvFsIsExistFile_3_device_not_found);
    }
    if (device->is_exist_file != 0) {
        return device->is_exist_file(file_name);
    }
    FUN_0026f530(cvFsIsExistFile_4_vtbl_error);
    return 0;
}
