/* Returns the record at +2208 of the handle's work area unless FUN_002a2f20 reports a positive
 * count; NULL without a work area. */
typedef struct SfdHandle {
    char pad0[13864];
    char *work;             /* +13864 */
} SfdHandle;

extern int FUN_002a2f20(SfdHandle *handle);

void *FUN_002a2ed0(SfdHandle *handle) {
    if (handle->work == 0) {
        return 0;
    }
    if (FUN_002a2f20(handle) > 0) {
        return 0;
    }
    return handle->work + 2208;
}
