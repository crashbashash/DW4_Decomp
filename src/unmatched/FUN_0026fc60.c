typedef struct {
    void *pad0[4];
    void *(*open)(const char *name, void *atr, int rw);
} CvFsDevice;

typedef struct {
    CvFsDevice *device;
    void *fd;
} CvFsHandle;

extern char DAT_004ef000[];
extern char DAT_004ef020[];
extern char DAT_004ef068[];
extern char DAT_004ef088[];
extern char DAT_004ef0a0[];
void FUN_0026f530(const char *message);
void FUN_0026fe00(char *device_name, char *file_name, const char *path);
CvFsDevice *FUN_0026fbb8(char *device_name, char *file_name, const char *path);
CvFsHandle *FUN_0026fd88(void);
void FUN_0026fdf0(CvFsHandle *handle);

CvFsHandle *FUN_0026fc60(const char *path, void *atr, int rw)
{
    char device_name[304];
    char file_name[304];
    CvFsHandle *handle;
    CvFsDevice *device;

    if (path == 0) {
        FUN_0026f530(DAT_004ef000);
        return 0;
    }
    FUN_0026fe00(device_name, file_name, path);
    if (file_name[0] == 0) {
        FUN_0026f530(DAT_004ef000);
        return 0;
    }
    handle = FUN_0026fd88();
    if (handle == 0) {
        FUN_0026f530(DAT_004ef020);
        return 0;
    }
    device = FUN_0026fbb8(device_name, file_name, path);
    handle->device = device;
    if (device == 0) {
        FUN_0026fdf0(handle);
        FUN_0026f530(DAT_004ef068);
        return 0;
    }
    if (device->open != 0) {
        handle->fd = device->open(file_name, atr, rw);
    } else {
        FUN_0026fdf0(handle);
        FUN_0026f530(DAT_004ef088);
        return 0;
    }
    if (handle->fd == 0) {
        FUN_0026fdf0(handle);
        FUN_0026f530(DAT_004ef0a0);
        return 0;
    }
    return handle;
}
