/* Destroys a handle: stops it through FUN_00275e50 when its state byte (+2) is 2 or more; unless
 * the shared flag (+1) is set, closes its file (+24) through FUN_00272918 between the
 * 0x5000/0x5001 trace markers and logs "HTCI: Failed sceClose" on failure; then clears the in-use
 * byte and releases it through FUN_002759b8. */
struct Handle275 {
    signed char used;      /* +0 */
    signed char shared;    /* +1 */
    unsigned char state;   /* +2 */
    char pad3[21];
    int fd;                /* +24: host file descriptor */
};

extern void FUN_00275e50(struct Handle275 *handle);
extern void FUN_002725a0(int marker);
extern int FUN_00272918(int fd);
extern void FUN_00265928(const char *message);
extern void FUN_002759b8(struct Handle275 *handle);
extern const char HTCI_Failed_sceClose[];

void FUN_00275b50(struct Handle275 *handle) {
    int result;

    if (handle != 0) {
        if (handle->state >= 2) {
            FUN_00275e50(handle);
        }
        if (handle->shared == 0) {
            FUN_002725a0(0x5000);
            result = FUN_00272918(handle->fd);
            FUN_002725a0(0x5001);
            if (result < 0) {
                FUN_00265928(HTCI_Failed_sceClose);
            }
        }
        handle->used = 0;
        FUN_002759b8(handle);
    }
}
