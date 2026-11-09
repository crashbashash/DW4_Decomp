typedef struct {
    void *pad0[18];
    int (*fn)(const char *path, int a1, int a2);
} CvFsDevice;

extern char DAT_004ef580[];
void FUN_0026f530(const char *message);
void FUN_0026fe00(char *device_name, char *file_name, const char *path);
void FUN_0026ff48(char *device_name);
void FUN_00271318(char *device_name, char *file_name);
CvFsDevice *FUN_0026f890(const char *device_name);

int FUN_002709b8(const char *path, int a1, int a2)
{
    char device_name[304];
    char file_name[304];
    CvFsDevice *device;
    int result;

    FUN_0026fe00(device_name, file_name, path);
    result = 0;
    if (device_name[0] == 0) {
        FUN_0026ff48(device_name);
        if (device_name[0] == 0) {
            FUN_0026f530(DAT_004ef580);
            return 0;
        }
    }
    FUN_00271318(device_name, file_name);
    device = FUN_0026f890(device_name);
    if (device != 0 && device->fn != 0) {
        result = device->fn(path, a1, a2);
    }
    return result;
}
