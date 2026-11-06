/* Returns the state byte (+2) of a handle, reporting a null handle and returning 0 for it. */
struct Handle275 {
    signed char used;      /* +0 */
    signed char shared;    /* +1 */
    signed char state;     /* +2 */
    char pad3[21];
    int fd;                /* +24 */
    int value28;           /* +28 */
    char pad32[8];
    int sectors;           /* +40 */
};

extern void FUN_002753d8(int detail, const char *message);
extern const char E0092712_handl_is_null[];

int FUN_00275f48(struct Handle275 *handle) {
    if (handle == 0) {
        FUN_002753d8(0, E0092712_handl_is_null);
        return 0;
    }
    return handle->state;
}
