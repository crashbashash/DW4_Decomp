/* 0x002713d0 — FUN_002713d0 (152 bytes). Reports DAT_004efb40 through FUN_0026f530 and returns 0 for a null object; otherwise returns the 64-bit value whose high word is query 200 and low word query 201 of the object's slot-24 function (0 when that slot is empty). Sony EE GCC 2.96 unit (docs/engine/sd-prologue.md). */
typedef struct DeviceTable_2713d0 {
    void *slot[24];
    int (*query)(void *handle, int code, int a2, int a3);  /* +0x60 */
} DeviceTable_2713d0;

typedef struct Device_2713d0 {
    DeviceTable_2713d0 *table;  /* 0x00 */
    void *handle;               /* 0x04 */
} Device_2713d0;

extern char DAT_004efb40[];
void FUN_0026f530(const char *message);

long long FUN_002713d0(Device_2713d0 *device) {
    long long value = 0;

    if (device == 0) {
        FUN_0026f530(DAT_004efb40);
        return 0;
    }
    if (device->table->query != 0) {
        value = ((long long)device->table->query(device->handle, 200, 0, 0) << 32) + (unsigned int)device->table->query(device->handle, 201, 0, 0);
    }
    return value;
}
