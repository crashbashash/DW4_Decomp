struct Ring00292f90 {
    char *start; /* +0 */
    int size;    /* +4 */
    char *cur;   /* +8 */
    int count;   /* +12 */
};

struct Prm00292f90 {
    char pad0[24];
    char *buf;   /* +24 */
    int size;    /* +28 */
};

void FUN_00292f90(char *obj, struct Prm00292f90 *prm) {
    struct Ring00292f90 *ring = (struct Ring00292f90 *)(obj + 512);
    int *p = (int *)(obj + 656);
    int i;

    ring->start = prm->buf;
    ring->size = prm->size;
    ring->cur = prm->buf;
    ring->count = 0;
    *(int *)(obj + 528) = 0;
    for (i = 31; i >= 0; i--) {
        *p-- = 0;
    }
}
