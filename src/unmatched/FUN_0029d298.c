/* When option 6 is set, attaches the interface embedded at +13780 and initialises it. */
typedef struct SfdHandle {
    char pad0[8460];
    void *iface;            /* +8460 */
    char pad8464[5316];
    char ifaceStorage[4];   /* +13780 */
} SfdHandle;

extern int FUN_002adc40(SfdHandle *handle, int option);
extern void FUN_0029d2d8(void *iface);

int FUN_0029d298(SfdHandle *handle) {
    int result = FUN_002adc40(handle, 6);
    void *iface = handle->ifaceStorage;

    if (result != 0) {
        handle->iface = iface;
        FUN_0029d2d8(iface);
        result = 0;
    }
    return result;
}
