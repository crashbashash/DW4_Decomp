typedef struct {
    void *pad0[24];
    int (*opt_fn1)(const char *path, int code, char *file_name, int arg);
} CvFsDevice;

void FUN_0026fe00(char *device_name, char *file_name, const char *path);
CvFsDevice *FUN_0026f890(const char *device_name);

long FUN_00271520(const char *path, int arg)
{
    char device_name[304];
    char file_name[304];
    CvFsDevice *device;
    long size;
    int high;

    device = FUN_0026f890(device_name);
    if (device == 0) {
        return 0;
    }
    FUN_0026fe00(device_name, file_name, path);
    size = 0;
    if (device->opt_fn1 != 0) {
        high = device->opt_fn1(path, 204, file_name, arg);
        size = ((long)high << 32) + (unsigned int)device->opt_fn1(path, 205, file_name, arg);
    }
    return size;
}
