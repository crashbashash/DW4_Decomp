/* 0x0026fbb8 — FUN_0026fbb8 (168 bytes). Finds the device interface for a split path: an empty device name takes the default device (FUN_0026ff48); FUN_00271318 adjusts the names and FUN_0026f890 looks the device up. If that fails, the default device is tried and the whole path becomes the file name. Returns the interface or 0. Sony EE GCC 2.96 unit (docs/engine/sd-prologue.md). */
void FUN_0026ff48(char *device_name);
void FUN_00271318(char *device_name, char *file_name);
void *FUN_0026f890(const char *device_name);
char *strcpy(char *dst, const char *src);

void *FUN_0026fbb8(char *device_name, char *file_name, const char *path) {
    void *device;

    if (device_name[0] == 0) {
        FUN_0026ff48(device_name);
        if (device_name[0] == 0) {
            return 0;
        }
    }
    FUN_00271318(device_name, file_name);
    device = FUN_0026f890(device_name);
    if (device == 0) {
        FUN_0026ff48(device_name);
        device = FUN_0026f890(device_name);
        if (device == 0) {
            return 0;
        }
        strcpy(file_name, path);
    }
    return device;
}
