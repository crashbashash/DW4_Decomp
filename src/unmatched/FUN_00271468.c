/* 0x00271468 — FUN_00271468 (180 bytes). Returns the 64-bit size of the named file: finds its device (FUN_0026fe00/FUN_0026fbb8) and, when the device has option function 1 (+96), asks it for the high (code 202) and low (code 203) 32-bit halves; 0 when there is no option function. Sony EE GCC 2.96 unit (docs/engine/sd-prologue.md). */
typedef struct CvFsDevice_271468 {
    void *pad0[24];
    int (*opt_fn1)(const char *path, int code, char *file_name, int arg);  /* 0x60 */
} CvFsDevice_271468;

void FUN_0026fe00(char *device_name, char *file_name, const char *path);
CvFsDevice_271468 *FUN_0026fbb8(const char *device_name, const char *file_name, const char *path);

long FUN_00271468(const char *path) {
    char device_name[304];
    char file_name[304];
    CvFsDevice_271468 *device;
    long size = 0;
    int high;

    FUN_0026fe00(device_name, file_name, path);
    device = FUN_0026fbb8(device_name, file_name, path);
    if (device->opt_fn1 != 0) {
        high = device->opt_fn1(path, 202, file_name, 0);
        size = ((long)high << 32) + (unsigned int)device->opt_fn1(path, 203, file_name, 0);
    }
    return size;
}

