/* 0x0026f728 — FUN_0026f728 (144 bytes). Registers a file-system device: checks the device name and interface-function pointer, adds the device (FUN_0026f7b8) and, when its interface has an error-callback entry (+4), installs FUN_0026f500 there; failures are reported through FUN_0026f530. Its error strings name it cvFsAddDev (CRI), a name hypothesis. Sony EE GCC 2.96 unit (docs/engine/sd-prologue.md). */
typedef struct CvFsDevice_26f728 {
    void *pad0;
    void (*entry_err_func)(void (*callback)(), int object);  /* 0x04 */
} CvFsDevice_26f728;

/* Points at the "CVFS/PS2EE Ver.2.37" build string (0x4eeed8); read and discarded so the string stays linked. */
extern char *volatile DAT_004a9278;
extern char s_cvFsAddDev_1_illegal_device_name_004eef10[];   /* 'cvFsAddDev #1:illegal device name' */
extern char s_cvFsAddDev_2_illegal_I_F_func_name_004eef38[]; /* 'cvFsAddDev #2:illegal I/F func name' */
extern char s_cvFsAddDev_3_failed_added_a_device_004eef60[]; /* 'cvFsAddDev #3:failed added a device' */
void FUN_0026f530(const char *message);
void FUN_0026f500();
CvFsDevice_26f728 *FUN_0026f7b8(const char *name, void *(*get_interface)(void));

void FUN_0026f728(const char *name, void *(*get_interface)(void)) {
    CvFsDevice_26f728 *device;
    (void)DAT_004a9278;
    if (name == 0) {
        FUN_0026f530(s_cvFsAddDev_1_illegal_device_name_004eef10);
        return;
    }
    if (get_interface == 0) {
        FUN_0026f530(s_cvFsAddDev_2_illegal_I_F_func_name_004eef38);
        return;
    }
    device = FUN_0026f7b8(name, get_interface);
    if (device == 0) {
        FUN_0026f530(s_cvFsAddDev_3_failed_added_a_device_004eef60);
        return;
    }
    if (device->entry_err_func != 0) {
        device->entry_err_func(FUN_0026f500, 0);
    }
}

